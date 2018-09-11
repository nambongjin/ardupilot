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
 * @file LogParserBase.cpp
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 11 Okt 2016
 * @brief File providing implementation for the log parser base
 */
/* *
 * @file LogParserBase.cpp
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @ 날짜 11 Okt 2016
 로그 파서베이스의 구현을 제공하는 * @brief 파일
 */

#include "LogParserBase.h"
#include "logging.h"

LogParserBase::typeDescriptor::typeDescriptor() : m_ID(s_InvalidID), m_length(0), m_hasTimeStamp(false), m_timeStampIndex(0)
{}

void LogParserBase::typeDescriptor::finalize(const timeStampType &timeStamp)
{
    int tempIndex = m_labels.indexOf(timeStamp.m_name);

    if(tempIndex != -1)
    {
        m_hasTimeStamp = true;
        m_timeStampIndex = tempIndex;
    }
}

void LogParserBase::typeDescriptor::addTimeStampField(const LogParserBase::timeStampType &timeStamp)
{
    // Add timestamp name to label list
    // 레이블 목록에 타임 스탬프 이름을 추가합니다.
    m_labels.push_front(timeStamp.m_name);
    // Add timestamp format code to format string
    // 형식 문자열에 타임 스탬프 형식 코드 추가
    m_format.prepend('Q');
    // and increase the length by 8 bytes ('Q' is a quint_64)
    // 길이를 8 바이트 씩 증가시킵니다 ( 'Q'는 quint_64 임).
    m_length += 8;

    m_hasTimeStamp = true;
    m_timeStampIndex = 0;
}

void LogParserBase::typeDescriptor::replaceLabelName(const QString &oldName, const QString &newName)
{
    int tempIndex = m_labels.indexOf(oldName);

    if(tempIndex != -1)
    {
        m_labels[tempIndex] = newName;
    }
}

QString LogParserBase::typeDescriptor::getLabelAtIndex(int index) const
{
    return index < m_labels.size() ? m_labels.at(index) : QString("NoLabel");
}

bool LogParserBase::typeDescriptor::hasNoTimestamp() const
{
    return !m_hasTimeStamp;
}

bool LogParserBase::typeDescriptor::isValid() const
{
    return true;    // Default implementation should be overloaded// 기본 구현을 오버로드해야합니다.
}

//*****************************************

LogParserBase::LogParserBase(LogdataStorage::Ptr storagePtr, IParserCallback *object):
    m_callbackObject(object),
    m_dataStoragePtr(storagePtr),
    m_stop(false),
    m_MessageCounter(0),
    m_loadedLogType(MAV_TYPE_GENERIC),
    m_idUnitMessage(typeDescriptor::s_InvalidID),
    m_idMultMessage(typeDescriptor::s_InvalidID),
    m_idFMTUMessage(typeDescriptor::s_InvalidID),
    m_hasUnitData(false),
    m_timeErrorCount(0),
    m_highestTimestamp(0),
    m_timestampOffset(0)
{
    QLOG_DEBUG() << "LogParserBase::LogParserBase - CTOR";
    if(!m_dataStoragePtr)
    {
        QLOG_ERROR() << "LogParserBase::LogParserBase - No valid datamodel - parsing will not be possible";
    }
    if(m_callbackObject == nullptr)
    {
        QLOG_ERROR() << "LogParserBase::LogParserBase - No valid callback object - parsing will not be possible";
    }

    // logs can have different timestamps
    // 로그는 다른 타임 스탬프를 가질 수 있습니다.
    m_possibleTimestamps.push_back(timeStampType("TimeUS", 1000000.0));
    m_possibleTimestamps.push_back(timeStampType("TimeMS", 1000.0));
    m_possibleTimestamps.push_back(timeStampType("time_boot_ms", 1000.0));
}

LogParserBase::~LogParserBase()
{
    QLOG_DEBUG() << "LogParserBase::LogParserBase - DTOR";
}

void LogParserBase::stopParsing()
{
    QLOG_DEBUG() << "LogParserBase::stopParsing";
    m_stop = true;
}

