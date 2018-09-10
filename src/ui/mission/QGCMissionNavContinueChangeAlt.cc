#include "QGCMissionNavContinueChangeAlt.h"
#include "ui_QGCMissionNavContinueChangeAlt.h"
#include "WaypointEditableView.h"

QGCMissionNavContinueChangeAlt::QGCMissionNavContinueChangeAlt(WaypointEditableView* WEV) :
    QWidget(WEV),
    ui(new Ui::QGCMissionNavContinueChangeAlt)
{
    ui->setupUi(this);
    this->WEV = WEV;
    //Using UI to change WP:	 UI를 사용하여 WP 변경하기 :  
    connect(this->ui->param7SpinBox, SIGNAL(valueChanged(double)),WEV,SLOT(changedParam7(double)));

    //Reading WP to update UI:	 UI를 업데이트하기 위해 WP를 읽습니다.  
    connect(WEV,SIGNAL(param7Broadcast(double)),this->ui->param7SpinBox,SLOT(setValue(double)));
}

QGCMissionNavContinueChangeAlt::~QGCMissionNavContinueChangeAlt()
{
    delete ui;
}
