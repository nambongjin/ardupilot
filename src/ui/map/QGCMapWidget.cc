#include "QGCMapWidget.h"
#include "logging.h"
#include "QGCMapToolBar.h"
#include "UASInterface.h"
#include "UASManager.h"
#include "MAV2DIcon.h"
#include "Waypoint2DIcon.h"
#include "UASWaypointManager.h"
#include "ArduPilotMegaMAV.h"
#include "WaypointNavigation.h"
#include <QInputDialog>

QGCMapWidget::QGCMapWidget(QWidget *parent) :
    mapcontrol::OPMapWidget(parent),
    firingWaypointChange(NULL),
    maxUpdateInterval(2.1f), // 2 seconds
    followUAVEnabled(false),
    trailType(mapcontrol::UAVTrailType::ByTimeElapsed),
    trailInterval(2.0f),
    followUAVID(0),
    mapInitialized(false),
    homeAltitude(0),
    uas(NULL)
{
    // Set the map cache directory
    // 지도 캐시 디렉토리 설정
    configuration->SetCacheLocation(QGC::appDataDirectory() + "/mapscache/");

    currWPManager = UASManager::instance()->getActiveUASWaypointManager();
    waypointLines.insert(0, new QGraphicsItemGroup(map));
    connect(currWPManager, SIGNAL(waypointEditableListChanged(int)), this, SLOT(updateWaypointList(int)));
    connect(currWPManager, SIGNAL(waypointEditableChanged(int, Waypoint*)), this, SLOT(updateWaypoint(int,Waypoint*)));
    connect(this, SIGNAL(waypointCreated(Waypoint*)), currWPManager, SLOT(addWaypointEditable(Waypoint*)));
    connect(this, SIGNAL(waypointChanged(Waypoint*)), currWPManager, SLOT(notifyOfChangeEditable(Waypoint*)));
    connect(map, SIGNAL(mapChanged()), this, SLOT(redrawWaypointLines()));
    offlineMode = true;
    // Widget is inactive until shown
    // 표시 될 때까지 위젯이 비활성 상태입니다.
    defaultGuidedRelativeAlt = 100.0; // Default set to 100m		// 기본값은 100m로 설정됩니다.
    defaultGuidedAltFirstTimeSet = false;
    loadSettings();

    //handy for debugging:
    //this->SetShowTileGridLines(true);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction *guidedaction = new QAction(this);
    guidedaction->setText("Go To Here (Guided Mode)");
    connect(guidedaction,SIGNAL(triggered()),this,SLOT(guidedActionTriggered()));
    this->addAction(guidedaction);
    guidedaction = new QAction(this);
    guidedaction->setText("Go To Here Alt (Guided Mode)");
    connect(guidedaction,SIGNAL(triggered()),this,SLOT(guidedAltActionTriggered()));
    this->addAction(guidedaction);
    QAction *cameraaction = new QAction(this);
    cameraaction->setText("Point Camera Here");
    connect(cameraaction,SIGNAL(triggered()),this,SLOT(cameraActionTriggered()));
    this->addAction(cameraaction);
}
void QGCMapWidget::guidedActionTriggered()
{
    if (!uas)
    {
        QMessageBox::information(0,"Error","Please connect first");
        return;
    }
    if (!currWPManager)
        return;
    Waypoint wp;
    double tmpAlt;
    // check the frame has not been changed from the last time we executed
    // 우리가 실행 한 마지막 시간에서 프레임이 변경되지 않았는지 확인
    bool aslAglChanged = defaultGuidedFrame != currWPManager->getFrameRecommendation();

    if ( aslAglChanged || !defaultGuidedAltFirstTimeSet)
    {
        defaultGuidedAltFirstTimeSet = true; // so we don't prompt again.		// 그래서 다시 프롬프트를 표시하지 않습니다.
        QString altFrame;
        defaultGuidedFrame = currWPManager->getFrameRecommendation();

        if (defaultGuidedFrame == MAV_FRAME_GLOBAL_RELATIVE_ALT){
            altFrame = "Relative Alt (AGL)";
            tmpAlt = defaultGuidedRelativeAlt;
        } else {
            altFrame = "Abs Alt (ASL)";
            // Waypoint 0 is always home on APM
            // 웨이 포인트 0은 항상 APM에서 집입니다.
            tmpAlt = currWPManager->getWaypoint(0)->getAltitude() + defaultGuidedRelativeAlt;
        }

        bool ok = false;
        tmpAlt = QInputDialog::getDouble(this,altFrame,"Enter " + altFrame + " (in meters) of destination point for guided mode",
                                          tmpAlt,0,30000.0,2,&ok);
        if (!ok)
        {
            //Use has chosen cancel. Do not send the waypoint
            // 사용은 취소를 선택했습니다. 경유지를 보내지 마라.
            return;
        }

        if (defaultGuidedFrame == MAV_FRAME_GLOBAL_RELATIVE_ALT){
            defaultGuidedRelativeAlt = tmpAlt;
        } else {
            defaultGuidedRelativeAlt = tmpAlt - currWPManager->getWaypoint(0)->getAltitude();
        }
    } else if (defaultGuidedFrame == MAV_FRAME_GLOBAL_RELATIVE_ALT){
        tmpAlt = defaultGuidedRelativeAlt;
    } else {
        tmpAlt = currWPManager->getWaypoint(0)->getAltitude() + defaultGuidedRelativeAlt;
    }
    wp.setFrame(static_cast<MAV_FRAME>(defaultGuidedFrame));
    sendGuidedAction(&wp, tmpAlt);
}

