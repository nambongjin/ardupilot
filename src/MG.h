/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Helper functions
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */


#ifndef _MG_H_
#define _MG_H_

#include <QDateTime>

#include <QDir>
#include <QThread>
#include <cmath>

namespace MG
{
const static int MAX_FLIGHT_TIME = 60 * 60 * 24 * 21;

class VERSION
{
public:

    static const int MAJOR = 1;
    static const int MINOR = 01;
};

class SYSTEM
{
public:

    static const int ID = 127;
    static const int COMPID = 0;
    static int getID() {
        return SYSTEM::ID;
    }
};


class SLEEP : public QThread
{
public:
    /**
     * @brief Set a thread to sleep for seconds
     * @param s time in seconds to sleep
     **/
    /* *
     * @brief 수초 동안 스레드를 잠자기 상태로 설정
     * @param 초의 시간 (초)
     * */
    static void sleep(unsigned long s) {
        QThread::sleep(s);
    }
    /**
     * @brief Set a thread to sleep for milliseconds
     * @param ms time in milliseconds to sleep
     **/
    /* *
     * @brief 밀리 세컨드 동안 쓰레드를 대기 상태로 설정
     * @param ms 시간 (밀리 세컨드 단위)
     * */
    static void msleep(unsigned long ms) {
        QThread::msleep(ms);
    }
    /**
     * @brief Set a thread to sleep for microseconds
     * @param us time in microseconds to sleep
     **/
    /* *
     * @brief 마이크로 세컨드 동안 스레드를 슬립 상태로 설정
     * @param 우리는 수면 시간 (마이크로 초)
     * */
    static void usleep(unsigned long us) {
        QThread::usleep(us);
    }
};


class UNITS
{
public:

    /** The distance units supported for display by the groundstation **/
    /* * 지상 스테이션이 표시 할 수있는 거리 단위 * */
    enum DistanceUnit {
        METER,
        CENTIMETER,
        MILLIMETER,
        INCH,
        FEET,
        MILE
    };

    /**
     * @brief Convert a distance in meters into another distance unit system
     *
     * @param in The distance to convert
     * @param newUnit The new unit to convert to
     *
     * @return The converted distance
     */
    /* *
     * @brief 다른 거리 단위계로 미터 단위로 변환
     *
     * @param in 변환 할 거리
     * @param newUnit 변환 대상의 새로운 단위
     *
     * @return 변환 된 거리
     */
    static double convertFromMeter(double in, DistanceUnit newUnit) {
        double result = in;

        // Conversion table in meter
        // 미터 단위의 변환 표
        static const double inInch = 39.3700787;
        static const double inFeet = 3.2808399;
        static const double inMile = 0.000000621371192;
        static const double inCentimeter = 100;
        static const double inMillimeter = 1000;

        switch (newUnit) {
        case METER:
            result = in;
            break;
        case CENTIMETER:
            result = in * inCentimeter;
            break;
        case MILLIMETER:
            result = in * inMillimeter;
            break;
        case INCH:
            result = in * inInch;
            break;
        case FEET:
            result = in * inFeet;
            break;
        case MILE:
            result = in * inMile;
            break;
        }

        return result;
    }

    /**
     * @brief Convert between two distance units
     *
     * This convenience function allows to convert between arbitrary distance units
     *
     * @param in The input distance
     * @param inputUnit The input unit
     * @param outputUnit The output unit
     *
     * @return The converted distance
     */
    /* *
     * @brief 두 거리 단위 사이의 변환
     *
     *이 편리한 함수는 임의의 거리 단위
     *
     * @param in 입력 거리
     * @param inputUnit 입력 단위
     * @param outputUnit 출력 단위
     *
     * @return 변환 된 거리
     */
    static double convert(double in, DistanceUnit inputUnit, DistanceUnit outputUnit) {
        double meters = convertToMeter(in, inputUnit);
        return convertFromMeter(meters, outputUnit);
    }

