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
 * @file TlogParser.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 22 Okt 2016
 * @brief File providing header for the tlog log parser	 로그 파서의 헤더 제공 파일
 */	 

#ifndef TLOGPARSER_H
#define TLOGPARSER_H

#include "ILogParser.h"
#include "IParserCallback.h"
#include "LogParserBase.h"
#include "MAVLinkDecoder.h"
#include "LogdataStorage.h"

/**
 * @brief The TlogParser class is a parser for tlog ArduPilot
 *        logfiles (.tlog extension).
 */

/*
 * @brief TlogParser 클래스는 tlog ArduPilot의 파서입니다.
 * logfiles (.tlog 확장자).
*/

class TlogParser : public QObject, public LogParserBase
{
    Q_OBJECT
public:
    /**
     * @brief TlogParser - CTOR
     * @param storagePtr - Pointer to a valid LogdataStorage used for data storage
     * @param object - Pointer to a valid call back interface
     */

/*
     * @brief TlogParser - CTOR
     * @param storagePtr - 데이터 저장에 사용되는 유효한 LogdataStorage에 대한 포인터
     * @param object - 유효한 콜백 인터페이스의 포인터
*/

    explicit TlogParser(LogdataStorage::Ptr storagePtr, IParserCallback *object);

    /**
     * @brief ~TlogParser - DTOR
     */
    virtual ~TlogParser();

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

    /**
     * @brief newValue - Callback for the mavlink decoder - called for every decoded value
     * @param uasId - UAS ID
     * @param name  - Name of the value
     * @param unit  - Unit / data type
     * @param value - the value itself
     * @param msec  - some sort of timestamp
     */

/*
     * @brief newValue - mavlink 디코더의 콜백 - 디코드 된 모든 값을 호출합니다.
     * @param uasId - UAS ID
     파라미터 : name - 값의 이름
     * @param unit - 유닛 / 데이터 형
     파라미터 : value - 값 자체
     * @param msec - 일종의 타임 스탬프
*/

    void newValue(int uasId, const QString &name, const QString &unit, const QVariant &value, quint64 msec);

    /**
     * @brief newTextValue - Callback for the mavlink decoder - called for every decoded string
     * @param uasId         - UAS ID
     * @param componentId   - Component ID
     * @param severity      - severity
     * @param text          - The text
     */

/*
     * @brief newTextValue - mavlink 디코더의 콜백 - 디코드 된 모든 문자열에 대해 호출됩니다.
     * @param uasId - UAS ID
     * @param componentId - 구성 요소 ID
     * @param의 severity - severity
     * @param text - 텍스트
*/

    void newTextValue(int uasId, int componentId, int severity, const QString &text);

private:

    static const quint8 s_GCSType = 255;  /// sys id of Ground station

    /**
     * @brief The tlogDescriptor class provides a specialized typeDescriptor
     *        with an own isValid method.
     */

/*
     * @brief tlogDescriptor 클래스는 특수한 typeDescriptor를 제공한다.
     * 자신의 isValid 메서드를 사용합니다.
*/

    class tlogDescriptor : public typeDescriptor
    {
    public:
        virtual bool isValid() const;
    };

    QHash<QString, tlogDescriptor> m_nameToDescriptorMap;   /// hashMap storing a format descriptor for every message type	 모든 메시지 유형에 대한 형식 설명자를 저장하는 // hashMap

    QByteArray m_dataBlock;                 /// Data buffer for parsing.	 구문 분석을위한 데이터 버퍼.

    QScopedPointer<MAVLinkDecoder> m_mavDecoderPtr;     /// pointer to mavlink decoder	 mavlink 디코더에 대한 포인터

    quint8 m_lastModeVal;       /// holds the current mode used to detect changes	 변경을 감지하는 데 사용되는 현재 모드를 보유합니다.

    QList<NameValuePair> *mp_ReceiveData;  /// pointer to the data structure for receiving data	 데이터 수신을위한 데이터 구조체에 대한 포인터

    /**
     * @brief addMissingDescriptors adds the missing type descriptors to the
     *        database. tlogs do not have a message for MODE or MSG messages
     *        but their meaning can be extracted from other messages. descriptors
     *        for MODE and MSG are added to the DB.
     */

/*
     * @brief addMissingDescriptors는 누락 된 유형 설명자를
     * 데이터베이스. tlogs에 MODE 또는 MSG 메시지에 대한 메시지가 없습니다.
     * 그 의미는 다른 메시지에서 추출 할 수 있습니다. 기술 어
     MODE 및 MSG에 대한 *가 DB에 추가됩니다.
*/

    void addMissingDescriptors();

