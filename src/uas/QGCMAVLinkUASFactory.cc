#include "QGCMAVLinkUASFactory.h"
#include "UASManager.h"

QGCMAVLinkUASFactory::QGCMAVLinkUASFactory(QObject *parent) :
    QObject(parent)
{
}

UASInterface* QGCMAVLinkUASFactory::createUAS(MAVLinkProtocol* mavlink, LinkInterface* link, int sysid, mavlink_heartbeat_t* heartbeat, QObject* parent)
{
    QPointer<QObject> p;

    if (parent != NULL)
    {
        p = parent;
    }
    else
    {
        p = mavlink;
    }

    UASInterface* uas;

    switch (heartbeat->autopilot)
    {
    case MAV_AUTOPILOT_GENERIC:
    {
        UAS* mav = new UAS(0, sysid);
        // Set the system type	 시스템 유형 설정  
        mav->setSystemType((int)heartbeat->type);
        // Connect this robot to the UAS object	 이 로봇을 UAS 객체에 연결합니다.  
        connect(mavlink, SIGNAL(messageReceived(LinkInterface*, mavlink_message_t)), mav, SLOT(receiveMessage(LinkInterface*, mavlink_message_t)));
#ifdef QGC_PROTOBUF_ENABLED
        connect(mavlink, SIGNAL(extendedMessageReceived(LinkInterface*, std::tr1::shared_ptr<google::protobuf::Message>)), mav, SLOT(receiveExtendedMessage(LinkInterface*, std::tr1::shared_ptr<google::protobuf::Message>)));
#endif
        uas = mav;
    }
    break;
//    case MAV_AUTOPILOT_PX4:
//    {
//        PxQuadMAV* mav = new PxQuadMAV(0, sysid);
//        // Set the system type	 시스템 타입을 설정한다.

//        mav->setSystemType((int)heartbeat->type);
//        // Connect this robot to the UAS object
//        // it is IMPORTANT here to use the right object type,
//        // else the slot of the parent object is called (and thus the special
//        // packets never reach their goal)

/*
//         //이 로봇을 UAS 객체에 연결합니다.
//         여기서 올바른 객체 유형을 사용하는 것이 중요합니다.
//         // else 부모 객체의 슬롯이 호출됩니다 (따라서 특수
//         목표에 도달하지 못하는 패킷)
*/

//        connect(mavlink, SIGNAL(messageReceived(LinkInterface*, mavlink_message_t)), mav, SLOT(receiveMessage(LinkInterface*, mavlink_message_t)));
//#ifdef QGC_PROTOBUF_ENABLED
//        connect(mavlink, SIGNAL(extendedMessageReceived(LinkInterface*, std::tr1::shared_ptr<google::protobuf::Message>)), mav, SLOT(receiveExtendedMessage(LinkInterface*, std::tr1::shared_ptr<google::protobuf::Message>)));
//#endif
//        uas = mav;
//    }
    break;
    case MAV_AUTOPILOT_SLUGS:
    {
        SlugsMAV* mav = new SlugsMAV(0, sysid);
        // Set the system type	 시스템 유형 설정  
        mav->setSystemType((int)heartbeat->type);
        // Connect this robot to the UAS object
        // it is IMPORTANT here to use the right object type,
        // else the slot of the parent object is called (and thus the special
        // packets never reach their goal)

/*
        // 이 로봇을 UAS 객체에 연결합니다.
        // 여기서 올바른 객체 유형을 사용하는 것이 중요합니다.
        // else 부모 객체의 슬롯이 호출됩니다 (따라서 특수
        // 패킷이 목표에 도달하지 못함)
*/
	 
        connect(mavlink, SIGNAL(messageReceived(LinkInterface*, mavlink_message_t)), mav, SLOT(receiveMessage(LinkInterface*, mavlink_message_t)));
        uas = mav;
    }
    break;
    case MAV_AUTOPILOT_ARDUPILOTMEGA:
    {
        ArduPilotMegaMAV* mav = new ArduPilotMegaMAV(0, sysid);
        // Set the system type	 시스템 유형 설정  
        mav->setSystemType((int)heartbeat->type);
        // Connect this robot to the UAS object
        // it is IMPORTANT here to use the right object type,
        // else the slot of the parent object is called (and thus the special
        // packets never reach their goal)

/*
        // 이 로봇을 UAS 객체에 연결합니다.
        // 여기서 올바른 객체 유형을 사용하는 것이 중요합니다.
        // else 부모 객체의 슬롯이 호출됩니다 (따라서 특수
        // 패킷이 목표에 도달하지 못함)
*/

        connect(mavlink, SIGNAL(messageReceived(LinkInterface*, mavlink_message_t)), mav, SLOT(receiveMessage(LinkInterface*, mavlink_message_t)));
        uas = mav;
    }
    break;
#ifdef QGC_USE_SENSESOAR_MESSAGES
	case MAV_AUTOPILOT_SENSESOAR:
		{
			senseSoarMAV* mav = new senseSoarMAV(mavlink,sysid);
			mav->setSystemType((int)heartbeat->type);
			connect(mavlink, SIGNAL(messageReceived(LinkInterface*, mavlink_message_t)), mav, SLOT(receiveMessage(LinkInterface*, mavlink_message_t)));
			uas = mav;
			break;
		}
#endif
    default:
    {
        UAS* mav = new UAS(0, sysid);
        mav->setSystemType((int)heartbeat->type);
        // Connect this robot to the UAS object
        // it is IMPORTANT here to use the right object type,
        // else the slot of the parent object is called (and thus the special
        // packets never reach their goal)

/*
        // 이 로봇을 UAS 객체에 연결합니다.
        // 여기서 올바른 객체 유형을 사용하는 것이 중요합니다.
        // else 부모 객체의 슬롯이 호출됩니다 (따라서 특수
        // 패킷이 목표에 도달하지 못함)
*/

        connect(mavlink, SIGNAL(messageReceived(LinkInterface*, mavlink_message_t)), mav, SLOT(receiveMessage(LinkInterface*, mavlink_message_t)));
        uas = mav;
    }
    break;
    }

    // Set the autopilot type	 자동 조종 장치 유형 설정  
    uas->setAutopilotType((int)heartbeat->autopilot);

    // Make UAS aware that this link can be used to communicate with the actual robot	  UAS가이 링크를 사용하여 실제 로봇과 통신 할 수 있음을 알린다.  
    uas->addLink(link);

    // Now add UAS to "official" list, which makes the whole application aware of it	 이제 UAS를 "공식"목록에 추가하면 전체 응용 프로그램이이를 인식합니다  
    UASManager::instance()->addUAS(uas);

    return uas;
}
