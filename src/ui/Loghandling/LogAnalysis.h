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
 * @file LogAnalysis.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @author Michael Carpenter <malcom2073@gmail.com>
 * @date 17 Mrz 2017
 * @brief File providing header for the log analysing classes
 */
/* *
 * @file LogAnalysis.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @author Michael Carpenter <malcom2073@gmail.com>
 * @date 17 Mrz 2017
 * @brief 로그 분석 클래스 용 헤더 제공 파일
 */

#ifndef LOGANALYSIS_HPP
#define LOGANALYSIS_HPP

#include <QObject>
#include <QWidget>
#include <QScopedPointer>
#include <QMap>
#include <QString>
#include <QStringList>

#include "qcustomplot.h"

#include "LogdataStorage.h"
#include "AP2DataPlotThread.h"
#include "AP2DataPlotStatus.h"
#include "AP2DataPlotAxisDialog.h"
#include "ui_LogAnalysis.h"
#include "PresetManager.h"

/**
 * @brief The LogAnalysisCursor class defines a cursor line (vertical selectable, movable line in plot).
 *        It supports 3 types of cursors:
 *        @li simple - One cursor in plot, emits newCursorPos() signal on end of dragging.
 *        @li left / right - Two cursors in plot, right can not be dragged over left and left can not be
 *                           dragged over right. Whenever one of them is dragged it emits cursorRangeChange()
 *                           signal on end of dragging. Used to mark a range.
 */
/* *
 * @brief LogAnalysisCursor 클래스는 커서 선 (수직 선택 가능, 플롯의 이동 가능한 선)을 정의합니다.
 * 3 가지 유형의 커서를 지원합니다.
 * @li simple - 하나의 커서가 플롯에서 드래그가 끝나면 newCursorPos () 신호를 내 보냅니다.
 * @ 왼쪽 / 오른쪽 - 플롯의 두 커서는 왼쪽이나 왼쪽으로 드래그 할 수 없습니다.
* 오른쪽 위로 드래그. 그 중 하나가 드래그 될 때마다 cursorRangeChange ()
* 끌기가 끝나면 신호. 범위를 표시하는 데 사용됩니다.
 */
class LogAnalysisCursor : public QCPItemStraightLine
{
    Q_OBJECT

public:
    /**
     * @brief The CursorType enum defines the cursor type. Simple has no restrictions,
     *        left and right hold their position. left is always left and right is always right.
     */
    /* *
     * @brief CursorType 열거 형은 커서 유형을 정의합니다. Simple에는 제한이 없습니다.
     * 왼쪽 및 오른쪽으로 자신의 위치를 ​​잡아라. 왼쪽은 항상 왼쪽이고 오른쪽은 항상 옳다.
     */
    enum CursorType
    {
        simple,     /// Simple cursor - one cursor in plot// / 단순 커서 - 플롯에서 하나의 커서
        left,       /// Range cursor - two cursors in plot - the left one// / 범위 커서 - 플롯의 두 커서 - 왼쪽 커서
        right       /// Range cursor - two cursors in plot - the right one// / 범위 커서 - 플롯의 두 커서 - 오른쪽 커서
    };

    /**
     * @brief LogAnalysisCursor - CTOR.
     * @param parentPlot - Pointer to parent QCustomPlot instance, which takes the ownership.
     * @param xPosition - Position on x axis where cursor shall be created.
     * @param type - One of the 3 possible cursor type (simple, left, right).
     */
    /* *
     * @brief LogAnalysisCursor - CTOR.
     * @param parentPlot - 소유권을 가지는 부모 QCustomPlot 인스턴스에 대한 포인터입니다.
     * @param xPosition - 커서가 생성되어야하는 x 축상의 위치.
     * @param type - 3 개의 가능한 커서 형 (단순, 좌, 우) 중 하나.
     */
    explicit LogAnalysisCursor(QCustomPlot *parentPlot, double xPosition, CursorType type);

    /**
     * @brief ~LogAnalysisCursor - DTOR
     */
    virtual ~LogAnalysisCursor();

    /**
     * @brief setOtherCursor - Used to set the the other cursor when using cursors of type left
     *                         or right. The pointer is needed to fetch the positon of the other
     *                         cursor to avoid dragging over each other.
     * @param pCursor - Pointer to the other cursor.
     */
    /* *
     * @brief setOtherCursor - left 타입의 커서를 사용할 때 다른 커서를 설정하는 데 사용됩니다.
     * 또는 오른쪽. 포인터는 다른 포인터의 위치를 ​​가져 오는 데 필요합니다.
     * 커서를 서로 드래그하지 마십시오.
     * @param p 커서 - 다른 커서의 포인터.
     */
    virtual void setOtherCursor(LogAnalysisCursor *pCursor);

    /**
     * @brief getCurrentXPos - returns the current position on x axis of the cursor.
     * @return - Current position on x axis.
     */
    /* *
     * @brief getCurrentXPos - 커서의 x 축상의 현재 위치를 반환합니다.
     * @return - x 축의 현재 위치
     */

    virtual double getCurrentXPos() const;

