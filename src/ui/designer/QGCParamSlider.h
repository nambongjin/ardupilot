#ifndef QGCPARAMSLIDER_H
#define QGCPARAMSLIDER_H

#include <QWidget>
#include <QAction>

#include "QGCToolWidgetItem.h"

namespace Ui
{
class QGCParamSlider;
}

class QGCParamSlider : public QGCToolWidgetItem
{
    Q_OBJECT

public:
    explicit QGCParamSlider(QWidget *parent = 0);
    ~QGCParamSlider();

public slots:
    void startEditMode();
    void endEditMode();
    /** @brief Send the parameter to the MAV 	 MAV에 매개 변수 보내기*/
    void sendParameter();
    /** @brief Set the slider value as parameter value	 슬라이더 값을 매개 변수 값으로 설정 */
    void setSliderValue(int sliderValue);
    /** @brief Update the UI with the new parameter value	 새 매개 변수 값으로 UI 업데이트 */
    void setParameterValue(int uas, int component, int paramCount, int paramIndex, QString parameterName, const QVariant value);
    void writeSettings(QSettings& settings);
    void readSettings(const QSettings& settings);
    void readSettings(const QString& pre,const QVariantMap& settings);
    void refreshParamList();
    void setActiveUAS(UASInterface *uas);
    void selectComponent(int componentIndex);
    void selectParameter(int paramIndex);
    /** @brief Set a double parameter value 	  이중 매개 변수 값 설정*/
    void setParamValue(double value);
    /** @brief Set an integer parameter value 	 정수 매개 변수 값 설정*/
    void setParamValue(int value);
    /** @brief Show descriptive text next to slider 	 슬라이더 옆에 설명 텍스트를 표시합니다.*/
    void showInfo(bool enable);
    /** @brief Show tool tip of calling element	 호출 요소의 툴팁 표시*/
    void showTooltip();

protected slots:
    /** @brief Request the parameter of this widget from the MAV 	 MAV에서이 위젯의 ​​매개 변수 요청 */
    void requestParameter();

protected:
    bool visibleEnabled;
    QString visibleParam;
    int visibleVal;
    //The below variables, and usage in QGCParamSlider.cc are a bit of a hack, since disconnect() does not seem to take effect
    //immediatly (perhaps it is put into the event loop?) - MLC

/*
    // QGCParamSlider.cc의 아래 변수와 사용법은 약간의 해킹입니다. disconnect ()는 효과가없는 것 같습니다.
    // immediatly (아마도 이벤트 루프에 삽입됩니까?) - MLC
*/

    bool valueModLock;              ///< Used to keep the slider/spinboxes from updating each other during user input	사용자가 입력하는 동안 슬라이더 / 스핀 상자가 서로 업데이트되지 않도록 유지하는 데 사용됩니다.
    bool valueModLockParam;         ///< Used to keep the slider/spinboxes from udpating each other when a new parametervalue comes in	 새로운 매개 변수 값이 들어 왔을 때 슬라이더 / 스핀 상자가 서로 짝 지워지지 않도록 유지하는 데 사용됩니다.
    QString parameterName;         ///< Key/Name of the parameter	 매개 변수의 키 / 이름
    QVariant parameterValue;          ///< Value of the parameter	 매개 변수 값
    double parameterScalingFactor; ///< Factor to scale the parameter between slider and true value	 슬라이더와 참 값 사이에서 매개 변수 크기를 조절하는 요소
    float parameterMin;
    float parameterMax;
    int component;                 ///< ID of the MAV component to address	 주소를 지정할 MAV 구성 요소의 ID
    double scaledInt;
    void changeEvent(QEvent *e);

    /** @brief Convert scaled int to float 	 스케일 된 int를 float로 변환*/

    float scaledIntToFloat(int sliderValue);
    int floatToScaledInt(float value);

private:
    Ui::QGCParamSlider *ui;
};

#endif // QGCPARAMSLIDER_H
