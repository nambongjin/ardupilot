#ifndef QUA_ZIPFILEINFO_H
#define QUA_ZIPFILEINFO_H

/*
Copyright (C) 2005-2011 Sergey A. Tachenov

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

See COPYING file for the full LGPL text.

Original ZIP package is copyrighted by Gilles Vollant, see
quazip/(un)zip.h files for details, basically it's zlib license.
 **/

#include <QByteArray>
#include <QDateTime>
#include <QFile>

#include "quazip_global.h"

/// Information about a file inside archive.
/** Call QuaZip::getCurrentFileInfo() or QuaZipFile::getFileInfo() to
 * fill this structure. */

/*
// / archive 내부의 파일에 대한 정보.
/ * * QuaZip :: getCurrentFileInfo () 또는 QuaZipFile :: getFileInfo ()를 호출하여
*이 구조체를 채우십시오. * /
*/

struct QUAZIP_EXPORT QuaZipFileInfo {
  /// File name.	파일 이름
  QString name;
  /// Version created by.	에 의해 만들어진 버전.
  quint16 versionCreated;
  /// Version needed to extract.	추출 할 버전이 필요합니다.
  quint16 versionNeeded;
  /// General purpose flags.	범용 플래그.
  quint16 flags;
  /// Compression method.	압축 메소드.
  quint16 method;
  /// Last modification date and time.	마지막 수정 날짜 및 시간.
  QDateTime dateTime;
  /// CRC.	CRC.
  quint32 crc;
  /// Compressed file size.	압축 된 파일 크기.
  quint32 compressedSize;
  /// Uncompressed file size.	압축되지 않은 파일 크기.
  quint32 uncompressedSize;
  /// Disk number start.	디스크 번호 start.
  quint16 diskNumberStart;
  /// Internal file attributes.	내부 파일 특성.
  quint16 internalAttr;
  /// External file attributes.	외부 파일 특성.
  quint32 externalAttr;
  /// Comment.	주석.
  QString comment;
  /// Extra field.	추가 필드.
  QByteArray extra;
  /// Get the file permissions.	파일 권한을 얻습니다.
  /**
    Returns the high 16 bits of external attributes converted to
    QFile::Permissions.
    */

/*
    변환 된 외부 속성의 상위 16 비트를 반환합니다.
    QFile :: Permissions.
*/

  QFile::Permissions getPermissions() const;
};

#endif
