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
 *   @brief Definition of list of waypoints widget
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *   @author Benjamin Knecht <mavteam@student.ethz.ch>
 *   @author Petri Tanskanen <mavteam@student.ethz.ch>
 *
 */

#ifndef WAYPOINTLIST_H
#define WAYPOINTLIST_H

#include <QtWidgets/QWidget>
#include <QMap>
#include <QVBoxLayout>
#include <QTimer>
#include "Waypoint.h"
#include "UASInterface.h"
#include "WaypointEditableView.h"
#include "WaypointViewOnlyView.h"
#include "UnconnectedUASInfoWidget.h"
//#include "PopupMessage.h"


namespace Ui
{
class WaypointList;
}

class WaypointList : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(WaypointList)
public:
    WaypointList(QWidget* parent = NULL, UASWaypointManager* wpm = NULL);
    virtual ~WaypointList();

public slots:
    void updatePosition(UASInterface*, double x, double y, double z, quint64 usec);
    void updateAttitude(UASInterface*, double roll, double pitch, double yaw, quint64 usec);

    void setUAS(UASInterface* uas);

    //Waypoint list operations
    /** @brief Save the local waypoint list to a file */
    /* * @brief 로컬 웨이 포인트리스트를 파일에 저장합니다. */
    void saveWaypoints();
    void saveWaypointsDialogAccepted();
    /** @brief Load a waypoint list from a file */
    /* * @brief 파일에서 웨이 포인트 목록로드 */
    void loadWaypoints();
    void loadWaypointsDialogAccepted();
    /** @brief Transmit the local waypoint list to the UAS */
    /* * @ brief UAS에 로컬 웨이 포인트 목록 전송 */
    void transmit();
    /** @brief Read the remote waypoint list to both tabs */
    /* * brief 원격 웨이 포인트 목록을 양쪽 탭 */
    void read();
    /** @brief Read the remote waypoint list to "view"-tab only*/
    /* * @brief 원격 웨이 포인트 목록을 "보기"로 읽기 -tab 만 */
    void refresh();
    /** @brief Add a waypoint to "edit"-tab */
    /* * brief "편집"에 웨이 포인트 추가 -tab */
    void addEditable();
    /** @brief Add a waypoint to "edit"-tab on current MAV position or on generic position (home) */
    /* * brief 현재 MAV 위치 또는 일반 위치 (집)에 "편집"- 탭에 웨이 포인트 추가 */
    void addEditable(bool onCurrentPosition);
    /** @brief Add a waypoint at the current MAV position */
    /* * brief 현재 MAV 위치에 웨이 포인트 추가 */
    void addCurrentPositionWaypoint();
    /** @brief Add a waypoint by mouse click over the map */
    /* * @ brief지도 위에서 마우스로 클릭하여 웨이 포인트 추가 */

    //Update events
    /** @brief sets statusLabel string */
    /* * @ brief는 statusLabel 문자열을 설정합니다. */
    void updateStatusLabel(const QString &string);
    /** @brief The user wants to change the current waypoint */
    /* * brief 사용자가 현재 웨이 포인트를 변경하려고합니다 */
    void changeCurrentWaypoint(quint16 seq);
    /** @brief Current waypoint in edit-tab was changed, so the list must be updated (to contain only one waypoint checked as "current")  */
    /* * @brief 편집 탭의 현재 웨이 포인트가 변경되어 목록을 업데이트해야합니다 ( "현재"로 표시된 웨이 포인트 하나만 포함)   */
    void currentWaypointEditableChanged(quint16 seq);
    /** @brief Current waypoint on UAV was changed, update view-tab  */
    /* * brief UAV의 현재 웨이 포인트가 변경되어 뷰 탭 업데이트   */
    void currentWaypointViewOnlyChanged(quint16 seq);
    /** @brief The waypoint manager informs that one editable waypoint was changed */
    /* * / brief 웨이 포인트 매니저는 하나의 편집 가능한 웨이 포인트가 변경되었음을 알려줍니다 */
    void updateWaypointEditable(int uas, Waypoint* wp);
    /** @brief The waypoint manager informs that one viewonly waypoint was changed */
    /* * brief 웨이 포인트 매니저는 하나의 뷰 전용 웨이 포인트가 변경되었음을 알립니다. */
    void updateWaypointViewOnly(int uas, Waypoint* wp);
    /** @brief The waypoint manager informs that the editable waypoint list was changed */
    /* * / brief 웨이 포인트 매니저는 편집 가능한 웨이 포인트리스트가 변경되었음을 알립니다. */
    void waypointEditableListChanged(void);
    /** @brief The waypoint manager informs that the waypoint list on the MAV was changed */
    /* * brief 웨이 포인트 매니저는 MAV의 웨이 포인트리스트가 변경되었음을 알립니다. */
    void waypointViewOnlyListChanged(void);

//    /** @brief The MapWidget informs that a waypoint global was changed on the map */
//    void waypointGlobalChanged(const QPointF coordinate, const int indexWP);

    void clearWPWidget();

    //void changeWPPositionBySpinBox(Waypoint* wp);

    // Waypoint operations
    void moveUp(Waypoint* wp);
    void moveDown(Waypoint* wp);
    void moveTop(Waypoint* wp);
    void moveBottom(Waypoint* wp);
    void removeWaypoint(Waypoint* wp);

    void parameterChanged(int uas, int component, QString parameterName, QVariant value);

    void wpRadiusChanged(double radius);

signals:
    void clearPathclicked();
    void createWaypointAtMap(const QPointF coordinate);

protected:
    virtual void changeEvent(QEvent *e);

protected:
    QMap<Waypoint*, WaypointEditableView*> wpEditableViews;
    QMap<Waypoint*, WaypointViewOnlyView*> wpViewOnlyViews;
    QVBoxLayout* viewOnlyListLayout;
    QVBoxLayout* editableListLayout;
    UASInterface* m_uas;
    UASWaypointManager* WPM;
    double mavX;
    double mavY;
    double mavZ;
    double mavYaw;
    QPointF centerMapCoordinate;
    bool loadFileGlobalWP;
    bool readGlobalWP;
    bool showOfflineWarning;

private:
    Ui::WaypointList *m_ui;

private slots:
    void on_clearWPListButton_clicked();

};

#endif // WAYPOINTLIST_H
