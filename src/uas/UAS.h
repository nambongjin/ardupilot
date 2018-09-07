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
 *   @brief Definition of Unmanned Aerial Vehicle object
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/* *
 * @file
 무인 공중 차량의 정의
 *
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#pragma once

#include "UASInterface.h"
#include <MAVLinkProtocol.h>
#include <QVector3D>
#include "QGCMAVLink.h"
#include "QGCHilLink.h"
#include "QGCFlightGearLink.h"
#include "QGCJSBSimLink.h"
//#include "QGCXPlaneLink.h"



/**
 * @brief A generic MAVLINK-connected MAV/UAV
 *
 * This class represents one vehicle. It can be used like the real vehicle, e.g. a call to halt()
 * will automatically send the appropriate messages to the vehicle. The vehicle state will also be
 * automatically updated by the comm architecture, so when writing code to e.g. control the vehicle
 * no knowledge of the communication infrastructure is needed.
 */
/* *
 * MAVLINK 연결 일반 MAV / UAV
 *
*이 클래스는 차량 1 대를 나타냅니다. 실제 차량처럼 사용할 수 있습니다 (예 : halt () 호출)
* 자동으로 적절한 메시지를 차량으로 보냅니다. 차량 상태도
 * 통신 아키텍처에 의해 자동으로 업데이트되므로 차량 제어 코드를 작성할 때
 * 통신 인프라에 대한 지식이 필요하지 않습니다.
 */
class UAS : public UASInterface
{
    Q_OBJECT
public:
    UAS(MAVLinkProtocol* protocol,int id = 0);
    ~UAS();

    static const double lipoFull;  ///< 100% charged voltage// / 100 % 충전 전압
    static const double lipoEmpty; ///< Discharged voltage// / <방전 전압

    /* MANAGEMENT */

    /** @brief The name of the robot */
    /* * @brief 로봇의 이름 */
    QString getUASName(void) const;
    /** @brief Get short state */
    /* * 짧은 시합을 얻으십시오 */
    const QString& getShortState() const;
    /** @brief Get short mode */
    /* * brief 짧은 모드 가져 오기 */
    const QString& getShortMode() const;
    /** @brief Translate from mode id to text */
    /* * brief 모드 ID에서 텍스트로 변환 */
    static QString getShortModeTextFor(int id);
    /** @brief Translate from mode id to audio text */
    /* * @ brief 모드 아이디에서 오디오 텍스트로 변환 */
    static QString getAudioModeTextFor(int id);

    /** @brief Get the human-speakable custom mode string */
    /* * @ brief 인간이 말할 수있는 커스텀 모드 문자열을 얻는다. */
    int getCustomMode();

    /** @brief Get the unique system id */
    /* * @ brief 시스템 고유 ID를 얻는다. */
    int getUASID() const;
    /** @brief Get the airframe */
    /* * brief 기체 도착 */
    int getAirframe() const
    {
        return airframe;
    }
    /** @brief Get the components */
    /* * brief 구성 요소 가져 오기 */
    QMap<int, QString> getComponents();

    /** @brief The time interval the robot is switched on */
    /* * brief 로봇이 켜진 시간 간격 */
    quint64 getUptime() const;
    /** @brief Get the status flag for the communication */
    /* * @ brief 통신에 대한 상태 플래그를 얻습니다. */
    int getCommunicationStatus() const;
    /** @brief Add one measurement and get low-passed voltage */
    /* * brief 하나의 측정을 추가하고 저역 통과 전압을 얻습니다. */
    double filterVoltage(double value) const;
    /** @brief Get the links associated with this robot */
    /* * brief이 로봇과 관련된 링크를 가져옵니다. */
    QList<LinkInterface*>* getLinks();
    QList<int> getLinkIdList();

