/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Implementation of simulated system link
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/* *
 * @file
 시뮬레이션 시스템 링크의 구현
 *
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
#include "logging.h"
#include "LinkManager.h"
//#include "MAVLinkProtocol.h"
#include "MAVLinkSimulationLink.h"
#include "QGCMAVLink.h"
#include "QGC.h"
#include "MAVLinkSimulationMAV.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <QTime>
#include <QImage>
#include <QFileInfo>

/**
 * Create a simulated link. This link is connected to an input and output file.
 * The link sends one line at a time at the specified sendrate. The timing of
 * the sendrate is free of drift, which means it is stable on the long run.
 * However, small deviations are mixed in to vary the sendrate slightly
 * in order to simulate disturbances on a real communication link.
 *
 * @param readFile The file with the messages to read (must be in ASCII format, line breaks can be Unix or Windows style)
 * @param writeFile The received messages are written to that file
 * @param rate The rate at which the messages are sent (in intervals of milliseconds)
 **/
/* *
* 시뮬레이션 된 링크를 만듭니다. 이 링크는 입력 및 출력 파일에 연결됩니다.
* 링크는 한 번에 한 줄씩 지정된 전송률로 보냅니다. 타이밍은
 * sendrate는 드리프트가 없으므로 장기적으로 안정적입니다.
 * 그러나 약간의 편차가 섞여 센드 비율이 약간 변경됩니다.
 * 실제 통신 링크에서의 교란을 시뮬레이션하기 위해.
 *
 * @param readFile 읽을 메시지가있는 파일 (ASCII 형식이어야하며 줄 바꿈은 Unix 또는 Windows 스타일 일 수 있음)
 * @param writeFile 수신 한 메세지가 그 파일에 기입 해집니다.
 * @param rate 메시지를 보내는 속도 (밀리 초 간격)
* */
MAVLinkSimulationLink::MAVLinkSimulationLink(QString readFile, QString writeFile, int rate) :
    readyBytes(0),
    timeOffset(0)
{
    this->rate = rate;
    _isConnected = false;

    onboardParams = QMap<QString, float>();
    onboardParams.insert("PID_ROLL_K_P", 0.5f);
    onboardParams.insert("PID_PITCH_K_P", 0.5f);
    onboardParams.insert("PID_YAW_K_P", 0.5f);
    onboardParams.insert("PID_XY_K_P", 100.0f);
    onboardParams.insert("PID_ALT_K_P", 0.5f);
    onboardParams.insert("SYS_TYPE", 1);
    onboardParams.insert("SYS_ID", systemId);
    onboardParams.insert("RC4_REV", 0);
    onboardParams.insert("RC5_REV", 1);
    onboardParams.insert("HDNG2RLL_P", 0.7f);
    onboardParams.insert("HDNG2RLL_I", 0.01f);
    onboardParams.insert("HDNG2RLL_D", 0.02f);
    onboardParams.insert("HDNG2RLL_IMAX", 500.0f);
    onboardParams.insert("RLL2SRV_P", 0.4f);
    onboardParams.insert("RLL2SRV_I", 0.0f);
    onboardParams.insert("RLL2SRV_D", 0.0f);
    onboardParams.insert("RLL2SRV_IMAX", 500.0f);

    // Comments on the variables can be found in the header file
    // 변수에 대한 주석은 헤더 파일에서 찾을 수 있습니다.

    simulationFile = new QFile(readFile, this);
    if (simulationFile->exists() && simulationFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        simulationHeader = simulationFile->readLine();
    }
    receiveFile = new QFile(writeFile, this);
    lastSent = QGC::groundTimeMilliseconds();

    if (simulationFile->exists())
    {
        this->name = "Simulation: " + QFileInfo(simulationFile->fileName()).fileName();
    }
    else
    {
        this->name = "MAVLink simulation link";
    }



    // Initialize the pseudo-random number generator
    // 의사 난수 생성기를 초기화합니다.
    srand(QTime::currentTime().msec());
    maxTimeNoise = 0;
    this->id = getNextLinkId();
    LinkManager::instance()->addLink(this);
}

MAVLinkSimulationLink::~MAVLinkSimulationLink()
{
    //TODO Check destructor
    //    fileStream->flush();
    //    outStream->flush();
    // Force termination, there is no
    // need for cleanup since
    // this thread is not manipulating
    // any relevant data
    // TODO 소멸자 검사
    //     fileStream-> flush ();
    //     outStream-> flush ();
    // 강제 종료.
    // 정리 이후에 필요한
    // 이 스레드는 조작하지 않습니다.
    // 관련 데이터
    terminate();
    delete simulationFile;
}

