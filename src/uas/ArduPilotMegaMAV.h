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
 *   @brief APM UAS specilization Object
 *
 *   @author Bill Bonney <billbonney@communistech.com>
 *
 */

#ifndef ARDUPILOTMEGAMAV_H
#define ARDUPILOTMEGAMAV_H

#include "UAS.h"
#include "APMFirmwareVersion.h"
#include <QString>
#include <QSqlDatabase>

static const QRegExp APM_COPTER_REXP("^(ArduCopter|APM:Copter)");
static const QRegExp APM_SOLO_REXP("^(APM:Copter solo-)");
static const QRegExp APM_PLANE_REXP("^(ArduPlane|APM:Plane)");
static const QRegExp APM_ROVER_REXP("^(ArduRover|APM:Rover)");
static const QRegExp APM_SUB_REXP("^(ArduSub|APM:Sub)");
static const QRegExp APM_PX4NUTTX_REXP("^PX4: .*NuttX: .*");
static const QRegExp APM_FRAME_REXP("^Frame: ");
static const QRegExp APM_SYSID_REXP("^PX4v2 ");

// Regex to parse version text coming from APM, gives out firmware type, major, minor and patch level numbers

/*

// APM에서 제공되는 버전 텍스트를 구문 분석하는 정규 표현식으로 펌웨어 유형, 주, 부 및 패치 레벨 번호를 제공합니다.*/

static const QRegExp VERSION_REXP("^(APM:Copter|APM:Plane|APM:Rover|APM:Sub|ArduCopter|ArduPlane|ArduRover|ArduSub) +[vV](\\d*)\\.*(\\d*)*\\.*(\\d*)*");

// minimum firmware versions that don't suffer from mavlink severity inversion bug.	 mavlink 심각도 반전 버그가없는 최소 펌웨어 버전.
// https://github.com/diydrones/apm_planner/issues/788
static const QString MIN_SOLO_VERSION_WITH_CORRECT_SEVERITY_MSGS("APM:Copter solo-1.2.0");
static const QString MIN_COPTER_VERSION_WITH_CORRECT_SEVERITY_MSGS("APM:Copter V3.4.0");
static const QString MIN_PLANE_VERSION_WITH_CORRECT_SEVERITY_MSGS("APM:Plane V3.4.0");
static const QString MIN_SUB_VERSION_WITH_CORRECT_SEVERITY_MSGS("APM:Sub V3.4.0");
static const QString MIN_ROVER_VERSION_WITH_CORRECT_SEVERITY_MSGS("APM:Rover V2.6.0");

class ArduPilotMegaMAV : public UAS
{
    Q_OBJECT
public:
    ArduPilotMegaMAV(MAVLinkProtocol* mavlink, int id = 0);
    /** @brief Set camera mount stabilization modes 	 카메라 마운트 안정화 모드 설정*/
    void setMountConfigure(unsigned char mode, bool stabilize_roll,bool stabilize_pitch,bool stabilize_yaw);
    /** @brief Set camera mount control 	 카메라 마운트 제어 설정 */
    void setMountControl(double pa,double pb,double pc,bool islatlong);

    QString getCustomModeText();
    QString getCustomModeAudioText();
    void playCustomModeChangedAudioMessage();
    void playArmStateChangedAudioMessage(bool armedState) ;

    void loadSettings();
    void saveSettings();

    void adjustSeverity(mavlink_message_t* message) const;

    bool useSeverityCompatibilityMode() {return m_severityCompatibilityMode;}

    APMFirmwareVersion getFirmwareVersion() {return m_firmwareVersion;}

signals:
    void versionDetected(QString versionString);

public slots:
    /** @brief Receive a MAVLink message from this MAV	 MAV로부터 MAVLink 메시지 받기 */
    void receiveMessage(LinkInterface* link, mavlink_message_t message);
    void RequestAllDataStreams();

