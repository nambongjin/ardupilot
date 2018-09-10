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
 * @file LogdataStorage.cpp
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 16 Nov 2016
 * @brief File providing implementation for the data storage for logfiles
 */
/**
 * @file LogdataStorage.cpp
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 2016 년 11 월 16 일
 * @brief 로그 파일을위한 데이터 저장을위한 구현을 제공하는 파일
 */


#include "LogdataStorage.h"
#include "logging.h"
#include <algorithm>

/**
 * @brief The TimeStampToIndexPairComparer class is a functor for sorting the
 *        time index by time.
 */
/**
 * @brief TimeStampToIndexPairComparer 클래스는 클래스를 정렬하기위한 펑 터입니다.
 * 시간별 시간 지수.
 */
class TimeStampToIndexPairComparer
{
public:
  bool operator() (LogdataStorage::TimeStampToIndexPair pair1, LogdataStorage::TimeStampToIndexPair pair2)
  {
      // pair.first is the time stamp
      // pair.first는 타임 스탬프입니다.
      return (pair1.first < pair2.first);
  }
};

//****************************************************

LogdataStorage::LogdataStorage() :
    m_columnCount(0),
    m_currentRow(0),
    m_timeDivisor(0.0),
    m_minTimeStamp(ULLONG_MAX),
    m_maxTimeStamp(0)
{
    QLOG_DEBUG() << "LogdataStorage::LogdataStorage()";
    // Reserve some memory...
    // 일부 메모리 예약 ...
    m_typeStorage.reserve(50);
    m_indexToTypeRow.reserve(50);
    m_dataStorage.reserve(50);
    m_TimeToIndexList.reserve(20000);
    m_indexToDataRow.reserve(20000);

    // add some default data to the multiplier
    // 기본 데이터를 승수에 추가합니다.
    m_multiplierStorage[45] = qQNaN();  // invalid / unused multiplier - missing in some logs therefore added here.
                                        // invalid / unused multiplier - 일부 로그에 누락이 있으므로 여기에 추가됩니다.
    m_multiplierStorage[63] = qQNaN();  // unknown multiplier - missing in some logs therefore added here.
                                        // 알 수없는 승수 - 따라서 일부 로그에 누락이 추가되어 여기에 추가됩니다.
}

LogdataStorage::~LogdataStorage()
{
    QLOG_DEBUG() << "LogdataStorage::~LogdataStorage()";
}

int LogdataStorage::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_indexToDataRow.size();
}

int LogdataStorage::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columnCount;
}

QVariant LogdataStorage::data(const QModelIndex &index, int role) const
{
    if ((role != Qt::DisplayRole) || !index.isValid())
    {
        return QVariant();
    }
    if (index.row() >= m_indexToDataRow.size())
    {
        QLOG_ERROR() << "Accessing a row that does not exist! Row was: " << index.row();
        return QVariant();
    }
    if (index.column() == 0)
    {
        // Column 0 is the index of the log data which is the same as the row
        // 열 0은 행과 동일한 로그 데이터의 인덱스입니다.
        return QVariant(QString::number(index.row()));
    }
    if (index.column() == 1)
    {
        // Column 1 is the name of the log data (ATT,ATUN...)
        // 열 1은 로그 데이터의 이름입니다 (ATT, ATUN ...).
        return QVariant(m_indexToDataRow[index.row()].first);
    }

    const TypeIndexPair &typeIndex = m_indexToDataRow[index.row()];
    const ValueTable &dataVect = m_dataStorage[typeIndex.first];
    if(index.column() - s_ColumnOffset >= dataVect.at(typeIndex.second).m_values.size())
    {
        return QVariant(); // this data type does not have so much colums
    }                      // 이 데이터 유형에는 콜럼이 너무 많지 않습니다.

    const dataType &type = m_typeStorage[typeIndex.first];
    if((index.column() - s_ColumnOffset) < type.m_multipliers.size())   // do we have a multiplier??
    {
        const double &multi = type.m_multipliers.at(index.column() - s_ColumnOffset);
        if(!qIsNaN(multi))     // unknown multiplier are NaNs
        {                      // 알 수없는 승수가 NaN 인 경우
            double temp = dataVect.at(typeIndex.second).m_values.at(index.column() - s_ColumnOffset).toDouble();
            if(index.column() == 2)
            {
                // Column 2 is the time we want 6 decimals in this one.
                // 칼럼 2는 우리가이 칼럼에서 6 개의 소수를 원할 때입니다.
                return QString::number(temp * multi, 'f', 6);
            }
            return QVariant(temp * multi);
        }
    }
    // If we do not have multipliers we do not need scaling
    // 승수가 없으면 스케일링 할 필요가 없습니다.
    return dataVect.at(typeIndex.second).m_values.at(index.column() - s_ColumnOffset);
}