void QGCMapWidget::guidedAltActionTriggered()
{
    if (!uas)
    {
        QMessageBox::information(0,"Error","Please connect first");
        return;
    }
    if (!currWPManager)
        return;

    Waypoint wp;
    double tmpAlt;
    if(  defaultGuidedFrame != currWPManager->getFrameRecommendation()){

        defaultGuidedFrame = currWPManager->getFrameRecommendation();
        QLOG_DEBUG() << "Changing from Frame type to:"
                     << (defaultGuidedFrame == MAV_FRAME_GLOBAL_RELATIVE_ALT? "AGL": "ASL");
    }

    wp.setFrame(static_cast<MAV_FRAME>(defaultGuidedFrame));
    QString altFrame;

    if (wp.getFrame() == MAV_FRAME_GLOBAL_RELATIVE_ALT){
        altFrame = "Relative Alt (AGL)";
        tmpAlt = defaultGuidedRelativeAlt;
    } else {
        altFrame = "Abs Alt (ASL)";
        // Waypoint 0 is always home on APM
        // 웨이 포인트 0은 항상 APM에서 집입니다.
        tmpAlt = currWPManager->getWaypoint(0)->getAltitude() + defaultGuidedRelativeAlt;
    }

    bool ok = false;
    tmpAlt = QInputDialog::getDouble(this,altFrame,"Enter " + altFrame + " (in meters) of destination point for guided mode",
                                      tmpAlt,0,30000.0,2,&ok);
    if (!ok)
    {
        //Use has chosen cancel. Do not send the waypoint
        // 사용은 취소를 선택했습니다. 경유지를 보내지 마라.
        return;
    }
    if (defaultGuidedFrame == MAV_FRAME_GLOBAL_RELATIVE_ALT){
        defaultGuidedRelativeAlt = tmpAlt;
    } else {
        defaultGuidedRelativeAlt = tmpAlt - currWPManager->getWaypoint(0)->getAltitude();
    }
    sendGuidedAction(&wp, tmpAlt);
}

void QGCMapWidget::sendGuidedAction(Waypoint* wp, double alt)
{
    // Create new waypoint and send it to the WPManager to send out.
    // 새로운 웨이 포인트를 생성하고 WPManager로 보내 전송합니다.
    internals::PointLatLng pos = map->FromLocalToLatLng(mousePressPos.x(), mousePressPos.y());
    QLOG_DEBUG() << "Guided action requested. Lat:" << pos.Lat() << "Lon:" << pos.Lng()
                 << "Alt:" << alt << "MAV_FRAME:"
                 << (defaultGuidedFrame == MAV_FRAME_GLOBAL_RELATIVE_ALT? "AGL": "ASL");
    wp->setLongitude(pos.Lng());
    wp->setLatitude(pos.Lat());
    wp->setAltitude(alt);
    currWPManager->goToWaypoint(wp);
}

void QGCMapWidget::cameraActionTriggered()
{
    if (!uas)
    {
        QMessageBox::information(0,"Error","Please connect first");
        return;
    }
    ArduPilotMegaMAV *newmav = qobject_cast<ArduPilotMegaMAV*>(this->uas);
    if (newmav)
    {
        newmav->setMountConfigure(4,true,true,true);
        internals::PointLatLng pos = map->FromLocalToLatLng(mousePressPos.x(), mousePressPos.y());
        newmav->setMountControl(pos.Lat(),pos.Lng(),100,true);
    }
}

void QGCMapWidget::mousePressEvent(QMouseEvent *event)
{
    QLOG_DEBUG() << "mousePressEvent pos:" << event->pos() << " posF:" << event->pos();
    mousePressPos = event->pos();
    mapcontrol::OPMapWidget::mousePressEvent(event);
}

void QGCMapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QLOG_DEBUG() << "mouseReleaseEvent pos:" << event->pos() << " posF:" << event->pos();
    mousePressPos = event->pos();
    mapcontrol::OPMapWidget::mouseReleaseEvent(event);
}

QGCMapWidget::~QGCMapWidget()
{
    SetShowHome(false);	// doing this appears to stop the map lib crashing on exit		//이 작업을 수행하면 exit시 map lib가 중단됩니다.
    SetShowUAV(false);	//   "          "
    storeSettings();
}