    // Overides from UAS virtual interface	 UAS 가상 인터페이스에서 덮어 쓴다.
    virtual void armSystem();
    virtual void disarmSystem();

    // UAS Interface
    void textMessageReceived(int uasid, int componentid, int severity, QString text);
    void heartbeatTimeout(bool timeout, unsigned int ms);

private slots:
    void uasConnected();
    void uasDisconnected();

private:
    void createNewMAVLinkLog(uint8_t type);
    static bool _isTextSeverityAdjustmentNeeded(const APMFirmwareVersion& firmwareVersion);


private:
    QTimer *txReqTimer;
    bool m_severityCompatibilityMode;
    APMFirmwareVersion m_firmwareVersion;
};


/**
 * @brief Base Class for all message types	  모든 메시지 유형에 대한 * @brief 기본 클래스
 */
class MessageBase
{
public:

    typedef QSharedPointer<MessageBase> Ptr;            /// Shared pointer type	 공유 포인터 유형
    typedef QPair<QString, QVariant> NameValuePair;     /// Pair of names and values	  이름과 값의 쌍

    MessageBase();

    /**
     * @brief MessageBase constructor for setting all params
     * @param index - Index of this message
     * @param timeStamp - Time stamp of this message. Double cause it should be in seconds
     * @param name - name of this message, used to identify type
     * @param color - color associated with this message type
     */

/*
     * @brief 모든 매개 변수를 설정하기위한 MessageBase 생성자
     파라미터 : index -이 메세지의 인덱스
     * @param timeStamp -이 메세지의 타임 스탬프입니다. 두 번 원인이 초 안에 있어야합니다.
     파라미터 : name -이 메세지의 이름. 타입의 식별에 사용한다
     파라미터 : color -이 메세지 타입에 관련 지을 수 있었던 색
*/

    MessageBase(const quint32 index, const double timeStamp, const QString &name, const QColor &color);

    virtual ~MessageBase(){}

    /**
     * @brief Getter for the index of this message
     * @return The index
     */

/*
     * @brief이 메시지의 색인을 얻습니다.
     * @return 인덱스
*/

    virtual quint32 getIndex() const;

    /**
     * @brief Getter for the Time stamp of this message.
     * @return The time stamp as double in seconds
     */

/*
     * @brief이 메시지의 타임 스탬프를 얻습니다.
     * @return 초 단위의 시간 표시
*/

    virtual double getTimeStamp() const;

    /**
     * @brief setFromNameValuPairList - Reads a list of NameValuePairs which should contain the name
     *        and the value of each measurement and sets the internal data accordingly
     * @param values - List of name value pairs
     * @param timeDivider - divider for timestamp value
     * @return true - success, false otherwise (data was not added)
     */

/*
     * @brief setFromNameValuPairList - 이름을 포함해야하는 NameValuePair의 목록을 읽습니다.
     * 및 각 측정 값에 따라 내부 데이터를 설정합니다.
     * @ 파라미터 치 - 이름 치의 페어의리스트
     timeDivider - 타임 스탬프 치의 디바이더
     * @return true - 성공, 그렇지 않으면 거짓 (데이터가 추가되지 않음)
*/

    virtual bool setFromNameValuePairList(const QList<NameValuePair> &values, const double timeDivider) = 0;

    /**
     * @brief Converts the ErrorCode into an uninterpreted string.
     *        Uinterpreted means it prints ErrorCode and SubSystem.
     * @return The uninterpreted Qstring
     */

/*
     * @brief ErrorCode를 해석되지 않은 문자열로 변환합니다.
     * Uinterpreted는 ErrorCode 및 SubSystem을 인쇄 함을 의미합니다.
     * @return 미 해석의 Qstring
*/

    virtual QString toString() const = 0;

    /**
     * @brief typeName returns the message type name.
     * @return Type name string
     */

/*
     * @brief typeName은 메시지 유형 이름을 리턴합니다.
     * @return 형명 캐릭터 라인
*/

    virtual QString typeName() const;

