/**
******************************************************************************
*
* @file       opmapwidget.h
* @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
* @brief      The Map Widget, this is the part exposed to the user
* @see        The GNU Public License (GPL) Version 3
* @defgroup   OPMapWidget
* @{
*
*****************************************************************************/
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#ifndef OPMAPWIDGET_H
#define OPMAPWIDGET_H

#include "../mapwidget/mapgraphicitem.h"
#include "../core/geodecoderstatus.h"
#include "../core/maptype.h"
#include "../core/languagetype.h"
#include "../core/diagnostics.h"
#include "omapconfiguration.h"
#include <QObject>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QGraphicsView>
#include "waypointitem.h"
#include "QtSvg/QGraphicsSvgItem"
#include "uavitem.h"
#include "gpsitem.h"
#include "homeitem.h"
#include "waypointlineitem.h"
#include "mapripper.h"
#include "uavtrailtype.h"
namespace mapcontrol
{
    class UAVItem;
    class GPSItem;
    class HomeItem;
    /**
    * @brief Collection of static functions to help dealing with various enums used
    *       Contains functions for enumToString conversio, StringToEnum, QStringList of enum values...
    *
    * @class Helper opmapwidget.h "opmapwidget.h"
    */

/*/ * *
    * @ 사용 된 다양한 enum을 다루는 데 도움이되는 정적 함수 모음
    * enumToString conversio, StringToEnum, QStringList for enum values ​​...에 대한 함수가 들어 있습니다.
    *
    * @class 도우미 opmapwidget.h "opmapwidget.h"
    * /*/

    class Helper
    {
    public:
        /**
         * @brief Converts from String to Type
         *
         * @param value String to convert
         * @return
         */

/*/ * *
         * @brief String에서 Type으로 변환합니다.
         *
         * @param value 변환 할 문자열
         * @ 반환
         * /*/

        static MapType::Types MapTypeFromString(QString const& value){return MapType::TypeByStr(value);}
        /**
         * @brief Converts from Type to String
         */

/*/ * *
         * @brief는 Type에서 String으로 변환합니다.
         * /*/

        static QString StrFromMapType(MapType::Types const& value){return MapType::StrByType(value);}
        /**
         * @brief Returns QStringList with string representing all the enum values
         */

/*/ * *
         * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
         * /*/

        static QStringList MapTypes(){return MapType::TypesList();}

        /**
        * @brief Converts from String to Type
        */

/*/ * *
        * @brief String에서 Type으로 변환합니다.
        * /*/

        static GeoCoderStatusCode::Types GeoCoderStatusCodeFromString(QString const& value){return GeoCoderStatusCode::TypeByStr(value);}
        /**
        * @brief Converts from Type to String
        */

/*/ * *
        * @brief는 Type에서 String으로 변환합니다.
        * /*/

        static QString StrFromGeoCoderStatusCode(GeoCoderStatusCode::Types const& value){return GeoCoderStatusCode::StrByType(value);}
        /**
        * @brief Returns QStringList with string representing all the enum values
        */

/*/ * *
        * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
        * /*/

        static QStringList GeoCoderTypes(){return GeoCoderStatusCode::TypesList();}

        /**
        * @brief Converts from String to Type
        */

/*/ * *
        * @brief String에서 Type으로 변환합니다.
        * /*/

        static internals::MouseWheelZoomType::Types MouseWheelZoomTypeFromString(QString const& value){return internals::MouseWheelZoomType::TypeByStr(value);}
        /**
        * @brief Converts from Type to String
        */

/*/ * *
        * @brief는 Type에서 String으로 변환합니다.
        * /*/

        static QString StrFromMouseWheelZoomType(internals::MouseWheelZoomType::Types const& value){return internals::MouseWheelZoomType::StrByType(value);}
        /**
        * @brief Returns QStringList with string representing all the enum values
        */

/*/ * *
        * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
        * /*/

