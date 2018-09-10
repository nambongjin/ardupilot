/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2013-2017 APM_PLANNER PROJECT <http://www.ardupilot.com>

This file is part of the APM_PLANNER project

    APM_PLANNER is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    APM_PLANNER is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with APM_PLANNER. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/
/**
 * @file
 *   @brief Airframe type configuration widget header.
 *
 *   @author Michael Carpenter <malcom2073@gmail.com>
 *   @author Arne Wischmann <wischmann-a@gmx.de>
 *
 */
/* *
 * @file
 * @brief Airframe type 설정 위젯 헤더.
 *
 * @author Michael Carpenter <malcom2073@gmail.com>
 * @author Arne Wischmann <wischmann-a@gmx.de>
 *
 */

#ifndef FRAMETYPECONFIG_H
#define FRAMETYPECONFIG_H

#include "UASParameter.h"
#include <QWidget>
#include "ui_FrameTypeConfig.h"
#include "ui_FrameTypeConfigOld.h"
#include "ui_FrameTypeConfigNew.h"
#include "UASInterface.h"
#include "UASManager.h"
#include "QGCUASParamManager.h"
#include "AP2ConfigWidget.h"
#include "APMFirmwareVersion.h"

/**
 * @brief The FrameTypeConfig class provides the outer Frame of the config dialog
 *        and loads a specialized inner dialog depending on the APM FW version.
 */
/* *
 * @brief FrameTypeConfig 클래스는 설정 대화 상자의 외부 프레임을 제공합니다
 * APM FW 버전에 따라 특수한 내부 대화 상자를로드합니다.
 */
class FrameTypeConfig : public AP2ConfigWidget
{
    Q_OBJECT
    
public:
    static const int FRAME_INIT_VALUE = 100;    /// Used to check if frameClass and FrameType have useful value// // frameClass 및 FrameType에 유용한 값이 있는지 확인하는 데 사용됩니다.

    explicit FrameTypeConfig(QWidget *parent = 0);
    ~FrameTypeConfig();

public slots:
    void paramButtonClicked();
    void activateCompareDialog();

signals:
    /**
     * @brief detectedOldFrameType - will be emitted if an ArduPilot FW < 3.5.0 is detected
     *        and the "FRAME" parameter is set.
     * @param frameType - Frame type ID of ArduPilot FW (@see FrameTypeConfigOld::FRAME_PLUS for example)
     */
    /* *
     * @brief detectedOldFrameType - ArduPilot FW <3.5.0이 감지되면 방출됩니다.
     * "FRAME"파라미터가 설정됩니다.
     * @param frameType - ArduPilot FW의 프레임 유형 ID (예 : FrameTypeConfigOld :: FRAME_PLUS 참조)
     */
    void detectedOldFrameType(int frameType);

    /**
     * @brief detectedNewFrameType - will be emitted if an ArduPilot FW >=3.5.0 is detected
     *        and "FRAME_TYPE" and "FRAME_CLASS" are set.
     * @param frameClass - Frame class ID of ArduPilot FW (@see FrameTypeConfigNew::FRAME_CLASS_QUAD for example)
     * @param frameType  - Frame type ID of ArduPilot FW (@see FrameTypeConfigNew::FRAME_TYPE_PLUS for example)
     */
    /* *
     * @brief detectedNewFrameType - ArduPilot FW> = 3.5.0이 감지되면 방출됩니다.
     * 및 "FRAME_TYPE"및 "FRAME_CLASS"가 설정됩니다.
     * @param frameClass - ArduPilot FW의 프레임 클래스 ID (예 : @see FrameTypeConfigNew :: FRAME_CLASS_QUAD)
     * @param frameType - ArduPilot FW의 프레임 유형 ID (예 : @see FrameTypeConfigNew :: FRAME_TYPE_PLUS)
     */
    void detectedNewFrameType(int frameClass, int frameType);


private slots:
    void parameterChanged(int uas, int component, QString parameterName, QVariant value);
    void parameterChanged(int uas, int component, int parameterCount, int parameterId,
                           QString parameterName, QVariant value);
private:
    Ui::FrameTypeConfig ui;

