#ifndef QGCGOOGLEEARTHVIEW_H
#define QGCGOOGLEEARTHVIEW_H

#include <QWidget>
#include <QTimer>
#include <UASInterface.h>

#if (defined Q_OS_MAC)
#include <QWebView>
#endif

#ifdef _MSC_VER
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>
#include "windows.h"

class QGCWebAxWidget : public QAxWidget
{
public:
    //Q_OBJECT
    QGCWebAxWidget(QWidget* parent = 0, Qt::WindowFlags f = 0)
        : QAxWidget(parent, f)/*,
		_document(NULL)*/
    {
        // Set web browser control	웹 브라우저 컨트롤 설정
        setControl("{8856F961-340A-11D0-A96B-00C04FD705A2}");
        // WARNING: Makes it impossible to actually debug javascript. But useful in production mode	경고 : 자바 스크립트를 실제로 디버그하는 것을 불가능하게 만든다. 그러나 프로덕션 모드에서 유용합니다.
        setProperty("ScriptErrorsSuppressed", true);
        // see: http://www.codeproject.com/KB/cpp/ExtendedWebBrowser.aspx?fid=285594&df=90&mpp=25&noise=3&sort=Position&view=Quick&fr=151#GoalScriptError

        //this->dynamicCall("setProperty(const QString&,
        //QObject::connect(this, SIGNAL(DocumentComplete(IDispatch*, QVariant&)), this, SLOT(setDocument(IDispatch*, QVariant&)));


    }
    /*
    QAxObject* document()
    {
    	return _document;
    }*/

protected:
    /*
    void setDocument(IDispatch* dispatch, QVariant& variant)
    {
    	_document = this->querySubObject("Document()");
    }
    QAxObject* _document;*/
    virtual bool translateKeyEvent(int message, int keycode) const {
        if (message >= WM_KEYFIRST && message <= WM_KEYLAST)
            return true;
        else
            return QAxWidget::translateKeyEvent(message, keycode);
    }

};
#endif

namespace Ui
{
class QGCGoogleEarthView;
}

class Waypoint;

class QGCGoogleEarthView : public QWidget
{
    Q_OBJECT

public:
    explicit QGCGoogleEarthView(QWidget *parent = 0);
    ~QGCGoogleEarthView();

