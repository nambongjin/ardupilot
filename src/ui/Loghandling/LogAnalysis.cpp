/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2017 APM_PLANNER PROJECT <http://www.ardupilot.com>

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
 * @file LogAnalysis.cpp
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @author Michael Carpenter <malcom2073@gmail.com>
 * @date 17 Mrz 2017
 * @brief File providing implementation for the log analysing classes
 */
/* *
 * @file LogAnalysis.cpp
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @author Michael Carpenter <malcom2073@gmail.com>
 * @date 17 Mrz 2017
 * @brief 로그 분석 클래스 구현을 제공하는 파일
 */

#include "LogAnalysis.h"
#include "logging.h"

#include "ArduPilotMegaMAV.h"
#include "Loghandling/LogExporter.h"
#include "Loghandling/PresetManager.h"



LogAnalysisCursor::LogAnalysisCursor(QCustomPlot *parentPlot, double xPosition, CursorType type) :
    QCPItemStraightLine(parentPlot),
    m_currentPos(xPosition),
    m_otherCursorPos(0.0),
    m_type(type),
    mp_otherCursor(0)
{
    QLOG_TRACE() << "LogAnalysisCursor::LogAnalysisCursor - CTOR - type " << type;
    point1->setCoords(m_currentPos, 1);
    point2->setCoords(m_currentPos, 0);
    setSelectable(true);
    setClipToAxisRect(false);
}

LogAnalysisCursor::~LogAnalysisCursor()
{
    QLOG_TRACE() << "LogAnalysisCursor::~LogAnalysisCursor - DTOR - type " << m_type;
}

void LogAnalysisCursor::setOtherCursor(LogAnalysisCursor *pCursor)
{
    mp_otherCursor = pCursor;
}

double LogAnalysisCursor::getCurrentXPos() const
{
    return m_currentPos;
}

void LogAnalysisCursor::setCurrentXPos(double xPosition)
{
    if(m_type == simple)
    {
        m_currentPos = xPosition;
        point1->setCoords(m_currentPos, 1);
        point2->setCoords(m_currentPos, 0);
        mParentPlot->replot();
    }
}

void LogAnalysisCursor::mousePressEvent(QMouseEvent *event, const QVariant &details)
{
    Q_UNUSED(details);
    QLOG_TRACE() << "LogAnalysisCursor::mousePressEvent";
    if(mSelected)
    {
        event->accept();
        if(mp_otherCursor)
        {
            m_otherCursorPos = dynamic_cast<LogAnalysisCursor*>(mp_otherCursor)->getCurrentXPos();
        }
    }
    else
    {
        event->ignore();
    }
}

void LogAnalysisCursor::mouseMoveEvent(QMouseEvent *event, const QPointF &startPos)
{
    QLOG_TRACE() << "LogAnalysisCursor::mouseMoveEvent " << event << " " << startPos;
    // allow dragging only if selected
    // 선택한 경우에만 끌기 허용
    if(mSelected)
    {
        double movePos = point1->keyAxis()->pixelToCoord(event->x());
        if(m_type == simple)
        {
            m_currentPos = movePos;
        }
        else if(m_type == left && movePos < m_otherCursorPos)   // avoid left cursor overtaking the right one// 왼쪽 커서가 오른쪽 커서를 추월하지 않도록합니다.
        {
            m_currentPos = movePos;
            emit rangeCursorMoving();
        }
        else if(m_type == right && movePos > m_otherCursorPos)  // avoid right cursor overtaking the left one// 오른쪽 커서가 왼쪽 커서를 추월하지 않도록합니다.
        {
            m_currentPos = movePos;
            emit rangeCursorMoving();
        }

        point1->setCoords(m_currentPos, 1);
        point2->setCoords(m_currentPos, 0);
        mParentPlot->replot(QCustomPlot::rpQueuedReplot);
    }
}

void LogAnalysisCursor::mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos)
{
    QLOG_TRACE() << "LogAnalysisCursor::mouseReleaseEvent " << event << " " << startPos;
    m_currentPos = point1->keyAxis()->pixelToCoord(event->x());
    if(m_type == simple)
    {
        emit newCursorPos(m_currentPos); // Simple cursor emits signal with new position// 단순한 커서는 새로운 위치로 신호를 내 보낸다.
    }
    else
    {
        emit cursorRangeChange();   // left and right emit signal that position has changed// 위치가 변경된 신호를 왼쪽 및 오른쪽으로 내 보냅니다.
    }
}

void LogAnalysisCursor::mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details)
{
    Q_UNUSED(event);
    Q_UNUSED(details);
    QLOG_DEBUG() << "LogAnalysisCursor::mouseDoubleClickEvent";
}