        static QStringList MouseWheelZoomTypes(){return internals::MouseWheelZoomType::TypesList();}
        /**
        * @brief Converts from String to Type
        */

/* / * *
        * @brief String에서 Type으로 변환합니다.
        * /*/

        static core::LanguageType::Types LanguageTypeFromString(QString const& value){return core::LanguageType::TypeByStr(value);}
        /**
        * @brief Converts from Type to String
        */

/*/ * *
        * @brief는 Type에서 String으로 변환합니다.
        * /*/

        static QString StrFromLanguageType(core::LanguageType::Types const& value){return core::LanguageType::StrByType(value);}
        /**
        * @brief Returns QStringList with string representing all the enum values
        */

/*/ * *
        * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
        * /*/

        static QStringList LanguageTypes(){return core::LanguageType::TypesList();}
        /**
        * @brief Converts from String to Type
        */

/*/ * *
        * @brief String에서 Type으로 변환합니다.
        * /*/

        static core::AccessMode::Types AccessModeFromString(QString const& value){return core::AccessMode::TypeByStr(value);}
        /**
        * @brief Converts from Type to String
        */

/*/ * *
        * @brief는 Type에서 String으로 변환합니다.
        * /*/

        static QString StrFromAccessMode(core::AccessMode::Types const& value){return core::AccessMode::StrByType(value);}
        /**
        * @brief Returns QStringList with string representing all the enum values
        */

/*/ * *
        * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
        * /*/

        static QStringList AccessModeTypes(){return core::AccessMode::TypesList();}

        /**
        * @brief Converts from String to Type
        */

/*/ * *
        * @brief String에서 Type으로 변환합니다.
        * /*/

        static UAVMapFollowType::Types UAVMapFollowFromString(QString const& value){return UAVMapFollowType::TypeByStr(value);}
        /**
        * @brief Converts from Type to String
        */

/* / * *
        * @brief는 Type에서 String으로 변환합니다.
        * /*/

        static QString StrFromUAVMapFollow(UAVMapFollowType::Types const& value){return UAVMapFollowType::StrByType(value);}
        /**
        * @brief Returns QStringList with string representing all the enum values
        */

/*    / * *
        * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
        * /*/

        static QStringList UAVMapFollowTypes(){return UAVMapFollowType::TypesList();}
        /**
         * @brief Converts from String to Type
         */

/*/ * *
         * @brief String에서 Type으로 변환합니다.
         * /*/

        static UAVTrailType::Types UAVTrailTypeFromString(QString const& value){return UAVTrailType::TypeByStr(value);}
        /**
         * @brief Converts from Type to String
         */

/*/ * *
        * @brief는 Type에서 String으로 변환합니다.
        * /*/

        static QString StrFromUAVTrailType(UAVTrailType::Types const& value){return UAVTrailType::StrByType(value);}
        /**
         * @brief Returns QStringList with string representing all the enum values
         */

/*  / * *
         * @brief 모든 열거 형 값을 나타내는 문자열로 QStringList를 반환합니다.
         * /*/

        static QStringList UAVTrailTypes(){return UAVTrailType::TypesList();}
    };

    class OPMapWidget:public QGraphicsView
    {
        Q_OBJECT

        // Q_PROPERTY(int MaxZoom READ MaxZoom WRITE SetMaxZoom)

/*      // Q_PROPERTY (int MaxZoom 읽기 MaxZoom WRITE SetMaxZoom)*/

        Q_PROPERTY(int MinZoom READ MinZoom WRITE SetMinZoom)
                Q_PROPERTY(bool ShowTileGridLines READ ShowTileGridLines WRITE SetShowTileGridLines)
                Q_PROPERTY(double Zoom READ ZoomTotal WRITE SetZoom)
                Q_PROPERTY(qreal Rotate READ Rotate WRITE SetRotate)
                Q_ENUMS(internals::MouseWheelZoomType::Types)
                Q_ENUMS(core::GeoCoderStatusCode::Types)

