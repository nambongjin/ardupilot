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
 *   @brief Implementation of MAVLinkSettingsWidget
 *   @author Lorenz Meier <mail@qgroundcontrol.org>
 */

#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

#include "MAVLinkSettingsWidget.h"
#include "LinkManager.h"
#include "UDPLink.h"
#include "ui_MAVLinkSettingsWidget.h"
#include <QSettings>

MAVLinkSettingsWidget::MAVLinkSettingsWidget(MAVLinkProtocol* protocol, QWidget *parent) :
    QWidget(parent),
    protocol(protocol),
    m_ui(new Ui::MAVLinkSettingsWidget)
{
    m_ui->setupUi(this);

    m_ui->gridLayout->setAlignment(Qt::AlignTop);

    // Initialize state
    // 상태를 초기화합니다.
    //m_ui->heartbeatCheckBox->setChecked(protocol->heartbeatsEnabled());
    //m_ui->loggingCheckBox->setChecked(protocol->loggingEnabled());
    //m_ui->versionCheckBox->setChecked(protocol->versionCheckEnabled());
    //m_ui->multiplexingCheckBox->setChecked(protocol->multiplexingEnabled());
    //m_ui->systemIdSpinBox->setValue(protocol->getSystemId());

    //m_ui->paramGuardCheckBox->setChecked(protocol->paramGuardEnabled());
    //m_ui->paramRetransmissionSpinBox->setValue(protocol->getParamRetransmissionTimeout());
    //m_ui->paramRewriteSpinBox->setValue(protocol->getParamRewriteTimeout());

    //m_ui->actionGuardCheckBox->setChecked(protocol->actionGuardEnabled());
    //m_ui->actionRetransmissionSpinBox->setValue(protocol->getActionRetransmissionTimeout());

    // AUTH
    // 저자
    //m_ui->droneOSCheckBox->setChecked(protocol->getAuthEnabled());
    QSettings settings;
    //m_ui->droneOSComboBox->setCurrentIndex(m_ui->droneOSComboBox->findText(settings.value("DRONEOS_HOST", "droneos.com:14555").toString()));
    //m_ui->droneOSLineEdit->setText(protocol->getAuthKey());

    // Connect actions
    // Heartbeat
    // 액션 연결
    // 하트 비트
    connect(protocol, SIGNAL(heartbeatChanged(bool)), m_ui->heartbeatCheckBox, SLOT(setChecked(bool)));
    connect(m_ui->heartbeatCheckBox, SIGNAL(toggled(bool)), protocol, SLOT(enableHeartbeats(bool)));
    // Logging
    // 로깅
    connect(protocol, SIGNAL(loggingChanged(bool)), m_ui->loggingCheckBox, SLOT(setChecked(bool)));
    // Version check
    // 버전 확인
    connect(protocol, SIGNAL(versionCheckChanged(bool)), m_ui->versionCheckBox, SLOT(setChecked(bool)));
    connect(m_ui->versionCheckBox, SIGNAL(toggled(bool)), protocol, SLOT(enableVersionCheck(bool)));
    // Logfile
    // 로그 파일
    connect(m_ui->logFileButton, SIGNAL(clicked()), this, SLOT(chooseLogfileName()));
    // System ID
    // 시스템 ID
    connect(protocol, SIGNAL(systemIdChanged(int)), m_ui->systemIdSpinBox, SLOT(setValue(int)));
    connect(m_ui->systemIdSpinBox, SIGNAL(valueChanged(int)), protocol, SLOT(setSystemId(int)));
    // Multiplexing
    // 다중화
    connect(protocol, SIGNAL(multiplexingChanged(bool)), m_ui->multiplexingCheckBox, SLOT(setChecked(bool)));
    connect(m_ui->multiplexingCheckBox, SIGNAL(toggled(bool)), protocol, SLOT(enableMultiplexing(bool)));
    // Parameter guard
    // 매개 변수 가드
    connect(protocol, SIGNAL(paramGuardChanged(bool)), m_ui->paramGuardCheckBox, SLOT(setChecked(bool)));
    connect(m_ui->paramGuardCheckBox, SIGNAL(toggled(bool)), protocol, SLOT(enableParamGuard(bool)));
    connect(protocol, SIGNAL(paramRetransmissionTimeoutChanged(int)), m_ui->paramRetransmissionSpinBox, SLOT(setValue(int)));
    connect(m_ui->paramRetransmissionSpinBox, SIGNAL(valueChanged(int)), protocol, SLOT(setParamRetransmissionTimeout(int)));
    connect(protocol, SIGNAL(paramRewriteTimeoutChanged(int)), m_ui->paramRewriteSpinBox, SLOT(setValue(int)));
    connect(m_ui->paramRewriteSpinBox, SIGNAL(valueChanged(int)), protocol, SLOT(setParamRewriteTimeout(int)));
    // Action guard
    // 액션 가드
    connect(protocol, SIGNAL(actionGuardChanged(bool)), m_ui->actionGuardCheckBox, SLOT(setChecked(bool)));
    connect(m_ui->actionGuardCheckBox, SIGNAL(toggled(bool)), protocol, SLOT(enableActionGuard(bool)));
    connect(protocol, SIGNAL(actionRetransmissionTimeoutChanged(int)), m_ui->actionRetransmissionSpinBox, SLOT(setValue(int)));
    connect(m_ui->actionRetransmissionSpinBox, SIGNAL(valueChanged(int)), protocol, SLOT(setActionRetransmissionTimeout(int)));
    // MAVLink AUTH
    connect(protocol, SIGNAL(authChanged(bool)), m_ui->droneOSCheckBox, SLOT(setChecked(bool)));
    connect(m_ui->droneOSCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableDroneOS(bool)));
    connect(protocol, SIGNAL(authKeyChanged(QString)), m_ui->droneOSLineEdit, SLOT(setText(QString)));
    connect(m_ui->droneOSLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setDroneOSKey(QString)));

    // Drone OS
    connect(m_ui->droneOSComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setDroneOSHost(QString)));
    // FIXME Manually trigger this action here, this brings control code to UI = BAD!
    // FIXME이 액션을 수동으로 여기에서 트리거하면 컨트롤 코드가 UI = BAD!
    setDroneOSHost(m_ui->droneOSComboBox->currentText());

    // Update values
    // 값을 업데이트합니다.
    //m_ui->versionLabel->setText(tr("MAVLINK_VERSION: %1").arg(protocol->getVersion()));
    //updateLogfileName(protocol->getLogfileName());

    // Connect visibility updates
    // 가시성 업데이트 연결
    connect(protocol, SIGNAL(versionCheckChanged(bool)), m_ui->versionLabel, SLOT(setVisible(bool)));
    //m_ui->versionLabel->setVisible(protocol->versionCheckEnabled());
