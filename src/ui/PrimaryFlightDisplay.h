#ifndef PRIMARYFLIGHTDISPLAY_H
#define PRIMARYFLIGHTDISPLAY_H

#include <QWidget>
#include <QPen>
#include "UASInterface.h"

class PrimaryFlightDisplay : public QWidget
{
    Q_OBJECT
public:
    PrimaryFlightDisplay(int width = 640, int height = 480, QWidget* parent = NULL);
    ~PrimaryFlightDisplay();

public slots:
    /** @brief Attitude from main autopilot / system state */
    /* * 기본 자동 조종 장치 / 시스템 상태에 대한 태도 */
    void updateAttitude(UASInterface* uas, double roll, double pitch, double yaw, quint64 timestamp);
    /** @brief Attitude from one specific component / redundant autopilot */
    /* * 하나의 특정 구성 요소로부터 태도 / 예비 자동 조종 장치 */
    void updateAttitude(UASInterface* uas, int component, double roll, double pitch, double yaw, quint64 timestamp);

    void speedChanged(UASInterface* uas, double groundspeed, double airspeed, quint64 timestamp);
    void altitudeChanged(UASInterface*uas, double altitudeAMSL, double altitudeRelative, double climbRate, quint64 timestamp);
    void updateNavigationControllerErrors(UASInterface* uas, double altitudeError, double speedError, double xtrackError);

    void uasTextMessage(int uasid, int componentid, int severity, QString text);

    void preArmMessageTimeout();

    /** @brief Set the currently monitored UAS */
    //void addUAS(UASInterface* uas);
    void forgetUAS(UASInterface* uas);
    void setActiveUAS(UASInterface* uas);

protected:
    enum Layout {
        COMPASS_INTEGRATED,
        COMPASS_SEPARATED               // For a very high container. Feature panels are at bottom.// 매우 높은 컨테이너의 경우. 기능 패널은 맨 아래에 있습니다.
    };

    enum Style {
        NO_OVERLAYS,                    // Hzon not visible through tapes nor through feature panels. Frames with margins between.// Hz는 테이프 나 기능 패널을 통해 보이지 않습니다. 사이에 여백이있는 프레임.
        OVERLAY_HORIZONTAL,             // Hzon visible through tapes and (frameless) feature panels.// Hz는 테이프 및 (프레임이없는) 기능 패널을 통해 볼 수 있습니다.
        OVERLAY_HSI                     // Hzon visible through everything except bottom feature panels. // 하단 기능 패널을 제외한 모든 항목을 통해 표시됩니다.
    };

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *e);

    // from HUD.h:

    /** @brief Preferred Size */
    /* * brief 기본 크기 */
    QSize sizeHint() const;
    /** @brief Start updating widget */
    /* * brief 위젯 업데이트 시작 */
    void showEvent(QShowEvent* event);
    /** @brief Stop updating widget */
    /* * brief 위젯 업데이트 중지 */
    void hideEvent(QHideEvent* event);

    // dongfang: We have no context menu. Viewonly.
    // void contextMenuEvent (QContextMenuEvent* event);

    // dongfang: What is that?
    // dongfang: OK it's for UI interaction. Presently, there is none.
    void createActions();

signals:
    void visibilityChanged(bool visible);

