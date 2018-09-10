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
 * @file AsciiLogParser.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 09 Okt 2016
 * @brief File providing header for the ascii log parser
 */
/**
 * @file AsciiLogParser.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 09 Okt 2016
 * @brief 아스키 로그 파서에 대한 헤더 제공 파일
 */

#ifndef ASCIILOGPARSER_H
#define ASCIILOGPARSER_H

#include "ILogParser.h"
#include "IParserCallback.h"
#include "LogParserBase.h"
#include "LogdataStorage.h"

/**
 * @brief The AsciiLogParser class is a parser for ASCII ArduPilot
 *        logfiles (.log extension).
 */
/**
 * @brief AsciiLogParser 클래스는 ASCII ArduPilot의 파서입니다.
 * logfiles (.log 확장자).
 */
class AsciiLogParser : public LogParserBase
{
public:

    static const QString s_FMTMessageName;      /// Name of the format (FMT) message
                                                /// 형식 (FMT) 메시지의 이름
    static const QString s_STRTMessageName;     /// Name of the Start (STRT) message
                                                /// 시작 (STRT) 메시지의 이름
    /**
     * @brief AsciiLogParser - CTOR
     * @param storagePtr - Pointer to a valid LogdataStorage used for data storage
     * @param object - Pointer to a valid call back interface
     */
    /**
     * @brief AsciiLogParser - CTOR
     * @param storagePtr - 데이터 저장에 사용되는 유효한 LogdataStorage에 대한 포인터
     * @param object - 유효한 콜백 인터페이스의 포인터
     */
    explicit AsciiLogParser(LogdataStorage::Ptr storagePtr, IParserCallback *object);

    /**
     * @brief ~AsciiLogParser - DTOR
     */
    virtual ~AsciiLogParser();

    /**
     * @brief parse method reads the logfile. Should be called with an
     *        own thread
     * @param logfile - The file which should be parsed
     * @return - Detailed status of the parsing
     */
    /**
     * @brief 구문 분석 메소드는 로그 파일을 읽습니다. 함께 전화해야합니다.
     * 자신의 스레드
     * @param logfile - 해석해야 할 파일
     * @return - 구문 분석의 자세한 상태
     */
    virtual AP2DataPlotStatus parse(QFile &logfile);


private:

    static const char s_TokenSeperator = ',';   /// Token seperator in log file            // 로그 파일의 토큰 seperator

    static const int s_TypeIndex   = 0;         /// Index of message type                  /// 메시지 유형의 색인
    static const int s_IDIndex     = 1;         /// Index of message ID                    /// 메시지 ID의 인덱스
    static const int s_LengthIndex = 2;         /// Index of message length                /// 메시지 길이의 인덱스
    static const int s_NameIndex   = 3;         /// Index of message name                  /// 메시지 이름의 인덱스
    static const int s_FormatIndex = 4;         /// Index of message format                /// 메시지 형식 색인

    static const int s_MinFmtTokens = 5;        /// Min amount of tokens in a FMT line     // FMT 라인의 최소 토큰 양

    /**
     * @brief The asciiDescriptor class provides a specialized typeDescriptor
     *        with an own isValid method.
     */
    /**
     * @brief asciiDescriptor 클래스는 특수한 typeDescriptor를 제공합니다.
     * 자신의 isValid 메서드를 사용합니다.
     */
    class asciiDescriptor : public typeDescriptor
    {
    public:
        virtual bool isValid() const;
    };

    QHash<QString, asciiDescriptor> m_nameToDescriptorMap;   /// hashMap storing a format descriptor for every message type
                                                             /// 모든 메시지 유형에 대한 형식 설명자를 저장하는 // hashMap
    QStringList m_tokensToParse;        /// Tokenized input data to parse
                                        /// 구문 분석 할 토큰 화 된 입력 데이터
    int m_noMessageBytes;               /// Dropped bytes during parsing
                                        /// 파싱하는 동안 바이트 삭제
    QList<asciiDescriptor> m_descriptorForDeferredStorage; /// temp list for storing descriptors without a timestamp field
                                                           /// 타임 스탬프 필드없이 디스크립터를 저장하는 임시 목록

 
    /**
     * @brief parseFMTMessage parses a FMT message into a asciiDescriptor.
     * @param desc asciiDescriptor to be filled
     * @return true - on success, false - parsing failure
     */
    /**
     * @brief parseFMTMessage는 FMT 메시지를 asciiDescriptor로 구문 분석합니다.
     * @param desc asciiDescriptor가 채워지는
     * @return true - 성공시, 거짓 분석 실패
     */
    bool parseFMTMessage(asciiDescriptor &desc);

    /**
     * @brief storeDescriptor validates the descriptor adds a time stamp field
     *        if needed and stores the descriptor in the datamodel
     * @param desc asciiDescriptor to store
     * @return true - success, false - datamodel failure
     */
    /**
     * @brief storeDescriptor는 설명 자의 유효성을 검사하여 타임 스탬프 필드를 추가합니다.
     * 필요한 경우 및 데이터 모델에 설명자를 저장합니다.
     * @param desc asciiDescriptor를 저장합니다.
     * @return true - 성공, 거짓 - 데이터 모델 실패
     */
 
    bool storeDescriptor(asciiDescriptor desc);

    /**
     * @brief extendedStoreDescriptor just calls storeDescriptor on all elements
     *        hold in m_descriptorForDeferredStorage, then clears the container
     *        and stores the descriptor passed
     * @param desc asciiDescriptor to be stored
     * @return true - success, false - datamodel failure
     */
    /**
     * @brief extendedStoreDescriptor는 모든 요소에 대해 storeDescriptor를 호출합니다.
     * m_descriptorForDeferredStorage를 유지 한 다음 컨테이너를 지 웁니다.
     * 전달 된 설명자를 저장합니다.
     * @param desc asciiDescriptor가 저장됩니다.
     * @return true - 성공, 거짓 - 데이터 모델 실패
     */
    bool extendedStoreDescriptor(const asciiDescriptor &desc);

    /**
     * @brief parseDataByDescriptor parses the data like described in the
     *        descriptor which is referenced by the message name.
     * @param NameValuePairList - conatiner for the parsed data
     * @return true - success, false - parsing failed
     */
    /**
     * @ brief parseDataByDescriptor는
     * 메시지 이름에 의해 참조되는 설명자.
     * @param NameValuePairList - 해석 된 데이터의 양수 처리자
     * @return true - 성공, 거짓 - 구문 분석에 실패했습니다.
     */
    bool parseDataByDescriptor(QList<NameValuePair> &NameValuePairList, const asciiDescriptor &desc);
};

#endif // ASCIILOGPARSER_H