void MAVLinkSimulationLink::run()
{

    status.voltage_battery = 0;
    status.errors_comm = 0;

    system.base_mode = MAV_MODE_PREFLIGHT;
    system.custom_mode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
    system.system_status = MAV_STATE_UNINIT;

    forever
    {
        static quint64 last = 0;

        if (QGC::groundTimeMilliseconds() - last >= rate)
        {
            if (_isConnected)
            {
                mainloop();
                readBytes();
            }
            else
            {
                // Sleep for substantially longer
                // if not connected
                // 실질적으로 더 오래자는
                // 연결되지 않은 경우
                QGC::SLEEP::msleep(500);
            }
            last = QGC::groundTimeMilliseconds();
        }
        QGC::SLEEP::msleep(3);
    }
}

void MAVLinkSimulationLink::sendMAVLinkMessage(const mavlink_message_t* msg)
{
    // Allocate buffer with packet data
    // 패킷 데이터로 버퍼를 할당한다.
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    unsigned int bufferlength = mavlink_msg_to_send_buffer(buf, msg);

    // Pack to link buffer
    // 링크 버퍼에 패킹한다.
    readyBufferMutex.lock();
    for (unsigned int i = 0; i < bufferlength; i++)
    {
        readyBuffer.enqueue(*(buf + i));
    }
    readyBufferMutex.unlock();
}

void MAVLinkSimulationLink::enqueue(uint8_t* stream, uint8_t* index, mavlink_message_t* msg)
{
    // Allocate buffer with packet data
    // 패킷 데이터로 버퍼를 할당한다.
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    unsigned int bufferlength = mavlink_msg_to_send_buffer(buf, msg);
    //add data into datastream
    // 데이터 스트림에 데이터 추가
    memcpy(stream+(*index),buf, bufferlength);
    (*index) += bufferlength;
}

