#ifndef MAVLINKSIMULATIONWAYPOINTPLANNER_H
#define MAVLINKSIMULATIONWAYPOINTPLANNER_H

#include <QObject>
#include <vector>

#include "MAVLinkSimulationLink.h"
#include "QGCMAVLink.h"

enum PX_WAYPOINTPLANNER_STATES {
    PX_WPP_IDLE = 0,
    PX_WPP_SENDLIST,
    PX_WPP_SENDLIST_SENDWPS,
    PX_WPP_GETLIST,
    PX_WPP_GETLIST_GETWPS,
    PX_WPP_GETLIST_GOTALL
};

class MAVLinkSimulationWaypointPlanner : public QObject
{
    Q_OBJECT
public:
    explicit MAVLinkSimulationWaypointPlanner(MAVLinkSimulationLink *parent, int systemid);

signals:
    void messageSent(const mavlink_message_t& msg);

public slots:
    void handleMessage(const mavlink_message_t& msg);

protected:
    MAVLinkSimulationLink* link;
    bool idle;      				///< indicates if the system is following the waypoints or is waiting	 <시스템이 웨이 포인트를 따르고 있거나 기다리고 있는지 나타냅니다.
    uint16_t current_active_wp_id;		///< id of current waypoint	 <현재 웨이 포인트의 id
    bool yawReached;						///< boolean for yaw attitude reached	 yaw 태도에 도달 한 부울 값
    bool posReached;						///< boolean for position reached	 도달 한 위치에 대한 부울 값
    uint64_t timestamp_lastoutside_orbit;///< timestamp when the MAV was last outside the orbit or had the wrong yaw value	  <MAV가 마지막으로 궤도를 벗어 났거나 잘못된 yaw 값을 가졌을 때의 타임 스탬프
    uint64_t timestamp_firstinside_orbit;///< timestamp when the MAV was the first time after a waypoint change inside the orbit and had the correct yaw value	 <MAV가 궤도 안의 웨이 포인트 변경 후 처음으로 yaw 값이 올바른 타임 스탬프

    std::vector<mavlink_mission_item_t*> waypoints1;	///< vector1 that holds the waypoints	 <웨이 포인트가있는 vector1
    std::vector<mavlink_mission_item_t*> waypoints2;	///< vector2 that holds the waypoints	 <웨이브 포인트를 저장하는 vector2

    std::vector<mavlink_mission_item_t*>* waypoints;		///< pointer to the currently active waypoint vector	 <현재 활성 웨이 포인트 벡터에 대한 포인터
    std::vector<mavlink_mission_item_t*>* waypoints_receive_buffer;	///< pointer to the receive buffer waypoint vector	 <수신 버퍼 웨이 포인트 벡터에 대한 포인터
    PX_WAYPOINTPLANNER_STATES current_state;
    uint16_t protocol_current_wp_id;
    uint16_t protocol_current_count;
    uint8_t protocol_current_partner_systemid;
    uint8_t protocol_current_partner_compid;
    uint64_t protocol_timestamp_lastaction;
    unsigned int protocol_timeout;
    uint64_t timestamp_last_send_setpoint;
    uint8_t systemid;
    uint8_t compid;
    unsigned int setpointDelay;
    float yawTolerance;
    bool silent;

    void send_waypoint_ack(uint8_t target_systemid, uint8_t target_compid, uint8_t type);
    void send_waypoint_current(uint16_t seq);
    void send_setpoint(uint16_t seq);
    void send_waypoint_count(uint8_t target_systemid, uint8_t target_compid, uint16_t count);
    void send_waypoint(uint8_t target_systemid, uint8_t target_compid, uint16_t seq);
    void send_waypoint_request(uint8_t target_systemid, uint8_t target_compid, uint16_t seq);
    void send_waypoint_reached(uint16_t seq);
    float distanceToSegment(uint16_t seq, float x, float y, float z);
    float distanceToPoint(uint16_t seq, float x, float y, float z);
    float distanceToPoint(uint16_t seq, float x, float y);
    void mavlink_handler(const mavlink_message_t* msg);

};

#endif // MAVLINKSIMULATIONWAYPOINTPLANNER_H
