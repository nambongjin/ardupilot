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

#include <QTimer>
#include <QList>
#include <QDebug>
#include <QMutexLocker>
#include <iostream>
#include "TCPLink.h"
#include "LinkManager.h"
#include "QGC.h"
#include <QHostInfo>
#include <QSignalSpy>

/// @file
///     @brief TCP link type for SITL support
///
///     @author Don Gagne <don@thegagnes.com>
// / @file
// SITL 지원을위한 @brief TCP 링크 유형
// /
// / @author Don Gagne <don@thegagnes.com>

TCPLink::TCPLink(const QHostAddress &hostAddress, const QString &hostName, quint16 socketPort, bool asServer) :
    _name(hostName),
    _hostAddress(hostAddress),
    _port(socketPort),
    _asServer(asServer),
    _socket(NULL)
{
    _server.setMaxPendingConnections(1);
    _linkId = getNextLinkId();
    QObject::connect(&_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    qDebug() << "TCP Created " << _hostAddress.toString();
}

TCPLink::~TCPLink()
{
    disconnect();
	deleteLater();
}

void TCPLink::run()
{
	exec();
}

void TCPLink::setHostAddress(const QHostAddress &hostAddress)
{
    bool reconnect = false;

	if (this->isConnected()) {
		disconnect();
		reconnect = true;
	}
    _hostAddress = hostAddress;
    emit linkChanged(this);

	if (reconnect) {
		connect();
	}
}

void TCPLink::setHostName(const QString& hostName)
{
    _name = hostName;
    emit nameChanged(_name);
}

void TCPLink::setPort(int port)
{
    bool reconnect = false;

	if (this->isConnected()) {
		disconnect();
		reconnect = true;
	}

	_port = port;
    emit linkChanged(this);

	if (reconnect) {
		connect();
	}
}

void TCPLink::setAsServer(bool asServer)
{
    if (_asServer == asServer)
        return;

    bool reconnect = false;

    if (this->isConnected()) {
        disconnect();
        reconnect = true;
    }

    _asServer = asServer;
    emit linkChanged(this);

    if (reconnect) {
        connect();
    }
}


#ifdef TCPLINK_READWRITE_DEBUG
void TCPLink::_writeDebugBytes(const char *data, qint16 size)
{
    QString bytes;
    QString ascii;
    for (int i=0; i<size; i++)
    {
        unsigned char v = data[i];
        bytes.append(QString().sprintf("%02x ", v));
        if (data[i] > 31 && data[i] < 127)
        {
            ascii.append(data[i]);
        }
        else
        {
            ascii.append(219);
        }
    }
    qDebug() << "Sent" << size << "bytes to" << _hostAddress.toString() << ":" << _port << "data:";
    qDebug() << bytes;
    qDebug() << "ASCII:" << ascii;
}
#endif

void TCPLink::writeBytes(const char* data, qint64 size)
{
    if (!(_socket && _socket->isOpen()))
        return;

#ifdef TCPLINK_READWRITE_DEBUG
    _writeDebugBytes(data, size);
#endif
    _socket->write(data, size);

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
void TCPLink::readBytes()
{
    qint64 byteCount = _socket->bytesAvailable();

    if (byteCount)
    {
        QByteArray buffer;
        buffer.resize(byteCount);

        _socket->read(buffer.data(), buffer.size());

        emit bytesReceived(this, buffer);

        // Log the amount and time received for future data rate calculations.
        // 미래의 데이터 속도 계산을 위해받은 금액과 시간을 기록합니다.
        QMutexLocker dataRateLocker(&dataRateMutex);
        logDataRateToBuffer(inDataWriteAmounts, inDataWriteTimes, &inDataIndex, byteCount, QDateTime::currentMSecsSinceEpoch());

#ifdef TCPLINK_READWRITE_DEBUG
        writeDebugBytes(buffer.data(), buffer.size());
#endif
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
qint64 TCPLink::bytesAvailable()
{
    return _socket->bytesAvailable();
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
bool TCPLink::disconnect()
{
	quit();
	wait();

    if (_socket) {
        _socket->disconnectFromHost();
	}

    _server.close();

    return true;
}

void TCPLink::_socketDisconnected()
{
    qDebug() << _hostAddress.toString() << ": disconnected";

    Q_ASSERT(_socket);

    _socket->deleteLater();
    _socket = NULL;

    emit disconnected();
    emit connected(false);
    emit disconnected(this);
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
bool TCPLink::connect()
{
	if (isRunning())
	{
		quit();
		wait();
	}
    bool connected = _hardwareConnect();
    if (connected) {
        start(HighPriority);
    }
    return connected;
}

void TCPLink::newConnection()
{
    if (_socket != NULL)
        disconnect();

    _socket = _server.nextPendingConnection();
    if (_socket == NULL)
        return;

    qDebug() << _hostAddress.toString() << ": new connection";

    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readBytes()));
    QObject::connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(_socketError(QAbstractSocket::SocketError)));
    QObject::connect(_socket, SIGNAL(disconnected()), this, SLOT(_socketDisconnected()));

    emit connected(true);
    emit connected();
    emit connected(this);
}

bool TCPLink::_hardwareConnect(void)
{
    Q_ASSERT(_socket == NULL);

    if (_asServer)
    {
        if (!_server.isListening() && !_server.listen(QHostAddress::Any, _port)) {
            return false;
        }

        // this wait isn't necessary but it gives visual feedback
        // that the server is actually waiting for connection
        // and listen() didn't fail.
        // 이 대기는 필요 없지만 시각적 피드백을 제공합니다.
        // 서버가 실제로 연결을 기다리고 있음
        // 및 listen ()이 실패하지 않았습니다.
        if (!_server.waitForNewConnection(5000))
            return false;

        // let the newConnection signal handle the new connection
        // newConnection 신호가 새 연결을 처리하도록합니다.

        return true;
    }
    else
    {
    	_socket = new QTcpSocket();

        QSignalSpy errorSpy(_socket, SIGNAL(error(QAbstractSocket::SocketError)));

        _socket->connectToHost(_hostAddress, _port);

        QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readBytes()));
        QObject::connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(_socketError(QAbstractSocket::SocketError)));
        QObject::connect(_socket, SIGNAL(disconnected()), this, SLOT(_socketDisconnected()));

        // Give the socket five seconds to connect to the other side otherwise error out
        // 소켓을 다른쪽에 연결하는데 5 초 준다 그렇지 않으면 에러가 난다.
        if (!_socket->waitForConnected(5000))
        {
            // Whether a failed connection emits an error signal or not is platform specific.
            // So in cases where it is not emitted, we emit one ourselves.
            // 실패한 연결이 오류 신호를 내보내는 지 여부는 플랫폼에 따라 다릅니다.
            // 방출되지 않는 경우, 우리는 스스로 방출합니다.
            if (errorSpy.count() == 0) {
                emit communicationError(getName(), "Connection Failed");
            }
            delete _socket;
            _socket = NULL;
            return false;
        }

        emit connected(true);
        emit connected();
        emit connected(this);

        return true;
    }
}

void TCPLink::_socketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit communicationError(getName(), "Error on socket: " + _socket->errorString());
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
bool TCPLink::isConnected() const
{
    return _socket ? _socket->isOpen() : false;
}

int TCPLink::getId() const
{
    return _linkId;
}

QString TCPLink::getName() const
{
    if (_name.isEmpty()){
        return _hostAddress.toString();
    } else {
        return _name;
    }
}

QString TCPLink::getShortName() const
{
    if (_name.isEmpty()){
        return _hostAddress.toString();
    } else {
        return _name;
    }
}

QString TCPLink::getDetail() const
{
    return QString::number(_port);
}

qint64 TCPLink::getConnectionSpeed() const
{
    return 54000000; // 54 Mbit
}

qint64 TCPLink::getCurrentInDataRate() const
{
    return 0;
}

qint64 TCPLink::getCurrentOutDataRate() const
{
    return 0;
}

void TCPLink::_resetName(void)
{
    _name = QString("TCP %1 (host:%2 port:%3)").arg(_asServer ? "Server" : "Link").arg(_hostAddress.toString()).arg(_port);
    emit nameChanged(_name);
}
