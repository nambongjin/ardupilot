#ifndef QUA_ZIPNEWINFO_H
#define QUA_ZIPNEWINFO_H

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

#include <QDateTime>
#include <QString>

#include "quazip_global.h"

/// Information about a file to be created.
/** This structure holds information about a file to be created inside
 * ZIP archive. At least name should be set to something correct before
 * passing this structure to
 * QuaZipFile::open(OpenMode,const QuaZipNewInfo&,int,int,bool).
 **/
// 생성 될 파일에 대한 정보.
/* *이 구조체는 내부에 생성 될 파일에 대한 정보를 가지고있다.
* ZIP 아카이브. 적어도 이름은 이전에 올바른 것으로 설정되어야합니다.
 *이 구조를 전달
 * QuaZipFile :: open (OpenMode, const QuaZipNewInfo &, int, int, bool).
* */
struct QUAZIP_EXPORT QuaZipNewInfo {
  /// File name.
  /** This field holds file name inside archive, including path relative
   * to archive root.
   **/
  // / 파일 이름.
  /* *이 필드는 상대 경로를 포함하여 아카이브 내부에 파일 이름을 포함합니다.
   * 아카이브 루트.
   * */
  QString name;
  /// File timestamp.
  /** This is the last file modification date and time. Will be stored
   * in the archive central directory. It is a good practice to set it
   * to the source file timestamp instead of archive creating time. Use
   * setFileDateTime() or QuaZipNewInfo(const QString&, const QString&).
   **/
  // / 파일 타임 스탬프.
  /* * 이것은 마지막 파일 수정 날짜와 시간입니다. 저장 됨
   * 아카이브 중앙 디렉토리에 있습니다. 그것을 설정하는 것이 좋습니다.
   * 아카이브 생성 시간 대신 원본 파일 타임 스탬프에 *. 용도
   * setFileDateTime () 또는 QuaZipNewInfo (const QString &, const QString &)입니다.
   * */
  QDateTime dateTime;
  /// File internal attributes.
  // / 내부 속성 파일.
  quint16 internalAttr;
  /// File external attributes.
  /**
    The highest 16 bits contain Unix file permissions and type (dir or
    file). The constructor QuaZipNewInfo(const QString&, const QString&)
    takes permissions from the provided file.
    */
  // / 외부 특성 파일.
  /* *
    최상위 16 비트는 유닉스 파일 사용 권한과 유형을 포함합니다 (dir 또는
    파일). 생성자 QuaZipNewInfo (const QString &, const QString &)
    제공된 파일에서 권한을 가져옵니다.
    */
  quint32 externalAttr;
  /// File comment.
  /** Will be encoded using QuaZip::getCommentCodec().
   **/
  // / 파일 주석.
  /* * QuaZip :: getCommentCodec ()를 사용하여 인코딩됩니다.
   * */
  QString comment;
  /// File local extra field.
  // 로컬 추가 필드 파일.
  QByteArray extraLocal;
  /// File global extra field.
  // / 전역 추가 필드 파일.
  QByteArray extraGlobal;
  /// Uncompressed file size.
  /** This is only needed if you are using raw file zipping mode, i. e.
   * adding precompressed file in the zip archive.
   **/
  // 압축되지 않은 파일 크기.
  /* * 이것은 원시 파일 압축 모드를 사용하는 경우에만 필요합니다.
   * zip 아카이브에 미리 압축 된 파일을 추가합니다.
   * */
  ulong uncompressedSize;
  /// Constructs QuaZipNewInfo instance.
  /** Initializes name with \a name, dateTime with current date and
   * time. Attributes are initialized with zeros, comment and extra
   * field with null values.
   **/
  // QuaZipNewInfo 인스턴스를 생성합니다.
  /* * 이름을 \ name으로 초기화하고 현재 날짜가있는 dateTime을
   * 시각. 속성은 0, 주석 및 추가로 초기화됩니다.
   * null 값을 가진 필드.
   * */
  QuaZipNewInfo(const QString& name);
  /// Constructs QuaZipNewInfo instance.
  /** Initializes name with \a name. Timestamp and permissions are taken
   * from the specified file. If the \a file does not exists or its timestamp
   * is inaccessible (e. g. you do not have read permission for the
   * directory file in), uses current time and zero permissions. Other attributes are
   * initialized with zeros, comment and extra field with null values.
   * 
   * \sa setFileDateTime()
   **/
  // QuaZipNewInfo 인스턴스를 생성합니다.
  /* * 이름을 \ a로 초기화합니다. 타임 스탬프 및 사용 권한이 적용됩니다.
   * 지정된 파일에서. \ a 파일이 없거나 타임 스탬프
   * 액세스 할 수 없습니다 (예 :
   * 디렉토리 파일에 있음), 현재 시간과 사용 권한을 사용합니다. 다른 속성은 다음과 같습니다.
   * null 값을 갖는 0, 주석 및 추가 필드로 초기화됩니다.
   * 
   * \ sa setFileDateTime ()
   * */
  QuaZipNewInfo(const QString& name, const QString& file);
  /// Sets the file timestamp from the existing file.
  /** Use this function to set the file timestamp from the existing
   * file. Use it like this:
   * \code
   * QuaZipFile zipFile(&zip);
   * QFile file("file-to-add");
   * file.open(QIODevice::ReadOnly);
   * QuaZipNewInfo info("file-name-in-archive");
   * info.setFileDateTime("file-to-add"); // take the timestamp from file
   * zipFile.open(QIODevice::WriteOnly, info);
   * \endcode
   *
   * This function does not change dateTime if some error occured (e. g.
   * file is inaccessible).
   **/
  // 기존 파일에서 파일 타임 스탬프를 설정합니다.
  /* *이 함수를 사용하여 기존의 파일 타임 스탬프를 설정합니다
   * 파일. 다음과 같이 사용하십시오.
   * \ code
   * QuaZipFile zipFile (& zip);
   * QFile 파일 ( "file-to-add");
   * file.open (QIODevice :: ReadOnly);
   * QuaZipNewInfo 정보 ( "파일 이름 - 인 - 아카이브");
   * info.setFileDateTime ( "파일 - 추가"); // 파일에서 타임 스탬프 가져 오기
   * zipFile.open (QIODevice :: WriteOnly, info);
   * \ endcode
   *
   *이 함수는 dateTime을 변경하지 않습니다.
   * 파일에 액세스 할 수 없음).
   * */
  void setFileDateTime(const QString& file);
  /// Sets the file permissions from the existing file.
  /**
    Takes permissions from the file and sets the high 16 bits of
    external attributes. Uses QFileInfo to get permissions on all
    platforms.
    */
  // 기존 파일에서 파일 사용 권한을 설정합니다.
  /* *
    파일에서 권한을 가져와 다음의 상위 16 비트를 설정합니다.
    외부 속성. QFileInfo를 사용하여 모든 사용자에게 권한을 부여합니다.
    플랫폼.
    */
  void setFilePermissions(const QString &file);
  /// Sets the file permissions.
  /**
    Modifies the highest 16 bits of external attributes. The type part
    is set to dir if the name ends with a slash, and to regular file
    otherwise.
    */
  // / 파일 권한을 설정합니다.
  /* *
    외부 속성의 최상위 16 비트를 수정합니다. 유형 부분
    이름이 슬래시로 끝나면 dir로, 일반 파일로 설정됩니다.
    그렇지 않으면.
    */
  void setPermissions(QFile::Permissions permissions);
};

#endif
