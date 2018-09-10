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
 *   @brief UDP connection (server) for unmanned vehicles	 무인 차량에 대한 * @brief UDP 연결 (서버)
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef QGCFLIGHTGEARLINK_H
#define QGCFLIGHTGEARLINK_H

#include <QString>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QUdpSocket>
#include <QTimer>
#include <QProcess>
#include <LinkInterface.h>
#include <configuration.h>
#include "UASInterface.h"
#include "QGCHilLink.h"
#include <QGCHilFlightGearConfiguration.h>

class QGCFlightGearLink : public QGCHilLink
{
    Q_OBJECT
    //Q_INTERFACES(QGCFlightGearLinkInterface:LinkInterface)

public:
    QGCFlightGearLink(UASInterface* mav, QString startupArguments, QString remoteHost=QString("127.0.0.1:49000"), QHostAddress host = QHostAddress::Any, quint16 port = 49005);
    ~QGCFlightGearLink();

    bool isConnected();
    qint64 bytesAvailable();
    int getPort() const {
        return port;
    }

    /**
     * @brief The human readable port name	  @brief 사람이 읽을 수있는 포트 이름
     */
    QString getName();

    /**
     * @brief Get remote host and port
     * @return string in format <host>:<port>
     */

/*
     * @brief 원격 호스트 및 포트 가져 오기
     * @ 반환 문자 형식의 문자열 <host> : <port>
*/

    QString getRemoteHost();

    QString getVersion()
    {
        return QString("FlightGear %1").arg(flightGearVersion);
    }

    int getAirFrameIndex()
    {
        return -1;
    }

    bool sensorHilEnabled() {
        return _sensorHilEnabled;
    }

    void sensorHilEnabled(bool sensorHilEnabled) {
        _sensorHilEnabled = sensorHilEnabled;
    }

    void run();

public slots:
//    void setAddress(QString address);
    void setPort(int port);
    /** @brief Add a new host to broadcast messages to 	 @brief 메시지를 브로드 캐스트 할 새 호스트를 추가하여*/
    void setRemoteHost(const QString& host);
    /** @brief Send new control states to the simulation 	 Brief 시뮬레이션에 새로운 제어 상태 보내기*/
    void updateControls(uint64_t time, float rollAilerons, float pitchElevator, float yawRudder, float throttle, uint8_t systemMode, uint8_t navMode);
    void updateActuators(uint64_t time, float act1, float act2, float act3, float act4, float act5, float act6, float act7, float act8);
//    /** @brief Remove a host from broadcasting messages to 	 @brief 브로드 캐스트에서 호스트를 제거하여*/
//    void removeHost(const QString& host);
    //    void readPendingDatagrams();
    void processError(QProcess::ProcessError err);
    /** @brief Set the simulator version as text string 	 @brief 시뮬레이터 버전을 텍스트 문자열로 설정*/
    void setVersion(const QString& version)
    {
        Q_UNUSED(version);
    }

    void selectAirframe(const QString& airframe)
    {
        Q_UNUSED(airframe);
    }

    void enableSensorHIL(bool enable) {
        if (enable != _sensorHilEnabled)
            _sensorHilEnabled = enable;
            emit sensorHilChanged(enable);
    }

    void readBytes();
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

    void writeBytes(const char* data, qint64 length);
    bool connectSimulation();
    bool disconnectSimulation();

    void printTerraSyncOutput();
    void printTerraSyncError();
    void printFgfsOutput();
    void printFgfsError();
    void setStartupArguments(QString startupArguments);
    void setBarometerOffset(float barometerOffsetkPa);

protected:
    QString name;
    QHostAddress host;
    QHostAddress currentHost;
    quint16 currentPort;
    quint16 port;
    int id;
    QUdpSocket* socket;
    bool connectState;

    quint64 bitsSentTotal;
    quint64 bitsSentCurrent;
    quint64 bitsSentMax;
    quint64 bitsReceivedTotal;
    quint64 bitsReceivedCurrent;
    quint64 bitsReceivedMax;
    quint64 connectionStartTime;
    QMutex statisticsMutex;
    QMutex dataMutex;
    QTimer refreshTimer;
    UASInterface* mav;
    QProcess* process;
    QProcess* terraSync;
    unsigned int flightGearVersion;
    QString startupArguments;
    bool _sensorHilEnabled;
    float barometerOffsetkPa;

    void setName(QString name);

signals:


};

#endif // QGCFLIGHTGEARLINK_H