    Q_PROPERTY(double localX READ getLocalX WRITE setLocalX NOTIFY localXChanged)
    Q_PROPERTY(double localY READ getLocalY WRITE setLocalY NOTIFY localYChanged)
    Q_PROPERTY(double localZ READ getLocalZ WRITE setLocalZ NOTIFY localZChanged)
    Q_PROPERTY(double latitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(double satelliteCount READ getSatelliteCount WRITE setSatelliteCount NOTIFY satelliteCountChanged)
    Q_PROPERTY(bool isLocalPositionKnown READ localPositionKnown)
    Q_PROPERTY(bool isGlobalPositionKnown READ globalPositionKnown)
    Q_PROPERTY(double roll READ getRoll WRITE setRoll NOTIFY rollChanged)
    Q_PROPERTY(double pitch READ getPitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(double yaw READ getYaw WRITE setYaw NOTIFY yawChanged)
    Q_PROPERTY(double distToWaypoint READ getDistToWaypoint WRITE setDistToWaypoint NOTIFY distToWaypointChanged)
    Q_PROPERTY(double airSpeed READ getGroundSpeed WRITE setGroundSpeed NOTIFY airSpeedChanged)
    Q_PROPERTY(double groundSpeed READ getGroundSpeed WRITE setGroundSpeed NOTIFY groundSpeedChanged)
    Q_PROPERTY(double bearingToWaypoint READ getBearingToWaypoint WRITE setBearingToWaypoint NOTIFY bearingToWaypointChanged)
    Q_PROPERTY(double altitudeAMSL READ getAltitudeAMSL WRITE setAltitudeAMSL NOTIFY altitudeAMSLChanged)
    Q_PROPERTY(double altitudeRelative READ getAltitudeRelative WRITE setAltitudeRelative NOTIFY altitudeRelativeChanged)

    void setGroundSpeed(double val)
    {
        groundSpeed = val;
        emit groundSpeedChanged(val,"groundSpeed");
        QString unitName = "Ground Speed";
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"m/s",QVariant(val),getUnixTime());
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"km/h",QVariant(val*3.6),getUnixTime());
        emit valueChanged(this->uasId,statusImperial().arg(unitName),"mi/h",QVariant(val*2.2369362921),getUnixTime());
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"kn",QVariant(val*1.9438444924),getUnixTime());
    }
    double getGroundSpeed() const
    {
        return groundSpeed;
    }

    void setAirSpeed(double val)
    {
        airSpeed = val;
        emit airSpeedChanged(val,"airSpeed");
        QString unitName = "Air Speed";
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"m/s",QVariant(val),getUnixTime());
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"km/h",QVariant(val*3.6),getUnixTime());
        emit valueChanged(this->uasId,statusImperial().arg(unitName),"mi/h",QVariant(val*2.2369362921),getUnixTime());
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"kn",QVariant(val*1.9438444924),getUnixTime());
    }

    double getAirSpeed() const
    {
        return airSpeed;
    }

    void setLocalX(double val)
    {
        localX = val;
        emit localXChanged(val,"localX");
        emit valueChanged(this->uasId,statusName().arg("localX"),"m",QVariant(val),getUnixTime());
    }

    double getLocalX() const
    {
        return localX;
    }

    void setLocalY(double val)
    {
        localY = val;
        emit localYChanged(val,"localY");
        emit valueChanged(this->uasId,statusName().arg("localY"),"m",QVariant(val),getUnixTime());
    }
    double getLocalY() const
    {
        return localY;
    }

    void setLocalZ(double val)
    {
        localZ = val;
        emit localZChanged(val,"localZ");
        emit valueChanged(this->uasId,statusName().arg("localZ"),"m",QVariant(val),getUnixTime());
    }
    double getLocalZ() const
    {
        return localZ;
    }

    void setLatitude(double val)
    {
        latitude = val;
        emit latitudeChanged(val,"latitude");
        emit valueChanged(this->uasId,statusName().arg("Latitude"),"deg",QVariant(val),getUnixTime());
    }

    double getLatitude() const
    {
        return latitude;
    }

    void setLongitude(double val)
    {
        longitude = val;
        emit longitudeChanged(val,"longitude");
        emit valueChanged(this->uasId,statusName().arg("Longitude"),"deg",QVariant(val),getUnixTime());
    }

    double getLongitude() const
    {
        return longitude;
    }


    void setAltitudeAMSL(double val)
    {
        altitudeAMSL = val;
        emit altitudeAMSLChanged(val, "altitudeAMSL");
        QString unitName = "Alt MSL";
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"m",QVariant(val),getUnixTime());
        emit valueChanged(this->uasId,statusImperial().arg(unitName),"ft",QVariant(val*3.280839895),getUnixTime());
    }

    double getAltitudeAMSL() const
    {
        return altitudeAMSL;
    }

    void setAltitudeRelative(double val)
    {
        altitudeRelative = val;
        emit altitudeRelativeChanged(val, "altitudeRelative");
        QString unitName = "Alt REL";
        emit valueChanged(this->uasId,statusMetric().arg(unitName),"m",QVariant(val),getUnixTime());
        emit valueChanged(this->uasId,statusImperial().arg(unitName),"ft",QVariant(val*3.280839895),getUnixTime());
    }

    double getAltitudeRelative() const
    {
        return altitudeRelative;
    }

    // GPS RAW values
    void setGPSLatitude(double val)
    {
        latitude_gps = val;
        emit valueChanged(this->uasId,statusGPS().arg("GPS Lat"),"deg",QVariant(val),getUnixTime());
    }

    double getGPSLatitude() const
    {
        return longitude_gps;
    }

    void setGPSLongitude(double val)
    {
        longitude_gps = val;
        emit valueChanged(this->uasId,statusGPS().arg("GPS Lng"),"deg",QVariant(val),getUnixTime());
    }

    double getGPSLongitude() const
    {
        return longitude_gps;
    }

    void setGPSAltitude(double val)
    {
        altitude_gps = val;
        QString unitName = "GPS Alt MSL";
        emit valueChanged(this->uasId,statusGPS().arg(unitName),"m",QVariant(val),getUnixTime());
        emit valueChanged(this->uasId,statusGPS().arg(unitName),"ft",QVariant(val*3.280839895),getUnixTime());
    }

    double getGPSAltitude() const
    {
        return altitude_gps;
    }

    void setGPSVelocity(double val)
    {
        velocity_gps = val;
        QString unitName = "GPS Velocity";
        emit valueChanged(this->uasId,statusGPS().arg(unitName),"m/s",QVariant(val),getUnixTime());
        emit valueChanged(this->uasId,statusGPS().arg(unitName),"km/h",QVariant(val*3.6),getUnixTime());
        emit valueChanged(this->uasId,statusGPS().arg(unitName),"mi/h",QVariant(val*2.2369362921),getUnixTime());
        emit valueChanged(this->uasId,statusGPS().arg(unitName),"kn",QVariant(val*1.9438444924),getUnixTime());
    }

    double getGPSVelocity() const
    {
        return velocity_gps;
    }

    void setSatelliteCount(double val)
    {
        m_satelliteCount = val;
        emit satelliteCountChanged(val,"satelliteCount");
        emit valueChanged(this->uasId,statusGPS().arg("GPS Sats"),"n",QVariant(val),getUnixTime());
    }

    int getSatelliteCount() const
    {
        return m_satelliteCount;
    }

    void setGpsHdop(double val)
    {
        m_gps_hdop = val;
        emit gpsHdopChanged(val,"GPS HDOP");
        emit valueChanged(this->uasId,statusGPS().arg("GPS HDOP"),"",QVariant(val),getUnixTime());
    }

    double getGpsHdop() const
    {
        return m_gps_hdop;
    }

    void setGpsFix(int val)
    {
        m_gps_fix = val;
        emit gpsFixChanged(val,"GPS Fix");
        emit valueChanged(this->uasId,statusGPS().arg("GPS Fix"),"",QVariant(val),getUnixTime());
    }

    double getGpsFix() const
    {
        return m_gps_fix;
    }

    QString getGpsFixString()
    {
        switch(m_gps_fix){
        case 5:
            return "3D+RTK";
        case 4:
            return "3D+DGPS";
        case 3:
            return "3D";
        case 2:
            return "2D";
        case 1:
            return "NO FIX";
        default:
            return ".";
        }
    }

    virtual bool localPositionKnown() const
    {
        return isLocalPositionKnown;
    }

    virtual bool globalPositionKnown() const
    {
        return isGlobalPositionKnown;
    }

    void setDistToWaypoint(double val)
    {
        distToWaypoint = val;
        emit distToWaypointChanged(val,"distToWaypoint");
        emit valueChanged(this->uasId,statusName().arg("distToWaypoint"),"m",QVariant(val),getUnixTime());
    }

    double getDistToWaypoint() const
    {
        return distToWaypoint;
    }

    void setBearingToWaypoint(double val)
    {
        bearingToWaypoint = val;
        emit bearingToWaypointChanged(val,"bearingToWaypoint");
        emit valueChanged(this->uasId,statusName().arg("bearingToWaypoint"),"deg",QVariant(val),getUnixTime());
    }

    double getBearingToWaypoint() const
    {
        return bearingToWaypoint;
    }


    void setRoll(double val)
    {
        roll = val;
        emit rollChanged(val,"roll");
    }

    double getRoll() const
    {
        return roll;
    }

    void setPitch(double val)
    {
        pitch = val;
        emit pitchChanged(val,"pitch");
    }

    double getPitch() const
    {
        return pitch;
    }

    void setYaw(double val)
    {
        yaw = val;
        emit yawChanged(val,"yaw");
    }

    double getYaw() const
    {
        return yaw;
    }

    bool getSelected() const;
    QVector3D getNedPosGlobalOffset() const
    {
        return nedPosGlobalOffset;
    }

    QVector3D getNedAttGlobalOffset() const
    {
        return nedAttGlobalOffset;
    }

    friend class UASWaypointManager;