    /**
     * @brief typeColor returns an QColor object with the color associated
     *        with the typ of the Message.
     * @return Color for this type
     */

/*
     * @brief typeColor는 색이 연관된 QColor 객체를 반환합니다.
     * 메시지의 typ.
     이 형식의 색
*/

    virtual QColor typeColor() const;

protected:

    quint32 m_Index;        /// DB Index of this message	 DB이 메시지의 인덱스
    double  m_TimeStamp;    /// Timestamp of this message. Should be in seconds	 이 메시지의 타임 스탬프. 몇 초 안에 있어야합니다.
    QString m_TypeName;     /// Name of this message	 이 메시지의 이름
    QString m_TimeFieldName;/// Name of the Timefield	 Timefield의 이름
    QColor  m_Color;        /// Color associated with this message	 이 메시지와 관련된 색
};

/**
 * @brief Class for making it easier to handle the errorcodes.
 *        This class implements everything which is needed to
 *        handle MAV Errors.
 */

/*
 * @brief 오류 코드를보다 쉽게 ​​처리하기위한 클래스.
 *이 클래스는 필요한 모든 것을 구현합니다.
 * MAV 오류를 처리합니다.
*/

class ErrorMessage : public MessageBase
{
public:

    static const QString TypeName;   /// Name of this message is 'ERR'	 이 메시지의 이름은 'ERR'입니다.

    ErrorMessage();

    /**
      * @brief ErrorMessage Constructor for setting name of the timefield
      *        used by the setFromSqlRecord() method
      * @param TimeFieldName - name of the timefield used for parsing the SQL record
      */

/*
      * @brief ErrorMessage 시간 필드의 이름을 설정하기위한 생성자.
      * setFromSqlRecord () 메서드에서 사용됩니다.
      * @param TimeFieldName - SQL 레코드의 구문 분석에 사용 된 시간 필드의 이름
*/

    ErrorMessage(const QString &TimeFieldName);

    /**
     * @brief ErrorMessage Constructor for setting all internals
     * @param index - Index of this message
     * @param timeStamp - Time stamp of this message as double in seconds
     * @param subSys - Subsys who emitted this error
     * @param errCode - Errorcode emitted by subsys
     */

/*
     * @brief ErrorMessage 모든 내부 설정을위한 생성자
     파라미터 : index -이 메세지의 인덱스
     * @param timeStamp -이 메세지의 타임 스탬프 (초 단위)
     * @param subSys -이 오류를 방출 한 Subsys
     * @param errCode - 서브 시스템에 의해 발생한 에러 코드
*/

    ErrorMessage(const quint32 index, const double timeStamp, const quint32 subSys, const quint32 errCode);

    /**
     * @brief Getter for the Subsystem ID which emitted the error
     * @return Subsystem ID
     */

/*
     * @brief 오류를 방출 한 서브 시스템 ID를 얻습니다.
     * @return 서브 시스템 ID
*/

    quint32 getSubsystemCode() const;

    /**
     * @brief Getter for the Errorcode emitted by the subsystem
     * @return Errorcode
     */

/*
     * @brief 서브 시스템이 내 보낸 Errorcode를 얻는다.
     * @return 에러 코드
*/

    quint32 getErrorCode() const;

    /**
     * @brief Reads an list of NameValuePairs and sets the internal data.
     *        The list must contain a pairs with name "Index", m_TimeFieldName,
     *        "ECode" and "Subsys" in order to get a positive return value.
     *        The timeDivider should scale the time stamp to seconds.
     *
     * @param values[in] - Filled list with NameValuePairs
     * @param timeDivider[in] - Devider to scale the timestamp to seconds
     * @return true - all Fields could be read
     *         false - not all data could be read
     */

/*
     * @brief NameValuePair의 목록을 읽고 내부 데이터를 설정합니다.
     * 목록에는 이름이 "Index"인 m_TimeFieldName,
     * 긍정적 인 반환 값을 얻기 위해 "ECode"및 "Subsys".
     * timeDivider는 타임 스탬프를 초 단위로 스케일합니다.
     *
     * @param values ​​[in] - 채워진리스트와 NameValuePairs
     * @param timeDivider [in] - 타임 스탬프를 초 단위로 스케일하는 데빈다.
     * @return true - 모든 필드를 읽을 수 있음
     * false - 모든 데이터를 읽을 수있는 것은 아닙니다.
*/

