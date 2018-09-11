#ifndef MAV2DICON_H
#define MAV2DICON_H

#include <QGraphicsItem>

#include "UASInterface.h"
#include "../../libs/opmapcontrol/opmapcontrol.h"

class MAV2DIcon : public mapcontrol::UAVItem
{
public:
    enum {
        MAV_ICON_GENERIC = 0,
        MAV_ICON_AIRPLANE,
        MAV_ICON_QUADROTOR,
        MAV_ICON_COAXIAL,
        MAV_ICON_HELICOPTER,
    } MAV_ICON_TYPE;

    //!
    /*!
     *
     * @param x longitude
     * @param y latitude
     * @param radius the radius of the circle
     * @param name name of the circle point
     * @param alignment alignment (Middle or TopLeft)
     * @param pen QPen for drawing
     */
    // !
    /* !
     *
     * @ 파라미터 x 경도
     * @ 파라미터 y 위도
     * @param radius 원의 반경
     파라미터 : name - 원점의 이름
     * @param 정렬 맞춤 (중간 또는 TopLeft)
     그리기를 위해 * @param 펜 QPen
     */
    MAV2DIcon(mapcontrol::MapGraphicItem* map,mapcontrol::OPMapWidget* parent, UASInterface* uas, int radius = 40, int type=0);

    /*!
     *
     * @param x longitude
     * @param y latitude
     * @param name name of the circle point
     * @param alignment alignment (Middle or TopLeft)
     * @param pen QPen for drawing
     */
    /* !
     *
     * @ 파라미터 x 경도
     * @ 파라미터 y 위도
     파라미터 : name - 원점의 이름
     * @param 정렬 맞춤 (중간 또는 TopLeft)
     그리기를 위해 * @param 펜 QPen
     */
    MAV2DIcon(mapcontrol::MapGraphicItem* map,mapcontrol::OPMapWidget* parent, qreal lat=0, qreal lon=0, qreal alt=0, QColor color=QColor());

    virtual ~MAV2DIcon();

    /** @brief Mark this system as selected */
    /* * brief이 시스템을 선택 사항으로 표시 */
    void setSelectedUAS(bool selected);
    void setYaw(float yaw);
    /** @brief Set the airframe this MAV uses */
    /* * brief MAV가 사용하는 기체를 설정 */
    void setAirframe(int airframe) {
        this->airframe = airframe;
    }

    /** @brief Get system id */
    /* * @ brief 시스템 ID 얻기 */
    int getUASId() const {
        return uasid;
    }

    void drawIcon();
    static void drawAirframePolygon(int airframe, QPainter& painter, int radius, QColor& iconColor, float yaw);

protected:
    float yaw;      ///< Yaw angle of the MAV// / <MAV의 요각
    int radius;     ///< Radius / width of the icon// / <아이콘의 반경 / 너비
    int type;       ///< Type of aircraft: 0: generic, 1: airplane, 2: quadrotor, 3-n: rotary wing// / <항공기 유형 : 0 : 일반, 1 : 비행기, 2 : 쿼드 로터, 3-n : 회전 날개
    int airframe;   ///< The specific type of airframe used// / <사용한 기체의 특정 유형
    QColor iconColor; ///< Color to be used for the icon// / <아이콘에 사용될 색상
    bool selected;  ///< Wether this is the system currently in focus// 이것은 현재 현재 포커스가있는 시스템입니다.
    int uasid;      ///< ID of tracked system// 추적 된 시스템의 ID
    QSize size;

};

#endif // MAV2DICON_H