protected: //COMMENTS FOR TEST UNIT// 테스트 단위에 대한 의견
    bool m_heartbeatsEnabled;
    /// LINK ID AND STATUS
    // / 링크 ID 및 상태
    int uasId;                    ///< Unique system ID// / <유일한 시스템 ID
    QMap<int, QString> components;///< IDs and names of all detected onboard components// 감지 된 모든 내장 구성 요소의 ID 및 이름
    QList<LinkInterface*>* links; ///< List of links this UAS can be reached by// / <이 UAS에 접근 할 수있는 링크 목록
    QList<int> unknownPackets;    ///< Packet IDs which are unknown and have been received// / <알 수없고 수신 된 패킷 ID
    //MAVLinkProtocol* mavlink;     ///< Reference to the MAVLink instance/// <MAVLink 인스턴스에 대한 참조
    CommStatus commStatus;        ///< Communication status// / <통신 상태
    double receiveDropRate;        ///< Percentage of packets that were dropped on the MAV's receiving link (from GCS and other MAVs)// / <MAV의 수신 링크에서 삭제 된 패킷 비율 (GCS 및 다른 MAV로부터)
    double sendDropRate;           ///< Percentage of packets that were not received from the MAV by the GCS// / <GCS가 MAV로부터 수신하지 못한 패킷 백분율
    quint64 lastHeartbeat;        ///< Time of the last heartbeat message// / <마지막 하트 비트 메시지의 시간
    QTimer* statusTimeout;        ///< Timer for various status timeouts// / <다양한 상태 타임 아웃을위한 타이머

    /// BASIC UAS TYPE, NAME AND STATE// 기본 UAS 유형, 이름 및 상태
    QString name;                 ///< Human-friendly name of the vehicle, e.g. bravo// / <인간 친화적 인 차량 이름, 예 : bravo
    unsigned char type;           ///< UAS type (from type enum)// / <UAS 유형 (유형 enum에서)
    int airframe;                 ///< The airframe type// / <기체 유형
    int autopilot;                ///< Type of the Autopilot: -1: None, 0: Generic, 1: PIXHAWK, 2: SLUGS, 3: Ardupilot (up to 15 types), defined in MAV_AUTOPILOT_TYPE ENUM// / <자동 조종 장치 유형 : -1 : 없음, 0 : 일반, 1 : PIXHAWK, 2 : SLUGS, 3 : Ardupilot (최대 15 개 유형), MAV_AUTOPILOT_TYPE ENUM에 정의 됨
    bool systemIsArmed;           ///< If the system is armed// / <시스템이 활성화 된 경우
    uint8_t base_mode;                 ///< The current mode of the MAV // / <MAV의 현재 모드
    uint32_t custom_mode;         ///< The current mode of the MAV// / <MAV의 현재 모드
    int status;                   ///< The current status of the MAV// / <MAV의 현재 상태
    QString shortModeText;        ///< Short textual mode description// / <짧은 텍스트 모드 설명
    QString shortStateText;       ///< Short textual state description// / <짧은 텍스트 상태 설명
    int systemId;                 ///< Currently connected mavlink system id// / <현재 연결된 mavlink 시스템 ID
    int componentId;              ///< Currently connected mavlink component id// / <현재 연결된 mavlink 구성 요소 ID입니다.
    int getSystemId() { return systemId; }
    int getComponentId() { return componentId; }

    /// OUTPUT
    QList<double> actuatorValues;
    QList<QString> actuatorNames;
    QList<double> motorValues;
    QList<QString> motorNames;
    double thrustSum;           ///< Sum of forward/up thrust of all thrust actuators, in Newtons// 모든 추력 작동기의 정방향 / 상향 추력의 합계, Newtons
    double thrustMax;           ///< Maximum forward/up thrust of this vehicle, in Newtons// / <이 차량의 최대 정방향 / 최대 추력, 뉴턴

    // dongfang: This looks like a candidate for being moved off to a separate class.
    /// BATTERY / ENERGY
    // dongfang : 이것은 별도의 클래스로 옮겨지는 후보자처럼 보입니다.
    // / 배터리 / 에너 지
    BatteryType batteryType;    ///< The battery type// / <배터리 유형
    int cells;                  ///< Number of cells// / <셀 수
    double fullVoltage;          ///< Voltage of the fully charged battery (100%)// / <만 충전 된 배터리의 전압 (100 %)
    double emptyVoltage;         ///< Voltage of the empty battery (0%)// / <빈 배터리의 전압 (0 %)
    double startVoltage;         ///< Voltage at system start // / <시스템 시작시 전압
    double tickVoltage;          ///< Voltage where 0.1 V ticks are told// / <전압이 0.1V 인 경우의 전압
    double lastTickVoltageValue; ///< The last voltage where a tick was announced// / <틱이 발표 된 마지막 전압
    double tickLowpassVoltage;   ///< Lowpass-filtered voltage for the tick announcement// / <진드기 발표를위한 저역 필터링 된 전압
    double warnVoltage;          ///< Voltage where QGC will start to warn about low battery// / <QGC가 배터리 부족에 대해 경고하기 시작할 전압
    double warnLevelPercent;     ///< Warning level, in percent// / <경고 수준 (백분율)
    double currentVoltage;      ///< Voltage currently measured// / <현재 측정 된 전압
    double lpVoltage;            ///< Low-pass filtered voltage// / <저역 필터링 된 전압
    double currentCurrent;      ///< Battery current currently measured// / <현재 배터리 전류 측정
    bool batteryRemainingEstimateEnabled; ///< If the estimate is enabled, QGC will try to estimate the remaining battery life// / <예상치를 사용하면 QGC는 배터리 잔량을 추정하려고합니다
    double chargeLevel;          ///< Charge level of battery, in percent// / <배터리의 충전 수준 (단위 : %)
    int timeRemaining;          ///< Remaining time calculated based on previous and current// / <이전 및 현재를 기반으로 계산 된 남은 시간
    bool lowBattAlarm;          ///< Switch if battery is low // / <배터리가 부족하면 스위치


    /// TIMEKEEPING
    quint64 startTime;            ///< The time the UAS was switched on// / <UAS가 켜졌을 때의 시간
    quint64 onboardTimeOffset;

    /// MANUAL CONTROL
    bool manualControl;             ///< status flag, true if roll/pitch/yaw/thrust are controlled manually// / <상태 플래그, roll / pitch / yaw / thrust가 수동으로 제어되는 경우 true
    bool overrideRC;                ///< status flag, true if RC overrides are in effect// / <상태 플래그, RC 재 지정이 유효한 경우 true입니다.

    /// POSITION
    bool positionLock;          ///< Status if position information is available or not// 위치 정보를 사용할 수 있는지 여부 </ status
    bool isLocalPositionKnown;      ///< If the local position has been received for this MAV// / <이 MAV에 대한 로컬 위치가 수신 된 경우
    bool isGlobalPositionKnown;     ///< If the global position has been received for this MAV// / <이 MAV에 대한 글로벌 위치가 수신 된 경우

    double localX;
    double localY;
    double localZ;

    double latitude;            ///< Global latitude as estimated by position estimator// / <위치 추정기에 의해 추정 된 전역 위도
    double longitude;           ///< Global longitude as estimated by position estimator// / <위치 추정에 의해 추정 된 전체 경도
    double altitudeAMSL;        ///< Global altitude as estimated by position estimator// / <위치 추정기에 의해 추정 된 전체 고도
    double altitudeRelative;    ///< Altitude above home as estimated by position estimator// / <위치 추정에 의해 예상되는 집 위의 고도

    int m_satelliteCount;       ///< Number of satellites visible to raw GPS// 원시 GPS에 보이는 위성의 수
    double m_gps_hdop;          ///< GPS HDOP// / <GPS HDOP
    int m_gps_fix;              ///< GPS FIX type 1, 2 = 2D, 3 = 3D// / <GPS FIX 유형 1, 2 = 2D, 3 = 3D
    bool globalEstimatorActive; ///< Global position estimator present, do not fall back to GPS raw for position// / <글로벌 위치 추정기가 현재 GPS 위치 정보로 돌아 가지 않습니다.
    double latitude_gps;        ///< Global latitude as estimated by raw GPS// 원시 GPS로 추정 한 전역 위도
    double longitude_gps;       ///< Global longitude as estimated by raw GPS// 원시 GPS로 추정 한 전체 경도
    double altitude_gps;        ///< Global altitude as estimated by raw GPS// 원시 GPS로 추정 된 전체 고도
    double velocity_gps;        ///< Global velocity as estimated by raw GPS// / <원시 GPS로 추정 한 전체 속도
    double speedX;              ///< True speed in X axis// / <X 축의 실제 속도
    double speedY;              ///< True speed in Y axis// / <Y 축의 실제 속도
    double speedZ;              ///< True speed in Z axis// / <Z 축의 실제 속도

    QVector3D nedPosGlobalOffset;   ///< Offset between the system's NED position measurements and the swarm / global 0/0/0 origin// / <시스템의 NED 위치 측정치와 swarm / global 0/0/0 원점 사이의 오프셋
    QVector3D nedAttGlobalOffset;   ///< Offset between the system's NED position measurements and the swarm / global 0/0/0 origin// / <시스템의 NED 위치 측정치와 swarm / global 0/0/0 원점 사이의 오프셋

    /// WAYPOINT NAVIGATION
    double distToWaypoint;       ///< Distance to next waypoint// / <다음 웨이 포인트까지의 거리
    double airSpeed;             ///< Airspeed // / <속도
    double groundSpeed;          ///< Groundspeed
    double bearingToWaypoint;    ///< Bearing to next waypoint// / <다음 웨이 포인트로 베어링
    UASWaypointManager waypointManager;

    /// ATTITUDE
    // / 자세
    bool attitudeKnown;             ///< True if attitude was received, false else// / <태도가 수신되면 True, 그렇지 않으면 false
    bool attitudeStamped;           ///< Should arriving data be timestamped with the last attitude? This helps with broken system time clocks on the MAV// / <도착하는 데이터에 마지막 태도의 타임 스탬프가 있어야합니까? MAV의 시스템 시간 시계 고장
    quint64 lastAttitude;           ///< Timestamp of last attitude measurement// / <마지막 자세 측정의 타임 스탬프
    double roll;
    double pitch;
    double yaw;

    // dongfang: This looks like a candidate for being moved off to a separate class.
    /// IMAGING
    // dongfang : 이것은 별도의 클래스로 옮겨지는 후보자처럼 보입니다.
    // / 이미징
    int imageSize;              ///< Image size being transmitted (bytes)// / <전송중인 이미지 크기 (바이트)
    int imagePackets;           ///< Number of data packets being sent for this image// / <이 이미지에 대해 전송 된 데이터 패킷 수
    int imagePacketsArrived;    ///< Number of data packets recieved// / <수신 된 데이터 패킷 수
    int imagePayload;           ///< Payload size per transmitted packet (bytes). Standard is 254, and decreases when image resolution increases.// / <전송 된 패킷 당 페이로드 크기 (바이트). 표준은 254이며 이미지 해상도가 높아지면 줄어 듭니다.
    int imageQuality;           ///< Quality of the transmitted image (percentage)// / <전송 된 이미지의 품질 (백분율)
    int imageType;              ///< Type of the transmitted image (BMP, PNG, JPEG, RAW 8 bit, RAW 32 bit)// / <전송 된 이미지의 종류 (BMP, PNG, JPEG, RAW 8 비트, RAW 32 비트)
    int imageWidth;             ///< Width of the image stream// / <이미지 스트림의 너비
    int imageHeight;            ///< Width of the image stream// / <이미지 스트림의 너비
    QByteArray imageRecBuffer;  ///< Buffer for the incoming bytestream// 들어오는 바이트 스트림 용 버퍼
    QImage image;               ///< Image data of last completely transmitted image// / <마지막으로 완전히 전송 된 이미지의 이미지 데이터
    quint64 imageStart;
    bool blockHomePositionChanges;   ///< Block changes to the home position// / <홈 위치로의 변경 차단
    bool receivedMode;          ///< True if mode was retrieved from current conenction to UAS// / <현재 회의에서 UAS로 모드를 검색 한 경우 참

    /// PARAMETERS
    QMap<int, QMap<QString, QVariant>* > parameters; ///< All parameters// / <모든 매개 변수
    bool paramsOnceRequested;       ///< If the parameter list has been read at least once// / <매개 변수 목록을 적어도 한 번 읽은 경우
    QGCUASParamManager* paramManager; ///< Parameter manager class// / <매개 변수 관리자 클래스

    /// SIMULATION
    QGCHilLink* simulation;         ///< Hardware in the loop simulation link// / 루프 시뮬레이션 링크의 하드웨어