    virtual bool setFromNameValuePairList(const QList<NameValuePair> &values, const double timeDivider);

    /**
     * @brief Converts the ErrorCode into an uninterpreted string.
     *        Uinterpreted means it prints ErrorCode and SubSystem.
     * @return The uninterpreted Qstring
     */

/*
     * @brief ErrorCode를 해석되지 않은 문자열로 변환합니다.
     * Uinterpreted는 ErrorCode 및 SubSystem을 인쇄 함을 의미합니다.
     * @return 미 해석의 Qstring
*/

    virtual QString toString() const;

private:

    quint32 m_SubSys;        /// Subsystem signaling the error	 오류를 알리는 서브 시스템
    quint32 m_ErrorCode;     /// Errorcode of the Subsystem	 서브 시스템의 에러 코드
};


/**
 * @brief Class for making it easier to handle the mode messages.
 *        This class implements everything which is needed to
 *        handle MAV Mode messages.
 */

/*
 * @brief 모드 메세지를 다루기 쉽게하기위한 클래스.
 *이 클래스는 필요한 모든 것을 구현합니다.
 * MAV 모드 메시지를 처리합니다.
*/

class ModeMessage : public MessageBase
{
public:
    static const QString TypeName;   /// Name of this message is 'MODE'	 이 메시지의 이름은 'MODE'입니다.

    ModeMessage();

    /**
      * @brief ModeMessage Constructor for setting name of the timefield
      *        used by the setFromSqlRecord() method
      * @param TimeFieldName - name of the timefield used for parsing the SQL record
      */

/*
      * @brief ModeMessage 시간 필드의 이름을 설정하기위한 생성자.
      * setFromSqlRecord () 메서드에서 사용됩니다.
      * @param TimeFieldName - SQL 레코드의 구문 분석에 사용 된 시간 필드의 이름
*/

    ModeMessage(const QString &TimeFieldName);

    /**
     * @brief ModeMessage Costructor for setting all internals
     * @param index - Index of this message
     * @param timeStamp - Time stamp of this message should be in seconds
     * @param mode - Mode of this message
     * @param modeNum - Mode Num of this message
     * @param reason - Reason ID leading to this mode change (since AC 3.4)
     */

/*
     * @brief ModeMessage 모든 내부 설정을위한 Costructor
     파라미터 : index -이 메세지의 인덱스
     * @param timeStamp -이 메세지의 타임 스탬프는 초 단위 일 필요가 있습니다.
     * @param mode -이 메세지의 모드
     * @param modeNum -이 메시지의 모드 번호
     * @param 이유 -이 모드 변경으로 이어지는 이유 ID (AC 3.4 이후)
*/

    ModeMessage(const quint32 index, const double timeStamp, const quint32 mode, const quint32 modeNum, const quint32 reason);

    /**
     * @brief Getter for the Mode of this message
     * @return Mode ID
     */

/*
     * @brief이 메시지 모드 가져 오기
     * @return 모드 ID
*/

    quint32 getMode() const;

    /**
     * @brief Getter for the ModeNum of this message
     * @return ModeNum ID
     */

/*
     * @brief이 메시지의 ModeNum을 얻습니다.
     * @return ModeNum ID
*/

    quint32 getModeNum() const;

    /**
     * @brief Getter for the mode change reason (since AC 3.4)
     * @return mode change reason ID
     */

/*
     * @brief 모드 변경 사유 (AC 3.4 이후)
     * @return 모드 변경 이유 ID
*/

    quint32 getReason() const;

