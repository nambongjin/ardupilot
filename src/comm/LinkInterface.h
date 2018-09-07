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
*   @brief Brief Description
*
*   @author Lorenz Meier <mavteam@student.ethz.ch>
*
*/

#ifndef _LINKINTERFACE_H_
#define _LINKINTERFACE_H_

#include <QThread>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>

/**
* The link interface defines the interface for all links used to communicate
* with the groundstation application.
*
**/
/* *
* 링크 인터페이스는 통신에 사용되는 모든 링크의 인터페이스를 정의합니다.
* 지상 설치 응용 프로그램과 함께.
*
* */
class LinkInterface : public QThread
{
    Q_OBJECT
public:
    enum LinkType
    {
        SERIAL_LINK,
        TCP_LINK,
        UDP_LINK,
        UDP_CLIENT_LINK,
        SIM_LINK,
        UNKNOWN_LINK
    };

public:
    LinkInterface();
    virtual ~LinkInterface();

    /**
     * @brief Conenction Management /부채 관리
     *
     **/
    virtual void disableTimeouts() = 0;
    virtual void enableTimeouts() = 0;

    /**
     * @brief Get the ID of this link
     *
     * The ID is an unsigned integer, starting at 0
     * @return ID of this link
     **/
  /* *
     * @brief이 링크의 ID를 가져옵니다.
     *
     * ID는 0에서 시작하는 부호없는 정수입니다.
     이 링크의 ID
     * */
    virtual int getId() const = 0;

    /**
     * @brief Get the human readable name of this link
     */
    /**
     * @brief이 링크의 사람이 읽을 수있는 이름을 가져옵니다.
     */
    virtual QString getName() const = 0;

    /**
     * @brief Get the human readable name of this link
     */
    /**
     * @brief이 링크의 사람이 읽을 수있는 이름을 가져옵니다.
     */
    virtual QString getShortName() const = 0;

    /**
     * @brief Get the detail of this link (ie. baud, ip addres etc)
     */
   /**
     * @brief이 링크의 세부 정보를 얻습니다 (즉, baud, ip addres 등).
     */
    virtual QString getDetail() const = 0;

    virtual void requestReset() = 0;

    /**
     * @brief Determine the connection status
     *
     * @return True if the connection is established, false otherwise
     **/
    /**
     * @brief 연결 상태 확인
     *
     * @return 연결이 성립하면 참, 그렇지 않으면 거짓
     * */
    virtual bool isConnected() const = 0;

    /* Connection characteristics */

    /**
     * @Brief Get the maximum connection speed for this interface.
     *
     * The nominal data rate is the theoretical maximum data rate of the
     * interface. For 100Base-T Ethernet this would be 100 Mbit/s (100'000'000
     * Bit/s, NOT 104'857'600 Bit/s).
     *
     * @return The nominal data rate of the interface in bit per second, 0 if unknown
     **/
    /* 연결 특성 */

    /* *
     * @Brief이 인터페이스의 최대 연결 속도를 얻습니다.
     *
     * 공칭 데이터 전송률은 이론적 최대 데이터 전송률입니다.
     * 인터페이스. 100Base-T 이더넷의 경우 100Mbit / s (100'000'000
     * 비트 / s, 104'857'600 비트 / s가 아님).
     *
     * @return 인터페이스의 공칭 데이터 전송률 (비트 / 초), 알 수없는 경우 0
     * */
    virtual qint64 getConnectionSpeed() const = 0;

    /**
     * @Brief Get the current incoming data rate.
     *
     * This should be over a short timespan, something like 100ms. A precise value isn't necessary,
     * and this can be filtered, but should be a reasonable estimate of current data rate.
     *
     * @return The data rate of the interface in bits per second, 0 if unknown
     **/
    /**
     * @Brief 현재 들어오는 데이터 속도를 가져옵니다.
     *
     *이 시간은 100ms와 같은 짧은 시간대를 넘어야합니다. 정확한 값은 필요하지 않지만,
     *이 필터는 필터링 할 수 있지만 현재 데이터 속도를 합리적으로 추정해야합니다.
     *
     * @return 인터페이스의 데이터 전송률 (비트 / 초), 알 수없는 경우 0
     **/
    qint64 getCurrentInDataRate() const
    {
        return getCurrentDataRate(inDataIndex, inDataWriteTimes, inDataWriteAmounts);
    }

