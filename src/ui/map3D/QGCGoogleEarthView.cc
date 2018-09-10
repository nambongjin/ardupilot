#include "QGC.h"
#include "ui_QGCGoogleEarthView.h"
#include "QsLog.h"
#include "QGCGoogleEarthView.h"
#include "UASWaypointManager.h"
#include "UASManager.h"

#include <QApplication>
#include <QDir>
#include <QShowEvent>
#include <QSettings>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>

#ifdef Q_OS_MAC
#include <QWebFrame>
#include <QWebPage>
#include <QWebElement>
#include "QGCWebPage.h"
#endif

#ifdef _MSC_VER
#include <QAxObject>
#include <QUuid>
#include <mshtml.h>
#include <comdef.h>
#include <qaxtypes.h>
#endif

#define QGCGOOGLEEARTHVIEWSETTINGS QString("GoogleEarthViewSettings_")

QGCGoogleEarthView::QGCGoogleEarthView(QWidget *parent) :
    QWidget(parent),
    updateTimer(new QTimer(this)),
    refreshRateMs(100),
    mav(NULL),
    followCamera(true),
    trailEnabled(true),
    webViewInitialized(false),
    jScriptInitialized(false),
    gEarthInitialized(false),
    currentViewMode(QGCGoogleEarthView::VIEW_MODE_SIDE),
#if (defined Q_OS_MAC)
    webViewMac(new QWebView(this)),
#endif
#ifdef _MSC_VER
    webViewWin(new QGCWebAxWidget(this)),
    documentWin(NULL),
#endif
    ui(new Ui::QGCGoogleEarthView)
{
#ifdef _MSC_VER
    // Create layout and attach webViewWin

//    QFile file("doc.html");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        QLOG_DEBUG() << __FILE__ << __LINE__ << "Could not open log file";

//    QTextStream out(&file);
//    out << webViewWin->generateDocumentation();
//    out.flush();
//    file.flush();
//    file.close();

/*
    // 레이아웃을 만들고 webViewWin을 첨부합니다.

//     QFile 파일 ( "doc.html");
//     if (! file.open (QIODevice :: WriteOnly | QIODevice :: Text))
//         QLOG_DEBUG () << __FILE__ << __LINE__ << "로그 파일을 열 수 없습니다";

//     QTextStream out (& file);
//     out << webViewWin-> generateDocumentation ();
//     out.flush ();
//     file.flush ();
//     file.close ();
*/



#else
#endif

    // Load settings
    QSettings settings;
    followCamera = settings.value(QGCGOOGLEEARTHVIEWSETTINGS + "follow", followCamera).toBool();
    trailEnabled = settings.value(QGCGOOGLEEARTHVIEWSETTINGS + "trail", trailEnabled).toBool();

    ui->setupUi(this);
#if (defined Q_OS_MAC)
    ui->webViewLayout->addWidget(webViewMac);
    //connect(webViewMac, SIGNAL(loadFinished(bool)), this, SLOT(initializeGoogleEarth(bool)));
#endif

#ifdef _MSC_VER
    ui->webViewLayout->addWidget(webViewWin);
#endif

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateState()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(reloadHTML()));
    connect(ui->changeViewButton, SIGNAL(clicked()), this, SLOT(toggleViewMode()));
    connect(ui->clearTrailsButton, SIGNAL(clicked()), this, SLOT(clearTrails()));
    connect(ui->atmosphereCheckBox, SIGNAL(clicked(bool)), this, SLOT(enableAtmosphere(bool)));
    connect(ui->daylightCheckBox, SIGNAL(clicked(bool)), this, SLOT(enableDaylight(bool)));

    connect(UASManager::instance(), SIGNAL(homePositionChanged(double,double,double)), this, SLOT(setHome(double,double,double)));
}

