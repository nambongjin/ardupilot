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
 *   @brief Implementation of class QGCCore
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/**
 * @file
 * 클래스 QGCCore의 구현
 *
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include "QGCCore.h"
#include "logging.h"
#include "configuration.h"
#include "QGC.h"
#include "MainWindow.h"
#include "GAudioOutput.h"

#ifdef OPAL_RT
#include "OpalLink.h"
#endif
#include "UDPLink.h"
#include "MAVLinkSimulationLink.h"

#include <QFile>
#include <QFlags>
#include <QThread>
#include <QSplashScreen>
#include <QPixmap>
#include <QDesktopWidget>
#include <QPainter>
#include <QStyleFactory>
#include <QAction>

/**
 * @brief Constructor for the main application.
 *
 * This constructor initializes and starts the whole application. It takes standard
 * command-line parameters
 *
 * @param argc The number of command-line parameters
 * @param argv The string array of parameters
 **/
/**
 * @brief 메인 어플리케이션의 생성자.
 *
 * 이 생성자는 전체 응용 프로그램을 초기화하고 시작합니다. 그것은 표준을 취한다.
 * 명령 줄 매개 변수
 *
 * @param argc 명령 줄 매개 변수 수
 * @param argv 파라미터의 캐릭터 라인 배열
**/


QGCCore::QGCCore(int &argc, char* argv[]) : QApplication(argc, argv)
{
    // Set settings format
    // 설정 형식 설정
    QSettings::setDefaultFormat(QSettings::IniFormat);

    // Set application name
    // 애플리케이션 이름 설정
    this->setApplicationName(QGC_APPLICATION_NAME);
    this->setApplicationVersion(QGC_APPLICATION_VERSION);
    this->setOrganizationName(QLatin1String("ardupilot"));
    this->setOrganizationDomain("org.ardupilot");

    m_mouseWheelFilter = new QGCMouseWheelEventFilter(this);

    connect(this, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));
}

void QGCCore::aboutToQuit()
{
    LinkManager::instance()->shutdown();
}

void QGCCore::initialize()
{
    QLOG_INFO() << "QGCCore::initialize()";
    QLOG_INFO() << "Current Build Info";
    QLOG_INFO() << "Git Hash:" << define2string(GIT_HASH);
    QLOG_INFO() << "Git Commit:" << define2string(GIT_COMMIT);
    QLOG_INFO() << "APPLICATION_NAME:" << define2string(QGC_APPLICATION_NAME);
    QLOG_INFO() << "APPLICATION_VERSION:" << define2string(QGC_APPLICATION_VERSION);
    QLOG_INFO() << "APP_PLATFORM:" << define2string(APP_PLATFORM);
    QLOG_INFO() << "APP_TYPE:" << define2string(APP_TYPE);


    // Check application settings
    // clear them if they mismatch
    // QGC then falls back to default
    // 응용 프로그램 설정을 확인하십시오.
    // 불일치가 있으면 지우기
    // QGC는 기본값으로 되돌아갑니다. 
    QSettings settings;

    // Show user an upgrade message if QGC got upgraded (see code below, after splash screen)
    // QGC가 업그레이드 된 경우 사용자에게 업그레이드 메시지를 표시합니다 (아래 코드, 시작 화면 후 참조).
    bool upgraded = false;
    QString lastApplicationVersion;
    if (settings.contains("QGC_APPLICATION_VERSION"))
    {
        QString qgcVersion = settings.value("QGC_APPLICATION_VERSION").toString();
        if (qgcVersion != QGC_APPLICATION_VERSION)
        {
            settings.beginGroup("AUTO_UPDATE");
            bool autoUpdateEnabled = settings.value("ENABLED", true).toBool();
            QString releaseType = settings.value("RELEASE_TYPE", define2string(APP_TYPE)).toString();
            settings.endGroup();

            lastApplicationVersion = qgcVersion;
            settings.clear();
            // Write current application version & update settings.
            // 현재 응용 프로그램 버전을 쓰고 설정을 업데이트합니다.
            settings.setValue("QGC_APPLICATION_VERSION", QGC_APPLICATION_VERSION);
            settings.beginGroup("AUTO_UPDATE");
            settings.setValue("ENABLED",autoUpdateEnabled);
            settings.setValue("RELEASE_TYPE", releaseType);
            settings.endGroup();
            upgraded = true;
        }
    }
    else
    {
        // If application version is not set, clear settings anyway
        // 응용 프로그램 버전이 설정되지 않은 경우 설정을 지우십시오.
        settings.clear();
        // Write current application version
        // 현재 응용 프로그램 버전 쓰기
        settings.setValue("QGC_APPLICATION_VERSION", QGC_APPLICATION_VERSION);
    }
    //settings.clear();
    settings.sync();


    // Show splash screen
    // 스플래시 화면 표시
    QPixmap splashImage(":/files/images/apm_planner_2_0-07.png");
    QSplashScreen* splashScreen = new QSplashScreen(splashImage);
    // Delete splash screen after mainWindow was displayed
    // mainWindow가 표시된 후에 시작 화면 삭제
    splashScreen->setAttribute(Qt::WA_DeleteOnClose);
    splashScreen->show();
    processEvents();
    splashScreen->showMessage(tr("Loading application fonts"), Qt::AlignLeft | Qt::AlignBottom, QColor(62, 93, 141));

    // Exit main application when last window is closed
    // 마지막 창을 닫을 때 메인 애플리케이션 종료
    connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));

    // Load application font
    // 응용 프로그램 글꼴로드
    QFontDatabase fontDatabase;
    const QString fontFileName(":/general/vera.ttf"); ///< Font file is part of the QRC file and compiled into the app
                                                      /// <글꼴 파일은 QRC 파일의 일부이며 앱에 컴파일됩니다.
    //const QString fontFamilyName = "Bitstream Vera Sans";
    if(!QFile::exists(fontFileName)) printf("ERROR! font file: %s DOES NOT EXIST!\n", fontFileName.toStdString().c_str());
    fontDatabase.addApplicationFont(fontFileName);
    // Avoid Using setFont(). In the Qt docu you can read the following:
    //     "Warning: Do not use this function in conjunction with Qt Style Sheets."
    // setFont(fontDatabase.font(fontFamilyName, "Roman", 12));
    // setFont () 사용을 피하십시오. Qt docu에서 다음을 읽을 수 있습니다 :
    //      "경고 : Qt 스타일 시트와 함께이 함수를 사용하지 마십시오."

    // Start the comm link manager
    // comm 링크 관리자를 시작합니다.
    splashScreen->showMessage(tr("Starting Communication Links"), Qt::AlignLeft | Qt::AlignBottom, QColor(62, 93, 141));
    startLinkManager();

    // Start the UAS Manager
    // UAS 관리자를 시작합니다.
    splashScreen->showMessage(tr("Starting UAS Manager"), Qt::AlignLeft | Qt::AlignBottom, QColor(62, 93, 141));
    startUASManager();

    // Start the user interface
    // 사용자 인터페이스를 시작합니다.
    splashScreen->showMessage(tr("Starting User Interface"), Qt::AlignLeft | Qt::AlignBottom, QColor(62, 93, 141));
    // Start UI

    // Connect links
    // to make sure that all components are initialized when the
    // first messages arrive
    //UDPLink* udpLink = new UDPLink(QHostAddress::Any, 14550);
    //MainWindow::instance()->addLink(udpLink);
    // Listen on Multicast-Address 239.255.77.77, Port 14550
    //QHostAddress * multicast_udp = new QHostAddress("239.255.77.77");
    //UDPLink* udpLink = new UDPLink(*multicast_udp, 14550);

    // UI 시작

    // 링크 연결
    // 모든 구성 요소가 초기화 될 때
    // 첫 번째 메시지 도착
    // UDPLink * udpLink = 새로운 UDPLink (QHostAddress :: Any, 14550);
    // MainWindow :: instance () -> addLink (udpLink);
    // 멀티 캐스트 주소 239.255.77.77, 포트 14550 수신 대기
    // QHostAddress * multicast_udp = 새로운 QHostAddress ( "239.255.77.77");
    // UDPLink * udpLink = 새로운 UDPLink (* multicast_udp, 14550);

