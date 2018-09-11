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
 *   @brief Definition of Head up display
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/**
 * @file
 헤드 업 디스플레이의 정의
 *
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */ 


#ifndef HUD_H
#define HUD_H

#include <QImage>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QFontDatabase>
#include <QTimer>
#include <QVector3D>
#include "UASInterface.h"

/**
 * @brief Displays a Head Up Display (HUD)
 *
 * This class represents a head up display (HUD) and draws this HUD in an OpenGL widget (QGLWidget).
 * It can superimpose the HUD over the current live image stream (any arriving image stream will be auto-
 * matically used as background), or it draws the classic blue-brown background known from instruments.
 */
/**
 * @brief 헤드 업 디스플레이 (HUD)
 *
 *이 클래스는 헤드 업 디스플레이 (HUD)를 나타내며이 HUD를 OpenGL 위젯 (QGLWidget)에 그립니다.
 * 현재 라이브 이미지 스트림에 HUD를 겹쳐 넣을 수 있습니다 (도착하는 모든 이미지 스트림은 자동으로 재생됩니다)
 * matically 배경으로 사용), 또는 악기에서 알려진 고전적인 푸른 갈색 배경을 그립니다.
 */
class HUD : public QLabel
{
    Q_OBJECT
public:
    HUD(int width = 640, int height = 480, QWidget* parent = NULL);
    ~HUD();

    void setImageSize(int width, int height, int depth, int channels);
    void resize(int w, int h);

public slots:
//    void initializeGL();
    //void paintGL();

    /** @brief Set the currently monitored UAS */
    /** @ brief 현재 모니터링되는 UAS를 설정합니다. */
    virtual void setActiveUAS(UASInterface* uas);

    /** @brief Attitude from main autopilot / system state */
    /** 기본 자동 조종 장치 / 시스템 상태에 대한 태도 */
    void updateAttitude(UASInterface* uas, double roll, double pitch, double yaw, quint64 timestamp);
    /** @brief Attitude from one specific component / redundant autopilot */
    /** 하나의 특정 구성 요소로부터 태도 / 예비 자동 조종 장치 */
    void updateAttitude(UASInterface* uas, int component, double roll, double pitch, double yaw, quint64 timestamp);
//    void updateAttitudeThrustSetPoint(UASInterface*, double rollDesired, double pitchDesired, double yawDesired, double thrustDesired, quint64 usec);

    void updateBattery(UASInterface*, double, double, double, int);
    void receiveHeartbeat(UASInterface*);
    void updateThrust(UASInterface*, double);
    void updateLocalPosition(UASInterface*,double,double,double,quint64);
    void updateGlobalPosition(UASInterface*,double,double,double,quint64);
    void updateSpeed(UASInterface*,double,double,double,quint64);
    void updateState(UASInterface*,QString);
    void updateMode(int id,QString mode, QString description);
    void updateLoad(UASInterface*, double);
    void selectWaypoint(int uasId, int id);

    void startImage(quint64 timestamp);
    void startImage(int imgid, int width, int height, int depth, int channels);
    void setPixels(int imgid, const unsigned char* imageData, int length, int startIndex);
    void finishImage();
    void saveImage();
    void saveImage(QString fileName);
    void saveImages(bool save);
    /** @brief Select directory where to load the offline files from */
    /** / brief 오프라인 파일을로드 할 디렉토리를 선택합니다. */
    void selectOfflineDirectory();
    /** @brief Enable the HUD instruments */
    /** brief HUD 기기 사용 가능 */
    void enableHUDInstruments(bool enabled);
    /** @brief Enable Video */
    /** brief 비디오 활성화 */
    void enableVideo(bool enabled);
    /** @brief Copy an image from the current active UAS */
    /** @brief 현재 활성 UAS에서 이미지 복사 */
    void copyImage();


protected slots:
    void paintRollPitchStrips();
    void paintPitchLines(float pitch, QPainter* painter);
    /** @brief Paint text on top of the image and OpenGL drawings */
    /** brief 이미지 및 OpenGL 드로잉 위에 텍스트를 페인트합니다. */
    void paintText(QString text, QColor color, float fontSize, float refX, float refY, QPainter* painter);
    void paintHUD();
    void paintPitchLinePos(QString text, float refPosX, float refPosY, QPainter* painter);
    void paintPitchLineNeg(QString text, float refPosX, float refPosY, QPainter* painter);

    void drawLine(float refX1, float refY1, float refX2, float refY2, float width, const QColor& color, QPainter* painter);
    void drawEllipse(float refX, float refY, float radiusX, float radiusY, float startDeg, float endDeg, float lineWidth, const QColor& color, QPainter* painter);
    void drawCircle(float refX, float refY, float radius, float startDeg, float endDeg, float lineWidth, const QColor& color, QPainter* painter);

    void drawChangeRateStrip(float xRef, float yRef, float height, float minRate, float maxRate, float value, QPainter* painter,bool reverse = false);
    void drawChangeIndicatorGauge(float xRef, float yRef, float radius, float expectedMaxChange, float value, const QColor& color, QPainter* painter, bool solid=true);