QGCGoogleEarthView::~QGCGoogleEarthView()
{
    QSettings settings;
    settings.setValue(QGCGOOGLEEARTHVIEWSETTINGS + "follow", followCamera);
    settings.setValue(QGCGOOGLEEARTHVIEWSETTINGS + "trail", trailEnabled);
    settings.sync();
#if (defined Q_OS_MAC)
    delete webViewMac;
#endif
#ifdef _MSC_VER
    delete webViewWin;
#endif
    delete ui;
}

/**
 * @param range in centimeters	 @param의 범위는 센티미터
 */
void QGCGoogleEarthView::setViewRangeScaledInt(int range)
{
    setViewRange(range/100.0f);
}

void QGCGoogleEarthView::reloadHTML()
{
    hide();
    webViewInitialized = false;
    jScriptInitialized = false;
    gEarthInitialized = false;
    show();
}

void QGCGoogleEarthView::enableEditMode(bool mode)
{
    javaScript(QString("setDraggingAllowed(%1);").arg(mode));
}

void QGCGoogleEarthView::enableDaylight(bool enable)
{
    javaScript(QString("enableDaylight(%1);").arg(enable));
}

void QGCGoogleEarthView::enableAtmosphere(bool enable)
{
    javaScript(QString("enableAtmosphere(%1);").arg(enable));
}

/**
 * @param range in meters (SI-units)	파라미터 범위 (미터) (SI 단위)
 */
void QGCGoogleEarthView::setViewRange(float range)
{
    javaScript(QString("setViewRange(%1);").arg(range, 0, 'f', 5));
}

void QGCGoogleEarthView::setDistanceMode(int mode)
{
    javaScript(QString("setDistanceMode(%1);").arg(mode));
}

void QGCGoogleEarthView::toggleViewMode()
{
    switch (currentViewMode) {
    case VIEW_MODE_MAP:
        setViewMode(VIEW_MODE_SIDE);
        break;
    case VIEW_MODE_SIDE:
        setViewMode(VIEW_MODE_MAP);
        break;
    case VIEW_MODE_CHASE_LOCKED:
        setViewMode(VIEW_MODE_CHASE_FREE);
        break;
    case VIEW_MODE_CHASE_FREE:
        setViewMode(VIEW_MODE_CHASE_LOCKED);
        break;
    }
}

void QGCGoogleEarthView::setViewMode(QGCGoogleEarthView::VIEW_MODE mode)
{
    switch (mode) {
    case VIEW_MODE_MAP:
        ui->changeViewButton->setText("Free View");
        break;
    case VIEW_MODE_SIDE:
        ui->changeViewButton->setText("Map View");
        break;
    case VIEW_MODE_CHASE_LOCKED:
        ui->changeViewButton->setText("Free Chase");
        break;
    case VIEW_MODE_CHASE_FREE:
        ui->changeViewButton->setText("Fixed Chase");
        break;
    }
    currentViewMode = mode;
    javaScript(QString("setViewMode(%1);").arg(mode));
}

void QGCGoogleEarthView::addUAS(UASInterface* uas)
{
    // uasid, type, color (in #rrbbgg format)
    QString uasColor = uas->getColor().name().remove(0, 1);
    // Convert to bbggrr format	bbggrr 형식으로 변환
    QString rChannel = uasColor.mid(0, 2);
    uasColor.remove(0, 2);
    uasColor.prepend(rChannel);
    // Set alpha value to 0x66, append JavaScript quotes ('')	알파 값을 0x66으로 설정하고 자바 스크립트 따옴표 ( '')를 추가합니다.
    uasColor.prepend("'66").append("'");
    javaScript(QString("createAircraft(%1, %2, %3);").arg(uas->getUASID()).arg(uas->getSystemType()).arg(uasColor));

    if (trailEnabled) javaScript(QString("showTrail(%1);").arg(uas->getUASID()));

    // Automatically receive further position updates	자동으로 추가 위치 업데이트를받습니다.
    connect(uas, SIGNAL(globalPositionChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateGlobalPosition(UASInterface*,double,double,double,quint64)));
    // Receive waypoint updates
    // Connect the waypoint manager / data storage to the UI

/*
    // 웨이 포인트 업데이트를받습니다.
    // UI에 웨이 포인트 매니저 / 데이터 스토리지 연결
*/

    connect(uas->getWaypointManager(), SIGNAL(waypointEditableListChanged(int)), this, SLOT(updateWaypointList(int)));
    connect(uas->getWaypointManager(), SIGNAL(waypointEditableChanged(int, Waypoint*)), this, SLOT(updateWaypoint(int,Waypoint*)));
    //connect(this, SIGNAL(waypointCreated(Waypoint*)), uas->getWaypointManager(), SLOT(addWaypointEditable(Waypoint*)));
    // TODO Update waypoint list on UI changes here

/*
    // connect (this, SIGNAL (waypointCreated (Waypoint *)), uas-> getWaypointManager (), SLOT (addWaypointEditable (Waypoint *)));
    // TODO 여기 UI 변경 사항에 대한 웨이 포인트 목록 업데이트
*/

}

