#ifndef QGCMAPWIDGET_H
#define QGCMAPWIDGET_H

#include <QMap>
#include <QTimer>
#include "../../../libs/opmapcontrol/opmapcontrol.h"

class UASInterface;
class UASWaypointManager;
class Waypoint;
typedef mapcontrol::WayPointItem WayPointItem;

/**
 * @brief Class representing a 2D map using aerial imagery
 */
/* *
 공중 이미지를 사용하는 2D지도를 나타내는 클래스
 */
class QGCMapWidget : public mapcontrol::OPMapWidget
{
    Q_OBJECT
public:
    explicit QGCMapWidget(QWidget *parent = 0);
    ~QGCMapWidget();
//    /** @brief Convert meters to pixels */
//    float metersToPixels(double meters);
//    double headingP1P2(internals::PointLatLng p1, internals::PointLatLng p2);
//    internals::PointLatLng targetLatLon(internals::PointLatLng source, double heading, double dist);

    /** @brief Map centered on current active system */
    /* * 현재 활성화 된 시스템을 중심으로 한지도 */
    bool getFollowUAVEnabled() { return followUAVEnabled; }
    /** @brief The maximum map update rate */
    /* * brief 최대지도 업데이트 속도 */
    float getUpdateRateLimit() { return maxUpdateInterval; }
    /** @brief Get the trail type */
    /* * 트레일 타입 가져 오기 */
    int getTrailType() { return static_cast<int>(trailType); }
    /** @brief Get the trail interval */
    /* * brief 트레일 간격 가져 오기 */
    float getTrailInterval() { return trailInterval; }

signals:
    void homePositionChanged(double latitude, double longitude, double altitude);
    /** @brief Signal for newly created map waypoints */
    /* * 새롭게 생성 된지도 웨이 포인트에 대한 신호 */
    void waypointCreated(Waypoint* wp);
    void waypointChanged(Waypoint* wp);

public slots:
    /** @brief Action triggered with point-camera action is selected from the context menu */
    /* * brief 포인트 카메라 동작으로 트리거 된 동작은 컨텍스트 메뉴에서 선택됩니다. */
    void cameraActionTriggered();
    /** @brief Action triggered when guided action is selected from the context menu */
    /* * @ brief 컨텍스트 메뉴에서 안내 작업을 선택하면 실행되는 작업 */
    void guidedActionTriggered();
    /** @brief Action triggered when guided action is selected from the context menu, allows for altitude selection */
    /* * @ brief 컨텍스트 메뉴에서 안내 액션을 선택했을 때 실행되는 액션으로 고도 선택 가능 */
    void guidedAltActionTriggered();
    /** @brief Add system to map view */
    /* * brief지도보기에 시스템 추가 */
    void addUAS(UASInterface* uas);
    /** @brief Update the global position of a system */
    /* * @brief 시스템의 글로벌 위치 업데이트 */
    void updateGlobalPosition(UASInterface* uas, double lat, double lon, double alt, quint64 usec);
    /** @brief Update the global position of all systems */
    /* * 모든 시스템의 글로벌 위치 업데이트 */
    void updateGlobalPosition();
    /** @brief Update the local position and draw it converted to GPS reference */
    /* * @brief 로컬 위치를 업데이트하고 GPS 참조로 변환 된 그림 그리기 */
    void updateLocalPosition();
    /** @brief Update the local position estimates (individual sensors) and draw it converted to GPS reference */
    /* * 최근 위치 추정치 (개별 센서)를 업데이트하고지도를 GPS 참조로 변환합니다. */
    void updateLocalPositionEstimates();
    /** @brief Update the type, size, etc. of this system */
    /* * brief이 시스템의 유형, 크기 등을 업데이트하십시오. */
    void updateSystemSpecs(int uas);
    /** @brief Change current system in focus / editing */
    /* * brief 현재 시스템을 초점 / 편집 중 변경 */
    void activeUASSet(UASInterface* uas);
    /** @brief Show a dialog to jump to given GPS coordinates */
    /* * brief 주어진 GPS 좌표로 점프하는 대화 상자를 보여줍니다 */
    void showGoToDialog();
    /** @brief Jump to the home position on the map */
    /* * brief지도의 원래 위치로 이동 */
    void goHome();
    /** @brief Jump to the last recorded position of an active UAS */
    /* * brief 활성 UAS의 마지막으로 기록 된 위치로 이동 */
    void lastPosition();
    /** @brief Update this waypoint for this UAS */
    /* * @ brief이 UAS의 웨이 포인트 업데이트 */
    void updateWaypoint(int uas, Waypoint* wp);
    /** @brief Update the whole waypoint */
    /* * @ brief 전체 웨이 포인트 업데이트 */
    void updateWaypointList(int uas);
    /** @brief Redraw lines between waypoints */
    /* * brief 웨이 포인트 사이의 선 그리기 */
    void redrawWaypointLines();
    void redrawWaypointLines(int uas);
    /** @brief Update the home position on the map */
    /* * @brief지도의 홈 위치 업데이트 */
    void updateHomePosition(double latitude, double longitude, double altitude);
    /** @brief Set update rate limit */
    /* * @brief 업데이트 속도 제한 설정 */
    void setUpdateRateLimit(float seconds);
    /** @brief Cache visible region to harddisk */
    /* * brief 가시 영역을 하드 디스크에 캐시 */
    void cacheVisibleRegion();
    /** @brief Set follow mode */
    /* * @ brief 팔로우 모드 설정 */
    void setFollowUAVEnabled(bool enabled) { followUAVEnabled = enabled; }
    /** @brief Set trail to time mode and set time @param seconds The minimum time between trail dots in seconds. If set to a value < 0, trails will be disabled*/
    /* * @ brief @tilil을 시간 모드로 설정하고 시간을 설정 @param seconds 트레일 점 사이의 최소 시간 (초). 값을 0보다 작게 설정하면 산책로가 비활성화됩니다. */
    void setTrailModeTimed(int seconds)
    {
        foreach(mapcontrol::UAVItem* uav, GetUAVS())
        {
            if (seconds >= 0)
            {
                uav->SetTrailTime(seconds);
                uav->SetTrailType(mapcontrol::UAVTrailType::ByTimeElapsed);
            }
            else
            {
                uav->SetTrailType(mapcontrol::UAVTrailType::NoTrail);
            }
        }
    }
    /** @brief Set trail to distance mode and set time @param meters The minimum distance between trail dots in meters. The actual distance depends on the MAV's update rate as well. If set to a value < 0, trails will be disabled*/
   /* * @brief 거리를 거리 모드로 설정하고 시간을 설정합니다. @param meters 트레일 점 사이의 최소 거리를 미터 단위로 나타냅니다. 실제 거리는 MAV의 업데이트 속도에 따라 다릅니다. 값을 0보다 작게 설정하면 산책로가 비활성화됩니다. */
    void setTrailModeDistance(int meters)
    {
        foreach(mapcontrol::UAVItem* uav, GetUAVS())
        {
            if (meters >= 0)
            {
                uav->SetTrailDistance(meters);
                uav->SetTrailType(mapcontrol::UAVTrailType::ByDistance);
            }
            else
            {
                uav->SetTrailType(mapcontrol::UAVTrailType::NoTrail);
            }
        }
    }
    /** @brief Delete all trails */
    /* * @ brief 모든 트레일 삭제 */
    void deleteTrails()
    {
        foreach(mapcontrol::UAVItem* uav, GetUAVS())
        {
            uav->DeleteTrail();
        }
    }