QVariant LogdataStorage::headerData(int column, Qt::Orientation orientation, int role) const
{
    if ((column == -1) || (role != Qt::DisplayRole) || (orientation == Qt::Vertical))
    {
        return QVariant();
    }
    if (m_indexToDataRow.empty())
    {
        return QVariant("No Data");  // corner case - we do not have any data
    }                                // corner case - 데이터가 없습니다.
    if (column == 0)
    {
        return QVariant("Index");   // first colum is always the index
    }                               // 첫 번째 열은 항상 색인입니다.
    if (column == 1)
    {
        return QVariant("MSG Type");    // second colum is always the message type
    }                                   // 두 번째 열은 항상 메시지 유형입니다.

    const TypeIndexPair &typeIndex = m_indexToDataRow[m_currentRow];
    const dataType &type = m_typeStorage[typeIndex.first];
    if ((column - s_ColumnOffset) >= type.m_labels.size())
    {
        return QVariant("");    // this row does not have this column
    }                           // 이 행에는이 열이 없습니다.

    return QVariant(getLabelName(column - s_ColumnOffset, type));
}

bool LogdataStorage::addDataType(const QString &typeName, quint32 typeID, int typeLength,
                                 const QString &typeFormat, const QStringList &typeLabels, int timeColumn)
{
    // set up column count - the storage adds s_ColumnOffset columns to the data.
    // One for the index and one for the name.
    // 열 수를 설정합니다. 저장소는 s_ColumnOffset 열을 데이터에 추가합니다.
    // 하나는 인덱스 용이고 다른 하나는 이름 용입니다.
    m_columnCount = m_columnCount < (typeLabels.size() + s_ColumnOffset) ? typeLabels.size() + s_ColumnOffset : m_columnCount;

    // create new type and store it
    // 새로운 타입을 생성하고 저장한다.
    dataType NewType(typeName, typeID, typeLength, typeFormat, typeLabels, timeColumn);
    m_typeStorage.insert(typeName, NewType);
    // to be able to recreate the order we store the names in a vector.
    // 벡터에 이름을 저장하는 순서를 다시 만들 수 있습니다.
    m_indexToTypeRow.push_back(typeName);

    return true;
}

bool LogdataStorage::addDataRow(const QString &typeName, const QList<QPair<QString,QVariant> >  &values)
{
    if (!m_typeStorage.count(typeName))  // type exists in type storage?
    {                                    // 유형이 유형 저장 장치에 있습니까?
        QTextStream error(&m_errorText);
        error << "Data of type " << typeName << " cannot be inserted cause its type is unknown.";
        return false;
    }

    dataType &tempType = m_typeStorage[typeName];
    if(values.size() != tempType.m_labels.size())    // Number of elements match type?
    {                                                // 매치하는 요소의 수는 얼마인가?
        QTextStream error(&m_errorText);
        error << "Number of datafields for type " << typeName << " does not match. Expected:"
              << tempType.m_labels.size() << " got:" << values.size();
        return false;
    }

    // fetch min & max timestamp of all data
    // 모든 데이터의 최소 및 최대 타임 스탬프를 가져옵니다.
    quint64 tempTime = values.at(tempType.m_timeStampIndex).second.toULongLong();
    m_minTimeStamp = m_minTimeStamp > tempTime ? tempTime : m_minTimeStamp;
    m_maxTimeStamp = m_maxTimeStamp < tempTime ? tempTime : m_maxTimeStamp;

    IndexValueRow newRow;
    newRow.m_values.reserve(values.size());
    for(int i = 0; i < values.size(); ++i)
    {
        if(values[i].first != tempType.m_labels[i])  // value name match?
        {                                            // 값 이름이 일치합니까?
            QTextStream error(&m_errorText);
            error << "Data of type " << typeName << " Value name mismatch. Expected:"
                  << tempType.m_labels[i] << " got:" << values[i].first;
            return false;
        }
        newRow.m_values.push_back(values[i].second);
    }
    // add current global dataindex to row
    // 행에 현재 전역 datainx를 추가합니다.
    newRow.m_index = m_indexToDataRow.size();   // size() will be the index after push_back()
    // add to data storage                      // size ()는 push_back () 이후의 인덱스가됩니다.
    // 데이터 저장소에 추가
    m_dataStorage[typeName].append(newRow);
    // add type name to global dataindex
    // 전역 dataindex에 유형 이름을 추가합니다.
    m_indexToDataRow.push_back(TypeIndexPair(typeName, m_dataStorage[typeName].size() - 1)); // last index is size() - 1
    // create time to index pair                                                             // 마지막 인덱스는 size () - 1입니다.
    // 인덱스 쌍을 만들 시간을 만듭니다.
    TimeStampToIndexPair timeIndex(tempTime, newRow.m_index);
    // and add it to time index
    // 시간 인덱스에 추가합니다.
    m_TimeToIndexList.push_back(timeIndex);
    return true;
}

