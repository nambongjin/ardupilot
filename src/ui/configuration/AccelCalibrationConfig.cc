/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2013 APM_PLANNER PROJECT <http://www.diydrones.com>

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

#include "AccelCalibrationConfig.h"
#include "GAudioOutput.h"
#include "MainWindow.h"


const char* COUNTDOWN_STRING = "<h3>Calibrate MAV%03d<br>Time remaining until timeout: <b>%d</b><h3>";

AccelCalibrationConfig::AccelCalibrationConfig(QWidget *parent) : AP2ConfigWidget(parent),
    m_muted(false),
    m_isCalibrating(false),
    m_countdownCount(CALIBRATION_TIMEOUT_SEC)
{
    ui.setupUi(this);
    connect(ui.calibrateAccelButton,SIGNAL(clicked()),this,SLOT(calibrateButtonClicked()));

    m_accelAckCount=0;
    initConnections();
    //coutdownLabel
    connect(&m_countdownTimer,SIGNAL(timeout()),this,SLOT(countdownTimerTick()));
}

AccelCalibrationConfig::~AccelCalibrationConfig()
{
}
void AccelCalibrationConfig::countdownTimerTick()
{
    ui.coutdownLabel->setText(QString().sprintf(COUNTDOWN_STRING, m_uas->getUASID(), m_countdownCount--));
    if (m_countdownCount <= 0)
    {
        ui.coutdownLabel->setText("Command timed out, please try again");
        m_countdownTimer.stop();
        ui.calibrateAccelButton->setText("Calibrate\nAccelerometer");
        m_accelAckCount = 0;
    }
}

void AccelCalibrationConfig::activeUASSet(UASInterface *uas)
{
    if (m_uas)
    {
        disconnect(m_uas,SIGNAL(textMessageReceived(int,int,int,QString)),this,SLOT(uasTextMessageReceived(int,int,int,QString)));
        disconnect(m_uas,SIGNAL(connected()),this,SLOT(uasConnected()));
        disconnect(m_uas,SIGNAL(disconnected()),this,SLOT(uasDisconnected()));
    }
    AP2ConfigWidget::activeUASSet(uas);
    if (!uas)
    {
        return;
    }
    connect(m_uas,SIGNAL(textMessageReceived(int,int,int,QString)),this,SLOT(uasTextMessageReceived(int,int,int,QString)));
    connect(m_uas,SIGNAL(connected()),this,SLOT(uasConnected()));
    connect(m_uas,SIGNAL(disconnected()),this,SLOT(uasDisconnected()));
    uasConnected();

}
void AccelCalibrationConfig::uasConnected()
{

}

void AccelCalibrationConfig::uasDisconnected()
{

}

void AccelCalibrationConfig::calibrateButtonClicked()
{
    if (!m_uas)
    {
        showNullMAVErrorMessageBox();
        return;
    }

    ui.outputLabel->clear();

    m_isCalibrating = true; // this is to guard against showing unwanted GCS Text Messages.
                            // 원하지 않는 GCS 문자 메시지를 표시하지 않으려 고합니다.
    // Mute Audio until calibrated to avoid HeartBeat Warning message
    // HeartBeat 경고 메시지를 피하기 위해 보정 될 때까지 오디오 음소거
    if (GAudioOutput::instance()->isMuted() == false) {
        GAudioOutput::instance()->mute(true);
        m_muted = true;
    }
    m_uas->getLinks()->at(0)->disableTimeouts();

    MainWindow::instance()->toolBar().stopAnimation();

    if (m_accelAckCount == 0)
    {
        MAV_CMD command = MAV_CMD_PREFLIGHT_CALIBRATION;
        int confirm = 0;
        float param1 = 0.0;
        float param2 = 0.0;
        float param3 = 0.0;
        float param4 = 0.0;
        float param5 = 1.0;
        float param6 = 0.0;
        float param7 = 0.0;
        int component = 1;
        m_uas->executeCommand(command, confirm, param1, param2, param3, param4, param5, param6, param7, component);
        m_countdownCount = CALIBRATION_TIMEOUT_SEC;
        ui.coutdownLabel->setText(QString().sprintf(COUNTDOWN_STRING, m_uas->getUASID(), m_countdownCount--));
        m_countdownTimer.start(1000);
    }
    else if (m_accelAckCount <= 10)
    {
        m_uas->executeCommandAck(m_accelAckCount++,true);
        m_countdownCount = CALIBRATION_TIMEOUT_SEC;
    }
    else
    {
        m_uas->executeCommandAck(m_accelAckCount++,true);
        ui.coutdownLabel->setText("");
        m_countdownTimer.stop();
        ui.calibrateAccelButton->setText("Calibrate\nAccelerometer");
        if (m_accelAckCount > 8)
        {
            //We've clicked too many times! Reset.
            // 너무 많이 클릭했습니다! 다시 놓기.
            for (int i=0;i<8;i++)
            {
                m_uas->executeCommandAck(i,true);
            }
            m_accelAckCount = 0;
        }
    }


}