public:
    void setHeartbeatEnabled(bool enabled) { m_heartbeatsEnabled = enabled; }
    /** @brief Set the current battery type */
    /* * / brief 현재 배터리 유형 설정 */
    void setBattery(BatteryType type, int cells);
    /** @brief Estimate how much flight time is remaining */
    /* * brief 비행 시간이 얼마나 남았는지 추정 */
    int calculateTimeRemaining();
    /** @brief Get the current charge level */
    /* * brief 현재 충전 레벨 가져 오기 */
    double getChargeLevel();
    /** @brief Get the human-readable status message for this code */
    /* * @ brief이 코드에 대한 사람이 읽을 수있는 상태 메시지를 얻습니다. */
    void getStatusForCode(int statusCode, QString& uasState, QString& stateDescription);

    /** @brief Get the human-readable custom mode string*/
    /* * @ brief 인간이 읽을 수있는 커스텀 모드 문자열을 얻는다. */
    virtual QString getCustomModeText();

    /** @brief Get the human-speakable custom mode string */
    /* * @ brief 인간이 말할 수있는 커스텀 모드 문자열을 얻는다. */
    virtual QString getCustomModeAudioText();

    /** @brief Ask to play autopilots audio annoucement for mode changes */
    /* * @brief 모드 변경을 위해 자동 파일 오디오 알림을 재생하도록 요청합니다. */
    virtual void playCustomModeChangedAudioMessage();
    /** @brief Ask to play autopilots audio annoucement for armed changes */
    /* * brief 무장 한 변경 사항에 대해 자동 파일 오디오 알림을 재생하도록 요청 */
    virtual void playArmStateChangedAudioMessage(bool armedState);

    /** @brief Check if vehicle is in autonomous mode */
    /* * brief 차량이 자치 모드인지 확인 */
    bool isAuto();
    /** @brief Check if vehicle is armed */
    /* * 차량이 무장 한 지 확인 */
    bool isArmed() const { return systemIsArmed; }
    /** @brief Check if vehicle is in HIL mode */
    /* * 차량이 HIL 모드인지 확인 */
    bool isHilEnabled() const { return hilEnabled; }

    /** @brief Get reference to the waypoint manager **/
    /* * brief 웨이 포인트 매니저에 대한 참조를 얻습니다 * */
    UASWaypointManager* getWaypointManager() {
        return &waypointManager;
    }
    /** @brief Get reference to the param manager **/
    /* * param 매니저에 대한 참조를 얻는다 * */
    QGCUASParamManager* getParamManager() const {
        return paramManager;
    }

    /** @brief Get the HIL simulation */
    /* * Brief HIL 시뮬레이션을 얻으십시오. */
    QGCHilLink* getHILSimulation() const {
        return simulation;
    }
    // TODO Will be removed
    /** @brief Set reference to the param manager **/
    // TODO가 제거됩니다.
    /* * brief param manager에 대한 참조를 설정합니다 * */
    void setParamManager(QGCUASParamManager* manager) {
        paramManager = manager;
    }
    int getSystemType();

    /**
     * @brief Returns true for systems that can reverse. If the system has no control over position, it returns false as
     * @return If the specified vehicle type can
     */
    /* *
     * @brief 되돌릴 수있는 시스템에 대해 true를 리턴합니다. 시스템이 위치를 제어 할 수없는 경우 false를 반환합니다.
     * @return 지정된 차량 유형이
     */
    bool systemCanReverse() const
    {
        switch(type)
        {
        case MAV_TYPE_GENERIC:
        case MAV_TYPE_FIXED_WING:
        case MAV_TYPE_ROCKET:
        case MAV_TYPE_FLAPPING_WING:

        // System types that don't have movement
        // 움직임이없는 시스템 타입
        case MAV_TYPE_ANTENNA_TRACKER:
        case MAV_TYPE_GCS:
        case MAV_TYPE_FREE_BALLOON:
        default:
            return false;
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
        case MAV_TYPE_AIRSHIP:
        case MAV_TYPE_GROUND_ROVER:
        case MAV_TYPE_SURFACE_BOAT:
        case MAV_TYPE_SUBMARINE:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_TRICOPTER:
            return true;
        }
    }

    QString getSystemTypeName()
    {
        switch(type)
        {
        case MAV_TYPE_GENERIC:
            return "GENERIC";
            break;
        case MAV_TYPE_FIXED_WING:
            return "FIXED_WING";
            break;
        case MAV_TYPE_QUADROTOR:
            return "QUADROTOR";
            break;
        case MAV_TYPE_COAXIAL:
            return "COAXIAL";
            break;
        case MAV_TYPE_HELICOPTER:
            return "HELICOPTER";
            break;
        case MAV_TYPE_ANTENNA_TRACKER:
            return "ANTENNA_TRACKER";
            break;
        case MAV_TYPE_GCS:
            return "GCS";
            break;
        case MAV_TYPE_AIRSHIP:
            return "AIRSHIP";
            break;
        case MAV_TYPE_FREE_BALLOON:
            return "FREE_BALLOON";
            break;
        case MAV_TYPE_ROCKET:
            return "ROCKET";
            break;
        case MAV_TYPE_GROUND_ROVER:
            return "GROUND_ROVER";
            break;
        case MAV_TYPE_SURFACE_BOAT:
            return "BOAT";
            break;
        case MAV_TYPE_SUBMARINE:
            return "SUBMARINE";
            break;
        case MAV_TYPE_HEXAROTOR:
            return "HEXAROTOR";
            break;
        case MAV_TYPE_OCTOROTOR:
            return "OCTOROTOR";
            break;
        case MAV_TYPE_TRICOPTER:
            return "TRICOPTER";
            break;
        case MAV_TYPE_FLAPPING_WING:
            return "FLAPPING_WING";
            break;
        default:
            return "";
            break;
        }
    }

    QImage getImage();
    void requestImage();
    int getAutopilotType(){
        return autopilot;
    }
    QString getAutopilotTypeName()
    {
        switch (autopilot)
        {
        case MAV_AUTOPILOT_GENERIC:
            return "GENERIC";
            break;
//        case MAV_AUTOPILOT_PIXHAWK:
//            return "PIXHAWK";
//            break;
        case MAV_AUTOPILOT_SLUGS:
            return "SLUGS";
            break;
        case MAV_AUTOPILOT_ARDUPILOTMEGA:
            return "ARDUPILOTMEGA";
            break;
        case MAV_AUTOPILOT_OPENPILOT:
            return "OPENPILOT";
            break;
        case MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY:
            return "GENERIC_WAYPOINTS_ONLY";
            break;
        case MAV_AUTOPILOT_GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY:
            return "GENERIC_MISSION_NAVIGATION_ONLY";
            break;
        case MAV_AUTOPILOT_GENERIC_MISSION_FULL:
            return "GENERIC_MISSION_FULL";
            break;
        case MAV_AUTOPILOT_INVALID:
            return "NO AP";
            break;
        case MAV_AUTOPILOT_PPZ:
            return "PPZ";
            break;
        case MAV_AUTOPILOT_UDB:
            return "UDB";
            break;
        case MAV_AUTOPILOT_FP:
            return "FP";
            break;
        case MAV_AUTOPILOT_PX4:
            return "PX4";
            break;
        default:
            return "";
            break;
        }
    }
	
  	/** From UASInterface */
    bool isMultirotor();
	bool isRotaryWing();
    bool isFixedWing();
    bool isGroundRover();
    bool isHelicopter();