    public:
                QSize sizeHint() const;
        /**
        * @brief Constructor
        *
        * @param parent parent widget
        * @param config pointer to configuration classed to be used
        * @return
        */

/*      / * *
        * @brief 생성자
        *
        * @param 부모 부모 위젯
        * @param 설정 사용되는 클래스의 구성에의 포인터
        * @ 반환
        * /*/

        OPMapWidget(QWidget *parent=0,Configuration *config=new Configuration);
        ~OPMapWidget();

        /**
        * @brief Returns true if map is showing gridlines
        *
        * @return bool
        */

/*       / * *
        * @ brief지도가 눈금 선을 표시하면 true를 반환합니다.
        *
        * @return bool
        * /*/

        bool ShowTileGridLines()const {return map->showTileGridLines;}

        /**
        * @brief Defines if map is to show gridlines
        *
        * @param value
        * @return
        */

/* / * *
        * @brief지도가 눈금 선을 표시할지 정의합니다.
        *
        * @param 값
        * @ 반환
        * /*/

        void SetShowTileGridLines(bool const& value){map->showTileGridLines=value;map->update();}

        /**
        * @brief Returns the maximum zoom for the map
        *
        */

/*  / * *
        * @brief지도의 최대 줌을 반환합니다.
        *
        * /*/

        int MaxZoom()const{return map->MaxZoom();}

        //  void SetMaxZoom(int const& value){map->maxZoom = value;}

        /**
        * @brief
        *
        */
        int MinZoom()const{return map->minZoom;}
        /**
        * @brief
        *
        * @param value
        */
        void SetMinZoom(int const& value){map->minZoom = value;}

        internals::MouseWheelZoomType::Types GetMouseWheelZoomType(){return  map->core->GetMouseWheelZoomType();}
        void SetMouseWheelZoomType(internals::MouseWheelZoomType::Types const& value){map->core->SetMouseWheelZoomType(value);}
        //  void SetMouseWheelZoomTypeByStr(const QString &value){map->core->SetMouseWheelZoomType(internals::MouseWheelZoomType::TypeByStr(value));}
        //  QString GetMouseWheelZoomTypeStr(){return map->GetMouseWheelZoomTypeStr();}

        internals::RectLatLng SelectedArea()const{return  map->selectedArea;}
        void SetSelectedArea(internals::RectLatLng const& value){ map->selectedArea = value;this->update();}

        bool CanDragMap()const{return map->CanDragMap();}
        void SetCanDragMap(bool const& value){map->SetCanDragMap(value);}

        internals::PointLatLng CurrentPosition()const{return map->core->CurrentPosition();}
        void SetCurrentPosition(internals::PointLatLng const& value){map->core->SetCurrentPosition(value);}

        double ZoomReal(){return map->Zoom();}
        double ZoomDigi(){return map->ZoomDigi();}
        double ZoomTotal(){return map->ZoomTotal();}

        qreal Rotate(){return map->rotation;}
        void SetRotate(qreal const& value);

        void ReloadMap(){map->ReloadMap(); map->resize();}

        GeoCoderStatusCode::Types SetCurrentPositionByKeywords(QString const& keys){return map->SetCurrentPositionByKeywords(keys);}

        bool UseOpenGL(){return useOpenGL;}
        void SetUseOpenGL(bool const& value);

        MapType::Types GetMapType(){return map->core->GetMapType();}
        void SetMapType(MapType::Types const& value){map->lastimage=QImage(); map->core->SetMapType(value);}

        bool isStarted(){return map->core->isStarted();}

        Configuration* configuration;

        internals::PointLatLng currentMousePosition();

        void SetFollowMouse(bool const& value){followmouse=value;this->setMouseTracking(followmouse);}
        bool FollowMouse(){return followmouse;}

        internals::PointLatLng GetFromLocalToLatLng(QPointF p) {return map->FromLocalToLatLng(p.x(),p.y());}

