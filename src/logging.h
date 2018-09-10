//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//    (c) 2016 Author: Arne Wischmann <wischmann-a@gmx.de>
//

#ifndef LOGGING_H
#define LOGGING_H

#include <QDebug>
#include <QtGlobal>
#include <QLoggingCategory>

// Declare the base logging category - creation is done in main.cc	 기본 로깅 카테고리 선언 - main.cc에서 작성 완료
Q_DECLARE_LOGGING_CATEGORY(apmGeneral);

// Define for enabling trace logging. As trace logging is not supported
// by the Qt logging framework the trace level is handeled by the debug level.
// Disabling the NO_TRACE define enabes the trace logging

/*
// 추적 로깅을 사용하도록 정의합니다. 추적 로깅은 지원되지 않으므로
// Qt 로깅 프레임 워크에 의해 트레이스 레벨은 디버그 레벨에 의해 전달됩니다.
// NO_TRACE 정의를 비활성화하면 추적 기록이 가능해집니다.
*/

#define NO_TRACE

// logging macro	 매크로 로깅
#ifdef NO_TRACE
    #define QLOG_TRACE() if(1){} else qDebug()
#else
    #define QLOG_TRACE() qCDebug(apmGeneral)
#endif


// The loglevels which have a corresponding Qt logging class (debug, info, warning) can be disabled
// by using the Qt defines (QT_NO_DEBUG_OUTPUT, QT_NO_INFO_OUTPUT, QT_NO_WARNING_OUTPUT) at
// compile time.

/*
// 해당 Qt 로깅 클래스 (debug, info, warning)가있는 loglevels를 비활성화 할 수 있습니다.
// Qt 정의를 사용하여 (QT_NO_DEBUG_OUTPUT, QT_NO_INFO_OUTPUT, QT_NO_WARNING_OUTPUT)를 정의합니다.
// 컴파일 시간.
*/

#define QLOG_DEBUG() qCDebug(apmGeneral)

// Qt versions below 5.5.0 does not support qInfo() or qcinfo() logging	 5.5 버전 이하의 Qt 버전은 qInfo () 또는 qcinfo () 로깅을 지원하지 않습니다.
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    #define QLOG_INFO() qCDebug(apmGeneral)
#else
    #define QLOG_INFO() qCInfo(apmGeneral)
#endif


#define QLOG_WARN() qCWarning(apmGeneral)

#define QLOG_ERROR() qCCritical(apmGeneral)

#define QLOG_FATAL() qCCritical(apmGeneral)


#endif // LOGGING_H