void LogdataStorage::addUnitData(quint8 unitID, const QString &unitName)
{
    m_unitStorage[unitID] = unitName;
}

void LogdataStorage::addMultiplierData(quint8 multiID, double multiplier)
{
    m_multiplierStorage[multiID] = multiplier;
}

void LogdataStorage::addMsgToUnitAndMultiplierData(quint32 typeID, const QByteArray &multiplierFieldInfo, const QByteArray &unitFieldInfo)
{
    m_typeIDToMultiplierFieldInfo[typeID] = multiplierFieldInfo;
    m_typeIDToUnitFieldInfo[typeID] = unitFieldInfo;
}

void LogdataStorage::selectedRowChanged(const QModelIndex &current)
{
    if (!current.isValid() || (m_currentRow == current.row()))
    {
        return;
    }
    m_currentRow = current.row() < m_indexToDataRow.size() ? current.row() : m_indexToDataRow.size() - 1; // size() -1 is last index
    emit headerDataChanged(Qt::Horizontal,0,9);                                                         // size () -1은 마지막 인덱스입니다.
}

void LogdataStorage::setTimeStamp(const QString &timeStampName, double divisor)
{
    m_timeStampName = timeStampName;
    m_timeDivisor = divisor;

    // As this method is called at the End of the parsing we should use the chance to sort the time index by
    // time - just to be sure...
    // 이 메소드는 파싱의 마지막에서 호출되므로 우리는 시간 인덱스를
    // 시간 - 확실하게 ...
    std::stable_sort(m_TimeToIndexList.begin(), m_TimeToIndexList.end(), TimeStampToIndexPairComparer());
}

double LogdataStorage::getTimeDivisor() const
{
    return m_timeDivisor;
}

QMap<QString, QStringList> LogdataStorage::getFmtValues(bool filterStringValues) const
{
    QMap<QString, QStringList> fmtValueMap; //using a map to get alphabetically sorting
                                            // 지도를 사용하여 사전 순 정렬하기
    for(const auto &type : m_typeStorage)
    {
        if(m_dataStorage.count(type.m_name))    // only types we have data for
        {                                       // 데이터가있는 유형 만
            if(!filterStringValues ||           // n N Z are string types - those cannot be plotted
                                                // n NZ는 문자열 유형입니다.
               !(type.m_format.contains('n') || type.m_format.contains('N') || type.m_format.contains('Z')))
            {
                QStringList labelPlusUnit;
                for(int i = 0; i < type.m_labels.size(); ++i)
                {
                    labelPlusUnit.append(getLabelName(i, type));
                }
                fmtValueMap.insert(type.m_name, labelPlusUnit);
            }
        }
    }
    return fmtValueMap;
}

QVector<LogdataStorage::dataType> LogdataStorage::getAllDataTypes() const
{
    QVector<dataType> dataTypes;
    foreach(const QString &name, m_indexToTypeRow)
    {
        dataTypes.push_back(m_typeStorage.value(name));
    }

    return dataTypes;
}

QVector<QPair<double, QVariant> > LogdataStorage::getValues(const QString &parent, const QString &child, bool useTimeAsIndex) const
{
    QVector<QPair<double, QVariant> > data;

    if(!m_typeStorage.count(parent) || !m_dataStorage.count(parent))
    {
        return data;    // don't have this type or no data for this type
    }                   // 이 유형에는이 유형 또는 데이터가 없습니다.

    int valueIndex = m_typeStorage[parent].m_labels.indexOf(child);
    int timeStampIndex = m_typeStorage[parent].m_timeStampIndex;

    if(valueIndex == -1)
    {
        return data;    // don't have this value type
    }                   // 이 값 유형이 없습니다.

    QPair<double, QVariant> indexValuePair;
    data.reserve(m_dataStorage[parent].size());
    foreach(const IndexValueRow &row, m_dataStorage[parent])
    {
        // TODO Add scaling!
        // TODO 스케일링을 추가하십시오!
        indexValuePair.first = useTimeAsIndex ? row.m_values.at(timeStampIndex).toDouble() / m_timeDivisor : row.m_index;
        indexValuePair.second = row.m_values.at(valueIndex);
        data.push_back(indexValuePair);
    }

    return data;
}

