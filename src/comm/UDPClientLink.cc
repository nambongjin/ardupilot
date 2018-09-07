/*=====================================================================

APM Planner 2.0 Open Source Ground Control Station

(c) 2015 APMPLANNER2 PROJECT <http://www.diydrones.com>

This file is part of the APMPLANNER2 project

    APMPLANNER2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    APMPLANNER2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with APMPLANNER2. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of UDP Client connection for unmanned vehicles
 *
 */
/* *
 * @file
 무인 차량을위한 UDP 클라이언트 연결 정의
 *
 */

#include "logging.h"
#include "UDPClientLink.h"
#include "LinkManager.h"
#include "QGC.h"

#include <QTimer>
#include <QList>
#include <QMutexLocker>
#include <iostream>
#include <QHostInfo>

UDPClientLink::UDPClientLink(QHostAddress host, quint16 port) :
    _targetHost(host),
    _port(port),
    _packetsReceived(false)
{
    // Set unique ID and add link to the list of links
    // 고유 ID를 설정하고 링크 목록에 링크를 추가합니다.
    _linkId = getNextLinkId();
    setName(tr("UDP Client (%1:%2)").arg(_targetHost.toString()).arg(_port));
    QLOG_INFO() << "UDP Created " << _name;

    QObject::connect(&_socket, SIGNAL(readyRead()), this, SLOT(readBytes()));

    QObject::connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(_socketError(QAbstractSocket::SocketError)));
    QObject::connect(&_socket, SIGNAL(disconnected()), this, SLOT(_socketDisconnected()));
}

UDPClientLink::~UDPClientLink()
{
    disconnect();
	this->deleteLater();
}

/**
 * @brief Runs the thread
 *
 **/
/* *
 * @brief 스레드를 실행합니다.
 *
* */
void UDPClientLink::run()
{
	exec();
}

void UDPClientLink::setAddress(QHostAddress host)
{
    bool reconnect = false;
    if(isConnected())
	{
		disconnect();
		reconnect = true;
	}
    _targetHost = host;
    setName(tr("UDP Client (%1:%2)").arg(_targetHost.toString()).arg(_port));
    emit linkChanged(this);

    if(reconnect)
	{
		connect();
	}
}

void UDPClientLink::setPort(int port)
{
    bool reconnect = false;
    if(isConnected())
	{
		disconnect();
		reconnect = true;
	}
    _port = port;
    setName(tr("UDP Client (%1:%2)").arg(_targetHost.toString()).arg(_port));
    emit linkChanged(this);

    if(reconnect)
	{
		connect();
	}
}

void UDPClientLink::writeBytes(const char* data, qint64 size)
{
    if (!_socket.isOpen())
        return;

//    _socket.writeDatagram(data,size,_targetHost,_port);
    _socket.write(data, size);

    // Log the amount and time written out for future data rate calculations.
    // 미래의 데이터 속도 계산을 위해 기록 된 양과 시간을 기록하십시오.
    QMutexLocker dataRateLocker(&dataRateMutex);
    logDataRateToBuffer(outDataWriteAmounts, outDataWriteTimes, &outDataIndex, size, QDateTime::currentMSecsSinceEpoch());
}

/**
 * @brief Read a number of bytes from the interface.
 *
 * @param data Pointer to the data byte array to write the bytes to
 * @param maxLength The maximum number of bytes to write
 **/
/* *
 * @brief 인터페이스에서 여러 바이트를 읽습니다.
 *
 파라미터 : data - 바이트 배열을 기입하는 데이터 바이트 배열의 포인터.
 * @param maxLength 기입 해지는 최대 바이트 수
* */
void UDPClientLink::readBytes()
{
    while (_socket.bytesAvailable())
    {
        _packetsReceived = true;
        QByteArray datagram;
        datagram.resize(_socket.bytesAvailable());

        _socket.read(datagram.data(), datagram.size());

        emit bytesReceived(this, datagram);

        // Log this data reception for this timestep
        // 이 timestep에 대해이 데이터 수신을 기록합니다.
        QMutexLocker dataRateLocker(&dataRateMutex);
        logDataRateToBuffer(inDataWriteAmounts, inDataWriteTimes, &inDataIndex, datagram.length(), QDateTime::currentMSecsSinceEpoch());
    }
}


