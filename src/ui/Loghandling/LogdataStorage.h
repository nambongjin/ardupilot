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
 * @file LogdataStorage.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 16 Nov 2016
 * @brief File providing header for the data storage for logfiles
 */
/**
 * @file LogdataStorage.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 2016 년 11 월 16 일
 * @brief 로그 파일의 데이터 저장을위한 헤더를 제공하는 파일
 */

#ifndef LOGDATASTORAGE_H
#define LOGDATASTORAGE_H

#include <QObject>
#include <QAbstractTableModel>
#include <ArduPilotMegaMAV.h>

/**
 * @brief The LogdataStorage class is used to store the data parsed from logfiles.
 *        Besides that it implements the QAbstractTableModel to provide a well known
 *        interface. Additionally it brings some helper an convenience functions.
 *
 *        To add some data first a dataType (by calling addDataType(...)) has to be added.
 *        After that data values for this type can be added. They must respect the format
 *        of the added type.
 *
 */
/**
 * @brief LogdataStorage 클래스는 로그 파일에서 파싱 된 데이터를 저장하는 데 사용됩니다.
 * 그 외에 QAbstractTableModel을 구현하여 잘 알려진
 * 인터페이스. 또한 도움이되는 일부 기능을 제공합니다.
 *
 * 일부 데이터를 먼저 추가하려면 addDataType (...)을 호출하여 dataType을 추가해야합니다.
 * 이후에이 유형의 데이터 값을 추가 할 수 있습니다. 그들은 형식을 존중해야합니다.
 * 추가 된 유형의.
 *
 */
class LogdataStorage : public QAbstractTableModel
{
    Q_OBJECT
public:

    typedef QPair<quint64, int> TimeStampToIndexPair;    /// Type for holding a time stamp and its corresponding index
                                                         /// 타임 스탬프와 해당 인덱스를 보유하기위한 유형

    /**
     * @brief Ptr - shared pointer type for this class
     */
    /**
     * @brief Ptr -이 클래스의 공유 포인터 유형
     */
    typedef QSharedPointer<LogdataStorage> Ptr;

    /**
     * @brief The dataType struct holds all data describing a datatype
     */
    /**
     * @brief dataType 구조체는 데이터 유형을 설명하는 모든 데이터를 보유합니다.
     */
    struct dataType
    {
        QString m_name;                 /// Name of the type                        // 유형 이름                              
        quint32 m_ID;                   /// ID of the type                          // 유형의 ID
        int m_length;                   /// Length in bytes                         // 길이 (바이트)
        QString m_format;               /// format string like "QBB"                // "QBB"와 같은 형식 문자열
        QStringList m_labels;           /// Lable (name) of each column             // 각 열의 Lable (이름)
        QStringList m_units;            /// Unit (name) of each column              // 각 열의 단위 (이름)
        QVector<double> m_multipliers;  /// Multiplier data for scaling the data    // 데이터 스케일링을위한 승수 데이터
        int m_timeStampIndex;           /// Index of the time stamp field - for faster access  
                                        // 타임 스탬프 필드의 인덱스 -보다 빠른 액세스를 위해

        dataType() : m_ID(0xFFFFFFFF), m_length(0), m_timeStampIndex(0)
        {}

        dataType(const QString &name, quint32 ID, int length,
                 const QString &format, const QStringList &labels, int timeColumn) :
            m_name(name), m_ID(ID), m_length(length),
            m_format(format), m_labels(labels), m_timeStampIndex(timeColumn)
        {}

        dataType(const QString &name, quint32 ID, int length,
                 const QString &format, const QStringList &labels,
                 const QStringList &units, const QVector<double> &m_multipliers, int timeColumn) :
            m_name(name), m_ID(ID), m_length(length),
            m_format(format), m_labels(labels), m_units(units), m_multipliers(m_multipliers),
            m_timeStampIndex(timeColumn)
        {}
    };

    /**
     * @brief LogdataStorage - CTOR
     */
    explicit LogdataStorage();

    /**
     * @brief ~LogdataStorage - DTOR
     */
    virtual ~LogdataStorage();