    enum VIEW_MODE {
        VIEW_MODE_SIDE = 0, ///< View from above, orientation is free	<위에서보기, 방향은 무료입니다.
        VIEW_MODE_MAP, ///< View from above, orientation is north (map view)	<위에서보기, 방향이 북쪽 (맵보기)
        VIEW_MODE_CHASE_LOCKED, ///< Locked chase camera	<잠긴 추적 카메라
        VIEW_MODE_CHASE_FREE, ///< Position is chasing object, but view can rotate around object	<위치는 객체를 쫓고 있지만 뷰는 객체를 중심으로 회전 할 수 있습니다.
    };

public slots:
    /** @brief Update the internal state. Does not trigger a redraw 	 / * * @ brief 내부 상태를 업데이트합니다. 다시 그리기를 트리거하지 않습니다 * /*/
    void updateState();
    /** @brief Add a new MAV/UAS to the visualization	 / * * @brief 시각화에 새로운 MAV / UAS 추가 * / */
    void addUAS(UASInterface* uas);
    /** @brief Set the currently selected UAS 	 / * * @ brief 현재 선택된 UAS를 설정합니다 * /*/
    void setActiveUAS(UASInterface* uas);
    /** @brief Update the global position 	/ * * 글로벌 위치 업데이트 * /*/
    void updateGlobalPosition(UASInterface* uas, double lat, double lon, double alt, quint64 usec);
    /** @brief Update a single waypoint 	 / * * @ brief 단일 웨이 포인트 업데이트 * /*/
    void updateWaypoint(int uas, Waypoint* wp);
    /** @brief Update the waypoint list 	 / * * @ brief 웨이 포인트 목록 업데이트 * /*/
    void updateWaypointList(int uas);
    /** @brief Show the vehicle trail 	 * * brief 차량 흔적 표시 * /*/
    void showTrail(bool state);
    /** @brief Clear the current vehicle trails and start with new ones	/ * * brief 현재 차량 트레일을 지우고 새로운 차량 트레일을 시작하십시오 * / */
    void clearTrails();
    /** @brief Show the waypoints 	/ * * brief 경유지 표시 * /*/
    void showWaypoints(bool state);
    /** @brief Follow the aircraft during flight 	 / * * brief 비행 중에 항공기를 따라 가십시오 * /*/
    void follow(bool follow);
    /** @brief Go to the home location	 / * * brief 집 위치로 이동 * / */
    void goHome();
    /** @brief Set the home location 	/ * * @brief 집 위치 설정 * /*/
    void setHome(double lat, double lon, double alt);
    /** @brief Set the home location interactively in the UI 	 / * * @ brief UI에서 대화 형으로 홈 위치 설정 * /*/
    void setHome();
    /** @brief Move the view to a latitude / longitude position 	/ * * brief보기를 위도 / 경도 위치로 이동시킵니다. * /*/
    void moveToPosition();
    /** @brief Allow waypoint editing	/ * * brief 웨이 포인트 수정 허용 * / */
    void enableEditMode(bool mode);
    /** @brief Enable daylight/night	/ * * brief 일광 / 야간 활성화 * / */
    void enableDaylight(bool enable);
    /** @brief Enable atmosphere 	 / * * brief 대기 사용 가능 * /*/
    void enableAtmosphere(bool enable);
    /** @brief Set camera view range to aircraft in meters 	/ * * brief 카메라 뷰 범위를 미터 단위로 항공기로 설정 * /*/
    void setViewRange(float range);
    /** @brief Set the distance mode - either to ground or to MAV 	/ * * / brief 거리 모드를 접지 또는 MAV로 설정 * /*/
    void setDistanceMode(int mode);
    /** @brief Set the view mode	/ * * @ brief보기 모드를 설정합니다 * / */
    void setViewMode(VIEW_MODE mode);
    /** @brief Toggle through the different view modes	 / * * @ brief 다른보기 모드로 전환합니다 * / */
    void toggleViewMode();
    /** @brief Set camera view range to aircraft in centimeters 	 / * * brief 카메라 뷰 범위를 센티미터 단위로 항공기로 설정 * /*/
    void setViewRangeScaledInt(int range);
    /** @brief Reset Google Earth View 	 / * * @ brief Google 어스보기 재설정 * /*/
    void reloadHTML();

    /** @brief Initialize Google Earth 	  / * * @ brief Google 어스 초기화 * /*/
    void initializeGoogleEarth();
    /** @brief Print a Windows exception	/ * * @brief Windows 예외 인쇄 * / */
    void printWinException(int no, QString str1, QString str2, QString str3);

public:
    /** @brief Execute java script inside the Google Earth window 	/ * * @ brief Google 어스 창에서 자바 스크립트 실행 * /*/
    QVariant javaScript(QString javascript);
    /** @brief Get a document element 	 / * * 문서 요소 가져 오기 * /*/
    QVariant documentElement(QString name);

signals:
    void visibilityChanged(bool visible);

protected:
    void changeEvent(QEvent *e);
    QTimer* updateTimer;
    int refreshRateMs;
    UASInterface* mav;
    bool followCamera;
    bool trailEnabled;
    bool waypointsEnabled;
    bool webViewInitialized;
    bool jScriptInitialized;
    bool gEarthInitialized;
    VIEW_MODE currentViewMode;
#ifdef _MSC_VER
    QGCWebAxWidget* webViewWin;
    QAxObject* jScriptWin;
    QAxObject* documentWin;
#endif
#if (defined Q_OS_MAC)
    QWebView* webViewMac;
#endif

    /** @brief Start widget updating 	 / * * brief 위젯 업데이트 시작 * /*/
    void showEvent(QShowEvent* event);
    /** @brief Stop widget updating	/ * * brief 위젯 업데이트 중지 * / */
    void hideEvent(QHideEvent* event);

private:
#ifdef _MSC_VER
    Ui::QGCGoogleEarthView* ui;
#else
    Ui::QGCGoogleEarthView* ui;
#endif
};

#endif // QGCGOOGLEEARTHVIEW_H
