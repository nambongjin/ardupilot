/*===================================================================
APM_PLANNER Open Source Ground Control Station

(c) 2017 APM_PLANNER PROJECT <http://www.ardupilot.com>

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
 * @file LogExporter.h
 * @author Arne Wischmann <wischmann-a@gmx.de>
 * @date 28 Jan 2017
 * @brief File providing header for the log exporter classes	 로그 내보내기 클래스 헤더 제공
 */


#ifndef LOGEXPORTER_H
#define LOGEXPORTER_H

#include <QString>

#include "LogdataStorage.h"
#include "src/output/kmlcreator.h"

/**
 * @brief The LogExporterBase class - for different log exporters. It handles
 *        the exporting workflow for every line oriented export.
 *        It provides a progress dialog with a cancel button.
 */

/*
* @brief LogExporterBase 클래스 - 다른 로그 내보내기에 사용됩니다. 핸들
 * 모든 라인 지향 수출을위한 수출 워크 플로우.
 * 취소 버튼이있는 진행 대화 상자를 제공합니다.
*/

class LogExporterBase
{
public:

    /**
     * @brief Shared pointer for LogExporterBase objects	  객체를위한 공유 포인터
     */
    typedef QSharedPointer<LogExporterBase> Ptr;

    /**
     * @brief LogExporterBase - CTOR
     * @param parent - Parent widget needed for progress and info windows.
     */

/*
     * @brief LogExporterBase - CTOR
     * @param parent - 진행 및 정보창에 필요한 부모 위젯.
*/

    explicit LogExporterBase(QWidget *parent);

    /**
     * @brief ~LogExporterBase - DTOR
     */
    virtual ~LogExporterBase();

    /**
     * @brief exportToFile - exports the content of the LogdataStorage pointed by
     *        dataStoragePtr to a file with name fileName.
     * @param fileName - filename for the export
     * @param dataStoragePtr - shared pointer to a filled LogdataStorage
     * @return QString with information about the export. Can be shown to the user.
     */

/*
     * @ brief exportToFile -에 의해 지적 된 LogdataStorage의 내용을 내 보냅니다.
     * dataStoragePtr을 fileName이라는 이름의 파일에 추가하십시오.
     * @param fileName - export의 파일명
     * @param dataStoragePtr - 채워진 LogdataStorage에 대한 공유 포인터
     * @return 내보내기에 대한 정보가있는 QString. 사용자에게 보여 질 수있다.
*/

    QString exportToFile(const QString &fileName, LogdataStorage::Ptr dataStoragePtr);

protected:

    QString m_ExportResult; /// String containing the result of the export	 내보내기 결과를 포함하는 문자열

private:

    QWidget *mp_parent; /// pointer to parent widget - do not delete	 부모 위젯에 대한 포인터 - 삭제하지 않음

    /**
     * @brief startExport - must be implemented by derived classes. It has to setup
     *        all preconditions needed to call writeline afterwards.
     * @param fileName - filename for the export
     * @return true on success, false otherwise
     */

/*
     * @brief startExport - 파생 클래스에 의해 구현되어야합니다. 설치가 필요하다.
     * 나중에 서면으로 전화 할 때 필요한 모든 전제 조건.
     * @param fileName - export의 파일명
     성공했을 경우는 true, 그렇지 않은 경우는 false
*/

    virtual bool startExport(const QString &fileName) = 0;

    /**
     * @brief writeLine - must be implemented by derived classes. Will be called by the
     *        export function for every logline stored in datamodel.
     * @param line - All data as a string
     */

/*
     * @brief writeLine - 파생 클래스에 의해 구현되어야합니다. 에 의해 호출됩니다.
     * 데이터 모델에 저장된 모든 로그 라인에 대한 내보내기 기능.
     * @param line - 모든 데이터를 문자열로
*/

    virtual void writeLine(QString &line) = 0;

    /**
     * @brief endExport - must be implemented by derived classes. Will be called by the
     *        export function at the end of the export process. It should close all used
     *        resources.
     */

/*
     endExport - 파생 클래스에 의해 구현되어야합니다. 에 의해 호출됩니다.
     * 내보내기 프로세스가 끝날 때 내보내기 기능. 사용 된 모든 것을 닫아야합니다.
     * 자원.
*/

