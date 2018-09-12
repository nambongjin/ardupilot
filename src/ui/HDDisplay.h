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
 *   @brief Definition of Head Down Display (HDD)
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef HDDISPLAY_H
#define HDDISPLAY_H
#include <cmath>

#include <QtWidgets/QGraphicsView>
#include <QColor>
#include <QTimer>
#include <QFontDatabase>
#include <QMap>
#include <QContextMenuEvent>
#include <QPair>

#include "UASInterface.h"

namespace Ui
{
class HDDisplay;
}

/**
 * @brief Head Down Display Widget
 *
 * This widget is used for any head down display as base widget. It handles the basic widget setup
 * each head down instrument has a virtual screen size in millimeters as base coordinate system
 * this virtual screen size is then scaled to pixels on the screen.
 * When the pixel per millimeter ratio is known, a 1:1 representation is possible on the screen
 */
/* *
 * @brief 헤드 다운 디스플레이 위젯
 *
*이 위젯은 기본 위젯으로 모든 헤드 다운 디스플레이에 사용됩니다. 기본 위젯 설정을 처리합니다.
 * 각 헤드 다운 계측기는 기본 좌표계로 밀리미터 단위의 가상 화면 크기를가집니다.
 *이 가상 화면 크기는 화면의 픽셀 크기로 조정됩니다.
 * 밀리미터 당 픽셀 비율이 알려지면 화면에서 1 : 1 표시가 가능합니다.
 */
class HDDisplay : public QGraphicsView
{
    Q_OBJECT
public:
    HDDisplay(QStringList* plotList, QString title="", QWidget *parent = 0);
    ~HDDisplay();

public slots:
    /** @brief Update the HDD with new int8 data */
    /* * 최신 HDD를 새로운 int8 데이터로 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const qint8 value, const quint64 msec);
    /** @brief Update the HDD with new uint8 data */
    /* * brief 새로운 uint8 데이터로 HDD 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const quint8 value, const quint64 msec);
    /** @brief Update the HDD with new int16 data */
    /* * 최신 HDD를 새로운 int16 데이터로 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const qint16 value, const quint64 msec);
    /** @brief Update the HDD with new uint16 data */
    /* * 새로운 HDD를 uint16 데이터로 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const quint16 value, const quint64 msec);
    /** @brief Update the HDD with new int32 data */
    /* * 새로운 HDD를 새로운 int32 데이터로 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const qint32 value, const quint64 msec);
    /** @brief Update the HDD with new uint32 data */
    /* * 새로운 HDD를 uint32 데이터로 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const quint32 value, const quint64 msec);
    /** @brief Update the HDD with new int64 data */
    /* * 새로운 HDD를 새로운 int64 데이터로 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const qint64 value, const quint64 msec);
    /** @brief Update the HDD with new uint64 data */
    /* * brief 새로운 uint64 데이터로 HDD 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const quint64 value, const quint64 msec);
    /** @brief Update the HDD with new double data */
    /* * brief 새로운 더블 데이터로 HDD 업데이트 */
    void updateValue(const int uasId, const QString& name, const QString& unit, const double value, const quint64 msec);
	
    virtual void setActiveUAS(UASInterface* uas);
	
	/** @brief Connects a source to the updateValue() signals */
	/* * @brief 소스를 updateValue () 신호에 연결합니다. */
    void addSource(QObject* obj);
	/** @brief Disconnects a source to the updateValue() signals */
	/* * @brief 소스를 updateValue () 신호에 연결 해제합니다 */
    void removeSource(QObject* obj);