    /**
     * @see help of QAbstractTableModel::rowCount
     */ 
    /**
     QAbstractTableModel :: rowCount의 도움을받습니다.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @see help of QAbstractTableModel::columnCount
     */
    /**
     QAbstractTableModel :: columnCount의 도움을받습니다.
     */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @see help of QAbstractTableModel::data
     */
    /**
     QAbstractTableModel :: @see의 도움을받습니다.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * @see help of QAbstractTableModel::headerData
     */
    /**
     QAbstractTableModel :: headerData의 도움을받습니다.
     */
    virtual QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /**
     * @brief addDataType adds a new data type to the model. The type is used to validate the data
     *        which is added with the addDataRow() method
     * @param typeName - name of the type to ba added
     * @param typeID - ID of the type to ba added
     * @param typeLength - Length of the type to ba added (bytes)
     * @param typeFormat - format string like "QbbI"
     * @param typeLabels - List of labels for each value in message (columns).
     * @param timeColumn - column index of the time stamp field
     *
     * @return - true success, false otherwise (data was not added)
     */
    /**
     * @brief addDataType은 모델에 새로운 데이터 유형을 추가합니다. 유형은 데이터의 유효성을 검사하는 데 사용됩니다.
     addDataRow () 메소드로 추가 된 *
     * @param typeName - ba를 추가하는 형태의 이름
     * @param typeID - ba에 추가되는 타입의 ID
     * @param typeLength - 추가 된 타입의 길이 (바이트)
     * @param typeFormat - "QbbI"와 같은 형식 캐릭터 라인
     * @param typeLabels - 메시지 (열)의 각 값에 대한 레이블 목록입니다.
     timeColumn - 타임 스탬프 필드의 열 인덱스
     *
     * @return - true의 경우는 true, 그렇지 않은 경우는 false (데이터는 추가되지 않았다)
     */
    virtual bool addDataType(const QString &typeName, quint32 typeID, int typeLength,
                             const QString &typeFormat, const QStringList &typeLabels, int timeColumn);

    /**
     * @brief addDataRow adds a data row - a list of pairs of string and value - to the data storage.
     *        The type of the data must be declared with addDataType(...) first. If the method
     *        returns false the reason can be read using the getError() method.
     * @param typeName - Type name of the data
     * @param values - list of pairs containing name and value of a measurement
     * @return - true success, false otherwise (data was not added)
     */
    /**
     * @brief addDataRow는 데이터 행 (문자열과 값 쌍의 목록)을 데이터 저장소에 추가합니다.
     * 데이터 유형은 addDataType (...)으로 먼저 선언해야합니다. 메소드가
     * getError () 메소드를 사용하여 이유를 읽을 수있는 false를 반환합니다.
     * @param typeName - 데이터의 형명
     * @param values ​​- 이름과 측정 값을 포함하는 쌍 목록
     * @return - true의 경우는 true, 그렇지 않은 경우는 false (데이터는 추가되지 않았다)
     */
    virtual bool addDataRow(const QString &typeName, const QList<QPair<QString,QVariant> >  &values);

    /**
     * @brief addUnitData adds unit data to the datamodel which can be used to add units to the
     *        plotted data.
     * @param unitID - Unique ID for this unit.
     * @param unitName - Name for this unit.
     */
    /**
     * @brief addUnitData는 유닛을 유닛에 추가하는 데 사용할 수있는 데이터 모델에 유닛 데이터를 추가합니다.
     * 플롯 된 데이터.
     * @param unitID -이 장치의 고유 ID입니다.
     * @param unitName -이 단위의 이름입니다.
     */
    virtual void addUnitData(quint8 unitID, const QString &unitName);

    /**
     * @brief addMultiplierData adds multiplier infos to the datamodel. This can be used for scaling.
     * @param multiID - Unique ID for this multiplier
     * @param multiplier - multiplier which scales the measurement to its Unit.
     */
    /**
     * @brief addMultiplierData는 데이터 모델에 승수 정보를 추가합니다. 이것은 스케일링에 사용될 수 있습니다.
     * @param multiID -이 승수의 일의의 ID
     * @param multiplier - 측정 값을 Unit에 스케일하는 배율입니다.
     */
    virtual void addMultiplierData(quint8 multiID, double multiplier);