//    // Multiplexing visibility
//    // 멀티플렉싱 가시성
//    connect(protocol, SIGNAL(multiplexingChanged(bool)), m_ui->multiplexingFilterCheckBox, SLOT(setVisible(bool)));
//    m_ui->multiplexingFilterCheckBox->setVisible(protocol->multiplexingEnabled());
//    connect(protocol, SIGNAL(multiplexingChanged(bool)), m_ui->multiplexingFilterLineEdit, SLOT(setVisible(bool)));
//    m_ui->multiplexingFilterLineEdit->setVisible(protocol->multiplexingEnabled());
    // Param guard visibility
    // Param guard 가시성
    connect(protocol, SIGNAL(paramGuardChanged(bool)), m_ui->paramRetransmissionSpinBox, SLOT(setVisible(bool)));
    //m_ui->paramRetransmissionSpinBox->setVisible(protocol->paramGuardEnabled());
    connect(protocol, SIGNAL(paramGuardChanged(bool)), m_ui->paramRetransmissionLabel, SLOT(setVisible(bool)));
    //m_ui->paramRetransmissionLabel->setVisible(protocol->paramGuardEnabled());
    connect(protocol, SIGNAL(paramGuardChanged(bool)), m_ui->paramRewriteSpinBox, SLOT(setVisible(bool)));
    //m_ui->paramRewriteSpinBox->setVisible(protocol->paramGuardEnabled());
    connect(protocol, SIGNAL(paramGuardChanged(bool)), m_ui->paramRewriteLabel, SLOT(setVisible(bool)));
    //m_ui->paramRewriteLabel->setVisible(protocol->paramGuardEnabled());
    // Action guard visibility
    connect(protocol, SIGNAL(actionGuardChanged(bool)), m_ui->actionRetransmissionSpinBox, SLOT(setVisible(bool)));
    //m_ui->actionRetransmissionSpinBox->setVisible(protocol->actionGuardEnabled());
    connect(protocol, SIGNAL(actionGuardChanged(bool)), m_ui->actionRetransmissionLabel, SLOT(setVisible(bool)));
    //m_ui->actionRetransmissionLabel->setVisible(protocol->actionGuardEnabled());

    // TODO implement filtering
    // and then remove these two lines
    // TODO 구현 필터링
    // 다음 두 줄을 제거하십시오.
    m_ui->multiplexingFilterCheckBox->setVisible(false);
    m_ui->multiplexingFilterLineEdit->setVisible(false);