void LogAnalysisCursor::wheelEvent(QWheelEvent *event)
{
    QLOG_TRACE() << "LogAnalysisCursor::wheelEvent";
    if(mSelected)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

//************************************************************************************

LogAnalysisAxis::LogAnalysisAxis(QCPAxisRect *axisRect, AxisType type) : QCPAxis(axisRect, type)
{
    QLOG_TRACE() << "LogAnalysisAxis::LogAnalysisAxis - CTOR";
}

LogAnalysisAxis::~LogAnalysisAxis()
{
    QLOG_TRACE() << "LogAnalysisAxis::~LogAnalysisAxis - DTOR";
}

void LogAnalysisAxis::wheelEvent(QWheelEvent *event)
{
    QLOG_TRACE() << "LogAnalysisCursor::wheelEvent";
    if(mSelectedParts == QCPAxis::spAxis)
    {
        event->accept();
        double axisPos = pixelToCoord(event->y());

        if(event->delta() < 0)
        {
            scaleRange(1.1, axisPos);
        }
        else if(event->delta() > 0)
        {
            scaleRange(0.9, axisPos);
        }
        mParentPlot->replot(QCustomPlot::rpQueuedReplot);
    }
    else
    {
        event->ignore();
    }
}

//************************************************************************************

const QString LogAnalysis::s_CursorLayerName("cursors");

LogAnalysis::LogAnalysis(QWidget *parent) :
    QWidget(parent),
    m_loadedLogMavType(MAV_TYPE_ENUM_END),
    m_useTimeOnXAxis(false),
    m_scrollStartIndex(0),
    m_scrollEndIndex(0),
    m_statusTextPos(0),
    m_lastHorizontalScrollVal(0),
    m_cursorXAxisRange(0.0),
    mp_cursorSimple(0),
    mp_cursorLeft(0),
    mp_cursorRight(0)
{
    QLOG_DEBUG() << "LogAnalysis::LogAnalysis - CTOR";
    ui.setupUi(this);

    // add menu bar
    m_menuBarPtr.reset(new QMenuBar(this));
    QMenu *exportMenu = new QMenu("Export...", this);
    m_menuBarPtr->addMenu(exportMenu);
    // add ascii export to menu
    QAction *p_Action = exportMenu->addAction("Export to Ascii log file");
    connect(p_Action, SIGNAL(triggered()), this, SLOT(exportAsciiLogClicked()));
    // add KMZ export to menu
    p_Action = exportMenu->addAction("Export to KML/KMZ file");
    connect(p_Action, SIGNAL(triggered()), this, SLOT(exportKmlClicked()));

    // create preset menu and give it to preset manager
    m_presetMgrPtr.reset(new PresetManager(this, m_menuBarPtr.data()));
    connect(m_presetMgrPtr.data(), SIGNAL(newPresetSelected(PresetManager::presetElementVec)), this, SLOT(analysisPresetSelected(PresetManager::presetElementVec)));

    // add menubar to window
    layout()->setMenuBar(m_menuBarPtr.data());

    // create QCustomPlot
    m_plotPtr.reset(new QCustomPlot(ui.widget));

    // Setup UI
    ui.verticalLayout_5->insertWidget(0, m_plotPtr.data());
    ui.horizontalLayout_3->setStretch(0,5);
    ui.horizontalLayout_3->setStretch(1,1);
    ui.horizontalSplitter->setStretchFactor(0,20);
    ui.horizontalSplitter->setStretchFactor(1,1);
    ui.tableWidget->verticalHeader()->setDefaultSectionSize(ui.tableWidget->fontMetrics().height() + s_ROW_HEIGHT_PADDING);
    ui.tableFilterGroupBox->setVisible(false);

    // on window open table view is hidden
    hideTableView(true);

    // setup QCustomPlot
    m_plotPtr->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems | QCP::iSelectAxes);  // set allowed intercations// 허용 intercations 설정
    m_plotPtr->plotLayout()->clear();                               // clear default axis rectangle so we can start from scratch// 처음부터 시작할 수 있도록 기본 축 사각형을 지운다.

    QCPAxisRect *axisRect = new QCPAxisRect(m_plotPtr.data());      // Create new axis rectangle. QCustomPlot takes ownership// 새 축 사각형을 만듭니다. QCustomPlot은 소유권을가집니다.
    axisRect->setupFullAxesBox(true);                               // Setup axis rect// 축 설정 rect
    axisRect->axis(QCPAxis::atRight, 0)->setTickLabels(false);      // remove tick labels on right axis// 오른쪽 축에서 틱 레이블 제거
    axisRect->axis(QCPAxis::atRight, 0)->setTicks(false);           // remove ticks on right axis// 오른쪽 축에서 틱을 제거합니다.
    axisRect->removeAxis(axisRect->axis(QCPAxis::atLeft, 0));       // remove left axis// 왼쪽 축 제거
    // setup x axis ticker
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    fixedTicker->setTickStep(1.0);
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
    axisRect->axis(QCPAxis::atBottom, 0)->setTicker(fixedTicker);
    axisRect->axis(QCPAxis::atBottom, 0)->setRange(0, 100);
    axisRect->axis(QCPAxis::atBottom, 0)->setSelectableParts(QCPAxis::spNone);
    // setup margins// 여백 설정
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_plotPtr.data()); //QCustomPlot takes ownership// QCustomPlot은 소유권을가집니다.
    axisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);

    m_plotPtr->plotLayout()->addElement(0, 0, axisRect);    // Add the configured axis rect to layout// 레이아웃에 구성된 축 rect 추가
    m_plotPtr->setPlottingHint(QCP::phFastPolylines, true);  // TODO perhaps use OpenGL?!// TODO는 아마도 OpenGL을 사용합니까?!
    m_plotPtr->show();

    // Add layers and make them invisible. All arrow plots and the cursor have an own layer above main
    // 레이어를 추가하고 보이지 않게합니다. 모든 화살표 그림과 커서는 메인 위에 자체 레이어가 있습니다.
    QCPLayer *pLayerBelow = m_plotPtr->layer("main");
    if(pLayerBelow)
    {
        m_plotPtr->addLayer(ModeMessage::TypeName, pLayerBelow);
        pLayerBelow = m_plotPtr->layer(ModeMessage::TypeName);
        pLayerBelow->setVisible(false);

        m_plotPtr->addLayer(ErrorMessage::TypeName, pLayerBelow);
        pLayerBelow = m_plotPtr->layer(ErrorMessage::TypeName);
        pLayerBelow->setVisible(false);

        m_plotPtr->addLayer(EventMessage::TypeName, pLayerBelow);
        pLayerBelow = m_plotPtr->layer(EventMessage::TypeName);
        pLayerBelow->setVisible(false);

        m_plotPtr->addLayer(MsgMessage::TypeName, pLayerBelow);
        pLayerBelow = m_plotPtr->layer(MsgMessage::TypeName);
        pLayerBelow->setVisible(false);

        m_plotPtr->addLayer(s_CursorLayerName, pLayerBelow);
        pLayerBelow = m_plotPtr->layer(s_CursorLayerName);
        pLayerBelow->setVisible(false);
    }

    // Create axis grouping dialog
    // 축 그룹 만들기 대화 상자를 만듭니다.
    m_axisGroupingDialog.reset(new AP2DataPlotAxisDialog());
    m_axisGroupingDialog->hide();
    connect(m_axisGroupingDialog.data(), SIGNAL(graphGroupingChanged(QList<AP2DataPlotAxisDialog::GraphRange>)), this, SLOT(graphGroupingChanged(QList<AP2DataPlotAxisDialog::GraphRange>)));
    connect(m_axisGroupingDialog.data(), SIGNAL(graphColorsChanged(QMap<QString,QColor>)), this, SLOT(graphColorsChanged(QMap<QString,QColor>)));

    // setup policy and connect slot for context menu popup
    // 설정 정책 및 컨텍스트 메뉴 팝업을위한 연결 슬롯
    m_plotPtr->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_plotPtr.data(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    m_plotPtr->replot();

    // connect to default signals
    // 기본 신호에 연결
    connect(ui.showValuesCheckBox,      SIGNAL(clicked(bool)), this, SLOT(showValueUnderMouseClicked(bool)));
    connect(ui.modeDisplayCheckBox,     SIGNAL(clicked(bool)), this, SLOT(modeCheckboxClicked(bool)));
    connect(ui.evDisplayCheckBox,       SIGNAL(clicked(bool)), this, SLOT(eventCheckboxClicked(bool)));
    connect(ui.errDisplayCheckBox,      SIGNAL(clicked(bool)), this, SLOT(errorCheckboxClicked(bool)));
    connect(ui.msgDisplayCheckBox,      SIGNAL(clicked(bool)), this, SLOT(msgCheckboxClicked(bool)));
    connect(ui.indexTypeCheckBox,       SIGNAL(clicked(bool)), this, SLOT(indexTypeCheckBoxClicked(bool)));
    connect(ui.tableCursorCheckBox,     SIGNAL(clicked(bool)), this, SLOT(enableTableCursor(bool)));
    connect(ui.rangeCursorCheckBox,     SIGNAL(clicked(bool)), this, SLOT(enableRangeCursor(bool)));

    connect(ui.filterSelectTreeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(filterItemChanged(QTreeWidgetItem*,int)));
    connect(ui.filterAcceptPushButton,SIGNAL(clicked()),this,SLOT(filterAcceptClicked()));
    connect(ui.filterCancelPushButton,SIGNAL(clicked()),this,SLOT(filterCancelClicked()));
    connect(ui.filterShowPushButton,SIGNAL(clicked()),this,SLOT(showFilterButtonClicked()));
    connect(ui.filterSelectAllPushButton,SIGNAL(clicked()),this,SLOT(filterSelectAllClicked()));
    connect(ui.filterInvertSelectPushButton,SIGNAL(clicked()),this,SLOT(filterSelectInvertClicked()));

    connect(ui.graphControlsPushButton, SIGNAL(clicked()), this, SLOT(graphControlsButtonClicked()));
    connect(ui.resetScalingPushButton, SIGNAL(clicked()), this, SLOT(resetValueScaling()));

    connect(ui.storeGraphSettingsButton, SIGNAL(clicked()), this, SLOT(storeGraphSettingsPressed()));
    connect(ui.applyGraphSettingsButton, SIGNAL(clicked()), this, SLOT(applyGraphSettingsPressed()));
    connect(ui.storeToPresetPushBtn, SIGNAL(clicked()), this, SLOT(addCurrentViewToPreset()));

    loadSettings();

    setStyleSheet("QToolTip {background: #ffffdf}");
}

LogAnalysis::~LogAnalysis()
{
    QLOG_DEBUG() << "LogAnalysis::~LogAnalysis - DTOR";
    saveSettings();
}

void LogAnalysis::loadLog(QString filename)
{
    QLOG_DEBUG() << "LogAnalysis::loadLog - Filename:" << filename;
    m_filename = filename;
    // setup window name
    // 설정 창 이름
    QString shortfilename = filename.mid(filename.lastIndexOf("/")+1);
    QString presetName = m_presetMgrPtr->getFileInfo().fileName();
    setWindowTitle(tr("Graph: %1 [%2]").arg(shortfilename).arg(presetName));

    // create datastorage, loader thread and connect the signals
    // 데이터 저장소, 로더 스레드를 생성하고 신호를 연결한다.
    m_dataStoragePtr = LogdataStorage::Ptr(new LogdataStorage());
    m_loaderThreadPtr.reset(new AP2DataPlotThread(m_dataStoragePtr));
    connect(m_loaderThreadPtr.data(), SIGNAL(startLoad()), this, SLOT(logLoadingStarted()));
    connect(m_loaderThreadPtr.data(), SIGNAL(loadProgress(qint64, qint64)), this, SLOT(logLoadingProgress(qint64, qint64)));
    connect(m_loaderThreadPtr.data(), SIGNAL(error(QString)), this, SLOT(logLoadingError(QString)));
    connect(m_loaderThreadPtr.data(), SIGNAL(done(AP2DataPlotStatus)), this, SLOT(logLoadingDone(AP2DataPlotStatus)));
    connect(m_loaderThreadPtr.data(), SIGNAL(finished()), this, SLOT(logLoadingThreadTerminated()));

    // let the loader start the log loading
    // 로더가 로그로드를 시작하게합니다.
    m_loaderThreadPtr->loadFile(filename);
}

void LogAnalysis::setTablePos(double xPosition)
{
    if(mp_cursorSimple)  // only if simple cursor is active// 단순 커서가 활성화 된 경우에만
    {
        double timeStamp = 0.0;

        if (m_useTimeOnXAxis)
        {
            timeStamp = xPosition;
            xPosition = m_dataStoragePtr->getNearestIndexForTimestamp(timeStamp);
        }

        qint64 position = static_cast<qint64>(floor(xPosition));
        qint64 min = 0;
        qint64 max = static_cast<qint64>(m_dataStoragePtr->rowCount());

        if ( position >= max )
        {
            ui.tableWidget->scrollToBottom();
            double plotPos = m_useTimeOnXAxis ? m_dataStoragePtr->getMaxTimeStamp() : max;
            mp_cursorSimple->setCurrentXPos(plotPos);

        }
        else if ( position <= min )
        {
            ui.tableWidget->scrollToTop();
            double plotPos = m_useTimeOnXAxis ? m_dataStoragePtr->getMinTimeStamp() : min;
            mp_cursorSimple->setCurrentXPos(plotPos);
        }
        else
        {
            //search for previous event (remember the table may be filtered)
            // 이전 이벤트를 검색합니다 (테이블이 필터링 될 수 있음을 기억하십시오)
            QModelIndex sourceIndex = m_dataStoragePtr->index(static_cast<int>(position - min), 0);
            QModelIndex index = mp_tableFilterProxyModel->mapFromSource(sourceIndex);
            while ( sourceIndex.row() >= static_cast<int>(min) && !index.isValid() )
            {
                sourceIndex = m_dataStoragePtr->index(sourceIndex.row() - 1, 0);
                index = mp_tableFilterProxyModel->mapFromSource(sourceIndex);
            }

            if ( !index.isValid() )
            {
                //couldn't find filtered index by looking back, try forward...
                // 뒤를 돌아보고 필터링 된 색인을 찾을 수 없습니다.
                sourceIndex = m_dataStoragePtr->index(static_cast<int>(position - min), 0);
                index = mp_tableFilterProxyModel->mapFromSource(sourceIndex);
                while ( sourceIndex.row() <= static_cast<int>(max) && !index.isValid() )
                {
                    sourceIndex = m_dataStoragePtr->index(sourceIndex.row() + 1, 0);
                    index = mp_tableFilterProxyModel->mapFromSource(sourceIndex);
                }
            }
            ui.tableWidget->setCurrentIndex(index);
            ui.tableWidget->scrollTo(index);
        }
    }
}

