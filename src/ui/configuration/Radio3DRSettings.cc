/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2013-2017 APM_PLANNER PROJECT <http://www.ardupilot.com>

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

#include "logging.h"
#include "Radio3DRSettings.h"
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>

#include <QMessageBox>
#include <QTimer>

Radio3DREeprom::Radio3DREeprom():
    m_deviceId(0),
    m_radioFreqCode(0),
    m_version(0),
    m_eepromVersion(0),
    m_serialSpeed(0),
    m_airSpeed(0),
    m_netID(0),
    m_txPower(0),
    m_ecc(0),
    m_mavlink(0),
    m_oppResend(0),
    m_minFreq(0),
    m_maxFreq(0),
    m_numChannels(0),
    m_dutyCyle(0),
    m_lbtRssi(0),
    m_manchester(0),
    m_rtsCts(0),
    m_maxWindow(0)
{

}

bool Radio3DREeprom::setParameter(QString &parameterString)
{
     QLOG_DEBUG() << "Radio3DREeprom Param:" << parameterString;
     QStringList values = parameterString.split("=", QString::SkipEmptyParts);
     bool success = false;

     if(values.length() == 0){
         QLOG_ERROR() << "Parameter String has Zero Params";
         return false;
     } else {
        success = true;
     }

     if(values[0].contains("S0:")){
         m_eepromVersion = values[1].toInt();

     } else if(values[0].contains("S1:")){
         m_serialSpeed = values[1].toInt();

     } else if(values[0].contains("S2:")){
         m_airSpeed = values[1].toInt();

     } else if(values[0].contains("S3:")){
         m_netID = values[1].toInt();

     } else if(values[0].contains("S4:")){
         m_txPower = values[1].toInt();

     } else if(values[0].contains("S5:")){
         m_ecc = values[1].toInt();

     } else if(values[0].contains("S6:")){
         m_mavlink = values[1].toInt();

     } else if(values[0].contains("S7:")){
         m_oppResend = values[1].toInt();

     } else if(values[0].contains("S8:")){
         m_minFreq = values[1].toInt();

     } else if(values[0].contains("S9:")){
         m_maxFreq = values[1].toInt();

     } else if(values[0].contains("S10:")){
         m_numChannels = values[1].toInt();

     } else if(values[0].contains("S11:")){
         m_dutyCyle = values[1].toInt();

     } else if(values[0].contains("S12:")){
         m_lbtRssi = values[1].toInt();

     } else if(values[0].contains("S13:")){
         m_manchester = values[1].toInt();

     } else if(values[0].contains("S14:")){
         m_rtsCts = values[1].toInt();

     } else if(values[0].contains("S15:")){
         m_maxWindow = values[1].toInt();
     }
     return success;
}

bool Radio3DREeprom::setVersion(const QString &versionString)
{
    QLOG_DEBUG() << "Radio3DREeprom Ver:" << versionString;
    QStringList values = versionString.split(" ", QString::SkipEmptyParts);

    if(values.count()>0 && values[0].contains("SiK")){
//        QRegExp versionEx("\\d\\*.\\d+");
//        int pos = versionEx.indexIn(versionString);
//        if (pos > -1) {
//            m_version = versionEx.cap(1).toFloat();
//        }
        QString majorMinorVersion(values[1]);
        majorMinorVersion.truncate(3); // [TODO] retrun x.n as the version for now
                                       // but this doesn't work for 1.10 and greater
                                       // Need to fix the above RegExp code to match
                                       // xx.nn (it should but doesn't
				       // [TODO] retrun xn을 지금 버전으로 사용
                                       // 하지만 1.10 이상에서는 작동하지 않습니다.
                                       // 일치하도록 위의 RegExp 코드를 수정해야합니다.
                                       // xx.nn (해야하지만하지 않습니다.
        m_version = majorMinorVersion.toFloat();

        // The number of params should be worked out from the returned ATI5 message
        // Or by using a lookup table of version to num of params.
        // 반환 된 ATI5 메시지에서 매개 변수 수를 계산해야합니다.
        // 또는 number of params에 대한 버전의 조회 테이블을 사용합니다.
        if (m_version < SIK_LOWLATENCY_MIN_VERSION){
            m_numberOfParams = 14;
            m_endParam = "S14";
        } else {
            m_numberOfParams = 15;
            m_endParam = "S15";
        }

    } else {
        return false;
    }
    m_versionString = versionString;
    return true;
}

bool Radio3DREeprom::setRadioFreqCode(int freqCode)
{
    m_radioFreqCode = freqCode;
    return true;
}

