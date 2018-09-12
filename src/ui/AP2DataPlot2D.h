/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2015 APM_PLANNER PROJECT <http://www.diydrones.com>

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
 *   @brief AP2DataPlot widget class
 *
 *   @author Michael Carpenter <malcom2073@gmail.com>
 */


#ifndef AP2DATAPLOT2D_H
#define AP2DATAPLOT2D_H

#include "UASInterface.h"
#include "MAVLinkDecoder.h"
#include "kmlcreator.h"
#include "qcustomplot.h"

#include "AP2DataPlotThread.h"
#include "dataselectionscreen.h"
#include "AP2DataPlotAxisDialog.h"
#include "ui_AP2DataPlot2D.h"

#include <QWidget>
#include <QProgressDialog>
#include <QSortFilterProxyModel>
#include <QTextBrowser>
#include <QSqlDatabase>
#include <QStandardItemModel>

#include "Loghandling/LogdataStorage.h"

class LogDownloadDialog;

class AP2DataPlot2D : public QWidget
{
    Q_OBJECT
    
public:
    explicit AP2DataPlot2D(QWidget *parent = 0);
    ~AP2DataPlot2D();

public slots:
    void showLogDownloadDialog();
    void closeLogDownloadDialog();
    void clearGraph();

    void logToKmlClicked();

private slots:
    //New Active UAS set
    // 새 활성 UAS 집합
    void activeUASSet(UASInterface* uas);

    void connected();
    void disconnected();

    //Load a graph from a file
    // 파일로부터 그래프 불러 오기
    void loadButtonClicked();
    void loadDialogAccepted();

    //settings
    // 설정
    void saveSettings();
    void loadSettings();

    //Called to remove an item from the graph
    // 그래프에서 항목을 제거하기 위해 호출됩니다.
    void itemDisabled(QString name);
    //Called to add an item to the graph
    // 그래프에 항목을 추가하기 위해 호출됩니다.
    void itemEnabled(QString name);

    //ValueChanged functions for getting mavlink values
    // mavlink 값을 가져 오는 ValueChanged 함수
    void valueChanged(const int uasid, const QString& name, const QString& unit, const QVariant& value,const quint64 msecs);
    //Called by every valueChanged function to actually save the value/graph it.
    // 모든 valueChanged 함수에 의해 호출되어 실제로 값을 저장하거나 그래프로 그립니다.
    void updateValue(const int uasId, const QString& name, const QString& unit, const double value, const quint64 msec,bool integer = true);

    void navModeChanged(int uasid, int mode, const QString& text);

    void autoScrollClicked(bool checked);
    void axisDoubleClick(QCPAxis* axis,QCPAxis::SelectablePart part,QMouseEvent* evt);
    void graphControlsButtonClicked();
    void plotMouseMove(QMouseEvent *evt);
    void horizontalScrollMoved(int value);
    void verticalScrollMoved(int value);
    void xAxisChanged(QCPRange range);
    void replyTLogButtonClicked();

    void graphGroupingChanged(QList<AP2DataPlotAxisDialog::GraphRange> graphRangeList);
    void graphColorsChanged(QMap<QString,QColor> colormap);

    void modeCheckBoxClicked(bool checked);

    void childGraphDestroyed(QObject *obj);

private:

    void showEvent(QShowEvent *evt);
    void hideEvent(QHideEvent *evt);


    int getStatusTextPos();
    void plotTextArrow(double index, const QString& text, const QString& graph, const QColor& color, QCheckBox *checkBox = NULL);

    /**
     * @brief This method hides or shows the text arrows of type
     *        garphName by changing their visability. Used by
     *        checkbox handlers.
     * @param show - true - make visible / false - hide them
     * @param type - typename of text arrows to hide or show
     */
    /* *
     * @brief이 메소드는 텍스트 화살표를 숨기거나 표시합니다.
     * garphName의 가시성을 변경합니다. 중고
     * 확인란 핸들러.
     * @param show - true - visible / false - 숨김
     * @param type - 숨기거나 보여줄 텍스트 화살표의 typename
     */
    void hideShowTextArrows(bool show, const QString &graphName);

    /**
     * @brief removeTextArrows removes all text arrows of type graphName
     *
     * @param graphName - Name of the graph whose test arrows shall be removed
     */
    /* *
     * @brief removeTextArrows는 graphName 유형의 모든 텍스트 화살표를 제거합니다.
     *
     * @param graphName - 테스트 화살표가 삭제되는 그래프의 이름
     */
    void removeTextArrows(const QString &graphName);

private:
    Ui::AP2DataPlot2D ui;

    QTimer *m_updateTimer;
    class Graph
    {
    public:
        bool isManualRange;
        QString groupName;
        bool isInGroup;
        double axisIndex;
        QCPAxis *axis;
        QCPGraph *graph;
        QList<QCPAbstractItem*> itemList;
        QMap<double,QString> messageMap;

        Graph() : isManualRange(false), isInGroup(false), axisIndex(0), axis(NULL), graph(NULL){}
    };

    QMap<QString,Graph> m_graphClassMap;

    //Map of group name to a list of graph titles
    // 그룹 이름을 그래프 제목 목록에 매핑합니다.
    QMap<QString,QList<QString> > m_graphGrouping;
    //Map from group titles to the value axis range.
    // 그룹 제목에서 값 축 범위로 매핑합니다.
    QMap<QString,QCPRange> m_graphGroupRanges;
    //Graph name to list of values for "online" mode
    // "온라인"모드의 값 목록에 그래프 이름
    QMap<QString,QList<QPair<double,double> > > m_onlineValueMap;
    // Child windows which were opened by open log
    // 열린 로그로 열린 자식 창
    QList<QWidget*> m_childGraphList;

    QList<QPair<qint64,double> > m_onlineValueTimeoutList;

    //List of graph names, used in m_axisList, m_graphMap,m_graphToGroupMap and the like as the graph name
    // 그래프 이름으로 m_axisList, m_graphMap, m_graphToGroupMap 등에서 사용 된 그래프 이름 목록
    QList<QString> m_graphNameList;
    // number of active graphs
    // 활성 그래프의 수
    int m_graphCount;
    QCustomPlot *m_plot;
    QCPAxisRect *m_wideAxisRect;
    //Current "index", X axis on graph. Used to keep all the graphs lined up.
    // 현재 "index", 그래프상의 X 축. 모든 그래프를 일렬로 유지하는 데 사용됩니다.
    qint64 m_currentIndex;
    qint64 m_startIndex; //epoch msecs since graphing started// 그래프가 시작된 이후의 기점 msecs
    QAction *m_addGraphAction;
    UASInterface *m_uas;
    AP2DataPlotAxisDialog *m_axisGroupingDialog;
    bool m_tlogReplayEnabled;

    qint64 m_scrollStartIndex; //Actual graph start// 실제 그래프 시작
    qint64 m_scrollEndIndex; //Actual graph end// 실제 그래프 끝

    LogDownloadDialog *m_logDownloadDialog;

    int m_statusTextPos;

    int m_lastHorizontalScrollerVal;                        /// Used to avoid multiple calls with same value// 동일한 값을 가진 다중 호출을 피하기 위해 사용됩니다.

};

#endif // AP2DATAPLOT2D_H