void LogAnalysis::rangeCursorsMoving()
{
    if(mp_cursorLeft && mp_cursorRight)
    {
        double leftPos  = mp_cursorLeft->getCurrentXPos();
        double rightPos = mp_cursorRight->getCurrentXPos();

        m_cursorXAxisRange = rightPos - leftPos;
    }
}


void LogAnalysis::cursorRangeChange()
{
    if(mp_cursorLeft && mp_cursorRight)
    {
        // get cursor positions and range
        // 커서 위치와 범위 가져 오기
        m_rangeValuesStorage.clear();
        double leftPos  = mp_cursorLeft->getCurrentXPos();
        double rightPos = mp_cursorRight->getCurrentXPos();

        m_cursorXAxisRange = rightPos - leftPos;

        // Calculate range values for every active graph
        // 모든 활성 그래프에 대한 범위 값 계산
        activeGraphType::Iterator iter;
        for(iter = m_activeGraphs.begin(); iter != m_activeGraphs.end(); ++iter)
        {
            QSharedPointer<QCPGraphDataContainer> dataPtr = iter->p_graph->data();
            RangeValues rangeVals;

            int rangeStartIndex = iter->p_graph->findBegin(leftPos);
            int rangeEndIndex   = iter->p_graph->findBegin(rightPos);
            rangeVals.m_measurements = rangeEndIndex - rangeStartIndex;

            for(int i = rangeStartIndex; i < rangeEndIndex; ++i)
            {
                double value = dataPtr->at(i)->mainValue();
                rangeVals.m_average += value;
                rangeVals.m_min = rangeVals.m_min > value ? value : rangeVals.m_min;
                rangeVals.m_max = rangeVals.m_max < value ? value : rangeVals.m_max;
            }
            rangeVals.m_average /= rangeVals.m_measurements;
            m_rangeValuesStorage.insert(iter.key(), rangeVals);
        }
    }
}

void LogAnalysis::setupXAxisAndScroller()
{
    // Setup X-Axis for time or index formatting
    // 시간 또는 인덱스 포맷을위한 X 축 설정
    QCPAxis *xAxis = m_plotPtr->axisRect()->axis(QCPAxis::atBottom);
    xAxis->setNumberFormat("f");

    if (m_useTimeOnXAxis)
    {
        m_scrollStartIndex = static_cast<qint64>(m_dataStoragePtr->getMinTimeStamp());
        m_scrollEndIndex = static_cast<qint64>(m_dataStoragePtr->getMaxTimeStamp());
        xAxis->setNumberPrecision(2);
        xAxis->setLabel("Time s");
    }
    else
    {
        m_scrollStartIndex = 0;
        m_scrollEndIndex = m_dataStoragePtr->rowCount();
        xAxis->setNumberPrecision(0);
        xAxis->setLabel("Index");
    }
    ui.horizontalScrollBar->setMinimum(static_cast<int>(m_scrollStartIndex));
    ui.horizontalScrollBar->setMaximum(static_cast<int>(m_scrollEndIndex));
}

void LogAnalysis::insertTextArrows()
{
    // Iterate all elements and call their formatter to create output string
    // 모든 요소를 ​​반복하고 그 포맷터를 호출하여 출력 문자열을 만듭니다.
    foreach (MessageBase::Ptr p_msg, m_indexToMessageMap)
    {
        double index = m_useTimeOnXAxis ? p_msg->getTimeStamp() : p_msg->getIndex();
        QString string;
        switch (m_loadedLogMavType)
        {
            case MAV_TYPE_QUADROTOR:
            case MAV_TYPE_HEXAROTOR:
            case MAV_TYPE_OCTOROTOR:
            case MAV_TYPE_HELICOPTER:
            case MAV_TYPE_TRICOPTER:
                string = Copter::MessageFormatter::format(p_msg);
                break;

            case MAV_TYPE_FIXED_WING:
                string = Plane::MessageFormatter::format(p_msg);
                break;

            case MAV_TYPE_GROUND_ROVER:
                string = Rover::MessageFormatter::format(p_msg);
                break;

            default:
                string = p_msg->toString();
                break;
        }
        QLOG_DEBUG() << p_msg->typeName() << " change at index" << index << "to" << string;

        // plot the text arrow
        // 텍스트 화살표를 그립니다.
        plotTextArrow(index, string, p_msg->typeName(), p_msg->typeColor());
    }
}

void LogAnalysis::plotTextArrow(double index, const QString &text, const QString &layerName, const QColor &color)
{
    QLOG_DEBUG() << "plotTextArrow:" << index << " to " << layerName << " layer.";
    m_statusTextPos++;
    m_statusTextPos = m_statusTextPos > s_TextArrowPositions ? 1 : m_statusTextPos;

    if(!m_plotPtr->setCurrentLayer(layerName))  // text arrows all have their own layer// 텍스트 화살표에는 모두 고유 한 레이어가 있습니다.
    {
        QLOG_WARN() << "LogAnalysis::plotTextArrow - no layer with name " << layerName;
    }

    QCPAxis *xAxis = m_plotPtr->axisRect()->axis(QCPAxis::atBottom);
    QCPItemText *itemtext = new QCPItemText(m_plotPtr.data()); // QCustomPlot takes ownership// QCustomPlot은 소유권을가집니다.
    itemtext->setText(text);
    itemtext->setColor(color);
    itemtext->setPositionAlignment(Qt::AlignLeft | Qt::AlignBottom);
    itemtext->position->setAxes(xAxis, m_arrowGraph.p_yAxis);
    itemtext->setSelectable(false);

    QCPItemLine *itemline = new QCPItemLine(m_plotPtr.data()); // QCustomPlot takes ownership// QCustomPlot은 소유권을가집니다.
    itemline->setPen(QPen(color));
    itemline->start->setAxes(xAxis, m_arrowGraph.p_yAxis);
    itemline->start->setCoords(index, m_statusTextPos);
    itemline->end->setAxes(xAxis, m_arrowGraph.p_yAxis);
    itemline->end->setCoords(index, 0.0);
    itemline->setTail(QCPLineEnding::esDisc);
    itemline->setHead(QCPLineEnding::esSpikeArrow);
    itemtext->position->setCoords(itemline->start->coords());
    itemline->setSelectable(false);
}

void LogAnalysis::disableTableFilter()
{
    // The order of the statements is important to be fast on huge logs (15MB)
    // It does not really disable the filter but sets the rules to get a fast
    // result without any filtering
    // 명령문 순서는 거대한 로그 (15MB)에서 빠르다는 것이 중요합니다.
    // 실제로 필터를 비활성화하지 않지만 규칙을 빠르게 설정합니다.
    // 필터링없이 결과
    mp_tableFilterProxyModel->setFilterKeyColumn(0);
    mp_tableFilterProxyModel->setFilterRole(Qt::DisplayRole);
    mp_tableFilterProxyModel->setFilterFixedString("");
}

void LogAnalysis::loadSettings()
{
    QSettings settings;
    settings.beginGroup("LOGANALYSIS_SETTINGS");
    ui.modeDisplayCheckBox->setChecked(settings.value("SHOW_MODE", Qt::Checked).toBool());
    ui.errDisplayCheckBox->setChecked(settings.value("SHOW_ERR", Qt::Checked).toBool());
    ui.evDisplayCheckBox->setChecked(settings.value("SHOW_EV", Qt::Checked).toBool());
    ui.msgDisplayCheckBox->setChecked(settings.value("SHOW_MSG", Qt::Checked).toBool());
    ui.showValuesCheckBox->setChecked(settings.value("SHOW_VALUES", Qt::Unchecked).toBool());

    m_useTimeOnXAxis = settings.value("USE_TIMEINDEX", Qt::Unchecked).toBool();
    ui.indexTypeCheckBox->setChecked(m_useTimeOnXAxis);

    m_presetMgrPtr->setFileName(settings.value("PRESET_FILE").toString());
    settings.endGroup();
}

void LogAnalysis::saveSettings()
{
    QSettings settings;
    settings.beginGroup("LOGANALYSIS_SETTINGS");
    settings.setValue("SHOW_MODE", ui.modeDisplayCheckBox->isChecked());
    settings.setValue("SHOW_ERR", ui.errDisplayCheckBox->isChecked());
    settings.setValue("SHOW_EV", ui.evDisplayCheckBox->isChecked());
    settings.setValue("SHOW_MSG", ui.msgDisplayCheckBox->isChecked());
    settings.setValue("SHOW_VALUES", ui.showValuesCheckBox->isChecked());
    settings.setValue("USE_TIMEINDEX", ui.indexTypeCheckBox->isChecked());

    QFileInfo fileInfo = m_presetMgrPtr->getFileInfo();
    QString filePath;
    if(!fileInfo.fileName().isEmpty())  // if fileName is empty absoluteFilePath() delivers unpredicted values // fileName이 비어 있으면 absoluteFilePath ()는 예측되지 않은 값을 전달합니다.
    {
        filePath = fileInfo.absoluteFilePath();
    }
    settings.setValue("PRESET_FILE", filePath);
    settings.endGroup();
}