public slots:

    void protocolStatusMessageRec(const QString& title, const QString& message);
    void valueChangedRec(const int uasId, const QString& name, const QString& unit, const QVariant& value, const quint64 msec);
    void textMessageReceivedRec(int uasid, int componentid, int severity, const QString& text);
    void receiveLossChangedRec(int id,float value);

    /** @brief Set the autopilot type */
    /* * @brief 자동 조종 장치 유형 설정 */
    void setAutopilotType(int apType)
    {
        autopilot = apType;
        emit systemSpecsChanged(uasId);
    }
    /** @brief Set the type of airframe */
    /* * brief 기체의 종류를 설정합니다 */
    void setSystemType(int systemType);
    /** @brief Set the specific airframe type */
    /* * / brief 특정 기체 유형을 설정합니다. */
    void setAirframe(int airframe)
    {
        if((airframe >= QGC_AIRFRAME_GENERIC) && (airframe < QGC_AIRFRAME_END_OF_ENUM))
        {
          this->airframe = airframe;
          emit systemSpecsChanged(uasId);
        }
        
    }
    /** @brief Set a new name **/
    /* * 새 이름 설정 * */
    void setUASName(const QString& name);
    /** @brief Executes a command **/
    /* * @ brief 명령을 실행합니다 * */
    void executeCommand(MAV_CMD command);
    /** @brief Executes a command with 7 params */
    /* * @brief 7 개의 매개 변수로 명령을 실행합니다. */
    void executeCommand(MAV_CMD command, int confirmation, float param1, float param2, float param3, float param4, float param5, float param6, float param7, int component);
    /** @brief Executes a command ack, with success boolean **/
    /* * @ brief 성공과 함께 명령을 실행합니다. 부울 * */
    void executeCommandAck(int num, bool success);
    /** @brief Set the current battery type and voltages */
    /* * / brief 현재 배터리 유형 및 전압 설정 */
    void setBatterySpecs(const QString& specs);
    /** @brief Get the current battery type and specs */
    /* * brief 현재 배터리 유형 및 사양을 확인하십시오. */
    QString getBatterySpecs();

    /** @brief Launches the system **/
    /* * @brief 시스템을 시작합니다 * */
    void launch();
    /** @brief Write this waypoint to the list of waypoints */
    /* * brief 웨이 포인트를 웨이 포인트 목록에 기록합니다. */
    //void setWaypoint(Waypoint* wp); FIXME tbd
    /** @brief Set currently active waypoint */
    /* * @ brief 현재 활성 웨이 포인트 설정 */
    //void setWaypointActive(int id); FIXME tbd
    /** @brief Order the robot to return home **/
    /* * brief 로봇이 집으로 돌아갈 것을 명령합니다 * */

    void home();
    /** @brief Order the robot to land **/
    /* * brief 착륙시킬 로봇을 주문 * */
    void land();
    /** @brief Order the robot to pair its receiver **/
    /* * brief 수신기와 쌍을 이루도록 로봇을 주문하십시오 * */
    void pairRX(int rxType, int rxSubType);

    void halt();
    void go();

    /** @brief Enable / disable HIL */
    /* * brief HIL을 활성화 / 비활성화합니다 */
    void enableHilFlightGear(bool enable, QString options, bool sensorHil, QObject * configuration);
    void enableHilJSBSim(bool enable, QString options);

    /** @brief Send the full HIL state to the MAV */
    /* * Brief 전체 HIL 상태를 MAV에 보냅니다. */
    void sendHilState(quint64 time_us, float roll, float pitch, float yaw, float rollRotationRate,
                        float pitchRotationRate, float yawRotationRate, double lat, double lon, double alt,
                        float vx, float vy, float vz, float ind_airspeed, float true_airspeed, float xacc, float yacc, float zacc);

    void sendHilGroundTruth(quint64 time_us, float roll, float pitch, float yaw, float rollRotationRate,
                        float pitchRotationRate, float yawRotationRate, double lat, double lon, double alt,
                        float vx, float vy, float vz, float ind_airspeed, float true_airspeed, float xacc, float yacc, float zacc);

    /** @brief RAW sensors for sensor HIL */
    /* * brief 센서 용 RAW 센서 HIL */
    void sendHilSensors(quint64 time_us, float xacc, float yacc, float zacc, float rollspeed, float pitchspeed, float yawspeed,
                        float xmag, float ymag, float zmag, float abs_pressure, float diff_pressure, float pressure_alt, float temperature, quint32 fields_changed);

    /**
     * @param time_us
     * @param lat
     * @param lon
     * @param alt
     * @param fix_type
     * @param eph
     * @param epv
     * @param vel
     * @param cog course over ground, in radians, -pi..pi
     * @param satellites
     */
    void sendHilGps(quint64 time_us, double lat, double lon, double alt, int fix_type, float eph, float epv, float vel, float vn, float ve, float vd,  float cog, int satellites);


    /** @brief Places the UAV in Hardware-in-the-Loop simulation status **/
    /* * @brief UAV를 Hardware-in-the-Loop 시뮬레이션 상태에 배치합니다 * */
    void startHil();

    /** @brief Stops the UAV's Hardware-in-the-Loop simulation status **/
    /* * @ brief UAV의 HIL (Hardware-in-the-Loop) 시뮬레이션 상태를 중지합니다 * */
    void stopHil();


    /** @brief Stops the robot system. If it is an MAV, the robot starts the emergency landing procedure **/
    /* * @ brief 로봇 시스템을 정지시킵니다. MAV 인 경우 로봇은 비상 착륙 절차를 시작합니다 * */
    void emergencySTOP();

    /** @brief Kills the robot. All systems are immediately shut down (e.g. the main power line is cut). This might lead to a crash **/
    /* * brief 로봇을 죽입니다. 모든 시스템이 즉시 종료됩니다 (예 : 주전 원선이 끊어짐). 이로 인해 충돌이 발생할 수 있습니다 * */
    bool emergencyKILL();

    /** @brief Shut the system cleanly down. Will shut down any onboard computers **/
    /* * brief 시스템을 깨끗이 종료하십시오. 온보드 컴퓨터를 종료합니다 * */
    void shutdown();

    /** @brief Reboot the system**/
    /* * @brief 시스템을 재부팅하십시오 * */
    void reboot();

    /** @brief Set the target position for the robot to navigate to. */
    /* * @ brief 로봇이 이동할 대상 위치를 설정합니다. */
    void setTargetPosition(float x, float y, float z, float yaw);

    void startLowBattAlarm();
    void stopLowBattAlarm();

    /** @brief Arm system */
    /* * 브리프 암 시스템 */
    virtual void armSystem();
    /** @brief Disable the motors */
    /* * brief 모터 비활성화 */
    virtual void disarmSystem();
    /** @brief Toggle the armed state of the system. */
    /* * brief 시스템의 무장 상태를 토글합니다. */
    void toggleArmedState();
    /**
     * @brief Tell the UAS to switch into a completely-autonomous mode, so disable manual input.
     */
    /* *
     * @brief UAS가 완전 자율 모드로 전환하도록 지시하므로 수동 입력을 비활성화하십시오.
     */
    void goAutonomous();
    /**
     * @brief Tell the UAS to switch to manual control. Stabilized attitude may simultaneously be engaged.
     */
   /* *
     * @brief UAS에 수동 제어로 전환하라고 알려줍니다. 안정화 된 태도가 동시에 작용할 수 있습니다.
     */
    void goManual();
    /**
     * @brief Tell the UAS to switch between manual and autonomous control.
     */
    /* *
     * @brief UAS에게 수동 제어와 자율 제어를 전환하도록 알려줍니다.
     */
    void toggleAutonomy();

    /** @brief Set the values for the manual control of the vehicle */
    /* * @ brief 차량의 수동 제어 값을 설정합니다 */
    void setManualControlCommands(double roll, double pitch, double yaw, double thrust, int xHat, int yHat, int buttons);
    /** @brief Receive a button pressed event from an input device, e.g. joystick */
    /* * brief 입력 장치 (예 : 조이스틱)에서 버튼 눌림 이벤트 수신 */
    void receiveButton(int buttonIndex);

    /** @brief Add a link associated with this robot */
    /* * @brief이 로봇과 관련된 링크 추가 */
    void addLink(LinkInterface* link);
    /** @brief Remove a link associated with this robot */
    /* * brief이 로봇과 관련된 링크 제거 */
    void removeLink(QObject* object);

    /** @brief Receive a message from one of the communication links. */
    /* * brief 통신 링크 중 하나에서 메시지를 수신합니다. */
    void receiveMessage(LinkInterface* link, mavlink_message_t message);

