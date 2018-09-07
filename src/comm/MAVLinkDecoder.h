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
 *   @brief MAVLinkDecoder
 *          This class decodes value fields from incoming mavlink_message_t packets
 *          It emits valueChanged, which is passed up to the UAS class to emit to the UI
 *
 *   @author Michael Carpenter <malcom2073@gmail.com>
 *   @author QGROUNDCONTROL PROJECT - This code has GPLv3+ snippets from QGROUNDCONTROL, (c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 */
/**
 * @file
 * @ 간단한 MAVLinkDecoder
 *이 클래스는 수신 mavlink_message_t 패킷의 값 필드를 디코딩합니다.
 * valueChanged를 내보내 UAS 클래스에 전달되어 UI로 전달됩니다.
 *
 * @author Michael Carpenter <malcom2073@gmail.com>
 * @author QGROUNDCONTROL PROJECT -이 코드에는 QGROUNDCONTROL의 GPLv3 + 스 니펫이 있습니다. (c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 */


#ifndef NEW_MAVLINKDECODER_H
#define NEW_MAVLINKDECODER_H

#include "logging.h"
#include <mavlink_types.h>
extern mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS]; // defined in src/main.cc // src / main.cc에 정의 됨
#include "mavlink.h"
#include "LinkInterface.h"

#include <QObject>
#include <QThread>
#include <QFile>
#include <QMap>
#include <QVector>

class ConnectionManager;
class UASInterface;

class MAVLinkDecoder : public QObject
{
    Q_OBJECT
public:
    MAVLinkDecoder(QObject *parent=0);
    ~MAVLinkDecoder();

    mavlink_field_info_t getFieldInfo(const QString &msgname, const QString &fieldname) const;
    QList<QString> getFieldList(const QString &msgname) const;
    QString getMessageName(quint32 msgid) const;
    quint64 getUnixTimeFromMs(int systemID, quint64 time);
    void decodeMessage(const mavlink_message_t &message);

signals:
    void protocolStatusMessage(const QString& title, const QString& message);
    void valueChanged(const int uasId, const QString& name, const QString& unit, const QVariant& value, const quint64 msec);
    void textMessageReceived(int uasid, int componentid, int severity, const QString& text);
    void receiveLossChanged(int id,float value);

public slots:
    void receiveMessage(LinkInterface* link, mavlink_message_t message);
    void sendMessage(mavlink_message_t msg);
    void emitFieldValue(mavlink_message_t* msg, int fieldid, quint64 time);

private:

    QHash<int,int> m_componentID;
    QHash<int,bool> m_componentMulti;
    QMap<quint32, bool> messageFilter;               ///< Message/field names not to emit
    QMap<quint32, bool> textMessageFilter;           ///< Message/field names not to emit in text mode
                                                     /// <출력 할 메시지 / 필드 이름
                                                     /// <텍스트 / 필드 모드에서 텍스트 모드로 나오지 않는 이름
    QHash<quint32, mavlink_message_info_t> messageInfo;
    QHash<QString, quint32> m_messageNameToID;

    QMap<int,quint64> onboardTimeOffset;
    QMap<int,quint64> firstOnboardTime;
    QMap<int,quint64> onboardToGCSUnixTimeOffsetAndDelay;

    bool m_localDecode;   /// true if decoding logfiles.
    UASInterface *mp_uas; /// pointer to active UAS. Can be null.
                          /// 로그 파일을 디코딩하는 경우에는 true입니다.
                          /// 활성 UAS를 가리키는 포인터. null도 가능
};

#endif // NEW_MAVLINKDECODER_H