void QGCGoogleEarthView::setActiveUAS(UASInterface* uas)
{
    if (uas)
    {
        mav = uas;
        javaScript(QString("setCurrAircraft(%1);").arg(uas->getUASID()));
        updateWaypointList(uas->getUASID());
    }
}

/**
 * This function is called if a a single waypoint is updated and
 * also if the whole list changes.
 */

/*
 *이 함수는 단일 웨이 포인트가 업데이트되고
 * 전체 목록이 변경된 경우에도 마찬가지입니다.
*/

void QGCGoogleEarthView::updateWaypoint(int uas, Waypoint* wp)
{
    // Only accept waypoints in global coordinate frame	전역 좌표계에서 웨이 포인트 만 허용
    if (wp->isGlobalFrame() && wp->isNavigationType())
    {
        // We're good, this is a global waypoint	우리는 훌륭하다. 이것은 세계적인 경유지이다.

        // Get the index of this waypoint
        // note the call to getGlobalFrameAndNavTypeIndexOf()
        // as we're only handling global waypoints

/*
        // 이 웨이 포인트의 인덱스를 가져옵니다.
        // getGlobalFrameAndNavTypeIndexOf ()에 대한 호출을 기록하십시오.
        // 우리는 세계적인 경유지 만 취급하기 때문에
*/

        int wpindex = UASManager::instance()->getUASForId(uas)->getWaypointManager()->getGlobalFrameAndNavTypeIndexOf(wp);
        // If not found, return (this should never happen, but helps safety)	찾을 수없는 경우 return (절대 일어나지 않지만 안전에 도움이 됨)
        if (wpindex == -1)
        {
            return;
        }
        else
        {
            javaScript(QString("updateWaypoint(%1,%2,%3,%4,%5,%6);").arg(uas).arg(wpindex).arg(wp->getLatitude(), 0, 'f', 22).arg(wp->getLongitude(), 0, 'f', 22).arg(wp->getAltitude(), 0, 'f', 22).arg(wp->getAction()));
            //QLOG_DEBUG() << QString("updateWaypoint(%1,%2,%3,%4,%5,%6);").arg(uas).arg(wpindex).arg(wp->getLatitude(), 0, 'f', 18).arg(wp->getLongitude(), 0, 'f', 18).arg(wp->getAltitude(), 0, 'f', 18).arg(wp->getAction());
        }
    }
}

/**
 * Update the whole list of waypoints. This is e.g. necessary if the list order changed.
 * The UAS manager will emit the appropriate signal whenever updating the list
 * is necessary.
 */

/*
* 웨이 포인트 전체 목록을 업데이트하십시오. 이것은 목록 순서가 변경된 경우에 필요합니다.
 * UAS 관리자는 목록을 업데이트 할 때마다 적절한 신호를 방출합니다.
 * 필수적이다.
*/

