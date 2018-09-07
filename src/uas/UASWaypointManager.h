/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of the waypoint protocol handler
 *
 *   @author Petri Tanskanen <mavteam@student.ethz.ch>
 *
 */
/* *
 * @file
 * @brief 웨이 포인트 프로토콜 핸들러의 정의
 *
 * @author Petri Tanskanen <mavteam@student.ethz.ch>
 *
 */

#ifndef UASWAYPOINTMANAGER_H
#define UASWAYPOINTMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include "Waypoint.h"
#include "QGCMAVLink.h"
class UAS;
class UASInterface;

/**
 * @brief Implementation of the MAVLINK waypoint protocol
 *
 * This class handles the communication with a waypoint manager on the MAV.
 * All waypoints are stored in the QList waypoints, modifications can be done with the WaypointList widget.
 * Notice that currently the access to the internal waypoint storage is not guarded nor thread-safe. This works as long as no other widget alters the data.
 *
 * See http://qgroundcontrol.org/waypoint_protocol for more information about the protocol and the states.
 */
/* *
 * @brief MAVLINK 웨이 포인트 프로토콜 구현
 *
 *이 클래스는 MAV에서 웨이 포인트 매니저와의 통신을 처리합니다.
 * 모든 경유지는 QList 경유지에 저장되며, WaypointList 위젯으로 수정할 수 있습니다.
* 현재 내부 웨이 포인트 저장소에 대한 액세스는 보호되거나 스레드로부터 안전하지 않습니다. 이것은 다른 위젯이 데이터를 변경하지 않는 한 작동합니다.
 *
 * 프로토콜 및 상태에 대한 자세한 내용은 http://qgroundcontrol.org/waypoint_protocol을 참조하십시오.
 */
class UASWaypointManager : public QObject
{
    Q_OBJECT
private:
    enum WaypointState {
        WP_IDLE = 0,        ///< Waiting for commands// / <명령 대기 중
        WP_SENDLIST,        ///< Initial state for sending waypoints to the MAV// / <웨이 포인트를 MAV로 보내는 초기 상태
        WP_SENDLIST_SENDWPS,///< Sending waypoints// / <웨이 포인트 보내기
        WP_GETLIST,         ///< Initial state for retrieving waypoints from the MAV// / <MAV에서 웨이 포인트를 검색하기위한 초기 상태
        WP_GETLIST_GETWPS,  ///< Receiving waypoints// / <웨이 포인트 받기
        WP_CLEARLIST,       ///< Clearing waypoint list on the MAV// / <MAV에서 웨이 포인트 목록 지우기
        WP_SETCURRENT       ///< Setting new current waypoint on the MAV// / <MAV에서 새로운 현재 웨이 포인트 설정
    }; ///< The possible states for the waypoint protocol// / <웨이 포인트 프로토콜의 가능한 상태

public:
    UASWaypointManager(UAS* uas=NULL);   ///< Standard constructor// / <표준 생성자
    ~UASWaypointManager();
    bool guidedModeSupported();

    void goToWaypoint(Waypoint *wp);
    /** @name Received message handlers */
    /*@{*/
    void handleWaypointCount(quint8 systemId, quint8 compId, quint16 count);                            ///< Handles received waypoint count messages// / <수신 된 웨이 포인트 수 메시지를 처리합니다.
    void handleWaypoint(quint8 systemId, quint8 compId, mavlink_mission_item_t *wp);                        ///< Handles received waypoint messages// / <수신 된 웨이 포인트 메시지를 처리합니다.
    void handleWaypointAck(quint8 systemId, quint8 compId, mavlink_mission_ack_t *wpa);                ///< Handles received waypoint ack messages// / <수신 된 웨이 포인트 ACK 메시지를 처리합니다.
    void handleWaypointRequest(quint8 systemId, quint8 compId, mavlink_mission_request_t *wpr);        ///< Handles received waypoint request messages// / <수신 된 웨이 포인트 요청 메시지를 처리합니다.
    void handleWaypointReached(quint8 systemId, quint8 compId, mavlink_mission_item_reached_t *wpr);        ///< Handles received waypoint reached messages// / <수신 된 웨이 포인트가 메시지에 도달하면 처리합니다.
    void handleWaypointCurrent(quint8 systemId, quint8 compId, mavlink_mission_current_t *wpc);        ///< Handles received set current waypoint messages// / <받은 세트의 현재 웨이 포인트 메시지를 처리합니다.
    /*@}*/

