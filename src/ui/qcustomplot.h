/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2017 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 04.09.17                                             **
**          Version: 2.0.0                                                **
****************************************************************************/
/* ************************************************ **************************
** **
** QCustomPlot, Qt ** 용 최신 플로팅 위젯 사용하기 쉽습니다.
** Copyright (C) 2011-2017 Emanuel Eichhammer **
** **
**이 프로그램은 자유 소프트웨어입니다 : 재배포 및 / 또는 수정 가능 **
** **에 의해 출판 된 GNU General Public License의 조건에 따라 **
** 자유 소프트웨어 재단, 라이센스 버전 3 또는 **
** (귀하의 선택에 따라) 이후 버전. **
** **
**이 프로그램은 유용 할 것이라는 희망으로 배포됩니다 **
** 그러나 어떠한 보증도하지 않습니다. ** 묵시적 보증없이
** 상품성 또는 특정 목적에의 적합성. **
** 자세한 내용은 GNU General Public License를 참조하십시오. **
** **
** GNU 일반 공중 사용 허가서 사본을 받아야합니다 **
**이 프로그램과 함께. 그렇지 않은 경우 http://www.gnu.org/licenses/를 참조하십시오. **
** **
*************************************************** **************************
** 저자 : Emanuel Eichhammer **
** 웹 사이트 / 연락처 : http://www.qcustomplot.com/ **
** 날짜 : 04.09.17 **
** 버전 : 2.0.0 **
*************************************************** ************************* */
#ifndef QCUSTOMPLOT_H
#define QCUSTOMPLOT_H

#include <QtCore/qglobal.h>

// some Qt version/configuration dependent macros to include or exclude certain code paths:
// 특정 코드 경로를 포함하거나 제외시킬 일부 Qt 버전 / 구성 종속 매크로 :
#ifdef QCUSTOMPLOT_USE_OPENGL
#  if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#    define QCP_OPENGL_PBUFFER
#  else
#    define QCP_OPENGL_FBO
#  endif
#  if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
#    define QCP_OPENGL_OFFSCREENSURFACE
#  endif
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
#  define QCP_DEVICEPIXELRATIO_SUPPORTED
#  if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
#    define QCP_DEVICEPIXELRATIO_FLOAT
#  endif
#endif

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QPixmap>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QMultiMap>
#include <QtCore/QFlags>
#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QCache>
#include <QtCore/QMargins>
#include <qmath.h>
#include <limits>
#include <algorithm>
#ifdef QCP_OPENGL_FBO
#  include <QtGui/QOpenGLContext>
#  include <QtGui/QOpenGLFramebufferObject>
#  ifdef QCP_OPENGL_OFFSCREENSURFACE
#    include <QtGui/QOffscreenSurface>
#  else
#    include <QtGui/QWindow>
#  endif
#endif
#ifdef QCP_OPENGL_PBUFFER
#  include <QtOpenGL/QGLPixelBuffer>
#endif
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#  include <qnumeric.h>
#  include <QtGui/QWidget>
#  include <QtGui/QPrinter>
#  include <QtGui/QPrintEngine>
#else
#  include <QtNumeric>
#  include <QtWidgets/QWidget>
#  include <QtPrintSupport/QtPrintSupport>
#endif

class QCPPainter;
class QCustomPlot;
class QCPLayerable;
class QCPLayoutElement;
class QCPLayout;
class QCPAxis;
class QCPAxisRect;
class QCPAxisPainterPrivate;
class QCPAbstractPlottable;
class QCPGraph;
class QCPAbstractItem;
class QCPPlottableInterface1D;
class QCPLegend;
class QCPItemPosition;
class QCPLayer;
class QCPAbstractLegendItem;
class QCPSelectionRect;
class QCPColorMap;
class QCPColorScale;
class QCPBars;

/* including file 'src/global.h', size 16225                                 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / global.h'파일 포함, 크기 16225                                      */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200   */

 
// decl definitions for shared library compilation/usage:
// 공유 라이브러리 컴파일 / 사용에 대한 정의를 선언합니다.
#if defined(QCUSTOMPLOT_COMPILE_LIBRARY)
#  define QCP_LIB_DECL Q_DECL_EXPORT
#elif defined(QCUSTOMPLOT_USE_LIBRARY)
#  define QCP_LIB_DECL Q_DECL_IMPORT
#else
#  define QCP_LIB_DECL
#endif

// define empty macro for Q_DECL_OVERRIDE if it doesn't exist (Qt < 5)
// Q_DECL_OVERRIDE가 존재하지 않으면 빈 매크로를 정의합니다 (Qt <5).
#ifndef Q_DECL_OVERRIDE
#  define Q_DECL_OVERRIDE
#endif

/*!
  The QCP Namespace contains general enums, QFlags and functions used throughout the QCustomPlot
  library.
  
  It provides QMetaObject-based reflection of its enums and flags via \a QCP::staticMetaObject.
*/
/*!
  QCP 네임 스페이스는 QCustomPlot 전체에서 사용되는 일반 열거 형, QFlags 및 함수를 포함합니다
  도서관.
  
  \ QCP :: staticMetaObject를 통해 열거 형과 플래그의 QMetaObject 기반 반영을 제공합니다.
*/
#ifndef Q_MOC_RUN
namespace QCP {
#else
class QCP { // when in moc-run, make it look like a class, so we get Q_GADGET, Q_ENUMS/Q_FLAGS features in namespace
  Q_GADGET  // moc-run 할 때 클래스처럼 보이게 만들면 네임 스페이스에 Q_GADGET, Q_ENUMS / Q_FLAGS 기능이 생깁니다.
  Q_ENUMS(ExportPen)
  Q_ENUMS(ResolutionUnit)
  Q_ENUMS(SignDomain)
  Q_ENUMS(MarginSide)
  Q_FLAGS(MarginSides)
  Q_ENUMS(AntialiasedElement)
  Q_FLAGS(AntialiasedElements)
  Q_ENUMS(PlottingHint)
  Q_FLAGS(PlottingHints)
  Q_ENUMS(Interaction)
  Q_FLAGS(Interactions)
  Q_ENUMS(SelectionRectMode)
  Q_ENUMS(SelectionType)
public:
#endif

/*!
  Defines the different units in which the image resolution can be specified in the export
  functions.

  \see QCustomPlot::savePng, QCustomPlot::saveJpg, QCustomPlot::saveBmp, QCustomPlot::saveRastered
*/
/*!
  내보내기에서 이미지 해상도를 지정할 수있는 여러 단위를 정의합니다.
  기능.
  \ QCustomPlot :: savePng, QCustomPlot :: saveJpg, QCustomPlot :: saveBmp, QCustomPlot :: saveRastered를 참조하십시오.
*/
enum ResolutionUnit { ruDotsPerMeter       ///< Resolution is given in dots per meter (dpm)
                                           /// <해상도는 미터 당 점 (dpm)으로 표시됩니다.
                      ,ruDotsPerCentimeter ///< Resolution is given in dots per centimeter (dpcm)
                                           /// <해상도는 센티미터 당 점 (dpcm)으로 표시됩니다.
                      ,ruDotsPerInch       ///< Resolution is given in dots per inch (DPI/PPI)
                    };                     /// <해상도는 인치당 도트 수 (DPI / PPI)로 표시됩니다.

/*!
  Defines how cosmetic pens (pens with numerical width 0) are handled during export.

  \see QCustomPlot::savePdf
*/
/* !
  엑스포트하는 동안 코스메틱 펜 (숫자 폭 0의 펜)을 처리하는 방법을 정의합니다.
  \ QCustomPlot :: savePdf를 참조하십시오.
*/
enum ExportPen { epNoCosmetic     ///< Cosmetic pens are converted to pens with pixel width 1 when exporting
                                  /// <화장품 펜은 내보낼 때 픽셀 너비가 1 인 펜으로 변환됩니다.
                 ,epAllowCosmetic ///< Cosmetic pens are exported normally (e.g. in PDF exports, cosmetic pens always appear as 1 pixel on screen, independent of viewer zoom level)
                                  /// <화장품 펜이 정상적으로 내보내집니다 (예 : PDF 내보내기에서 화장품 펜은 뷰어 줌 레벨과 관계없이 항상 화면에 1 픽셀로 표시됨)
               };

/*!
  Represents negative and positive sign domain, e.g. for passing to \ref
  QCPAbstractPlottable::getKeyRange and \ref QCPAbstractPlottable::getValueRange.
  
  This is primarily needed when working with logarithmic axis scales, since only one of the sign
  domains can be visible at a time.
*/
/* !
  예를 들어 \ ref에 전달할 때 음수 및 양수 부호 도메인을 나타냅니다.
  QCPAbstractPlottable :: getKeyRange 및 \ ref QCPAbstractPlottable :: getValueRange.
  
  대수 축 스케일로 작업 할 때 주로 필요합니다. 부호 중 하나만
  도메인은 한 번에 볼 수 있습니다.
*/
enum SignDomain { sdNegative  ///< The negative sign domain, i.e. numbers smaller than zero
                              /// <음수 기호 도메인, 즉 0보다 작은 수
                  ,sdBoth     ///< Both sign domains, including zero, i.e. all numbers
                              /// <0을 포함하여 모두 서명 도메인, 즉 모든 숫자
                  ,sdPositive ///< The positive sign domain, i.e. numbers greater than zero
                };            /// <양수 기호 도메인, 즉 0보다 큰 숫자

/*!
  Defines the sides of a rectangular entity to which margins can be applied.
  
  \see QCPLayoutElement::setAutoMargins, QCPAxisRect::setAutoMargins
*/
/* !
  여백을 적용 할 수있는 직사각형 엔티티의 변을 정의합니다.
  
  \ QCPLayoutElement :: setAutoMargins, QCPAxisRect :: setAutoMargins를 참조하십시오.
*/
enum MarginSide { msLeft     = 0x01 ///< <tt>0x01</tt> left margin    //왼쪽 여백
                  ,msRight   = 0x02 ///< <tt>0x02</tt> right margin   //오른쪽 여백
                  ,msTop     = 0x04 ///< <tt>0x04</tt> top margin     //위쪽 여백
                  ,msBottom  = 0x08 ///< <tt>0x08</tt> bottom margin  //하단 여백
                  ,msAll     = 0xFF ///< <tt>0xFF</tt> all margins    //모든 여백
                  ,msNone    = 0x00 ///< <tt>0x00</tt> no margin      //여백 없음
                };
Q_DECLARE_FLAGS(MarginSides, MarginSide)

/*!
  Defines what objects of a plot can be forcibly drawn antialiased/not antialiased. If an object is
  neither forcibly drawn antialiased nor forcibly drawn not antialiased, it is up to the respective
  element how it is drawn. Typically it provides a \a setAntialiased function for this.
  
  \c AntialiasedElements is a flag of or-combined elements of this enum type.
  
  \see QCustomPlot::setAntialiasedElements, QCustomPlot::setNotAntialiasedElements
*/
/* !
  강제로 그릴 수있는 플롯의 객체를 정의합니다. 객체가
  강제로 그린 앤티 엘리 어싱도 강제로 앤티 엘리 어싱하지도 않습니다.
  요소 그려지는 방법. 전형적으로 이것은 setAntialiased 함수를 제공한다.
  
  \ c AntialiasedElements는이 enum 유형의 또는 결합 된 요소의 플래그입니다.
  
  \ QCustomPlot :: setAntialiasedElements, QCustomPlot :: setNotAntialiasedElements를 참조하십시오.
*/
enum AntialiasedElement { aeAxes           = 0x0001 ///< <tt>0x0001</tt> Axis base line and tick marks
                                                    /// 축 기준선 및 눈금
                          ,aeGrid          = 0x0002 ///< <tt>0x0002</tt> Grid lines
                                                    /// 눈금 선
                          ,aeSubGrid       = 0x0004 ///< <tt>0x0004</tt> Sub grid lines
                                                    /// 서브 그리드 선
                          ,aeLegend        = 0x0008 ///< <tt>0x0008</tt> Legend box
                                                    /// 범례 상자
                          ,aeLegendItems   = 0x0010 ///< <tt>0x0010</tt> Legend items
                                                    /// 범례 항목
                          ,aePlottables    = 0x0020 ///< <tt>0x0020</tt> Main lines of plottables
                                                    ///  plottables의 메인 라인
                          ,aeItems         = 0x0040 ///< <tt>0x0040</tt> Main lines of items
                                                    ///  아이템의 메인 라인
                          ,aeScatters      = 0x0080 ///< <tt>0x0080</tt> Scatter symbols of plottables (excluding scatter symbols of type ssPixmap)                           /// plottables의 분산 형 기호 (ssPixmap 유형의 분산 형 기호 제외)
                          ,aeFills         = 0x0100 ///< <tt>0x0100</tt> Borders of fills (e.g. under or between graphs)
                                                    /// 채우기 테두리 (예 : 그래프 아래 또는 사이)
                          ,aeZeroLine      = 0x0200 ///< <tt>0x0200</tt> Zero-lines, see \ref QCPGrid::setZeroLinePen
                                                    /// 제로 라인은 \ ref를 참조하십시오 QCPGrid :: setZeroLinePen
                          ,aeOther         = 0x8000 ///< <tt>0x8000</tt> Other elements that don't fit into any of the existing categories                                          /// 기존 범주에 맞지 않는 다른 요소
                          ,aeAll           = 0xFFFF ///< <tt>0xFFFF</tt> All elements
                                                    /// 모든 요소들
                          ,aeNone          = 0x0000 ///< <tt>0x0000</tt> No elements
                                                    /// 요소 없음
                        };
Q_DECLARE_FLAGS(AntialiasedElements, AntialiasedElement)

/*!
  Defines plotting hints that control various aspects of the quality and speed of plotting.
  
  \see QCustomPlot::setPlottingHints
*/
/* !
  플로팅의 품질과 속도의 다양한 측면을 제어하는 ​​플로팅 힌트를 정의합니다.
  
  \ QCustomPlot :: setPlottingHints를 참조하십시오.
*/

enum PlottingHint { phNone              = 0x000 ///< <tt>0x000</tt> No hints are set
                                                /// 힌트가 설정되지 않았습니다.

                    ,phFastPolylines    = 0x001 ///< <tt>0x001</tt> Graph/Curve lines are drawn with a faster method. This reduces the quality especially of the line segment
/// 그래프 / 곡선 선은보다 빠른 방법으로 그려집니다. 이렇게하면 특히 선분의 품질이 떨어집니다.

///<joins, thus is most effective for pen sizes larger than 1. It is only used for solid line pens.
/// <조인이므로 1보다 큰 펜 크기에서는 가장 효과적입니다.이 펜은 실선 펜에만 사용됩니다.

                    ,phImmediateRefresh = 0x002 ///< <tt>0x002</tt> causes an immediate repaint() instead of a soft update() when QCustomPlot::replot() is called with parameter \ref QCustomPlot::rpRefreshHint.
/// <tt> 0x002 </ tt>는 소프트 업데이트 () 대신 즉시 repaint ()를 발생시킵니다.

///<This is set by default to prevent the plot from freezing on fast consecutive replots (e.g. user drags ranges with mouse).
/// <이것은 빠른 연속 replot에서 plot이 정지되는 것을 방지하기 위해 기본적으로 설정됩니다 (예 : 사용자가 마우스로 범위를 드래그)

                    ,phCacheLabels      = 0x004 ///< <tt>0x004</tt> axis (tick) labels will be cached as pixmaps, increasing replot performance.
/// <tt> 0x004 </ tt> 축 (틱) 레이블은 픽스맵으로 캐시되어 replot 성능이 향상됩니다.
                  };
Q_DECLARE_FLAGS(PlottingHints, PlottingHint)

/*!
  Defines the mouse interactions possible with QCustomPlot.
  
  \c Interactions is a flag of or-combined elements of this enum type.
  
  \see QCustomPlot::setInteractions
*/
/* !
  QCustomPlot에서 가능한 마우스 상호 작용을 정의합니다.
  
  \ c 상호 작용은이 enum 유형의 또는 결합 된 요소의 플래그입니다.
  
  \ QCustomPlot :: setInteractions를 참조하십시오.
*/

enum Interaction { iRangeDrag         = 0x001 ///< <tt>0x001</tt> Axis ranges are draggable (see \ref QCPAxisRect::setRangeDrag, \ref QCPAxisRect::setRangeDragAxes)
/// <tt> 0x001 </ tt> 축 범위는 드래그 가능하다 (\ ref QCPAxisRect :: setRangeDrag, \ ref QCPAxisRect :: setRangeDragAxes 참조)

                   ,iRangeZoom        = 0x002 ///< <tt>0x002</tt> Axis ranges are zoomable with the mouse wheel (see \ref QCPAxisRect::setRangeZoom, \ref QCPAxisRect::setRangeZoomAxes)
/// <tt> 0x002 </ tt> 축 범위는 마우스 휠을 사용하여 확대 / 축소 할 수 있습니다 (\ ref QCPAxisRect :: setRangeZoom, \ ref QCPAxisRect :: setRangeZoomAxes 참조)

                   ,iMultiSelect      = 0x004 ///< <tt>0x004</tt> The user can select multiple objects by holding the modifier set by \ref QCustomPlot::setMultiSelectModifier while clicking
/// <tt> 0x004 </ tt> 사용자는 \ ref QCustomPlot :: setMultiSelectModifier에 의해 설정된 수정자를 클릭하여 여러 객체를 선택할 수 있습니다.

                   ,iSelectPlottables = 0x008 ///< <tt>0x008</tt> Plottables are selectable (e.g. graphs, curves, bars,... see QCPAbstractPlottable)
/// <tt> 0x008 </ tt> Plottables를 선택할 수 있습니다 (예 : 그래프, 커브, 바, ... QCPAbstractPlottable 참조)

                   ,iSelectAxes       = 0x010 ///< <tt>0x010</tt> Axes are selectable (or parts of them, see QCPAxis::setSelectableParts)
/// <0x010 </ tt> 축을 선택할 수 있습니다 (또는 그 일부는 QCPAxis :: setSelectableParts를 참조하십시오)

                   ,iSelectLegend     = 0x020 ///< <tt>0x020</tt> Legends are selectable (or their child items, see QCPLegend::setSelectableParts)
/// <<tt> 0x020 </ tt> 범례는 선택 가능합니다 (또는 하위 항목은 QCPLegend :: setSelectableParts를 참조하십시오)

                   ,iSelectItems      = 0x040 ///< <tt>0x040</tt> Items are selectable (Rectangles, Arrows, Textitems, etc. see \ref QCPAbstractItem)
/// <tt> 0x040 </ tt> 항목 선택 가능 (직사각형, 화살표, 텍스트 항목 등 \ ref QCPAbstractItem 참조)

                   ,iSelectOther      = 0x080 ///< <tt>0x080</tt> All other objects are selectable (e.g. your own derived layerables, other layout elements,...)
/// <tt> 0x080 </ tt> 다른 모든 객체는 선택할 수 있습니다 (예 : 자신의 파생 된 레이어 가능 요소, 다른 레이아웃 요소 ...)
                 };
Q_DECLARE_FLAGS(Interactions, Interaction)

/*!
  Defines the behaviour of the selection rect.
  
  \see QCustomPlot::setSelectionRectMode, QCustomPlot::selectionRect, QCPSelectionRect
*/
/* !
  선택 사항 rect의 비헤이비어를 정의합니다.
  
  \ QCustomPlot :: setSelectionRectMode, QCustomPlot :: selectionRect, QCPSelectionRect를 참조하십시오.
*/

enum SelectionRectMode { srmNone    ///< The selection rect is disabled, and all mouse events are forwarded to the underlying objects, e.g. for axis range dragging
/// <선택 영역을 비활성화하고 모든 마우스 이벤트를 기본 객체 (예 : 축 범위 드래그)로 전달합니다.

                         ,srmZoom   ///< When dragging the mouse, a selection rect becomes active. Upon releasing, the axes that are currently set as range zoom axes (\ref QCPAxisRect::setRangeZoomAxes) will have their ranges zoomed accordingly.
/// <마우스를 끌 때 선택 영역이 활성화됩니다. 놓을 때 현재 범위 줌 축 (\ ref QCPAxisRect :: setRangeZoomAxes)으로 설정된 축의 범위는 그에 따라 확대됩니다.

                         ,srmSelect ///< When dragging the mouse, a selection rect becomes active. Upon releasing, plottable data points that were within the selection rect are selected, if the plottable's selectability setting permits. (See  \ref dataselection "data selection mechanism" for details.)
/// <마우스를 끌 때 선택 영역이 활성화됩니다. 해제시, 선택란 안에있는 플롯 가능한 데이터 포인트가 선택됩니다 (플롯 테이블의 선택 가능성 설정이 허용되는 경우). 자세한 내용은 \ ref dataslection "데이터 선택 메커니즘"을 참조하십시오.

                         ,srmCustom ///< When dragging the mouse, a selection rect becomes active. It is the programmer's responsibility to connect according slots to the selection rect's signals (e.g. \ref QCPSelectionRect::accepted) in order to process the user interaction.
/// <마우스를 끌 때 선택 영역이 활성화됩니다. 사용자 상호 작용을 처리하기 위해 슬롯에 따라 선택 rect의 신호 (예 : \ ref QCPSelectionRect :: accepted)를 연결하는 것은 프로그래머의 책임입니다.
                       
                       };

/*!
  Defines the different ways a plottable can be selected. These images show the effect of the
  different selection types, when the indicated selection rect was dragged:
  //플롯 테이블을 선택할 수있는 여러 가지 방법을 정의합니다. 이 이미지는 표시된 selection rect가 드래그되었을 때 다른 선택 유형 :
  <center>
  <table>
  <tr>
    <td>\image html selectiontype-none.png stNone</td>
    <td>\image html selectiontype-whole.png stWhole</td>
    <td>\image html selectiontype-singledata.png stSingleData</td>
    <td>\image html selectiontype-datarange.png stDataRange</td>
    <td>\image html selectiontype-multipledataranges.png stMultipleDataRanges</td>
  </tr>
  </table>
  </center>
  
  \see QCPAbstractPlottable::setSelectable, QCPDataSelection::enforceType
*/
enum SelectionType { stNone                ///< The plottable is not selectable
                                           /// <플롯 테이블을 선택할 수 없습니다.
                     ,stWhole              ///< Selection behaves like \ref stMultipleDataRanges, but if there are any data points selected, the entire plottable is drawn as selected.
                                           /// <Selection은 \ ref stMultipleDataRanges처럼 작동하지만 선택된 데이터 포인트가 있으면 전체 플롯 테이블이 선택된 것으로 그려집니다.
                     ,stSingleData         ///< One individual data point can be selected at a time
                                           /// <한 번에 하나의 개별 데이터 요소를 선택할 수 있습니다
                     ,stDataRange          ///< Multiple contiguous data points (a data range) can be selected
                                           /// <여러 연속 데이터 포인트 (데이터 범위)를 선택할 수 있습니다
                     ,stMultipleDataRanges ///< Any combination of data points/ranges can be selected
                    };                     /// <데이터 포인트 / 범위의 모든 조합을 선택할 수 있습니다.

/*! \internal
  
  Returns whether the specified \a value is considered an invalid data value for plottables (i.e.
  is \e nan or \e +/-inf). This function is used to check data validity upon replots, when the
  compiler flag \c QCUSTOMPLOT_CHECK_DATA is set.
*/
/* ! \내부의
  
  지정된 \ a 값이 plottables에 대한 잘못된 데이터 값으로 간주되는지 여부를 반환합니다 (즉,
  \ e nan 또는 \ e +/- inf). 이 함수는 replots에서 데이터 유효성을 검사 할 때 사용됩니다.
  컴파일러 플래그 \ c QCUSTOMPLOT_CHECK_DATA가 설정되었습니다.
*/
inline bool isInvalidData(double value)
{
  return qIsNaN(value) || qIsInf(value);
}

/*! \internal
  \overload
  
  Checks two arguments instead of one.
*/
/* ! \내부의
  \초과 적재
  
  하나가 아닌 두 개의 인수를 검사합니다.
*/
inline bool isInvalidData(double value1, double value2)
{
  return isInvalidData(value1) || isInvalidData(value2);
}

/*! \internal
  
  Sets the specified \a side of \a margins to \a value
  
  \see getMarginValue
*/
/* ! \내부의
  
  마진의 \ a면을 \ a 값으로 설정합니다.
  
  \ see getMarginValue
*/
inline void setMarginValue(QMargins &margins, QCP::MarginSide side, int value)
{
  switch (side)
  {
    case QCP::msLeft: margins.setLeft(value); break;
    case QCP::msRight: margins.setRight(value); break;
    case QCP::msTop: margins.setTop(value); break;
    case QCP::msBottom: margins.setBottom(value); break;
    case QCP::msAll: margins = QMargins(value, value, value, value); break;
    default: break;
  }
}

/*! \internal
  
  Returns the value of the specified \a side of \a margins. If \a side is \ref QCP::msNone or
  \ref QCP::msAll, returns 0.
  
  \see setMarginValue
*/
/* ! \내부의
  
  \ 여백의 \ a면의 값을 반환합니다. \ a면이 \ ref QCP :: msNone이거나
  \ ref QCP :: msAll은 0을 반환합니다.
  
  \ setMarginValue 참조
*/
inline int getMarginValue(const QMargins &margins, QCP::MarginSide side)
{
  switch (side)
  {
    case QCP::msLeft: return margins.left();
    case QCP::msRight: return margins.right();
    case QCP::msTop: return margins.top();
    case QCP::msBottom: return margins.bottom();
    default: break;
  }
  return 0;
}


extern const QMetaObject staticMetaObject; // in moc-run we create a static meta object for QCP "fake" object. This line is the link to it via QCP::staticMetaObject in normal operation as namespace
// moc-run에서 우리는 QCP "fake"객체를위한 정적 메타 객체를 만든다. 이 줄은 일반적인 작업에서 QCP :: staticMetaObject를 통해 네임 스페이스로 연결되는 링크입니다.
} // end of namespace QCP
  // 네임 스페이스의 끝 QCP
Q_DECLARE_OPERATORS_FOR_FLAGS(QCP::AntialiasedElements)
Q_DECLARE_OPERATORS_FOR_FLAGS(QCP::PlottingHints)
Q_DECLARE_OPERATORS_FOR_FLAGS(QCP::MarginSides)
Q_DECLARE_OPERATORS_FOR_FLAGS(QCP::Interactions)
Q_DECLARE_METATYPE(QCP::ExportPen)
Q_DECLARE_METATYPE(QCP::ResolutionUnit)
Q_DECLARE_METATYPE(QCP::SignDomain)
Q_DECLARE_METATYPE(QCP::MarginSide)
Q_DECLARE_METATYPE(QCP::AntialiasedElement)
Q_DECLARE_METATYPE(QCP::PlottingHint)
Q_DECLARE_METATYPE(QCP::Interaction)
Q_DECLARE_METATYPE(QCP::SelectionRectMode)
Q_DECLARE_METATYPE(QCP::SelectionType)

/* end of 'src/global.h' */
/* 'src / global.h'의 끝 */


/* including file 'src/vector2d.h', size 4928                                */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 파일 'src / vector2d.h'포함, 크기 4928                                   */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */


class QCP_LIB_DECL QCPVector2D
{
public:
  QCPVector2D();
  QCPVector2D(double x, double y);
  QCPVector2D(const QPoint &point);
  QCPVector2D(const QPointF &point);
  
  // getters:
  double x() const { return mX; }
  double y() const { return mY; }
  double &rx() { return mX; }
  double &ry() { return mY; }
  
  // setters:
  void setX(double x) { mX = x; }
  void setY(double y) { mY = y; }
  
  // non-virtual methods:
  // 비 가상 메소드 :
  double length() const { return qSqrt(mX*mX+mY*mY); }
  double lengthSquared() const { return mX*mX+mY*mY; }
  QPoint toPoint() const { return QPoint(mX, mY); }
  QPointF toPointF() const { return QPointF(mX, mY); }
  
  bool isNull() const { return qIsNull(mX) && qIsNull(mY); }
  void normalize();
  QCPVector2D normalized() const;
  QCPVector2D perpendicular() const { return QCPVector2D(-mY, mX); }
  double dot(const QCPVector2D &vec) const { return mX*vec.mX+mY*vec.mY; }
  double distanceSquaredToLine(const QCPVector2D &start, const QCPVector2D &end) const;
  double distanceSquaredToLine(const QLineF &line) const;
  double distanceToStraightLine(const QCPVector2D &base, const QCPVector2D &direction) const;
  
  QCPVector2D &operator*=(double factor);
  QCPVector2D &operator/=(double divisor);
  QCPVector2D &operator+=(const QCPVector2D &vector);
  QCPVector2D &operator-=(const QCPVector2D &vector);
  
private:
  // property members:
  // 속성 멤버 :
  double mX, mY;
  
  friend inline const QCPVector2D operator*(double factor, const QCPVector2D &vec);
  friend inline const QCPVector2D operator*(const QCPVector2D &vec, double factor);
  friend inline const QCPVector2D operator/(const QCPVector2D &vec, double divisor);
  friend inline const QCPVector2D operator+(const QCPVector2D &vec1, const QCPVector2D &vec2);
  friend inline const QCPVector2D operator-(const QCPVector2D &vec1, const QCPVector2D &vec2);
  friend inline const QCPVector2D operator-(const QCPVector2D &vec);
};
Q_DECLARE_TYPEINFO(QCPVector2D, Q_MOVABLE_TYPE);

inline const QCPVector2D operator*(double factor, const QCPVector2D &vec) { return QCPVector2D(vec.mX*factor, vec.mY*factor); }
inline const QCPVector2D operator*(const QCPVector2D &vec, double factor) { return QCPVector2D(vec.mX*factor, vec.mY*factor); }
inline const QCPVector2D operator/(const QCPVector2D &vec, double divisor) { return QCPVector2D(vec.mX/divisor, vec.mY/divisor); }
inline const QCPVector2D operator+(const QCPVector2D &vec1, const QCPVector2D &vec2) { return QCPVector2D(vec1.mX+vec2.mX, vec1.mY+vec2.mY); }
inline const QCPVector2D operator-(const QCPVector2D &vec1, const QCPVector2D &vec2) { return QCPVector2D(vec1.mX-vec2.mX, vec1.mY-vec2.mY); }
inline const QCPVector2D operator-(const QCPVector2D &vec) { return QCPVector2D(-vec.mX, -vec.mY); }

/*! \relates QCPVector2D

  Prints \a vec in a human readable format to the qDebug output.
*/

/* ! \ 관련 QCPVector2D
  사람이 읽을 수있는 형식의 vec를 qDebug 출력에 인쇄합니다.
*/
inline QDebug operator<< (QDebug d, const QCPVector2D &vec)
{
    d.nospace() << "QCPVector2D(" << vec.x() << ", " << vec.y() << ")";
    return d.space();
}

/* end of 'src/vector2d.h' */


/* including file 'src/painter.h', size 4035                                 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / vector2d.h'의 끝 */


/* 파일 'src / painter.h', 크기 4035 포함                                  */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPPainter : public QPainter
{
  Q_GADGET
public:
  /*!
    Defines special modes the painter can operate in. They disable or enable certain subsets of features/fixes/workarounds,
    depending on whether they are wanted on the respective output device.
  */
 /* !
    페인터가 조작 할 수있는 특수 모드를 정의합니다. 기능 / 픽스 / 해결 방법의 특정 하위 집합을 비활성화하거나 활성화합니다.
    각각의 출력 장치에 원하는지 여부에 따라 다릅니다.
  */
  enum PainterMode { pmDefault       = 0x00   ///< <tt>0x00</tt> Default mode for painting on screen devices
                                              /// < 0x0 </ tt> 화면 장치의 페인팅을위한 기본 모드
                     ,pmVectorized   = 0x01   ///< <tt>0x01</tt> Mode for vectorized painting (e.g. PDF export). For example, this prevents some antialiasing fixes.
/// <tt> 0x01 </ tt> 벡터화 된 페인팅을위한 모드 (예 : PDF 내보내기). 예를 들어, 일부 안티 앨리어싱 수정이 방지됩니다.

                     ,pmNoCaching    = 0x02   ///< <tt>0x02</tt> Mode for all sorts of exports (e.g. PNG, PDF,...). For example, this prevents using cached pixmap labels
/// <tt> 0x02 </ tt> 모든 종류의 내보내기 (예 : PNG, PDF, ...) 모드. 예를 들어, 캐시 된 픽스맵 레이블을 사용할 수 없습니다.


                     ,pmNonCosmetic  = 0x04   ///< <tt>0x04</tt> Turns pen widths 0 to 1, i.e. disables cosmetic pens. (A cosmetic pen is always drawn with width 1 pixel in the vector image/pdf viewer, independent of zoom.)
/// <0x04 </ tt> 펜 너비를 0에서 1로 바꾸어줍니다 . 즉 화장 용 펜을 사용할 수 없습니다. (화장품 펜은 항상 벡터 이미지 / PDF 뷰어에서 너비 1 픽셀로 그려지지만 줌과는 관련이 없습니다.)
                   };
  Q_ENUMS(PainterMode)
  Q_FLAGS(PainterModes)
  Q_DECLARE_FLAGS(PainterModes, PainterMode)
  
  QCPPainter();
  explicit QCPPainter(QPaintDevice *device);
  
  // getters:
  bool antialiasing() const { return testRenderHint(QPainter::Antialiasing); }
  PainterModes modes() const { return mModes; }

  // setters:
  void setAntialiasing(bool enabled);
  void setMode(PainterMode mode, bool enabled=true);
  void setModes(PainterModes modes);

  // methods hiding non-virtual base class functions (QPainter bug workarounds):
  // 비 - 가상 기본 클래스 함수를 숨기는 메소드 (QPainter bug workarounds) :
  bool begin(QPaintDevice *device);
  void setPen(const QPen &pen);
  void setPen(const QColor &color);
  void setPen(Qt::PenStyle penStyle);
  void drawLine(const QLineF &line);
  void drawLine(const QPointF &p1, const QPointF &p2) {drawLine(QLineF(p1, p2));}
  void save();
  void restore();
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void makeNonCosmetic();
  
protected:
  // property members:
  // 속성 멤버 :
  PainterModes mModes;
  bool mIsAntialiasing;
  
  // non-property members:
  // 비 속성 멤버 :
  QStack<bool> mAntialiasingStack;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QCPPainter::PainterModes)
Q_DECLARE_METATYPE(QCPPainter::PainterMode)

/* end of 'src/painter.h' */


/* including file 'src/paintbuffer.h', size 4958                             */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / painter.h'의 끝 */


/* 파일 'src / paintbuffer.h', 크기 4958 포함                              */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPAbstractPaintBuffer
{
public:
  explicit QCPAbstractPaintBuffer(const QSize &size, double devicePixelRatio);
  virtual ~QCPAbstractPaintBuffer();
  
  // getters:
  QSize size() const { return mSize; }
  bool invalidated() const { return mInvalidated; }
  double devicePixelRatio() const { return mDevicePixelRatio; }
  
  // setters:
  void setSize(const QSize &size);
  void setInvalidated(bool invalidated=true);
  void setDevicePixelRatio(double ratio);
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual QCPPainter *startPainting() = 0;
  virtual void donePainting() {}
  virtual void draw(QCPPainter *painter) const = 0;
  virtual void clear(const QColor &color) = 0;
  
protected:
  // property members:
  // 속성 멤버 :
  QSize mSize;
  double mDevicePixelRatio;
  
  // non-property members:
  // 비 속성 멤버 :
  bool mInvalidated;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void reallocateBuffer() = 0;
};


class QCP_LIB_DECL QCPPaintBufferPixmap : public QCPAbstractPaintBuffer
{
public:
  explicit QCPPaintBufferPixmap(const QSize &size, double devicePixelRatio);
  virtual ~QCPPaintBufferPixmap();
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  // 비 속성 멤버 :
  QPixmap mBuffer;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};


#ifdef QCP_OPENGL_PBUFFER
class QCP_LIB_DECL QCPPaintBufferGlPbuffer : public QCPAbstractPaintBuffer
{
public:
  explicit QCPPaintBufferGlPbuffer(const QSize &size, double devicePixelRatio, int multisamples);
  virtual ~QCPPaintBufferGlPbuffer();
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  // 비 속성 멤버 :
  QGLPixelBuffer *mGlPBuffer;
  int mMultisamples;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};
#endif // QCP_OPENGL_PBUFFER


#ifdef QCP_OPENGL_FBO
class QCP_LIB_DECL QCPPaintBufferGlFbo : public QCPAbstractPaintBuffer
{
public:
  explicit QCPPaintBufferGlFbo(const QSize &size, double devicePixelRatio, QWeakPointer<QOpenGLContext> glContext, QWeakPointer<QOpenGLPaintDevice> glPaintDevice);
  virtual ~QCPPaintBufferGlFbo();
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void donePainting() Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  // 비 속성 멤버 :
  QWeakPointer<QOpenGLContext> mGlContext;
  QWeakPointer<QOpenGLPaintDevice> mGlPaintDevice;
  QOpenGLFramebufferObject *mGlFrameBuffer;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};
#endif // QCP_OPENGL_FBO

/* end of 'src/paintbuffer.h' */


/* including file 'src/layer.h', size 6885                                   */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / paintbuffer.h'의 끝 */


/* 파일 'src / layer.h'포함, 크기 6885                                      */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPLayer : public QObject
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QCustomPlot* parentPlot READ parentPlot)
  Q_PROPERTY(QString name READ name)
  Q_PROPERTY(int index READ index)
  Q_PROPERTY(QList<QCPLayerable*> children READ children)
  Q_PROPERTY(bool visible READ visible WRITE setVisible)
  Q_PROPERTY(LayerMode mode READ mode WRITE setMode)
  /// \endcond
public:
  
  /*!
    Defines the different rendering modes of a layer. Depending on the mode, certain layers can be
    replotted individually, without the need to replot (possibly complex) layerables on other
    layers.

    \see setMode
  */
 /* !
    레이어의 여러 렌더링 모드를 정의합니다. 모드에 따라 특정 레이어가 될 수 있습니다.
    다른 레이어에 복제 가능 (복잡한 경우가 있음)없이 개별적으로 재구성
    레이어.
    \ setMode 참조
  */ 
  enum LayerMode { lmLogical   ///< Layer is used only for rendering order, and shares paint buffer with all other adjacent logical layers.
/// <레이어는 렌더링 순서에만 사용되며 다른 모든 인접한 논리 레이어와 페인트 버퍼를 공유합니다.

                   ,lmBuffered ///< Layer has its own paint buffer and may be replotted individually (see \ref replot).
                 };            /// <layer>에는 자체 페인트 버퍼가 있으며 개별적으로 다시 칠할 수 있습니다 (\ ref replot 참조).
  Q_ENUMS(LayerMode)
  
  QCPLayer(QCustomPlot* parentPlot, const QString &layerName);
  virtual ~QCPLayer();
  
  // getters:
  QCustomPlot *parentPlot() const { return mParentPlot; }
  QString name() const { return mName; }
  int index() const { return mIndex; }
  QList<QCPLayerable*> children() const { return mChildren; }
  bool visible() const { return mVisible; }
  LayerMode mode() const { return mMode; }
  
  // setters:
  void setVisible(bool visible);
  void setMode(LayerMode mode);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void replot();
  
protected:
  // property members:
  // 속성 멤버 :
  QCustomPlot *mParentPlot;
  QString mName;
  int mIndex;
  QList<QCPLayerable*> mChildren;
  bool mVisible;
  LayerMode mMode;
  
  // non-property members:
  // 비 속성 멤버 :
  QWeakPointer<QCPAbstractPaintBuffer> mPaintBuffer;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void draw(QCPPainter *painter);
  void drawToPaintBuffer();
  void addChild(QCPLayerable *layerable, bool prepend);
  void removeChild(QCPLayerable *layerable);
  
private:
  Q_DISABLE_COPY(QCPLayer)
  
  friend class QCustomPlot;
  friend class QCPLayerable;
};
Q_DECLARE_METATYPE(QCPLayer::LayerMode)

class QCP_LIB_DECL QCPLayerable : public QObject
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(bool visible READ visible WRITE setVisible)
  Q_PROPERTY(QCustomPlot* parentPlot READ parentPlot)
  Q_PROPERTY(QCPLayerable* parentLayerable READ parentLayerable)
  Q_PROPERTY(QCPLayer* layer READ layer WRITE setLayer NOTIFY layerChanged)
  Q_PROPERTY(bool antialiased READ antialiased WRITE setAntialiased)
  /// \endcond
public:
  QCPLayerable(QCustomPlot *plot, QString targetLayer=QString(), QCPLayerable *parentLayerable=0);
  virtual ~QCPLayerable();
  
  // getters:
  bool visible() const { return mVisible; }
  QCustomPlot *parentPlot() const { return mParentPlot; }
  QCPLayerable *parentLayerable() const { return mParentLayerable.data(); }
  QCPLayer *layer() const { return mLayer; }
  bool antialiased() const { return mAntialiased; }
  
  // setters:
  void setVisible(bool on);
  Q_SLOT bool setLayer(QCPLayer *layer);
  bool setLayer(const QString &layerName);
  void setAntialiased(bool enabled);
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const;

  // non-property methods:
  // 비 속성 메소드 :
  bool realVisibility() const;
  
signals:
  void layerChanged(QCPLayer *newLayer);
  
protected:
  // property members:
  // 속성 멤버 :
  bool mVisible;
  QCustomPlot *mParentPlot;
  QPointer<QCPLayerable> mParentLayerable;
  QCPLayer *mLayer;
  bool mAntialiased;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void parentPlotInitialized(QCustomPlot *parentPlot);
  virtual QCP::Interaction selectionCategory() const;
  virtual QRect clipRect() const;
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const = 0;
  virtual void draw(QCPPainter *painter) = 0;
  // selection events:
  // 선택 이벤트 :
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged);
  virtual void deselectEvent(bool *selectionStateChanged);
  // low-level mouse events:
  // 저수준 마우스 이벤트 :
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details);
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos);
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos);
  virtual void mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details);
  virtual void wheelEvent(QWheelEvent *event);
  
  // non-property methods:
  // 비 속성 메소드 :
  void initializeParentPlot(QCustomPlot *parentPlot);
  void setParentLayerable(QCPLayerable* parentLayerable);
  bool moveToLayer(QCPLayer *layer, bool prepend);
  void applyAntialiasingHint(QCPPainter *painter, bool localAntialiased, QCP::AntialiasedElement overrideElement) const;
  
private:
  Q_DISABLE_COPY(QCPLayerable)
  
  friend class QCustomPlot;
  friend class QCPLayer;
  friend class QCPAxisRect;
};

/* end of 'src/layer.h' */


/* including file 'src/axis/range.h', size 5280                              */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / layer.h'의 끝 */


/* 파일 'src / axis / range.h'포함, 크기 5280                               */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPRange
{
public:
  double lower, upper;
  
  QCPRange();
  QCPRange(double lower, double upper);
  
  bool operator==(const QCPRange& other) const { return lower == other.lower && upper == other.upper; }
  bool operator!=(const QCPRange& other) const { return !(*this == other); }
  
  QCPRange &operator+=(const double& value) { lower+=value; upper+=value; return *this; }
  QCPRange &operator-=(const double& value) { lower-=value; upper-=value; return *this; }
  QCPRange &operator*=(const double& value) { lower*=value; upper*=value; return *this; }
  QCPRange &operator/=(const double& value) { lower/=value; upper/=value; return *this; }
  friend inline const QCPRange operator+(const QCPRange&, double);
  friend inline const QCPRange operator+(double, const QCPRange&);
  friend inline const QCPRange operator-(const QCPRange& range, double value);
  friend inline const QCPRange operator*(const QCPRange& range, double value);
  friend inline const QCPRange operator*(double value, const QCPRange& range);
  friend inline const QCPRange operator/(const QCPRange& range, double value);
  
  double size() const { return upper-lower; }
  double center() const { return (upper+lower)*0.5; }
  void normalize() { if (lower > upper) qSwap(lower, upper); }
  void expand(const QCPRange &otherRange);
  void expand(double includeCoord);
  QCPRange expanded(const QCPRange &otherRange) const;
  QCPRange expanded(double includeCoord) const;
  QCPRange bounded(double lowerBound, double upperBound) const;
  QCPRange sanitizedForLogScale() const;
  QCPRange sanitizedForLinScale() const;
  bool contains(double value) const { return value >= lower && value <= upper; }
  
  static bool validRange(double lower, double upper);
  static bool validRange(const QCPRange &range);
  static const double minRange;
  static const double maxRange;
  
};
Q_DECLARE_TYPEINFO(QCPRange, Q_MOVABLE_TYPE);

/*! \relates QCPRange

  Prints \a range in a human readable format to the qDebug output.
*/
/* ! \ 관련 QCPRange
  사람이 읽을 수있는 형식의 범위를 qDebug 출력으로 인쇄합니다.
*/
inline QDebug operator<< (QDebug d, const QCPRange &range)
{
    d.nospace() << "QCPRange(" << range.lower << ", " << range.upper << ")";
    return d.space();
}

/*!
  Adds \a value to both boundaries of the range.
*/
/* !
  범위의 양쪽 경계에 \ a 값을 추가합니다.
*/
inline const QCPRange operator+(const QCPRange& range, double value)
{
  QCPRange result(range);
  result += value;
  return result;
}

/*!
  Adds \a value to both boundaries of the range.
*/
/* !
  범위의 양쪽 경계에 \ a 값을 추가합니다.
*/
inline const QCPRange operator+(double value, const QCPRange& range)
{
  QCPRange result(range);
  result += value;
  return result;
}

/*!
  Subtracts \a value from both boundaries of the range.
*/
/* !
  범위의 두 경계에서 \ a 값을 뺍니다.
*/
inline const QCPRange operator-(const QCPRange& range, double value)
{
  QCPRange result(range);
  result -= value;
  return result;
}

/*!
  Multiplies both boundaries of the range by \a value.
*/
/* !
  범위의 두 경계를 모두 \ a 값만큼 곱합니다.
*/
inline const QCPRange operator*(const QCPRange& range, double value)
{
  QCPRange result(range);
  result *= value;
  return result;
}

/*!
  Multiplies both boundaries of the range by \a value.
*/
/* !
  범위의 두 경계를 모두 \ a 값만큼 곱합니다.
*/
inline const QCPRange operator*(double value, const QCPRange& range)
{
  QCPRange result(range);
  result *= value;
  return result;
}

/*!
  Divides both boundaries of the range by \a value.
*/
/* !
  범위의 두 경계를 \ a 값으로 나눕니다.
*/
inline const QCPRange operator/(const QCPRange& range, double value)
{
  QCPRange result(range);
  result /= value;
  return result;
}

/* end of 'src/axis/range.h' */


/* including file 'src/selection.h', size 8579                               */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/
/* 'src / axis / range.h'의 끝 */


/* 'src / selection.h'파일 포함, 크기 8579                                  */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/

class QCP_LIB_DECL QCPDataRange
{
public:
  QCPDataRange();
  QCPDataRange(int begin, int end);
  
  bool operator==(const QCPDataRange& other) const { return mBegin == other.mBegin && mEnd == other.mEnd; }
  bool operator!=(const QCPDataRange& other) const { return !(*this == other); }
  
  // getters:
  int begin() const { return mBegin; }
  int end() const { return mEnd; }
  int size() const { return mEnd-mBegin; }
  int length() const { return size(); }
  
  // setters:
  void setBegin(int begin) { mBegin = begin; }
  void setEnd(int end)  { mEnd = end; }
  
  // non-property methods:
  // 비 속성 메소드 :
  bool isValid() const { return (mEnd >= mBegin) && (mBegin >= 0); }
  bool isEmpty() const { return length() == 0; }
  QCPDataRange bounded(const QCPDataRange &other) const;
  QCPDataRange expanded(const QCPDataRange &other) const;
  QCPDataRange intersection(const QCPDataRange &other) const;
  QCPDataRange adjusted(int changeBegin, int changeEnd) const { return QCPDataRange(mBegin+changeBegin, mEnd+changeEnd); }
  bool intersects(const QCPDataRange &other) const;
  bool contains(const QCPDataRange &other) const;
  
private:
  // property members:
  // 속성 멤버 :
  int mBegin, mEnd;

};
Q_DECLARE_TYPEINFO(QCPDataRange, Q_MOVABLE_TYPE);


class QCP_LIB_DECL QCPDataSelection
{
public:
  explicit QCPDataSelection();
  explicit QCPDataSelection(const QCPDataRange &range);
  
  bool operator==(const QCPDataSelection& other) const;
  bool operator!=(const QCPDataSelection& other) const { return !(*this == other); }
  QCPDataSelection &operator+=(const QCPDataSelection& other);
  QCPDataSelection &operator+=(const QCPDataRange& other);
  QCPDataSelection &operator-=(const QCPDataSelection& other);
  QCPDataSelection &operator-=(const QCPDataRange& other);
  friend inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataRange& b);
  friend inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataRange& b);
  friend inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataRange& b);
  friend inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataRange& b);
  
  // getters:
  int dataRangeCount() const { return mDataRanges.size(); }
  int dataPointCount() const;
  QCPDataRange dataRange(int index=0) const;
  QList<QCPDataRange> dataRanges() const { return mDataRanges; }
  QCPDataRange span() const;
  
  // non-property methods:
  // 비 속성 메소드 :
  void addDataRange(const QCPDataRange &dataRange, bool simplify=true);
  void clear();
  bool isEmpty() const { return mDataRanges.isEmpty(); }
  void simplify();
  void enforceType(QCP::SelectionType type);
  bool contains(const QCPDataSelection &other) const;
  QCPDataSelection intersection(const QCPDataRange &other) const;
  QCPDataSelection intersection(const QCPDataSelection &other) const;
  QCPDataSelection inverse(const QCPDataRange &outerRange) const;
  
private:
  // property members:
  // 속성 멤버 :
  QList<QCPDataRange> mDataRanges;
  
  inline static bool lessThanDataRangeBegin(const QCPDataRange &a, const QCPDataRange &b) { return a.begin() < b.begin(); }
};
Q_DECLARE_METATYPE(QCPDataSelection)


/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
/* !
  \ aa에있는 데이터 포인트가 \ a에있는 데이터 포인트와 합쳐진 \ ref QCPDataSelection을 반환합니다. b.
  결과 데이터 선택은 이미 단순화되었습니다 (\ ref QCPDataSelection :: simplify 참조).
*/
inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
/* !
  \ aa에있는 데이터 포인트가 \ a에있는 데이터 포인트와 합쳐진 \ ref QCPDataSelection을 반환합니다. b.
  결과 데이터 선택은 이미 단순화되었습니다 (\ ref QCPDataSelection :: simplify 참조).
*/
inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
/* !
  \ aa에있는 데이터 포인트가 \ a에있는 데이터 포인트와 합쳐진 \ ref QCPDataSelection을 반환합니다. b.
  결과 데이터 선택은 이미 단순화되었습니다 (\ ref QCPDataSelection :: simplify 참조).
*/
inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
/* !
  \ aa에있는 데이터 포인트가 \ a에있는 데이터 포인트와 합쳐진 \ ref QCPDataSelection을 반환합니다. b.
  결과 데이터 선택은 이미 단순화되었습니다 (\ ref QCPDataSelection :: simplify 참조).
*/
inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
/* !
  \ aa에는 있지만 \ a에는없는 데이터 점을 가진 \ ref QCPDataSelection을 리턴하십시오. b.
*/
inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/

/* !
  \ aa에는 있지만 \ a에는없는 데이터 점을 가진 \ ref QCPDataSelection을 리턴하십시오. b.
*/
inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
/* !
  \ aa에는 있지만 \ a에는없는 데이터 점을 가진 \ ref QCPDataSelection을 리턴하십시오. b.
*/
inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
/* !
  \ aa에는 있지만 \ a에는없는 데이터 점을 가진 \ ref QCPDataSelection을 리턴하십시오. b.
*/
inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*! \relates QCPDataRange

  Prints \a dataRange in a human readable format to the qDebug output.
*/
/* ! \ 관련 QCPDataRange
  사람이 읽을 수있는 형식의 dataRange를 qDebug 출력에 인쇄합니다.
*/
inline QDebug operator<< (QDebug d, const QCPDataRange &dataRange)
{
    d.nospace() << "[" << dataRange.begin() << ".." << dataRange.end()-1 << "]";
    return d.space();
}

/*! \relates QCPDataSelection

  Prints \a selection in a human readable format to the qDebug output.
*/
/* ! \ 관련 QCPDataSelection
  사람이 읽을 수있는 형식의 선택을 qDebug 출력으로 인쇄합니다.
*/
inline QDebug operator<< (QDebug d, const QCPDataSelection &selection)
{
    d.nospace() << "QCPDataSelection(";
    for (int i=0; i<selection.dataRangeCount(); ++i)
    {
      if (i != 0)
        d << ", ";
      d << selection.dataRange(i);
    }
    d << ")";
    return d.space();
}



/* end of 'src/selection.h' */


/* including file 'src/selectionrect.h', size 3338                           */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / selection.h'의 끝 */


/* 파일 'src / selectionrect.h', 크기 3338 포함                             */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPSelectionRect : public QCPLayerable
{
  Q_OBJECT
public:
  explicit QCPSelectionRect(QCustomPlot *parentPlot);
  virtual ~QCPSelectionRect();
  
  // getters:
  QRect rect() const { return mRect; }
  QCPRange range(const QCPAxis *axis) const;
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  bool isActive() const { return mActive; }
  
  // setters:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  
  // non-property methods:
  // 비 속성 메소드 :
  Q_SLOT void cancel();
  
signals:
  void started(QMouseEvent *event);
  void changed(const QRect &rect, QMouseEvent *event);
  void canceled(const QRect &rect, QInputEvent *event);
  void accepted(const QRect &rect, QMouseEvent *event);
  
protected:
  // property members:
  // 속성 멤버 :
  QRect mRect;
  QPen mPen;
  QBrush mBrush;
  // non-property members:
  // 비 속성 멤버 :
  bool mActive;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void startSelection(QMouseEvent *event);
  virtual void moveSelection(QMouseEvent *event);
  virtual void endSelection(QMouseEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  
  // reimplemented virtual methods
  // 구현 된 가상 메소드
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  
  friend class QCustomPlot;
};

/* end of 'src/selectionrect.h' */


/* including file 'src/layout.h', size 14224                                 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / selectionrect.h'의 끝 */


/* 파일 'src / layout.h'포함, 크기 14224                                   */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPMarginGroup : public QObject
{
  Q_OBJECT
public:
  explicit QCPMarginGroup(QCustomPlot *parentPlot);
  virtual ~QCPMarginGroup();
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QList<QCPLayoutElement*> elements(QCP::MarginSide side) const { return mChildren.value(side); }
  bool isEmpty() const;
  void clear();
  
protected:
  // non-property members:
  // 비 속성 멤버 :
  QCustomPlot *mParentPlot;
  QHash<QCP::MarginSide, QList<QCPLayoutElement*> > mChildren;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual int commonMargin(QCP::MarginSide side) const;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void addChild(QCP::MarginSide side, QCPLayoutElement *element);
  void removeChild(QCP::MarginSide side, QCPLayoutElement *element);
  
private:
  Q_DISABLE_COPY(QCPMarginGroup)
  
  friend class QCPLayoutElement;
};


class QCP_LIB_DECL QCPLayoutElement : public QCPLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QCPLayout* layout READ layout)
  Q_PROPERTY(QRect rect READ rect)
  Q_PROPERTY(QRect outerRect READ outerRect WRITE setOuterRect)
  Q_PROPERTY(QMargins margins READ margins WRITE setMargins)
  Q_PROPERTY(QMargins minimumMargins READ minimumMargins WRITE setMinimumMargins)
  Q_PROPERTY(QSize minimumSize READ minimumSize WRITE setMinimumSize)
  Q_PROPERTY(QSize maximumSize READ maximumSize WRITE setMaximumSize)
  Q_PROPERTY(SizeConstraintRect sizeConstraintRect READ sizeConstraintRect WRITE setSizeConstraintRect)
  /// \endcond
public:
  /*!
    Defines the phases of the update process, that happens just before a replot. At each phase,
    \ref update is called with the according UpdatePhase value.
  */
  /* !
    replot 바로 전에 발생하는 업데이트 프로세스의 단계를 정의합니다. 각 단계에서,
    UpdatePhase 값에 따라 \ ref update가 호출됩니다.
  */
  enum UpdatePhase { upPreparation ///< Phase used for any type of preparation that needs to be done before margin calculation and layout                         /// <마진 계산 및 레이아웃을 수행하기 전에 수행해야하는 모든 유형의 준비에 사용되는 단계

                     ,upMargins    ///< Phase in which the margins are calculated and set
                                   /// <여백을 계산하고 설정하는 단계
                     ,upLayout     ///< Final phase in which the layout system places the rects of the elements
                   };              /// <레이아웃 시스템이 요소의 직사각형을      배치하는 최종 단계
  Q_ENUMS(UpdatePhase)
  
  /*!
    Defines to which rect of a layout element the size constraints that can be set via \ref
    setMinimumSize and \ref setMaximumSize apply. The outer rect (\ref outerRect) includes the
    margins (e.g. in the case of a QCPAxisRect the axis labels), whereas the inner rect (\ref rect)
    does not.
    
    \see setSizeConstraintRect
  */
  /* !
    \ ref를 통해 설정할 수있는 크기 제약 조건을 레이아웃 요소의 어느 rect에 정의 할 것인가?
    setMinimumSize 및 \ ref setMaximumSize가 적용됩니다. 바깥 쪽 rect (\ ref outerRect)에는
    여백 (예 : QCPAxisRect 축 레이블의 경우), 내부 rect (\ ref rect)
    하지 않습니다.
    
    \ setSizeConstraintRect 참조
  */
  enum SizeConstraintRect { scrInnerRect ///< Minimum/Maximum size constraints apply to inner rect
                                         /// <최소 / 최대 크기 제한은 내부 rect에 적용됩니다.
                            , scrOuterRect ///< Minimum/Maximum size constraints apply to outer rect, thus include layout element margins                            /// <최소 / 최대 크기 제한은 외부 rect에 적용되므로 레이아웃 요소 여백이 포함됩니다
                          };
  Q_ENUMS(SizeConstraintRect)

  explicit QCPLayoutElement(QCustomPlot *parentPlot=0);
  virtual ~QCPLayoutElement();
  
  // getters:
  QCPLayout *layout() const { return mParentLayout; }
  QRect rect() const { return mRect; }
  QRect outerRect() const { return mOuterRect; }
  QMargins margins() const { return mMargins; }
  QMargins minimumMargins() const { return mMinimumMargins; }
  QCP::MarginSides autoMargins() const { return mAutoMargins; }
  QSize minimumSize() const { return mMinimumSize; }
  QSize maximumSize() const { return mMaximumSize; }
  SizeConstraintRect sizeConstraintRect() const { return mSizeConstraintRect; }
  QCPMarginGroup *marginGroup(QCP::MarginSide side) const { return mMarginGroups.value(side, (QCPMarginGroup*)0); }
  QHash<QCP::MarginSide, QCPMarginGroup*> marginGroups() const { return mMarginGroups; }
  
  // setters:
  void setOuterRect(const QRect &rect);
  void setMargins(const QMargins &margins);
  void setMinimumMargins(const QMargins &margins);
  void setAutoMargins(QCP::MarginSides sides);
  void setMinimumSize(const QSize &size);
  void setMinimumSize(int width, int height);
  void setMaximumSize(const QSize &size);
  void setMaximumSize(int width, int height);
  void setSizeConstraintRect(SizeConstraintRect constraintRect);
  void setMarginGroup(QCP::MarginSides sides, QCPMarginGroup *group);
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void update(UpdatePhase phase);
  virtual QSize minimumOuterSizeHint() const;
  virtual QSize maximumOuterSizeHint() const;
  virtual QList<QCPLayoutElement*> elements(bool recursive) const;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  // 구현 된 가상 메소드 :
  QCPLayout *mParentLayout;
  QSize mMinimumSize, mMaximumSize;
  SizeConstraintRect mSizeConstraintRect;
  QRect mRect, mOuterRect;
  QMargins mMargins, mMinimumMargins;
  QCP::MarginSides mAutoMargins;
  QHash<QCP::MarginSide, QCPMarginGroup*> mMarginGroups;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual int calculateAutoMargin(QCP::MarginSide side);
  virtual void layoutChanged();
  
  // reimplemented virtual methods:
  // 비 가상 메소드 :
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE { Q_UNUSED(painter) }
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE { Q_UNUSED(painter) }
  virtual void parentPlotInitialized(QCustomPlot *parentPlot) Q_DECL_OVERRIDE;

private:
  Q_DISABLE_COPY(QCPLayoutElement)
  
  friend class QCustomPlot;
  friend class QCPLayout;
  friend class QCPMarginGroup;
};
Q_DECLARE_METATYPE(QCPLayoutElement::UpdatePhase)


class QCP_LIB_DECL QCPLayout : public QCPLayoutElement
{
  Q_OBJECT
public:
  explicit QCPLayout();
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  virtual QList<QCPLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual int elementCount() const = 0;
  virtual QCPLayoutElement* elementAt(int index) const = 0;
  virtual QCPLayoutElement* takeAt(int index) = 0;
  virtual bool take(QCPLayoutElement* element) = 0;
  virtual void simplify();
  
  // non-virtual methods:
  // 비 가상 메소드 :
  bool removeAt(int index);
  bool remove(QCPLayoutElement* element);
  void clear();
  
protected:
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void updateLayout();
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void sizeConstraintsChanged() const;
  void adoptElement(QCPLayoutElement *el);
  void releaseElement(QCPLayoutElement *el);
  QVector<int> getSectionSizes(QVector<int> maxSizes, QVector<int> minSizes, QVector<double> stretchFactors, int totalSize) const;
  static QSize getFinalMinimumOuterSize(const QCPLayoutElement *el);
  static QSize getFinalMaximumOuterSize(const QCPLayoutElement *el);
  
private:
  Q_DISABLE_COPY(QCPLayout)
  friend class QCPLayoutElement;
};


class QCP_LIB_DECL QCPLayoutGrid : public QCPLayout
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(int rowCount READ rowCount)
  Q_PROPERTY(int columnCount READ columnCount)
  Q_PROPERTY(QList<double> columnStretchFactors READ columnStretchFactors WRITE setColumnStretchFactors)
  Q_PROPERTY(QList<double> rowStretchFactors READ rowStretchFactors WRITE setRowStretchFactors)
  Q_PROPERTY(int columnSpacing READ columnSpacing WRITE setColumnSpacing)
  Q_PROPERTY(int rowSpacing READ rowSpacing WRITE setRowSpacing)
  Q_PROPERTY(FillOrder fillOrder READ fillOrder WRITE setFillOrder)
  Q_PROPERTY(int wrap READ wrap WRITE setWrap)
  /// \endcond
public:
  
  /*!
    Defines in which direction the grid is filled when using \ref addElement(QCPLayoutElement*).
    The column/row at which wrapping into the next row/column occurs can be specified with \ref
    setWrap.

    \see setFillOrder
  */
 /* !
    \ ref addElement (QCPLayoutElement *)를 사용할 때 격자가 채워지는 방향을 정의합니다.
    다음 행 / 열로 래핑되는 열 / 행은 \ ref로 지정할 수 있습니다
    setWrap.
    \ setFillOrder를 참조하십시오.
  */
  enum FillOrder { foRowsFirst    ///< Rows are filled first, and a new element is wrapped to the next column if the row count would exceed \ref setWrap.
/// <행이 먼저 채워지고, 행 수가 \ ref setWrap을 초과하면 새 요소가 다음 열로 래핑됩니다.
                  ,foColumnsFirst ///< Columns are filled first, and a new element is wrapped to the next row if the column count would exceed \ref setWrap.
/// <열이 먼저 채워지고 열 개수가 \ ref setWrap을 초과하면 새 요소가 다음 행으로 래핑됩니다.
                };
  Q_ENUMS(FillOrder)
  
  explicit QCPLayoutGrid();
  virtual ~QCPLayoutGrid();
  
  // getters:
  int rowCount() const { return mElements.size(); }
  int columnCount() const { return mElements.size() > 0 ? mElements.first().size() : 0; }
  QList<double> columnStretchFactors() const { return mColumnStretchFactors; }
  QList<double> rowStretchFactors() const { return mRowStretchFactors; }
  int columnSpacing() const { return mColumnSpacing; }
  int rowSpacing() const { return mRowSpacing; }
  int wrap() const { return mWrap; }
  FillOrder fillOrder() const { return mFillOrder; }
  
  // setters:
  void setColumnStretchFactor(int column, double factor);
  void setColumnStretchFactors(const QList<double> &factors);
  void setRowStretchFactor(int row, double factor);
  void setRowStretchFactors(const QList<double> &factors);
  void setColumnSpacing(int pixels);
  void setRowSpacing(int pixels);
  void setWrap(int count);
  void setFillOrder(FillOrder order, bool rearrange=true);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void updateLayout() Q_DECL_OVERRIDE;
  virtual int elementCount() const Q_DECL_OVERRIDE { return rowCount()*columnCount(); }
  virtual QCPLayoutElement* elementAt(int index) const Q_DECL_OVERRIDE;
  virtual QCPLayoutElement* takeAt(int index) Q_DECL_OVERRIDE;
  virtual bool take(QCPLayoutElement* element) Q_DECL_OVERRIDE;
  virtual QList<QCPLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;
  virtual void simplify() Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  virtual QSize maximumOuterSizeHint() const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QCPLayoutElement *element(int row, int column) const;
  bool addElement(int row, int column, QCPLayoutElement *element);
  bool addElement(QCPLayoutElement *element);
  bool hasElement(int row, int column);
  void expandTo(int newRowCount, int newColumnCount);
  void insertRow(int newIndex);
  void insertColumn(int newIndex);
  int rowColToIndex(int row, int column) const;
  void indexToRowCol(int index, int &row, int &column) const;
  
protected:
  // property members:
  // 속성 멤버 :
  QList<QList<QCPLayoutElement*> > mElements;
  QList<double> mColumnStretchFactors;
  QList<double> mRowStretchFactors;
  int mColumnSpacing, mRowSpacing;
  int mWrap;
  FillOrder mFillOrder;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void getMinimumRowColSizes(QVector<int> *minColWidths, QVector<int> *minRowHeights) const;
  void getMaximumRowColSizes(QVector<int> *maxColWidths, QVector<int> *maxRowHeights) const;
  
private:
  Q_DISABLE_COPY(QCPLayoutGrid)
};
Q_DECLARE_METATYPE(QCPLayoutGrid::FillOrder)


class QCP_LIB_DECL QCPLayoutInset : public QCPLayout
{
  Q_OBJECT
public:
  /*!
    Defines how the placement and sizing is handled for a certain element in a QCPLayoutInset.
  */
 /* !
    QCPLayoutInset의 특정 요소에 대해 배치 및 크기 조정이 처리되는 방식을 정의합니다.
  */
  enum InsetPlacement { ipFree            ///< The element may be positioned/sized arbitrarily, see \ref setInsetRect
                                          /// <요소가 임의로 배치 / 크기 조정될 수 있습니다. \ ref setInsetRect를 참조하십시오.
                        ,ipBorderAligned  ///< The element is aligned to one of the layout sides, see \ref setInsetAlignment
                      };                  /// <요소가 레이아웃면 중 하나에 정렬됩니다. \ ref setInsetAlignment를 참조하십시오.
  Q_ENUMS(InsetPlacement)
  
  explicit QCPLayoutInset();
  virtual ~QCPLayoutInset();
  
  // getters:
  InsetPlacement insetPlacement(int index) const;
  Qt::Alignment insetAlignment(int index) const;
  QRectF insetRect(int index) const;
  
  // setters:
  void setInsetPlacement(int index, InsetPlacement placement);
  void setInsetAlignment(int index, Qt::Alignment alignment);
  void setInsetRect(int index, const QRectF &rect);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void updateLayout() Q_DECL_OVERRIDE;
  virtual int elementCount() const Q_DECL_OVERRIDE;
  virtual QCPLayoutElement* elementAt(int index) const Q_DECL_OVERRIDE;
  virtual QCPLayoutElement* takeAt(int index) Q_DECL_OVERRIDE;
  virtual bool take(QCPLayoutElement* element) Q_DECL_OVERRIDE;
  virtual void simplify() Q_DECL_OVERRIDE {}
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void addElement(QCPLayoutElement *element, Qt::Alignment alignment);
  void addElement(QCPLayoutElement *element, const QRectF &rect);
  
protected:
  // property members:
  // 속성 멤버 :
  QList<QCPLayoutElement*> mElements;
  QList<InsetPlacement> mInsetPlacement;
  QList<Qt::Alignment> mInsetAlignment;
  QList<QRectF> mInsetRect;
  
private:
  Q_DISABLE_COPY(QCPLayoutInset)
};
Q_DECLARE_METATYPE(QCPLayoutInset::InsetPlacement)

/* end of 'src/layout.h' */


/* including file 'src/lineending.h', size 4426                              */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/
/* 'src / layout.h'의 끝 */


/* 파일 'src / lineending.h'포함, 크기 4426                                */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/

class QCP_LIB_DECL QCPLineEnding
{
  Q_GADGET
public:
  /*!
    Defines the type of ending decoration for line-like items, e.g. an arrow.
    
    \image html QCPLineEnding.png
    
    The width and length of these decorations can be controlled with the functions \ref setWidth
    and \ref setLength. Some decorations like \ref esDisc, \ref esSquare, \ref esDiamond and \ref esBar only
    support a width, the length property is ignored.
    
    \see QCPItemLine::setHead, QCPItemLine::setTail, QCPItemCurve::setHead, QCPItemCurve::setTail, QCPAxis::setLowerEnding, QCPAxis::setUpperEnding
  */
 /* !
    라인과 같은 항목의 끝 장식의 유형을 정의합니다 (예 : 화살표).
    
    \ image html QCPLineEnding.png
    
    이러한 장식의 너비와 길이는 \ ref setWidth 함수를 사용하여 제어 할 수 있습니다.
    및 \ ref setLength. \ ref esDisc, \ ref esSquare, \ ref esDiamond 및 \ ref esBar와 같은 일부 장식
    width를 지원하면 length 속성은 무시됩니다.
    
    \ QCPItemLine :: setHead, QCPItemLine :: setTail, QCPItemCurve :: setHead, QCPItemCurve :: setTail, QCPAxis :: setLowerEnding, QCPAxis :: setUpperEnding을 참조하십시오.
  */
  enum EndingStyle { esNone          ///< No ending decoration
                                     /// <끝 장식 없음
                     ,esFlatArrow    ///< A filled arrow head with a straight/flat back (a triangle)
                                     /// <직선 / 평면 뒤 (삼각형)가있는 채워진 화살표 헤드
                     ,esSpikeArrow   ///< A filled arrow head with an indented back
                                     /// <들여 쓰기 된 뒤쪽이있는 채워진 화살표 헤드
                     ,esLineArrow    ///< A non-filled arrow head with open back
                                     /// < 비어있는     화살표 머리, 오픈 백
                     ,esDisc         ///< A filled circle
                                     /// <채워진 원
                     ,esSquare       ///< A filled square
                                     /// <채워진 사각형
                     ,esDiamond      ///< A filled diamond (45 degrees rotated square)
                                     /// <채워진 다이아몬드 (45도 회전 한 사각형)
                     ,esBar          ///< A bar perpendicular to the line
                                     /// <선에 수직 인 막대
                     ,esHalfBar      ///< A bar perpendicular to the line, pointing out to only one side (to which side can be changed with \ref setInverted)
                                     /// <라인에 수직 인 한 변 (한 변만을 \ ref setInverted로 바꿀 수있는 바)
                     ,esSkewedBar    ///< A bar that is skewed (skew controllable via \ref setLength)
                   };                /// <비뚤어진 막대 (\ ref setLength를 통해 스큐 조절 가능)
  Q_ENUMS(EndingStyle)
  
  QCPLineEnding();
  QCPLineEnding(EndingStyle style, double width=8, double length=10, bool inverted=false);
  
  // getters:
  EndingStyle style() const { return mStyle; }
  double width() const { return mWidth; }
  double length() const { return mLength; }
  bool inverted() const { return mInverted; }
  
  // setters:
  void setStyle(EndingStyle style);
  void setWidth(double width);
  void setLength(double length);
  void setInverted(bool inverted);
  
  // non-property methods:
  // 비 속성 메소드 :
  double boundingDistance() const;
  double realLength() const;
  void draw(QCPPainter *painter, const QCPVector2D &pos, const QCPVector2D &dir) const;
  void draw(QCPPainter *painter, const QCPVector2D &pos, double angle) const;
  
protected:
  // property members:
  // 속성 멤버 :
  EndingStyle mStyle;
  double mWidth, mLength;
  bool mInverted;
};
Q_DECLARE_TYPEINFO(QCPLineEnding, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(QCPLineEnding::EndingStyle)

/* end of 'src/lineending.h' */


/* including file 'src/axis/axisticker.h', size 4177                         */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / lineending.h'의 끝 */


/* 파일 'src / axis / axisticker.h', 크기 4177 포함                          */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */


class QCP_LIB_DECL QCPAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines the strategies that the axis ticker may follow when choosing the size of the tick step.
    
    \see setTickStepStrategy
  */
  /* !
    틱 단계의 크기를 선택할 때 축 티커가 따라 올 수있는 전략을 정의합니다.
    
    \ setTickStepStrategy 참조
  */
  enum TickStepStrategy
  {
    tssReadability    ///< A nicely readable tick step is prioritized over matching the requested number of ticks (see \ref setTickCount)
/// <멋지게 읽을 수있는 틱 단계는 요청 된 틱 수와 일치하는 것보다 우선 순위가 높습니다 (\ ref setTickCount 참조)
    ,tssMeetTickCount ///< Less readable tick steps are allowed which in turn facilitates getting closer to the requested tick count
/// <덜 읽을 수있는 눈금 단계가 허용되어 다시 요청 된 눈금 수에 더 가깝게됩니다
  };
  Q_ENUMS(TickStepStrategy)
  
  QCPAxisTicker();
  virtual ~QCPAxisTicker();
  
  // getters:
  TickStepStrategy tickStepStrategy() const { return mTickStepStrategy; }
  int tickCount() const { return mTickCount; }
  double tickOrigin() const { return mTickOrigin; }
  
  // setters:
  void setTickStepStrategy(TickStepStrategy strategy);
  void setTickCount(int count);
  void setTickOrigin(double origin);
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void generate(const QCPRange &range, const QLocale &locale, QChar formatChar, int precision, QVector<double> &ticks, QVector<double> *subTicks, QVector<QString> *tickLabels);
  
protected:
  // property members:
  // 속성 멤버 :
  TickStepStrategy mTickStepStrategy;
  int mTickCount;
  double mTickOrigin;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range);
  virtual int getSubTickCount(double tickStep);
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision);
  virtual QVector<double> createTickVector(double tickStep, const QCPRange &range);
  virtual QVector<double> createSubTickVector(int subTickCount, const QVector<double> &ticks);
  virtual QVector<QString> createLabelVector(const QVector<double> &ticks, const QLocale &locale, QChar formatChar, int precision);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void trimTicks(const QCPRange &range, QVector<double> &ticks, bool keepOneOutlier) const;
  double pickClosest(double target, const QVector<double> &candidates) const;
  double getMantissa(double input, double *magnitude=0) const;
  double cleanMantissa(double input) const;
};
Q_DECLARE_METATYPE(QCPAxisTicker::TickStepStrategy)
Q_DECLARE_METATYPE(QSharedPointer<QCPAxisTicker>)

/* end of 'src/axis/axisticker.h' */


/* including file 'src/axis/axistickerdatetime.h', size 3289                 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / axis / axisticker.h'의 끝 */


/* 파일 'src / axis / axistickerdatetime.h', 크기 3289 포함                  */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200  */ 


class QCP_LIB_DECL QCPAxisTickerDateTime : public QCPAxisTicker
{
public:
  QCPAxisTickerDateTime();
  
  // getters:
  QString dateTimeFormat() const { return mDateTimeFormat; }
  Qt::TimeSpec dateTimeSpec() const { return mDateTimeSpec; }
  
  // setters:
  void setDateTimeFormat(const QString &format);
  void setDateTimeSpec(Qt::TimeSpec spec);
  void setTickOrigin(double origin); // hides base class method but calls baseclass implementation ("using" throws off IDEs and doxygen)
  void setTickOrigin(const QDateTime &origin);
  
  // static methods:
  // 정적 메소드 :
  static QDateTime keyToDateTime(double key);
  static double dateTimeToKey(const QDateTime dateTime);
  static double dateTimeToKey(const QDate date);
  
protected:
  // property members:
  // 속성 멤버 :
  QString mDateTimeFormat;
  Qt::TimeSpec mDateTimeSpec;
  
  // non-property members:
  // 비 속성 멤버 :
  enum DateStrategy {dsNone, dsUniformTimeInDay, dsUniformDayInMonth} mDateStrategy;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE;
};

/* end of 'src/axis/axistickerdatetime.h' */


/* including file 'src/axis/axistickertime.h', size 3542                     */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / axis / axistickerdatetime.h'의 끝 */


/* 'src / axis / axistickertime.h'파일 포함, 크기 3542                      */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPAxisTickerTime : public QCPAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines the logical units in which fractions of time spans can be expressed.
    
    \see setFieldWidth, setTimeFormat
  */
 /* !
    시간 범위를 표현할 수있는 논리 단위를 정의합니다.
    
    \ setFieldWidth, setTimeFormat을 참조하십시오.
  */
  enum TimeUnit { tuMilliseconds ///< Milliseconds, one thousandth of a second (%%z in \ref setTimeFormat)
                  ,tuSeconds     ///< Seconds (%%s in \ref setTimeFormat)
                  ,tuMinutes     ///< Minutes (%%m in \ref setTimeFormat)
                  ,tuHours       ///< Hours (%%h in \ref setTimeFormat)
                  ,tuDays        ///< Days (%%d in \ref setTimeFormat)
                };
  Q_ENUMS(TimeUnit)
  
  QCPAxisTickerTime();

  // getters:
  QString timeFormat() const { return mTimeFormat; }
  int fieldWidth(TimeUnit unit) const { return mFieldWidth.value(unit); }
  
  // setters:
  void setTimeFormat(const QString &format);
  void setFieldWidth(TimeUnit unit, int width);
  
protected:
  // property members:
  // 속성 멤버 :
  QString mTimeFormat;
  QHash<TimeUnit, int> mFieldWidth;
  
  // non-property members:
  // 비 속성 멤버 :
  TimeUnit mSmallestUnit, mBiggestUnit;
  QHash<TimeUnit, QString> mFormatPattern;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void replaceUnit(QString &text, TimeUnit unit, int value) const;
};
Q_DECLARE_METATYPE(QCPAxisTickerTime::TimeUnit)

/* end of 'src/axis/axistickertime.h' */


/* including file 'src/axis/axistickerfixed.h', size 3308                    */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / axis / axistickertime.h'의 끝 */


/* 파일 'src / axis / axistickerfixed.h', 크기 3308 포함                    */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPAxisTickerFixed : public QCPAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines how the axis ticker may modify the specified tick step (\ref setTickStep) in order to
    control the number of ticks in the axis range.
    
    \see setScaleStrategy
  */
  /* !
    축 티커가 지정된 틱 스텝 (\ ref setTickStep)을 어떻게 수정 하는지를 정의합니다.
    축 범위의 틱 수를 제어합니다.
    
    \ setScaleStrategy 참조
  */

  enum ScaleStrategy { ssNone      ///< Modifications are not allowed, the specified tick step is absolutely fixed. This might cause a high tick density and overlapping labels if the axis range is zoomed out.
/// <수정은 허용되지 않으며 지정된 틱 단계는 절대적으로 수정됩니다. 축 범위가 축소 된 경우 틱 밀도가 높아지고 레이블이 겹칠 수 있습니다.

                       ,ssMultiples ///< An integer multiple of the specified tick step is allowed. The used factor follows the base class properties of \ref setTickStepStrategy and \ref setTickCount.
/// <지정된 틱 단계의 정수 배가 허용됩니다. 사용 된 인수는 \ ref setTickStepStrategy 및 \ ref setTickCount의 기본 클래스 속성을 따릅니다.
                       ,ssPowers    ///< An integer power of the specified tick step is allowed.
                     };             /// <지정된 틱 스텝의 정수 값이 허용됩니다.
  Q_ENUMS(ScaleStrategy)
  
  QCPAxisTickerFixed();
  
  // getters:
  double tickStep() const { return mTickStep; }
  ScaleStrategy scaleStrategy() const { return mScaleStrategy; }
  
  // setters:
  void setTickStep(double step);
  void setScaleStrategy(ScaleStrategy strategy);
  
protected:
  // property members:
  // 속성 멤버 :
  double mTickStep;
  ScaleStrategy mScaleStrategy;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
};
Q_DECLARE_METATYPE(QCPAxisTickerFixed::ScaleStrategy)

/* end of 'src/axis/axistickerfixed.h' */


/* including file 'src/axis/axistickertext.h', size 3085                     */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/
/* 'src / axis / axistickerfixed.h'의 끝 */


/* 파일 'src / axis / axistickertext.h'를 포함하여 크기 3085                 */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/

class QCP_LIB_DECL QCPAxisTickerText : public QCPAxisTicker
{
public:
  QCPAxisTickerText();
  
  // getters:
  QMap<double, QString> &ticks() { return mTicks; }
  int subTickCount() const { return mSubTickCount; }
  
  // setters:
  void setTicks(const QMap<double, QString> &ticks);
  void setTicks(const QVector<double> &positions, const QVector<QString> labels);
  void setSubTickCount(int subTicks);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void clear();
  void addTick(double position, QString label);
  void addTicks(const QMap<double, QString> &ticks);
  void addTicks(const QVector<double> &positions, const QVector<QString> &labels);
  
protected:
  // property members:
  // 속성 멤버 :
  QMap<double, QString> mTicks;
  int mSubTickCount;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE;
  
};

/* end of 'src/axis/axistickertext.h' */


/* including file 'src/axis/axistickerpi.h', size 3911                       */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / axis / axistickertext.h'의 끝 */


/* 'src / axis / axistickerpi.h'파일 포함, 크기 3911                        */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPAxisTickerPi : public QCPAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines how fractions should be displayed in tick labels.
    
    \see setFractionStyle
  */
 /* !
    분수를 틱 레이블로 표시하는 방법을 정의합니다.
    
    \ setFractionStyle 참조
  */
  enum FractionStyle { fsFloatingPoint     ///< Fractions are displayed as regular decimal floating point numbers, e.g. "0.25" or "0.125".
/// <분수는 "0.25"또는 "0.125"와 같이 일반 10 진수 부동 소수점 숫자로 표시됩니다.

                       ,fsAsciiFractions   ///< Fractions are written as rationals using ASCII characters only, e.g. "1/4" or "1/8"
/// <분수는 "1/4"또는 "1/8"과 같이 ASCII 문자 만 사용하여 rationals로 작성됩니다.
                       ,fsUnicodeFractions ///< Fractions are written using sub- and superscript UTF-8 digits and the fraction symbol.
/// <소수는 위와 아래 첨자 UTF-8 숫자와 분수 기호를 사용하여 작성됩니다.
                     };
  Q_ENUMS(FractionStyle)
  
  QCPAxisTickerPi();
  
  // getters:
  QString piSymbol() const { return mPiSymbol; }
  double piValue() const { return mPiValue; }
  bool periodicity() const { return mPeriodicity; }
  FractionStyle fractionStyle() const { return mFractionStyle; }
  
  // setters:
  void setPiSymbol(QString symbol);
  void setPiValue(double pi);
  void setPeriodicity(int multiplesOfPi);
  void setFractionStyle(FractionStyle style);
  
protected:
  // property members:
  // 속성 멤버 :
  QString mPiSymbol;
  double mPiValue;
  int mPeriodicity;
  FractionStyle mFractionStyle;
  
  // non-property members:
  // 비 속성 멤버 :
  double mPiTickStep; // size of one tick step in units of mPiValue
                      // mPiValue 단위로 틱 스텝 하나의 크기
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void simplifyFraction(int &numerator, int &denominator) const;
  QString fractionToString(int numerator, int denominator) const;
  QString unicodeFraction(int numerator, int denominator) const;
  QString unicodeSuperscript(int number) const;
  QString unicodeSubscript(int number) const;
};
Q_DECLARE_METATYPE(QCPAxisTickerPi::FractionStyle)

/* end of 'src/axis/axistickerpi.h' */


/* including file 'src/axis/axistickerlog.h', size 2663                      */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / axis / axistickerpi.h'의 끝 */


/* 파일 'src / axis / axistickerlog.h', 크기 2663 포함                      */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPAxisTickerLog : public QCPAxisTicker
{
public:
  QCPAxisTickerLog();
  
  // getters:
  double logBase() const { return mLogBase; }
  int subTickCount() const { return mSubTickCount; }
  
  // setters:
  void setLogBase(double base);
  void setSubTickCount(int subTicks);
  
protected:
  // property members:
  // 속성 멤버 :
  double mLogBase;
  int mSubTickCount;
  
  // non-property members:
  // 비 속성 멤버 :
  double mLogBaseLnInv;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE;
};

/* end of 'src/axis/axistickerlog.h' */


/* including file 'src/axis/axis.h', size 20634                              */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/
/* 'src / axis / axistickerlog.h'의 끝 */


/* 파일 'src / axis / axis.h', 크기 20634 포함                              */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/

class QCP_LIB_DECL QCPGrid :public QCPLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(bool subGridVisible READ subGridVisible WRITE setSubGridVisible)
  Q_PROPERTY(bool antialiasedSubGrid READ antialiasedSubGrid WRITE setAntialiasedSubGrid)
  Q_PROPERTY(bool antialiasedZeroLine READ antialiasedZeroLine WRITE setAntialiasedZeroLine)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen subGridPen READ subGridPen WRITE setSubGridPen)
  Q_PROPERTY(QPen zeroLinePen READ zeroLinePen WRITE setZeroLinePen)
  /// \endcond
public:
  explicit QCPGrid(QCPAxis *parentAxis);
  
  // getters:
  bool subGridVisible() const { return mSubGridVisible; }
  bool antialiasedSubGrid() const { return mAntialiasedSubGrid; }
  bool antialiasedZeroLine() const { return mAntialiasedZeroLine; }
  QPen pen() const { return mPen; }
  QPen subGridPen() const { return mSubGridPen; }
  QPen zeroLinePen() const { return mZeroLinePen; }
  
  // setters:
  void setSubGridVisible(bool visible);
  void setAntialiasedSubGrid(bool enabled);
  void setAntialiasedZeroLine(bool enabled);
  void setPen(const QPen &pen);
  void setSubGridPen(const QPen &pen);
  void setZeroLinePen(const QPen &pen);
  
protected:
  // property members:
  // 속성 멤버 :
  bool mSubGridVisible;
  bool mAntialiasedSubGrid, mAntialiasedZeroLine;
  QPen mPen, mSubGridPen, mZeroLinePen;
  
  // non-property members:
  // 비 속성 멤버 :
  QCPAxis *mParentAxis;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void drawGridLines(QCPPainter *painter) const;
  void drawSubGridLines(QCPPainter *painter) const;
  
  friend class QCPAxis;
};


class QCP_LIB_DECL QCPAxis : public QCPLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(AxisType axisType READ axisType)
  Q_PROPERTY(QCPAxisRect* axisRect READ axisRect)
  Q_PROPERTY(ScaleType scaleType READ scaleType WRITE setScaleType NOTIFY scaleTypeChanged)
  Q_PROPERTY(QCPRange range READ range WRITE setRange NOTIFY rangeChanged)
  Q_PROPERTY(bool rangeReversed READ rangeReversed WRITE setRangeReversed)
  Q_PROPERTY(QSharedPointer<QCPAxisTicker> ticker READ ticker WRITE setTicker)
  Q_PROPERTY(bool ticks READ ticks WRITE setTicks)
  Q_PROPERTY(bool tickLabels READ tickLabels WRITE setTickLabels)
  Q_PROPERTY(int tickLabelPadding READ tickLabelPadding WRITE setTickLabelPadding)
  Q_PROPERTY(QFont tickLabelFont READ tickLabelFont WRITE setTickLabelFont)
  Q_PROPERTY(QColor tickLabelColor READ tickLabelColor WRITE setTickLabelColor)
  Q_PROPERTY(double tickLabelRotation READ tickLabelRotation WRITE setTickLabelRotation)
  Q_PROPERTY(LabelSide tickLabelSide READ tickLabelSide WRITE setTickLabelSide)
  Q_PROPERTY(QString numberFormat READ numberFormat WRITE setNumberFormat)
  Q_PROPERTY(int numberPrecision READ numberPrecision WRITE setNumberPrecision)
  Q_PROPERTY(QVector<double> tickVector READ tickVector)
  Q_PROPERTY(QVector<QString> tickVectorLabels READ tickVectorLabels)
  Q_PROPERTY(int tickLengthIn READ tickLengthIn WRITE setTickLengthIn)
  Q_PROPERTY(int tickLengthOut READ tickLengthOut WRITE setTickLengthOut)
  Q_PROPERTY(bool subTicks READ subTicks WRITE setSubTicks)
  Q_PROPERTY(int subTickLengthIn READ subTickLengthIn WRITE setSubTickLengthIn)
  Q_PROPERTY(int subTickLengthOut READ subTickLengthOut WRITE setSubTickLengthOut)
  Q_PROPERTY(QPen basePen READ basePen WRITE setBasePen)
  Q_PROPERTY(QPen tickPen READ tickPen WRITE setTickPen)
  Q_PROPERTY(QPen subTickPen READ subTickPen WRITE setSubTickPen)
  Q_PROPERTY(QFont labelFont READ labelFont WRITE setLabelFont)
  Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor)
  Q_PROPERTY(QString label READ label WRITE setLabel)
  Q_PROPERTY(int labelPadding READ labelPadding WRITE setLabelPadding)
  Q_PROPERTY(int padding READ padding WRITE setPadding)
  Q_PROPERTY(int offset READ offset WRITE setOffset)
  Q_PROPERTY(SelectableParts selectedParts READ selectedParts WRITE setSelectedParts NOTIFY selectionChanged)
  Q_PROPERTY(SelectableParts selectableParts READ selectableParts WRITE setSelectableParts NOTIFY selectableChanged)
  Q_PROPERTY(QFont selectedTickLabelFont READ selectedTickLabelFont WRITE setSelectedTickLabelFont)
  Q_PROPERTY(QFont selectedLabelFont READ selectedLabelFont WRITE setSelectedLabelFont)
  Q_PROPERTY(QColor selectedTickLabelColor READ selectedTickLabelColor WRITE setSelectedTickLabelColor)
  Q_PROPERTY(QColor selectedLabelColor READ selectedLabelColor WRITE setSelectedLabelColor)
  Q_PROPERTY(QPen selectedBasePen READ selectedBasePen WRITE setSelectedBasePen)
  Q_PROPERTY(QPen selectedTickPen READ selectedTickPen WRITE setSelectedTickPen)
  Q_PROPERTY(QPen selectedSubTickPen READ selectedSubTickPen WRITE setSelectedSubTickPen)
  Q_PROPERTY(QCPLineEnding lowerEnding READ lowerEnding WRITE setLowerEnding)
  Q_PROPERTY(QCPLineEnding upperEnding READ upperEnding WRITE setUpperEnding)
  Q_PROPERTY(QCPGrid* grid READ grid)
  /// \endcond
public:
  /*!
    Defines at which side of the axis rect the axis will appear. This also affects how the tick
    marks are drawn, on which side the labels are placed etc.
  */
 /* !
    축이 표시 될 축의 어느 측면에 정의할지 정의합니다. 이것은 또한 틱
    라벨이 그려지는 곳에 마크가 그려집니다.
  */
  enum AxisType { atLeft    = 0x01  ///< <tt>0x01</tt> Axis is vertical and on the left side of the axis rect
                                    /// <tt> 0x01 </ tt> 축은 수직이며 축의 왼쪽에있다 rect
                  ,atRight  = 0x02  ///< <tt>0x02</tt> Axis is vertical and on the right side of the axis rect
                                    /// <tt> 0x02 </ tt> 축은 수직이며 축의 오른쪽에있다 rect
                  ,atTop    = 0x04  ///< <tt>0x04</tt> Axis is horizontal and on the top side of the axis rect
                                    /// <<tt> 0x04 </ tt> 축은 수평이며 축 위쪽에 rect
                  ,atBottom = 0x08  ///< <tt>0x08</tt> Axis is horizontal and on the bottom side of the axis rect
                                    /// <0x08 </ tt> 축은 수평이며 축의 아래쪽에 rect  
                };
  Q_ENUMS(AxisType)
  Q_FLAGS(AxisTypes)
  Q_DECLARE_FLAGS(AxisTypes, AxisType)
  /*!
    Defines on which side of the axis the tick labels (numbers) shall appear.
    
    \see setTickLabelSide
  */
/* !
    축의 어느쪽에 눈금 레이블 (숫자)이 나타나는지 정의합니다.
    
    \ setTickLabelSide를 참조하십시오.
  */
  enum LabelSide { lsInside    ///< Tick labels will be displayed inside the axis rect and clipped to the inner axis rect
                               /// <Tick 레이블은 축 rect 내부에 표시되고 내부 축 rect로 잘립니다.
                   ,lsOutside  ///< Tick labels will be displayed outside the axis rect
                               /// <틱 레이블은 축 rect 외부에 표시됩니다.
                 };
  Q_ENUMS(LabelSide)
  /*!
    Defines the scale of an axis.
    \see setScaleType
  */
 /* !
    축의 축척을 정의합니다.
    \ see setScaleType
  */
  enum ScaleType { stLinear       ///< Linear scaling
                                  /// <선형 스케일링
                   ,stLogarithmic ///< Logarithmic scaling with correspondingly transformed axis coordinates (possibly also \ref setTicker to a \ref QCPAxisTickerLog instance).
/// <대응하는 변환 된 축 좌표를 가진 로그 스케일링 (또한 \ ref setTicker를 \ ref QCPAxisTickerLog 인스턴스로도 가능).
                 };

  Q_ENUMS(ScaleType)
  /*!
    Defines the selectable parts of an axis.
    \see setSelectableParts, setSelectedParts
  */
 /* !
    축의 선택 가능한 부분을 정의합니다.
    \ setSelectableParts, setSelectedParts를 참조하십시오.
  */
  enum SelectablePart { spNone        = 0      ///< None of the selectable parts
                                               /// <선택 가능한 부분이 없음
                        ,spAxis       = 0x001  ///< The axis backbone and tick marks
                                               /// <축 백본 및 눈금
                        ,spTickLabels = 0x002  ///< Tick labels (numbers) of this axis (as a whole, not individually)
                                               /// <이 축의 레이블 (숫자)을 틱합니다 (전체적으로, 개별적으로는 안됨)
                        ,spAxisLabel  = 0x004  ///< The axis label
                      };                       /// <축 레이블
  Q_ENUMS(SelectablePart)
  Q_FLAGS(SelectableParts)
  Q_DECLARE_FLAGS(SelectableParts, SelectablePart)
  
  explicit QCPAxis(QCPAxisRect *parent, AxisType type);
  virtual ~QCPAxis();
  
  // getters:
  AxisType axisType() const { return mAxisType; }
  QCPAxisRect *axisRect() const { return mAxisRect; }
  ScaleType scaleType() const { return mScaleType; }
  const QCPRange range() const { return mRange; }
  bool rangeReversed() const { return mRangeReversed; }
  QSharedPointer<QCPAxisTicker> ticker() const { return mTicker; }
  bool ticks() const { return mTicks; }
  bool tickLabels() const { return mTickLabels; }
  int tickLabelPadding() const;
  QFont tickLabelFont() const { return mTickLabelFont; }
  QColor tickLabelColor() const { return mTickLabelColor; }
  double tickLabelRotation() const;
  LabelSide tickLabelSide() const;
  QString numberFormat() const;
  int numberPrecision() const { return mNumberPrecision; }
  QVector<double> tickVector() const { return mTickVector; }
  QVector<QString> tickVectorLabels() const { return mTickVectorLabels; }
  int tickLengthIn() const;
  int tickLengthOut() const;
  bool subTicks() const { return mSubTicks; }
  int subTickLengthIn() const;
  int subTickLengthOut() const;
  QPen basePen() const { return mBasePen; }
  QPen tickPen() const { return mTickPen; }
  QPen subTickPen() const { return mSubTickPen; }
  QFont labelFont() const { return mLabelFont; }
  QColor labelColor() const { return mLabelColor; }
  QString label() const { return mLabel; }
  int labelPadding() const;
  int padding() const { return mPadding; }
  int offset() const;
  SelectableParts selectedParts() const { return mSelectedParts; }
  SelectableParts selectableParts() const { return mSelectableParts; }
  QFont selectedTickLabelFont() const { return mSelectedTickLabelFont; }
  QFont selectedLabelFont() const { return mSelectedLabelFont; }
  QColor selectedTickLabelColor() const { return mSelectedTickLabelColor; }
  QColor selectedLabelColor() const { return mSelectedLabelColor; }
  QPen selectedBasePen() const { return mSelectedBasePen; }
  QPen selectedTickPen() const { return mSelectedTickPen; }
  QPen selectedSubTickPen() const { return mSelectedSubTickPen; }
  QCPLineEnding lowerEnding() const;
  QCPLineEnding upperEnding() const;
  QCPGrid *grid() const { return mGrid; }
  
  // setters:
  Q_SLOT void setScaleType(QCPAxis::ScaleType type);
  Q_SLOT void setRange(const QCPRange &range);
  void setRange(double lower, double upper);
  void setRange(double position, double size, Qt::AlignmentFlag alignment);
  void setRangeLower(double lower);
  void setRangeUpper(double upper);
  void setRangeReversed(bool reversed);
  void setTicker(QSharedPointer<QCPAxisTicker> ticker);
  void setTicks(bool show);
  void setTickLabels(bool show);
  void setTickLabelPadding(int padding);
  void setTickLabelFont(const QFont &font);
  void setTickLabelColor(const QColor &color);
  void setTickLabelRotation(double degrees);
  void setTickLabelSide(LabelSide side);
  void setNumberFormat(const QString &formatCode);
  void setNumberPrecision(int precision);
  void setTickLength(int inside, int outside=0);
  void setTickLengthIn(int inside);
  void setTickLengthOut(int outside);
  void setSubTicks(bool show);
  void setSubTickLength(int inside, int outside=0);
  void setSubTickLengthIn(int inside);
  void setSubTickLengthOut(int outside);
  void setBasePen(const QPen &pen);
  void setTickPen(const QPen &pen);
  void setSubTickPen(const QPen &pen);
  void setLabelFont(const QFont &font);
  void setLabelColor(const QColor &color);
  void setLabel(const QString &str);
  void setLabelPadding(int padding);
  void setPadding(int padding);
  void setOffset(int offset);
  void setSelectedTickLabelFont(const QFont &font);
  void setSelectedLabelFont(const QFont &font);
  void setSelectedTickLabelColor(const QColor &color);
  void setSelectedLabelColor(const QColor &color);
  void setSelectedBasePen(const QPen &pen);
  void setSelectedTickPen(const QPen &pen);
  void setSelectedSubTickPen(const QPen &pen);
  Q_SLOT void setSelectableParts(const QCPAxis::SelectableParts &selectableParts);
  Q_SLOT void setSelectedParts(const QCPAxis::SelectableParts &selectedParts);
  void setLowerEnding(const QCPLineEnding &ending);
  void setUpperEnding(const QCPLineEnding &ending);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  // non-property methods:
  // 비 속성 메소드 :
  Qt::Orientation orientation() const { return mOrientation; }
  int pixelOrientation() const { return rangeReversed() != (orientation()==Qt::Vertical) ? -1 : 1; }
  void moveRange(double diff);
  void scaleRange(double factor);
  void scaleRange(double factor, double center);
  void setScaleRatio(const QCPAxis *otherAxis, double ratio=1.0);
  void rescale(bool onlyVisiblePlottables=false);
  double pixelToCoord(double value) const;
  double coordToPixel(double value) const;
  SelectablePart getPartAt(const QPointF &pos) const;
  QList<QCPAbstractPlottable*> plottables() const;
  QList<QCPGraph*> graphs() const;
  QList<QCPAbstractItem*> items() const;
  
  static AxisType marginSideToAxisType(QCP::MarginSide side);
  static Qt::Orientation orientation(AxisType type) { return type==atBottom||type==atTop ? Qt::Horizontal : Qt::Vertical; }
  static AxisType opposite(AxisType type);
  
signals:
  void rangeChanged(const QCPRange &newRange);
  void rangeChanged(const QCPRange &newRange, const QCPRange &oldRange);
  void scaleTypeChanged(QCPAxis::ScaleType scaleType);
  void selectionChanged(const QCPAxis::SelectableParts &parts);
  void selectableChanged(const QCPAxis::SelectableParts &parts);

protected:
  // property members:
  // axis base:
  // 속성 멤버 :
  // 축베이스 :
  AxisType mAxisType;
  QCPAxisRect *mAxisRect;
  //int mOffset; // in QCPAxisPainter
  int mPadding;
  Qt::Orientation mOrientation;
  SelectableParts mSelectableParts, mSelectedParts;
  QPen mBasePen, mSelectedBasePen;
  //QCPLineEnding mLowerEnding, mUpperEnding; // in QCPAxisPainter
  // axis label:
  // 축 레이블 :
  //int mLabelPadding; // in QCPAxisPainter
  QString mLabel;
  QFont mLabelFont, mSelectedLabelFont;
  QColor mLabelColor, mSelectedLabelColor;
  // tick labels:
  // 눈금 표시 :
  //int mTickLabelPadding; // in QCPAxisPainter
  bool mTickLabels;
  //double mTickLabelRotation; // in QCPAxisPainter
  QFont mTickLabelFont, mSelectedTickLabelFont;
  QColor mTickLabelColor, mSelectedTickLabelColor;
  int mNumberPrecision;
  QLatin1Char mNumberFormatChar;
  bool mNumberBeautifulPowers;
  //bool mNumberMultiplyCross; // QCPAxisPainter
  // ticks and subticks:
  // 틱 및 하위 태그 :
  bool mTicks;
  bool mSubTicks;
  //int mTickLengthIn, mTickLengthOut, mSubTickLengthIn, mSubTickLengthOut; // QCPAxisPainter
  QPen mTickPen, mSelectedTickPen;
  QPen mSubTickPen, mSelectedSubTickPen;
  // scale and range:
  // 축척 및 범위 :
  QCPRange mRange;
  bool mRangeReversed;
  ScaleType mScaleType;
  
  // non-property members:
  // 비 속성 멤버 :
  QCPGrid *mGrid;
  QCPAxisPainterPrivate *mAxisPainter;
  QSharedPointer<QCPAxisTicker> mTicker;
  QVector<double> mTickVector;
  QVector<QString> mTickVectorLabels;
  QVector<double> mSubTickVector;
  bool mCachedMarginValid;
  int mCachedMargin;
  bool mDragging;
  QCPRange mDragStartRange;
  QCP::AntialiasedElements mAADragBackup, mNotAADragBackup;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual int calculateMargin();
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QCP::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  // mouse events:
  // 마우스 이벤트 :
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details);
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos);
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos);
  virtual void wheelEvent(QWheelEvent *event);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void setupTickVectors();
  QPen getBasePen() const;
  QPen getTickPen() const;
  QPen getSubTickPen() const;
  QFont getTickLabelFont() const;
  QFont getLabelFont() const;
  QColor getTickLabelColor() const;
  QColor getLabelColor() const;
  
private:
  Q_DISABLE_COPY(QCPAxis)
  
  friend class QCustomPlot;
  friend class QCPGrid;
  friend class QCPAxisRect;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QCPAxis::SelectableParts)
Q_DECLARE_OPERATORS_FOR_FLAGS(QCPAxis::AxisTypes)
Q_DECLARE_METATYPE(QCPAxis::AxisType)
Q_DECLARE_METATYPE(QCPAxis::LabelSide)
Q_DECLARE_METATYPE(QCPAxis::ScaleType)
Q_DECLARE_METATYPE(QCPAxis::SelectablePart)


class QCPAxisPainterPrivate
{
public:
  explicit QCPAxisPainterPrivate(QCustomPlot *parentPlot);
  virtual ~QCPAxisPainterPrivate();
  
  virtual void draw(QCPPainter *painter);
  virtual int size() const;
  void clearCache();
  
  QRect axisSelectionBox() const { return mAxisSelectionBox; }
  QRect tickLabelsSelectionBox() const { return mTickLabelsSelectionBox; }
  QRect labelSelectionBox() const { return mLabelSelectionBox; }
  
  // public property members:
  // 공공의 속성 멤버 :
  QCPAxis::AxisType type;
  QPen basePen;
  QCPLineEnding lowerEnding, upperEnding; // directly accessed by QCPAxis setters/getters
                                          // QCPAxis setters / getters에서 직접 액세스합니다.
  int labelPadding; // directly accessed by QCPAxis setters/getters
  QFont labelFont;  // QCPAxis setters / getters에서 직접 액세스합니다.
  QColor labelColor;
  QString label;
  int tickLabelPadding; // directly accessed by QCPAxis setters/getters
                        // QCPAxis setters / getters에서 직접 액세스합니다.
  double tickLabelRotation; // directly accessed by QCPAxis setters/getters
                            // QCPAxis setters / getters에서 직접 액세스합니다.
  QCPAxis::LabelSide tickLabelSide; // directly accessed by QCPAxis setters/getters
  bool substituteExponent;          // QCPAxis setters / getters에서 직접 액세스합니다.
  bool numberMultiplyCross; // directly accessed by QCPAxis setters/getters
                            // QCPAxis setters / getters에서 직접 액세스합니다.
  int tickLengthIn, tickLengthOut, subTickLengthIn, subTickLengthOut; // directly accessed by QCPAxis setters/getters
  QPen tickPen, subTickPen;                                           // QCPAxis setters / getters에서 직접 액세스합니다.
  QFont tickLabelFont;
  QColor tickLabelColor;
  QRect axisRect, viewportRect;
  double offset;                 // directly accessed by QCPAxis setters/getters
  bool abbreviateDecimalPowers;  // QCPAxis setters / getters에서 직접 액세스합니다.
  bool reversedEndings;
  
  QVector<double> subTickPositions;
  QVector<double> tickPositions;
  QVector<QString> tickLabels;
  
protected:
  struct CachedLabel
  {
    QPointF offset;
    QPixmap pixmap;
  };
  struct TickLabelData
  {
    QString basePart, expPart, suffixPart;
    QRect baseBounds, expBounds, suffixBounds, totalBounds, rotatedTotalBounds;
    QFont baseFont, expFont;
  };
  QCustomPlot *mParentPlot;
  QByteArray mLabelParameterHash;           // to determine whether mLabelCache needs to be cleared due to changed parameters
  QCache<QString, CachedLabel> mLabelCache; // 변경된 매개 변수로 인해 mLabelCache를 삭제해야하는지 여부를 결정합니다.
  QRect mAxisSelectionBox, mTickLabelsSelectionBox, mLabelSelectionBox;
  
  virtual QByteArray generateLabelParameterHash() const;
  
  virtual void placeTickLabel(QCPPainter *painter, double position, int distanceToAxis, const QString &text, QSize *tickLabelsSize);
  virtual void drawTickLabel(QCPPainter *painter, double x, double y, const TickLabelData &labelData) const;
  virtual TickLabelData getTickLabelData(const QFont &font, const QString &text) const;
  virtual QPointF getTickLabelDrawOffset(const TickLabelData &labelData) const;
  virtual void getMaxTickLabelSize(const QFont &font, const QString &text, QSize *tickLabelsSize) const;
};

/* end of 'src/axis/axis.h' */


/* including file 'src/scatterstyle.h', size 7275                            */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / axis / axis.h'의 끝 */


/* 파일 'src / scatterstyle.h'포함, 크기 7275                               */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPScatterStyle
{
  Q_GADGET
public:
  /*!
    Represents the various properties of a scatter style instance. For example, this enum is used
    to specify which properties of \ref QCPSelectionDecorator::setScatterStyle will be used when
    highlighting selected data points.

    Specific scatter properties can be transferred between \ref QCPScatterStyle instances via \ref
    setFromOther.
  */
 /* !
    스 캐터 스타일 인스턴스의 다양한 속성을 나타냅니다. 예를 들어이 열거 형은
    \ ref QCPSelectionDecorator :: setScatterStyle의 속성을 지정할 때 사용됩니다.
    선택한 데이터 포인트를 강조 표시합니다.
    \ ref를 통해 \ ref QCPScatterStyle 인스턴스간에 특정 분산 속성을 전송할 수 있습니다.
    setFromOther.
  */
  enum ScatterProperty { spNone  = 0x00  ///< <tt>0x00</tt> None
                                         /// < 0x0 > </ tt> 없음
                         ,spPen   = 0x01  ///< <tt>0x01</tt> The pen property, see \ref setPen
                                          /// <tt> 0x01 </ tt> 펜 속성은 \ ref setPen을 참조하십시오.
                         ,spBrush = 0x02  ///< <tt>0x02</tt> The brush property, see \ref setBrush
                                          /// <tt> 0x02 </ tt> brush 속성은 \ ref setBrush를 참조하십시오.
                         ,spSize  = 0x04  ///< <tt>0x04</tt> The size property, see \ref setSize
                                          /// <tt> 0x04 </ tt> size 속성은 \ ref setSize를 참조하십시오.
                         ,spShape = 0x08  ///< <tt>0x08</tt> The shape property, see \ref setShape
                                          /// <0x08 </ tt> 모양 속성은 \ ref를 참조하십시오 setShape
                         ,spAll   = 0xFF  ///< <tt>0xFF</tt> All properties
                                          /// <<tt> 0xFF </ tt> 모든 속성
                       };

  Q_ENUMS(ScatterProperty)
  Q_FLAGS(ScatterProperties)
  Q_DECLARE_FLAGS(ScatterProperties, ScatterProperty)

  /*!
    Defines the shape used for scatter points.

    On plottables/items that draw scatters, the sizes of these visualizations (with exception of
    \ref ssDot and \ref ssPixmap) can be controlled with the \ref setSize function. Scatters are
    drawn with the pen and brush specified with \ref setPen and \ref setBrush.
  */
 /* !
    스 캐터 포인트에 사용되는 모양을 정의합니다.
    스프 래트를 그리는 플롯 테이블 / 항목에서 이러한 시각화의 크기는 (
    \ ref ssDot 및 \ ref ssPixmap)은 \ ref setSize 함수로 제어 할 수 있습니다. 흩어진 자들은
    \ ref setPen과 \ ref setBrush로 지정된 펜과 브러쉬로 그려진다.
  */
  enum ScatterShape { ssNone       ///< no scatter symbols are drawn (e.g. in QCPGraph, data only represented with lines)
                                   /// <scatter 기호가 그려지지 않습니다 (예 : QCPGraph에서는 선으로 만 표시되는 데이터).
                      ,ssDot       ///< \enumimage{ssDot.png} a single pixel (use \ref ssDisc or \ref ssCircle if you want a round shape with a certain radius) /// </ enumimage {ssDot.png} 단일 픽셀 (특정 반경을 가진 원형을 원할 경우 \ ref ssDisc 또는 \ ref ssCircle 사용)
                      ,ssCross     ///< \enumimage{ssCross.png} a cross
                                   // / <\ enumimage {ssCross.png} 십자가
                      ,ssPlus      ///< \enumimage{ssPlus.png} a plus
                                   // / <\ enumimage {ssPlus.png} a plus
                      ,ssCircle    ///< \enumimage{ssCircle.png} a circle
                                   /// <\ enumimage {ssCircle.png} 원
                      ,ssDisc      ///< \enumimage{ssDisc.png} a circle which is filled with the pen's color (not the brush as with ssCircle)                     /// <\ enumimage {ssDisc.png} 펜 색상으로 채워진 원 (ssCircle과 같이 브러시가 아닙니다)
                      ,ssSquare    ///< \enumimage{ssSquare.png} a square
                                   /// <\ enumimage {ssSquare.png} 정사각형
                      ,ssDiamond   ///< \enumimage{ssDiamond.png} a diamond
                                   /// <\ enumimage {ssDiamond.png} a diamond
                      ,ssStar      ///< \enumimage{ssStar.png} a star with eight arms, i.e. a combination of cross and plus
                                   /// <\ enumimage {ssStar.png} 8 개의 팔이있는 별, 즉 십자가와 플러스의 조합
                      ,ssTriangle  ///< \enumimage{ssTriangle.png} an equilateral triangle, standing on baseline
                                   /// <\ enumimage {ssTriangle.png} 정삼각형, 기준선 위에 서 있음
                      ,ssTriangleInverted ///< \enumimage{ssTriangleInverted.png} an equilateral triangle, standing on corner
                                          /// <\ enumimage {ssTriangleInverted.png} 코너에 서있는 정삼각형
                      ,ssCrossSquare      ///< \enumimage{ssCrossSquare.png} a square with a cross inside
                                          /// <\ enumimage {ssCrossSquare.png} 십자가가있는 정사각형
                      ,ssPlusSquare       ///< \enumimage{ssPlusSquare.png} a square with a plus inside
                                          /// <\ enumimage {ssPlusSquare.png} 내부에 정사각형이있는 사각형
                      ,ssCrossCircle      ///< \enumimage{ssCrossCircle.png} a circle with a cross inside
                                          /// <\ enumimage {ssCrossCircle.png} 십자가가있는 원
                      ,ssPlusCircle       ///< \enumimage{ssPlusCircle.png} a circle with a plus inside
                                          /// <\ enumimage {ssPlusCircle.png} 내부에 더하기가있는 원
                      ,ssPeace     ///< \enumimage{ssPeace.png} a circle, with one vertical and two downward diagonal lines
                                   /// <\ enumimage {ssPeace.png} 한 개의 수직선과 두 개의 아래쪽 대각선이있는 원
                      ,ssPixmap    ///< a custom pixmap specified by \ref setPixmap, centered on the data point coordinates
                                   /// <데이터 포인트 좌표를 중심으로 \ ref setPixmap에 지정된 사용자 정의 픽스맵
                      ,ssCustom    ///< custom painter operations are performed per scatter (As QPainterPath, see \ref setCustomPath)                     /// <사용자 정의 페인터 작업은 스 캐터마다 수행됩니다 (QPainterPath처럼 \ ref setCustomPath 참조)

                    };
  Q_ENUMS(ScatterShape)

  QCPScatterStyle();
  QCPScatterStyle(ScatterShape shape, double size=6);
  QCPScatterStyle(ScatterShape shape, const QColor &color, double size);
  QCPScatterStyle(ScatterShape shape, const QColor &color, const QColor &fill, double size);
  QCPScatterStyle(ScatterShape shape, const QPen &pen, const QBrush &brush, double size);
  QCPScatterStyle(const QPixmap &pixmap);
  QCPScatterStyle(const QPainterPath &customPath, const QPen &pen, const QBrush &brush=Qt::NoBrush, double size=6);
  
  // getters:
  double size() const { return mSize; }
  ScatterShape shape() const { return mShape; }
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  QPixmap pixmap() const { return mPixmap; }
  QPainterPath customPath() const { return mCustomPath; }

  // setters:
  void setFromOther(const QCPScatterStyle &other, ScatterProperties properties);
  void setSize(double size);
  void setShape(ScatterShape shape);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setPixmap(const QPixmap &pixmap);
  void setCustomPath(const QPainterPath &customPath);

  // non-property methods:
  // 비 속성 메소드 :
  bool isNone() const { return mShape == ssNone; }
  bool isPenDefined() const { return mPenDefined; }
  void undefinePen();
  void applyTo(QCPPainter *painter, const QPen &defaultPen) const;
  void drawShape(QCPPainter *painter, const QPointF &pos) const;
  void drawShape(QCPPainter *painter, double x, double y) const;

protected:
  // property members:
  // 속성 멤버 :
  double mSize;
  ScatterShape mShape;
  QPen mPen;
  QBrush mBrush;
  QPixmap mPixmap;
  QPainterPath mCustomPath;
  
  // non-property members:
  // 비 속성 멤버 :
  bool mPenDefined;
};
Q_DECLARE_TYPEINFO(QCPScatterStyle, Q_MOVABLE_TYPE);
Q_DECLARE_OPERATORS_FOR_FLAGS(QCPScatterStyle::ScatterProperties)
Q_DECLARE_METATYPE(QCPScatterStyle::ScatterProperty)
Q_DECLARE_METATYPE(QCPScatterStyle::ScatterShape)

/* end of 'src/scatterstyle.h' */


/* including file 'src/datacontainer.h', size 4596                           */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

/*! \relates QCPDataContainer
  Returns whether the sort key of \a a is less than the sort key of \a b.

  \see QCPDataContainer::sort
*/
/* 'src / scatterstyle.h'의 끝 */


/* 파일 'src / datacontainer.h'포함, 크기 4596                            */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

/* ! \ 관련 QCPDataContainer
  \ aa의 소트 키가 \ a의 소트 키보다 작은 지 어떤지를 반환합니다. b.
  \ see QCPDataContainer :: sort
*/
template <class DataType>
inline bool qcpLessThanSortKey(const DataType &a, const DataType &b) { return a.sortKey() < b.sortKey(); }

template <class DataType>
class QCPDataContainer // no QCP_LIB_DECL, template class ends up in header (cpp included below)
{                      // QCP_LIB_DECL 없음, 템플릿 클래스가 헤더로 끝남 (아래 포함 된 cpp)
public:
  typedef typename QVector<DataType>::const_iterator const_iterator;
  typedef typename QVector<DataType>::iterator iterator;
  
  QCPDataContainer();
  
  // getters:
  int size() const { return mData.size()-mPreallocSize; }
  bool isEmpty() const { return size() == 0; }
  bool autoSqueeze() const { return mAutoSqueeze; }
  
  // setters:
  void setAutoSqueeze(bool enabled);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void set(const QCPDataContainer<DataType> &data);
  void set(const QVector<DataType> &data, bool alreadySorted=false);
  void add(const QCPDataContainer<DataType> &data);
  void add(const QVector<DataType> &data, bool alreadySorted=false);
  void add(const DataType &data);
  void removeBefore(double sortKey);
  void removeAfter(double sortKey);
  void remove(double sortKeyFrom, double sortKeyTo);
  void remove(double sortKey);
  void clear();
  void sort();
  void squeeze(bool preAllocation=true, bool postAllocation=true);
  
  const_iterator constBegin() const { return mData.constBegin()+mPreallocSize; }
  const_iterator constEnd() const { return mData.constEnd(); }
  iterator begin() { return mData.begin()+mPreallocSize; }
  iterator end() { return mData.end(); }
  const_iterator findBegin(double sortKey, bool expandedRange=true) const;
  const_iterator findEnd(double sortKey, bool expandedRange=true) const;
  const_iterator at(int index) const { return constBegin()+qBound(0, index, size()); }
  QCPRange keyRange(bool &foundRange, QCP::SignDomain signDomain=QCP::sdBoth);
  QCPRange valueRange(bool &foundRange, QCP::SignDomain signDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange());
  QCPDataRange dataRange() const { return QCPDataRange(0, size()); }
  void limitIteratorsToDataRange(const_iterator &begin, const_iterator &end, const QCPDataRange &dataRange) const;
  
protected:
  // property members:
  // 속성 멤버 :
  bool mAutoSqueeze;
  
  // non-property memebers:
  QVector<DataType> mData;
  int mPreallocSize;
  int mPreallocIteration;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void preallocateGrow(int minimumPreallocSize);
  void performAutoSqueeze();
};

// include implementation in header since it is a class template:

/* including file 'src/datacontainer.cpp', size 31349                        */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

// 클래스 템플릿이므로 헤더에 구현을 포함시킵니다.

/* 파일 'src / datacontainer.cpp', 크기 31349 포함                          */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPDataContainer
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPDataContainer
  \brief The generic data container for one-dimensional plottables

  This class template provides a fast container for data storage of one-dimensional data. The data
  type is specified as template parameter (called \a DataType in the following) and must provide
  some methods as described in the \ref qcpdatacontainer-datatype "next section".

  The data is stored in a sorted fashion, which allows very quick lookups by the sorted key as well
  as retrieval of ranges (see \ref findBegin, \ref findEnd, \ref keyRange) using binary search. The
  container uses a preallocation and a postallocation scheme, such that appending and prepending
  data (with respect to the sort key) is very fast and minimizes reallocations. If data is added
  which needs to be inserted between existing keys, the merge usually can be done quickly too,
  using the fact that existing data is always sorted. The user can further improve performance by
  specifying that added data is already itself sorted by key, if he can guarantee that this is the
  case (see for example \ref add(const QVector<DataType> &data, bool alreadySorted)).

  The data can be accessed with the provided const iterators (\ref constBegin, \ref constEnd). If
  it is necessary to alter existing data in-place, the non-const iterators can be used (\ref begin,
  \ref end). Changing data members that are not the sort key (for most data types called \a key) is
  safe from the container's perspective.

  Great care must be taken however if the sort key is modified through the non-const iterators. For
  performance reasons, the iterators don't automatically cause a re-sorting upon their
  manipulation. It is thus the responsibility of the user to leave the container in a sorted state
  when finished with the data manipulation, before calling any other methods on the container. A
  complete re-sort (e.g. after finishing all sort key manipulation) can be done by calling \ref
  sort. Failing to do so can not be detected by the container efficiently and will cause both
  rendering artifacts and potential data loss.

  Implementing one-dimensional plottables that make use of a \ref QCPDataContainer<T> is usually
  done by subclassing from \ref QCPAbstractPlottable1D "QCPAbstractPlottable1D<T>", which
  introduces an according \a mDataContainer member and some convenience methods.

  \section qcpdatacontainer-datatype Requirements for the DataType template parameter

  The template parameter <tt>DataType</tt> is the type of the stored data points. It must be
  trivially copyable and have the following public methods, preferably inline:

  \li <tt>double sortKey() const</tt>\n Returns the member variable of this data point that is the
  sort key, defining the ordering in the container. Often this variable is simply called \a key.

  \li <tt>static DataType fromSortKey(double sortKey)</tt>\n Returns a new instance of the data
  type initialized with its sort key set to \a sortKey.

  \li <tt>static bool sortKeyIsMainKey()</tt>\n Returns true if the sort key is equal to the main
  key (see method \c mainKey below). For most plottables this is the case. It is not the case for
  example for \ref QCPCurve, which uses \a t as sort key and \a key as main key. This is the reason
  why QCPCurve unlike QCPGraph can display parametric curves with loops.

  \li <tt>double mainKey() const</tt>\n Returns the variable of this data point considered the main
  key. This is commonly the variable that is used as the coordinate of this data point on the key
  axis of the plottable. This method is used for example when determining the automatic axis
  rescaling of key axes (\ref QCPAxis::rescale).

  \li <tt>double mainValue() const</tt>\n Returns the variable of this data point considered the
  main value. This is commonly the variable that is used as the coordinate of this data point on
  the value axis of the plottable.

  \li <tt>QCPRange valueRange() const</tt>\n Returns the range this data point spans in the value
  axis coordinate. If the data is single-valued (e.g. QCPGraphData), this is simply a range with
  both lower and upper set to the main data point value. However if the data points can represent
  multiple values at once (e.g QCPFinancialData with its \a high, \a low, \a open and \a close
  values at each \a key) this method should return the range those values span. This method is used
  for example when determining the automatic axis rescaling of value axes (\ref
  QCPAxis::rescale).
*/
/* ! \ class QCPDataContainer
  \ brief 1 차원 Plotables를위한 일반적인 데이터 컨테이너
  이 클래스 템플릿은 1 차원 데이터의 데이터 저장을위한 빠른 컨테이너를 제공합니다. 자료
  type은 템플릿 매개 변수로 지정되며 (다음에서 \ a DataType이라고 함)
  \ ref qcpdatacontainer-datatype "다음 섹션"에 설명 된 일부 방법.
  데이터는 정렬 된 방식으로 저장되므로 정렬 된 키로 매우 빠르게 조회 할 수 있습니다.
  이진 검색을 사용하여 범위 검색 (\ ref findBegin, \ ref findEnd, \ ref keyRange 참조). 그만큼
  container는 preallocation과 postallocation scheme을 사용한다.
  데이터 (정렬 키와 관련하여)는 매우 빠르며 재 할당을 최소화합니다. 데이터가 추가되면
  기존 키 사이에 삽입해야하는 경우 병합은 대개 신속하게 수행 할 수 있습니다.
  기존 데이터가 항상 정렬된다는 사실을 사용합니다. 사용자는
  추가 된 데이터가 키에 의해 이미 정렬되어 있음을 지정합니다.
  case (예 : \ ref add (const QVector <DataType> & data, bool alreadySorted) 참조)를 참조하십시오.
  제공된 const 반복자 (\ ref constBegin, \ ref constEnd)를 사용하여 데이터에 액세스 할 수 있습니다. 만약
  기존의 데이터를 그 자리에서 변경해야하며 비 const 반복기를 사용할 수 있습니다 (\ ref begin,
  \ ref end). 정렬 키가 아닌 데이터 멤버 변경 (\ 키와 같은 대부분의 데이터 유형의 경우)
  컨테이너의 관점에서 안전하다.
  그러나 정렬 키가 비 const 반복자를 통해 수정되는 경우 매우주의해야합니다. 에 대한
  성능상의 이유로 인해 반복기는 자동으로 다시 정렬하지 않습니다.
  시장 조작. 따라서 컨테이너를 정렬 된 상태로 두는 것은 사용자의 책임입니다
  컨테이너에서 다른 메소드를 호출하기 전에 데이터 조작이 끝나면 에이
  완전한 정렬 (예 : 모든 정렬 키 조작을 완료 한 후)은 \ ref를 호출하여 수행 할 수 있습니다
  종류. 그렇게하지 않으면 컨테이너가 효율적으로 감지 할 수 없으며 두 가지 원인이됩니다.
  유물 렌더링 및 잠재적 인 데이터 손실을 방지합니다.
  \ ref QCPDataContainer <T>를 사용하는 1 차원 Plotables 구현은 대개
  \ ref QCPAbstractPlottable1D "QCPAbstractPlottable1D <T>"에서 서브 클래 싱하여
  mDataContainer 멤버 및 편리한 메서드를 소개합니다.
  \ section qcpdatacontainer-datatype DataType 템플릿 매개 변수에 대한 요구 사항
  템플릿 매개 변수 <tt> DataType </ tt>은 저장된 데이터 요소의 유형입니다. 그것은 있어야합니다.
  쉽게 복사 할 수 있으며 다음과 같은 공개 방법을 사용하는 것이 좋습니다.
  \ li <tt> double sortKey () const </ tt> \ n이 데이터 포인트의 멤버 변수를 반환합니다.
  정렬 키로 컨테이너의 순서를 정의합니다. 흔히이 변수는 단순히 \ a 키라고 불립니다.
  \ li <tt> 고정 데이터 유형 fromSortKey (double sortKey) </ tt> \ n 데이터의 새 인스턴스를 반환합니다.
  정렬 키를 \ a sortKey로 설정하여 초기화 된 유형
  \ li <tt> 정적 bool sortKeyIsMainKey () </ tt> \ n 정렬 키가 main과 동일한 경우 true를 반환합니다.
  key (아래 메소드 \ c mainkey를 보라). 대부분의 plottables의 경우이 경우입니다. 그것은 사실이 아니다.
  예를 들어 \ ref QCPCurve는 \ at를 정렬 키로 사용하고 \ key를 기본 키로 사용합니다. 이것이 이유 다
  QCPCurve가 QCPGraph와 달리 QCPCurve가 루프가있는 매개 변수 곡선을 표시 할 수있는 이유는 무엇입니까?
  \ li <tt> double mainKey () const </ tt> \ n이 데이터 포인트의 변수를 main
  키. 이것은 일반적으로 키에서이 데이터 포인트의 좌표로 사용되는 변수입니다
  플롯 테이블의 축. 이 방법은 예를 들어 자동 축을 결정할 때 사용됩니다.
  키 축의 재 스케일링 (\ ref QCPAxis :: rescale).
  \ li <tt> double mainValue () const </ tt> \ n이 데이터 포인트의 변수를
  주 값. 일반적으로이 데이터 요소의 좌표로 사용되는 변수입니다.
  plottable의 값의 축
  \ li <tt> QCPRange valueRange () const </ tt> \ n이 데이터 포인트가 값 범위에 걸쳐있는 범위를 반환합니다.
  축 좌표. 데이터가 단일 값 (예 : QCPGraphData) 인 경우이 값은
  아래쪽과 위쪽 모두 주 데이터 포인트 값으로 설정됩니다. 그러나 데이터 요소가
  한 번에 여러 값 (예 : QCPFinancialData의 \ a 높음, \ a 낮음, \ a 열린 및 \ 닫기
  각 키의 값),이 메소드는 그러한 값의 범위를 돌려줍니다. 이 방법이 사용됩니다.
  예를 들어 값 축의 자동 축 리 스케일링을 결정할 때 (\ ref
  QCPAxis :: rescale).
*/
/* start documentation of inline functions */
/* 인라인 함수의 시작 문서 */

/*! \fn int QCPDataContainer<DataType>::size() const
  
  Returns the number of data points in the container.
*/
/* ! \ fn int QCPDataContainer <DataType> :: size () const
  
  컨테이너에있는 데이터 요소의 수를 반환합니다.
*/

/*! \fn bool QCPDataContainer<DataType>::isEmpty() const
  
  Returns whether this container holds no data points.
*/
/* ! \ fn bool QCPDataContainer <DataType> :: isEmpty () const
  
  이 컨테이너가 데이터 포인트를 보관 유지하고 있을지 어떨지를 돌려줍니다.
*/

/*! \fn QCPDataContainer::const_iterator QCPDataContainer<DataType>::constBegin() const
  
  Returns a const iterator to the first data point in this container.
*/
/* ! \ fn QCPDataContainer :: const_iterator QCPDataContainer <데이터 형식> :: constBegin () const
  
  이 컨테이너의 최초의 데이터 포인트에의 itter 반복자를 돌려줍니다.
*/

/*! \fn QCPDataContainer::const_iterator QCPDataContainer<DataType>::constEnd() const
  
  Returns a const iterator to the element past the last data point in this container.
*/
/* ! \ fn QCPDataContainer :: const_iterator QCPDataContainer <데이터 형식> :: constEnd () const
  
  이 컨테이너의 마지막 데이터 포인트를 지나서 요소에 대한 const 반복자를 리턴합니다.
*/


/*! \fn QCPDataContainer::iterator QCPDataContainer<DataType>::begin() const
  
  Returns a non-const iterator to the first data point in this container.

  You can manipulate the data points in-place through the non-const iterators, but great care must
  be taken when manipulating the sort key of a data point, see \ref sort, or the detailed
  description of this class.
*/
/* ! \ fn QCPDataContainer :: iterator QCPDataContainer <DataType> :: begin () const
  
  이 컨테이너의 최초의 데이터 포인트에의 비 정수 반복자를 돌려줍니다.
  비 const 반복자를 통해 데이터 포인트를 제 위치에서 조작 할 수 있지만주의를 기울여야합니다.
  데이터 포인트의 정렬 키를 조작 할 때 가져 오거나, \ ref 정렬을 보거나, 자세한
  이 클래스의 설명.
*/

/*! \fn QCPDataContainer::iterator QCPDataContainer<DataType>::end() const
  
  Returns a non-const iterator to the element past the last data point in this container.
  
  You can manipulate the data points in-place through the non-const iterators, but great care must
  be taken when manipulating the sort key of a data point, see \ref sort, or the detailed
  description of this class.
*/
/* ! \ fn QCPDataContainer :: iterator QCPDataContainer <DataType> :: end () const
  
  이 컨테이너의 마지막 데이터 점을 지나서 요소에 대한 비 const 반복자를 리턴합니다.
  
  비 const 반복자를 통해 데이터 포인트를 제 위치에서 조작 할 수 있지만주의를 기울여야합니다.
  데이터 포인트의 정렬 키를 조작 할 때 가져 오거나, \ ref 정렬을 보거나, 자세한
  이 클래스의 설명.
*/

/*! \fn QCPDataContainer::const_iterator QCPDataContainer<DataType>::at(int index) const

  Returns a const iterator to the element with the specified \a index. If \a index points beyond
  the available elements in this container, returns \ref constEnd, i.e. an iterator past the last
  valid element.

  You can use this method to easily obtain iterators from a \ref QCPDataRange, see the \ref
  dataselection-accessing "data selection page" for an example.
*/
/* ! \ fn QCPDataContainer :: const_iterator QCPDataContainer <데이터 타입> :: at (int 인덱스) const
  지정된 \ a 인덱스를 사용하여 요소에 대한 const 반복자를 반환합니다. \ a 이상의 인덱스가있는 경우
  이 컨테이너에서 사용할 수있는 요소는 \ ref constEnd를 반환합니다. 즉, 마지막
  유효한 요소.
  이 방법을 사용하면 \ ref QCPDataRange에서 반복자를 쉽게 얻을 수 있습니다. \ ref
  데이터 선택 - 예를 들어 '데이터 선택 페이지'에 액세스하십시오.
*/

/*! \fn QCPDataRange QCPDataContainer::dataRange() const

  Returns a \ref QCPDataRange encompassing the entire data set of this container. This means the
  begin index of the returned range is 0, and the end index is \ref size.
*/
/* ! \ fn QCPDataRange QCPDataContainer :: dataRange () const
  이 컨테이너의 전체 데이터 세트를 포함하는 \ ref QCPDataRange를 리턴합니다. 이것은
  반환 된 범위의 시작 인덱스는 0이고 끝 인덱스는 \ ref 크기입니다.
*/

/* end documentation of inline functions */
/* 인라인 함수의 끝 문서화 */

/*!
  Constructs a QCPDataContainer used for plottable classes that represent a series of key-sorted
  data
*/
/* !
  일련의 키 정렬을 나타내는 plottable 클래스에 사용되는 QCPDataContainer를 생성합니다.
  데이터
*/
template <class DataType>
QCPDataContainer<DataType>::QCPDataContainer() :
  mAutoSqueeze(true),
  mPreallocSize(0),
  mPreallocIteration(0)
{
}

/*!
  Sets whether the container automatically decides when to release memory from its post- and
  preallocation pools when data points are removed. By default this is enabled and for typical
  applications shouldn't be changed.
  
  If auto squeeze is disabled, you can manually decide when to release pre-/postallocation with
  \ref squeeze.
*/
/* !
  컨테이너가 메모리를 포스트 및 릴리스에서 자동으로 해제 할시기를 자동으로 결정하는지 여부를 설정합니다.
  데이터 포인트가 제거 될 때 사전 할당 풀. 기본적으로이 옵션이 활성화되어 있으며 일반적인 경우
  응용 프로그램을 변경하면 안됩니다.
  
  자동 압착이 비활성화 된 경우 수동으로 / 사전 할당을 해제 할시기를 수동으로 결정할 수 있습니다.
  \ ref를 쥐어 짜십시오.
*/
template <class DataType>
void QCPDataContainer<DataType>::setAutoSqueeze(bool enabled)
{
  if (mAutoSqueeze != enabled)
  {
    mAutoSqueeze = enabled;
    if (mAutoSqueeze)
      performAutoSqueeze();
  }
}

/*! \overload
  
  Replaces the current data in this container with the provided \a data.
  
  \see add, remove
*/
/* ! \초과 적재
  
  이 컨테이너의 현재 데이터를 제공된 \ a 데이터로 바꿉니다.
  
  \ 추가, 제거 참조
*/
template <class DataType>
void QCPDataContainer<DataType>::set(const QCPDataContainer<DataType> &data)
{
  clear();
  add(data);
}

/*! \overload
  
  Replaces the current data in this container with the provided \a data

  If you can guarantee that the data points in \a data have ascending order with respect to the
  DataType's sort key, set \a alreadySorted to true to avoid an unnecessary sorting run.
  
  \see add, remove
*/
/* ! \초과 적재
  
  이 컨테이너의 현재 데이터를 제공된 \ a 데이터로 바꿉니다.
  \ a 데이터의 데이터 포인트가 해당 데이터 포인트에 대해 오름차순으로 표시되도록 보장 할 수 있다면
  DataType의 소트 키. 불필요한 소트의 실행을 피하기 (위해) 때문에, \ a alreadySorted를 true로 설정합니다.
  
  \ 추가, 제거 참조
*/
template <class DataType>
void QCPDataContainer<DataType>::set(const QVector<DataType> &data, bool alreadySorted)
{
  mData = data;
  mPreallocSize = 0;
  mPreallocIteration = 0;
  if (!alreadySorted)
    sort();
}

/*! \overload
  
  Adds the provided \a data to the current data in this container.
  
  \see set, remove
*/
/* ! \초과 적재
  
  제공된 컨테이너의 현재 데이터에 제공된 \ a 데이터를 추가합니다.
  
  \ set set, remove
*/
template <class DataType>
void QCPDataContainer<DataType>::add(const QCPDataContainer<DataType> &data)
{
  if (data.isEmpty())
    return;
  
  const int n = data.size();
  const int oldSize = size();
  
  if (oldSize > 0 && !qcpLessThanSortKey<DataType>(*constBegin(), *(data.constEnd()-1)))
 // prepend if new data keys are all smaller than or equal to existing ones
 // 새로운 데이터 키가 모두 기존 데이터 키보다 작거나 같은 경우 앞에 추가 합니다 
  {
    if (mPreallocSize < n)
      preallocateGrow(n);
    mPreallocSize -= n;
    std::copy(data.constBegin(), data.constEnd(), begin());
  } else // don't need to prepend, so append and merge if necessary
  {      // 앞에 추가 할 필요가 없으므로 필요에 따라 추가 및 병합합니다.
    mData.resize(mData.size()+n);
    std::copy(data.constBegin(), data.constEnd(), end()-n);
    if (oldSize > 0 && !qcpLessThanSortKey<DataType>(*(constEnd()-n-1), *(constEnd()-n)))
 // if appended range keys aren't all greater than existing ones, merge the two partitions
 // 첨부 범위 키 모두보다 기존 아닌 경우, 병합 두 개의 파티션
      std::inplace_merge(begin(), end()-n, end(), qcpLessThanSortKey<DataType>);
  }
}

/*!
  Adds the provided data points in \a data to the current data.
  
  If you can guarantee that the data points in \a data have ascending order with respect to the
  DataType's sort key, set \a alreadySorted to true to avoid an unnecessary sorting run.
  
  \see set, remove
*/
/* !
  \ data에 제공된 데이터 요소를 현재 데이터에 추가합니다.
  
  \ a 데이터의 데이터 포인트가 해당 데이터 포인트에 대해 오름차순으로 표시되도록 보장 할 수 있다면
  DataType의 소트 키. 불필요한 소트의 실행을 피하기 (위해) 때문에, \ a alreadySorted를 true로 설정합니다.
  
  \ set set, remove
*/
template <class DataType>
void QCPDataContainer<DataType>::add(const QVector<DataType> &data, bool alreadySorted)
{
  if (data.isEmpty())
    return;
  if (isEmpty())
  {
    set(data, alreadySorted);
    return;
  }
  
  const int n = data.size();
  const int oldSize = size();
  
  if (alreadySorted && oldSize > 0 && !qcpLessThanSortKey<DataType>(*constBegin(), *(data.constEnd()-1)))
 // prepend if new data is sorted and keys are all smaller than or equal to existing ones
 // 앞에 추가 새로운 데이터 정렬되고 키는 모두 같거나 작은 기존의 경우
  {
    if (mPreallocSize < n)
      preallocateGrow(n);
    mPreallocSize -= n;
    std::copy(data.constBegin(), data.constEnd(), begin());
  } else // don't need to prepend, so append and then sort and merge if necessary
  {      // 앞에 추가 할 필요가 없으므로 필요한 경우 추가 한 다음 정렬 및 병합합니다.
    mData.resize(mData.size()+n);
    std::copy(data.constBegin(), data.constEnd(), end()-n);
    if (!alreadySorted) // sort appended subrange if it wasn't already sorted
                        // 이미 정렬되지 않은 경우 추가 된 하위 범위를 정렬합니다.
      std::sort(end()-n, end(), qcpLessThanSortKey<DataType>);
    if (oldSize > 0 && !qcpLessThanSortKey<DataType>(*(constEnd()-n-1), *(constEnd()-n)))
 // if appended range keys aren't all greater than existing ones, merge the two partitions
 // 첨부 범위 키 모두보다 기존 아닌 경우, 병합 두 개의 파티션
      std::inplace_merge(begin(), end()-n, end(), qcpLessThanSortKey<DataType>);
  }
}

/*! \overload
  
  Adds the provided single data point to the current data.
  
  \see remove
*/

/* ! \초과 적재
  
  제공된 단일 데이터 요소를 현재 데이터에 추가합니다.
  
  \ 제거 참조
*/
template <class DataType>
void QCPDataContainer<DataType>::add(const DataType &data)
{
  if (isEmpty() || !qcpLessThanSortKey<DataType>(data, *(constEnd()-1))) // quickly handle appends if new data key is greater or equal to existing ones
  {                                                                      // 신속하게 추가를 처리하는 새로운 데이터 키를 기존보다 크거나 같은 경우
    mData.append(data);
  } else if (qcpLessThanSortKey<DataType>(data, *constBegin()))  // quickly handle prepends using preallocated space
  {                                                              // 미리 할당 된 공간을 사용하여 앞자리를 빠르게 처리합니다.
    if (mPreallocSize < 1)
      preallocateGrow(1);
    --mPreallocSize;
    *begin() = data;
  } else // handle inserts, maintaining sorted keys
  {      // 삽입 처리, 정렬 된 키 관리
    QCPDataContainer<DataType>::iterator insertionPoint = std::lower_bound(begin(), end(), data, qcpLessThanSortKey<DataType>);
    mData.insert(insertionPoint, data);
  }
}

/*!
  Removes all data points with (sort-)keys smaller than or equal to \a sortKey.
  
  \see removeAfter, remove, clear
*/
/* !
  \ sortKey보다 작거나 같은 (소트 -) 키를 가지는 모든 데이터 포인트를 삭제합니다.
  
  \ removeAfter, remove, clear를 참조하십시오.
*/
template <class DataType>
void QCPDataContainer<DataType>::removeBefore(double sortKey)
{
  QCPDataContainer<DataType>::iterator it = begin();
  QCPDataContainer<DataType>::iterator itEnd = std::lower_bound(begin(), end(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  mPreallocSize += itEnd-it; // don't actually delete, just add it to the preallocated block (if it gets too large, squeeze will take care of it)
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*!
  Removes all data points with (sort-)keys greater than or equal to \a sortKey.

  \see removeBefore, remove, clear
*/
template <class DataType>
void QCPDataContainer<DataType>::removeAfter(double sortKey)
{
  QCPDataContainer<DataType>::iterator it = std::upper_bound(begin(), end(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  QCPDataContainer<DataType>::iterator itEnd = end();
  mData.erase(it, itEnd); // typically adds it to the postallocated block
  if (mAutoSqueeze)       // 실제로 삭제하지 않고 미리 할당 된 블록에 추가합니다 (너무 커지면 squeeze가 처리합니다).
    performAutoSqueeze();
}

/*!
  Removes all data points with (sort-)keys between \a sortKeyFrom and \a sortKeyTo. if \a
  sortKeyFrom is greater or equal to \a sortKeyTo, the function does nothing. To remove a single
  data point with known (sort-)key, use \ref remove(double sortKey).
  
  \see removeBefore, removeAfter, clear
*/
/* !
  \ sortKey보다 크거나 같은 (sort-) 키를 가지는 모든 데이터 포인트를 삭제합니다.
  \ removeBefore보기, 제거, 지우기
*/
template <class DataType>
void QCPDataContainer<DataType>::remove(double sortKeyFrom, double sortKeyTo)
{
  if (sortKeyFrom >= sortKeyTo || isEmpty())
    return;
  
  QCPDataContainer<DataType>::iterator it = std::lower_bound(begin(), end(), DataType::fromSortKey(sortKeyFrom), qcpLessThanSortKey<DataType>);
  QCPDataContainer<DataType>::iterator itEnd = std::upper_bound(it, end(), DataType::fromSortKey(sortKeyTo), qcpLessThanSortKey<DataType>);
  mData.erase(it, itEnd);
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*! \overload
  
  Removes a single data point at \a sortKey. If the position is not known with absolute (binary)
  precision, consider using \ref remove(double sortKeyFrom, double sortKeyTo) with a small
  fuzziness interval around the suspected position, depeding on the precision with which the
  (sort-)key is known.
  
  \see removeBefore, removeAfter, clear
*/
/* !
  \ sortKeyFrom와 \ sortKeyTo의 사이의 (sort-) 키를 가지는 모든 데이터 포인트를 삭제합니다. 만약
  sortKeyFrom이 \ sortKeyTo보다 크거나 같으면 함수는 아무 작업도 수행하지 않습니다. 단일 항목을 제거하려면
  알려진 (sort-) 키가있는 데이터 포인트는 \ ref remove (double sortKey)를 사용하십시오.
  
  \ removeBefore, removeAfter, clear를 참조하십시오.
*/
template <class DataType>
void QCPDataContainer<DataType>::remove(double sortKey)
{
  QCPDataContainer::iterator it = std::lower_bound(begin(), end(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  if (it != end() && it->sortKey() == sortKey)
  {
    if (it == begin())
      ++mPreallocSize; // don't actually delete, just add it to the preallocated block (if it gets too large, squeeze will take care of it)
    else               // 실제로 삭제하지 않고 미리 할당 된 블록에 추가합니다 (너무 커지면 squeeze가 처리합니다).
      mData.erase(it);
  }
  if (mAutoSqueeze)
    performAutoSqueeze();
}

/*!
  Removes all data points.
  
  \see remove, removeAfter, removeBefore
*/
/* !
  모든 데이터 요소를 제거합니다.
  
  \ remove remove, removeAfter, removeBefore를 참조하십시오.
*/
template <class DataType>
void QCPDataContainer<DataType>::clear()
{
  mData.clear();
  mPreallocIteration = 0;
  mPreallocSize = 0;
}

/*!
  Re-sorts all data points in the container by their sort key.

  When setting, adding or removing points using the QCPDataContainer interface (\ref set, \ref add,
  \ref remove, etc.), the container makes sure to always stay in a sorted state such that a full
  resort is never necessary. However, if you choose to directly manipulate the sort key on data
  points by accessing and modifying it through the non-const iterators (\ref begin, \ref end), it
  is your responsibility to bring the container back into a sorted state before any other methods
  are called on it. This can be achieved by calling this method immediately after finishing the
  sort key manipulation.
*/
/* !
  정렬 키를 사용하여 컨테이너의 모든 데이터 요소를 다시 정렬합니다.
  QCPDataContainer 인터페이스를 사용하여 점을 설정, 추가 또는 제거 할 때 (\ ref 집합, \ ref 추가,
  \ ref 제거 등), 컨테이너는 항상 정렬 된 상태를 유지하여 전체
  리조트는 절대 필요하지 않습니다. 그러나 데이터의 정렬 키를 직접 조작하도록 선택한 경우
  점이 아닌 반복자 (\ ref begin, \ ref end)를 통해 액세스하고 수정함으로써 점
  다른 방법보다 먼저 정렬 된 상태로 컨테이너를 가져 오는 것은 사용자의 책임입니다
  그것에 불려진다. 이것은,이 메소드를 호출 한 직후에이 메소드를 호출하는 것으로 실현할 수 있습니다.
  정렬 키 조작.
*/
template <class DataType>
void QCPDataContainer<DataType>::sort()
{
  std::sort(begin(), end(), qcpLessThanSortKey<DataType>);
}

/*!
  Frees all unused memory that is currently in the preallocation and postallocation pools.
  
  Note that QCPDataContainer automatically decides whether squeezing is necessary, if \ref
  setAutoSqueeze is left enabled. It should thus not be necessary to use this method for typical
  applications.
  
  The parameters \a preAllocation and \a postAllocation control whether pre- and/or post allocation
  should be freed, respectively.
*/
/* !
  preallocation 및 postallocation 풀에 현재있는 모든 사용되지 않은 메모리를 해제합니다.
  
  \ ref라면 QCPDataContainer가 자동으로 압착이 필요한지를 결정합니다.
  setAutoSqueeze가 사용 가능으로 남아 있습니다. 따라서 전형적인 방법으로는이 방법을 사용할 필요가 없다.
  응용 프로그램.
  
  사전 및 / 또는 사후 할당 여부에 관계없이 매개 변수 \ a preAllocation 및 \ a postAllocation
  각각 해방되어야한다.
*/
template <class DataType>
void QCPDataContainer<DataType>::squeeze(bool preAllocation, bool postAllocation)
{
  if (preAllocation)
  {
    if (mPreallocSize > 0)
    {
      std::copy(begin(), end(), mData.begin());
      mData.resize(size());
      mPreallocSize = 0;
    }
    mPreallocIteration = 0;
  }
  if (postAllocation)
    mData.squeeze();
}

/*!
  Returns an iterator to the data point with a (sort-)key that is equal to, just below, or just
  above \a sortKey. If \a expandedRange is true, the data point just below \a sortKey will be
  considered, otherwise the one just above.

  This can be used in conjunction with \ref findEnd to iterate over data points within a given key
  range, including or excluding the bounding data points that are just beyond the specified range.

  If \a expandedRange is true but there are no data points below \a sortKey, \ref constBegin is
  returned.

  If the container is empty, returns \ref constEnd.

  \see findEnd, QCPPlottableInterface1D::findBegin
*/
/* !
  데이터 포인트와 같은 (sort-) 키를 가진 iterator를 리턴합니다.
  위에서 \ a sortKey. \ a expandedLange가 true 인 경우 \ sortKey 바로 아래의 데이터 요소는
  고려해야합니다.
  \ ref findEnd와 함께 사용하면 주어진 키 내의 데이터 요소를 반복 할 수 있습니다
  범위를 벗어나면 지정된 범위를 벗어나는 경계 데이터 점을 포함하거나 제외 할 수 있습니다.
  \ a expandedRange가 true이지만 sortKey 아래에 데이터 요소가없는 경우 \ ref constBegin은 다음과 같습니다.
  반환되었습니다.
  컨테이너가 비어 있으면 \ ref constEnd를 반환합니다.
  \ findEnd, QCPPlottableInterface1D :: findBegin을 참조하십시오.
*/
template <class DataType>
typename QCPDataContainer<DataType>::const_iterator QCPDataContainer<DataType>::findBegin(double sortKey, bool expandedRange) const
{
  if (isEmpty())
    return constEnd();
  
  QCPDataContainer<DataType>::const_iterator it = std::lower_bound(constBegin(), constEnd(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  if (expandedRange && it != constBegin()) // also covers it == constEnd case, and we know --constEnd is valid because mData isn't empty
    --it;                                  // 또한 커버한다. == constEnd case, mData가 비어 있지 않기 때문에 --constEnd가 유효하다.
  return it;
}

/*!
  Returns an iterator to the element after the data point with a (sort-)key that is equal to, just
  above or just below \a sortKey. If \a expandedRange is true, the data point just above \a sortKey
  will be considered, otherwise the one just below.

  This can be used in conjunction with \ref findBegin to iterate over data points within a given
  key range, including the bounding data points that are just below and above the specified range.

  If \a expandedRange is true but there are no data points above \a sortKey, \ref constEnd is
  returned.

  If the container is empty, \ref constEnd is returned.

  \see findBegin, QCPPlottableInterface1D::findEnd
*/
/* !
  동일한 (sort-) 키를 가진 데이터 요소 뒤의 요소에 대한 반복자를 반환합니다.
  \ sortKey 위 또는 바로 아래에. \ a expandedRange가 true 인 경우, \ ​​sortKey 바로 위에있는 데이터 포인트
  고려 될 것입니다, 그렇지 않으면 바로 아래에있는 것.
  이것은 \ ref findBegin과 함께 사용하여 주어진 데이터 포인트를 반복 처리 할 수 ​​있습니다.
  지정된 범위 바로 아래 및 위에있는 경계 데이터 점을 포함하여 키 범위.
  \ a expandedRange가 true이지만 \ sortKey 위에 데이터 포인트가없는 경우 \ ref constEnd는
  반환되었습니다.
  컨테이너가 비어 있으면 \ ref constEnd가 반환됩니다.
  \ seeBegin, QCPPlottableInterface1D :: findEnd를 참조하십시오.
*/
template <class DataType>
typename QCPDataContainer<DataType>::const_iterator QCPDataContainer<DataType>::findEnd(double sortKey, bool expandedRange) const
{
  if (isEmpty())
    return constEnd();
  
  QCPDataContainer<DataType>::const_iterator it = std::upper_bound(constBegin(), constEnd(), DataType::fromSortKey(sortKey), qcpLessThanSortKey<DataType>);
  if (expandedRange && it != constEnd())
    ++it;
  return it;
}

/*!
  Returns the range encompassed by the (main-)key coordinate of all data points. The output
  parameter \a foundRange indicates whether a sensible range was found. If this is false, you
  should not use the returned QCPRange (e.g. the data container is empty or all points have the
  same key).
  
  Use \a signDomain to control which sign of the key coordinates should be considered. This is
  relevant e.g. for logarithmic plots which can mathematically only display one sign domain at a
  time.
  
  If the DataType reports that its main key is equal to the sort key (\a sortKeyIsMainKey), as is
  the case for most plottables, this method uses this fact and finds the range very quickly.
  
  \see valueRange
*/
/* !
  모든 데이터 포인트의 (주) 키 좌표로 둘러싸인 범위를 돌려줍니다. 출력
  매개 변수 \ a foundRange는 의미있는 범위가 발견되었는지 여부를 나타냅니다. 이것이 틀린 경우, 귀하는
  반환 된 QCPRange를 사용하면 안됩니다 (예 : 데이터 컨테이너가 비어 있거나 모든 포인트에
  같은 열쇠).
  
  \ a signDomain를 사용해, 고려되어야 할 키 좌표의 부호를 제어합니다. 이것은
  예를 들어 수학적으로 하나의 부호 영역 만 표시 할 수있는 로그 플롯의 경우
  시각.
  
  DataType이 기본 키가 정렬 키 (\ a sortKeyIsMainKey)와 같다고보고하면
  대부분의 plottables의 경우,이 방법은이 사실을 사용하고 범위를 매우 빨리 찾습니다.
  
  \ 참조 valueRange
*/
template <class DataType>
QCPRange QCPDataContainer<DataType>::keyRange(bool &foundRange, QCP::SignDomain signDomain)
{
  if (isEmpty())
  {
    foundRange = false;
    return QCPRange();
  }
  QCPRange range;
  bool haveLower = false;
  bool haveUpper = false;
  double current;
  
  QCPDataContainer<DataType>::const_iterator it = constBegin();
  QCPDataContainer<DataType>::const_iterator itEnd = constEnd();
  if (signDomain == QCP::sdBoth) // range may be anywhere
  {                              // 범위는 어디에도있을 수 있습니다.
    if (DataType::sortKeyIsMainKey()) 
// if DataType is sorted by main key (e.g. QCPGraph, but not QCPCurve), use faster algorithm by finding just first and last key with non-NaN value               
// DataType이 기본 키 (예 : QCPGraph, QCPCurve)로 정렬 된 경우 NaN 이외의 값으로 첫 번째와 마지막 키를 찾아 빠른 알고리즘 사용
    {
      while (it != itEnd) // find first non-nan going up from left
      {                   // 처음부터 non-nan을 찾아서 왼쪽부터
        if (!qIsNaN(it->mainValue()))
        {
          range.lower = it->mainKey();
          haveLower = true;
          break;
        }
        ++it;
      }
      it = itEnd;
      while (it != constBegin()) // find first non-nan going down from right
      {                          // 처음부터 non-nan을 오른쪽에서 찾는다.
        --it;
        if (!qIsNaN(it->mainValue()))
        {
          range.upper = it->mainKey();
          haveUpper = true;
          break;
        }
      }
    } else // DataType is not sorted by main key, go through all data points and accordingly expand range
    {      // 데이터 타입은 메인 키별로 정렬되지 않으며, 모든 데이터 포인트를 거쳐 범위를 확장합니다.
      while (it != itEnd)
      {
        if (!qIsNaN(it->mainValue()))
        {
          current = it->mainKey();
          if (current < range.lower || !haveLower)
          {
            range.lower = current;
            haveLower = true;
          }
          if (current > range.upper || !haveUpper)
          {
            range.upper = current;
            haveUpper = true;
          }
        }
        ++it;
      }
    }
  } else if (signDomain == QCP::sdNegative) // range may only be in the negative sign domain
  {                                         // 범위는 음수 부호 도메인에만있을 수 있습니다
    while (it != itEnd)
    {
      if (!qIsNaN(it->mainValue()))
      {
        current = it->mainKey();
        if ((current < range.lower || !haveLower) && current < 0)
        {
          range.lower = current;
          haveLower = true;
        }
        if ((current > range.upper || !haveUpper) && current < 0)
        {
          range.upper = current;
          haveUpper = true;
        }
      }
      ++it;
    }
  } else if (signDomain == QCP::sdPositive) // range may only be in the positive sign domain
  {                                         // 범위는 양수 부호 도메인에만있을 수 있습니다.
    while (it != itEnd)
    {
      if (!qIsNaN(it->mainValue()))
      {
        current = it->mainKey();
        if ((current < range.lower || !haveLower) && current > 0)
        {
          range.lower = current;
          haveLower = true;
        }
        if ((current > range.upper || !haveUpper) && current > 0)
        {
          range.upper = current;
          haveUpper = true;
        }
      }
      ++it;
    }
  }
  
  foundRange = haveLower && haveUpper;
  return range;
}

/*!
  Returns the range encompassed by the value coordinates of the data points in the specified key
  range (\a inKeyRange), using the full \a DataType::valueRange reported by the data points. The
  output parameter \a foundRange indicates whether a sensible range was found. If this is false,
  you should not use the returned QCPRange (e.g. the data container is empty or all points have the
  same value).

  If \a inKeyRange has both lower and upper bound set to zero (is equal to <tt>QCPRange()</tt>),
  all data points are considered, without any restriction on the keys.

  Use \a signDomain to control which sign of the value coordinates should be considered. This is
  relevant e.g. for logarithmic plots which can mathematically only display one sign domain at a
  time.

  \see keyRange
*/
/* !
  지정된 키 내의 데이터 포인트의 값 좌표로 둘러싸인 범위를 돌려줍니다.
  범위 (\ inKeyRange), 데이터 포인트에 의해보고 된 전체 DataType :: valueRange를 사용합니다. 그만큼
  출력 매개 변수 \ a foundRange는 감지 할 수있는 범위가 있는지 여부를 나타냅니다. 이것이 틀리면,
  반환 된 QCPRange를 사용하면 안됩니다 (예 : 데이터 컨테이너가 비어 있거나 모든 포인트에
  같은 가치).
  inKeyRange가 하한과 상한이 모두 0으로 설정되어있는 경우 (<tt> QCPRange () </ tt>와 동일)
  모든 데이터 포인트는 키에 대한 제한없이 고려됩니다.
  \ a signDomain를 사용하여 값 좌표의 부호를 고려해야하는지 제어하십시오. 이것은
  예를 들어 수학적으로 하나의 부호 영역 만 표시 할 수있는 로그 플롯의 경우
  시각.
  \ 참조 keyRange
*/
template <class DataType>
QCPRange QCPDataContainer<DataType>::valueRange(bool &foundRange, QCP::SignDomain signDomain, const QCPRange &inKeyRange)
{
  if (isEmpty())
  {
    foundRange = false;
    return QCPRange();
  }
  QCPRange range;
  const bool restrictKeyRange = inKeyRange != QCPRange();
  bool haveLower = false;
  bool haveUpper = false;
  QCPRange current;
  QCPDataContainer<DataType>::const_iterator itBegin = constBegin();
  QCPDataContainer<DataType>::const_iterator itEnd = constEnd();
  if (DataType::sortKeyIsMainKey() && restrictKeyRange)
  {
    itBegin = findBegin(inKeyRange.lower);
    itEnd = findEnd(inKeyRange.upper);
  }
  if (signDomain == QCP::sdBoth) // range may be anywhere
  {                              // 범위는 어디에도있을 수 있습니다.
    for (QCPDataContainer<DataType>::const_iterator it = itBegin; it != itEnd; ++it)
    {
      if (restrictKeyRange && (it->mainKey() < inKeyRange.lower || it->mainKey() > inKeyRange.upper))
        continue;
      current = it->valueRange();
      if ((current.lower < range.lower || !haveLower) && !qIsNaN(current.lower))
      {
        range.lower = current.lower;
        haveLower = true;
      }
      if ((current.upper > range.upper || !haveUpper) && !qIsNaN(current.upper))
      {
        range.upper = current.upper;
        haveUpper = true;
      }
    }
  } else if (signDomain == QCP::sdNegative) // range may only be in the negative sign domain
  {                                         // 범위는 음수 부호 도메인에만있을 수 있습니다
    for (QCPDataContainer<DataType>::const_iterator it = itBegin; it != itEnd; ++it)
    {
      if (restrictKeyRange && (it->mainKey() < inKeyRange.lower || it->mainKey() > inKeyRange.upper))
        continue;
      current = it->valueRange();
      if ((current.lower < range.lower || !haveLower) && current.lower < 0 && !qIsNaN(current.lower))
      {
        range.lower = current.lower;
        haveLower = true;
      }
      if ((current.upper > range.upper || !haveUpper) && current.upper < 0 && !qIsNaN(current.upper))
      {
        range.upper = current.upper;
        haveUpper = true;
      }
    }
  } else if (signDomain == QCP::sdPositive) // range may only be in the positive sign domain
  {                                         // 범위는 양수 부호 도메인에만있을 수 있습니다.
    for (QCPDataContainer<DataType>::const_iterator it = itBegin; it != itEnd; ++it)
    {
      if (restrictKeyRange && (it->mainKey() < inKeyRange.lower || it->mainKey() > inKeyRange.upper))
        continue;
      current = it->valueRange();
      if ((current.lower < range.lower || !haveLower) && current.lower > 0 && !qIsNaN(current.lower))
      {
        range.lower = current.lower;
        haveLower = true;
      }
      if ((current.upper > range.upper || !haveUpper) && current.upper > 0 && !qIsNaN(current.upper))
      {
        range.upper = current.upper;
        haveUpper = true;
      }
    }
  }
  
  foundRange = haveLower && haveUpper;
  return range;
}

/*!
  Makes sure \a begin and \a end mark a data range that is both within the bounds of this data
  container's data, as well as within the specified \a dataRange. The initial range described by
  the passed iterators \a begin and \a end is never expanded, only contracted if necessary.
  
  This function doesn't require for \a dataRange to be within the bounds of this data container's
  valid range.
*/
/* !
  이 데이터의 범위 내에있는 데이터 범위를 \ begin 및 \ end 끝으로 표시합니다.
  컨테이너의 데이터뿐만 아니라 지정된 \ a dataRange. 에 의해 기술 된 초기 범위
  전달 된 반복자 \ a begin과 \ end는 결코 확장되지 않으며, 필요한 경우에만 축소됩니다.
  
  이 함수는 \ dataRange가이 데이터 컨테이너의 범위 내에 있지 않아도됩니다.
  유효한 범위.
*/
template <class DataType>
void QCPDataContainer<DataType>::limitIteratorsToDataRange(const_iterator &begin, const_iterator &end, const QCPDataRange &dataRange) const
{
  QCPDataRange iteratorRange(begin-constBegin(), end-constBegin());
  iteratorRange = iteratorRange.bounded(dataRange.bounded(this->dataRange()));
  begin = constBegin()+iteratorRange.begin();
  end = constBegin()+iteratorRange.end();
}

/*! \internal
  
  Increases the preallocation pool to have a size of at least \a minimumPreallocSize. Depending on
  the preallocation history, the container will grow by more than requested, to speed up future
  consecutive size increases.
  
  if \a minimumPreallocSize is smaller than or equal to the current preallocation pool size, this
  method does nothing.
*/
/* ! \내부의
  
  사전 할당 풀을 최소 \ minimumPreallocSize 이상의 크기로 늘립니다. 에 따라
  사전 할당 내역, 컨테이너가 요청 이상으로 커져서 미래를 가속화합니다.
  연속 크기가 증가합니다.
  
  \ minimumPreallocSize가 현재의 사전 할당 풀 크기보다 작거나 같은 경우이
  메서드는 아무 것도하지 않습니다.
*/
template <class DataType>
void QCPDataContainer<DataType>::preallocateGrow(int minimumPreallocSize)
{
  if (minimumPreallocSize <= mPreallocSize)
    return;
  
  int newPreallocSize = minimumPreallocSize;
  newPreallocSize += (1u<<qBound(4, mPreallocIteration+4, 15)) - 12;
 // do 4 up to 32768-12 preallocation, doubling in each intermediate iteration
 // 4에서 32768-12까지의 preallocation, 각 중간 반복에서 두 배로 수행
  ++mPreallocIteration;
  
  int sizeDifference = newPreallocSize-mPreallocSize;
  mData.resize(mData.size()+sizeDifference);
  std::copy_backward(mData.begin()+mPreallocSize, mData.end()-sizeDifference, mData.end());
  mPreallocSize = newPreallocSize;
}

/*! \internal
  
  This method decides, depending on the total allocation size and the size of the unused pre- and
  postallocation pools, whether it is sensible to reduce the pools in order to free up unused
  memory. It then possibly calls \ref squeeze to do the deallocation.
  
  If \ref setAutoSqueeze is enabled, this method is called automatically each time data points are
  removed from the container (e.g. \ref remove).
  
  \note when changing the decision parameters, care must be taken not to cause a back-and-forth
  between squeezing and reallocation due to the growth strategy of the internal QVector and \ref
  preallocateGrow. The hysteresis between allocation and deallocation should be made high enough
  (at the expense of possibly larger unused memory from time to time).
*/
/* ! \내부의
  
  이 방법은 전체 할당 크기와 사용되지 않은 프리 -
  사용되지 않은 공간을 확보하기 위해 풀을 줄이는 것이 현명한 지 여부와 상관없이 사후 할당 풀
  기억. 그런 다음 \ ref squeeze를 호출하여 할당 취소를 수행 할 수 있습니다.
  
  \ ref setAutoSqueeze가 사용 가능한 경우이 메소드는 데이터 요소가
  컨테이너에서 제거 (예 : \ ref 제거).
  
  결정 매개 변수를 변경할 때주의하십시오. 앞뒤로 움직이지 않도록주의해야합니다.
  내부 QVector 및 \ ref의 성장 전략으로 인한 압박과 재 할당 사이
  preallocateGrow. 할당과 할당 해제 간의 히스테리시스는 충분히 높아야합니다.
  (때로는 사용되지 않는 메모리가 커질 수 있음).
*/
template <class DataType>
void QCPDataContainer<DataType>::performAutoSqueeze()
{
  const int totalAlloc = mData.capacity();
  const int postAllocSize = totalAlloc-mData.size();
  const int usedSize = size();
  bool shrinkPostAllocation = false;
  bool shrinkPreAllocation = false;
  if (totalAlloc > 650000) // if allocation is larger, shrink earlier with respect to total used size
  {                        // 할당이 더 큰 경우 사용 된 총 크기에 대해 먼저 축소합니다.
    shrinkPostAllocation = postAllocSize > usedSize*1.5;
 // QVector grow strategy is 2^n for static data. Watch out not to oscillate!
 // QVector 성장 전략은 정적 데이터의 경우 2 ^ n입니다. 조심하지 마세요!
    shrinkPreAllocation = mPreallocSize*10 > usedSize;
  } else if (totalAlloc > 1000)
 // below 10 MiB raw data be generous with preallocated memory, below 1k points don't even bother
 // 10 MiB 이하의 미가공 데이터는 미리 할당 된 메모리로 충분 하며, 1k 포인트 미만에서는 걱정하지 않아도됩니다.
  {
    shrinkPostAllocation = postAllocSize > usedSize*5;
    shrinkPreAllocation = mPreallocSize > usedSize*1.5; 
// preallocation can grow into postallocation, so can be smaller
// preallocation은 postallocation으로 성장할 수 있으므로 더 작을 수 있습니다. 
 }                                          
  
  if (shrinkPreAllocation || shrinkPostAllocation)
    squeeze(shrinkPreAllocation, shrinkPostAllocation);
}
/* end of 'src/datacontainer.cpp' */


/* end of 'src/datacontainer.h' */


/* including file 'src/plottable.h', size 8312                               */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / datacontainer.cpp'의 끝 */


/* 'src / datacontainer.h'의 끝 */


/* 파일 'src / plottable.h'포함, 크기 8312                                */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPSelectionDecorator
{
  Q_GADGET
public:
  QCPSelectionDecorator();
  virtual ~QCPSelectionDecorator();
  
  // getters:
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  QCPScatterStyle scatterStyle() const { return mScatterStyle; }
  QCPScatterStyle::ScatterProperties usedScatterProperties() const { return mUsedScatterProperties; }
  
  // setters:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setScatterStyle(const QCPScatterStyle &scatterStyle, QCPScatterStyle::ScatterProperties usedProperties=QCPScatterStyle::spPen);
  void setUsedScatterProperties(const QCPScatterStyle::ScatterProperties &properties);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void applyPen(QCPPainter *painter) const;
  void applyBrush(QCPPainter *painter) const;
  QCPScatterStyle getFinalScatterStyle(const QCPScatterStyle &unselectedStyle) const;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void copyFrom(const QCPSelectionDecorator *other);
  virtual void drawDecoration(QCPPainter *painter, QCPDataSelection selection);
  
protected:
  // property members:
  // 속성 멤버 :
  QPen mPen;
  QBrush mBrush;
  QCPScatterStyle mScatterStyle;
  QCPScatterStyle::ScatterProperties mUsedScatterProperties;
  // non-property members:
  // 비 속성 멤버 :
  QCPAbstractPlottable *mPlottable;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual bool registerWithPlottable(QCPAbstractPlottable *plottable);
  
private:
  Q_DISABLE_COPY(QCPSelectionDecorator)
  friend class QCPAbstractPlottable;
};
Q_DECLARE_METATYPE(QCPSelectionDecorator*)


class QCP_LIB_DECL QCPAbstractPlottable : public QCPLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(bool antialiasedFill READ antialiasedFill WRITE setAntialiasedFill)
  Q_PROPERTY(bool antialiasedScatters READ antialiasedScatters WRITE setAntialiasedScatters)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QCPAxis* keyAxis READ keyAxis WRITE setKeyAxis)
  Q_PROPERTY(QCPAxis* valueAxis READ valueAxis WRITE setValueAxis)
  Q_PROPERTY(QCP::SelectionType selectable READ selectable WRITE setSelectable NOTIFY selectableChanged)
  Q_PROPERTY(QCPDataSelection selection READ selection WRITE setSelection NOTIFY selectionChanged)
  Q_PROPERTY(QCPSelectionDecorator* selectionDecorator READ selectionDecorator WRITE setSelectionDecorator)
  /// \endcond
public:
  QCPAbstractPlottable(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPAbstractPlottable();
  
  // getters:
  QString name() const { return mName; }
  bool antialiasedFill() const { return mAntialiasedFill; }
  bool antialiasedScatters() const { return mAntialiasedScatters; }
  QPen pen() const { return mPen; }
  QBrush brush() const { return mBrush; }
  QCPAxis *keyAxis() const { return mKeyAxis.data(); }
  QCPAxis *valueAxis() const { return mValueAxis.data(); }
  QCP::SelectionType selectable() const { return mSelectable; }
  bool selected() const { return !mSelection.isEmpty(); }
  QCPDataSelection selection() const { return mSelection; }
  QCPSelectionDecorator *selectionDecorator() const { return mSelectionDecorator; }
  
  // setters:
  void setName(const QString &name);
  void setAntialiasedFill(bool enabled);
  void setAntialiasedScatters(bool enabled);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setKeyAxis(QCPAxis *axis);
  void setValueAxis(QCPAxis *axis);
  Q_SLOT void setSelectable(QCP::SelectionType selectable);
  Q_SLOT void setSelection(QCPDataSelection selection);
  void setSelectionDecorator(QCPSelectionDecorator *decorator);

  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const = 0;
  virtual QCPPlottableInterface1D *interface1D() { return 0; }
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const = 0;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const = 0;
  
  // non-property methods:
  // 비 속성 메소드 :
  void coordsToPixels(double key, double value, double &x, double &y) const;
  const QPointF coordsToPixels(double key, double value) const;
  void pixelsToCoords(double x, double y, double &key, double &value) const;
  void pixelsToCoords(const QPointF &pixelPos, double &key, double &value) const;
  void rescaleAxes(bool onlyEnlarge=false) const;
  void rescaleKeyAxis(bool onlyEnlarge=false) const;
  void rescaleValueAxis(bool onlyEnlarge=false, bool inKeyRange=false) const;
  bool addToLegend(QCPLegend *legend);
  bool addToLegend();
  bool removeFromLegend(QCPLegend *legend) const;
  bool removeFromLegend() const;
  
signals:
  void selectionChanged(bool selected);
  void selectionChanged(const QCPDataSelection &selection);
  void selectableChanged(QCP::SelectionType selectable);
  
protected:
  // property members:
  // 속성 멤버 :
  QString mName;
  bool mAntialiasedFill, mAntialiasedScatters;
  QPen mPen;
  QBrush mBrush;
  QPointer<QCPAxis> mKeyAxis, mValueAxis;
  QCP::SelectionType mSelectable;
  QCPDataSelection mSelection;
  QCPSelectionDecorator *mSelectionDecorator;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QRect clipRect() const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE = 0;
  virtual QCP::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const = 0;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void applyFillAntialiasingHint(QCPPainter *painter) const;
  void applyScattersAntialiasingHint(QCPPainter *painter) const;

private:
  Q_DISABLE_COPY(QCPAbstractPlottable)
  
  friend class QCustomPlot;
  friend class QCPAxis;
  friend class QCPPlottableLegendItem;
};


/* end of 'src/plottable.h' */


/* including file 'src/item.h', size 9384                                    */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/
/* 'src / plottable.h'의 끝 */


/* 파일 'src / item.h'포함, 크기 9384                                       */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200*/
class QCP_LIB_DECL QCPItemAnchor
{
  Q_GADGET
public:
  QCPItemAnchor(QCustomPlot *parentPlot, QCPAbstractItem *parentItem, const QString &name, int anchorId=-1);
  virtual ~QCPItemAnchor();
  
  // getters:
  QString name() const { return mName; }
  virtual QPointF pixelPosition() const;
  
protected:
  // property members:
  // 속성 멤버 :
  QString mName;
  
  // non-property members:
  // 비 속성 멤버 :
  QCustomPlot *mParentPlot;
  QCPAbstractItem *mParentItem;
  int mAnchorId;
  QSet<QCPItemPosition*> mChildrenX, mChildrenY;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual QCPItemPosition *toQCPItemPosition() { return 0; }
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void addChildX(QCPItemPosition* pos); // called from pos when this anchor is set as parent
                                        // POS에서 호출이 앵커는 부모로 설정되어있는 경우
  void removeChildX(QCPItemPosition *pos); // called from pos when its parent anchor is reset or pos deleted
                                           // 부모 앵커가 재설정되거나 pos가 삭제되면 pos에서 호출됩니다.
  void addChildY(QCPItemPosition* pos); // called from pos when this anchor is set as parent
                                        // POS에서 호출이 앵커는 부모로 설정되어있는 경우
  void removeChildY(QCPItemPosition *pos); // called from pos when its parent anchor is reset or pos deleted
                                           // 부모 앵커가 재설정되거나 pos가 삭제되면 pos에서 호출됩니다.
  
private:
  Q_DISABLE_COPY(QCPItemAnchor)
  
  friend class QCPItemPosition;
};



class QCP_LIB_DECL QCPItemPosition : public QCPItemAnchor
{
  Q_GADGET
public:
  /*!
    Defines the ways an item position can be specified. Thus it defines what the numbers passed to
    \ref setCoords actually mean.
    
    \see setType
  */
/* !
    항목 위치를 지정할 수있는 방법을 정의합니다. 따라서 그것은 전달 된 숫자를 정의합니다.
    \ ref setCoords는 실제로 의미합니다.
    
    \ setType을 참조하십시오.
  */
  enum PositionType { ptAbsolute        ///< Static positioning in pixels, starting from the top left corner of the viewport/widget. 
//                                      /// <뷰포트 / 위젯의 왼쪽 위 모퉁이에서 시작하는 픽셀 단위의 정적 위치 지정.
                      ,ptViewportRatio  ///< Static positioning given by a fraction of the viewport size. For example, if you call setCoords(0, 0), the position will be at the top
//                                      /// <뷰포트 크기의 일부분만큼 정적 위치 지정. 예를 들어, setCoords (0, 0)를 호출하면 위치는 맨 위에 표시됩니다
                                        ///< left corner of the viewport/widget. setCoords(1, 1) will be at the bottom right corner, setCoords(0.5, 0) will be horizontally centered and
//                                      /// 뷰포트 / 위젯의 왼쪽 구석. setCoords (1, 1)는 오른쪽 아래 모서리에 있고, setCoords (0.5, 0)는 가로로 가운데에 놓이며

                                        ///< vertically at the top of the viewport/widget, etc.
//                                      /// <뷰포트 / 위젯의 맨 위에서 수직으로, 등.
                      ,ptAxisRectRatio  ///< Static positioning given by a fraction of the axis rect size (see \ref setAxisRect). For example, if you call setCoords(0, 0), the position will be at the top
//                                      /// <축 rect 크기의 분수로 주어진 정적 위치 지정 (\ ref setAxisRect 참조). 예를 들어, setCoords (0, 0)를 호출하면 위치는 맨 위에 표시됩니다
                                        ///< left corner of the axis rect. setCoords(1, 1) will be at the bottom right corner, setCoords(0.5, 0) will be horizontally centered and
//                                      /// <축 rect의 왼쪽 구석. setCoords (1, 1)는 오른쪽 아래 모서리에 있고, setCoords (0.5, 0)는 가로로 가운데에 놓이며
                                        ///< vertically at the top of the axis rect, etc. You can also go beyond the axis rect by providing negative coordinates or coordinates larger than 1.
//                                      /// <축 rect의 꼭대기에서 수직으로 등등. 음의 좌표 또는 1보다 큰 좌표를 제공하여 축 rect를 넘을 수도 있습니다.
                      ,ptPlotCoords     ///< Dynamic positioning at a plot coordinate defined by two axes (see \ref setAxes).
//                                      /// <두 축으로 정의 된 플롯 좌표에서 동적 위치 지정 (\ ref setAxes 참조).
                    };
  Q_ENUMS(PositionType)
  
  QCPItemPosition(QCustomPlot *parentPlot, QCPAbstractItem *parentItem, const QString &name);
  virtual ~QCPItemPosition();
  
  // getters:
  PositionType type() const { return typeX(); }
  PositionType typeX() const { return mPositionTypeX; }
  PositionType typeY() const { return mPositionTypeY; }
  QCPItemAnchor *parentAnchor() const { return parentAnchorX(); }
  QCPItemAnchor *parentAnchorX() const { return mParentAnchorX; }
  QCPItemAnchor *parentAnchorY() const { return mParentAnchorY; }
  double key() const { return mKey; }
  double value() const { return mValue; }
  QPointF coords() const { return QPointF(mKey, mValue); }
  QCPAxis *keyAxis() const { return mKeyAxis.data(); }
  QCPAxis *valueAxis() const { return mValueAxis.data(); }
  QCPAxisRect *axisRect() const;
  virtual QPointF pixelPosition() const Q_DECL_OVERRIDE;
  
  // setters:
  void setType(PositionType type);
  void setTypeX(PositionType type);
  void setTypeY(PositionType type);
  bool setParentAnchor(QCPItemAnchor *parentAnchor, bool keepPixelPosition=false);
  bool setParentAnchorX(QCPItemAnchor *parentAnchor, bool keepPixelPosition=false);
  bool setParentAnchorY(QCPItemAnchor *parentAnchor, bool keepPixelPosition=false);
  void setCoords(double key, double value);
  void setCoords(const QPointF &coords);
  void setAxes(QCPAxis* keyAxis, QCPAxis* valueAxis);
  void setAxisRect(QCPAxisRect *axisRect);
  void setPixelPosition(const QPointF &pixelPosition);
  
protected:
  // property members:
  // 속성 멤버 :
  PositionType mPositionTypeX, mPositionTypeY;
  QPointer<QCPAxis> mKeyAxis, mValueAxis;
  QPointer<QCPAxisRect> mAxisRect;
  double mKey, mValue;
  QCPItemAnchor *mParentAnchorX, *mParentAnchorY;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPItemPosition *toQCPItemPosition() Q_DECL_OVERRIDE { return this; }
  
private:
  Q_DISABLE_COPY(QCPItemPosition)
  
};
Q_DECLARE_METATYPE(QCPItemPosition::PositionType)


class QCP_LIB_DECL QCPAbstractItem : public QCPLayerable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(bool clipToAxisRect READ clipToAxisRect WRITE setClipToAxisRect)
  Q_PROPERTY(QCPAxisRect* clipAxisRect READ clipAxisRect WRITE setClipAxisRect)
  Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectableChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectionChanged)
  /// \endcond
public:
  explicit QCPAbstractItem(QCustomPlot *parentPlot);
  virtual ~QCPAbstractItem();
  
  // getters:
  bool clipToAxisRect() const { return mClipToAxisRect; }
  QCPAxisRect *clipAxisRect() const;
  bool selectable() const { return mSelectable; }
  bool selected() const { return mSelected; }
  
  // setters:
  void setClipToAxisRect(bool clip);
  void setClipAxisRect(QCPAxisRect *rect);
  Q_SLOT void setSelectable(bool selectable);
  Q_SLOT void setSelected(bool selected);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE = 0;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QList<QCPItemPosition*> positions() const { return mPositions; }
  QList<QCPItemAnchor*> anchors() const { return mAnchors; }
  QCPItemPosition *position(const QString &name) const;
  QCPItemAnchor *anchor(const QString &name) const;
  bool hasAnchor(const QString &name) const;
  
signals:
  void selectionChanged(bool selected);
  void selectableChanged(bool selectable);
  
protected:
  // property members:
  // 속성 멤버 :
  bool mClipToAxisRect;
  QPointer<QCPAxisRect> mClipAxisRect;
  QList<QCPItemPosition*> mPositions;
  QList<QCPItemAnchor*> mAnchors;
  bool mSelectable, mSelected;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCP::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  virtual QRect clipRect() const Q_DECL_OVERRIDE;
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE = 0;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual QPointF anchorPixelPosition(int anchorId) const;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  double rectDistance(const QRectF &rect, const QPointF &pos, bool filledRect) const;
  QCPItemPosition *createPosition(const QString &name);
  QCPItemAnchor *createAnchor(const QString &name, int anchorId);
  
private:
  Q_DISABLE_COPY(QCPAbstractItem)
  
  friend class QCustomPlot;
  friend class QCPItemAnchor;
};

/* end of 'src/item.h' */


/* including file 'src/core.h', size 14886                                   */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / item.h'의 끝 */


/* 파일 'src / core.h'포함, 크기 14886                                      */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCustomPlot : public QWidget
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QRect viewport READ viewport WRITE setViewport)
  Q_PROPERTY(QPixmap background READ background WRITE setBackground)
  Q_PROPERTY(bool backgroundScaled READ backgroundScaled WRITE setBackgroundScaled)
  Q_PROPERTY(Qt::AspectRatioMode backgroundScaledMode READ backgroundScaledMode WRITE setBackgroundScaledMode)
  Q_PROPERTY(QCPLayoutGrid* plotLayout READ plotLayout)
  Q_PROPERTY(bool autoAddPlottableToLegend READ autoAddPlottableToLegend WRITE setAutoAddPlottableToLegend)
  Q_PROPERTY(int selectionTolerance READ selectionTolerance WRITE setSelectionTolerance)
  Q_PROPERTY(bool noAntialiasingOnDrag READ noAntialiasingOnDrag WRITE setNoAntialiasingOnDrag)
  Q_PROPERTY(Qt::KeyboardModifier multiSelectModifier READ multiSelectModifier WRITE setMultiSelectModifier)
  Q_PROPERTY(bool openGl READ openGl WRITE setOpenGl)
  /// \endcond
public:
  /*!
    Defines how a layer should be inserted relative to an other layer.

    \see addLayer, moveLayer
  */
  /* !
    다른 레이어를 기준으로 레이어를 삽입하는 방법을 정의합니다.
    \ see addLayer, moveLayer
  */
  enum LayerInsertMode { limBelow  ///< Layer is inserted below other layer /// <다른 레이어 아래에 레이어가 삽입되었습니다.
                         ,limAbove ///< Layer is inserted above other layer /// <레이어가 다른 레이어 위에 삽입됩니다.
                       };
  Q_ENUMS(LayerInsertMode)
  
  /*!
    Defines with what timing the QCustomPlot surface is refreshed after a replot.

    \see replot
  */
 /* !
    복제 후에 QCustomPlot 표면을 새로 고칠 타이밍을 정의합니다.
    \ 복제본보기
  */
  enum RefreshPriority { rpImmediateRefresh ///< Replots immediately and repaints the widget immediately by calling QWidget::repaint() after the replot
/// <replot 바로 다음에 QWidget :: repaint ()를 호출하여 즉시 재부팅하고 위젯을 다시 그립니다.
                         ,rpQueuedRefresh   ///< Replots immediately, but queues the widget repaint, by calling QWidget::update() after the replot. This way multiple redundant widget repaints can be avoided.
/// <replot 바로 뒤에 QWidget :: update ()를 호출하여 위젯 repaint을 대기열에 넣습니다. 이렇게하면 여러 중복 된 위젯 다시 칠을 피할 수 있습니다
                         ,rpRefreshHint     ///< Whether to use immediate or queued refresh depends on whether the plotting hint \ref QCP::phImmediateRefresh is set, see \ref setPlottingHints.
/// <즉시 새로 고침 또는 대기열 새로 고침을 사용할지 여부는 플로팅 힌트 \ ref QCP :: phImmediateRefresh가 설정되었는지 여부에 따라 다릅니다. \ ref setPlottingHints를 참조하십시오.
                         ,rpQueuedReplot    ///< Queues the entire replot for the next event loop iteration. This way multiple redundant replots can be avoided. The actual replot is then done with \ref rpRefreshHint priority.
/// <다음 이벤트 루프 반복을 위해 전체 복제본을 큐에 넣습니다. 이렇게하면 중복 된 중복 복제를 피할 수 있습니다. 실제 replot은 \ ref rpRefreshHint 우선 순위로 수행됩니다.
                       };
  Q_ENUMS(RefreshPriority)
  
  explicit QCustomPlot(QWidget *parent = 0);
  virtual ~QCustomPlot();
  
  // getters:
  QRect viewport() const { return mViewport; }
  double bufferDevicePixelRatio() const { return mBufferDevicePixelRatio; }
  QPixmap background() const { return mBackgroundPixmap; }
  bool backgroundScaled() const { return mBackgroundScaled; }
  Qt::AspectRatioMode backgroundScaledMode() const { return mBackgroundScaledMode; }
  QCPLayoutGrid *plotLayout() const { return mPlotLayout; }
  QCP::AntialiasedElements antialiasedElements() const { return mAntialiasedElements; }
  QCP::AntialiasedElements notAntialiasedElements() const { return mNotAntialiasedElements; }
  bool autoAddPlottableToLegend() const { return mAutoAddPlottableToLegend; }
  const QCP::Interactions interactions() const { return mInteractions; }
  int selectionTolerance() const { return mSelectionTolerance; }
  bool noAntialiasingOnDrag() const { return mNoAntialiasingOnDrag; }
  QCP::PlottingHints plottingHints() const { return mPlottingHints; }
  Qt::KeyboardModifier multiSelectModifier() const { return mMultiSelectModifier; }
  QCP::SelectionRectMode selectionRectMode() const { return mSelectionRectMode; }
  QCPSelectionRect *selectionRect() const { return mSelectionRect; }
  bool openGl() const { return mOpenGl; }
  
  // setters:
  void setViewport(const QRect &rect);
  void setBufferDevicePixelRatio(double ratio);
  void setBackground(const QPixmap &pm);
  void setBackground(const QPixmap &pm, bool scaled, Qt::AspectRatioMode mode=Qt::KeepAspectRatioByExpanding);
  void setBackground(const QBrush &brush);
  void setBackgroundScaled(bool scaled);
  void setBackgroundScaledMode(Qt::AspectRatioMode mode);
  void setAntialiasedElements(const QCP::AntialiasedElements &antialiasedElements);
  void setAntialiasedElement(QCP::AntialiasedElement antialiasedElement, bool enabled=true);
  void setNotAntialiasedElements(const QCP::AntialiasedElements &notAntialiasedElements);
  void setNotAntialiasedElement(QCP::AntialiasedElement notAntialiasedElement, bool enabled=true);
  void setAutoAddPlottableToLegend(bool on);
  void setInteractions(const QCP::Interactions &interactions);
  void setInteraction(const QCP::Interaction &interaction, bool enabled=true);
  void setSelectionTolerance(int pixels);
  void setNoAntialiasingOnDrag(bool enabled);
  void setPlottingHints(const QCP::PlottingHints &hints);
  void setPlottingHint(QCP::PlottingHint hint, bool enabled=true);
  void setMultiSelectModifier(Qt::KeyboardModifier modifier);
  void setSelectionRectMode(QCP::SelectionRectMode mode);
  void setSelectionRect(QCPSelectionRect *selectionRect);
  void setOpenGl(bool enabled, int multisampling=16);
  
  // non-property methods:
  // plottable interface:
  // 비 속성 메소드 :
  // plottable 인터페이스 :
  QCPAbstractPlottable *plottable(int index);
  QCPAbstractPlottable *plottable();
  bool removePlottable(QCPAbstractPlottable *plottable);
  bool removePlottable(int index);
  int clearPlottables();
  int plottableCount() const;
  QList<QCPAbstractPlottable*> selectedPlottables() const;
  QCPAbstractPlottable *plottableAt(const QPointF &pos, bool onlySelectable=false) const;
  bool hasPlottable(QCPAbstractPlottable *plottable) const;
 
  // specialized interface for QCPGraph:
  // QCPGraph의 특수 인터페이스 :
  QCPGraph *graph(int index) const;
  QCPGraph *graph() const;
  QCPGraph *addGraph(QCPAxis *keyAxis=0, QCPAxis *valueAxis=0);
  bool removeGraph(QCPGraph *graph);
  bool removeGraph(int index);
  int clearGraphs();
  int graphCount() const;
  QList<QCPGraph*> selectedGraphs() const;

  // item interface:
  QCPAbstractItem *item(int index) const;
  QCPAbstractItem *item() const;
  bool removeItem(QCPAbstractItem *item);
  bool removeItem(int index);
  int clearItems();
  int itemCount() const;
  QList<QCPAbstractItem*> selectedItems() const;
  QCPAbstractItem *itemAt(const QPointF &pos, bool onlySelectable=false) const;
  bool hasItem(QCPAbstractItem *item) const;
  
  // layer interface:
  // 레이어 인터페이스 :
  QCPLayer *layer(const QString &name) const;
  QCPLayer *layer(int index) const;
  QCPLayer *currentLayer() const;
  bool setCurrentLayer(const QString &name);
  bool setCurrentLayer(QCPLayer *layer);
  int layerCount() const;
  bool addLayer(const QString &name, QCPLayer *otherLayer=0, LayerInsertMode insertMode=limAbove);
  bool removeLayer(QCPLayer *layer);
  bool moveLayer(QCPLayer *layer, QCPLayer *otherLayer, LayerInsertMode insertMode=limAbove);
  
  // axis rect/layout interface:
  // 축 rect / layout 인터페이스 :
  int axisRectCount() const;
  QCPAxisRect* axisRect(int index=0) const;
  QList<QCPAxisRect*> axisRects() const;
  QCPLayoutElement* layoutElementAt(const QPointF &pos) const;
  QCPAxisRect* axisRectAt(const QPointF &pos) const;
  Q_SLOT void rescaleAxes(bool onlyVisiblePlottables=false);
  
  QList<QCPAxis*> selectedAxes() const;
  QList<QCPLegend*> selectedLegends() const;
  Q_SLOT void deselectAll();
  
  bool savePdf(const QString &fileName, int width=0, int height=0, QCP::ExportPen exportPen=QCP::epAllowCosmetic, const QString &pdfCreator=QString(), const QString &pdfTitle=QString());
  bool savePng(const QString &fileName, int width=0, int height=0, double scale=1.0, int quality=-1, int resolution=96, QCP::ResolutionUnit resolutionUnit=QCP::ruDotsPerInch);
  bool saveJpg(const QString &fileName, int width=0, int height=0, double scale=1.0, int quality=-1, int resolution=96, QCP::ResolutionUnit resolutionUnit=QCP::ruDotsPerInch);
  bool saveBmp(const QString &fileName, int width=0, int height=0, double scale=1.0, int resolution=96, QCP::ResolutionUnit resolutionUnit=QCP::ruDotsPerInch);
  bool saveRastered(const QString &fileName, int width, int height, double scale, const char *format, int quality=-1, int resolution=96, QCP::ResolutionUnit resolutionUnit=QCP::ruDotsPerInch);
  QPixmap toPixmap(int width=0, int height=0, double scale=1.0);
  void toPainter(QCPPainter *painter, int width=0, int height=0);
  Q_SLOT void replot(QCustomPlot::RefreshPriority refreshPriority=QCustomPlot::rpRefreshHint);
  
  QCPAxis *xAxis, *yAxis, *xAxis2, *yAxis2;
  QCPLegend *legend;
  
signals:
  void mouseDoubleClick(QMouseEvent *event);
  void mousePress(QMouseEvent *event);
  void mouseMove(QMouseEvent *event);
  void mouseRelease(QMouseEvent *event);
  void mouseWheel(QWheelEvent *event);
  
  void plottableClick(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
  void plottableDoubleClick(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
  void itemClick(QCPAbstractItem *item, QMouseEvent *event);
  void itemDoubleClick(QCPAbstractItem *item, QMouseEvent *event);
  void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
  void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
  void legendClick(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);
  void legendDoubleClick(QCPLegend *legend,  QCPAbstractLegendItem *item, QMouseEvent *event);
  
  void selectionChangedByUser();
  void beforeReplot();
  void afterReplot();
  
protected:
  // property members:
  // 속성 멤버 :
  QRect mViewport;
  double mBufferDevicePixelRatio;
  QCPLayoutGrid *mPlotLayout;
  bool mAutoAddPlottableToLegend;
  QList<QCPAbstractPlottable*> mPlottables;
  QList<QCPGraph*> mGraphs;       // extra list of plottables also in mPlottables that are of type QCPGraph
  QList<QCPAbstractItem*> mItems; // QCPGraph 유형의 mPlottables에도있는 plottables의 추가 목록
  QList<QCPLayer*> mLayers;
  QCP::AntialiasedElements mAntialiasedElements, mNotAntialiasedElements;
  QCP::Interactions mInteractions;
  int mSelectionTolerance;
  bool mNoAntialiasingOnDrag;
  QBrush mBackgroundBrush;
  QPixmap mBackgroundPixmap;
  QPixmap mScaledBackgroundPixmap;
  bool mBackgroundScaled;
  Qt::AspectRatioMode mBackgroundScaledMode;
  QCPLayer *mCurrentLayer;
  QCP::PlottingHints mPlottingHints;
  Qt::KeyboardModifier mMultiSelectModifier;
  QCP::SelectionRectMode mSelectionRectMode;
  QCPSelectionRect *mSelectionRect;
  bool mOpenGl;
  
  // non-property members:
  // 비 속성 멤버 :
  QList<QSharedPointer<QCPAbstractPaintBuffer> > mPaintBuffers;
  QPoint mMousePressPos;
  bool mMouseHasMoved;
  QPointer<QCPLayerable> mMouseEventLayerable;
  QPointer<QCPLayerable> mMouseSignalLayerable;
  QVariant mMouseEventLayerableDetails;
  QVariant mMouseSignalLayerableDetails;
  bool mReplotting;
  bool mReplotQueued;
  int mOpenGlMultisamples;
  QCP::AntialiasedElements mOpenGlAntialiasedElementsBackup;
  bool mOpenGlCacheLabelsBackup;
#ifdef QCP_OPENGL_FBO
  QSharedPointer<QOpenGLContext> mGlContext;
  QSharedPointer<QSurface> mGlSurface;
  QSharedPointer<QOpenGLPaintDevice> mGlPaintDevice;
#endif
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QSize minimumSizeHint() const Q_DECL_OVERRIDE;
  virtual QSize sizeHint() const Q_DECL_OVERRIDE;
  virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void draw(QCPPainter *painter);
  virtual void updateLayout();
  virtual void axisRemoved(QCPAxis *axis);
  virtual void legendRemoved(QCPLegend *legend);
  Q_SLOT virtual void processRectSelection(QRect rect, QMouseEvent *event);
  Q_SLOT virtual void processRectZoom(QRect rect, QMouseEvent *event);
  Q_SLOT virtual void processPointSelection(QMouseEvent *event);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  bool registerPlottable(QCPAbstractPlottable *plottable);
  bool registerGraph(QCPGraph *graph);
  bool registerItem(QCPAbstractItem* item);
  void updateLayerIndices() const;
  QCPLayerable *layerableAt(const QPointF &pos, bool onlySelectable, QVariant *selectionDetails=0) const;
  QList<QCPLayerable*> layerableListAt(const QPointF &pos, bool onlySelectable, QList<QVariant> *selectionDetails=0) const;
  void drawBackground(QCPPainter *painter);
  void setupPaintBuffers();
  QCPAbstractPaintBuffer *createPaintBuffer();
  bool hasInvalidatedPaintBuffers();
  bool setupOpenGl();
  void freeOpenGl();
  
  friend class QCPLegend;
  friend class QCPAxis;
  friend class QCPLayer;
  friend class QCPAxisRect;
  friend class QCPAbstractPlottable;
  friend class QCPGraph;
  friend class QCPAbstractItem;
};
Q_DECLARE_METATYPE(QCustomPlot::LayerInsertMode)
Q_DECLARE_METATYPE(QCustomPlot::RefreshPriority)

/* end of 'src/core.h' */


/* including file 'src/plottable1d.h', size 4544                             */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / core.h'의 끝 */


/* 파일 'src / plottable1d.h'포함, 크기 4544                              */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCPPlottableInterface1D
{
public:
  virtual ~QCPPlottableInterface1D() {}
  // introduced pure virtual methods:
  // 순수 가상 메소드 도입 :
  virtual int dataCount() const = 0;
  virtual double dataMainKey(int index) const = 0;
  virtual double dataSortKey(int index) const = 0;
  virtual double dataMainValue(int index) const = 0;
  virtual QCPRange dataValueRange(int index) const = 0;
  virtual QPointF dataPixelPosition(int index) const = 0;
  virtual bool sortKeyIsMainKey() const = 0;
  virtual QCPDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const = 0;
  virtual int findBegin(double sortKey, bool expandedRange=true) const = 0;
  virtual int findEnd(double sortKey, bool expandedRange=true) const = 0;
};

template <class DataType>
class QCPAbstractPlottable1D : public QCPAbstractPlottable, public QCPPlottableInterface1D // no QCP_LIB_DECL, template class ends up in header (cpp included below)
// QCP_LIB_DECL 없음, 템플릿 클래스가 헤더로 끝납니다 (아래 cpp 포함).
{
  // No Q_OBJECT macro due to template class
  // 템플릿 클래스로 인해 Q_OBJECT 매크로가 없습니다.
  
public:
  QCPAbstractPlottable1D(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPAbstractPlottable1D();
  
  // virtual methods of 1d plottable interface:
  // 1d plottable 인터페이스의 가상 메소드 :
  virtual int dataCount() const Q_DECL_OVERRIDE;
  virtual double dataMainKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataSortKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataMainValue(int index) const Q_DECL_OVERRIDE;
  virtual QCPRange dataValueRange(int index) const Q_DECL_OVERRIDE;
  virtual QPointF dataPixelPosition(int index) const Q_DECL_OVERRIDE;
  virtual bool sortKeyIsMainKey() const Q_DECL_OVERRIDE;
  virtual QCPDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual int findBegin(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  virtual int findEnd(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPPlottableInterface1D *interface1D() Q_DECL_OVERRIDE { return this; }
  
protected:
  // property members:
  // 속성 멤버 :
  QSharedPointer<QCPDataContainer<DataType> > mDataContainer;
  
  // helpers for subclasses:
  // 하위 클래스에 대한 헬퍼 :
  void getDataSegments(QList<QCPDataRange> &selectedSegments, QList<QCPDataRange> &unselectedSegments) const;
  void drawPolyline(QCPPainter *painter, const QVector<QPointF> &lineData) const;

private:
  Q_DISABLE_COPY(QCPAbstractPlottable1D)
  
};

// include implementation in header since it is a class template:

/* including file 'src/plottable1d.cpp', size 22240                          */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
// 클래스 템플릿이므로 헤더에 구현을 포함시킵니다.

/* 파일 'src / plottable1d.cpp'포함, 크기 22240                           */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPPlottableInterface1D
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPPlottableInterface1D
  \brief Defines an abstract interface for one-dimensional plottables

  This class contains only pure virtual methods which define a common interface to the data
  of one-dimensional plottables.

  For example, it is implemented by the template class \ref QCPAbstractPlottable1D (the preferred
  base class for one-dimensional plottables). So if you use that template class as base class of
  your one-dimensional plottable, you won't have to care about implementing the 1d interface
  yourself.

  If your plottable doesn't derive from \ref QCPAbstractPlottable1D but still wants to provide a 1d
  interface (e.g. like \ref QCPErrorBars does), you should inherit from both \ref
  QCPAbstractPlottable and \ref QCPPlottableInterface1D and accordingly reimplement the pure
  virtual methods of the 1d interface, matching your data container. Also, reimplement \ref
  QCPAbstractPlottable::interface1D to return the \c this pointer.

  If you have a \ref QCPAbstractPlottable pointer, you can check whether it implements this
  interface by calling \ref QCPAbstractPlottable::interface1D and testing it for a non-zero return
  value. If it indeed implements this interface, you may use it to access the plottable's data
  without needing to know the exact type of the plottable or its data point type.
*/
/* ! \ class QCPPlottableInterface1D
  \ brief 1 차원 Plotables에 대한 추상 인터페이스를 정의합니다.
  이 클래스는 데이터에 대한 공통 인터페이스를 정의하는 순수 가상 메서드 만 포함합니다.
  1 차원 plottables.
  예를 들어, 템플릿 클래스 \ ref QCPAbstractPlottable1D (기본 설정
  1 차원 Plotables의 기본 클래스). 그래서 그 템플릿 클래스를 기본 클래스로 사용하면
  1 차원 플롯 테이블을 사용하면 1d 인터페이스를 구현할 필요가 없습니다.
  당신 자신.
  귀하의 플롯 테이블이 \ ref QCPAbstractPlottable1D에서 파생되지는 않지만 여전히 1d를 제공하려고한다면
  인터페이스 (예 : \ ref QCPErrorBars)와 같이 \ ref에서 상속해야합니다.
  QCPAbstractPlottable 및 \ ref QCPPlottableInterface1D를 호출하여 순수한
  데이터 컨테이너와 일치하는 1d 인터페이스의 가상 메소드 또한 \ ref를 다시 구현하십시오.
  이 포인터를 반환하는 QCPAbstractPlottable :: interface1D.
  \ ref QCPAbstractPlottable 포인터가 있으면이 포인터가 구현되는지 여부를 확인할 수 있습니다
  \ ref QCPAbstractPlottable :: interface1D를 호출하고 0이 아닌 값으로 테스트하여 인터페이스
  값. 이 인터페이스를 실제로 구현하는 경우이를 사용하여 플롯 테이블의 데이터에 액세스 할 수 있습니다
  플롯 테이블 또는 데이터 포인트 유형의 정확한 유형을 알 필요가 없습니다.
*/


/* start documentation of pure virtual functions */
/* 순수 가상 함수의 시작 문서 */

/*! \fn virtual int QCPPlottableInterface1D::dataCount() const = 0;
  
  Returns the number of data points of the plottable.
*/
/* ! \ fn 가상 int QCPPlottableInterface1D :: dataCount () const = 0;
  
  플롯 테이블의 데이터 요소 수를 반환합니다.
*/

/*! \fn virtual QCPDataSelection QCPPlottableInterface1D::selectTestRect(const QRectF &rect, bool onlySelectable) const = 0;
  
  Returns a data selection containing all the data points of this plottable which are contained (or
  hit by) \a rect. This is used mainly in the selection rect interaction for data selection (\ref
  dataselection "data selection mechanism").
  
  If \a onlySelectable is true, an empty QCPDataSelection is returned if this plottable is not
  selectable (i.e. if \ref QCPAbstractPlottable::setSelectable is \ref QCP::stNone).
  
  \note \a rect must be a normalized rect (positive or zero width and height). This is especially
  important when using the rect of \ref QCPSelectionRect::accepted, which is not necessarily
  normalized. Use <tt>QRect::normalized()</tt> when passing a rect which might not be normalized.
*/
/* ! \ fn 가상 QCPDataSelection QCPPlottableInterface1D :: selectTestRect (const QRectF & rect, bool onlySelectable) const = 0;
  
  포함 된 (또는 포함 된)이 플롯 테이블의 모든 데이터 요소를 포함하는 데이터 선택을 반환합니다.
  hit by) \ a rect. 주로 데이터 선택을위한 선택 항목 상호 작용에 사용됩니다 (\ ref
  데이터 선택 "데이터 선택 메커니즘).
  
  \ a onlySelectable이 true이면이 plottable이 아닌 경우 빈 QCPDataSelection이 반환됩니다.
  선택할 수 있습니다 (즉, \ ref QCPAbstractPlottable :: setSelectable이 \ ref QCP :: stNone 인 경우).
  
  \ note \ rect는 정규화 된 rect (양수 또는 0 너비 및 높이) 여야합니다. 이것은 특히
  \ ref QCPSelectionRect :: accepted의 rect를 사용할 때 중요합니다. 반드시 필요하지는 않습니다.
  표준화. 정규화되지 않을 수도있는 rect를 전달할 때는 <tt> QRect :: normalized () </ tt>를 사용하십시오.
*/

/*! \fn virtual double QCPPlottableInterface1D::dataMainKey(int index) const = 0
  
  Returns the main key of the data point at the given \a index.
  
  What the main key is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "QCPDataContainer DataType" documentation for details about this naming
  convention.
*/
/* ! \ fn 가상 더블 QCPPlottableInterface1D :: dataMainKey (int index) const = 0
  
  지정된 \ a 인덱스에있는 데이터 요소의 기본 키를 반환합니다.
  
  기본 키는 플롯 테이블의 데이터 유형에 의해 정의됩니다. \ ref를 보라.
  이 명명에 대한 자세한 내용은 qcpdatacontainer-datatype "QCPDataContainer DataType"설명서를 참조하십시오.
  협약.
*/

/*! \fn virtual double QCPPlottableInterface1D::dataSortKey(int index) const = 0
  
  Returns the sort key of the data point at the given \a index.
  
  What the sort key is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "QCPDataContainer DataType" documentation for details about this naming
  convention.
*/
/* ! \ fn 가상 더블 QCPPlottableInterface1D :: dataSortKey (int index) const = 0
  
  지정된 \ a 인덱스에있는 데이터 포인트의 정렬 키를 리턴합니다.
  
  정렬 키는 플롯 테이블의 데이터 유형에 의해 정의됩니다. \ ref를 보라.
  이 명명에 대한 자세한 내용은 qcpdatacontainer-datatype "QCPDataContainer DataType"설명서를 참조하십시오.
  협약.
*/

/*! \fn virtual double QCPPlottableInterface1D::dataMainValue(int index) const = 0
  
  Returns the main value of the data point at the given \a index.
  
  What the main value is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "QCPDataContainer DataType" documentation for details about this naming
  convention.
*/
/* ! \ fn 가상 더블 QCPPlottableInterface1D :: dataMainValue (int index) const = 0
  
  지정된 \ a 인덱스에있는 데이터 요소의 주 값을 반환합니다.
  
  주요 값은 플롯 테이블의 데이터 유형에 의해 정의됩니다. \ ref를 보라.
  이 명명에 대한 자세한 내용은 qcpdatacontainer-datatype "QCPDataContainer DataType"설명서를 참조하십시오.
  협약.
*/
/*! \fn virtual QCPRange QCPPlottableInterface1D::dataValueRange(int index) const = 0
  
  Returns the value range of the data point at the given \a index.
  
  What the value range is, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "QCPDataContainer DataType" documentation for details about this naming
  convention.
*/
/* ! \ fn 가상 QCPRange QCPPlottableInterface1D :: dataValueRange (int index) const = 0
  
  지정된 \ a 인덱스에있는 데이터 요소의 값 범위를 반환합니다.
  
  값 범위는 플롯 테이블의 데이터 유형에 의해 정의됩니다. \ ref를 보라.
  이 명명에 대한 자세한 내용은 qcpdatacontainer-datatype "QCPDataContainer DataType"설명서를 참조하십시오.
  협약.
*/

/*! \fn virtual QPointF QCPPlottableInterface1D::dataPixelPosition(int index) const = 0

  Returns the pixel position on the widget surface at which the data point at the given \a index
  appears.

  Usually this corresponds to the point of \ref dataMainKey/\ref dataMainValue, in pixel
  coordinates. However, depending on the plottable, this might be a different apparent position
  than just a coord-to-pixel transform of those values. For example, \ref QCPBars apparent data
  values can be shifted depending on their stacking, bar grouping or configured base value.
*/
/* ! \ fn 가상 QPointF QCPPlottableInterface1D :: dataPixelPosition (int index) const = 0
  지정된 \ a 인덱스의 데이터 점이있는 위젯 표면의 픽셀 위치를 반환합니다.
  나타납니다.
  일반적으로 \ ref dataMainKey / \ ref dataMainValue의 점에 해당합니다 (픽셀 단위).
  좌표. 그러나 플롯 테이블에 따라이 위치가 다를 수 있습니다.
  이러한 값의 좌표 대 픽셀 변환보다 예를 들어, \ ref QCPBars 명백한 데이터
  스태킹, 바 그룹 또는 구성된 기본 값에 따라 값을 이동할 수 있습니다.
*/

/*! \fn virtual bool QCPPlottableInterface1D::sortKeyIsMainKey() const = 0

  Returns whether the sort key (\ref dataSortKey) is identical to the main key (\ref dataMainKey).

  What the sort and main keys are, is defined by the plottable's data type. See the \ref
  qcpdatacontainer-datatype "QCPDataContainer DataType" documentation for details about this naming
  convention.
*/
/* ! \ fn 가상 bool QCPPlottableInterface1D :: sortKeyIsMainKey () const = 0
  소트 키 (\ ref dataSortKey)가 메인 키 (\ ref dataMainKey)와 동일한 지 어떤지를 반환합니다.
  정렬 및 기본 키는 플롯 테이블의 데이터 유형에 의해 정의됩니다. \ ref를 보라.
  이 명명에 대한 자세한 내용은 qcpdatacontainer-datatype "QCPDataContainer DataType"설명서를 참조하십시오.
  협약.
*/

/*! \fn virtual int QCPPlottableInterface1D::findBegin(double sortKey, bool expandedRange) const = 0

  Returns the index of the data point with a (sort-)key that is equal to, just below, or just above
  \a sortKey. If \a expandedRange is true, the data point just below \a sortKey will be considered,
  otherwise the one just above.

  This can be used in conjunction with \ref findEnd to iterate over data points within a given key
  range, including or excluding the bounding data points that are just beyond the specified range.

  If \a expandedRange is true but there are no data points below \a sortKey, 0 is returned.

  If the container is empty, returns 0 (in that case, \ref findEnd will also return 0, so a loop
  using these methods will not iterate over the index 0).

  \see findEnd, QCPDataContainer::findBegin
*/
/* ! \ fn 가상 정수 QCPPlottableInterface1D :: findBegin (double sortKey, bool expandedRange) const = 0
  데이터 포인트와 동일한, 바로 아래 또는 바로 위에 (정렬) 키가있는 데이터 요소의 인덱스를 반환합니다.
  \ sortKey. \ a expandedLange가 true의 경우, sortKey의 바로 아래의 데이터 포인트가 고려됩니다.
  그렇지 않으면 위에있는 것.
  \ ref findEnd와 함께 사용하면 주어진 키 내의 데이터 요소를 반복 할 수 있습니다
  범위를 벗어나면 지정된 범위를 벗어나는 경계 데이터 점을 포함하거나 제외 할 수 있습니다.
  \ a expandedRange가 true이지만 sortKey 아래에 데이터 포인트가없는 경우 0이 리턴됩니다.
  컨테이너가 비어 있으면 0을 반환합니다 (이 경우 \ ref findEnd도 0을 반환하므로 루프가 반환됩니다.
  이러한 메소드를 사용하면 인덱스 0을 반복하지 않습니다.
  \ findEnd, QCPDataContainer :: findBegin을 참조하십시오.
*/

/*! \fn virtual int QCPPlottableInterface1D::findEnd(double sortKey, bool expandedRange) const = 0

  Returns the index one after the data point with a (sort-)key that is equal to, just above, or
  just below \a sortKey. If \a expandedRange is true, the data point just above \a sortKey will be
  considered, otherwise the one just below.

  This can be used in conjunction with \ref findBegin to iterate over data points within a given
  key range, including the bounding data points that are just below and above the specified range.

  If \a expandedRange is true but there are no data points above \a sortKey, the index just above the
  highest data point is returned.

  If the container is empty, returns 0.

  \see findBegin, QCPDataContainer::findEnd
*/
/* ! \ fn 가상 정수 QCPPlottableInterface1D :: findEnd (double sortKey, bool expandedRange) const = 0
  데이터 포인트 뒤의 인덱스 1을 반환합니다.
  \ sortKey 바로 아래에. \ a expandedLange가 true 인 경우 \ sortKey 바로 위에있는 데이터 요소는
  고려해야합니다. 그렇지 않으면 바로 아래에있는 것입니다.
  이것은 \ ref findBegin과 함께 사용하여 주어진 데이터 포인트를 반복 처리 할 수 ​​있습니다.
  지정된 범위 바로 아래 및 위에있는 경계 데이터 점을 포함하여 키 범위.
  \ a expandedRange가 true이지만 \ sortKey 위에 데이터 포인트가없는 경우 인덱스 바로 위에있는 인덱스
  가장 높은 데이터 포인트가 반환됩니다.
  컨테이너가 비어 있으면 0을 반환합니다.
  \ findBegin, QCPDataContainer :: findEnd를 참조하십시오.
*/


/* end documentation of pure virtual functions */
/* 순수 가상 함수의 끝 문서 */


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPAbstractPlottable1D
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPAbstractPlottable1D
  \brief A template base class for plottables with one-dimensional data

  This template class derives from \ref QCPAbstractPlottable and from the abstract interface \ref
  QCPPlottableInterface1D. It serves as a base class for all one-dimensional data (i.e. data with
  one key dimension), such as \ref QCPGraph and QCPCurve.

  The template parameter \a DataType is the type of the data points of this plottable (e.g. \ref
  QCPGraphData or \ref QCPCurveData). The main purpose of this base class is to provide the member
  \a mDataContainer (a shared pointer to a \ref QCPDataContainer "QCPDataContainer<DataType>") and
  implement the according virtual methods of the \ref QCPPlottableInterface1D, such that most
  subclassed plottables don't need to worry about this anymore.

  Further, it provides a convenience method for retrieving selected/unselected data segments via
  \ref getDataSegments. This is useful when subclasses implement their \ref draw method and need to
  draw selected segments with a different pen/brush than unselected segments (also see \ref
  QCPSelectionDecorator).

  This class implements basic functionality of \ref QCPAbstractPlottable::selectTest and \ref
  QCPPlottableInterface1D::selectTestRect, assuming point-like data points, based on the 1D data
  interface. In spite of that, most plottable subclasses will want to reimplement those methods
  again, to provide a more accurate hit test based on their specific data visualization geometry.
*/
/* ! \ class QCPAbstractPlottable1D
  \ brief 1 차원 데이터가있는 플롯 테이블에 대한 템플릿 기본 클래스입니다.
  이 템플릿 클래스는 \ ref QCPAbstractPlottable 및 추상 인터페이스 \ ref에서 파생됩니다.
  QCPPlottableInterface1D. 모든 1 차원 데이터의 기본 클래스로 사용됩니다 (예 :
  하나의 키 차원) (예 : \ ref QCPGraph 및 QCPCurve).
  템플릿 매개 변수 \ a DataType은이 표의 데이터 요소 유형입니다 (예 : \ ref
  QCPGraphData 또는 \ ref QCPCurveData). 이 기본 클래스의 주 목적은 멤버에게
  \ mDataContainer (\ ref QCPDataContainer "QCPDataContainer <DataType>"에 대한 공유 포인터) 및
  \ ref QCPPlottableInterface1D의 가상 메소드를 구현하여
  서브 클래 싱 된 플롯 테이블은 더 이상 걱정할 필요가 없습니다.
  또한, 선택 / 비 선택 데이터 세그먼트를 검색하는 편리한 방법을 제공합니다.
  \ ref getDataSegments. 서브 클래스가 \ ref draw 메소드를 구현했을 때 유용합니다.
  선택한 세그먼트를 선택되지 않은 세그먼트와 다른 펜 / 브러쉬로 그립니다 (\ ref도 참조하십시오).
  QCPSelectionDecorator).
  이 클래스는 \ ref QCPAbstractPlottable :: selectTest 및 \ ref의 기본 기능을 구현합니다.
  QCPPlottableInterface1D :: selectTestRect, 1D 데이터를 기반으로 점 형식의 데이터 요소라고 가정합니다.
  인터페이스. 그럼에도 불구하고 대부분의 plottable 서브 클래스는 이러한 메소드를 다시 구현하고자합니다.
  특정 데이터 시각화 지오메트리를 기반으로보다 정확한 히트 테스트를 제공합니다.
*/

/* start documentation of inline functions */
/* 인라인 함수의 시작 문서 */

/*! \fn QCPPlottableInterface1D *QCPAbstractPlottable1D::interface1D()
  
  Returns a \ref QCPPlottableInterface1D pointer to this plottable, providing access to its 1D
  interface.
  
  \seebaseclassmethod
*/
/* ! \ fn QCPPlottableInterface1D * QCPAbstractPlottable1D :: interface1D ()
  
  이 플롯 테이블에 \ ref QCPPlottableInterface1D 포인터를 반환하여 1D에 대한 액세스를 제공합니다.
  인터페이스.
  
  \ seebaseclassmethod
*/

/* end documentation of inline functions */
/* 인라인 함수의 끝 문서화 */

/*!
  Forwards \a keyAxis and \a valueAxis to the \ref QCPAbstractPlottable::QCPAbstractPlottable
  "QCPAbstractPlottable" constructor and allocates the \a mDataContainer.
*/
/* !
  \ keyAxis 및 \ a valueAxis를 \ ref QCPAbstractPlottable :: QCPAbstractPlottable로 전달합니다.
  "QCPAbstractPlottable"생성자를 만들고 mDataContainer를 할당합니다.
*/
template <class DataType>
QCPAbstractPlottable1D<DataType>::QCPAbstractPlottable1D(QCPAxis *keyAxis, QCPAxis *valueAxis) :
  QCPAbstractPlottable(keyAxis, valueAxis),
  mDataContainer(new QCPDataContainer<DataType>)
{
}

template <class DataType>
QCPAbstractPlottable1D<DataType>::~QCPAbstractPlottable1D()
{
}

/*!
  \copydoc QCPPlottableInterface1D::dataCount
*/

template <class DataType>
int QCPAbstractPlottable1D<DataType>::dataCount() const
{
  return mDataContainer->size();
}

/*!
  \copydoc QCPPlottableInterface1D::dataMainKey
*/
/* !
  \ copydoc QCPPlottableInterface1D :: dataMainKey
*/
template <class DataType>
double QCPAbstractPlottable1D<DataType>::dataMainKey(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->mainKey();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return 0;
  }
}

/*!
  \copydoc QCPPlottableInterface1D::dataSortKey
*/
/* !
  \ copydoc QCPPlottableInterface1D :: dataSortKey
*/
template <class DataType>
double QCPAbstractPlottable1D<DataType>::dataSortKey(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->sortKey();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return 0;
  }
}

/*!
  \copydoc QCPPlottableInterface1D::dataMainValue
*/
/* !
  \ copydoc QCPPlottableInterface1D :: dataMainValue
*/
template <class DataType>
double QCPAbstractPlottable1D<DataType>::dataMainValue(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->mainValue();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return 0;
  }
}

/*!
  \copydoc QCPPlottableInterface1D::dataValueRange
*/
/* !
  \ copydoc QCPPlottableInterface1D :: dataValueRange
*/
template <class DataType>
QCPRange QCPAbstractPlottable1D<DataType>::dataValueRange(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    return (mDataContainer->constBegin()+index)->valueRange();
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return QCPRange(0, 0);
  }
}

/*!
  \copydoc QCPPlottableInterface1D::dataPixelPosition
*/
/* !
  \ copydoc QCPPlottableInterface1D :: dataPixelPosition
*/
template <class DataType>
QPointF QCPAbstractPlottable1D<DataType>::dataPixelPosition(int index) const
{
  if (index >= 0 && index < mDataContainer->size())
  {
    const typename QCPDataContainer<DataType>::const_iterator it = mDataContainer->constBegin()+index;
    return coordsToPixels(it->mainKey(), it->mainValue());
  } else
  {
    qDebug() << Q_FUNC_INFO << "Index out of bounds" << index;
    return QPointF();
  }
}

/*!
  \copydoc QCPPlottableInterface1D::sortKeyIsMainKey
*/
/* !
  \ copydoc QCPPlottableInterface1D :: sortKeyIsMainKey
*/
template <class DataType>
bool QCPAbstractPlottable1D<DataType>::sortKeyIsMainKey() const
{
  return DataType::sortKeyIsMainKey();
}

/*!
  Implements a rect-selection algorithm assuming the data (accessed via the 1D data interface) is
  point-like. Most subclasses will want to reimplement this method again, to provide a more
  accurate hit test based on the true data visualization geometry.

  \seebaseclassmethod
*/
/* !
  데이터 (1D 데이터 인터페이스를 통해 액세스 됨)가 다음과 같다고 가정 할 때 rect 선택 알고리즘을 구현합니다.
  point-like. 대부분의 서브 클래스에서는,이 메소드를 다시 구현해,보다 많은 정보를 제공하려고합니다.
  진정한 데이터 시각화 기하학에 기반한 정확한 히트 테스트.
  \ seebaseclassmethod
*/
template <class DataType>
QCPDataSelection QCPAbstractPlottable1D<DataType>::selectTestRect(const QRectF &rect, bool onlySelectable) const
{
  QCPDataSelection result;
  if ((onlySelectable && mSelectable == QCP::stNone) || mDataContainer->isEmpty())
    return result;
  if (!mKeyAxis || !mValueAxis)
    return result;
  
  // convert rect given in pixels to ranges given in plot coordinates:
  // 픽셀로 주어진 rect를 그림 좌표로 주어진 범위로 변환 :
  double key1, value1, key2, value2;
  pixelsToCoords(rect.topLeft(), key1, value1);
  pixelsToCoords(rect.bottomRight(), key2, value2);
  QCPRange keyRange(key1, key2); // QCPRange normalizes internally so we don't have to care about whether key1 < key2
  QCPRange valueRange(value1, value2); // QCPRange는 내부적으로 표준화되므로 key1 <key2
  typename QCPDataContainer<DataType>::const_iterator begin = mDataContainer->constBegin();
  typename QCPDataContainer<DataType>::const_iterator end = mDataContainer->constEnd();
  if (DataType::sortKeyIsMainKey()) // we can assume that data is sorted by main key, so can reduce the searched key interval:
// 데이터가 메인 키에 의해 정렬된다고 가정 할 수 있으므로 검색된 키 간격을 줄일 수 있습니다 :
  {
    begin = mDataContainer->findBegin(keyRange.lower, false);
    end = mDataContainer->findEnd(keyRange.upper, false);
  }
  if (begin == end)
    return result;
  
  int currentSegmentBegin = -1; // -1 means we're currently not in a segment that's contained in rect
                                // -1은 현재 rect에 포함 된 세그먼트에 없다는 것을 의미합니다.
  for (typename QCPDataContainer<DataType>::const_iterator it=begin; it!=end; ++it)
  {
    if (currentSegmentBegin == -1)
    {
      if (valueRange.contains(it->mainValue()) && keyRange.contains(it->mainKey())) // start segment
        currentSegmentBegin = it-mDataContainer->constBegin();                      // 세그먼트를 시작
    } else if (!valueRange.contains(it->mainValue()) || !keyRange.contains(it->mainKey())) // segment just ended
    {                                                                                      // 세그먼트는 끝났다
      result.addDataRange(QCPDataRange(currentSegmentBegin, it-mDataContainer->constBegin()), false);
      currentSegmentBegin = -1;
    }
  }
  // process potential last segment:
  // 잠재적 인 마지막 세그먼트 처리 :
  if (currentSegmentBegin != -1)
    result.addDataRange(QCPDataRange(currentSegmentBegin, end-mDataContainer->constBegin()), false);
  
  result.simplify();
  return result;
}

/*!
  \copydoc QCPPlottableInterface1D::findBegin
*/
/* !
  \ copydoc QCPPlottableInterface1D :: findBegin
*/
template <class DataType>
int QCPAbstractPlottable1D<DataType>::findBegin(double sortKey, bool expandedRange) const
{
  return mDataContainer->findBegin(sortKey, expandedRange)-mDataContainer->constBegin();
}

/*!
  \copydoc QCPPlottableInterface1D::findEnd
*/
/* !
  \ copydoc QCPPlottableInterface1D :: findEnd
*/
template <class DataType>
int QCPAbstractPlottable1D<DataType>::findEnd(double sortKey, bool expandedRange) const
{
  return mDataContainer->findEnd(sortKey, expandedRange)-mDataContainer->constBegin();
}

/*!
  Implements a point-selection algorithm assuming the data (accessed via the 1D data interface) is
  point-like. Most subclasses will want to reimplement this method again, to provide a more
  accurate hit test based on the true data visualization geometry.

  \seebaseclassmethod
*/
/* !
  데이터 (1D 데이터 인터페이스를 통해 액세스)가 다음과 같다고 가정 할 때 점 선택 알고리즘을 구현합니다.
  point-like. 대부분의 서브 클래스에서는,이 메소드를 다시 구현해,보다 많은 정보를 제공하려고합니다.
  진정한 데이터 시각화 기하학에 기반한 정확한 히트 테스트.
  \ seebaseclassmethod
*/
template <class DataType>
double QCPAbstractPlottable1D<DataType>::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
  if ((onlySelectable && mSelectable == QCP::stNone) || mDataContainer->isEmpty())
    return -1;
  if (!mKeyAxis || !mValueAxis)
    return -1;
  
  QCPDataSelection selectionResult;
  double minDistSqr = std::numeric_limits<double>::max();
  int minDistIndex = mDataContainer->size();
  
  typename QCPDataContainer<DataType>::const_iterator begin = mDataContainer->constBegin();
  typename QCPDataContainer<DataType>::const_iterator end = mDataContainer->constEnd();
  if (DataType::sortKeyIsMainKey()) // we can assume that data is sorted by main key, so can reduce the searched key interval:
// 데이터가 메인 키에 의해 정렬된다고 가정 할 수 있으므로 검색된 키 간격을 줄일 수 있습니다 :
  {
    // determine which key range comes into question, taking selection tolerance around pos into account:
    // 어떤 키 범위가 문제가되는지 판단하고 pos 주위의 선택 공차를 고려합니다.
    double posKeyMin, posKeyMax, dummy;
    pixelsToCoords(pos-QPointF(mParentPlot->selectionTolerance(), mParentPlot->selectionTolerance()), posKeyMin, dummy);
    pixelsToCoords(pos+QPointF(mParentPlot->selectionTolerance(), mParentPlot->selectionTolerance()), posKeyMax, dummy);
    if (posKeyMin > posKeyMax)
      qSwap(posKeyMin, posKeyMax);
    begin = mDataContainer->findBegin(posKeyMin, true);
    end = mDataContainer->findEnd(posKeyMax, true);
  }
  if (begin == end)
    return -1;
  QCPRange keyRange(mKeyAxis->range());
  QCPRange valueRange(mValueAxis->range());
  for (typename QCPDataContainer<DataType>::const_iterator it=begin; it!=end; ++it)
  {
    const double mainKey = it->mainKey();
    const double mainValue = it->mainValue();
    if (keyRange.contains(mainKey) && valueRange.contains(mainValue)) // make sure data point is inside visible range, for speedup in cases where sort key isn't main key and we iterate over all points
 // 데이터 포인트가 가시 범위 안에 있는지 확인하십시오. 정렬 키가 메인 키가 아닌 경우 속도를 높이고 모든 포인트를 반복합니다.
    {
      const double currentDistSqr = QCPVector2D(coordsToPixels(mainKey, mainValue)-pos).lengthSquared();
      if (currentDistSqr < minDistSqr)
      {
        minDistSqr = currentDistSqr;
        minDistIndex = it-mDataContainer->constBegin();
      }
    }
  }
  if (minDistIndex != mDataContainer->size())
    selectionResult.addDataRange(QCPDataRange(minDistIndex, minDistIndex+1), false);
  
  selectionResult.simplify();
  if (details)
    details->setValue(selectionResult);
  return qSqrt(minDistSqr);
}

/*!
  Splits all data into selected and unselected segments and outputs them via \a selectedSegments
  and \a unselectedSegments, respectively.

  This is useful when subclasses implement their \ref draw method and need to draw selected
  segments with a different pen/brush than unselected segments (also see \ref
  QCPSelectionDecorator).

  \see setSelection
*/
/* !
  모든 데이터를 선택된 세그먼트와 선택되지 않은 세그먼트로 분할하고 \ selectedSegments를 통해 출력합니다.
  및 \ a는 각각 unselectedSegments입니다.
  서브 클래스가 \ ref draw 메소드를 구현해, 선택된 것을 묘화 할 필요가있는 경우에 유용합니다.
  선택되지 않은 세그먼트와 다른 펜 / 브러쉬로 된 세그먼트 (\ ref
  QCPSelectionDecorator).
  \ see setSelection
*/
template <class DataType>
void QCPAbstractPlottable1D<DataType>::getDataSegments(QList<QCPDataRange> &selectedSegments, QList<QCPDataRange> &unselectedSegments) const
{
  selectedSegments.clear();
  unselectedSegments.clear();
  if (mSelectable == QCP::stWhole) // stWhole selection type draws the entire plottable with selected style if mSelection isn't empty
// stWhole 선택 유형은 mSelection이 비어 있지 않은 경우 선택한 스타일로 전체 플롯을 그립니다.

  {
    if (selected())
      selectedSegments << QCPDataRange(0, dataCount());
    else
      unselectedSegments << QCPDataRange(0, dataCount());
  } else
  {
    QCPDataSelection sel(selection());
    sel.simplify();
    selectedSegments = sel.dataRanges();
    unselectedSegments = sel.inverse(QCPDataRange(0, dataCount())).dataRanges();
  }
}

/*!
  A helper method which draws a line with the passed \a painter, according to the pixel data in \a
  lineData. NaN points create gaps in the line, as expected from QCustomPlot's plottables (this is
  the main difference to QPainter's regular drawPolyline, which handles NaNs by lagging or
  crashing).

  Further it uses a faster line drawing technique based on \ref QCPPainter::drawLine rather than \c
  QPainter::drawPolyline if the configured \ref QCustomPlot::setPlottingHints() and \a painter
  style allows.
*/
/* !
  \ a의 픽셀 데이터에 따라 전달 된 \ painter와 함께 선을 그려주는 도우미 메서드입니다.
  lineData. NaN 점은 QCustomPlot의 플롯 테이블에서 예상 한대로 라인에 틈을 만듭니다 (이것은
  QPainter의 정규 drawPolyline과의 주요 차이점은 지연 또는 지연으로 NaN을 처리하는 것입니다.
  충돌).
  또한 \ c보다 \ ref QCPPainter :: drawLine을 기반으로하는보다 빠른 선 그리기 기술을 사용합니다.
  QPainter :: drawPolyline 구성된 \ ref QCustomPlot :: setPlottingHints () 및 \ painter가있는 경우
  스타일을 허용합니다.
*/
template <class DataType>
void QCPAbstractPlottable1D<DataType>::drawPolyline(QCPPainter *painter, const QVector<QPointF> &lineData) const
{
  // if drawing solid line and not in PDF, use much faster line drawing instead of polyline:
  // PDF가 아닌 실선을 그리는 경우 폴리 라인 대신 훨씬 더 빠른 선 그리기를 사용하십시오.
  if (mParentPlot->plottingHints().testFlag(QCP::phFastPolylines) &&
      painter->pen().style() == Qt::SolidLine &&
      !painter->modes().testFlag(QCPPainter::pmVectorized) &&
      !painter->modes().testFlag(QCPPainter::pmNoCaching))
  {
    int i = 0;
    bool lastIsNan = false;
    const int lineDataSize = lineData.size();
    while (i < lineDataSize && (qIsNaN(lineData.at(i).y()) || qIsNaN(lineData.at(i).x())))
   // make sure first point is not NaN
   // 반드시 제 포인트 NaN이 확인되지
      ++i;
    ++i; // because drawing works in 1 point retrospect
         // 드로잉은 1 포인트의 회고에서 작동하기 때문에
    while (i < lineDataSize)
    {
      if (!qIsNaN(lineData.at(i).y()) && !qIsNaN(lineData.at(i).x())) // NaNs create a gap in the line
                                                                      // NaN이이 광고에 간극을 만들
      {
        if (!lastIsNan)
          painter->drawLine(lineData.at(i-1), lineData.at(i));
        else
          lastIsNan = false;
      } else
        lastIsNan = true;
      ++i;
    }
  } else
  {
    int segmentStart = 0;
    int i = 0;
    const int lineDataSize = lineData.size();
    while (i < lineDataSize)
    {
      if (qIsNaN(lineData.at(i).y()) || qIsNaN(lineData.at(i).x()) || qIsInf(lineData.at(i).y()))
    // NaNs create a gap in the line. Also filter Infs which make drawPolyline block
    // NaN을 만들 줄의 틈새. 또한 drawPolyline 블록을 만드는 Infs를 필터링합니다.
      {
        painter->drawPolyline(lineData.constData()+segmentStart, i-segmentStart);
    // i, because we don't want to include the current NaN point
    // i, 현재의 NaN 포인트를 포함하고 싶지 않기 때문에
        segmentStart = i+1;
      }
      ++i;
    }
    // draw last segment:
    // 마지막 세그먼트를 그립니다.
    painter->drawPolyline(lineData.constData()+segmentStart, lineDataSize-segmentStart);
  }
}
/* end of 'src/plottable1d.cpp' */


/* end of 'src/plottable1d.h' */


/* including file 'src/colorgradient.h', size 6243                           */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottable1d.cpp'의 끝 */


/* 'src / plottable1d.h'의 끝 */


/* 파일 'src / colorgradient.h'포함, 크기 6243                              */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPColorGradient
{
  Q_GADGET
public:
  /*!
    Defines the color spaces in which color interpolation between gradient stops can be performed.
    
    \see setColorInterpolation
  */
/* !
    그라디언트 정지 사이의 색상 보간을 수행 할 수있는 색상 공간을 정의합니다.
    
    \ setColorInterpolation 참조
  */
  enum ColorInterpolation { ciRGB  ///< Color channels red, green and blue are linearly interpolated
                                   /// <빨강, 녹색 및 파랑 색 채널이 선형 보간됩니다.
                            ,ciHSV ///< Color channels hue, saturation and value are linearly interpolated (The hue is interpolated over the shortest angle distance)
/// <색상 채널 색조, 채도 및 값이 선형 보간됩니다 (색조가 가장 짧은 각도 거리에 보간됩니다)
                          };
  Q_ENUMS(ColorInterpolation)
  
  /*!
    Defines the available presets that can be loaded with \ref loadPreset. See the documentation
    there for an image of the presets.
  */
 /* !
    \ ref loadPreset을 사용하여로드 할 수있는 사용 가능한 사전 설정을 정의합니다. 설명서보기
    프리셋 이미지가 있습니다.
  */
  enum GradientPreset { gpGrayscale  ///< Continuous lightness from black to white (suited for non-biased data representation)
/// <검정색에서 흰색으로 연속 밝기 (비 바이어스 데이터 표현에 적합)
                        ,gpHot       ///< Continuous lightness from black over firey colors to white (suited for non-biased data representation)
/// < 불투명 한 색상에서 검정색으로의 연속 밝기 (비 편향적인 데이터 표현에 적합)
                        ,gpCold      ///< Continuous lightness from black over icey colors to white (suited for non-biased data representation)
/// <얼음색에서 검정색까지의 연속 밝기 (비 편향적 인 데이터 표현에 적합)
                        ,gpNight     ///< Continuous lightness from black over weak blueish colors to white (suited for non-biased data representation)
/// <약한 청색 이상의 검정색에서 흰색까지의 연속 밝기 (비 편향된 데이터 표현에 적합)
                        ,gpCandy     ///< Blue over pink to white
                                     /// <핑크색에서 흰색으로 파랑
                        ,gpGeography ///< Colors suitable to represent different elevations on geographical maps
                                     /// <지리지도에서 다른 고도를 나타내는 데 적합한 색상
                        ,gpIon       ///< Half hue spectrum from black over purple to blue and finally green (creates banding illusion but allows more precise magnitude estimates)
/// <보라색에서 파란색, 그리고 마지막으로 초록색의 반 색조 스펙트럼 (밴딩 환상을 생성하지만보다 정확한 크기 추정을 가능하게 함)
                        ,gpThermal   ///< Colors suitable for thermal imaging, ranging from dark blue over purple to orange, yellow and white
/// <열 이미징에 적합한 색상으로 진한 파란색에서 자주색, 주황색, 노란색 및 흰색에 이르기까지 다양합니다.
                        ,gpPolar     ///< Colors suitable to emphasize polarity around the center, with blue for negative, black in the middle and red for positive values
/// <중앙 부근에서 극성을 강조하는 데 적합한 색상으로, 파란색은 음수, 검정색은 중간, 빨간색은 양수 값
                        ,gpSpectrum  ///< An approximation of the visible light spectrum (creates banding illusion but allows more precise magnitude estimates)
/// <가시 광선 스펙트럼의 근사 (banding illusion을 만들지 만보다   정확한 크기 추정을 가능하게 함)
                        ,gpJet       ///< Hue variation similar to a spectrum, often used in numerical visualization (creates banding illusion but allows more precise magnitude estimates)
/// <스펙트럼과 유사한 색조 변화, 종종 수치 시각화에 사용됨 (밴딩 환상을 생성하지만보다 정확한 크기 추정을 가능하게 함)
                        ,gpHues      ///< Full hue cycle, with highest and lowest color red (suitable for periodic data, such as angles and phases, see \ref setPeriodic)
/// <가장 높은 색과 가장 낮은 색을 가진 전체 색상주기 (각도와 위상과 같은주기적인 데이터에 적합, \ ref setPeriodic 참조)
                      };
  Q_ENUMS(GradientPreset)
  
  QCPColorGradient();
  QCPColorGradient(GradientPreset preset);
  bool operator==(const QCPColorGradient &other) const;
  bool operator!=(const QCPColorGradient &other) const { return !(*this == other); }
  
  // getters:
  int levelCount() const { return mLevelCount; }
  QMap<double, QColor> colorStops() const { return mColorStops; }
  ColorInterpolation colorInterpolation() const { return mColorInterpolation; }
  bool periodic() const { return mPeriodic; }
  
  // setters:
  void setLevelCount(int n);
  void setColorStops(const QMap<double, QColor> &colorStops);
  void setColorStopAt(double position, const QColor &color);
  void setColorInterpolation(ColorInterpolation interpolation);
  void setPeriodic(bool enabled);
  
  // non-property methods:
  // 비 속성 메소드 :
  void colorize(const double *data, const QCPRange &range, QRgb *scanLine, int n, int dataIndexFactor=1, bool logarithmic=false);
  void colorize(const double *data, const unsigned char *alpha, const QCPRange &range, QRgb *scanLine, int n, int dataIndexFactor=1, bool logarithmic=false);
  QRgb color(double position, const QCPRange &range, bool logarithmic=false);
  void loadPreset(GradientPreset preset);
  void clearColorStops();
  QCPColorGradient inverted() const;
  
protected:
  // property members:
  // 속성 멤버 :
  int mLevelCount;
  QMap<double, QColor> mColorStops;
  ColorInterpolation mColorInterpolation;
  bool mPeriodic;
  
  // non-property members:
  // 비 속성 멤버 :
  QVector<QRgb> mColorBuffer; // have colors premultiplied with alpha (for usage with QImage::Format_ARGB32_Premultiplied)
  // 알파로 미리 곱한 색상을 가짐 (QImage :: Format_ARGB32_Premultiplied 사용)
  bool mColorBufferInvalidated;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  bool stopsUseAlpha() const;
  void updateColorBuffer();
};
Q_DECLARE_METATYPE(QCPColorGradient::ColorInterpolation)
Q_DECLARE_METATYPE(QCPColorGradient::GradientPreset)

/* end of 'src/colorgradient.h' */


/* including file 'src/selectiondecorator-bracket.h', size 4442              */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / colorgradient.h'의 끝 */


/* 파일 'src / selectiondecorator-bracket.h', 크기 4442 포함               */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */


class QCP_LIB_DECL QCPSelectionDecoratorBracket : public QCPSelectionDecorator
{
  Q_GADGET
public:
  
  /*!
    Defines which shape is drawn at the boundaries of selected data ranges.
    
    Some of the bracket styles further allow specifying a height and/or width, see \ref
    setBracketHeight and \ref setBracketWidth.
  */
 /* !
    선택한 데이터 범위의 경계에서 그려지는 모양을 정의합니다.
    
    브래킷 스타일 중 일부는 높이 및 / 또는 너비를 지정할 수 있습니다. \ ref를 참조하십시오.
    setBracketHeight 및 \ ref setBracketWidth입니다.
  */
  enum BracketStyle { bsSquareBracket ///< A square bracket is drawn.
                                      /// <대괄호가 그려집니다.
                      ,bsHalfEllipse   ///< A half ellipse is drawn. The size of the ellipse is given by the bracket width/height properties.
/// <반 타원이 그려집니다. 타원의 크기는 브래킷의 너비 / 높이 속성으로 지정됩니다.
                      ,bsEllipse       ///< An ellipse is drawn. The size of the ellipse is given by the bracket width/height properties.
/// <타원이 그려집니다. 타원의 크기는 브래킷의 너비 / 높이 속성으로 지정됩니다.
                      ,bsPlus         ///< A plus is drawn.
/// <더하기가 그려집니다.
                      ,bsUserStyle    ///< Start custom bracket styles at this index when subclassing and reimplementing \ref drawBracket.
/// <\ ref drawBracket를 하위 클래스 화하고 다시 구현할 때이 인덱스에서 사용자 정의 괄호 스타일을 시작합니다

  };
  Q_ENUMS(BracketStyle)
  
  QCPSelectionDecoratorBracket();
  virtual ~QCPSelectionDecoratorBracket();
  
  // getters:
  QPen bracketPen() const { return mBracketPen; }
  QBrush bracketBrush() const { return mBracketBrush; }
  int bracketWidth() const { return mBracketWidth; }
  int bracketHeight() const { return mBracketHeight; }
  BracketStyle bracketStyle() const { return mBracketStyle; }
  bool tangentToData() const { return mTangentToData; }
  int tangentAverage() const { return mTangentAverage; }
  
  // setters:
  void setBracketPen(const QPen &pen);
  void setBracketBrush(const QBrush &brush);
  void setBracketWidth(int width);
  void setBracketHeight(int height);
  void setBracketStyle(BracketStyle style);
  void setTangentToData(bool enabled);
  void setTangentAverage(int pointCount);
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void drawBracket(QCPPainter *painter, int direction) const;
  
  // virtual methods:
  // 가상 메소드 :
  virtual void drawDecoration(QCPPainter *painter, QCPDataSelection selection) Q_DECL_OVERRIDE;
  
protected:
  // property members:
  // 속성 멤버 :
  QPen mBracketPen;
  QBrush mBracketBrush;
  int mBracketWidth;
  int mBracketHeight;
  BracketStyle mBracketStyle;
  bool mTangentToData;
  int mTangentAverage;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  double getTangentAngle(const QCPPlottableInterface1D *interface1d, int dataIndex, int direction) const;
  QPointF getPixelCoordinates(const QCPPlottableInterface1D *interface1d, int dataIndex) const;
  
};
Q_DECLARE_METATYPE(QCPSelectionDecoratorBracket::BracketStyle)

/* end of 'src/selectiondecorator-bracket.h' */


/* including file 'src/layoutelements/layoutelement-axisrect.h', size 7507   */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / selectiondecorator-bracket.h'의 끝 */


/* 'src / layoutelements / layoutelement-axisrect.h'파일을 포함하여 크기 7507*/
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */


class QCP_LIB_DECL QCPAxisRect : public QCPLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPixmap background READ background WRITE setBackground)
  Q_PROPERTY(bool backgroundScaled READ backgroundScaled WRITE setBackgroundScaled)
  Q_PROPERTY(Qt::AspectRatioMode backgroundScaledMode READ backgroundScaledMode WRITE setBackgroundScaledMode)
  Q_PROPERTY(Qt::Orientations rangeDrag READ rangeDrag WRITE setRangeDrag)
  Q_PROPERTY(Qt::Orientations rangeZoom READ rangeZoom WRITE setRangeZoom)
  /// \endcond
public:
  explicit QCPAxisRect(QCustomPlot *parentPlot, bool setupDefaultAxes=true);
  virtual ~QCPAxisRect();
  
  // getters:
  QPixmap background() const { return mBackgroundPixmap; }
  QBrush backgroundBrush() const { return mBackgroundBrush; }
  bool backgroundScaled() const { return mBackgroundScaled; }
  Qt::AspectRatioMode backgroundScaledMode() const { return mBackgroundScaledMode; }
  Qt::Orientations rangeDrag() const { return mRangeDrag; }
  Qt::Orientations rangeZoom() const { return mRangeZoom; }
  QCPAxis *rangeDragAxis(Qt::Orientation orientation);
  QCPAxis *rangeZoomAxis(Qt::Orientation orientation);
  QList<QCPAxis*> rangeDragAxes(Qt::Orientation orientation);
  QList<QCPAxis*> rangeZoomAxes(Qt::Orientation orientation);
  double rangeZoomFactor(Qt::Orientation orientation);
  
  // setters:
  void setBackground(const QPixmap &pm);
  void setBackground(const QPixmap &pm, bool scaled, Qt::AspectRatioMode mode=Qt::KeepAspectRatioByExpanding);
  void setBackground(const QBrush &brush);
  void setBackgroundScaled(bool scaled);
  void setBackgroundScaledMode(Qt::AspectRatioMode mode);
  void setRangeDrag(Qt::Orientations orientations);
  void setRangeZoom(Qt::Orientations orientations);
  void setRangeDragAxes(QCPAxis *horizontal, QCPAxis *vertical);
  void setRangeDragAxes(QList<QCPAxis*> axes);
  void setRangeDragAxes(QList<QCPAxis*> horizontal, QList<QCPAxis*> vertical);
  void setRangeZoomAxes(QCPAxis *horizontal, QCPAxis *vertical);
  void setRangeZoomAxes(QList<QCPAxis*> axes);
  void setRangeZoomAxes(QList<QCPAxis*> horizontal, QList<QCPAxis*> vertical);
  void setRangeZoomFactor(double horizontalFactor, double verticalFactor);
  void setRangeZoomFactor(double factor);
  
  // non-property methods:
  // 비 속성 메소드 :
  int axisCount(QCPAxis::AxisType type) const;
  QCPAxis *axis(QCPAxis::AxisType type, int index=0) const;
  QList<QCPAxis*> axes(QCPAxis::AxisTypes types) const;
  QList<QCPAxis*> axes() const;
  QCPAxis *addAxis(QCPAxis::AxisType type, QCPAxis *axis=0);
  QList<QCPAxis*> addAxes(QCPAxis::AxisTypes types);
  bool removeAxis(QCPAxis *axis);
  QCPLayoutInset *insetLayout() const { return mInsetLayout; }
  
  void zoom(const QRectF &pixelRect);
  void zoom(const QRectF &pixelRect, const QList<QCPAxis*> &affectedAxes);
  void setupFullAxesBox(bool connectRanges=false);
  QList<QCPAbstractPlottable*> plottables() const;
  QList<QCPGraph*> graphs() const;
  QList<QCPAbstractItem*> items() const;
  
  // read-only interface imitating a QRect:
  // QRect를 모방 한 읽기 전용 인터페이스 :
  int left() const { return mRect.left(); }
  int right() const { return mRect.right(); }
  int top() const { return mRect.top(); }
  int bottom() const { return mRect.bottom(); }
  int width() const { return mRect.width(); }
  int height() const { return mRect.height(); }
  QSize size() const { return mRect.size(); }
  QPoint topLeft() const { return mRect.topLeft(); }
  QPoint topRight() const { return mRect.topRight(); }
  QPoint bottomLeft() const { return mRect.bottomLeft(); }
  QPoint bottomRight() const { return mRect.bottomRight(); }
  QPoint center() const { return mRect.center(); }
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  virtual QList<QCPLayoutElement*> elements(bool recursive) const Q_DECL_OVERRIDE;

protected:
  // property members:
  // 속성 멤버 :
  QBrush mBackgroundBrush;
  QPixmap mBackgroundPixmap;
  QPixmap mScaledBackgroundPixmap;
  bool mBackgroundScaled;
  Qt::AspectRatioMode mBackgroundScaledMode;
  QCPLayoutInset *mInsetLayout;
  Qt::Orientations mRangeDrag, mRangeZoom;
  QList<QPointer<QCPAxis> > mRangeDragHorzAxis, mRangeDragVertAxis;
  QList<QPointer<QCPAxis> > mRangeZoomHorzAxis, mRangeZoomVertAxis;
  double mRangeZoomFactorHorz, mRangeZoomFactorVert;
  
  // non-property members:
  // 비 속성 멤버 :
  QList<QCPRange> mDragStartHorzRange, mDragStartVertRange;
  QCP::AntialiasedElements mAADragBackup, mNotAADragBackup;
  bool mDragging;
  QHash<QCPAxis::AxisType, QList<QCPAxis*> > mAxes;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual int calculateAutoMargin(QCP::MarginSide side) Q_DECL_OVERRIDE;
  virtual void layoutChanged() Q_DECL_OVERRIDE;
  // events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
  // non-property methods:
  // 비 속성 메소드 :
  void drawBackground(QCPPainter *painter);
  void updateAxesOffset(QCPAxis::AxisType type);
  
private:
  Q_DISABLE_COPY(QCPAxisRect)
  
  friend class QCustomPlot;
};


/* end of 'src/layoutelements/layoutelement-axisrect.h' */


/* including file 'src/layoutelements/layoutelement-legend.h', size 10397    */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / layoutelements / layoutelement-axisrect.h'의 끝 */


/* 'src / layoutelements / layoutelement-legend.h'파일을 포함하여 크기 10397 */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPAbstractLegendItem : public QCPLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QCPLegend* parentLegend READ parentLegend)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
  Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectionChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectableChanged)
  /// \endcond
public:
  explicit QCPAbstractLegendItem(QCPLegend *parent);
  
  // getters:
  QCPLegend *parentLegend() const { return mParentLegend; }
  QFont font() const { return mFont; }
  QColor textColor() const { return mTextColor; }
  QFont selectedFont() const { return mSelectedFont; }
  QColor selectedTextColor() const { return mSelectedTextColor; }
  bool selectable() const { return mSelectable; }
  bool selected() const { return mSelected; }
  
  // setters:
  void setFont(const QFont &font);
  void setTextColor(const QColor &color);
  void setSelectedFont(const QFont &font);
  void setSelectedTextColor(const QColor &color);
  Q_SLOT void setSelectable(bool selectable);
  Q_SLOT void setSelected(bool selected);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
signals:
  void selectionChanged(bool selected);
  void selectableChanged(bool selectable);
  
protected:
  // property members:
  // 속성 멤버 :
  QCPLegend *mParentLegend;
  QFont mFont;
  QColor mTextColor;
  QFont mSelectedFont;
  QColor mSelectedTextColor;
  bool mSelectable, mSelected;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCP::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual QRect clipRect() const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE = 0;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
private:
  Q_DISABLE_COPY(QCPAbstractLegendItem)
  
  friend class QCPLegend;
};


class QCP_LIB_DECL QCPPlottableLegendItem : public QCPAbstractLegendItem
{
  Q_OBJECT
public:
  QCPPlottableLegendItem(QCPLegend *parent, QCPAbstractPlottable *plottable);
  
  // getters:
  QCPAbstractPlottable *plottable() { return mPlottable; }
  
protected:
  // property members:
  // 속성 멤버 :
  QCPAbstractPlottable *mPlottable;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPen getIconBorderPen() const;
  QColor getTextColor() const;
  QFont getFont() const;
};


class QCP_LIB_DECL QCPLegend : public QCPLayoutGrid
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen borderPen READ borderPen WRITE setBorderPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
  Q_PROPERTY(int iconTextPadding READ iconTextPadding WRITE setIconTextPadding)
  Q_PROPERTY(QPen iconBorderPen READ iconBorderPen WRITE setIconBorderPen)
  Q_PROPERTY(SelectableParts selectableParts READ selectableParts WRITE setSelectableParts NOTIFY selectionChanged)
  Q_PROPERTY(SelectableParts selectedParts READ selectedParts WRITE setSelectedParts NOTIFY selectableChanged)
  Q_PROPERTY(QPen selectedBorderPen READ selectedBorderPen WRITE setSelectedBorderPen)
  Q_PROPERTY(QPen selectedIconBorderPen READ selectedIconBorderPen WRITE setSelectedIconBorderPen)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
  /// \endcond
public:
  /*!
    Defines the selectable parts of a legend
    
    \see setSelectedParts, setSelectableParts
  */
 /* !
    범례의 선택 가능한 부분을 정의합니다.
    
    \ setSelectedParts, setSelectableParts를 참조하십시오.
  */
  enum SelectablePart { spNone        = 0x000 ///< <tt>0x000</tt> None
                                              /// < 0x0000 > </ tt> 없음
                        ,spLegendBox  = 0x001 ///< <tt>0x001</tt> The legend box (frame)
                                              /// <tt> 0x001 </ tt> 범례 상자 (프레임)
                        ,spItems      = 0x002 ///< <tt>0x002</tt> Legend items individually (see \ref selectedItems)
/// <tt> 0x002 </ tt> 범례 항목 개별적으로 (\ ref selectedItems 참조)
                      };
  Q_ENUMS(SelectablePart)
  Q_FLAGS(SelectableParts)
  Q_DECLARE_FLAGS(SelectableParts, SelectablePart)
  
  explicit QCPLegend();
  virtual ~QCPLegend();
  
  // getters:
  QPen borderPen() const { return mBorderPen; }
  QBrush brush() const { return mBrush; }
  QFont font() const { return mFont; }
  QColor textColor() const { return mTextColor; }
  QSize iconSize() const { return mIconSize; }
  int iconTextPadding() const { return mIconTextPadding; }
  QPen iconBorderPen() const { return mIconBorderPen; }
  SelectableParts selectableParts() const { return mSelectableParts; }
  SelectableParts selectedParts() const;
  QPen selectedBorderPen() const { return mSelectedBorderPen; }
  QPen selectedIconBorderPen() const { return mSelectedIconBorderPen; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  QFont selectedFont() const { return mSelectedFont; }
  QColor selectedTextColor() const { return mSelectedTextColor; }
  
  // setters:
  void setBorderPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setFont(const QFont &font);
  void setTextColor(const QColor &color);
  void setIconSize(const QSize &size);
  void setIconSize(int width, int height);
  void setIconTextPadding(int padding);
  void setIconBorderPen(const QPen &pen);
  Q_SLOT void setSelectableParts(const SelectableParts &selectableParts);
  Q_SLOT void setSelectedParts(const SelectableParts &selectedParts);
  void setSelectedBorderPen(const QPen &pen);
  void setSelectedIconBorderPen(const QPen &pen);
  void setSelectedBrush(const QBrush &brush);
  void setSelectedFont(const QFont &font);
  void setSelectedTextColor(const QColor &color);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QCPAbstractLegendItem *item(int index) const;
  QCPPlottableLegendItem *itemWithPlottable(const QCPAbstractPlottable *plottable) const;
  int itemCount() const;
  bool hasItem(QCPAbstractLegendItem *item) const;
  bool hasItemWithPlottable(const QCPAbstractPlottable *plottable) const;
  bool addItem(QCPAbstractLegendItem *item);
  bool removeItem(int index);
  bool removeItem(QCPAbstractLegendItem *item);
  void clearItems();
  QList<QCPAbstractLegendItem*> selectedItems() const;
  
signals:
  void selectionChanged(QCPLegend::SelectableParts parts);
  void selectableChanged(QCPLegend::SelectableParts parts);
  
protected:
  // property members:
  // 속성 멤버 :
  QPen mBorderPen, mIconBorderPen;
  QBrush mBrush;
  QFont mFont;
  QColor mTextColor;
  QSize mIconSize;
  int mIconTextPadding;
  SelectableParts mSelectedParts, mSelectableParts;
  QPen mSelectedBorderPen, mSelectedIconBorderPen;
  QBrush mSelectedBrush;
  QFont mSelectedFont;
  QColor mSelectedTextColor;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void parentPlotInitialized(QCustomPlot *parentPlot) Q_DECL_OVERRIDE;
  virtual QCP::Interaction selectionCategory() const Q_DECL_OVERRIDE;
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPen getBorderPen() const;
  QBrush getBrush() const;
  
private:
  Q_DISABLE_COPY(QCPLegend)
  
  friend class QCustomPlot;
  friend class QCPAbstractLegendItem;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QCPLegend::SelectableParts)
Q_DECLARE_METATYPE(QCPLegend::SelectablePart)

/* end of 'src/layoutelements/layoutelement-legend.h' */


/* including file 'src/layoutelements/layoutelement-textelement.h', size 5353 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200  */
/* 'src / layoutelements / layoutelement-legend.h'의 끝 */


/* 파일 'src / layoutelements / layoutelement-textelement.h'포함, 크기 5353   */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200   */

class QCP_LIB_DECL QCPTextElement : public QCPLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QString text READ text WRITE setText)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
  Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectableChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectionChanged)
  /// \endcond
public:
  explicit QCPTextElement(QCustomPlot *parentPlot);
  QCPTextElement(QCustomPlot *parentPlot, const QString &text);
  QCPTextElement(QCustomPlot *parentPlot, const QString &text, double pointSize);
  QCPTextElement(QCustomPlot *parentPlot, const QString &text, const QString &fontFamily, double pointSize);
  QCPTextElement(QCustomPlot *parentPlot, const QString &text, const QFont &font);
  
  // getters:
  QString text() const { return mText; }
  int textFlags() const { return mTextFlags; }
  QFont font() const { return mFont; }
  QColor textColor() const { return mTextColor; }
  QFont selectedFont() const { return mSelectedFont; }
  QColor selectedTextColor() const { return mSelectedTextColor; }
  bool selectable() const { return mSelectable; }
  bool selected() const { return mSelected; }
  
  // setters:
  void setText(const QString &text);
  void setTextFlags(int flags);
  void setFont(const QFont &font);
  void setTextColor(const QColor &color);
  void setSelectedFont(const QFont &font);
  void setSelectedTextColor(const QColor &color);
  Q_SLOT void setSelectable(bool selectable);
  Q_SLOT void setSelected(bool selected);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  
signals:
  void selectionChanged(bool selected);
  void selectableChanged(bool selectable);
  void clicked(QMouseEvent *event);
  void doubleClicked(QMouseEvent *event);
  
protected:
  // property members:
  // 속성 멤버 :
  QString mText;
  int mTextFlags;
  QFont mFont;
  QColor mTextColor;
  QFont mSelectedFont;
  QColor mSelectedTextColor;
  QRect mTextBoundingRect;
  bool mSelectable, mSelected;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QSize minimumOuterSizeHint() const Q_DECL_OVERRIDE;
  virtual QSize maximumOuterSizeHint() const Q_DECL_OVERRIDE;
  // events:
  virtual void selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged) Q_DECL_OVERRIDE;
  virtual void deselectEvent(bool *selectionStateChanged) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QFont mainFont() const;
  QColor mainTextColor() const;
  
private:
  Q_DISABLE_COPY(QCPTextElement)
};



/* end of 'src/layoutelements/layoutelement-textelement.h' */


/* including file 'src/layoutelements/layoutelement-colorscale.h', size 5923 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / layoutelements / layoutelement-textelement.h'의 끝 */


/* 파일 'src / layoutelements / layoutelement-colorscale.h', 크기 5923 포함 */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */


class QCPColorScaleAxisRectPrivate : public QCPAxisRect
{
  Q_OBJECT
public:
  explicit QCPColorScaleAxisRectPrivate(QCPColorScale *parentColorScale);
protected:
  QCPColorScale *mParentColorScale;
  QImage mGradientImage;
  bool mGradientImageInvalidated;
  // re-using some methods of QCPAxisRect to make them available to friend class QCPColorScale
  // QCPAxisRect의 일부 메소드를 다시 사용하여 QCPColorScale 친구 클래스에서 사용할 수 있도록합니다.
  using QCPAxisRect::calculateAutoMargin;
  using QCPAxisRect::mousePressEvent;
  using QCPAxisRect::mouseMoveEvent;
  using QCPAxisRect::mouseReleaseEvent;
  using QCPAxisRect::wheelEvent;
  using QCPAxisRect::update;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  void updateGradientImage();
  Q_SLOT void axisSelectionChanged(QCPAxis::SelectableParts selectedParts);
  Q_SLOT void axisSelectableChanged(QCPAxis::SelectableParts selectableParts);
  friend class QCPColorScale;
};


class QCP_LIB_DECL QCPColorScale : public QCPLayoutElement
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QCPAxis::AxisType type READ type WRITE setType)
  Q_PROPERTY(QCPRange dataRange READ dataRange WRITE setDataRange NOTIFY dataRangeChanged)
  Q_PROPERTY(QCPAxis::ScaleType dataScaleType READ dataScaleType WRITE setDataScaleType NOTIFY dataScaleTypeChanged)
  Q_PROPERTY(QCPColorGradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged)
  Q_PROPERTY(QString label READ label WRITE setLabel)
  Q_PROPERTY(int barWidth READ barWidth WRITE setBarWidth)
  Q_PROPERTY(bool rangeDrag READ rangeDrag WRITE setRangeDrag)
  Q_PROPERTY(bool rangeZoom READ rangeZoom WRITE setRangeZoom)
  /// \endcond
public:
  explicit QCPColorScale(QCustomPlot *parentPlot);
  virtual ~QCPColorScale();
  
  // getters:
  QCPAxis *axis() const { return mColorAxis.data(); }
  QCPAxis::AxisType type() const { return mType; }
  QCPRange dataRange() const { return mDataRange; }
  QCPAxis::ScaleType dataScaleType() const { return mDataScaleType; }
  QCPColorGradient gradient() const { return mGradient; }
  QString label() const;
  int barWidth () const { return mBarWidth; }
  bool rangeDrag() const;
  bool rangeZoom() const;
  
  // setters:
  void setType(QCPAxis::AxisType type);
  Q_SLOT void setDataRange(const QCPRange &dataRange);
  Q_SLOT void setDataScaleType(QCPAxis::ScaleType scaleType);
  Q_SLOT void setGradient(const QCPColorGradient &gradient);
  void setLabel(const QString &str);
  void setBarWidth(int width);
  void setRangeDrag(bool enabled);
  void setRangeZoom(bool enabled);
  
  // non-property methods:
  // 비 속성 메소드 :
  QList<QCPColorMap*> colorMaps() const;
  void rescaleDataRange(bool onlyVisibleMaps);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void update(UpdatePhase phase) Q_DECL_OVERRIDE;
  
signals:
  void dataRangeChanged(const QCPRange &newRange);
  void dataScaleTypeChanged(QCPAxis::ScaleType scaleType);
  void gradientChanged(const QCPColorGradient &newGradient);

protected:
  // property members:
  // 속성 멤버 :
  QCPAxis::AxisType mType;
  QCPRange mDataRange;
  QCPAxis::ScaleType mDataScaleType;
  QCPColorGradient mGradient;
  int mBarWidth;
  
  // non-property members:
  // 비 속성 멤버 :
  QPointer<QCPColorScaleAxisRectPrivate> mAxisRect;
  QPointer<QCPAxis> mColorAxis;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const Q_DECL_OVERRIDE;
  // events:
  virtual void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  
private:
  Q_DISABLE_COPY(QCPColorScale)
  
  friend class QCPColorScaleAxisRectPrivate;
};


/* end of 'src/layoutelements/layoutelement-colorscale.h' */


/* including file 'src/plottables/plottable-graph.h', size 9294              */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / layoutelements / layoutelement-colorscale.h'의 끝 */


/* 'src / plottables / plottable-graph.h'파일 포함, 크기 9294               */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPGraphData
{
public:
  QCPGraphData();
  QCPGraphData(double key, double value);
  
  inline double sortKey() const { return key; }
  inline static QCPGraphData fromSortKey(double sortKey) { return QCPGraphData(sortKey, 0); }
  inline static bool sortKeyIsMainKey() { return true; }
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return value; }
  
  inline QCPRange valueRange() const { return QCPRange(value, value); }
  
  double key, value;
};
Q_DECLARE_TYPEINFO(QCPGraphData, Q_PRIMITIVE_TYPE);


/*! \typedef QCPGraphDataContainer
  
  Container for storing \ref QCPGraphData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which QCPGraph holds its data. For details about
  the generic container, see the documentation of the class template \ref QCPDataContainer.
  
  \see QCPGraphData, QCPGraph::setData
*/
/* ! \ typedef QCPGraphDataContainer
  
  \ ref QCPGraphData 포인트를 저장하기위한 컨테이너. 데이터는 키로 정렬되어 저장됩니다.
  
  이 템플릿 인스턴스화는 QCPGraph가 데이터를 보유하고있는 컨테이너입니다. 자세한 내용은
  제네릭 컨테이너에 대해서는 클래스 템플릿 \ ref QCPDataContainer의 설명서를 참조하십시오.
  
  \ QCPGraphData, QCPGraph :: setData를 참조하십시오.
*/
typedef QCPDataContainer<QCPGraphData> QCPGraphDataContainer;

class QCP_LIB_DECL QCPGraph : public QCPAbstractPlottable1D<QCPGraphData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(LineStyle lineStyle READ lineStyle WRITE setLineStyle)
  Q_PROPERTY(QCPScatterStyle scatterStyle READ scatterStyle WRITE setScatterStyle)
  Q_PROPERTY(int scatterSkip READ scatterSkip WRITE setScatterSkip)
  Q_PROPERTY(QCPGraph* channelFillGraph READ channelFillGraph WRITE setChannelFillGraph)
  Q_PROPERTY(bool adaptiveSampling READ adaptiveSampling WRITE setAdaptiveSampling)
  /// \endcond
public:
  /*!
    Defines how the graph's line is represented visually in the plot. The line is drawn with the
    current pen of the graph (\ref setPen).
    \see setLineStyle
  */
 /* !
    플롯에서 그래프의 선이 시각적으로 어떻게 표시되는지 정의합니다. 선은
    그래프의 현재 펜 (\ ref setPen).
    \ setLineStyle 참조
  */
  enum LineStyle { lsNone        ///< data points are not connected with any lines (e.g. data only represented
/// <데이터 포인트가 어떤 라인과도 연결되지 않았습니다 (예 : 데이터 만 표현됨).
                                 ///< with symbols according to the scatter style, see \ref setScatterStyle)
/// <스 캐터 스타일에 따른 기호로, \ ref setScatterStyle 참조)
                   ,lsLine       ///< data points are connected by a straight line
/// <데이터 점은 직선으로 연결됩니다.
                   ,lsStepLeft   ///< line is drawn as steps where the step height is the value of the left data point
/// <선은 단계 높이가 왼쪽 데이터 요소의 값 인 단계로 그려집니다
                   ,lsStepRight  ///< line is drawn as steps where the step height is the value of the right data point
/// <선은 단계 높이가 오른쪽 데이터 요소의 값 인 단계로 그려집니다
                   ,lsStepCenter ///< line is drawn as steps where the step is in between two data points
/// <선은 단계가 두 데이터 점 사이에있는 단계로 그려집니다
                   ,lsImpulse    ///< each data point is represented by a line parallel to the value axis, which reaches from the data point to the zero-value-line
/// <각 데이터 점은 데이터 축에서 0 값 행까지 도달하는 값 축과 평행 한 선으로 표시됩니다
                 };
  Q_ENUMS(LineStyle)
  
  explicit QCPGraph(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPGraph();
  
  // getters:
  QSharedPointer<QCPGraphDataContainer> data() const { return mDataContainer; }
  LineStyle lineStyle() const { return mLineStyle; }
  QCPScatterStyle scatterStyle() const { return mScatterStyle; }
  int scatterSkip() const { return mScatterSkip; }
  QCPGraph *channelFillGraph() const { return mChannelFillGraph.data(); }
  bool adaptiveSampling() const { return mAdaptiveSampling; }
  
  // setters:
  void setData(QSharedPointer<QCPGraphDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setLineStyle(LineStyle ls);
  void setScatterStyle(const QCPScatterStyle &style);
  void setScatterSkip(int skip);
  void setChannelFillGraph(QCPGraph *targetGraph);
  void setAdaptiveSampling(bool enabled);
  
  // non-property methods:
  // 비 속성 메소드 :
  void addData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(double key, double value);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  // 속성 멤버 :
  LineStyle mLineStyle;
  QCPScatterStyle mScatterStyle;
  int mScatterSkip;
  QPointer<QCPGraph> mChannelFillGraph;
  bool mAdaptiveSampling;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void drawFill(QCPPainter *painter, QVector<QPointF> *lines) const;
  virtual void drawScatterPlot(QCPPainter *painter, const QVector<QPointF> &scatters, const QCPScatterStyle &style) const;
  virtual void drawLinePlot(QCPPainter *painter, const QVector<QPointF> &lines) const;
  virtual void drawImpulsePlot(QCPPainter *painter, const QVector<QPointF> &lines) const;
  
  virtual void getOptimizedLineData(QVector<QCPGraphData> *lineData, const QCPGraphDataContainer::const_iterator &begin, const QCPGraphDataContainer::const_iterator &end) const;
  virtual void getOptimizedScatterData(QVector<QCPGraphData> *scatterData, QCPGraphDataContainer::const_iterator begin, QCPGraphDataContainer::const_iterator end) const;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void getVisibleDataBounds(QCPGraphDataContainer::const_iterator &begin, QCPGraphDataContainer::const_iterator &end, const QCPDataRange &rangeRestriction) const;
  void getLines(QVector<QPointF> *lines, const QCPDataRange &dataRange) const;
  void getScatters(QVector<QPointF> *scatters, const QCPDataRange &dataRange) const;
  QVector<QPointF> dataToLines(const QVector<QCPGraphData> &data) const;
  QVector<QPointF> dataToStepLeftLines(const QVector<QCPGraphData> &data) const;
  QVector<QPointF> dataToStepRightLines(const QVector<QCPGraphData> &data) const;
  QVector<QPointF> dataToStepCenterLines(const QVector<QCPGraphData> &data) const;
  QVector<QPointF> dataToImpulseLines(const QVector<QCPGraphData> &data) const;
  QVector<QCPDataRange> getNonNanSegments(const QVector<QPointF> *lineData, Qt::Orientation keyOrientation) const;
  QVector<QPair<QCPDataRange, QCPDataRange> > getOverlappingSegments(QVector<QCPDataRange> thisSegments, const QVector<QPointF> *thisData, QVector<QCPDataRange> otherSegments, const QVector<QPointF> *otherData) const;
  bool segmentsIntersect(double aLower, double aUpper, double bLower, double bUpper, int &bPrecedence) const;
  QPointF getFillBasePoint(QPointF matchingDataPoint) const;
  const QPolygonF getFillPolygon(const QVector<QPointF> *lineData, QCPDataRange segment) const;
  const QPolygonF getChannelFillPolygon(const QVector<QPointF> *lineData, QCPDataRange thisSegment, const QVector<QPointF> *otherData, QCPDataRange otherSegment) const;
  int findIndexBelowX(const QVector<QPointF> *data, double x) const;
  int findIndexAboveX(const QVector<QPointF> *data, double x) const;
  int findIndexBelowY(const QVector<QPointF> *data, double y) const;
  int findIndexAboveY(const QVector<QPointF> *data, double y) const;
  double pointDistance(const QPointF &pixelPoint, QCPGraphDataContainer::const_iterator &closestData) const;
  
  friend class QCustomPlot;
  friend class QCPLegend;
};
Q_DECLARE_METATYPE(QCPGraph::LineStyle)

/* end of 'src/plottables/plottable-graph.h' */


/* including file 'src/plottables/plottable-curve.h', size 7409              */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

/* 'src / plottables / plottable-graph.h'의 끝 */


/* 파일 'src / plottables / plottable-curve.h'포함, 크기 7409               */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPCurveData
{
public:
  QCPCurveData();
  QCPCurveData(double t, double key, double value);
  
  inline double sortKey() const { return t; }
  inline static QCPCurveData fromSortKey(double sortKey) { return QCPCurveData(sortKey, 0, 0); }
  inline static bool sortKeyIsMainKey() { return false; }
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return value; }
  
  inline QCPRange valueRange() const { return QCPRange(value, value); }
  
  double t, key, value;
};
Q_DECLARE_TYPEINFO(QCPCurveData, Q_PRIMITIVE_TYPE);


/*! \typedef QCPCurveDataContainer
  
  Container for storing \ref QCPCurveData points. The data is stored sorted by \a t, so the \a
  sortKey() (returning \a t) is different from \a mainKey() (returning \a key).
  
  This template instantiation is the container in which QCPCurve holds its data. For details about
  the generic container, see the documentation of the class template \ref QCPDataContainer.
  
  \see QCPCurveData, QCPCurve::setData
*/
/* ! \ typedef QCPCurveDataContainer
  
  \ ref QCPCurveData 포인트를 저장하는 컨테이너입니다. 데이터는 \ at로 정렬되어 저장되므로 \ a
  sortKey () (\ at를 반환하는)는 \ a mainKey ()와 다릅니다 (\ a 키를 반환).
  
  이 템플릿 인스턴스화는 QCPCurve가 데이터를 보유하는 컨테이너입니다. 자세한 내용은
  제네릭 컨테이너에 대해서는 클래스 템플릿 \ ref QCPDataContainer의 설명서를 참조하십시오.
  
  \ QCPCurveData, QCPCurve :: setData를 참조하십시오.
*/
typedef QCPDataContainer<QCPCurveData> QCPCurveDataContainer;

class QCP_LIB_DECL QCPCurve : public QCPAbstractPlottable1D<QCPCurveData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QCPScatterStyle scatterStyle READ scatterStyle WRITE setScatterStyle)
  Q_PROPERTY(int scatterSkip READ scatterSkip WRITE setScatterSkip)
  Q_PROPERTY(LineStyle lineStyle READ lineStyle WRITE setLineStyle)
  /// \endcond
public:
  /*!
    Defines how the curve's line is represented visually in the plot. The line is drawn with the
    current pen of the curve (\ref setPen).
    \see setLineStyle
  */
 /* !
    플롯에서 곡선의 선이 시각적으로 어떻게 표시되는지 정의합니다. 선은
    커브의 현재 펜 (\ ref setPen).
    \ setLineStyle 참조
  */
  enum LineStyle { lsNone  ///< No line is drawn between data points (e.g. only scatters)
                           /// <데이터 포인트 사이에 선이 그려지지 않습니다 (예 : 산란 만).
                   ,lsLine ///< Data points are connected with a straight line
                           /// <데이터 포인트가 직선과 연결됨
                 };
  Q_ENUMS(LineStyle)
  
  explicit QCPCurve(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPCurve();
  
  // getters:
  QSharedPointer<QCPCurveDataContainer> data() const { return mDataContainer; }
  QCPScatterStyle scatterStyle() const { return mScatterStyle; }
  int scatterSkip() const { return mScatterSkip; }
  LineStyle lineStyle() const { return mLineStyle; }
  
  // setters:
  void setData(QSharedPointer<QCPCurveDataContainer> data);
  void setData(const QVector<double> &t, const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setData(const QVector<double> &keys, const QVector<double> &values);
  void setScatterStyle(const QCPScatterStyle &style);
  void setScatterSkip(int skip);
  void setLineStyle(LineStyle style);
  
  // non-property methods:
  // 비 속성 메소드 :
  void addData(const QVector<double> &t, const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(const QVector<double> &keys, const QVector<double> &values);
  void addData(double t, double key, double value);
  void addData(double key, double value);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  // 속성 멤버 :
  QCPScatterStyle mScatterStyle;
  int mScatterSkip;
  LineStyle mLineStyle;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void drawCurveLine(QCPPainter *painter, const QVector<QPointF> &lines) const;
  virtual void drawScatterPlot(QCPPainter *painter, const QVector<QPointF> &points, const QCPScatterStyle &style) const;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void getCurveLines(QVector<QPointF> *lines, const QCPDataRange &dataRange, double penWidth) const;
  void getScatters(QVector<QPointF> *scatters, const QCPDataRange &dataRange, double scatterWidth) const;
  int getRegion(double key, double value, double keyMin, double valueMax, double keyMax, double valueMin) const;
  QPointF getOptimizedPoint(int prevRegion, double prevKey, double prevValue, double key, double value, double keyMin, double valueMax, double keyMax, double valueMin) const;
  QVector<QPointF> getOptimizedCornerPoints(int prevRegion, int currentRegion, double prevKey, double prevValue, double key, double value, double keyMin, double valueMax, double keyMax, double valueMin) const;
  bool mayTraverse(int prevRegion, int currentRegion) const;
  bool getTraverse(double prevKey, double prevValue, double key, double value, double keyMin, double valueMax, double keyMax, double valueMin, QPointF &crossA, QPointF &crossB) const;
  void getTraverseCornerPoints(int prevRegion, int currentRegion, double keyMin, double valueMax, double keyMax, double valueMin, QVector<QPointF> &beforeTraverse, QVector<QPointF> &afterTraverse) const;
  double pointDistance(const QPointF &pixelPoint, QCPCurveDataContainer::const_iterator &closestData) const;
  
  friend class QCustomPlot;
  friend class QCPLegend;
};
Q_DECLARE_METATYPE(QCPCurve::LineStyle)

/* end of 'src/plottables/plottable-curve.h' */


/* including file 'src/plottables/plottable-bars.h', size 8924               */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottables / plottable-curve.h'의 끝 */


/* 'src / plottables / plottable-bars.h'파일 포함, 크기 8924                */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPBarsGroup : public QObject
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(SpacingType spacingType READ spacingType WRITE setSpacingType)
  Q_PROPERTY(double spacing READ spacing WRITE setSpacing)
  /// \endcond
public:
  /*!
    Defines the ways the spacing between bars in the group can be specified. Thus it defines what
    the number passed to \ref setSpacing actually means.
    
    \see setSpacingType, setSpacing
  */
 /* !
    그룹에서 막대 사이의 간격을 지정할 수있는 방법을 정의합니다. 따라서 그것은 무엇을 정의 하는가?
    \ ref setSpacing에 전달 된 숫자는 실제로 의미합니다.
    
    \ setSpacingType, setSpacing 참조
  */
  enum SpacingType { stAbsolute       ///< Bar spacing is in absolute pixels
                                      /// <바 간격은 절대 픽셀 수
                     ,stAxisRectRatio ///< Bar spacing is given by a fraction of the axis rect size
/// <바 간격은 축 rect 크기의 분수로 지정됩니다.
                     ,stPlotCoords    ///< Bar spacing is in key coordinates and thus scales with the key axis range
/// <막대 간격은 키 좌표이므로 키 축 범위와 함께 조절됩니다
                   };
  Q_ENUMS(SpacingType)
  
  QCPBarsGroup(QCustomPlot *parentPlot);
  virtual ~QCPBarsGroup();
  
  // getters:
  SpacingType spacingType() const { return mSpacingType; }
  double spacing() const { return mSpacing; }
  
  // setters:
  void setSpacingType(SpacingType spacingType);
  void setSpacing(double spacing);
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QList<QCPBars*> bars() const { return mBars; }
  QCPBars* bars(int index) const;
  int size() const { return mBars.size(); }
  bool isEmpty() const { return mBars.isEmpty(); }
  void clear();
  bool contains(QCPBars *bars) const { return mBars.contains(bars); }
  void append(QCPBars *bars);
  void insert(int i, QCPBars *bars);
  void remove(QCPBars *bars);
  
protected:
  // non-property members:
  // 비 속성 멤버 :
  QCustomPlot *mParentPlot;
  SpacingType mSpacingType;
  double mSpacing;
  QList<QCPBars*> mBars;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void registerBars(QCPBars *bars);
  void unregisterBars(QCPBars *bars);
  
  // virtual methods:
  // 가상 메소드 :
  double keyPixelOffset(const QCPBars *bars, double keyCoord);
  double getPixelSpacing(const QCPBars *bars, double keyCoord);
  
private:
  Q_DISABLE_COPY(QCPBarsGroup)
  
  friend class QCPBars;
};
Q_DECLARE_METATYPE(QCPBarsGroup::SpacingType)


class QCP_LIB_DECL QCPBarsData
{
public:
  QCPBarsData();
  QCPBarsData(double key, double value);
  
  inline double sortKey() const { return key; }
  inline static QCPBarsData fromSortKey(double sortKey) { return QCPBarsData(sortKey, 0); }
  inline static bool sortKeyIsMainKey() { return true; } 
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return value; }
  
  inline QCPRange valueRange() const { return QCPRange(value, value); } // note that bar base value isn't held in each QCPBarsData and thus can't/shouldn't be returned here
// 각 QCPBarsData에 막대 기본 값이 저장되지 않으므로 여기에 반환 할 수 없으며 반환 할 수 없습니다.
    
  double key, value;
};
Q_DECLARE_TYPEINFO(QCPBarsData, Q_PRIMITIVE_TYPE);


/*! \typedef QCPBarsDataContainer
  
  Container for storing \ref QCPBarsData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which QCPBars holds its data. For details about
  the generic container, see the documentation of the class template \ref QCPDataContainer.
  
  \see QCPBarsData, QCPBars::setData
*/
/* ! \ typedef QCPBarsDataContainer
  
  \ ref QCPBarsData 포인트를 저장하는 컨테이너입니다. 데이터는 키로 정렬되어 저장됩니다.
  
  이 템플릿 인스턴스화는 QCPBars가 데이터를 보유하고있는 컨테이너입니다. 자세한 내용은
  제네릭 컨테이너에 대해서는 클래스 템플릿 \ ref QCPDataContainer의 설명서를 참조하십시오.
  
  \ see QCPBarsData, QCPBars :: setData
*/
typedef QCPDataContainer<QCPBarsData> QCPBarsDataContainer;

class QCP_LIB_DECL QCPBars : public QCPAbstractPlottable1D<QCPBarsData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(double width READ width WRITE setWidth)
  Q_PROPERTY(WidthType widthType READ widthType WRITE setWidthType)
  Q_PROPERTY(QCPBarsGroup* barsGroup READ barsGroup WRITE setBarsGroup)
  Q_PROPERTY(double baseValue READ baseValue WRITE setBaseValue)
  Q_PROPERTY(double stackingGap READ stackingGap WRITE setStackingGap)
  Q_PROPERTY(QCPBars* barBelow READ barBelow)
  Q_PROPERTY(QCPBars* barAbove READ barAbove)
  /// \endcond
public:
  /*!
    Defines the ways the width of the bar can be specified. Thus it defines what the number passed
    to \ref setWidth actually means.
    
    \see setWidthType, setWidth
  */
  /* !
    막대의 너비를 지정할 수있는 방법을 정의합니다. 따라서 그것은 전달 된 숫자를 정의합니다.
    to \ ref setWidth는 실제로 의미합니다.
    
    \ setWidthType 참조, setWidth
  */
  enum WidthType { wtAbsolute       ///< Bar width is in absolute pixels
                                    /// <막대 너비가 절대 픽셀 수
                   ,wtAxisRectRatio ///< Bar width is given by a fraction of the axis rect size
                                    /// <막대 너비는 축 rect 크기의 분수로 지정됩니다.
                   ,wtPlotCoords    ///< Bar width is in key coordinates and thus scales with the key axis range
/// <막대 너비는 키 좌표이므로 키 축 범위와 함께 조절됩니다
                 };
  Q_ENUMS(WidthType)
  
  explicit QCPBars(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPBars();
  
  // getters:
  double width() const { return mWidth; }
  WidthType widthType() const { return mWidthType; }
  QCPBarsGroup *barsGroup() const { return mBarsGroup; }
  double baseValue() const { return mBaseValue; }
  double stackingGap() const { return mStackingGap; }
  QCPBars *barBelow() const { return mBarBelow.data(); }
  QCPBars *barAbove() const { return mBarAbove.data(); }
  QSharedPointer<QCPBarsDataContainer> data() const { return mDataContainer; }
  
  // setters:
  void setData(QSharedPointer<QCPBarsDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void setWidth(double width);
  void setWidthType(WidthType widthType);
  void setBarsGroup(QCPBarsGroup *barsGroup);
  void setBaseValue(double baseValue);
  void setStackingGap(double pixels);
  
  // non-property methods:
  // 비 속성 메소드 :
  void addData(const QVector<double> &keys, const QVector<double> &values, bool alreadySorted=false);
  void addData(double key, double value);
  void moveBelow(QCPBars *bars);
  void moveAbove(QCPBars *bars);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  virtual QPointF dataPixelPosition(int index) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  // 속성 멤버 :
  double mWidth;
  WidthType mWidthType;
  QCPBarsGroup *mBarsGroup;
  double mBaseValue;
  double mStackingGap;
  QPointer<QCPBars> mBarBelow, mBarAbove;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void getVisibleDataBounds(QCPBarsDataContainer::const_iterator &begin, QCPBarsDataContainer::const_iterator &end) const;
  QRectF getBarRect(double key, double value) const;
  void getPixelWidth(double key, double &lower, double &upper) const;
  double getStackedBaseValue(double key, bool positive) const;
  static void connectBars(QCPBars* lower, QCPBars* upper);
  
  friend class QCustomPlot;
  friend class QCPLegend;
  friend class QCPBarsGroup;
};
Q_DECLARE_METATYPE(QCPBars::WidthType)

/* end of 'src/plottables/plottable-bars.h' */


/* including file 'src/plottables/plottable-statisticalbox.h', size 7516     */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottables / plottable-bars.h'의 끝 */

/* 'src / plottables / plottable-statisticalbox.h'파일을 포함하여 크기 7516  */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPStatisticalBoxData
{
public:
  QCPStatisticalBoxData();
  QCPStatisticalBoxData(double key, double minimum, double lowerQuartile, double median, double upperQuartile, double maximum, const QVector<double>& outliers=QVector<double>());
  
  inline double sortKey() const { return key; }
  inline static QCPStatisticalBoxData fromSortKey(double sortKey) { return QCPStatisticalBoxData(sortKey, 0, 0, 0, 0, 0); }
  inline static bool sortKeyIsMainKey() { return true; }
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return median; }
  
  inline QCPRange valueRange() const
  {
    QCPRange result(minimum, maximum);
    for (QVector<double>::const_iterator it = outliers.constBegin(); it != outliers.constEnd(); ++it)
      result.expand(*it);
    return result;
  }
  
  double key, minimum, lowerQuartile, median, upperQuartile, maximum;
  QVector<double> outliers;
};
Q_DECLARE_TYPEINFO(QCPStatisticalBoxData, Q_MOVABLE_TYPE);


/*! \typedef QCPStatisticalBoxDataContainer
  
  Container for storing \ref QCPStatisticalBoxData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which QCPStatisticalBox holds its data. For
  details about the generic container, see the documentation of the class template \ref
  QCPDataContainer.
  
  \see QCPStatisticalBoxData, QCPStatisticalBox::setData
*/
/* ! \ typedef QCPStatisticalBoxDataContainer
  
  \ ref QCPStatisticalBoxData 데이터를 저장하는 컨테이너입니다. 데이터는 키로 정렬되어 저장됩니다.
  
  이 템플릿 인스턴스화는 QCPStatisticalBox가 데이터를 보유하는 컨테이너입니다. 에 대한
  제네릭 컨테이너에 대한 자세한 내용은 클래스 템플릿 \ ref의 설명서를 참조하십시오.
  QCPDataContainer.
  
  \ QCPStatisticalBoxData, QCPStatisticalBox :: setData를 참조하십시오.
*/
typedef QCPDataContainer<QCPStatisticalBoxData> QCPStatisticalBoxDataContainer;

class QCP_LIB_DECL QCPStatisticalBox : public QCPAbstractPlottable1D<QCPStatisticalBoxData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(double width READ width WRITE setWidth)
  Q_PROPERTY(double whiskerWidth READ whiskerWidth WRITE setWhiskerWidth)
  Q_PROPERTY(QPen whiskerPen READ whiskerPen WRITE setWhiskerPen)
  Q_PROPERTY(QPen whiskerBarPen READ whiskerBarPen WRITE setWhiskerBarPen)
  Q_PROPERTY(bool whiskerAntialiased READ whiskerAntialiased WRITE setWhiskerAntialiased)
  Q_PROPERTY(QPen medianPen READ medianPen WRITE setMedianPen)
  Q_PROPERTY(QCPScatterStyle outlierStyle READ outlierStyle WRITE setOutlierStyle)
  /// \endcond
public:
  explicit QCPStatisticalBox(QCPAxis *keyAxis, QCPAxis *valueAxis);
  
  // getters:
  QSharedPointer<QCPStatisticalBoxDataContainer> data() const { return mDataContainer; }
  double width() const { return mWidth; }
  double whiskerWidth() const { return mWhiskerWidth; }
  QPen whiskerPen() const { return mWhiskerPen; }
  QPen whiskerBarPen() const { return mWhiskerBarPen; }
  bool whiskerAntialiased() const { return mWhiskerAntialiased; }
  QPen medianPen() const { return mMedianPen; }
  QCPScatterStyle outlierStyle() const { return mOutlierStyle; }

  // setters:
  void setData(QSharedPointer<QCPStatisticalBoxDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &minimum, const QVector<double> &lowerQuartile, const QVector<double> &median, const QVector<double> &upperQuartile, const QVector<double> &maximum, bool alreadySorted=false);
  void setWidth(double width);
  void setWhiskerWidth(double width);
  void setWhiskerPen(const QPen &pen);
  void setWhiskerBarPen(const QPen &pen);
  void setWhiskerAntialiased(bool enabled);
  void setMedianPen(const QPen &pen);
  void setOutlierStyle(const QCPScatterStyle &style);
  
  // non-property methods:
  // 비 속성 메소드 :
  void addData(const QVector<double> &keys, const QVector<double> &minimum, const QVector<double> &lowerQuartile, const QVector<double> &median, const QVector<double> &upperQuartile, const QVector<double> &maximum, bool alreadySorted=false);
  void addData(double key, double minimum, double lowerQuartile, double median, double upperQuartile, double maximum, const QVector<double> &outliers=QVector<double>());
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  
protected:
  // property members:
  // 속성 멤버 :
  double mWidth;
  double mWhiskerWidth;
  QPen mWhiskerPen, mWhiskerBarPen;
  bool mWhiskerAntialiased;
  QPen mMedianPen;
  QCPScatterStyle mOutlierStyle;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void drawStatisticalBox(QCPPainter *painter, QCPStatisticalBoxDataContainer::const_iterator it, const QCPScatterStyle &outlierStyle) const;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void getVisibleDataBounds(QCPStatisticalBoxDataContainer::const_iterator &begin, QCPStatisticalBoxDataContainer::const_iterator &end) const;
  QRectF getQuartileBox(QCPStatisticalBoxDataContainer::const_iterator it) const;
  QVector<QLineF> getWhiskerBackboneLines(QCPStatisticalBoxDataContainer::const_iterator it) const;
  QVector<QLineF> getWhiskerBarLines(QCPStatisticalBoxDataContainer::const_iterator it) const;
  
  friend class QCustomPlot;
  friend class QCPLegend;
};

/* end of 'src/plottables/plottable-statisticalbox.h' */


/* including file 'src/plottables/plottable-colormap.h', size 7070           */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottables / plottable-statisticalbox.h'의 끝 */


/* 파일 'src / plottables / plottable-colormap.h', 크기 7070            포함*/
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPColorMapData
{
public:
  QCPColorMapData(int keySize, int valueSize, const QCPRange &keyRange, const QCPRange &valueRange);
  ~QCPColorMapData();
  QCPColorMapData(const QCPColorMapData &other);
  QCPColorMapData &operator=(const QCPColorMapData &other);
  
  // getters:
  int keySize() const { return mKeySize; }
  int valueSize() const { return mValueSize; }
  QCPRange keyRange() const { return mKeyRange; }
  QCPRange valueRange() const { return mValueRange; }
  QCPRange dataBounds() const { return mDataBounds; }
  double data(double key, double value);
  double cell(int keyIndex, int valueIndex);
  unsigned char alpha(int keyIndex, int valueIndex);
  
  // setters:
  void setSize(int keySize, int valueSize);
  void setKeySize(int keySize);
  void setValueSize(int valueSize);
  void setRange(const QCPRange &keyRange, const QCPRange &valueRange);
  void setKeyRange(const QCPRange &keyRange);
  void setValueRange(const QCPRange &valueRange);
  void setData(double key, double value, double z);
  void setCell(int keyIndex, int valueIndex, double z);
  void setAlpha(int keyIndex, int valueIndex, unsigned char alpha);
  
  // non-property methods:
  // 비 속성 메소드 :
  void recalculateDataBounds();
  void clear();
  void clearAlpha();
  void fill(double z);
  void fillAlpha(unsigned char alpha);
  bool isEmpty() const { return mIsEmpty; }
  void coordToCell(double key, double value, int *keyIndex, int *valueIndex) const;
  void cellToCoord(int keyIndex, int valueIndex, double *key, double *value) const;
  
protected:
  // property members:
  // 속성 멤버 :
  int mKeySize, mValueSize;
  QCPRange mKeyRange, mValueRange;
  bool mIsEmpty;
  
  // non-property members:
  // 비 속성 멤버 :
  double *mData;
  unsigned char *mAlpha;
  QCPRange mDataBounds;
  bool mDataModified;
  
  bool createAlpha(bool initializeOpaque=true);
  
  friend class QCPColorMap;
};


class QCP_LIB_DECL QCPColorMap : public QCPAbstractPlottable
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QCPRange dataRange READ dataRange WRITE setDataRange NOTIFY dataRangeChanged)
  Q_PROPERTY(QCPAxis::ScaleType dataScaleType READ dataScaleType WRITE setDataScaleType NOTIFY dataScaleTypeChanged)
  Q_PROPERTY(QCPColorGradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged)
  Q_PROPERTY(bool interpolate READ interpolate WRITE setInterpolate)
  Q_PROPERTY(bool tightBoundary READ tightBoundary WRITE setTightBoundary)
  Q_PROPERTY(QCPColorScale* colorScale READ colorScale WRITE setColorScale)
  /// \endcond
public:
  explicit QCPColorMap(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPColorMap();
  
  // getters:
  QCPColorMapData *data() const { return mMapData; }
  QCPRange dataRange() const { return mDataRange; }
  QCPAxis::ScaleType dataScaleType() const { return mDataScaleType; }
  bool interpolate() const { return mInterpolate; }
  bool tightBoundary() const { return mTightBoundary; }
  QCPColorGradient gradient() const { return mGradient; }
  QCPColorScale *colorScale() const { return mColorScale.data(); }
  
  // setters:
  void setData(QCPColorMapData *data, bool copy=false);
  Q_SLOT void setDataRange(const QCPRange &dataRange);
  Q_SLOT void setDataScaleType(QCPAxis::ScaleType scaleType);
  Q_SLOT void setGradient(const QCPColorGradient &gradient);
  void setInterpolate(bool enabled);
  void setTightBoundary(bool enabled);
  void setColorScale(QCPColorScale *colorScale);
  
  // non-property methods:
  // 비 속성 메소드 :
  void rescaleDataRange(bool recalculateDataBounds=false);
  Q_SLOT void updateLegendIcon(Qt::TransformationMode transformMode=Qt::SmoothTransformation, const QSize &thumbSize=QSize(32, 18));
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  
signals:
  void dataRangeChanged(const QCPRange &newRange);
  void dataScaleTypeChanged(QCPAxis::ScaleType scaleType);
  void gradientChanged(const QCPColorGradient &newGradient);
  
protected:
  // property members:
  // 속성 멤버 :
  QCPRange mDataRange;
  QCPAxis::ScaleType mDataScaleType;
  QCPColorMapData *mMapData;
  QCPColorGradient mGradient;
  bool mInterpolate;
  bool mTightBoundary;
  QPointer<QCPColorScale> mColorScale;
  
  // non-property members:
  // 비 속성 멤버 :
  QImage mMapImage, mUndersampledMapImage;
  QPixmap mLegendIcon;
  bool mMapImageInvalidated;
  
  // introduced virtual methods:
  // 도입 된 가상 메소드 :
  virtual void updateMapImage();
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  friend class QCustomPlot;
  friend class QCPLegend;
};

/* end of 'src/plottables/plottable-colormap.h' */


/* including file 'src/plottables/plottable-financial.h', size 8622          */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottables / plottable-colormap.h'의 끝 */

/* 'src / plottables / plottable-financial.h'파일을 포함하여 크기 8622       */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPFinancialData
{
public:
  QCPFinancialData();
  QCPFinancialData(double key, double open, double high, double low, double close);
  
  inline double sortKey() const { return key; }
  inline static QCPFinancialData fromSortKey(double sortKey) { return QCPFinancialData(sortKey, 0, 0, 0, 0); }
  inline static bool sortKeyIsMainKey() { return true; } 
  
  inline double mainKey() const { return key; }
  inline double mainValue() const { return open; }
  
  inline QCPRange valueRange() const { return QCPRange(low, high); } // open and close must lie between low and high, so we don't need to check them
// 열림과 닫힘은 낮고 높게 놓여 야합니다. 그래서 우리는 그것들을 검사 할 필요가 없습니다
  
  double key, open, high, low, close;
};
Q_DECLARE_TYPEINFO(QCPFinancialData, Q_PRIMITIVE_TYPE);


/*! \typedef QCPFinancialDataContainer
  
  Container for storing \ref QCPFinancialData points. The data is stored sorted by \a key.
  
  This template instantiation is the container in which QCPFinancial holds its data. For details
  about the generic container, see the documentation of the class template \ref QCPDataContainer.
  
  \see QCPFinancialData, QCPFinancial::setData
*/
/* ! \ typedef QCPFinancialDataContainer
  
  \ ref QCPFinancialData 포인트를 저장하는 컨테이너. 데이터는 키로 정렬되어 저장됩니다.
  
  이 템플릿 인스턴스화는 QCPFinancial이 데이터를 보유하고있는 컨테이너입니다. 자세한 내용은
  제네릭 컨테이너에 대해서는 클래스 템플릿 \ ref QCPDataContainer의 설명서를 참조하십시오.
  
  \ see QCPFinancialData, QCPFinancial :: setData
*/
typedef QCPDataContainer<QCPFinancialData> QCPFinancialDataContainer;

class QCP_LIB_DECL QCPFinancial : public QCPAbstractPlottable1D<QCPFinancialData>
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(ChartStyle chartStyle READ chartStyle WRITE setChartStyle)
  Q_PROPERTY(double width READ width WRITE setWidth)
  Q_PROPERTY(WidthType widthType READ widthType WRITE setWidthType)
  Q_PROPERTY(bool twoColored READ twoColored WRITE setTwoColored)
  Q_PROPERTY(QBrush brushPositive READ brushPositive WRITE setBrushPositive)
  Q_PROPERTY(QBrush brushNegative READ brushNegative WRITE setBrushNegative)
  Q_PROPERTY(QPen penPositive READ penPositive WRITE setPenPositive)
  Q_PROPERTY(QPen penNegative READ penNegative WRITE setPenNegative)
  /// \endcond
public:
  /*!
    Defines the ways the width of the financial bar can be specified. Thus it defines what the
    number passed to \ref setWidth actually means.

    \see setWidthType, setWidth
  */
  /* !
    재무 막대의 너비를 지정할 수있는 방법을 정의합니다. 따라서 그것은
    \ ref setWidth에 전달 된 숫자는 실제로 의미합니다.
    \ setWidthType 참조, setWidth
  */
  enum WidthType { wtAbsolute       ///< width is in absolute pixels
                                    /// <width는 절대 픽셀 수입니다.
                   ,wtAxisRectRatio ///< width is given by a fraction of the axis rect size
                                    /// <width는 축 rect 크기의 분수로 주어진다.
                   ,wtPlotCoords    ///< width is in key coordinates and thus scales with the key axis range
/// <width는 키 좌표에 있으므로 키 축 범위와 함께 조절됩니다
                 };
  Q_ENUMS(WidthType)
  
  /*!
    Defines the possible representations of OHLC data in the plot.
    
    \see setChartStyle
  */
 
  /* !
    플롯에서 OHLC 데이터의 가능한 표현을 정의합니다.
    
    \ see setChartStyle
  */
  enum ChartStyle { csOhlc         ///< Open-High-Low-Close bar representation
                                   /// <열린 높이가 낮은 닫기 막대 표현
                   ,csCandlestick  ///< Candlestick representation
                                   /// <촛대 표현
                  };
  Q_ENUMS(ChartStyle)
  
  explicit QCPFinancial(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPFinancial();
  
  // getters:
  QSharedPointer<QCPFinancialDataContainer> data() const { return mDataContainer; }
  ChartStyle chartStyle() const { return mChartStyle; }
  double width() const { return mWidth; }
  WidthType widthType() const { return mWidthType; }
  bool twoColored() const { return mTwoColored; }
  QBrush brushPositive() const { return mBrushPositive; }
  QBrush brushNegative() const { return mBrushNegative; }
  QPen penPositive() const { return mPenPositive; }
  QPen penNegative() const { return mPenNegative; }
  
  // setters:
  void setData(QSharedPointer<QCPFinancialDataContainer> data);
  void setData(const QVector<double> &keys, const QVector<double> &open, const QVector<double> &high, const QVector<double> &low, const QVector<double> &close, bool alreadySorted=false);
  void setChartStyle(ChartStyle style);
  void setWidth(double width);
  void setWidthType(WidthType widthType);
  void setTwoColored(bool twoColored);
  void setBrushPositive(const QBrush &brush);
  void setBrushNegative(const QBrush &brush);
  void setPenPositive(const QPen &pen);
  void setPenNegative(const QPen &pen);
  
  // non-property methods:
  // 비 속성 메소드 :
  void addData(const QVector<double> &keys, const QVector<double> &open, const QVector<double> &high, const QVector<double> &low, const QVector<double> &close, bool alreadySorted=false);
  void addData(double key, double open, double high, double low, double close);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual QCPDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  
  // static methods:
  // 정적 메소드 :
  static QCPFinancialDataContainer timeSeriesToOhlc(const QVector<double> &time, const QVector<double> &value, double timeBinSize, double timeBinOffset = 0);
  
protected:
  // property members:
  // 속성 멤버 :
  ChartStyle mChartStyle;
  double mWidth;
  WidthType mWidthType;
  bool mTwoColored;
  QBrush mBrushPositive, mBrushNegative;
  QPen mPenPositive, mPenNegative;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void drawOhlcPlot(QCPPainter *painter, const QCPFinancialDataContainer::const_iterator &begin, const QCPFinancialDataContainer::const_iterator &end, bool isSelected);
  void drawCandlestickPlot(QCPPainter *painter, const QCPFinancialDataContainer::const_iterator &begin, const QCPFinancialDataContainer::const_iterator &end, bool isSelected);
  double getPixelWidth(double key, double keyPixel) const;
  double ohlcSelectTest(const QPointF &pos, const QCPFinancialDataContainer::const_iterator &begin, const QCPFinancialDataContainer::const_iterator &end, QCPFinancialDataContainer::const_iterator &closestDataPoint) const;
  double candlestickSelectTest(const QPointF &pos, const QCPFinancialDataContainer::const_iterator &begin, const QCPFinancialDataContainer::const_iterator &end, QCPFinancialDataContainer::const_iterator &closestDataPoint) const;
  void getVisibleDataBounds(QCPFinancialDataContainer::const_iterator &begin, QCPFinancialDataContainer::const_iterator &end) const;
  QRectF selectionHitBox(QCPFinancialDataContainer::const_iterator it) const;
  
  friend class QCustomPlot;
  friend class QCPLegend;
};
Q_DECLARE_METATYPE(QCPFinancial::ChartStyle)

/* end of 'src/plottables/plottable-financial.h' */


/* including file 'src/plottables/plottable-errorbar.h', size 7727           */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottables / plottable-financial.h'의 끝 */

/* 'src / plottables / plottable-errorbar.h'파일 포함, 크기 7727            */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPErrorBarsData
{
public:
  QCPErrorBarsData();
  explicit QCPErrorBarsData(double error);
  QCPErrorBarsData(double errorMinus, double errorPlus);
  
  double errorMinus, errorPlus;
};
Q_DECLARE_TYPEINFO(QCPErrorBarsData, Q_PRIMITIVE_TYPE);


/*! \typedef QCPErrorBarsDataContainer

  Container for storing \ref QCPErrorBarsData points. It is a typedef for <tt>QVector<\ref
  QCPErrorBarsData></tt>.

  This is the container in which \ref QCPErrorBars holds its data. Unlike most other data
  containers for plottables, it is not based on \ref QCPDataContainer. This is because the error
  bars plottable is special in that it doesn't store its own key and value coordinate per error
  bar. It adopts the key and value from the plottable to which the error bars shall be applied
  (\ref QCPErrorBars::setDataPlottable). So the stored \ref QCPErrorBarsData doesn't need a
  sortable key, but merely an index (as \c QVector provides), which maps one-to-one to the indices
  of the other plottable's data.

  \see QCPErrorBarsData, QCPErrorBars::setData
*/
/* ! \ typedef QCPErrorBarsDataContainer
  \ ref QCPErrorBarsData 포인트를 저장하기위한 컨테이너. <tt> QVector <\ ref의 typedef입니다.
  QCPErrorBarsData> </ tt>를 선택하십시오.
  이것은 \ ref QCPErrorBars가 데이터를 보유하고있는 컨테이너입니다. 다른 대부분의 데이터와 달리
  plottables에 대한 컨테이너는 \ ref QCPDataContainer를 기반으로하지 않습니다. 이것은 오류
  bar plottable은 오류 당 자체 키와 값 좌표를 저장하지 않는다는 점에서 특별합니다.
  바. 오차 막대가 적용될 플롯 테이블의 키와 값을 사용합니다.
  (\ ref QCPErrorBars :: setDataPlottable). 그래서 저장된 \ ref QCPErrorBarsData는 필요하지 않습니다.
  정렬 가능한 키가 아니라 색인에 일대일로 매핑하는 색인 ​​(QVector에서 제공)
  다른 플롯 데이터의
  \ see QCPErrorBarsData, QCPErrorBars :: setData
*/
typedef QVector<QCPErrorBarsData> QCPErrorBarsDataContainer;

class QCP_LIB_DECL QCPErrorBars : public QCPAbstractPlottable, public QCPPlottableInterface1D
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QSharedPointer<QCPErrorBarsDataContainer> data READ data WRITE setData)
  Q_PROPERTY(QCPAbstractPlottable* dataPlottable READ dataPlottable WRITE setDataPlottable)
  Q_PROPERTY(ErrorType errorType READ errorType WRITE setErrorType)
  Q_PROPERTY(double whiskerWidth READ whiskerWidth WRITE setWhiskerWidth)
  Q_PROPERTY(double symbolGap READ symbolGap WRITE setSymbolGap)
  /// \endcond
public:
  
  /*!
    Defines in which orientation the error bars shall appear. If your data needs both error
    dimensions, create two \ref QCPErrorBars with different \ref ErrorType.

    \see setErrorType
  */
 /* !
    오류 막대가 나타날 방향을 정의합니다. 데이터에 오류가 모두 필요한 경우
    두 개의 \ ref QCPErrorBars를 서로 다른 \ ref 오류 유형으로 작성하십시오.
    \ setErrorType을 참조하십시오.
  */
  enum ErrorType { etKeyError    ///< The errors are for the key dimension (bars appear parallel to the key axis)
/// <키 치수에 대한 오류입니다 (막대가 키 축에 평행하게 나타납니다)
                   ,etValueError ///< The errors are for the value dimension (bars appear parallel to the value axis)
/// <오류는 값 차원을 나타냅니다 (막대는 값 축과 평행하게 나타납니다)
  };
  Q_ENUMS(ErrorType)
  
  explicit QCPErrorBars(QCPAxis *keyAxis, QCPAxis *valueAxis);
  virtual ~QCPErrorBars();
  // getters:
  QSharedPointer<QCPErrorBarsDataContainer> data() const { return mDataContainer; }
  QCPAbstractPlottable *dataPlottable() const { return mDataPlottable.data(); }
  ErrorType errorType() const { return mErrorType; }
  double whiskerWidth() const { return mWhiskerWidth; }
  double symbolGap() const { return mSymbolGap; }
  
  // setters:
  void setData(QSharedPointer<QCPErrorBarsDataContainer> data);
  void setData(const QVector<double> &error);
  void setData(const QVector<double> &errorMinus, const QVector<double> &errorPlus);
  void setDataPlottable(QCPAbstractPlottable* plottable);
  void setErrorType(ErrorType type);
  void setWhiskerWidth(double pixels);
  void setSymbolGap(double pixels);
  
  // non-property methods:
  // 비 속성 메소드 :
  void addData(const QVector<double> &error);
  void addData(const QVector<double> &errorMinus, const QVector<double> &errorPlus);
  void addData(double error);
  void addData(double errorMinus, double errorPlus);
  
  // virtual methods of 1d plottable interface:
  // 1d plottable 인터페이스의 가상 메소드 :
  virtual int dataCount() const Q_DECL_OVERRIDE;
  virtual double dataMainKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataSortKey(int index) const Q_DECL_OVERRIDE;
  virtual double dataMainValue(int index) const Q_DECL_OVERRIDE;
  virtual QCPRange dataValueRange(int index) const Q_DECL_OVERRIDE;
  virtual QPointF dataPixelPosition(int index) const Q_DECL_OVERRIDE;
  virtual bool sortKeyIsMainKey() const Q_DECL_OVERRIDE;
  virtual QCPDataSelection selectTestRect(const QRectF &rect, bool onlySelectable) const Q_DECL_OVERRIDE;
  virtual int findBegin(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  virtual int findEnd(double sortKey, bool expandedRange=true) const Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  virtual QCPPlottableInterface1D *interface1D() Q_DECL_OVERRIDE { return this; }
  
protected:
  // property members:
  // 속성 멤버 :
  QSharedPointer<QCPErrorBarsDataContainer> mDataContainer;
  QPointer<QCPAbstractPlottable> mDataPlottable;
  ErrorType mErrorType;
  double mWhiskerWidth;
  double mSymbolGap;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual void drawLegendIcon(QCPPainter *painter, const QRectF &rect) const Q_DECL_OVERRIDE;
  virtual QCPRange getKeyRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth) const Q_DECL_OVERRIDE;
  virtual QCPRange getValueRange(bool &foundRange, QCP::SignDomain inSignDomain=QCP::sdBoth, const QCPRange &inKeyRange=QCPRange()) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void getErrorBarLines(QCPErrorBarsDataContainer::const_iterator it, QVector<QLineF> &backbones, QVector<QLineF> &whiskers) const;
  void getVisibleDataBounds(QCPErrorBarsDataContainer::const_iterator &begin, QCPErrorBarsDataContainer::const_iterator &end, const QCPDataRange &rangeRestriction) const;
  double pointDistance(const QPointF &pixelPoint, QCPErrorBarsDataContainer::const_iterator &closestData) const;
  // helpers:
  // 헬퍼 :
  void getDataSegments(QList<QCPDataRange> &selectedSegments, QList<QCPDataRange> &unselectedSegments) const;
  bool errorBarVisible(int index) const;
  bool rectIntersectsLine(const QRectF &pixelRect, const QLineF &line) const;
  
  friend class QCustomPlot;
  friend class QCPLegend;
};

/* end of 'src/plottables/plottable-errorbar.h' */


/* including file 'src/items/item-straightline.h', size 3117                 */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / plottables / plottable-errorbar.h'의 끝 */

/* 'src / items / item-straightline.h'파일 포함, 크기 3117                  */ 
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPItemStraightLine : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  /// \endcond
public:
  explicit QCPItemStraightLine(QCustomPlot *parentPlot);
  virtual ~QCPItemStraightLine();
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const point1;
  QCPItemPosition * const point2;
  
protected:
  // property members:
  // 속성 멤버 :
  QPen mPen, mSelectedPen;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QLineF getRectClippedStraightLine(const QCPVector2D &point1, const QCPVector2D &vec, const QRect &rect) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-straightline.h' */


/* including file 'src/items/item-line.h', size 3407                         */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-straightline.h'의 끝 */

/* 파일 'src / items / item-line.h', 크기 3407 포함                         */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPItemLine : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QCPLineEnding head READ head WRITE setHead)
  Q_PROPERTY(QCPLineEnding tail READ tail WRITE setTail)
  /// \endcond
public:
  explicit QCPItemLine(QCustomPlot *parentPlot);
  virtual ~QCPItemLine();
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QCPLineEnding head() const { return mHead; }
  QCPLineEnding tail() const { return mTail; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setHead(const QCPLineEnding &head);
  void setTail(const QCPLineEnding &tail);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const start;
  QCPItemPosition * const end;
  
protected:
  // property members:
  // 속성 멤버 :
  QPen mPen, mSelectedPen;
  QCPLineEnding mHead, mTail;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QLineF getRectClippedLine(const QCPVector2D &start, const QCPVector2D &end, const QRect &rect) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-line.h' */


/* including file 'src/items/item-curve.h', size 3379                        */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-line.h'의 끝 */

/* 'src / items / item-curve.h'파일 포함, 크기 3379                         */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPItemCurve : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QCPLineEnding head READ head WRITE setHead)
  Q_PROPERTY(QCPLineEnding tail READ tail WRITE setTail)
  /// \endcond
public:
  explicit QCPItemCurve(QCustomPlot *parentPlot);
  virtual ~QCPItemCurve();
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QCPLineEnding head() const { return mHead; }
  QCPLineEnding tail() const { return mTail; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setHead(const QCPLineEnding &head);
  void setTail(const QCPLineEnding &tail);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const start;
  QCPItemPosition * const startDir;
  QCPItemPosition * const endDir;
  QCPItemPosition * const end;
  
protected:
  // property members:
  // 속성 멤버 :
  QPen mPen, mSelectedPen;
  QCPLineEnding mHead, mTail;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPen mainPen() const;
};

/* end of 'src/items/item-curve.h' */


/* including file 'src/items/item-rect.h', size 3688                         */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-curve.h'의 끝 */

/* 'src / items / item-rect.h'파일 포함, 크기 3688                          */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPItemRect : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  /// \endcond
public:
  explicit QCPItemRect(QCustomPlot *parentPlot);
  virtual ~QCPItemRect();
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const topLeft;
  QCPItemPosition * const bottomRight;
  QCPItemAnchor * const top;
  QCPItemAnchor * const topRight;
  QCPItemAnchor * const right;
  QCPItemAnchor * const bottom;
  QCPItemAnchor * const bottomLeft;
  QCPItemAnchor * const left;
  
protected:
  enum AnchorIndex {aiTop, aiTopRight, aiRight, aiBottom, aiBottomLeft, aiLeft};
  
  // property members:
  // 속성 멤버 :
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPen mainPen() const;
  QBrush mainBrush() const;
};

/* end of 'src/items/item-rect.h' */


/* including file 'src/items/item-text.h', size 5554                         */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-rect.h'의 끝 */


/* 파일 'src / items / item-text.h'포함, 크기 5554                          */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
class QCP_LIB_DECL QCPItemText : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)
  Q_PROPERTY(QString text READ text WRITE setText)
  Q_PROPERTY(Qt::Alignment positionAlignment READ positionAlignment WRITE setPositionAlignment)
  Q_PROPERTY(Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment)
  Q_PROPERTY(double rotation READ rotation WRITE setRotation)
  Q_PROPERTY(QMargins padding READ padding WRITE setPadding)
  /// \endcond
public:
  explicit QCPItemText(QCustomPlot *parentPlot);
  virtual ~QCPItemText();
  
  // getters:
  QColor color() const { return mColor; }
  QColor selectedColor() const { return mSelectedColor; }
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  QFont font() const { return mFont; }
  QFont selectedFont() const { return mSelectedFont; }
  QString text() const { return mText; }
  Qt::Alignment positionAlignment() const { return mPositionAlignment; }
  Qt::Alignment textAlignment() const { return mTextAlignment; }
  double rotation() const { return mRotation; }
  QMargins padding() const { return mPadding; }
  
  // setters;
  void setColor(const QColor &color);
  void setSelectedColor(const QColor &color);
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  void setFont(const QFont &font);
  void setSelectedFont(const QFont &font);
  void setText(const QString &text);
  void setPositionAlignment(Qt::Alignment alignment);
  void setTextAlignment(Qt::Alignment alignment);
  void setRotation(double degrees);
  void setPadding(const QMargins &padding);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const position;
  QCPItemAnchor * const topLeft;
  QCPItemAnchor * const top;
  QCPItemAnchor * const topRight;
  QCPItemAnchor * const right;
  QCPItemAnchor * const bottomRight;
  QCPItemAnchor * const bottom;
  QCPItemAnchor * const bottomLeft;
  QCPItemAnchor * const left;
  
protected:
  enum AnchorIndex {aiTopLeft, aiTop, aiTopRight, aiRight, aiBottomRight, aiBottom, aiBottomLeft, aiLeft};
  
  // property members:
  // 속성 멤버 :
  QColor mColor, mSelectedColor;
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  QFont mFont, mSelectedFont;
  QString mText;
  Qt::Alignment mPositionAlignment;
  Qt::Alignment mTextAlignment;
  double mRotation;
  QMargins mPadding;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPointF getTextDrawPoint(const QPointF &pos, const QRectF &rect, Qt::Alignment positionAlignment) const;
  QFont mainFont() const;
  QColor mainColor() const;
  QPen mainPen() const;
  QBrush mainBrush() const;
};

/* end of 'src/items/item-text.h' */


/* including file 'src/items/item-ellipse.h', size 3868                      */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-text.h'의 끝 */


/* 파일 'src / items / item-ellipse.h'포함, 크기 3868                       */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPItemEllipse : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  /// \endcond
public:
  explicit QCPItemEllipse(QCustomPlot *parentPlot);
  virtual ~QCPItemEllipse();
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const topLeft;
  QCPItemPosition * const bottomRight;
  QCPItemAnchor * const topLeftRim;
  QCPItemAnchor * const top;
  QCPItemAnchor * const topRightRim;
  QCPItemAnchor * const right;
  QCPItemAnchor * const bottomRightRim;
  QCPItemAnchor * const bottom;
  QCPItemAnchor * const bottomLeftRim;
  QCPItemAnchor * const left;
  QCPItemAnchor * const center;
  
protected:
  enum AnchorIndex {aiTopLeftRim, aiTop, aiTopRightRim, aiRight, aiBottomRightRim, aiBottom, aiBottomLeftRim, aiLeft, aiCenter};
  
  // property members:
  // 속성 멤버 :
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPen mainPen() const;
  QBrush mainBrush() const;
};

/* end of 'src/items/item-ellipse.h' */


/* including file 'src/items/item-pixmap.h', size 4373                       */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-ellipse.h'의 끝 */


/* 'src / items / item-pixmap.h'파일을 포함하여 크기 4373                    */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPItemPixmap : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
  Q_PROPERTY(bool scaled READ scaled WRITE setScaled)
  Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ aspectRatioMode)
  Q_PROPERTY(Qt::TransformationMode transformationMode READ transformationMode)
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  /// \endcond
public:
  explicit QCPItemPixmap(QCustomPlot *parentPlot);
  virtual ~QCPItemPixmap();
  
  // getters:
  QPixmap pixmap() const { return mPixmap; }
  bool scaled() const { return mScaled; }
  Qt::AspectRatioMode aspectRatioMode() const { return mAspectRatioMode; }
  Qt::TransformationMode transformationMode() const { return mTransformationMode; }
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  
  // setters;
  void setPixmap(const QPixmap &pixmap);
  void setScaled(bool scaled, Qt::AspectRatioMode aspectRatioMode=Qt::KeepAspectRatio, Qt::TransformationMode transformationMode=Qt::SmoothTransformation);
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const topLeft;
  QCPItemPosition * const bottomRight;
  QCPItemAnchor * const top;
  QCPItemAnchor * const topRight;
  QCPItemAnchor * const right;
  QCPItemAnchor * const bottom;
  QCPItemAnchor * const bottomLeft;
  QCPItemAnchor * const left;
  
protected:
  enum AnchorIndex {aiTop, aiTopRight, aiRight, aiBottom, aiBottomLeft, aiLeft};
  
  // property members:
  // 속성 멤버 :
  QPixmap mPixmap;
  QPixmap mScaledPixmap;
  bool mScaled;
  bool mScaledPixmapInvalidated;
  Qt::AspectRatioMode mAspectRatioMode;
  Qt::TransformationMode mTransformationMode;
  QPen mPen, mSelectedPen;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void updateScaledPixmap(QRect finalRect=QRect(), bool flipHorz=false, bool flipVert=false);
  QRect getFinalRect(bool *flippedHorz=0, bool *flippedVert=0) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-pixmap.h' */


/* including file 'src/items/item-tracer.h', size 4762                       */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-pixmap.h'의 끝 */


/* 파일 'src / items / item-tracer.h'포함, 크기 4762                        */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPItemTracer : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
  Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
  Q_PROPERTY(double size READ size WRITE setSize)
  Q_PROPERTY(TracerStyle style READ style WRITE setStyle)
  Q_PROPERTY(QCPGraph* graph READ graph WRITE setGraph)
  Q_PROPERTY(double graphKey READ graphKey WRITE setGraphKey)
  Q_PROPERTY(bool interpolating READ interpolating WRITE setInterpolating)
  /// \endcond
public:
  /*!
    The different visual appearances a tracer item can have. Some styles size may be controlled with \ref setSize.
    
    \see setStyle
  */
 /* !
    추적 항목이 가질 수있는 다양한 시각적 외관. 일부 스타일 크기는 \ ref setSize로 제어 할 수 있습니다.
    
    \ see setStyle
  */
  enum TracerStyle { tsNone        ///< The tracer is not visible
                                   /// <추적 프로그램이 표시되지 않습니다.
                     ,tsPlus       ///< A plus shaped crosshair with limited size
                                   /// <크기가 제한된 더하기 모양의 십자선
                     ,tsCrosshair  ///< A plus shaped crosshair which spans the complete axis rect
                                   /// <완전한 축 rect에 걸쳐있는 플러스 모양의 십자선
                     ,tsCircle     ///< A circle
                                   /// <원
                     ,tsSquare     ///< A square
                                   /// <정사각형
                   };
  Q_ENUMS(TracerStyle)

  explicit QCPItemTracer(QCustomPlot *parentPlot);
  virtual ~QCPItemTracer();

  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  QBrush brush() const { return mBrush; }
  QBrush selectedBrush() const { return mSelectedBrush; }
  double size() const { return mSize; }
  TracerStyle style() const { return mStyle; }
  QCPGraph *graph() const { return mGraph; }
  double graphKey() const { return mGraphKey; }
  bool interpolating() const { return mInterpolating; }

  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setSelectedBrush(const QBrush &brush);
  void setSize(double size);
  void setStyle(TracerStyle style);
  void setGraph(QCPGraph *graph);
  void setGraphKey(double key);
  void setInterpolating(bool enabled);

  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  void updatePosition();

  QCPItemPosition * const position;

protected:
  // property members:
  // 속성 멤버 :
  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;
  double mSize;
  TracerStyle mStyle;
  QCPGraph *mGraph;
  double mGraphKey;
  bool mInterpolating;

  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;

  // non-virtual methods:
  // 비 가상 메소드 :
  QPen mainPen() const;
  QBrush mainBrush() const;
};
Q_DECLARE_METATYPE(QCPItemTracer::TracerStyle)

/* end of 'src/items/item-tracer.h' */


/* including file 'src/items/item-bracket.h', size 3969                      */
/* commit 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */
/* 'src / items / item-tracer.h'의 끝 */

/* 파일 'src / items / item-bracket.h', 크기 3969 포함                      */
/* 커밋 9868e55d3b412f2f89766bb482fcf299e93a0988 2017-09-04 01:56:22 +0200 */

class QCP_LIB_DECL QCPItemBracket : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  Q_PROPERTY(double length READ length WRITE setLength)
  Q_PROPERTY(BracketStyle style READ style WRITE setStyle)
  /// \endcond
public:
  /*!
    Defines the various visual shapes of the bracket item. The appearance can be further modified
    by \ref setLength and \ref setPen.
    
    \see setStyle
  */
 /* !
    브래킷 항목의 다양한 시각적 모양을 정의합니다. 외관을 추가로 수정할 수 있습니다.
    \ ref setLength와 \ ref setPen에 의해.
    
    \ see setStyle
  */

  enum BracketStyle { bsSquare  ///< A brace with angled edges
                                /// <모서리가 둥근   브레이스
                      ,bsRound  ///< A brace with round edges
                                /// <둥근 모서리가있는 중괄호
                      ,bsCurly  ///< A curly brace
                                /// <중괄호
                      ,bsCalligraphic ///< A curly brace with varying stroke width giving a calligraphic impression
/// <서예 인상을주는 다양한 스트로크 폭을 가진 중괄호
  };
  Q_ENUMS(BracketStyle)

  explicit QCPItemBracket(QCustomPlot *parentPlot);
  virtual ~QCPItemBracket();
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  double length() const { return mLength; }
  BracketStyle style() const { return mStyle; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  void setLength(double length);
  void setStyle(BracketStyle style);
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const left;
  QCPItemPosition * const right;
  QCPItemAnchor * const center;
  
protected:
  // property members:
  // 속성 멤버 :
  enum AnchorIndex {aiCenter};
  QPen mPen, mSelectedPen;
  double mLength;
  BracketStyle mStyle;
  
  // reimplemented virtual methods:
  // 구현 된 가상 메소드 :
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  // 비 가상 메소드 :
  QPen mainPen() const;
};
Q_DECLARE_METATYPE(QCPItemBracket::BracketStyle)

/* end of 'src/items/item-bracket.h' */


#endif // QCUSTOMPLOT_H