bool LogdataStorage::getValues(const QString &name, bool useTimeAsIndex, QVector<double> &xValues, QVector<double> &yValues) const
{
    auto splitName = name.split(".");
    if(splitName.size() != 2)
    {
        return false;   // name is not valid - structure must be "part1.part2"
    }                   // name이 유효하지 않습니다. 구조체는 "part1.part2"여야합니다.
    if(!m_typeStorage.count(splitName.at(0)) || !m_dataStorage.count(splitName.at(0)))
    {
        return false;    // don't have this type or no data for this type
    }                    // 이 유형에는이 유형 또는 데이터가 없습니다.
    

    const auto &type = m_typeStorage[splitName.at(0)];
    auto part1 = splitName.at(1).split(s_UnitParOpen).at(0).trimmed();  // Remove unit info like "[s]" from
    const int valueIndex = type.m_labels.indexOf(part1);                // "[s]"와 (과) 같은 단위 정보를 제거합니다.
    if(valueIndex == -1)
    {
        return false;    // don't have this value type 
    }                    // 이 값 유형이 없습니다.


    const int timeStampIndex = type.m_timeStampIndex;
    double multiplier = qQNaN();                        // Unknown multiplier is always qQNaN
    if(type.m_multipliers.size() > valueIndex)          // 알 수없는 승수는 항상 qQNaN입니다.
    {
        multiplier  = type.m_multipliers[valueIndex];
    }

    xValues.clear();
    xValues.reserve(m_dataStorage[splitName.at(0)].size());
    yValues.clear();
    yValues.reserve(m_dataStorage[splitName.at(0)].size());

    for(const IndexValueRow &row: m_dataStorage[splitName.at(0)])
    {
        xValues.push_back(useTimeAsIndex ? row.m_values.at(timeStampIndex).toDouble() / m_timeDivisor : row.m_index);
        if(!qIsNaN(multiplier))
        {
            yValues.push_back(row.m_values.at(valueIndex).toDouble() * multiplier);
        }
        else
        {
            yValues.push_back(row.m_values.at(valueIndex).toDouble());
        }
    }

    return true;
}

void LogdataStorage::getRawDataRow(int index, QString &name, QVector<QVariant> &measurements) const
{
    if(index < m_indexToDataRow.size())
    {
        TypeIndexPair indexPair = m_indexToDataRow[index];
        name = indexPair.first;
        measurements = m_dataStorage.value(name).at(indexPair.second).m_values;
    }
    else
    {
        name.clear();
        measurements.clear();
    }
}

QHash<quint8, QString> LogdataStorage::getUnitData() const
{
    return m_unitStorage;
}

QHash<quint8, double> LogdataStorage::getMultiplierData() const
{
    return m_multiplierStorage;
}

QPair<QByteArray, QByteArray> LogdataStorage::getMsgToUnitAndMultiplierData(quint32 typeID) const
{
    QPair<QByteArray, QByteArray> dataPair;

    dataPair.first  = m_typeIDToMultiplierFieldInfo[typeID];
    dataPair.second = m_typeIDToUnitFieldInfo[typeID];
    return dataPair;
}

double LogdataStorage::getMinTimeStamp() const
{
    return static_cast<double>(m_minTimeStamp) / m_timeDivisor;
}

double LogdataStorage::getMaxTimeStamp() const
{
    return static_cast<double>(m_maxTimeStamp) / m_timeDivisor;
}

int LogdataStorage::getNearestIndexForTimestamp(double timevalue) const
{
    quint64 timeToFind = static_cast<quint64>(m_timeDivisor * timevalue);
    float intervalSize = m_TimeToIndexList.size();
    float intervalStart = 0;
    float middle = 0;
    int   index = 0;

    // first check if timevalue is within our range
    // timevalue가 우리 범위 내에 있는지 먼저 확인하십시오.
    if(m_TimeToIndexList.first().first > timeToFind)
    {
        return 0;   // timevalue too small deliver index 0
    }               // 시간 값이 너무 작아서 인덱스 0을 전달합니다.
    else if(m_TimeToIndexList.last().first < timeToFind)
    {
        return m_TimeToIndexList.size();    // timevalue too big deliver last index.
    }                                       // 너무 큰 시간 값은 마지막 색인을 제공합니다.
    else
    {
        while (intervalSize > 1)
        {
            middle = intervalStart + intervalSize / 2;
            index = static_cast<int>(middle + 0.5f);
            quint64 tempTime = m_TimeToIndexList[index].first;
            if (timeToFind > tempTime)
            {
                intervalStart = middle;
            }
            else if (timeToFind == tempTime)
            {
                break;
            }
            intervalSize = intervalSize / 2;
        }
    }
    return m_TimeToIndexList[index].second;
}

