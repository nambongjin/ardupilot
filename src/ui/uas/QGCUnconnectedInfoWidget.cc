#include "QGCUnconnectedInfoWidget.h"
#include "LinkInterface.h"
#include "LinkManager.h"
#include "MAVLinkSimulationLink.h"
#include "MainWindow.h"
#include "ui_QGCUnconnectedInfoWidget.h"

QGCUnconnectedInfoWidget::QGCUnconnectedInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCUnconnectedInfoWidget)
{
    ui->setupUi(this);

    //connect(ui->simulationButton, SIGNAL(clicked()), this, SLOT(simulate()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(addLink()));

    // Overwrite global style sheet
    //ui->connectButton->setStyleSheet("* { max-height: 1000; background-color: transparent; border-color: transparent; }");
    //ui->connectButton->setStyleSheet("QToolButton {background-color: green; border-radius: 20px; } QButton {} QPushButton {}");	     // 전역 스타일 시트 덮어 쓰기
    // ui-> connectButton-> setStyleSheet ( "* {max-height : 1000, 배경색 : 투명, 테두리 색상 : 투명;}");
    // ui-> connectButton-> setStyleSheet ( "QToolButton {background-color : green; border-radius : 20px;} QButton {} QPushButton {}");  
}

QGCUnconnectedInfoWidget::~QGCUnconnectedInfoWidget()
{
    delete ui;
}

/**
 * @brief Starts the system simulation	  * @brief 시스템 시뮬레이션을 시작합니다.  
 */
void QGCUnconnectedInfoWidget::simulate()
{
    // Try to get reference to MAVLinkSimulationlink	 MAVLinkSimulationlink에 대한 참조를 얻으려고 시도한다.  
    /*QList<LinkInterface*> links = LinkManager::instance()->getLinks();
    foreach(LinkInterface* link, links) {
        MAVLinkSimulationLink* sim = dynamic_cast<MAVLinkSimulationLink*>(link);
        if (sim) {
            sim->connectLink();
        }
    }*/
}

/**
 * @return Opens a "Connect new Link" popup	 return "새 링크 연결"팝업 창이 열립니다.  
 */
void QGCUnconnectedInfoWidget::addLink()
{
    MainWindow::instance()->addLink();
}
