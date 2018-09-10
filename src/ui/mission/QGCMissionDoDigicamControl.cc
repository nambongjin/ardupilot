#include "QGCMissionDoDigicamControl.h"
#include "ui_QGCMissionDoDigicamControl.h"
#include "WaypointEditableView.h"

QGCMissionDoDigicamControl::QGCMissionDoDigicamControl(WaypointEditableView* WEV) :
    QWidget(WEV),
    ui(new Ui::QGCMissionDoDigicamControl)
{
    ui->setupUi(this);
    this->WEV = WEV;

    //Using UI to change WP:
    // UI를 사용하여 WP 변경 :

    connect(this->ui->param1SpinBox, SIGNAL(valueChanged(double)),WEV,SLOT(changedParam1(double)));
    connect(this->ui->param4SpinBox, SIGNAL(valueChanged(double)),WEV,SLOT(changedParam4(double)));
    connect(this->ui->param5SpinBox, SIGNAL(valueChanged(double)),WEV,SLOT(changedParam5(double)));

    //Reading WP to update UI:
    // UI를 업데이트하기 위해 WP를 읽습니다.

    connect(WEV,SIGNAL(param1Broadcast(double)),this->ui->param1SpinBox,SLOT(setValue(double)));
    connect(WEV,SIGNAL(param4Broadcast(double)),this->ui->param4SpinBox,SLOT(setValue(double)));
    connect(WEV,SIGNAL(param5Broadcast(double)),this->ui->param5SpinBox,SLOT(setValue(double)));
}

QGCMissionDoDigicamControl::~QGCMissionDoDigicamControl()
{
    delete ui;
}