void QGCGoogleEarthView::updateWaypointList(int uas)
{
    // Get already existing waypoints	기존 웨이 포인트 가져 오기
    UASInterface* uasInstance = UASManager::instance()->getUASForId(uas);
    if (uasInstance)
    {
        // Get all waypoints, including non-global waypoints	비 글로벌 웨이 포인트를 포함한 모든 웨이 포인트 가져 오기
        QList<Waypoint*> wpList = uasInstance->getWaypointManager()->getGlobalFrameAndNavTypeWaypointList(false);

        // Trim internal list to number of global waypoints in the waypoint manager list	웨이 포인트 매니저 목록에있는 전역 웨이 포인트의 수에 내부리스트를 트림합니다
        javaScript(QString("updateWaypointListLength(%1,%2);").arg(uas).arg(wpList.count()));

        QLOG_DEBUG() << QString("updateWaypointListLength(%1,%2);").arg(uas).arg(wpList.count());

        // Load all existing waypoints into map view	기존의 모든 웨이 포인트를 맵보기에로드합니다.
        foreach (Waypoint* wp, wpList)
        {
            updateWaypoint(uas, wp);
        }
    }
}

void QGCGoogleEarthView::updateGlobalPosition(UASInterface* uas, double lat, double lon, double alt, quint64 usec)
{
    Q_UNUSED(usec);
    javaScript(QString("addTrailPosition(%1, %2, %3, %4);").arg(uas->getUASID()).arg(lat, 0, 'f', 22).arg(lon, 0, 'f', 22).arg(alt, 0, 'f', 22));
}

void QGCGoogleEarthView::clearTrails()
{
    QList<UASInterface*> mavs = UASManager::instance()->getUASList();
    foreach (UASInterface* currMav, mavs)
    {
        javaScript(QString("clearTrail(%1);").arg(currMav->getUASID()));
    }
}

void QGCGoogleEarthView::showTrail(bool state)
{
    // Check if the current trail has to be hidden	현재 트레일을 숨겨야하는지 확인
    if (trailEnabled && !state)
    {
        QList<UASInterface*> mavs = UASManager::instance()->getUASList();
        foreach (UASInterface* currMav, mavs)
        {
            javaScript(QString("hideTrail(%1);").arg(currMav->getUASID()));
        }
    }

    // Check if the current trail has to be shown	현재 트레 일을 표시해야하는지 확인합니다.
    if (!trailEnabled && state)
    {
        QList<UASInterface*> mavs = UASManager::instance()->getUASList();
        foreach (UASInterface* currMav, mavs)
        {
            javaScript(QString("showTrail(%1);").arg(currMav->getUASID()));
        }
    }
    trailEnabled = state;
    ui->trailCheckbox->setChecked(state);
}

void QGCGoogleEarthView::showWaypoints(bool state)
{
    waypointsEnabled = state;
}

void QGCGoogleEarthView::follow(bool follow)
{
    ui->followAirplaneCheckbox->setChecked(follow);
    if (follow != followCamera)
    {
        if (follow)
        {
            setViewMode(VIEW_MODE_CHASE_LOCKED);
        }
        else
        {
            setViewMode(VIEW_MODE_SIDE);
        }
    }
    followCamera = follow;
    javaScript(QString("setFollowEnabled(%1)").arg(follow));
}

void QGCGoogleEarthView::goHome()
{
    // Disable follow and update	추적 및 업데이트 사용 중지
    follow(false);
    updateState();
    // Go to home location	집 위치로 이동
    javaScript("goHome();");
}

void QGCGoogleEarthView::setHome(double lat, double lon, double alt)
{
    QLOG_DEBUG() << "SETTING GCS HOME IN GOOGLE MAPS" << lat << lon << alt;
    javaScript(QString("setGCSHome(%1,%2,%3);").arg(lat, 0, 'f', 15).arg(lon, 0, 'f', 15).arg(alt, 0, 'f', 15));
}

void QGCGoogleEarthView::setHome()
{
    javaScript(QString("enableSetHomeMode();"));
}