void MAVLinkSimulationLink::mainloop()
{

    // Test for encoding / decoding packets
    // 패킷 인코딩 / 디코딩 테스트

    // Test data stream
    // 테스트 데이터 스트림
    streampointer = 0;

    // Fake system values
    // 가짜 시스템 값

    static float fullVoltage = 4.2f * 3.0f;
    static float emptyVoltage = 3.35f * 3.0f;
    static float voltage = fullVoltage;
    static float drainRate = 0.025f; // x.xx% of the capacity is linearly drained per second// 용량의 x.xx %는 초당 선형으로 배수됩니다

    mavlink_attitude_t attitude;
    memset(&attitude, 0, sizeof(mavlink_attitude_t));
#ifdef MAVLINK_ENABLED_PIXHAWK
    mavlink_raw_aux_t rawAuxValues;
    memset(&rawAuxValues, 0, sizeof(mavlink_raw_aux_t));
#endif
    mavlink_raw_imu_t rawImuValues;
    memset(&rawImuValues, 0, sizeof(mavlink_raw_imu_t));

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int bufferlength;
    mavlink_message_t msg;

    // Timers
    static unsigned int rate1hzCounter = 1;
    static unsigned int rate10hzCounter = 1;
    static unsigned int rate50hzCounter = 1;
    static unsigned int circleCounter = 0;

    // Vary values
    // 값을 다르게합니다.

    // VOLTAGE
    // The battery is drained constantly
    // 전압
    // 배터리가 끊임없이 소모됩니다.
    voltage = voltage - ((fullVoltage - emptyVoltage) * drainRate / rate);
    if (voltage < 3.550f * 3.0f) voltage = 3.550f * 3.0f;

    static int state = 0;

    if (state == 0)
    {
        state++;
    }


    // 50 HZ TASKS
    if (rate50hzCounter == 1000 / rate / 40)
    {
        if (simulationFile->isOpen())
        {
            if (simulationFile->atEnd()) {
                // We reached the end of the file, start from scratch
                // 파일의 끝에 도달했습니다. 처음부터 시작합니다.
                simulationFile->reset();
                simulationHeader = simulationFile->readLine();
            }

            // Data was made available, read one line
            // first entry is the timestamp
            // 데이터를 사용할 수있게 한 줄을 읽습니다.
            // 첫 번째 항목은 타임 스탬프입니다.
            QString values = QString(simulationFile->readLine());
            QStringList parts = values.split("\t");
            QStringList keys = simulationHeader.split("\t");
            QLOG_TRACE() << simulationHeader;
            QLOG_TRACE() << values;
            bool ok;
            static quint64 lastTime = 0;
            static quint64 baseTime = 0;
            quint64 time = QString(parts.first()).toLongLong(&ok, 10);
            // FIXME Remove multiplicaton by 1000
            // FIXME 곱셈을 1000 씩 제거합니다.
            time *= 1000;

            if (ok) {
                if (timeOffset == 0) {
                    timeOffset = time;
                    baseTime = time;
                }

                if (lastTime > time) {
                    // We have wrapped around in the logfile
                    // Add the measurement time interval to the base time
                    // 로그 파일에 랩핑되었습니다.
                    // 기본 시간에 측정 시간 간격을 추가합니다.
                    baseTime += lastTime - timeOffset;
                }
                lastTime = time;

                time = time - timeOffset + baseTime;

                // Gather individual measurement values
                // 개별 측정 값 수집
                for (int i = 1; i < (parts.size() - 1); ++i) {
                    // Get one data field
                    // 하나의 데이터 필드 가져 오기
                    bool res;
                    double d = QString(parts.at(i)).toDouble(&res);
                    if (!res) d = 0;

                    if (keys.value(i, "") == "Accel._X") {
                        rawImuValues.xacc = d;
                    }

                    if (keys.value(i, "") == "Accel._Y") {
                        rawImuValues.yacc = d;
                    }

                    if (keys.value(i, "") == "Accel._Z") {
                        rawImuValues.zacc = d;
                    }
                    if (keys.value(i, "") == "Gyro_Phi") {
                        rawImuValues.xgyro = d;
                        attitude.rollspeed = ((d-29.000)/15000.0)*2.7-2.7-2.65;
                    }

                    if (keys.value(i, "") == "Gyro_Theta") {
                        rawImuValues.ygyro = d;
                        attitude.pitchspeed = ((d-29.000)/15000.0)*2.7-2.7-2.65;
                    }

                    if (keys.value(i, "") == "Gyro_Psi") {
                        rawImuValues.zgyro = d;
                        attitude.yawspeed = ((d-29.000)/3000.0)*2.7-2.7-2.65;
                    }
#ifdef MAVLINK_ENABLED_PIXHAWK
                    if (keys.value(i, "") == "Pressure") {
                        rawAuxValues.baro = d;
                    }

                    if (keys.value(i, "") == "Battery") {
                        rawAuxValues.vbat = d;
                    }
#endif
                    if (keys.value(i, "") == "roll_IMU") {
                        attitude.roll = d;
                    }

                    if (keys.value(i, "") == "pitch_IMU") {
                        attitude.pitch = d;
                    }

                    if (keys.value(i, "") == "yaw_IMU") {
                        attitude.yaw = d;
                    }

                    //Accel._X	Accel._Y	Accel._Z	Battery	Bottom_Rotor	CPU_Load	Ground_Dist.	Gyro_Phi	Gyro_Psi	Gyro_Theta	Left_Servo	Mag._X	Mag._Y	Mag._Z	Pressure	Right_Servo	Temperature	Top_Rotor	pitch_IMU	roll_IMU	yaw_IMU

                }
                // Send out packets
                // 패킷을 전송합니다.


                // ATTITUDE
                // 태도
                attitude.time_boot_ms = time/1000;
                // Pack message and get size of encoded byte string
                // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
                mavlink_msg_attitude_encode(systemId, componentId, &msg, &attitude);
                // Allocate buffer with packet data
                // 패킷 데이터로 버퍼를 할당한다.
                bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                //add data into datastream
                // 데이터 스트림에 데이터 추가
                memcpy(stream+streampointer,buffer, bufferlength);
                streampointer += bufferlength;

                // IMU
                rawImuValues.time_usec = time;
                rawImuValues.xmag = 0;
                rawImuValues.ymag = 0;
                rawImuValues.zmag = 0;
                // Pack message and get size of encoded byte string
                // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
                mavlink_msg_raw_imu_encode(systemId, componentId, &msg, &rawImuValues);
                // Allocate buffer with packet data
                // 패킷 데이터로 버퍼를 할당한다.
                bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                //add data into datastream
             // 데이터 스트림에 데이터 추가
                memcpy(stream+streampointer,buffer, bufferlength);
                streampointer += bufferlength;

                QLOG_TRACE() << "ATTITUDE" << "BUF LEN" << bufferlength << "POINTER" << streampointer;

                QLOG_TRACE() << "REALTIME" << QGC::groundTimeMilliseconds() << "ONBOARDTIME" << attitude.time_boot_ms << "ROLL" << attitude.roll;

            }

        }

        rate50hzCounter = 1;
    }


    // 10 HZ TASKS
    if (rate10hzCounter == 1000 / rate / 9) {
        rate10hzCounter = 1;

        double lastX = x;
        double lastY = y;
        double lastZ = z;
        double hackDt = 0.1f; // 100 ms

        // Move X Position
        // X 위치로 이동
        x = 12.0*sin(((double)circleCounter)/200.0);
        y = 5.0*cos(((double)circleCounter)/200.0);
        z = 1.8 + 1.2*sin(((double)circleCounter)/200.0);

        double xSpeed = (x - lastX)/hackDt;
        double ySpeed = (y - lastY)/hackDt;
        double zSpeed = (z - lastZ)/hackDt;



        circleCounter++;


//        x = (x > 5.0f) ? 5.0f : x;
//        y = (y > 5.0f) ? 5.0f : y;
//        z = (z > 3.0f) ? 3.0f : z;

//        x = (x < -5.0f) ? -5.0f : x;
//        y = (y < -5.0f) ? -5.0f : y;
//        z = (z < -3.0f) ? -3.0f : z;

        // Send back new setpoint
        // 새 설정 값을 되돌려 보냅니다.
        mavlink_message_t ret;
//        [REMOVED] mavlink_msg_local_position_setpoint_pack(systemId, componentId, &ret, MAV_FRAME_LOCAL_NED, spX, spY, spZ, spYaw); // spYaw/180.0*M_PI);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // Send back new position
        // 새로운 위치로 되돌려 보내기
        mavlink_msg_local_position_ned_pack(systemId, componentId, &ret, 0, x, y, -fabs(z), xSpeed, ySpeed, zSpeed);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

//        // GPS RAW
//        mavlink_msg_gps_raw_pack(systemId, componentId, &ret, 0, 3, 47.376417+(x*0.00001), 8.548103+(y*0.00001), z, 0, 0, 2.5f, 0.1f);
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

        // GLOBAL POSITION
        // 글로벌 위치
        mavlink_msg_global_position_int_pack(systemId, componentId, &ret, 0, (473780.28137103+(x))*1E3, (85489.9892510421+(y))*1E3, (z+550.0)*1000.0, (z+550.0)*1000.0-1, xSpeed, ySpeed, zSpeed, yaw);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // GLOBAL POSITION VEHICLE 2
        // 글로벌 포지션 차량 2
        mavlink_msg_global_position_int_pack(systemId+1, componentId+1, &ret, 0, (473780.28137103+(x+0.00001))*1E3, (85489.9892510421+((y/2)+0.00001))*1E3, (z+550.0)*1000.0, (z+550.0)*1000.0-1, xSpeed, ySpeed, zSpeed, yaw);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

//        // ATTITUDE VEHICLE 2
//        mavlink_msg_attitude_pack(54, MAV_COMP_ID_IMU, &ret, 0, 0, 0, atan2((y/2)+0.3, (x+0.002)), 0, 0, 0);
//        sendMAVLinkMessage(&ret);


//        // GLOBAL POSITION VEHICLE 3
//        mavlink_msg_global_position_int_pack(60, componentId, &ret, 0, (473780.28137103+(x/2+0.002))*1E3, (85489.9892510421+((y*2)+0.3))*1E3, (z+590.0)*1000.0, 0*100.0, 0*100.0, 0*100.0);
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

        static int rcCounter = 0;
        if (rcCounter == 2) {
            mavlink_rc_channels_raw_t chan;
            chan.time_boot_ms = 0;
            chan.port = 0;
            chan.chan1_raw = 1000 + ((int)(fabs(x) * 1000) % 2000);
            chan.chan2_raw = 1000 + ((int)(fabs(y) * 1000) % 2000);
            chan.chan3_raw = 1000 + ((int)(fabs(z) * 1000) % 2000);
            chan.chan4_raw = (chan.chan1_raw + chan.chan2_raw) / 2.0f;
            chan.chan5_raw = (chan.chan3_raw + chan.chan4_raw) / 2.0f;
            chan.chan6_raw = (chan.chan3_raw + chan.chan2_raw) / 2.0f;
            chan.chan7_raw = (chan.chan4_raw + chan.chan2_raw) / 2.0f;
            chan.chan8_raw = 0;
            chan.rssi = 100;
            mavlink_msg_rc_channels_raw_encode(systemId, componentId, &msg, &chan);
            // Allocate buffer with packet data
           // 패킷 데이터로 버퍼를 할당한다.
            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
            //add data into datastream
            // 데이터 스트림에 데이터 추가
            memcpy(stream+streampointer,buffer, bufferlength);
            streampointer += bufferlength;
            rcCounter = 0;
        }
        rcCounter++;

    }

    // 1 HZ TASKS
    if (rate1hzCounter == 1000 / rate / 1) {
        // STATE
        static int statusCounter = 0;
        if (statusCounter == 100) {
            system.base_mode = (system.base_mode + 1) % MAV_MODE_ENUM_END;
            statusCounter = 0;
        }
        statusCounter++;

        static int detectionCounter = 6;
        if (detectionCounter % 10 == 0) {
#ifdef MAVLINK_ENABLED_PIXHAWK
            mavlink_pattern_detected_t detected;
            detected.confidence = 5.0f;
            detected.type = 0;  // compiler confused into thinking type is used unitialized, bogus init to silence// 사고 방식에 혼란스러워하는 컴파일러는 unitialized, bogus init을 사용하여 침묵시킨다.

            if (detectionCounter == 10) {
                char fileName[] = "patterns/face5.png";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 0; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 20) {
                char fileName[] = "7";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 1; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 30) {
                char fileName[] = "patterns/einstein.bmp";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 0; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 40) {
                char fileName[] = "F";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 1; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 50) {
                char fileName[] = "patterns/face2.png";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 0; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 60) {
                char fileName[] = "H";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 1; // 0: Pattern, 1: Letter
                detectionCounter = 0;
            }
            detected.detected = 1;
            mavlink_msg_pattern_detected_encode(systemId, componentId, &msg, &detected);
            // Allocate buffer with packet data
            // 패킷 데이터로 버퍼를 할당한다.
            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
            //add data into datastream
            // 데이터 스트림에 데이터 추가
            memcpy(stream+streampointer,buffer, bufferlength);
            streampointer += bufferlength;
            //detectionCounter = 0;
#endif
        }
        detectionCounter++;

        status.voltage_battery = voltage * 1000; // millivolts
        status.load = 33 * detectionCounter % 1000;

        // Pack message and get size of encoded byte string
        // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
        mavlink_msg_sys_status_encode(systemId, componentId, &msg, &status);
        // Allocate buffer with packet data
        // 패킷 데이터로 버퍼를 할당한다.
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // Pack debug text message
        // 디버그 텍스트 메시지 팩
        mavlink_statustext_t text;
        text.severity = 0;
        strcpy((char*)(text.text), "Text message from system 32");
        mavlink_msg_statustext_encode(systemId, componentId, &msg, &text);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        memcpy(stream+streampointer, buffer, bufferlength);
        streampointer += bufferlength;

        /*
        // Pack message and get size of encoded byte string
        mavlink_msg_boot_pack(systemId, componentId, &msg, version);
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;*/

        // HEARTBEAT
        // 심장 박동

        static int typeCounter = 0;
        uint8_t mavType;
        if (typeCounter < 10)
        {
            mavType = MAV_TYPE_QUADROTOR;
        }
        else
        {
            mavType = typeCounter % (MAV_TYPE_GCS);
        }
        typeCounter++;

        // Pack message and get size of encoded byte string
        // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
        mavlink_msg_heartbeat_pack(systemId, componentId, &msg, mavType, MAV_AUTOPILOT_PX4, system.base_mode, system.custom_mode, system.system_status);
        // Allocate buffer with packet data
        // 패킷 데이터로 버퍼를 할당한다.
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        QLOG_TRACE() << "CRC:" << msg.checksum;
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // Pack message and get size of encoded byte string
        // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
        mavlink_msg_heartbeat_pack(systemId+1, componentId+1, &msg, mavType, MAV_AUTOPILOT_GENERIC, system.base_mode, system.custom_mode, system.system_status);
        // Allocate buffer with packet data
        // 패킷 데이터로 버퍼를 할당한다.
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        QLOG_TRACE() << "CRC:" << msg.checksum;
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


        // Send controller states
        // 컨트롤러 상태를 보냅니다.

        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        memcpy(stream+streampointer, buffer, bufferlength);
        streampointer += bufferlength;



//        // HEARTBEAT VEHICLE 2
//         // 심장 박동 차량 2

//        // Pack message and get size of encoded byte string
//        mavlink_msg_heartbeat_pack(54, componentId, &msg, MAV_HELICOPTER, MAV_AUTOPILOT_ARDUPILOTMEGA);
//        // Allocate buffer with packet data
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

//        // HEARTBEAT VEHICLE 3
//         // 심장 박동 차량 3

//        // Pack message and get size of encoded byte string
//        mavlink_msg_heartbeat_pack(60, componentId, &msg, MAV_FIXED_WING, MAV_AUTOPILOT_PX4);
//        // Allocate buffer with packet data
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

        // Pack message and get size of encoded byte string
        // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
        mavlink_msg_sys_status_encode(54, componentId, &msg, &status);
        // Allocate buffer with packet data
        // 패킷 데이터로 버퍼를 할당한다.
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        // 데이터 스트림에 데이터 추가
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        rate1hzCounter = 1;
    }

    // FULL RATE TASKS
    // Default is 50 Hz
    // 전체 요율 작업
    // 기본값은 50Hz입니다.

    /*
    // 50 HZ TASKS
    if (rate50hzCounter == 1000 / rate / 50)
    {

        //streampointer = 0;

        // Attitude

        // Pack message and get size of encoded byte string
        mavlink_msg_attitude_pack(systemId, componentId, &msg, usec, roll, pitch, yaw, 0, 0, 0);
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        rate50hzCounter = 1;
    }*/

    readyBufferMutex.lock();
    for (unsigned int i = 0; i < streampointer; i++) {
        readyBuffer.enqueue(*(stream + i));
    }
    readyBufferMutex.unlock();

    // Increment counters after full main loop
    // 메인 루프가 완료된 후 카운터를 증가시킵니다.
    rate1hzCounter++;
    rate10hzCounter++;
    rate50hzCounter++;
}


