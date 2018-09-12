#ifndef QGCMAVLINKLOGPLAYER_H
#define QGCMAVLINKLOGPLAYER_H

#include <QWidget>
#include <QFile>
#include "MAVLinkProtocol.h"
#include "TLogReplayLink.h"
#include "MAVLinkDecoder.h"
#include "QGCMAVLinkInspector.h"
namespace Ui
{
class QGCMAVLinkLogPlayer;
}

/**
 * @brief Replays MAVLink log files
 *
 * This class allows to replay MAVLink logs at varying speeds.
 * captured flights can be replayed, shown to others and analyzed
 * in-depth later on.
 */
/* *
 * @brief MAVLink 로그 파일을 재생합니다.
 *
 *이 클래스는 다양한 속도로 MAVLink 로그를 재생할 수 있습니다.
 * 캡처 한 항공편을 재생하여 다른 사람에게 보여주고 분석 할 수 있습니다.
 * 나중에 깊이.
 */
class QGCMAVLinkLogPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit QGCMAVLinkLogPlayer(QWidget *parent = 0);
    void setMavlinkDecoder(MAVLinkDecoder *decoder);
    void setMavlinkInspector(QGCMAVLinkInspector *inspector);
    ~QGCMAVLinkLogPlayer();
    bool isPlayingLogFile()
    {
        return m_isPlaying;
    }

    /**
     * @brief Set the last log file name
     * @param filename
     */
    /* *
     * @brief 마지막 로그 파일 이름을 설정합니다.
     * @ 파라미터 파일명
     */
/*    void setLastLogFile(const QString& filename) {
        lastLogDirectory = filename;
    }*/

public slots:
    void loadLogButtonClicked();
    void playButtonClicked();
    void logLinkTerminated();
    void speedSliderValueChanged(int value);
    void speed75Clicked();
    void speed100Clicked();
    void speed150Clicked();
    void speed200Clicked();
    void speed500Clicked();
    void speed1000Clicked();
private slots:
    void logProgress(qint64 pos,qint64 total);
    void positionSliderReleased();
    void positionSliderPressed();
    void loadLogDialogAccepted();
protected:
    bool m_sliderDown;
    bool m_isPlaying;
    void changeEvent(QEvent *e);

    void storeSettings();

private:
    Ui::QGCMAVLinkLogPlayer *ui;
    TLogReplayLink *m_logLink;
    bool m_logLoaded;
    MAVLinkDecoder *m_mavlinkDecoder;
    QGCMAVLinkInspector *m_mavlinkInspector;
signals:
    void logFinished();
    void logLoaded();
};

#endif // QGCMAVLINKLOGPLAYER_H
