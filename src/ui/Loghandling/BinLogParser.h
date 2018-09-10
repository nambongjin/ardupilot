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
 * @file BinLogParser.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 14 Jul 2016
 * @brief File providing header for the binary log parser	 바이너리 로그 파서에 헤더를 제공하는 파일
 */

#ifndef BINLOGPARSER_H
#define BINLOGPARSER_H

#include "ILogParser.h"
#include "IParserCallback.h"
#include "LogParserBase.h"
#include "LogdataStorage.h"

/**
 * @brief The BinLogParser class is a parser for binary ArduPilot
 *        logfiles aka flash logs
 */

/*
 * BriefLogParser 클래스는 ArduPilot 바이너리 파서이다.
 * 로그 파일 일명 플래시 로그
*/

class BinLogParser : public LogParserBase
{
public:

    /**
     * @brief BinLogParser - CTOR
     * @param storagePtr - Pointer to a valid LogdataStorage used for data storage
     * @param object - Pointer to a valid call back interface
     */

/*
     * @brief BinLogParser - CTOR
     * @param storagePtr - 데이터 저장에 사용되는 유효한 LogdataStorage에 대한 포인터
     * @param object - 유효한 콜백 인터페이스의 포인터
*/

    explicit BinLogParser(LogdataStorage::Ptr storagePtr, IParserCallback *object);

    /**
     * @brief ~BinLogParser - DTOR
     */
    virtual ~BinLogParser();

    /**
     * @brief parse method reads the logfile. Should be called with an
     *        own thread
     * @param logfile - The file which should be parsed
     * @return - Detailed status of the parsing
     */

/*
     * @brief 구문 분석 메소드는 로그 파일을 읽습니다. 함께 전화해야합니다.
     * 자신의 스레드
     * @param logfile - 해석해야 할 파일
     * @return - 구문 분석의 자세한 상태
*/

    virtual AP2DataPlotStatus parse(QFile &logfile);

private:

    static const quint8 s_FMTMessageType  = 0x80; /// Type Id of the format (FMT) message	 형식 (FMT) 메시지의 유형 ID
 
    static const int s_MinHeaderSize = 5;        /// Minimal size to be able to start parsing	 파싱을 시작할 수있는 최소 크기
    static const int s_HeaderOffset  = 3;        /// byte offset after successful header parsing	 헤더 파싱 성공 후 바이트 오프셋
    static const quint8 s_StartByte1 = 0xA3;     /// Startbyte 1 is always first byte in one message	 Startbyte 1은 항상 하나의 메시지에서 첫 번째 바이트입니다.
    static const quint8 s_StartByte2 = 0x95;     /// Startbyte 2 is always second byte in one message	 Startbyte 2는 한 메시지에서 항상 두 번째 바이트입니다.

    static const int s_FMTNameSize   = 4;        /// Size of the name field in FMT message	 FMT 메시지의 이름 필드 크기
    static const int s_FMTFormatSize = 16;       /// Size of the format field in FMT message	 FMT 메시지의 형식 필드 크기
	    static const int s_FMTLabelsSize = 64;       /// Size of the comma delimited names field in FMT message	 MT 메시지의 쉼표로 구분 된 이름 필드의 크기

    static const quint32 s_FloatSoftNaN  = 0x7FC04152;         /// Value to detect a quiet/soft float NaN from ardupilot	 ardupilot의 조용한 / 부드러운 플로트 NaN을 검출하는 값
    static const quint64 s_DoubleSoftNaN = 0x7FF952445550490A; /// Value to detect a quiet/soft double NaN from ardupilot	 ardupilot에서 조용한 / 부드러운 이중 NaN을 탐지하는 값


    /**
     * @brief The binDescriptor class provides a specialized typeDescriptor
     *        with an own isValid method.
     */

/*
     * @brief binDescriptor 클래스는 특수한 typeDescriptor를 제공합니다.
     * 자신의 isValid 메서드를 사용합니다.
*/

