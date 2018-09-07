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
 *   @brief UDP connection (server) for unmanned vehicles
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef UDPLINK_H
#define UDPLINK_H

#include <QString>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QUdpSocket>
#include <LinkInterface.h>
#include <configuration.h>
#include <QQueue>
#include <QByteArray>
#include <QNetworkProxy>

class UDPLink : public LinkInterface
{
    Q_OBJECT
    //Q_INTERFACES(UDPLinkInterface:LinkInterface)

public:
    UDPLink(QHostAddress host = QHostAddress::Any, quint16 port = 14550);

    ~UDPLink();
    void disableTimeouts() { }
    void enableTimeouts() { }

    void requestReset() { }

    bool isConnected() const;
    qint64 bytesAvailable();
    int getPort() const {
        return port;
    }

    /**
     * @brief The human readable port name
     */
    /**
     * @brief 사람이 읽을 수있는 포트 이름
     */
    QString getName() const;
    QString getShortName() const;
    QString getDetail() const;
    int getBaudRate() const;
    int getBaudRateType() const;
    int getFlowType() const;
    int getParityType() const;
    int getDataBitsType() const;
    int getStopBitsType() const;
    QList<QHostAddress> getHosts() const {
        return hosts;
    }
    QList<quint16> getPorts() const {
        return ports;
    }

    // Extensive statistics for scientific purposes
    // 과학적 목적을위한 광범위한 통계
    qint64 getConnectionSpeed() const;
    qint64 getCurrentInDataRate() const;
    qint64 getCurrentOutDataRate() const;

    void run();

    int getId() const;

    LinkType getLinkType() { return UDP_LINK; }

public slots:
    void setAddress(QHostAddress host);
    void setPort(int port);
    /** @brief Add a new host to broadcast messages to */
    /** @brief 메시지를 브로드 캐스트 할 새 호스트를 추가하여 */
    void addHost(const QString& host);
    /** @brief Remove a host from broadcasting messages to */
    /** @ brief 호스트가 브로드 캐스트 메시지에서 제거하여 */
    void removeHost(const QString& host);
    //    void readPendingDatagrams();

    void readBytes();
    /**
     * @brief Write a number of bytes to the interface.
     *
     * @param data Pointer to the data byte array
     * @param size The size of the bytes array
     **/
    /**
     * @brief 인터페이스에 몇 바이트를 씁니다.
     *
     파라미터 : data - 데이터 바이트 배열의 포인터.
     * @param size 바이트 배열의 크기
     **/
    void writeBytes(const char* data, qint64 length);
    bool connect();
    bool disconnect();

private:
    QString name;
    QHostAddress host;
    quint16 port;
    int id;
    QUdpSocket* socket;
    bool connectState;
    bool _shouldRestartConnection;
    QList<QHostAddress> hosts;
    QList<quint16> ports;

    QMutex dataMutex;

    void setName(QString name);

private:
	bool hardwareConnect(void);

    bool                _running;
    QMutex              _mutex;
    QQueue<QByteArray*> _outQueue;

    bool _dequeBytes    ();
    void _sendBytes     (const char* data, qint64 size);


};

#endif // UDPLINK_H