qint64 MAVLinkSimulationLink::bytesAvailable()
{
    readyBufferMutex.lock();
    qint64 size = readyBuffer.size();
    readyBufferMutex.unlock();
    return size;
}

void MAVLinkSimulationLink::writeBytes(const char* data, qint64 size)
{
    // Parse bytes
    // 바이트를 파싱합니다.
    mavlink_message_t msg;
    mavlink_status_t comm;

    uint8_t stream[2048];
    int streampointer = 0;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int bufferlength = 0;
    
    // Initialize drop count to 0 so it isn't referenced uninitialized when returned at the bottom of this function
    // 이 함수의 맨 아래에 반환 될 때 초기화되지 않은 것으로 참조되지 않도록 드롭 수를 0으로 초기화합니다.
    comm.packet_rx_drop_count = 0;

    // Output all bytes as hex digits
    // 모든 바이트를 16 진수로 출력합니다.
    for (int i=0; i<size; i++)
    {
        if (mavlink_parse_char(this->id, data[i], &msg, &comm))
        {
            // MESSAGE RECEIVED!
            // 받은 메시지!
            QLOG_TRACE() << "SIMULATION LINK RECEIVED MESSAGE!";
            emit messageReceived(msg);

            switch (msg.msgid)
            {
                // SET THE SYSTEM MODE
                // 시스템 모드 설정
            case MAVLINK_MSG_ID_SET_MODE:
            {
                mavlink_set_mode_t mode;
                mavlink_msg_set_mode_decode(&msg, &mode);
                // Set mode indepent of mode.target
                system.base_mode = mode.base_mode;
            }
            break;
                // [REMOVED from AP2]
//            case MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT:
//            {
//                mavlink_set_local_position_setpoint_t set;
//                mavlink_msg_set_local_position_setpoint_decode(&msg, &set);
//                spX = set.x;
//                spY = set.y;
//                spZ = set.z;
//                spYaw = set.yaw;

//                // Send back new setpoint
//                mavlink_message_t ret;
//                mavlink_msg_local_position_setpoint_pack(systemId, componentId, &ret, MAV_FRAME_LOCAL_NED, spX, spY, spZ, spYaw);
//                bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                //add data into datastream
//                memcpy(stream+streampointer,buffer, bufferlength);
//                streampointer += bufferlength;
//            }
            break;
            // EXECUTE OPERATOR ACTIONS
          // 운영자 액션 실행
            case MAVLINK_MSG_ID_COMMAND_LONG:
            {
                mavlink_command_long_t action;
                mavlink_msg_command_long_decode(&msg, &action);

                QLOG_TRACE() << "SIM" << "received action" << action.command << "for system" << action.target_system;

                // FIXME MAVLINKV10PORTINGNEEDED
//                switch (action.action) {
//                case MAV_ACTION_LAUNCH:
//                    status.status = MAV_STATE_ACTIVE;
//                    status.mode = MAV_MODE_AUTO;
//                    break;
//                case MAV_ACTION_RETURN:
//                    status.status = MAV_STATE_ACTIVE;
//                    break;
//                case MAV_ACTION_MOTORS_START:
//                    status.status = MAV_STATE_ACTIVE;
//                    status.mode = MAV_MODE_LOCKED;
//                    break;
//                case MAV_ACTION_MOTORS_STOP:
//                    status.status = MAV_STATE_STANDBY;
//                    status.mode = MAV_MODE_LOCKED;
//                    break;
//                case MAV_ACTION_EMCY_KILL:
//                    status.status = MAV_STATE_EMERGENCY;
//                    status.mode = MAV_MODE_MANUAL;
//                    break;
//                case MAV_ACTION_SHUTDOWN:
//                    status.status = MAV_STATE_POWEROFF;
//                    status.mode = MAV_MODE_LOCKED;
//                    break;
//                }
            }
            break;
#ifdef MAVLINK_ENABLED_PIXHAWK
            case MAVLINK_MSG_ID_MANUAL_CONTROL: {
                mavlink_manual_control_t control;
                mavlink_msg_manual_control_decode(&msg, &control);
                QLOG_TRACE() << "\n" << "ROLL:" << control.x << "PITCH:" << control.y;
            }
            break;
#endif
            case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
            {
                QLOG_TRACE() << "GCS REQUESTED PARAM LIST FROM SIMULATION";
                mavlink_param_request_list_t read;
                mavlink_msg_param_request_list_decode(&msg, &read);
                if (read.target_system == systemId)
                {
                    // Output all params
                    // Iterate through all components, through all parameters and emit them
                    // 모든 매개 변수를 출력합니다.
                    // 모든 매개 변수를 통해 모든 구성 요소를 반복하고이를 내 보냅니다.
                    QMap<QString, float>::iterator i;
                    // Iterate through all components / subsystems
                    // 모든 구성 요소 / 하위 시스템을 반복합니다.
                    int j = 0;
                    for (i = onboardParams.begin(); i != onboardParams.end(); ++i) {
                        if (j != 5) {
                            // Pack message and get size of encoded byte string
                            // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
                            mavlink_msg_param_value_pack(read.target_system, componentId, &msg, i.key().toStdString().c_str(), i.value(), MAV_PARAM_TYPE_REAL32, onboardParams.size(), j);
                            // Allocate buffer with packet data
                            // 패킷 데이터로 버퍼를 할당한다.
                            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                            //add data into datastream
                          // 데이터 스트림에 데이터 추가
                            memcpy(stream+streampointer,buffer, bufferlength);
                            streampointer+=bufferlength;
                        }
                        j++;
                    }

                    QLOG_TRACE() << "SIMULATION SENT PARAMETERS TO GCS";
                }
            }
                break;
            case MAVLINK_MSG_ID_PARAM_SET:
            {
                // Drop on even milliseconds
                // 밀리 초 단위로 떨어 뜨린다.
                if (QGC::groundTimeMilliseconds() % 2 == 0)
                {
                    QLOG_TRACE() << "SIMULATION RECEIVED COMMAND TO SET PARAMETER";
                    mavlink_param_set_t set;
                    mavlink_msg_param_set_decode(&msg, &set);
                    //                    if (set.target_system == systemId)
                    //                    {
                    QString key = QString((char*)set.param_id);
                    if (onboardParams.contains(key))
                    {
                        onboardParams.remove(key);
                        onboardParams.insert(key, set.param_value);

                        // Pack message and get size of encoded byte string
                      // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
                        mavlink_msg_param_value_pack(set.target_system, componentId, &msg, key.toStdString().c_str(), set.param_value, MAV_PARAM_TYPE_REAL32, onboardParams.size(), onboardParams.keys().indexOf(key));
                        // Allocate buffer with packet data
                        // 패킷 데이터로 버퍼를 할당한다.
                        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                        //add data into datastream
                        // 데이터 스트림에 데이터 추가
                        memcpy(stream+streampointer,buffer, bufferlength);
                        streampointer+=bufferlength;
                    }
                    //                    }
                }
            }
            break;
            case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
            {
                QLOG_TRACE() << "SIMULATION RECEIVED COMMAND TO SEND PARAMETER";
                mavlink_param_request_read_t read;
                mavlink_msg_param_request_read_decode(&msg, &read);
                QByteArray bytes((char*)read.param_id, MAVLINK_MSG_PARAM_REQUEST_READ_FIELD_PARAM_ID_LEN);
                QString key = QString(bytes);
                if (onboardParams.contains(key))
                {
                    float paramValue = onboardParams.value(key);

                    // Pack message and get size of encoded byte string
                    // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
                    mavlink_msg_param_value_pack(read.target_system, componentId, &msg, key.toStdString().c_str(), paramValue, MAV_PARAM_TYPE_REAL32, onboardParams.size(), onboardParams.keys().indexOf(key));
                    // Allocate buffer with packet data
                    // 패킷 데이터로 버퍼를 할당한다.
                    bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                    //add data into datastream
                    // 데이터 스트림에 데이터 추가
                    memcpy(stream+streampointer,buffer, bufferlength);
                    streampointer+=bufferlength;
                    QLOG_TRACE() << "Sending PARAM" << key;
                }
                else if (read.param_index >= 0 && read.param_index < onboardParams.keys().size())
                {
                    key = onboardParams.keys().at(read.param_index);
                    float paramValue = onboardParams.value(key);

                    // Pack message and get size of encoded byte string
                 // 메시지를 팩하고 인코딩 된 바이트 문자열의 크기를 가져옵니다.
                    mavlink_msg_param_value_pack(read.target_system, componentId, &msg, key.toStdString().c_str(), paramValue, MAV_PARAM_TYPE_REAL32, onboardParams.size(), onboardParams.keys().indexOf(key));
                    // Allocate buffer with packet data
                    // 패킷 데이터로 버퍼를 할당한다.
                    bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                    //add data into datastream
                   // 데이터 스트림에 데이터 추가
                    memcpy(stream+streampointer,buffer, bufferlength);
                    streampointer+=bufferlength;
                    QLOG_INFO() << "Sending PARAM #ID" << (read.param_index) << "KEY:" << key;
                }
            }
            break;
            }
        }
    }

    // Log the amount and time written out for future data rate calculations.
    // While this interface doesn't actually write any data to external systems,
    // this data "transmit" here should still count towards the outgoing data rate.
    // 미래의 데이터 속도 계산을 위해 기록 된 양과 시간을 기록하십시오.
    // 이 인터페이스는 실제로 외부 시스템에 데이터를 쓰지 않지만,
    // 여기에있는이 데이터 "전송"은 나가는 데이터 속도를 계산해야합니다.
    QMutexLocker dataRateLocker(&dataRateMutex);
    logDataRateToBuffer(outDataWriteAmounts, outDataWriteTimes, &outDataIndex, size, QDateTime::currentMSecsSinceEpoch());

    readyBufferMutex.lock();
    for (int i = 0; i < streampointer; i++)
    {
        readyBuffer.enqueue(*(stream + i));
    }
    readyBufferMutex.unlock();

    // Update comm status
    // 통신 상태 업데이트
    status.errors_comm = comm.packet_rx_drop_count;

}