        /** @brief Convert meters to pixels */

/*
        / * * @brief 미터를 픽셀로 변환 * /*/

        float metersToPixels(double meters);

        /** @brief Return the bearing from one point to another .. in degrees */

/*        / * * Brief 한 지점에서 다른 지점으로 베어링을 반환합니다. 각도로 표시 * /*/

        double bearing(internals::PointLatLng from, internals::PointLatLng to);

        /** @brief Return a destination lat/lon point given a source lat/lon point and the bearing and distance from the source point */

/*        / * * @brief 소스 위도 / 경도 지점과 소스 지점으로부터의 방위 및 거리가 주어지면 목적지 위도 / 경도 점을 반환합니다. * /*/

        internals::PointLatLng destPoint(internals::PointLatLng source, double bear, double dist);

        /**
        * @brief Creates a new WayPoint on the center of the map
        *
        * @return WayPointItem a pointer to the WayPoint created
        */

/*  / * *
        * @brief지도의 중심에 새로운 WayPoint를 만듭니다.
        *
        * @return WayPointItem 생성 된 WayPoint에 대한 포인터
        * /*/

        WayPointItem* WPCreate();
        /**
        * @brief Creates a new WayPoint
        *
        * @param item the WayPoint to create
        */

/* / * *
        * @brief 새로운 WayPoint를 만듭니다.
        *
        * @param 항목 작성하는 WayPoint
        * /*/

        void WPCreate(WayPointItem* item);
        /**
        * @brief Creates a new WayPoint
        *
        * @param id the system (MAV) id this waypoint belongs to
        * @param item the WayPoint to create
        */

/*/ * *
        * @brief 새로운 WayPoint를 만듭니다.
        *
        * @param id이 경유지가 속한 시스템 (MAV) id
        * @param 항목 작성하는 WayPoint
        * /*/

        void WPCreate(int id, WayPointItem* item);
        /**
        * @brief Creates a new WayPoint
        *
        * @param coord the coordinates in LatLng of the WayPoint
        * @param altitude the Altitude of the WayPoint
        * @return WayPointItem a pointer to the WayPoint created
        */

/*       / * *
        * @brief 새로운 WayPoint를 만듭니다.
        *
        * @param은 WayPoint의 LatLng 좌표를 조정합니다.
        * @param 고도 WayPoint의 고도
        * @return WayPointItem 생성 된 WayPoint에 대한 포인터
        * /*/

        WayPointItem* WPCreate(internals::PointLatLng const& coord,int const& altitude);
        /**
        * @brief Creates a new WayPoint
        *
        * @param coord the coordinates in LatLng of the WayPoint
        * @param altitude the Altitude of the WayPoint
        * @param description the description of the WayPoint
        * @return WayPointItem a pointer to the WayPoint created
        */

/*       / * *
        * @brief 새로운 WayPoint를 만듭니다.
        *
        * @param은 WayPoint의 LatLng 좌표를 조정합니다.
        * @param 고도 WayPoint의 고도
        * @param 설명 WayPoint의 설명
        * @return WayPointItem 생성 된 WayPoint에 대한 포인터
        * /*/

        WayPointItem* WPCreate(internals::PointLatLng const& coord,int const& altitude, QString const& description);
        /**
        * @brief Inserts a new WayPoint on the specified position
        *
        * @param position index of the WayPoint
        * @return WayPointItem a pointer to the WayPoint created
        */

/*     / * *
        * @brief 지정된 위치에 새로운 WayPoint를 삽입합니다.
        *
        WayPoint의 @param 위치 인덱스
        * @return WayPointItem 생성 된 WayPoint에 대한 포인터
        * /*/

