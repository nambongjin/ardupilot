#include "QGCToolWidget.h"
#include "ui_QGCToolWidget.h"
#include "logging.h"
#include "QGCParamSlider.h"
#include "QGCComboBox.h"
#include "QGCTextLabel.h"
#include "QGCCommandButton.h"
#include "UASManager.h"

#include <QMenu>
#include <QList>
#include <QInputDialog>
#include <QDockWidget>
#include <QContextMenuEvent>
#include <QSettings>
#include <QFileDialog>
#include <QDesktopServices>

QGCToolWidget::QGCToolWidget(const QString& title, QWidget *parent, QSettings* settings) :
        QWidget(parent),
        mav(NULL),
        mainMenuAction(NULL),
        widgetTitle(title),
        ui(new Ui::QGCToolWidget)
{
    isFromMetaData = false;
    ui->setupUi(this);
    if (settings) loadSettings(*settings);

    if (title == "Unnamed Tool")
    {
        widgetTitle = QString("%1 %2").arg(title).arg(QGCToolWidget::instances()->count());
    }
    //QLOG_DEBUG() << "WidgetTitle" << widgetTitle;

    setObjectName(widgetTitle);
    createActions();
    toolLayout = ui->toolLayout;
    toolLayout->setAlignment(Qt::AlignTop);
    toolLayout->setSpacing(8);

    QDockWidget* dock = dynamic_cast<QDockWidget*>(this->parentWidget());
    if (dock) {
        dock->setWindowTitle(widgetTitle);
        dock->setObjectName(widgetTitle+"DOCK");
    }

    // Try with parent	 부모와 함께 시도  
    dock = dynamic_cast<QDockWidget*>(parent);
    if (dock) {
        dock->setWindowTitle(widgetTitle);
        dock->setObjectName(widgetTitle+"DOCK");
    }

    this->setWindowTitle(widgetTitle);
    QList<UASInterface*> systems = UASManager::instance()->getUASList();
    foreach (UASInterface* uas, systems)
    {
        UAS* newMav = dynamic_cast<UAS*>(uas);
        if (newMav)
        {
            addUAS(uas);
        }
    }
    connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(addUAS(UASInterface*)));
    if (!instances()->contains(widgetTitle)) instances()->insert(widgetTitle, this);

    // Enforce storage if this not loaded from settings
    // is MUST NOT BE SAVED if it was loaded from settings!
    //if (!settings) storeWidgetsToSettings();

/*
    // 설정에서로드되지 않은 경우 저장소를 적용합니다.
    // 설정에서로드 된 경우 // 절대로 저장하지 마십시오!
*/

}

QGCToolWidget::~QGCToolWidget()
{
    if (mainMenuAction) mainMenuAction->deleteLater();
    if (QGCToolWidget::instances()) QGCToolWidget::instances()->remove(widgetTitle);
    delete ui;
}

void QGCToolWidget::setParent(QWidget *parent)
{
    QWidget::setParent(parent);
    // Try with parent
    QDockWidget* dock = dynamic_cast<QDockWidget*>(parent);
    if (dock)
    {
        dock->setWindowTitle(getTitle());
        dock->setObjectName(getTitle()+"DOCK");
    }
}

/**
 * @param parent Object later holding these widgets, usually the main window
 * @return List of all widgets
 */

/*
 * @param parent 나중에이 위젯들을 가지고있는 객체, 보통 메인 윈도우
 * @return 모든 위젯의리스트
*/