void MAVLinkSimulationLink::readBytes()
{
    // Lock concurrent resource readyBuffer
    // 동시 리소스 잠금 readyBuffer
    readyBufferMutex.lock();
    const qint64 maxLength = 2048;
    char data[maxLength];
    qint64 len = qMin((qint64)readyBuffer.size(), maxLength);

    for (unsigned int i = 0; i < len; i++) {
        *(data + i) = readyBuffer.takeFirst();
    }

    QByteArray b(data, len);
    emit bytesReceived(this, b);
    readyBufferMutex.unlock();

    // Log the amount and time received for future data rate calculations.
    // 미래의 데이터 속도 계산을 위해받은 금액과 시간을 기록합니다.
    QMutexLocker dataRateLocker(&dataRateMutex);
    logDataRateToBuffer(inDataWriteAmounts, inDataWriteTimes, &inDataIndex, len, QDateTime::currentMSecsSinceEpoch());

}

/**
 * Disconnect the connection.
 *
 * @return True if connection has been disconnected, false if connection
 * couldn't be disconnected.
 **/
/* *
 * 연결을 끊으십시오.
 *
 * @return 연결이 끊어진 경우 true, 연결되면 false
 * 연결을 끊을 수 없습니다.
* */
bool MAVLinkSimulationLink::disconnect()
{

    if(isConnected())
    {
        //        timer->stop();

        _isConnected = false;

        emit disconnected();
        emit connected(false);

        //exit();
    }

    return true;
}