    /**
     * @brief addMsgToUnitAndMultiplierData combines the unit data and the multiplier data with a
     *        typeID. Every data field in a special type gets its own unit and multiplier which are
     *        referenced by their ID.
     * @param typeID - Type ID this iformation is for.
     * @param multiplierFieldInfo - multiplier IDs
     * @param unitFieldInfo - unit IDs
     * @return - true success, false otherwise (data was not added)
     */
    /**
     * @brief addMsgToUnitAndMultiplierData는 유닛 데이터와 승수 데이터를
     * typeID. 특수 유형의 모든 데이터 필드는 자체 단위 및 배율을 가져옵니다.
     * 자신의 ID로 참조.
     * @param typeID -이 iformation을위한 ID를 입력하십시오.
     * @param multiplierFieldInfo - 승수 ID
     * @param unitFieldInfo - 단위 ID
     * @return - true의 경우는 true, 그렇지 않은 경우는 false (데이터는 추가되지 않았다)
     */
    virtual void addMsgToUnitAndMultiplierData(quint32 typeID, const QByteArray &multiplierFieldInfo,
                                               const QByteArray &unitFieldInfo);

    /**
     * @brief selectedRowChanged must be called if the selected row in the datamodel changes.
     *        It is needed to emit the right header data for the selected row.
     * @param current - QModelIndex holding the current row.
     */
    /**
     * @brief selectedRowChanged는 데이터 모델의 선택된 행이 변경되면 호출되어야합니다.
     * 선택한 행에 적합한 헤더 데이터를 내보내는 데 필요합니다.
     * @param current - 현재의 행을 보관 유지하는 QModelIndex
     */
    virtual void selectedRowChanged(const QModelIndex &current);

    /**
     * @brief setTimeStamp - sets the time stamp type of the datamodel. It will be used
     *        for scaling the time stamps to seconds. This method MUST be called at the END
     *        of the parsing process if there was no unit data in the log.
     *        In case there was unit data in the log the \ref setupUnitData() method should
     *        be called instead.
     *
     * @param timeStampName - name of the timestamp field. All types MUST have the same.
     * @param divisor - divisor used to scale the Time stamps to seconds
     */
    /**
     * @brief setTimeStamp - 데이터 모델의 타임 스탬프 유형을 설정합니다. 그것은 사용될 것이다.
     * 시간 소인을 초 단위로 조정합니다. 이 메소드는 반드시 END에서 호출되어야한다.
     * 로그에 단위 데이터가없는 경우 구문 분석 프로세스의 *.
     * 로그에 단위 데이터가있는 경우 \ ref setupUnitData () 메소드는
     * 대신 호출 할 수 있습니다.
     *
     * @param timeStampName - 타임 스탬프 필드의 이름. 모든 유형은 반드시 같아야합니다.
     * @param 제수 - 타임 스탬프를 초 단위로 스케일하는 데 사용되는 제수입니다.
     */
    virtual void setTimeStamp(const QString &timeStampName, double divisor);

    /**
     * @brief getTimeDivisor - Getter for the divisor for time stamps
     * @return - the current divisor
     */
    /**
     * @brief getTimeDivisor - 타임 스탬프의 제수를 취득합니다.
     * @return - 현재의 제수
     */
    virtual double getTimeDivisor() const;

    /**
     * @brief getFmtValues delivers a map of all data types with a list of the names of
     *        the values. For example: (IMU,[TimeMs, GyrX, GyrY...])
     * @param - filterStringValues - if true all data with string payload are suppressed,
     *          can be used for the plot selection tree, cause strings cannot be plotted
     * @return - the map containing the data. Only types which have data are listed.
     */
    /**
     * @brief getFmtValues는 모든 데이터 유형의 맵을 이름 목록과 함께 전달합니다.
     * 값. 예 : (IMU, [TimeMs, GyrX, GyrY ...])
     * @param - filterStringValues ​​- true의 경우, 캐릭터 라인의 페이로드를 포함한 모든 데이터가 억제됩니다.
     * 플롯 선택 트리에 사용할 수 있습니다. 원인 문자열을 플롯 할 수 없습니다.
     * @return - 데이터를 포함한 맵. 데이터가있는 유형 만 나열됩니다.
     */
    virtual QMap<QString, QStringList> getFmtValues(bool filterStringValues) const;