QList<QGCToolWidget*> QGCToolWidget::createWidgetsFromSettings(QWidget* parent, QString settingsFile)
{
    // Load widgets from application settings	 애플리케이션 설정에서 위젯로드  
    QSettings* settings;

    // Or load them from a settings file	 또는 설정 파일에서로드합니다.  
    if (!settingsFile.isEmpty())
    {
        settings = new QSettings(settingsFile, QSettings::IniFormat);
       //QLOG_DEBUG() << "LOADING SETTINGS FROM" << settingsFile;
    }
    else
    {
        settings = new QSettings();
        //QLOG_DEBUG() << "LOADING SETTINGS FROM DEFAULT" << settings->fileName();
    }

    QList<QGCToolWidget*> newWidgets;
    settings->beginGroup("Custom_Tool_Widgets");
    int size = settings->beginReadArray("QGC_TOOL_WIDGET_NAMES");
    for (int i = 0; i < size; i++)
    {
        settings->setArrayIndex(i);
        QString name = settings->value("TITLE", "").toString();
        QString objname = settings->value("OBJECT_NAME", "").toString();

        if (!instances()->contains(name) && name.length() != 0)
        {
            //QLOG_DEBUG() << "CREATED WIDGET:" << name;
            QGCToolWidget* tool = new QGCToolWidget(name, parent, settings);
            tool->setObjectName(objname);
            newWidgets.append(tool);
        }
        else if (name.length() == 0)
        {
            // Silently catch empty widget name - sanity check
            // to survive broken settings (e.g. from user manipulation)

/*
            // 빈 위젯 이름을 자동으로 catch합니다.
            // 깨진 설정 (예 : 사용자 조작에서 생존)
*/

        }
        else
        {
            //QLOG_DEBUG() << "WIDGET" << name << "DID ALREADY EXIST, REJECTING";
        }
    }
    settings->endArray();

    //QLOG_DEBUG() << "NEW WIDGETS: " << newWidgets.size();

    // Load individual widget items
    for (int i = 0; i < newWidgets.size(); i++)
    {
        newWidgets.at(i)->loadSettings(*settings);
    }
    settings->endGroup();
    settings->sync();
    delete settings;

    return instances()->values();
}
void QGCToolWidget::showLabel(QString name,int num)
{
    for (int i=0;i<toolItemList.size();i++)
    {
        if (toolItemList[i]->objectName() == name)
        {
            QGCTextLabel *label = qobject_cast<QGCTextLabel*>(toolItemList[i]);
            if (label)
            {
                label->enableText(num);
            }
        }
    }
}

/**
 * @param singleinstance If this is set to true, the widget settings will only be loaded if not another widget with the same title exists
 */

/*
 * @param singleinstance 이것이 true로 설정되면 같은 제목을 가진 다른 위젯이 존재하지 않을 경우에만 위젯 설정이로드됩니다
*/

bool QGCToolWidget::loadSettings(const QString& settings, bool singleinstance)
{
    QSettings set(settings, QSettings::IniFormat);
    QStringList groups = set.childGroups();
    if (groups.length() > 0)
    {
        QString widgetName = groups.first();
	this->setObjectName(widgetName);
        if (singleinstance && QGCToolWidget::instances()->keys().contains(widgetName)) return false;
        // Do not use setTitle() here,
        // interferes with loading settings

/*
        // 여기서 setTitle ()을 사용하지 마십시오.
        // 로드 설정을 방해합니다.
*/

        widgetTitle = widgetName;
        //QLOG_DEBUG() << "WIDGET TITLE LOADED: " << widgetName;
        loadSettings(set);
        return true;
    }
    else
    {
        return false;
    }
}
void QGCToolWidget::setSettings(QVariantMap& settings)
{
    isFromMetaData = true;
    settingsMap = settings;
    QString widgetName = getTitle();
    int size = settingsMap["count"].toInt();
    for (int j = 0; j < size; j++)
    {
        QString type = settings.value(widgetName + "\\" + QString::number(j) + "\\" + "TYPE", "UNKNOWN").toString();
        if (type == "SLIDER")
        {
            QString checkparam = settingsMap.value(widgetName + "\\" + QString::number(j) + "\\" + "QGC_PARAM_SLIDER_PARAMID").toString();
            paramList.append(checkparam);
        }
        else if (type == "COMBO")
        {
            QString checkparam = settingsMap.value(widgetName + "\\" + QString::number(j) + "\\" + "QGC_PARAM_COMBOBOX_PARAMID").toString();
            paramList.append(checkparam);
        }
    }
}
QList<QString> QGCToolWidget::getParamList()
{
    return paramList;
}
void QGCToolWidget::setParameterValue(int uas, int component, QString parameterName, const QVariant value)
{
    Q_UNUSED(uas)
    Q_UNUSED(component)
    Q_UNUSED(value)

    QString widgetName = getTitle();
    int size = settingsMap["count"].toInt();
    if (paramToItemMap.contains(parameterName))
    {
        //If we already have an item for this parameter, updates are handled internally.

/*

        // 이미이 매개 변수에 대한 항목이있는 경우 내부적으로 업데이트가 처리됩니다.*/

        return;
    }

    for (int j = 0; j < size; j++)
    {
        QString type = settingsMap.value(widgetName + "\\" + QString::number(j) + "\\" + "TYPE", "UNKNOWN").toString();
        QGCToolWidgetItem* item = NULL;
        if (type == "COMMANDBUTTON")
        {
            //This shouldn't happen, but I'm not sure... so lets test for it.

/*
            // 이런 일은 있어서는 안되지만 확실하지는 않습니다 ... 그래서 테스트 해보십시오.
*/

            continue;
        }
        else if (type == "SLIDER")
        {
            QString checkparam = settingsMap.value(widgetName + "\\" + QString::number(j) + "\\" + "QGC_PARAM_SLIDER_PARAMID").toString();
            if (checkparam == parameterName)
            {
                item = new QGCParamSlider(this);
                paramToItemMap[parameterName] = item;
                addToolWidget(item);
                item->readSettings(widgetName + "\\" + QString::number(j) + "\\",settingsMap);
                return;
            }
        }
        else if (type == "COMBO")
        {
            QString checkparam = settingsMap.value(widgetName + "\\" + QString::number(j) + "\\" + "QGC_PARAM_COMBOBOX_PARAMID").toString();
            if (checkparam == parameterName)
            {
                item = new QGCComboBox(this);
                addToolWidget(item);
                item->readSettings(widgetName + "\\" + QString::number(j) + "\\",settingsMap);
                paramToItemMap[parameterName] = item;
                return;
            }
        }
    }
}

