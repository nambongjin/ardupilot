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
 *   @brief Definition of class UASControlWidget
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/**
 * @file
 * @brief UASControlWidget 클래스의 정의
 *
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef _UASCONTROLWIDGET_H_
#define _UASCONTROLWIDGET_H_

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <ui_UASControl.h>
#include <UASInterface.h>

/**
 * @brief Widget controlling one MAV
 */
/**
 * 하나의 MAV를 제어하는 ​​간단한 위젯
 */
class UASControlWidget : public QWidget
{
    Q_OBJECT

public:
    UASControlWidget(QWidget *parent = 0);
    ~UASControlWidget();

public slots:
    /** @brief Set the system this widget controls */
    /** @ brief이 위젯이 제어하는 ​​시스템 설정 */
    void setUAS(UASInterface* uas);
    /** @brief Trigger next context action */
    /** brief 다음 컨텍스트 액션을 트리거합니다 */
    void cycleContextButton();
    /** @brief Set the operation mode of the MAV */
    /** @ brief MAV의 작동 모드를 설정합니다 */
    void setMode(int mode);
    /** @brief Transmit the operation mode */
    /** @ brief 운영 모드 전송 */
    void transmitMode();
    /** @brief Update the mode */
    /** @brief 모드 업데이트 */
    void updateMode(int uas,QString mode,QString description);
    /** @brief Update state */
    /** 업데이트 상태 */
    void updateState(int state);
    /** @brief Update internal state machine */
    /** @ brief 내부 상태 머신 업데이트 */
    void updateStatemachine();

signals:
    void changedMode(int);


protected slots:
    /** @brief Set the background color for the widget */
    /**  brief 위젯의 배경색을 설정합니다 */
    void setBackgroundColor(QColor color);

protected:
    int m_uas;              ///< Reference to the current uas
                            /// <현재의 uas에 대한 참조
    unsigned int m_uasMode; ///< Current uas mode
                            /// <현재 uas 모드
    bool m_engineOn;        ///< Engine state
                            /// <엔진 상태


private:
    Ui::uasControl ui;

};

#endif // _UASCONTROLWIDGET_H_
