/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2016 APM_PLANNER PROJECT <http://www.ardupilot.com>

This file is part of the APM_PLANNER project

    APM_PLANNER is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    APM_PLANNER is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with APM_PLANNER. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/
/**
 * @file AP2DataPlotStatus.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 21 sept 2016
 * @brief File providing header for the AP2DataPlotStatus
 */
/* *
 * @file AP2DataPlotStatus.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @ 날짜 2016 년 9 월 21 일
 * @brief AP2DataPlotStatus에 대한 헤더 제공 파일
 */


#ifndef AP2DATAPLOTSTATUS_H
#define AP2DATAPLOTSTATUS_H

#include <QString>
#include <QVector>

// Mavlink include is only used for MAV_TYPE constant defined in the protocol
// Mavlink include는 프로토콜에 정의 된 MAV_TYPE 상수에만 사용됩니다.
#include <mavlink_types.h>
extern mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS]; // defined in src/main.cc
#include <mavlink.h>

/**
 * @brief The AP2DataPlotStatus class is a helper class desinged as status type for
 *        the log parsing.
 *        It contains the final state of parsing as well as all error strings inserted
 *        with the corruptDataRead(), corruptFMTRead() etc. methods during the parsing
 *        process.
 */
/* *
 * @brief AP2DataPlotStatus 클래스는 상태 유형으로 지정된 헬퍼 클래스입니다.
 * 로그 파싱.
 * 삽입 된 모든 오류 문자열뿐만 아니라 파싱의 최종 상태를 포함합니다.
 * 파싱하는 동안 corruptDataRead (), corruptFMTRead () 등의 메소드 사용
 * 프로세스.
 */
class AP2DataPlotStatus
{
public:

    /**
     * @brief The parsingState enum
     *        All possible parsing states
     */
    /* *
     * @brief parsingState 열거 형
     * 가능한 모든 파싱 상태
     */
    enum parsingState
    {
        OK,                 /// Perfect result// / 완벽한 결과
        FmtError,           /// Corrupt Format description.// / 부패 형식 설명.
        TruncationError,    /// The log was truncated due to errors @ the end// / @ 오류로 인해 로그가 잘린 경우
        TimeError,          /// The log contains corrupt time data// / 로그에 손상된 시간 데이터가 있습니다.
        DataError           /// Data can be corrupted or incomplete// / 데이터가 손상되거나 불완전 할 수 있습니다.
    };

    /**
     * @brief AP2DataPlotStatus CTOR
     */
    AP2DataPlotStatus();

    /**
     * @brief validDataRead
     *        Shall be called if a logline was read successful. Used to
     *        determine if the error(s) are only at the end of the log.
     *        Should be inline due to the high calling frequency.
     */
    /* *
     * @brief validDataRead
     * 로그 라인이 성공적으로 읽혀지면 호출해야합니다. 사용
     * 오류가 로그 끝에서만 있는지 확인하십시오.
     * 호출 빈도가 높기 때문에 인라인해야합니다.
     */
    inline void validDataRead()
    {
        // Rows with time errors will stored too, so they have to handeled like
        // the OK ones.
        // 시간 오류가있는 행도 저장되므로, 다음과 같이
        // 정상적인 것.
        if (!((m_lastParsingState == OK)||(m_lastParsingState == TimeError)))
        {
            // insert entry with state OK to mark data is ok.
            // 상태가 OK 인 항목을 삽입하여 데이터를 확인하십시오.
            m_errors.push_back(errorEntry());
            m_lastParsingState = OK;
            // When here we know we had an error and now data is OK again
            // Set to data error as we cannot predict whats wrong
            // 여기에 우리가 오류를 알았고 이제 데이터가 다시 OK입니다.
            // 무엇이 잘못되었는지 예측할 수 없으므로 데이터 오류로 설정합니다.
            m_globalState = DataError;
        }
    }

    /**
     * @brief corruptDataRead
     *        Shall be called when ever an error occurs while parsing
     *        a data package.
     *
     * @param index - The log index the error occured
     * @param errorMessage - Error message describing the error reason
     */
    /* *
     * @brief corruptDataRead
     * 파싱하는 동안 오류가 발생하면 호출해야합니다.
     * 데이터 패키지.
     *
     파라미터 : index - 에러가 발생한 로그 인덱스
     파라미터 : errorMessage - 에러의 이유를 설명하는 에러 메세지
     */
    void corruptDataRead(const int index, const QString &errorMessage);

    /**
     * @brief corruptFMTRead
     *        Shall be called when ever an error occurs while parsing
     *        a format package.
     *
     * @param index - The log index the error occured
     * @param errorMessage - Error message describing the error reason
     */
    /* *
     * @brief corruptFMTRead
     * 파싱하는 동안 오류가 발생하면 호출해야합니다.
     * 형식 패키지.
     *
     파라미터 : index - 에러가 발생한 로그 인덱스
     파라미터 : errorMessage - 에러의 이유를 설명하는 에러 메세지
     */
    void corruptFMTRead(const int index, const QString &errorMessage);