    /** @name Remote operations */
    /*@{*/
    void clearWaypointList();                       ///< Sends the waypoint clear all message to the MAV// / <모든 웨이 포인트 지우기 메시지를 MAV로 보낸다.

    void readWaypoints(bool read_to_edit=false);    ///< Requests the MAV's current waypoint list.// / <MAV의 현재 웨이 포인트 목록을 요청합니다.
    void writeWaypoints();                          ///< Sends the waypoint list to the MAV// / <웨이 포인트리스트를 MAV에 보냅니다.
    int setCurrentWaypoint(quint16 seq);            ///< Sends the sequence number of the waypoint that should get the new target waypoint to the UAS// / <새 목표 웨이 포인트를 UAS에 가져와야하는 웨이 포인트의 시퀀스 번호를 보냅니다.
    int setCurrentEditable(quint16 seq);          ///< Changes the current waypoint in edit tab// / <편집 탭에서 현재 웨이 포인트를 변경합니다.
    /*@}*/

    /** @name Waypoint list operations */
    /*@{*/
    const QList<Waypoint *> &getWaypointEditableList(void) {
        return waypointsEditable;    ///< Returns a const reference to the waypoint list.// / <웨이 포인트리스트에 대한 const 참조를 반환합니다.
    }
    const QList<Waypoint *> &getWaypointViewOnlyList(void) {
        return waypointsViewOnly;    ///< Returns a const reference to the waypoint list.// / <웨이 포인트리스트에 대한 const 참조를 반환합니다.
    }
    const QList<Waypoint *> getGlobalFrameWaypointList();  ///< Returns a global waypoint list// / <글로벌 웨이 포인트 목록을 반환합니다.
    const QList<Waypoint *> getGlobalFrameAndNavTypeWaypointList(bool onlypath); ///< Returns a global waypoint list containing only waypoints suitable for navigation. Actions and other mission items are filtered out.// / <네비게이션에 적합한 웨이 포인트 만 포함하는 전역 웨이 포인트 목록을 반환합니다. 작업 및 기타 미션 항목은 필터링되어 제거됩니다.
    const QList<Waypoint *> getNavTypeWaypointList(); ///< Returns a waypoint list containing only waypoints suitable for navigation. Actions and other mission items are filtered out.// / <네비게이션에 적합한 웨이 포인트 만 포함하는 웨이 포인트 목록을 반환합니다. 작업 및 기타 미션 항목은 필터링되어 제거됩니다.
    const Waypoint* getWaypoint(int index);     ///< Returns the waypoint at index, or NULL if not valid.// / <인덱스에서 웨이 포인트를 반환하거나, 유효하지 않으면 NULL을 반환합니다.
    int getIndexOf(Waypoint* wp);                   ///< Get the index of a waypoint in the list// / <목록에서 웨이 포인트 인덱스 가져 오기
    int getGlobalFrameIndexOf(Waypoint* wp);    ///< Get the index of a waypoint in the list, counting only global waypoints// / <목록에서 웨이 포인트 인덱스를 가져 와서 전역 웨이 포인트 만 계산합니다.
    int getGlobalFrameAndNavTypeIndexOf(Waypoint* wp); ///< Get the index of a waypoint in the list, counting only global AND navigation mode waypoints// / <목록에서 웨이 포인트 인덱스 가져 오기, 전역 AND 탐색 모드 웨이 포인트 만 계산
    int getNavTypeIndexOf(Waypoint* wp); ///< Get the index of a waypoint in the list, counting only navigation mode waypoints// / <탐색 모드 웨이 포인트 만 세어 목록에서 웨이 포인트의 인덱스를 가져옵니다.
    int getLocalFrameIndexOf(Waypoint* wp);     ///< Get the index of a waypoint in the list, counting only local waypoints// / <목록에서 중간 점의 수를 계산하여 중간 점의 지수를 가져옵니다.
    int getMissionFrameIndexOf(Waypoint* wp);   ///< Get the index of a waypoint in the list, counting only mission waypoints// / <목록에서 중간 지점의 지수를 가져 와서 임무 중간 지점 만 계산합니다.
    int getGlobalFrameCount(); ///< Get the count of global waypoints in the list// / <목록에서 전역 웨이 포인트 수를 가져옵니다.
    int getGlobalFrameAndNavTypeCount(); ///< Get the count of global waypoints in navigation mode in the list// / <목록의 탐색 모드에서 전역 중간 지점 수를 가져옵니다.
    int getNavTypeCount(); ///< Get the count of global waypoints in navigation mode in the list// / <목록의 탐색 모드에서 전역 중간 지점 수를 가져옵니다.
    int getLocalFrameCount();   ///< Get the count of local waypoints in the list// / <목록에서 로컬 웨이 포인트 수를 가져옵니다.
    /*@}*/

