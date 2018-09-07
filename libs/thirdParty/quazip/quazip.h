#ifndef QUA_ZIP_H
#define QUA_ZIP_H

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

#include <QString>
#include <QStringList>
#include <QTextCodec>

#include "zip.h"
#include "unzip.h"

#include "quazip_global.h"
#include "quazipfileinfo.h"

// just in case it will be defined in the later versions of the ZIP/UNZIP
// 이후 버전의 ZIP / UNZIP에서 정의 될 경우를 대비하여
#ifndef UNZ_OPENERROR
// define additional error code
// 추가 오류 코드 정의
#define UNZ_OPENERROR -1000
#endif

class QuaZipPrivate;

/// ZIP archive.
/** \class QuaZip quazip.h <quazip/quazip.h>
 * This class implements basic interface to the ZIP archive. It can be
 * used to read table contents of the ZIP archive and retreiving
 * information about the files inside it.
 *
 * You can also use this class to open files inside archive by passing
 * pointer to the instance of this class to the constructor of the
 * QuaZipFile class. But see QuaZipFile::QuaZipFile(QuaZip*, QObject*)
 * for the possible pitfalls.
 *
 * This class is indended to provide interface to the ZIP subpackage of
 * the ZIP/UNZIP package as well as to the UNZIP subpackage. But
 * currently it supports only UNZIP.
 *
 * The use of this class is simple - just create instance using
 * constructor, then set ZIP archive file name using setFile() function
 * (if you did not passed the name to the constructor), then open() and
 * then use different functions to work with it! Well, if you are
 * paranoid, you may also wish to call close before destructing the
 * instance, to check for errors on close.
 *
 * You may also use getUnzFile() and getZipFile() functions to get the
 * ZIP archive handle and use it with ZIP/UNZIP package API directly.
 *
 * This class supports localized file names inside ZIP archive, but you
 * have to set up proper codec with setCodec() function. By default,
 * locale codec will be used, which is probably ok for UNIX systems, but
 * will almost certainly fail with ZIP archives created in Windows. This
 * is because Windows ZIP programs have strange habit of using DOS
 * encoding for file names in ZIP archives. For example, ZIP archive
 * with cyrillic names created in Windows will have file names in \c
 * IBM866 encoding instead of \c WINDOWS-1251. I think that calling one
 * function is not much trouble, but for true platform independency it
 * would be nice to have some mechanism for file name encoding auto
 * detection using locale information. Does anyone know a good way to do
 * it?
 **/
