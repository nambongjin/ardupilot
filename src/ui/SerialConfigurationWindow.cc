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
 *   @brief Implementation of SerialConfigurationWindow
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include "logging.h"
#include "QGCCore.h"

#include <SerialConfigurationWindow.h>
#include <SerialLinkInterface.h>
#include <QDir>
#include <QSettings>
#include <QInputDialog>
#include <QFileInfoList>

SerialConfigurationWindow::SerialConfigurationWindow(int linkid, QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags),
    userConfigured(false)
{
    m_linkId = linkid;

    ui.setupUi(this);

    QList<QWidget*> widgetList = this->findChildren<QWidget*>();
    for (int i=0;i<widgetList.size();i++)
    {
        if (qobject_cast<QComboBox*>(widgetList[i]) || qobject_cast<QAbstractSpinBox*>(widgetList[i]) || qobject_cast<QAbstractSlider*>(widgetList[i]))
        {
            widgetList[i]->installEventFilter(QGCMouseWheelEventFilter::getFilter());
        }
    }

    // Create action to open this menu
    // Create configuration action for this link
    // Connect the current UAS
    // 이 메뉴를 열려면 액션 만들기
    // 이 링크에 대한 구성 작업 만들기
    // 현재 UAS 연결
    action = new QAction(QIcon(":/files/images/devices/network-wireless.svg"), "", this);

    // Set up baud rates
    // 보오율 설정
    ui.baudRate->clear();

    // Keep track of all desired baud rates by OS. These are iterated through
    // later and added to ui.baudRate.
    // 운영 체제별로 원하는 모든 전송 속도를 추적합니다. 이것들은
    // 나중에 ui.baudRate에 추가되었습니다.
    QList<int> supportedBaudRates;

    // Baud rates supported only by POSIX systems
    // 보오율은 POSIX 시스템에서만 지원됩니다.
#if defined(Q_OS_UNIX) || defined(Q_OS_LINUX) || defined(Q_OS_DARWIN)
    //supportedBaudRates << 50;
    //supportedBaudRates << 75;
    //supportedBaudRates << 134;
    //supportedBaudRates << 150;
    //supportedBaudRates << 200;
    //supportedBaudRates << 1800;
#endif

    // Baud rates supported only by Windows
#if defined(Q_OS_WIN)
    //supportedBaudRates << 14400;
    //supportedBaudRates << 56000;
    //supportedBaudRates << 128000;
    //supportedBaudRates << 256000;
#endif

    // Baud rates supported by everyone
    //supportedBaudRates << 110;
    //supportedBaudRates << 300;
    //supportedBaudRates << 600;
    //supportedBaudRates << 1200;
    //supportedBaudRates << 2400;
    //supportedBaudRates << 4800;
    supportedBaudRates << 9600;
    supportedBaudRates << 19200;
    supportedBaudRates << 38400;
    supportedBaudRates << 57600;
    supportedBaudRates << 115200;
    //supportedBaudRates << 230400;
    //supportedBaudRates << 460800;

#if defined(Q_OS_LINUX)
    // Baud rates supported only by Linux
    //supportedBaudRates << 500000;
    //supportedBaudRates << 576000;
#endif

    //supportedBaudRates << 921600;

    // Now actually add all of our supported baud rates to the UI.
    // 실제로 지원되는 모든 보오율을 UI에 추가합니다.
    qSort(supportedBaudRates.begin(), supportedBaudRates.end());
    for (int i = 0; i < supportedBaudRates.size(); ++i) {
        ui.baudRate->addItem(QString::number(supportedBaudRates.at(i)), supportedBaudRates.at(i));
    }

    setupPortList();

    // Load current link config
    // 현재 링크 설정로드
    SerialLinkInterface* serialLink = getSerialInterfaceLink();
    QString linkportname = "";
    int linkbaudrate = -1;
    if (serialLink) {
        linkportname = serialLink->getName();
        setLinkName(linkportname);
        linkbaudrate = serialLink->getBaudRate();
    }
    int portid = ui.portName->findText(linkportname);
    int baudid = ui.baudRate->findText(QString::number(linkbaudrate));

    QLOG_DEBUG() << "Baud rate:" << linkbaudrate << "Expected:" << baudid;
    if (baudid == -1)
    {
        if (linkbaudrate != -1 && linkbaudrate != 0)
        {
            //Baudrate is a custom baud rate, add it to the list.
            // Baudrate는 사용자 정의 전송 속도이며 목록에 추가합니다.
            ui.baudRate->addItem(QString::number(linkbaudrate));
            baudid = ui.baudRate->findText(QString::number(linkbaudrate));
        }
        else
        {
            //No baud rate found, select the default 115200
            // 전송 속도 없음, 기본 115200 선택
            baudid = ui.baudRate->findText("115200");
        }
    }
    ui.baudRate->setCurrentIndex(baudid);

    //Allows setting of custom baud rate, add it to the end of the list.
    // 사용자 정의 전송 속도를 설정하고 목록 끝에 추가합니다.
    ui.baudRate->addItem("Custom Baud Rate");
    if (portid == -1)
    {
        //No valid port name found, is it No Devices?
        // 유효한 포트 이름이 없습니다. No Devices입니까?
        if (linkportname == "No Devices")
        {
            if (ui.portName->count() > 0)
            {
                ui.portName->setCurrentIndex(0);
                setPortName(ui.portName->currentText());
            }
            else
            {
                ui.portName->setEditText("No Devices");
            }
        }
        else
        {
            ui.portName->setEditText(linkportname);
        }
    }
    else
    {
        ui.portName->setCurrentIndex(portid);
    }



    connect(action, SIGNAL(triggered()), this, SLOT(configureCommunication()));
    ui.advCheckBox->setVisible(true);

    // Make sure that a change in the link name will be reflected in the UI
    // 링크 이름의 변경 사항이 UI에 반영되는지 확인합니다.
    connect(LinkManager::instance(),SIGNAL(linkChanged(int)),this,SLOT(linkChanged(int)));
    linkChanged(m_linkId);

    // Connect the individual user interface inputs
    // 개별 사용자 인터페이스 입력을 연결합니다.
    connect(ui.portName, SIGNAL(editTextChanged(QString)), this, SLOT(setPortName(QString)));
    //connect(ui.portName, SIGNAL(currentIndexChanged(QString)), this, SLOT(setPortName(QString)));
    connect(ui.baudRate,SIGNAL(currentIndexChanged(QString)),this,SLOT(setBaudRateString(QString)));
    //connect(ui.baudRate, SIGNAL(activated(QString)), this->link, SLOT(setBaudRateString(QString)));
    connect(ui.flowControlCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableFlowControl(bool)));
    connect(ui.parNone, SIGNAL(toggled(bool)), this, SLOT(setParityNone(bool)));
    connect(ui.parOdd, SIGNAL(toggled(bool)), this, SLOT(setParityOdd(bool)));
    connect(ui.parEven, SIGNAL(toggled(bool)), this, SLOT(setParityEven(bool)));
    connect(ui.dataBitsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setDataBits(int)));
    connect(ui.stopBitsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setStopBits(int)));
    connect(ui.advCheckBox,SIGNAL(clicked(bool)),ui.advGroupBox,SLOT(setVisible(bool)));
    ui.advCheckBox->setChecked(false);
    ui.advGroupBox->setVisible(false);

    //connect(this->link, SIGNAL(connected(bool)), this, SLOT());
    //ui.portName->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    //ui.baudRate->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

    /*switch(this->link->getParityType()) {
    case 0:
        ui.parNone->setChecked(true);
        break;
    case 1:
        ui.parOdd->setChecked(true);
        break;
    case 2:
        ui.parEven->setChecked(true);
        break;
    default:
        // Enforce default: no parity in link
        setParityNone(true);
        ui.parNone->setChecked(true);
        break;
    }

    switch(this->link->getFlowType()) {
    case 0:
        ui.flowControlCheckBox->setChecked(false);
        break;
    case 1:
        ui.flowControlCheckBox->setChecked(true);
        break;
    default:
        ui.flowControlCheckBox->setChecked(false);
        enableFlowControl(false);
    }*/

    //ui.baudRate->setCurrentIndex(ui.baudRate->findText(QString("%1").arg(this->link->getBaudRate())));

    //ui.dataBitsSpinBox->setValue(this->link->getDataBits());
    //ui.stopBitsSpinBox->setValue(this->link->getStopBits());

    portCheckTimer = new QTimer(this);
    portCheckTimer->setInterval(1000);
    connect(portCheckTimer, SIGNAL(timeout()), this, SLOT(setupPortList()));

    // Display the widget
    // 위젯을 표시합니다.
    this->window()->setWindowTitle(tr("Serial Communication Settings"));
}
void SerialConfigurationWindow::linkChanged(int linkid)
{
    if (linkid != m_linkId)
    {
        return;
    }
    int baud = LinkManager::instance()->getSerialLinkBaud(linkid);
    QString port = LinkManager::instance()->getSerialLinkPort(linkid);
    disconnect(ui.baudRate,SIGNAL(currentIndexChanged(QString)),this,SLOT(setBaudRateString(QString)));
    disconnect(ui.portName, SIGNAL(editTextChanged(QString)), this, SLOT(setPortName(QString)));
    if (baud != ui.baudRate->currentText().toInt())
    {
        int baudid = ui.baudRate->findText(QString::number(baud));
        if (baudid == -1)
        {
            //Nothing found, add it just before the last item.
            // 찾을 수없는 항목은 마지막 항목 바로 앞에 추가하십시오.
            ui.baudRate->insertItem(ui.baudRate->count()-1,QString::number(baud));
            ui.baudRate->setCurrentIndex(ui.baudRate->count()-2);
        }
        else
        {
            ui.baudRate->setCurrentIndex(baudid);
        }
    }

    if (ui.portName->currentText() != port)
    {
        ui.portName->setEditText(port);
    }
    connect(ui.baudRate,SIGNAL(currentIndexChanged(QString)),this,SLOT(setBaudRateString(QString)));
    connect(ui.portName, SIGNAL(editTextChanged(QString)), this, SLOT(setPortName(QString)));
    connectionStateChanged(LinkManager::instance()->getLinkConnected(linkid));
}