void QGCToolWidget::loadSettings(QVariantMap& settings)
{

    QString widgetName = getTitle();
    //settings.beginGroup(widgetName);
    QLOG_DEBUG() << "LOADING FOR" << widgetName;
    //int size = settings.beginReadArray("QGC_TOOL_WIDGET_ITEMS");
    int size = settings["count"].toInt();
    QLOG_DEBUG() << "CHILDREN SIZE:" << size;
    for (int j = 0; j < size; j++)
    {
        QApplication::processEvents();
        //settings.setArrayIndex(j);
        QString type = settings.value(widgetName + "\\" + QString::number(j) + "\\" + "TYPE", "UNKNOWN").toString();
        if (type != "UNKNOWN")
        {
            QGCToolWidgetItem* item = NULL;
            if (type == "COMMANDBUTTON")
            {
                item = new QGCCommandButton(this);
                //QLOG_DEBUG() << "CREATED COMMANDBUTTON";
            }
            else if (type == "TEXT")
            {
                item = new QGCTextLabel(this);
                item->setActiveUAS(mav);
            }
            else if (type == "SLIDER")
            {
                item = new QGCParamSlider(this);
                //QLOG_DEBUG() << "CREATED PARAM SLIDER";
            }
            else if (type == "COMBO")
            {
                item = new QGCComboBox(this);
                //QLOG_DEBUG() << "CREATED PARAM COMBOBOX";
            }
            if (item)
            {
                // Configure and add to layout
                addToolWidget(item);
                item->readSettings(widgetName + "\\" + QString::number(j) + "\\",settings);

                //QLOG_DEBUG() << "Created tool widget";
            }
        }
        else
        {
            QLOG_DEBUG() << "UNKNOWN TOOL WIDGET TYPE" << type;
        }
    }
    //settings.endArray();
    //settings.endGroup();
}