// / ZIP 아카이브.
/* * \ class QuaZip quazip.h <quazip / quazip.h>
*이 클래스는 ZIP 아카이브에 대한 기본 인터페이스를 구현합니다. 그것은 될 수 있습니다
 * ZIP 아카이브의 테이블 내용을 읽고 검색하는 데 사용됩니다.
 * 내부 파일에 대한 정보.
 *
 * 또한이 클래스를 사용하여 아카이브 내에서 파일을 전달할 수 있습니다.
 *이 클래스의 인스턴스를 가리키는 포인터.
* QuaZipFile 클래스. 그러나 QuaZipFile :: QuaZipFile (QuaZip *, QObject *)를 참조하십시오.
 가능한 함정을 위해 *.
 *
 *이 클래스는 ZIP 서브 패키지에 대한 인터페이스를 제공하기 위해 내포되어 있습니다.
* ZIP / UNZIP 패키지뿐만 아니라 UNZIP 하위 패키지. 그러나
 * 현재 UNZIP 만 지원합니다.
 *
 *이 클래스의 사용은 간단합니다.
 * 생성자, setFile () 함수를 사용하여 ZIP 아카이브 파일 이름 설정
 * (생성자에 이름을 전달하지 않은 경우), open () 및
* 그런 다음 다른 기능을 사용하여 작업하십시오! 네가 그렇다면
 * 편집증, 당신은 또한 파괴하기 전에 가까이에 전화하기를 원할 수도 있습니다.
 * 인스턴스, 닫을 때 오류를 확인합니다.
 *
 * getUnzFile () 및 getZipFile () 함수를 사용하여
 * ZIP 보관 처리 및 ZIP / UNZIP 패키지 API와 함께 직접 사용하십시오.
 *
 *이 클래스는 ZIP 아카이브 내에서 지역화 된 파일 이름을 지원하지만
* setCodec () 함수로 적절한 코덱을 설정해야합니다. 기본적으로,
 * 로케일 코덱이 사용됩니다. 이것은 UNIX 시스템에서는 좋지만
* Windows에서 생성 된 ZIP 아카이브로 거의 확실하게 실패합니다. 이
 * Windows ZIP 프로그램이 DOS를 사용하는 이상한 버릇이 있기 때문입니다.
* ZIP 아카이브의 파일 이름 인코딩. 예 : ZIP 아카이브
 * Windows에서 생성 된 키릴 문자 이름은 파일 이름이 \ c
* \ c WINDOWS-1251 대신 IBM866 인코딩. 나는 그걸 부르는 것이
 * 기능은별로 문제가되지 않지만 진정한 플랫폼 독립성을 위해서는
 * 자동으로 파일 이름 인코딩을위한 메커니즘을 갖는 것이 좋을 것입니다.
로케일 정보를 사용하여 탐지. 누구든지 할 수있는 좋은 방법을 알고 있습니까?
 그것?
* */
class QUAZIP_EXPORT QuaZip {
  friend class QuaZipPrivate;
  public:
    /// Useful constants.
    // / 유용한 상수.
    enum Constants {
      MAX_FILE_NAME_LENGTH=256 /**< Maximum file name length. Taken from
                                 \c UNZ_MAXFILENAMEINZIP constant in
                                 unzip.c. */
                               /* * <파일 이름의 최대 길이. 취한
                                 \ UNZ_MAXFILENAMEINZIP 상수
                                 unzip.c. */
    };
    /// Open mode of the ZIP file.
    // ZIP 파일의 열기 모드.
    enum Mode {
      mdNotOpen, ///< ZIP file is not open. This is the initial mode.// / <ZIP 파일이 열려 있지 않습니다. 이것은 초기 모드입니다.
      mdUnzip, ///< ZIP file is open for reading files inside it.// / <내부에 파일을 읽을 수있는 ZIP 파일이 열려 있습니다.
      mdCreate, ///< ZIP file was created with open() call.// / <ZIP 파일이 open () 호출로 생성되었습니다.
      mdAppend, /**< ZIP file was opened in append mode. This refers to
                  * \c APPEND_STATUS_CREATEAFTER mode in ZIP/UNZIP package
                  * and means that zip is appended to some existing file
                  * what is useful when that file contains
                  * self-extractor code. This is obviously \em not what
                  * you whant to use to add files to the existing ZIP
                  * archive.
                  **/
                /* * <ZIP 파일이 추가 모드로 열렸습니다. 이 말은
                  * \ c APPEND_STATUS_CREATEAFTER 모드 (ZIP / UNZIP 패키지)
                  *는 기존 파일에 zip이 추가되었음을 의미합니다.
                  * 그 파일이 포함되어있을 때 유용합니다.
                  * 자기 추출 코드. 이것은 분명히 \ em 무엇하지 않습니다
                  * 기존 ZIP에 파일을 추가하는 데 사용하는 것
                  * 아카이브.
                  * */
      mdAdd ///< ZIP file was opened for adding files in the archive.// / <아카이브에 파일을 추가하기 위해 ZIP 파일이 열렸습니다.
    };
    /// Case sensitivity for the file names.
    /** This is what you specify when accessing files in the archive.
     * Works perfectly fine with any characters thanks to Qt's great
     * unicode support. This is different from ZIP/UNZIP API, where
     * only US-ASCII characters was supported.
     **/
    // / 파일 이름의 대 / 소문자 구분.
    /* * 아카이브에서 파일에 액세스 할 때 지정하는 내용입니다.
     Qt의 위대한 덕분에 모든 문자가 완벽하게 작동합니다.
     * 유니 코드 지원. 이것은 ZIP / UNZIP API와는 다릅니다.
     * US-ASCII 문자 만 지원되었습니다.
     * */
    enum CaseSensitivity {
      csDefault=0, ///< Default for platform. Case sensitive for UNIX, not for Windows.// / <플랫폼의 기본값. UNIX는 대소 문자를 구분하고 Windows는 구분하지 않습니다.
      csSensitive=1, ///< Case sensitive.// / <대소 문자를 구분합니다.
      csInsensitive=2 ///< Case insensitive.// / <대소 문자를 구분하지 않습니다.
    };
    /// Returns the actual case sensitivity for the specified QuaZIP one.
    /**
      \param cs The value to convert.
      \returns If CaseSensitivity::csDefault, then returns the default
      file name case sensitivity for the platform. Otherwise, just
      returns the appropriate value from the Qt::CaseSensitivity enum.
      */
    // 지정된 QuaZIP에 대한 실제 대 / 소문자 구분을 반환합니다.
    /* *
      \ param cs 변환 할 값입니다.
      \ returns CaseSensitivity :: csDefault 인 경우 기본값을 반환합니다.
      플랫폼의 파일 이름 대 / 소문자 구분. 그렇지 않으면, 그냥
      Qt :: CaseSensitivity 열거 형에서 적절한 값을 반환합니다.
      */
    static Qt::CaseSensitivity convertCaseSensitivity(
            CaseSensitivity cs);
  private:
    QuaZipPrivate *p;
    // not (and will not be) implemented
    // 구현되지 않을 것입니다.
    QuaZip(const QuaZip& that);
    // not (and will not be) implemented
    // 구현되지 않을 것입니다.
    QuaZip& operator=(const QuaZip& that);
  public:
    /// Constructs QuaZip object.
    /** Call setName() before opening constructed object. */
    // / QuaZip 객체를 생성합니다.
    /* * 생성 된 객체를 열기 전에 setName ()을 호출하십시오. */
    QuaZip();
    /// Constructs QuaZip object associated with ZIP file \a zipName.
    // ZIP 파일 \ zipName에 연결된 QuaZip 객체를 생성합니다.
    QuaZip(const QString& zipName);
    /// Constructs QuaZip object associated with ZIP file represented by \a ioDevice.
    /** The IO device must be seekable, otherwise an error will occur when opening. */
    // / ioDevice로 표시된 ZIP 파일과 연관된 QuaZip 객체를 구성합니다.
    /* * 입출력 장치는 탐색 가능해야하며 그렇지 않으면 열 때 오류가 발생합니다. */
    QuaZip(QIODevice *ioDevice);
    /// Destroys QuaZip object.
    /** Calls close() if necessary. */
    // / QuaZip 객체를 소멸시킵니다.
    /* * 필요한 경우 close ()를 호출합니다. */
    ~QuaZip();
    /// Opens ZIP file.
    /**
     * Argument \a mode specifies open mode of the ZIP archive. See Mode
     * for details. Note that there is zipOpen2() function in the
     * ZIP/UNZIP API which accepts \a globalcomment argument, but it
     * does not use it anywhere, so this open() function does not have this
     * argument. See setComment() if you need to set global comment.
     *
     * If the ZIP file is accessed via explicitly set QIODevice, then
     * this device is opened in the necessary mode. If the device was
     * already opened by some other means, then the behaviour is defined by
     * the device implementation, but generally it is not a very good
     * idea. For example, QFile will at least issue a warning.
     *
     * \return \c true if successful, \c false otherwise.
     *
     * \note ZIP/UNZIP API open calls do not return error code - they
     * just return \c NULL indicating an error. But to make things
     * easier, quazip.h header defines additional error code \c
     * UNZ_ERROROPEN and getZipError() will return it if the open call
     * of the ZIP/UNZIP API returns \c NULL.
     *
     * Argument \a ioApi specifies IO function set for ZIP/UNZIP
     * package to use. See unzip.h, zip.h and ioapi.h for details. Note
     * that IO API for QuaZip is different from the original package.
     * The file path argument was changed to be of type \c voidpf, and
     * QuaZip passes a QIODevice pointer there. This QIODevice is either
     * set explicitly via setIoDevice() or the QuaZip(QIODevice*)
     * constructor, or it is created internally when opening the archive
     * by its file name. The default API (qioapi.cpp) just delegates
     * everything to the QIODevice API. Not only this allows to use a
     * QIODevice instead of file name, but also has a nice side effect
     * of raising the file size limit from 2G to 4G.
     *
     * In short: just forget about the \a ioApi argument and you'll be
     * fine.
     **/
    // / ZIP 파일을 엽니 다.
    /* *
     * Argument \ a mode는 ZIP 아카이브의 열린 모드를 지정합니다. 모드 참조
     * 자세한 내용은 zipOpen2 () 함수는
     * ZIP / UNZIP API는 \ 전역 인수를 받아들이지 만,
     *는 아무데도 사용하지 않으므로이 open () 함수는 이것을 가지고 있지 않습니다.
     * 인수. 전역 주석을 설정해야하는 경우 setComment ()를 참조하십시오.
     *
     * 명시 적으로 설정된 QIODevice를 통해 ZIP 파일에 액세스 한 경우
     *이 장치는 필요한 모드로 열립니다. 기기가
     * 이미 다른 방법으로 열면 행동은 다음과 같이 정의됩니다.
     * 장치 구현이지만, 일반적으로 매우 좋지 않습니다.
     * 아이디어. 예를 들어, QFile은 최소한 경고를 발행합니다.
     *
     * \ return \ c 성공하면 true, 그렇지 않으면 false.
     *
     * 참고 : ZIP / UNZIP API 열기 호출은 오류 코드를 반환하지 않습니다.
     * 단지 \ c 오류를 나타내는 NULL을 리턴한다. 하지만 사물을 만들기 위해서
     * 더 쉬운, quazip.h 헤더는 추가적인 오류 코드를 정의한다. \ c
     UNZ_ERROROPEN과 getZipError ()는 열린 호출
     *는 ZIP / UNZIP API의 \ c NULL을 반환합니다.
     *
     * Argument \ a ioApi는 ZIP / UNZIP에 설정된 입출력 함수를 지정합니다.
     * 사용할 패키지. 자세한 내용은 unzip.h, zip.h 및 ioapi.h를 참조하십시오. 노트
     * QuaZip 용 IO API는 원래 패키지와 다릅니다.
     * 파일 경로 인수가 \ c voidpf 유형으로 변경되었습니다.
     * QuaZip은 거기에 QIODevice 포인터를 전달합니다. 이 QIODevice는 다음 중 하나입니다.
     * setIoDevice () 또는 QuaZip (QIODevice *)를 통해 명시 적으로 설정
     * 생성자이거나 아카이브를 열 때 내부적으로 생성됩니다.
     * 파일 이름으로. 기본 API (qioapi.cpp)가 위임합니다.
     * QIODevice API에 대한 모든 것. 뿐만 아니라 이것은
     파일 이름 대신 * QIODevice뿐만 아니라 좋은 부작용이 있습니다.
     * 파일 크기 제한을 2G에서 4G로 높이는 방법.
     *
     * 간단히 말해서 \ a ioApi 인수를 잊어 버리면됩니다.
     * 괜찮아.
     * */
    bool open(Mode mode, zlib_filefunc_def *ioApi =NULL);
    /// Closes ZIP file.
    /** Call getZipError() to determine if the close was successful. The
     * underlying QIODevice is also closed, regardless of whether it was
     * set explicitly or not. */
    // ZIP 파일을 닫습니다.
    /* * getZipError ()를 호출하여 닫기가 성공적인지 여부를 확인하십시오. 그만큼
     * 기본 QIODevice도 닫혔는지 여부에 관계없이 닫힙니다.
     * 명시 적으로 설정되지 않거나 설정되지 않습니다. */
    void close();
    /// Sets the codec used to encode/decode file names inside archive.
    /** This is necessary to access files in the ZIP archive created
     * under Windows with non-latin characters in file names. For
     * example, file names with cyrillic letters will be in \c IBM866
     * encoding.
     **/
    // / archive 내에서 파일 이름을 인코딩 / 디코딩하는 데 사용되는 코덱을 설정합니다.
    /* * 생성 된 ZIP 파일의 파일에 액세스하려면 필요합니다.
     * 파일 이름에 비 라틴 문자가있는 Windows에서. 에 대한
     * 예 : 키릴 문자가있는 파일 이름은 \ c IBM866에 있습니다.
     * 인코딩.
     * */
    void setFileNameCodec(QTextCodec *fileNameCodec);
    /// Sets the codec used to encode/decode file names inside archive.
    /** \overload
     * Equivalent to calling setFileNameCodec(QTextCodec::codecForName(codecName));
     **/
    // / archive 내에서 파일 이름을 인코딩 / 디코딩하는 데 사용되는 코덱을 설정합니다.
    /* * \ overload
     * setFileNameCodec (QTextCodec :: codecForName (codecName)) 호출과 동일합니다.
     * */
    void setFileNameCodec(const char *fileNameCodecName);
    /// Returns the codec used to encode/decode comments inside archive.
    // / archive 내에서 주석을 인코딩 / 디코딩하는 데 사용되는 코덱을 반환합니다.
    QTextCodec* getFileNameCodec() const;
    /// Sets the codec used to encode/decode comments inside archive.
    /** This codec defaults to locale codec, which is probably ok.
     **/
    // / archive 안에 주석을 인 코드 / 디코드하는 데 사용되는 코덱을 설정합니다.
    /* *이 코덱의 기본값은 locale 코덱입니다. 아마도 괜찮습니다.
     * */
    void setCommentCodec(QTextCodec *commentCodec);
    /// Sets the codec used to encode/decode comments inside archive.
    /** \overload
     * Equivalent to calling setCommentCodec(QTextCodec::codecForName(codecName));
     **/
    // / archive 안에 주석을 인 코드 / 디코드하는 데 사용되는 코덱을 설정합니다.
    /* * \ overload
     * setCommentCodec (QTextCodec :: codecForName (codecName)) 호출과 동일합니다.
     * */
    void setCommentCodec(const char *commentCodecName);
    /// Returns the codec used to encode/decode comments inside archive.
    // / archive 내에서 주석을 인코딩 / 디코딩하는 데 사용되는 코덱을 반환합니다.
    QTextCodec* getCommentCodec() const;
    /// Returns the name of the ZIP file.
    /** Returns null string if no ZIP file name has been set, for
     * example when the QuaZip instance is set up to use a QIODevice
     * instead.
     * \sa setZipName(), setIoDevice(), getIoDevice()
     **/
    // / ZIP 파일의 이름을 반환합니다.
    /* * ZIP 파일 이름이 설정되지 않은 경우 null 문자열을 반환합니다.
     * QuaZip 인스턴스가 QIODevice를 사용하도록 설정된 경우의 예
     * 대신.
     * \ sa setZipName (), setIoDevice (), getIoDevice ()
     * */
    QString getZipName() const;
    /// Sets the name of the ZIP file.
    /** Does nothing if the ZIP file is open.
     *
     * Does not reset error code returned by getZipError().
     * \sa setIoDevice(), getIoDevice(), getZipName()
     **/
    // / ZIP 파일의 이름을 설정합니다.
    /* * ZIP 파일이 열려 있으면 아무 일도하지 않습니다.
     *
     * getZipError ()에 의해 반환 된 오류 코드를 재설정하지 않습니다.
     * \ sa setIoDevice (), getIoDevice (), getZipName ()
     * */
    void setZipName(const QString& zipName);
    /// Returns the device representing this ZIP file.
    /** Returns null string if no device has been set explicitly, for
     * example when opening a ZIP file by name.
     * \sa setIoDevice(), getZipName(), setZipName()
     **/
    // 이 ZIP 파일을 나타내는 장치를 반환합니다.
    /* * 명시 적으로 장치가 설정되지 않은 경우 null 문자열을 반환합니다.
     * 이름으로 ZIP 파일을 열 때의 예.
     * \ sa setIoDevice (), getZipName (), setZipName ()
     * */
    QIODevice *getIoDevice() const;
    /// Sets the device representing the ZIP file.
    /** Does nothing if the ZIP file is open.
     *
     * Does not reset error code returned by getZipError().
     * \sa getIoDevice(), getZipName(), setZipName()
     **/
    // / ZIP 파일을 나타내는 장치를 설정합니다.
    /* * ZIP 파일이 열려 있으면 아무 일도하지 않습니다.
     *
     * getZipError ()에 의해 반환 된 오류 코드를 재설정하지 않습니다.
     * \ sa getIoDevice (), getZipName (), setZipName ()
     * */
    void setIoDevice(QIODevice *ioDevice);
    /// Returns the mode in which ZIP file was opened.
    // / ZIP 파일이 열린 모드를 반환합니다.
    Mode getMode() const;
    /// Returns \c true if ZIP file is open, \c false otherwise.
    // / Returns \ c ZIP 파일이 열려 있으면 true이고, 그렇지 않으면 false입니다.
    bool isOpen() const;
    /// Returns the error code of the last operation.
    /** Returns \c UNZ_OK if the last operation was successful.
     *
     * Error code resets to \c UNZ_OK every time you call any function
     * that accesses something inside ZIP archive, even if it is \c
     * const (like getEntriesCount()). open() and close() calls reset
     * error code too. See documentation for the specific functions for
     * details on error detection.
     **/
    // 마지막 작업의 오류 코드를 반환합니다.
    /* * 마지막 작업이 성공하면 \ c UNZ_OK를 반환합니다.
     *
     * 함수를 호출 할 때마다 오류 코드가 \ c UNZ_OK로 재설정됩니다.
     *는 ZIP 아카이브 내부의 내용에 액세스합니다. \ c
     * const (getEntriesCount ()와 같습니다). open () 및 close () 호출 재설정
     * 오류 코드. 특정 기능은 설명서를 참조하십시오.
     * 오류 탐지에 대한 자세한 내용.
     * */
    int getZipError() const;
    /// Returns number of the entries in the ZIP central directory.
    /** Returns negative error code in the case of error. The same error
     * code will be returned by subsequent getZipError() call.
     **/
    // / ZIP 중앙 디렉토리의 항목 번호를 반환합니다.
    /* * 오류가 발생하면 부정적인 오류 코드를 반환합니다. 같은 오류
     * 코드는 후속 getZipError () 호출에 의해 반환됩니다.
     * */
    int getEntriesCount() const;
    /// Returns global comment in the ZIP file.
    // / ZIP 파일의 전역 주석을 반환합니다.
    QString getComment() const;
    /// Sets the global comment in the ZIP file.
    /** The comment will be written to the archive on close operation.
     * QuaZip makes a distinction between a null QByteArray() comment 
     * and an empty &quot;&quot; comment in the QuaZip::mdAdd mode. 
     * A null comment is the default and it means &quot;don't change 
     * the comment&quot;. An empty comment removes the original comment.
     *
     * \sa open()
     **/
    // / ZIP 파일의 전역 주석을 설정합니다.
    /* * 코멘트는 닫기 작업시 아카이브에 기록됩니다.
     * QuaZip은 null QByteArray () 주석을 구별합니다. 
     * 및 빈 "& quot; QuaZip :: mdAdd 모드의 주석.
     * null 댓글이 기본값이며 & quot; 변경하지 않음 
     * 코멘트 ". 빈 주석은 원래 주석을 제거합니다.
     *
     * \ sa open ()
     * */
    void setComment(const QString& comment);
    /// Sets the current file to the first file in the archive.
    /** Returns \c true on success, \c false otherwise. Call
     * getZipError() to get the error code.
     **/
    // 현재 파일을 아카이브의 첫 번째 파일로 설정합니다.
    /* * 성공하면 \ c를 반환하고 그렇지 않으면 false를 반환합니다. 요구
     * getZipError ()를 사용하여 오류 코드를 가져옵니다.
     * */
    bool goToFirstFile();
    /// Sets the current file to the next file in the archive.
    /** Returns \c true on success, \c false otherwise. Call
     * getZipError() to determine if there was an error.
     *
     * Should be used only in QuaZip::mdUnzip mode.
     *
     * \note If the end of file was reached, getZipError() will return
     * \c UNZ_OK instead of \c UNZ_END_OF_LIST_OF_FILE. This is to make
     * things like this easier:
     * \code
     * for(bool more=zip.goToFirstFile(); more; more=zip.goToNextFile()) {
     *   // do something
     * }
     * if(zip.getZipError()==UNZ_OK) {
     *   // ok, there was no error
     * }
     * \endcode
     **/
    // 현재 파일을 아카이브의 다음 파일로 설정합니다.
    /** 성공하면 \ c를 반환하고 그렇지 않으면 false를 반환합니다. 요구
     * getZipError () : 오류가 있었는지 확인합니다.
     *
     * QuaZip :: mdUnzip 모드에서만 사용해야합니다.
     *
     * \ note 파일 끝에 도달하면 getZipError ()가 반환됩니다.
     * \ c UNZ_END_OF_LIST_OF_FILE 대신 UNZ_OK. 이것은
     * 이와 같은 것들이 더 쉽습니다.
     * \ code
     * for (bool more = zip.goToFirstFile (); more; more = zip.goToNextFile ()) {
     * // 뭔가를하십시오.
     *}
     * if (zip.getZipError () == UNZ_OK) {
     * // ok, 오류가 없습니다.
     *}
     * \ endcode
     * */
    bool goToNextFile();
    /// Sets current file by its name.
    /** Returns \c true if successful, \c false otherwise. Argument \a
     * cs specifies case sensitivity of the file name. Call
     * getZipError() in the case of a failure to get error code.
     *
     * This is not a wrapper to unzLocateFile() function. That is
     * because I had to implement locale-specific case-insensitive
     * comparison.
     *
     * Here are the differences from the original implementation:
     *
     * - If the file was not found, error code is \c UNZ_OK, not \c
     *   UNZ_END_OF_LIST_OF_FILE (see also goToNextFile()).
     * - If this function fails, it unsets the current file rather than
     *   resetting it back to what it was before the call.
     *
     * If \a fileName is null string then this function unsets the
     * current file and return \c true. Note that you should close the
     * file first if it is open! See
     * QuaZipFile::QuaZipFile(QuaZip*,QObject*) for the details.
     *
     * Should be used only in QuaZip::mdUnzip mode.
     *
     * \sa setFileNameCodec(), CaseSensitivity
     **/
    // 현재 파일을 이름으로 설정합니다.
    /* *를 반환합니다. 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다. 인수 \ a
     * cs는 파일 이름의 대소.자를 구분합니다. 요구
     오류 코드를 얻지 못한 경우 getZipError ().
     *
     * unzLocateFile () 함수에 대한 래퍼가 아닙니다. 그건
     * 로케일 고유의 대문자 소문자를 구별하지 않으면 안되기 때문에
     * 비교.
     *
     * 원래 구현과의 차이점은 다음과 같습니다.
     *
     * - 파일을 찾을 수없는 경우 오류 코드는 \ c가 아니라 \ c UNZ_OK입니다.
     * UNZ_END_OF_LIST_OF_FILE (goToNextFile () 참조).
     * -이 함수가 실패하면, 현재 파일을 언 세트합니다.
     * 통화하기 전의 상태로 되돌립니다.
     *
     * \ fileName가 null 캐릭터 라인의 경우,이 함수는
     현재 파일을 반환하고 \ c true. 참고로
     * 파일이 열려 있으면 먼저 파일을 만드십시오! 만나다
     * 자세한 내용은 QuaZipFile :: QuaZipFile (QuaZip *, QObject *)을 참조하십시오.
     *
     * QuaZip :: mdUnzip 모드에서만 사용해야합니다.
     *
     * \ sa setFileNameCodec (), CaseSensitivity
     * */
    bool setCurrentFile(const QString& fileName, CaseSensitivity cs =csDefault);
    /// Returns \c true if the current file has been set.
    // 현재 파일이 설정되면 true를 반환합니다.
    bool hasCurrentFile() const;
    /// Retrieves information about the current file.
    /** Fills the structure pointed by \a info. Returns \c true on
     * success, \c false otherwise. In the latter case structure pointed
     * by \a info remains untouched. If there was an error,
     * getZipError() returns error code.
     *
     * Should be used only in QuaZip::mdUnzip mode.
     *
     * Does nothing and returns \c false in any of the following cases.
     * - ZIP is not open;
     * - ZIP does not have current file;
     * - \a info is \c NULL;
     *
     * In all these cases getZipError() returns \c UNZ_OK since there
     * is no ZIP/UNZIP API call.
     **/
    // / 현재 파일에 대한 정보를 검색합니다.
    /* * \ a 정보가 가리키는 구조체를 채 웁니다. on을 true로 반환합니다.
     * 성공, 그렇지 않으면 false. 후자의 경우 구조체가 가리킨다.
     * by \ a 정보는 변경되지 않습니다. 오류가있는 경우,
     * getZipError ()는 오류 코드를 반환합니다.
     *
     * QuaZip :: mdUnzip 모드에서만 사용해야합니다.
     *
     * 다음 경우에 아무것도하지 않고 \ c false를 반환합니다.
     * - ZIP이 열려 있지 않습니다.
     * - ZIP에는 현재 파일이 없습니다.
     * - \ a 정보는 \ c NULL입니다.
     *
     *이 모든 경우 getZipError ()는 \ c UNZ_OK를 반환합니다.
     *는 ZIP / UNZIP API 호출이 아닙니다.
     * */
    bool getCurrentFileInfo(QuaZipFileInfo* info)const;
    /// Returns the current file name.
    /** Equivalent to calling getCurrentFileInfo() and then getting \c
     * name field of the QuaZipFileInfo structure, but faster and more
     * convenient.
     *
     * Should be used only in QuaZip::mdUnzip mode.
     **/
    // 현재 파일 이름을 반환합니다.
    /* * getCurrentFileInfo ()를 호출 한 다음 \ c를 얻는 것과 같습니다.
     * QuaZipFileInfo 구조의 이름 필드, 더 빠르거나 더
     * 편리합니다.
     *
     * QuaZip :: mdUnzip 모드에서만 사용해야합니다.
     * */
    QString getCurrentFileName()const;
    /// Returns \c unzFile handle.
    /** You can use this handle to directly call UNZIP part of the
     * ZIP/UNZIP package functions (see unzip.h).
     *
     * \warning When using the handle returned by this function, please
     * keep in mind that QuaZip class is unable to detect any changes
     * you make in the ZIP file state (e. g. changing current file, or
     * closing the handle). So please do not do anything with this
     * handle that is possible to do with the functions of this class.
     * Or at least return the handle in the original state before
     * calling some another function of this class (including implicit
     * destructor calls and calls from the QuaZipFile objects that refer
     * to this QuaZip instance!). So if you have changed the current
     * file in the ZIP archive - then change it back or you may
     * experience some strange behavior or even crashes.
     **/
    // / unzFile 핸들을 반환합니다.
    /* *이 핸들을 사용하여 UNZIP 부분을 직접 호출 할 수 있습니다.
     * ZIP / UNZIP 패키지 기능 (unzip.h 참조).
     *
     * \ warning이 함수가 리턴 한 핸들을 사용할 때,
     * QuaZip 클래스는 변경 사항을 감지 할 수 없음을 기억하십시오.
     * ZIP 파일 상태로 만듭니다 (예 : 현재 파일 변경 또는
     * 핸들을 닫음). 그러니 제발 이걸로 아무것도하지 마세요.
     *이 클래스의 함수로 처리 할 수있는 핸들.
     * 또는 적어도 원래 상태로 핸들을 반환합니다.
     *이 클래스의 또 다른 함수를 호출합니다 (암시 적 포함).
     * 참조하는 QuaZipFile 객체의 소멸자 호출 및 호출
     *이 QuaZip 인스턴스에!). 그래서 만약 당신이 현재의
     * 파일을 ZIP 아카이브에 저장 한 다음 다시 변경하거나
     * 이상한 행동이나 충돌을 경험합니다.
     * */
    unzFile getUnzFile();
    /// Returns \c zipFile handle.
    /** You can use this handle to directly call ZIP part of the
     * ZIP/UNZIP package functions (see zip.h). Warnings about the
     * getUnzFile() function also apply to this function.
     **/
    // / zip 파일 핸들을 반환합니다.
    /* *이 핸들을 사용하여 ZIP 부분을 직접 호출 할 수 있습니다.
     * ZIP / UNZIP 패키지 기능 (zip.h 참조). 에 대한 경고
     * getUnzFile () 함수는이 함수에도 적용됩니다.
     * */
    zipFile getZipFile();
    /// Changes the data descriptor writing mode.
    /**
      According to the ZIP format specification, a file inside archive
      may have a data descriptor immediately following the file
      data. This is reflected by a special flag in the local file header
      and in the central directory. By default, QuaZIP sets this flag
      and writes the data descriptor unless both method and level were
      set to 0, in which case it operates in 1.0-compatible mode and
      never writes data descriptors.

      By setting this flag to false, it is possible to disable data
      descriptor writing, thus increasing compatibility with archive
      readers that don't understand this feature of the ZIP file format.

      Setting this flag affects all the QuaZipFile instances that are
      opened after this flag is set.

      The data descriptor writing mode is enabled by default.

      \param enabled If \c true, enable local descriptor writing,
      disable it otherwise.

      \sa QuaZipFile::setDataDescriptorWritingEnabled()
      */
    // 데이터 디스크립터 쓰기 모드를 변경합니다.
    /* *
      ZIP 형식 사양에 따르면 아카이브 내부의 파일
      파일 바로 다음에 데이터 설명자가있을 수 있습니다.
      데이터. 로컬 파일 헤더에 특수 플래그가 반영됩니다.
      중앙 디렉토리에 있습니다. 기본적으로 QuaZIP는이 플래그를 설정합니다.
      메소드와 레벨이 모두 같지 않으면 데이터 디스크립터를 쓴다.
      0으로 설정하면 1.0 호환 모드에서 작동하고
      데이터 기술자를 쓰지 않습니다.
      이 플래그를 false로 설정하면 데이터를 비활성화 할 수 있습니다.
      설명자 쓰기, 따라서 아카이브와의 호환성 향상
      독자는 ZIP 파일 형식의이 기능을 이해하지 못합니다.
      이 플래그를 설정하면 모든 QuaZipFile 인스턴스가 영향을받습니다.
      이 플래그가 설정된 후에 열립니다.
      데이터 디스크립터 쓰기 모드는 기본적으로 사용 가능합니다.
      \ param enabled \ c true이면 로컬 디스크립터 쓰기를 활성화하고,
      그렇지 않으면 해제하십시오.
      \ sa QuaZipFile :: setDataDescriptorWritingEnabled ()
      */
    void setDataDescriptorWritingEnabled(bool enabled);
    /// Returns the data descriptor default writing mode.
    /**
      \sa setDataDescriptorWritingEnabled()
      */
    // 데이터 기술자의 기본 쓰기 모드를 반환합니다.
    /* *
      \ sa setDataDescriptorWritingEnabled ()
      */
    bool isDataDescriptorWritingEnabled() const;
    /// Returns a list of files inside the archive.
    /**
      \return A list of file names or an empty list if there
      was an error or if the archive is empty (call getZipError() to
      figure out which).
      \sa getFileInfoList()
      */
    // / 아카이브 안의 파일 목록을 반환합니다.
    /* *
      \ return 파일 이름 목록 또는 빈 목록이 있으면 그 목록
      오류이거나 아카이브가 비어 있으면 (getZipError ()를 호출하여
      어느 그림인지).
      \ sa getFileInfoList ()
      */
    QStringList getFileNameList() const;
    /// Returns information list about all files inside the archive.
    /**
      \return A list of QuaZipFileInfo objects or an empty list if there
      was an error or if the archive is empty (call getZipError() to
      figure out which).
      \sa getFileNameList()
      */
    // / 아카이브 안에있는 모든 파일에 대한 정보 목록을 반환합니다.
    /* *
      \ return QuaZipFileInfo 객체의 목록 또는 빈 목록이있는 경우
      오류이거나 아카이브가 비어 있으면 (getZipError ()를 호출하여
      어느 그림인지).
      \ sa getFileNameList ()
      */
    QList<QuaZipFileInfo> getFileInfoList() const;
};

#endif
