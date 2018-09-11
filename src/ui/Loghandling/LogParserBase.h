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
 * @file LogParserBase.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 11 okt 2016
 * @brief File providing header for the log parser base class
 */
/* *
 * @file LogParserBase.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 11 okt 2016
 * @brief 로그 파서 기본 클래스의 헤더 제공 파일
 */

#ifndef LOGPARSERBASE_H
#define LOGPARSERBASE_H

#include "ILogParser.h"
#include "IParserCallback.h"
#include "LogdataStorage.h"

/**
 * @brief The LogParserBase class provides a base class for all log
 *        parsers.
 */
/* *
 * @brief LogParserBase 클래스는 모든 로그에 대한 기본 클래스를 제공합니다.
 * 파서.
 */
class LogParserBase : public ILogParser
{
public:
    /**
     * @brief LogParserBase - CTOR
     * @param storagePtr - Pointer to a valid LogdataStorage used for data storage
     * @param object - Pointer to a valid call back interface
     */
    /* *
     * @brief LogParserBase - CTOR
     * @param storagePtr - 데이터 저장에 사용되는 유효한 LogdataStorage에 대한 포인터
     * @param object - 유효한 콜백 인터페이스의 포인터
     */
    explicit LogParserBase(LogdataStorage::Ptr storagePtr, IParserCallback *object);

    /**
     * @brief ~LogParserBase - DTOR
     */
    virtual ~LogParserBase();

    /**
     * @brief stopParsing forces the parse method to return immediately.
     *        Shall be used for cancelling or stopping.
     */
    /* *
     * @brief stopParsing (은)는, 해석 메소드가 즉시 복귀하도록 (듯이) 강제합니다.
     * 취소 또는 중지 할 때 사용하십시오.
     */
    virtual void stopParsing();

protected:

    /**
     * @brief The timeStampType struct
     *        Used to hold the name and the scaling of a time stamp.
     */
    /* *
     * @brief timeStampType 구조체
     * 타임 스탬프의 이름과 스케일링을 유지하는 데 사용됩니다.
     */
    struct timeStampType
    {
        QString m_name;     /// Name of the time stamp// / 타임 스탬프 이름
        double  m_divisor;  /// Divisor to scale time stamp to seconds// 타임 스탬프를 초 단위로 스케일하는 제수

        timeStampType() : m_divisor(0.0) {}
        timeStampType(const QString &name, const double divisor) : m_name(name), m_divisor(divisor) {}
        bool valid()
        {
            return m_name.size() != 0;
        }
    };

    /**
     * @brief The typeDescriptor struct
     *        Used to hold all data needed to describe a message type
     */
    /* *
     * @brief typeDescriptor 구조체
     * 메시지 유형을 설명하는 데 필요한 모든 데이터를 보유하는 데 사용됩니다.
     */
    class typeDescriptor
    {
    public:

        static constexpr quint32 s_InvalidID = 0xFFFFFFFF;

        typeDescriptor();

        virtual ~typeDescriptor() {}

        /**
         * @brief finalize sets the m_hasTimeStamp and the m_timeStampIndex by trying to
         *        find the Timestamp name in m_labels
         * @param timeStamp - time stamp to search for.
         */
        /* *
         * @brief finalize는 다음을 시도하여 m_hasTimeStamp와 m_timeStampIndex를 설정합니다.
         * m_labels에서 타임 스탬프 이름 찾기
         * @param timeStamp - 검색하는 타임 스탬프
         */
        virtual void finalize(const timeStampType &timeStamp);

        /**
         * @brief addTimeStampField adds a timestamp field to the descriptor.
         * @param timestamp - time stamp type which should be added
         */
        /* *
         * @brief addTimeStampField는 기술자에 타임 스탬프 필드를 추가합니다.
         * @param timestamp - 추가되는 타임 스탬프 형
         */
        virtual void addTimeStampField(const timeStampType &timestamp);

        /**
         * @brief replaceLabelName replaces a special label in m_labels
         * @param oldName - name string to search for
         * @param newName - the new name to replace the old one
         */
        /* *
         * @brief replaceLabelName은 m_labels의 특수 레이블을 대체합니다.
         * @param oldName - 검색하는 이름 캐릭터 라인
         * @param newName - 이전의 이름을 옮겨 놓을 새로운 이름
         */
        virtual void replaceLabelName(const QString &oldName, const QString &newName);

        virtual QString getLabelAtIndex(int index) const;
        virtual bool hasNoTimestamp() const;
        virtual bool isValid() const;