void QGCToolWidget::loadSettings(QSettings& settings)
{
    QString widgetName = getTitle();
    settings.beginGroup(widgetName);
    //QLOG_DEBUG() << "LOADING FOR" << widgetName;
    int size = settings.beginReadArray("QGC_TOOL_WIDGET_ITEMS");
    //QLOG_DEBUG() << "CHILDREN SIZE:" << size;
    for (int j = 0; j < size; j++)
    {
        settings.setArrayIndex(j);
        QString type = settings.value("TYPE", "UNKNOWN").toString();
        if (type != "UNKNOWN")
        {
            QGCToolWidgetItem* item = NULL;
            if (type == "COMMANDBUTTON")
            {
                QGCCommandButton *button = new QGCCommandButton(this);
                connect(button,SIGNAL(showLabel(QString,int)),this,SLOT(showLabel(QString,int)));
                item = button;
                item->setActiveUAS(mav);
                //QLOG_DEBUG() << "CREATED COMMANDBUTTON";
            }
            else if (type == "SLIDER")
            {
                item = new QGCParamSlider(this);
                item->setActiveUAS(mav);
                //QLOG_DEBUG() << "CREATED PARAM SLIDER";
            }
            else if (type == "COMBO")
            {
                item = new QGCComboBox(this);
                item->setActiveUAS(mav);
                QLOG_DEBUG() << "CREATED PARAM COMBOBOX";
            }
            else if (type == "TEXT")
            {
                item = new QGCTextLabel(this);
                item->setObjectName(settings.value("QGC_TEXT_ID").toString());
                item->setActiveUAS(mav);
            }

            if (item)
            {
                // Configure and add to layout
                addToolWidget(item);
                item->readSettings(settings);

                //QLOG_DEBUG() << "Created tool widget";
            }
        }
        else
        {
            //QLOG_DEBUG() << "UNKNOWN TOOL WIDGET TYPE";
        }
    }
    settings.endArray();
    settings.endGroup();
}

void QGCToolWidget::storeWidgetsToSettings(QString settingsFile)
{
    // Store list of widgets	    위젯 목록 저장  
    QSettings* settings;
    if (!settingsFile.isEmpty())
    {
        settings = new QSettings(settingsFile, QSettings::IniFormat);
        //QLOG_DEBUG() << "STORING SETTINGS TO" << settings->fileName();
    }
    else
    {
        settings = new QSettings();
        //QLOG_DEBUG() << "STORING SETTINGS TO DEFAULT" << settings->fileName();
    }

    settings->beginGroup("Custom_Tool_Widgets");
    int preArraySize = settings->beginReadArray("QGC_TOOL_WIDGET_NAMES");
    settings->endArray();

    settings->beginWriteArray("QGC_TOOL_WIDGET_NAMES");
    int num = 0;
    for (int i = 0; i < qMax(preArraySize, instances()->size()); ++i)
    {
        if (i < instances()->size())
        {
            // Updating value	 값을 업데이트 중입니다.  
            if (!instances()->values().at(i)->fromMetaData())
            {
                settings->setArrayIndex(num++);
                settings->setValue("TITLE", instances()->values().at(i)->getTitle());
                settings->setValue("OBJECT_NAME", instances()->values().at(i)->objectName());
                //QLOG_DEBUG() << "WRITING TITLE" << instances()->values().at(i)->getTitle();
            }
        }
        else
        {
            // Deleting old value	 이전 값 삭제  
            settings->remove("TITLE");
        }
    }
    settings->endArray();

    // Store individual widget items	 개별 위젯 항목 저장  
    for (int i = 0; i < instances()->size(); ++i)
    {
        instances()->values().at(i)->storeSettings(*settings);
    }
    settings->endGroup();
    settings->sync();
    delete settings;
}

void QGCToolWidget::storeSettings()
{
    QSettings settings;
    storeSettings(settings);
}

void QGCToolWidget::storeSettings(const QString& settingsFile)
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    storeSettings(settings);
}

void QGCToolWidget::storeSettings(QSettings& settings)
{
    if (isFromMetaData)
    {
        //Refuse to store if this is loaded from metadata or dynamically generated.	   메타 데이터에서로드되거나 동적으로 생성 된 경우 저장을 거부합니다.  
        return;
    }
    //QLOG_DEBUG() << "WRITING WIDGET" << widgetTitle << "TO SETTINGS";
    settings.beginGroup(widgetTitle);
    settings.beginWriteArray("QGC_TOOL_WIDGET_ITEMS");
    int k = 0; // QGCToolItem counter
    for (int j = 0; j  < children().size(); ++j)
    {
        // Store only QGCToolWidgetItems	  QGCToolWidgetItems 만 저장  
        QGCToolWidgetItem* item = dynamic_cast<QGCToolWidgetItem*>(children().at(j));
        if (item)
        {
            // Only count actual tool widget item children	 실제 도구 위젯 항목의 자식 만 계산합니다.  
            settings.setArrayIndex(k++);
            // Store the ToolWidgetItem	 ToolWidgetItem을 저장한다.  
            item->writeSettings(settings);
        }
    }
    //QLOG_DEBUG() << "WROTE" << k << "SUB-WIDGETS TO SETTINGS";
    settings.endArray();
    settings.endGroup();
}

