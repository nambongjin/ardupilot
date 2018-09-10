#ifndef QGCTOOLWIDGET_H
#define QGCTOOLWIDGET_H

#include <QWidget>
#include <QAction>
#include <QMap>
#include <QVBoxLayout>
#include "QGCToolWidgetItem.h"

#include "UAS.h"

namespace Ui
{
class QGCToolWidget;
}

class QGCToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGCToolWidget(const QString& title=QString("Unnamed Tool"), QWidget *parent = 0, QSettings* settings = 0);
    ~QGCToolWidget();

    /** @brief Factory method to instantiate all tool widgets	 모든 도구 위젯을 인스턴스화하는 팩토리 메소드 */
    static QList<QGCToolWidget*> createWidgetsFromSettings(QWidget* parent, QString settingsFile=QString());
    /** @Give the tool widget a reference to its action in the main menu 	 도구 위젯에 주 메뉴에서 해당 동작에 대한 참조 표시*/
    void setMainMenuAction(QAction* action);
    /** @brief All instances of this class 	 클래스의 모든 인스턴스*/
    static QMap<QString, QGCToolWidget*>* instances();
    /** @brief Get title of widget 	 위젯의 제목 가져 오기*/
    const QString getTitle();

    int isVisible(int view) { return viewVisible.value(view, false); }
    Qt::DockWidgetArea getDockWidgetArea(int view) { return dockWidgetArea.value(view, Qt::BottomDockWidgetArea); }
    void setParent(QWidget *parent);

public slots:
    void addUAS(UASInterface* uas);
    /** @brief Delete this widget	 위젯 삭제 */
    void deleteWidget();
    /** @brief Export this widget to a file	 위젯을 파일로 내보내기*/
    void exportWidget();
    /** @brief Import settings for this widget from a file	 파일에서이 위젯의 ​​설정 가져 오기 */
    void importWidget();
    /** @brief Store all widgets of this type to QSettings	 유형의 모든 위젯을 QSettings에 저장  */
    static void storeWidgetsToSettings(QString settingsFile=QString());
    void loadSettings(QVariantMap& settings);
    /** @brief Load this widget from a QSettings object 	 QSettings 객체에서이 위젯로드  */
    void loadSettings(QSettings& settings);
    /** @brief Load this widget from a settings file 	 설정 파일에서 위젯로드 */
    bool loadSettings(const QString& settings, bool singleinstance=false);
    /** @brief Store this widget to a QSettings object	 위젯을 QSettings 객체에 저장 */
    void storeSettings(QSettings& settings);
    /** @brief Store this widget to a settings file 	 위젯을 설정 파일에 저장하십시오.*/
    void storeSettings(const QString& settingsFile);
    /** @brief Store this widget to a settings file	 위젯을 설정 파일에 저장하십시오. */
    void storeSettings();
    /** @brief Store the view id and dock widget area 	 	  뷰 id와 도킹 위젯 영역 저장*/
    void setViewVisibilityAndDockWidgetArea(int view, bool visible, Qt::DockWidgetArea area);
    void setSettings(QVariantMap& settings);
    QList<QString> getParamList();
    void setParameterValue(int uas, int component, QString parameterName, const QVariant value);
    bool fromMetaData() { return isFromMetaData; }
    void showLabel(QString name,int num);
signals:
    void titleChanged(QString);

protected:
    bool isFromMetaData;
    QMap<QString,QGCToolWidgetItem*> paramToItemMap;
    QList<QGCToolWidgetItem*> toolItemList;
    QList<QString> paramList;
    QVariantMap settingsMap;
    QAction* addParamAction;
    QAction* addCommandAction;
    QAction* setTitleAction;
    QAction* deleteAction;
    QAction* exportAction;
    QAction* importAction;
    QVBoxLayout* toolLayout;
    UAS* mav;
    QAction* mainMenuAction;             ///< Main menu action	 메인 메뉴 액션
    QMap<int, Qt::DockWidgetArea> dockWidgetArea;   ///< Dock widget area desired by this widget	 이 위젯이 원하는 위젯 영역 고정
    QMap<int, bool> viewVisible;  ///< Visibility in one view	 하나의보기에서의 가시성
    QString widgetTitle;
    static int instanceCount;     ///< Number of instances around	 주변 인스턴스 수

    void contextMenuEvent(QContextMenuEvent* event);
    void createActions();
    QList<QGCToolWidgetItem* >* itemList();
    /** @brief Add an existing tool widget	 기존 도구 위젯 추가 */
    void addToolWidget(QGCToolWidgetItem* widget);

    void hideEvent(QHideEvent* event);
public slots:
    void setTitle(QString title);
    void addParam(int uas,int component,QString paramname,QVariant value);
protected slots:
    void addParam();
    void addCommand();
    void setTitle();

    void setWindowTitle(const QString& title);


private:
    Ui::QGCToolWidget *ui;
};

#endif // QGCTOOLWIDGET_H
