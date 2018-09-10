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
 *   @brief Implementation of class WatchdogControl
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include "WatchdogControl.h"
#include "WatchdogView.h"
#include "WatchdogProcessView.h"
#include "ui_WatchdogControl.h"
#include "logging.h"
#include "PxQuadMAV.h"
#include "UASManager.h"

WatchdogControl::WatchdogControl(QWidget *parent) :
    QWidget(parent),
    mav(NULL),
    updateInterval(2000000),
    ui(new Ui::WatchdogControl)
{
    ui->setupUi(this);

    // UI is initialized, setup layout	 UI가 초기화됩니다.  
    listLayout = new QVBoxLayout(ui->mainWidget);
    listLayout->setSpacing(6);
    listLayout->setMargin(0);
    listLayout->setAlignment(Qt::AlignTop);
    ui->mainWidget->setLayout(listLayout);

    connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    this->setVisible(false);
}

WatchdogControl::~WatchdogControl()
{
    delete ui;
}

void WatchdogControl::setUAS(UASInterface* uas)
{
    PxQuadMAV* qmav = dynamic_cast<PxQuadMAV*>(uas);

    if (qmav) {
        connect(qmav, SIGNAL(processReceived(int,int,int,QString,QString,int)), this, SLOT(addProcess(int,int,int,QString,QString,int)));
        connect(qmav, SIGNAL(watchdogReceived(int,int,uint)), this, SLOT(updateWatchdog(int,int,uint)));
        connect(qmav, SIGNAL(processChanged(int,int,int,int,bool,int,int)), this, SLOT(updateProcess(int,int,int,int,bool,int,int)));
    }
}

void WatchdogControl::updateWatchdog(int systemId, int watchdogId, unsigned int processCount)
{
    // request the watchdog with the given ID
    // Get the watchdog and request the info for it

/*
    // 주어진 ID로 워치 독을 요청한다.
    // 워치 독을 가져와 정보를 요청합니다.
*/

    WatchdogInfo& watchdog = this->getWatchdog(systemId, watchdogId);

    // if the proces count doesn't match, the watchdog is either new or has changed - create a new vector with new (and empty) ProcessInfo structs.

/*
   // 처리 횟수가 일치하지 않으면 워치 독은 새로운 것이거나 변경되었습니다. 새로운 (그리고 빈) ProcessInfo 구조체를 가진 새로운 벡터를 만듭니다.
*/

    if (watchdog.processes_.size() != processCount) {
        watchdog.processes_ = std::vector<ProcessInfo>(processCount);
        // Create new UI widget
        //WatchdogView* view = new WatchdogView(this);

/*
        // 새 UI 위젯을 만듭니다.
        // WatchdogView * view = 새로운 WatchdogView (this);
*/


    }

    // start the timeout timer
    //watchdog.timeoutTimer_.reset();

/*
    // 타임 아웃 타이머를 시작합니다.
    // watchdog.timeoutTimer_.reset ();
*/


    QLOG_DEBUG() << "WATCHDOG RECEIVED";
//    QLOG_TRACE() << "<-- received mavlink_watchdog_heartbeat_t " << msg->sysid << " / " << payload.watchdog_id << " / " << payload.process_count << std::endl;
}

void WatchdogControl::addProcess(int systemId, int watchdogId, int processId, QString name, QString arguments, int timeout)
{
    // request the watchdog and the process with the given IDs	 주어진 ID로 워치 독과 프로세스를 요청한다.  
    WatchdogInfo& watchdog = this->getWatchdog(systemId, watchdogId);
    ProcessInfo& process = watchdog.getProcess(processId);

    // store the process information in the ProcessInfo struct	  ProcessInfo 구조체에 프로세스 정보 저장  
    process.name_ = name.toStdString();
    process.arguments_ = arguments.toStdString();
    process.timeout_ = timeout;
    QLOG_DEBUG() << "PROCESS RECEIVED";
    QLOG_DEBUG() << "SYS" << systemId << "WD" << watchdogId << "PROCESS" << processId << name << "ARG" << arguments << "TO" << timeout;
//    QLOG_TRACE() << "<-- received mavlink_watchdog_process_info_t " << msg->sysid << " / " << (const char*)payload.name << " / " << (const char*)payload.arguments << " / " << payload.timeout << std::endl;
}


