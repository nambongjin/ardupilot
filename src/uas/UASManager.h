/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009 - 2011 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

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
 *   @brief Definition of class UASManager
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef _UASMANAGER_H_
#define _UASMANAGER_H_

#include "QGCGeo.h"
#include <QThread>
#include <QList>
#include <QMutex>
#include <UASInterface.h>

/**
 * @brief Central manager for all connected aerial vehicles
 *
 * This class keeps a list of all connected / configured UASs. It also stores which
 * UAS is currently select with respect to user input or manual controls.
 **/
/**
 * 연결된 모든 공중 차량의 중앙 관리자
 *
*이 클래스는 연결된 / 구성된 UAS의 목록을 유지합니다. 또한 다음을 저장합니다.
 * UAS는 현재 사용자 입력 또는 수동 제어와 관련하여 선택됩니다.
**/
class UASManager : public QObject
{
    Q_OBJECT

public:
    static UASManager* instance();
    ~UASManager();

    /**
     * @brief Get the currently selected UAS
     *
     * @return NULL pointer if no UAS exists, active UAS else
     **/
    /**
     * @brief 현재 선택된 UAS를 가져옵니다.
     *
     * @return UAS가 존재하지 않는 경우 NULL 포인터, 액티브 UAS else
     **/
    UASInterface* getActiveUAS();
    /**
     * @brief getActiveUASWaypointManager
     * @return uas->getUASWaypointManager(), or if not connected, a singleton instance of a UASWaypointManager.
     */
    /**
     * @brief getActiveUASWaypointManager
     * @return uas-> getUASWaypointManager (), 또는 접속되어 있지 않은 경우는, UASWaypointManager의 싱글 톤 인스턴스입니다.
     */
   
    UASWaypointManager *getActiveUASWaypointManager();

    UASInterface* silentGetActiveUAS();
    /**
     * @brief Get the UAS with this id
     *
     * Although not enforced by this implementation, the IDs are constrained to be
     * in the range of 1 - 127 by the MAVLINK protocol.
     *
     * @param id unique system / aircraft id
     * @return UAS with the given ID, NULL pointer else
     **/
    /**
     * @brief이 ID로 UAS 가져 오기
     *
     *이 구현에 의해 시행되지는 않지만 ID는 다음과 같이 제한됩니다.
     *는 MAVLINK 프로토콜에 의해 1 - 127 범위에 있습니다.
     *
     * @param ID 고유 시스템 / 항공기 ID
     지정된 ID를 가지는 UAS, NULL 포인터 else
     **/
    UASInterface* getUASForId(int id);

    QList<UASInterface*> getUASList();
    /** @brief Get home position latitude */
    /** brief 가정 위치 위도 */
    double getHomeLatitude() const {
        return homeLat;
    }
    /** @brief Get home position longitude */
    /** brief 집 위치 경도 가져 오기 */
    double getHomeLongitude() const {
        return homeLon;
    }
    /** @brief Get home position altitude */
    /** brief 집 위치 고도 가져 오기 */
    double getHomeAltitude() const {
        return homeAlt;
    }

    /** @brief Get the home position coordinate frame */
    /** brief 원점 좌표 프레임 얻기 */
    int getHomeFrame() const
    {
        return homeFrame;
    }

    /** @brief Convert WGS84 coordinates to earth centric frame */
    /** @ brief WGS84 좌표를 지구 중심 프레임으로 변환 */
    Vector3d wgs84ToEcef(const double & latitude, const double & longitude, const double & altitude);
    /** @brief Convert earth centric frame to EAST-NORTH-UP frame (x-y-z directions */
    /** @ brief 지구 중심 프레임을 동쪽 - 북쪽 - 위로 프레임으로 변환합니다 (xyz 방향 */
    Vector3d ecefToEnu(const Vector3d & ecef);
    /** @brief Convert WGS84 lat/lon coordinates to carthesian coordinates with home position as origin */
    /** @brief WGS84 위도 / 경도 좌표를 원점으로 원점 좌표로 변환합니다. */
    void wgs84ToEnu(const double& lat, const double& lon, const double& alt, double* east, double* north, double* up);
    /** @brief Convert x,y,z coordinates to lat / lon / alt coordinates in east-north-up frame */
    /** @ brief 동서 북쪽 프레임의 x, y, z 좌표를 위도 / 경도 / 고도 좌표로 변환합니다. */
    void enuToWgs84(const double& x, const double& y, const double& z, double* lat, double* lon, double* alt);
    /** @brief Convert x,y,z coordinates to lat / lon / alt coordinates in north-east-down frame */
    /** brief north-east-down 프레임의 x, y, z 좌표를 lat / lon / alt 좌표로 변환합니다. */
    void nedToWgs84(const double& x, const double& y, const double& z, double* lat, double* lon, double* alt);