    /**
     * @brief getAllDataTypes delivers a vector of all dataTypes probably stored in this datamodel.
     *        Mainly used for exporting.
     * @return Vector with all data types in the same order they were stored.
     */
    /**
     * @brief getAllDataTypes는이 datamodel에 저장되어있는 모든 dataTypes의 벡터를 전달합니다.
     * 주로 수출에 사용됩니다.
     * @return Vector는, 모든 데이터 형이 보관 유지되고있는 순서로 Vector를 돌려줍니다.
     */
    virtual QVector<dataType> getAllDataTypes() const;

    /**
     * @brief getValues - delivers a vector of measurements of one type. The pair contains an index on first
     *        and the value on second. The index can be the normal index or a time stamp.
     * @param parent - The name of the type conatinig the measurement like "IMU"
     * @param child - The name of the column like "GyrX"
     * @param useTimeAsIndex - true - use time in index
     * @return The data Vector
     */
    /**
     * @ brief getValues ​​- 하나의 유형의 측정 벡터를 전달합니다. 쌍에는 첫 번째에 색인이 포함되어 있습니다.
     *와 두 번째 값. 인덱스는 일반 인덱스 또는 시간 소인이 될 수 있습니다.
     * @param parent - "IMU"와 같은 측정을 수행하는 유형의 이름입니다.
     * @param child - "GyrX"와 같은 열의 이름
     * @param useTimeAsIndex - true - 인덱스의 시간을 사용합니다.
     * @return 데이터 벡터
     */
    virtual QVector<QPair<double, QVariant> > getValues(const QString &parent, const QString &child, bool useTimeAsIndex) const;

    /**
     * @brief getValues - delivers the X and Y values of one type for plotting. If the model supports
     *        scaling the values will be scaled to their unit. Due to the fact that the values
     *        are delivered as double no string values can be fetched with this method.
     * @param name - The name of the type containig the measurement like "IMU.GyrX" or "IMU.GyrX [rad/s]"
     * @param useTimeAsIndex - true - use time in index
     * @param xValues - reference of a vector for storing the X-Values
     * @param yValues - reference of a vector for storing the Y-Values
     * @return true - data found, false otherwise
     */
    /**
     * @brief getValues ​​- 플로팅을위한 한 유형의 X 및 Y 값을 전달합니다. 모델이 지원하는 경우
     * 값을 스케일하는 것은 단위로 조정됩니다. 사실 값 때문에
     *는이 메서드로 가져올 수있는 문자열 값이없는 double 형식으로 제공됩니다.
     * @param name - "IMU.GyrX"또는 "IMU.GyrX [rad / s]"와 같은 측정을 포함하는 유형의 이름입니다.
     * @param useTimeAsIndex - true - 인덱스의 시간을 사용합니다.
     * @param xValues ​​- X 값을 저장하기위한 벡터 참조
     * @param yValues ​​- Y 값을 저장하기위한 벡터 참조
     * @return true - 발견 된 데이터, 그렇지 않으면 거짓
     */
    virtual bool getValues(const QString &name, bool useTimeAsIndex, QVector<double> &xValues, QVector<double> &yValues) const;

    /**
     * @brief getRawDataRow - gets a whole data row like it was written into the model. Even if the Model
     *        supports scaling the data is NOT scaled. Used for Ascii Log exporting.
     * @param index - Index of the row to be fetched.
     * @param name - conatains the name of the value after the call.
     * @param measurements - contains the measurements of this index after the call.
     */
    /**
     * @brief getRawDataRow - 모델에 쓰여진 것처럼 전체 데이터 행을 가져옵니다. 모델
     * 지원하는 크기 조정은 확장되지 않습니다. Ascii 로그 내보내기에 사용됩니다.
     파라미터 : index - 취득되는 행의 인덱스.
     * @param name - 호출 후에 값의 이름을 인식합니다.
     * @param measurements - 호출 후에이 인덱스의 측정 값을 포함합니다.
     */
    virtual void getRawDataRow(int index, QString &name, QVector<QVariant> &measurements) const;