#ifdef QGC_PROTOBUF_ENABLED
    /** @brief Receive a message from one of the communication links. */
    /* * brief 통신 링크 중 하나에서 메시지를 수신합니다. */
    virtual void receiveExtendedMessage(LinkInterface* link, std::tr1::shared_ptr<google::protobuf::Message> message);
#endif

    /** @brief Send a message over this link (to this or to all UAS on this link) */
    /* * Brief이 링크를 통해 메시지를 보냅니다 (이 링크 또는이 링크의 모든 UAS로). */
    void sendMessage(LinkInterface* link, mavlink_message_t message);
    /** @brief Send a message over all links this UAS can be reached with (!= all links) */
    /* * @ brief이 UAS에 연결할 수있는 모든 링크를 통해 메시지 보내기 (! = 모든 링크) */
    void sendMessage(mavlink_message_t message);

    /** @brief Temporary Hack for sending packets to patch Antenna. Send a message over all serial links except for this UAS's */
    /* * brief Antenna를 패치하기 위해 패킷을 보내는 임시 해킹. 이 UAS의 * /를 제외한 모든 직렬 링크를 통해 메시지 보내기 */
    void forwardMessage(mavlink_message_t message);

    /** @brief Set this UAS as the system currently in focus, e.g. in the main display widgets */
    /* * @ brief이 UAS를 현재 포커스가있는 시스템으로 설정합니다 (예 : 기본 디스플레이 위젯 */
    void setSelected();

    /** @brief Set current mode of operation, e.g. auto or manual */
    /* * @ brief 현재 또는 현재 작동 모드를 설정합니다. 예 : 자동 또는 수동 */
    void setMode(int mode);

    /** @brief Set current mode of operation, e.g. auto or manual, always uses the current arming status for safety reason */
    /* * @ brief 현재의 작동 모드를 설정합니다 (예 : 자동 또는 수동). 안전 이유로 항상 현재 작동 상태를 사용합니다. */
    void setMode(uint8_t newBaseMode, uint32_t newCustomMode);

    /** @brief Set current mode of operation, e.g. auto or manual, does not check the arming status, for anything else than arming/disarming operations use setMode instead */
    /* * @brief 자동 또는 수동과 같은 현재 작동 모드를 설정하면 작동 준비 상태를 확인하지 않습니다. 무장 / 작동 해제 조작 이외의 다른 작업은 setMode를 대신 사용합니다. */
    void setModeArm(uint8_t newBaseMode, uint32_t newCustomMode);

    /** @brief Request all parameters */
    /* * 모든 파라미터 요청 */
    void requestParameters();

    /** @brief Request a single parameter by name */
    /* * @brief 단일 매개 변수를 이름으로 요청 */
    void requestParameter(int component, const QString& parameter);
    /** @brief Request a single parameter by index */
    /* * brief 인덱스로 단일 매개 변수 요청 */
    void requestParameter(int component, int id);

    /** @brief Set a system parameter */
    /* * @ brief 시스템 매개 변수 설정 */
    void setParameter(const int compId, const QString& paramId, const QVariant& value);

    /** @brief Write parameters to permanent storage */
    /* * brief 영구 저장 장치에 매개 변수 쓰기 */
    void writeParametersToStorage();
    /** @brief Read parameters from permanent storage */
    /* * brief 영구 저장 장치에서 매개 변수 읽기 */
    void readParametersFromStorage();

    /** @brief Get the names of all parameters */
   /* * 모든 파라미터의 이름을 얻는다. */
    QList<QString> getParameterNames(int component);

    /** @brief Get the ids of all components */
    /* * brief 모든 구성 요소의 ID 가져 오기 */
    QList<int> getComponentIds();

    void enableAllDataTransmission(int rate);
    void enableRawSensorDataTransmission(int rate);
    void enableExtendedSystemStatusTransmission(int rate);
    void enableRCChannelDataTransmission(int rate);
    void enableRawControllerDataTransmission(int rate);
    //void enableRawSensorFusionTransmission(int rate);
    void enablePositionTransmission(int rate);
    void enableExtra1Transmission(int rate);
    void enableExtra2Transmission(int rate);
    void enableExtra3Transmission(int rate);

    /** @brief Update the system state */
    /* * brief 시스템 상태 업데이트 */
    virtual void updateState();

    /** @brief Set world frame origin at current GPS position */
    /* * / brief 현재 GPS 위치에서 월드 프레임 원점을 설정합니다. */
    void setLocalOriginAtCurrentGPSPosition();
    /** @brief Set world frame origin / home position at this GPS position */
    /* * @ brief이 GPS 위치에서 월드 프레임 원점 / 홈 위치를 설정합니다. */
    void setHomePosition(double lat, double lon, double alt);
    /** @brief Set local position setpoint */
    /* * brief 로컬 위치 설정 값 설정 */
    void setLocalPositionSetpoint(float x, float y, float z, float yaw);
    /** @brief Add an offset in body frame to the setpoint */
    /* * @brief 본체 프레임에 오프셋을 설정 점에 추가하십시오. */
    void setLocalPositionOffset(float x, float y, float z, float yaw);

    void startRadioControlCalibration(int param=1);
    void endRadioControlCalibration();
    void startMagnetometerCalibration();
    void startGyroscopeCalibration();
    void startPressureCalibration();
    void startCompassMotCalibration();

    void startDataRecording();
    void stopDataRecording();
    void deleteSettings();
	
    // Log Download
    void logRequestList(uint16_t start, uint16_t end);
    void logRequestData(uint16_t id, uint32_t ofs, uint32_t count);
    void logEraseAll();
    void logRequestEnd();

    void sendHeartbeat();

