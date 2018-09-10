#ifndef QGCMESSAGEVIEW_H
#define QGCMESSAGEVIEW_H

#include <QWidget>
#include <UASInterface.h>
#include <QVBoxLayout>
#include <QAction>
#include "QGCUnconnectedInfoWidget.h"

namespace Ui {
class QGCMessageView;
}

class QGCMessageView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QGCMessageView(QWidget *parent = 0);
    ~QGCMessageView();

public slots:
    /**
     * @brief Set currently active UAS
     * @param uas the current active UAS
     */
    /**
     * @brief 현재 활성 UAS 설정
     현재의 액티브 한 UAS의 @ 파라미터
     */
    void setActiveUAS(UASInterface* uas);
    /**
     * @brief Handle text message from current active UAS
     * @param uasid
     * @param componentid
     * @param severity
     * @param text
     */
    /**
     * @brief 현재 활성 UAS의 텍스트 메시지 처리
     * @param uasid
     * @param componentid
     * @param의 중요도
     * @param 텍스트
     */
    void handleTextMessage(int uasid, int componentid, int severity, QString text);

    /**
     * @brief Hand context menu event
     * @param event
     */
    /**
     * @brief 핸드 컨텍스트 메뉴 이벤트
     * @param 이벤트
     */
    virtual void contextMenuEvent(QContextMenuEvent* event);

protected:
    UASInterface* activeUAS;
    QVBoxLayout* initialLayout;
    QGCUnconnectedInfoWidget *connectWidget;
    QAction* clearAction;
    
private:
    Ui::QGCMessageView *ui;
};

#endif // QGCMESSAGEVIEW_H