    /**
     * @brief parseDescriptor extracts the descriptor data from tlog messages.
     *        It reads its data direcly from the mavlink decoder.
     * @param desc - The descriptor is filled.
     * @return - true - success, false - data could not be parsed
     */

/*
     * @brief parseDescriptor는 tlog 메시지에서 설명자 데이터를 추출합니다.
     * mavlink 디코더에서 데이터를 직접 읽습니다.
     * @param desc - 기술자가 채워집니다.
     * @return - true - 성공, 거짓 - 데이터를 구문 분석 할 수 없습니다.
*/

    bool parseDescriptor(tlogDescriptor &desc);

    /**
     * @brief extractDataFields extracts the datafields of a descriptor. it is a helper
     *        used by parseDescriptor method. Maily handles the differences between single
     *        and array data.
     * @param desc - The tlog descriptor to add the datatfiled info
     * @param fieldInfo - the mavlink fieldinfo descriptor where the data is extracted from
     * @param format - the format type for the field
     * @param size - the size of the data field in bytes
     */

/*
     * @brief extractDataFields는 디스크립터의 데이터 필드를 추출합니다. 그것은 도우미이다.
     parseDescriptor 메소드에 의해 사용됩니다. Maily는 싱글
     * 및 배열 데이터.
     * @param desc - datatfiled 정보를 추가하는 tlog 서술자
     * @param fieldInfo - 데이터를 추출하는 mavlink fieldinfo 기술자
     * @param 형식 - 필드의 형식 유형
     파라미터 : size - 데이터 필드의 사이즈 (바이트 단위)
*/

    void extractDescriptorDataFields(tlogDescriptor &desc, const mavlink_field_info_t &fieldInfo, const QString &format, int size);

    /**
     * @brief storeDescriptor validates the descriptor adds a time stamp field
     *        if needed and stores it in the datamodel
     * @param desc tlogDescriptor to store
     * @return true - success, false - datamodel failure
     */

/*
     * @brief storeDescriptor는 설명 자의 유효성을 검사하여 타임 스탬프 필드를 추가합니다.
     * 필요한 경우 데이터 모델에 저장
     * 저장할 @param desc tlogDescriptor
     * @return true - 성공, 거짓 - 데이터 모델 실패
*/

    bool storeDescriptor(tlogDescriptor desc);

    /**
     * @brief decodeData - decodes data from a mavlink message to a name value
     *        pair list.
     * @param mavlinkMessage - the message to decode
     * @param NameValuePairList - the parsing result as list of NameValuePair
     * @return true - success, false otherwise or no result
     */

/*
     * @brief decodeData - 데이터를 mavlink 메시지에서 이름 값으로 디코딩합니다.
     * 쌍 목록.
     mavlinkMessage - 디코드하는 메세지
     * @param NameValuePairList - NameValuePair의리스트로서 해석되는 결과
     * @return true - 성공, 그렇지 않으면 거짓 또는 결과 없음
*/

    bool decodeData(const mavlink_message_t &mavlinkMessage, QList<NameValuePair> &NameValuePairList);

    /**
     * @brief extractModeMessage - extracts the data needed for a MODE message from
     *        a NameValuePair list of a tlog HEARTBEAT message and stores it in the datamodel.
     * @param NameValuePairList - input data of a tlog HEARTBEAT message
     * @return - true success, false datamodel failure
     */

/*
     * @brief extractModeMessage - 모드 메시지에 필요한 데이터를 추출합니다.
     * tlog HEARTBEAT 메시지의 NameValuePair 목록을 데이터 모델에 저장합니다.
     * @param NameValuePairList - tlog HEARTBEAT 메시지의 데이터 입력
     * @return - true의 성공, false의 데이터 모델의 실패
*/

    bool extractModeMessage(const QList<NameValuePair> &NameValuePairList);

    /**
     * @brief extractMsgMessage extracts the data needed for a MSG message from
     *        a NameValuePair list of a tlog STATUSTEXT message and stores it in the datamodel.
     * @param NameValuePairList - input data of a tlog STATUSTEXT message
     * @return - true success, false datamodel failure
     */

/*
     * @brief extractMsgMessage는 MSG 메시지에 필요한 데이터를 추출합니다.
     * tlog STATUSTEXT 메시지의 NameValuePair 목록이며이를 데이터 모델에 저장합니다.
     * @param NameValuePairList - tlog STATUSTEXT 메시지의 데이터 입력
     * @return - true의 성공, false의 데이터 모델의 실패
*/

    bool extractMsgMessage(const QList<NameValuePair> &NameValuePairList);

};

#endif // TLOGPARSER_H