    /**
     * @brief getUnitData - returns the unit data stored in model. Can be empty if no unit data
     *        available. Used for exporting.
     * @return - container holding id to unit data. As the order is not important we just use the
     *           same format as in datamodel.
     */
    /**
     * @brief getUnitData - 모델에 저장된 단위 데이터를 반환합니다. 단위 데이터가 없으면 비워 둘 수 있습니다.
     * 사용할 수 있습니다. 내보낼 때 사용됩니다.
     * @return - 단위 데이터에 대한 ID 보유 컨테이너. 순서가 중요하지 않으므로
     * 데이터 모델과 동일한 형식입니다.
     */
    virtual QHash<quint8, QString> getUnitData() const;

    /**
     * @brief getMultiplierData - returns the multiplier data stored in model. Can be empty if no multiplier data
     *        available. Used for exporting.
     * @return - container holding id to multiplier data. As the order is not important we just use the
     *           same format as in datamodel.
     */
    /**
     * @brief getMultiplierData - 모델에 저장된 승수 데이터를 반환합니다. 승수 데이터가 없으면 비어있을 수 있습니다.
     * 사용할 수 있습니다. 내보낼 때 사용됩니다.
     * @return - ID를 배수 데이터에 보관하는 컨테이너 순서가 중요하지 않으므로
     * 데이터 모델과 동일한 형식입니다.
     */
    virtual QHash<quint8, double> getMultiplierData() const;

    /**
     * @brief getMsgToUnitAndMultiplierData - returns the unit and the multiplier indexes used by a special
     *        message type
     * @param typeID - message type ID to get the data for
     * @return - mulriplier and unit data for the requested message ID
     */
    /**
     * @brief getMsgToUnitAndMultiplierData - 스페셜 에디터가 사용하는 단위 및 배율 인덱스를 반환합니다.
     * 메시지 유형
     * @param typeID - 데이터를 취득하는 메세지 타입 ID
     * @return - 요구 된 메세지 ID의 단위 데이터
     */
    virtual QPair<QByteArray, QByteArray> getMsgToUnitAndMultiplierData(quint32 typeID) const;

    /**
     * @brief getMinTimeStamp - getter for the smallest timestamp in log
     * @return - the smallest timestamp scaled to seconds
     */
    /**
     * @brief getMinTimeStamp - 로그 내의 최소 타임 스탬프의 취득 자
     * @return - 초로 스케일 된 최소 타임 스탬프
     */
    virtual double getMinTimeStamp() const;

    /**
     * @brief getMaxTimeStamp - getter for the biggest timestamp in log
     * @return - the biggest timestamp scaled to seconds
     * @return
     */
    /**
     * @brief getMaxTimeStamp - 로그 내의 가장 큰 타임 스탬프의 취득 자
     * @return - 초로 스케일 된 가장 큰 타임 스탬프
     * @ 반환
     */
    virtual double getMaxTimeStamp() const;

    /**
     * @brief getNearestIndexForTimestamp delivers the row index which has the
     *        smallest deviation in its timeStamp to the delivered timeValue.
     *
     * @param timevalue - The timeStamp to search for
     * @return The index with the best timestamp match.
     */
    /**
     * @brief getNearestIndexForTimestamp는 행 인덱스를 전달합니다.
     * 전달 된 timeValue에 대한 해당 timeStamp의 최소 편차입니다.
     *
     * @param timevalue - 검색하는 타임 스탬프
     * @return 최적의 타임 스탬프 매치를 가지는 인덱스.
     */
    virtual int getNearestIndexForTimestamp(double timevalue) const;