void QGCGoogleEarthView::moveToPosition()
{
    bool ok;
    javaScript("sampleCurrentPosition();");
    double latitude = documentElement("currentCameraLatitude").toDouble();
    double longitude = documentElement("currentCameraLongitude").toDouble();
    QString text = QInputDialog::getText(this, tr("Please enter coordinates"),
                                         tr("Coordinates (Lat,Lon):"), QLineEdit::Normal,
                                         QString("%1,%2").arg(latitude).arg(longitude), &ok);
    if (ok && !text.isEmpty()) {
        QStringList split = text.split(",");
        if (split.length() == 2) {
            bool convert;
            double latitude = split.first().toDouble(&convert);
            ok &= convert;
            double longitude = split.last().toDouble(&convert);
            ok &= convert;

            if (ok) {
                javaScript(QString("setLookAtLatLon(%1,%2);").arg(latitude, 0, 'f', 15).arg(longitude, 0, 'f', 15));
            }
        }
    }
}

void QGCGoogleEarthView::hideEvent(QHideEvent* event)
{
    updateTimer->stop();
    QWidget::hideEvent(event);
    emit visibilityChanged(false);
}

void QGCGoogleEarthView::showEvent(QShowEvent* event)
{
    // React only to internal (pre-display)
    // events

/*
    // 내부 (사전 표시)
    // 이벤트
*/

    QWidget::showEvent(event);
    // Enable widget, initialize on first run	위젯 활성화, 첫 번째 실행시 초기화

    if (!webViewInitialized)
    {
#if (defined Q_OS_MAC)
        webViewMac->setPage(new QGCWebPage(webViewMac));
        webViewMac->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
        webViewMac->load(QUrl(QCoreApplication::applicationDirPath()+"/earth.html"));
#endif

#ifdef _MSC_VER
        //webViewWin->dynamicCall("GoHome()");
        webViewWin->dynamicCall("Navigate(const QString&)", QApplication::applicationDirPath() + "/files/images/earth.html");
#endif

        webViewInitialized = true;
        // Reloading the webpage, this resets Google Earth	웹 페이지를 다시로드하면 Google 어스가 재설정됩니다.
        gEarthInitialized = false;

        QTimer::singleShot(3000, this, SLOT(initializeGoogleEarth()));
    }
    else
    {
        updateTimer->start(refreshRateMs);
    }
    emit visibilityChanged(true);
}

void QGCGoogleEarthView::printWinException(int no, QString str1, QString str2, QString str3)
{
    QLOG_DEBUG() << no << str1 << str2 << str3;
}

QVariant QGCGoogleEarthView::javaScript(QString javaScript)
{
#ifdef Q_OS_MAC
    if (!jScriptInitialized) {
        return QVariant(false);
    } else {
        return webViewMac->page()->currentFrame()->evaluateJavaScript(javaScript);
    }
#endif
#ifdef _MSC_VER
    if(!jScriptInitialized) {
        QLOG_DEBUG() << "TOO EARLY JAVASCRIPT CALL, ABORTING";
        return QVariant(false);
    } else {
        QVariantList params;
        params.append(javaScript);
        params.append("JScript");
        QVariant result = jScriptWin->dynamicCall("execScript(QString, QString)", params);
        return result;
    }
#endif
}

