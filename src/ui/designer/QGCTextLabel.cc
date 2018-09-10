#include "QGCTextLabel.h"
#include "ui_QGCTextLabel.h"
#include "logging.h"
#include "MAVLinkProtocol.h"
#include "UASManager.h"

#include <QDockWidget>


QGCTextLabel::QGCTextLabel(QWidget *parent) :
    QGCToolWidgetItem("Command Button", parent),
    ui(new Ui::QGCTextLabel)
{
    uas = 0;
    enabledNum = -1;
    ui->setupUi(this);

    connect(ui->editFinishButton, SIGNAL(clicked()), this, SLOT(endEditMode()));

    // Hide all edit items
    // 모든 편집 항목 숨기기
    ui->editFinishButton->hide();
    ui->editNameLabel->hide();
    ui->editTextParam->hide();
    ui->editComponentSpinBox->hide();
    ui->editLine1->hide();
    ui->editLine2->hide();

    ui->editLine1->setStyleSheet("QWidget { border: 1px solid #66666B; border-radius: 3px; padding: 10px 0px 0px 0px; background: #111122; }");
    ui->editLine2->setStyleSheet("QWidget { border: 1px solid #66666B; border-radius: 3px; padding: 10px 0px 0px 0px; background: #111122; }");

    // Add commands to combo box
    // 콤보 상자에 명령 추가


}

QGCTextLabel::~QGCTextLabel()
{
    delete ui;
}



void QGCTextLabel::startEditMode()
{
    // Hide elements
    // 요소 숨기기
    ui->nameLabel->hide();

    ui->editTextParam->show();
    ui->editFinishButton->show();
    ui->editNameLabel->show();
    ui->editComponentSpinBox->show();
    ui->editLine1->show();
    ui->editLine2->show();
    //setStyleSheet("QGroupBox { border: 1px solid #66666B; border-radius: 3px; padding: 10px 0px 0px 0px; background: #111122; }");
    // setStyleSheet ( "QGroupBox {테두리 : 1px 솔리드 # 66666B; 테두리 반경 : 3px; 패딩 : 10px 0px 0px; 배경 : # 111122;}");
    // Attempt to undock the dock widget
    // 도킹 위젯을 도킹 해제하려고 시도합니다.
    QWidget* p = this;
    QDockWidget* dock;

    do {
        p = p->parentWidget();
        dock = dynamic_cast<QDockWidget*>(p);

        if (dock)
        {
            dock->setFloating(true);
            break;
        }
    } while (p && !dock);

    isInEditMode = true;
}

void QGCTextLabel::endEditMode()
{
    ui->editFinishButton->hide();
    ui->editTextParam->hide();
    ui->editNameLabel->hide();
    ui->editComponentSpinBox->hide();
    ui->editLine1->hide();
    ui->editLine2->hide();

    ui->nameLabel->show();

    // Write to settings
    // 설정에 기록
    emit editingFinished();
    //setStyleSheet("");

    // Attempt to dock the dock widget
    // 도킹 위젯을 도킹하려고 시도합니다.
    QWidget* p = this;
    QDockWidget* dock;

    do {
        p = p->parentWidget();
        dock = dynamic_cast<QDockWidget*>(p);

        if (dock)
        {
            dock->setFloating(false);
            break;
        }
    } while (p && !dock);

    isInEditMode = false;
}

void QGCTextLabel::writeSettings(QSettings& settings)
{
    QLOG_DEBUG() << "COMMAND BUTTON WRITING SETTINGS";
    settings.setValue("TYPE", "COMMANDBUTTON");
    settings.setValue("QGC_COMMAND_BUTTON_DESCRIPTION", ui->nameLabel->text());

    settings.sync();
}
void QGCTextLabel::readSettings(const QString& pre,const QVariantMap& settings)
{
    ui->editTextParam->setText(settings.value(pre + "QGC_TEXT_SOURCE", "UNKNOWN").toString());
    //ui->editCommandComboBox->setCurrentIndex(settings.value(pre + "QGC_COMMAND_BUTTON_COMMANDID", 0).toInt());
    if (ui->editTextParam->text() == "NONE")
    {
        ui->editNameLabel->setText(settings.value(pre + "QGC_TEXT_TEXT","").toString());
        ui->nameLabel->setText(ui->editNameLabel->text());
    }
    else if (ui->editTextParam->text() == "MAV")
    {
        //MAV command text
        // MAV 명령 텍스트
        connect(uas,SIGNAL(textMessageReceived(int,int,int,QString)),this,SLOT(textMessageReceived(int,int,int,QString)));
    }

    //int commandId = settings.value(pre + "QGC_COMMAND_BUTTON_COMMANDID", 0).toInt();




    //ui->editNameLabel->setText(settings.value(pre + "QGC_COMMAND_BUTTON_DESCRIPTION", "ERROR LOADING BUTTON").toString());
    //ui->nameLabel->setText(settings.value(pre + "QGC_COMMAND_BUTTON_DESCRIPTION", "ERROR LOADING BUTTON").toString());
}
void QGCTextLabel::textMessageReceived(int uasid, int component, int severity, QString message)
{
    Q_UNUSED(uasid)
    Q_UNUSED(component)
    Q_UNUSED(severity)

    if (enabledNum != -1)
    {
        //SUCCESS: Executed CMD: 241
        // 성공 : 실행 된 명령 : 241
        if (message.contains("SUCCESS"))
        {
            if (message.trimmed().endsWith(QString::number(enabledNum)))
            {
                enabledNum = -1;
                ui->textLabel->setText(ui->textLabel->text() + " Complete");
            }
        }
        else
        {
            ui->textLabel->setText(message);
        }
    }
}

void QGCTextLabel::readSettings(const QSettings& settings)
{
    //ui->editNameLabel->setText(settings.value("QGC_COMMAND_BUTTON_DESCRIPTION", "ERROR LOADING BUTTON").toString());
    //ui->nameLabel->setText(settings.value("QGC_COMMAND_BUTTON_DESCRIPTION", "ERROR LOADING BUTTON").toString());
    ui->editTextParam->setText(settings.value("QGC_TEXT_SOURCE", "UNKNOWN").toString());
    ui->editNameLabel->setText(settings.value("QGC_TEXT_TEXT","").toString());
    //ui->editCommandComboBox->setCurrentIndex(settings.value(pre + "QGC_COMMAND_BUTTON_COMMANDID", 0).toInt());
    if (ui->editTextParam->text() == "NONE")
    {
        ui->textLabel->setText(ui->editNameLabel->text());
        ui->nameLabel->setText("");
    }
    else if (ui->editTextParam->text() == "MAV")
    {
        //MAV command text
        // MAV 명령 텍스트
        ui->nameLabel->setText(ui->editNameLabel->text());
        ui->textLabel->setText("");
        connect(uas,SIGNAL(textMessageReceived(int,int,int,QString)),this,SLOT(textMessageReceived(int,int,int,QString)));
    }
    else
    {

    }
}
void QGCTextLabel::enableText(int num)
{
    enabledNum = num;

}

void QGCTextLabel::setActiveUAS(UASInterface *uas)
{
    this->uas = uas;
}
