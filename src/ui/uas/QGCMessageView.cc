#include "QGCMessageView.h"
#include "ui_QGCMessageView.h"

#include "UASManager.h"
#include "QGCUnconnectedInfoWidget.h"
#include <QMenu>

QGCMessageView::QGCMessageView(QWidget *parent) :
    QWidget(parent),
    activeUAS(NULL),
    clearAction(new QAction(tr("Clear Text"), this)),
    ui(new Ui::QGCMessageView)
{
    setObjectName("QUICKVIEW_MESSAGE_CONSOLE");

    ui->setupUi(this);
    setStyleSheet("QScrollArea { border: 0px; } QPlainTextEdit { border: 0px }");

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));
}

QGCMessageView::~QGCMessageView()
{
    delete ui;
}

void QGCMessageView::setActiveUAS(UASInterface* uas)
{
    if (!uas)
        return;

    if (activeUAS) {
        disconnect(uas, SIGNAL(textMessageReceived(int,int,int,QString)), this, SLOT(handleTextMessage(int,int,int,QString)));
        ui->plainTextEdit->clear();
    } else {

        // First time UI setup, clear layout
        // 처음으로 UI 설정, 레이아웃 지우기
        ui->plainTextEdit->show();

        connect(clearAction, SIGNAL(triggered()), ui->plainTextEdit, SLOT(clear()));
    }

    connect(uas, SIGNAL(textMessageReceived(int,int,int,QString)), this, SLOT(handleTextMessage(int,int,int,QString)));
    activeUAS = uas;
}

void QGCMessageView::handleTextMessage(int uasid, int componentid, int severity, QString text)
{
    // XXX color messages according to severity
    // 심각도에 따른 XXX 컬러 메시지

    Q_UNUSED(severity)

    ui->plainTextEdit->appendHtml(QString("<font color=\"%1\">[%2:%3] %4</font>\n").arg(UASManager::instance()->getUASForId(uasid)->getColor().name()).arg(UASManager::instance()->getUASForId(uasid)->getUASName()).arg(componentid).arg(text));
    // Ensure text area scrolls correctly
    // 텍스트 영역이 올바르게 스크롤되도록합니다.
    ui->plainTextEdit->ensureCursorVisible();
}

void QGCMessageView::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
    menu.addAction(clearAction);
    menu.exec(event->globalPos());
}
