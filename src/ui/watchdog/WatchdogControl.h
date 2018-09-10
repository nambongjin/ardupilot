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
 *   @brief Definition of class WatchdogControl
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef WATCHDOGCONTROL_H
#define WATCHDOGCONTROL_H

#include <inttypes.h>

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>

#include <map>
#include <string>
#include <sstream>

#include "WatchdogView.h"

#include "UASInterface.h"

namespace Ui
{
class WatchdogControl;
}

/**
 * @brief Overall widget for controlling all watchdogs of all connected MAVs	 연결된 모든 MAV의 모든 워치 독을 제어하기위한 전체 위젯
 */
class WatchdogControl : public QWidget
{
    Q_OBJECT
public:


    ///! Command codes, used to send and receive commands over lcm	 lcm 이상의 명령을 보내고받는 데 사용되는 명령 코드
    struct Command {
        enum Enum {
            Start         = 0,
            Restart       = 1,
            Stop          = 2,
            Mute          = 3,
            Unmute        = 4,

            RequestInfo   = 254,
            RequestStatus = 255
        };
    };

    ///! This struct represents a process on the watchdog. Used to store all values.	 이 구조체는 워치 독에 대한 프로세스를 나타냅니다. 모든 값을 저장하는 데 사용됩니다.
    struct ProcessInfo {
        ///! Process state - each process is in exactly one of those states (except unknown, that's just to initialize it)	 프로세스 상태 - 각 프로세스는 해당 상태 중 하나에 있습니다 (알 수없는 경우를 제외하고, 초기화하는 것만 제외하고).
        struct State {
            enum Enum {
                Unknown       = 0,
                Running       = 1,
                Stopped       = 2,
                Stopped_OK    = 3,
                Stopped_ERROR = 4
            };
        };

        ///! Constructor - initialize the values	 생성자 - 값 초기화
        ProcessInfo() : timeout_(0), state_(State::Unknown), muted_(false), crashes_(0), pid_(-1) {}

        std::string name_;      ///< The name of the process	 프로세스 이름
        std::string arguments_; ///< The arguments (argv of the process)	 인수 (프로세스의 argv)

        int32_t timeout_;       ///< Heartbeat timeout value (in microseconds)	 하트 비트 제한 시간 값 (마이크로 초)

        State::Enum state_;     ///< The current state of the process	 프로세스의 현재 상태
        bool muted_;            ///< True if the process is currently muted	 프로세스가 현재 음소거되어 있으면 true
        uint16_t crashes_;      ///< The number of crashes	 충돌 수
        int32_t pid_;           ///< The PID of the process	 프로세스의 PID

        //quint64_t requestTimeout;
        //    Timer requestTimer_;    ///< Internal timer, used to repeat status and info requests after some time (in case of packet loss)

/*
					내부 타이머, 잠시 후 상태 및 정보 요청을 반복하는 데 사용됩니다 (패킷 손실의 경우)
*/
	 
        //    Timer updateTimer_;     ///< Internal timer, used to measure the time since the last update (used only for graphics)

/*
					내부 타이머, 마지막 업데이트 이후 시간을 측정하는 데 사용됩니다 (그래픽에만 사용됨)
*/

    };

    ///! This struct identifies a watchdog. It's a combination of system-ID and watchdog-ID. implements operator< to be used as key in a std::map

/*
	이 구조체는 워치 독을 식별합니다. 이것은 시스템 ID와 워치 독 ID의 조합입니다. std :: map에서 키로 사용되는 연산자 <를 구현합니다.
*/

    struct WatchdogID {
        ///! Constructor - initialize the values		 생성자 - 값 초기화 
        WatchdogID(uint8_t system_id, uint16_t watchdog_id) : system_id_(system_id), watchdog_id_(watchdog_id) {}

        uint8_t system_id_;     ///< The system-ID	 시스템 ID
        uint16_t watchdog_id_;  ///< The watchdog-ID	 워치 독 ID

        ///! Comparison operator which is used by std::map	 std :: map에서 사용되는 비교 연산자
        inline bool operator<(const WatchdogID& other) const {
            return (this->system_id_ != other.system_id_) ? (this->system_id_ < other.system_id_) : (this->watchdog_id_ < other.watchdog_id_);
        }

    };

    ///! This struct represents a watchdog	 이 구조체는 워치 독을 나타냅니다.
    struct WatchdogInfo {
        ProcessInfo& getProcess(uint16_t index);

        std::vector<ProcessInfo> processes_;    ///< A vector containing all processes running on this watchdog	 이 워치 독에서 실행중인 모든 프로세스를 포함하는 벡터
        uint64_t timeout;
        QTimer* timeoutTimer_;                    ///< Internal timer, used to measure the time since the last heartbeat message	 내부 타이머, 마지막 하트 비트 메시지 이후의 시간을 측정하는 데 사용됩니다.
    };

    WatchdogControl(QWidget *parent = 0);
    ~WatchdogControl();

    static const uint16_t ALL         = (uint16_t)-1;   ///< A magic value for a process-ID which addresses "all processes"	 "모든 프로세스"를 처리하는 프로세스 ID의 마법 값
    static const uint16_t ALL_RUNNING = (uint16_t)-2;   ///< A magic value for a process-ID which addresses "all running processes"	 실행중인 모든 프로세스"를 처리하는 프로세스 ID의 매직 값
    static const uint16_t ALL_CRASHED = (uint16_t)-3;   ///< A magic value for a process-ID which addresses "all crashed processes"	 충돌 한 모든 프로세스"를 처리하는 프로세스 ID의 매직 값

public slots:
    void updateWatchdog(int systemId, int watchdogId, unsigned int processCount);
    void addProcess(int systemId, int watchdogId, int processId, QString name, QString arguments, int timeout);
    void updateProcess(int systemId, int watchdogId, int processId, int state, bool muted, int crashed, int pid);
    void setUAS(UASInterface* uas);

signals:
    void sendProcessCommand(int watchdogId, int processId, unsigned int command);

protected:
    void changeEvent(QEvent *e);

    UASInterface* mav;
    QVBoxLayout* listLayout;
    uint64_t updateInterval;

private:
    Ui::WatchdogControl *ui;

    void sendCommand(const WatchdogID& w_id, uint16_t p_id, Command::Enum command);

    WatchdogInfo& getWatchdog(uint8_t system_id, uint16_t watchdog_id);

    std::map<WatchdogID, WatchdogInfo> watchdogs_;          ///< A map containing all watchdogs which are currently active	 현재 활성화 된 모든 워치 독이 포함 된지도
    std::map<WatchdogID, WatchdogView> views;
    QTimer updateTimer_;
};

#endif // WATCHDOGCONTROL_H

///! Convert a value to std::string	 값을 std :: string으로 변환하십시오.
template <class T>
std::string convertToString(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