    /**
     * @brief Convert a distance to the meter unit
     *
     * @param in The distance to convert
     * @param inputUnit The unit the distance is represented in
     *
     * @return The converted distance
     */
    /* *
     * @brief 미터기와의 거리 변환
     *
     * @param in 변환 할 거리
     파라미터 : inputUnit - 거리를 나타내는 단위
     *
     * @return 변환 된 거리
     */
    static double convertToMeter(double in, DistanceUnit inputUnit) {

        double result = in;


        // Conversion table in meter
        // 미터 단위의 변환 표
        static const double inInch = 39.3700787;
        static const double inFeet = 3.2808399;
        static const double inMile = 0.000000621371192;
        static const double inCentimeter = 100;
        static const double inMillimeter = 1000;

        // Don't convert if new unit is same unit
        // 새로운 단위가 같은 단위 일 경우 변환하지 않는다.

        switch (inputUnit) {
        case METER:
            result = in;
            break;
        case CENTIMETER:
            result = in / inCentimeter;
            break;
        case MILLIMETER:
            result = in / inMillimeter;
            break;
        case INCH:
            result = in / inInch;
            break;
        case FEET:
            result = in / inFeet;
            break;
        case MILE:
            result = in / inMile;
            break;
        }

        return result;
    }

};

class DISPLAY
{

public:

    DISPLAY() {
        // Initialize static class display with notebook display default value
        //pixelSize = 0.224f;
        //setPixelSize(0.224f);
        // 노트북 디스플레이 기본값으로 정적 클래스 표시 초기화
        // pixelSize = 0.224f;
        // setPixelSize (0.224f);
    }

    ~DISPLAY() {

    }

    /**
     * @brief Get the size of a single pixel
     *
     * This value can be used to generate user interfaces with
     * a size in physical units, for example a gauge which is
     * always 50.8 mm (2") in diameter, regardless of the screen.
     *
     * @return The horizontal and vertical size of a pixel-square
     */
    /* *
     * @brief 단일 픽셀의 크기를 가져옵니다.
     *
     *이 값은 다음과 같은 사용자 인터페이스를 생성하는 데 사용될 수 있습니다.
     * 물리적 단위의 크기. 예를 들어 게이지
     * 화면에 관계없이 항상 지름 50.8mm (2 인치).
     *
     * @return 픽셀 정사각형의 수평 및 수직 크기
     */
    static double getPixelSize() {
        return 0.224f;
    }

    /**
     * @brief Set the size of a single pixel
     *
     * @param size The horizontal and vertical size of a pixel-square
     */
    /* *
     * @brief 단일 픽셀의 크기를 설정합니다.
     *
     * @param size 픽셀 정사각형의 수평 및 수직 크기
     */
    static void setPixelSize(double size) {
        pixelSize = size;
    }

    /**
     * @brief Set the size of a single pixel
     *
     * This method calculates the pixel size from the vertical and horizontal
     * resolution and the screen diameter. The diameter is in mm (as this unit
     * is a SI unit). One inch = 25.4 mm
     *
     * @param horizontalResolution The horizontal screen resolution, e.g. 1280.
     * @param verticalResolution The vertical screen resolution, e.g. 800.
     * @param screenDiameter The screen diameter in mm, e.g. 13.3" = 338 mm.
     */
    /* *
     * @brief 단일 픽셀의 크기를 설정합니다.
     *
     *이 메서드는 픽셀 크기를 가로 및 세로로 계산합니다.
     * 해상도 및 화면 직경. 지름은 mm 단위입니다 (이 단위
     *는 SI 단위 임). 1 인치 = 25.4mm
     *
     * @param horizontalResolution 수평 화면 해상도, 예를 들어 1280.
     * @param verticalResolution 수직 화면 해상도 (예 : 800)입니다.
     * @param screenDiameter 화면 직경 (mm)입니다 (예 : 13.3 "= 338mm).
     */
    static void setPixelSize(int horizontalResolution, int verticalResolution, double screenDiameter) {
        pixelSize = screenDiameter / sqrt(static_cast<float>(horizontalResolution*horizontalResolution + verticalResolution*verticalResolution));
    }

private:
    /** The size of a single pixel **/
    /* * 단일 픽셀의 크기 * */
    static double pixelSize;
};

class STAT
{
    /** The time interval for the last few moments in milliseconds **/
    /* * 마지막 몇 분의 시간 간격 (밀리 초 단위) * */
    static const int SHORT_TERM_INTERVAL = 300;
    /** The time interval for the last moment in milliseconds **/
    /* * 마지막 순간의 시간 간격 (밀리 초) * */
    static const int CURRENT_INTERVAL = 50;
};

class TIME
{

public:

    //static const QString ICONDIR = "./icons";