        quint32 m_ID;           /// ID of the message - mainly used for validation// / 메시지의 ID - 주로 유효성 검사에 사용됩니다.
        int m_length;           /// Length of the message// / 메시지 길이
        QString m_name;         /// Name of the message// / 메시지 이름
        QString m_format;       /// Format string like "QbbI"// / "QbbI"와 같은 형식 문자열
        QStringList m_labels;   /// List of labels for each value in message (colums).// 메시지의 각 값에 대한 레이블 목록 (열).
        bool m_hasTimeStamp;    /// true if descriptor has valid Timestamp.// 설명자에 유효한 타임 스탬프가있는 경우 true입니다.
        int m_timeStampIndex;   /// contains the index pointing to the time stamp field.// / 타임 스탬프 필드를 가리키는 인덱스를 포함합니다.
    };

    typedef QPair<QString, QVariant> NameValuePair;          /// Type holding Lablestring and its value// Lablestring 및 해당 값을 보유하고있는 유형

    IParserCallback *m_callbackObject;      /// Pointer to callback interface.// / 콜백 인터페이스에 대한 포인터.
    LogdataStorage::Ptr m_dataStoragePtr;   /// Pointer to the datamodel for storing the data// 데이터를 저장하기위한 데이터 모델에 대한 포인터

    bool m_stop;                            /// Flag indicating to stop parsing// / 구문 분석을 중지하도록 지시하는 플래그
    quint64 m_MessageCounter;               /// Simple counter showing number of message wich is currently parsed// 현재 구문 분석중인 메시지 수를 보여주는 간단한 카운터

    MAV_TYPE m_loadedLogType;               /// Mav type of the log - will be populated during parsing// 로그의 Mav 유형 - 파싱하는 동안 채워집니다.
    AP2DataPlotStatus m_logLoadingState;    /// State of the parser// 파서의 상태

    timeStampType m_activeTimestamp;        /// the detected timestamp used for parsing// 파싱에 사용 된 감지 된 타임 스탬프

    quint32 m_idUnitMessage;                /// to store the Type Id of the unit (UNIT) message// 유닛의 유닛 ID (UNIT) 메시지 저장
    quint32 m_idMultMessage;                /// to store the Type Id of the multiplier (MULT) message// 승수 (MULT) 메시지의 유형 ID 저장
    quint32 m_idFMTUMessage;                /// to store the Type Id of the Format unit multiplier (FMTU) message// 형식 단위 배율기 (FMTU) 메시지의 유형 ID 저장

    bool m_hasUnitData;                     /// True if parsed log contains unit data// 구문 분석 된 로그에 유닛 데이터가 포함되어 있으면 true


    /**
     * @brief checkForValidTimestamp verifies whether the descriptor has a
     *        time stamp field. If the descriptor has one it sets the internal
     *        m_activeTimestamp.
     * @param desc - the binDescriptor to check
     */
    /* *
     * @brief checkForValidTimestamp는 디스크립터에
     * 시간 소인 필드. 디스크립터에 디스크립터가 있으면
     * m_activeTimestamp.
     파라미터 : desc - 체크 대상의 binDescriptor
     */
    void checkForValidTimestamp(typeDescriptor &desc);

    /**
     * @brief storeNameValuePairList stores the NameValuePairList into the
     *        datamodel. Adds a timestamp if needed
     * @param NameValuePairList to be stored
     * @return true - success, false - datamodel failure
     */
    /* *
     * @brief storeNameValuePairList는 NameValuePairList를에 저장합니다.
     * 데이터 모델. 필요한 경우 타임 스탬프를 추가합니다.
     * 저장 될 @ValueNameValuePairList
     * @return true - 성공, 거짓 - 데이터 모델 실패
     */
    bool storeNameValuePairList(QList<NameValuePair> &NameValuePairList, const typeDescriptor &desc);

    /**
     * @brief extendedStoreNameValuePairList checks for the unit data types (UNIT, MULT, FMTU)
     *        and inserts them correctly into the datamodel. All other data will be passed to
     *        the storeNameValuePairList() method.
     * @param NameValuePairList to be stored
     * @param desc - matching descriptor for this NameValuePairList
     * @return true success, false otherwise
     */
    /* *
     * @brief extendedStoreNameValuePairList는 단위 데이터 유형 (UNIT, MULT, FMTU)을 확인합니다.
     * 데이터 모델에 올바르게 삽입합니다. 다른 모든 데이터는로 전달됩니다.
     * storeNameValuePairList () 메소드.
     * 저장 될 @ValueNameValuePairList
     * @param desc -이 NameValuePairList에 일치하는 기술자
     성공했을 경우는 true, 그렇지 않은 경우는 false
     */
    bool extendedStoreNameValuePairList(QList<NameValuePair> &NameValuePairList, const typeDescriptor &desc);