    /**
     * @brief getMessagesOfType fetches the special messages (ModeMessage, ErrorMessage,
     *        EventMessage, MsgMessage) from the datamodel. These messages need special handling
     *        as they are events.
     *
     * @param type - Type the message to be fetched. like ModeMessage::TypeName or ErrorMessage::TypeName
     * @param indexToMessageMap - A map to store the results. The Map maintains the order.
     */
    /**
     * @brief getMessagesOfType은 특수 메시지 (ModeMessage, ErrorMessage,
     * EventMessage, MsgMessage)를 사용합니다. 이 메시지는 특별한 처리가 필요합니다.
     * 사건이기 때문에.
     *
     * @param type - 페치 할 메시지를 입력하십시오. 같은 ModeMessage :: TypeName 또는 ErrorMessage :: TypeName
     파라미터 : indexToMessageMap - 결과를 포함하는 맵. 맵은 순서를 유지합니다.
     */
    virtual void getMessagesOfType(const QString &type, QMap<quint64, MessageBase::Ptr> &indexToMessageMap) const;

    /**
     * @brief getError delivers the last error detected by the datamodel. This method should be called
     *        if the addDataRow(...) returns false. In that case the reason could be read here.
     *
     * @return String conatining the reason for the error.
     */
    /**
     * @brief getError는 데이터 모델에 의해 검출 된 마지막 에러를 전달합니다. 이 메소드를 호출해야합니다.
     addDataRow (...)가 false를 돌려주는 경우. 이 경우 이유는 여기에서 읽을 수 있습니다.
     *
     에러의 원인을 나타내는 String
     */
    virtual QString getError() const;

    /**
     * @brief setupUnitData processes the Unit data and adds it to every dataType stored in m_typeStorage.
     *        This method MUST be called at the END of the parsing process if there was unit data in the log.
     *        In case there was no unit data in the log the \ref setTimeStamp() method should
     *        be called instead.
     *
     * @param timeStampName - name of the timestamp field. All types MUST have the same.
     * @param divisor - divisor used to scale the Time stamps to seconds
     * @return StringList containing all problems which occured while processing the unit data.
     */
    /**
     * @brief setupUnitData는 유닛 데이터를 처리하여 m_typeStorage에 저장된 모든 데이터 유형에 추가합니다.
     *이 메서드는 로그에 단위 데이터가있는 경우 파싱 프로세스의 끝에서 호출되어야합니다.
     * 로그에 단위 데이터가없는 경우 \ ref setTimeStamp () 메소드는
     * 대신 호출 할 수 있습니다.
     *
     * @param timeStampName - 타임 스탬프 필드의 이름. 모든 유형은 반드시 같아야합니다.
     * @param 제수 - 타임 스탬프를 초 단위로 스케일하는 데 사용되는 제수입니다.
     * @return 유닛 데이터의 처리 중에 발생한 모든 문제를 포함한 StringList
     */
    virtual QStringList setupUnitData(const QString &timeStampName, double divisor);

    /**
     * @brief ModelIsScaled returns true if datamodel contains scaling information
     * @return true - datamodel is scaled, false it is not.
     */
    /**
     * @brief ModelIsScaled는 datamodel에 배율 정보가 포함되어 있으면 true를 반환합니다.
     * @return true - 데이터 모델의 크기가 조절되고 그렇지 않으면 false입니다.
     */
    virtual bool ModelIsScaled() const;

private:

    constexpr static int s_ColumnOffset  = 2;           /// Offset for columns cause model adds index and name column
                                                        /// 열에 대한 오프셋으로 인해 모델에서 인덱스 및 이름 열을 추가합니다.
    constexpr static char s_UnitParOpen  = '[';         /// Unit names are surrounded by this parenthesis
                                                        /// 이 괄호로 묶은 단위 이름
    constexpr static char s_UnitParClose = ']';         /// Unit names are surrounded by this parenthesis
                                                        /// 이 괄호로 묶은 단위 이름