void LogParserBase::checkForValidTimestamp(typeDescriptor &desc)
{
    for(const auto &timeStamp: m_possibleTimestamps)
    {
        if (desc.m_labels.contains(timeStamp.m_name))
        {
            m_activeTimestamp = timeStamp;
            desc.finalize(m_activeTimestamp);
            break;
        }
    }
}

bool LogParserBase::storeNameValuePairList(QList<NameValuePair> &NameValuePairList, const typeDescriptor &desc)
{
    bool wasNotRepaired = true;
    // Verify data matches descriptor - simple size check
    // 데이터가 디스크립터와 일치하는지 확인한다 - 간단한 크기 검사
    if(NameValuePairList.size() != desc.m_labels.size())
    {
        QLOG_WARN() << "Number of received values does not match number defined in type. Type:"
                    << desc.m_name << " Expected:" << desc.m_labels.size() << " got:"
                    << NameValuePairList.size() << ". Repairing message.";
        m_logLoadingState.corruptDataRead(static_cast<int>(m_MessageCounter),
                                          "Number of received values does not match number defined in type. Type:"
                                          + desc.m_name + " Expected:" + QString::number(desc.m_labels.size()) + " got:"
                                          + QString::number(NameValuePairList.size()) + ". Repairing message.");

        repairMessage(NameValuePairList, desc);
        wasNotRepaired = false;
    }

    // Set or read timestamp
    // 타임 스탬프를 설정하거나 읽습니다.
    if(desc.hasNoTimestamp())
    {
        NameValuePairList.prepend(NameValuePair(m_activeTimestamp.m_name, m_highestTimestamp));
    }
    else
    {
        handleTimeStamp(NameValuePairList, desc);
    }

    if(!m_dataStoragePtr->addDataRow(desc.m_name, NameValuePairList))
    {
        m_callbackObject->onError(m_dataStoragePtr->getError());
        return false;
    }

    if(wasNotRepaired)
    {
        m_logLoadingState.validDataRead();
    }
    m_MessageCounter++;
    return true;
}

bool LogParserBase::extendedStoreNameValuePairList(QList<NameValuePair> &NameValuePairList, const typeDescriptor &desc)
{
    bool retCode = true;
    // Store unit related information
    // 유닛 관련 정보 저장
    if(desc.m_ID == m_idUnitMessage)
    {
        // Unit data contains unit ID on index 1 and Unit Name on index 2
        // 유닛 데이터에 인덱스 1의 유닛 ID와 인덱스 2의 유닛 이름이 들어 있습니다.
        quint8 id = static_cast<quint8>(NameValuePairList[1].second.toUInt());
        m_dataStoragePtr->addUnitData(id, NameValuePairList[2].second.toString());
    }
    else if(desc.m_ID == m_idMultMessage)
    {
        // Multiplier data contains unit ID on index 1 and the multiplier on index 2
        // 승수 데이터에는 인덱스 1의 단위 ID와 인덱스 2의 승수가 포함됩니다.
        quint8 id = static_cast<quint8>(NameValuePairList[1].second.toUInt());
        double multi = NameValuePairList[2].second.toDouble();
        // ID 45 and ID 63 are multipliers which should not be used eg. unknown
        // ID 45와 ID 63은 사용해서는 안되는 승수입니다. 알 수 없는
        if((id == 45) || (id == 63))
        {
            multi = qQNaN();    // we mark them with an NaN wich is easy to detect.// 감지하기 쉬운 NaN으로 표시합니다.
        }
        m_dataStoragePtr->addMultiplierData(id, multi);
    }
    else if(desc.m_ID == m_idFMTUMessage)
    {
        QByteArray multiplierField(NameValuePairList[3].second.toByteArray());
        QByteArray unitField(NameValuePairList[2].second.toByteArray());
        // number of elements in multiplier & unit should be the same
        // 승수와 단위의 요소 수는 같아야합니다.
        if(multiplierField.size() == unitField.size())
        {
            m_dataStoragePtr->addMsgToUnitAndMultiplierData(NameValuePairList[1].second.toUInt(), multiplierField, unitField);
            m_hasUnitData = true;
        }
        else
        {
            QLOG_WARN() << "Unit and multiplier info have size mismatch. Number of elements should be the same. "
                        << "Data of type " << NameValuePairList[1].second.toUInt() << " will have no scaling nor Unit info";

            m_logLoadingState.corruptDataRead(static_cast<int>(m_MessageCounter),
                              "Unit and multiplier info have size mismatch. Number of elements should be the same. Data of type "
                              + QString::number(NameValuePairList[1].second.toUInt()) + " will have no scaling nor Unit info");
            retCode = false;
        }
    }
    else
    {
        retCode = storeNameValuePairList(NameValuePairList, desc);
    }

    return retCode;
}

