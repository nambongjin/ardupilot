/*===================================================================
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
 *   @brief Implementation of class LogCompressor. This class reads in a file containing messages and translates it into a tab-delimited CSV file.
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */
/**
 * @file
 * class LogCompressor 클래스의 구현입니다. 이 클래스는 메시지가 포함 된 파일을 읽어 탭으로 구분 된 CSV 파일로 변환합니다.
 * @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTemporaryFile>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>
#include <QList>
#include "LogCompressor.h"



/**
 * Initializes all the variables necessary for a compression run. This won't actually happen
 * until startCompression(...) is called.
 */
/**
 * 압축 실행에 필요한 모든 변수를 초기화합니다. 이것은 실제로 일어나지 않을 것이다.
 startCompression (...)이 호출 될 때까지 *.
 */
LogCompressor::LogCompressor(QString logFileName, QString outFileName, QString delimiter) :
	logFileName(logFileName),
	outFileName(outFileName),
	running(true),
	currentDataLine(0),
    delimiter(delimiter),
    holeFillingEnabled(true)
{
}

void LogCompressor::run()
{
	// Verify that the input file is useable
        // 입력 파일을 사용할 수 있는지 확인합니다.
	QFile infile(logFileName);
	if (!infile.exists() || !infile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		emit logProcessingStatusChanged(tr("Log Compressor: Cannot start/compress log file, since input file %1 is not readable").arg(QFileInfo(infile.fileName()).absoluteFilePath()));
		return;
	}

//    outFileName = logFileName;

    QString outFileName;

    QStringList parts = QFileInfo(infile.fileName()).absoluteFilePath().split(".", QString::SkipEmptyParts);

    parts.replace(0, parts.first() + "_compressed");
    parts.replace(parts.size()-1, "txt");
    outFileName = parts.join(".");

	// Verify that the output file is useable
        // 출력 파일을 사용할 수 있는지 확인합니다.
    QFile outTmpFile(outFileName);
    if (!outTmpFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
		emit logProcessingStatusChanged(tr("Log Compressor: Cannot start/compress log file, since output file %1 is not writable").arg(QFileInfo(outTmpFile.fileName()).absoluteFilePath()));
		return;
	}


	// First we search the input file through keySearchLimit number of lines
	// looking for variables. This is neccessary before CSV files require
	// the same number of fields for every line.
        // 먼저 keySearchLimit을 통해 입력 파일을 검색합니다.
	// 변수를 찾습니다. CSV 파일을 만들기 전에 필요합니다.
	// 모든 줄마다 같은 수의 필드.
	const unsigned int keySearchLimit = 15000;
	unsigned int keyCounter = 0;
	QTextStream in(&infile);
	QMap<QString, int> messageMap;

	while (!in.atEnd() && keyCounter < keySearchLimit) {
		QString messageName = in.readLine().split(delimiter).at(2);
		messageMap.insert(messageName, 0);
		++keyCounter;
	}

	// Now update each key with its index in the output string. These are
	// all offset by one to account for the first field: timestamp_ms.
        // 이제 각 키를 출력 문자열의 인덱스로 업데이트하십시오. 이것들은
	// 첫 번째 필드 인 timestamp_ms를 고려하여 1 씩 오프셋됩니다.
    QMap<QString, int>::iterator i = messageMap.begin();
	int j;
	for (i = messageMap.begin(), j = 1; i != messageMap.end(); ++i, ++j) {
		i.value() = j;
	}

	// Open the output file and write the header line to it
        // 출력 파일을 열고 헤더 행을 출력한다.
	QStringList headerList(messageMap.keys());

	QString headerLine = "timestamp_ms" + delimiter + headerList.join(delimiter) + "\n";
    // Clean header names from symbols Matlab considers as Latex syntax
    // Matlab이 라텍스 구문으로 간주하는 기호에서 헤더 이름을 지 웁니다.
    headerLine = headerLine.replace("timestamp", "TIMESTAMP");
    headerLine = headerLine.replace(":", "");
    headerLine = headerLine.replace("_", "");
    headerLine = headerLine.replace(".", "");
	outTmpFile.write(headerLine.toLocal8Bit());

    emit logProcessingStatusChanged(tr("Log compressor: Dataset contains dimensions: ") + headerLine);

    // Template list stores a list for populating with data as it's parsed from messages.
    // 템플릿 목록은 메시지에서 파싱 된 데이터로 채울 목록을 저장합니다.
    QStringList templateList;
    for (int i = 0; i < headerList.size() + 1; ++i) {
        templateList << (holeFillingEnabled?"NaN":"");
    }


//	// Reset our position in the input file before we start the main processing loop.
//    in.seek(0);

//    // Search through all lines and build a list of unique timestamps
//    QMap<quint64, QStringList> timestampMap;
//    while (!in.atEnd()) {
//        quint64 timestamp = in.readLine().split(delimiter).at(0).toULongLong();
//        timestampMap.insert(timestamp, templateList);
//    }
// 	기본 처리 루프를 시작하기 전에 입력 파일에서 위치를 재설정합니다.
//     in.seek (0);

//     // 모든 행을 검색하고 고유 한 타임 스탬프 목록을 작성합니다.
//     QMap <quint64, QStringList> timestampMap;
//     while (! in.atEnd ()) {
//         quint64 timestamp = in.readLine (). split (구분 기호) .at (0) .toULongLong ();
//         timestampMap.insert (timestamp, templateList);
//     }

    // Jump back to start of file
    // 파일의 처음으로 돌아 가기
    in.seek(0);

    // Map of final output lines, key is time
   // 최종 출력 행의 맵, 키는 시간입니다. 
   QMap<quint64, QStringList> timestampMap;

    // Run through the whole file and fill map of timestamps
    // 전체 파일을 실행하고 타임 스탬프의 맵을 채 웁니다.
    while (!in.atEnd()) {
        QStringList newLine = in.readLine().split(delimiter);
        quint64 timestamp = newLine.at(0).toULongLong();

        // Check if timestamp does exist - if not, add it
        // 타임 스탬프가 존재하는지 확인 - 그렇지 않으면 추가
        if (!timestampMap.contains(timestamp)) {
            timestampMap.insert(timestamp, templateList);
        }

        QStringList list = timestampMap.value(timestamp);

        QString currentDataName = newLine.at(2);
        QString currentDataValue = newLine.at(3);
        list.replace(messageMap.value(currentDataName), currentDataValue);
        timestampMap.insert(timestamp, list);
    }

    int lineCounter = 0;

    QStringList lastList = timestampMap.values().at(1);

    foreach (QStringList list, timestampMap.values()) {
        // Write this current time set out to the file
        // only do so from the 2nd line on, since the first
        // line could be incomplete
        // 파일에 설정된이 현재 시간을 씁니다.
        // 첫 번째 줄부터 두 번째 줄부터 만 수행하십시오.
        // 라인이 불완전 할 수 있습니다.
        if (lineCounter > 1) {
            // Set the timestamp
            // 타임 스탬프를 설정합니다.
            list.replace(0,QString("%1").arg(timestampMap.keys().at(lineCounter)));

            // Fill holes if necessary
            // 필요한 경우 구멍을 채 웁니다.
            if (holeFillingEnabled) {
                int index = 0;
                foreach (QString str, list) {
                    if (str == "" || str == "NaN") {
                        list.replace(index, lastList.at(index));
                    }
                    index++;
                }
            }

            // Set last list
            // 마지막 목록 설정
            lastList = list;

            // Write data columns
            // 데이터 열 쓰기
            QString output = list.join(delimiter) + "\n";
            outTmpFile.write(output.toLocal8Bit());
        }
        lineCounter++;
    }

	// We're now done with the source file
        // 이제 소스 파일을 다 끝냈습니다.
	infile.close();

    emit logProcessingStatusChanged(tr("Log Compressor: Writing output to file %1").arg(QFileInfo(outFileName).absoluteFilePath()));

	// Clean up and update the status before we return.
        // 반환하기 전에 상태를 정리하고 업데이트합니다.
	currentDataLine = 0;
    emit logProcessingStatusChanged(tr("Log compressor: Finished processing file: %1").arg(outFileName));
	emit finishedFile(outFileName);
	running = false;
}

/**
 * @param holeFilling If hole filling is enabled, the compressor tries to fill empty data fields with previous
 * values from the same variable (or NaN, if no previous value existed)
 */
/**
 * @param holeFilling 구멍 채우기가 활성화 된 경우 압축기는 빈 데이터 필드를 이전
 * 동일한 변수의 값 (이전 값이없는 경우 NaN)
 */
void LogCompressor::startCompression(bool holeFilling)
{
	holeFillingEnabled = holeFilling;
	start();
}

bool LogCompressor::isFinished()
{
	return !running;
}

int LogCompressor::getCurrentLine()
{
	return currentDataLine;
}
