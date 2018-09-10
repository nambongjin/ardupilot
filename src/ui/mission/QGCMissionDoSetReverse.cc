#include "QGCMissionDoSetReverse.h"
#include "ui_QGCMissionDoSetReverse.h"
#include "WaypointEditableView.h"

QGCMissionDoSetReverse::QGCMissionDoSetReverse(WaypointEditableView* WEV) :
    QWidget(WEV),
    ui(new Ui::QGCMissionDoSetReverse)
{
    ui->setupUi(this);
    this->WEV = WEV;
    //Using UI to change WP:
    // UI를 사용하여 WP 변경 
    connect(this->ui->param1SpinBox, SIGNAL(valueChanged(double)),WEV,SLOT(changedParam1(double)));

    //Reading WP to update UI:
    // UI를 업데이트하기 위해 WP를 읽습니다.
    connect(WEV,SIGNAL(param1Broadcast(double)),this->ui->param1SpinBox,SLOT(setValue(double)));
}

QGCMissionDoSetReverse::~QGCMissionDoSetReverse()
{
    delete ui;
}
