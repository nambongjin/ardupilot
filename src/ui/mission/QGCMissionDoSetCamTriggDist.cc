#include "QGCMissionDoSetCamTriggDist.h"
#include "ui_QGCMissionDoSetCamTriggDist.h"
#include "WaypointEditableView.h"

QGCMissionDoSetCamTriggDist::QGCMissionDoSetCamTriggDist(WaypointEditableView* WEV) :
    QWidget(WEV),
    ui(new Ui::QGCMissionDoSetCamTriggDist)
{
    ui->setupUi(this);
    this->WEV = WEV;
    //Using UI to change WP:
    // UI를 사용하여 WP 변경 :
    connect(this->ui->param1SpinBox, SIGNAL(valueChanged(double)),WEV,SLOT(changedParam1(double)));

    //Reading WP to update UI:
    // UI를 업데이트하기 위해 WP를 읽습니다.
    connect(WEV,SIGNAL(param1Broadcast(double)),this->ui->param1SpinBox,SLOT(setValue(double)));
}

QGCMissionDoSetCamTriggDist::~QGCMissionDoSetCamTriggDist()
{
    delete ui;
}
