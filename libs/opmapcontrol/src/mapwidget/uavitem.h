/**
******************************************************************************
*
* @file       uavitem.h
* @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
* @brief      A graphicsItem representing a WayPoint
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
#ifndef UAVITEM_H
#define UAVITEM_H

#include <QTime>
#include "graphicsitem.h"
#include "graphicsusertypes.h"
#include "uavmapfollowtype.h"
#include "uavtrailtype.h"

namespace mapcontrol
{
    class WayPointItem;
    /**
* @brief A QGraphicsItem representing the UAV
*
* @class UAVItem uavitem.h "mapwidget/uavitem.h"
*/

/*   / * *
* @brief UAV를 나타내는 QGraphicsItem
*
* @class UAVItem uavitem.h "mapwidget / uavitem.h"
* /*/

    class UAVItem : public GraphicsItem
    {
        Q_OBJECT
        Q_INTERFACES(QGraphicsItem)
    public:
        enum { Type = usertypes::UAVITEM };
        UAVItem(MapGraphicItem* map, OPMapWidget* parent, QString uavPic=QString::fromUtf8(":/uavs/images/mapquad.png"));
        ~UAVItem();
        /**
        * @brief Sets the UAV position
        *
        * @param position LatLng point
        * @param altitude altitude in meters
        */

/*       / * *
        * @brief UAV 위치를 설정합니다.
        *
        * @param 위치 LatLng 포인트
        * @ 고도 고도 (미터)
        * /*/

        void SetUAVPos(internals::PointLatLng const& position,int const& altitude, QColor const& color=QColor(Qt::red));
        /**
        * @brief Sets the UAV heading
        *
        * @param value heading angle (north=0deg)
        */

/*  / * *
        * @brief UAV 제목을 설정합니다.
        *
        * @param 값 방위각 (북쪽 = 0도)
        * /*/

        void SetUAVHeading(qreal const& value);
        /**
        * @brief Returns the UAV position
        *
        * @return internals::PointLatLng
        */

/*     / * *
        * @brief UAV 위치를 반환합니다.
        *
        * @return 내부 :: PointLatLng
        * /*/

        internals::PointLatLng UAVPos()const{return coord;}
        /**
        * @brief Sets the Map follow type
        *
        * @param value can be "none"(map doesnt follow UAV), "CenterMap"(map moves to keep UAV centered) or "CenterAndRotateMap"(map moves and rotates to keep UAV centered and straight)
        */

/* / * *
        * @brief지도 팔로우 유형을 설정합니다.
        *
        * @param 값은 "none"(지도가 UAV를 따르지 않음), "CenterMap"(UAV를 중앙으로 유지하기 위해 이동하는지도) 또는 "CenterAndRotateMap"(UAV를 중앙에두고 직선으로 유지하기 위해 이동 및 회전)
        * /*/

        void SetMapFollowType(UAVMapFollowType::Types const& value){mapfollowtype=value;}
        /**
        * @brief Sets the trail type
        *
        * @param value can be "NoTrail"(no trail is plotted), "ByTimeElapsed"(a trail point is plotted each TrailTime()) or ByDistance(a trail point is plotted if the distance between the UAV and the last trail point is bigger than TrailDistance())
        */

/*    / * *
        * @brief 트레일 유형을 설정합니다.
        *
        * @param 값은 "NoTrail"(트레일 없음), "ByTimeElapsed"(트레일 점은 각 TrailTime ()) 또는 ByDistance (UAV와 마지막 트레일 점 사이의 거리가 TrailDistance ()보다 큼)
        * /*/

        void SetTrailType(UAVTrailType::Types const& value);
        /**
        * @brief Returns the map follow method used
        *
        * @return UAVMapFollowType::Types
        */

/*   / * *
        * @brief 사용 된지도 팔로우 메서드를 반환합니다.
        *
        * @return UAVMapFollowType :: Types
        * /*/

        UAVMapFollowType::Types GetMapFollowType()const{return mapfollowtype;}
        /**
        * @brief Returns the UAV trail type. It can be plotted by time elapsed or distance
        *
        * @return UAVTrailType::Types
        */

/*  / * *
        * @brief UAV 트레일 유형을 반환합니다. 시간 경과 또는 거리에 따라 플롯 될 수 있습니다.
        *
        * @return UAVTrailType :: Types
        * /*/



        UAVTrailType::Types GetTrailType()const{return trailtype;}

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget);
        void RefreshPos();
        QRectF boundingRect() const;
        /**
        * @brief Sets the trail time to be used if TrailType is ByTimeElapsed
        *
        * @param seconds the UAV trail time elapsed value. If the trail type is time elapsed
        *        a trail point will be plotted each "value returned" seconds.
        */

/*    / * *
        * @brief TrailType이 ByTimeElapsed 일 때 사용할 트레 일 시간을 설정합니다.
        *
        * @param 초 UAV 트레일 시간 경과 값. 트레일 유형이 시간 경과하면
        * 트레일 포인트는 각 "값 반환"초로 표시됩니다.
        * /*/

        void SetTrailTime(int const& seconds){trailtime=seconds;}
        /**
        * @brief Returns the UAV trail time elapsed value. If the trail type is time elapsed
        *        a trail point will be plotted each "value returned" seconds.
        *
        * @return int
        */

