/*======================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009-2011 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

========================================================================*/

/**
*   @file
*   @brief a program to manage waypoints and exchange them with the ground station
*
*   @author Petri Tanskanen <petri.tanskanen@inf.ethz.ch>
*   @author Benjamin Knecht <bknecht@student.ethz.ch>
*   @author Christian Schluchter <schluchc@ee.ethz.ch>
*/

#include "logging.h"
#include <cmath>

#include "MAVLinkSimulationWaypointPlanner.h"
#include "QGC.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class PxMatrix3x3;


/**
 * @brief Pixhawk 3D vector class, can be cast to a local OpenCV CvMat.	  Pixhawk 3D 벡터 클래스는 로컬 OpenCV CvMat에 캐스트 될 수 있습니다.  
 *
 */
class PxVector3
{
public:
    /** @brief standard constructor 	 표준 생성자  */
    PxVector3(void) {}
    /** @brief copy constructor 	 복사 생성자   */
    PxVector3(const PxVector3 &v) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = v.m_vec[i];
        }
    }
    /** @brief x,y,z constructor 	  x, y, z 생성자  */
    PxVector3(const float _x, const float _y, const float _z) {
        m_vec[0] = _x;
        m_vec[1] = _y;
        m_vec[2] = _z;
    }
    /** @brief broadcast constructor 	 브로드 캐스트 생성자  */
    PxVector3(const float _f) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = _f;
        }
    }

private:
    /** @brief private constructor (not used here, for SSE compatibility) 	 개인 생성자 (SSE 호환성을 위해 여기에 사용되지 않음)  */
    PxVector3(const float (&_vec)[3]) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = _vec[i];
        }
    }

public:
    /** @brief assignment operator 	 대입 연산자  */
    void operator= (const PxVector3 &r) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = r.m_vec[i];
        }
    }
    /** @brief const element access	 const 요소 접근   */
    float operator[] (const int i) const {
        return m_vec[i];
    }
    /** @brief element access 	 간단한 요소 접근  */
    float &operator[] (const int i) {
        return m_vec[i];
    }
	 
    // === arithmetic operators ===	 === 산술 연산자 ===  
    /** @brief element-wise negation	 요소 별 부정    */
    friend PxVector3 operator- (const PxVector3 &v) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = -v.m_vec[i];
        }
        return ret;
    }
    friend PxVector3 operator+ (const PxVector3 &l, const PxVector3 &r) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] + r.m_vec[i];
        }
        return ret;
    }
    friend PxVector3 operator- (const PxVector3 &l, const PxVector3 &r) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] - r.m_vec[i];
        }
        return ret;
    }
    friend PxVector3 operator* (const PxVector3 &l, const PxVector3 &r) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] * r.m_vec[i];
        }
        return ret;
    }
    friend PxVector3 operator/ (const PxVector3 &l, const PxVector3 &r) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] / r.m_vec[i];
        }
        return ret;
    }

    friend void operator+= (PxVector3 &l, const PxVector3 &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] + r.m_vec[i];
        }
    }
    friend void operator-= (PxVector3 &l, const PxVector3 &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] - r.m_vec[i];
        }
    }
    friend void operator*= (PxVector3 &l, const PxVector3 &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] * r.m_vec[i];
        }
    }
    friend void operator/= (PxVector3 &l, const PxVector3 &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] / r.m_vec[i];
        }
    }

    friend PxVector3 operator+ (const PxVector3 &l, float f) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] + f;
        }
        return ret;
    }
    friend PxVector3 operator- (const PxVector3 &l, float f) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] - f;
        }
        return ret;
    }
    friend PxVector3 operator* (const PxVector3 &l, float f) {
        PxVector3 ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] * f;
        }
        return ret;
    }
    friend PxVector3 operator/ (const PxVector3 &l, float f) {
        PxVector3 ret;
        float inv = 1.f/f;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] * inv;
        }
        return ret;
    }

    friend void operator+= (PxVector3 &l, float f) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] + f;
        }
    }
    friend void operator-= (PxVector3 &l, float f) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] - f;
        }
    }
    friend void operator*= (PxVector3 &l, float f) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] * f;
        }
    }
    friend void operator/= (PxVector3 &l, float f) {
        float inv = 1.f/f;
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] * inv;
        }
    }

    // === vector operators ===	 === 벡터 연산자 ===  
    /** @brief dot product 	 간단한 내 용품  */
    float	dot(const PxVector3 &v) const {
        return m_vec[0]*v.m_vec[0] + m_vec[1]*v.m_vec[1] + m_vec[2]*v.m_vec[2];
    }
    /** @brief length squared of the vector	 벡터의 제곱 길이    */
    float	lengthSquared(void) const {
        return m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2];
    }
    /** @brief length of the vector	 벡터의 짧은 길이   */
    float	length(void) const {
        return sqrt(lengthSquared());
    }
    /** @brief cross product 		 십자가 제품   	 */
    PxVector3 cross(const PxVector3 &v) const {
        return PxVector3(m_vec[1]*v.m_vec[2] - m_vec[2]*v.m_vec[1], m_vec[2]*v.m_vec[0] - m_vec[0]*v.m_vec[2], m_vec[0]*v.m_vec[1] - m_vec[1]*v.m_vec[0]);
    }
    /** @brief normalizes the vector 	 벡터를 정규화합니다  */
    PxVector3 &normalize(void) {
        const float l = 1.f / length();
        for (int i=0; i < 3; i++) {
            m_vec[i] *= l;
        }
        return *this;
    }

    friend class PxMatrix3x3;
protected:
    float m_vec[3];
};