const QString Radio3DREeprom::formattedParameter(Mode mode, int index)
{
    QString modeString;

    if(mode == local) {
        modeString = "A";
    } else {
        modeString = "R";
    }
    QString command;

    switch(index){
    case 1:
        command = QString("%1TS1=%2\r\n").arg(modeString).arg(m_serialSpeed);
        break;
    case 2:
        command = QString("%1TS2=%2\r\n").arg(modeString).arg(m_airSpeed);
        break;
    case 3:
        command = QString("%1TS3=%2\r\n").arg(modeString).arg(m_netID);
        break;
    case 4:
        command = QString("%1TS4=%2\r\n").arg(modeString).arg(m_txPower);
        break;
    case 5:
        command = QString("%1TS5=%2\r\n").arg(modeString).arg(m_ecc);
        break;
    case 6:
        command = QString("%1TS6=%2\r\n").arg(modeString).arg(m_mavlink);
        break;
    case 7:
        command = QString("%1TS7=%2\r\n").arg(modeString).arg(m_oppResend);
        break;
    case 8:
        command = QString("%1TS8=%2\r\n").arg(modeString).arg(m_minFreq);
        break;
    case 9:
        command = QString("%1TS9=%2\r\n").arg(modeString).arg(m_maxFreq);
        break;
    case 10:
        command = QString("%1TS10=%2\r\n").arg(modeString).arg(m_numChannels);
        break;
    case 11:
        command = QString("%1TS11=%2\r\n").arg(modeString).arg(m_dutyCyle);
        break;
    case 12:
        command = QString("%1TS12=%2\r\n").arg(modeString).arg(m_lbtRssi);
        break;
    case 13:
        command = QString("%1TS13=%2\r\n").arg(modeString).arg(m_manchester);
        break;
    case 14:
        command = QString("%1TS14=%2\r\n").arg(modeString).arg(m_rtsCts);
        break;
    case 15:
        command = QString("%1TS15=%2\r\n").arg(modeString).arg(m_maxWindow);
        break;
    }

    QLOG_DEBUG() << "Setting Radio Parameter: " << command;
    return command;
}

const QString& Radio3DREeprom::versionString()
{
    return m_versionString;
}

QString Radio3DREeprom::frequencyCodeString()
{
        switch(m_radioFreqCode){
        case FREQ_915:
            return QString("FREQ_915");;

        case FREQ_433:
            return QString("FREQ_433");

        case FREQ_868:
            return QString("FREQ_868");

        default:
            return QString(); // Unknown
        }
}

QString Radio3DREeprom::deviceIdString()
{
        switch(m_deviceId){
        case DEVICE_ID_HM_TRP:
            return QString("HM_TRP");

        case DEVICE_ID_RFD900:
            return QString("RFD900");

        case DEVICE_ID_RFD900A:
            return QString("RFD900A");

        case DEVICE_ID_RFD900U:
            return QString("RFD900U");

        case DEVICE_ID_RFD900P:
            return QString("RFD900P");

        default:
            return QString(); // Unknown
        }
}

