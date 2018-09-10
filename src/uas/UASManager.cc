/*==================================================================
======================================================================*/

/**
 * @file
 *   @brief Implementation of class UASManager
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include <QList>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QSettings>
#include "UAS.h"
#include "UASInterface.h"
#include "UASManager.h"
#include "QGC.h"

#include <QVector3D>
#include <QMatrix3x3>

#define PI 3.1415926535897932384626433832795
#define MEAN_EARTH_DIAMETER	12756274.0
#define UMR	0.017453292519943295769236907684886

UASManager* UASManager::instance()
{
    static UASManager* _instance = 0;
    if(_instance == 0) {
        _instance = new UASManager();

        // Set the application as parent to ensure that this object
        // will be destroyed when the main application exits
        // 이 객체를 보장하기 위해 응용 프로그램을 부모로 설정합니다.
        // 메인 응용 프로그램이 종료되면 파괴됩니다
        _instance->setParent(qApp);
    }
    return _instance;
}

void UASManager::storeSettings()
{
    QSettings settings;
    settings.beginGroup("QGC_UASMANAGER");
    settings.setValue("HOMELAT", homeLat);
    settings.setValue("HOMELON", homeLon);
    settings.setValue("HOMEALT", homeAlt);
    settings.endGroup();
    settings.sync();
}

void UASManager::loadSettings()
{
    QSettings settings;
    settings.sync();
    settings.beginGroup("QGC_UASMANAGER");
    bool changed =  setHomePosition(settings.value("HOMELAT", homeLat).toDouble(),
                                    settings.value("HOMELON", homeLon).toDouble(),
                                    settings.value("HOMEALT", homeAlt).toDouble());

    // Make sure to fire the change - this will
    // make sure widgets get the signal once
    // 변경 사항을 실행하십시오.
    // 위젯이 한 번 신호를 받도록하십시오.
    if (!changed)
    {
        emit homePositionChanged(homeLat, homeLon, homeAlt);
    }

    settings.endGroup();
}

bool UASManager::setHomePosition(double lat, double lon, double alt)
{
    // Checking for NaN and infitiny
    // and checking for borders
    // NaN 및 infitiny 확인하기
    // 테두리를 확인합니다.
    bool changed = false;
    if (!qIsNaN(lat) && !qIsNaN(lon) && !qIsNaN(alt)
        && !qIsInf(lat) && !qIsInf(lon) && !qIsInf(alt)
        && lat <= 90.0 && lat >= -90.0 && lon <= 180.0 && lon >= -180.0)
        {

        if (homeLat != lat) changed = true;
        if (homeLon != lon) changed = true;
        if (homeAlt != alt) changed = true;

        // Initialize conversion reference in any case
        // 어떤 경우에도 변환 참조 초기화
        initReference(lat, lon, alt);

        if (changed)
        {
            homeLat = lat;
            homeLon = lon;
            homeAlt = alt;

            emit homePositionChanged(homeLat, homeLon, homeAlt);

            // Update all UAVs
            // 모든 UAV를 업데이트합니다.
            foreach (UASInterface* mav, systems)
            {
                mav->setHomePosition(homeLat, homeLon, homeAlt);
            }
        }
    }
    return changed;
}

/**
 * @param x1 Point 1 coordinate in x dimension
 * @param y1 Point 1 coordinate in y dimension
 * @param z1 Point 1 coordinate in z dimension
 *
 * @param x2 Point 2 coordinate in x dimension
 * @param y2 Point 2 coordinate in y dimension
 * @param z2 Point 2 coordinate in z dimension
 */
/**
 * @param x1 x 차원의 점 1 좌표
 * @param y1 y 차원의 점 1 좌표
 * @param z1 z 방향의 점 1 좌표
 *
 * @param x2 x 차원의 점 2 좌표
 * @param y2 y 차원의 점 2 좌표
 * @param z2 z 차원에서의 점 2 좌표
 */
void UASManager::setLocalNEDSafetyBorders(double x1, double y1, double z1, double x2, double y2, double z2)
{
    nedSafetyLimitPosition1.setX(x1);
    nedSafetyLimitPosition1.setY(y1);
    nedSafetyLimitPosition1.setZ(z1);

    nedSafetyLimitPosition2.setX(x2);
    nedSafetyLimitPosition2.setY(y2);
    nedSafetyLimitPosition2.setZ(z2);
}