/**
 * @brief Pixhawk 3D vector class in double precision, can be cast to a local OpenCV CvMat.	  Pixhawk 3D 벡터 클래스는 이중 정밀도로 로컬 OpenCV CvMat에 캐스트 할 수 있습니다.  
 *
 */
class PxVector3Double
{
public:
    /** @brief standard constructor	 표준 생성자   */
    PxVector3Double(void) {}
    /** @brief copy constructor 	 복사 생성자  */
    PxVector3Double(const PxVector3Double &v) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = v.m_vec[i];
        }
    }
    /** @brief x,y,z constructor 	  간단한 x, y, z 생성자  */
    PxVector3Double(const double _x, const double _y, const double _z) {
        m_vec[0] = _x;
        m_vec[1] = _y;
        m_vec[2] = _z;
    }
    /** @brief broadcast constructor	  간단한 브로드 캐스트 생성자   */
    PxVector3Double(const double _f) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = _f;
        }
    }

private:
    /** @brief private constructor (not used here, for SSE compatibility)	 개인 생성자 (SSE 호환성을 위해 여기에 사용되지 않음)   */
    PxVector3Double(const double (&_vec)[3]) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = _vec[i];
        }
    }

public:
    /** @brief assignment operator 	 대입 연산자  */
    void operator= (const PxVector3Double &r) {
        for (int i=0; i < 3; i++) {
            m_vec[i] = r.m_vec[i];
        }
    }
    /** @brief const element access 	 const 요소 접근  */
    double operator[] (const int i) const {
        return m_vec[i];
    }
    /** @brief element access	  간단한 요소 접근   */
    double &operator[] (const int i) {
        return m_vec[i];
    }

    // === arithmetic operators ===	  === 산술 연산자 ===  
    /** @brief element-wise negation 	 요소 별 부정  */
    friend PxVector3Double operator- (const PxVector3Double &v) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = -v.m_vec[i];
        }
        return ret;
    }
    friend PxVector3Double operator+ (const PxVector3Double &l, const PxVector3Double &r) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] + r.m_vec[i];
        }
        return ret;
    }
    friend PxVector3Double operator- (const PxVector3Double &l, const PxVector3Double &r) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] - r.m_vec[i];
        }
        return ret;
    }
    friend PxVector3Double operator* (const PxVector3Double &l, const PxVector3Double &r) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] * r.m_vec[i];
        }
        return ret;
    }
    friend PxVector3Double operator/ (const PxVector3Double &l, const PxVector3Double &r) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] / r.m_vec[i];
        }
        return ret;
    }

    friend void operator+= (PxVector3Double &l, const PxVector3Double &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] + r.m_vec[i];
        }
    }
    friend void operator-= (PxVector3Double &l, const PxVector3Double &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] - r.m_vec[i];
        }
    }
    friend void operator*= (PxVector3Double &l, const PxVector3Double &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] * r.m_vec[i];
        }
    }
    friend void operator/= (PxVector3Double &l, const PxVector3Double &r) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] / r.m_vec[i];
        }
    }

    friend PxVector3Double operator+ (const PxVector3Double &l, double f) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] + f;
        }
        return ret;
    }
    friend PxVector3Double operator- (const PxVector3Double &l, double f) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] - f;
        }
        return ret;
    }
    friend PxVector3Double operator* (const PxVector3Double &l, double f) {
        PxVector3Double ret;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] * f;
        }
        return ret;
    }
    friend PxVector3Double operator/ (const PxVector3Double &l, double f) {
        PxVector3Double ret;
        double inv = 1.f/f;
        for (int i=0; i < 3; i++) {
            ret.m_vec[i] = l.m_vec[i] * inv;
        }
        return ret;
    }

    friend void operator+= (PxVector3Double &l, double f) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] + f;
        }
    }
    friend void operator-= (PxVector3Double &l, double f) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] - f;
        }
    }
    friend void operator*= (PxVector3Double &l, double f) {
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] * f;
        }
    }
    friend void operator/= (PxVector3Double &l, double f) {
        double inv = 1.f/f;
        for (int i=0; i < 3; i++) {
            l.m_vec[i] = l.m_vec[i] * inv;
        }
    }

    // === vector operators ===	 === 벡터 연산자 ===  
    /** @brief dot product 	  내 용품  */
    double	dot(const PxVector3Double &v) const {
        return m_vec[0]*v.m_vec[0] + m_vec[1]*v.m_vec[1] + m_vec[2]*v.m_vec[2];
    }
    /** @brief length squared of the vector  벡터의 제곱 길이 */
    double	lengthSquared(void) const {
        return m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2];
    }
    /** @brief length of the vector	 벡터의 짧은 길이   */
    double	length(void) const {
        return sqrt(lengthSquared());
    }
    /** @brief cross product	 	 십자가 제품   */
    PxVector3Double cross(const PxVector3Double &v) const {
        return PxVector3Double(m_vec[1]*v.m_vec[2] - m_vec[2]*v.m_vec[1], m_vec[2]*v.m_vec[0] - m_vec[0]*v.m_vec[2], m_vec[0]*v.m_vec[1] - m_vec[1]*v.m_vec[0]);
    }
    /** @brief normalizes the vector 	 벡터를 정규화합니다.  */
    PxVector3Double &normalize(void) {
        const double l = 1.f / length();
        for (int i=0; i < 3; i++) {
            m_vec[i] *= l;
        }
        return *this;
    }

    friend class PxMatrix3x3;
protected:
    double m_vec[3];
};