Radio3DRSettings::Radio3DRSettings(QObject *parent) :
    QObject(parent),
    m_state(none),
    m_serialPort(),
    m_retryCount(0)
{
    //  Command Set for 3DR SiK Radios
    //
    //        +++ - Escape to command mode (need 1s silence before it will work)
    //        ATI - show radio version
    //        ATI2 - show board type
    //        ATI3 - show board frequency
    //        ATI4 - show board version
    //        ATI5 - show all user settable EEPROM parameters
    //        ATI6 - display TDM timing report
    //        ATI7 - display RSSI signal report
    //        ATO - exit AT command mode
    //        ATSn? - display radio parameter number 'n'
    //        ATSn=X - set radio parameter number 'n' to 'X'
    //        ATZ - reboot the radio
    //        AT&W - write current parameters to EEPROM
    //        AT&F - reset all parameters to factory default
    //        AT&T=RSSI - enable RSSI debug reporting
    //        AT&T=TDM - enable TDM debug reporting
    //        AT&T - disable debug reporting
    //
    //        e.g.    ATI0 Version = SiK 1.5 on HM-TRP
    //                ATI5
    //                S0: FORMAT=25
    //                S1: SERIAL_SPEED=57
    //                S2: AIR_SPEED=64
    //                S3: NETID=41
    //                S4: TXPOWER=20
    //                S5: ECC=1
    //                S6: MAVLINK=1
    //                S7: OPPRESEND=1
    //                S8: MIN_FREQ=915000
    //                S9: MAX_FREQ=928000
    //                S10: NUM_CHANNELS=50
    //                S11: DUTY_CYCLE=100
    //                S12: LBT_RSSI=0
    //                S13: MANCHESTER=0
    //                S14: RTSCTS=0
    //                S15: MAX_WINDOW=131 // or 33 for SiK 1.8 and greater
    //   3DR SiK 라디오에 대한 명령 세트
    //
    //         +++ - 명령 모드로 탈출 (작동하기 전에 1s 침묵 필요)
    //         ATI - 라디오 버전 표시
    //         ATI2 - 보드 유형 표시
    //         ATI3 - 보드 주파수 표시
    //         ATI4 - 보드 버전 표시
    //         ATI5 - 사용자가 설정할 수있는 모든 EEPROM 매개 변수 표시
    //         ATI6 - TDM 타이밍 보고서를 표시합니다.
    //         ATI7 - RSSI 신호 보고서 표시
    //         ATO - AT 명령 모드를 종료합니다.
    //         ATSn? - 라디오 매개 변수 번호 'n'표시
    //         ATSn = X - 라디오 매개 변수 번호 'n'을 'X'로 설정합니다.
    //         ATZ - 라디오를 재부팅합니다.
    //         AT & W - 현재 매개 변수를 EEPROM에 씁니다.
    //         AT & F - 모든 매개 변수를 공장 기본값으로 재설정합니다.
    //         AT & T = RSSI - RSSI 디버그보고 활성화
    //         AT & T = TDM - TDM 디버그보고 활성화
    //         AT & T - 디버그보고 사용 안함
    //
    //         예 : HM-TRP에서 ATI0 Version = SiK 1.5
    //                 ATI5
    //                 S0 : FORMAT = 25
    //                 S1 : SERIAL_SPEED = 57
    //                 S2 : AIR_SPEED = 64
    //                 S3 : NETID = 41
    //                 S4 : TXPOWER = 20
    //                 S5 : ECC = 1
    //                 S6 : MAVLINK = 1
    //                 S7 : OPPRESEND = 1
    //                 S8 : MIN_FREQ = 915000
    //                 S9 : MAX_FREQ = 928000
    //                 S10 : NUM_CHANNELS = 50
    //                 S11 : DUTY_CYCLE = 100
    //                 S12 : LBT_RSSI = 0
    //                 S13 : 맨체스터 = 0
    //                 S14 : RTSCTS = 0
    //                 S15 : SiK 1.8 이상에서는 MAX_WINDOW = 131 // 또는 33
    m_timer.setSingleShot(true);
    m_timerReadWrite.setSingleShot(true);
}

Radio3DRSettings::~Radio3DRSettings()
{
    closeSerialPort();
}

bool Radio3DRSettings::openSerialPort(SerialSettings settings)
{
    if (!m_serialPort){
        m_serialPort.reset(new QSerialPort(settings.name, this));
        if (!m_serialPort){
            emit updateLocalStatus(tr("FAILED to create serial port"), red);
            return false;
        }
    }
    else
    {
        closeSerialPort();
    }

#if defined(Q_OS_MACX) && ((QT_VERSION == 0x050402)||(QT_VERSION == 0x0500401))
    // temp fix Qt5.4.1 issue on OSX
    // http://code.qt.io/cgit/qt/qtserialport.git/commit/?id=687dfa9312c1ef4894c32a1966b8ac968110b71e
    // temp는 OSX에서 Qt5.4.1 문제를 해결합니다.
    // http://code.qt.io/cgit/qt/qtserialport.git/commit/?id=687dfa9312c1ef4894c32a1966b8ac968110b71e
    m_serialPort->setPortName("/dev/cu." + settings.name);
#else
    m_serialPort->setPortName(settings.name);
#endif

    if(m_serialPort->open(QIODevice::ReadWrite)){
        // Start Reading the settings
        // 설정 읽기 시작
        QLOG_DEBUG() << "Radio3DRSettings Serial Port Open SUCCESS" << settings.name;
        // Serial Port Connections
        // 직렬 포트 연결

        QLOG_DEBUG() << "Port" << settings.name << settings.baudRate << settings.dataBits
                     << "FC" << settings.flowControl << "P" << settings.parity
                     << "SB" << settings.stopBits;
        if (m_serialPort->setBaudRate(settings.baudRate)
                && m_serialPort->setDataBits(settings.dataBits)
                && m_serialPort->setFlowControl(settings.flowControl)
                && m_serialPort->setParity(settings.parity)
                && m_serialPort->setStopBits(settings.stopBits)) {
            QLOG_INFO() << "Port Configured with success";
            connect(m_serialPort.data(), SIGNAL(error(QSerialPort::SerialPortError)), this,
                    SLOT(handleError(QSerialPort::SerialPortError)));

            connect(m_serialPort.data(), SIGNAL(readyRead()), this, SLOT(readData()));
            m_state = enterCommandMode;
            return true;
        } else {
            QLOG_ERROR() << "Radio3DRSettings Serial Port Configuration FAILURE! " << m_serialPort->errorString();
            emit updateLocalStatus(tr("FAILED to configure serial port"), red);
            emit serialPortOpenFailure(m_serialPort->error(), m_serialPort->errorString());
            closeSerialPort();
            return false;
        }
    } else {
        // Abort
        // 중단
        QLOG_DEBUG() << "Radio3DRSettings Serial Port Open FAILURE! " << m_serialPort->errorString();
        emit serialPortOpenFailure(m_serialPort->error(), m_serialPort->errorString());
        emit updateLocalStatus(tr("FAILED to open serial port"), red);
        closeSerialPort();
    }
    return false;
}

