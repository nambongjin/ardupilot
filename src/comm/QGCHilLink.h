#ifndef QGCHILLINK_H
#define QGCHILLINK_H

#include <QThread>
#include <QProcess>
#include "inttypes.h"

class QGCHilLink : public QThread
{
    Q_OBJECT
public:
    
    virtual bool isConnected() = 0;
    virtual qint64 bytesAvailable() = 0;
    virtual int getPort() const = 0;

    /**
     * @brief The human readable port name	 사람이 읽을 수있는 포트 이름
     */
    virtual QString getName() = 0;

    /**
     * @brief Get remote host and port	 
     * @return string in format <host>:<port>
     */

/*
     * @brief 원격 호스트 및 포트 가져 오기
     * @ 반환 문자 형식의 문자열 <host> : <port>
*/

    virtual QString getRemoteHost() = 0;

    /**
     * @brief Get the application name and version
     * @return A string containing a unique application name and compatibility version
     */

/*
     * @brief 응용 프로그램 이름 및 버전 얻기
     * @return 고유 한 응용 프로그램 이름과 호환성 버전을 포함하는 문자열
*/

    virtual QString getVersion() = 0;

    /**
     * @brief Get index of currently selected airframe
     * @return -1 if default is selected, index else
     */

/*
     * @brief 현재 선택된 기체의 색인을 얻는다.
     디폴트를 선택하면 (자), 인덱스 else
*/

    virtual int getAirFrameIndex() = 0;

    /**
     * @brief Check if sensor level HIL is enabled
     * @return true if sensor HIL is enabled
     */

/*
     * @brief 센서 레벨 HIL이 활성화되어 있는지 확인하십시오
     * @return 센서의 HIL가 유효한 경우는 true
*/

    virtual bool sensorHilEnabled() = 0;

public slots:
    virtual void setPort(int port) = 0;
    /** @brief Add a new host to broadcast messages to 	 메시지를 브로드 캐스트 할 새 호스트를 추가하여*/
    virtual void setRemoteHost(const QString& host) = 0;
    /** @brief Send new control states to the simulation 	 시뮬레이션에 새로운 제어 상태 보내기*/
    virtual void updateControls(uint64_t time, float rollAilerons, float pitchElevator, float yawRudder, float throttle, uint8_t systemMode, uint8_t navMode) = 0;
    virtual void updateActuators(uint64_t time, float act1, float act2, float act3, float act4, float act5, float act6, float act7, float act8) = 0;
    virtual void processError(QProcess::ProcessError err) = 0;
    /** @brief Set the simulator version as text string 	 시뮬레이터 버전을 텍스트 문자열로 설정*/
    virtual void setVersion(const QString& version) = 0;
    /** @brief Enable sensor-level HIL (instead of state-level HIL) 	센서 수준의 HIL (국가 수준의 HIL 대신) 활성화*/
    virtual void enableSensorHIL(bool enable) = 0;

    virtual void selectAirframe(const QString& airframe) = 0;

    virtual void readBytes() = 0;
    /**
     * @brief Write a number of bytes to the interface.
     *
     * @param data Pointer to the data byte array
     * @param size The size of the bytes array
     **/

/*
     * @brief 인터페이스에 몇 바이트를 씁니다.
     *
     파라미터 : data - 데이터 바이트 배열의 포인터.
     * @param size 바이트 배열의 크기
*/

    virtual void writeBytes(const char* data, qint64 length) = 0;
    virtual bool connectSimulation() = 0;
    virtual bool disconnectSimulation() = 0;

protected:
    virtual void setName(QString name) = 0;

signals:
    /**
     * @brief This signal is emitted instantly when the link is connected	 신호는 링크가 연결될 때 즉시 방출됩니다.
     **/
    void simulationConnected();

    /**
     * @brief This signal is emitted instantly when the link is disconnected	 신호는 링크가 끊어지면 즉시 방출됩니다.
     **/
    void simulationDisconnected();

    /**
     * @brief This signal is emitted instantly when the link status changes	 신호는 링크 상태가 변경 될 때 즉시 방출됩니다.
     **/
    void simulationConnected(bool connected);

    /** @brief State update from simulation 	 시뮬레이션에서의 상태 업데이트*/
    void hilStateChanged(quint64 time_us, float roll, float pitch, float yaw, float rollspeed,
                                          float pitchspeed, float yawspeed, double lat, double lon, double alt,
                                          float vx, float vy, float vz, float ind_airspeed, float true_airspeed, float xacc, float yacc, float zacc);

    void hilGroundTruthChanged(quint64 time_us, float roll, float pitch, float yaw, float rollspeed,
                              float pitchspeed, float yawspeed, double lat, double lon, double alt,
                              float vx, float vy, float vz, float ind_airspeed, float true_airspeed, float xacc, float yacc, float zacc);

    void sensorHilGpsChanged(quint64 time_us, double lat, double lon, double alt, int fix_type, float eph, float epv, float vel, float vn, float ve, float vd, float cog, int satellites);

    void sensorHilRawImuChanged(quint64 time_us, float xacc, float yacc, float zacc,
                                                  float xgyro, float ygyro, float zgyro,
                                                  float xmag, float ymag, float zmag,
                                                  float abs_pressure, float diff_pressure,
                                                  float pressure_alt, float temperature,
                                                  quint32 fields_updated);
    
    /** @brief Remote host and port changed 	  원격 호스트와 포트가 변경되었습니다*/
    void remoteChanged(const QString& hostPort);

    /** @brief Status text message from link 	 링크의 상태 텍스트 메시지*/
    void statusMessage(const QString& message);

    /** @brief Airframe changed */
    void airframeChanged(const QString& airframe);

    /** @brief Selected sim version changed 	 선택한 sim 버전이 변경되었습니다.*/
    void versionChanged(const QString& version);

    /** @brief Selected sim version changed 	 선택한 sim 버전이 변경되었습니다. */
    void versionChanged(const int version);

    /** @brief Sensor leve HIL state changed 	 센서 레벨 HIL 상태가 변경됨 */
    void sensorHilChanged(bool enabled);
};

#endif // QGCHILLINK_H