        WayPointItem* WPInsert(int const& position);
        /**
        * @brief Inserts a new WayPoint on the specified position
        *
        * @param item the WayPoint to Insert
        * @param position index of the WayPoint
        */

/*   / * *
        * @brief 지정된 위치에 새로운 WayPoint를 삽입합니다.
        *
        * @param 항목 삽입 할 WayPoint 항목
        WayPoint의 @param 위치 인덱스
        * /*/

        void WPInsert(WayPointItem* item,int const& position);
        /**
        * @brief Inserts a new WayPoint on the specified position
        *
        * @param coord the coordinates in LatLng of the WayPoint
        * @param altitude the Altitude of the WayPoint
        * @param position index of the WayPoint
        * @return WayPointItem a pointer to the WayPoint Inserted
        */

/*   / * *
        * @brief 지정된 위치에 새로운 WayPoint를 삽입합니다.
        *
        * @param은 WayPoint의 LatLng 좌표를 조정합니다.
        * @param 고도 WayPoint의 고도
        WayPoint의 @param 위치 인덱스
        * @return WayPointItem 삽입 된 WayPoint에 대한 포인터
        * /*/

        WayPointItem* WPInsert(internals::PointLatLng const& coord,int const& altitude,int const& position);
        /**
        * @brief Inserts a new WayPoint on the specified position
        *
        * @param coord the coordinates in LatLng of the WayPoint
        * @param altitude the Altitude of the WayPoint
        * @param description the description of the WayPoint
        * @param position index of the WayPoint
        * @return WayPointItem a pointer to the WayPoint Inserted
        */

/* / * *
        * @brief 지정된 위치에 새로운 WayPoint를 삽입합니다.
        *
        * @param은 WayPoint의 LatLng 좌표를 조정합니다.
        * @param 고도 WayPoint의 고도
        * @param 설명 WayPoint의 설명
        WayPoint의 @param 위치 인덱스
        * @return WayPointItem 삽입 된 WayPoint에 대한 포인터
        * /*/

        WayPointItem* WPInsert(internals::PointLatLng const& coord,int const& altitude, QString const& description,int const& position);

        /**
        * @brief Deletes the WayPoint
        *
        * @param item the WayPoint to delete
        */

/*  / * *
        * @brief WayPoint를 삭제합니다.
        *
        * @param 항목 삭제할 WayPoint
        * /*/

        void WPDelete(WayPointItem* item);
        /**
        * @brief deletes all WayPoints
        *
        */

/*  / * *
        * @brief는 모든 WayPoint를 삭제합니다.
        *
        * /*/

        void WPDeleteAll();
        /**
        * @brief Returns the currently selected WayPoints
        *
        * @return @return QList<WayPointItem *>
        */

/*  / * *
        * @brief 현재 선택된 WayPoint를 반환합니다.
        *
        * @return @return QList <WayPointItem *>
        * /*/

        QList<WayPointItem*> WPSelected();

        /**
        * @brief Renumbers the WayPoint and all others as needed
        *
        * @param item the WayPoint to renumber
        * @param newnumber the WayPoint's new number
        */

/*
        / * *
        * @brief WayPoint 및 필요에 따라 다른 모든 항목 번호를 다시 매 깁니다.
        *
        * @param 항목 번호를 다시 매기는 WayPoint
        * @param newnumber 웨이 포인트의 새 번호
        * /*/

        void WPRenumber(WayPointItem* item,int const& newnumber);

        void SetShowCompass(bool const& value);

        // FIXME XXX Move to protected namespace
        UAVItem* UAV;
        QMap<int, QGraphicsItemGroup*> waypointLines;
        GPSItem* GPS;
        HomeItem* Home;
        // END OF FIXME XXX

        UAVItem* AddUAV(int id);
        void AddUAV(int id, UAVItem* uav);
        /** @brief Deletes UAV and its waypoints from map */
        void DeleteUAV(int id);
        UAVItem* GetUAV(int id);
        const QList<UAVItem*> GetUAVS();
        QGraphicsItemGroup* waypointLine(int id);
        void SetShowUAV(bool const& value);
        bool ShowUAV()const{return showuav;}
        void SetShowHome(bool const& value);
        bool ShowHome()const{return showhome;}
        void SetShowDiagnostics(bool const& value);
        void SetUavPic(QString UAVPic);
        QMap<int, UAVItem*> UAVS;