/**
 * @brief Get the number of bytes to read.
 *
 * @return The number of bytes to read
 **/
/* *
 * @brief 읽을 바이트 수를 가져옵니다.
 *
 * @return 읽을 바이트 수
* */
qint64 UDPClientLink::bytesAvailable()
{
    return _socket.bytesAvailable();
}

/**
 * @brief Disconnect the connection.
 *
 * @return True if connection has been disconnected, false if connection couldn't be disconnected.
 **/
/* *
 * @brief 연결을 끊습니다.
 *
 * @return 연결이 끊어진 경우 true, 연결을 끊을 수없는 경우 false.
* */
bool UDPClientLink::disconnect()
{
    QLOG_INFO() << "UDP disconnect";
    quit();
    wait();

    _socket.close();
    _packetsReceived = true;

    emit disconnected();
    emit connected(false);
    emit disconnected(this);
    emit linkChanged(this);
    return false;
}

/**
 * @brief Connect the connection.
 *
 * @return True if connection has been established, false if connection couldn't be established.
 **/
/* *
 * @brief 연결을 연결하십시오.
 *
 * @return 접속이 확립하면 true, 접속을 확립 할 수없는 경우는 false
* */
bool UDPClientLink::connect()
{
    if (_socket.isOpen())
            disconnect();
    QLOG_INFO() << "UDPClientLink::UDP connect " << _targetHost.toString() << ":" << _port;
    bool connected = _hardwareConnect();
    if (connected){
        start(NormalPriority);
    }
    return connected;
}

bool UDPClientLink::_hardwareConnect()
{

    if (!_targetHost.isNull() && _port!=0) {
        QLOG_INFO() << "Connected UDP Client socket:" << _targetHost.toString();
        _socket.connectToHost(_targetHost,_port);
        _socket.write(QByteArray("HELLO")); // Force Trigger connection.// 강제 트리거 연결.
        emit connected(true);
        emit connected(this);
        emit connected();
        QTimer::singleShot(5000, this, SLOT(_sendTriggerMessage()));
        return true;
    } else {
        QLOG_ERROR() << "connect failed! " << _targetHost.toString() << ":" << _port
                     << " err:" << _socket.error() << ": " << _socket.errorString();
        emit connected(false);
        emit disconnected(this);
        emit disconnected();
    }
    return false;
}

void UDPClientLink::_sendTriggerMessage()
{
    if (!_packetsReceived){
        QLOG_DEBUG() << "Send UDP Client HELLO" << _targetHost.toString();
        _socket.write("HELLO");
        QTimer::singleShot(5000, this, SLOT(_sendTriggerMessage()));
    }
}

void UDPClientLink::_socketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit communicationError(getName(), "UDP Client error on socket: " + _socket.errorString());
}

void UDPClientLink::_socketDisconnected()
{
    qDebug() << _name << ": disconnected";
    _socket.close();

    emit disconnected();
    emit connected(false);
    emit disconnected(this);
    emit linkChanged(this);
}
/**
 * @brief Check if connection is active.
 *
 * @return True if link is connected, false otherwise.
 **/
/* *
 * @brief 연결이 활성화되어 있는지 확인하십시오.
 *
 * @return 링크가 연결되어 있으면 true이고, 그렇지 않으면 false입니다.
* */
bool UDPClientLink::isConnected() const
{
    return _socket.isOpen();
}

int UDPClientLink::getId() const
{
    return _linkId;
}

QHostAddress UDPClientLink::getHostAddress() const
{
    return _targetHost;
}

quint16 UDPClientLink::getPort() const
{
    return _port;
}

QString UDPClientLink::getName() const
{
    return _name;
}

QString UDPClientLink::getShortName() const
{
    return QString("UDP %1").arg(_targetHost.toString());
}

QString UDPClientLink::getDetail() const
{
    return QString::number(_port);
}

void UDPClientLink::setName(QString name)
{
    _name = name;
    emit nameChanged(_name);
    emit linkChanged(this);
}


qint64 UDPClientLink::getConnectionSpeed() const
{
    return 54000000; // 54 Mbit
}

qint64 UDPClientLink::getCurrentInDataRate() const
{
    return 0;
}

qint64 UDPClientLink::getCurrentOutDataRate() const
{
    return 0;
}