    /** @brief Load the settings for this widget from disk */
    /* * @brief이 위젯에 대한 설정을 디스크 */
    void loadSettings();
    /** @brief Store the settings for this widget to disk */
    /* * @brief이 위젯에 대한 설정을 디스크에 저장 */
    void storeSettings();

protected slots:
    /** @brief Convert a map edit into a QGC waypoint event */
    /* * @ brief지도 편집을 QGC 웨이 포인트 이벤트로 변환 */
    void handleMapWaypointEdit(WayPointItem* waypoint);

private:
    void sendGuidedAction(Waypoint *wp, double alt);
    bool isValidGpsLocation(UASInterface* system) const;

    void shiftOtherSelectedWaypoints(mapcontrol::WayPointItem* selectedWaypoint,
                                     double shiftLong, double shiftLat);

protected:
    /** @brief Update the highlighting of the currently controlled system */
    /* * @brief 현재 제어되는 시스템의 강조 표시 업데이트 */
    void updateSelectedSystem(int uas);
    /** @brief Initialize */
    /* * 초기 설정 */
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);

    UASWaypointManager* currWPManager; ///< The current waypoint manager// / <현재 웨이 포인트 매니저
    bool offlineMode;
    QMap<Waypoint* , mapcontrol::WayPointItem*> waypointsToIcons;
    QMap<mapcontrol::WayPointItem*, Waypoint*> iconsToWaypoints;
    Waypoint* firingWaypointChange;
    QTimer updateTimer;
    float maxUpdateInterval;
    enum editMode {
        EDIT_MODE_NONE,
        EDIT_MODE_WAYPOINTS,
        EDIT_MODE_SWEEP,
        EDIT_MODE_UAVS,
        EDIT_MODE_HOME,
        EDIT_MODE_SAFE_AREA,
        EDIT_MODE_CACHING
    };
    editMode currEditMode;              ///< The current edit mode on the map					// / <지도의 현재 편집 모드
    bool followUAVEnabled;              ///< Does the map follow the UAV?					// / <지도가 UAV를 따르고 있습니까?
    mapcontrol::UAVTrailType::Types trailType; ///< Time or distance based trail dots				// / <시간 또는 거리 기반의 트레일 도트
    float trailInterval;                ///< Time or distance between trail items				// / <트레일 아이템 간의 시간 또는 거리
    int followUAVID;                    ///< Which UAV should be tracked?					// / <어떤 UAV를 추적해야합니까?
    bool mapInitialized;                ///< Map initialized?							// / <맵이 초기화 되었습니까?
    float homeAltitude;                 ///< Home altitude							// / <집의 고도
    QPoint mousePressPos;               ///< Mouse position when the button is released.			// / <버튼을 놓을 때의 마우스 위치.
    double defaultGuidedRelativeAlt;            ///< Default relative altitude for guided mode			// / <가이드 모드의 기본 상대 고도
    int defaultGuidedFrame;             ///< Default guided frame						// / <기본 유도 프레임
    bool defaultGuidedAltFirstTimeSet;   ///< manages the first time set of guided alt				// / <안내 된 alt의 처음 세트를 관리합니다.
    UASInterface *uas;                  ///< Currently selected UAS.						// / <현재 선택한 UAS.
    // Atlantic Ocean near Africa, coordinate origin								// 아프리카 근교의 대서양, 좌표 원점
    double m_lastZoom;
    double m_lastLat;
    double m_lastLon;

};

#endif // QGCMAPWIDGET_H
