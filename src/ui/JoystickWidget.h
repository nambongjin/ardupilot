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
 *   @brief Definition of joystick widget
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef JOYSTICKWIDGET_H
#define JOYSTICKWIDGET_H

#include <QtWidgets/QDialog>
#include <QLabel>

#include "JoystickInput.h"
#include "UASInterface.h"

namespace Ui
{
class JoystickWidget;
}

class JoystickWidget : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(JoystickWidget)
public:
    explicit JoystickWidget(JoystickInput* joystick, QWidget *parent = 0);
    virtual ~JoystickWidget();

public slots:
    /**
     * @brief Receive raw joystick values
     *
     * @param roll forward / pitch / x axis, front: 32'767, center: 0, back: -32'768
     * @param pitch left / roll / y axis, left: -32'768, middle: 0, right: 32'767
     * @param yaw turn axis, left-turn: -32'768, centered: 0, right-turn: 32'767
     * @param thrust Thrust, 0%: 0, 100%: 65535
     * @param xHat hat vector in forward-backward direction, +1 forward, 0 center, -1 backward
     * @param yHat hat vector in left-right direction, -1 left, 0 center, +1 right
     * @param buttons bitmask of pressed buttons
     */
    /* *
     * @brief 원시 조이스틱 값 받기
     *
     * @param 롤 포워드 / 피치 / x 축, 앞 : 32'767, 중심 : 0, 뒤 : -32'768
     * @param 피치 left / roll / y 축, 왼쪽 : -32'768, 중간 : 0, 오른쪽 : 32'767
     * @param yaw 회전축, 좌회전 : -32'768, 중심 맞춤 : 0, 우회전 : 32'767
     * @param 추력 추력, 0 % : 0, 100 % : 65535
     * @param x 전방 - 후방 방향의 모자 모자 벡터, 전진 +1, 중심 0, 역 -1
     * @param y 왼쪽 - 오른쪽 방향으로 모자이크 벡터, 왼쪽 -1, 중심 0, 오른쪽 +1
     * @param buttons 눌려진 버튼의 비트 마스크
     */
    void updateJoystick(double roll, double pitch, double yaw, double thrust, int xHat, int yHat, int buttons);
    /** @brief Throttle lever */
    /* * @ brief 스로틀 레버 */
    void setThrottle(double thrust);
    /** @brief Back/forth movement */
    /* * brief 앞뒤 운동 */
    void setX(double x);
    /** @brief Left/right movement */
    /* * brief 왼쪽 / 오른쪽 이동 */
    void setY(double y);
    /** @brief Wrist rotation */
    /* * brief 손목 회전 */
    void setZ(double z);
    /** @brief Hat switch position */
    /* * brief 모자 스위치 위치 */
    void setHat(int x, int y);
    /** @brief Clear keys */
    /* * 간단한 키 지우기 */
    void clearKeys();
    /** @brief Joystick keys, as labeled on the joystick */
    /* * brief 조이스틱 키, 조이스틱에 표시된대로 */
    void buttonStateChanged(const int key, const bool pressed);
    /** @brief Update status string */
    /* * 업데이트 상태 문자열 */
    void updateStatus(const QString& status);

protected slots:

    void joystickSelected(const QString&);
    void joystickEnabled(bool);

    void activeUASSet(UASInterface*);

private slots:
    void storeMapping();

    void restoreMapping();

protected:
    /** @brief UI change event */
    /* * 간단한 UI 변경 이벤트 */
    virtual void changeEvent(QEvent *e);

private:
    Ui::JoystickWidget *m_ui;
    JoystickInput* joystick;  ///< Reference to the joystick// / <조이스틱에 대한 참조

    int m_buttonStates[64];

    QString m_buttonPressedMessage;

    QList<QLabel*> m_buttonList;

    void addJoystickButtonLabel(int i);

    void updateMappings();
};

#endif // JOYSTICKWIDGET_H