void SerialConfigurationWindow::connectionStateChanged(bool connected)
{
    if (connected)
    {
        ui.baudRate->setEnabled(false);
        ui.portName->setEnabled(false);
    }
    else
    {
        ui.baudRate->setEnabled(true);
        ui.portName->setEnabled(true);
    }
}

void SerialConfigurationWindow::setAdvancedSettings(bool visible)
{
    ui.advGroupBox->setVisible(visible);
}

SerialConfigurationWindow::~SerialConfigurationWindow()
{

}

void SerialConfigurationWindow::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);
    portCheckTimer->start();
}

void SerialConfigurationWindow::hideEvent(QHideEvent* event)
{
    Q_UNUSED(event);
    portCheckTimer->stop();
}

QAction* SerialConfigurationWindow::getAction()
{
    return action;
}

void SerialConfigurationWindow::configureCommunication()
{
    QString selected = ui.portName->currentText();
    setupPortList();
    ui.portName->setEditText(selected);
    this->show();
}

void SerialConfigurationWindow::setupPortList()
{
    SerialLinkInterface* serialLink = getSerialInterfaceLink();
    if (!serialLink){
        return;
    }

    QLOG_DEBUG() << "SCW: Link is" << (serialLink->isConnected() ? "connected" : "disconnected");

    // Get the ports available on this system
    // 이 시스템에서 사용할 수있는 포트 가져 오기

    QList<QString> ports = serialLink->getCurrentPorts();

    QString storedName = serialLink->getPortName();
    QString currentName = ui.portName->currentText();

    if (ui.portName->currentText() != ui.portName->itemText(ui.portName->currentIndex()))
    {
        //Custom text entered
        // 사용자 정의 텍스트 입력
        if (storedName != currentName)
        {
            return;
        }
    }
    bool storedFound = false;

    // Add the ports in reverse order, because we prepend them to the list
    // 목록을 앞에 추가하기 때문에 역순으로 포트를 추가하십시오.
    disconnect(ui.portName, SIGNAL(editTextChanged(QString)), this, SLOT(setPortName(QString)));
    ui.portName->clear();

    for (int i = ports.count() - 1; i >= 0; --i)
    {
        ui.portName->insertItem(0,ports[i]);
        // Check if the stored link name is still present
        // 저장된 링크 이름이 여전히 존재하는지 확인
        if (ports[i].contains(storedName))
            storedFound = true;
    }

    if (storedFound)
    {
        int index = ui.portName->findText(storedName);
        ui.portName->setCurrentIndex(index);
    }
    else
    {
        //Put the name back
        // 이름을 다시 붙이십시오.
        ui.portName->setEditText(storedName);
    }
    connect(ui.portName, SIGNAL(editTextChanged(QString)), this, SLOT(setPortName(QString)));
}

