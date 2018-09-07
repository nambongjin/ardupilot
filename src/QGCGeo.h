#ifndef QGCGEO_H
#define QGCGEO_H

#include <QList>
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix3x3>
#include <math.h>

#define DEG2RAD (M_PI/180.0)

/* Safeguard for systems lacking sincos (e.g. Mac OS X Leopard) */
/* sincos가없는 시스템 (예 : Mac OS X Leopard)에 대한 보호 장치 */
#ifndef sincos
#define sincos(th,x,y) { (*(x))=sin(th); (*(y))=cos(th); }
#endif

/** @brief A class to hold a 3D vector made with doubles. This class is meant to help isolate the code
 * against external library includes like alglib and Eigen. We can't use the vector supplied by Qt (QVector3d), because
 * that one is made out of floats. We need the extra precision for expressing latitude/longitude, for example.
 */
/** brief double로 만든 3D 벡터를 유지하는 클래스. 이 클래스는 코드 분리를 돕기위한 클래스입니다.
* 외부 라이브러리에 대해 alglib 및 Eigen을 포함합니다. Qt (QVector3d)에서 제공하는 벡터는 사용할 수 없습니다.
* 하나는 수레로 만들어졌다. 예를 들어, 위도 / 경도 표현을위한 추가 정밀도가 필요합니다.
*/

class Vector3d
{
public:
    /** @brief Constructs an empty, null vector */
    /* * @brief 하늘의 null 벡터를 구축합니다. */
    Vector3d(void) : m_x(0.0), m_y(0.0), m_z(0.0) {}

    /** @brief Constructs a vector with coordinates (x, y, z) */
    /** @brief 좌표 (x, y, z)가있는 벡터를 구성합니다 */
    Vector3d(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

    /** @brief Construct a vector initialized with the given vector */
    /** @brief 주어진 벡터로 초기화 된 벡터를 만듭니다. */
    Vector3d(const Vector3d &rhs) : m_x(rhs.m_x), m_y(rhs.m_y), m_z(rhs.m_z) {}

    /** @brief Construct a vector initialized with the given QVector3D */
    /** @brief 주어진 QVector3D로 초기화 된 벡터를 구성한다 */
    Vector3d(const QVector3D &rhs) : m_x(rhs.x()), m_y(rhs.y()), m_z(rhs.z()) {}

    /** @brief Sets the fields of this vector to the values of the given vector */
    /** @ brief이 벡터의 필드를 주어진 벡터의 값으로 설정합니다. */
    const Vector3d &operator=(const Vector3d &rhs);

    /** @brief Adds the given vector to this vector */
    /** @brief 지정된 벡터를이 벡터에 추가합니다. */
    Vector3d &operator+=(const Vector3d &rhs);

    /** @brief Subtracts the given vector from this vector */
    /** @brief 벡터로부터 주어진 벡터를 뺍니다. */
    Vector3d &operator-=(const Vector3d &rhs);

    /** @brief returns the individual coordinates */
    /** @ brief는 개별 좌표를 반환합니다 */
    double x(void) const { return m_x; }
    double y(void) const { return m_y; }
    double z(void) const { return m_z; }
    double operator[](int i) const;

    /** @brief sets the individual coordinates */
    /** @ brief는 개별 좌표를 설정합니다 */
    void set(double x, double y, double z) { m_x = x; m_y = y; m_z = z; }
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }
    void setZ(double z) { m_z = z; }
    double &operator[](int i);

    /** @brief returns true, if the x, y and z field is exactly 0.0. Returns false otherwise */
    /** @ brief는 x, y 및 z 필드가 정확히 0.0 인 경우 true를 반환합니다. 그렇지 않으면 false를 반환합니다. */
    bool isNull(void) const;

    /** @brief returns true, if this vector is the same as the given vector */
    /**이 벡터가 주어진 벡터와 동일한 경우 @ brief는 true를 반환합니다. */
    bool isEqualTo(const Vector3d &other) const;

    /** @brief returns the cartesian length of this vector */
    /** brief는이 벡터의 데카르트 길이를 반환합니다 */
    double length(void) const;

    /** @brief returns the squared length of this vector */
    /** brief는 벡터의 제곱 길이를 반환합니다 */
    double lengthSquared(void) const;

    /** @brief calculates the approximate center of a sphere, given the points on the sphere.
      * @returns return true, if the method converged on a value. returns false, if there not enough points.
      * @param pointsOnSphere a list of points that are on the sphere
     **/
    /** @brief는 구의 점을 고려하여 구의 근사 중심을 계산합니다.
      *메서드가 값에 수렴하면 * @returns는 true를 반환합니다. 포인트가 충분하지 않으면 false를 반환합니다.
      * @param pointsOnSphere는 구에있는 점의 목록입니다.
     **/
    bool setToLeastSquaresSphericalCenter(const QVector<Vector3d> &pointsOnSphere);

    /** @brief returns a QVector3d for this vector.
      * (Note: QVector3d uses floats to store the fields, so some rounding will occur.)
     **/
    /** @ brief는이 벡터에 대한 QVector3d를 반환합니다.
      * (참고 : QVector3d는 수레를 사용하여 필드를 저장하므로 일부 반올림이 발생합니다.)
     **/
    QVector3D toQVector3D(void) const;

    /** @brief calculates the dot product of this vector with the given vector */
    /** brief는이 벡터와 주어진 벡터의 내적을 계산합니다 */
    double dot(const Vector3d &v) const;

    /** @brief calcuates the dot product of the two given vectors */
    /** brief는 두 벡터의 내적을 계산합니다 */
    static double dotProduct(const Vector3d &v1, const Vector3d &v2);

    /** @brief calculates and stores the cross product of this vector with the given vector */
    /** @ brief는이 벡터의 외적을 계산하여 주어진 벡터와 함께 저장합니다 */
    Vector3d &cross(const Vector3d &v);

    /** @brief returns the cross product of the two given vectors */
    /** brief는 주어진 두 벡터의 외적을 반환합니다 */
    static Vector3d crossProduct(const Vector3d &lhs, const Vector3d &rhs);

    /** @brief rotates the current vector with the given quaternion. */
    /** brief는 주어진 쿼터니온으로 현재 벡터를 회전시킵니다. */
    Vector3d &rotateWithQuaternion(const QQuaternion &q);

    /** @brief returns the vector, rotated by the given quaternion */
    /** brief는 주어진 쿼터니온에 의해 회전 된 벡터를 반환합니다 */
    static Vector3d rotateVectorWithQuaternion(const Vector3d &v, const QQuaternion &q);

protected:
    double m_x;
    double m_y;
    double m_z;
};

const Vector3d crossProduct(const Vector3d &lhs, const Vector3d &rhs);
bool operator==(const Vector3d &lhs, const Vector3d &rhs);
bool operator!=(const Vector3d &lhs, const Vector3d &rhs);
const Vector3d operator+(const Vector3d &v1, const Vector3d &v2);
const Vector3d operator-(const Vector3d &v1, const Vector3d &v2);
const Vector3d operator*(double scalar, const Vector3d &v);
const Vector3d operator*(const Vector3d &v, double scalar);

/** Convert a rotation matrix to a quaternion */
/** 회전 행렬을 쿼터니언으로 변환 */
QQuaternion quaternionFromMatrix3x3(const QMatrix3x3 &mat);

#endif // QGCGEO_H