    /** @brief Removes a plot item by the action data */
    /* * @brief 작업 데이터로 플롯 항목을 제거합니다. */
    void removeItemByAction();
    /** @brief Bring up the menu to add a gauge */
    /* * brief 메뉴를 불러와 게이지 추가 */
    void addGauge();
    /** @brief Add a gauge using this spec string */
    /* * @brief이 스펙 문자열을 사용하여 게이지 추가 */
    void addGauge(const QString& gauge);
    /** @brief Set the title of this widget and any existing parent dock widget */
    /* * @ brief이 위젯과 기존의 모든 부모 도킹 위젯의 제목을 설정합니다 */
    void setTitle();
    /** @brief Set the number of colums via popup */
    /* * @ brief 팝업을 통해 열의 수를 설정합니다 */
    void setColumns();
    /** @brief Set the number of colums */
    /* * @ brief 콜룸 수를 설정합니다 */
    void setColumns(int cols);
    /** @brief Save the current layout and state to disk */
    /* * @brief 현재 레이아웃과 상태를 디스크에 저장합니다. */
    void saveState();
    /** @brief Restore the last layout and state from disk */
    /* * @ brief 디스크에서 마지막 레이아웃과 상태를 복원합니다. */
    void restoreState();

protected slots:
    void enableGLRendering(bool enable);
    //void render(QPainter* painter, const QRectF& target = QRectF(), const QRect& source = QRect(), Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio);
    void renderOverlay();
    void triggerUpdate();
    /** @brief Adjust the size hint for the current gauge layout */
    /* * @brief 현재 게이지 레이아웃의 크기 힌트 조정 */
    void adjustGaugeAspectRatio();

protected:
    QSize sizeHint() const;
    void changeEvent(QEvent* e);
    void paintEvent(QPaintEvent* event);
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);
    void contextMenuEvent(QContextMenuEvent* event);
    QList<QAction*> getItemRemoveActions();
    void createActions();
    float refLineWidthToPen(float line);
    float refToScreenX(float x);
    float refToScreenY(float y);
    float screenToRefX(float x);
    float screenToRefY(float y);
    void rotatePolygonClockWiseRad(QPolygonF& p, float angle, QPointF origin);
    void drawPolygon(QPolygonF refPolygon, QPainter* painter);
    void drawLine(float refX1, float refY1, float refX2, float refY2, float width, const QColor& color, QPainter* painter);
    void drawEllipse(float refX, float refY, float radiusX, float radiusY, float lineWidth, const QColor& color, QPainter* painter);
    void drawCircle(float refX, float refY, float radius, float lineWidth, const QColor& color, QPainter* painter);

    void drawChangeRateStrip(float xRef, float yRef, float height, float minRate, float maxRate, float value, QPainter* painter);
    void drawChangeIndicatorGauge(float xRef, float yRef, float radius, float expectedMaxChange, float value, const QColor& color, QPainter* painter, bool solid=true);
    void drawGauge(float xRef, float yRef, float radius, float min, float max, const QString name, float value, const QColor& color, QPainter* painter, bool symmetric, QPair<float, float> goodRange, QPair<float, float> criticalRange, bool solid=true);
    void drawSystemIndicator(float xRef, float yRef, int maxNum, float maxWidth, float maxHeight, QPainter* painter);
    void paintText(QString text, QColor color, float fontSize, float refX, float refY, QPainter* painter);

