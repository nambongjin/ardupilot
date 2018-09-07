#ifndef QGCUASPARAMMANAGER_H
#define QGCUASPARAMMANAGER_H

#include <QWidget>
#include <QMap>
#include <QTimer>
#include <QVariant>

class UASInterface;

class QGCUASParamManager : public QWidget
{
    Q_OBJECT
public:
    enum ParamFileType
    {
        TabSeperatedValues,
        CommaSeperatedValues
    };
    QGCUASParamManager(UASInterface* uas, QWidget *parent = 0);

    QList<QString> getParameterNames(int component) const;
    QList<QVariant> getParameterValues(int component) const;
    bool getParameterValue(int component, const QString& parameter, QVariant& value) const;
    QVariant getParameterValue(int component, const QString& parameter) const;

    virtual bool isParamMinKnown(const QString& param) = 0;
    virtual bool isParamMaxKnown(const QString& param) = 0;
    virtual bool isParamDefaultKnown(const QString& param) = 0;
    virtual double getParamMin(const QString& param) = 0;
    virtual double getParamMax(const QString& param) = 0;
    virtual double getParamDefault(const QString& param) = 0;
    virtual QString getParamInfo(const QString& param) = 0;
    virtual void setParamInfo(const QMap<QString,QString>& param) = 0;

    virtual QString summaryInfoFromFile(const QString& filename) = 0;
    virtual bool loadParamsFromFile(const QString &filename,ParamFileType type) = 0;

    /** @brief Request an update for the parameter list */
    /** brief 매개 변수 목록에 대한 업데이트 요청 */
    void requestParameterListUpdate(int component = 0);
    /** @brief Request an update for this specific parameter */
    /** @ brief이 특정 매개 변수에 대한 업데이트 요청 */
    virtual void requestParameterUpdate(int component, const QString& parameter) = 0;

signals:
    void parameterChanged(int component, QString parameter, QVariant value);
    void parameterChanged(int component, int parameterIndex, QVariant value);
    void parameterListUpToDate(int component);

public slots:
    /** @brief Write one parameter to the MAV */
    /* * @ brief MAV에 하나의 매개 변수 쓰기 */
    virtual void setParameter(int component, QString parameterName, QVariant value) = 0;
    /** @brief Request list of parameters from MAV */
    /* * brief MAV로부터 매개 변수 목록 요청 */
    virtual void requestParameterList() = 0;

protected:
    UASInterface* mav;   ///< The MAV this widget is controlling// / <이 위젯이 제어하는 ​​MAV
    QMap<int, QMap<QString, QVariant>* > changedValues; ///< Changed values// / <변경된 값
    QMap<int, QMap<QString, QVariant>* > parameters; ///< All parameters// / <모든 매개 변수
    QVector<bool> received; ///< Successfully received parameters// / <매개 변수를 받았습니다.
    QMap<int, QList<int>* > transmissionMissingPackets; ///< Missing packets// / <누락 된 패킷
    QMap<int, QMap<QString, QVariant>* > transmissionMissingWriteAckPackets; ///< Missing write ACK packets// / <쓰기 ACK 패킷 누락
    bool transmissionListMode;       ///< Currently requesting list// / <현재 요청 목록
    QMap<int, bool> transmissionListSizeKnown;  ///< List size initialized?// / <리스트 크기가 초기화 되었습니까?
    bool transmissionActive;         ///< Missing packets, working on list?// / <빠진 패킷,리스트 작업중?
    quint64 transmissionTimeout;     ///< Timeout// / <Timeout
    QTimer retransmissionTimer;      ///< Timer handling parameter retransmission// / <타이머 처리 매개 변수 재전송
    int retransmissionTimeout; ///< Retransmission request timeout, in milliseconds// / <재전송 요청 시간 제한 (밀리 초 단위)
    int rewriteTimeout; ///< Write request timeout, in milliseconds// / <쓰기 요청 제한 시간 (밀리 초)
    int retransmissionBurstRequestSize; ///< Number of packets requested for retransmission per burst// / <버스트 당 재전송 요청 된 패킷 수

};

#endif // QGCUASPARAMMANAGER_H
