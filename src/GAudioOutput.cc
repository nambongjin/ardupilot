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
 *   @brief Implementation of audio output
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include "logging.h"
#include "configuration.h"
#include "GAudioOutput.h"
#include "MG.h"

#include <QApplication>
#include <QSettings>
#include <QTemporaryFile>

#ifdef Q_OS_MAC
#include <ApplicationServices/ApplicationServices.h>
#endif

// Speech synthesis is only supported with MSVC compiler	 음성 합성은 MSVC 컴파일러에서만 지원됩니다.  
#if _MSC_VER2
// Documentation: http://msdn.microsoft.com/en-us/library/ee125082%28v=VS.85%29.aspx	 Documentation : http://msdn.microsoft.com/en-us/library/ee125082%28v=VS.85%29.aspx  
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override something,
//but do not change the name of _Module

/*
// CComModule에서 클래스를 파생시키고 무언가를 무효화하려면 클래스를 사용할 수 있습니다.
// 하지만 _Module의 이름은 변경하지 않습니다.
*/

extern CComModule _Module;
#include <atlcom.h>

#include <sapi.h>

//using System;
//using System.Speech.Synthesis;

/*
// using System;
// using System.Speech.Synthesis;
*/

#endif

#if defined(FLITE_AUDIO_ENABLED)
extern "C" {
#include <flite/flite.h>
    cst_voice* register_cmu_us_kal(const char* voxdir);
};
#endif



/**
 * This class follows the singleton design pattern
 * @see http://en.wikipedia.org/wiki/Singleton_pattern
 * A call to this function thus returns the only instance of this object
 * the call can occur at any place in the code, no reference to the
 * GAudioOutput object has to be passed.
 */

/*
 *이 클래스는 싱글 톤 디자인 패턴을 따릅니다.
 * @ http://en.wikipedia.org/wiki/Singleton_pattern 참조
 *이 함수를 호출하면이 객체의 유일한 인스턴스가 반환됩니다.
 * 호출은 코드의 어느 위치에서나 발생할 수 있으며
 * GAudioOutput 객체가 전달되어야합니다.
*/

GAudioOutput* GAudioOutput::instance()
{
    static GAudioOutput* _instance = 0;
    if(_instance == 0)
    {
        _instance = new GAudioOutput();
        // Set the application as parent to ensure that this object
        // will be destroyed when the main application exits

/*
        // 이 객체를 보장하기 위해 응용 프로그램을 부모로 설정합니다.
        / / 메인 응용 프로그램이 종료되면 파괴됩니다
*/

        _instance->setParent(qApp);
    }
    return _instance;
}

#define QGC_GAUDIOOUTPUT_KEY QString("QGC_AUDIOOUTPUT_")

GAudioOutput::GAudioOutput(QObject* parent) : QObject(parent),
    voiceIndex(0),
    emergency(false),
    muted(false)
{
    // Load settings

/*
    // 설정로드
*/

    QSettings settings;
    settings.sync();
    muted = settings.value(QGC_GAUDIOOUTPUT_KEY+"muted", muted).toBool();

#ifdef FLITE_AUDIO_ENABLED
    // Remove Phonon Audio for linux and use alsa

/*
    // linux에서 Phonon Audio를 제거하고 alsa를 사용합니다.
*/

    flite_init();

    QLOG_INFO() << "Using Alsa Audio driver";

    // Create shared dir tmp_audio
    // we create new spoken audio files here. we don't delete them as befor.
    // we save audiofiles like message inside.
    // if new messages will create in code this new messages will saved as audio file on first call
    // this save time and also it will possible to queue audio messages later because the are not temporary

/*
    // 공유 디렉토리를 만듭니다. tmp_audio
    // 여기서 새로운 음성 파일을 만듭니다. 우리는 그들을 befor로서 삭제하지 않는다.
    // 메시지와 같은 오디오 파일을 저장합니다.
    // 새 메시지가 코드에서 생성되는 경우이 새 메시지는 첫 번째 호출에서 오디오 파일로 저장됩니다.
    // 이 시간을 절약 할 수 있으며 일시적인 것이 아니기 때문에 나중에 오디오 메시지를 대기열에 넣을 수도 있습니다
*/

    QDir dir(QString("%1/%2").arg( QGC::appDataDirectory() ).arg( "tmp_audio" ));
    if (!dir.exists()) {
        QLOG_WARN() << "Create directory tmp_audio";
        dir.mkpath(".");
    }else
    {
        QLOG_WARN() << "Dir directory tmp_audio exists";
    }

#endif

#ifdef Q_OS_MAC
    m_speech_channel = new SpeechChannel;
    OSErr theErr = NewSpeechChannel(NULL, m_speech_channel);
    if (theErr != noErr)
    {
        QLOG_WARN() << "Creating speech channel failed!";
        delete m_speech_channel;
        m_speech_channel = NULL;
    }
#endif

#if _MSC_VER2

    ISpVoice * pVoice = NULL;
    if (FAILED(::CoInitialize(NULL)))
    {
        QLOG_WARN() << "Creating COM object for audio output failed!";
    }
    else
    {

        HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice;);
        if( SUCCEEDED( hr ) )
        {
            hr = pVoice->Speak(L"Hello world", 0, NULL);
            pVoice->Release();
            pVoice = NULL;
        }
    }