    virtual void endExport() = 0;
};

//***********************************************************************

/**
 * @brief The AsciiLogExporter class is used to export a *.log file.	  * @brief AsciiLogExporter 클래스는 * .log 파일을 내보내는 데 사용됩니다.
 */
class AsciiLogExporter : public LogExporterBase
{
public:

    /**
     * @brief Shared pointer for AsciiLogExporter objects	      * @brief AsciiLogExporter 객체를위한 공유 포인터
     */
    typedef QSharedPointer<AsciiLogExporter> Ptr;

    /**
     * @brief AsciiLogExporter - CTOR
     * @param parent - Parent widget needed for progress and info windows.	      * @param parent - 진행 및 정보창에 필요한 부모 위젯.
     */
    AsciiLogExporter(QWidget *parent);

    /**
     * @brief ~AsciiLogExporter - DTOR
     */
    virtual ~AsciiLogExporter();

private:

    QFile m_outputFile;     /// file object for exporting	  내보내기를위한 파일 객체

    /**
     * @brief startExport - Creates and opens the output file
     * @param fileName - file name
     * @return - true on success, false otherwise
     */

/*
     * @brief startExport - 출력 파일을 생성하고 엽니 다.
     * @param fileName - 파일명
     * @return - 성공했을 경우는 true, 그렇지 않은 경우는 false
*/

    virtual bool startExport(const QString &fileName);

    /**
     * @brief writeLine - writes the line directly into the output file.
     * @param line - string to be written to the file
     */

/*
     * @brief writeLine - 출력 파일에 직접 줄을 씁니다.
     * @param line - 파일에 기입 해지는 캐릭터 라인
*/

    virtual void writeLine(QString &line);

    /**
     * @brief endExport - closes the output file	 endExport - 출력 파일을 닫습니다.
     */
    virtual void endExport();
};

//***********************************************************************

/**
 * @brief The KmlLogExporter class is used to export kml files which can be used
 *        with google earth.
 */

/*
 * @brief KmlLogExporter 클래스는 사용할 수있는 kml 파일을 내보내는 데 사용됩니다.
 Google 어스와 함께 *.
*/

class KmlLogExporter : public LogExporterBase
{
public:

    /**
     * @brief Shared pointer for KmlLogExporter objects	 KmlLogExporter 객체를위한 공유 포인터
     */
    typedef QSharedPointer<KmlLogExporter> Ptr;

    /**
     * @brief KmlLogExporter - CTOR
     * @param parent - Parent widget needed for progress and info windows.
     */

/*
     * @brief KmlLogExporter - CTOR
     * @param parent - 진행 및 정보창에 필요한 부모 위젯.
*/

    KmlLogExporter(QWidget *parent, MAV_TYPE mav_type, double iconInterval);

    /**
     * @brief ~KmlLogExporter - DTOR
     */
    virtual ~KmlLogExporter();

private:

    kml::KMLCreator m_kmlExporter;      /// KML export object	 KML 내보내기 개체

    /**
     * @brief startExport - sets up the kmlExporter.
     * @param fileName - file name to be used by the kmlExporter
     * @return
     */

/*
     * @brief startExport - kmlExporter를 설정합니다.
     * @param fileName - kmlExporter에서 사용할 파일 이름입니다.
*/

    virtual bool startExport(const QString &fileName);

    /**
     * @brief writeLine - gives the line to kmlExporter which extracts the
     *        neede data.
     * @param line - data to be analyzed
     */

/*
     * @brief writeLine - kmlExporter에 줄을 지정합니다.
     * 데이터가 필요합니다.
     * @param line - 분석 할 데이터
*/

    virtual void writeLine(QString &line);

    /**
     * @brief endExport - exports the data collected by the kmlExporter to
     *        the file.
     */

/*
     * @brief endExport - kmlExporter에서 수집 한 데이터를 다음 위치로 내 보냅니다.
     * 파일.
*/

    virtual void endExport();
};


#endif // LOGEXPORTER_H