QVariant QGCGoogleEarthView::documentElement(QString name)
{
#ifdef Q_OS_MAC
    QString javaScript("getGlobal(%1)");
    QVariant result = webViewMac->page()->currentFrame()->evaluateJavaScript(javaScript.arg(name));
    return result;
#endif
#ifdef _MSC_VER
    if(!jScriptInitialized) {
        QLOG_DEBUG() << "TOO EARLY JAVASCRIPT CALL, ABORTING";
    } else {
        if (documentWin) {
            QString resultString;

            // Get HTMLElement object	HTMLElement 객체를 가져옵니다.
            QVariantList params;
            IHTMLDocument3* doc;
            documentWin->queryInterface( IID_IHTMLDocument3, (void**)&doc);
            params.append(name);
            IHTMLElement* element = NULL;
            // Append alias	별칭 추가
            name.prepend("JScript_");
            HRESULT res = doc->getElementById(QStringToBSTR(name), &element);
            //BSTR elemString;
            if (SUCCEEDED(res) && element) {
                //element->get_innerHTML(&elemString);
                VARIANT var;
                var.vt = VT_BSTR;
                HRESULT res = element->getAttribute(L"value", 0, &var);
                if (SUCCEEDED(res) && (var.vt != VT_NULL)) {
                    QByteArray typeName;
                    QVariant qtValue = VARIANTToQVariant(var,typeName);
                    return qtValue;
                } else {
                    QLOG_DEBUG() << __FILE__ << __LINE__ << "JAVASCRIPT ATTRIBUTE" << name << "NOT FOUND";
                }
            } else {
                QLOG_DEBUG() << __FILE__ << __LINE__ << "DID NOT GET HTML ELEMENT" << name;
            }
        }
    }
    return QVariant(0);
#endif
}

void QGCGoogleEarthView::initializeGoogleEarth()
{
    if (!jScriptInitialized) {
#ifdef Q_OS_MAC
        jScriptInitialized = true;
#endif
#ifdef _MSC_VER
        QAxObject* doc = webViewWin->querySubObject("Document()");
        //IDispatch* Disp;
        IDispatch* winDoc = NULL;
        IHTMLDocument2* document = NULL;

        //332C4425-26CB-11D0-B483-00C04FD90119 IHTMLDocument2
        //25336920-03F9-11CF-8FD0-00AA00686F13 HTMLDocument
        doc->queryInterface(QUuid("{332C4425-26CB-11D0-B483-00C04FD90119}"), (void**)(&winDoc));
        if (winDoc) {
            document = NULL;
            winDoc->QueryInterface( IID_IHTMLDocument2, (void**)&document );
            IHTMLWindow2 *window = NULL;
            document->get_parentWindow( &window );
            documentWin = new QAxObject(document, webViewWin);
            jScriptWin = new QAxObject(window, webViewWin);
            connect(jScriptWin, SIGNAL(exception(int,QString,QString,QString)), this, SLOT(printWinException(int,QString,QString,QString)));
            jScriptInitialized = true;
        } else {
            QLOG_DEBUG() << "COULD NOT GET DOCUMENT OBJECT! Aborting";
        }
#endif
        QTimer::singleShot(1500, this, SLOT(initializeGoogleEarth()));
        return;
    }

    if (!gEarthInitialized) {
        if (!documentElement("initialized").toBool()) {
            QTimer::singleShot(300, this, SLOT(initializeGoogleEarth()));
            QLOG_DEBUG() << "NOT INITIALIZED, WAITING";
        } else {
            gEarthInitialized = true;

            // Set home location	집 위치 설정
            setHome(UASManager::instance()->getHomeLatitude(), UASManager::instance()->getHomeLongitude(), UASManager::instance()->getHomeAltitude());

            // Add all MAVs	모든 MAV 추가
            QList<UASInterface*> mavs = UASManager::instance()->getUASList();
            foreach (UASInterface* currMav, mavs) {
                addUAS(currMav);
            }

            // Set current UAS	현재 UAS 설정
            setActiveUAS(UASManager::instance()->getActiveUAS());

            // Add any further MAV automatically	추가로 MAV를 자동으로 추가합니다.
            connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(addUAS(UASInterface*)), Qt::UniqueConnection);
            connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)), Qt::UniqueConnection);

            // Connect UI signals/slots	 UI 신호 / 슬롯 연결

            // Follow checkbox	체크 박스를 따른다.
            ui->followAirplaneCheckbox->setChecked(followCamera);
            connect(ui->followAirplaneCheckbox, SIGNAL(toggled(bool)), this, SLOT(follow(bool)), Qt::UniqueConnection);

            // Trail checkbox	흔적 확인란
            ui->trailCheckbox->setChecked(trailEnabled);
            connect(ui->trailCheckbox, SIGNAL(toggled(bool)), this, SLOT(showTrail(bool)), Qt::UniqueConnection);

            // Go home	집에 가라.
            connect(ui->goHomeButton, SIGNAL(clicked()), this, SLOT(goHome()));
            // Set home	 집에 설정
            connect(ui->setHomeButton, SIGNAL(clicked()), this, SLOT(setHome()));

            // Visibility of set home button	홈 버튼 설정 가시성
            connect(ui->editButton, SIGNAL(clicked(bool)), ui->setHomeButton, SLOT(setVisible(bool)));
            ui->setHomeButton->setVisible(ui->editButton->isChecked());

            // To Lat/Lon button	Lat / Lon 버튼으로 이동
            connect(ui->toLatLonButton, SIGNAL(clicked()), this, SLOT(moveToPosition()));

            // Cam distance slider	캠 거리 슬라이더
            connect(ui->camDistanceSlider, SIGNAL(valueChanged(int)), this, SLOT(setViewRangeScaledInt(int)), Qt::UniqueConnection);
            setViewRangeScaledInt(ui->camDistanceSlider->value());

            // Distance combo box	거리 콤보 상자
            connect(ui->camDistanceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setDistanceMode(int)), Qt::UniqueConnection);
            // Edit mode button		모드 수정 버튼
            connect(ui->editButton, SIGNAL(clicked(bool)), this, SLOT(enableEditMode(bool)), Qt::UniqueConnection);

            // Update waypoint list	 웨이 포인트 목록 업데이트
            if (mav) updateWaypointList(mav->getUASID());

            // Start update timer	업데이트 타이머를 시작합니다.
            updateTimer->start(refreshRateMs);

            // Set current view mode	현재보기 모드 설정
            setViewMode(currentViewMode);
            setDistanceMode(ui->camDistanceComboBox->currentIndex());
            enableEditMode(ui->editButton->isChecked());
            enableAtmosphere(ui->atmosphereCheckBox->isChecked());
            enableDaylight(ui->daylightCheckBox->isChecked());
            follow(this->followCamera);

            // Move to home location	집 위치로 이동
            goHome();
        }
    }
}

