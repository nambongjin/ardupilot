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
 *   @brief Definition of class UASView
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/**
 * @file
 * @brief UASView 클래스의 정의
 *
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef UASVIEW_H
#define UASVIEW_H

#include <QtWidgets/QWidget>
#include <QString>
#include <QTimer>
#include <QMouseEvent>
#include <UASInterface.h>

namespace Ui
{
class UASView;
}

class UASView : public QWidget
{
    Q_OBJECT
public:
    UASView(UASInterface* uas, QWidget *parent = 0);
    ~UASView();

public slots:
    /** @brief Update the name of the system */
    /** @ brief 시스템 이름 업데이트 */
    void updateName(const QString& name);
    void receiveHeartbeat(UASInterface* uas);
    void updateThrust(UASInterface* uas, double thrust);
    void updateBattery(UASInterface* uas, double voltage, double current, double percent, int seconds);
    void updateLocalPosition(UASInterface*, double x, double y, double z, quint64 usec);
    void updateGlobalPosition(UASInterface*, double lon, double lat, double alt, quint64 usec);
    void updateSpeed(UASInterface*, double x, double y, double z, quint64 usec);
    void updateState(UASInterface*, QString uasState, QString stateDescription);
    /** @brief Update the MAV mode */
    /** @ brief MAV 모드를 업데이트합니다. */
    void updateMode(int sysId, QString status, QString description);
    void updateLoad(UASInterface* uas, double load);
    //void receiveValue(int uasid, QString id, double value, quint64 time);
    void showHILUi();
    void refresh();
    /** @brief Receive new waypoint information */
    /** 새로운 웨이 포인트 정보 수신 */
    void setWaypoint(int uasId, int id, double x, double y, double z, double yaw, bool autocontinue, bool current);
    /** @brief Update the current active waypoint */
    /** @brief 현재 활성 웨이 포인트 업데이트 */
    void currentWaypointUpdated(quint16 waypoint);
    /** @brief Set waypoint as current target */
    /** brief 웨이 포인트를 현재 타겟으로 설정합니다. */
    void selectWaypoint(int uasId, int id);
    /** @brief Set the current system type */
    /** @ brief 현재 시스템 유형 설정 */
    void setSystemType(UASInterface* uas, unsigned int systemType);
    /** @brief Set the current UAS as the globally active system */
    /** @ brief 현재 UAS를 전역 활성 시스템으로 설정합니다. */
    void setUASasActive(bool);
    /** @brief Update the view if an UAS has been set to active */
    /** @ brief UAS가 활성으로 설정된 경우보기를 업데이트합니다. */
    void updateActiveUAS(UASInterface* uas, bool active);
    /** @brief Set the widget into critical mode */
    /** @brief 위젯을 중요한 모드로 설정합니다. */
    void heartbeatTimeout(bool timeout, unsigned int ms);
    /** @brief Set the background color for the widget */
    /** / brief 위젯의 배경색을 설정합니다 */
    void setBackgroundColor();
    /** @brief Bring up the dialog to rename the system */
    /** @ brief 시스템의 이름을 바꾸기 위해 대화 상자를 불러옵니다. */
    void rename();
    /** @brief Select airframe for this vehicle */
    /** brief이 차량의 기체를 선택하십시오 */
    void selectAirframe();
    /** @brief Select the battery type */
    /** brief 배터리 유형 선택 */
    void setBatterySpecs();
    /** @brief Show a status text message */
    /** brief 상태 텍스트 메시지 표시 */
    void showStatusText(int uasid, int componentid, int severity, QString text);
    /** @brief Update the navigation mode state */
    /** @ brief 탐색 모드 상태를 업데이트합니다. */
    void updateNavMode(int uasid, int mode, const QString& text);

protected:
    void changeEvent(QEvent *e);
    QTimer* refreshTimer;
    QColor heartbeatColor;
    quint64 startTime;
    bool timeout;
    bool iconIsRed;
    int timeRemaining;
    float chargeLevel;
    UASInterface* uas;
    float load;
    QString state;
    QString stateDesc;
    QString mode;
    double thrust; ///< Current vehicle thrust: 0 - 1.0 for 100% thrust
                   /// <현재 차량 추력 : 100 % 추력에 대해 0 - 1.0
    bool isActive; ///< Is this MAV selected by the user?
                   /// <이 MAV가 사용자에 의해 선택 되었습니까?
    float x;
    float y;
    float z;
    float totalSpeed;
    float lat;
    float lon;
    float alt;
    float groundDistance;
    bool localFrame;
    bool globalFrameKnown;
    QAction* removeAction;
    QAction* renameAction;
    QAction* selectAction;
    QAction* hilAction;
    QAction* hilXAction;
    QAction* selectAirframeAction;
    QAction* setBatterySpecsAction;
    static const int updateInterval = 800;
    static const int errorUpdateInterval = 200;
    bool lowPowerModeEnabled; ///< Low power mode reduces update rates
                              /// <저전력 모드로 업데이트 속도 감소
    unsigned int generalUpdateCount; ///< Skip counter for updates
                                     /// <업데이트를 위해 카운터 건너 뛰기
    double filterTime; ///< Filter time estimate of battery
                       /// <배터리 시간의 필터 예상 시간


    void mouseDoubleClickEvent (QMouseEvent * event);
    /** @brief Mouse enters the widget */
    /** brief 마우스가 위젯을 입력합니다 */
    void enterEvent(QEvent* event);
    /** @brief Mouse leaves the widget */
    /** brief 마우스가 위젯을 떠난다. */
    void leaveEvent(QEvent* event);
    /** @brief Start widget updating */
    /** brief 위젯 업데이트 시작 */
    void showEvent(QShowEvent* event);
    /** @brief Stop widget updating */
    /** brief 위젯 업데이트 중지 */
    void hideEvent(QHideEvent* event);
    void contextMenuEvent(QContextMenuEvent* event);

private:
    Ui::UASView *m_ui;

signals:
    void uasInFocus(UASInterface* uas);
    void uasOutFocus(UASInterface* uas);
};

#endif // UASVIEW_H