//    //Holds the current centerpoint for the view, used for panning and zooming
//     QPointF currentCenterPoint;
//
//     //From panning the view
//     QPoint lastPanPoint;
//
//     //Set the current centerpoint in the
//     void setCenter(const QPointF& centerPoint);
//     QPointF getCenter() { return currentCenterPoint; }
//
//     //Take over the interaction
//     virtual void mousePressEvent(QMouseEvent* event);
//     virtual void mouseReleaseEvent(QMouseEvent* event);
//     virtual void mouseMoveEvent(QMouseEvent* event);
//     virtual void wheelEvent(QWheelEvent* event);
//     virtual void resizeEvent(QResizeEvent* event);

    UASInterface* uas;                 ///< The uas currently monitored// / <현재 모니터링중인 uas
    QMap<QString, double> values;       ///< The variables this HUD displays// / <이 HUD가 표시하는 변수들
    QMap<QString, QString> units;      ///< The units// / <단위
    QMap<QString, float> valuesDot;    ///< First derivative of the variable// / <변수의 1 차 미분
    QMap<QString, float> valuesMean;   ///< Mean since system startup for this variable// / <이 변수에 대한 시스템 시작 이후의 평균
    QMap<QString, int> valuesCount;    ///< Number of values received so far// / <지금까지받은 값의 수
    QMap<QString, quint64> lastUpdate; ///< The last update time for this variable// / <이 변수의 마지막 업데이트 시간
    QMap<QString, float> minValues;    ///< The minimum value this variable is assumed to have// / <이 변수에 있다고 가정되는 최소값
    QMap<QString, float> maxValues;    ///< The maximum value this variable is assumed to have// / <이 변수가 가진 것으로 가정되는 최대 값
    QMap<QString, bool> symmetric;     ///< Draw the gauge / dial symmetric bool = yes// / <대칭 그리기 / 대칭 다이얼 그리기 bool = yes
    QMap<QString, bool> intValues;     ///< Is the gauge value an integer?// / <게이지 값이 정수입니까?
    QMap<QString, QString> customNames; ///< Custom names for the data names// / <데이터 이름의 사용자 정의 이름
    QMap<QString, QPair<float, float> > goodRanges; ///< The range of good values// / <좋은 값의 범위
    QMap<QString, QPair<float, float> > critRanges; ///< The range of critical values// / <임계 값의 범위
    double scalingFactor;      ///< Factor used to scale all absolute values to screen coordinates// / <모든 절대 값을 화면 좌표로 축척하는 데 사용되는 계수
    float xCenterOffset, yCenterOffset; ///< Offset from center of window in mm coordinates// / <창의 중심에서 mm 좌표로 오프셋
    float vwidth;              ///< Virtual width of this window, 200 mm per default. This allows to hardcode positions and aspect ratios. This virtual image plane is then scaled to the window size. // / <이 창의 가상 너비, 기본값 당 200mm. 이렇게하면 위치 및 종횡비를 하드 코드 할 수 있습니다. 이 가상 이미지 평면은 창 크기로 조정됩니다.
    float vheight;             ///< Virtual height of this window, 150 mm per default// / <이 창의 가상 높이, 기본값 당 150mm

    int xCenter;               ///< Center of the HUD instrument in pixel coordinates. Allows to off-center the whole instrument in its OpenGL window, e.g. to fit another instrument// / <픽셀 좌표의 HUD 도구 중심. OpenGL 창에서 전체 악기를 중심에 맞출 수 있습니다 (예 : 다른 악기에 맞추기).
    int yCenter;               ///< Center of the HUD instrument in pixel coordinates. Allows to off-center the whole instrument in its OpenGL window, e.g. to fit another instrument// / <픽셀 좌표의 HUD 도구 중심. OpenGL 창에서 전체 악기를 중심에 맞출 수 있습니다 (예 : 다른 악기에 맞추기).

    // HUD colors
   // HUD 색상
    QColor backgroundColor;    ///< Background color// / <배경색
    QColor defaultColor;       ///< Color for most HUD elements, e.g. pitch lines, center cross, change rate gauges// / <대부분의 HUD 요소의 색, 예를 들어 피치 선, 중심 십자 기호, 변화율 계
    QColor setPointColor;      ///< Color for the current control set point, e.g. yaw desired// / <현재 제어 설정 점의 색상입니다. 예 : 원하는 요 요
    QColor warningColor;       ///< Color for warning messages// / <경고 메시지의 색상
    QColor criticalColor;      ///< Color for caution messages// / <주의 메시지의 색상
    QColor infoColor;          ///< Color for normal/default messages// / <일반 / 기본 메시지의 색상
    QColor fuelColor;          ///< Current color for the fuel message, can be info, warning or critical color// / <연료 메시지의 현재 색은 정보, 경고 또는 임계 색일 수 있습니다.

    // Blink rates
    // 깜박임 속도
    int warningBlinkRate;      ///< Blink rate of warning messages, will be rounded to the refresh rate// / <경고 메시지의 깜박임 속도는 새로 고침 빈도로 반올림됩니다.

    QTimer* refreshTimer;      ///< The main timer, controls the update rate// / <메인 타이머는 업데이트 속도를 제어합니다.
    static const int updateInterval = 300; ///< Update interval in milliseconds// / <밀리 초 단위로 업데이트 간격
    QPainter* hudPainter;
    QFont font;                ///< The HUD font, per default the free Bitstream Vera SANS, which is very close to actual HUD fonts// / <실제 HUD 글꼴에 매우 근접한 무료 Bitstream Vera SANS의 기본값 인 HUD 글꼴
    QFontDatabase fontDatabase;///< Font database, only used to load the TrueType font file (the HUD font is directly loaded from file rather than from the system)// <글꼴 데이터베이스, 트루 타입 글꼴 파일을로드하는 데 사용됩니다 (HUD 글꼴은 시스템에서가 아니라 파일에서 직접로드됩니다)
    bool hardwareAcceleration; ///< Enable hardware acceleration// / <하드웨어 가속 사용

    float strongStrokeWidth;   ///< Strong line stroke width, used throughout the HUD// / <강한 라인 스트로크 폭, HUD 전반에 걸쳐 사용됨
    float normalStrokeWidth;   ///< Normal line stroke width, used throughout the HUD// / <HUD 전체에서 사용되는 일반적인 선 스트로크 너비
    float fineStrokeWidth;     ///< Fine line stroke width, used throughout the HUD // / <미세 선 스트로크 폭, HUD 전체에서 사용됨

    QStringList* acceptList;       ///< Variable names to plot// / <플롯 할 변수 이름
    QStringList* acceptUnitList;   ///< Unit names to plot// / <플롯 할 단위 이름

    quint64 lastPaintTime;     ///< Last time this widget was refreshed// / <이 위젯이 마지막으로 새로 고쳐진 시간
    int columns;               ///< Number of instrument columns// / <계측기 열 수

    QAction* addGaugeAction;   ///< Action adding a gauge// / <게이지 추가 동작
    QAction* setTitleAction;   ///< Action setting the title// / <제목을 설정하는 작업
    QAction* setColumnsAction; ///< Action setting the number of columns// / <컬럼의 수를 설정하는 액션
    bool valuesChanged;

private:
    Ui::HDDisplay *m_ui;
};

#endif // HDDISPLAY_H
