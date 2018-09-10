/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009 - 2011 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

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
 *   @brief Main executable
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include "QGCCore.h"
#include "MainWindow.h"
#include "configuration.h"
#include "logging.h"
#include <QtWidgets/QApplication>
#include <fstream>

#include <mavlink_types.h>

/* SDL does ugly things to main() 	 SDL은 main ()에 추악한 일을한다  */
#ifdef main
#undef main
#endif

// Create the base logging category as defined in logging.h	  logging.h에 정의 된 기본 로깅 범주를 만듭니다.  
Q_LOGGING_CATEGORY(apmGeneral, "apm.general");

// Install a message handler so you do not need
// the MSFT debug tools installed to se
// qDebug(), qWarning(), qCritical and qAbort

/*
// 필요없는 메시지 핸들러를 설치하십시오.
// 설치되어있는 MSFT 디버그 도구
// qDebug (), qWarning (), qCritical 및 qAbort
*/

#ifdef Q_OS_WIN
void msgHandler( QtMsgType type, const char* msg )
{
    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = QString("[%1] %2").arg( symbols[type] ).arg( msg );
    std::cerr << output.toStdString() << std::endl;
    if( type == QtFatalMsg ) abort();
}
#endif

// Global status structures for mavlink protocol	 mavlink 프로토콜의 전역 상태 구조  
mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS];

// Path for file logging	 파일 로깅을위한 경로  
static QString sLogPath;

// Message handler for logging provides console and file output
// The handler itself has to be reentrant and threadsafe!

/*
// 콘솔 및 파일 출력을 제공하는 로깅 용 메시지 처리기
// 핸들러 자체는 재진입 및 threadsafe가되어야합니다!
*/

void loggingMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    // The message handler has to be thread safe

/*
    // 메시지 처리기는 스레드로부터 안전해야합니다.
*/

    static QMutex mutex;
    QMutexLocker localLoc(&mutex);

    static std::ofstream logFile(sLogPath.toStdString().c_str(), std::ofstream::out | std::ofstream::app);

    QString outMessage(qFormatLogMessage(type, context, message));  // just format only once	  한 번만 포맷하십시오. 
    if(logFile)
    {
        logFile << qPrintable(outMessage) << std::endl; // log to file	 파일에 기록  
    }

    LogWindowSingleton::instance().write(outMessage);   // log to debug window	 디버그 창에 기록  

    fprintf(stderr, "%s\n", qPrintable(outMessage));    // log to console	 콘솔에 기록  
}


/**
 * @brief Starts the application
 *
 * @param argc Number of commandline arguments
 * @param argv Commandline arguments
 * @return exit code, 0 for normal exit and !=0 for error cases
 */

/*
 * @brief 응용 프로그램을 시작합니다.
 *
 * @param argc 명령 행 인수의 수
 * @param argv 명령 줄 인수
 * @return 종료 코드, 정상 종료의 경우 0, 오류 케이스의 경우! = 0
*/

int main(int argc, char *argv[])
{
// install the message handler	 메시지 처리기를 설치합니다.  
#ifdef Q_OS_WIN
    //qInstallMsgHandler( msgHandler );
#endif

#ifdef Q_OS_LINUX
    // Part of a fix for "#646 Primary Flight Display acts as a CPU hog..." wich consumed lots
    // of cpu cylcles when APM-Plannner is used on machines with Intel Graphics.
    // The complete fix needs the environment variable "QSG_RENDER_LOOP=threaded" to be set before
    // APM-Planner is started in order to work correctly.
    // Be aware that setting only the environment variable seems to fix the problem, but without
    // this code change the application could crash or hang after a while.
    // see https://forum.qt.io/topic/68721/high-cpu-usage/4
    // MUST be called before construction of QApplication - in our case QGCCore.

/*
    // "# 646 Primary Flight Display가 CPU 호그 역할을합니다 ..."에 대한 수정 사항 중 일부가 많이 소비되었습니다.
    // Intel Graphics가있는 컴퓨터에서 APM-Plannner를 사용할 때 CPU 순환 횟수.
    // 완전한 수정은 "QSG_RENDER_LOOP = threaded"환경 변수가 필요합니다.
    // 올바르게 작동하려면 APM-Planner가 시작됩니다.
    // 환경 변수 만 설정하면 문제가 해결되는 것 같지만
    // 이 코드를 변경하면 응용 프로그램이 충돌하거나 잠시 멈출 수 있습니다.
    // https://forum.qt.io/topic/68721/high-cpu-usage/4를 참조하십시오.
    // QApplication을 생성하기 전에 반드시 호출해야합니다 - 우리의 경우 QGCCore.
*/

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
#endif

    // Init application	 응용 프로그램 초기화  
    QGCCore core(argc, argv);

    // Init logging
    // create filename and path for logfile like "apmlog_20160529.txt"
    // one logfile for every day. Size is not limited

/*
    // 로깅 초기화
    // "apmlog_20160529.txt"와 같은 로그 파일의 파일 이름과 경로를 만듭니다.
    // 매일 하나의 로그 파일. 크기는 제한되지 않습니다.
*/

    QString logFileName("apmlog_");
    logFileName.append(QDateTime::currentDateTime().toString("yyyyMMdd"));
    logFileName.append(".txt");
    sLogPath = QString(QDir(QGC::appDataDirectory()).filePath(logFileName));

    // Just keep the 5 recent logfiles and delete the rest.	 최근 로그 파일 5 개를 유지하고 나머지는 삭제하십시오.  
    QDir logDirectory(QGC::appDataDirectory(), "apmlog*", QDir::Name, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QStringList logFileList(logDirectory.entryList());
    // As the file list is sorted we can delete index 0 cause its the oldest one	 파일 목록이 정렬되면 인덱스 0을 삭제할 수 있습니다.  
    while(logFileList.size() > 5)
    {
        logDirectory.remove(logFileList.at(0));
        logFileList.pop_front();
    }

    // Add sperator for better orientation in Logfiles	 로그 파일에서보다 나은 오리엔테이션을위한 sperator 추가  
    std::ofstream logFile(sLogPath.toStdString().c_str(), std::ofstream::out | std::ofstream::app);
    if (logFile)
    {
        logFile << std::endl << std::endl << "**************************************************" << std::endl << std::endl;
        logFile.close();
    }

    // set up logging pattern	 로깅 패턴 설정  
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    // QT < 5.5.x does not support qInfo() logging macro and no info-formatting too	 QT <5.5.x는 qInfo () 로깅 매크로를 지원하지 않으며 정보 형식도 지원하지 않습니다.  
    QString logPattern("[%{time yyyyMMdd h:mm:ss.zzz} %{if-debug}DEBUG%{endif}%{if-warning}WARN %{endif}%{if-critical}ERROR%{endif}%{if-fatal}FATAL%{endif}] - %{message}");
#else
    QString logPattern("[%{time yyyyMMdd h:mm:ss.zzz} %{if-debug}DEBUG%{endif}%{if-info}INFO %{endif}%{if-warning}WARN %{endif}%{if-critical}ERROR%{endif}%{if-fatal}FATAL%{endif}] - %{message}");
#endif

    qSetMessagePattern(logPattern);

    // install the message handler for logging	 로깅을위한 메시지 핸들러 설치  
    qInstallMessageHandler(loggingMessageHandler);

    // Setup output for logging category	  로깅 범주에 대한 출력 설정 
    QLoggingCategory::setFilterRules(QStringLiteral("apm.general.debug=true"));

    // start the application	  응용 프로그램을 시작합니다  
    core.initialize();
    return core.exec();
}