    /**
     * @brief setCurrentXPos - Sets the positon of the cursor on the x axis.
     * @param xPosition - X pos to move the cursor to.
     */
    /* *
     * @brief setCurrentXPos - x 축에 커서의 위치를 ​​설정합니다.
     * @param xPosition - 커서를 이동시키는 X pos.
     */
    virtual void setCurrentXPos(double xPosition);

signals:
    /**
     * @brief newCursorPos - Signal emitted by a "simple" cursor at the end of dragging it somewhere.
     * @param xPosition - The new positon the cursor is dragged to.
     */
    /* *
     * @brief newCursorPos - 어딘가에 끌기의 끝에 "간단한"커서에 의해 방출되는 신호.
     xPosition - 커서가 드래그되는 새로운 위치.
     */
    void newCursorPos(double xPosition);

    /**
     * @brief rangeCursorMoving - Signal is emitted while one of the range cursors is moved by the user
     * @param xPosition - the new position of the cursor
     */
    /* *
     * @brief rangeCursorMoving - 범위 커서 중 하나가 사용자에 의해 이동되는 동안 신호가 방출됩니다.
     xPosition - 커서의 새로운 위치
     */
    void rangeCursorMoving();

    /**
     * @brief cursorRangeChange - Signal emitted by a cursor pair at the end of dragging one of them to
     *                            a new position.
     */
    /* *
     * @brief cursorRangeChange - 커서 쌍 중 하나를 드래그 한 끝에 커서 쌍이 내 보낸 신호
     * 새로운 위치.
     */
    void cursorRangeChange();

protected:
    // Methods which could be overwritten - not used at the moment
    // virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged);
    // virtual void deselectEvent(bool *selectionStateChanged);
    // virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details = 0)	const;

    // Used methods - See QCustomPlot::QCPItemStraightLine for further description
    // 사용 된 메소드 - 자세한 설명은 QCustomPlot :: QCPItemStraightLine을 참조하십시오.
    virtual void mousePressEvent(QMouseEvent *event, const QVariant &details);
    virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos);
    virtual void mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details);
    virtual void wheelEvent(QWheelEvent *event);

private:
    double m_currentPos;                    /// Current cursor position on x axis// / x 축상의 현재 커서 위치
    double m_otherCursorPos;                /// Position of the other cursor when using range cursors.// 범위 커서를 사용할 때 다른 커서의 위치.
    CursorType m_type;                      /// Type of the cursor// / 커서 유형
    QCPItemStraightLine *mp_otherCursor;    /// Pointer to the other cursor when using range cursors.// 범위 커서를 사용할 때 다른 커서에 대한 포인터.
};

//************************************************************************************************************

/**
 * @brief The LogAnalysisAxis class is a QCPAxis which implements the wheelEvent() method. All y axis in a
 *        plot are of this type to allow proper mouse wheel scaling if selected
 */
/* *
* @brief LogAnalysisAxis 클래스는 wheelEvent () 메소드를 구현하는 QCPAxis입니다. 모든 y 축
 * 플롯은 마우스 휠을 적절하게 조정할 수 있도록하는이 유형의 플롯입니다.
 */
class LogAnalysisAxis : public QCPAxis
{
public:
    /**
     * @brief LogAnalysisAxis - CTOR
     * @param axisRect - Pointer to the AxisRect where the axis shall reside.
     * @param type - Type of the axis
     */
    /* *
     * @brief LogAnalysisAxis - CTOR
     * @param axisRect - 축이 존재하는 AxisRect의 포인터.
     파라미터 : type - 축의 종류
     */
    explicit LogAnalysisAxis(QCPAxisRect *axisRect, AxisType type);

    /**
     * @brief ~LogAnalysisAxis - DTOR
     */
    virtual ~LogAnalysisAxis();

    /**
     * @brief wheelEvent handler for mouse wheel events over this axis
     * @param event - the wheel event
     */
    /* *
     이 축상의 마우스 휠 이벤트의 휠처 핸들러
     * @param event - 휠 이벤트
     */
    virtual void wheelEvent(QWheelEvent *event);
};


//************************************************************************************************************

/**
 * @brief The LogAnalysis class provides everything which is needed for offline log analysis. After a call
 *        to loadLog it opens and parses the log, stores it in a datastorage and opens a GraphView window
 *        where several data analysis can be done.
 */
/* *
* @brief LogAnalysis 클래스는 오프라인 로그 분석에 필요한 모든 것을 제공합니다. 전화 후
 *로드하려면 LogLog는 열리고 로그를 분석하여 데이터 저장소에 저장하고 GraphView 창을 엽니 다.
 * 여러 데이터 분석이 가능한 곳.
 */
class LogAnalysis : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief LogAnalysis - CTOR
     * @param parent - parent object
     */
    /* *
     * @brief LogAnalysis - CTOR
     * @param parent - 부모 객체
     */
    explicit LogAnalysis(QWidget *parent = 0);

    /**
     * @brief LogAnalysis - DTOR
     *
     */
    ~LogAnalysis();

    /**
     * @brief loadLog - starts the logloading and parsing. After successful loading a new window is opened
     *                  where the data can be plotted and analyzed.
     * @param filename - filename of the log to load
     */
    /* *
     * @brief loadLog - 로그 로딩과 파싱을 시작합니다. 로드가 완료되면 새 창이 열립니다.
     * 데이터를 플롯하고 분석 할 수 있습니다.
     * @param filename -로드하는 로그의 파일명
     */
    void loadLog(QString filename);