void WatchdogControl::updateProcess(int systemId, int watchdogId, int processId, int state, bool muted, int crashes, int pid)
{
    // request the watchdog and the process with the given IDs	 주어진 ID로 워치 독과 프로세스를 요청한다.  
    WatchdogInfo& watchdog = this->getWatchdog(systemId, watchdogId);
    ProcessInfo& process = watchdog.getProcess(processId);

    // store the status information in the ProcessInfo struct	 ProcessInfo 구조체에 상태 정보를 저장합니다.  
    process.state_ = static_cast<ProcessInfo::State::Enum>(state);
    process.muted_ = muted;
    process.crashes_ = crashes;
    process.pid_ = pid;

    QLOG_DEBUG() << "PROCESS UPDATED";
    QLOG_DEBUG() << "SYS" << systemId << "WD" << watchdogId << "PROCESS" << processId << "STATE" << state << "CRASH" << crashes << "PID" << pid;

    //process.updateTimer_.reset();
//    QLOG_TRACE() << "<-- received mavlink_watchdog_process_status_t " << msg->sysid << " / " << payload.state << " / " << payload.muted << " / " << payload.crashes << " / " << payload.pid << std::endl;
}

/**
    @brief Returns a WatchdogInfo struct that belongs to the watchdog with the given system-ID and watchdog-ID
*/

/*
    @brief 지정된 system-ID 및 watchdog-ID를 가진 워치 독에 속한 WatchdogInfo 구조체를 반환합니다.
*/

WatchdogControl::WatchdogInfo& WatchdogControl::getWatchdog(uint8_t systemId, uint16_t watchdogId)
{
    WatchdogID id(systemId, watchdogId);

    std::map<WatchdogID, WatchdogInfo>::iterator it = this->watchdogs_.find(id);
    if (it != this->watchdogs_.end()) {
        // the WatchdogInfo struct already exists in the map, return it

/*
        // WatchdogInfo 구조체가 이미 맵에 존재하면이를 반환합니다.
*/

        return it->second;
    } else {
        // the WatchdogInfo struct doesn't exist - request info and status for all processes and create the struct

/*
        // WatchdogInfo 구조체가 존재하지 않습니다 - 모든 프로세스에 대한 정보와 상태를 요청하고 구조체를 생성합니다
*/

        this->sendCommand(id, WatchdogControl::ALL, Command::RequestInfo);
        this->sendCommand(id, WatchdogControl::ALL, Command::RequestStatus);
        return this->watchdogs_[id];
    }
}

/**
    @brief Returns a ProcessInfo struct that belongs to the process with the given ID.
*/

/*
    @brief 지정된 ID를 가진 프로세스에 속한 ProcessInfo 구조체를 리턴합니다.
*/

WatchdogControl::ProcessInfo& WatchdogControl::WatchdogInfo::getProcess(uint16_t index)
{
    // if the index is out of bounds, resize the vector	 인덱스가 경계를 벗어난 경우 벡터의 크기를 조정합니다.  
    if (index >= this->processes_.size())
        this->processes_.resize(index + 1);

    return this->processes_[index];
}

/**
    @brief Sends a watchdog command to a process on a given watchdog.
    @param w_id The WatchdogID struct (containing system-ID and watchdog-ID) that identifies the watchdog
    @param p_id The process-ID
    @param command The command-ID
*/

/*
    @brief 지정된 watchdog의 프로세스에 watchdog 명령을 보냅니다.
    @param w_id 워치 독을 식별하는 WatchdogID 구조체 (시스템 ID와 워치 독 ID 포함)
    @param p_id 프로세스 ID
    @param command 커멘드 ID
*/

void WatchdogControl::sendCommand(const WatchdogID& w_id, uint16_t p_id, Command::Enum command)
{
    emit sendProcessCommand(w_id.watchdog_id_, p_id, command);
}

void WatchdogControl::changeEvent(QEvent *e)
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
