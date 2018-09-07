#include "waypointlineitem.h"

namespace mapcontrol
{
WaypointLineItem::WaypointLineItem(WayPointItem* wp1, WayPointItem* wp2, QColor color, mapcontrol::MapGraphicItem* map) :
        QGraphicsLineItem(map),
    wp1(wp1),
    wp2(wp2),
    map(map)
{
    // Make sure this stick to the map
    //이걸지도에 붙이세요.
    //this->setFlag(QGraphicsItem::Item,true);

    
    setParentItem(map);

    // Set up the pen for this icon with the UAV color
    // 이 아이콘에 대한 펜을 UAV 색상으로 설정하십시오.
    QPen pen(color);
    pen.setWidth(2);
    setPen(pen);

    point1 = wp1->Coord();
    point2 = wp2->Coord();

    // Pixel coordinates of the local points
    // 로컬 포인트의 픽셀 좌표
    core::Point localPoint1 = map->FromLatLngToLocal(wp1->Coord());
    core::Point localPoint2 = map->FromLatLngToLocal(wp2->Coord());
    // Draw line
    // 선 그리기
    setLine(localPoint1.X(), localPoint1.Y(), localPoint2.X(), localPoint2.Y());

    // Connect updates
    // Update line from both waypoints
    // 업데이트 연결
    // 두 웨이 포인트에서 라인 업데이트

    connect(wp1, SIGNAL(WPValuesChanged(WayPointItem*)), this, SLOT(updateWPValues(WayPointItem*)));
    connect(wp2, SIGNAL(WPValuesChanged(WayPointItem*)), this, SLOT(updateWPValues(WayPointItem*)));
    // Delete line if one of the waypoints get deleted
    // 경유지 중 하나가 삭제되면 줄 삭제

    connect(wp1, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    connect(wp2, SIGNAL(destroyed()), this, SLOT(deleteLater()));

    // Map Zoom and move
    // 지도 확대 / 축소 및 이동
    connect(map, SIGNAL(mapChanged()), this, SLOT(updateWPValues()));
}

void WaypointLineItem::RefreshPos()
{
    // Delete if either waypoint got deleted
    // 어느 웨이 포인트가 삭제되면 삭제
    if (!wp1 || !wp2)
    {
        this->deleteLater();
    }
    else
    {
        // Set new pixel coordinates based on new global coordinates
        //  새 전역 좌표를 기반으로 새 픽셀 좌표를 설정합니다.
        //QTimer::singleShot(0, this, SLOT(updateWPValues()));


        core::Point localPoint1 = map->FromLatLngToLocal(point1);
        core::Point localPoint2 = map->FromLatLngToLocal(point2);
        if (!localPoint1.IsEmpty() && !localPoint2.IsEmpty())
        {
            setLine(localPoint1.X(), localPoint1.Y(), localPoint2.X(), localPoint2.Y());
        }
    }
}

void WaypointLineItem::updateWPValues(WayPointItem* waypoint)
{
    Q_UNUSED(waypoint);
    // Delete if either waypoint got deleted
    // 어느 웨이 포인트가 삭제되면 삭제
    if (!wp1 || !wp2)
    {
        this->deleteLater();
    }
    else
    {
        // Set new pixel coordinates based on new global coordinates
        // 새 전역 좌표를 기반으로 새 픽셀 좌표를 설정합니다.
        point1 = wp1->Coord();
        point2 = wp2->Coord();
        core::Point localPoint1 = map->FromLatLngToLocal(wp1->Coord());
        core::Point localPoint2 = map->FromLatLngToLocal(wp2->Coord());

        setLine(localPoint1.X(), localPoint1.Y(), localPoint2.X(), localPoint2.Y());
    }
}

void WaypointLineItem::updateWPValues()
{
    updateWPValues(NULL);
}

int WaypointLineItem::type()const
{
    return Type;
}

}