void SerialConfigurationWindow::enableFlowControl(bool flow)
{
    if(flow)
    {
        getSerialInterfaceLink()->setFlowType(1);
    }
    else
    {
        getSerialInterfaceLink()->setFlowType(0);
    }
}

void SerialConfigurationWindow::setParityNone(bool accept)
{
    if (accept)
    {
        getSerialInterfaceLink()->setParityType(0);
    }
    //if (accept) link->setParityType(0);
}

void SerialConfigurationWindow::setParityOdd(bool accept)
{
    if (accept)
    {
        getSerialInterfaceLink()->setParityType(1);
    }
}

void SerialConfigurationWindow::setParityEven(bool accept)
{
    if (accept)
    {
        getSerialInterfaceLink()->setParityType(2);
    }
}
void SerialConfigurationWindow::setDataBits(int bits)
{
    getSerialInterfaceLink()->setDataBitsType(bits);
}

void SerialConfigurationWindow::setStopBits(int bits)
{
    getSerialInterfaceLink()->setStopBitsType(bits);
}

void SerialConfigurationWindow::setPortName(QString port)
{
#ifdef Q_OS_WIN
    port = port.split("-").first();
#endif
    port = port.remove(" ");

    getSerialInterfaceLink()->setPortName(port);
    userConfigured = true;
}

