#include "logging.h"
#include "MAVLinkSimulationMAV.h"

#include <cmath>
#include <qmath.h>
#include <QGC.h>

MAVLinkSimulationMAV::MAVLinkSimulationMAV(MAVLinkSimulationLink *parent, int systemid, double lat, double lon, int version) :
    QObject(parent),
    link(parent),
    planner(parent, systemid),
    systemid(systemid),
    timer25Hz(0),
    timer10Hz(0),
    timer1Hz(0),
    latitude(lat),
    longitude(lon),
    altitude(550.0),
    x(lat),
    y(lon),
    z(altitude),
    roll(0.0),
    pitch(0.0),
    yaw(0.0),
    rollspeed(0.0),
    pitchspeed(0.0),
    yawspeed(0.0),
    globalNavigation(true),
    firstWP(false),
    //    previousSPX(8.548056),
    //    previousSPY(47.376389),
    //    previousSPZ(550),
    //    previousSPYaw(0.0),
    //    nextSPX(8.548056),
    //    nextSPY(47.376389),
    //    nextSPZ(550),
    previousSPX(37.480391),
    previousSPY(122.282883),
    previousSPZ(550),
    previousSPYaw(0.0),
    nextSPX(37.480391),
    nextSPY(122.282883),
    nextSPZ(550),
    nextSPYaw(0.0),
    sys_mode(MAV_MODE_PREFLIGHT),
    sys_state(MAV_STATE_STANDBY),
    nav_mode(0),
    flying(false),
    mavlink_version(version)
{
    // Please note: The waypoint planner is running
    // 참고 : 웨이 포인트 플래너가 실행 중입니다.
    connect(&mainloopTimer, SIGNAL(timeout()), this, SLOT(mainloop()));
    connect(&planner, SIGNAL(messageSent(mavlink_message_t)), this, SLOT(handleMessage(mavlink_message_t)));
    connect(link, SIGNAL(messageReceived(mavlink_message_t)), this, SLOT(handleMessage(mavlink_message_t)));
    mainloopTimer.start(20);
    mainloop();
}

