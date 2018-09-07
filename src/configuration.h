#ifndef QGC_CONFIGURATION_H
#define QGC_CONFIGURATION_H

#include "globalobject.h"
#include <QString>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>

/** @brief Polling interval in ms */
/** brief 폴링 간격 (ms) */
#define SERIAL_POLL_INTERVAL 100

/** @brief Heartbeat emission rate, in Hertz (times per second) */
/** brief 하트 비트 방출 속도 (단위 : 초) */
#define MAVLINK_HEARTBEAT_DEFAULT_RATE 1
#define WITH_TEXT_TO_SPEECH 1

#define QGC_APPLICATION_NAME "APM Planner"
#define QGC_APPLICATION_VERSION "v2.0.26-rc2"
#define APP_DATA_DIRECTORY "/apmplanner2"
#define LOG_DIRECTORY "/dataflashLogs"
#define PARAMETER_DIRECTORY "/parameters"
#define MISSION_DIRECTORY "/missions"
#define MAVLINK_LOG_DIRECTORY "/tlogs"
#define MAVLINK_LOGFILE_EXT ".tlog"

#ifndef APP_TYPE
#define APP_TYPE stable // or "daily" for master branch builds
#endif                  // 또는 "daily" 정의 

#ifndef APP_PLATFORM

#ifdef Q_OS_MACX
#define APP_PLATFORM osx
#elif defined(Q_LINUX_64) && defined(Q_UBUNTU)
#define APP_PLATFORM ubuntu64
#elif defined(Q_LINUX_64) && defined(Q_ARCHLINUX)
#define APP_PLATFORM archlinux64
#elif defined(Q_LINUX_64) && defined(Q_FEDORA)
#define APP_PLATFORM fedora64
#elif defined(Q_LINUX_64)
#define APP_PLATFORM debian64
#elif defined(Q_OS_LINUX) && defined(Q_UBUNTU)
#define APP_PLATFORM ubuntu32
#elif defined(Q_LINUX_32) && defined(Q_ARCHLINUX)
#define APP_PLATFORM archlinux32
#elif defined(Q_LINUX_32) && defined(Q_FEDORA)
#define APP_PLATFORM fedora32
#elif defined(Q_OS_LINUX)
#define APP_PLATFORM debian32
#elif defined(Q_OPENBSD)
#define APP_PLATFORM OpenBSD
#else
#define APP_PLATFORM win
#endif

#endif

namespace QGC

{
const QString APPNAME = "APMPLANNER2";
const QString COMPANYNAME = "ARDUPILOT";
const int APPLICATIONVERSION = 2026; // 2.0.26 [TODO] we should deprecate this version definition
                                     // 2.0.26 [TODO]이 버전 정의를 더 이상 사용하지 말아야합니다.
    inline void close(){
        GlobalObject* global = GlobalObject::sharedInstance();
        delete global;
        global = NULL;
    }

    inline void loadSettings(){
        GlobalObject::sharedInstance()->loadSettings();
    }

    inline void saveSettings(){
        GlobalObject::sharedInstance()->saveSettings();
    }

    inline QString fileNameAsTime(){
        return GlobalObject::sharedInstance()->fileNameAsTime();
    }

    inline bool makeDirectory(const QString& dir){
        return GlobalObject::sharedInstance()->makeDirectory(dir);
    }

    inline QString appDataDirectory(){
        return GlobalObject::sharedInstance()->appDataDirectory();
    }

    inline void setAppDataDirectory(const QString& dir){
        GlobalObject::sharedInstance()->setAppDataDirectory(dir);
    }

    inline QString MAVLinkLogDirectory(){
        return GlobalObject::sharedInstance()->MAVLinkLogDirectory();
    }

    inline void setMAVLinkLogDirectory(const QString& dir){
        GlobalObject::sharedInstance()->setMAVLinkLogDirectory(dir);
    }

    inline QString logDirectory(){
        return GlobalObject::sharedInstance()->logDirectory();
    }

    inline void setLogDirectory(const QString& dir){
        GlobalObject::sharedInstance()->setLogDirectory(dir);
    }

    inline QString parameterDirectory(){
        return GlobalObject::sharedInstance()->parameterDirectory();
    }

    inline void setParameterDirectory(const QString& dir){
        GlobalObject::sharedInstance()->setParameterDirectory(dir);
    }

    inline QString missionDirectory(){
        return GlobalObject::sharedInstance()->missionDirectory();
    }

    inline void setMissionDirectory(const QString& dir){
        GlobalObject::sharedInstance()->setMissionDirectory(dir);
    }

    //Returns the absolute parth to the files, data, qml support directories
    //It could be in 1 of 2 places under Linux
    // 파일, 데이터, qml 지원 디렉토리에 절대 parth를 반환합니다.
    // Linux에서 2 곳 중 1 곳이 될 수 있습니다.
    inline QString shareDirectory(){
        return GlobalObject::sharedInstance()->shareDirectory();
    }

    inline QRegExp paramSplitRegExp() {
        return QRegExp("\t|,|=");
    }

    inline QRegExp paramLineSplitRegExp() {
        return QRegExp("\r|\n");
    }

}

#endif // QGC_CONFIGURATION_H