void QGCMapWidget::showEvent(QShowEvent* event)
{
    // Disable OP's standard UAV, we have more than one
    // OP의 표준 UAV를 비활성화합니다. 우리는 둘 이상을가집니다.
    SetShowUAV(false);
    loadSettings();

    // Pass on to parent widget
    // 부모 위젯에 전달
    OPMapWidget::showEvent(event);



    internals::PointLatLng pos_lat_lon = internals::PointLatLng(m_lastLat, m_lastLon);

    if (!mapInitialized)
    {
        connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(addUAS(UASInterface*)), Qt::UniqueConnection);
        connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(activeUASSet(UASInterface*)), Qt::UniqueConnection);
        connect(UASManager::instance(), SIGNAL(homePositionChanged(double,double,double)), this, SLOT(updateHomePosition(double,double,double)));

        foreach (UASInterface* uas, UASManager::instance()->getUASList())
        {
            addUAS(uas);
        }

        //this->SetUseOpenGL(true);
        SetMouseWheelZoomType(internals::MouseWheelZoomType::MousePositionWithoutCenter);	    // set how the mouse wheel zoom functions// 마우스 휠 줌 기능 설정 방법
        SetFollowMouse(true);				    // we want a contiuous mouse position reading// 우리는 연속적인 마우스 위치 읽기를 원한다.

        SetShowHome(true);					    // display the HOME position on the map// 지도에 HOME 위치를 표시합니다.
        Home->SetSafeArea(0);                         // set radius (meters)// 반경 (미터) 설정
        Home->SetShowSafeArea(false);                                         // show the safe area// 안전 영역 표시
        Home->SetCoord(pos_lat_lon);             // set the HOME position// HOME 위치를 설정합니다.

        setFrameStyle(QFrame::NoFrame);      // no border frame// 테두리 프레임 없음
        setBackgroundBrush(QBrush(Qt::black)); // tile background// 타일 ​​배경

        // Set current home position
        // 현재 홈 위치 설정
        updateHomePosition(UASManager::instance()->getHomeLatitude(), UASManager::instance()->getHomeLongitude(), UASManager::instance()->getHomeAltitude());

        // Set currently selected system
        // 현재 선택된 시스템을 설정합니다.
        activeUASSet(UASManager::instance()->getActiveUAS());

        // Connect map updates to the adapter slots
        // 지도 슬롯에 어댑터 업데이트 연결
        connect(this, SIGNAL(WPValuesChanged(WayPointItem*)), this, SLOT(handleMapWaypointEdit(WayPointItem*)));


        // Start timer
        // 타이머 시작
        connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateGlobalPosition()));
        mapInitialized = true;
        //QTimer::singleShot(800, this, SLOT(loadSettings()));
    }
    SetCurrentPosition(pos_lat_lon);         // set the map position// 지도 위치를 설정합니다.
    setFocus();
    updateTimer.start(maxUpdateInterval*1000);
    // Update all UAV positions
    // 모든 UAV 위치 업데이트
    updateGlobalPosition();
}

void QGCMapWidget::hideEvent(QHideEvent* event)
{
    updateTimer.stop();
    storeSettings();
    OPMapWidget::hideEvent(event);
}

/**
 * @param changePosition Load also the last position from settings and update the map position.
 */
/* *
 * changePosition 설정으로부터 마지막 ​​위치도로드 해, 맵의 위치를 ​​갱신합니다.
 */
void QGCMapWidget::loadSettings()
{
    QSettings settings;
    settings.beginGroup("QGC_MAPWIDGET");
    m_lastLat = settings.value("LAST_LATITUDE", 0.0f).toDouble();
    m_lastLon = settings.value("LAST_LONGITUDE", 0.0f).toDouble();
    m_lastZoom = settings.value("LAST_ZOOM", 1.0f).toDouble();

    SetMapType(static_cast<MapType::Types>(settings.value("MAP_TYPE", MapType::GoogleHybrid).toInt()));

    trailType = static_cast<mapcontrol::UAVTrailType::Types>(settings.value("TRAIL_TYPE", trailType).toInt());
    trailInterval = settings.value("TRAIL_INTERVAL", trailInterval).toFloat();
    settings.endGroup();

    // SET CORRECT MENU CHECKBOXES
    // Set the correct trail interval
    // 올바른 메뉴 검사 점 설정
    // 올바른 트레일 간격을 설정합니다.
    if (trailType == mapcontrol::UAVTrailType::ByDistance)
    {
        // XXX
#ifdef Q_OS_WIN
#pragma message ("WARNING: Settings loading for trail type not implemented")
#else
#warning Settings loading for trail type not implemented
#endif
    }
    else if (trailType == mapcontrol::UAVTrailType::ByTimeElapsed)
    {
        // XXX
    }

    // SET TRAIL TYPE
    foreach (mapcontrol::UAVItem* uav, GetUAVS())
    {
        // Set the correct trail type
        // 올바른 트레일 유형 설정
        uav->SetTrailType(trailType);
        // Set the correct trail interval
        // 올바른 트레일 간격을 설정합니다.
        if (trailType == mapcontrol::UAVTrailType::ByDistance)
        {
            uav->SetTrailDistance(trailInterval);
        }
        else if (trailType == mapcontrol::UAVTrailType::ByTimeElapsed)
        {
            uav->SetTrailTime(trailInterval);
        }
    }

    // SET INITIAL POSITION AND ZOOM
    // 초기 위치 설정 및 줌 설정
    internals::PointLatLng pos_lat_lon = internals::PointLatLng(m_lastLat, m_lastLon);
    SetCurrentPosition(pos_lat_lon);        // set the map position// 지도 위치를 설정합니다.
    SetZoom(m_lastZoom); // set map zoom level// 지도 확대 / 축소 수준 설정
}

void QGCMapWidget::storeSettings()
{
    QSettings settings;
    settings.beginGroup("QGC_MAPWIDGET");
    internals::PointLatLng pos = CurrentPosition();
    if ((pos.Lat() != 0.0f)&&(pos.Lng()!=0.0f)){
        settings.setValue("LAST_LATITUDE", pos.Lat());
        settings.setValue("LAST_LONGITUDE", pos.Lng());
    }
    settings.setValue("LAST_ZOOM", ZoomReal());
    settings.setValue("TRAIL_TYPE", static_cast<int>(trailType));
    settings.setValue("TRAIL_INTERVAL", trailInterval);
    settings.setValue("MAP_TYPE", static_cast<int>(GetMapType()));
    settings.endGroup();
    settings.sync();
}

void QGCMapWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    // If a waypoint manager is available
    // 웨이 포인트 매니저가 사용 가능한 경우
    if (currWPManager)
    {
        // Create new waypoint
        // 새로운 웨이 포인트를 만듭니다.
        internals::PointLatLng pos = map->FromLocalToLatLng(event->pos().x(), event->pos().y());
        currWPManager->blockSignals(true);
        Waypoint* wp = currWPManager->createWaypoint();
        //            wp->setFrame(MAV_FRAME_GLOBAL_RELATIVE_ALT);
        wp->setLatitude(pos.Lat());
        wp->setLongitude(pos.Lng());
        currWPManager->blockSignals(false);
        currWPManager->notifyOfChangeEditable(NULL); // yes: NULL to fire waypointEditableListChanged
    }

    OPMapWidget::mouseDoubleClickEvent(event);
}


/**
 *
 * @param uas the UAS/MAV to monitor/display with the map widget
 */
/* *
 *
 * @param UAS / MAV로지도 위젯을 모니터 / 표시합니다.
 */
void QGCMapWidget::addUAS(UASInterface* uas)
{
    QLOG_DEBUG() << "addUAS" << uas->getUASName();

    connect(uas, SIGNAL(globalPositionChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateGlobalPosition(UASInterface*,double,double,double,quint64)));
    connect(uas, SIGNAL(systemSpecsChanged(int)), this, SLOT(updateSystemSpecs(int)));
}

void QGCMapWidget::activeUASSet(UASInterface* uas)
{
    // Only execute if proper UAS is set
    // 적절한 UAS가 설정된 경우에만 실행
    if (!uas)
    {
        this->uas = 0;
        return;
    }
    if (this->uas == uas) return;

    QLOG_DEBUG() << "activeUASSet" << uas->getUASName();

    // Disconnect old MAV manager
    // 이전 MAV 관리자 연결을 끊습니다.
    if (currWPManager)
    {
        // Disconnect the waypoint manager / data storage from the UI
        // UI에서 웨이 포인트 매니저 / 데이터 스토리지 연결을 끊습니다.
        disconnect(currWPManager, SIGNAL(waypointEditableListChanged(int)), this, SLOT(updateWaypointList(int)));
        disconnect(currWPManager, SIGNAL(waypointEditableChanged(int, Waypoint*)), this, SLOT(updateWaypoint(int,Waypoint*)));
        disconnect(this, SIGNAL(waypointCreated(Waypoint*)), currWPManager, SLOT(addWaypointEditable(Waypoint*)));
        disconnect(this, SIGNAL(waypointChanged(Waypoint*)), currWPManager, SLOT(notifyOfChangeEditable(Waypoint*)));

        QGraphicsItemGroup* group = waypointLine(this->uas ? this->uas->getUASID() : 0);
        if (group)
        {
            // Delete existing waypoint lines
            // 기존 웨이 포인트 라인 삭제
            foreach (QGraphicsItem* item, group->childItems())
            {
                group->removeFromGroup(item);
                delete item;
                item = 0;
            }
        }
    }

    this->uas = uas;
    this->currWPManager = uas->getWaypointManager();

    updateSelectedSystem(uas->getUASID());
    followUAVID = uas->getUASID();
    updateWaypointList(uas->getUASID());

    // Connect the waypoint manager / data storage to the UI
    // UI에 웨이 포인트 매니저 / 데이터 스토리지 연결
    connect(currWPManager, SIGNAL(waypointEditableListChanged(int)), this, SLOT(updateWaypointList(int)));
    connect(currWPManager, SIGNAL(waypointEditableChanged(int, Waypoint*)), this, SLOT(updateWaypoint(int,Waypoint*)));
    connect(this, SIGNAL(waypointCreated(Waypoint*)), currWPManager, SLOT(addWaypointEditable(Waypoint*)));
    connect(this, SIGNAL(waypointChanged(Waypoint*)), currWPManager, SLOT(notifyOfChangeEditable(Waypoint*)));

}

/**
 * Updates the global position of one MAV and append the last movement to the trail
 *
 * @param uas The unmanned air system
 * @param lat Latitude in WGS84 ellipsoid
 * @param lon Longitutde in WGS84 ellipsoid
 * @param alt Altitude over mean sea level
 * @param usec Timestamp of the position message in milliseconds FIXME will move to microseconds
 */
/* *
 * 하나의 MAV의 글로벌 위치를 업데이트하고 마지막 움직임을 트레일에 추가합니다.
 *
 * @param uas 무인 공기 시스템
 * @param 위도 WGS84 타원체 위도
 WGS84 타원체의 * @ 매개 변수 Longitutde
 * @param alt 평균 해발에 대한 고도
 * @param usec 위치 메시지의 밀리 초 단위의 타임 스탬프 FIXME는 마이크로 초로 이동합니다.
 */
