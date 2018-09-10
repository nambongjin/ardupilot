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
 *   @brief Detail information of one MAV
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef _UASINFOWIDGET_H_
#define _UASINFOWIDGET_H_

#include <QWidget>
#include <QTimer>
#include <QMap>

#include "UASInterface.h"
#include "ui_UASInfo.h"

/**
 * @brief Info indicator for the currently active UAS	  현재 사용중인 UAS에 대한 정보 표시기
 *
 **/
class UASInfoWidget : public QWidget
{
    Q_OBJECT
public:
    UASInfoWidget(QWidget *parent = 0, QString name = "");
    ~UASInfoWidget();

public slots:
    void addUAS(UASInterface* uas);

    void setActiveUAS(UASInterface* uas);

    void updateBattery(UASInterface* uas, double voltage, double current, double percent, int seconds);
    void updateCPULoad(UASInterface* uas, double load);
    /** 
	 * @brief Set the loss rate of packets received by the MAV.
	 * @param uasId UNUSED
	 * @param receiveLoss A percentage value (0-100) of how many message the UAS has failed to receive.
	 */

/*
	 * @brief MAV가 수신 한 패킷의 손실률을 설정합니다.
	 * @param uasId UNUSED
	 * @param receiveLoss UAS가 수신하지 못한 메시지의 백분율 값 (0-100)입니다.
*/

    void updateReceiveLoss(int uasId, float receiveLoss);

    /**
	 * @brief Set the loss rate of packets sent from the MAV 
	 * @param uasId UNUSED
	 * @param sendLoss A percentage value (0-100) of how many message QGC has failed to receive.
	 */

/*
	 * @brief MAV에서 보낸 패킷의 손실률을 설정합니다. 
	 * @param uasId UNUSED
	 * @param sendLoss 수신 실패한 QGC 메시지의 백분율 값 (0-100)입니다.
*/

    void updateSendLoss(int uasId, float sendLoss);
	
    /** @brief Update the error count 	 오류 카운트 업데이트 */
    void updateErrorCount(int uasid, QString component, QString device, int count);

    void setVoltage(UASInterface* uas, double voltage);
    void setChargeLevel(UASInterface* uas, double chargeLevel);
    void setTimeRemaining(UASInterface* uas, double seconds);
//    void setBattery(int uasid, BatteryType type, int cells);

//    void valueChanged(int uasid, QString key, double value,quint64 time);
//    void actuatorChanged(UASInterface* uas, int actId, double value);
    void refresh();

protected:

    UASInterface* activeUAS;

    // Configuration variables	 설정 변수
    int voltageDecimals;
    int loadDecimals;

    // State variables	 상태 변수

    // Voltage	 전압
    double voltage;
    double chargeLevel;
    double timeRemaining;
    double load;
    float receiveLoss;
    float sendLoss;
    bool changed;
    QTimer* updateTimer;
    QString name;
    quint64 startTime;
    QMap<QString, int> errors;
    static const int updateInterval = 800; ///< Refresh interval in milliseconds	 새로 고침 간격 (밀리 초)

    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);

private:
    Ui::uasInfo ui;

};

#endif // _UASINFOWIDGET_H_