void MAVLinkSimulationMAV::mainloop()
{
    // Calculate new simulator values
    //    double maxSpeed = 0.0001; // rad/s in earth coordinate frame

    //        double xNew = // (nextSPX - previousSPX)
    // 새로운 시뮬레이터 값을 계산합니다.
    //     double maxSpeed ​​= 0.0001; // 지구 좌표계의 rad / s

    //         double xNew = // (nextSPX - previousSPX)

    if (flying) {
        sys_state = MAV_STATE_ACTIVE;
        sys_mode = MAV_MODE_AUTO_ARMED;
        nav_mode = 0;
    }

    // 1 Hz execution
    // 1 Hz 실행
    if (timer1Hz <= 0) {
        mavlink_message_t msg;
        mavlink_msg_heartbeat_pack(systemid, MAV_COMP_ID_IMU, &msg, MAV_TYPE_FIXED_WING, MAV_AUTOPILOT_ARDUPILOTMEGA, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        link->sendMAVLinkMessage(&msg);
        planner.handleMessage(msg);

        mavlink_servo_output_raw_t servos;
        servos.time_usec = 0;
        servos.servo1_raw = 1000;
        servos.servo2_raw = 1250;
        servos.servo3_raw = 1400;
        servos.servo4_raw = 1500;
        servos.servo5_raw = 1800;
        servos.servo6_raw = 1500;
        servos.servo7_raw = 1500;
        servos.servo8_raw = 2000;
        servos.port = 1;    // set a fake port number
                            // 가짜 포트 번호를 설정합니다.
        mavlink_msg_servo_output_raw_encode(systemid, MAV_COMP_ID_IMU, &msg, &servos);
        link->sendMAVLinkMessage(&msg);
        timer1Hz = 50;
    }

    // 10 Hz execution
    // 10 Hz 실행
    if (timer10Hz <= 0) {
        double radPer100ms = 0.00006;
        double altPer100ms = 0.4;
        double xm = (nextSPX - x);
        double ym = (nextSPY - y);
        double zm = (nextSPZ - z);

        float zsign = (zm < 0) ? -1.0f : 1.0f;

        if (!(sys_mode & MAV_MODE_FLAG_DECODE_POSITION_HIL))
        {
            if (!firstWP) {
                //float trueyaw = atan2f(xm, ym);

                float newYaw = atan2f(ym, xm);

                if (fabs(yaw - newYaw) < 90) {
                    yaw = yaw*0.7 + 0.3*newYaw;
                } else {
                    yaw = newYaw;
                }

                QLOG_TRACE() << "SIMULATION MAV: x:" << xm << "y:" << ym << "z:" << zm << "yaw:" << yaw;

                //if (sqrt(xm*xm+ym*ym) > 0.0000001)
                if (flying) {
                    x += cos(yaw)*radPer100ms;
                    y += sin(yaw)*radPer100ms;
                    z += altPer100ms*zsign;
                }

                //if (xm < 0.001) xm
            } else {
                x = nextSPX;
                y = nextSPY;
                z = nextSPZ;
                firstWP = false;
                QLOG_TRACE() << "INIT STEP";
            }
        }
        else
        {
            // FIXME Implement heading and altitude controller
            // FIXME 표제와 고도 컨트롤러 구현
        }

        // GLOBAL POSITION
        // 글로벌 위치
        mavlink_message_t msg;
        mavlink_global_position_int_t pos;
        pos.alt = altitude*1000.0;
        pos.lat = longitude*1E7;
        pos.lon = longitude*1E7;
        pos.vx = sin(yaw)*10.0f*100.0f;
        pos.vy = 0;
        pos.vz = altPer100ms*10.0f*100.0f*zsign*-1.0f;
        mavlink_msg_global_position_int_encode(systemid, MAV_COMP_ID_IMU, &msg, &pos);
        link->sendMAVLinkMessage(&msg);
        planner.handleMessage(msg);

        // ATTITUDE
        // 태도
        mavlink_attitude_t attitude;
        attitude.time_boot_ms = 0;
        attitude.roll = roll;
        attitude.pitch = pitch;
        attitude.yaw = yaw;
        attitude.rollspeed = rollspeed;
        attitude.pitchspeed = pitchspeed;
        attitude.yawspeed = yawspeed;

        mavlink_msg_attitude_encode(systemid, MAV_COMP_ID_IMU, &msg, &attitude);
        link->sendMAVLinkMessage(&msg);

        // SYSTEM STATUS
        // 시스템 상태
        mavlink_sys_status_t status;
        
        // Since the simulation outputs global position, attitude and raw pressure we specify that the
        // sensors that would be collecting this information are present, enabled and healthy.
        // 시뮬레이션은 글로벌 위치, 태도 및 원시 압력을 출력하므로 우리는
        // 이 정보를 수집 할 센서가 있으며, 활성화되어 있고 건강합니다.
        
        status.onboard_control_sensors_present = MAV_SYS_STATUS_SENSOR_3D_GYRO |
                                                    MAV_SYS_STATUS_SENSOR_3D_ACCEL |
                                                    MAV_SYS_STATUS_SENSOR_3D_MAG |
                                                    MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE |
                                                    MAV_SYS_STATUS_SENSOR_GPS;
        
        status.onboard_control_sensors_enabled = status.onboard_control_sensors_present;
        status.onboard_control_sensors_health = status.onboard_control_sensors_present;
        status.load = 300;
        status.voltage_battery = 10500;
        status.current_battery = -1;  // -1: autopilot does not measure the current
        status.drop_rate_comm = 0;    // -1 : 자동 조종 장치는 전류를 측정하지 않습니다.
        status.errors_comm = 0;
        status.errors_count1 = 0;
        status.errors_count2 = 0;
        status.errors_count3 = 0;
        status.errors_count4 = 0;
        status.battery_remaining = 90;
        mavlink_msg_sys_status_encode(systemid, MAV_COMP_ID_IMU, &msg, &status);
        link->sendMAVLinkMessage(&msg);
        timer10Hz = 5;

        // VFR HUD
        mavlink_vfr_hud_t hud;
        hud.airspeed = pos.vx/100.0f;
        hud.groundspeed = pos.vx/100.0f;
        hud.alt = altitude;
        hud.heading = static_cast<int>((yaw/M_PI)*180.0f+180.0f) % 360;
        hud.climb = pos.vz/100.0f;
        hud.throttle = 90;
        mavlink_msg_vfr_hud_encode(systemid, MAV_COMP_ID_IMU, &msg, &hud);
        link->sendMAVLinkMessage(&msg);

        // NAV CONTROLLER
        mavlink_nav_controller_output_t nav;
        nav.nav_roll = roll;
        nav.nav_pitch = pitch;
        nav.nav_bearing = yaw;
        nav.target_bearing = yaw;
        nav.wp_dist = 2.0f;
        nav.alt_error = 0.5f;
        nav.xtrack_error = 0.2f;
        nav.aspd_error = 0.0f;
        mavlink_msg_nav_controller_output_encode(systemid, MAV_COMP_ID_IMU, &msg, &nav);
        link->sendMAVLinkMessage(&msg);

        // RAW PRESSURE
        // 원시 압력
        mavlink_raw_pressure_t pressure;
        pressure.press_abs = 1000;
        pressure.press_diff1 = 2000;
        pressure.press_diff2 = 5000;
        pressure.temperature = 18150; // 18.15 deg Celsius
        pressure.time_usec = 0; // Works also with zero timestamp
        mavlink_msg_raw_pressure_encode(systemid, MAV_COMP_ID_IMU, &msg, &pressure);
        link->sendMAVLinkMessage(&msg);
    }

    // 25 Hz execution
    // 25 Hz 실행
    if (timer25Hz <= 0) {
        // The message container to be used for sending
        // 보내는 데 사용할 메시지 컨테이너
        mavlink_message_t ret;

        if (sys_mode & MAV_MODE_FLAG_DECODE_POSITION_HIL)
        {
            mavlink_hil_controls_t hil;
            hil.roll_ailerons = 0.0f;
            hil.pitch_elevator = 0.05f;
            hil.yaw_rudder = 0.05f;
            hil.throttle = 0.6f;
            hil.aux1 = 0.0f;
            hil.aux2 = 0.0f;
            hil.aux3 = 0.0f;
            hil.aux4 = 0.0f;
            hil.mode = MAV_MODE_FLAG_HIL_ENABLED;
            hil.nav_mode = 0;   // not currently used by any HIL consumers
                                // 모든 HIL 소비자가 현재 사용하지 않습니다.
            // Encode the data (adding header and checksums, etc.)
            // 데이터 인코딩 (헤더 및 체크섬 추가 등)
            mavlink_msg_hil_controls_encode(systemid, MAV_COMP_ID_IMU, &ret, &hil);
            // And send it
            // 그리고 그것을 보내라.
            link->sendMAVLinkMessage(&ret);
        }

        // Send actual controller outputs
        // This message just shows the direction
        // and magnitude of the control output
        //        mavlink_position_controller_output_t pos;
        //        pos.x = sin(yaw)*127.0f;
        //        pos.y = cos(yaw)*127.0f;
        //        pos.z = 0;
        //        mavlink_msg_position_controller_output_encode(systemid, MAV_COMP_ID_IMU, &ret, &pos);
        //        link->sendMAVLinkMessage(&ret);

        // Send a named value with name "FLOAT" and 0.5f as value

        // The message container to be used for sending
        //mavlink_message_t ret;
        // The C-struct holding the data to be sent

        // 실제 컨트롤러 출력 보내기
        // 이 메시지는 방향을 보여줍니다.
        // 및 제어 출력의 크기
        //         mavlink_position_controller_output_t pos;
        //         pos.x = sin (요) * 127.0f;
        //         pos.y = cos (요) * 127.0f;
        //         pos.z = 0;
        //         mavlink_msg_position_controller_output_encode (systemid, MAV_COMP_ID_IMU, & ret, & pos);
        //         link-> sendMAVLinkMessage (& ret);

        // 이름이 "FLOAT"이고 값이 0.5f 인 명명 된 값을 전송합니다.

        // 보내는 데 사용할 메시지 컨테이너
        // mavlink_message_t ret;
        // 전송할 데이터를 보유하고있는 C-struct
        mavlink_named_value_float_t val;

        // Fill in the data
        // Name of the value, maximum 10 characters
        // see full message specs at:
        // http://pixhawk.ethz.ch/wiki/mavlink/
        
        // 데이터를 입력하십시오.
        // 값의 이름, 최대 10 자
        // 전체 메시지 스펙보기 :
        // http://pixhawk.ethz.ch/wiki/mavlink/
        strcpy((char *)val.name, "FLOAT");
        // Value, in this case 0.5
        // 값 (이 경우 0.5)
        val.value = 0.5f;

        // Encode the data (adding header and checksums, etc.)
        // 데이터 인코딩 (헤더 및 체크섬 추가 등)
        mavlink_msg_named_value_float_encode(systemid, MAV_COMP_ID_IMU, &ret, &val);
        // And send it
        // 그리고 그것을 보내라.
        link->sendMAVLinkMessage(&ret);

        // MICROCONTROLLER SEND CODE:

        // uint8_t buf[MAVLINK_MAX_PACKET_LEN];
        // int16_t len = mavlink_msg_to_send_buffer(buf, &ret);
        // uart0_transmit(buf, len);


        // SEND INTEGER VALUE

        // We are reusing the "mavlink_message_t ret"
        // "mavlink_message_t ret"를 재사용 중입니다.
        // message buffer

        // The C-struct holding the data to be sent
         // 전송할 데이터를 보유하고있는 C-struct
        mavlink_named_value_int_t valint;

        // Fill in the data
        // Name of the value, maximum 10 characters
        // see full message specs at:
        // http://pixhawk.ethz.ch/wiki/mavlink/

        // 데이터를 입력하십시오.
        // 값의 이름, 최대 10 자
        // 전체 메시지 스펙보기 :
        // http://pixhawk.ethz.ch/wiki/mavlink/
        strcpy((char *)valint.name, "INTEGER");
        // Value, in this case 18000
        // 값 (이 경우 18000)
        valint.value = 18000;

        // Encode the data (adding header and checksums, etc.)
        // 데이터 인코딩 (헤더 및 체크섬 추가 등)
        mavlink_msg_named_value_int_encode(systemid, MAV_COMP_ID_IMU, &ret, &valint);
        // And send it
        // 그리고 그것을 보내라.
        link->sendMAVLinkMessage(&ret);

        // MICROCONTROLLER SEND CODE:

        // uint8_t buf[MAVLINK_MAX_PACKET_LEN];
        // int16_t len = mavlink_msg_to_send_buffer(buf, &ret);
        // uart0_transmit(buf, len);

        timer25Hz = 2;
    }

    timer1Hz--;
    timer10Hz--;
    timer25Hz--;
}

// Uncomment to turn on debug message printing
// 디버그 메시지 인쇄 기능을 해제하려면 주석 처리를 해제하십시오.
//#define DEBUG_PRINT_MESSAGE

#ifdef DEBUG_PRINT_MESSAGE

//static unsigned chan_counts[MAVLINK_COMM_NUM_BUFFERS];


static const unsigned message_lengths[] = MAVLINK_MESSAGE_LENGTHS;
//static unsigned error_count;

mavlink_message_info_t message_info[256] = MAVLINK_MESSAGE_INFO;

static void print_one_field(const mavlink_message_t *msg, const mavlink_field_info_t *f, int idx)
{
#define PRINT_FORMAT(f, def) (f->print_format?f->print_format:def)
    switch (f->type) {
    case MAVLINK_TYPE_CHAR:
        qDebug(PRINT_FORMAT(f, "%c"), _MAV_RETURN_char(msg, f->wire_offset+idx*1));
        break;
    case MAVLINK_TYPE_UINT8_T:
        qDebug(PRINT_FORMAT(f, "%u"), _MAV_RETURN_uint8_t(msg, f->wire_offset+idx*1));
        break;
    case MAVLINK_TYPE_INT8_T:
        qDebug(PRINT_FORMAT(f, "%d"), _MAV_RETURN_int8_t(msg, f->wire_offset+idx*1));
        break;
    case MAVLINK_TYPE_UINT16_T:
        qDebug(PRINT_FORMAT(f, "%u"), _MAV_RETURN_uint16_t(msg, f->wire_offset+idx*2));
        break;
    case MAVLINK_TYPE_INT16_T:
        qDebug(PRINT_FORMAT(f, "%d"), _MAV_RETURN_int16_t(msg, f->wire_offset+idx*2));
        break;
    case MAVLINK_TYPE_UINT32_T:
        qDebug(PRINT_FORMAT(f, "%lu"), (unsigned long)_MAV_RETURN_uint32_t(msg, f->wire_offset+idx*4));
        break;
    case MAVLINK_TYPE_INT32_T:
        qDebug(PRINT_FORMAT(f, "%ld"), (long)_MAV_RETURN_int32_t(msg, f->wire_offset+idx*4));
        break;
    case MAVLINK_TYPE_UINT64_T:
        qDebug(PRINT_FORMAT(f, "%llu"), (unsigned long long)_MAV_RETURN_uint64_t(msg, f->wire_offset+idx*8));
        break;
    case MAVLINK_TYPE_INT64_T:
        qDebug(PRINT_FORMAT(f, "%lld"), (long long)_MAV_RETURN_int64_t(msg, f->wire_offset+idx*8));
        break;
    case MAVLINK_TYPE_FLOAT:
        qDebug(PRINT_FORMAT(f, "%f"), (double)_MAV_RETURN_float(msg, f->wire_offset+idx*4));
        break;
    case MAVLINK_TYPE_DOUBLE:
        qDebug(PRINT_FORMAT(f, "%f"), _MAV_RETURN_double(msg, f->wire_offset+idx*8));
        break;
    }
}

static void print_field(const mavlink_message_t *msg, const mavlink_field_info_t *f)
{
    QLOG_DEBUG() << f->name << ": ";
    if (f->array_length == 0) {
        print_one_field(msg, f, 0);
        QLOG_DEBUG() << " ";
    } else {
        unsigned i;
        /* print an array */
        /* 배열 인쇄 */ 
        if (f->type == MAVLINK_TYPE_CHAR) {
            QLOG_DEBUG() << "'" << f->array_length << "'" <<
                   f->wire_offset+(const char *)_MAV_PAYLOAD(msg);

        } else {
            QLOG_DEBUG() << "[ ";
            for (i=0; i<f->array_length; i++) {
                print_one_field(msg, f, i);
                if (i < f->array_length) {
                    QLOG_DEBUG() << ", ";
                }
            }
            QLOG_DEBUG() << "]";
        }
    }
    QLOG_DEBUG() << " ";
}
#endif

static void print_message(const mavlink_message_t *msg)
{
#ifdef DEBUG_PRINT_MESSAGE
    const mavlink_message_info_t *m = &message_info[msg->msgid];
    const mavlink_field_info_t *f = m->fields;
    unsigned i;
    QLOG_DEBUG() << m->name << " { ";
    for (i=0; i<m->num_fields; i++) {
        print_field(msg, &f[i]);
    }
    QLOG_DEBUG() << "}\n";
#else
    Q_UNUSED(msg);
#endif
}

void MAVLinkSimulationMAV::handleMessage(const mavlink_message_t& msg)
{
    if (msg.sysid != systemid)
    {
        print_message(&msg);
        QLOG_WARN() << "MAV:" << systemid << "RECEIVED MESSAGE FROM" << msg.sysid << "COMP" << msg.compid;
    }

    switch(msg.msgid) {
    case MAVLINK_MSG_ID_ATTITUDE:
        break;
    case MAVLINK_MSG_ID_SET_MODE: {
        mavlink_set_mode_t mode;
        mavlink_msg_set_mode_decode(&msg, &mode);
        if (systemid == mode.target_system) sys_mode = mode.base_mode;
    }
    break;
    case MAVLINK_MSG_ID_HIL_STATE_QUATERNION:
    {
        mavlink_hil_state_quaternion_t state;
        mavlink_msg_hil_state_quaternion_decode(&msg, &state);

        double a = state.attitude_quaternion[0];
        double b = state.attitude_quaternion[1];
        double c = state.attitude_quaternion[2];
        double d = state.attitude_quaternion[3];
        double aSq = a * a;
        double bSq = b * b;
        double cSq = c * c;
        double dSq = d * d;
        float dcm[3][3];
        dcm[0][0] = aSq + bSq - cSq - dSq;
        dcm[0][1] = 2.0 * (b * c - a * d);
        dcm[0][2] = 2.0 * (a * c + b * d);
        dcm[1][0] = 2.0 * (b * c + a * d);
        dcm[1][1] = aSq - bSq + cSq - dSq;
        dcm[1][2] = 2.0 * (c * d - a * b);
        dcm[2][0] = 2.0 * (b * d - a * c);
        dcm[2][1] = 2.0 * (a * b + c * d);
        dcm[2][2] = aSq - bSq - cSq + dSq;

        float phi, theta, psi;
        theta = asin(-dcm[2][0]);

        if (fabs(theta - M_PI_2) < 1.0e-3f) {
            phi = 0.0f;
            psi = (atan2(dcm[1][2] - dcm[0][1],
                    dcm[0][2] + dcm[1][1]) + phi);

        } else if (fabs(theta + M_PI_2) < 1.0e-3f) {
            phi = 0.0f;
            psi = atan2f(dcm[1][2] - dcm[0][1],
                      dcm[0][2] + dcm[1][1] - phi);

        } else {
            phi = atan2f(dcm[2][1], dcm[2][2]);
            psi = atan2f(dcm[1][0], dcm[0][0]);
        }

        roll = phi;
        pitch = theta;
        yaw = psi;
        rollspeed = state.rollspeed;
        pitchspeed = state.pitchspeed;
        yawspeed = state.yawspeed;
        latitude = state.lat;
        longitude = state.lon;
        altitude = state.alt;
    }
    break;
    // FIXME MAVLINKV10PORTINGNEEDED
    //    case MAVLINK_MSG_ID_ACTION: {
    //        mavlink_action_t action;
    //        mavlink_msg_action_decode(&msg, &action);
    //        if (systemid == action.target && (action.target_component == 0 || action.target_component == MAV_COMP_ID_IMU)) {
    //            mavlink_action_ack_t ack;
    //            ack.action = action.action;
    ////            switch (action.action) {
    ////            case MAV_ACTION_TAKEOFF:
    ////                flying = true;
    ////                nav_mode = MAV_NAV_LIFTOFF;
    ////                ack.result = 1;
    ////                break;
    ////            default: {
    ////                ack.result = 0;
    ////            }
    ////            break;
    ////            }

    //            // Give feedback about action
    //            mavlink_message_t r_msg;
    //            mavlink_msg_action_ack_encode(systemid, MAV_COMP_ID_IMU, &r_msg, &ack);
    //            link->sendMAVLinkMessage(&r_msg);
    //        }
    //    }
    break;
//        [REMOVED from AP2]
//    case MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT: {
//        mavlink_set_local_position_setpoint_t sp;
//        mavlink_msg_set_local_position_setpoint_decode(&msg, &sp);
//        if (sp.target_system == this->systemid) {
//            nav_mode = 0;
//            previousSPX = nextSPX;
//            previousSPY = nextSPY;
//            previousSPZ = nextSPZ;
//            nextSPX = sp.x;
//            nextSPY = sp.y;
//            nextSPZ = sp.z;

//            // Rotary wing
//            //nextSPYaw = sp.yaw;

//            // Airplane
//            //yaw = atan2(previousSPX-nextSPX, previousSPY-nextSPY);

//            //if (!firstWP) firstWP = true;
//        }
        QLOG_DEBUG() << "UPDATED SP:" << "X" << nextSPX << "Y" << nextSPY << "Z" << nextSPZ;
//    }
    break;
    }
}