void LogParserBase::handleTimeStamp(QList<NameValuePair> &valuepairlist, const typeDescriptor &desc)
{
    // read time stamp value, add time offset of prepending flight (if there was one), and store it back.
    // Due to this we always have a increasing time value
    // 타임 스탬프 값을 읽고, 선행 비행의 시간 오프셋을 추가하고 (만약 있다면), 그것을 다시 저장하십시오.
    //이 때문에 항상 시간 가치가 증가합니다.
    quint64 tempVal = static_cast<quint64>(valuepairlist.at(desc.m_timeStampIndex).second.toULongLong());
    tempVal += m_timestampOffset;
    valuepairlist[desc.m_timeStampIndex].second = tempVal;

    if(!m_lastValidTimePerType.contains(desc.m_name))
    {
        m_lastValidTimePerType.insert(desc.m_name, 0);
    }
    // store highest
    // 최고로 저장합니다.
    m_highestTimestamp = m_highestTimestamp < tempVal ? tempVal : m_highestTimestamp;

    // check if time is increasing
    // 시간이 증가하고 있는지 확인하십시오.
    if (tempVal >= m_lastValidTimePerType[desc.m_name])
    {
        m_lastValidTimePerType[desc.m_name] = tempVal;
    }
    // All time jumps < 60 sec shall be treated as error
    // 60 초 미만의 모든 시간 점프는 오류로 처리됩니다.
    else if(tempVal >= m_lastValidTimePerType[desc.m_name] - 60 * m_activeTimestamp.m_divisor)
    {
        if(m_timeErrorCount < 50)
        {
            QLOG_WARN() << "Corrupt data read: Time for " << desc.m_name << " is not increasing! Last valid time stamp:"
                        << QString::number(m_lastValidTimePerType[desc.m_name]) << " actual read time stamp is:"
                        << QString::number(tempVal);

            ++m_timeErrorCount;
        }
        else if(m_timeErrorCount < 51)
        {
            QLOG_WARN() << "Supressing further time is not increasing messages....";
            ++m_timeErrorCount;
        }
        m_logLoadingState.corruptTimeRead(static_cast<int>(m_MessageCounter), "Log time for " + desc.m_name +
                                          " is not increasing! Last Time:" + QString::number(m_lastValidTimePerType[desc.m_name]) +
                                          " new Time:" + QString::number(tempVal));
        // if not increasing set to last valid value
        // 마지막 유효한 값으로 설정하지 않는 경우
        valuepairlist[desc.m_timeStampIndex].second = m_lastValidTimePerType[desc.m_name];
    }
    else
    {
        QLOG_INFO() << "Log Start over detected - setting time offset to " << m_highestTimestamp;
        m_timestampOffset = m_highestTimestamp;
        tempVal += m_timestampOffset;
        m_highestTimestamp = tempVal;

        m_lastValidTimePerType[desc.m_name] = tempVal;
        valuepairlist[desc.m_timeStampIndex].second = tempVal;
    }
}

