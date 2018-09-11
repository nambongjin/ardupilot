#ifndef MAVLINKSETTINGSWIDGET_H
#define MAVLINKSETTINGSWIDGET_H

#include <QtWidgets/QWidget>

#include "MAVLinkProtocol.h"

namespace Ui
{
class MAVLinkSettingsWidget;
}

class MAVLinkSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    MAVLinkSettingsWidget(MAVLinkProtocol* protocol, QWidget *parent = 0);
    ~MAVLinkSettingsWidget();

public slots:
    /** @brief Update the log file name display */
     /** @brief 로그 파일 이름 표시 업데이트 */
    void updateLogfileName(const QString& fileName);
    /** @brief Start the file select dialog for the log file */
    /** @brief 로그 파일의 파일 선택 대화 상자 시작 */
    void chooseLogfileName();
    /** @brief Enable DroneOS forwarding */
    /** brief DroneOS 포워딩 활성화 */
    void enableDroneOS(bool enable);

    void setDroneOSKey(QString key);

    void setDroneOSHost(QString host);

protected:
    MAVLinkProtocol* protocol;
    void changeEvent(QEvent *e);
    void hideEvent(QHideEvent* event);

private:
    Ui::MAVLinkSettingsWidget *m_ui;
};

#endif // MAVLINKSETTINGSWIDGET_H