    /**
     * @brief Reads a QList of NameValuePair and sets the internal data.
     *        The list must contain a pairs with name "Index", m_TimeFieldName,
     *        "Mode" and "ModeNum" in order to get a positive return value.
     *        The timeDivider should scale the time stamp to seconds.
     *
     * @param values[in] - Filled list with NameValuePairs
     * @param timeDivider[in] - Divider to scale the timestamp to seconds
     * @return true - all mandatory Fields could be read
     *         false - not all mandatory data could be read
     */

/*
     * @brief NameValuePair의 QList를 읽고 내부 데이터를 설정합니다.
     * 목록에는 이름이 "Index"인 m_TimeFieldName,
     * 양수 반환 값을 얻기 위해 "Mode"와 "ModeNum".
     * timeDivider는 타임 스탬프를 초 단위로 스케일합니다.
     *
     * @param values ​​[in] - 채워진리스트와 NameValuePairs
     * @param timeDivider [in] - 타임 스탬프를 초 단위로 스케일하는 디바이더입니다.
     * @return true - 모든 필수 필드를 읽을 수 있음
     * false - 모든 필수 데이터를 읽을 수있는 것은 아닙니다.
*/

    virtual bool setFromNameValuePairList(const QList<NameValuePair> &values, const double timeDivider);

    /**
     * @brief Converts the ModeMessage into an uninterpreted string.
     *        Uinterpreted means it prints Mode ID and ModNum ID.
     * @return The uninterpreted Qstring
     */

/*
     * @brief ModeMessage를 해석되지 않은 문자열로 변환합니다.
     * Uinterpreted는 모드 ID 및 ModNum ID를 인쇄 함을 의미합니다.
     * @return 미 해석의 Qstring
*/

    virtual QString toString() const;

private:

    quint32 m_Mode;        /// Mode ID
    quint32 m_ModeNum;     /// ModeNum ID (unused)
    quint32 m_Reason;      /// Mode change ID
};

/**
 * @brief Class for making it easier to handle the event messages.
 *        This class implements everything which is needed to
 *        handle MAV EV messages.
 */

/*
 * @brief 이벤트 메세지를 다루기 쉽게하기위한 클래스.
 *이 클래스는 필요한 모든 것을 구현합니다.
 * MAV EV 메시지를 처리합니다.
*/

class EventMessage : public MessageBase
{
public:

    static const QString TypeName;   /// Name of this message is 'EV'	 이 메시지의 이름은 'EV'입니다.

    EventMessage();

    /**
      * @brief EventMessage Constructor for setting name of the timefield
      *        used by the setFromSqlRecord() method
      * @param TimeFieldName - name of the timefield used for parsing the SQL record
      */

/*
      * @brief EventMessage 시간 필드의 이름을 설정하기위한 생성자입니다.
      * setFromSqlRecord () 메서드에서 사용됩니다.
      * @param TimeFieldName - SQL 레코드의 구문 분석에 사용 된 시간 필드의 이름
*/

    EventMessage(const QString &TimeFieldName);

    /**
     * @brief EventMessage Constructor for setting all internals
     * @param index - Index of this message
     * @param timeStamp - Time stamp of this message should be in seconds
     * @param eventID - Event ID of this message
     */

/*
     * @brief EventMessage 모든 내부 설정을위한 생성자
     파라미터 : index -이 메세지의 인덱스
     * @param timeStamp -이 메세지의 타임 스탬프는 초 단위 일 필요가 있습니다.
     * @param eventID -이 메세지의 이벤트 ID
*/

    EventMessage(const quint32 index, const double timeStamp, const quint32 eventID);

    /**
     * @brief Getter for the Event ID of this message
     * @return Event ID
     */

/*
     * @brief이 메시지의 이벤트 ID 가져 오기
     * @return 이벤트 ID
*/

    quint32 getEventID() const;