    /**
     * @brief handleTimeStamp does all time stamp handling. It checks if the time is increasing and
     *        if not it handles error generation and offset management.
     * @param valuepairlist - value pair list to read/store the timestamp.
     * @param timeStampIndex - Index in list where the timestamp resides.
     */
    /* *
     * @brief handleTimeStamp는 모든 타임 스탬프 처리를 수행합니다. 시간이 증가하고 있는지 확인합니다.
     * 그렇지 않으면 오류 생성 및 오프셋 관리를 처리합니다.
     * @param valuepairlist - 타임 스탬프를 읽고 저장하는 값 쌍 목록.
     * @param timeStampIndex - 타임 스탬프가있는리스트의 인덱스.
     */
    void handleTimeStamp(QList<NameValuePair> &valuepairlist, const typeDescriptor &desc);

    /**
     * @brief detectMavType tries to detect the MAV type from the data in a
     *        value pair list.
     * @param valuepairlist - value pair list to do the check on
     */
    /* *
     * @brief detectMavType은 MAV 형식의 데이터에서 MAV 형식을 검색하려고 시도합니다.
     * 값 쌍 목록.
     * @param valuepairlist - 체크를 실시하는 값의 페어리스트
     */
    void detectMavType(const QList<NameValuePair> &valuepairlist);

    /**
     * @brief repairMessage tries to repair a message to match the descriptor.
     *        Missing fields will be added and set to 0. If there are too many fields
     *        they are cut.
     * @param NameValuePairList - list that needs repair.
     * @param descriptor - descriptor describing the message type.
     * @return true - message is ok, false otherwise.
     */
    /* *
     * @brief repairMessage는 설명자와 일치하는 메시지를 복구하려고합니다.
     * 누락 된 필드가 추가되고 0으로 설정됩니다. 너무 많은 필드가있는 경우
     * 그들은 자른다.
     * @param NameValuePairList - 수리가 필요한리스트.
     파라미터 : descriptor - 메세지 타입을 설명하는 기술자.
     * @return true - 메시지는 ok이며, 그렇지 않으면 false입니다.
     */
    bool repairMessage(QList<NameValuePair> &NameValuePairList, const typeDescriptor &desc);

    /**
     * @brief nextValidTimestamp delivers a valid time stamp that can be added to messages. Offset
     *        handling is done later so its important to use this method to get a good timestamp.
     *
     * @return - valid time stamp
     */
    /* *
     * @brief nextValidTimestamp는 메시지에 추가 할 수있는 유효한 타임 스탬프를 전달합니다. 오프셋
     * 처리는 나중에 수행되므로 중요한 타임 스탬프를 얻기 위해이 메서드를 사용하는 것이 중요합니다.
     *
     * @return - 유효한 타임 스탬프
     */
    quint64 nextValidTimestamp();

    /**
     * @brief specialDescriptorHandling does some extra handling for speial descriptor. As some
     *        message types need special treatment and / or deliver special information they can
     *        be handled inside this method.
     */
    /* *
     * @brief specialDescriptorHandling은 speial 서술자에 대한 추가 처리를 수행합니다. 일부로서
     * 메시지 유형은 특별한 치료가 필요하거나 그들이 할 수있는 특별한 정보를 제공해야합니다.
     *이 메서드 내에서 처리됩니다.
     */
    void specialDescriptorHandling(typeDescriptor &desc);


private:
    int m_timeErrorCount;                            /// Counter for time errors used to avoid log flooding// 로그 홍수를 피하기 위해 사용 된 시간 오류 카운터

    QList<timeStampType> m_possibleTimestamps;       /// List of possible timestamps. Filled in CTOR// / 가능한 타임 스탬프 목록. CTOR에 채워짐
    QHash<QString, quint64> m_lastValidTimePerType;  /// Contains the last valid timestamp for each type (which have a timestamp)// 각 유형 (타임 스탬프가있는)에 대한 마지막 유효한 타임 스탬프를 포함합니다.
    quint64 m_highestTimestamp;                      /// Contains always the biggest timestamp// 항상 가장 큰 타임 스탬프를 포함합니다.
    quint64 m_timestampOffset;                       /// Holds a timestamp offset in case the log contains 2 or more flights// 로그에 두 개 이상의 항공편이 포함되어있는 경우 타임 스탬프 오프셋을 유지합니다.
};

#endif // LOGPARSERBASE_H