    /**
     * @brief corruptTimeRead
     *        Shall be called when ever a time error occurs while parsing
     *        any data.
     *
     * @param index - The log index the error occured
     * @param errorMessage - Error message describing the error reason
     */
    /* *
     * @brief corruptTimeRead
     * 파싱하는 동안 시간 오류가 발생하면 호출해야합니다.
     * 모든 데이터.
     *
     파라미터 : index - 에러가 발생한 로그 인덱스
     파라미터 : errorMessage - 에러의 이유를 설명하는 에러 메세지
     */
    void corruptTimeRead(const int index, const QString &errorMessage);

    /**
     * @brief setNoMessageBytes
     *        Stores the number of bytes which could not be parsed and adds
     *        them to the output
     *
     * @param noMessageBytes - number of bytes which could not be parsed
     */
    /* *
     * @brief setNoMessageBytes
     * 파싱 할 수없고 추가 할 수있는 바이트 수를 저장합니다.
     * 출력물에
     *
     * @param noMessageBytes - 해석 할 수 없었던 바이트 수
     */
    void setNoMessageBytes(const int noMessageBytes);

    /**
     * @brief setMavType
     *        Set the MAV_TYPE of the loaded log.
     *
     * @param type - MAV_TYPE
     */
    /* *
     * @brief setMavType
     *로드 된 로그의 MAV_TYPE을 설정하십시오.
     *
     * @param 유형 - MAV_TYPE
     */
    void setMavType(const MAV_TYPE type);

    /**
     * @brief getMavType
     *        Gets the stored MAV_TYPE.
     *
     * @return The stored MAV_TYPE
     */
    /* *
     * @brief getMavType
     * 저장된 MAV_TYPE을 가져옵니다.
     *
     * @return 저장된 MAV_TYPE
     */
    MAV_TYPE getMavType() const;

    /**
     * @brief getParsingState
     *        Delivers the final state of the log parsing. The value
     *        is only valid if parsing is finished.
     *
     * @return - The parsing state - @see parsingState
     */
    /* *
     * @brief getParsingState
     * 로그 구문 분석의 최종 상태를 제공합니다. 가치
     *는 구문 분석이 끝난 경우에만 유효합니다.
     *
     * @return - 구문 분석 상태 - @see parsingState
     */
    parsingState getParsingState() const;

    /**
     * @brief getErrorOverview
     *        Creates an overview of errors occured. Type and number are listed
     *
     *  @return - String containing overview data
     */
    /* *
     * @brief getErrorOverview
     * 발생한 오류에 대한 개요를 작성합니다. 유형 및 번호가 나열됩니다.
     *
     * @return - 개요 데이터가 포함 된 문자열
     */
    QString getErrorOverview() const;

    /**
     * @brief getDetailedErrorText
     *        Creates a text containing all errormessages inserted during
     *        parsing. One line for each error.
     *
     * @return - multi line string with all error messages.
     */
    /* *
     * @brief getDetailedErrorText
     * 모든 오류 메시지가 포함 된 텍스트를 만듭니다.
     * 파싱. 각 오류마다 한 행씩.
     *
     * @return - 모든 에러 메시지를 포함한 멀티 라인 문자열.
     */
    QString getDetailedErrorText() const;

private:
    /**
     * @brief The errorEntry struct
     *        holds all data describing the error
     */
    /* *
     * @brief errorEntry struct
     *는 오류를 설명하는 모든 데이터를 보유합니다.
     */
    struct errorEntry
    {
        parsingState m_state;
        int m_index;
        QString m_errortext;

        errorEntry() : m_state(OK), m_index(0){}
        errorEntry(const parsingState state, const int index, const QString &text) :
                   m_state(state), m_index(index), m_errortext(text) {}
    };

    parsingState m_lastParsingState;        /// The internal parsing state since last call// 마지막 호출 이후의 내부 파싱 상태
    parsingState m_globalState;             /// Reflecting the overall parsing state// 전체 파싱 상태 반영
    QVector<errorEntry> m_errors;           /// For storing all error entries// 모든 오류 항목 저장
    MAV_TYPE     m_loadedLogType;           /// Type of the loaded log (QUAD, PLANE, ROVER...)// 로드 된 로그의 유형 (QUAD, PLANE, ROVER ...)
    int m_noMessageBytes;                   /// Shall store the No Message Bytes of the log// 로그의 메시지 없음 바이트를 저장합니다.
};


#endif // AP2DATAPLOTSTATUS_H