    /**
     * @brief Reads a QList of NameValuePair and sets the internal data.
     *        The list must contain a pairs with name "Index", m_TimeFieldName
     *        and "Id" in order to get a positive return value.
     *        The timeDivider should scale the time stamp to seconds.
     *
     * @param values[in] - Filled list with NameValuePairs
     * @param timeDivider[in] - Devider to scale the timestamp to seconds
     * @return true - all Fields could be read
     *         false - not all data could be read
     */

/*
     * @brief NameValuePair의 QList를 읽고 내부 데이터를 설정합니다.
     * 목록에는 이름이 "Index"인 쌍이 포함되어야합니다. m_TimeFieldName
     * 및 "Id"를 반환합니다.
     * timeDivider는 타임 스탬프를 초 단위로 스케일합니다.
     *
     * @param values ​​[in] - 채워진리스트와 NameValuePairs
     * @param timeDivider [in] - 타임 스탬프를 초 단위로 스케일하는 데빈다.
     * @return true - 모든 필드를 읽을 수 있음
     * false - 모든 데이터를 읽을 수있는 것은 아닙니다.
*/

    virtual bool setFromNameValuePairList(const QList<NameValuePair> &values, const double timeDivider);

    /**
     * @brief Converts the ModeMessage into an uninterpreted string.
     *        Uinterpreted means it prints Mode ID and ModNum ID.
     * @return The uninterpreted Qstring
     */

/*
     * @brief ModeMessage를 해석되지 않은 문자열로 변환합니다.
     * Uinterpreted는 모드 ID 및 ModNum ID를 인쇄 함을 의미합니다.
     * @return 미 해석의 Qstring
*/

    virtual QString toString() const;

private:

     quint32 m_EventID;    /// EventID
};

/**
 * @brief Class for making it easier to handle the Msg messages.
 *        This class implements everything which is needed to
 *        handle MAV MSG messages.
 *        This class has no getter - use toString method instead.
 */

/*
 * @brief 메시지 메시지를보다 쉽게 ​​처리하기위한 클래스.
 *이 클래스는 필요한 모든 것을 구현합니다.
 * MAV MSG 메시지를 처리합니다.
 *이 클래스는 대신 getter-toString 메소드를 사용합니다.
*/

class MsgMessage : public MessageBase
{
public:

    static const QString TypeName;   /// Name of this message is 'MSG'

    MsgMessage();

    /**
      * @brief MsgMessage Constructor for setting name of the timefield
      *        used by the setFromSqlRecord() method
      * @param TimeFieldName - name of the timefield used for parsing the SQL record
      */

/*
      * @brief MsgMessage 시간 필드의 이름을 설정하기위한 생성자.
      * setFromSqlRecord () 메서드에서 사용됩니다.
      * @param TimeFieldName - SQL 레코드의 구문 분석에 사용 된 시간 필드의 이름
*/

    MsgMessage(const QString &TimeFieldName);


    /**
     * @brief MsgMessage Constructor for setting all internals
     * @param index - Index of this message
     * @param timeStamp - Time stamp of this message should be in seconds
     * @param eventID - Event ID of this message
     */

/*
     * @brief MsgMessage 모든 내부 설정을위한 생성자
     파라미터 : index -이 메세지의 인덱스
     * @param timeStamp -이 메세지의 타임 스탬프는 초 단위 일 필요가 있습니다.
     * @param eventID -이 메세지의 이벤트 ID
*/

    MsgMessage(const quint32 index, const double timeStamp, const QString &message);