public slots:
    /**
     * @brief setTablePos - scrolls the table view to the measurement which conatins the measures referred by
     *                      xPosition, which is normally a position in the plotting window.
     * @param xPosition - Position to scroll to. Uses time or index dependent of the m_useTimeOnXAxis setting.
     */
    /* *
     * @brief setTablePos - 테이블 뷰를 참조 된 측정 값과 일치하는 측정 값으로 스크롤합니다.
     * x 위치, 보통 플로팅 윈도우의 위치입니다.
     * @param xPosition - 스크롤 할 위치입니다. m_useTimeOnXAxis 설정의 시간 또는 인덱스 종속성을 사용합니다.
     */
    void setTablePos(double xPosition);

    /**
     * @brief rangeCursorsMoving - calculates the m_cursorXAxisRange. Used to update the range delta while
     *                             moving the cursors.
     */
    /* *
     * @brief rangeCursorsMoving - m_cursorXAxisRange를 계산합니다. 범위 델타를 업데이트하는 데 사용됩니다.
     * 커서 이동.
     */
    void rangeCursorsMoving();

    /**
     * @brief cursorRangeChange - should be called if the cursors change the range. It calculates additional
     *                            values like min/max/average for all visible graphs within the cursor range.
     */
    /* *
     * @brief cursorRangeChange - 커서가 범위를 변경하는 경우 호출해야합니다. 추가로
     * 커서 범위 내의 모든 보이는 그래프에 대한 최소 / 최대 / 평균 값.
     */
    void cursorRangeChange();

