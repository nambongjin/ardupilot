#ifndef QGCUNCONNECTEDINFOWIDGET_H
#define QGCUNCONNECTEDINFOWIDGET_H

#include <QWidget>

namespace Ui
{
class QGCUnconnectedInfoWidget;
}

/**
 * @brief Widget providing initial instructions
 *
 * This widget provides initial instructions to new users how
 * to connect a simulation or a live link to a system to
 * QGroundControl. The widget should be automatically be
 * unloaded and destroyed once the first MAV/UAS is connected.
 *
 * @see UASListWidget
 */

/*
 *이 위젯은 새로운 사용자에게 초기 지침을 제공합니다.
 * 시뮬레이션 또는 라이브 링크를 시스템에 연결
* QGroundControl. 위젯은 자동으로 있어야합니다.
 첫 번째 MAV / UAS가 연결되면 언로드되고 파괴됩니다.
 *
*/

class QGCUnconnectedInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGCUnconnectedInfoWidget(QWidget *parent = 0);
    ~QGCUnconnectedInfoWidget();

    Ui::QGCUnconnectedInfoWidget *ui;

public slots:
    /** @brief Start simulation 	 시뮬레이션 시작*/
    void simulate();
    /** @brief Add a link 	 링크 추가*/
    void addLink();
};

#endif // QGCUNCONNECTEDINFOWIDGET_H