    /**
     * @Brief Get the current outgoing data rate.
     *
     * This should be over a short timespan, something like 100ms. A precise value isn't necessary,
     * and this can be filtered, but should be a reasonable estimate of current data rate.
     *
     * @return The data rate of the interface in bits per second, 0 if unknown
     **/
    /**
     * @Brief 현재 나가는 데이터 전송률을 얻습니다.
     *
     *이 시간은 100ms와 같은 짧은 시간대를 넘어야합니다. 정확한 값은 필요하지 않지만,
     *이 필터는 필터링 할 수 있지만 현재 데이터 속도를 합리적으로 추정해야합니다.
     *
     * @return 인터페이스의 데이터 전송률 (비트 / 초), 알 수없는 경우 0
     **/
    qint64 getCurrentOutDataRate() const
    {
        return getCurrentDataRate(outDataIndex, outDataWriteTimes, outDataWriteAmounts);
    }

    /**
     * @brief Get the current number of bytes in buffer.
     *
     * @return The number of bytes ready to read
     **/
   /**
     * @brief 버퍼에있는 현재 바이트 수를 가져옵니다.
     *
     * @return 읽을 준비가되어있는 바이트 수
     **/
    virtual qint64 bytesAvailable() = 0;

    virtual LinkType getLinkType() { return UNKNOWN_LINK; }


public slots:

    /**
     * @brief Connect this interface logically
     *
     * @return True if connection could be established, false otherwise
     **/
   /**
     * @brief이 인터페이스를 논리적으로 연결하십시오.
     *
     * @return 접속을 확립 할 수있는 경우는 true, 그렇지 않은 경우는 false
     **/
    virtual bool connect() = 0;

    /**
     * @brief Disconnect this interface logically
     *
     * @return True if connection could be terminated, false otherwise
     **/
    /**
     * @brief 논리적으로이 인터페이스의 연결을 끊습니다.
     *
     * @return 접속을 종료 할 수있는 경우는 true, 그렇지 않은 경우는 false
     **/
    
    virtual bool disconnect() = 0;

    /**
     * @brief This method allows to write bytes to the interface.
     *
     * If the underlying communication is packet oriented,
     * one write command equals a datagram. In case of serial
     * communication arbitrary byte lengths can be written
     *
     * @param bytes The pointer to the byte array containing the data
     * @param length The length of the data array
     **/
    /**
     * @brief이 메소드는 인터페이스에 바이트를 쓸 수있게합니다.
     *
     * 기본 통신이 패킷 지향 인 경우,
     * 하나의 쓰기 명령은 데이터 그램과 같습니다. 시리얼의 경우
     * 통신 임의의 바이트 길이를 쓸 수 있습니다
     *
     * @param 바이트 데이터를 포함한 바이트 배열의 포인터
     * @param length 데이터 배열의 길이
     **/
    virtual void writeBytes(const char *bytes, qint64 length) = 0;

signals:

    /**
     * @brief New data arrived
     *
     * The new data is contained in the QByteArray data. The data is copied for each
     * receiving protocol. For high-speed links like image transmission this might
     * affect performance, for control links it is however desirable to directly
     * forward the link data.
     *
     * @param data the new bytes
     */
    /**
     * 새로운 데이터 도착
     *
     * 새 데이터는 QByteArray 데이터에 포함됩니다. 데이터는 각각 복사됩니다.
     * 수신 프로토콜. 이미지 전송과 같은 고속 링크의 경우
     * 성능에 영향을 미치지 만 제어 링크의 경우 직접적으로 바람직하다.
     * 링크 데이터를 전달하십시오.
     *
     파라미터 : data - 새로운 바이트
     */
    void bytesReceived(LinkInterface* link, QByteArray data);

    /**
     * @brief This signal is emitted instantly when the link is connected
     **/
    /**
     * @ brief이 신호는 링크가 연결될 때 즉시 방출됩니다.
     **/
    void connected();

    /**
     * @brief This signal is emitted when the link is connected
     **/
    /**
     * @ brief이 신호는 링크가 연결될 때 나옵니다.
     **/
    void connected(LinkInterface* linkInterface);


    /**
     * @brief This signal is emitted instantly when the link is disconnected
     **/
    /**
     * @brief이 신호는 링크가 끊어지면 즉시 방출됩니다.
     **/
   
    void disconnected();

    /**
     * @brief This signal is emitted when the link is disconnected
     **/
    /**
     * @brief이 신호는 링크가 끊어졌을 때 나옵니다.
     **/
    void disconnected(LinkInterface* linkInterface);

    /**
     * @brief This signal is emitted instantly when the link status changes
     **/
    /**
     * @ brief이 신호는 링크 상태가 변경 될 때 즉시 방출됩니다.
     **/
    void connected(bool connected);

    /**
     * @brief This signal is emitted if the human readable name of this link changes
     */
    /**
     * @brief이 링크의 사람이 읽을 수있는 이름이 바뀌면이 신호가 방출됩니다.
     */
    void nameChanged(QString name);