signals:
    /** @brief The main/battery voltage has changed/was updated */
    /* * brief 메인 / 배터리 전압이 변경 / 업데이트되었습니다 */
    //void voltageChanged(int uasId, double voltage); // Defined in UASInterface already
    /** @brief An actuator value has changed */
    /* * brief 액츄에이터 값이 변경되었습니다. */
    //void actuatorChanged(UASInterface*, int actId, double value); // Defined in UASInterface already
    /** @brief An actuator value has changed */
    /* * brief 액츄에이터 값이 변경되었습니다. */
    void actuatorChanged(UASInterface* uas, QString actuatorName, double min, double max, double value);
    void motorChanged(UASInterface* uas, QString motorName, double min, double max, double value);
    /** @brief The system load (MCU/CPU usage) changed */
    /* * brief 시스템 부하 (MCU / CPU 사용)가 변경되었습니다 */
    void loadChanged(UASInterface* uas, double load);
    /** @brief Propagate a heartbeat received from the system */
    /* * @ brief 시스템에서받은 하트 비트 전파 */
    //void heartbeat(UASInterface* uas); // Defined in UASInterface already// 이미 UASInterface에 정의되어 있습니다.
    void imageStarted(quint64 timestamp);
    /** @brief A new camera image has arrived */
    /* * 새로운 카메라 이미지가 도착했습니다. */
    void imageReady(UASInterface* uas);
    /** @brief HIL controls have changed */
    /* * 간단한 HIL 컨트롤이 변경되었습니다 */
    void hilControlsChanged(uint64_t time, float rollAilerons, float pitchElevator, float yawRudder, float throttle, uint8_t systemMode, uint8_t navMode);
    /** @brief HIL actuator outputs have changed */
    /* * 간단한 HIL 액츄에이터 출력이 변경되었습니다. */
    void hilActuatorsChanged(uint64_t time, float act1, float act2, float act3, float act4, float act5, float act6, float act7, float act8);

    /** @brief Raw servo output values */
    /* * brief 원시 서보 출력 값 */
    void servoRawOutputChanged(uint64_t time, float act1, float act2, float act3, float act4, float act5, float act6, float act7, float act8);


    void localXChanged(double val,QString name);
    void localYChanged(double val,QString name);
    void localZChanged(double val,QString name);
    void longitudeChanged(double val,QString name);
    void latitudeChanged(double val,QString name);
    void altitudeAMSLChanged(double val,QString name);
    void altitudeRelativeChanged(double val,QString name);
    void rollChanged(double val,QString name);
    void pitchChanged(double val,QString name);
    void yawChanged(double val,QString name);
    void satelliteCountChanged(int val,QString name);
    void gpsHdopChanged(double val, QString name);
    void gpsFixChanged(int val, QString name);
    void distToWaypointChanged(double val,QString name);
    void groundSpeedChanged(double val, QString name);
    void airSpeedChanged(double val, QString name);
    void bearingToWaypointChanged(double val,QString name);