QList<AP2DataPlotAxisDialog::GraphRange> LogAnalysis::presetToRangeConverter(const PresetManager::presetElementVec &preset)
{
    QList<AP2DataPlotAxisDialog::GraphRange> graphRanges;

    for(int i = 0; i < preset.size(); ++i)
    {
        if(m_activeGraphs.contains(preset.at(i).m_graph))    // the element is enabled?// 요소가 사용 가능합니까?
        {
            GraphElements &element = m_activeGraphs[preset.at(i).m_graph];
            element.p_graph->setPen(QPen(preset.at(i).m_color, 1));
            element.p_yAxis->setLabelColor(preset.at(i).m_color);
            element.p_yAxis->setTickLabelColor(preset.at(i).m_color);

            AP2DataPlotAxisDialog::GraphRange range;
            range.graph = preset.at(i).m_graph;
            if(preset.at(i).m_manualRange)
            {
                range.manual = true;
                range.max = preset.at(i).m_range.upper;
                range.min = preset.at(i).m_range.lower;
            }
            else if(preset.at(i).m_group.size() > 0)
            {
                range.isgrouped = true;
                range.group = preset.at(i).m_group;
                range.max = element.p_yAxis->range().upper; // As the graph is already autoscaled (done when enabling) we just use the autoscaled min / max.// 그래프가 이미 자동 스케일되어 있으므로 (활성화 할 때 완료) autoscaled min / max를 사용합니다.
                range.min = element.p_yAxis->range().lower;
            }

            graphRanges.push_back(range);
        }
        else
        {
            QLOG_WARN() << "The graph " << preset.at(i).m_graph << " was not found! Could not apply settings.";
        }
    }
    return graphRanges;
}

void LogAnalysis::hideTableView(bool hide)
{
    if (hide)
    {
        ui.splitter->setSizes(QList<int>() << 1 << 0);
        ui.filterShowPushButton->setDisabled(true);
    }
    else
    {
        ui.splitter->setSizes(QList<int>() << 1 << 1);
        ui.filterShowPushButton->setDisabled(false);
    }
}

void LogAnalysis::showValueUnderMouseClicked(bool checked)
{
    if(checked)
    {
        connect(m_plotPtr.data(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    }
    else
    {
        disconnect(m_plotPtr.data(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    }
}


void LogAnalysis::logLoadingStarted()
{
    m_loadProgressDialog.reset(new QProgressDialog("Loading File", "Cancel", 0, 100, 0));
    m_loadProgressDialog->setWindowModality(Qt::WindowModal);
    connect(m_loadProgressDialog.data(), SIGNAL(canceled()), this, SLOT(logLoadingProgressDialogCanceled()));
    m_loadProgressDialog->show();
}

void LogAnalysis::logLoadingProgress(qint64 pos, qint64 size)
{
    if (m_loadProgressDialog)
    {
        double tempProgress = (static_cast<double>(pos) / static_cast<double>(size)) * 100.0;
        m_loadProgressDialog->setValue(static_cast<int>(tempProgress));
    }
}

void LogAnalysis::logLoadingError(QString errorstr)
{
    QLOG_ERROR() << "LogAnalysis::logLoadingError - Log loading stopped with error:" << errorstr;
    QMessageBox::warning(this ,"Error", errorstr);
    this->close();
}

void LogAnalysis::logLoadingDone(AP2DataPlotStatus status)
{
    QLOG_DEBUG() << "LogAnalysis::logLoadingDone - Log loading is done.";
    m_loadedLogMavType = status.getMavType();

    // close progress window. When setting value of the progress window to 100 it will
    // automatically close
    // 진행 창을 닫습니다. 진행 창 값을 100으로 설정하면
    // 자동으로 닫기
    m_loadProgressDialog->setValue(100);

    // status handling
    // 상태 처리
    if (status.getParsingState() != AP2DataPlotStatus::OK)
    {
        QString infoString;
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Log parsing ended with errors.");
        msgBox.addButton(QMessageBox::Ok);

        if (status.getParsingState() == AP2DataPlotStatus::FmtError)
        {
            infoString = "There were errors only in format discription. Usually this is no problem.\n\r";
        }
        else if (status.getParsingState() == AP2DataPlotStatus::TruncationError)
        {
            infoString = "The data was truncated!\n\r";
        }
        else if (status.getParsingState() == AP2DataPlotStatus::TimeError)
        {
            infoString = "The time data was currupted. Maybe plotting by time may not work.\n\r";
        }
        else
        {
            infoString = "There were data errors / unreadable data in the log! The data is potentially corrupt and incorrect.\r";
        }

        QLOG_WARN() << infoString << status.getErrorOverview();
        msgBox.setInformativeText(infoString + "Detected:\r" + status.getErrorOverview());
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setDetailedText(status.getDetailedErrorText());
        msgBox.exec();
    }

    // First setup X-axis and scroller
    // 첫 번째 설정 X 축 및 스크롤러
    setupXAxisAndScroller();

    // Insert data into tree view suppressing all measurements containing strings as values
    // 트리 뷰에 데이터를 삽입하여 문자열을 값으로 포함하는 모든 측정을 억제합니다.
    fmtMapType fmtMap = m_dataStoragePtr->getFmtValues(true);
    for (fmtMapType::const_iterator iter = fmtMap.constBegin(); iter != fmtMap.constEnd(); ++iter)
    {
        QString name = iter.key();
        for (int i = 0; i < iter.value().size(); ++i)
        {
            ui.dataSelectionScreen->addItem(name + "." + iter.value().at(i));
        }
    }
    // and connect the signals for enabling and disabling
    // 활성화 및 비활성화를 위해 신호를 연결합니다.
    connect(ui.dataSelectionScreen, SIGNAL(itemEnabled(QString)), this, SLOT(itemEnabled(QString)));
    connect(ui.dataSelectionScreen, SIGNAL(itemDisabled(QString)), this, SLOT(itemDisabled(QString)));

    // Insert data into filter window including all measurements with string data
    // 문자열 데이터가있는 모든 측정을 포함하여 필터 창에 데이터 삽입
    fmtMap.clear();
    fmtMap = m_dataStoragePtr->getFmtValues(false);
    for (fmtMapType::const_iterator iter = fmtMap.constBegin(); iter != fmtMap.constEnd(); ++iter)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList() << iter.key());
        child->setFlags(child->flags() | Qt::ItemIsUserCheckable);
        child->setCheckState(0, Qt::Checked); // Set it checked, since all items are enabled by default// 모든 항목이 기본적으로 사용 가능하므로 체크 표시를 설정합니다.
        ui.filterSelectTreeWidget->addTopLevelItem(child);
        m_tableFilterList.append(iter.key());
    }

    // create an invisible y-axis for the text arrows  // 텍스트 화살표에 대해 보이지 않는 y 축을 만듭니다.
    m_arrowGraph.p_yAxis = m_plotPtr->axisRect()->addAxis(QCPAxis::atLeft);
    m_arrowGraph.p_yAxis->setVisible(false);
    m_arrowGraph.p_yAxis->setRangeUpper(s_TextArrowPositions + 1);  // The last text shall not be on upper border (+1)// 마지막 텍스트는 위쪽 테두리 (+1)에 있지 않아야합니다.
    // Load MODE, ERR, EV, MSG messages from datamodel
    // 데이터 모델로부터 MODE, ERR, EV, MSG 메시지로드
    m_dataStoragePtr->getMessagesOfType(ModeMessage::TypeName, m_indexToMessageMap);
    m_dataStoragePtr->getMessagesOfType(ErrorMessage::TypeName, m_indexToMessageMap);
    m_dataStoragePtr->getMessagesOfType(EventMessage::TypeName, m_indexToMessageMap);
    m_dataStoragePtr->getMessagesOfType(MsgMessage::TypeName, m_indexToMessageMap);
    // and insert them into the graph
    // 그래프에 삽입한다.
    insertTextArrows();

    // connect scroll bars
    // 스크롤 막대 연결
    connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(verticalScrollMoved(int)));
    connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollMoved(int)));
    connect(m_plotPtr->axisRect()->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    // set range -> whole graph should be viewable therefore 20 percent offset on both sides
    // 범위 설정 -> 전체 그래프를 볼 수 있어야하므로 양쪽에서 20 % 오프셋됩니다.
    qint64 offset = (m_scrollEndIndex - m_scrollStartIndex) / 20;
    m_plotPtr->axisRect()->axis(QCPAxis::atBottom)->setRange(m_scrollStartIndex - offset, m_scrollEndIndex + offset);
    ui.verticalScrollBar->setValue(ui.verticalScrollBar->maximum());

    // Set up proxy for table filtering
    // 테이블 필터링을위한 프록시 설정
    mp_tableFilterProxyModel = new QSortFilterProxyModel(this);     // will be deleted upon destruction of "this"// "this"가 삭제되면 삭제됩니다.
    mp_tableFilterProxyModel->setSourceModel(m_dataStoragePtr.data());
    ui.tableWidget->setModel(mp_tableFilterProxyModel);
    connect(ui.tableWidget->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(selectedRowChanged(QModelIndex, QModelIndex)));

    // Graph is loaded - Setup ui. Connect mouseMove signal according to checkbox state
    // 그래프가로드됩니다 - ui를 설정하십시오. 체크 박스 상태에 따라 mouseMove 신호를 연결합니다.
    if(ui.showValuesCheckBox->isChecked())
    {
        connect(m_plotPtr.data(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    }

    // Show the table view
    // 테이블 뷰를 표시합니다.
    hideTableView(false);

    // Enable only the layers that are enabled by their checkbox
    // 확인란에 의해 활성화 된 레이어 만 활성화합니다.
    if(ui.modeDisplayCheckBox->isChecked()) m_plotPtr->layer(ModeMessage::TypeName)->setVisible(true);
    if(ui.evDisplayCheckBox->isChecked())   m_plotPtr->layer(EventMessage::TypeName)->setVisible(true);
    if(ui.errDisplayCheckBox->isChecked())  m_plotPtr->layer(ErrorMessage::TypeName)->setVisible(true);
    if(ui.msgDisplayCheckBox->isChecked())  m_plotPtr->layer(MsgMessage::TypeName)->setVisible(true);
    m_plotPtr->layer(s_CursorLayerName)->setVisible(true);  // cursor layer is always visible// 커서 레이어가 항상 표시됩니다.

    // final rescaling and plotting.
    // 최종 재배치 및 플로팅.
    m_plotPtr->rescaleAxes(false);
    m_plotPtr->replot();
}

void LogAnalysis::logLoadingThreadTerminated()
{
    QLOG_DEBUG() << "LogAnalysis::logLoadingThreadTerminated.";
    m_loaderThreadPtr.reset();
}

void LogAnalysis::logLoadingProgressDialogCanceled()
{
    QLOG_DEBUG() << "LogAnalysis::logLoadingProgressDialogCanceled.";
    if(m_loaderThreadPtr)
    {
        m_loaderThreadPtr->stopLoad();
    }
}

void LogAnalysis::modeCheckboxClicked(bool checked)
{
    m_plotPtr->layer(ModeMessage::TypeName)->setVisible(checked);
    m_plotPtr->replot();
}

void LogAnalysis::errorCheckboxClicked(bool checked)
{
    m_plotPtr->layer(ErrorMessage::TypeName)->setVisible(checked);
    m_plotPtr->replot();
}

void LogAnalysis::eventCheckboxClicked(bool checked)
{
    m_plotPtr->layer(EventMessage::TypeName)->setVisible(checked);
    m_plotPtr->replot();
}

void LogAnalysis::msgCheckboxClicked(bool checked)
{
    m_plotPtr->layer(MsgMessage::TypeName)->setVisible(checked);
    m_plotPtr->replot();
}

void LogAnalysis::verticalScrollMoved(int value)
{
    QCPAxis *xAxis = m_plotPtr->axisRect()->axis(QCPAxis::atBottom);
    double percent = value / 100.0;
    double center = xAxis->range().center();
    double requestedrange = (m_scrollEndIndex - m_scrollStartIndex) * percent;
    xAxis->setRangeUpper(center + (requestedrange/2.0));
    xAxis->setRangeLower(center - (requestedrange/2.0));
    m_plotPtr->replot(QCustomPlot::rpQueuedReplot);
}

void LogAnalysis::horizontalScrollMoved(int value)
{
    if (value != m_lastHorizontalScrollVal)
    {
        QCPAxis *xAxis = m_plotPtr->axisRect()->axis(QCPAxis::atBottom);
        m_lastHorizontalScrollVal = value;
        disconnect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
        xAxis->setRange(value, xAxis->range().size(), Qt::AlignCenter);
        m_plotPtr->replot(QCustomPlot::rpQueuedReplot);
        connect(xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    }
}

void LogAnalysis::xAxisChanged(QCPRange range)
{
    disconnect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollMoved(int)));
    disconnect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(verticalScrollMoved(int)));

    ui.horizontalScrollBar->setValue(qRound(range.center())); // adjust position of scroll bar slider// 스크롤 막대 슬라이더의 위치 조정
    ui.horizontalScrollBar->setPageStep(qRound(range.size())); // adjust size of scroll bar slider// 스크롤 막대 슬라이더의 크기 조정
    double totalrange = m_scrollEndIndex - m_scrollStartIndex;
    double currentrange = range.upper - range.lower;
    ui.verticalScrollBar->setValue(static_cast<int>(100.0 * (currentrange / totalrange)));

    connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollMoved(int)));
    connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(verticalScrollMoved(int)));
}