void QGCToolWidget::addUAS(UASInterface* uas)
{
    UAS* newMav = dynamic_cast<UAS*>(uas);
    if (newMav)
    {
        // FIXME Convert to list	 FIXME리스트로 변환  
        if (mav == NULL) mav = newMav;
    }
}

void QGCToolWidget::contextMenuEvent (QContextMenuEvent* event)
{
    QMenu menu(this);
    menu.addAction(addParamAction);
    menu.addAction(addCommandAction);
    menu.addSeparator();
    menu.addAction(setTitleAction);
    menu.addAction(exportAction);
    menu.addAction(importAction);
    menu.addAction(deleteAction);
    menu.exec(event->globalPos());
}

void QGCToolWidget::hideEvent(QHideEvent* event)
{
    // Store settings	  설정 저장  
    QWidget::hideEvent(event);
}

/**
 * The widgets current view and the applied dock widget area.
 * Both values are only stored internally and allow an external
 * widget to configure it accordingly
 */

/*
/ * *
 * 위젯 현재보기 및 적용된 도크 위젯 영역.
 * 두 값은 내부적으로 만 저장되며 외부 값
 그에 따라 구성하는 * 위젯
*/

void QGCToolWidget::setViewVisibilityAndDockWidgetArea(int view, bool visible, Qt::DockWidgetArea area)
{
    viewVisible.insert(view, visible);
    dockWidgetArea.insert(view, area);
}

void QGCToolWidget::createActions()
{
    addParamAction = new QAction(tr("New &Parameter Slider"), this);
    addParamAction->setStatusTip(tr("Add a parameter setting slider widget to the tool"));
    connect(addParamAction, SIGNAL(triggered()), this, SLOT(addParam()));

    addCommandAction = new QAction(tr("New MAV &Command Button"), this);
    addCommandAction->setStatusTip(tr("Add a new action button to the tool"));
    connect(addCommandAction, SIGNAL(triggered()), this, SLOT(addCommand()));

    setTitleAction = new QAction(tr("Set Widget Title"), this);
    setTitleAction->setStatusTip(tr("Set the title caption of this tool widget"));
    connect(setTitleAction, SIGNAL(triggered()), this, SLOT(setTitle()));

    deleteAction = new QAction(tr("Delete this widget"), this);
    deleteAction->setStatusTip(tr("Delete this widget permanently"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteWidget()));

    exportAction = new QAction(tr("Export this widget"), this);
    exportAction->setStatusTip(tr("Export this widget to be reused by others"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportWidget()));

    importAction = new QAction(tr("Import widget"), this);
    importAction->setStatusTip(tr("Import this widget from a file (current content will be removed)"));
    connect(importAction, SIGNAL(triggered()), this, SLOT(importWidget()));
}

QMap<QString, QGCToolWidget*>* QGCToolWidget::instances()
{
    static QMap<QString, QGCToolWidget*>* instances;
    if (!instances) instances = new QMap<QString, QGCToolWidget*>();
    return instances;
}

QList<QGCToolWidgetItem*>* QGCToolWidget::itemList()
{
    static QList<QGCToolWidgetItem*>* instances;
    if (!instances) instances = new QList<QGCToolWidgetItem*>();
    return instances;
}
void QGCToolWidget::addParam(int uas,int component,QString paramname,QVariant value)
{
    isFromMetaData = true;
    QGCParamSlider* slider = new QGCParamSlider(this);
    connect(slider, SIGNAL(destroyed()), this, SLOT(storeSettings()));
    if (ui->hintLabel)
    {
        ui->hintLabel->deleteLater();
        ui->hintLabel = NULL;
    }
    toolLayout->addWidget(slider);
    slider->setActiveUAS(mav);
    slider->setParameterValue(uas,component,0,-1,paramname,value);


}