#endif

    // Prepare regular emergency signal, will be fired off on calling startEmergency()

/*
    // 정규 비상 신호를 준비하고 startEmergency ()를 호출하면 해고됩니다.
*/

    emergencyTimer = new QTimer();
    connect(emergencyTimer, SIGNAL(timeout()), this, SLOT(beep()));

    switch (voiceIndex) {
    case 0:
        selectFemaleVoice();
        break;
    default:
        selectMaleVoice();
        break;
    }
}


GAudioOutput::~GAudioOutput()
{
    QLOG_INFO() << "~GAudioOutput()";
#ifdef Q_OS_LINUX
    // wait until thread is running before terminate AlsaAudio thread

/*
    // 스레드가 실행될 때까지 기다렸다가 AlsaAudio 스레드를 종료합니다.
*/

    AlsaAudio::instance(this)->wait();
#endif
#ifdef Q_OS_MAC
    if(m_speech_channel)
    {
        DisposeSpeechChannel(*m_speech_channel);
    };
    delete m_speech_channel;
    m_speech_channel = NULL;
#endif
//#ifdef _MSC_VER2
// ::CoUninitialize();
//#endif
}

void GAudioOutput::mute(bool mute)
{
    if (mute != muted)
    {
        this->muted = mute;
        QSettings settings;
        settings.setValue(QGC_GAUDIOOUTPUT_KEY+"muted", this->muted);
        settings.sync();
        emit mutedChanged(muted);
    }
}

bool GAudioOutput::isMuted()
{
    return this->muted;
}

bool GAudioOutput::say(QString text, int severity)
{
    if (!muted)
    {
        if (text.compare("system %1") == 0)
            //don't say system %1 [HACK] :(	 시스템 % 1을 말하지 않습니다. [해킹] :(  
            return true;

        // TODO Add severity filter	 TODO 심각도 필터 추가  
        Q_UNUSED(severity);
        bool res = false;
        if (!emergency)
        {

            // Speech synthesis is only supported with MSVC compiler	  음성 합성은 MSVC 컴파일러에서만 지원됩니다.  
#ifdef _MSC_VER2
            SpeechSynthesizer synth = new SpeechSynthesizer();
            synth.SelectVoice("Microsoft Anna");
            synth.SpeakText(text.toStdString().c_str());
            res = true;
#endif

#ifdef FLITE_AUDIO_ENABLED
            // spokenfilename is the filename created from spoken text	 spokenfilename은 말한 텍스트에서 생성 된 파일 이름입니다.  
            QString spokenFilename = text;
            spokenFilename.replace(QRegExp(" "), "_");
            spokenFilename = QGC::appDataDirectory() + "/tmp_audio/" + spokenFilename + ".wav";

            // alsadriver is a qthread. tmp. files dont work here	 alsadriver는 qthread입니다. tmp. 파일은 여기에서 일하지 않는다.  
            QFile file( spokenFilename );
            if (!file.exists(spokenFilename)){ // if file not exist we create a new one	 파일이 없으면 새로 만듭니다.  
                if (file.open(QIODevice::ReadWrite))
                {
                    QLOG_INFO() << file.fileName() << " file not exist, create a new one";
                    cst_voice *v = register_cmu_us_kal(NULL);
                    cst_wave *wav = flite_text_to_wave(text.toStdString().c_str(), v);
                    cst_wave_save(wav, file.fileName().toStdString().c_str(), "riff");
                    file.close();
                    AlsaAudio::instance(this)->enqueueFilname(file.fileName());
                    if(!AlsaAudio::instance(this)->isRunning())
                        AlsaAudio::instance(this)->start();
                    res = true;
                }
            }else // we open existing file	 기존 파일을 엽니 다.  
            {
                QLOG_INFO() << file.fileName() << " file exist, playing this file";
                AlsaAudio::instance(this)->enqueueFilname(file.fileName());
                if(!AlsaAudio::instance(this)->isRunning())
                    AlsaAudio::instance(this)->start();
                res = true;
            }
#endif

#ifdef Q_OS_MAC
            if(m_speech_channel)
            {
                SpeakCFString(*m_speech_channel, text.toCFString(), NULL);
            }
            res = true;
#endif
        }
        return res;
    }
    else
    {
        return false;
    }
}