    /**
     * @brief Reads a QList of NameValuePair and sets the internal data.
     *        The list must contain a pairs with name "Index", m_TimeFieldName
     *        and "Msg" in order to get a positive return value.
     *        The timeDivider should scale the time stamp to seconds.
     *
     * @param values[in] - Filled list with NameValuePairs
     * @param timeDivider[in] - Devider to scale the timestamp to seconds
     * @return true - all Fields could be read
     *         false - not all data could be read
     */

/*
     * @brief NameValuePair의 QList를 읽고 내부 데이터를 설정합니다.
     * 목록에는 이름이 "Index"인 쌍이 포함되어야합니다. m_TimeFieldName
     * 및 "Msg"를 반환합니다.
     * timeDivider는 타임 스탬프를 초 단위로 스케일합니다.
     *
     * @param values ​​[in] - 채워진리스트와 NameValuePairs
     * @param timeDivider [in] - 타임 스탬프를 초 단위로 스케일하는 데빈다.
     * @return true - 모든 필드를 읽을 수 있음
     * false - 모든 데이터를 읽을 수있는 것은 아닙니다.
*/

    virtual bool setFromNameValuePairList(const QList<NameValuePair> &values, const double timeDivider);

    /**
     * @brief Converts the MsgMessage into an uninterpreted string.
     *        In this case there is nothing to interpret. The internal
     *        string is directly returned.
     * @return The uninterpreted Qstring
     */

/*
     * @brief MsgMessage를 해석되지 않은 문자열로 변환합니다.
     *이 경우 해석 할 내용이 없습니다. 내부
     * 문자열이 직접 반환됩니다.
     * @return 미 해석의 Qstring
*/

    virtual QString toString() const;

private:

    QString m_Message; /// The 'message'
};

/**
 * @brief The MessageFactory class should be used to construct
 *        messages of every type by name.
 */

/*
 MessageFactory 클래스는,
 * 이름별로 모든 유형의 메시지.
*/

class MessageFactory
{
public:
    /**
     * @brief CreateMessageOfType - creates a filled entry of type "type"
     * @param type - Name of the message to be created
     * @param values - Data values for setting up the entry
     * @param timeFieldName - Name of the time filed in data model
     * @param timeDivider - Divider for the time stamp to scale to seconds
     * @return  - smartpointer to new Message
     */

/*
     * @brief CreateMessageOfType - "type"유형의 채워진 항목을 만듭니다.
     파라미터 : type - 작성되는 메세지의 이름
     파라미터 : @param values ​​- 엔트리를 설정하기위한 데이터 치
     * @param timeFieldName - 데이터 모델로 제출 된 시간의 이름
     timeDivider - 타임 스탬프의 디바이더를 초 단위로 확장합니다.
     * @return - 새로운 메시지에 smartpointer
*/

    static MessageBase::Ptr CreateMessageOfType(const QString &type, const QList<QPair<QString, QVariant> > &values, const QString &timeFieldName, const double &timeDivider);
};

/**
 *  Namespace for all copter related stuff	  * 모든 헬리콥터 관련 물건의 네임 스페이스
 */
namespace Copter
{

/**
 * @brief The Mode enum holds all possible flying modes
 *        of a copter
 */

/*
 모드 열거 형은 가능한 모든 비행 모드를 유지합니다.
 * 헬기의
*/

enum Mode
{
    STABILIZE   = 0,
    ACRO        = 1,
    ALT_HOLD    = 2,
    AUTO        = 3,
    GUIDED      = 4,
    LOITER      = 5,
    RTL         = 6,
    CIRCLE      = 7,
    RESERVED_8  = 8,
    LAND        = 9,
    OF_LOITER   = 10,
    DRIFT       = 11,
    RESERVED_12 = 12,
    SPORT       = 13,
    FLIP        = 14,
    AUTOTUNE    = 15,
    POS_HOLD    = 16,
    BRAKE       = 17,
    THROW       = 18,
    AVOID_ADSB  = 19,
    GUIDED_NOGPS= 20,
    SMART_RTL   = 21,
    FLOWHOLD    = 22,
    LAST_MODE           // This must always be the last entry	 항상 마지막 항목이어야합니다.
};

/**
 * @brief Helper class for creating an interpreted output of
 *        all messages generated by copter logs
 */

/*
 * @brief 인터프리터 출력을 생성하기위한 헬퍼 클래스.
 * 헬리콥터 로그에 의해 생성 된 모든 메시지
*/

class MessageFormatter
{
public:
    static QString format(MessageBase::Ptr &p_message);