void SerialConfigurationWindow::setLinkName(QString name)
{
    Q_UNUSED(name);
    // FIXME
    //action->setText(tr("Configure ") + link->getName());
    //action->setStatusTip(tr("Configure ") + link->getName());
    //setWindowTitle(tr("Configuration of ") + link->getName());
}

void SerialConfigurationWindow::setBaudRateString(QString baud)
{
    if (baud == "Custom Baud Rate")
    {
        bool ok = false;
        int newbaud = QInputDialog::getInt(this,"Enter baud Rate","Baud Rate:",115200,0,INT_MAX,1,&ok);
        if (!ok)
        {
            disconnect(ui.baudRate,SIGNAL(currentIndexChanged(QString)),this,SLOT(setBaudRateString(QString)));
            ui.baudRate->setCurrentText(QString::number(LinkManager::instance()->getSerialLinkBaud(m_linkId)));
            connect(ui.baudRate,SIGNAL(currentIndexChanged(QString)),this,SLOT(setBaudRateString(QString)));
            return;
        }
        baud = QString::number(newbaud);
    }

    QString port = ui.portName->currentText();
#ifdef Q_OS_WIN
    port = port.split("-").first();
#endif
    port = port.remove(" ");

    SerialLinkInterface *link = getSerialInterfaceLink();
    if (link){
        link->setPortName(port);
        link->setBaudRate(baud.toInt());
    }
}

SerialLinkInterface* SerialConfigurationWindow::getSerialInterfaceLink() const
{
    return dynamic_cast<SerialLinkInterface*>(LinkManager::instance()->getLink(m_linkId));
}