/**
 * Connect the link.
 *
 * @return True if connection has been established, false if connection
 * couldn't be established.
 **/
/* *
 * 링크를 연결하십시오.
 *
 * @return 접속이 확립되어있는 경우는 true, 접속의 경우는 false
 * 설립 될 수 없었다.
* */
bool MAVLinkSimulationLink::connect()
{
    _isConnected = true;
    emit connected();
    emit connected(true);

    start(LowPriority);
    MAVLinkSimulationMAV* mav1 = new MAVLinkSimulationMAV(this, 1, 37.480391, -122.282883);
    Q_UNUSED(mav1);
//    MAVLinkSimulationMAV* mav2 = new MAVLinkSimulationMAV(this, 2, 47.375, 8.548, 1);
//    Q_UNUSED(mav2);
    //    timer->start(rate);
    return true;
}

/**
 * Connect the link.
 *
 * @param connect true connects the link, false disconnects it
 * @return True if connection has been established, false if connection
 * couldn't be established.
 **/
/* *
 * 링크를 연결하십시오.
 *
 connect @ true는 링크를 연결하고, false는 연결을 끊습니다.
 * @return 접속이 확립되어있는 경우는 true, 접속의 경우는 false
 * 설립 될 수 없었다.
* */
void MAVLinkSimulationLink::connectLink()
{
    this->connect();
}