void LogdataStorage::getMessagesOfType(const QString &type, QMap<quint64, MessageBase::Ptr> &indexToMessageMap) const
{
    if(!m_dataStorage.count(type))
    {
        QLOG_DEBUG() << "Graph loaded with no table of type " << type;
        return;
    }

    QList<NameValuePair> nameValueList;

    for(const auto &row : m_dataStorage[type])
    {
        nameValueList.clear();
        nameValueList.append(NameValuePair("Index", row.m_index));  // Add Data index
                                                                    // 데이터 색인 추가
        for(int i = 0; i < row.m_values.size(); ++i)
        {
            NameValuePair tempPair(m_typeStorage[type].m_labels.at(i), row.m_values.at(i)); // add names and values
            nameValueList.append(tempPair);                                                 // 이름과 값을 추가합니다.
        }
        MessageBase::Ptr msgPtr = MessageFactory::CreateMessageOfType(type, nameValueList, m_timeStampName, m_timeDivisor);
        if(msgPtr)
        {
            indexToMessageMap.insert(static_cast<quint64>(row.m_index), msgPtr);
        }
    }
}

QString LogdataStorage::getError() const
{
    return m_errorText;
}

QStringList LogdataStorage::setupUnitData(const QString &timeStampName, double divisor)
{
    QStringList errors;

    // handle the unit and multiplier data if there is some
    // 유닛과 배율기 데이터가 있으면 처리한다.
    if(m_typeIDToMultiplierFieldInfo.size() != 0)
    {
        QHash<QString, dataType>::Iterator iter;
        for(iter = m_typeStorage.begin(); iter != m_typeStorage.end(); ++iter)
        {
            unsigned int typeID = iter.value().m_ID;
            // handle unit data
            // 단위 데이터를 처리합니다.
            if(m_typeIDToUnitFieldInfo.contains(typeID))
            {
                for(const qint8 unitID : m_typeIDToUnitFieldInfo.value(typeID))
                {
                    if(m_unitStorage.contains(static_cast<quint8>(unitID)))
                    {
                        iter.value().m_units.push_back(m_unitStorage.value(static_cast<quint8>(unitID)));
                    }
                    else
                    {
                        QString error("Found unit ID " + QString::number(unitID) + " but no matching unit");
                        errors.append(error);
                    }
                }
            }
            else
            {
                QString error("No unit description for data type " + iter.value().m_name + " found");
                errors.append(error);
            }
            // handle multiplier data
            // 승수 데이터를 처리합니다.
            if(m_typeIDToMultiplierFieldInfo.contains(typeID))
            {
                for(const qint8 multID : m_typeIDToMultiplierFieldInfo.value(typeID))
                {
                    if(m_multiplierStorage.contains(static_cast<quint8>(multID)))
                    {
                        iter.value().m_multipliers.append(m_multiplierStorage.value(static_cast<quint8>(multID)));
                    }
                    else
                    {
                        QString error("Found multiplier ID " + QString::number(multID) + " but no matching multiplier");
                        errors.append(error);
                    }
                }
            }
            else
            {
                QString error("No multiplier description for data type " + iter.value().m_name + " found");
                errors.append(error);
            }
        }
    }

    setTimeStamp(timeStampName, divisor);

    return errors;
}

bool LogdataStorage::ModelIsScaled() const
{
    return m_typeIDToMultiplierFieldInfo.size() > 0;
}

QString LogdataStorage::getLabelName(int index, const dataType & type) const
{
    QString label = type.m_labels.at(index);
    if(index < type.m_units.size())         // do we have a unit?
    {                                       // 단위가 있나요?
        const QString &unit = type.m_units.at(index);
        if(unit.size() != 0)    // only add if unit is not empty
        {                       // unit이 비어 있지 않은 경우에만 추가
            label.append(' ');
            label.append(s_UnitParOpen);
            label.append(unit);
            label.append(s_UnitParClose);
        }
    }
    return label;
}

