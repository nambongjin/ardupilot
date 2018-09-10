/*=====================================================================

APM_PLANNER Open Source Ground Control Station

(c) 2013, Bill Bonney <billbonney@communistech.com>

This file is part of the APM_PLANNER project

    APM_PLANNER is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    APM_PLANNER is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with APM_PLANNER. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Serial Settings View.
 *
 *   @author Bill Bonney <billbonney@communistech.com>
 *
 * Influenced from Qt examples by :-
 * Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
 * Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
 *
 */
/**
 * @file
 * @ 간단한 시리얼 설정보기.
 *
 * @author Bill Bonney <billbonney@communistech.com>
 *
 * 다음과 같은 Qt 예제의 영향 : -
 * Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
 * Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
 *
 */
#include "logging.h"
#include "SerialSettingsDialog.h"
#include "TerminalConsole.h"
#include "ui_SerialSettingsDialog.h"

#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>
#include <QIntValidator>
#include <QLineEdit>
#include <QPointer>

QT_USE_NAMESPACE

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    m_intValidator = new QIntValidator(0, 4000000, this);

    ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    connect(ui->applyButton, SIGNAL(clicked()),
            this, SLOT(apply()));
    connect(ui->serialPortInfoListBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(showPortInfo(int)));
    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(checkCustomBaudRatePolicy(int)));

    fillPortsParameters();
    fillPortsInfo(*ui->serialPortInfoListBox);
    updateSettings();

    //Keep refreshing the serial port list
    // 시리얼 포트 목록을 새로 고칩니다.
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(populateSerialPorts()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

const SerialSettings& SettingsDialog::settings() const
{
    return m_currentSettings;
}

void SettingsDialog::showPortInfo(int idx)
{
    if (idx != -1) {
        QStringList list = ui->serialPortInfoListBox->itemData(idx).toStringList();
        ui->descriptionLabel->setText(tr("Description: %1").arg(list.at(1)));
        ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.at(2)));
        ui->locationLabel->setText(tr("Location: %1").arg(list.at(3)));
        ui->vidLabel->setText(tr("Vendor Identifier: %1").arg(list.at(4)));
        ui->pidLabel->setText(tr("Product Identifier: %1").arg(list.at(5)));
    }
}

void SettingsDialog::apply()
{
    updateSettings();
    hide();
}

void SettingsDialog::checkCustomBaudRatePolicy(int idx)
{
    bool isCustomBaudRate = !ui->baudRateBox->itemData(idx).isValid();
    ui->baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        ui->baudRateBox->clearEditText();
        QLineEdit *edit = ui->baudRateBox->lineEdit();
        edit->setValidator(m_intValidator);
    }
}

void SettingsDialog::fillPortsParameters()
{
    // fill baud rate (is not the entire list of available values,
    // desired values??, add your independently)
    // 전송 속도를 채 웁니다. (사용 가능한 값의 전체 목록이 아니며,
    // 원하는 값 ??, 독립적으로 추가)
    ui->baudRateBox->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->baudRateBox->addItem(QLatin1String("57600"), QSerialPort::Baud57600);
    ui->baudRateBox->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QLatin1String("Custom"));

    // fill data bits
    // 데이터 비트 채우기
    ui->dataBitsBox->addItem(QLatin1String("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QLatin1String("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QLatin1String("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QLatin1String("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    // fill parity
    // 패리티 채우기
    ui->parityBox->addItem(QLatin1String("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);

    // fill stop bits
    // 스톱 비트 채우기
    ui->stopBitsBox->addItem(QLatin1String("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QLatin1String("2"), QSerialPort::TwoStop);

    // fill flow control
    // 흐름 제어 채우기
    ui->flowControlBox->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SettingsDialog::populateSerialPorts()
{
    QLOG_TRACE() << "SettingsDialog::populateSerialPorts";
    fillPortsInfo(*ui->serialPortInfoListBox);
}

void SettingsDialog::fillPortsInfo(QComboBox &comboBox)
{
    QLOG_DEBUG() << "fillPortsInfo ";
    QString current = comboBox.itemText(comboBox.currentIndex());
    disconnect(&comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setLink(int)));
    comboBox.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QStringList list;
        list << info.portName()
             << info.description()
             << info.manufacturer()
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString())
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());

        int found = comboBox.findData(list);
        if (found == -1) {
            QLOG_INFO() << "Inserting " << list.first();
            comboBox.insertItem(0,list[0], list);
        } else {
            // Do nothing as the port is already listed
            // 포트가 이미 나열되어 있으므로 아무 작업도 수행하지 않습니다.
        }
    }
    for (int i=0;i<comboBox.count();i++)
    {
        if (comboBox.itemText(i) == current)
        {
            comboBox.setCurrentIndex(i);
            break;
        }
    }
    setLink(comboBox.currentIndex());
    connect(&comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setLink(int)));
}

void SettingsDialog::setLink(int index)
{
    if (index == -1)
    {
        return;
    }

    m_currentSettings.name = ui->serialPortInfoListBox->itemData(index).toStringList()[0];
    QLOG_INFO() << "Changed Link to:" << m_currentSettings.name;

}

void SettingsDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    // Start refresh Timer
    // 새로 고침 타이머를 시작합니다.
    m_timer.start(2000);
}

void SettingsDialog::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    // Stop the port list refeshing
    // 포트 목록 refeshing 중지
    m_timer.stop();

}

void SettingsDialog::updateSettings()
{
    m_currentSettings.name = ui->serialPortInfoListBox->currentText();

    // Baud Rate
    // 전송 속도
    if (ui->baudRateBox->currentIndex() == 4) {
        // custom baud rate
        // 사용자 정의 전송 속도
        m_currentSettings.baudRate = ui->baudRateBox->currentText().toInt();
    } else {
        // standard baud rate
        // 표준 보오율
        m_currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                    ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
    }
    // Data bits
    // 데이터 비트
    m_currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
    // Parity
    // 패리티
    m_currentSettings.parity = static_cast<QSerialPort::Parity>(
                ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
    // Stop bits
    // 정지 비트
    m_currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
    // Flow control
    // 흐름 제어
    m_currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
                ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
}