    class binDescriptor : public typeDescriptor
    {
    public:
        virtual bool isValid() const;
    };

    QByteArray m_dataBlock;                 /// Data buffer for parsing.	 구문 분석을위한 데이터 버퍼.
    int m_dataPos;                          /// bytecounter for running through the data packet.	 데이터 패킷을 통해 실행하기위한 bytecounter.
    quint32 m_messageType;                  /// Holding type of the actual message.	 실제 메시지의 보류 유형.

    QHash<quint32, binDescriptor> m_typeToDescriptorMap;   /// hashMap storing a format descriptor for every message type	 모든 메시지 유형에 대한 형식 설명자를 저장하는 // hashMap

    QList<binDescriptor> m_descriptorForDeferredStorage; /// temp list for storing descriptors without a timestamp field	 타임 스탬프 필드없이 디스크립터를 저장하는 임시 목록

    /**
     * @brief headerIsValid checks the first 2 start bytes
     *        and extracts the message type which is stored in m_messageType.
     *
     * @return true - header is valid, false otherwise
     */

/*
     * @brief headerIsValid는 처음 2 바이트를 검사합니다.
     * m_messageType에 저장된 메시지 유형을 추출합니다.
     *
     * @return true - 헤더가 유효하고, 그렇지 않으면 false
*/

    bool headerIsValid();

    /**
     * @brief parseFMTMessage parses a FMT message into a binDescriptor
     *        and removes the parsed data from the input array
     * @param desc binDescriptor to be filled
     * @return true - on success, false - not enough data to parse the message
     */

/*
     * @brief parseFMTMessage는 FMT 메시지를 binDescriptor로 구문 분석합니다.
     * 그리고 입력 배열에서 파싱 된 데이터를 제거한다.
     * @param desc binDescriptor를 채 웁니다.
     * @return true - 성공시, false - 메시지를 분석 할 데이터가 충분하지 않음
*/

    bool parseFMTMessage(binDescriptor &desc);

    /**
     * @brief storeDescriptor validates the descriptor adds a time stamp field
     *        if needed and stores it in the datamodel
     * @param desc binDescriptor to store
     * @return true - success, false - datamodel failure
     */

/*
     * @brief storeDescriptor는 설명 자의 유효성을 검사하여 타임 스탬프 필드를 추가합니다.
     * 필요한 경우 데이터 모델에 저장
     * 저장하려면 @param desc binDescriptor
     * @return true - 성공, 거짓 - 데이터 모델 실패
*/

    bool storeDescriptor(binDescriptor desc);

    /**
     * @brief extendedStoreDescriptor just calls storeDescriptor on all elements
     *        hold in m_descriptorForDeferredStorage, then clears the container
     *        and stores the descriptor passed
     * @param desc binDescriptor to be stored
     * @return true - success, false - datamodel failure
     */

/*
     * @brief extendedStoreDescriptor는 모든 요소에 대해 storeDescriptor를 호출합니다.
     * m_descriptorForDeferredStorage를 유지 한 다음 컨테이너를 지 웁니다.
     * 전달 된 설명자를 저장합니다.
     저장된 @param desc binDescriptor
     * @return true - 성공, 거짓 - 데이터 모델 실패
*/



    bool extendedStoreDescriptor(const binDescriptor &desc);

    /**
     * @brief parseDataByDescriptor parses the data like described in the
     *        descriptor which is referenced by m_messageType. After the
     *        parsing the used data is removed from the data array
     * @param NameValuePairList - conatiner for the paresed data
     * @return
     */

/*
     * @ brief parseDataByDescriptor는
     m_messageType에 의해 참조되는 * 기술자. 후
     * 사용 된 데이터를 파싱하면 데이터 배열에서 제거됩니다.
     * @param NameValuePairList - 병행 처리 된 데이터의 양성자
     * @ 반환
*/

    bool parseDataByDescriptor(QList<NameValuePair> &NameValuePairList, const binDescriptor &desc);

};

#endif // BINLOGPARSER_H