void LogAnalysis::itemEnabled(QString name)
{
    QVector<double> xlist;
    QVector<double> ylist;

    if (!m_dataStoragePtr->getValues(name, m_useTimeOnXAxis, xlist, ylist))
    {
        //No values!
        QLOG_WARN() << "No values in datamodel for " << name;
        ui.dataSelectionScreen->disableItem(name);
        return;
    }

    // HACK - a graph with only one value is not plottet. So we add a second point with same value
    // which forces the graph to plot a short line. Moreover the mouse over which is handeled by
    // the plotMouseMove(QMouseEvent *evt) method delivers always NONE for a graph with only one point.
    // HACK - 하나의 값만 가진 그래프는 plottet이 아닙니다. 그래서 같은 값의 두 번째 점을 더합니다.
    // 을 사용하면 그래프에 짧은 선을 그립니다. 또한 마우스는
    // plotMouseMove (QMouseEvent * evt) 메서드는 오직 하나의 점을 가진 그래프에 대해 항상 NONE을 전달합니다.
    if(xlist.size() == 1)
    {
        xlist.append(xlist[0]++);
        ylist.append(ylist[0]);
    }

    m_plotPtr->setCurrentLayer("main");     // All plots are on main layer// 모든 플롯은 메인 레이어에 있습니다.
    QCPAxisRect *axisRect = m_plotPtr->axisRect();

    // use golden ratio for evenly distributed colors
    // 균등하게 분포 된 색상에 황금 비율 사용
    double golden_ratio_conjugate = 0.618033988749895;
    double h = (static_cast<double>(rand()) / RAND_MAX);
    h = h + golden_ratio_conjugate;
    h = fmod(h, 1);     // hue
    double s = 0.75;    // saturation
    double v = 0.8516;  // value
    QColor color = QColor::fromHsvF(h, s, v);

    GraphElements newPlot;
    QCPAxis *paxis = new LogAnalysisAxis(axisRect, QCPAxis::atLeft);
    newPlot.p_yAxis = axisRect->addAxis(QCPAxis::atLeft, paxis);
    newPlot.p_yAxis->setLabel(name);
    newPlot.p_yAxis->setNumberFormat("gb");
    newPlot.p_yAxis->setLabelColor(color);
    newPlot.p_yAxis->setTickLabelColor(color);
    newPlot.p_yAxis->setSelectableParts(QCPAxis::spAxis);

    newPlot.p_graph = m_plotPtr->addGraph(axisRect->axis(QCPAxis::atBottom), newPlot.p_yAxis);
    newPlot.p_graph->setPen(QPen(color, 1));
    newPlot.p_graph->setData(xlist, ylist);
    newPlot.p_graph->rescaleValueAxis();

    m_activeGraphs[name] = newPlot;     // store the plot by name// 이름으로 플롯 저장
    // Add to gouping dialog
    // gouping 대화 상자에 추가
    m_axisGroupingDialog->addAxis(name, newPlot.p_yAxis->range().lower, newPlot.p_yAxis->range().upper, color);
    // if cursors are present call range change to update tool tip values
    // 커서가있는 경우 공구 팁 값을 업데이트하기위한 호출 범위 변경
    if(mp_cursorLeft && mp_cursorRight)
    {
        cursorRangeChange();
    }

    // Enable / disable grid - Enabled as long as only one line graph is visible
    // As soon as there are more than one line graph the grid is removed
    // 그리드 활성화 / 비활성화 - 한 라인 그래프 만 표시되는 경우 활성화
    // 두 개 이상의 선 그래프가 생기면 그리드가 제거됩니다.
    int activeAxes = axisRect->axisCount(QCPAxis::atLeft);
    if(activeAxes == 2)   // 1st axis is for the text arrows, 2nd for the first line graph// 첫 번째 축은 텍스트 화살표 용이고 두 번째 축은 첫 번째 선 그래프 용입니다.
    {
        newPlot.p_yAxis->grid()->setVisible(true);
    }
    else if(activeAxes > 2)
    {
        QCPAxis *yAxis = m_plotPtr->axisRect()->axis(QCPAxis::atLeft, 1);
        yAxis->grid()->setVisible(false);
    }

    m_plotPtr->replot();
}

void LogAnalysis::itemDisabled(QString name)
{
    if (m_activeGraphs.contains(name)) // only enabled items can be disabled// 활성화 된 항목 만 비활성화 할 수 있습니다.
    {
        // remove axis, graph and stored info from m_activeGraphs
        // m_activeGraphs에서 축, 그래프 및 저장된 정보를 제거합니다.
        m_plotPtr->axisRect()->removeAxis(m_activeGraphs.value(name).p_yAxis);
        m_plotPtr->removeGraph(m_activeGraphs.value(name).p_graph);
        m_activeGraphs.remove(name);

        // if cursors are present call range change to update tool tip values
        // 커서가있는 경우 공구 팁 값을 업데이트하기위한 호출 범위 변경
        if(mp_cursorLeft && mp_cursorRight)
        {
            cursorRangeChange();
        }

        // Add grid if only one line graph is left
        // 하나의 선 그래프 만 남아있는 경우 그리드 추가
        if(m_plotPtr->axisRect()->axisCount(QCPAxis::atLeft) == 2)   // 1st axis is for the text arrows, 2nd for the first line graph// 첫 번째 축은 텍스트 화살표 용이고 두 번째 축은 첫 번째 선 그래프 용입니다.
        {
            QCPAxis *yAxis = m_plotPtr->axisRect()->axis(QCPAxis::atLeft, 1);
            yAxis->grid()->setVisible(true);
        }

        // remove from group dialog
        // 그룹 대화 상자에서 제거
        m_axisGroupingDialog->removeAxis(name);
        m_plotPtr->replot();
    }
}

