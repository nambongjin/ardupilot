/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009, 2010 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

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
 *   @brief Definition of audio output	 오디오 출력의 정의
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef GAUDIOOUTPUT_H
#define GAUDIOOUTPUT_H

#include <QObject>
#include <QTimer>
#include <QStringList>
#include <audio/AlsaAudio.h>
#ifdef Q_OS_MAC
#include <QtMultimedia>
#endif

#ifdef Q_OS_MAC
struct SpeechChannelRecord;
typedef SpeechChannelRecord *           SpeechChannel;
#endif

#ifdef Q_OS_LINUX2
extern "C" {
    cst_voice *REGISTER_VOX(const char *voxdir);
    void UNREGISTER_VOX(cst_voice *vox);
    cst_voice* register_cmu_us_kal16(const char *voxdir);
}
#endif

/**
 * @brief Audio Output (speech synthesizer and "beep" output)	 
 * This class follows the singleton design pattern
 * @see http://en.wikipedia.org/wiki/Singleton_pattern
*/

/*
 * @brief 오디오 출력 (음성 합성기 및 "삐"출력)
 *이 클래스는 싱글 톤 디자인 패턴을 따릅니다.
 * @ http://en.wikipedia.org/wiki/Singleton_pattern 참조
*/

class GAudioOutput : public QObject
{
    Q_OBJECT
public:
    /** @brief Get the singleton instance	 싱글 톤 인스턴스 가져 오기 */
    static GAudioOutput* instance();
    /** @brief List available voices 	 사용 가능한 음성 목록*/
    QStringList listVoices(void);
    enum {
        VOICE_MALE = 0,
        VOICE_FEMALE
    } QGVoice;

    /** @brief Get the mute state	 소거 상태 가져 오기 */
    bool isMuted();

public slots:
    /** @brief Say this text if current output priority matches	 현재 출력 우선 순위가 와 일치하면이 텍스트를 말하십시오 */
    bool say(QString text, int severity=1);
    /** @brief Play alert sound and say notification message 	 알림 소리를 내고 알림 메시지를 말하십시오*/
    bool alert(QString text);
    /** @brief Start emergency sound 	 긴급 사운드 시작*/
    bool startEmergency();
    /** @brief Stop emergency sound 	 긴급 소리를 멈추십시*/
    bool stopEmergency();
    /** @brief Select female voice	 여성 음성 선택   */
    void selectFemaleVoice();
    /** @brief Select male voice 	 남성 음성 선택  */
    void selectMaleVoice();
    /** @brief Play emergency sound once 	 한 번 비상 소리 재생  */
    void beep();
    /** @brief Notify about positive event 	 긍정적 인 사건에 대해 알린다  */
    void notifyPositive();
    /** @brief Notify about negative event 	 부정적인 이벤트에 대한 알림  */
    void notifyNegative();
    /** @brief Mute/unmute sound	 음소거 / 음소거 해제    */
    void mute(bool mute);

signals:
    void mutedChanged(bool);

protected:
#ifdef Q_OS_MAC
    SpeechChannel *m_speech_channel;
#endif
#ifdef Q_OS_LINUX
    //cst_voice* voice; ///< The flite voice object	  cst_voice * 음성; /// <flite 음성 객체  
#endif
    int voiceIndex;   ///< The index of the flite voice to use (awb, slt, rms)	 사용하려는 flite 음성의 색인 (awb, slt, rms)  
    // Phonon::MediaObject* m_media; ///< The output object for audio	 오디오의 출력 객체  
    // Phonon::AudioOutput* m_audioOutput;
    bool emergency;   ///< Emergency status flag	 비상 상태 플래그  
    QTimer* emergencyTimer;
    bool muted;
private:
    GAudioOutput(QObject* parent=NULL);
    ~GAudioOutput();
};

#endif // AUDIOOUTPUT_H