    QMap<QString, UASParameter*> m_parameterList;
    QString m_paramFileToCompare;
    APMFirmwareVersion m_currentFirmwareVersion;    /// holds the actual FW version as soon as it has been set.// / 설정되면 실제 FW 버전을 보유합니다.
    int m_frameClass;
    int m_frameType;
};

/**
 * @brief The FrameTypeConfigOld class provides the complete air frame config for
 *        APM versions prior 3.5.0
 *        Those Firmwares support only a parameter named "FRAME"
 */
/* *
 FrameTypeConfigOld 클래스는 다음을위한 완전한 에어 프레임 설정을 제공합니다.
 * APM 버전 3.5.0 이전
 * 해당 펌웨어는 "FRAME"이라는 매개 변수 만 지원합니다.
 */
class FrameTypeConfigOld : public QWidget
{
    Q_OBJECT

public:
    /** @defgroup Frame
     *  Possible values for parameter "FRAME"
     *  @{
     */
    static const int FRAME_PLUS  =  0;
    static const int FRAME_X     =  1;
    static const int FRAME_V     =  2;
    static const int FRAME_H     =  3;
    static const int FRAME_NEWY6 = 10;
    /** @} */ // end of Frame

    explicit FrameTypeConfigOld(UASInterface *uasInterface, QWidget *parent = 0);
    ~FrameTypeConfigOld();

public slots:
    /**
     * @brief setFrameType - to be called as soon as parameter "FRAME" is known.
     *        Sets up gui to reflect the settings
     * @param frameType  - Frame type ID of ArduPilot FW - @see Frame
     */
    /* *
     * @brief setFrameType - 매개 변수 "FRAME"이 알려지 자마자 호출됩니다.
     * 설정을 반영하도록 GUI 설정
     * @param frameType - ArduPilot FW의 프레임 유형 ID - @see 프레임
     */
    void setFrameType(int frameType);

private slots:
    void xFrameSelected();
    void plusFrameSelected();
    void vFrameSelected();
    void hFrameSelected();
    void newY6FrameSelected();

private:
    Ui::FrameTypeConfigOld ui;

    UASInterface *m_uasInterface;
    int           m_frameType;

    void enableButtons(bool enabled);

};

/**
 * @brief The FrameTypeConfigNew class provides the complete air frame config for
 *        APM versions since 3.5.0
 *        Those Firmwares support two parameters named "FRAME_CLASS" and "FRAME_TYPE"
 */
/* *
 * @brief FrameTypeConfigNew 클래스는 다음을위한 완벽한 에어 프레임 설정을 제공합니다.
 * 3.5.0 이후 APM 버전
 * 이들 펌웨어는 "FRAME_CLASS"및 "FRAME_TYPE"이라는 두 개의 매개 변수를 지원합니다.
 */
class FrameTypeConfigNew : public QWidget
{
    Q_OBJECT

public:
    /** @defgroup Frame class
     *  Possible values for parameter "FRAME_CLASS"
     *  @{
     */
    static const int FRAME_CLASS_UNDEFINED = 0;
    static const int FRAME_CLASS_QUAD      = 1;
    static const int FRAME_CLASS_HEXA      = 2;
    static const int FRAME_CLASS_OCTA      = 3;
    static const int FRAME_CLASS_OCTAQUAD  = 4;
    static const int FRAME_CLASS_Y6        = 5;
    static const int FRAME_CLASS_HELI      = 6;
    static const int FRAME_CLASS_TRI       = 7;
    static const int FRAME_CLASS_SINGLE    = 8;
    static const int FRAME_CLASS_COAX      = 9;
    /** @} */ // end of Frame class

    /** @defgroup Frame type
     *  Possible values for parameter "FRAME_TYPE"
     *  @{
     */
    static const int FRAME_TYPE_PLUS   =  0;
    static const int FRAME_TYPE_X      =  1;
    static const int FRAME_TYPE_V      =  2;
    static const int FRAME_TYPE_H      =  3;
    static const int FRAME_TYPE_V_TAIL =  4;
    static const int FRAME_TYPE_A_TAIL =  5;
    static const int FRAME_TYPE_Y6B    = 10;
    /** @} */ // end of Frame types


