/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Implementation of CommConfigurationWindow
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *   @author Bill Bonney <billbonney@communistech.com>
 *
 */

#include "logging.h"

#include "CommConfigurationWindow.h"
#include "SerialConfigurationWindow.h"
#include "UDPLink.h"
#include "TCPLink.h"
#include "MAVLinkSimulationLink.h"
#ifdef XBEELINK
#include "XbeeLink.h"
#include "XbeeConfigurationWindow.h"
#endif // XBEELINK
#ifdef OPAL_RT
#include "OpalLink.h"
#include "OpalLinkConfigurationWindow.h"
#endif
#include "MAVLinkProtocol.h"
#include "MAVLinkSettingsWidget.h"
#include "QGCUDPLinkConfiguration.h"
#include "QGCUDPClientLinkConfiguration.h"
#include "QGCTCPLinkConfiguration.h"
#include "LinkManager.h"
#include "MainWindow.h"

#include <QDir>
#include <QFileInfoList>
#include <QBoxLayout>
#include <QWidget>

CommConfigurationWindow::CommConfigurationWindow(int linkid, ProtocolInterface* protocol, QWidget *parent)
    : QDialog(parent),
      m_linkid(linkid)

{
    Q_UNUSED(protocol);

    // Setup the user interface according to link type
    // 링크 유형에 따라 사용자 인터페이스를 설정합니다.
    ui.setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

    // Initialize basic ui state
    // 기본 UI 상태 초기화

    // Do not allow changes here unless advanced is checked
    // 고급을 체크하지 않으면 여기서 변경을 허용하지 않는다.
    ui.connectionType->setEnabled(false);
    ui.linkType->setEnabled(false);
    ui.protocolGroupBox->setVisible(false);
    ui.protocolTypeGroupBox->setVisible(false);

    // Connect UI element visibility to checkbox
    // UI 요소 가시성을 확인란에 연결
    ui.advancedOptionsCheckBox->setVisible(false);
    connect(ui.advCheckBox, SIGNAL(clicked(bool)), ui.connectionType, SLOT(setEnabled(bool)));
    connect(ui.advCheckBox, SIGNAL(clicked(bool)), ui.linkType, SLOT(setEnabled(bool)));
    connect(ui.advCheckBox, SIGNAL(clicked(bool)), ui.protocolGroupBox, SLOT(setVisible(bool)));
    ui.advCheckBox->setVisible(false);

    // add link types
    // 링크 유형 추가
    ui.linkType->addItem(tr("Serial"), QGC_LINK_SERIAL);
    ui.linkType->addItem(tr("UDP"), QGC_LINK_UDP);
    ui.linkType->addItem(tr("UDP Client"), QGC_LINK_UDP_CLIENT);
    ui.linkType->addItem(tr("TCP"), QGC_LINK_TCP);
    //    ui.linkType->addItem(tr("Simulation"), QGC_LINK_SIMULATION); // [TODO] left as key where to add simulation mode
    //     ui.linkType-> addItem (tr ( "Simulation"), QGC_LINK_SIMULATION); // [TODO] 키로 남음 시뮬레이션 모드를 추가 할 위치
#ifdef OPAL_RT
    ui.linkType->addItem(tr("Opal-RT Link"), QGC_LINK_OPAL);
#endif
#ifdef XBEELINK
	ui.linkType->addItem(tr("Xbee API"),QGC_LINK_XBEE);
#endif // XBEELINK
    ui.linkType->setEditable(false);

    // Create action to open this menu
    // Create configuration action for this link
    // Connect the current UAS
    // 이 메뉴를 열려면 액션 만들기
    // 이 링크에 대한 구성 작업 만들기
    // 현재 UAS 연결
    action = new QAction(QIcon(":/files/images/devices/network-wireless.svg"), "", this);
    action->setData(linkid);
    action->setEnabled(true);
    action->setVisible(true);

    setLinkName(LinkManager::instance()->getLinkName(linkid));
    connect(action, SIGNAL(triggered()), this, SLOT(show()));

    // Setup user actions and link notifications
    // 사용자 작업 및 링크 알림 설정
    connect(ui.connectButton, SIGNAL(clicked()), this, SLOT(setConnection()));
    connect(ui.closeButton, SIGNAL(clicked()), this->window(), SLOT(close()));
    connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(remove()));

    connect(LinkManager::instance(),SIGNAL(linkChanged(int)),this,SLOT(linkUpdate(int)));

    // Fill in the current data
    // 현재 데이터를 채운다.
    if(LinkManager::instance()->getLinkConnected(m_linkid)) ui.connectButton->setChecked(true);

    connectButtonStatus(linkid);

    // Open details pane for serial link if necessary
    // 필요한 경우 직렬 링크의 세부 정보 창을 엽니 다.

    if (LinkManager::instance()->getLinkType(linkid) == LinkInterface::SERIAL_LINK)
    {
        QWidget* conf = new SerialConfigurationWindow(linkid, this);
        ui.linkScrollArea->setWidget(conf);
        ui.linkGroupBox->setTitle(tr("Serial Link"));
        ui.linkType->setCurrentIndex(ui.linkType->findData(QGC_LINK_SERIAL));

    }
    else if (LinkManager::instance()->getLinkType(linkid) == LinkInterface::UDP_LINK)
    {
        QWidget* conf = new QGCUDPLinkConfiguration(linkid, this);
        ui.linkScrollArea->setWidget(conf);
        ui.linkGroupBox->setTitle(tr("UDP Link"));
        ui.linkType->setCurrentIndex(ui.linkType->findData(QGC_LINK_UDP));
    }
    else if (LinkManager::instance()->getLinkType(linkid) == LinkInterface::TCP_LINK)
    {
        QWidget *conf = new QGCTCPLinkConfiguration(linkid,this);
        ui.linkScrollArea->setWidget(conf);
        ui.linkGroupBox->setTitle(tr("TCP Link"));
        ui.linkType->setCurrentIndex(ui.linkType->findData(QGC_LINK_TCP));
    }
    else if (LinkManager::instance()->getLinkType(linkid) == LinkInterface::UDP_CLIENT_LINK)
    {
        QWidget* conf = new QGCUDPClientLinkConfiguration(linkid, this);
        ui.linkScrollArea->setWidget(conf);
        ui.linkGroupBox->setTitle(tr("UDP Client Link"));
        ui.linkType->setCurrentIndex(ui.linkType->findData(QGC_LINK_UDP_CLIENT));
    }

    // Display the widget
    // 위젯을 표시합니다.
    this->window()->setWindowTitle(tr("Settings for ") + LinkManager::instance()->getLinkName(linkid));
    this->hide();
}