/**
 * @param text This message will be played after the alert beep	  * @param text이 메시지는 경고음이 울린 후 재생됩니다.  
 */
bool GAudioOutput::alert(QString text)
{
    if (!emergency || !muted)
    {
        // Play alert sound	 경고음 재생  
        beep();
        // Say alert message	 경고 메시지를 말하십시오.  
        say(text, 2);
        return true;
    }
    else
    {
        return false;
    }
}

void GAudioOutput::notifyPositive()
{
    if (!muted)
    {
        // Use QFile to transform path for all OS	 QFile을 사용하여 모든 OS의 경로를 변환합니다.  
        QFile f(QGC::shareDirectory()+QString("/files/audio/double_notify.wav"));
        //m_media->setCurrentSource(Phonon::MediaSource(f.fileName().toStdString().c_str()));
        //m_media->play();
    }
}

void GAudioOutput::notifyNegative()
{
    if (!muted)
    {
        // Use QFile to transform path for all OS	 QFile을 사용하여 모든 OS의 경로를 변환합니다.  
        QFile f(QGC::shareDirectory()+QString("/files/audio/flat_notify.wav"));
        //m_media->setCurrentSource(Phonon::MediaSource(f.fileName().toStdString().c_str()));
        //m_media->play();
    }
}

/**
 * The emergency sound will be played continously during the emergency.
 * call stopEmergency() to disable it again. No speech synthesis or other
 * audio output is available during the emergency.
 *
 * @return true if the emergency could be started, false else
 */

/*
 * 비상 사태시 비상 사태가 계속 재생됩니다.
* stopEmergency ()를 호출하여 다시 비활성화합니다. 음성 합성 또는 기타 없음
 * 오디오 출력은 응급 상황에서 사용할 수 있습니다.
 *
 * @return 응급이 시작될 수 있으면 true, 그렇지 않으면 false
*/

bool GAudioOutput::startEmergency()
{
    if (!emergency)
    {
        emergency = true;
        // Beep immediately and then start timer	 // 즉시 경고음을 울리고 타이머를 시작하십시오.  
        if (!muted) beep();
        emergencyTimer->start(1500);
        QTimer::singleShot(5000, this, SLOT(stopEmergency()));
    }
    return true;
}

/**
 * Stops the continous emergency sound. Use startEmergency() to start
 * the emergency sound.
 *
 * @return true if the emergency could be stopped, false else
 */

/*
* 연속 비상 소리를 멈 춥니 다. 시작하려면 startEmergency ()를 사용하십시오.
 * 비상 소리.
 *
 * @return 비상 사태가 정지 할 수있는 경우는 true, 그렇지 않은 경우는 false
*/

bool GAudioOutput::stopEmergency()
{
    if (emergency) {
        emergency = false;
        emergencyTimer->stop();
    }
    return true;
}

void GAudioOutput::beep()
{
    if (!muted)
    {
        // Use QFile to transform path for all OS	 QFile을 사용하여 모든 OS의 경로를 변환합니다.  
        QFile f(QGC::shareDirectory()+QString("/files/audio/alert.wav"));

#ifdef Q_OS_LINUX
        AlsaAudio::instance(this)->enqueueFilname(f.fileName());
        if(!AlsaAudio::instance(this)->isRunning())
            AlsaAudio::instance(this)->start();
#endif

    }
}

void GAudioOutput::selectFemaleVoice()
{
#ifdef Q_OS_LINUX
    //this->voice = register_cmu_us_slt(NULL);
#endif
}

void GAudioOutput::selectMaleVoice()
{
#ifdef Q_OS_LINUX
    //this->voice = register_cmu_us_rms(NULL);
#endif
}

/*
void GAudioOutput::selectNeutralVoice()
{
#ifdef Q_OS_LINUX
    this->voice = register_cmu_us_awb(NULL);
#endif
}*/

QStringList GAudioOutput::listVoices(void)
{
    QStringList l;
#ifdef FLITE_AUDIO_ENABLED
    cst_voice *voice;
    const cst_val *v;



    printf("Voices available: ");
    for (v=flite_voice_list; v; v=val_cdr(v)) {
        voice = val_voice(val_car(v));
        QString s;
        s.sprintf("%s",voice->name);
        printf("%s",voice->name);
        l.append(s);
    }
    printf("\n");

#endif
    return l;

}