void QGCToolWidget::addParam()
{
    QGCParamSlider* slider = new QGCParamSlider(this);
    connect(slider, SIGNAL(destroyed()), this, SLOT(storeSettings()));
    if (ui->hintLabel)
    {
        ui->hintLabel->deleteLater();
        ui->hintLabel = NULL;
    }
    toolLayout->addWidget(slider);
    slider->startEditMode();
}

void QGCToolWidget::addCommand()
{
    QGCCommandButton* button = new QGCCommandButton(this);
    connect(button, SIGNAL(destroyed()), this, SLOT(storeSettings()));
    if (ui->hintLabel)
    {
        ui->hintLabel->deleteLater();
        ui->hintLabel = NULL;
    }
    toolLayout->addWidget(button);
    button->startEditMode();
}

void QGCToolWidget::addToolWidget(QGCToolWidgetItem* widget)
{
    if (ui->hintLabel)
    {
        ui->hintLabel->deleteLater();
        ui->hintLabel = NULL;
    }
    connect(widget, SIGNAL(destroyed()), this, SLOT(storeSettings()));
    toolLayout->addWidget(widget);
    toolItemList.append(widget);
}

void QGCToolWidget::exportWidget()
{
    const QString widgetFileExtension(".qgw");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Specify File Name"),
                                                    QGC::appDataDirectory(),
                                                    tr("Control Widget (*%1);;").arg(widgetFileExtension));
    if (!fileName.endsWith(widgetFileExtension))
    {
        fileName = fileName.append(widgetFileExtension);
    }
    storeSettings(fileName);
}

void QGCToolWidget::importWidget()
{
    const QString widgetFileExtension(".qgw");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Specify File Name"),
                                                    QGC::appDataDirectory(),
                                                    tr("Control Widget (*%1);;").arg(widgetFileExtension));
    loadSettings(fileName);
}

const QString QGCToolWidget::getTitle()
{
    return widgetTitle;
}

void QGCToolWidget::setTitle()
{
    QDockWidget* parent = dynamic_cast<QDockWidget*>(this->parentWidget());
    if (parent)
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Enter Widget Title"),
                                             tr("Widget title:"), QLineEdit::Normal,
                                             parent->windowTitle(), &ok);
        if (ok && !text.isEmpty())
        {
            setTitle(text);
        }
    }
}

void QGCToolWidget::setWindowTitle(const QString& title)
{
    // Sets title and calls setWindowTitle on QWidget	 제목을 설정하고 QWidget에 setWindowTitle을 호출합니다.  
    widgetTitle = title;
    QWidget::setWindowTitle(title);
}

void QGCToolWidget::setTitle(QString title)
{
    // Remove references to old title	 이전 제목에 대한 참조를 제거합니다.  
    /*QSettings settings;
    settings.beginGroup(widgetTitle);
    settings.remove("");
    settings.endGroup();
    settings.sync();*/

    if (instances()->contains(widgetTitle)) instances()->remove(widgetTitle);

    // Switch to new title	 새 제목으로 전환  
    widgetTitle = title;

    if (!instances()->contains(title)) instances()->insert(title, this);
    QWidget::setWindowTitle(title);
    QDockWidget* parent = dynamic_cast<QDockWidget*>(this->parentWidget());
    if (parent) parent->setWindowTitle(title);
    // Store all widgets	 모든 위젯 저장  
    //storeWidgetsToSettings();

    emit titleChanged(title);
    if (mainMenuAction) mainMenuAction->setText(title);
}

void QGCToolWidget::setMainMenuAction(QAction* action)
{
    this->mainMenuAction = action;
}

void QGCToolWidget::deleteWidget()
{
    // Remove from settings	 설정에서 제거  

    // Hide	 숨기기  
    this->hide();
    instances()->remove(getTitle());
    /*QSettings settings;
    settings.beginGroup(getTitle());
    settings.remove("");
    settings.endGroup();
    storeWidgetsToSettings();*/
    storeWidgetsToSettings();

    // Delete	 삭제  
    this->deleteLater();
}