//    // Update settings
//    // 설정 업데이트
//    m_ui->loggingCheckBox->setChecked(protocol->loggingEnabled());
//    m_ui->heartbeatCheckBox->setChecked(protocol->heartbeatsEnabled());
//    m_ui->versionCheckBox->setChecked(protocol->versionCheckEnabled());
}

void MAVLinkSettingsWidget::updateLogfileName(const QString& fileName)
{
    QFileInfo file(fileName);
    m_ui->logFileLabel->setText(file.fileName());
}

void MAVLinkSettingsWidget::chooseLogfileName()
{
    QString suggestedFileName = QGC::MAVLinkLogDirectory() + QGC::fileNameAsTime();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Specify MAVLink log file name"),
                                                    suggestedFileName
                                                    , tr("MAVLink Logfile (%1);;").arg(MAVLINK_LOGFILE_EXT));

    if (!fileName.endsWith(MAVLINK_LOGFILE_EXT))
    {
        fileName.append(MAVLINK_LOGFILE_EXT);
    }

    QFileInfo file(fileName);
    if (file.exists() && !file.isWritable())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("The selected logfile is not writable"));
        msgBox.setInformativeText(tr("Please make sure that the file %1 is writable or select a different file").arg(fileName));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        updateLogfileName(fileName);
       // m_ui->loggingCheckBox->setEnabled(protocol->startLogging(fileName));
    }
}

void MAVLinkSettingsWidget::enableDroneOS(bool enable)
{
    // Enable multiplexing
    // 멀티플렉싱 사용
    //protocol->enableMultiplexing(enable);
    // Get current selected host and port
    // 현재 선택된 호스트 및 포트 가져 오기
    QString hostString = m_ui->droneOSComboBox->currentText();
    //QString host = hostString.split(":").first();

    // Delete from all lists first
    // 모든 목록에서 먼저 삭제
    UDPLink* firstUdp = NULL;
    /*QList<LinkInterface*> links = LinkManager::instance()->getLinksForProtocol(protocol);
    foreach (LinkInterface* link, links)
    {
        UDPLink* udp = dynamic_cast<UDPLink*>(link);
        if (udp)
        {
            if (!firstUdp) firstUdp = udp;
            // Remove current hosts
            // 현재 호스트를 제거합니다.
            for (int i = 0; i < m_ui->droneOSComboBox->count(); ++i)
            {
                QString oldHostString = m_ui->droneOSComboBox->itemText(i);
                oldHostString = hostString.split(":").first();
                udp->removeHost(oldHostString);
            }
        }
    }*/

    // Re-add if enabled
    // 활성화 된 경우 다시 추가
    if (enable)
    {
        if (firstUdp)
        {
            firstUdp->addHost(hostString);
        }
        // Set key
        // 키 설정
       // protocol->setAuthKey(m_ui->droneOSLineEdit->text().trimmed());
        QSettings settings;
        settings.setValue("DRONEOS_HOST", m_ui->droneOSComboBox->currentText());
        settings.sync();
    }
    //protocol->enableAuth(enable);
}

void MAVLinkSettingsWidget::setDroneOSKey(QString key)
{
    Q_UNUSED(key);
    enableDroneOS(m_ui->droneOSCheckBox->isChecked());
}

void MAVLinkSettingsWidget::setDroneOSHost(QString host)
{
    Q_UNUSED(host);
    enableDroneOS(m_ui->droneOSCheckBox->isChecked());
}

MAVLinkSettingsWidget::~MAVLinkSettingsWidget()
{
    delete m_ui;
}

void MAVLinkSettingsWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MAVLinkSettingsWidget::hideEvent(QHideEvent* event)
{
    Q_UNUSED(event);
   // protocol->storeSettings();
}