void LogAnalysis::indexTypeCheckBoxClicked(bool checked)
{
    if (m_useTimeOnXAxis != checked)
    {
        m_useTimeOnXAxis = checked;
        // We have to remove all graphs when changing x-axis storing the active selection
        // 활성 선택을 저장하는 x 축을 변경할 때 모든 그래프를 제거해야합니다.
        QList<QString> reEnableList = ui.dataSelectionScreen->disableAllItems();

        // remove the text arrows and cursors
        // 텍스트 화살표와 커서를 제거합니다.
        m_plotPtr->clearItems();
        mp_cursorSimple = 0;      // clearItems() deletes the cursors!// clearItems ()는 커서를 삭제합니다!
        mp_cursorLeft = 0;        // clearItems() deletes the cursors!// clearItems ()는 커서를 삭제합니다!
        mp_cursorRight = 0;       // clearItems() deletes the cursors!// clearItems ()는 커서를 삭제합니다!
        m_cursorXAxisRange = 0.0; // no cursor no range// 커서가없는 범위 없음

        // uncheck cursor checkboxes
        // 커서 체크 박스를 선택 해제합니다.
        ui.tableCursorCheckBox->setCheckState(Qt::Unchecked);
        ui.rangeCursorCheckBox->setCheckState(Qt::Unchecked);

        // arrows can be inserted instantly again
        // 화살표를 다시 삽입 할 수 있습니다.
        m_statusTextPos = 0;    // reset text arrow length// 텍스트 화살표 길이 재설정
        insertTextArrows();

        // Graphs can be reenabled using previous stored selection
        // 이전 저장된 선택을 사용하여 그래프를 다시 활성화 할 수 있습니다.
        ui.dataSelectionScreen->enableItemList(reEnableList);

        // Re -set x axis, scroller and zoom
        // x 축, scroller 및 zoom 다시 설정
        disconnect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(verticalScrollMoved(int)));
        disconnect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollMoved(int)));

        setupXAxisAndScroller();
        m_plotPtr->axisRect()->axis(QCPAxis::atBottom)->setRange(m_scrollStartIndex, m_scrollEndIndex);
        m_plotPtr->replot();
        ui.verticalScrollBar->setValue(ui.verticalScrollBar->maximum());

        connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(verticalScrollMoved(int)));
        connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollMoved(int)));
    }
}

void LogAnalysis::filterItemChanged(QTreeWidgetItem* item, int col)
{
    Q_UNUSED(col)
    //Sorting item changed.
    if (!item)
    {
        return;
    }
    QString msgname = item->text(0);
    if (item->checkState(0) == Qt::Checked)
    {
        if (!m_tableFilterList.contains(msgname))
        {
            m_tableFilterList.append(msgname);
        }
    }
    else
    {
        if (m_tableFilterList.contains(msgname))
        {
            m_tableFilterList.removeOne(msgname);
        }
    }
}

void LogAnalysis::filterAcceptClicked()
{
    // All elements selected -> filter is disabled
    // 선택한 모든 요소 -> 필터가 비활성화됩니다.
    if (ui.filterSelectTreeWidget->topLevelItemCount() == m_tableFilterList.size())
    {
        disableTableFilter();
    }
    // one or more elements selected -> RegEx must be used
    // 하나 이상의 요소가 선택됨 -> RegEx를 사용해야 함
    else
    {
        // It is VERY important to disable the filtering prior to set up a new one
        // If this is not done the regex filter gets terribly slow!!!
        // 새 필터를 설정하기 전에 필터링을 비활성화하는 것이 중요합니다.
        // 이것이 수행되지 않으면 정규식 필터가 매우 느려집니다 !!!
        disableTableFilter();
        QString regex = m_tableFilterList.join("\\b|");  // Create regex like val1\b|val2\b|val3// val1과 같은 정규 표현식을 만듭니다. \ b | val2 \ b | val3
        regex.append("\\b");                             // append the final \b// 마지막에 \ b를 추가합니다.
        mp_tableFilterProxyModel->setFilterRegExp(regex);
        mp_tableFilterProxyModel->setFilterRole(Qt::DisplayRole);
        mp_tableFilterProxyModel->setFilterKeyColumn(1);
    }

    ui.tableFilterGroupBox->setVisible(false);
}

void LogAnalysis::filterCancelClicked()
{
    ui.tableFilterGroupBox->setVisible(false);
}

void LogAnalysis::showFilterButtonClicked()
{
    if (ui.tableFilterGroupBox->isVisible())
    {
        ui.tableFilterGroupBox->setVisible(false);
    }
    else
    {
        ui.tableFilterGroupBox->setVisible(true);
    }
}

void LogAnalysis::filterSelectAllClicked()
{
    for (int i = 0; i < ui.filterSelectTreeWidget->topLevelItemCount(); ++i)
    {
        if (ui.filterSelectTreeWidget->topLevelItem(i)->checkState(0) != Qt::Checked)
        {
            ui.filterSelectTreeWidget->topLevelItem(i)->setCheckState(0, Qt::Checked);
        }
    }
}

void LogAnalysis::filterSelectInvertClicked()
{
    for (int i = 0; i < ui.filterSelectTreeWidget->topLevelItemCount(); ++i)
    {
        if (ui.filterSelectTreeWidget->topLevelItem(i)->checkState(0) == Qt::Checked)
        {
            ui.filterSelectTreeWidget->topLevelItem(i)->setCheckState(0,Qt::Unchecked);
        }
        else
        {
            ui.filterSelectTreeWidget->topLevelItem(i)->setCheckState(0,Qt::Checked);
        }
    }
}

void LogAnalysis::selectedRowChanged(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous);
    if (!current.isValid())
    {
        return;
    }
    qint64 index =  mp_tableFilterProxyModel->mapToSource(current).row();

    if(mp_cursorSimple)
    {
        if (m_useTimeOnXAxis)
        {
            // timestamp value of the current row is in colum 2
            // 현재 행의 시간 소인 값은 2 열입니다.
            double item = ui.tableWidget->model()->itemData(ui.tableWidget->model()->index(current.row(), 2)).value(Qt::DisplayRole).toInt();
            if(!m_dataStoragePtr->ModelIsScaled())
            {
                // If datamodel is NOT scaled we have to scale the timestamp.
                // datamodel의 크기를 조정하지 않은 경우 타임 스탬프의 크기를 조정해야합니다.
                mp_cursorSimple->setCurrentXPos(item / m_dataStoragePtr->getTimeDivisor());
            }
        }
        else
        {
            mp_cursorSimple->setCurrentXPos(index);
        }
    }

    m_dataStoragePtr->selectedRowChanged(mp_tableFilterProxyModel->mapToSource(current));

    // TODO check if we want to handle a context menu on table?!
    // TODO 테이블에서 상황에 맞는 메뉴를 처리 할 것인지 확인합니다.
}

void LogAnalysis::exportAsciiLogClicked()
{
    doExport(false, 0.0);   // ascii export does not use the iconInterval// ascii export는 iconInterval을 사용하지 않습니다.
}

void LogAnalysis::exportKmlClicked()
{
    bool ok = false;
    double iconInterval = QInputDialog::getDouble(this, tr("Set icon interval"),
                                         tr("Icon interval (meters):"), 2, 0, 100, 3, &ok);
    if (!ok)
    {   // user has cancelled the dialog// 사용자가 대화 상자를 취소했습니다.
        iconInterval = 2;
    }
    doExport(true, iconInterval);
}

