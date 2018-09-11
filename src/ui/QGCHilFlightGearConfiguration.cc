#include "QGCHilFlightGearConfiguration.h"
#include "ui_QGCHilFlightGearConfiguration.h"

#include "MainWindow.h"

QGCHilFlightGearConfiguration::QGCHilFlightGearConfiguration(UAS* mav,QWidget *parent) :
    QWidget(parent),
    mav(mav),
    ui(new Ui::QGCHilFlightGearConfiguration)
{
    ui->setupUi(this);

    QStringList items = QStringList();
    if (mav->getSystemType() == MAV_TYPE_FIXED_WING)
    {
        items << "EasyStar";
        items << "Rascal110-JSBSim";
        items << "c172p";
        items << "YardStik";
        items << "Malolo1";
    }
    else if (mav->getSystemType() == MAV_TYPE_QUADROTOR)
    {
        items << "arducopter";
    }
    else
    {
        items << "<aircraft>";
    }
    ui->aircraftComboBox->addItems(items);
}

QGCHilFlightGearConfiguration::~QGCHilFlightGearConfiguration()
{
    delete ui;
}

void QGCHilFlightGearConfiguration::on_startButton_clicked()
{
    //XXX check validity of inputs
    // XXX 입력의 유효성 검사
    QString options = ui->optionsPlainTextEdit->toPlainText();
    options.append(" --aircraft=" + ui->aircraftComboBox->currentText());
    // FIXME: 29/4/2014 UI is not insync with this feature
    // FIXME : 2014 년 29/4 분기 UI가이 기능과 비동기 적이 아닙니다.


    //mav->enableHilFlightGear(true,  options, ui->sensorHilCheckBox->isChecked(), this);
}

void QGCHilFlightGearConfiguration::on_stopButton_clicked()
{
    mav->stopHil();
}

void QGCHilFlightGearConfiguration::on_barometerOffsetLineEdit_textChanged(const QString& baroOffset)
{
    emit barometerOffsetChanged(baroOffset.toFloat());
}