    private:
        internals::Core *core;
        QGraphicsScene mscene;
        bool useOpenGL;
        GeoCoderStatusCode x;
        MapType y;
        core::AccessMode xx;
        internals::PointLatLng currentmouseposition;
        bool followmouse;
        QGraphicsSvgItem *compass;
        bool showuav;
        bool showhome;
        QTimer * diagTimer;
        bool showDiag;
        QGraphicsTextItem * diagGraphItem;

    private slots:
        void diagRefresh();
        //   WayPointItem* item;//apagar
    protected:
        MapGraphicItem *map;
        void resizeEvent(QResizeEvent *event);
        void showEvent ( QShowEvent * event );
        void closeEvent(QCloseEvent *event);
        void mouseMoveEvent ( QMouseEvent * event );
        void ConnectWP(WayPointItem* item);
        //    private slots:
    signals:
        void zoomChanged(double zoomt,double zoom, double zoomd);
        /**
        * @brief Notify connected widgets about new map zoom
        */

/*    / * *
        * @brief 연결된 위젯에 새지도 줌에 대해 알립니다.
        * /*/

        void zoomChanged(int newZoom);
        /**
        * @brief fires when one of the WayPoints numbers changes (not fired if due to a auto-renumbering)
        *
        * @param oldnumber WayPoint old number
        * @param newnumber WayPoint new number
        * @param waypoint a pointer to the WayPoint that was renumbered
        */

/*/ * *
        * @brief는 WayPoint 번호 중 하나가 변경되면 작동합니다 (자동 번호 재 지정으로 인해 실행되지 않음).
        *
        * @ 매개 변수 oldNumber WayPoint 이전 번호
        * @ 매개 변수 newnumber WayPoint 새 번호
        * @param 웨이 포인트 넘버링 된 웨이 포인트에 대한 포인터
        * /*/

        void WPNumberChanged(int const& oldnumber,int const& newnumber,WayPointItem* waypoint);
        /**
        * @brief Fired when the description, altitude or coordinates of a WayPoint changed
        *
        * @param waypoint a pointer to the WayPoint
        */

/*   / * *
        * @brief WayPoint의 설명, 고도 또는 좌표가 변경되면 시작됩니다.
        *
        * @param waypoint WayPoint에 대한 포인터
        * /*/

        void WPValuesChanged(WayPointItem* waypoint);
        /**
        * @brief Fires when a new WayPoint is inserted
        *
        * @param number new WayPoint number
        * @param waypoint WayPoint inserted
        */

/*   / * *
        * @brief 새로운 WayPoint가 삽입되면 시작됩니다.
        *
        * @param 번호 새로운 WayPoint 번호
        * 웨이 포인트 삽입 된 @ 매개 변수 웨이 포인트
        * /*/

        void WPReached(WayPointItem* waypoint);
        /**
        * @brief Fires when a new WayPoint is inserted
        *
        * @param number new WayPoint number
        * @param waypoint WayPoint inserted
        */

/* / * *
        * @brief 새로운 WayPoint가 삽입되면 시작됩니다.
        *
        * @param 번호 새로운 WayPoint 번호
        * 웨이 포인트 삽입 된 @ 매개 변수 웨이 포인트
        * /*/

        void WPInserted(int const& number,WayPointItem* waypoint);
        /**
        * @brief Fires When a WayPoint is deleted
        *
        * @param number number of the deleted WayPoint
        */

/*        / * *
        * @brief WayPoint가 삭제 될 때 발생합니다.
        *
        * @param 삭제 된 WayPoint의 번호 번호
        * /*/