void QGCMapWidget::updateGlobalPosition(UASInterface* uas, double lat, double lon, double alt, quint64 usec)
{
    Q_UNUSED(usec);

    // Immediate update
    // 즉각적인 업데이트
    if (maxUpdateInterval == 0)
    {
        // Get reference to graphic UAV item
        // 그래픽 UAV 항목에 대한 참조 가져 오기
        mapcontrol::UAVItem* uav = GetUAV(uas->getUASID());
        // Check if reference is valid, else create a new one
        // 참조가 유효한 지 확인한 다음 참조가 유효한지 확인합니다. 그렇지 않으면 새 참조를 만듭니다.
        if (uav == NULL)
        {
            MAV2DIcon* newUAV = new MAV2DIcon(map, this, uas);
            newUAV->setParentItem(map);
            UAVS.insert(uas->getUASID(), newUAV);
            uav = GetUAV(uas->getUASID());
            // Set the correct trail type
          // 올바른 트레일 유형 설정
            uav->SetTrailType(trailType);
            // Set the correct trail interval
            // 올바른 트레일 간격을 설정합니다.
            if (trailType == mapcontrol::UAVTrailType::ByDistance)
            {
                uav->SetTrailDistance(trailInterval);
            }
            else if (trailType == mapcontrol::UAVTrailType::ByTimeElapsed)
            {
                uav->SetTrailTime(trailInterval);
            }
        }

        // Set new lat/lon position of UAV icon
        // UAV 아이콘의 새로운 위도 / 경도 위치 설정
        internals::PointLatLng pos_lat_lon = internals::PointLatLng(lat, lon);
        uav->SetUAVPos(pos_lat_lon, alt);

        if(this->uas == uas){
            // save the last know postion
            // 마지막으로 알고있는 위치를 저장합니다.
            m_lastLat = uas->getLatitude();
            m_lastLon = uas->getLongitude();
        }

        // Follow status
        // 상태를 따르십시오.
        if (followUAVEnabled && (uas->getUASID() == followUAVID) && isValidGpsLocation(uas)){
            SetCurrentPosition(pos_lat_lon);
        }
        // Convert from radians to degrees and apply
        // 라디안에서 각도로 변환하고 적용합니다.
        uav->SetUAVHeading((uas->getYaw()/M_PI)*180.0f);
    }
}

bool QGCMapWidget::isValidGpsLocation(UASInterface* system) const
{
    if ((system->getLatitude() == 0.0f)
            ||(system->getLongitude() == 0.0f)){
        return false;
    }
    return true;
}

/**
 * Pulls in the positions of all UAVs from the UAS manager
 */
/* *
 * 모든 UAV의 위치를 ​​UAS 관리자로부터 끌어냅니다.
 */
void QGCMapWidget::updateGlobalPosition()
{
    QList<UASInterface*> systems = UASManager::instance()->getUASList();
    foreach (UASInterface* system, systems)
    {
        // Get reference to graphic UAV item
        // 그래픽 UAV 항목에 대한 참조 가져 오기
        mapcontrol::UAVItem* uav = GetUAV(system->getUASID());
        // Check if reference is valid, else create a new one
        // 참조가 유효한 지 확인한 다음 참조가 유효한지 확인합니다. 그렇지 않으면 새 참조를 만듭니다.
        if (uav == NULL)
        {
            MAV2DIcon* newUAV = new MAV2DIcon(map, this, system);
            AddUAV(system->getUASID(), newUAV);
            uav = newUAV;
            uav->SetTrailTime(1);       // [TODO] This should be based on a user setting// [TODO] 이는 사용자 설정을 기반으로해야합니다.
            uav->SetTrailDistance(5);    // [TODO] This should be based on a user setting// [TODO] 이는 사용자 설정을 기반으로해야합니다.
            uav->SetTrailType(mapcontrol::UAVTrailType::ByTimeElapsed);
        }

        // Set new lat/lon position of UAV icon
        // UAV 아이콘의 새로운 위도 / 경도 위치 설정
        internals::PointLatLng pos_lat_lon = internals::PointLatLng(system->getLatitude(), system->getLongitude());
        uav->SetUAVPos(pos_lat_lon, system->getAltitudeAMSL());
        // Follow status
        // 상태를 따르십시오.
        if (followUAVEnabled && (system->getUASID() == followUAVID) && isValidGpsLocation(system)) {
            SetCurrentPosition(pos_lat_lon);
        }
        // Convert from radians to degrees and apply
        // 라디안에서 각도로 변환하고 적용합니다.
        uav->SetUAVHeading((system->getYaw()/M_PI)*180.0f);
    }
}

void QGCMapWidget::updateLocalPosition()
{
    QList<UASInterface*> systems = UASManager::instance()->getUASList();
    foreach (UASInterface* system, systems)
    {
        // Get reference to graphic UAV item
        // 그래픽 UAV 항목에 대한 참조 가져 오기
        mapcontrol::UAVItem* uav = GetUAV(system->getUASID());
        // Check if reference is valid, else create a new one
        // 참조가 유효한 지 확인한 다음 참조가 유효한지 확인합니다. 그렇지 않으면 새 참조를 만듭니다.
        if (uav == NULL)
        {
            MAV2DIcon* newUAV = new MAV2DIcon(map, this, system);
            AddUAV(system->getUASID(), newUAV);
            uav = newUAV;
            uav->SetTrailTime(1);
            uav->SetTrailDistance(5);
            uav->SetTrailType(mapcontrol::UAVTrailType::ByTimeElapsed);
        }

        // Set new lat/lon position of UAV icon
        // UAV 아이콘의 새로운 위도 / 경도 위치 설정
        internals::PointLatLng pos_lat_lon = internals::PointLatLng(system->getLatitude(), system->getLongitude());
        uav->SetUAVPos(pos_lat_lon, system->getAltitudeAMSL());
        // Follow status
        // 상태를 따르십시오.
        if (followUAVEnabled && (system->getUASID() == followUAVID) && isValidGpsLocation(system)) {
            SetCurrentPosition(pos_lat_lon);
        }
        // Convert from radians to degrees and apply
        // 라디안에서 각도로 변환하고 적용합니다.
        uav->SetUAVHeading((system->getYaw()/M_PI)*180.0f);
    }
}