    static QString format(const ErrorMessage &message);

    static QString format(const ModeMessage &message);

    static QString format(const EventMessage &message);
};

} // namespace Copter	 네임 스페이스 헬리콥터

/**
 *  Namespace for all plane related stuff	  * 모든 비행기 관련 물건에 대한 네임 스페이스
 */
namespace Plane
{

/**
 * @brief The Mode enum holds all possible flying modes
 *        of a plane
 */

/*
 모드 열거 형은 가능한 모든 비행 모드를 유지합니다.
 비행기의 *
*/

enum Mode
{
    MANUAL        = 0,
    CIRCLE        = 1,
    STABILIZE     = 2,
    TRAINING      = 3,
    ACRO          = 4,
    FLY_BY_WIRE_A = 5,
    FLY_BY_WIRE_B = 6,
    CRUISE        = 7,
    AUTOTUNE      = 8,
    LAND          = 9,
    AUTO          = 10,
    RTL           = 11,
    LOITER        = 12,
    RESERVED_13   = 13, // RESERVED FOR FUTURE USE	 미래 사용을 위해 예약 됨
    RESERVED_14   = 14, // RESERVED FOR FUTURE USE	 미래 사용을 위해 예약 됨
    GUIDED        = 15,
    INITIALIZING  = 16,
    QSTABILIZE    = 17,
    QHOVER        = 18,
    QLOITER       = 19,
    QLAND         = 20,
    QRTL          = 21,
    LAST_MODE           // This must always be the last entry	 항상 마지막 항목이어야합니다.
};

/**
 * @brief Helper class for creating an interpreted output of
 *        all messages generated by Plane logs
 */

/*
 * @brief 인터프리터 출력을 생성하기위한 헬퍼 클래스.
 * Plane 로그에 의해 생성 된 모든 메시지
*/

class MessageFormatter
{
public:
    static QString format(MessageBase::Ptr &p_message);

    static QString format(const ModeMessage &message);
};

} // namespace Plane

/**
 *  Namespace for all rover related stuff	 모든 로버 관련 물건의 네임 스페이스
 */
namespace Rover
{

/**
 * @brief The Mode enum holds all possible driving Modes
 *        of a rover
 */

/*
 모드 열거 형은 가능한 모든 운전 모드를 유지합니다.
 * 로버의
*/

enum Mode
{
    MANUAL        = 0,
    RESERVED_1    = 1, // RESERVED FOR FUTURE USE	 미래 사용을 위해 예약 됨
    LEARNING      = 2,
    STEERING      = 3,
    HOLD          = 4,
    RESERVED_5    = 5, // RESERVED FOR FUTURE USE
    RESERVED_6    = 6, // RESERVED FOR FUTURE USE
    RESERVED_7    = 7, // RESERVED FOR FUTURE USE
    RESERVED_8    = 8, // RESERVED FOR FUTURE USE
    RESERVED_9    = 9, // RESERVED FOR FUTURE USE
    AUTO          = 10,
    RTL           = 11,
    RESERVED_12   = 12, // RESERVED FOR FUTURE USE
    RESERVED_13   = 13, // RESERVED FOR FUTURE USE
    RESERVED_14   = 14, // RESERVED FOR FUTURE USE
    GUIDED        = 15,
    INITIALIZING  = 16,
    LAST_MODE           // This must always be the last entry
};


/**
 * @brief Helper class for creating an interpreted output of
 *        all messages generated by Rover logs
 */

/*
 * @brief 인터프리터 출력을 생성하기위한 헬퍼 클래스.
 * Rover 로그에서 생성 된 모든 메시지
*/

class MessageFormatter
{
public:
    static QString format(MessageBase::Ptr &p_message);

    static QString format(const ModeMessage &message);
};

} // Namespace Rover

#endif // ARDUPILOTMAV_H