void UASManager::initReference(const double & latitude, const double & longitude, const double & altitude)
{
    QMatrix3x3 R;
    double s_long, s_lat, c_long, c_lat;
    sincos(latitude * DEG2RAD, &s_lat, &c_lat);
    sincos(longitude * DEG2RAD, &s_long, &c_long);

    R(0, 0) = -s_long;
    R(0, 1) = c_long;
    R(0, 2) = 0;

    R(1, 0) = -s_lat * c_long;
    R(1, 1) = -s_lat * s_long;
    R(1, 2) = c_lat;

    R(2, 0) = c_lat * c_long;
    R(2, 1) = c_lat * s_long;
    R(2, 2) = s_lat;

    ecef_ref_orientation_ = quaternionFromMatrix3x3(R);

    ecef_ref_point_ = wgs84ToEcef(latitude, longitude, altitude);
}

Vector3d UASManager::wgs84ToEcef(const double & latitude, const double & longitude, const double & altitude)
{
    const double a = 6378137.0; // semi-major axis
    const double e_sq = 6.69437999014e-3; // first eccentricity squared
                                          // 첫 번째 이심률 제곱
    double s_long, s_lat, c_long, c_lat;
    sincos(latitude * DEG2RAD, &s_lat, &c_lat);
    sincos(longitude * DEG2RAD, &s_long, &c_long);

    const double N = a / sqrt(1 - e_sq * s_lat * s_lat);

    Vector3d ecef;

    ecef[0] = (N + altitude) * c_lat * c_long;
    ecef[1] = (N + altitude) * c_lat * s_long;
    ecef[2] = (N * (1 - e_sq) + altitude) * s_lat;

    return ecef;
}

Vector3d UASManager::ecefToEnu(const Vector3d & ecef)
{
    Vector3d derefd = ecef - ecef_ref_point_;
    derefd.rotateWithQuaternion(ecef_ref_orientation_);
    return derefd;
}

void UASManager::wgs84ToEnu(const double& lat, const double& lon, const double& alt, double* east, double* north, double* up)
{
    Vector3d ecef = wgs84ToEcef(lat, lon, alt);
    Vector3d enu = ecefToEnu(ecef);
    *east = enu.x();
    *north = enu.y();
    *up = enu.z();
}

void UASManager::enuToWgs84(const double& x, const double& y, const double& z, double* lat, double* lon, double* alt)
{
    *lat=homeLat+y/MEAN_EARTH_DIAMETER*360./PI;
    *lon=homeLon+x/MEAN_EARTH_DIAMETER*360./PI/cos(homeLat*UMR);
    *alt=homeAlt+z;
}

void UASManager::nedToWgs84(const double& x, const double& y, const double& z, double* lat, double* lon, double* alt)
{
    *lat=homeLat+x/MEAN_EARTH_DIAMETER*360./PI;
    *lon=homeLon+y/MEAN_EARTH_DIAMETER*360./PI/cos(homeLat*UMR);
    *alt=homeAlt-z;
}


/**
 * This function will change QGC's home position on a number of conditions only
 */
/**
 *이 기능은 여러 조건에서 QGC의 홈 위치를 변경합니다
 */
void UASManager::uavChangedHomePosition(int uav, double lat, double lon, double alt)
{
    // FIXME: Accept any home position change for now from the active UAS
    // this means that the currently select UAS can change the home location
    // of the whole swarm. This makes sense, but more control might be needed
    // FIXME : 활성 UAS에서 현재 집 위치 변경을 수락합니다.
    // 이것은 현재 선택 UAS가 집 위치를 변경할 수 있다는 것을 의미합니다.
    // 전체 떼의. 이는 의미가 있지만 더 많은 제어가 필요할 수 있습니다.
    if (uav == activeUAS->getUASID())
    {
        if (setHomePosition(lat, lon, alt))
        {
            foreach (UASInterface* mav, systems)
            {
                // Only update the other systems, not the original source
                // 원본 소스가 아닌 다른 시스템 만 업데이트합니다.
                if (mav->getUASID() != uav)
                {
                    mav->setHomePosition(homeLat, homeLon, homeAlt);
                }
            }
        }
    }
}

/**
 * @brief Private singleton constructor
 *
 * This class implements the singleton design pattern and has therefore only a private constructor.
 **/
/**
 * @brief 개인 싱글 톤 생성자
 *
 *이 클래스는 싱글 톤 디자인 패턴을 구현하므로 private 생성자 만 있습니다.
**/
UASManager::UASManager() :
        activeUAS(NULL),
        offlineUASWaypointManager(NULL),
        homeLat(32.835354),
        homeLon(-117.162774),
        homeAlt(25.0),
        homeFrame(MAV_FRAME_GLOBAL)
{
    loadSettings();
    setLocalNEDSafetyBorders(1, -1, 0, -1, 1, -1);
}