    void getLocalNEDSafetyLimits(double* x1, double* y1, double* z1, double* x2, double* y2, double* z2)
    {
        *x1 = nedSafetyLimitPosition1.x();
        *y1 = nedSafetyLimitPosition1.y();
        *z1 = nedSafetyLimitPosition1.z();

        *x2 = nedSafetyLimitPosition2.x();
        *y2 = nedSafetyLimitPosition2.y();
        *z2 = nedSafetyLimitPosition2.z();
    }

    /** @brief Check if a position is in the local NED safety limits */
    /** brief 위치가 로컬 NED 안전 제한에 있는지 확인 */
    bool isInLocalNEDSafetyLimits(double x, double y, double z)
    {
        if (x < nedSafetyLimitPosition1.x() &&
            y > nedSafetyLimitPosition1.y() &&
            z < nedSafetyLimitPosition1.z() &&
            x > nedSafetyLimitPosition2.x() &&
            y < nedSafetyLimitPosition2.y() &&
            z > nedSafetyLimitPosition2.z())
        {
            // Within limits
            // 한도 내
            return true;
        }
        else
        {
            // Not within limits
            // 제한 내에 없습니다.
            return false;
        }
    }

//    void wgs84ToNed(const double& lat, const double& lon, const double& alt, double* north, double* east, double* down);


public slots:

    /**
     * @brief Add a new UAS to the list
     *
     * This command will only be executed if this UAS does not yet exist.
     * @param UAS unmanned air system to add
     **/
    /**
     * @brief 새 UAS를 목록에 추가하십시오.
     *
     *이 UAS가 아직없는 경우에만이 명령이 실행됩니다.
     * @ param UAS 무인 항공 시스템 추가
     **/
    void addUAS(UASInterface* UAS);

    /** @brief Remove a system from the list */
    /** brief 목록에서 시스템 제거 */
    void removeUAS(UASInterface* uas);
    void removeUAS(QObject* uas);


    /**
      * @brief Set a UAS as currently selected
      *
      * @param UAS Unmanned Air System to set
      **/
    /**
      * @brief 현재 선택된 UAS 설정
      *
      * @param UAS 무인 항공 시스템 설정
      **/
    void setActiveUAS(UASInterface* UAS);


    /**
     * @brief Launch the active UAS
     *
     * The groundstation has always one Unmanned Air System selected.
     * All commands are executed on the UAS in focus. This command starts
     * the launch sequence.
     *
     * @return True if the UAS could be launched, false else
     */
 /* *
     * @brief 활성 UAS 실행
     *
     * 지상 주둔은 항상 무인 항공 시스템을 선택했습니다.
     * 모든 명령은 포커스가있는 UAS에서 실행됩니다. 이 명령이 시작됩니다.
     * 시작 순서.
     *
     * @return UAS가 기동 할 수있는 경우는 true, 그렇지 않은 경우는 false
     */
    bool launchActiveUAS();

    bool haltActiveUAS();

    bool continueActiveUAS();

    /**
     * @brief Land the active UAS
     *
     * The groundstation has always one Unmanned Air System selected.
     * All commands are executed on the UAS in focus. This command starts
     * the land sequence. Depending on the onboard control, this could mean
     * returning to the landing spot as well as descending on the current
     * position.
     *
     * @return True if the UAS could be landed, false else
     */
    /**
     * @brief 활성 UAS 착륙
     *
     * 지상 주둔은 항상 무인 항공 시스템을 선택했습니다.
     * 모든 명령은 포커스가있는 UAS에서 실행됩니다. 이 명령이 시작됩니다.
     * 땅의 순서. 온보드 컨트롤에 따라 이것은 의미 할 수 있습니다.
     * 방문 지점으로 돌아갈뿐만 아니라 현재의 강하
     * 위치.
     *
     * @return UAS가 착륙 할 수있는 경우는 true, 그렇지 않은 경우는 false
     */
    bool returnActiveUAS();


    /**
     * @brief EMERGENCY: Stop active UAS
     *
     * The groundstation has always one Unmanned Air System selected.
     * All commands are executed on the UAS in focus. This command
     * starts an emergency landing. Depending on the onboard control,
     * this usually means descending rapidly on the current position.
     *
     * @warning This command can severely damage the UAS!
     *
     * @return True if the UAS could be landed, false else
     */

    /**
     * @ 비상 사태 비상 사태 : 활동중인 UAS 중단
     *
     * 지상 주둔은 항상 무인 항공 시스템을 선택했습니다.
     * 모든 명령은 포커스가있는 UAS에서 실행됩니다. 이 명령
     * 비상 착륙을 시작합니다. 온보드 컨트롤에 따라,
     * 이것은 일반적으로 현재 위치에서 빠르게 내림차순임을 의미합니다.
     *
     * @warning이 명령은 UAS를 심각하게 손상시킬 수 있습니다!
     *
     * @return UAS가 착륙 할 수있는 경우는 true, 그렇지 않은 경우는 false
     */
    bool stopActiveUAS();