void AccelCalibrationConfig::hideEvent(QHideEvent *evt)
{
    Q_UNUSED(evt);

    if (m_muted) { // turns audio backon, when you leave the page
                   // 오디오 백온을 돌리면, 페이지를 떠날 때
        GAudioOutput::instance()->mute(false);
        m_muted = false;
    }

    MainWindow::instance()->toolBar().startAnimation();

    if (!m_uas || !m_accelAckCount)
    {
        return;
    }
    for (int i=m_accelAckCount;i<8;i++)
    {
        m_uas->executeCommandAck(i,true); //Clear out extra commands.
    }                                     // 추가 명령을 지 웁니다.
    m_uas->getLinks()->at(0)->enableTimeouts();
}
void AccelCalibrationConfig::uasTextMessageReceived(int uasid, int componentid, int severity, QString text)
{
    Q_UNUSED(uasid);
    Q_UNUSED(componentid);

    QLOG_DEBUG() << "Severity:" << severity << " text:" <<text;

    if (severity <= MAV_SEVERITY_CRITICAL)
    {
        //This is a calibration instruction
        // 이것은 교정 명령입니다.  
        if (!m_isCalibrating || text.startsWith("PreArm:") || text.startsWith("EKF") || text.startsWith("Arm") || text.startsWith("Initialising"))
        {
            // Don't show these warning messages
            // 이 경고 메시지를 표시하지 않습니다.
            return;
        }

        if (text.contains("Place") && text.contains ("and press any key"))
        {
            //Instruction
            // 지시 사항
            if (m_accelAckCount == 0)
            {
                //Calibration Sucessful\r"
                // 교정 성공 \ r "
                ui.calibrateAccelButton->setText("Continue\nPress SpaceBar");
            }
            ui.outputLabel->setText(text);
            m_accelAckCount++;
        }
        else if (text.contains("Calibration successful") || text.contains("FAILED") || text.contains("Failed CMD: 241"))
        {
            //Calibration complete success or failure
            // 보정 완료 성공 또는 실패
            if (m_muted) { // turns audio back on, when you complete fail or success
                           // 오디오를 다시 켭니다. 실패 또는 성공을 완료하면
                GAudioOutput::instance()->mute(false);
                m_muted = false;
            }
            ui.outputLabel->setText(ui.outputLabel->text() + "\n" + text);
            ui.coutdownLabel->setText("");
            m_countdownTimer.stop();
            MainWindow::instance()->toolBar().startAnimation();
            m_accelAckCount = 0;
            ui.calibrateAccelButton->setText("Calibrate\nAccelerometer");
            m_isCalibrating = false;
        }
        else
        {
            ui.outputLabel->setText(ui.outputLabel->text() + "\n" + text);
        }
    }

}