    /** @brief Communication error occured */
    /** brief 통신 오류가 발생했습니다. */
    void communicationError(const QString& linkname, const QString& error);

    void communicationUpdate(const QString& linkname, const QString& text);

    /** @brief destroying element */
    /* * 간단한 파괴 요소 */
    void deleteLink(LinkInterface* const link);

    void error(LinkInterface* link,QString errorstring);

    /**
      * @brief Sends an update message when the link parameters are changed
      *
      */
     /**
      * @brief 링크 매개 변수가 변경되면 업데이트 메시지를 보냅니다.
      *
      */
    void linkChanged(LinkInterface* link);

protected:

    static const int dataRateBufferSize = 20; ///< Specify how many data points to capture for data rate calculations.
                                              /// <데이터 속도 계산을 위해 캡처 할 데이터 포인트의 수를 지정하십시오.
    static const qint64 dataRateCurrentTimespan = 500; ///< Set the maximum age of samples to use for data calculations (ms).
                                                       /// <데이터 계산에 사용할 샘플의 최대 보존 기간을 설정합니다 (밀리 초).
    // Implement a simple circular buffer for storing when and how much data was received.
    // Used for calculating the incoming data rate. Use with *StatsBuffer() functions.
    // 수신 된 데이터의 양과 양을 저장하기위한 간단한 순환 버퍼를 구현합니다.
    // 들어오는 데이터 속도를 계산하는 데 사용됩니다. * StatsBuffer () 함수와 함께 사용하십시오.
    int inDataIndex;
    quint64 inDataWriteAmounts[dataRateBufferSize]; // In bytes
    qint64 inDataWriteTimes[dataRateBufferSize]; // in ms

    // Implement a simple circular buffer for storing when and how much data was transmit.
    // Used for calculating the outgoing data rate. Use with *StatsBuffer() functions.
    // 전송 된 데이터의 양과 양을 저장하기위한 간단한 순환 버퍼를 구현합니다.
    // 나가는 데이터 전송률을 계산하는 데 사용됩니다. * StatsBuffer () 함수와 함께 사용하십시오.
    int outDataIndex;
    quint64 outDataWriteAmounts[dataRateBufferSize]; // In bytes
    qint64 outDataWriteTimes[dataRateBufferSize]; // in ms

    mutable QMutex dataRateMutex; // Mutex for accessing the data rate member variables
                                  // 데이터 속도 멤버 변수에 액세스하기위한 뮤텍스
    /**
     * @brief logDataRateToBuffer Stores transmission times/amounts for statistics
     *
     * This function logs the send times and amounts of datas to the given circular buffers.
     * This data is used for calculating the transmission rate.
     *
     * @param bytesBuffer[out] The buffer to write the bytes value into.
     * @param timeBuffer[out] The buffer to write the time value into
     * @param writeIndex[out] The write index used for this buffer.
     * @param bytes The amount of bytes transmit.
     * @param time The time (in ms) this transmission occurred.
     */
    /**
     * @brief logDataRateToBuffer 통계에 대한 전송 시간 / 양을 저장합니다.
     *
     *이 함수는 주어진 순환 버퍼에 데이터의 전송 시간과 양을 기록합니다.
     *이 데이터는 전송 속도를 계산하는 데 사용됩니다.
     *
     byteBuffer [out] 바이트 치를 기입하는 버퍼입니다.
     timeBuffer [out] 시간 치를 기입하는 버퍼
     writeIndex [out] 현재의 버퍼로 사용되는 기입 인덱스.
     * @param bytes 전송하는 바이트의 양.
     * @param time이 전송이 발생한 시간 (밀리 초).
     */
    static void logDataRateToBuffer(quint64 *bytesBuffer, qint64 *timeBuffer, int *writeIndex, quint64 bytes, qint64 time)
    {
        int i = *writeIndex;

        // Now write into the buffer, if there's no room, we just overwrite the first data point.
        // 이제 버퍼에 씁니다. 여유가 없다면 첫 번째 데이터 점을 덮어 씁니다.
        bytesBuffer[i] = bytes;
        timeBuffer[i] = time;

        // Increment and wrap the write index
        // 쓰기 인덱스를 증가시키고 감싸기
        ++i;
        if (i == dataRateBufferSize)
        {
            i = 0;
        }
        *writeIndex = i;
    }