    explicit FrameTypeConfigNew(UASInterface *uasInterface, QWidget *parent = 0);
    ~FrameTypeConfigNew();

public slots:
    /**
     * @brief setFrameType - to be called as soon as "FRAME_CLASS" and "FRAME_TYPE" are known.
     *        Sets up gui to reflect the settings
     * @param frameClass - Frame class ID of ArduPilot FW - @see Frame class
     * @param frameType  - Frame type ID of ArduPilot FW - @see Frame type
     */
    /* *
     * @brief setFrameType - "FRAME_CLASS"와 "FRAME_TYPE"이 알려지 자마자 호출됩니다.
     * 설정을 반영하도록 GUI 설정
     * @param frameClass - ArduPilot FW의 프레임 클래스 ID - @see Frame 클래스
     * @param frameType - ArduPilot FW의 프레임 유형 ID - @see 프레임 유형
     */
    void setFrameType(int frameClass, int frameType);

private slots:
    /**
     * @brief FrameClass button handlers
     */
    /* *
     * @brief FrameClass 버튼 핸들러
     */
    void FrameClassQuadSelected();
    void FrameClassHexaSelected();
    void FrameClassOctaSelected();
    void FrameClassOctaQuadSelected();
    void FrameClassY6Selected();
    void FrameClassHeliSelected();
    void FrameClassTriSelected();
    void FrameClassSingleSelected();
    void FrameClassCoaxSelected();

    /**
     * @brief FrameType button handlers
     */
    /* *
     * @brief FrameType 버튼 핸들러
     */
    void FrameTypePlusSelected();
    void FrameTypeXSelected();
    void FrameTypeHSelected();
    void FrameTypeVSelected();
    void FrameTypeVTailSelected();
    void FrameTypeATailSelected();
    void FrameTypeY6BSelected();

private:
    Ui::FrameTypeConfigNew ui;

    UASInterface *m_uasInterface;
    int m_frameClass;
    int m_frameType;

    /**
     * @brief enableClassButtons - En / Disables all frame class buttons.
     * @param enabled - true enable, false disable.
     */
    /* *
     * @brief enableClassButtons - En / 모든 프레임 클래스 버튼을 비활성화합니다.
     파라미터 : enabled - true, false를 무효로합니다.
     */
    void enableClassButtons(bool enabled);

    /**
     * @brief enableTypeWidgets - Makes the frame type buttons visible / invisible
     * @param plus: true - Plus frame type visible, false - not visible
     * @param X   : true - X frame type visible, false - not visible
     * @param HV  : true - H and V frame type visible, false - not visible
     * @param AVTail : true - A/V-Tail frame type visible, false - not visible
     * @param Y6B : true - Y6B frame type visible, false - not visible
     */
    /* *
     * @ brief enableTypeWidgets - 프레임 유형 버튼을 보이거나 보이지 않게합니다.
     * @param plus : true - 플러스 프레임 유형 표시, false - 표시 안 함
     * @param X : true - X 프레임 유형 표시, false - 표시 안 함
     * @param HV : true - H 및 V 프레임 유형이 표시되고, false - 표시되지 않음
     * @param AVTail : true - A / V-Tail 프레임 유형 표시, false - 표시되지 않음
     * @param Y6B : 참 - Y6B 프레임 유형 표시, 거짓 - 표시되지 않음
     */
    void enableTypeWidgets(bool plus, bool X, bool HV, bool AVTail, bool Y6B);

    /**
     * @brief writeFrameParams - Writes the content of the members m_frameClass and m_frameType
     *        to the MAV.
     */
    /* *
     * @brief writeFrameParams - 멤버 m_frameClass 및 m_frameType의 내용을 씁니다.
     * MAV에.
     */
    void writeFrameParams();

};

#endif // FRAMETYPECONFIG_H