    UAS* getUAS();
    double getAltitudeRecommendation(MAV_FRAME frame);
    int getFrameRecommendation();
    double getAcceptanceRadiusRecommendation();

    double getDefaultRelAltitude();

private:
    /** @name Message send functions */
    /*@{*/
    void sendWaypointClearAll();
    void sendWaypointSetCurrent(quint16 seq);
    void sendWaypointCount();
    void sendWaypointRequestList();
    void sendWaypointRequest(quint16 seq);          ///< Requests a waypoint with sequence number seq// / <시퀀스 번호 seq가있는 웨이 포인트를 요청합니다.
    void sendWaypoint(quint16 seq);                 ///< Sends a waypoint with sequence number seq// / <시퀀스 번호 seq가있는 웨이 포인트를 보냅니다.
    void sendWaypointAck(quint8 type);              ///< Sends a waypoint ack// / <웨이 포인트 ack를 보냅니다.
    /*@}*/

    const QVariant readSetting(const QString& key, const QVariant& value);
    void writeSetting(const QString& key, const QVariant& defaultValue);

public slots:
    void timeout();                                 ///< Called by the timer if a response times out. Handles send retries.// / <응답 시간이 초과되면 타이머에 의해 호출됩니다. 처리 재전송을 보냅니다.
    /** @name Waypoint list operations */
    /*@{*/
    void addWaypointEditable(Waypoint *wp, bool enforceFirstActive=true);                 ///< adds a new waypoint to the end of the editable list and changes its sequence number accordingly// / <편집 할 수있는 목록의 끝에 새로운 웨이 포인트를 추가하고 이에 따라 시퀀스 번호를 변경합니다.
    void addWaypointViewOnly(Waypoint *wp);                                               ///< adds a new waypoint to the end of the view-only list and changes its sequence number accordingly// / <뷰 전용 목록의 끝에 새로운 웨이 포인트를 추가하고 이에 따라 시퀀스 번호를 변경합니다.
    Waypoint* createWaypoint(bool enforceFirstActive=true);     ///< Creates a waypoint// / <웨이 포인트를 만듭니다.
    int removeWaypoint(quint16 seq);                       ///< locally remove the specified waypoint from the storage// / <지정된 웨이 포인트를 저장소에서 로컬로 제거합니다.
    void moveWaypoint(quint16 cur_seq, quint16 new_seq);   ///< locally move a waypoint from its current position cur_seq to a new position new_seq // / <현재 위치 cur_seq에서 새 위치 new_seq로 중간 점 이동
    void saveWaypoints(const QString &saveFile);           ///< saves the local waypoint list to saveFile// / <로컬 웨이 포인트 목록을 saveFile에 저장합니다.
    void loadWaypoints(const QString &loadFile);           ///< loads a waypoint list from loadFile// / <loadFile에서 웨이 포인트리스트를로드합니다.
    void notifyOfChangeEditable(Waypoint* wp);             ///< Notifies manager to changes to an editable waypoint// / <편집 가능한 웨이 포인트에 대한 변경 사항을 관리자에게 알립니다.
    void notifyOfChangeViewOnly(Waypoint* wp);             ///< Notifies manager to changes to a viewonly waypoint, e.g. some widget wants to change "current"// / <보기 전용 웨이 포인트에 대한 변경 사항을 관리자에게 알려줍니다. 예를 들어 일부 위젯이 "현재"를 변경하려고합니다.
    /*@}*/
    void handleLocalPositionChanged(UASInterface* mav, double x, double y, double z, quint64 time);
    void handleGlobalPositionChanged(UASInterface* mav, double lat, double lon, double alt, quint64 time);