MAVLinkSimulationWaypointPlanner::MAVLinkSimulationWaypointPlanner(MAVLinkSimulationLink *parent, int sysid) :
    QObject(parent),
    link(parent),
    idle(false),
    current_active_wp_id(-1),
    timestamp_lastoutside_orbit(0),
    timestamp_firstinside_orbit(0),
    waypoints(&waypoints1),
    waypoints_receive_buffer(&waypoints2),
    current_state(PX_WPP_IDLE),
    protocol_current_wp_id(0),
    protocol_current_count(0),
    protocol_current_partner_systemid(0),
    protocol_current_partner_compid(0),
    protocol_timestamp_lastaction(0),
    protocol_timeout(1000),
    timestamp_last_send_setpoint(0),
    systemid(sysid),
    compid(MAV_COMP_ID_MISSIONPLANNER),
    setpointDelay(10),
    yawTolerance(0.4f),
    silent(false)
{
    connect(parent, SIGNAL(messageReceived(mavlink_message_t)), this, SLOT(handleMessage(mavlink_message_t)));
    QLOG_DEBUG() << "PLANNER FOR SYSTEM" << systemid << "INITIALIZED";
}



/*
*  @brief Sends an waypoint ack message	 웨이 포인트 응답 메시지를 보냅니다.  
*/
void MAVLinkSimulationWaypointPlanner::send_waypoint_ack(uint8_t target_systemid, uint8_t target_compid, uint8_t type)
{
    mavlink_message_t msg;
    mavlink_mission_ack_t wpa;

    wpa.target_system = target_systemid;
    wpa.target_component = target_compid;
    wpa.type = type;

    mavlink_msg_mission_ack_encode(systemid, compid, &msg, &wpa);
    link->sendMAVLinkMessage(&msg);

    QLOG_INFO() << "Sent waypoint ack (%u) to ID" << wpa.type << wpa.target_system << "\n";
}

/*
*  @brief Broadcasts the new target waypoint and directs the MAV to fly there
*
*  This function broadcasts its new active waypoint sequence number and
*  sends a message to the controller, advising it to fly to the coordinates
*  of the waypoint with a given orientation
*
*  @param seq The waypoint sequence number the MAV should fly to.
*/

/*
* @brief 새로운 목표 웨이 포인트를 방송하고 MAV가 거기로 날아 오도록 지시합니다.
*
*이 기능은 새로운 활성 웨이 포인트 시퀀스 번호를 브로드 캐스트하고
* 컨트롤러에 메시지를 보냅니다. 좌표로 날아 가라고 명령합니다.
주어진 방향을 가진 웨이 포인트의 *
*
* @param seq MAV가 비행해야하는 웨이 포인트 시퀀스 번호.
*/

void MAVLinkSimulationWaypointPlanner::send_waypoint_current(uint16_t seq)
{
    if(seq < waypoints->size()) {
        mavlink_mission_item_t *cur = waypoints->at(seq);

        mavlink_message_t msg;
        mavlink_mission_current_t wpc;

        wpc.seq = cur->seq;

        mavlink_msg_mission_current_encode(systemid, compid, &msg, &wpc);
        link->sendMAVLinkMessage(&msg);

        QLOG_INFO() << "Broadcasted new current waypoint " << wpc.seq << "\n";
    }
}

/*
*  @brief Directs the MAV to fly to a position
*
*  Sends a message to the controller, advising it to fly to the coordinates
*  of the waypoint with a given orientation
*
*  @param seq The waypoint sequence number the MAV should fly to.
*/	 

/*
* @brief MAV가 특정 위치로 날아 오도록 지시합니다.
*
* 컨트롤러에 메시지를 보냅니다. 좌표로 날아 가라고 명령합니다.
주어진 방향을 가진 웨이 포인트의 *
*
* @param seq MAV가 비행해야하는 웨이 포인트 시퀀스 번호.
*/

void MAVLinkSimulationWaypointPlanner::send_setpoint(uint16_t seq)
{
    if(seq < waypoints->size()) {
        mavlink_mission_item_t *cur = waypoints->at(seq);

        // send new set point to local IMU	 새로운 설정 값을 로컬 IMU에 보낸다.  
        if (cur->frame == MAV_FRAME_LOCAL_NED || cur->frame == MAV_FRAME_LOCAL_ENU) {

            uint64_t now = QGC::groundTimeMilliseconds();
            timestamp_last_send_setpoint = now;
        } else {
            qDebug("No new set point sent to IMU because the new waypoint %u had no local coordinates\n", cur->seq);
        }

    }
}

void MAVLinkSimulationWaypointPlanner::send_waypoint_count(uint8_t target_systemid, uint8_t target_compid, uint16_t count)
{
    mavlink_message_t msg;
    mavlink_mission_count_t wpc;

    wpc.target_system = target_systemid;
    wpc.target_component = target_compid;
    wpc.count = count;

    mavlink_msg_mission_count_encode(systemid, compid, &msg, &wpc);
    link->sendMAVLinkMessage(&msg);

    QLOG_INFO() << "Sent waypoint count (" << wpc.count
                << " << ) to ID " << wpc.target_system << "\n";


}

void MAVLinkSimulationWaypointPlanner::send_waypoint(uint8_t target_systemid, uint8_t target_compid, uint16_t seq)
{
    if (seq < waypoints->size()) {
        mavlink_message_t msg;
        mavlink_mission_item_t *wp = waypoints->at(seq);
        wp->target_system = target_systemid;
        wp->target_component = target_compid;

        QLOG_INFO() << "Sent waypoint " << wp->seq << " (" << wp->target_system << " / "
               << wp->target_component << " / " << wp->seq << " / " << wp->frame  << " / " << wp->command
               << " / " << wp->param3 << " / " << wp->param1 << " / " << wp->param2 << " / " << wp->current
               << " / " << wp->x << " / " << wp->y << " / " << wp->z << " / " << wp->param4 << " / " << wp->autocontinue << ")\n";

        mavlink_msg_mission_item_encode(systemid, compid, &msg, wp);
        link->sendMAVLinkMessage(&msg);
        QLOG_INFO() << "Sent waypoint " << wp->seq << "to ID " <<  wp->target_system << "\n";


    } else {
        QLOG_INFO() << "ERROR: index out of bounds\n";
    }
}

