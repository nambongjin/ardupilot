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
 *   @brief Definition of the configuration Window for Slugs' HIL Simulator
 *   @author Mariano Lizarraga <malife@gmail.com>
 */
/**
 * @file
 * 슬럼프의 HIL 시뮬레이터 구성 창 정의
 * @author Mariano Lizarraga <malife@gmail.com>
 */

#ifndef SLUGSHILSIM_H
#define SLUGSHILSIM_H

#include <stdint.h>

#include <QWidget>
#include <QHostAddress>
#include <QUdpSocket>
#include <QMessageBox>
#include <QByteArray>


#include "LinkInterface.h"
#include "UAS.h"
#include "LinkManager.h"
#include "SlugsMAV.h"


namespace Ui
{
class SlugsHilSim;
}

class SlugsHilSim : public QWidget
{
    Q_OBJECT

public:
    explicit SlugsHilSim(QWidget *parent = 0);
    ~SlugsHilSim();



protected:
    LinkInterface* hilLink;
    QHostAddress* simulinkIp;
    QUdpSocket* txSocket;
    QUdpSocket* rxSocket;
    UAS* activeUas;

    mavlink_local_position_ned_t tmpLocalPositionData;
    mavlink_attitude_t tmpAttitudeData;
    mavlink_raw_imu_t tmpRawImuData;
#ifdef MAVLINK_ENABLED_SLUGS
    mavlink_air_data_t tmpAirData;
#endif
    mavlink_gps_raw_int_t tmpGpsData;
#ifdef MAVLINK_ENABLED_SLUGS
    mavlink_gps_date_time_t tmpGpsTime;
#endif

public slots:

    /**
     * @brief Adds a link to the combo box listing so the user can select a link
     *
     * Populates the Combo box that allows the user to select the link with which Slugs will
     * receive the simulated sensor data from Simulink
     *
     * @param theLink the link that is being added to the combo box
     */
    /**
     * @brief 사용자가 링크를 선택할 수 있도록 콤보 상자 목록에 링크를 추가합니다.
     *
     * 사용자가 Slug가있는 링크를 선택할 수있는 콤보 상자를 채 웁니다.
     * Simulink에서 시뮬레이션 된 센서 데이터 수신
     *
     * combobox에 추가되고있는 링크를 @param에 링크합니다.
     */
    void addToCombo(LinkInterface* theLink);

    /**
     * @brief Puts Slugs in HIL Mode
     *
     * Sends the required messages through the main communication link to set Slugs in HIL Mode
     *
     */
    /**
     * @brief는 슬러그를 HIL 모드로 만든다.
     *
     * HIL 모드에서 슬러그를 설정하기 위해 메인 통신 링크를 통해 필요한 메시지를 보냅니다.
     *
     */
    void putInHilMode(void);

    /**
     * @brief Receives a datagram from Simulink containing the sensor data.
     *
     * Receives a datagram from Simulink containing the simulated sensor data. This data is then
     * forwarded to Slugs to use as input to the attitude estimation and navigation algorithms.
     *
     */
    /**
     * @brief 센서 데이터가 포함 된 Simulink에서 데이터 그램을받습니다.
     *
     * 시뮬레이션 된 센서 데이터가 포함 된 Simulink에서 데이터 그램을 수신합니다. 이 데이터는
     * 자세 추정 및 탐색 알고리즘의 입력으로 사용하기 위해 민달팽이에게 전달.
     *
     */
    void readDatagram(void);

    /**
     * @brief Called when the a new UAS is set to active.
     *
     * Called when the a new UAS is set to active.
     *
     * @param uas The new active UAS
     */
    /**
     * @brief 새 UAS가 활성으로 설정된 경우 호출됩니다.
     *
     * 새 UAS가 활성으로 설정된 경우 호출됩니다.
     *
     * @param uas 새로운 활성 UAS
     */
    void activeUasSet(UASInterface* uas);

    /**
     * @brief Called when the Link combobox selects a new link.
     *
     * @param uas The new index of the selected link
     */
    /**
     * @brief 링크 콤보 박스가 새로운 링크를 선택할 때 호출됩니다.
     *
     * @param uas 선택한 링크의 새 색인
     */
    void linkSelected (int cbIndex);

public slots:



private:

    typedef union _tFloatToChar {
        unsigned char   chData[4];
        float   		flData;
    } tFloatToChar;

    typedef union _tUint16ToChar {
        unsigned char   chData[2];
        uint16_t   		uiData;
    } tUint16ToChar;

    Ui::SlugsHilSim *ui;

    QHash <int, LinkInterface*> linksAvailable;

    void processHilDatagram (const QByteArray* datagram);
    float getFloatFromDatagram (const QByteArray* datagram, unsigned char * i);
    uint16_t getUint16FromDatagram (const QByteArray* datagram, unsigned char * i);
    void setUInt16ToDatagram(QByteArray& datagram, unsigned char* pos, uint16_t value);


    void sendMessageToSlugs();

    void commandDatagramToSimulink();

};

#endif // SLUGSHILSIM_H
