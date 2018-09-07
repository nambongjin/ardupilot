#ifndef WAYPOINTLINEITEM_H
#define WAYPOINTLINEITEM_H

#include <QGraphicsLineItem>
#include "../../opmapcontrol.h"
#include "graphicsusertypes.h"

namespace mapcontrol {
class WaypointLineItem : public QObject,public QGraphicsLineItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Type = usertypes::WAYPOINTLINEITEM };
    WaypointLineItem(WayPointItem* wp1, WayPointItem* wp2, QColor color=QColor(Qt::red), MapGraphicItem* parent=0);
    int type() const;

public slots:
    /**
    * @brief Update waypoint values
    *
    * @param waypoint The waypoint object that just changed
    */
   /**
    * @brief 웨이 포인트 값 업데이트
    *
    * @param 웨이 포인트 방금 변경 한 웨이 포인트 오브젝트
    */
    void updateWPValues(WayPointItem* waypoint);
    /**
    * @brief Update waypoint values
    */
   /**
    * @brief 웨이 포인트 값 업데이트
    */
    void updateWPValues();
    /**
    * @brief Update waypoint values
    *
    */
   /**
    * @brief 웨이 포인트 값 업데이트
    *
    */
    void RefreshPos();

protected:
    internals::PointLatLng point1;
    internals::PointLatLng point2;
    WayPointItem* wp1;
    WayPointItem* wp2;
    MapGraphicItem* map;              ///< The map this item is parent of
};                                    ///<이 항목이 부모가되는지도
}

#endif // WAYPOINTLINEITEM_H