    /**
     * @brief getCurrentDataRate Get the current data rate given a data rate buffer.
     *
     * This function attempts to use the times and number of bytes transmit into a current data rate
     * estimation. Since it needs to use timestamps to get the timeperiods over when the data was sent,
     * this is effectively a global data rate over the last dataRateBufferSize - 1 data points. Also note
     * that data points older than NOW - dataRateCurrentTimespan are ignored.
     *
     * @param index The first valid sample in the data rate buffer. Refers to the oldest time sample.
     * @param dataWriteTimes The time, in ms since epoch, that each data sample took place.
     * @param dataWriteAmounts The amount of data (in bits) that was transferred.
     * @return The bits per second of data transferrence of the interface over the last [-statsCurrentTimespan, 0] timespan.
     */
    /**
     * @brief getCurrentDataRate 주어진 데이터 속도 버퍼의 현재 데이터 속도를 가져옵니다.
     *
     *이 함수는 시간과 바이트 수를 현재 데이터 전송률로 사용하려고 시도합니다
     * 추정. 데이터가 전송되었을 때 시간을 얻으려면 타임 스탬프를 사용해야하기 때문에,
     * 이것은 효과적으로 마지막 dataRateBufferSize - 1 데이터 포인트에 대한 전역 데이터 전송률입니다. 또한 메모
     * 지금보다 오래된 데이터 포인트 - dataRateCurrentTimespan은 무시됩니다.
     *
     * @param index 데이터 레이트 버퍼의 최초의 유효한 샘플. 가장 오래된 시간 샘플을 참조하십시오.
     * @param dataWriteTimes 각 데이터 샘플이 발생한 시간 (밀리 초 단위).
     * @param dataWriteAmounts 전송 된 데이터의 양 (비트 단위).
     * @return 마지막 [-statsCurrentTimespan, 0] timespan 동안 인터페이스의 데이터 전송의 초당 비트.
     */
    qint64 getCurrentDataRate(int index, const qint64 dataWriteTimes[], const quint64 dataWriteAmounts[]) const
    {
        const qint64 now = QDateTime::currentMSecsSinceEpoch();

        // Limit the time we calculate to the recent past
        // 우리가 계산 한 시간을 최근 과거로 제한합니다.
        const qint64 cutoff = now - dataRateCurrentTimespan;

        // Grab the mutex for working with the stats variables
        // 통계 변수로 작업하기위한 뮤텍스 가져 오기
        QMutexLocker dataRateLocker(&dataRateMutex);

        // Now iterate through the buffer of all received data packets adding up all values
        // within now and our cutof.
        // 이제 모든 값을 합친 모든 수신 된 데이터 패킷의 버퍼를 반복합니다.
        // 지금과 우리의 컷오프.
        qint64 totalBytes = 0;
        qint64 totalTime = 0;
        qint64 lastTime = 0;
        int size = dataRateBufferSize;
        while (size-- > 0)
        {
            // If this data is within our cutoff time, include it in our calculations.
            // This also accounts for when the buffer is empty and filled with 0-times.
            // 이 데이터가 컷오프 시간 내에 있으면 계산에 포함하십시오.
            // 이것은 또한 버퍼가 비어 있고 0 번으로 채워지는 경우를 설명합니다.
            if (dataWriteTimes[index] > cutoff && lastTime > 0) {
                // Track the total time, using the previous time as our timeperiod.
                // 이전 시간을 시간으로 사용하여 총 시간을 추적합니다.
                totalTime += dataWriteTimes[index] - lastTime;
                totalBytes += dataWriteAmounts[index];
            }

            // Track the last time sample for doing timespan calculations
            // 시간 경과 계산을위한 마지막 샘플 추적
            lastTime = dataWriteTimes[index];

            // Increment and wrap the index if necessary.
            // 필요하다면 인덱스를 증가시키고 감싼다.
            if (++index == dataRateBufferSize)
            {
                index = 0;
            }
        }

        // Return the final calculated value in bits / s, converted from bytes/ms.
        // 마지막 계산 된 값을 바이트 / 초에서 변환 된 비트 / 초로 반환합니다.
        qint64 dataRate = (totalTime != 0)?(qint64)((float)totalBytes * 8.0f / ((float)totalTime / 1000.0f)):0;

        // Finally return our calculated data rate.
        // 마지막으로 계산 된 데이터 전송률을 반환합니다.
        return dataRate;
    }

    static int getNextLinkId() {
        static int nextId = 1;
        return nextId++;
    }

protected slots:

    /**
     * @brief Read a number of bytes from the interface.
     *
     * @param bytes The pointer to write the bytes to
     * @param maxLength The maximum length which can be written
     **/
    /**
     * @brief 인터페이스에서 여러 바이트를 읽습니다.
     *
     * @param bytes 바이트를 기입하는 포인터.
     * @param maxLength 쓸 수있는 최대 길이
     **/
    virtual void readBytes() = 0;

};

#endif // _LINKINTERFACE_H_
