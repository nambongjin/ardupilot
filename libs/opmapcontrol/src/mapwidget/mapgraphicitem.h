/**
******************************************************************************
*
* @file       mapgraphicitem.h
* @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
* @brief      The main graphicsItem used on the widget, contains the map and map logic
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
#ifndef MAPGRAPHICITEM_H
#define MAPGRAPHICITEM_H

#include <QGraphicsItem>
#include "../internals/core.h"
//#include "../internals/point.h"
#include "../core/diagnostics.h"
#include "omapconfiguration.h"
#include <QtGui>
#include <QTransform>
#include <QWidget>
#include <QBrush>
#include <QFont>
#include <QObject>

namespace mapcontrol
{
    class OPMapWidget;
    /**
    * @brief The main graphicsItem used on the widget, contains the map and map logic
    *
    * @class MapGraphicItem mapgraphicitem.h "mapgraphicitem.h"
    */

/*/ * *
    * @brief 위젯에서 사용되는 메인 graphicsItem에는지도와지도 논리가 포함되어 있습니다.
    *
    * @class MapGraphicItem mapgraphicitem.h "mapgraphicitem.h"
    * /*/

    class MapGraphicItem:public QObject,public QGraphicsItem
    {
        friend class mapcontrol::OPMapWidget;
        Q_OBJECT
        Q_INTERFACES(QGraphicsItem)
    public:


        /**
        * @brief Contructer
        *
        * @param core
        * @param configuration the configuration to be used
        * @return
        */

/*/ * *
        * @brief Contructer
        *
        * @param core
        파라미터 : configuration - 사용하는 설정
        * @ 반환
        * /*/

        MapGraphicItem(internals::Core *core,Configuration *configuration);
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

        QSize sizeHint()const;
        /**
        * @brief Convertes LatLong coordinates to local item coordinates
        *
        * @param point LatLong point to be converted
        * @return core::Point Local item point
        */

/*/ * *
        * @brief LatLong 좌표를 로컬 항목 좌표로 변환합니다.
        *
        * @param point 변환 될 LatLong 포인트
        * @return core :: Point 로컬 항목 포인트
        * /*/

        core::Point FromLatLngToLocal(internals::PointLatLng const& point);
        /**
        * @brief Converts from local item coordinates to LatLong point
        *
        * @param x x local coordinate
        * @param y y local coordinate
        * @return internals::PointLatLng LatLng coordinate
        */

/*/ * *
        * @brief 로컬 항목 좌표에서 LatLong 점으로 변환합니다.
        *
        * @param xx 로컬 좌표
        * @param yy 로컬 좌표
        * @return internals :: PointLatLng LatLng 좌표
        * /*/

        internals::PointLatLng FromLocalToLatLng(int x, int y);
        /**
        * @brief Converts from meters at one location to pixels
        *
        * @param meters Distance to convert
        * @param coord Coordinate close to the distance measure
        * @return float Distance in pixels
        */

/* / * *
        * @brief 한 위치의 미터에서 픽셀로 변환합니다.
        *
        * @param meters 변환 할 거리
        * @param coord 거리 측정에 가까운 좌표
        * @return float 픽셀 단위의 거리
        * /*/

        float metersToPixels(double meters, internals::PointLatLng coord);
        /**
        * @brief Returns true if map is being dragged
        *
        * @return
        */

/*/ * *
        맵이 드래그되고있는 경우는 true를 돌려줍니다.
        *
        * @ 반환
        * /*/

        bool IsDragging()const{return core->IsDragging();}

        QImage lastimage;
//        QPainter* imagePainter;
        core::Point lastimagepoint;
        void paintImage(QPainter* painter);
        void ConstructLastImage(int const& zoomdiff);
        internals::PureProjection* Projection()const{return core->Projection();}
        double Zoom();
        double ZoomDigi();
        double ZoomTotal();

        /**
        * @brief The area currently selected by the user
        *
        * @return The rectangle in lat/lon coordinates currently selected
        */

/*/ * *
        * @ brief 사용자가 현재 선택한 영역
        *
        * @return 현재 선택된 위도 / 경도 좌표의 사각형
        * /*/

        internals::RectLatLng SelectedArea()const{return selectedArea;}

    public slots:
        void SetSelectedArea(internals::RectLatLng const& value){selectedArea = value;this->update();}

    protected:
        void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
        void mousePressEvent ( QGraphicsSceneMouseEvent * event );
        void wheelEvent ( QGraphicsSceneWheelEvent * event );
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        bool IsMouseOverMarker()const{return isMouseOverMarker;}

        /**
        * @brief Returns current map zoom
        *
        * @return int Current map zoom
        */

/*/ * *
        * @brief 현재지도 줌을 반환합니다.
        *
        * @return int 현재지도 확대 / 축소
        * /*/

        int ZoomStep()const;
        /**
        * @brief Sets map zoom
        *
        * @param value zoom value
        */

/*/ * *
        * @brief 세트지도 줌
        *
        * @param 값 줌 값
        * /*/

        void SetZoomStep(int const& value);

        /**
        * @brief Ask Stacey
        *
        * @param value
        */

/*/ * *
        * @brief 스테이시에게 묻기
        *
        * @param 값
        * /*/

        void SetShowDragons(bool const& value);
    private:
        bool showDragons;
        bool SetZoomToFitRect(internals::RectLatLng const& rect);
        internals::Core *core;
        Configuration *config;
        bool showTileGridLines;
        qreal MapRenderTransform;
        void DrawMap2D(QPainter *painter);
        /**
        * @brief Maximum possible zoom
        *
        * @var maxZoom
        */

/*/ * *
        * 최대 가능한 줌
        *
        * @var maxZoom
        * /*/

        int maxZoom;
        /**
        * @brief Minimum possible zoom
        *
        * @var minZoom
        */



/*/ * *
        * 가능한 최소 줌
        *
        * @var minZoom
        * /*/
/**/

        int minZoom;
        internals::RectLatLng selectedArea;
        internals::PointLatLng selectionStart;
        internals::PointLatLng selectionEnd;
        double zoomReal;
        qreal rotation;
        double zoomDigi;
        QRectF maprect;
        bool isSelected;
        bool isMouseOverMarker;
        QPixmap dragons;
        void SetIsMouseOverMarker(bool const& value){isMouseOverMarker = value;}


        /**
        * @brief Creates a rectangle that represents the "view" of the cuurent map, to compensate
        *       rotation
        *
        * @param rect original rectangle
        * @param angle angle of rotation
        * @return QRectF
        */

/*/ * *
        * @brief 보정하기 위해 cuurent 맵의 "보기"를 나타내는 사각형을 만듭니다.
        * 회전
        *
        * @param rect의 원의 구형
        * @param 회전 각도
        * @return QRectF
        * /*/

        QRectF boundingBox(QRectF const& rect, qreal const& angle);
        /**
        * @brief Returns the maximum allowed zoom
        *
        * @return int
        */

/*/ * *
        * @brief 최대 허용 줌을 반환합니다.
        *
        * @return int
        * /*/

        int MaxZoom()const{return core->MaxZoom();}
        /**
        * @brief Returns the minimum allowed zoom
        *
        * @return int
        */

/*/ * *
        * @brief 허용되는 최소 줌을 반환합니다.
        *
        * @return int
        * /*/

        int MinZoom()const{return minZoom;}
        internals::MouseWheelZoomType::Types GetMouseWheelZoomType(){return core->GetMouseWheelZoomType();}
        internals::RectLatLng BoundsOfMap;
        void Offset(int const& x, int const& y);
        bool CanDragMap()const{return core->CanDragMap;}
        void SetCanDragMap(bool const& value){core->CanDragMap = value;}

        void SetZoom(double const& value);
        void mapRotate ( qreal angle );
        void start();
        void  ReloadMap(){core->ReloadMap();}
        GeoCoderStatusCode::Types SetCurrentPositionByKeywords(QString const& keys){return core->SetCurrentPositionByKeywords(keys);}
        MapType::Types GetMapType(){return core->GetMapType();}
        void SetMapType(MapType::Types const& value){core->SetMapType(value);}
    private slots:
        void Core_OnNeedInvalidation();
        void ChildPosRefresh();
    public slots:
        /**
        * @brief To be called when the scene size changes
        *
        * @param rect
        */

/*/ * *
        * @brief 장면 크기가 변경 될 때 호출됩니다.
        *
        * @param rect
        * /*/

        void resize ( QRectF const &rect=QRectF() );
    signals:
        /**
        * @brief Fired when the current zoom is changed
        *
        * @param zoom
        */

/*/ * *
        * @brief 현재 줌이 변경되면 시작됩니다.
        *
        * @param 줌
        * /*/

        void zoomChanged(double zoomtotal,double zoomreal,double zoomdigi);

        /**
        * @brief Fired when map changes in any visible way
        */

/*/ * *
        * @brief지도가 눈에 보이는대로 바뀌면 시작됩니다.
        * /*/

        void mapChanged();
    };
}
#endif // MAPGRAPHICITEM_H