    /**
     * @brief Convenience method to get the milliseconds time stamp for now
     *
     * The timestamp is created at the instant of calling this method. It is
     * defined as the number of milliseconds since unix epoch, which is
     * 1.1.1970, 00:00 UTC.
     *
     * @return The number of milliseconds elapsed since unix epoch
     * @deprecated Will the replaced by time helper class
     **/
    /* *
     * @brief 편리한 밀리 세컨드 타임 스탬프를 얻기위한 메소드
     *
     * 타임 스탬프는이 메서드를 호출하는 순간 생성됩니다. 그것은
     * 유닉스 시대 이후의 밀리 초 수로 정의됩니다.
     * 1.1.1970, 00:00 UTC.
     *
     * @return 유닉스 에포크 이후 경과 된 시간 (밀리 초)
     @deprecated 시간 도우미 클래스로 대체 될 것인가?
     * */
    static quint64 getGroundTimeNow() {
        QDateTime time = QDateTime::currentDateTime();
        time = time.toUTC();
        /* Return seconds and milliseconds, in milliseconds unit */
        /* 밀리 초 단위의 초 및 밀리 초 반환 */
        quint64 milliseconds = time.toTime_t() * static_cast<quint64>(1000);
        return static_cast<quint64>(milliseconds + time.time().msec());
    }

    /**
     * @brief Convenience method to get the milliseconds time stamp for now
     *
     * The timestamp is created at the instant of calling this method. It is
     * defined as the number of milliseconds since unix epoch, which is
     * 1.1.1970, 00:00 UTC.
     *
     * @return The number of milliseconds elapsed since unix epoch
     * @deprecated Will the replaced by time helper class
     **/
    /* *
     * @brief 편리한 밀리 세컨드 타임 스탬프를 얻기위한 메소드
     *
     * 타임 스탬프는이 메서드를 호출하는 순간 생성됩니다. 그것은
     * 유닉스 시대 이후의 밀리 초 수로 정의됩니다.
     * 1.1.1970, 00:00 UTC.
     *
     * @return 유닉스 에포크 이후 경과 된 시간 (밀리 초)
     @deprecated 시간 도우미 클래스로 대체 될 것인가?
     * */
    static quint64 getGroundTimeNowUsecs() {
        QDateTime time = QDateTime::currentDateTime();
        time = time.toUTC();
        /* Return seconds and milliseconds, in milliseconds unit */
        /* 밀리 초 단위의 초 및 밀리 초 반환 */
        quint64 microseconds = time.toTime_t() * static_cast<quint64>(1000000);
        return static_cast<quint64>(microseconds + (time.time().msec()*1000));
    }

    /*tatic quint64 getMissionTimeUsecs()
    {
        ;
    }*/

    /**
     * Convert milliseconds to an QDateTime object. This method converts the amount of
     * milliseconds since 1.1.1970, 00:00 UTC (unix epoch) to a QDateTime date object.
     *
     * @param msecs The milliseconds since unix epoch (in Qt unsigned 64bit integer type quint64)
     * @return The QDateTime object set to corresponding date and time
     * @deprecated Will the replaced by time helper class
     **/
    /* *
     밀리 초를 QDateTime 객체로 변환합니다. 이 메소드는
     * 1.1.1970, 00:00 UTC (Unix epoch)부터 QDateTime 날짜 객체까지의 시간 (밀리 초)입니다.
     *
     * @param msecs 유닉스 에포크 이후의 밀리 세컨드 (Qt 부호 없음 64 비트 정수형의 quint64)
     * @return 해당 날짜 및 시간으로 설정된 QDateTime 객체
     @deprecated 시간 도우미 클래스로 대체 될 것인가?
     * */
    static QDateTime msecToQDateTime(quint64 msecs) {
        QDateTime time = QDateTime();
        /* Set date and time depending on the seconds since unix epoch,
             * integer division truncates the milliseconds */
        /* 유닉스 시대 이후의 초에 따라 날짜와 시간을 설정한다.
             * 정수 나누기가 밀리 초를 자릅니다 */
        time.setTime_t(msecs / 1000);
        /* Add the milliseconds, modulo returns the milliseconds part */
        /* 밀리 초를 더한다. 모듈러스는 밀리 초 부분을 반환한다. */
        return time.addMSecs(msecs % 1000);
    }

};

}

#endif // _MG_H_