    void setDefaultRelAltitude(double alt);

signals:
    void waypointEditableListChanged(void);                 ///< emits signal that the list of editable waypoints has been changed// / <편집 가능한 웨이 포인트 목록이 변경되었다는 신호를 내 보냅니다.
    void waypointEditableListChanged(int uasid);            ///< emits signal that the list of editable waypoints has been changed// / <편집 가능한 웨이 포인트 목록이 변경되었다는 신호를 내 보냅니다.
    void waypointEditableChanged(int uasid, Waypoint* wp);  ///< emits signal that a single editable waypoint has been changed// / <편집 가능한 단일 웨이 포인트가 변경되었다는 신호를 내 보냅니다.
    void waypointViewOnlyListChanged(void);                 ///< emits signal that the list of editable waypoints has been changed // / <편집 가능한 웨이 포인트 목록이 변경되었다는 신호를 내 보냅니다.
    void waypointViewOnlyListChanged(int uasid);            ///< emits signal that the list of editable waypoints has been changed// / <편집 가능한 웨이 포인트 목록이 변경되었다는 신호를 내 보냅니다.
    void waypointViewOnlyChanged(int uasid, Waypoint* wp);  ///< emits signal that a single editable waypoint has been changed// / <편집 가능한 단일 웨이 포인트가 변경되었다는 신호를 내 보냅니다.
    void currentWaypointChanged(quint16);           ///< emits the new current waypoint sequence number// / <새로운 현재 웨이 포인트 시퀀스 번호를 내 보냅니다.
    void updateStatusString(const QString &);       ///< emits the current status string// / <현재 상태 문자열을 내 보냅니다.
    void waypointDistanceChanged(double distance);   ///< Distance to next waypoint changed (in meters)// / <다음 웨이 포인트까지의 거리 (미터)

    void loadWPFile();                              ///< emits signal that a file wp has been load// / <wp 파일이로드되었다는 신호를 내 보냅니다.
    void readGlobalWPFromUAS(bool value);           ///< emits signal when finish to read Global WP from UAS// UAS에서 글로벌 WP를 읽으려면 끝낼 때 신호를 내 보냅니다.

private:
    UAS* uas;                                       ///< Reference to the corresponding UAS// / <해당 UAS에 대한 참조
    quint32 current_retries;                        ///< The current number of retries left// / <현재 재시도 횟수
    quint16 current_wp_id;                          ///< The last used waypoint ID in the current protocol transaction// / <현재 프로토콜 트랜잭션에서 마지막으로 사용한 웨이 포인트 ID
    quint16 current_count;                          ///< The number of waypoints in the current protocol transaction// / <현재 프로토콜 트랜잭션의 웨이 포인트 수
    WaypointState current_state;                    ///< The current protocol state// / <현재 프로토콜 상태
    quint8 current_partner_systemid;                ///< The current protocol communication target system// / <현재 프로토콜 통신 대상 시스템
    quint8 current_partner_compid;                  ///< The current protocol communication target component// / <현재 프로토콜 통신 대상 구성 요소
    bool read_to_edit;                              ///< If true, after readWaypoints() incoming waypoints will be copied both to "edit"-tab and "view"-tab. Otherwise, only to "view"-tab.
 // / <true 인 경우, readWaypoints () 수신 웨이 포인트는 "편집"- 탭과 "보기"- 탭으로 복사됩니다. 그렇지 않으면, 오직 "보기"- 탭.
    QList<Waypoint *> waypointsViewOnly;                  ///< local copy of current waypoint list on MAV// / <MAV에서 현재 웨이 포인트리스트의 로컬 복사본
    QList<Waypoint *> waypointsEditable;                  ///< local editable waypoint list// / <편집 가능한 웨이 포인트 목록
    Waypoint* currentWaypointEditable;                      ///< The currently used waypoint// / <현재 사용중인 웨이 포인트
    QList<mavlink_mission_item_t *> waypoint_buffer;  ///< buffer for waypoints during communication// / <통신 중 웨이 포인트 버퍼링
    QTimer protocol_timer;                          ///< Timer to catch timeouts// / <타임 아웃을 잡을 타이머
    bool standalone;                                ///< If standalone is set, do not write to UAS// 독립 실행 형이 설정된 경우 UAS에 쓰지 않습니다.
    quint16 uasid;

    double m_defaultAcceptanceRadius;                 ///< Default Acceptance Radius in meters// / <기본 허용 반경 (미터)
    double m_defaultRelativeAlt;                      ///< Default relative alt in meters// / <기본 상대 고도 (미터)

    quint16 waypointIDHandled;
};

#endif // UASWAYPOINTMANAGER_H