private:

    static const QString s_CursorLayerName;     /// Name for the cursor layer// 커서 레이어의 이름

    static const int s_ROW_HEIGHT_PADDING = 3;  /// Number of additional pixels over font height for each row for the table view.// / 테이블 뷰의 각 행에 대한 글꼴 높이에 대한 추가 픽셀 수입니다.
    static const int s_TextArrowPositions = 12;  /// Max number of different positions for the test arrows// 테스트 화살표에 대한 서로 다른 위치의 최대 수

    /**
     * @brief The GraphElements struct holds all needed information about an active graph
     */
    /* *
     * @brief GraphElements 구조체는 활성 그래프에 대한 모든 필요한 정보를 담고있다.
     */
    struct GraphElements
    {
        QCPAxis  *p_yAxis;     /// pointer to the y-Axis of this graph// 이 그래프의 y 축에 대한 포인터
        QCPGraph *p_graph;     /// pointer to the graph itself// 그래프 자체에 대한 포인터
        QString m_groupName;   /// name of the group the plot belongs to.// 플롯이 속한 그룹의 이름.
        bool m_manualRange;    /// has user defined scaling// / 사용자가 정의한 배율을가집니다.
        bool m_inGroup;        /// has group scaling// / 그룹 확장

        GraphElements() : p_yAxis(0), p_graph(0), m_manualRange(false), m_inGroup(false) {}
    };

    /**
     * @brief The GroupElement struct is used for graph grouping. It holds the group name its range and a list of
     *        graph names which are in this group.
     */
    /* *
     * @brief GroupElement 구조체는 그래프 그룹화에 사용됩니다. 그룹 이름의 범위와 목록을 보유하고 있습니다.
     *이 그룹에있는 그래프 이름.
     */
    struct GroupElement
    {
        QString m_groupName;        /// group name// / 그룹 이름
        double m_lower;             /// lower range value// / 낮은 범위 값
        double m_upper;             /// upper range value// / 위쪽 범위 값
        QStringList m_graphList;    /// list of graph names beloging to this group// 이 그룹에 속하는 그래프 이름 목록

        GroupElement() : m_lower(std::numeric_limits<double>::max()), m_upper(m_lower * -1) {}
    };

    /**
     * @brief The RangeValues struct stores all additiona values calculated by cursorRangeChanged() method.
     */
    /* *
     * @brief RangeValues ​​구조체는 cursorRangeChanged () 메소드로 계산 된 모든 추가 값을 저장합니다.
     */
    struct RangeValues
    {
        double m_min;           /// Min value in range// 범위의 최소값
        double m_max;           /// Max value in range// 범위의 최대 값
        double m_average;       /// Average value in range// 범위의 평균값
        int    m_measurements;  /// Number of measurements in range// 범위 내의 측정 수

        RangeValues() : m_min(std::numeric_limits<double>::max()), m_max(m_min * -1), m_average(0.0), m_measurements(0) {}
    };

    typedef QMap<QString, QStringList> fmtMapType;          /// type for handling fmt values from datamodel// 데이터 모델에서 fmt 값을 처리하기위한 유형
    typedef QHash<QString, GraphElements> activeGraphType;  /// type for handling active graph container// 활성 그래프 컨테이너를 처리하기위한 타입



    Ui::LogAnalysis ui;     /// The user interface// / 사용자 인터페이스

    QScopedPointer<QCustomPlot>  m_plotPtr;            /// Scoped pointer to QCustomplot // QCustomplot에 범위가 지정된 포인터
    LogdataStorage::Ptr          m_dataStoragePtr;     /// Shared pointer to data storage// 데이터 저장소에 대한 공유 포인터

    QScopedPointer<QMenuBar, QScopedPointerDeleteLater> m_menuBarPtr;        /// Scoped pointer to the menu bar// / 메뉴 바에 스코프 된 포인터
    QScopedPointer<PresetManager, QScopedPointerDeleteLater> m_presetMgrPtr; /// Scoped pointer to the preset manager// 미리 설정된 관리자에 대한 범위가 지정된 포인터


    QScopedPointer<AP2DataPlotThread, QScopedPointerDeleteLater> m_loaderThreadPtr;        /// Scoped pointer to AP2DataPlotThread// / AP2DataPlotThread에 대한 범위 포인터
    QScopedPointer<QProgressDialog, QScopedPointerDeleteLater>   m_loadProgressDialog;     /// Scoped pointer to load progress window// 진행률 창을로드 할 범위가 지정된 포인터
    QScopedPointer<AP2DataPlotAxisDialog, QScopedPointerDeleteLater> m_axisGroupingDialog; /// Scoped pointer to axis grouping dialog// 축 그룹화 대화 상자에 대한 범위 지정 포인터

    activeGraphType m_activeGraphs;                         /// Holds all active graphs// 모든 활성 그래프를 유지합니다.
    QHash<QString, RangeValues> m_rangeValuesStorage;       /// If there is a range cursor the range values are stored here.// 범위 커서가 있으면 범위 값이 여기에 저장됩니다.
    QMap<quint64, MessageBase::Ptr> m_indexToMessageMap;    /// Map holding all Messages which are printed as arrows// 화살표로 인쇄 된 모든 메시지 보유 맵
    GraphElements m_arrowGraph;                             /// The text arrows have an own graph// / 텍스트 화살표에는 그래프가 있습니다.

    QStringList m_tableFilterList;   /// Used to create regex filter pattern for table view.// 테이블 뷰를위한 regex 필터 패턴을 만드는 데 사용됩니다.

    QSortFilterProxyModel *mp_tableFilterProxyModel;    /// Filter model for table view.// / 테이블 뷰의 필터 모델.

    QString m_filename;              /// Filename of the loaded Log - mainly used for export// 로드 된 로그의 파일 이름 - 주로 내보내기에 사용됩니다.

    MAV_TYPE m_loadedLogMavType;     /// Holds the mav type of the loaded log// 로드 된 로그의 mav 유형을 보유합니다.

    bool m_useTimeOnXAxis;           /// true if x axis holds time values // x 축에 시간 값이있는 경우 true입니다.
    qint64 m_scrollStartIndex;       /// Current start index of the loaded log// 로드 된 로그의 현재 시작 인덱스
    qint64 m_scrollEndIndex;         /// Current end index of the loaded log // 로드 된 로그의 현재 끝 인덱스
    int    m_statusTextPos;          /// Counter for giving text arrows a different length// 다른 길이의 화살표를주는 카운터
    int m_lastHorizontalScrollVal;   /// Stores the last value of the horizontal scroller/ / 가로 스크롤러의 마지막 값을 저장합니다.

    double m_cursorXAxisRange;       /// X axis range of the cursors.// 커서의 X 축 범위.

    LogAnalysisCursor *mp_cursorSimple;     /// Pointer to the simple cursor only valid if visible // 단순한 커서에 대한 포인터 (보이는 경우에만 유효 함)
    LogAnalysisCursor *mp_cursorLeft;       /// Pointer to the left cursor only valid if visible// / 보이는 경우에만 유효한 왼쪽 커서 포인터
    LogAnalysisCursor *mp_cursorRight;      /// Pointer to the right cursor only valid if visible// 오른쪽 커서에 대한 포인터는 보이는 경우에만 유효합니다.

    /**
     * @brief setupXAxisAndScroller sets up x axis and the horizontal scroller
     *        to use the normal index (the artifical) or the time index regarding
     *        to the value of m_useTimeOnXAxis.
     */
    /* *
     * @brief setupXAxisAndScroller는 x 축과 수평 스크롤러를 설정합니다.
     * 정상적인 색인 (artifical) 또는 시간 색인에 관한 사용
     *를 m_useTimeOnXAxis의 값으로 설정합니다.
     */
    void setupXAxisAndScroller();

    /**
     * @brief insertTextArrows inserts messages stored in m_indexToMessageMap
     *        as text arrows into the graph
     *        Uses normal or time index regarding of the value of m_useTimeOnX
     */
    /* *
     * @brief insertTextArrows는 m_indexToMessageMap에 저장된 메시지를 삽입합니다.
     * 텍스트 화살표로 그래프에 삽입
     * m_useTimeOnX 값과 관련하여 표준 또는 시간 인덱스를 사용합니다.
     */
    void insertTextArrows();

    /**
     * @brief plotTextArrow - plots a text arrow into the Graph
     * @param index - position on x axis
     * @param text - the text which shall be printed above the arrow
     * @param layerName - name of the layer the arrow shall be plotted into
     * @param color - the color of the arrow and its text
     */
    /* *
     * @brief plotTextArrow - 그래프에 텍스트 화살표를 그립니다.
     * @param index - x 축상의 위치
     * @param text - 화살표 위에 인쇄되는 텍스트
     * @param layerName - 화살표가 그려지는 레이어의 이름
     * @param color - 화살표와 텍스트의 색
     */
    void plotTextArrow(double index, const QString &text, const QString &layerName, const QColor &color);

    /**
     * @brief This method disables the filtering of m_tableFilterProxyModel
     *        After a call the table model will show all rows again.
     */
    /* *
     * @brief이 메소드는, m_tableFilterProxyModel의 필터링을 무효로합니다.
     * 호출 후 테이블 모델은 모든 행을 다시 표시합니다.
     */
    void disableTableFilter();

    /**
     * @brief loadSettings - loads the settings for the log analysis window.
     *                       At the moment this means the state of the checkboxes
     */
    /* *
     * @briefloadSettings - 로그 분석 창에 대한 설정을로드합니다.
     * 현재 체크 박스의 상태를 의미합니다.
     */
    void loadSettings();

    /**
     * @brief saveSettings - saves the settings for the log analysis window.
     *                       At the moment this means the state of the checkboxes
     */
    /* *
     * @brief saveSettings - 로그 분석 창에 대한 설정을 저장합니다.
     * 현재 체크 박스의 상태를 의미합니다.
     */
    void saveSettings();

    /**
     * @brief presetToRangeConverter - Converts a presetElementVec to a list of graph ranges
     *        making it possible to use the graphGroupingChanged() method to apply a preset.
     *        Moreover this method also sets the colors of the graph as stored in the presets.
     * @param preset - the preset vector containing the preset data
     * @return - a GraphRange list wich can be given to graphGroupingChanged() method.
     */
    /* *
     * @brief presetToRangeConverter - 사전 설정된 요소 Vec를 그래프 범위 목록으로 변환합니다.
     * graphGroupingChanged () 메서드를 사용하여 사전 설정을 적용 할 수 있습니다.
     * 또한이 방법은 프리셋에 저장된 그래프의 색상을 설정합니다.
     파라미터 : preset - 프리셋 데이터를 포함한 프리 세트 벡터
     * @return - graphGroupingChanged () 메소드에 지정할 수있는 GraphRange리스트.
     */
    QList<AP2DataPlotAxisDialog::GraphRange> presetToRangeConverter(const PresetManager::presetElementVec &preset);