void LogAnalysis::doExport(bool kmlExport, double iconInterval)
{
    QString exportExtension = kmlExport ? "kml" : "log";
    // for exporting use the name of the loaded log and replace any extension by the export extension
    // 내보내는 경우로드 된 로그의 이름을 사용하고 확장명을 내보내기 확장명으로 바꿉니다.
    QString exportFilename = m_filename.replace(QRegularExpression("\\w+$"), exportExtension);

    QFileDialog dialog(this, "Save Log File", QGC::logDirectory(), "Logformat (*.kml *.kmz *.log)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.selectFile(exportFilename);
    QLOG_DEBUG() << "Suggested Export Filename: " << exportFilename;

    if(dialog.exec())
    {
        QTime timer;
        QString result;
        QString outputFileName = dialog.selectedFiles().at(0);
        timer.start();

        if(kmlExport)
        {
            QLOG_DEBUG() << "iconInterval: " << iconInterval;

            KmlLogExporter kmlExporter(this, m_loadedLogMavType, iconInterval);
            result = kmlExporter.exportToFile(outputFileName, m_dataStoragePtr);
        }
        else
        {
            AsciiLogExporter asciiExporter(this);
            result = asciiExporter.exportToFile(outputFileName, m_dataStoragePtr);
        }

        QLOG_DEBUG() << "Log export took " << timer.elapsed() << "ms";
        QMessageBox::information(this,  "Information", result);
    }
    else
    {
        QLOG_DEBUG() << "Logexporting cancelled";
    }
}

void LogAnalysis::graphControlsButtonClicked()
{
    activeGraphType::const_iterator iter;
    for (iter = m_activeGraphs.constBegin(); iter != m_activeGraphs.constEnd() ; ++iter)
    {
        m_axisGroupingDialog->fullAxisUpdate(iter.key(), iter->p_yAxis->range().lower, iter->p_yAxis->range().upper,
                                             iter->m_manualRange, iter->m_inGroup, iter->m_groupName, iter->p_graph->pen().color());
    }

    m_axisGroupingDialog->show();
    m_axisGroupingDialog->activateWindow();
    m_axisGroupingDialog->raise();
}

void LogAnalysis::graphGroupingChanged(QList<AP2DataPlotAxisDialog::GraphRange> graphRangeList)
{
    // first reset all active elements to their default state
    // 먼저 모든 활성 요소를 기본 상태로 재설정합니다.
    activeGraphType::iterator iter;
    for (iter = m_activeGraphs.begin(); iter != m_activeGraphs.end() ; ++iter)
    {
        if(iter->m_inGroup || iter->m_manualRange)
        {
            iter->m_inGroup = false;
            iter->m_manualRange = false;
            iter->m_groupName = QString();
        }
        iter->p_graph->rescaleValueAxis();
    }

    // Now sort all grouped items into a map, and all manuals into a vector
    // 이제 모든 그룹화 된 항목을 맵으로 정렬하고 모든 매뉴얼을 벡터로 정렬합니다.
    QMap<QString, GroupElement> groupingMap;
    QVector<AP2DataPlotAxisDialog::GraphRange> manualRangeVec;
    foreach(const AP2DataPlotAxisDialog::GraphRange &range, graphRangeList)
    {
        if(range.isgrouped)
        {
            GroupElement &groupElement = groupingMap[range.group];  // yes, if doesn't exist just create a new one.// 예, 존재하지 않으면 새로운 것을 만듭니다.
            groupElement.m_groupName = range.group;
            groupElement.m_upper = groupElement.m_upper < range.max ? range.max : groupElement.m_upper;
            groupElement.m_lower = groupElement.m_lower > range.min ? range.min : groupElement.m_lower;
            groupElement.m_graphList.push_back(range.graph);
        }
        else if(range.manual)
        {
            manualRangeVec.push_back(range);
        }
    }

    // set all grouped items to same scaling
    // 모든 그룹화 된 항목을 동일한 크기 조정으로 설정합니다.
    foreach(const GroupElement &element, groupingMap)
    {
        foreach(const QString &name, element.m_graphList)
        {
            if(m_activeGraphs.contains(name))
            {
                GraphElements &graph = m_activeGraphs[name];
                graph.p_yAxis->setRangeUpper(element.m_upper);
                graph.p_yAxis->setRangeLower(element.m_lower);
                graph.m_inGroup = true;
                graph.m_groupName = element.m_groupName;
            }
        }
    }

    // set all manual item to their individual scaling
    // 모든 수동 항목을 개별 배율로 설정합니다.
    foreach(const AP2DataPlotAxisDialog::GraphRange &range, manualRangeVec)
    {
        if(m_activeGraphs.contains(range.graph))
        {
            GraphElements &graph = m_activeGraphs[range.graph];
            graph.p_yAxis->setRangeUpper(range.max);
            graph.p_yAxis->setRangeLower(range.min);
            graph.m_manualRange = true;
        }
    }

    m_plotPtr->replot();
}

void LogAnalysis::graphColorsChanged(QMap<QString,QColor> colorlist)
{
    QMap<QString,QColor>::ConstIterator iter;
    for(iter = colorlist.constBegin(); iter != colorlist.constEnd(); ++iter)
    {
        if(m_activeGraphs.contains(iter.key()))
        {
            GraphElements &element = m_activeGraphs[iter.key()];
            element.p_graph->setPen(QPen(*iter, 1));
            element.p_yAxis->setLabelColor(*iter);
            element.p_yAxis->setTickLabelColor(*iter);
        }
    }

    m_plotPtr->replot();
}

void LogAnalysis::plotMouseMove(QMouseEvent *evt)
{
    bool insideCursorRange = false;
    QString out;
    QTextStream outStream(&out);

    // Create 1st line of the mouse over tooltip
    // 툴팁 위에 마우스의 첫 번째 줄을 만듭니다.
    double viewableRange = (m_plotPtr->xAxis->range().upper - m_plotPtr->xAxis->range().lower);
    double xValue = m_plotPtr->axisRect()->axis(QCPAxis::atBottom)->pixelToCoord(evt->x());
    double offset = viewableRange / 100;   // an offset of 1 percent// 1 퍼센트의 오프셋
    if(m_useTimeOnXAxis)
    {
        outStream << "Time s:" << QString::number(xValue, 'f', 3);
    }
    else
    {
        outStream << "Line:" << QString::number(xValue, 'f', 0);
    }
    if(mp_cursorLeft && mp_cursorRight)
    {
        // the offset increases the range where we are inside the cursor range. If we don't do this
        // the tool tip will not show the range values when increasing cursor range. When dragging
        // the right cursor to the right the mouse leaves the range.
        // 오프셋은 커서 범위 안에있는 범위를 증가시킵니다. 우리가 이것을하지 않으면
        // 커서 범위를 늘리면 툴팁에 범위 값이 표시되지 않습니다. 드래그 할 때
        // 마우스가 범위를 벗어나는 오른쪽 커서.
        if((mp_cursorLeft->getCurrentXPos() < xValue + offset) && (mp_cursorRight->getCurrentXPos() > xValue - offset))
        {
            outStream << " " << QChar(0x0394) << ":" << m_cursorXAxisRange;
            insideCursorRange = true;
        }
    }

    // and now the data of all enabled graphs
    // 그리고 이제 모든 활성화 된 그래프의 데이터
    outStream.setRealNumberNotation(QTextStream::FixedNotation);
    activeGraphType::Iterator iter;
    for(iter = m_activeGraphs.begin(); iter != m_activeGraphs.end(); ++iter)
    {
        outStream.setRealNumberPrecision(3);
        double key   = iter->p_graph->keyAxis()->pixelToCoord(evt->x());
        int keyIndex = iter->p_graph->findBegin(key);

        outStream << endl << iter.key();

        if(insideCursorRange && m_rangeValuesStorage.contains(iter.key()))
        {
            RangeValues &range = m_rangeValuesStorage[iter.key()];
            outStream << " min:" << range.m_min << " max:" << range.m_max << " " << QChar(0x0394) << ":" << range.m_max - range.m_min
                      << " avg:" << range.m_average;
        }

        outStream.setRealNumberPrecision(4);

        if(keyIndex)
        {
            outStream << " val:" << iter->p_graph->dataMainValue(keyIndex);
        }
        else
        {
            outStream << " val:" << iter.key() << "NONE";
        }
    }
    QToolTip::showText(QPoint(evt->globalPos().x() + m_plotPtr->x(), evt->globalPos().y() + m_plotPtr->y()), out);
}

void LogAnalysis::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if(!mp_cursorSimple)
    {
        menu->addAction("Add simple cursor", this, SLOT(insertSimpleCursor()));
    }
    if(!mp_cursorLeft)
    {
        menu->addAction("Add range cursors", this, SLOT(insertRangeCursors()));
    }
    if(mp_cursorSimple)
    {
        menu->addAction("Remove simple cursor", this, SLOT(removeSimpleCursor()));
    }
    if(mp_cursorLeft || mp_cursorRight)
    {
        menu->addAction("Remove range cursors", this, SLOT(removeRangeCursors()));
    }

    menu->popup(m_plotPtr->mapToGlobal(pos));
}

void LogAnalysis::insertSimpleCursor()
{
    if(!mp_cursorSimple)
    {
        m_plotPtr->setCurrentLayer(s_CursorLayerName);
        // initial cursor pos is in the middle od the visible area
        // 초기 커서 위치가 보이는 영역의 중간 또는 위치에 있습니다.
        double viewableRange = (m_plotPtr->xAxis->range().upper - m_plotPtr->xAxis->range().lower);
        double newCursorPos = m_plotPtr->xAxis->range().lower + (viewableRange / 2);
        mp_cursorSimple = new LogAnalysisCursor(m_plotPtr.data(), newCursorPos, LogAnalysisCursor::simple);    // QcustomPlot takes ownership
        mp_cursorSimple->setPen(QPen(QColor::fromRgb(0, 0, 255), 1));
        setTablePos(newCursorPos); // call once to set table view to initial cursor pos// 한 번 호출하여 테이블 뷰를 초기 커서 위치로 설정합니다.
        connect(mp_cursorSimple, SIGNAL(newCursorPos(double)), this, SLOT(setTablePos(double)));
        m_plotPtr->replot();
        // when cursors are inserted the check box should reflect this
        // 커서가 삽입 될 때 확인란에이를 반영해야합니다.
        ui.tableCursorCheckBox->setCheckState(Qt::Checked);
    }
}