    typedef QPair<QString, QVariant> NameValuePair;     /// Type holding lable string and its value
                                                        /// lable 문자열과 그 값을 보유한 타입
    typedef QPair<QString, int> TypeIndexPair;          /// Type holding name and index
                                                        /// 보유 이름 및 색인 유형 지정
    typedef QVector<QVariant> ValueRow;                 /// Type holding one data line of a specific type
                                                        /// 특정 유형의 하나의 데이터 행을 보유하는 유형
    /**
     * @brief The IndexValueRow struct adds a dedicated index field to the
     *        ValueRow.
     */
    /**
     * @brief IndexValueRow 구조체는 인덱스에 전용 인덱스 필드를 추가합니다.
     * ValueRow.
     */
    struct IndexValueRow
    {
        int m_index;        /// the global index of this row
                            /// 이 행의 글로벌 인덱스
        ValueRow m_values;  /// The value row
                            /// 값 행
        IndexValueRow() : m_index(0)
        {}
    };

    typedef QVector<IndexValueRow> ValueTable;            /// Type holding all data rows of a specific type
                                                          /// 특정 유형의 모든 데이터 행을 보유하는 유형

    int m_columnCount;           /// Holds the maximum column count of all rows
                                 /// 모든 행의 최대 열 수를 보유합니다.
    int m_currentRow;            /// The current selected row in table
                                 /// 테이블에서 현재 선택된 행

    QString m_timeStampName;    /// Holds the name of the time stamp
                                /// 타임 스탬프의 이름을 유지합니다.
    double  m_timeDivisor;      /// Scaling for timestamp for creating second scaling
                                /// 두 번째 크기 조절을 만들기위한 타임 스탬프 배율
    quint64 m_minTimeStamp;     /// the min time stamp in data
                                /// 데이터의 최소 시간 스탬프
    quint64 m_maxTimeStamp;     /// the max time stamp in data
                                /// 데이터의 최대 타임 스탬프

    QVector<TimeStampToIndexPair> m_TimeToIndexList;    /// List holding pairs of time stamp and table row index
                                                        /// 타임 스탬프와 테이블 행 인덱스 쌍을 나열합니다.

    QHash<QString, dataType> m_typeStorage;     /// Holds all known types
                                                /// 모든 알려진 유형을 보유합니다.
    QVector<QString>         m_indexToTypeRow;  /// Holds the Type name in the order they were added
                                                /// 추가 된 순서로 Type 이름을 유지합니다.

    QHash<QString, ValueTable> m_dataStorage;    /// Holds the complete data
                                                 /// 전체 데이터 보유 
    QVector<TypeIndexPair>     m_indexToDataRow; /// The global index pointing to the row
                                                 /// 행을 가리키는 전역 인덱스
    QString m_errorText;                         /// Used to store current error
                                                 /// 현재 오류를 저장하는 데 사용됩니다.

    QHash<quint8, QString> m_unitStorage;           /// Holds UNIT data and unit id (if available)
                                                    /// UNIT 데이터 및 유닛 ID를 보유합니다 (사용 가능한 경우).
    QHash<quint8, double>  m_multiplierStorage;     /// Holds Multiplier data and multiplier id (if available)
                                                    /// 승수 (multiplier) 데이터와 배율 (multiplier) ID (사용 가능한 경우)
    QHash<quint32, QByteArray> m_typeIDToUnitFieldInfo;       /// Holds Unit IDs for every type
                                                              /// 모든 유형의 단위 ID 보유
    QHash<quint32, QByteArray> m_typeIDToMultiplierFieldInfo; /// Holds Multiplier IDs for every type
                                                              /// 모든 유형에 대한 승수 ID를 보유합니다.


    /**
     * @brief getLabelName - Constructs and delivers the Label name for the dataType at a given index.
     *        If unit information is available it will be added and sourrounded by [].
     * @param index - Index of the label which shall be fetched from dataType
     * @param type - The dataType the label shall be fetched from
     * @return - String containing a least the label plus unit name if available.
     */
    /**
     getLabelName - 지정된 인덱스에있는 dataType의 Label 명을 구축해 전달합니다.
     * 단위 정보가있는 경우 []로 추가되고 sourrounded됩니다.
     파라미터 : index - 데이터 형으로부터 꺼낼 수있는 라벨의 인덱스
     * @param type - 라벨을 꺼내는 데이터 형
     * @return - 가능한 경우, 레이블과 단위 명을 더한 문자열.
     */
    QString getLabelName(int index, const dataType &type) const;
};

#endif // LOGDATASTORAGE_H