    void drawPolygon(QPolygonF refPolygon, QPainter* painter);

signals:
    void visibilityChanged(bool visible);

protected:
    void commitRawDataToGL();
    /** @brief Convert reference coordinates to screen coordinates */
    /** @ brief 표준 좌표를 화면 좌표로 변환 */
    float refToScreenX(float x);
    /** @brief Convert reference coordinates to screen coordinates */
    /** @ brief 표준 좌표를 화면 좌표로 변환 */
    float refToScreenY(float y);
    /** @brief Convert mm line widths to QPen line widths */
    /** @ brief mm 선 너비를 QPen 선 너비로 변환 */
    float refLineWidthToPen(float line);
    /** @brief Rotate a polygon around a point clockwise */
    /** brief 점을 중심으로 다각형을 시계 방향으로 회전 */
    void rotatePolygonClockWiseRad(QPolygonF& p, float angle, QPointF origin);
    /** @brief Preferred Size */
    /** brief 기본 크기 */
    QSize sizeHint() const;
    /** @brief Start updating widget */
    /** brief 위젯 업데이트 시작 */
    void showEvent(QShowEvent* event);
    /** @brief Stop updating widget */
    /** brief 위젯 업데이트 중지 */
    void hideEvent(QHideEvent* event);
    void contextMenuEvent (QContextMenuEvent* event);
    void createActions();

    static const int updateInterval = 100;

    QImage* image; ///< Double buffer image
                   /// <이중 버퍼 이미지
    QImage glImage; ///< The background / camera image
                    /// <배경 / 카메라 이미지
    UASInterface* uas; ///< The uas currently monitored
                       /// <현재 모니터링중인 uas
    float yawInt; ///< The yaw integral. Used to damp the yaw indication.
                  /// <yaw 적분입니다. 요우 표시를 감쇠시키는 데 사용됩니다.
    QString mode; ///< The current vehicle mode
                  /// <현재 차량 모드
    QString state; ///< The current vehicle state
                   /// <현재 차량 상태
    QString fuelStatus; ///< Current fuel level / battery voltage
                        /// <현재 연료 수준 / 배터리 전압
    double scalingFactor; ///< Factor used to scale all absolute values to screen coordinates
                          /// <모든 절대 값을 화면 좌표로 축척하는 데 사용되는 계수
    float xCenterOffset, yCenterOffset; ///< Offset from center of window in mm coordinates
                                        /// <창의 중심에서 mm 좌표로 오프셋
    float vwidth; ///< Virtual width of this window, 200 mm per default. This allows to hardcode positions and aspect ratios. This virtual image plane is then scaled to the window size.
 /// <이 창의 가상 너비, 기본값 당 200mm. 이렇게하면 위치 및 종횡비를 하드 코드 할 수 있습니다. 이 가상 이미지 평면은 창 크기로 조정됩니다.

    float vheight; ///< Virtual height of this window, 150 mm per default
                   /// <이 창의 가상 높이, 기본값 당 150mm
    float vGaugeSpacing; ///< Virtual spacing of the gauges from the center, 50 mm per default
                         /// <중심에서 게이지의 가상 간격, 기본값 당 50mm
    float vPitchPerDeg; ///< Virtual pitch to mm conversion. Currently one degree is 3 mm up/down in the pitch markings
                        /// <가상 피치에서 mm 변환으로. 현재 1 도는 피치 표시에서 3mm 위 / 아래입니다.

    int xCenter; ///< Center of the HUD instrument in pixel coordinates. Allows to off-center the whole instrument in its OpenGL window, e.g. to fit another instrument
                 /// <픽셀 좌표의 HUD 도구 중심. OpenGL 창에서 전체 악기를 중심에 맞출 수 있습니다 (예 : 다른 악기에 맞추기).
    int yCenter; ///< Center of the HUD instrument in pixel coordinates. Allows to off-center the whole instrument in its OpenGL window, e.g. to fit another instrument
                 /// <픽셀 좌표의 HUD 도구 중심. OpenGL 창에서 전체 악기를 중심에 맞출 수 있습니다 (예 : 다른 악기에 맞추기).