void MAVLinkSimulationWaypointPlanner::send_waypoint_request(uint8_t target_systemid, uint8_t target_compid, uint16_t seq)
{
    mavlink_message_t msg;
    mavlink_mission_request_t wpr;
    wpr.target_system = target_systemid;
    wpr.target_component = target_compid;
    wpr.seq = seq;
    mavlink_msg_mission_request_encode(systemid, compid, &msg, &wpr);
    link->sendMAVLinkMessage(&msg);
    QLOG_INFO() << "Sent waypoint request " << wpr.seq << " to ID "<< wpr.target_system << "\n";


}

/*
*  @brief emits a message that a waypoint reached
*
*  This function broadcasts a message that a waypoint is reached.
*
*  @param seq The waypoint sequence number the MAV has reached.
*/

/*
* @ brief는 중간 지점에 도달했다는 메시지를 내 보냅니다.
*
*이 함수는 웨이 포인트에 도달했다는 메시지를 방송합니다.
*
* @param seq MAV가 도달 한 웨이 포인트 시퀀스 번호.
*/

void MAVLinkSimulationWaypointPlanner::send_waypoint_reached(uint16_t seq)
{
    mavlink_message_t msg;
    mavlink_mission_item_reached_t wp_reached;

    wp_reached.seq = seq;

    mavlink_msg_mission_item_reached_encode(systemid, compid, &msg, &wp_reached);
    link->sendMAVLinkMessage(&msg);

    QLOG_INFO() << "Sent waypoint " << wp_reached.seq << " reached message\n";


}

float MAVLinkSimulationWaypointPlanner::distanceToSegment(uint16_t seq, float x, float y, float z)
{
    if (seq < waypoints->size()) {
        mavlink_mission_item_t *cur = waypoints->at(seq);

        const PxVector3 A(cur->x, cur->y, cur->z);
        const PxVector3 C(x, y, z);

        // seq not the second last waypoint	  마지막 두 번째 웨이 포인트가 아닌 seq  
        if ((uint16_t)(seq+1) < waypoints->size()) {
            mavlink_mission_item_t *next = waypoints->at(seq+1);
            const PxVector3 B(next->x, next->y, next->z);
            const float r = (B-A).dot(C-A) / (B-A).lengthSquared();
            if (r >= 0 && r <= 1) {
                const PxVector3 P(A + r*(B-A));
                return (P-C).length();
            } else if (r < 0.f) {
                return (C-A).length();
            } else {
                return (C-B).length();
            }
        } else {
            return (C-A).length();
        }
    }
    return -1.f;
}

float MAVLinkSimulationWaypointPlanner::distanceToPoint(uint16_t seq, float x, float y, float z)
{
    if (seq < waypoints->size()) {
        mavlink_mission_item_t *cur = waypoints->at(seq);

        const PxVector3 A(cur->x, cur->y, cur->z);
        const PxVector3 C(x, y, z);

        return (C-A).length();
    }
    return -1.f;
}

float MAVLinkSimulationWaypointPlanner::distanceToPoint(uint16_t seq, float x, float y)
{
    if (seq < waypoints->size()) {
        mavlink_mission_item_t *cur = waypoints->at(seq);

        const PxVector3 A(cur->x, cur->y, 0);
        const PxVector3 C(x, y, 0);

        return (C-A).length();
    }
    return -1.f;
}

void MAVLinkSimulationWaypointPlanner::handleMessage(const mavlink_message_t& msg)
{
    mavlink_handler(&msg);
}