void CommConfigurationWindow::connectButtonStatus(int linkid)
{
    if(LinkManager::instance()->getLinkConnected(linkid)) {
        ui.deleteButton->setEnabled(false);
        ui.connectionStatusLabel->setText(tr("Connected"));
        ui.connectButton->setText("Disconnect");
    } else {
        ui.deleteButton->setEnabled(true);
        ui.connectionStatusLabel->setText(tr("Disconnected"));
        ui.connectButton->setText("Connect");
    }
}

void CommConfigurationWindow::linkUpdate(int linkid)
{
    if (linkid != this->m_linkid)
    {
        return;
    }
    setLinkName(LinkManager::instance()->getLinkName(linkid));
    connectButtonStatus(linkid);
}

CommConfigurationWindow::~CommConfigurationWindow()
{

}

QAction* CommConfigurationWindow::getAction()
{
    return action;
}

void CommConfigurationWindow::setProtocol(int protocol)
{
    QLOG_DEBUG() << "Changing to protocol" << protocol;
}

void CommConfigurationWindow::setConnection()
{
    if (!LinkManager::instance()->getLinkConnected(m_linkid))
    {
        if (LinkManager::instance()->connectLink(m_linkid))
            this->window()->close();
    }
    else
    {
        LinkManager::instance()->disconnectLink(m_linkid);
    }
}

void CommConfigurationWindow::setLinkName(QString name)
{
    if (action)
    {
        action->setText(tr("%1 Settings").arg(name));
        action->setStatusTip(tr("Adjust setting for link %1").arg(name));
        this->window()->setWindowTitle(tr("Settings for %1").arg(name));
    }
}

void CommConfigurationWindow::remove()
{
    if(action) delete action; //delete action first since it has a pointer to link
    action=NULL;              // 링크를 가리키는 포인터가 있기 때문에 먼저 액션을 삭제하십시오.

    LinkManager::instance()->removeLink(m_linkid); //close & remove link from LinkManager list
                                                   // LinkManager 목록에서 링크를 닫고 제거합니다.
    this->window()->close();
    this->deleteLater();
}

void CommConfigurationWindow::connectionState(bool connect)
{
    ui.connectButton->setChecked(connect);
    if(connect) {
        ui.connectionStatusLabel->setText(tr("Connected"));
        ui.connectButton->setText(tr("Disconnect"));
    } else {
        ui.connectionStatusLabel->setText(tr("Disconnected"));
        ui.connectButton->setText(tr("Connect"));
    }
}