void QGCMapWidget::updateLocalPositionEstimates()
{
    updateLocalPosition();
}


void QGCMapWidget::updateSystemSpecs(int uas)
{
    foreach (mapcontrol::UAVItem* p, UAVS.values())
    {
        MAV2DIcon* icon = dynamic_cast<MAV2DIcon*>(p);
        if (icon && icon->getUASId() == uas)
        {
            // Set new airframe
            // 새로운 기체 설정
            icon->setAirframe(UASManager::instance()->getUASForId(uas)->getAirframe());
            icon->drawIcon();
        }
    }
}

/**
 * Does not update the system type or configuration, only the selected status
 */
/* *
 * 시스템 유형이나 구성을 업데이트하지 않고 선택한 상태 만 업데이트합니다.
 */
void QGCMapWidget::updateSelectedSystem(int uas)
{
    foreach (mapcontrol::UAVItem* p, UAVS.values())
    {
        MAV2DIcon* icon = dynamic_cast<MAV2DIcon*>(p);
        if (icon)
        {
            // Set as selected if ids match
            // ID가 일치 할 경우 선택 항목으로 설정
            icon->setSelectedUAS((icon->getUASId() == uas));
        }
    }
}


// MAP NAVIGATION
// MAP 네비게이션
void QGCMapWidget::showGoToDialog()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Please enter coordinates"),
                                         tr("Coordinates (Lat,Lon):"), QLineEdit::Normal,
                                         QString("%1,%2").arg(CurrentPosition().Lat(), 0, 'g', 6).arg(CurrentPosition().Lng(), 0, 'g', 6), &ok);
    if (ok && !text.isEmpty())
    {
        QStringList split = text.split(",");
        if (split.length() == 2)
        {
            bool convert;
            double latitude = split.first().toDouble(&convert);
            ok &= convert;
            double longitude = split.last().toDouble(&convert);
            ok &= convert;

            if (ok)
            {
                internals::PointLatLng pos_lat_lon = internals::PointLatLng(latitude, longitude);
                SetCurrentPosition(pos_lat_lon);        // set the map position// 지도 위치를 설정합니다.
            }
        }
    }
}


void QGCMapWidget::updateHomePosition(double latitude, double longitude, double altitude)
{
    Home->SetCoord(internals::PointLatLng(latitude, longitude));
    Home->SetAltitude(altitude);
    homeAltitude = altitude;
    SetShowHome(true);                      // display the HOME position on the map// 지도에 HOME 위치를 표시합니다.
}

void QGCMapWidget::goHome()
{
    SetCurrentPosition(Home->Coord());
    SetZoom(18); //zoom to "large RC park" size
}

void QGCMapWidget::lastPosition()
{
    internals::PointLatLng pos_lat_lon = internals::PointLatLng(m_lastLat, m_lastLon);
    SetCurrentPosition(pos_lat_lon);
    SetZoom(m_lastZoom); //zoom to "large RC park" size// "RC 파크"크기로 확대
}

/**
 * Limits the update rate on the specified interval. Set to zero (0) to run at maximum
 * telemetry speed. Recommended rate is 2 s.
 */
/* *
* 지정된 간격으로 업데이트 속도를 제한합니다. 최대로 실행하려면 0으로 설정하십시오.
* 원격 측정 속도. 권장 속도는 2 초입니다.
 */
void QGCMapWidget::setUpdateRateLimit(float seconds)
{
    maxUpdateInterval = seconds;
    updateTimer.start(maxUpdateInterval*1000);
}