void MAVLinkSimulationWaypointPlanner::mavlink_handler (const mavlink_message_t* msg)
{
    // Handle param messages
//        paramClient->handleMAVLinkPacket(msg);

    //check for timed-out operations

/*
    // param 메시지를 처리한다.
//         paramClient-> handleMAVLinkPacket (msg);

    // 시간 초과 된 작업을 확인합니다.
*/


    QLOG_DEBUG() << "MAV: %d WAYPOINTPLANNER GOT MESSAGE" << systemid;

    uint64_t now = QGC::groundTimeMilliseconds();
    if (now-protocol_timestamp_lastaction > protocol_timeout && current_state != PX_WPP_IDLE) {
        QLOG_INFO() << "Last operation (state=%u) timed out, changing state to PX_WPP_IDLE" << current_state;
        current_state = PX_WPP_IDLE;
        protocol_current_count = 0;
        protocol_current_partner_systemid = 0;
        protocol_current_partner_compid = 0;
        protocol_current_wp_id = -1;

        if(waypoints->size() == 0) {
            current_active_wp_id = -1;
        }
    }

    if(now-timestamp_last_send_setpoint > setpointDelay) {
        send_setpoint(current_active_wp_id);
    }

    switch(msg->msgid) {
    case MAVLINK_MSG_ID_ATTITUDE: {
        if(msg->sysid == systemid && current_active_wp_id < waypoints->size()) {
            mavlink_mission_item_t *wp = waypoints->at(current_active_wp_id);
            if(wp->frame == 1) {
                mavlink_attitude_t att;
                mavlink_msg_attitude_decode(msg, &att);
                float yaw_tolerance = yawTolerance;
                //compare current yaw	 현재 요를 비교합니다.  
                if (att.yaw - yaw_tolerance >= 0.0f && att.yaw + yaw_tolerance < 2.f*M_PI) {
                    if (att.yaw - yaw_tolerance <= wp->param4 && att.yaw + yaw_tolerance >= wp->param4)
                        yawReached = true;
                } else if(att.yaw - yaw_tolerance < 0.0f) {
                    float lowerBound = 360.0f + att.yaw - yaw_tolerance;
                    if (lowerBound < wp->param4 || wp->param4 < att.yaw + yaw_tolerance)
                        yawReached = true;
                } else {
                    float upperBound = att.yaw + yaw_tolerance - 2.f*M_PI;
                    if (att.yaw - yaw_tolerance < wp->param4 || wp->param4 < upperBound)
                        yawReached = true;
                }

                // FIXME HACK: Ignore yaw:	 FIXME HACK : 무시한다.  

                yawReached = true;
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_LOCAL_POSITION_NED: {
        if(msg->sysid == systemid && current_active_wp_id < waypoints->size()) {
            mavlink_mission_item_t *wp = waypoints->at(current_active_wp_id);

            if(wp->frame == 1) {
                mavlink_local_position_ned_t pos;
                mavlink_msg_local_position_ned_decode(msg, &pos);
                QLOG_DEBUG() << "Received new position: x:" << pos.x << "| y:" << pos.y << "| z:" << pos.z;

                posReached = false;

                // compare current position (given in message) with current waypoint	 현재의 웨이 포인트와 현재의 위치 (메세지로 지정)를 비교한다  
                float orbit = wp->param1;

                float dist;
                if (wp->param2 == 0) {
                    dist = distanceToSegment(current_active_wp_id, pos.x, pos.y, pos.z);
                } else {
                    dist = distanceToPoint(current_active_wp_id, pos.x, pos.y, pos.z);
                }

                if (dist >= 0.f && dist <= orbit && yawReached) {
                    posReached = true;
                }
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
        if(msg->sysid == systemid && current_active_wp_id < waypoints->size()) {
            mavlink_mission_item_t *wp = waypoints->at(current_active_wp_id);

            if(wp->frame == 0) {
                mavlink_global_position_int_t pos;
                mavlink_msg_global_position_int_decode(msg, &pos);

                float x = static_cast<double>(pos.lat)/1E7;
                float y = static_cast<double>(pos.lon)/1E7;
                //float z = static_cast<double>(pos.alt)/1000;

                QLOG_DEBUG() << "Received new position: x:" << x << "| y:" << y << "| z:" << "N/A";//z;

                posReached = false;
                yawReached = true;

                // FIXME big hack for simulation!
                //float oneDegreeOfLatMeters = 111131.745f;

/*
                // 시뮬레이션을위한 큰 해킹을 고칩니다!
                // float oneDegreeOfLatMeters = 111131.745f;
*/

                float orbit = 0.00008f;

                // compare current position (given in message) with current waypoint
                //float orbit = wp->param1;

                // Convert to degrees

/*
                // 현재의 웨이 포인트와 현재의 위치 (메세지로 지정)를 비교한다
                // float orbit = wp-> param1;

                // 도 단위로 변환
*/



                float dist;
                dist = distanceToPoint(current_active_wp_id, x, y);

                if (dist >= 0.f && dist <= orbit && yawReached) {
                    posReached = true;
                    QLOG_INFO() << "WP PLANNER: REACHED POSITION";
                }
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_COMMAND_LONG:
    { // special action from ground station	  지상국의 특수 작전  
        mavlink_command_long_t action;
        mavlink_msg_command_long_decode(msg, &action);
        if(action.target_system == systemid) {
            QLOG_INFO() << "Waypoint: received message with action " << action.command << "\n";
//            switch (action.action) {
//				case MAV_ACTION_LAUNCH:
//					if (verbose) std::cerr << "Launch received" << std::endl;
//					current_active_wp_id = 0;
//					if (waypoints->size()>0)
//					{
//						setActive(waypoints[current_active_wp_id]);
//					}
//					else
//						if (verbose) std::cerr << "No launch, waypointList empty" << std::endl;
//					break;

//				case MAV_ACTION_CONTINUE:
//					if (verbose) std::c
//					err << "Continue received" << std::endl;
//					idle = false;
//					setActive(waypoints[current_active_wp_id]);
//					break;

//				case MAV_ACTION_HALT:
//					if (verbose) std::cerr << "Halt received" << std::endl;
//					idle = true;
//					break;

//				default:
//					if (verbose) std::cerr << "Unknown action received with id " << action.action << ", no action taken" << std::endl;
//					break;
//            }
        }
        break;
	}

    case MAVLINK_MSG_ID_MISSION_ACK: {
        mavlink_mission_ack_t wpa;
        mavlink_msg_mission_ack_decode(msg, &wpa);

        if((msg->sysid == protocol_current_partner_systemid && msg->compid == protocol_current_partner_compid) && (wpa.target_system == systemid && wpa.target_component == compid)) {
            protocol_timestamp_lastaction = now;

            if (current_state == PX_WPP_SENDLIST || current_state == PX_WPP_SENDLIST_SENDWPS) {
                if (protocol_current_wp_id == waypoints->size()-1) {
                    QLOG_INFO() << "Received Ack after having sent last waypoint, going to state PX_WPP_IDLE\n";
                    current_state = PX_WPP_IDLE;
                    protocol_current_wp_id = 0;
                }
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_SET_CURRENT: {
        mavlink_mission_set_current_t wpc;
        mavlink_msg_mission_set_current_decode(msg, &wpc);

        if(wpc.target_system == systemid && wpc.target_component == compid) {
            protocol_timestamp_lastaction = now;

            if (current_state == PX_WPP_IDLE) {
                if (wpc.seq < waypoints->size()) {
                    QLOG_INFO() << "Received MAVLINK_MSG_ID_MISSION_ITEM_SET_CURRENT\n";
                    current_active_wp_id = wpc.seq;
                    uint32_t i;
                    for(i = 0; i < waypoints->size(); i++) {
                        if (i == current_active_wp_id) {
                            waypoints->at(i)->current = true;
                        } else {
                            waypoints->at(i)->current = false;
                        }
                    }
                    QLOG_INFO() << "New current waypoint " << current_active_wp_id << "\n";
                    yawReached = false;
                    posReached = false;
                    send_waypoint_current(current_active_wp_id);
                    send_setpoint(current_active_wp_id);
                    timestamp_firstinside_orbit = 0;
                } else {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_SET_CURRENT: Index out of bounds\n";
                }
            }
        } else {
            QLOG_INFO() << "SYSTEM / COMPONENT ID MISMATCH: target sys:" << wpc.target_system
                        << "this system:" << systemid << "target comp:" << wpc.target_component
                        << "this comp:" << compid;
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_REQUEST_LIST: {
        mavlink_mission_request_list_t wprl;
        mavlink_msg_mission_request_list_decode(msg, &wprl);
        if(wprl.target_system == systemid && wprl.target_component == compid) {
            protocol_timestamp_lastaction = now;

            if (current_state == PX_WPP_IDLE || current_state == PX_WPP_SENDLIST) {
                if (waypoints->size() > 0) {
                    if (current_state == PX_WPP_IDLE) {
                        QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_REQUEST_LIST from"
                                    << msg->sysid <<" changing state to PX_WPP_SENDLIST\n";
                    }
                    if (current_state == PX_WPP_SENDLIST) {
                        QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_REQUEST_LIST again from"
                                    << msg->sysid << "staying in state PX_WPP_SENDLIST\n";
                    }
                    current_state = PX_WPP_SENDLIST;
                    protocol_current_wp_id = 0;
                    protocol_current_partner_systemid = msg->sysid;
                    protocol_current_partner_compid = msg->compid;
                } else {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_REQUEST_LIST from "
                                << msg->sysid << " but have no waypoints, staying in \n";
                }
                protocol_current_count = waypoints->size();
                send_waypoint_count(msg->sysid,msg->compid, protocol_current_count);
            } else {
                QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST_LIST because i'm doing something else already (state="
                            << current_state << ").\n";
            }
        } else {
            QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST_LIST because not my systemid or compid.\n";
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_REQUEST: {
        mavlink_mission_request_t wpr;
        mavlink_msg_mission_request_decode(msg, &wpr);
        if(msg->sysid == protocol_current_partner_systemid && msg->compid == protocol_current_partner_compid
                && wpr.target_system == systemid && wpr.target_component == compid) {
            protocol_timestamp_lastaction = now;

            //ensure that we are in the correct state and that the first request
            //has id 0 and the following requests have either the last id
            // (re-send last waypoint) or last_id+1 (next waypoint)

/*
            // 우리가 올바른 상태에 있고 첫 번째 요청이
            // 는 id가 0이고 다음 요청은 마지막 ID
            // (마지막 웨이 포인트 재전송) 또는 last_id + 1 (다음 웨이 포인트)
*/

            if ((current_state == PX_WPP_SENDLIST && wpr.seq == 0)
                    || (current_state == PX_WPP_SENDLIST_SENDWPS
                        && (wpr.seq == protocol_current_wp_id || wpr.seq == protocol_current_wp_id + 1)
                        && wpr.seq < waypoints->size())) {
                if (current_state == PX_WPP_SENDLIST) {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_REQUEST of waypoint"
                                << wpr.seq  << "from" << msg->sysid
                                << "changing state to PX_WPP_SENDLIST_SENDWPS\n";
                }
                if (current_state == PX_WPP_SENDLIST_SENDWPS
                    && wpr.seq == protocol_current_wp_id + 1) {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_REQUEST of waypoint "
                                <<  wpr.seq << " from " << msg->sysid << " staying in state PX_WPP_SENDLIST_SENDWPS\n";
                }
                if (current_state == PX_WPP_SENDLIST_SENDWPS
                    && wpr.seq == protocol_current_wp_id) {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_REQUEST of waypoint "
                                << wpr.seq << "(again) from " << msg->sysid << " staying in state PX_WPP_SENDLIST_SENDWPS\n";
                }
                current_state = PX_WPP_SENDLIST_SENDWPS;
                protocol_current_wp_id = wpr.seq;
                send_waypoint(protocol_current_partner_systemid, protocol_current_partner_compid, wpr.seq);
            } else {

                if (!(current_state == PX_WPP_SENDLIST || current_state == PX_WPP_SENDLIST_SENDWPS)) {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST because i'm \
                                   doing something else already (state=" << current_state << ").\n";
                                   break;
                } else if (current_state == PX_WPP_SENDLIST) {
                    if (wpr.seq != 0) {
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST because the first requested waypoint ID ("
                                    << wpr.seq << ") was not 0.\n";
                    }
                } else if (current_state == PX_WPP_SENDLIST_SENDWPS) {
                    if (wpr.seq != protocol_current_wp_id && wpr.seq != protocol_current_wp_id + 1)
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST because the requested waypoint ID ("
                                    << wpr.seq << ") was not the expected ("
                                    << protocol_current_wp_id << " or " << protocol_current_wp_id+1 << ").\n";
                    else if (wpr.seq >= waypoints->size()) {
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST because the requested waypoint ID ("
                                    <<  wpr.seq << ") was out of bounds.\n";
                    }
                } else {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST - FIXME: missed error description\n";
                }

            }
        } else {
            //we we're target but already communicating with someone else	 우리는 목표이지만 다른 누군가와 이미 의사 소통 중입니다.  
            if((wpr.target_system == systemid && wpr.target_component == compid)
                    && !(msg->sysid == protocol_current_partner_systemid
                         && msg->compid == protocol_current_partner_compid)) {
                QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_REQUEST from ID "
                            << msg->sysid << " because i'm already talking to ID "
                            << protocol_current_partner_systemid << ".\n";
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_COUNT: {
        mavlink_mission_count_t wpc;
        mavlink_msg_mission_count_decode(msg, &wpc);
        if(wpc.target_system == systemid && wpc.target_component == compid) {
            protocol_timestamp_lastaction = now;

            if (current_state == PX_WPP_IDLE || (current_state == PX_WPP_GETLIST && protocol_current_wp_id == 0)) {
                if (wpc.count > 0) {
                    if (current_state == PX_WPP_IDLE) {
                        QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_COUNT ("
                                    << wpc.count << ") from " << msg->sysid
                                    << " changing state to PX_WPP_GETLIST\n";
                    }
                    if (current_state == PX_WPP_GETLIST) {
                        QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_COUNT ("
                                    << wpc.count << ") again from "
                                    << msg->sysid << "\n";
                    }
                    current_state = PX_WPP_GETLIST;
                    protocol_current_wp_id = 0;
                    protocol_current_partner_systemid = msg->sysid;
                    protocol_current_partner_compid = msg->compid;
                    protocol_current_count = wpc.count;

                    QLOG_INFO() << "clearing receive buffer and readying for receiving waypoints\n";
                    while(waypoints_receive_buffer->size() > 0) {
                        delete waypoints_receive_buffer->back();
                        waypoints_receive_buffer->pop_back();
                    }

                    send_waypoint_request(protocol_current_partner_systemid, protocol_current_partner_compid, protocol_current_wp_id);
                } else {
                    QLOG_INFO() << "Ignoring MAVLINK_MSG_ID_MISSION_COUNT from "
                                << msg->sysid << " with count of " << wpc.count << "\n";
                }
            } else {
                if (!(current_state == PX_WPP_IDLE || current_state == PX_WPP_GETLIST)) {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_COUNT because i'm doing something else already (state="
                                << current_state << ").\n";
                } else if (current_state == PX_WPP_GETLIST && protocol_current_wp_id != 0) {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_COUNT because i'm already receiving waypoint "
                                << protocol_current_wp_id << ".\n";
                }
                else {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_COUNT - FIXME: missed error description\n";
                }
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_ITEM: {
        mavlink_mission_item_t wp;
        mavlink_msg_mission_item_decode(msg, &wp);

        if((msg->sysid == protocol_current_partner_systemid && msg->compid == protocol_current_partner_compid)
                && (wp.target_system == systemid && wp.target_component == compid)) {
            protocol_timestamp_lastaction = now;

            //ensure that we are in the correct state and that the first
            //waypoint has id 0 and the following waypoints have the correct ids

/*
            // 우리가 올바른 상태에 있고 첫 번째
            // waypoint는 id가 0이고 다음 웨이 포인트는 올바른 id를가집니다.
*/

            if ((current_state == PX_WPP_GETLIST && wp.seq == 0)
                   || (current_state == PX_WPP_GETLIST_GETWPS && wp.seq == protocol_current_wp_id
                       && wp.seq < protocol_current_count)) {
                if (current_state == PX_WPP_GETLIST) {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM "
                                << wp.seq << " from "
                                << msg->sysid << " changing state to PX_WPP_GETLIST_GETWPS\n";
                }
                if (current_state == PX_WPP_GETLIST_GETWPS && wp.seq == protocol_current_wp_id) {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM "
                                << wp.seq << " from " << msg->sysid << "\n";
                }
                if (current_state == PX_WPP_GETLIST_GETWPS && wp.seq-1 == protocol_current_wp_id) {
                    QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM "
                                << wp.seq << " (again) from " << msg->sysid << "\n";
                }
                current_state = PX_WPP_GETLIST_GETWPS;
                protocol_current_wp_id = wp.seq + 1;
                mavlink_mission_item_t* newwp = new mavlink_mission_item_t;
                memcpy(newwp, &wp, sizeof(mavlink_mission_item_t));
                waypoints_receive_buffer->push_back(newwp);

                if(protocol_current_wp_id == protocol_current_count && current_state == PX_WPP_GETLIST_GETWPS) {
                        QLOG_INFO() << "Got all " << protocol_current_count
                                    << " waypoints, changing state to PX_WPP_IDLE\n";

                    send_waypoint_ack(protocol_current_partner_systemid, protocol_current_partner_compid, 0);

                    if (current_active_wp_id > waypoints_receive_buffer->size()-1) {
                        current_active_wp_id = waypoints_receive_buffer->size() - 1;
                    }

                    // switch the waypoints list	  경유지 목록을 전환합니다.  
                    std::vector<mavlink_mission_item_t*>* waypoints_temp = waypoints;
                    waypoints = waypoints_receive_buffer;
                    waypoints_receive_buffer = waypoints_temp;

                    //get the new current waypoint	 새로운 현재 웨이 포인트를 얻는다.  
                    uint32_t i;
                    for(i = 0; i < waypoints->size(); i++) {
                        if (waypoints->at(i)->current == 1) {
                            current_active_wp_id = i;
                            //if (verbose) QLOG_INFO() << "New current waypoint " << current_active_wp_id << "\n";
                            yawReached = false;
                            posReached = false;
                            send_waypoint_current(current_active_wp_id);
                            send_setpoint(current_active_wp_id);
                            timestamp_firstinside_orbit = 0;
                            break;
                        }
                    }

                    if (i == waypoints->size()) {
                        current_active_wp_id = -1;
                        yawReached = false;
                        posReached = false;
                        timestamp_firstinside_orbit = 0;
                    }

                    current_state = PX_WPP_IDLE;
                } else {
                    send_waypoint_request(protocol_current_partner_systemid, protocol_current_partner_compid, protocol_current_wp_id);
                }
            } else {
                if (current_state == PX_WPP_IDLE) {
                    //we're done receiving waypoints, answer with ack.	 우리는 웨이 포인트 수신을 마쳤습니다.  
                    send_waypoint_ack(protocol_current_partner_systemid, protocol_current_partner_compid, 0);
                    QLOG_INFO() << "Received MAVLINK_MSG_ID_MISSION_ITEM while state=PX_WPP_IDLE, answered with WAYPOINT_ACK.\n";
                }

                if (!(current_state == PX_WPP_GETLIST || current_state == PX_WPP_GETLIST_GETWPS)) {
                    QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM "
                                << wp.seq << " because i'm doing something else already (state="
                                << current_state << ").\n";
                    break;
                } else if (current_state == PX_WPP_GETLIST) {
                    if(!(wp.seq == 0))
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM because the first waypoint ID ("
                                    << wp.seq <<") was not 0.\n";
                    else
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM "
                                    << wp.seq << " - FIXME: missed error description\n";
                } else if (current_state == PX_WPP_GETLIST_GETWPS) {
                    if (!(wp.seq == protocol_current_wp_id))
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM because the waypoint ID ("
                                    << wp.seq << ") was not the expected "
                                    << protocol_current_wp_id << ".\n";
                    else if (!(wp.seq < protocol_current_count))
                        QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM because the waypoint ID ("
                                    << wp.seq << ") was out of bounds.\n";
                    else QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM "
                                     << wp.seq << " - FIXME: missed error description\n";
                } else QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM "
                                   << wp.seq << " - FIXME: missed error description\n";
            }
        } else {
            // We're target but already communicating with someone else	 목표이지만 이미 다른 사람과 통신 중입니다.  
            if((wp.target_system == systemid && wp.target_component == compid) && !(msg->sysid == protocol_current_partner_systemid && msg->compid == protocol_current_partner_compid) && current_state != PX_WPP_IDLE) {
                QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM "
                            << wp.seq << " from ID " << msg->sysid << " because i'm already talking to ID "
                            << protocol_current_partner_systemid << ".\n";
            } else if(wp.target_system == systemid && wp.target_component == compid) {
                QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM "
                            << wp.seq << " from ID "
                            << msg->sysid << " because i have no idea what to do with it\n";
            }
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_CLEAR_ALL: {
        mavlink_mission_clear_all_t wpca;
        mavlink_msg_mission_clear_all_decode(msg, &wpca);

        if(wpca.target_system == systemid && wpca.target_component == compid && current_state == PX_WPP_IDLE) {
            protocol_timestamp_lastaction = now;

            QLOG_INFO() << "Got MAVLINK_MSG_ID_MISSION_ITEM_CLEAR_LIST from "
                                     << msg->sysid << " deleting all waypoints\n";
            while(waypoints->size() > 0) {
                delete waypoints->back();
                waypoints->pop_back();
            }
            current_active_wp_id = -1;
        } else if (wpca.target_system == systemid && wpca.target_component == compid && current_state != PX_WPP_IDLE) {
            QLOG_INFO() << "Ignored MAVLINK_MSG_ID_MISSION_ITEM_CLEAR_LIST from "
                        << msg->sysid << " because i'm doing something else already (state=" << current_state << ").\n";
        }
        break;
    }

    default: {
        break;
    }
    }

    //check if the current waypoint was reached	 현재 웨이 포인트에 도달했는지 확인  
    if ((posReached && /*yawReached &&*/ !idle)) {
        if (current_active_wp_id < waypoints->size()) {
            mavlink_mission_item_t *cur_wp = waypoints->at(current_active_wp_id);

            if (timestamp_firstinside_orbit == 0) {
                // Announce that last waypoint was reached	 마지막 웨이 포인트에 도달했음을 발표합니다.  
                QLOG_INFO() << "*** Reached waypoint " << cur_wp->seq << " ***\n";
                send_waypoint_reached(cur_wp->seq);
                timestamp_firstinside_orbit = now;
            }

            // check if the MAV was long enough inside the waypoint orbit
            //if (now-timestamp_lastoutside_orbit > (cur_wp->hold_time*1000))

/*
            // MAV가 웨이 포인트 궤도 내부에서 충분히 길 었는지 확인
            // if (now-timestamp_lastoutside_orbit> (cur_wp-> hold_time * 1000))
*/

            if(now-timestamp_firstinside_orbit >= cur_wp->param2*1000) {
                if (cur_wp->autocontinue) {
                    cur_wp->current = 0;
                    if (current_active_wp_id == waypoints->size() - 1 && waypoints->size() > 0) {
                        //the last waypoint was reached, if auto continue is
                        //activated restart the waypoint list from the beginning

/*
                        // 자동 계속이있는 경우 마지막 웨이 포인트에 도달했습니다.
                        // activated 웨이 포인트리스트를 처음부터 다시 시작합니다.
*/

                        current_active_wp_id = 0;
                    } else {
                        current_active_wp_id++;
                    }

                    // Fly to next waypoint	 다음 웨이 포인트로 날아라.  
                    timestamp_firstinside_orbit = 0;
                    send_waypoint_current(current_active_wp_id);
                    send_setpoint(current_active_wp_id);
                    waypoints->at(current_active_wp_id)->current = true;
                    posReached = false;
                    //yawReached = false;
                    QLOG_INFO() << "Set new waypoint (" << current_active_wp_id << ")\n";
                }
            }
        }
    } else {
        timestamp_lastoutside_orbit = now;
    }
}