void QGCGoogleEarthView::updateState()
{
#if (QGC_EVENTLOOP_DEBUG)
    QLOG_DEBUG() << "EVENTLOOP:" << __FILE__ << __LINE__;
#endif
    if (gEarthInitialized)
    {
        int uasId = 0;
        double lat = 47.3769;
        double lon = 8.549444;
        double alt = 470.0;

        float roll = 0.0f;
        float pitch = 0.0f;
        float yaw = 0.0f;

        // Update all MAVs	모든 MAV 업데이트
        QList<UASInterface*> mavs = UASManager::instance()->getUASList();
        foreach (UASInterface* currMav, mavs)
        {
            // Only update if known	알려진 경우에만 업데이트
            if (!currMav->globalPositionKnown()) continue;
            uasId = currMav->getUASID();
            lat = currMav->getLatitude();
            lon = currMav->getLongitude();
            alt = currMav->getAltitude();
            roll = currMav->getRoll();
            pitch = currMav->getPitch();
            yaw = currMav->getYaw();

            //QLOG_DEBUG() << "SETTING POSITION FOR" << uasId << lat << lon << alt << roll << pitch << yaw;

/*
            // QLOG_DEBUG () << "위치 설정"<< uasId << lat << lon << alt << roll << pitch << yaw;
*/


            javaScript(QString("setAircraftPositionAttitude(%1, %2, %3, %4, %6, %7, %8);")
                       .arg(uasId)
                       .arg(lat, 0, 'f', 22)
                       .arg(lon, 0, 'f', 22)
                       .arg(alt, 0, 'f', 22)
                       .arg(roll, 0, 'f', 9)
                       .arg(pitch, 0, 'f', 9)
                       .arg(yaw, 0, 'f', 9));
        }


        // Read out new waypoint positions and waypoint create events
        // this is polling (bad) but forced because of the crappy
        // Microsoft API available in Qt - improvements wanted

        // First check if a new WP should be created

/*
        // 새로운 웨이 포인트 위치 및 웨이 포인트 생성 이벤트 읽기
        // 이것은 폴링 (나쁜)이지만 엉터리 때문에 강제됩니다.
        // Qt에서 사용할 수있는 Microsoft API - 개선 된 기능

        // 새로운 WP가 생성되어야하는지 먼저 체크한다.
*/

        bool newWaypointPending = documentElement("newWaypointPending").toBool();
        if (newWaypointPending)
        {
            bool coordsOk = true;
            bool ok;
            double latitude = documentElement("newWaypointLatitude").toDouble(&ok);
            coordsOk &= ok;
            double longitude = documentElement("newWaypointLongitude").toDouble(&ok);
            coordsOk &= ok;
            double altitude = documentElement("newWaypointAltitude").toDouble(&ok);
            coordsOk &= ok;
            if (coordsOk)
            {
                // Add new waypoint	새로운 웨이 포인트 추가
                if (mav)
                {
                    Waypoint* wp = mav->getWaypointManager()->createWaypoint();
                    wp->setFrame(MAV_FRAME_GLOBAL);
                    wp->setAction(MAV_CMD_NAV_WAYPOINT);
                    wp->setLatitude(latitude);
                    wp->setLongitude(longitude);
                    wp->setAltitude(altitude);
                    wp->setAcceptanceRadius(10.0); // 10 m
                }
            }
            javaScript("setNewWaypointPending(false);");
        }

        // Check if a waypoint should be moved	웨이 포인트가 이동해야하는지 확인
        bool dragWaypointPending = documentElement("dragWaypointPending").toBool();

        if (dragWaypointPending)
        {
            bool coordsOk = true;
            bool ok;
            double latitude = documentElement("dragWaypointLatitude").toDouble(&ok);
            coordsOk &= ok;
            double longitude = documentElement("dragWaypointLongitude").toDouble(&ok);
            coordsOk &= ok;
            double altitude = documentElement("dragWaypointAltitude").toDouble(&ok);
            coordsOk &= ok;

            // UPDATE WAYPOINTS, HOME LOCATION AND OTHER LOCATIONS	길 찾기, 집 위치 및 기타 위치 업데이트
            if (coordsOk)
            {
                QString idText = documentElement("dragWaypointIndex").toString();
                if (idText == "HOME")
                {
                    QLOG_DEBUG() << "HOME UPDATED!";
                    UASManager::instance()->setHomePosition(latitude, longitude, altitude);
                    ui->setHomeButton->setChecked(false);
                }
                else
                {
                    // Update waypoint or symbol	 웨이 포인트 또는 심볼 업데이트
                    if (mav)
                    {
                        QList<Waypoint*> wps = mav->getWaypointManager()->getGlobalFrameAndNavTypeWaypointList(false);

                        bool ok;
                        int index = idText.toInt(&ok);

                        if (ok && index >= 0 && index < wps.count())
                        {
                            Waypoint* wp = wps.at(index);
                            wp->setLatitude(latitude);
                            wp->setLongitude(longitude);
                            wp->setAltitude(altitude);
                            mav->getWaypointManager()->notifyOfChangeEditable(wp);
                        }
                    }
                }
            }
            else
            {
                // If coords were not ok, move the view in google earth back
                // to last acceptable location

/*
                // 좌표가 맞지 않으면 google 어스에서보기를 뒤로 이동합니다.
                // 허용되는 위치를 마지막으로 지정합니다.
*/

                updateWaypointList(mav->getUASID());
            }
            javaScript("setDragWaypointPending(false);");
        }
    }
}


void QGCGoogleEarthView::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