void Radio3DRSettings::closeSerialPort()
{
    if (m_serialPort && m_serialPort->isOpen()){
        QLOG_DEBUG() << "Close Serial Port:" << m_serialPort->portName() << m_serialPort.data();
        m_serialPort->write("ATO\r\n"); // leave command mode - just to be sure// 명령 모드를 종료하십시오.
        m_serialPort->flush();
        m_serialPort->close();
    }
    m_retryCount = 0;   // when we close the port the retry must be reset// 포트를 닫을 때 재시도를 재설정해야합니다.
}

void Radio3DRSettings::readData()
{
    // Sanity check
    // 온전한 검사
    if(!m_serialPort){
        return;
    }
    // read raw data
    // 원시 데이터를 읽습니다.
    QByteArray data;
    if(m_serialPort->canReadLine()){
        data = m_serialPort->readLine();  // normally we can wait for a \n// 일반적으로 우리는 \ n 기다릴 수 있습니다. \ n
    }
    else if((m_state == rebootLocal) && (m_serialPort->bytesAvailable() >= 3)){
        data = m_serialPort->readAll();     // in case of a reset ATZ has not always a \n// 재설정의 경우 ATZ가 항상 \ n이 아님
    }
    else {
        return; // no data
    }

    // filter all unwanted ascii characters
    // 원하지 않는 모든 ASCII 문자를 필터링합니다.
    QString currentLine;
    foreach(const char &character, data)
    {
        if((static_cast<quint8>(character) < 128) &&        // above 128 there are only graphics// 128 이상이면 그래픽 만 있습니다.
                ((static_cast<quint8>(character) > 31) ||   // below 31 only control chars// 31 이하의 문자 만 제어
                 (static_cast<quint8>(character) == 10) ||  // but we need linefeed// 하지만 줄 바꿈이 필요합니다.
                 (static_cast<quint8>(character) == 13)))   // and carriage return// 캐리지 리턴
        {
            currentLine.append(character);
        }
    }

    QLOG_DEBUG() << "Radio readData currentline:" << currentLine;

    if(currentLine.contains("+++")){
        // We are already in command mode and it just reflecrted the escape sequence
        // 이미 명령 모드에 있으며 이스케이프 시퀀스를 리플렉션했습니다.
        QLOG_WARN() << "3DR Radio already in command mode";
        // Reset Radios to known state and start again
        // 라디오를 알려진 상태로 재설정하고 다시 시작합니다.
        m_serialPort->flush();
//        m_serialPort->write("\r\n");
//        m_serialPort->flush();
        m_timer.stop();
        emit updateLocalStatus(tr("Already in Command Mode"), black);
        readLocalVersionString();
        return;
    }

    if(currentLine.contains("RTZ")){
        // Rebooted remote
        // 재부팅 된 원격
        QLOG_DEBUG() << "Resetted remote radio";
        return;
    }

    if(currentLine.contains("ATZ")){
        // Rebooted local -> read all data again
        // 재부팅 된 로컬 -> 모든 데이터를 다시 읽습니다.
        QLOG_DEBUG() << "Resetted local radio - Refresh all data.";
        m_state = enterCommandMode;
        m_retryCount = 0;
        writeEscapeSeqeunce();
        return;
    }

    if(currentLine.startsWith("AT")||currentLine.startsWith("RT")){
        //throw away the command echo
       // 명령을 버린다 echo
        if(m_serialPort->canReadLine()){
           currentLine = m_serialPort->readLine();
           QLOG_DEBUG() << "Radio readData nextline:" << currentLine;

        } else {
            // no data to read so wait for more
            // 읽을 데이터가 없으므로 더 기다려야합니다.
            currentLine = "";
            return;
        }
    }

    switch(m_state){
    case enterCommandMode: {
        if (currentLine.contains("OK")){
            m_timer.stop();
            QLOG_INFO() << "3DR Radio: Entered Command Mode";
            emit updateLocalStatus(tr("Entered Command mode"), black);
//            m_serialPort->write("AT&T\r\n");
            readLocalVersionString();
        }
    } break;

    case writeLocalParams: {
        if (currentLine.contains("OK")){
            emit updateLocalStatus(tr("param %1 written ok").arg(m_paramIndexSend), black);
            m_paramIndexSend++;

            if (m_paramIndexSend > m_newLocalRadio.numberOfParams()){
                emit updateLocalStatus(tr("param write complete"), green);
                m_state = writeLocalEepromValues;
                m_serialPort->write("AT&W\r\n");
                return;
            }

            QLOG_INFO() << "Writing Local Param:"
                        << m_newLocalRadio.formattedParameter(Radio3DREeprom::local, m_paramIndexSend);
            m_serialPort->write(m_newLocalRadio.formattedParameter(Radio3DREeprom::local, m_paramIndexSend).toLatin1());

        } else {
            emit updateLocalStatus(tr("param %1 failed write").arg(m_paramIndexSend), black);
            QLOG_ERROR() << "FAILED Writing Local Param:"
                         << m_newLocalRadio.formattedParameter(Radio3DREeprom::local, m_paramIndexSend);
            // [ToDo] Can retry at this point
            // [할 일]이 시점에서 재 시도 할 수 있습니다.
        }
    } break;

    case writeRemoteParams: {
        if (currentLine.contains("OK")){
            emit updateRemoteStatus(tr("param %1 written ok").arg(m_paramIndexSend), black);
            m_paramIndexSend++;

            if (m_paramIndexSend > m_newRemoteRadio.numberOfParams()){
                emit updateRemoteStatus(tr("param write complete"), green);
                // Now write to eeprom and reset
                // 이제 eeprom에 기록하고 재설정합니다.
                m_state = writeRemoteEepromValues;
                m_serialPort->write("RT&W\r\n");
                return;
            }

            QLOG_INFO() << "Writing Remote Param:"
                        << m_newRemoteRadio.formattedParameter(Radio3DREeprom::remote, m_paramIndexSend);
            m_serialPort->write(m_newRemoteRadio.formattedParameter(Radio3DREeprom::remote, m_paramIndexSend).toLatin1());

        } else {
            emit updateRemoteStatus(tr("param %1 failed write").arg(m_paramIndexSend), black);
            QLOG_ERROR() << "FAILED Writing Remote Param:"
                         << m_newRemoteRadio.formattedParameter(Radio3DREeprom::remote,m_paramIndexSend);
            // [ToDo] Can retry at this point
            // [할 일]이 시점에서 재 시도 할 수 있습니다.
        }
    } break;

    case writeRemoteFactorySettings: {
        if (currentLine.contains("OK")){
            emit updateRemoteStatus(tr("Reset to factory Settings"), black);
            m_serialPort->write("RT&F\r\n"); // Write eeprom settings// eeprom 설정을 씁니다.
            m_state = writeRemoteEepromValues;
        } else {
            emit updateRemoteStatus(tr("Failed to reset to factory settings"), red);
            m_state = error;
        }
    } break;

    case writeRemoteEepromValues: {
        if (currentLine.contains("OK")){
            emit updateRemoteStatus(tr("Saved to EEPROM"), black);
            emit updateRemoteComplete(0); // 0 == SUCCESS
        } else {
            emit updateRemoteStatus(tr("Failed to save settings to eeprom"), black);
            emit updateRemoteComplete(-1); // -1 == FAILED
            m_state = error;
        }
    } break;

    case writeLocalFactorySettings: {
        if (currentLine.contains("OK")){
            emit updateLocalStatus(tr("Reset to factory Settings"), black);
            m_serialPort->write("AT&F\r\n"); // Write eeprom settings// eeprom 설정을 씁니다.
            m_state = writeLocalEepromValues;
        } else {
            emit updateLocalStatus(tr("Failed to reset to factory settings"), red);
            m_state = error;
        }
    } break;

    case writeLocalEepromValues: {
        if (currentLine.contains("OK")){
            m_state = none;
            emit updateLocalStatus(tr("Saved to EEPROM"), black);
            emit updateLocalComplete(0); // 0 == SUCCESS
        } else {
            m_state = error;
            emit updateLocalStatus(tr("Failed to save settings to EEPROM"), black);
            emit updateLocalComplete(-1); // -1 == FAILED
        }
    } break;

    case readLocalVersion:{
        QRegExp rx("^SiK\\s+(.*)\\s+on\\s+(.*)");
        if(currentLine.contains(rx)) {
            QLOG_INFO() << "3DR Local Radio: Version" << currentLine;
            if (!m_localRadio.setVersion(currentLine)) {
                // Failed to read Version
                QLOG_DEBUG() << " Failed to Read Version";
                emit updateLocalStatus(tr("FAILED"), red);
                closeSerialPort();
                m_state = error;
            } else {
                emit updateLocalStatus(tr("Read local radio version"), black);
                readLocalRadioFrequency();
            }
        }
    } break;

    case readLocalFrequency:{
        if(currentLine.toInt() > 0){
            int freqCode = currentLine.toInt();
            QLOG_DEBUG() << "Read Local Freq:" << QString().sprintf("0x%x",freqCode);
            emit updateLocalStatus(tr("read local radio frequency"), black);
            m_localRadio.setRadioFreqCode(freqCode);
            readLocalSettingsStrings();
        } else {
            emit updateLocalStatus(tr("FAILED"), red);
            closeSerialPort();
            m_state = error;
        }
    } break;

    case readLocalParams:{
        //[TODO] add more error checking by checking return value of setParam
        // [TODO] setParam의 리턴 값을 검사하여 더 많은 에러 검사를 추가한다.
        m_localRadio.setParameter(currentLine);
        while(m_serialPort->canReadLine()){
            currentLine = m_serialPort->readLine();
            m_localRadio.setParameter(currentLine);
        };
        if (currentLine.contains(m_localRadio.endParam())) {
            // All data received
            // 받은 모든 데이터
            emit updateLocalStatus(tr("SUCCESS"), green);
            emit localReadComplete(m_localRadio, true);
            readLocalRssi();
        }; // else wait for more// 다른 경우는 더 기다린다.
    } break;

    case readRemoteVersion:{
        m_timerReadWrite.stop();
        disconnect(&m_timerReadWrite, SIGNAL(timeout()), this , SLOT(readRemoteTimeout()));
        QRegExp rx("^SiK\\s+(.*)\\s+on\\s+(.*)");
        if(currentLine.contains(rx)) {
            QLOG_INFO() << "3DR Remote Radio: Version" << currentLine;
            if (!m_remoteRadio.setVersion(currentLine)) {
                // Failed to read Version
                QLOG_DEBUG() << " Failed to Read Version";
                emit updateRemoteStatus(tr("FAILED"), red);
                closeSerialPort();
                m_state = error;
            } else {
                emit updateRemoteStatus(tr("Remote Version read"), black);
                readRemoteRadioFrequency();
            }
        }
    } break;

    case readRemoteFrequency:{
        if(currentLine.toInt() > 0){
            int freqCode = currentLine.toInt();
            QLOG_DEBUG() << "Read Remote Freq:" << QString().sprintf("0x%x",freqCode);
            emit updateRemoteStatus(tr("Read remote radio frequency"), black);
            m_remoteRadio.setRadioFreqCode(freqCode);
            readRemoteSettingsStrings();
        } else {
            emit updateRemoteStatus(tr("FAILED"), red);
            closeSerialPort();
            m_state = error;
        }


    } break;

    case readRemoteParams:{
        //[TODO] add more error checking by checking return value of setParam
        // [TODO] setParam의 리턴 값을 검사하여 더 많은 에러 검사를 추가한다.
        m_remoteRadio.setParameter(currentLine);
        while(m_serialPort->canReadLine()){
            currentLine = m_serialPort->readLine();
            m_remoteRadio.setParameter(currentLine);
        };
        if (currentLine.contains(m_remoteRadio.endParam())) {
            // All data received
            emit updateRemoteStatus(tr("SUCCESS"), green);
            emit remoteReadComplete(m_remoteRadio, true);
            // Start the RSSI reading
            readRemoteRssi();
        };
    } break;

    case readRssiLocal:{
        if (currentLine.startsWith("L/R RSSI:")){
            emit updateLocalRssi(currentLine);
        }
        readRemoteVersionString();
    }break;

    case readRssiRemote:{
        if (currentLine.startsWith("L/R RSSI:")){
            emit updateRemoteRssi(currentLine);
        }
        m_state = portOpen; // finshed
    }break;

    case rebootLocal:
    case rebootRemote:
        // May need to consume echo'd bytes here[?]
        // 여기 에코 바이트를 소비해야 할 수도 있습니다 [?]
        break;
    case error:
        QLOG_DEBUG() << "Error: " << m_serialPort->errorString();
        m_state = complete;
        break;
    case none:
    case complete:
    default:
//        closeSerialPort();
        m_state = complete;
    }
}