    /**
     * @brief EMERGENCY: Kill active UAS
     *
     * The groundstation has always one Unmanned Air System selected.
     * All commands are executed on the UAS in focus. This command
     * shuts off all onboard motors immediately. This leads to a
     * system crash, but might prevent external damage, e.g. to people.
     * This command is secured by an additional popup message window.
     *
     * @warning THIS COMMAND RESULTS IN THE LOSS OF THE SYSTEM!
     *
     * @return True if the UAS could be landed, false else
     */
    /**
     * @ 비상 사태 비상 사태 : 활동적인 UAS를 죽이십시오
     *
     * 지상 주둔은 항상 무인 항공 시스템을 선택했습니다.
     * 모든 명령은 포커스가있는 UAS에서 실행됩니다. 이 명령
     * 모든 온보드 모터를 즉시 차단합니다. 이것은
     * 시스템 충돌이 발생하지만 외부 피해를 예방할 수 있습니다 (예 : 사람).
     *이 명령은 추가 팝업 메시지 창에 의해 보호됩니다.
     *
     * @이 명령의 결과는 시스템의 손실을 경고합니다!
     *
     * @return UAS가 착륙 할 수있는 경우는 true, 그렇지 않은 경우는 false
     */
    bool killActiveUAS();

    /**
     * @brief Configure the currently active UAS
     *
     * This command will bring up the configuration dialog for the particular UAS.
     */
    /**
     * @ brief 현재 활성 UAS 구성
     *
     *이 명령은 특정 UAS에 대한 구성 대화 상자를 표시합니다.
     */
    void configureActiveUAS();

    /** @brief Shut down the onboard operating system down */
    /** brief 온보드 운영 체제를 종료 */
    bool shutdownActiveUAS();

    /** @brief Set the current home position on all UAVs*/
    /** @ brief 모든 UAV의 현재 홈 위치 설정 */
    bool setHomePosition(double lat, double lon, double alt);

    /** @brief Set the safety limits in local position frame */
    /**  brief 로컬 위치 프레임의 안전 한계 설정 */
    void setLocalNEDSafetyBorders(double x1, double y1, double z1, double x2, double y2, double z2);

    /** @brief Update home position based on the position from one of the UAVs */
    /** brief UAV 중 하나의 위치를 ​​기준으로 홈 위치 업데이트 */
    void uavChangedHomePosition(int uav, double lat, double lon, double alt);

    /** @brief Load settings */
    /** brief 설정로드 */
    void loadSettings();
    /** @brief Store settings */
    /** 간단한 저장 설정 */
    void storeSettings();


protected:
    UASManager();
    QList<UASInterface*> systems;
    UASInterface* activeUAS;
    UASWaypointManager *offlineUASWaypointManager;
    QMutex activeUASMutex;
    double homeLat;
    double homeLon;
    double homeAlt;
    int homeFrame;
    QQuaternion ecef_ref_orientation_;
    Vector3d ecef_ref_point_;
    Vector3d nedSafetyLimitPosition1;
    Vector3d nedSafetyLimitPosition2;

    void initReference(const double & latitude, const double & longitude, const double & altitude);

signals:

    /** A new system was created */
    /* 새로운 시스템이 생성되었습니다 */
    void UASCreated(UASInterface* UAS);
    /** A system was deleted */
    /** 시스템이 삭제되었습니다 */
    void UASDeleted(UASInterface* UAS);
    /** @brief The UAS currently under main operator control changed */
    /** brief 현재 주 운영자 제어하에있는 UAS가 변경되었습니다. */
    void activeUASSet(UASInterface* UAS);
    /** @brief The UAS currently under main operator control changed */
    /** brief 현재 주 운영자 제어하에있는 UAS가 변경되었습니다. */
    void activeUASSet(int systemId);
    /** @brief The UAS currently under main operator control changed */
    /** brief 현재 주 운영자 제어하에있는 UAS가 변경되었습니다. */
    void activeUASSetListIndex(int listIndex);
    /** @brief The UAS currently under main operator control changed */
    /** brief 현재 주 운영자 제어하에있는 UAS가 변경되었습니다. */
    void activeUASStatusChanged(UASInterface* UAS, bool active);
    /** @brief The UAS currently under main operator control changed */
    /** brief 현재 주 운영자 제어하에있는 UAS가 변경되었습니다. */
    void activeUASStatusChanged(int systemId, bool active);
    /** @brief Current home position changed */
    /** brief 현재 홈 위치가 변경됨 */
    void homePositionChanged(double lat, double lon, double alt);

};

#endif // _UASMANAGER_H_
