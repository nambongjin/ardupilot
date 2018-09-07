/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009, 2010 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Interface class for protocols  /프로토콜에 대한 인터페이스 클래스
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef _PROTOCOLINTERFACE_H_
#define _PROTOCOLINTERFACE_H_

#include <QThread>
#include <QString>
#include <QByteArray>
#include "LinkInterface.h"

/**
 * @brief Interface for all protocols.
 *
 * This class defines the interface for
 * communication packets transported by the LinkManager.
 *
 * @see LinkManager.
 *
 **/
/**
 * @brief 모든 프로토콜의 인터페이스.
 *
 *이 클래스는
 LinkManager에 의해 전송 된 통신 패킷.
 *
 * @ LinkManager를 참조하십시오.
 *
**/
class ProtocolInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~ProtocolInterface () {}
    virtual QString getName() = 0;
    /**
     * Retrieve a total of all successfully parsed packets for the specified link.
     * @param link The link to return metadata about.
     * @returns -1 if this is not available for this protocol, # of packets otherwise.
     */
    /**
     * 지정된 링크에 대해 성공적으로 파싱 된 모든 패킷의 총합을 검색하십시오.
     * @param link 메타 데이타를 돌려주는 링크.
     * @returns -이 프로토콜에서는 사용할 수없는 경우 -1, 그렇지 않으면 패킷 수.
     */
    virtual qint32 getReceivedPacketCount(const LinkInterface *link) const = 0;
    /**
     * Retrieve a total of all parsing errors for the specified link.
     * @param link The link to return metadata about.
     * @returns -1 if this is not available for this protocol, # of errors otherwise.
     */
    /**
     * 지정된 링크에 대한 모든 구문 분석 오류를 모두 검색하십시오.
     * @param link 메타 데이타를 돌려주는 링크.
     이 프로토콜에서는 사용할 수없는 경우는 -1을 돌려 주어, 그렇지 않은 경우는 에러의 수를 돌려줍니다.
     */
    virtual qint32 getParsingErrorCount(const LinkInterface *link) const = 0;
    /**
     * Retrieve a total of all dropped packets for the specified link.
     * @param link The link to return metadata about.
     * @returns -1 if this is not available for this protocol, # of packets otherwise.
     */
    /**
     * 지정된 링크에 대해 삭제 된 패킷의 총 합계를 검색합니다.
     * @param link 메타 데이타를 돌려주는 링크.
     * @returns -이 프로토콜에서는 사용할 수없는 경우 -1, 그렇지 않으면 패킷 수.
     */
    virtual qint32 getDroppedPacketCount(const LinkInterface *link) const = 0;
    /**
     * Reset the received, error, and dropped counts for the given link. Useful for
     * when reconnecting a link.
     * @param link The link to reset metadata for.
     */
   /**
     * 주어진 링크에 대해 수신, 오류 및 삭제 된 횟수를 재설정합니다. 에 유용한
     * 링크를 다시 연결할 때.
     * @param link 메타 데이터를 재설정하는 링크입니다.
     */
    virtual void resetMetadataForLink(const LinkInterface *link) = 0;

public slots:
    virtual void receiveBytes(LinkInterface *link, QByteArray b) = 0;
    virtual void linkStatusChanged(bool connected) = 0;

signals:
    /** @brief Update the packet loss from one system */
    /** @brief 하나의 시스템에서 패킷 손실 업데이트 */
    void receiveLossChanged(int uasId, float loss);

};

#endif // _PROTOCOLINTERFACE_H_