protected:
    /** @brief Get the UNIX timestamp in milliseconds, enter microseconds */
    /* * @ brief UNIX 타임 스탬프를 밀리 초 단위로 가져옵니다. 마이크로 초를 입력하십시오. */
    quint64 getUnixTime(quint64 time=0);
    /** @brief Get the UNIX timestamp in milliseconds, enter milliseconds */
    /* * @ brief UNIX 타임 스탬프를 밀리 초 단위로 가져오고 밀리 초 단위로 입력 */
    quint64 getUnixTimeFromMs(quint64 time);
    /** @brief Get the UNIX timestamp in milliseconds, ignore attitudeStamped mode */
    /* * @ brief UNIX 타임 스탬프를 밀리 초 단위로 가져오고, attitudeStamped 모드를 무시합니다. */
    quint64 getUnixReferenceTime(quint64 time);

    /** @brief convert Joystick input ([-1.0, +1.0]) to RC PPM value ([1000, 2000]) for channel */
   /* * 채널에 대한 RC PPM 값 ([1000, 2000])으로 조이스틱 입력 ([-1.0, +1.0]) 변환 */
    uint16_t scaleJoystickToRC(double pct, int channel) const;

    virtual void processParamValueMsg(mavlink_message_t& msg, const QString& paramName,const mavlink_param_value_t& rawValue, mavlink_param_union_t& paramValue);

    int componentID[256];
    bool componentMulti[256];
    bool connectionLost; ///< Flag indicates a timed out connection// / <시간 초과 된 연결을 나타내는 플래그입니다.
    quint64 connectionLossTime; ///< Time the connection was interrupted// / <연결이 중단 된 시간
    quint64 lastVoltageWarning; ///< Time at which the last voltage warning occured// / <마지막 전압 경고가 발생한 시간
    quint64 lastNonNullTime;    ///< The last timestamp from the MAV that was not null// / <null이 아니었던 MAV의 마지막 타임 스탬프
    unsigned int onboardTimeOffsetInvalidCount;     ///< Count when the offboard time offset estimation seemed wrong// / <오프 보드 시간 옵셋 추정이 잘못되었을 때 계산
    bool hilEnabled;            ///< Set to true if HIL mode is enabled from GCS (UAS might be in HIL even if this flag is not set, this defines the GCS HIL setting)// / <GCS에서 HIL 모드를 사용하는 경우 true로 설정합니다.이 플래그가 설정되어 있지 않아도 UAS가 HIL에있을 수 있습니다.이 옵션은 GCS HIL 설정을 정의합니다.
    bool sensorHil;             ///< True if sensor HIL is enabled// / <센서 HIL이 활성화되면 참
    quint64 lastSendTimeGPS;     ///< Last HIL GPS message sent// 마지막 <HIL GPS 메시지가 전송되었습니다.
    quint64 lastSendTimeSensors;

    QMutex requestQueueMutex;
    QList< QPair<int, QString> >  paramRequestQueue;

    QTimer m_parameterSendTimer;


protected slots:
    void requestNextParamFromQueue();

    /** @brief Write settings to disk */
    /* * @ brief 디스크에 설정 쓰기 */
    void writeSettings();
    /** @brief Read settings from disk */
    /* * brief 디스크에서 설정 읽기 */
    void readSettings();

private:
    QString statusName() const;
    QString statusMetric() const;
    QString statusImperial() const;
    QString statusGPS() const;
};