private slots:

    /**
     * @brief hideTableView - hides / shows the table view
     * @param hide - true: hide table view, flase: show table view
     */
    /* *
     * @brief hideTableView - 테이블보기를 숨기거나 보여줍니다.
     * @param hide - true : 테이블 뷰를 숨 깁니다. flase : 테이블 뷰를 표시합니다.
     */
    void hideTableView(bool hide);

    /**
     * @brief showValueUnderMouseClicked - handles the clicked signal of the "show vaules under mouse"
     *        checkbox. Connects / disconnects the mouse moved signal of qCustomPlot.
     * @param checked - reflects the state of the checkbox.
     */
    /* *
     * @brief showValueUnderMouseClicked - "마우스 아래에 vaules 보여주기"의 클릭 신호를 처리합니다.
     * 확인란. qCustomPlot의 마우스 이동 신호를 연결 / 연결 해제합니다.
     * @param checked - 체크 박스의 상태를 반영합니다.
     */

    void showValueUnderMouseClicked(bool checked);

    /**
     * @brief logLoadingStarted - creates the Progress window
     */
    /* *
     * @brief logLoadingStarted - 진행 창을 만듭니다.
     */
    void logLoadingStarted();

    /**
     * @brief logLoadingProgress - sets the progressbar to actual
     *        loading position.
     * @param pos - Position of log loading.
     * @param size - Size of data to be loaded.
     */
    /* *
     * @brief logLoadingProgress - 진행률 막대를 실제 값으로 설정합니다.
     * 적재 자세.
     * @param pos - 로그로드의 위치.
     파라미터 : size -로드되는 데이터의 사이즈
     */
    void logLoadingProgress(qint64 pos, qint64 size);

    /**
     * @brief logLoadingError - to be called on loag loading error.
     *        logs the "errorstr" to log and opens an Info dialog.
     * @param errorstr - The error string to be printed.
     */
    /* *
     * @brief logLoadingError - 로깅로드 오류에서 호출됩니다.
     *는 "errorstr"을 기록하여 기록하고 정보 대화 상자를 엽니 다.
     * @param errorstr - 인쇄되는 에러 캐릭터 라인
     */
    void logLoadingError(QString errorstr);

    /**
     * @brief logLoadingDone - does the basic setup after a successful
     *        log loading. It analyzes the AP2DataPlotStatus and shows an
     *        info box if neede. Moreover it populates all initial filled
     *        datafields (like table or filter view) and connects their signals.
     * @param status - status of the parsing.
     */
    /* *
     * @brief logLoadingDone - 성공 후 기본 설정을 수행합니다.
     * 로그로드. AP2DataPlotStatus를 분석하여
     * 정보 상자가 필요한 경우. 또한 모든 초기 채우기
     * datafields (테이블 또는 필터보기와 같은) 및 해당 신호를 연결합니다.
     * @param status - 파싱의 상태.
     */
    void logLoadingDone(AP2DataPlotStatus status);

    /**
     * @brief logLoadingThreadTerminated - shall be called as soon as the log loading
     *        thread terminates. Resets the pointer to the thread object.
     */
   /* *
     * @brief logLoadingThreadTerminated - 로그로드가 끝나자 마자 호출됩니다.
     * 스레드가 종료됩니다. 포인터를 스레드 객체에 다시 설정합니다.
     */
    void logLoadingThreadTerminated();

    /**
     * @brief logLoadingProgressDialogCanceled - should be called if someone presses
     *        cancle in the progress dialog. Stops the Logloading.
     */
    /* *
     * @brief logLoadingProgressDialogCanceled - 누군가가 누를 경우 호출되어야합니다.
     진행 대화 상자에서 * cancle. 로그로드를 중지합니다.
     */
    void logLoadingProgressDialogCanceled();

    /**
     * @brief modeCheckboxClicked - to be called if someone clicks the Mode checkbox
     * @param checked - true if checked, false otherwise
     */
    /* *
     * @brief modeCheckboxClicked - 누군가가 Mode 체크 박스를 클릭하면 호출됩니다.
     * @param checked - 체크하면 true, 그렇지 않으면 false
     */
    void modeCheckboxClicked(bool checked);

    /**
     * @brief errorCheckboxClicked - @see modeCheckboxClicked(bool checked)
     */
    /* *
     * @brief errorCheckboxClicked - @see modeCheckboxClicked (bool 선택)
     */
    void errorCheckboxClicked(bool checked);

    /**
     * @brief eventCheckboxClicked - @see modeCheckboxClicked(bool checked)
     */
    /* *
     * @brief eventCheckboxClicked - @see modeCheckboxClicked (bool 체크)
     */
    void eventCheckboxClicked(bool checked);

    /**
     * @brief msgCheckboxClicked - @see modeCheckboxClicked(bool checked)
     */
    /* *
     * @brief msgCheckboxClicked - @see modeCheckboxClicked (bool 선택)
     */
    void msgCheckboxClicked(bool checked);

    /**
     * @brief verticalScrollMoved - to be called if someone moves the vertical
     *        scroller.
     * @param value - the new value of the scroller
     */
    /* *
     * @brief verticalScrollMoved - 누군가가 수직을 움직이면 호출됩니다.
     * 스크롤러.
     * @param value - 스크롤러의 새로운 값
     */
    void verticalScrollMoved(int value);

    /**
     * @brief horizontalScrollMoved - @see verticalScrollMoved(int value)
     */
    /* *
     * @brief horizontalScrollMoved - @see verticalScrollMoved (int 값)
     */
    void horizontalScrollMoved(int value);

    /**
     * @brief xAxisChanged - should be called whenever the x axis of the plot changes
     * @param range - visible range of x axis
     */
   /* *
     * @brief xAxisChanged - 플롯의 x 축이 변경 될 때마다 호출되어야합니다
     * @param 범위 - x 축의 가시 범위
     */
    void xAxisChanged(QCPRange range);

    /**
     * @brief itemEnabled - adds the item graph named "name" to the plot area.
     * @param name - the name of the data to be plotted.
     */
    /* *
     * @brief itemEnabled - "name"이라는 항목 그래프를 플롯 영역에 추가합니다.
     파라미터 : name - 그릴 데이터의 이름.
     */
    void itemEnabled(QString name);

    /**
     * @brief itemDisabled - removes the item graph named "name" from plot area
     * @param name - the name of the item to be removed
     */
    /* *
     * @brief itemDisabled - 플롯 영역에서 "name"이라는 항목 그래프를 제거합니다.
     파라미터 : name - 삭제되는 아이템의 이름 예외 :
     */
    void itemDisabled(QString name);

    /**
     * @brief indexTypeCheckBoxClicked - shall be called when the "use time on x-axis" checkbox
     *        is pressed. It changes the x axis scaling from index to time
     * @param checked - true checkbox is checked, false otherwise.
     */
    /* *
     * @brief indexTypeCheckBoxClicked - "x 축에 시간 사용"체크 박스가 호출 될 때 호출됩니다.
     *를 누르십시오. x 축 스케일링을 인덱스에서 시간으로 변경합니다.
     * @param checked - true 체크 박스가 체크 된 경우는 false, 그렇지 않은 경우는 false
     */
    void indexTypeCheckBoxClicked(bool checked);

    /**
     * @brief filterItemChanged - adds or removes names from the filterlist. Shall be called
     *        whenever a check box is checked or unchecked in the sorting dialog.
     * @param item - the Item that was checked / unchecked
     * @param col - ignored
     */
    /* *
     * @brief filterItemChanged - 필터 목록에 이름을 추가하거나 제거합니다. 전화해야한다.
     * 정렬 대화 상자에서 확인란을 선택하거나 선택 취소 할 때마다
     파라미터 : item - 체크 된 항목 또는 체크되지 않았던 항목
     * @param col - 무시된다
     */
    void filterItemChanged(QTreeWidgetItem* item,int col);

    /**
     * @brief filterAcceptClicked - sets the new filter for the table view.
     */
    /* *
     * @ brief filterAcceptClicked - 테이블 뷰에 대한 새 필터를 설정합니다.
     */
    void filterAcceptClicked();

    /**
     * @brief filterCancelClicked - just hides the filter dialog.
     */
    /* *
     * @brief filterCancelClicked - 필터 대화 상자를 숨 깁니다.
     */
    void filterCancelClicked();

    /**
     * @brief showFilterButtonClicked - opens / closes the filter dialog
     */
    /* *
     * @brief showFilterButtonClicked - 필터 대화 상자를 열고 닫습니다.
     */
    void showFilterButtonClicked();

    /**
     * @brief filterSelectAllClicked - set all items checked in the filter dialog
     */
    /* *
     * @brief filterSelectAllClicked - 필터 대화 상자에서 체크 된 모든 항목을 설정합니다.
     */
    void filterSelectAllClicked();

    /**
     * @brief filterSelectInvertClicked - inverts the selection in the filter dialog
     */
    /* *
     * @brief filterSelectInvertClicked - 필터 대화 상자에서 선택 항목을 반전합니다.
     */
    void filterSelectInvertClicked();

    /**
     * @brief selectedRowChanged - tells the datamodel that the active row in table model
     *        has changed. Used to update the table header (show correct colum names) and
     *        the position of the simple cursor if present
     * @param current - the current row which is selected in table model
     * @param previous - unused
     */
    /* *
     * @brief selectedRowChanged - 테이블 모델의 활성 행을 데이터 모델에 알립니다.
     * 변경되었습니다. 테이블 헤더를 업데이트하는 데 사용됩니다 (올바른 열 이름 표시).
     * 존재하는 경우 단순 커서의 위치
     파라미터 : current - 테이블 모델로 선택되고있는 현재의 행
     이전의 @param - 미사용
     */
    void selectedRowChanged(QModelIndex current, QModelIndex previous);

    /**
     * @brief exportTlogClicked - starts an ASCII log export, csv style
     */
    /* *
     * @brief exportTlogClicked - ASCII 로그 내보내기, CSV 스타일 시작
     */
    void exportAsciiLogClicked();

    /**
     * @brief exportKmlClicked - starts a KML log export, google earth
     */
    /* *
     * @ brief 수출 KmlClicked - KML 로그 내보내기를 시작합니다. Google 어스
     */
    void exportKmlClicked();

    /**
     * @brief doExport - Starts an export eg. opens the file dialog to select
     *        the path to export to.
     * @param kmlExport  @li true - do KML Export (google earth)
     *                   @li false - do ascii export (simple ascii log, csv style)
     * @param iconInterval - only used by KML/KMZ export. Defines the minimum kml
     *                       plane icon interval in meters
     */
    /* *
     * @brief doExport - 내보내기를 시작합니다. 선택할 파일 대화 상자를 엽니 다.
     * 내보낼 경로.
     * @param kmlExport @li true - KML 내보내기 수행 (Google 어스)
     * @li 거짓 - ascii 내보내기 (간단한 아스키 로그, CSV 스타일)
     * @param iconInterval - KML / KMZ 내보내기에서만 사용됩니다. 최소 kml을 정의합니다.
     * 비행기 아이콘 간격 (미터)
     */
    void doExport(bool kmlExport, double iconInterval);

    /**
     * @brief graphControlsButtonClicked - opens the plot grouping dialog and sends
     *        the current group settings to the grouping dialog.
     */
    /* *
     * @brief graphControlsButtonClicked - 플롯 그룹화 대화 상자를 열고 보내기
     * 그룹화 대화 상자에 대한 현재 그룹 설정.
     */
    void graphControlsButtonClicked();

    /**
     * @brief graphGroupingChanged - handles the graphGroupingChanged() signal of the
     *        gouping dialog. It sets the scaling and grouping of all plots.
     * @param graphRangeList - the List of graphs with their scaling and grouping.
     */
    /* *
     * @brief graphGroupingChanged - ()의 graphGroupingChanged () 신호를 처리합니다.
     * gouping 대화 상자. 모든 플롯의 비율 및 그룹화를 설정합니다.
     * @param graphRangeList - 그래프의 스케일 및 그룹화의리스트.
     */
    void graphGroupingChanged(QList<AP2DataPlotAxisDialog::GraphRange> graphRangeList);

    /**
     * @brief graphColorsChanged - handles the graphColorsChanged() signal from the grouping
     *        dialog.
     * @param colorlist - map of graph names and their colors.
     */
    /* *
     * @brief graphColorsChanged - 그룹에서 graphColorsChanged () 신호를 처리합니다.
     * 대화 상자.
     * @param colorlist - 그래프 명과 그 색의 맵.
     */
    void graphColorsChanged(QMap<QString,QColor> colorlist);

    /**
     * @brief contextMenuRequest - handles the customContextMenuRequested() signal from
     *        qCustomPlot on right click. It handles the cursor enabling/disabling.
     * @param pos - Pos where the context menu opens. Used to place the cursors initially.
     */
    /* *
     * @brief contextMenuRequest -에서 customContextMenuRequested () 신호를 처리합니다.
     * qCustomPlot을 마우스 오른쪽 버튼으로 클릭하십시오. 그것은 커서의 활성화 / 비활성화를 처리합니다.
     * @param pos - 컨텍스트 메뉴가 열리는 Pos입니다. 커서를 처음에 배치하는 데 사용됩니다.
     */
    void contextMenuRequest(QPoint pos);

    /**
     * @brief insertSimpleCursor - paints the simple cursor and connects the required signals.
     */
    /* *
     * @brief insertSimpleCursor - 간단한 커서를 칠하고 필요한 신호를 연결합니다.
     */
    void insertSimpleCursor();

    /**
     * @brief insertRangeCursors - paints the range cursors and connects the required signals.
     */
    /* *
     * @brief insertRangeCursors - 범위 커서를 칠하고 필요한 신호를 연결합니다.
     */
    void insertRangeCursors();

    /**
     * @brief removeSimpleCursor - removes the simple cursor from graph.
     */
    /* *
     * @brief removeSimpleCursor - 그래프에서 간단한 커서를 제거합니다.
     */
    void removeSimpleCursor();

    /**
     * @brief removeSimpleCursor - removes the range cursors from graph.
     */
    /* *
     * @brief removeSimpleCursor - 그래프에서 범위 커서를 제거합니다.
     */
    void removeRangeCursors();

    /**
     * @brief plotMouseMove - handles the mousMove signal of qCustomPlot. It shows a tooltip
     *        with several measurements.
     * @param evt - the mouse event.
     */
    /* *
     * @brief plotMouseMove - qCustomPlot의 mousMove 신호를 처리합니다. 툴팁을 보여줍니다.
     * 여러 번 측정.
     * @param evt - 마우스 이벤트.
     */
    void plotMouseMove(QMouseEvent *evt);

    /**
     * @brief resetValueScaling - resets the scaling of the graph it it were changed by
     *        mouse.
     */
    /* *
     * @ brief 리셋 값 스케일링 - 변경된 그래프의 스케일을 리셋합니다.
     * 쥐.
     */
    void resetValueScaling();

    /**
     * @brief enableRangeCursor - handles the range cursor checkbox click signal
     * @param enable - true checkbox is checked, false unchecked
     */
    /* *
     * @brief enableRangeCursor - 범위 커서 체크 박스 클릭 신호 처리
     파라미터 : enable - true 체크 박스가 체크됩니다. false
     */
    void enableRangeCursor(bool enable);

    /**
     * @brief enableTableCursor - handles the table cursor checkbox click signal
     * @param enable - true checkbox is checked, false unchecked
     */
    /* *
     * @brief enableTableCursor - 테이블 커서 체크 박스 클릭 신호 처리
     파라미터 : enable - true 체크 박스가 체크됩니다. false
     */
    void enableTableCursor(bool enable);

    /**
     * @brief storeGraphSettingsPressed - is called when the store Settings button is pressed.
     *        Stores the active graphs and their settings into ini file.
     */
    /* *
     * @brief storeGraphSettingsPressed - 상점 설정 버튼을 누르면 호출됩니다.
     * 활성 그래프 및 해당 설정을 ini 파일에 저장합니다.
     */
    void storeGraphSettingsPressed();

    /**
     * @brief applyGraphSettingsPressed - is called when the apply settings button is pressed.
     *        Applies the data stored with storeGraphSettingsPressed() to the current LogAnalysis window.
     */
    /* *
     * @brief applyGraphSettingsPressed - 설정 적용 버튼을 누르면 호출됩니다.
     * storeGraphSettingsPressed ()와 함께 저장된 데이터를 현재 LogAnalysis 창에 적용합니다.
     */
    void applyGraphSettingsPressed();

    /**
     * @brief analysisPresetSelected - is called when the preset manager selects a new preset. It does
     *        everything to apply the preset to the graph.
     */
    /* *
     * @brief analysisPresetSelected - 프리셋 관리자가 새 프리셋을 선택할 때 호출됩니다. 그렇습니다
     * 그래프에 프리셋을 적용하기위한 모든 것.
     */
    void analysisPresetSelected(PresetManager::presetElementVec preset);

    /**
     * @brief addCurrentViewToPreset - applies the current graph view to the preset manager
     */
    /* *
     * @brief addCurrentViewToPreset - 현재 그래프 뷰를 프리셋 관리자에 적용합니다.
     */
    void addCurrentViewToPreset();

};

#endif // LOGANALYSIS_HPP