        void WPDeleted(int const& number);
        /**
        * @brief Fires When a WayPoint is Reached
        *
        * @param number number of the Reached WayPoint
        */

/*       / * *
        WayPoint에 도달하면 * 화재가 발생합니다.
        *
        * @param 도달 한 WayPoint의 번호 번호
        * /*/

        void UAVReachedWayPoint(int const& waypointnumber,WayPointItem* waypoint);
        /**
        * @brief Fires When the UAV lives the safety bouble
        *
        * @param position the position of the UAV
        */

/*   / * *
        * @brief 화재 UAV가 안전을 위해 살 때 bouble
        *
        * @param 위치 UAV의 위치
        * /*/

        void UAVLeftSafetyBouble(internals::PointLatLng const& position);

        /**
        * @brief Fires when map position changes
        *
        * @param point the point in LatLng of the new center of the map
        */

/*    / * *
        * @brief지도 위치가 변경되면 실행됩니다.
        *
        * @param지도의 새 중심이 LatLng에있는 점을 가리킴
        * /*/

        void OnCurrentPositionChanged(internals::PointLatLng point);
        /**
        * @brief Fires when there are no more tiles to load
        *
        */

/*  / * *
        * @brief로드 할 타일이 더 이상 없을 때 발생합니다.
        *
        * /*/

        void OnTileLoadComplete();
        /**
        * @brief Fires when tiles loading begins
        *
        */

/* / * *
        * @brief 타일 로딩이 시작될 때 발생합니다.
        *
        * /*/

        void OnTileLoadStart();
        /**
        * @brief Fires when the map is dragged
        *
        */

/*   / * *
        * @brief지도가 드래그되면 실행됩니다.
        *
        * /*/

        void OnMapDrag();
        /**
        * @brief Fires when map zoom changes
        *
        */

/*   / * *
        * @brief지도 확대 / 축소가 변경되면 실행됩니다.
        *
        * /*/

        void OnMapZoomChanged();
        /**
        * @brief Fires when map type changes
        *
        * @param type The maps new type
        */

/*  / * *
        * @brief지도 유형이 변경되면 실행됩니다.
        *
        파라미터 : map - 새로운 형태의 맵
        * /*/

        void OnMapTypeChanged(MapType::Types type);
        /**
        * @brief Fires when an error ocurred while loading a tile
        *
        * @param zoom tile zoom
        * @param pos tile position
        */

/*  / * *
        * @brief 타일을로드하는 동안 오류가 발생했을 때 발생합니다.
        *
        * @param 줌 타일 줌
        * @param pos의 타일 위치
        * /*/

        void OnEmptyTileError(int zoom, core::Point pos);
        /**
        * @brief Fires when the number of tiles in the load queue changes
        *
        * @param number the number of tiles still in the queue
        */

/*  / * *
        * @brief로드 대기열의 타일 수가 변경되면 실행됩니다.
        *
        * @param number 큐에있는 타일의 수
        * /*/

        void OnTilesStillToLoad(int number);
    public slots:
        /**
        * @brief Ripps the current selection to the DB
        */

/*    / * *
        * @brief DB에 현재 선택 항목을 리핑합니다.
        * /*/

        void RipMap();

        /**
        * @brief Sets the map zoom level
        */

/*   / * *
        * @brief지도 줌 레벨을 설정합니다.
        * /*/

        void SetZoom(double const& value){map->SetZoom(value);}
        /**
        * @brief Sets the map zoom level
        */

/* / * *
        * @brief지도 줌 레벨을 설정합니다.
        * /*/

        void SetZoom(int const& value){map->SetZoom(value);}

        /**
        * @brief Notify external widgets about map zoom change
        */

/*
        / * *
        * @brief 외부 위젯에게지도 확대 / 축소 변경에 대해 알립니다.
        * /*/

        void emitMapZoomChanged()
        {
            emit zoomChanged(ZoomReal());
        }

    };
}
#endif // OPMAPWIDGET_H