void QGCMapWidget::cacheVisibleRegion()
{
    internals::RectLatLng rect = map->SelectedArea();

    if (rect.IsEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Cannot cache tiles for offline use");
        msgBox.setInformativeText("Please select an area first by holding down SHIFT or ALT and selecting the area with the left mouse button.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        RipMap();
        // Set empty area = unselect area
        // 빈 영역 설정 = 비 선택 영역
        map->SetSelectedArea(internals::RectLatLng());
    }
}


// WAYPOINT MAP INTERACTION FUNCTIONS
// WAYPOINT MAP 상호 작용 기능

void QGCMapWidget::shiftOtherSelectedWaypoints(mapcontrol::WayPointItem* selectedWaypoint,
                                               double shiftLong, double shiftLat)
{
    QMap<mapcontrol::WayPointItem*, Waypoint*>::iterator i;
    for (i = iconsToWaypoints.begin(); i != iconsToWaypoints.end(); ++i)
    {
        mapcontrol::WayPointItem* waypoint = i.key();

        if (waypoint->isSelected())
        {
            if (waypoint == selectedWaypoint)
            {
                continue;
            }

            // Update WP values
            // WP 값 업데이트
            Waypoint* wp = i.value();
            internals::PointLatLng pos = waypoint->Coord();

            // Block waypoint signals
            // 웨이 포인트 신호 차단
            wp->blockSignals(true);
            wp->setLatitude(pos.Lat() - shiftLat);
            wp->setLongitude(pos.Lng() - shiftLong);
            wp->blockSignals(false);

            emit waypointChanged(wp);
        }
    }
}

void QGCMapWidget::handleMapWaypointEdit(mapcontrol::WayPointItem* waypoint)
{
    // Block circle updates
    // 서클 업데이트 차단
    Waypoint* wp = iconsToWaypoints.value(waypoint, NULL);

    // Delete UI element if wp doesn't exist
    // wp가 없으면 UI 요소를 삭제합니다.
    if (!wp)
        WPDelete(waypoint);

    // Protect from vicious double update cycle
    // 악성 중복 업데이트주기로부터 보호
    if (firingWaypointChange == wp) return;
    // Not in cycle, block now from entering it
    // 순환하지 않고 입력을 차단합니다.
    firingWaypointChange = wp;

    QLOG_TRACE() << "UPDATING WP FROM MAP" << wp->getId();

    // Update WP values
    // WP 값 업데이트
    internals::PointLatLng pos = waypoint->Coord();

    double shiftLat = wp->getLatitude() - pos.Lat();
    double shiftLong = wp->getLongitude() - pos.Lng();
    // Block waypoint signals
    // 웨이 포인트 신호 차단
    wp->blockSignals(true);
    wp->setLatitude(pos.Lat());
    wp->setLongitude(pos.Lng());
    wp->blockSignals(false);

    firingWaypointChange = NULL;

    emit waypointChanged(wp);

    shiftOtherSelectedWaypoints(waypoint, shiftLong, shiftLat);
}

// WAYPOINT UPDATE FUNCTIONS
// WAYPOINT 업데이트 기능

/**
 * This function is called if a a single waypoint is updated and
 * also if the whole list changes.
 */
/* *
 *이 함수는 단일 웨이 포인트가 업데이트되고
 * 전체 목록이 변경된 경우에도 마찬가지입니다.
 */
void QGCMapWidget::updateWaypoint(int uas, Waypoint* wp)
{
    QLOG_TRACE() << __FILE__ << __LINE__ << "UPDATING WP FUNCTION CALLED";
    // Source of the event was in this widget, do nothing
    // 이벤트 소스가이 위젯에 있었고 아무것도하지 않았습니다.
    if (firingWaypointChange == wp) {
        return;
    }
    // Currently only accept waypoint updates from the UAS in focus
    // this has to be changed to accept read-only updates from other systems as well.
    // 현재 포커스가있는 UAS에서 웨이 포인트 업데이트 만 허용
    // 다른 시스템의 읽기 전용 업데이트도 수락하도록 변경해야합니다.
    UASInterface* uasInstance = UASManager::instance()->getUASForId(uas);
    if (currWPManager)
    {
        // Only accept waypoints in global coordinate frame
        // 전역 좌표계에서 웨이 포인트 만 허용
        if (((wp->getFrame() == MAV_FRAME_GLOBAL) ||
             (wp->getFrame() == MAV_FRAME_GLOBAL_RELATIVE_ALT) ||
             (wp->getFrame() == MAV_FRAME_GLOBAL_TERRAIN_ALT)) && (wp->isNavigationType() || wp->visibleOnMapWidget()))
        {
            // We're good, this is a global waypoint
            // 우리는 훌륭하다. 이것은 세계적인 경유지이다.

            // Get the index of this waypoint
            // 이 웨이 포인트의 인덱스를 가져옵니다.
            int wpindex = currWPManager->getIndexOf(wp);
            // If not found, return (this should never happen, but helps safety)
            // 찾을 수없는 경우 return (절대 일어나지 않지만 안전에 도움이 됨)
            if (wpindex < 0) return;
            // Mark this wp as currently edited
            // 이 wp를 현재 편집 된 것으로 표시합니다.
            firingWaypointChange = wp;

            QLOG_TRACE() << "UPDATING WAYPOINT" << wpindex << "IN 2D MAP";

            // Check if wp exists yet in map
            // wp가지도에 아직 있는지 확인
            if (!waypointsToIcons.contains(wp))
            {
                QLOG_TRACE() << "UPDATING NEW WAYPOINT" << wpindex << "IN 2D MAP";
                // Create icon for new WP
               // 새 WP에 대한 아이콘을 만듭니다.
                QColor wpColor(Qt::red);
                if (uasInstance) wpColor = uasInstance->getColor();
                Waypoint2DIcon* icon = new Waypoint2DIcon(map, this, wp, wpColor, wpindex);
                ConnectWP(icon);
                icon->setParentItem(map);
                // Update maps to allow inverse data association
                // 역 데이터 연결을 허용하도록지도를 업데이트합니다.
                waypointsToIcons.insert(wp, icon);
                iconsToWaypoints.insert(icon, wp);
            }
            else
            {
                QLOG_TRACE() << "UPDATING EXISTING WAYPOINT" << wpindex << "IN 2D MAP";
                // Waypoint exists, block it's signals and update it
             // 웨이 포인트가 존재하고, 신호를 차단하고 업데이트합니다.
                mapcontrol::WayPointItem* icon = waypointsToIcons.value(wp);
                // Make sure we don't die on a null pointer
                // this should never happen, just a precaution
                // 널 포인터로 죽지 않는지 확인한다.
                // 이것은 결코 일어나지 않아야한다.
                if (!icon) return;
                // Block outgoing signals to prevent an infinite signal loop
                // should not happen, just a precaution
                // 무한 신호 루프를 방지하기 위해 나가는 신호 차단
                // 예방책 만 있으면 안됩니다.
                this->blockSignals(true);
                // Update the WP
                // WP 업데이트
                Waypoint2DIcon* wpicon = dynamic_cast<Waypoint2DIcon*>(icon);
                if (wpicon)
                {
                    // Let icon read out values directly from waypoint
                    // 아이콘이 웨이 포인트에서 직접 값을 읽도록합니다.
                    icon->SetNumber(wpindex);
                    wpicon->updateWaypoint();
                }
                else
                {
                    // Use safe standard interfaces for non Waypoint-class based wps
                    // 비 Waypoint 클래스 기반 wps에 안전한 표준 인터페이스 사용
                    icon->SetCoord(internals::PointLatLng(wp->getLatitude(), wp->getLongitude()));
                    icon->SetAltitude(wp->getAltitude());
                    icon->SetHeading(wp->getYaw());
                    icon->SetNumber(wpindex);
                }
                // Re-enable signals again
                // 신호를 다시 사용 설정합니다.
                this->blockSignals(false);
            }

            redrawWaypointLines(uas);

            firingWaypointChange = NULL;
        }
        else
        {
            // Check if the index of this waypoint is larger than the global
            // waypoint list. This implies that the coordinate frame of this
            // waypoint was changed and the list containing only global
            // waypoints was shortened. Thus update the whole list
            // 이 웨이 포인트의 인덱스가 글로벌보다 큰지 확인
            // 웨이 포인트리스트. 이것은 이것의 좌표계가
            // 웨이 포인트가 변경되고 전역 만 포함하는 목록
            // 경유지가 짧아졌습니다. 따라서 전체 목록을 업데이트하십시오.
            if (waypointsToIcons.count() > currWPManager->getGlobalFrameAndNavTypeCount())
            {
                updateWaypointList(uas);
            }
        }
    }
}

void QGCMapWidget::redrawWaypointLines()
{
    redrawWaypointLines(uas ? uas->getUASID() : 0);
}

void QGCMapWidget::redrawWaypointLines(int uas)
{
    QLOG_TRACE() << "REDRAW WAYPOINT LINES FOR UAS" << uas;

    if (!currWPManager)
        return;

    QGraphicsItemGroup* group = waypointLine(uas);
    if (!group)
        return;
    Q_ASSERT(group->parentItem() == map);

    // Delete existing waypoint lines
    // 기존 웨이 포인트 라인 삭제
    foreach (QGraphicsItem* item, group->childItems())
    {
        QLOG_TRACE() << "DELETE EXISTING WAYPOINT LINES" << item;
        delete item;
    }

    QList<Waypoint*> wps = currWPManager->getGlobalFrameAndNavTypeWaypointList(true);
    if (wps.size() > 1)
    {
        QPainterPath path = WaypointNavigation::path(wps, *map);
        if (path.elementCount() > 1)
        {
            QGraphicsPathItem* gpi = new QGraphicsPathItem(map);
            gpi->setPath(path);

            QColor color(Qt::red);
            UASInterface* uasInstance = UASManager::instance()->getUASForId(uas);
            if (uasInstance) color = uasInstance->getColor();
            QPen pen(color);
            pen.setWidth(2);
            gpi->setPen(pen);

            QLOG_TRACE() << "ADDING WAYPOINT LINES" << gpi;
            group->addToGroup(gpi);
        }
    }
}

/**
 * Update the whole list of waypoints. This is e.g. necessary if the list order changed.
 * The UAS manager will emit the appropriate signal whenever updating the list
 * is necessary.
 */
/* *
* 웨이 포인트 전체 목록을 업데이트하십시오. 이것은 목록 순서가 변경된 경우에 필요합니다.
 * UAS 관리자는 목록을 업데이트 할 때마다 적절한 신호를 방출합니다.
 * 필수적이다.
 */
void QGCMapWidget::updateWaypointList(int uas)
{
    QLOG_DEBUG() << "UPDATE WP LIST IN 2D MAP CALLED FOR UAS" << uas;
    // Currently only accept waypoint updates from the UAS in focus
    // this has to be changed to accept read-only updates from other systems as well.
    // 현재 포커스가있는 UAS에서 웨이 포인트 업데이트 만 허용
    // 다른 시스템의 읽기 전용 업데이트도 수락하도록 변경해야합니다.
    if (currWPManager)
    {
        // Delete first all old waypoints
        // this is suboptimal (quadratic, but wps should stay in the sub-100 range anyway)
        // 먼저 모든 이전 경유지를 삭제합니다.
        // 이것은 차선입니다 (이차원이지만 wps는 어쨌든 100 이하 범위에 있어야합니다)
        QList<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList(false);
        foreach (Waypoint* wp, waypointsToIcons.keys())
        {
            if (!wps.contains(wp))
            {
                QLOG_TRACE() << "DELETE EXISTING WP" << wp->getId();
                // Get icon to work on
                // 작업 할 아이콘 가져 오기
                mapcontrol::WayPointItem* icon = waypointsToIcons.value(wp);
                waypointsToIcons.remove(wp);
                iconsToWaypoints.remove(icon);
                WPDelete(icon);
            }
        }

        // Update all existing waypoints
       // 모든 기존 웨이 포인트 업데이트
        foreach (Waypoint* wp, waypointsToIcons.keys())
        {
            QLOG_TRACE() << "UPDATING EXISTING WP" << wp->getId();
            updateWaypoint(uas, wp);
        }

        // Update all potentially new waypoints
        // 잠재적으로 새로운 모든 웨이 포인트를 업데이트합니다.
        foreach (Waypoint* wp, wps)
        {
            // Update / add only if new
            // 새로운 경우에만 업데이트 / 추가
            if (!waypointsToIcons.contains(wp))
            {
                QLOG_TRACE() << "UPDATING NEW WP" << wp->getId();
                updateWaypoint(uas, wp);
            }
        }

//        redrawWaypointLines(uas);
    }
}
