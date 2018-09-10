#ifndef QGCCOMBOBOX_H
#define QGCCOMBOBOX_H

#include <QWidget>
#include <QAction>

#include "QGCToolWidgetItem.h"

namespace Ui
{
class QGCComboBox;
}

class QGCComboBox : public QGCToolWidgetItem
{
    Q_OBJECT

public:
    explicit QGCComboBox(QWidget *parent = 0);
    ~QGCComboBox();

public slots:
    void startEditMode();
    void endEditMode();
    /** @brief Send the parameter to the MAV 	 MAV에 매개 변수 보내기*/
    void sendParameter();
    /** @brief Update the UI with the new parameter value	 새 매개 변수 값으로 UI 업데이트 */
    void setParameterValue(int uas, int component, int paramCount, int paramIndex, QString parameterName, const QVariant value);
    void writeSettings(QSettings& settings);
    void readSettings(const QString& pre,const QVariantMap& settings);
    void readSettings(const QSettings& settings);
    void refreshParamList();
    void setActiveUAS(UASInterface *uas);
    void selectComponent(int componentIndex);
    void selectParameter(int paramIndex);
    /** @brief Show descriptive text next to slider	 슬라이더 옆에 설명 텍스트를 표시합니다. */
    void showInfo(bool enable);
    /** @brief Show tool tip of calling element 	 호출 요소의 툴팁 표시*/
    void showTooltip();

protected slots:
    /** @brief Request the parameter of this widget from the MAV 	 MAV에서이 위젯의 ​​매개 변수 요청*/
    void requestParameter();
    /** @brief Button click to add a new item to the combobox 	 콤보 상자에 새 항목을 추가하려면 클릭하십시오*/
    void addButtonClicked();
    /** @brief Button click to remove the currently selected item from the combobox 	 단추 클릭하면 콤보 박스에서 현재 선택된 항목이 제거됩니다.*/
    void delButtonClicked();
    /** @brief Updates current parameter based on new combobox value 	 새 콤보 박스 값을 기반으로 현재 매개 변수를 업데이트합니다.*/
    void comboBoxIndexChanged(QString val);
protected:
    bool visibleEnabled;
    QString visibleParam;
    int visibleVal;
    QMap<QString,QString> comboBoxTextToParamMap;
    QMap<int,QPixmap> comboBoxIndexToPixmap;
    QMap<QString,int> comboBoxTextToValMap; ///< Comboboxtext/parameter value map	 Comboboxtext / 매개 변수 값 맵
    QString parameterName;         ///< Key/Name of the parameter	 <매개 변수의 키 / 이름
    QVariant parameterValue;          ///< Value of the parameter	 매개 변수 값
    double parameterScalingFactor; ///< Factor to scale the parameter between slider and true value	 슬라이더와 참 값 사이에서 매개 변수 크기를 조절하는 요소
    float parameterMin;
    bool isDisabled;
    float parameterMax;
    int component;                 ///< ID of the MAV component to address	 주소를 지정할 MAV 구성 요소의 ID
    //double scaledInt;
    void changeEvent(QEvent *e);

private:
    Ui::QGCComboBox *ui;
};

#endif // QGCCOMBOBOX_H
