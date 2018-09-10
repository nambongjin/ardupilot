#ifndef WAYPOINT2DICON_H
#define WAYPOINT2DICON_H

#include <QGraphicsItem>

#include "Waypoint.h"
#include "opmapcontrol.h"

class Waypoint2DIcon : public mapcontrol::WayPointItem
{
public:
    /**
     *
     * @param latitude
     * @param longitude
     * @param name name of the circle point
     */
    /**
     *
     * @param 위도
     * @param 경도
     파라미터 : name - 원점의 이름
     */
    Waypoint2DIcon(mapcontrol::MapGraphicItem* map, mapcontrol::OPMapWidget* parent, qreal latitude, qreal longitude, qreal altitude, int listindex, QString name = QString(), QString description = QString(), int radius=30);

    /**
     *
     * @param wp Waypoint
     * @param radius the radius of the circle
     */
    /**
     *
     * @param wp Waypoint
     * @param radius 원의 반경
     */


    Waypoint2DIcon(mapcontrol::MapGraphicItem* map, mapcontrol::OPMapWidget* parent, Waypoint* wp, const QColor& color, int listindex, int radius = 31);

    virtual ~Waypoint2DIcon();

    void SetHeading(float heading);

    /** @brief Rectangle to be updated on changes */
    /** brief 변경시에 갱신되는 구형 */
    QRectF boundingRect() const;
    /** @brief Draw the icon in a double buffer */
    /** @brief 이중 버퍼에 아이콘 그리기 */
    void drawIcon();
    /** @brief Draw the icon on a QPainter device (map) */
    /** @ brief QPainter 장치 (지도)에 아이콘 그리기 */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateWaypoint();

protected:
    mapcontrol::OPMapWidget* parent; ///< Parent widget
                                     /// <부모 위젯
    Waypoint* waypoint;   ///< Waypoint data container this icon represents
                          /// 이 아이콘이 나타내는 웨이 포인트 데이터 컨테이너
    int radius;           ///< Radius / diameter of the icon in pixels
                          /// <아이콘의 반지름 / 지름 (픽셀 단위)
    bool showAcceptanceRadius; 
    bool showOrbit;
    QColor color;
};

#endif // WAYPOINT2DICON_H