void Radio3DRSettings::writeEscapeSeqeunce()
{
    // sanity check
    if(!m_serialPort){
        return;
    }
    QLOG_DEBUG() << "Radio3DRSettings::writeEscapeSequence()";
    disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(writeEscapeSeqeunce()));
    emit updateLocalStatus(tr("entering command mode"), black);
    if (m_state == enterCommandMode){
        if (m_retryCount++ < 3) {
            QLOG_INFO() << "Try " << m_retryCount;
            m_serialPort->write("\r\n");
            m_serialPort->flush();
            connect(&m_timer, SIGNAL(timeout()), this, SLOT(writeEscapeSeqeunceNow()), Qt::UniqueConnection);
            m_timer.start(1100);
        } else {
            closeSerialPort();
            m_state = error; // Quit any more retries// 더 이상 다시 시도하지 않습니다.
            emit updateLocalStatus(tr("FAILED"), red);
            emit updateRemoteStatus(tr("FAILED"), red);
        }
    }
}

void Radio3DRSettings::writeEscapeSeqeunceNow()
{
    disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(writeEscapeSeqeunceNow()));
    if (!m_serialPort){
        return;
    }

    QLOG_DEBUG() << "Radio3DRSettings::writeEscapeSequenceNow()";
    m_serialPort->write("\x2B\x2B\x2B"); // +++
    m_serialPort->flush();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(writeEscapeSeqeunce()), Qt::UniqueConnection);
    m_timer.start(1100);
}