private:
    /*
    enum AltimeterMode {
        PRIMARY_MAIN_GPS_SUB,   // Show the primary alt. on tape and GPS as extra info
        GPS_MAIN                // Show GPS on tape and no extra info
    };

    enum AltimeterFrame {
        ASL,                    // Show ASL altitudes (plane pilots' normal preference)
        RELATIVE_TO_HOME        // Show relative-to-home altitude (copter pilots)
    };

    enum SpeedMode {
        PRIMARY_MAIN_GROUND_SUB,// Show primary speed (often airspeed) on tape and groundspeed as extra
        GROUND_MAIN             // Show groundspeed on tape and no extra info
    };
    */

    /*
     * There are at least these differences between airplane and copter PDF view:
     * - Airplane show absolute altutude in altimeter, copter shows relative to home
     */
    /*
     * 적어도 비행기와 헬리콥터 PDF보기에는 다음과 같은 차이점이 있습니다.
     * - 비행기는 고도계에서 절대 고도를 표시하고, 헬리콥터는 집과 관련하여 보여줍니다.
     */
    bool shouldDisplayNavigationData();

    void drawTextCenter(QPainter& painter, QString text, float fontSize, float x, float y);
    void drawTextLeftCenter(QPainter& painter, QString text, float fontSize, float x, float y);
    void drawTextRightCenter(QPainter& painter, QString text, float fontSize, float x, float y);
    void drawTextCenterBottom(QPainter& painter, QString text, float fontSize, float x, float y);
    void drawTextCenterTop(QPainter& painter, QString text, float fontSize, float x, float y);
    void drawAIGlobalFeatures(QPainter& painter, QRectF mainArea, QRectF paintArea);
    void drawAIAirframeFixedFeatures(QPainter& painter, QRectF area);
    void drawPitchScale(QPainter& painter, QRectF area, float intrusion, bool drawNumbersLeft, bool drawNumbersRight);
    void drawRollScale(QPainter& painter, QRectF area, bool drawTicks, bool drawNumbers);
    void drawAIAttitudeScales(QPainter& painter, QRectF area, float intrusion);
    void drawAICompassDisk(QPainter& painter, QRectF area, float halfspan);
    void drawSeparateCompassDisk(QPainter& painter, QRectF area);

    void drawAltimeter(QPainter& painter, QRectF area, float altitudeRelative, float altitudeAMSL, float vv);
    void drawVelocityMeter(QPainter& painter, QRectF area, float speed, float secondarySpeed);
    void fillInstrumentBackground(QPainter& painter, QRectF edge);
    void fillInstrumentOpagueBackground(QPainter& painter, QRectF edge);
    void drawInstrumentBackground(QPainter& painter, QRectF edge);

    /* This information is not currently included. These headers left in as a memo for restoration later.
    void drawLinkStatsPanel(QPainter& painter, QRectF area);
    void drawSysStatsPanel(QPainter& painter, QRectF area);
    void drawMissionStatsPanel(QPainter& painter, QRectF area);
    void drawSensorsStatsPanel(QPainter& painter, QRectF area);
    */

    void doPaint();

    UASInterface* uas;          ///< The uas currently monitored// / <현재 모니터링중인 uas

    /*
    AltimeterMode altimeterMode;
    AltimeterFrame altimeterFrame;
    SpeedMode speedMode;
    */

    bool preArmCheckFailure;
    QString preArmCheckMessage;
    QTimer *preArmMessageTimer;

    bool didReceivePrimaryAltitude;
    bool didReceivePrimarySpeed;

    float roll;
    float pitch;
    float heading;

    float m_altitudeRelative;
    float m_altitudeAMSL;

    // APM: GPS and baro mix above home (GPS) altitude. This value comes from the GLOBAL_POSITION_INT message.
    // Do !!!NOT!!! ever do altitude calculations at the ground station. There are enough pitfalls already.
    // If the MP "set home altitude" button is migrated to here, it must set the UAS home altitude, not a GS-local one.
    // APM : GPS 및 baro 집 (GPS) 고도 위. 이 값은 GLOBAL_POSITION_INT 메시지에서 가져옵니다.
    // 하지 마 !!! 지상국에서 고도 계산을해라. 이미 함정이 충분히 있습니다.
    // MP "home altitude 설정"버튼이 여기로 이동되면 GS 로컬이 아닌 UAS 집 고도를 설정해야합니다.
    float aboveHomeAltitude;

    float m_groundspeed;
    float m_airspeed;
    float m_climbRate;

    float navigationAltitudeError;
    float navigationSpeedError;
    float navigationCrosstrackError;
    float navigationTargetBearing;

    Layout layout;      // The display layout.// 표시 레이아웃.
    Style style;        // The AI style (tapes translucent or opague)// AI 스타일 (테이프 반투명 또는 opague)

    // TODO: Use stylesheet colors?
    // TODO : 스타일 시트 색상을 사용합니까?
    QColor redColor;
    QColor amberColor;
    QColor greenColor;

    qreal lineWidth;
    qreal fineLineWidth;

    qreal smallTextSize;
    qreal mediumTextSize;
    qreal largeTextSize;

    // Globally used stuff only.
    // 전역 적으로 사용되는 항목 만.
    QPen instrumentEdgePen;
    QBrush instrumentBackground;
    QBrush instrumentOpagueBackground;

    QFont font;

    QTimer* refreshTimer;       ///< The main timer, controls the update rate// / <메인 타이머는 업데이트 속도를 제어합니다.

    static const int tickValues[];
    static const QString compassWindNames[];

    static const int updateInterval = 250;
};

#endif // PRIMARYFLIGHTDISPLAY_H