UASManager::~UASManager()
{
    storeSettings();
    // Delete all systems
    // 모든 시스템 삭제
    foreach (UASInterface* mav, systems) {
        delete mav;
    }
}

void UASManager::addUAS(UASInterface* uas)
{
    // WARNING: The active uas is set here
    // and then announced below. This is necessary
    // to make sure the getActiveUAS() function
    // returns the UAS once the UASCreated() signal
    // is emitted. The code is thus NOT redundant.
    // 경고 : 활성 uas가 여기에 설정됩니다.
    // 그런 다음 아래에 발표했습니다. 이것은 필요하다.
    // getActiveUAS () 함수를 확인합니다.
    // UASCreated () 신호를 받으면 UAS를 반환합니다.
    // 가 출력됩니다. 따라서 코드는 중복되지 않습니다.
    bool firstUAS = false;
    if (activeUAS == NULL)
    {
        firstUAS = true;
        activeUAS = uas;
    }

    // Only execute if there is no UAS at this index
    // 이 인덱스에 UAS가없는 경우에만 실행
    if (!systems.contains(uas))
    {
        systems.append(uas);
        connect(uas, SIGNAL(destroyed(QObject*)), this, SLOT(removeUAS(QObject*)));
        // Set home position on UAV if set in UI
        // - this is done on a per-UAV basis
        // Set home position in UI if UAV chooses a new one (caution! if multiple UAVs are connected, take care!)
        // UI에 설정된 경우 UAV에 홈 위치 설정
        // -이 작업은 UAV 단위로 수행됩니다.
        // UAV가 새로운 UAV를 선택하면 UI의 홈 위치를 설정합니다 (주의! 여러 UAV가 연결되어 있다면주의하십시오!)
        connect(uas, SIGNAL(homePositionChanged(int,double,double,double)), this, SLOT(uavChangedHomePosition(int,double,double,double)));
        emit UASCreated(uas);
    }

    // If there is no active UAS yet, set the first one as the active UAS
    // 활성 UAS가 아직 없으면 첫 번째 UAS를 활성 UAS로 설정합니다.
    if (firstUAS)
    {
        setActiveUAS(uas);
        if (offlineUASWaypointManager->getWaypointEditableList().size() > 0)
        {
            if (QMessageBox::question(0,"Question","Do you want to append the offline waypoints to the ones currently on the UAV?",QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
            {
                //Need to transfer all waypoints from the offline mode WPManager to the online mode.
                // 모든 중간 지점을 오프라인 모드 WPManager에서 온라인 모드로 전송해야합니다.
                for (int i=0;i<offlineUASWaypointManager->getWaypointEditableList().size();i++)
                {
                    Waypoint *wp = uas->getWaypointManager()->createWaypoint();
                    wp->setLatitude(offlineUASWaypointManager->getWaypointEditableList()[i]->getLatitude());
                    wp->setLongitude(offlineUASWaypointManager->getWaypointEditableList()[i]->getLongitude());
                    wp->setAltitude(offlineUASWaypointManager->getWaypointEditableList()[i]->getAltitude());
                }
            }
            offlineUASWaypointManager->deleteLater();
            offlineUASWaypointManager = 0;
        }
    }
}

void UASManager::removeUAS(QObject* uas)
{
    UASInterface* mav = qobject_cast<UASInterface*>(uas);
    removeUAS(mav);
}

void UASManager::removeUAS(UASInterface* uas)
{
    UASInterface* mav = uas;

    if (mav) {
        int listindex = systems.indexOf(mav);

        if (mav == activeUAS)
        {
            if (systems.count() > 1)
            {
                // We only set a new UAS if more than one is present
                // 하나 이상의 UAS가있는 경우 새 UAS 만 설정합니다.
                if (listindex != 0)
                {
                    // The system to be removed is not at position 1
                    // set position one as new active system
                    // 제거 할 시스템이 위치 1에 있지 않습니다.
                    // 위치 1을 새로운 활성 시스템으로 설정합니다.
                    setActiveUAS(systems.first());
                }
                else
                {
                    // The system to be removed is at position 1,
                    // select the next system
                    // 제거 할 시스템의 위치가 1이고,
                    // 다음 시스템 선택
                    setActiveUAS(systems.at(1));
                }
            }
            else
            {
                // sends a null pointer if no UAS is present any more.
                // It requires listeners of activeUASSet signal to
                // check for NULL, otherwise bad stuff will happen!
                // UAS가 더 이상 존재하지 않으면 // null 포인터를 보냅니다.
                // 활성 UASSet 신호의 리스너가 필요합니다.
                // NULL을 확인하십시오, 그렇지 않으면 나쁜 일이 일어납니다!
                activeUAS = NULL;
                emit activeUASSet(activeUAS);
            }
        }
        systems.removeAt(listindex);
        emit UASDeleted(mav);
    }
}

QList<UASInterface*> UASManager::getUASList()
{
    return systems;
}

UASInterface* UASManager::getActiveUAS()
{
    return activeUAS; ///< Return zero pointer if no UAS has been loaded
}                     /// <UAS가로드되지 않은 경우 제로 포인터를 반환합니다.

UASInterface* UASManager::silentGetActiveUAS()
{
    return activeUAS; ///< Return zero pointer if no UAS has been loaded
}                     /// <UAS가로드되지 않은 경우 제로 포인터를 반환합니다.
UASWaypointManager *UASManager::getActiveUASWaypointManager()
{
    if (activeUAS)
    {
        return activeUAS->getWaypointManager();
    }
    if (!offlineUASWaypointManager)
    {
        offlineUASWaypointManager = new UASWaypointManager(NULL);
    }
    return offlineUASWaypointManager;


}

bool UASManager::launchActiveUAS()
{
    // If the active UAS is set, execute command
    // 활성 UAS가 설정된 경우 명령 실행
    if (getActiveUAS()) activeUAS->launch();
    return (activeUAS); ///< Returns true if the UAS exists, false else
}                       /// <UAS가 있으면 true를 반환하고 그렇지 않으면 false를 반환합니다.

bool UASManager::haltActiveUAS()
{
    // If the active UAS is set, execute command
    // 활성 UAS가 설정된 경우 명령 실행
    if (getActiveUAS()) activeUAS->halt();
    return (activeUAS); ///< Returns true if the UAS exists, false else
}                       /// <UAS가 있으면 true를 반환하고 그렇지 않으면 false를 반환합니다.

bool UASManager::continueActiveUAS()
{
    // If the active UAS is set, execute command
    // 활성 UAS가 설정된 경우 명령 실행
    if (getActiveUAS()) activeUAS->go();
    return (activeUAS); ///< Returns true if the UAS exists, false else
}                       /// <UAS가 있으면 true를 반환하고 그렇지 않으면 false를 반환합니다.

bool UASManager::returnActiveUAS()
{
    // If the active UAS is set, execute command
    // 활성 UAS가 설정된 경우 명령 실행
    if (getActiveUAS()) activeUAS->home();
    return (activeUAS); ///< Returns true if the UAS exists, false else
}                       /// <UAS가 있으면 true를 반환하고 그렇지 않으면 false를 반환합니다.

bool UASManager::stopActiveUAS()
{
    // If the active UAS is set, execute command
    // 활성 UAS가 설정된 경우 명령 실행
    if (getActiveUAS()) activeUAS->emergencySTOP();
    return (activeUAS); ///< Returns true if the UAS exists, false else
}                       /// <UAS가 있으면 true를 반환하고 그렇지 않으면 false를 반환합니다.

bool UASManager::killActiveUAS()
{
    if (getActiveUAS()) activeUAS->emergencyKILL();
    return (activeUAS);
}

bool UASManager::shutdownActiveUAS()
{
    if (getActiveUAS()) activeUAS->shutdown();
    return (activeUAS);
}

void UASManager::configureActiveUAS()
{
    UASInterface* actUAS = getActiveUAS();
    if(actUAS) {
        // Do something
    }   // 무언가를하십시오.
}

UASInterface* UASManager::getUASForId(int id)
{
    UASInterface* system = NULL;

    foreach(UASInterface* sys, systems) {
        if (sys->getUASID() == id) {
            system = sys;
        }
    }

    // Return NULL if not found
    // 찾을 수없는 경우 NULL을 반환합니다.
    return system;
}

void UASManager::setActiveUAS(UASInterface* uas)
{
    if (uas != NULL) {
        activeUASMutex.lock();
        if (activeUAS != NULL) {
            emit activeUASStatusChanged(activeUAS, false);
            emit activeUASStatusChanged(activeUAS->getUASID(), false);
        }
        activeUAS = uas;
        activeUASMutex.unlock();

        activeUAS->setSelected();
        emit activeUASSet(uas);
        emit activeUASSet(uas->getUASID());
        emit activeUASSetListIndex(systems.indexOf(uas));
        emit activeUASStatusChanged(uas, true);
        emit activeUASStatusChanged(uas->getUASID(), true);
    }
}