#ifdef OPAL_RT
    // Add OpalRT Link, but do not connect
    // OpalRT Link를 추가하지만 연결하지 않습니다.
    OpalLink* opalLink = new OpalLink();
    MainWindow::instance()->addLink(opalLink);
#endif
#ifdef SIMULATION_LINK
    MAVLinkSimulationLink* simulationLink = new MAVLinkSimulationLink(":/demo-log.txt");
    simulationLink->disconnect();
#endif



    mainWindow = MainWindow::instance(splashScreen);

    // Remove splash screen
    // 스플래시 화면 제거
    splashScreen->finish(mainWindow);

    if (upgraded) mainWindow->showInfoMessage(tr("Default Settings Loaded"),
                                              tr("APM Planner has been upgraded from version %1 to version %2. Some of your user preferences have been reset to defaults for safety reasons. Please adjust them where needed.").arg(lastApplicationVersion).arg(QGC_APPLICATION_VERSION));

}

/**
 * @brief Destructor for the groundstation. It destroys all loaded instances.
 *
 **/
/**
 * @brief 지상국을위한 소멸자. 그것은로드 된 모든 인스턴스를 파괴합니다.
 *
**/
QGCCore::~QGCCore()
{
    QGC::saveSettings();
    QGC::close();
    // Delete singletons
    // First systems
    // 싱글 톤 삭제
    // 첫 번째 시스템
    delete UASManager::instance();
    // then links

    // Finally the main window
    //delete MainWindow::instance();
    //The main window now autodeletes on close.
    // 그런 다음 링크

    // 마지막으로 메인 윈도우
    // MainWindow :: instance ()를 삭제하십시오;
    // 메인 윈도우는 닫을 때 자동 완성됩니다.
}

/**
 * @brief Start the link managing component.
 *
 * The link manager keeps track of all communication links and provides the global
 * packet queue. It is the main communication hub
 **/
/**
* @brief 링크 관리 구성 요소를 시작하십시오.
*
* 링크 관리자는 모든 통신 링크를 추적하고 전역 통신 링크를 제공합니다.
* 패킷 대기열. 주요 통신 허브입니다.
**/
void QGCCore::startLinkManager()
{
    QLOG_INFO() << "Start Link Manager";
    LinkManager::instance();
}

/**
 * @brief Start the Unmanned Air System Manager
 *
 **/
/**
 *무인 항공 시스템 관리자 시작
 *
 **/
void QGCCore::startUASManager()
{
    QLOG_INFO() << "Start UAS Manager";
    // Load UAS plugins
    // UAS 플러그인로드
    QDir pluginsDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_LINUX)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

    UASManager::instance();

    // Load plugins
    // 플러그인을로드하십시오.

    QStringList pluginFileNames;

    foreach (const QString& fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            //populateMenus(plugin);
            pluginFileNames += fileName;
            //printf(QString("Loaded plugin from " + fileName + "\n").toStdString().c_str());
        }
    }
}