/* / * *
        * @brief UAV 트레일 시간 경과 값을 반환합니다. 트레일 유형이 시간 경과하면
        * 트레일 포인트는 각 "값 반환"초로 표시됩니다.
        *
        * @return int
        * /*/

        int TrailTime()const{return trailtime;}
        /**
        * @brief Sets the trail distance to be used if TrailType is ByDistance
        *
        * @param distance the UAV trail plot distance.
        *        If the trail type is ByDistance a trail dot is plotted if
        *        the distance between the current UAV position and the last trail point
        *        is bigger than the returned value
        */

/*   / * *
        * @brief TrailType이 ByDistance 인 경우 사용할 트레일 거리를 설정합니다.
        *
        * @param distance UAV 트레일 플롯 거리.
        * 트레일 타입이 ByDistance 인 경우 트레일 도트가 그려집니다.
        * 현재 UAV 위치와 마지막 트레일 지점 사이의 거리
        * 반환 값보다 큽니다.
        * /*/

        void SetTrailDistance(int const& distance){traildistance=distance;}
        /**
        * @brief Returns the UAV trail plot distance.
        *        If the trail type is distance diference a trail dot is plotted if
        *        the distance between the current UAV position and the last trail point
        *        is bigger than the returned value
        *
        * @return int
        */

/*        / * *
        * @brief UAV 트레일 플롯 거리를 반환합니다.
        * 트레일 유형이 거리 차이 인 경우 트레일 점은
        * 현재 UAV 위치와 마지막 트레일 지점 사이의 거리
        * 반환 값보다 큽니다.
        *
        * @return int
        * /*/

        int TrailDistance()const{return traildistance;}
        /**
        * @brief Returns true if UAV trail is shown
        *
        * @return bool
        */

/*    / * *
        * @ brief UAV 트레일이 표시되면 true를 반환합니다.
        *
        * @return bool
        * /*/

        bool ShowTrail()const{return showtrail;}
        /**
        * @brief Returns true if UAV trail line is shown
        *
        * @return bool
        */
/*    / * *
        * @ brief UAV 트레일 줄이 표시되면 true를 반환합니다.
        *
        * @return bool
        * /
*/

        bool ShowTrailLine()const{return showtrailline;}
        /**
        * @brief Used to define if the UAV displays a trail
        *
        * @param value
        */
/* / * *
        * @brief UAV가 흔적을 표시하는지 정의하는 데 사용됩니다.
        *
        * @param 값
        * /
*/

        void SetShowTrail(bool const& value);
        /**
        * @brief Used to define if the UAV displays a trail line
        *
        * @param value
        */
/*/ * *
        * @brief UAV가 트레일 선을 표시하는지 정의하는 데 사용됩니다.
        *
        * @param 값
        * /
*/

        void SetShowTrailLine(bool const& value);
        /**
        * @brief Deletes all the trail points
        */

/*
/ * *
        * @brief UAV가 트레일 선을 표시하는지 정의하는 데 사용됩니다.
        *
        * @param 값
        * /
*/

        void DeleteTrail()const;
        /**
        * @brief Returns true if the UAV automaticaly sets WP reached value (changing its color)
        *
        * @return bool
        */
/** @brief 모든 트레일 포인트를 삭제합니다.
*/

        bool AutoSetReached()const{return autosetreached;}
        /**
        * @brief Defines if the UAV can set the WP's "reached" value automaticaly.
        *
        * @param value
        */
/*        * @ brief UAV 자동 설정이 WP 도달 값을 설정하면 true를 반환합니다 (색상 변경).
        *
        * @return bool
*/

        void SetAutoSetReached(bool const& value){autosetreached=value;}
        /**
        * @brief Returns the 3D distance in meters necessary for the UAV to set WP's to "reached"
        *
        * @return double
        */

/*       / * *
        * @brief UAV가 WP의 "도달 된"값을 자동으로 설정할 수 있는지를 정의합니다.
        *
        * @param 값
        * /
*/

        double AutoSetDistance()const{return autosetdistance;}
        /**
        * @brief Sets the  the 3D distance in meters necessary for the UAV to set WP's to "reached"
        *
        * @param value
        */
/*
       / * *
        * @brief UAV가 WP의 "도달 된"값을 자동으로 설정할 수 있는지를 정의합니다.
        *
        * @param 값
        * /*/

        void SetAutoSetDistance(double const& value){autosetdistance=value;}

        int type() const;

        void SetUavPic(QString UAVPic);

    private:
        int altitude;
        UAVMapFollowType::Types mapfollowtype;
        UAVTrailType::Types trailtype;
        internals::PointLatLng lastcoord;
        QGraphicsItemGroup* trail;
        QGraphicsItemGroup * trailLine;
        internals::PointLatLng lasttrailline;
        QTime timer;
        bool showtrail;
        bool showtrailline;
        int trailtime;
        int traildistance;
        bool autosetreached;
        double Distance3D(internals::PointLatLng const& coord, int const& altitude);
        double autosetdistance;
      //  QRectF rect;

    public slots:

    signals:
        void UAVReachedWayPoint(int const& waypointnumber,WayPointItem* waypoint);
        void UAVLeftSafetyBouble(internals::PointLatLng const& position);
    };
}
#endif // UAVITEM_H