/**
 * Connect the link.
 *
 * @param connect true connects the link, false disconnects it
 * @return True if connection has been established, false if connection
 * couldn't be established.
 **/
/* *
 * 링크를 연결하십시오.
 *
 connect @ true는 링크를 연결하고, false는 연결을 끊습니다.
 * @return 접속이 확립되어있는 경우는 true, 접속의 경우는 false
 * 설립 될 수 없었다.
* */
bool MAVLinkSimulationLink::connectLink(bool connect)
{
    _isConnected = connect;

    if(connect) {
        this->connect();
    }

    return true;
}

/**
 * Check if connection is active.
 *
 * @return True if link is connected, false otherwise.
 **/
/* *
 * 연결이 활성화되어 있는지 확인하십시오.
 *
 * @return 링크가 연결되어 있으면 true이고, 그렇지 않으면 false입니다.
* */
bool MAVLinkSimulationLink::isConnected() const
{
    return _isConnected;
}

int MAVLinkSimulationLink::getId() const
{
    return id;
}

QString MAVLinkSimulationLink::getName() const
{
    return name;
}

QString MAVLinkSimulationLink::getShortName() const
{
    return name;
}

QString MAVLinkSimulationLink::getDetail() const
{
    return QString("sim");
}

qint64 MAVLinkSimulationLink::getConnectionSpeed() const
{
    /* 100 Mbit is reasonable fast and sufficient for all embedded applications */
    /* 100 Mbit는 모든 임베디드 애플리케이션에 빠르고 적합합니다 */
    return 100000000;
}

qint64 MAVLinkSimulationLink::getCurrentInDataRate() const
{
    return 0;
}

qint64 MAVLinkSimulationLink::getCurrentOutDataRate() const
{
    return 0;
}