void Radio3DRSettings::readLocalVersionString()
{
    QLOG_DEBUG() << "Radio3DRSettings::readLocalVersionString()";
    emit updateLocalStatus(tr("Read local radio version"), black);
    if (m_serialPort && m_serialPort->isOpen()){
        // start state machine// 상태 시스템을 시작합니다.
        m_serialPort->write("ATI0\r\n");
        m_serialPort->flush();
        m_state = readLocalVersion;
    } else {
        m_state = error;
        emit updateRemoteStatus(tr("FAILED"), red);
    }
}

void Radio3DRSettings::readRemoteVersionString()
{
    QLOG_DEBUG() << "Radio3DRSettings::readRemoteVersionString()";
    emit updateRemoteStatus(tr("Reading remote version"), black);
    if (m_serialPort && m_serialPort->isOpen()){
        // start state machine// 상태 시스템을 시작합니다.
        m_serialPort->write("RTI0\r\n");
        m_serialPort->flush();
        m_state = readRemoteVersion;
        connect(&m_timerReadWrite, SIGNAL(timeout()), this , SLOT(readRemoteTimeout()));
        m_timerReadWrite.start(500);
    } else {
        m_state = error;
        emit updateRemoteStatus(tr("FAILED"), red);
    }
}

void Radio3DRSettings::readRemoteTimeout()
{
    // No remote so read local radio.
    // 리모컨이 없으므로 로컬 라디오를 읽지 않습니다.
    QLOG_DEBUG() << " Failed to Read Remote Version";
    disconnect(&m_timerReadWrite, SIGNAL(timeout()), this , SLOT(readRemoteTimeout()));
    emit updateRemoteStatus(tr("FAILED"), red);
}

