#ifndef QGCMAVLINKUASFACTORY_H
#define QGCMAVLINKUASFACTORY_H

#include <QObject>

#include "QGCMAVLink.h"
#include "MAVLinkProtocol.h"
#include "UASInterface.h"
#include "LinkInterface.h"

// INCLUDE ALL MAV/UAS CLASSES USING MAVLINK	 MAVLINK를 사용하여 모든 MAV / UAS 클래스 포함
#include "UAS.h"
#include "SlugsMAV.h"
#include "PxQuadMAV.h"
#include "senseSoarMAV.h"
#include "ArduPilotMegaMAV.h"

class QGCMAVLinkUASFactory : public QObject
{
    Q_OBJECT
public:
    explicit QGCMAVLinkUASFactory(QObject *parent = 0);

    /** @brief Create a new UAS object using MAVLink as protocol 	 MAVLink를 프로토콜로 사용하여 새 UAS 객체 만들기 */
    static UASInterface* createUAS(MAVLinkProtocol* mavlink, LinkInterface* link, int sysid, mavlink_heartbeat_t* heartbeat, QObject* parent=NULL);

signals:

public slots:

};

#endif // QGCMAVLINKUASFACTORY_H
