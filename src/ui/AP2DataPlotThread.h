/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2016 APM_PLANNER PROJECT <http://www.ardupilot.com>

This file is part of the APM_PLANNER project

    APM_PLANNER is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    APM_PLANNER is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with APM_PLANNER. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/
/**
 * @file
 *   @brief AP2DataPlot log loader thread
 *
 *   @author Michael Carpenter <malcom2073@gmail.com>
 *   @author Arne Wischmann <wischmann-a@gmx.de>
 */


#ifndef AP2DATAPLOTTHREAD_H
#define AP2DATAPLOTTHREAD_H

#include <QThread>
#include "Loghandling/IParserCallback.h"
#include "Loghandling/ILogParser.h"

#include "Loghandling/LogdataStorage.h"

/**
 * @brief The AP2DataPlotThread class provides the infrastucture for log parsing.
 *        It handles the thread and the signals and selects the parser type.
 */
class AP2DataPlotThread : public QThread, public IParserCallback
{
    Q_OBJECT
public:

    /**
     * @brief AP2DataPlotThread - CTOR
     * @param model - Pointer to the AP2DataPlot2DModel data stucture
     */
    /**
     * @brief AP2DataPlotThread 클래스는 로그 구문 분석을위한 인프라를 제공합니다.
     * 스레드와 신호를 처리하고 파서 유형을 선택합니다.
     */ 
    explicit AP2DataPlotThread(LogdataStorage::Ptr storagePtr, QObject *parent = 0);

    /**
     * @brief ~AP2DataPlotThread - DTOR
     */
    /**
     * @brief AP2DataPlotThread - CTOR
     * @param model - AP2DataPlot2DModel 데이터 구조의 포인터
     */
    ~AP2DataPlotThread();

    /**
     * @brief loadFile starts the parsing of file
     * @param file - filename of the file to parse
     */
    /**
     * @briefloadFile은 파일의 구문 분석을 시작합니다.
     * @param file - 해석하는 파일의 이름
     */
    void loadFile(const QString& file);

    /**
     * @brief stopLoad stops the parsing process and forces
     *        the parser to return immediately
     */
    /**
     * @brief stopLoad는 구문 분석 프로세스를 중지하고 강제 실행합니다.
     파서가 즉시 반환합니다.
     */
    void stopLoad();

    /**
     * @copydoc IParserCallback::onProgress
     */
    virtual void onProgress(const qint64 pos, const qint64 size);

    /**
     * @copydoc IParserCallback::onError
     */
    virtual void onError(const QString &errorMsg);

signals:
    void startLoad();                           /// Emited as soon as log parsing starts
                                                /// 로그 구문 분석이 시작되면 즉시 방출됩니다.
    void loadProgress(qint64 pos, qint64 size); /// Emited to show parsing progress
                                                /// 구문 분석 진행을 표시하기 위해 Emited
    void done(AP2DataPlotStatus state);         /// Emited as soon as the parsing is done
                                                /// 파싱이 끝나자 마자 나왔다.
    void error(QString errorstr);               /// Emited on parsing error
                                                /// 파싱 ​​오류시 발생 함
private:

    QString m_fileName;     /// Filename of the file to be parsed
                            /// 파싱 할 파일의 파일 이름
    bool m_stop;            /// true if parsing shall be stopped
                            /// 구문 분석을 중지해야하는 경우 true

    LogdataStorage::Ptr m_dataStoragePtr;   /// Pointer to the datamodel for storing the data
                                            /// 데이터를 저장하기위한 데이터 모델에 대한 포인터
    ILogParser         *mp_logParser;   /// Pointer to active parser use to pass stop command
                                        /// stop 명령을 전달하기 위해 활성 구문 분석기에 대한 포인터
    void run();             /// from QThread - the thread;
    bool isMainThread();    /// from QThread - 쓰레드;

};




#endif // AP2DATAPLOTTHREAD_H