void Radio3DRSettings::readLocalRadioFrequency()
{
    QLOG_DEBUG() << "Radio3DRSettings::readLocalRadioFrequency()";
    emit updateLocalStatus(tr("Read local radio frequency"), black);
    if (m_serialPort && m_serialPort->isOpen()){
        // start state machine
        // 상태 시스템을 시작합니다.
        m_serialPort->write("ATI3\r\n");
        m_serialPort->flush();
        m_state = readLocalFrequency;
    } else {
        m_state = error;
        emit updateLocalStatus(tr("FAILED"), red);
    }
}

void Radio3DRSettings::readRemoteRadioFrequency()
{
    QLOG_DEBUG() << "Radio3DRSettings::readRemoteRadioFrequency()";
    emit updateRemoteStatus(tr("Read remote radio frequency"), black);
    if (m_serialPort && m_serialPort->isOpen()){
        // start state machine
        // 상태 시스템을 시작합니다.
        m_serialPort->write("RTI3\r\n");
        m_serialPort->flush();
        m_state = readRemoteFrequency;
    } else {
        m_state = error;
        emit updateRemoteStatus(tr("FAILED"), red);
    }
}

void Radio3DRSettings::readLocalSettingsStrings()
{
    QLOG_DEBUG() << "Radio3DRSettings::readLocalSettingsStrings()";
    emit updateLocalStatus(tr("Read local radio eeprom values"), black);
    if (m_serialPort && m_serialPort->isOpen()){
        m_serialPort->write("ATI5\r\n"); // Request all EEPROM params// 모든 EEPROM 매개 변수 요청
        m_serialPort->flush();
        m_state = readLocalParams;
    } else {
        m_state = error;
        emit updateLocalStatus(tr("FAILED"), red);
    }
}

void Radio3DRSettings::readRemoteSettingsStrings()
{
    QLOG_DEBUG() << "Radio3DRSettings::readRemoteSettingsStrings()";
    emit updateRemoteStatus(tr("Read remote radio eeprom values"), black);
    if (m_serialPort && m_serialPort->isOpen()){
        m_serialPort->write("RTI5\r\n"); // Request all EEPROM params// 모든 EEPROM 매개 변수 요청
        m_serialPort->flush();
        m_state = readRemoteParams;
    } else {
        m_state = error;
        emit updateRemoteStatus(tr("FAILED"), red);
    }
}