    // Image buffers
    // 이미지 버퍼
    unsigned char* rawBuffer1; ///< Double buffer 1 for the image
                               /// <이미지의 이중 버퍼 1
    unsigned char* rawBuffer2; ///< Double buffer 2 for the image
                               /// <이미지의 이중 버퍼 2
    unsigned char* rawImage;   ///< Pointer to current complete image
                               /// <현재 완성 된 이미지의 포인터
    int rawLastIndex;          ///< The last byte index received of the image
                               /// <이미지의 마지막 바이트 인덱스
    int rawExpectedBytes;      ///< Number of raw image bytes expected. Calculated by: image depth * channels * widht * height / 8                              /// <예상 이미지 바이트의 수. 계산 기준 : 이미지 깊이 * 채널 * widht * 높이 / 8
    int bytesPerLine;          ///< Bytes per image line. Is calculated as: image depth * channels * width / 8
                               /// 이미지 라인 당 바이트. 다음과 같이 계산됩니다 : 이미지 깊이 * 채널 * 너비 / 8
    bool imageStarted;         ///< If an image is currently in transmission
                               /// <이미지가 현재 전송 중이면
    int receivedDepth;         ///< Image depth in bit for the current image
                               /// <현재 이미지의 비트 심도 비트
    int receivedChannels;      ///< Number of color channels
                               /// <색상 채널 수
    int receivedWidth;         ///< Width in pixels of the current image
                               /// 현재 이미지의 픽셀 단위의 너비
    int receivedHeight;        ///< Height in pixels of the current image
                               /// <현재 이미지의 픽셀 단위 높이
    // HUD colors
    // HUD 색상
    QColor defaultColor;       ///< Color for most HUD elements, e.g. pitch lines, center cross, change rate gauges
                               /// <대부분의 HUD 요소의 색, 예를 들어 피치 선, 중심 십자 기호, 변화율 계
    QColor setPointColor;      ///< Color for the current control set point, e.g. yaw desired
                               /// <현재 제어 설정 점의 색상입니다. 예 : 원하는 요 요
    QColor warningColor;       ///< Color for warning messages
                               /// <경고 메시지의 색상
    QColor criticalColor;      ///< Color for caution messages
                               /// <주의 메시지의 색상
    QColor infoColor;          ///< Color for normal/default messages
                               /// <일반 / 기본 메시지의 색상
    QColor fuelColor;          ///< Current color for the fuel message, can be info, warning or critical color
                               /// <연료 메시지의 현재 색은 정보, 경고 또는 임계 색일 수 있습니다.

    // Blink rates
    // 깜박임 속도
    int warningBlinkRate;      ///< Blink rate of warning messages, will be rounded to the refresh rate
                               /// <경고 메시지의 깜박임 속도는 새로 고침 빈도로 반올림됩니다.
    QTimer* refreshTimer;      ///< The main timer, controls the update rate
    QPainter* HUDPainter;      /// <메인 타이머는 업데이트 속도를 제어합니다.
    QFont font;             ///< The HUD font, per default the free Bitstream Vera SANS, which is very close to actual HUD fonts
                            /// <실제 HUD 글꼴에 매우 근접한 무료 Bitstream Vera SANS의 기본값 인 HUD 글꼴
    QFontDatabase fontDatabase;///< Font database, only used to load the TrueType font file (the HUD font is directly loaded from file rather than from the system)
    /// <글꼴 데이터베이스, 트루 타입 글꼴 파일을로드하는 데 사용됩니다 (HUD 글꼴은 시스템에서가 아니라 파일에서 직접로드됩니다)

    bool noCamera;             ///< No camera images available, draw the ground/sky box to indicate the horizon
                               /// <사용할 수있는 카메라 이미지가 없습니다. 지평선을 표시하기 위해 땅 / 하늘 상자를 그립니다.
    bool hardwareAcceleration; ///< Enable hardware acceleration
                               /// <하드웨어 가속 사용
    float strongStrokeWidth;   ///< Strong line stroke width, used throughout the HUD
                               /// <강한 라인 스트로크 폭, HUD 전반에 걸쳐 사용됨
    float normalStrokeWidth;   ///< Normal line stroke width, used throughout the HUD
                               /// <HUD 전체에서 사용되는 일반적인 선 스트로크 너비
    float fineStrokeWidth;     ///< Fine line stroke width, used throughout the HUD
                               /// <미세 선 스트로크 폭, HUD 전체에서 사용됨

    QString waypointName;      ///< Waypoint name displayed in HUD
    float roll;                /// <HUD에 표시된 웨이 포인트 이름
    float pitch;
    float yaw;
    QMap<uint8_t, QVector3D> attitudes;
    float rollLP;
    float pitchLP;
    float yawLP;
    double yawDiff;
    double xPos;
    double yPos;
    double zPos;
    double xSpeed;
    double ySpeed;
    double zSpeed;
    quint64 lastSpeedUpdate;
    double totalSpeed;
    double totalAcc;
    double lat;
    double lon;
    double alt;
    float load;
    QString offlineDirectory;
    QString nextOfflineImage;
    bool HUDInstrumentsEnabled;
    bool videoEnabled;
    bool dataStreamEnabled;
    bool imageLoggingEnabled;
    float xImageFactor;
    float yImageFactor;
    QAction* enableHUDAction;
    QAction* enableVideoAction;
    QAction* selectOfflineDirectoryAction;
    QAction* selectVideoChannelAction;
    QAction* selectSaveDirectoryAction;
    void paintEvent(QPaintEvent *event);
    bool imageRequested;
    QString imageLogDirectory;
    unsigned int imageLogCounter;
};

#endif // HUD_H
