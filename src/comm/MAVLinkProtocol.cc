/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2014 APM_PLANNER PROJECT <http://www.diydrones.com>

This file is part of the APM_PLANNER project

    APM_PLANNER is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    APM_PLANNER is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with APM_PLANNER. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief MAVLinkProtocol
 *          This class handles incoming mavlink_message_t packets.
 *          It will create a UAS class if one does not exist for a particular heartbeat systemid
 *          It will pass mavlink_message_t on to the UAS class for further parsing


이 클래스는 수신 mavlink_message_t 패킷을 처리합니다.
 * 특정 하트 비트 시스템 ID가 없으면 UAS 클래스를 만듭니다.
 * 추가 파싱을 위해 UAS 클래스에 mavlink_message_t를 전달합니다.


 *
 *   @author Michael Carpenter <malcom2073@gmail.com>
 *   @author QGROUNDCONTROL PROJECT - This code has GPLv3+ snippets from QGROUNDCONTROL, (c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 */


#include "MAVLinkProtocol.h"
#include "LinkManager.h"

#include <cstring>
#include <QDataStream>

MAVLinkProtocol::MAVLinkProtocol():
    m_isOnline(true),
    m_loggingEnabled(false),
    m_throwAwayGCSPackets(false),
    m_connectionManager(nullptr),
    versionMismatchIgnore(false),
    m_enable_version_check(false)
{
}

MAVLinkProtocol::~MAVLinkProtocol()
{
    stopLogging();
}

void MAVLinkProtocol::sendMessage(mavlink_message_t msg)
{
    Q_UNUSED(msg);
}

void MAVLinkProtocol::receiveBytes(LinkInterface* link, const QByteArray &dataBytes)
{
    static int nonmavlinkCount = 0;
    static int radioVersionMismatchCount = 0;
    static bool decodedFirstPacket = false;
    static bool checkedUserNonMavlink = false;
    static bool warnedUserNonMavlink = false;

    mavlink_message_t message;
    memset(&message, 0, sizeof(mavlink_message_t));
    mavlink_status_t status;

    // Cache the link ID for common use.	 일반적인 사용을 위해 링크 ID를 캐시합니다.  
    quint8 linkId = static_cast<quint8>(link->getId());

    for(const auto &data : dataBytes)
    {
        unsigned int decodeState = mavlink_parse_char(MAVLINK_COMM_0, static_cast<quint8>(data), &message, &status);

        if (decodeState == 0 && !decodedFirstPacket)
        {
            nonmavlinkCount++;
            if (nonmavlinkCount > 2000 && !warnedUserNonMavlink)
            {
                //2000 bytes with no mavlink message. Are we connected to a mavlink capable device?	 mavlink 메시지가없는 2000 바이트. 우리는 mavlink 가능 장치에 연결되어 있습니까?  
                if (!checkedUserNonMavlink)
                {
                    link->requestReset();
                    nonmavlinkCount=0;
                    checkedUserNonMavlink = true;
                }
                else
                {
                    warnedUserNonMavlink = true;
                    emit protocolStatusMessage("MAVLink Baud Rate or Version Mismatch", "Please check if the baud rates of APM Planner and your autopilot are the same.");
                }
            }
        }

        if (decodeState == 1)
        {
            mavlink_status_t* mavlinkStatus = mavlink_get_channel_status(MAVLINK_COMM_0);
            if (!decodedFirstPacket)
            {
                decodedFirstPacket = true;

                if (mavlinkStatus->flags & MAVLINK_STATUS_FLAG_IN_MAVLINK1)
                {
                    QLOG_INFO() << "First Mavlink message is version 1.0. Using mavlink 1.0 and ask for mavlink 2.0 capability";
                    mavlinkStatus->flags |= MAVLINK_STATUS_FLAG_OUT_MAVLINK1;

                    // Request AUTOPILOT_VERSION message to check if vehicle is mavlink 2.0 capable	 차량이 mavlink 2.0을 지원하는지 확인하기 위해 AUTOPILOT_VERSION 메시지를 요청한다.  
                    mavlink_command_long_t command;
                    mavlink_message_t commandMessage;
                    uint8_t sendbuffer[MAVLINK_MAX_PACKET_LEN];
                    command.command = MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES;
                    command.param1 = 1.0f;

                    mavlink_msg_command_long_encode(message.sysid, message.compid, &commandMessage, &command);
                    // Write message into buffer, prepending start sign	 버퍼에 메시지를 쓰고 시작 기호를 앞에 쓴다.  
                    int len = mavlink_msg_to_send_buffer(sendbuffer, &commandMessage);
                    link->writeBytes(reinterpret_cast<const char*>(sendbuffer), len);
                    return;
                }
                else
                {
                    QLOG_INFO() << "First Mavlink message is version 2.0. Using Mavlink 2.0 for communication";
                    mavlinkStatus->flags &= ~MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
                }
            }

            // Check if we are receiving mavlink 2.0 while sending mavlink 1.0	 mavlink 1.0을 보내는 동안 mavlink 2.0을 받고 있는지 확인하십시오.  
            if (!(mavlinkStatus->flags & MAVLINK_STATUS_FLAG_IN_MAVLINK1) && (mavlinkStatus->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1))
            {
                QLOG_DEBUG() << "Switching outbound to mavlink 2.0 due to incoming mavlink 2.0 packet:" << mavlinkStatus << linkId << mavlinkStatus->flags;
                mavlinkStatus->flags &= ~MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
            }

            if(message.msgid == MAVLINK_MSG_ID_AUTOPILOT_VERSION)
            {
                mavlink_autopilot_version_t version;
                mavlink_msg_autopilot_version_decode(&message, &version);
                if(version.capabilities & MAV_PROTOCOL_CAPABILITY_MAVLINK2)
                {
                    QLOG_INFO() << "Vehicle reports mavlink 2.0 capability. Using Mavlink 2.0 for communication";
                    mavlinkStatus->flags &= ~MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
                }
                else
                {
                    QLOG_INFO() << "Vehicle reports mavlink 1.0 capability. Using Mavlink 1.0 for communication";
                    mavlinkStatus->flags |= MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
                }
            }

            else if(message.msgid == MAVLINK_MSG_ID_PING)
            {
                // process ping requests (tgt_system and tgt_comp must be zero)	 ping 요청을 처리합니다 (tgt_system 및 tgt_comp는 0이어야합니다)  
                mavlink_ping_t ping;
                mavlink_msg_ping_decode(&message, &ping);
                if(!ping.target_system && !ping.target_component && m_isOnline)
                {
                    mavlink_message_t msg;
                    mavlink_msg_ping_pack(s_SystemID, s_ComponentID, &msg, ping.time_usec, ping.seq, message.sysid, message.compid);
                    sendMessage(msg);
                }
            }

            else if(message.msgid == MAVLINK_MSG_ID_RADIO_STATUS)
            {
                // process telemetry status message	 텔레 메 트리 상태 메시지 처리  
                mavlink_radio_status_t rstatus;
                mavlink_msg_radio_status_decode(&message, &rstatus);
                int rssi = rstatus.rssi;
                int remrssi = rstatus.remrssi;
                // 3DR Si1k radio needs rssi fields to be converted to dBm	 3DR Si1k 라디오는 rssi 필드를 dBm으로 변환해야합니다.  
                if (message.sysid == '3' && message.compid == 'D')
                {
                    /* Per the Si1K datasheet figure 23.25 and SI AN474 code
                     * samples the relationship between the RSSI register
                     * and received power is as follows:
                     *
                     *                       10
                     * inputPower = rssi * ------ 127
                     *                       19
                     *
                     * Additionally limit to the only realistic range [-120,0] dBm
                     */

/*
                    / * Si1K 데이터 시트 그림 23.25 및 SI AN474 코드
                     * RSSI 레지스터 간의 관계를 샘플링합니다.
                     * 수신 전력은 다음과 같습니다.
                     *
                     * 10
                     * inputPower = rssi * ------ 127
                     * 19
                     *
                     * 유일하게 현실적인 범위 [-120,0] dBm에 추가로 제한
                     * /
*/

                    rssi    = qMin(qMax(qRound(static_cast<qreal>(rssi)    / 1.9 - 127.0), - 120), 0);
                    remrssi = qMin(qMax(qRound(static_cast<qreal>(remrssi) / 1.9 - 127.0), - 120), 0);
                }
                else
                {
                    rssi    = static_cast<qint8>(rstatus.rssi);
                    remrssi = static_cast<qint8>(rstatus.remrssi);
                }                
            }

            // Detect if we are talking to an old radio not supporting v2	 v2를 지원하지 않는 이전 라디오와 대화하고 있는지 감지합니다.  
            else if (message.msgid == MAVLINK_MSG_ID_RADIO_STATUS)
            {
                if ((mavlinkStatus->flags & MAVLINK_STATUS_FLAG_IN_MAVLINK1)
                        && !(mavlinkStatus->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1))
                {

                    radioVersionMismatchCount++;
                }
            }

            if (radioVersionMismatchCount == 5)
            {
                // Warn the user if the radio continues to send v1 while the link uses v2	 링크가 v2를 사용하는 동안 라디오가 v1을 계속 보내면 사용자에게 경고합니다.  
                emit protocolStatusMessage(tr("MAVLink Protocol"), tr("Detected radio still using MAVLink v1.0 on a link with MAVLink v2.0 enabled. Please upgrade the radio firmware."));
                // Ensure the warning can't get stuck	 경고가 멈추지 않도록하십시오.  
                radioVersionMismatchCount++;
                // Flick link back to v1	 v1로 다시 쓸어 넘김 링크  
                QLOG_DEBUG() << "Switching outbound to mavlink 1.0 due to incoming mavlink 1.0 packet:" << mavlinkStatus << linkId << mavlinkStatus->flags;
                mavlinkStatus->flags |= MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
            }

            // Log data	  데이터 로깅  
            if (m_loggingEnabled && !m_ScopedLogfilePtr.isNull())
            {
                quint64 time = QGC::groundTimeUsecs();
                uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

                QDataStream outStream(m_ScopedLogfilePtr.data());
                outStream.setByteOrder(QDataStream::BigEndian);
                outStream << time; // write time stamp	 타임 스탬프를 씁니다.  

                // write decoded message into buffer and buffer to disk	 디코드 된 메시지를 버퍼에 기록하고 버퍼를 디스크에 기록합니다.  
                int len = mavlink_msg_to_send_buffer(&buffer[0], &message);
                int bytesWritten = outStream.writeRawData(reinterpret_cast<const char*>(&buffer[0]), len);

                if(bytesWritten != len)
                {
                    emit protocolStatusMessage(tr("MAVLink Logging failed"),
                                               tr("Could not write to file %1, disabling logging.")
                                               .arg(m_ScopedLogfilePtr->fileName()));
                    // Stop logging	 로깅 중지  
                    stopLogging();
                }
            }

            if (m_isOnline)
            {
                 handleMessage(link, message);
            }
        }
    }
}

void MAVLinkProtocol::handleMessage(LinkInterface *link, const mavlink_message_t &message)
{
    // ORDER MATTERS HERE!
    // If the matching UAS object does not yet exist, it has to be created
    // before emitting the packetReceived signal

/*
    // 여기에서 순서를 결정하십시오!
    // 일치하는 UAS 객체가 아직 존재하지 않으면 생성해야합니다.
    // packetReceived 신호를 내기 전에
*/


    Q_ASSERT_X(m_connectionManager != NULL, "MAVLinkProtocol::receiveBytes", " error:m_connectionManager == NULL");
    UASInterface* uas = m_connectionManager->getUas(message.sysid);

    // Check and (if necessary) create UAS object	  UAS 객체를 확인하고 (필요한 경우) 만듭니다.  
    if ((uas == nullptr) && (message.msgid == MAVLINK_MSG_ID_HEARTBEAT))
    {
        // ORDER MATTERS HERE!
        // The UAS object has first to be created and connected,
        // only then the rest of the application can be made aware
        // of its existence, as it only then can send and receive
        // it's first messages.

/*
        // 여기에서 순서를 결정하십시오!
        // UAS 객체가 먼저 만들어지고 연결됩니다.
        // 그 다음에 만 나머지 응용 프로그램을 인식 할 수 있습니다.
        // 그것의 존재의, 그것만이 그 때 보내고받을 수 있던대로
        // 첫 번째 메시지입니다.
*/


        // Check if the UAS has the same id like this system	 UAS가이 시스템과 같은 ID를 가지고 있는지 확인  
        if (message.sysid == s_SystemID)
        {
            if (m_throwAwayGCSPackets)
            {
                //If replaying, we have to assume that it's just hearing ground control traffic	 재생하는 경우 청취 지상 컨트롤 트래픽이라고 가정해야합니다.  
                return;
            }
            emit protocolStatusMessage(tr("SYSTEM ID CONFLICT!"), tr("Warning: A second system is using the same system id (%1)").arg(s_SystemID));
        }

        // Create a new UAS based on the heartbeat received
        // Todo dynamically load plugin at run-time for MAV
        // WIKISEARCH:AUTOPILOT_TYPE_INSTANTIATION

/*
        // 수신 된 하트 비트를 기반으로 새 UAS를 만듭니다.
        // Todo가 MAV를 위해 런타임에 동적으로 플러그인을로드합니다.
        // WIKISEARCH : AUTOPILOT_TYPE_INSTANTIATION
*/


        // First create new UAS object
        // Decode heartbeat message

/*
        // 먼저 새 UAS 객체를 만듭니다.
        // 하트 비트 메시지 디코딩
*/

        mavlink_heartbeat_t heartbeat;
        // Reset version field to 0	  // 버전 필드를 0으로 재설정합니다.  
        heartbeat.mavlink_version = 0;
        mavlink_msg_heartbeat_decode(&message, &heartbeat);

        // Check if the UAS has a different protocol version
        // TODO Check if this is still needed!

/*
        // UAS의 프로토콜 버전이 다른지 확인
        // TODO 이것이 여전히 필요한지 확인하십시오!
*/

        if (m_enable_version_check && (heartbeat.mavlink_version != MAVLINK_VERSION))
        {
            // Bring up dialog to inform user	 사용자에게 알려주는 대화 상자를 표시합니다.  
            if (!versionMismatchIgnore)
            {
                emit protocolStatusMessage(tr("The MAVLink protocol version on the MAV and APM Planner mismatch!"),
                                           tr("It is unsafe to use different MAVLink versions. APM Planner therefore refuses to connect to system %1, which sends MAVLink version %2 (APM Planner uses version %3).").arg(message.sysid).arg(heartbeat.mavlink_version).arg(MAVLINK_VERSION));
                versionMismatchIgnore = true;
            }

            // Ignore this message and continue gracefully	 이 메시지를 무시하고 정상적으로 계속합니다.  
            return;
        }

        // Create a new UAS object	  새 UAS 객체를 만듭니다. 
        uas = m_connectionManager->createUAS(this,link,message.sysid,&heartbeat);
    }

    // Only count message if UAS exists for this message	 이 메시지에 대한 UAS가있는 경우에만 메시지 수를 계산합니다.  
    if (uas != nullptr)
    {

        // Increase receive counter	 수신 카운터를 늘립니다.  
        quint8 linkId = static_cast<quint8>(link->getId());
        totalReceiveCounter[linkId]++;
        currReceiveCounter[linkId]++;

        // Update last message sequence ID	 마지막 메시지 시퀀스 ID 업데이트  
        quint8 expectedSequence = 0;
        if (lastIndex.contains(message.sysid))
        {
            if (lastIndex.value(message.sysid).contains(message.compid))
            {
                //Sequence is uint8 type -> next value after 255 is 0. We do expect the overrun here!	 255가 0이되면 시퀀스는 uint8 타입 -> 다음 값입니다. 오버런이 예상됩니다!  
                expectedSequence = lastIndex[message.sysid][message.compid] + 1;
            }
            else
            {
                lastIndex[message.sysid].insert(message.compid, message.seq);
                expectedSequence = message.seq;
            }
        }
        else
        {
            lastIndex.insert(message.sysid,QMap<int, quint8>());
            lastIndex[message.sysid].insert(message.compid, message.seq);
            expectedSequence = message.seq;
        }

        // Make some noise if a message was skipped
        //QLOG_DEBUG() << "SYSID" << message.sysid << "COMPID" << message.compid << "MSGID" << message.msgid << "EXPECTED INDEX:" << expectedIndex << "SEQ" << message.seq;

/*
        // 메시지를 건너 뛰면 약간의 잡음이 들린다.
        // "SYSID"<< message.sysid << "COMPID"<< message.compid << "MSGID"<< message.msgid << "EXPEDED INDEX :"<< expectedIndex << "SEQ" 
*/

        if (message.seq != expectedSequence)
        {
            // Determine how many messages were skipped accounting for 0-wraparound	 건너 뛴 메시지의 수를 결정합니다.  
            int16_t lostMessages = message.seq - expectedSequence;
            if (lostMessages < 0)
            {
                // Usually, this happens in the case of an out-of order packet	 보통 이는 순서가 잘못된 패킷의 경우에 발생합니다.  
                lostMessages = 0;
            }
            else
            {
                // TODO Console generates excessive load at high loss rates, needs better GUI visualization
                //QLOG_DEBUG() << QString("Lost %1 messages for comp %4: expected sequence ID %2 but received %3.").arg(lostMessages).arg(expectedIndex).arg(message.seq).arg(message.compid);

/*
// TODO Console은 높은 손실 속도로 과도한로드를 생성하고 더 나은 GUI 시각화가 필요합니다.
                // QLOG_DEBUG () << QString ( "comp % 4에 대한 % 1 메시지 손실 : 예상 시퀀스 ID % 2이지만 % 3을 (를) 수신했습니다.") arg (lostMessages) .arg (expectedIndex) .arg (message.seq) .arg (message.compid);
*/

            }
            totalLossCounter[linkId] += lostMessages;
            currLossCounter[linkId] += lostMessages;
        }

        // Update the last sequence ID	 마지막 시퀀스 ID를 업데이트합니다.  
        lastIndex[message.sysid][message.compid] = message.seq;

        // Update on every 32th packet	 32 번째 패킷마다 업데이트  
        if (totalReceiveCounter[linkId] % 32 == 0)
        {
            // Calculate new receive loss ratio	 새 수신 손실 비율 계산  
            float receiveLoss = (double)currLossCounter[linkId]/(double)(currReceiveCounter[linkId]+currLossCounter[linkId]);
            receiveLoss *= 100.0f;
            currLossCounter[linkId] = 0;
            currReceiveCounter[linkId] = 0;
            emit receiveLossChanged(message.sysid, receiveLoss);
        }

        // The packet is emitted as a whole, as it is only 255 - 261 bytes short
        // kind of inefficient, but no issue for a groundstation pc.
        // It buys as reentrancy for the whole code over all threads

/*
        // 패킷은 255 - 261 바이트만큼 짧기 때문에 전체적으로 방출됩니다.
        // 종류가 비효율적이지만, 지상 PC에 대해서는 아무런 문제가 없습니다.
        // 모든 스레드에 대해 전체 코드의 재진입 성을 확보합니다.
*/

        emit messageReceived(link, message);
    }
}

void MAVLinkProtocol::stopLogging()
{
    if (!m_ScopedLogfilePtr.isNull() && m_ScopedLogfilePtr->isOpen())
    {
        QLOG_DEBUG() << "Stop MAVLink logging" << m_ScopedLogfilePtr->fileName();
        // Close the current open file	 현재 열려있는 파일을 닫습니다.  
        m_ScopedLogfilePtr->close();
        m_ScopedLogfilePtr.reset();
    }
    m_loggingEnabled = false;
}

bool MAVLinkProtocol::startLogging(const QString& filename)
{
    if (!m_ScopedLogfilePtr.isNull() && m_ScopedLogfilePtr->isOpen())
    {
        return true;
    }
    stopLogging();
    QLOG_DEBUG() << "Start MAVLink logging" << filename;

    m_ScopedLogfilePtr.reset(new QFile(filename));
    if (m_ScopedLogfilePtr->open(QIODevice::WriteOnly | QIODevice::Append))
    {
         m_loggingEnabled = true;
    }
    else
    {
        emit protocolStatusMessage(tr("Started MAVLink logging"),
                                   tr("FAILED: MAVLink cannot start logging to.").arg(m_ScopedLogfilePtr->fileName()));
        m_loggingEnabled = false;
        m_ScopedLogfilePtr.reset();
    }
    return m_loggingEnabled; // reflects if logging started or not.	  로깅이 시작되었는지 여부를 반영합니다.  
}