void Radio3DRSettings::writeLocalSettings(Radio3DREeprom eepromSettings)
{
    QLOG_DEBUG() << "Radio3DRSettings::writeLocalSettings()";
    if (!m_serialPort || !m_serialPort->isOpen()) {
        QLOG_DEBUG() << "Serial Port not Open";
        return;
    }
    m_newLocalRadio = eepromSettings;
    m_paramIndexSend = 1; // start of the first parameter// 첫 번째 매개 변수의 시작
    QLOG_DEBUG() << " Sending" << m_newLocalRadio.formattedParameter(Radio3DREeprom::local, m_paramIndexSend).toLatin1();
    m_serialPort->write(m_newLocalRadio.formattedParameter(Radio3DREeprom::local, m_paramIndexSend).toLatin1());
    m_state = writeLocalParams;
}

void Radio3DRSettings::writeRemoteSettings(Radio3DREeprom eepromSettings)
{
    QLOG_DEBUG() << "Radio3DRSettings::writeRemoteSettings()";

    if (!m_serialPort || !m_serialPort->isOpen()) {
        QLOG_DEBUG() << "Serial Port not Open";
        return;
    }
    m_newRemoteRadio = eepromSettings;
    m_paramIndexSend = 1; // start of the first parameter// 첫 번째 매개 변수의 시작
    QLOG_DEBUG() << " Sending" << m_newRemoteRadio.formattedParameter(Radio3DREeprom::remote, m_paramIndexSend).toLatin1();
    m_serialPort->write(m_newRemoteRadio.formattedParameter(Radio3DREeprom::remote, m_paramIndexSend).toLatin1());
    m_state = writeRemoteParams;
}

void Radio3DRSettings::readLocalRssi()
{
    if(m_serialPort && m_serialPort->isOpen()){
        QLOG_DEBUG() << "readLocalRssi";
        m_serialPort->write("ATI7\r\n");
        m_state = readRssiLocal;
    }
}

void Radio3DRSettings::readRemoteRssi()
{
    if(m_serialPort && m_serialPort->isOpen()){
        QLOG_DEBUG() << "readRemoteRssi";
        m_serialPort->write("RTI7\r\n");
        m_state = readRssiRemote;
    }
}

void Radio3DRSettings::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        // disconnect signals immediately to avoid that accidentally sent data triggers call of this method again
        // 실수로 보낸 데이터가이 메서드를 다시 호출하는 것을 방지하기 위해 즉시 신호 연결을 끊습니다.
        disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(writeEscapeSeqeunceNow()));
        disconnect(m_serialPort.data(), SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        disconnect(m_serialPort.data(), SIGNAL(readyRead()), this, SLOT(readData()));

        if(m_serialPort){
            emit serialConnectionFailure(m_serialPort->errorString());
            emit updateLocalStatus(tr("Serial connection lost"), red);
            m_retryCount = 0;
            m_serialPort.reset();
        } else {
            QLOG_ERROR() << "Crtical Error - Received error without opened serial port!?" ;
        }
    }
    else if(error != QSerialPort::NoError)
    {
       QLOG_WARN() << "Serial Port Error " << m_serialPort->errorString();
    }
}

void Radio3DRSettings::resetLocalRadioToDefaults()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        QLOG_DEBUG() << "Serial Port not Open";
        return;
    }
    QLOG_INFO() <<  "Reseting local radio back to factory settings";;

    m_serialPort->write("AT&F\r\n");
    m_state = writeLocalFactorySettings;

}

void Radio3DRSettings::resetRemoteRadioToDefaults()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        QLOG_DEBUG() << "Serial Port not Open";
        return;
    }
    QLOG_INFO() << "Reseting remote radio back to factory settings";

    m_serialPort->write("RT&F\r\n");
    m_state = writeRemoteFactorySettings;

}

void Radio3DRSettings::rebootLocalRadio()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        QLOG_DEBUG() << "Serial Port not Open";
        return;
    }
    QLOG_INFO() << "Reboot local radio";
    emit updateLocalStatus(tr("Send reset - waiting for reconnect"), black);
    m_serialPort->flush();
    m_serialPort->write("ATZ\r\n");
    m_serialPort->flush();
    m_state = rebootLocal;

}

void Radio3DRSettings::rebootRemoteRadio()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        QLOG_DEBUG() << "Serial Port not Open";
        return;
    }
    QLOG_INFO() << "Reboot remote radio";
    emit updateRemoteStatus(tr("Send reset - waiting for reconnect"), black);
    m_serialPort->flush();
    m_serialPort->write("RTZ\r\n");
    m_serialPort->flush();
    m_state = rebootRemote;

}

QString Radio3DRSettings::stateColorToString(stateColor color)
{
    QString colorString("black");
    switch (color)
    {
        case black:
            colorString = "black";
            break;

        case green:
            colorString = "green";
            break;

        case red:
            colorString = "red";
            break;
    }
    return colorString;
}