void LogParserBase::detectMavType(const QList<NameValuePair> &valuepairlist)
{
    // Name field in bin logs is not always on same Index. So first search for the right position.
    // 빈 로그의 이름 필드가 항상 같은 색인에있는 것은 아닙니다. 먼저 올바른 위치를 찾으십시오.
    int nameIndex = 0;
    for (int i = 0; i < valuepairlist.size(); ++i)
    {
        if (valuepairlist[i].first == "Name")
        {
            nameIndex = i;
            break;
        }
        // in tlogs the mav type can be directly read
        // tlogs에서 mav 유형을 직접 읽을 수 있음
        if (valuepairlist[i].first == "type")   // "type" field holds MAV_TYPE// "type"필드에 MAV_TYPE이 저장 됨
        {
            m_loadedLogType = static_cast<MAV_TYPE>(valuepairlist[i].second.toInt());
            break;
        }
    }

    // check again - avoid overwrite in case of tlog file
    // 다시 확인하십시오 - tlog 파일의 경우 덮어 쓰지 마십시오
    if(m_loadedLogType == MAV_TYPE_GENERIC)
    {
        if (valuepairlist[nameIndex].second == "RATE_RLL_P" || valuepairlist[nameIndex].second == "H_SWASH_PLATE"
                || valuepairlist[nameIndex].second == "ATC_RAT_RLL_P" ) // ATC_RAT_RLL_P Used in AC3.4+
        {
            m_loadedLogType = MAV_TYPE_QUADROTOR;
        }
        else if (valuepairlist[nameIndex].second == "PTCH2SRV_P")
        {
            m_loadedLogType = MAV_TYPE_FIXED_WING;
        }
        else if (valuepairlist[nameIndex].second == "SKID_STEER_OUT")
        {
            m_loadedLogType = MAV_TYPE_GROUND_ROVER;
        }
    }

    if(m_loadedLogType != MAV_TYPE_GENERIC)
    {
        m_logLoadingState.setMavType(m_loadedLogType);
    }
}

bool LogParserBase::repairMessage(QList<NameValuePair> &NameValuePairList, const typeDescriptor &descriptor)
{
    QList<NameValuePair> originalList(NameValuePairList);
    NameValuePairList.clear();
    // reconstruct message based on descriptor
    // 설명자를 기반으로 메시지를 재구성합니다.
    for(const QString &label: descriptor.m_labels)
    {
        bool found = false;
        for(QList<NameValuePair>::Iterator iter = originalList.begin(); iter != originalList.end(); ++iter)
        {
            if(label == iter->first) // does this value exist in original message?// 이 값은 원래 메시지에 존재합니까?
            {
                NameValuePairList.append(*iter);
                originalList.erase(iter);
                found = true;
                break;
            }
        }

        if(!found)
        {
            // this value is missing in message add one with value 0
            // 이 값은 메시지에 없으며 값이 0 인 하나를 추가합니다.
            NameValuePair pair(label, QVariant(0));
            NameValuePairList.append(pair);
        }
    }
    return true;
}

quint64 LogParserBase::nextValidTimestamp()
{
    return m_highestTimestamp - m_timestampOffset;
}

void LogParserBase::specialDescriptorHandling(typeDescriptor &desc)
{
    if(desc.m_name == "GPS" && !desc.m_labels.contains("GPSTimeMS"))
    {
        // Special handling for "GPS" messages that have a "TimeMS"
        // timestamp but scaling and value does not mach all other time stamps
        // "TimeMS"메시지가있는 "GPS"메시지에 대한 특수 처리
        // timestamp하지만 스케일링과 값은 다른 모든 타임 스탬프를 변경하지 않습니다.
        desc.replaceLabelName("TimeMS", "GPSTimeMS");
    }
    // Store IDs of UNIT, MULT and FMTU messages to use them later
    // 나중에 사용할 UNIT, MULT 및 FMTU 메시지의 ID 저장
    else if(desc.m_name == "UNIT")
    {
        m_idUnitMessage = desc.m_ID;
    }
    else if(desc.m_name == "MULT")
    {
        m_idMultMessage = desc.m_ID;
    }
    else if(desc.m_name == "FMTU")
    {
        m_idFMTUMessage = desc.m_ID;
    }
}