void LogAnalysis::insertRangeCursors()
{
    if(!mp_cursorLeft && !mp_cursorRight)
    {
        m_plotPtr->setCurrentLayer(s_CursorLayerName);
        // initial cursor pos is in the middle od the visible area
        // 초기 커서 위치가 보이는 영역의 중간 또는 위치에 있습니다.
        double viewableRange = (m_plotPtr->xAxis->range().upper - m_plotPtr->xAxis->range().lower);
        double newCursorPos = m_plotPtr->xAxis->range().lower + (viewableRange / 2);
        // without offset both cursors are exactly at the same position - you have to drag one to see the other
        // 오프셋없이 두 커서가 정확히 같은 위치에 있습니다. 한 커서를 드래그하여 다른 커서를 표시해야합니다.
        double offset = (m_plotPtr->xAxis->range().upper - m_plotPtr->xAxis->range().lower) / 20.0;
        mp_cursorLeft = new LogAnalysisCursor(m_plotPtr.data(), newCursorPos - offset, LogAnalysisCursor::left);   // QcustomPlot takes ownership
        mp_cursorLeft->setPen(QPen(QColor::fromRgb(255, 0, 0), 1));
        mp_cursorRight = new LogAnalysisCursor(m_plotPtr.data(), newCursorPos + offset, LogAnalysisCursor::right); // QcustomPlot takes ownership
        mp_cursorRight->setPen(QPen(QColor::fromRgb(0, 155, 0), 1));

        mp_cursorLeft->setOtherCursor(mp_cursorRight);
        mp_cursorRight->setOtherCursor(mp_cursorLeft);
        cursorRangeChange();    // call once to fill the range values// 한 번 호출하여 범위 값을 채 웁니다.
        connect(mp_cursorLeft, SIGNAL(cursorRangeChange()), this, SLOT(cursorRangeChange()));
        connect(mp_cursorRight, SIGNAL(cursorRangeChange()), this, SLOT(cursorRangeChange()));
        connect(mp_cursorLeft, SIGNAL(rangeCursorMoving()), this, SLOT(rangeCursorsMoving()));
        connect(mp_cursorRight, SIGNAL(rangeCursorMoving()), this, SLOT(rangeCursorsMoving()));
        m_plotPtr->replot();
        // when cursors are inserted the check box should reflect this
        // 커서가 삽입 될 때 확인란에이를 반영해야합니다.
        ui.rangeCursorCheckBox->setCheckState(Qt::Checked);
    }
}

void LogAnalysis::removeSimpleCursor()
{
    if(mp_cursorSimple)
    {
        m_plotPtr->removeItem(mp_cursorSimple); // remove also deletes the pointer// remove는 또한 포인터를 삭제합니다.
        mp_cursorSimple = 0;
    }
    m_plotPtr->replot();
    // when cursors are removed the check box should reflect this
    // 커서가 제거 될 때이 확인란을 반영해야합니다.
    ui.tableCursorCheckBox->setCheckState(Qt::Unchecked);
}

void LogAnalysis::removeRangeCursors()
{
    if(mp_cursorLeft)
    {
        m_plotPtr->removeItem(mp_cursorLeft); // remove also deletes the pointer// remove는 또한 포인터를 삭제합니다.
        mp_cursorLeft = 0;
    }
    if(mp_cursorRight)
    {
        m_plotPtr->removeItem(mp_cursorRight); // remove also deletes the pointer// remove는 또한 포인터를 삭제합니다.
        mp_cursorRight = 0;
    }
    m_cursorXAxisRange = 0.0;   // no cursor no range// 커서가없는 범위 없음
    m_plotPtr->replot();
    // when cursors are removed the check box should reflect this
    // 커서가 제거 될 때이 확인란을 반영해야합니다.
    ui.rangeCursorCheckBox->setCheckState(Qt::Unchecked);
}

void LogAnalysis::resetValueScaling()
{
    // reset all active elements to their default state
    // 모든 활성 요소를 기본 상태로 재설정합니다.
    activeGraphType::iterator iter;
    for (iter = m_activeGraphs.begin(); iter != m_activeGraphs.end() ; ++iter)
    {
        if(iter->m_inGroup || iter->m_manualRange)
        {
            iter->m_inGroup = false;
            iter->m_manualRange = false;
            iter->m_groupName = QString();
        }
        iter->p_graph->rescaleValueAxis();
    }
    m_plotPtr->replot();
}

void LogAnalysis::enableRangeCursor(bool enable)
{
    if(enable)
    {
        insertRangeCursors();
    }
    else
    {
        removeRangeCursors();
    }
}

void LogAnalysis::enableTableCursor(bool enable)
{
    if(enable)
    {
        insertSimpleCursor();
    }
    else
    {
        removeSimpleCursor();
    }
}

void LogAnalysis::storeGraphSettingsPressed()
{
    QLOG_DEBUG() << "LogAnalysis::storeGraphSettingsPressed()";

    activeGraphType::iterator iter;
    PresetManager::presetElementVec preset;
    // iterate all visible graphs and store their setting
    // 모든 보이는 그래프를 반복하고 그들의 설정을 저장한다.
    for(iter = m_activeGraphs.begin(); iter != m_activeGraphs.end(); ++iter)
    {
        PresetManager::presetElement element;
        element.m_graph = iter.key();
        element.m_color = iter->p_graph->pen().color();
        if(iter->m_manualRange)
        {   // y-axis scaling is only stored if graph is in manual range...// y 축 스케일링은 그래프가 수동 범위에있는 경우에만 저장됩니다.
            element.m_manualRange = true;
            element.m_range = iter->p_yAxis->range();
        }
        else if(iter->m_inGroup)
        {   //... or in group range// ... 또는 그룹 범위 내에 있음
            element.m_group = iter->m_groupName;
            element.m_range = iter->p_yAxis->range();
        }

        preset.push_back(element);
    }
    m_presetMgrPtr->saveSpecialSet(preset, ui.indexTypeCheckBox->isChecked());
}

void LogAnalysis::applyGraphSettingsPressed()
{
    QLOG_DEBUG() << "LogAnalysis::applyGraphSettingsPressed()";

    // get preset from manager
    // 관리자로부터 사전 설정을 얻습니다.
    PresetManager::presetElementVec preset;
    bool usesTimeAxis = m_presetMgrPtr->loadSpecialSet(preset);

    // disable all open graphs
    // 열려있는 모든 그래프를 비활성화합니다.
    ui.dataSelectionScreen->disableAllItems();
    // X-Axis settings
    // X 축 설정
    ui.indexTypeCheckBox->setChecked(usesTimeAxis);
    indexTypeCheckBoxClicked(usesTimeAxis);

    // the enabling has to be done in 2 steps.
    // first enable all graphs stored in the settings.
    // Second configure then enabled graphs color and range

    // Create list with enabled graphs and enable them
    // 활성화는 2 단계로 이루어져야합니다.
    // 먼저 설정에 저장된 모든 그래프를 활성화합니다.
    // 두 번째 구성 후 활성화 된 그래프 색상 및 범위

    // 활성화 된 그래프를 사용하여 목록 만들기 및 활성화
    QStringList enabledGraphList;
    for(int i = 0; i < preset.size(); ++i)
    {
        enabledGraphList.push_back(preset.at(i).m_graph);
    }
    ui.dataSelectionScreen->enableItemList(enabledGraphList);

    // convert preset to ranges and use grouping changed method to scale the graph
    // 사전 설정을 범위로 변환하고 그룹화 된 변경된 방법을 사용하여 그래프 크기 조정
    QList<AP2DataPlotAxisDialog::GraphRange> graphRanges;
    graphRanges = presetToRangeConverter(preset);
    graphGroupingChanged(graphRanges);
}

void LogAnalysis::analysisPresetSelected(PresetManager::presetElementVec preset)
{
    QLOG_DEBUG() << "LogAnalysis::analysisPresetSelected()";
    // first clear the graph
    // 먼저 그래프를 지 웁니다.
    ui.dataSelectionScreen->disableAllItems();

    // Create list with enabled graphs and enable them
    // 활성화 된 그래프를 사용하여 목록 만들기 및 활성화
    QStringList enabledGraphList;
    for(int i = 0; i < preset.size(); ++i)
    {
        enabledGraphList.push_back(preset.at(i).m_graph);
    }
    ui.dataSelectionScreen->enableItemList(enabledGraphList);

    // now set range and color
    // convert preset to ranges and use grouping changed method to scale the graph
    // 이제 범위와 색상을 설정합니다.
    // 사전 설정을 범위로 변환하고 그룹화 된 변경된 방법을 사용하여 그래프 크기 조정
    QList<AP2DataPlotAxisDialog::GraphRange> graphRanges;
    graphRanges = presetToRangeConverter(preset);
    graphGroupingChanged(graphRanges);
}

void LogAnalysis::addCurrentViewToPreset()
{
    QLOG_DEBUG() << "LogAnalysis::addCurrentViewToPreset()";

    activeGraphType::iterator iter;
    PresetManager::presetElementVec preset;
    for(iter = m_activeGraphs.begin(); iter != m_activeGraphs.end(); ++iter)
    {
        PresetManager::presetElement element;
        element.m_graph = iter.key();
        element.m_color = iter->p_graph->pen().color();
        if(iter->m_manualRange)
        {   // y-axis scaling is only stored if graph is in manual range...// y 축 스케일링은 그래프가 수동 범위에있는 경우에만 저장됩니다.
            element.m_manualRange = true;
            element.m_range = iter->p_yAxis->range();
        }
        else if(iter->m_inGroup)
        {   //... or in group range// ... 또는 그룹 범위 내에 있음
            element.m_group = iter->m_groupName;
            element.m_range = iter->p_yAxis->range();
        }

        preset.push_back(element);
    }

    m_presetMgrPtr->addToCurrentPresets(preset);
}
