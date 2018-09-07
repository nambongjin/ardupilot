#ifndef QUA_ZIPFILE_H
#define QUA_ZIPFILE_H

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
/*
Copyright (C) 2005-2011 Sergey A. Tachenov
이 프로그램은 무료 소프트웨어입니다. 재배포 및 / 또는 수정할 수 있습니다.
GNU 약소 일반 공중 사용 허가서 (GNU Lesser General Public License)의 조건에 따라
자유 소프트웨어 재단; 라이선스 버전 2 또는 (
귀하의 옵션) 모든 최신 버전.
이 프로그램은 유용 할 것이라는 희망으로 배포됩니다.
어떠한 보증도하지 않습니다. 묵시적 보증없이
상품성 또는 특정 목적에의 적합성. GNU Lesser를 보라.
자세한 내용은 일반 공중 사용 허가서.
GNU 약소 일반 공중 사용 허가서 (GNU Lesser General Public License)
이 프로그램과 함께; 그렇지 않다면 자유 소프트웨어 재단에 기고하십시오.
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 미국
전체 LGPL 텍스트는 COPYING 파일을 참조하십시오.
원래 ZIP 패키지는 Gilles Vollant에 저작권이 있습니다.
quazip / (un) zip.h 파일에 대한 자세한 내용은 기본적으로 zlib 라이센스입니다.
* */

#include <QIODevice>

#include "quazip_global.h"
#include "quazip.h"
#include "quazipnewinfo.h"

class QuaZipFilePrivate;

/// A file inside ZIP archive.
/** \class QuaZipFile quazipfile.h <quazip/quazipfile.h>
 * This is the most interesting class. Not only it provides C++
 * interface to the ZIP/UNZIP package, but also integrates it with Qt by
 * subclassing QIODevice. This makes possible to access files inside ZIP
 * archive using QTextStream or QDataStream, for example. Actually, this
 * is the main purpose of the whole QuaZIP library.
 *
 * You can either use existing QuaZip instance to create instance of
 * this class or pass ZIP archive file name to this class, in which case
 * it will create internal QuaZip object. See constructors' descriptions
 * for details. Writing is only possible with the existing instance.
 *
 * Note that due to the underlying library's limitation it is not
 * possible to use multiple QuaZipFile instances to open several files
 * in the same archive at the same time. If you need to write to
 * multiple files in parallel, then you should write to temporary files
 * first, then pack them all at once when you have finished writing. If
 * you need to read multiple files inside the same archive in parallel,
 * you should extract them all into a temporary directory first.
 *
 * \section quazipfile-sequential Sequential or random-access?
 *
 * At the first thought, QuaZipFile has fixed size, the start and the
 * end and should be therefore considered random-access device. But
 * there is one major obstacle to making it random-access: ZIP/UNZIP API
 * does not support seek() operation and the only way to implement it is
 * through reopening the file and re-reading to the required position,
 * but this is prohibitively slow.
 *
 * Therefore, QuaZipFile is considered to be a sequential device. This
 * has advantage of availability of the ungetChar() operation (QIODevice
 * does not implement it properly for non-sequential devices unless they
 * support seek()). Disadvantage is a somewhat strange behaviour of the
 * size() and pos() functions. This should be kept in mind while using
 * this class.
 *
 **/
// / ZIP 아카이브 내의 파일.
/* * \ class QuaZipFile quazipfile.h <quazip / quazipfile.h>
* 이것은 가장 흥미로운 수업입니다. C ++을 제공 할뿐만 아니라
 * ZIP / UNZIP 패키지와의 인터페이스는 물론 Qt 와도 통합됩니다.
* 하위 클래스 QIODevice. 이렇게하면 ZIP 내부의 파일에 액세스 할 수 있습니다.
* QTextStream 또는 QDataStream을 사용하여 아카이브하십시오. 사실,이
 * 전체 QuaIPIP 라이브러리의 주요 목적입니다.
 *
 * 기존의 QuaZip 인스턴스를 사용하여
 *이 클래스 또는 ZIP 아카이브 파일 이름을이 클래스에 전달하십시오.
* 내부 QuaZip 객체를 생성합니다. 생성자의 설명보기
* 자세한 내용은 쓰기는 기존 인스턴스에서만 가능합니다.
 *
 * 기본 라이브러리의 제한으로 인해
 * 여러 개의 QuaZipFile 인스턴스를 사용하여 여러 파일을 열 수 있음
* 같은 아카이브에서 동시에. 쓸 필요가있는 경우
 * 여러 파일을 병렬로 사용하면 임시 파일에 기록해야합니다.
* 먼저, 글쓰기를 끝내면 한꺼번에 모두 포장하십시오. 만약
 * 동일한 아카이브 내부의 여러 파일을 병렬로 읽어야합니다.
 * 먼저 임시 디렉토리에 모든 파일을 추출해야합니다.
 *
 * \ quazipfile-sequential 순차 또는 무작위 액세스?
 *
 * 처음 생각했을 때, QuaZipFile은 크기가 고정되었고 시작과
* 끝이므로 랜덤 액세스 장치로 간주되어야합니다. 그러나
 * 랜덤 액세스를 만드는 데 하나의 큰 장애물이 있습니다. ZIP / UNZIP API
 *는 seek () 작업을 지원하지 않으며이를 구현하는 유일한 방법은
 * 파일을 다시 열고 필요한 위치로 다시 읽음으로써,
 * 그러나 이것은 매우 느립니다.
 *
* 따라서 QuaZipFile은 순차적 장치로 간주됩니다. 이
 * ungetChar () 작업의 가용성을 활용합니다 (QIODevice
 * 비 순차적 장치의 경우 제대로 구현되지 않습니다.
* seek () 지원). 단점은 다소 이상한 행동입니다.
* size ()와 pos () 함수. 사용하는 동안 명심해야합니다.
 *이 클래스.
 *
* */
class QUAZIP_EXPORT QuaZipFile: public QIODevice {
  friend class QuaZipFilePrivate;
  Q_OBJECT
  private:
    QuaZipFilePrivate *p;
    // these are not supported nor implemented
    // 이들은 지원되거나 구현되지 않는다.
    QuaZipFile(const QuaZipFile& that);
    QuaZipFile& operator=(const QuaZipFile& that);
  protected:
    /// QIODevice::readData() 구현.
    qint64 readData(char *data, qint64 maxSize);
    /// QIODevice::writeData() 구현.
    qint64 writeData(const char *data, qint64 maxSize);
  public:
    /// Constructs a QuaZipFile instance.
    /** You should use setZipName() and setFileName() or setZip() before
     * trying to call open() on the constructed object.
     **/
    /// QuaZipFile 인스턴스를 생성합니다.
    /* * setZipName ()과 setFileName () 또는 setZip ()을 먼저 사용해야합니다.
     * 생성 된 객체에서 open ()을 호출하려고합니다.
     * */
    QuaZipFile();
    /// Constructs a QuaZipFile instance.
    /** \a parent argument specifies this object's parent object.
     *
     * You should use setZipName() and setFileName() or setZip() before
     * trying to call open() on the constructed object.
     **/
    /// QuaZipFile 인스턴스를 생성합니다.
    /* * \ parent 인수는이 객체의 부모 객체를 지정합니다.
     *
     * setZipName () 및 setFileName () 또는 setZip ()을 사용해야합니다.
     * 생성 된 객체에서 open ()을 호출하려고합니다.
     * */
    QuaZipFile(QObject *parent);
    /// Constructs a QuaZipFile instance.
    /** \a parent argument specifies this object's parent object and \a
     * zipName specifies ZIP archive file name.
     *
     * You should use setFileName() before trying to call open() on the
     * constructed object.
     *
     * QuaZipFile constructed by this constructor can be used for read
     * only access. Use QuaZipFile(QuaZip*,QObject*) for writing.
     **/
    /// QuaZipFile 인스턴스를 생성합니다.
    /* * \ parent 인수는이 객체의 부모 객체를 지정하고 \ a
     * zipName은 ZIP 아카이브 파일 이름을 지정합니다.
     *
     * open ()을 호출하기 전에 setFileName ()을 사용해야합니다.
     * 생성 된 객체.
     *
     *이 생성자로 생성 된 QuaZipFile은 읽기에 사용될 수 있습니다.
     * 액세스 전용. 쓰기에는 QuaZipFile (QuaZip *, QObject *)을 사용하십시오.
     * */
    QuaZipFile(const QString& zipName, QObject *parent =NULL);
    /// Constructs a QuaZipFile instance.
    /** \a parent argument specifies this object's parent object, \a
     * zipName specifies ZIP archive file name and \a fileName and \a cs
     * specify a name of the file to open inside archive.
     *
     * QuaZipFile constructed by this constructor can be used for read
     * only access. Use QuaZipFile(QuaZip*,QObject*) for writing.
     *
     * \sa QuaZip::setCurrentFile()
     **/
    /// QuaZipFile 인스턴스를 생성합니다.
    /* * \ parent 인수는이 객체의 상위 객체 인 \ a를 지정합니다.
     * zipName은 ZIP 보관 파일 이름과 \ a fileName 및 \ c cs를 지정합니다.
     * 아카이브 내부에서 열 파일의 이름을 지정하십시오.
     *
     *이 생성자로 생성 된 QuaZipFile은 읽기에 사용될 수 있습니다.
     * 액세스 전용. 쓰기에는 QuaZipFile (QuaZip *, QObject *)을 사용하십시오.
     *
     * \ sa QuaZip :: setCurrentFile ()
     * */
    QuaZipFile(const QString& zipName, const QString& fileName,
        QuaZip::CaseSensitivity cs =QuaZip::csDefault, QObject *parent =NULL);
    /// Constructs a QuaZipFile instance.
    /** \a parent argument specifies this object's parent object.
     *
     * \a zip is the pointer to the existing QuaZip object. This
     * QuaZipFile object then can be used to read current file in the
     * \a zip or to write to the file inside it.
     *
     * \warning Using this constructor for reading current file can be
     * tricky. Let's take the following example:
     * \code
     * QuaZip zip("archive.zip");
     * zip.open(QuaZip::mdUnzip);
     * zip.setCurrentFile("file-in-archive");
     * QuaZipFile file(&zip);
     * file.open(QIODevice::ReadOnly);
     * // ok, now we can read from the file
     * file.read(somewhere, some);
     * zip.setCurrentFile("another-file-in-archive"); // oops...
     * QuaZipFile anotherFile(&zip);
     * anotherFile.open(QIODevice::ReadOnly);
     * anotherFile.read(somewhere, some); // this is still ok...
     * file.read(somewhere, some); // and this is NOT
     * \endcode
     * So, what exactly happens here? When we change current file in the
     * \c zip archive, \c file that references it becomes invalid
     * (actually, as far as I understand ZIP/UNZIP sources, it becomes
     * closed, but QuaZipFile has no means to detect it).
     *
     * Summary: do not close \c zip object or change its current file as
     * long as QuaZipFile is open. Even better - use another constructors
     * which create internal QuaZip instances, one per object, and
     * therefore do not cause unnecessary trouble. This constructor may
     * be useful, though, if you already have a QuaZip instance and do
     * not want to access several files at once. Good example:
     * \code
     * QuaZip zip("archive.zip");
     * zip.open(QuaZip::mdUnzip);
     * // first, we need some information about archive itself
     * QByteArray comment=zip.getComment();
     * // and now we are going to access files inside it
     * QuaZipFile file(&zip);
     * for(bool more=zip.goToFirstFile(); more; more=zip.goToNextFile()) {
     *   file.open(QIODevice::ReadOnly);
     *   // do something cool with file here
     *   file.close(); // do not forget to close!
     * }
     * zip.close();
     * \endcode
     **/
    /// QuaZipFile 인스턴스를 생성합니다.
    /* * \ parent 인수는이 객체의 부모 객체를 지정합니다.
     *
     * \ zip은 기존 QuaZip 객체에 대한 포인터입니다. 이
     * QuaZipFile 객체를 사용하면 현재 파일을 읽을 수 있습니다.
     * \ zip 또는 그 안에있는 파일에 쓰십시오.
     *
     * \ warning이 생성자를 사용하여 현재 파일을 읽을 수 있습니다.
     * 까다 롭다. 다음 예제를 보겠습니다.
     * \ code
     * QuaZip zip ( "archive.zip");
     * zip.open (QuaZip :: mdUnzip);
     * zip.setCurrentFile ( "파일 - 인 - 아카이브");
     * QuaZipFile 파일 (& zip);
     * file.open (QIODevice :: ReadOnly);
     * // 이제 파일에서 읽을 수 있습니다.
     * file.read (어딘가, 일부);
     * zip.setCurrentFile ( "다른 파일 - 인 - 아카이브"); // oops ...
     * QuaZipFile anotherFile (& zip);
     * anotherFile.open (QIODevice :: ReadOnly);
     * anotherFile.read (어딘가, 일부); // 여전히 괜찮습니다 ...
     * file.read (어딘가, 일부); // 이것은 NOT이다.
     * \ endcode
     * 여기 정확히 무슨 일이 일어 났습니까? 현재 파일을
     * \ zip 압축 파일, 그것을 참조하는 \ c 파일이 무효화됩니다.
     * (실제로 ZIP / UNZIP 소스를 이해하는 한
     * 닫히지 만, QuaZipFile에는 그것을 탐지 할 수단이 없습니다.)
     *
     요약 : \ zip 객체를 닫거나 현재 파일을 다음과 같이 변경하지 마십시오.
     * QuaZipFile이 열려있는 한 오래. 더 나은 - 다른 생성자 사용
     * 개체마다 하나씩 내부 QuaZip 인스턴스를 생성합니다.
     따라서 불필요한 문제가 발생하지 않습니다. 이 생성자는
     * 이미 QuaZip 인스턴스가있는 경우 유용합니다.
     * 한 번에 여러 파일에 액세스하고 싶지 않습니다. 좋은 예 :
     * \ code
     * QuaZip zip ( "archive.zip");
     * zip.open (QuaZip :: mdUnzip);
     * // 먼저 아카이브 자체에 대한 정보가 필요합니다.
     * QByteArray comment = zip.getComment ();
     * // 이제 우리는 그 안에있는 파일에 접근 할 것입니다.
     * QuaZipFile 파일 (& zip);
     * for (bool more = zip.goToFirstFile (); more; more = zip.goToNextFile ()) {
     * file.open (QIODevice :: ReadOnly);
     * // 여기 파일로 멋지게해라.
     * file.close (); // 닫는 것을 잊지 마라!
     *}
     * zip.close ();
     * \ endcode
     * */

    QuaZipFile(QuaZip *zip, QObject *parent =NULL);
    /// Destroys a QuaZipFile instance.
    /** Closes file if open, destructs internal QuaZip object (if it
     * exists and \em is internal, of course).
     **/
    /// QuaZipFile 인스턴스를 소멸시킵니다.
    /* * 열려있는 경우 파일을 닫고 내부 QuaZip 객체를 소멸시킵니다 (
     * 존재하고 \ em 물론 내부입니다.
     * */
    virtual ~QuaZipFile();
    /// Returns the ZIP archive file name.
    /** If this object was created by passing QuaZip pointer to the
     * constructor, this function will return that QuaZip's file name
     * (or null string if that object does not have file name yet).
     *
     * Otherwise, returns associated ZIP archive file name or null
     * string if there are no name set yet.
     *
     * \sa setZipName() getFileName()
     **/
    /// ZIP 아카이브 파일 이름을 반환합니다.
    /* *이 객체가 QuaZip 포인터를
     * 생성자,이 함수는 QuaZip의 파일 이름을 반환합니다.
     * (또는 객체에 아직 파일 이름이없는 경우 null 문자열).
     *
     * 그렇지 않으면 연관된 ZIP 아카이브 파일 이름 또는 null을 리턴합니다.
     * 이름이 아직 설정되지 않은 경우 문자열.
     *
     * \ sa setZipName () getFileName ()
     * */
    QString getZipName()const;
    /// Returns a pointer to the associated QuaZip object.
    /** Returns \c NULL if there is no associated QuaZip or it is
     * internal (so you will not mess with it).
     **/
    // 연결된 QuaZip 개체에 대한 포인터를 반환합니다.
    /* * 연결된 QuaZip이 없거나 NULL 인 경우 NULL을 반환합니다.
     * 내부 (그래서 당신은 그것을 망쳐 놓지 않을 것이다).
     * */
    QuaZip* getZip()const;
    /// Returns file name.
    /** This function returns file name you passed to this object either
     * by using
     * QuaZipFile(const QString&,const QString&,QuaZip::CaseSensitivity,QObject*)
     * or by calling setFileName(). Real name of the file may differ in
     * case if you used case-insensitivity.
     *
     * Returns null string if there is no file name set yet. This is the
     * case when this QuaZipFile operates on the existing QuaZip object
     * (constructor QuaZipFile(QuaZip*,QObject*) or setZip() was used).
     * 
     * \sa getActualFileName
     **/
    /// 파일 이름을 반환합니다.
    /* *이 함수는이 객체에 전달한 파일 이름을 반환합니다.
     * 사용하여
     * QuaZipFile (const QString &, const QString &, QuaZip :: CaseSensitivity, QObject *)
     * 또는 setFileName ()을 호출하여. 파일의 실제 이름은 다음과 다를 수 있습니다.
     * 대소 문자를 구분하지 않는 경우.
     *
     * 아직 파일 이름이 설정되지 않은 경우 null 문자열을 반환합니다. 이것이
     *이 QuaZip 파일이 기존 QuaZip 개체에서 작동하는 경우
     * (생성자 QuaZipFile (QuaZip *, QObject *) 또는 setZip ()이 사용되었습니다.
     * 
     * \ sa getActualFileName
     * */
    QString getFileName() const;
    /// Returns case sensitivity of the file name.
    /** This function returns case sensitivity argument you passed to
     * this object either by using
     * QuaZipFile(const QString&,const QString&,QuaZip::CaseSensitivity,QObject*)
     * or by calling setFileName().
     *
     * Returns unpredictable value if getFileName() returns null string
     * (this is the case when you did not used setFileName() or
     * constructor above).
     *
     * \sa getFileName
     **/
    /// 파일 이름의 대 / 소문자 구분을 반환합니다.
    /* *이 함수는 전달 된 대소 문자 구분 인수를 반환합니다.
     *이 객체는
     * QuaZipFile (const QString &, const QString &, QuaZip :: CaseSensitivity, QObject *)
     * 또는 setFileName ()을 호출하여.
     *
     getFileName ()이 null 문자열을 반환하면 예기치 않은 값을 반환합니다.
     * (setFileName ()을 사용하지 않았거나
     * 위의 생성자).
     *
     * \ sa getFileName
     * */
    QuaZip::CaseSensitivity getCaseSensitivity() const;
    /// Returns the actual file name in the archive.
    /** This is \em not a ZIP archive file name, but a name of file inside
     * archive. It is not necessary the same name that you have passed
     * to the
     * QuaZipFile(const QString&,const QString&,QuaZip::CaseSensitivity,QObject*),
     * setFileName() or QuaZip::setCurrentFile() - this is the real file
     * name inside archive, so it may differ in case if the file name
     * search was case-insensitive.
     *
     * Equivalent to calling getCurrentFileName() on the associated
     * QuaZip object. Returns null string if there is no associated
     * QuaZip object or if it does not have a current file yet. And this
     * is the case if you called setFileName() but did not open the
     * file yet. So this is perfectly fine:
     * \code
     * QuaZipFile file("somezip.zip");
     * file.setFileName("somefile");
     * QString name=file.getName(); // name=="somefile"
     * QString actual=file.getActualFileName(); // actual is null string
     * file.open(QIODevice::ReadOnly);
     * QString actual=file.getActualFileName(); // actual can be "SoMeFiLe" on Windows
     * \endcode
     *
     * \sa getZipName(), getFileName(), QuaZip::CaseSensitivity
     **/
    /// 실제 파일 이름을 아카이브에 반환합니다.
    /* * 이것은 ZIP 아카이브 파일 이름이 아니라 내부 파일 이름입니다.
     * 아카이브. 당신이 보낸 것과 같은 이름은 필요하지 않습니다.
     * 로
     * QuaZipFile (const QString &, const QString &, QuaZip :: CaseSensitivity, QObject *),
     * setFileName () 또는 QuaZip :: setCurrentFile () - 이것은 실제 파일입니다.
     * 이름은 아카이브 내부에 있으므로 파일 이름
     * 검색은 대소 문자를 구분하지 않았습니다.
     *
     * 관련 클래스에서 getCurrentFileName ()을 호출하는 것과 같습니다.
     * QuaZip 개체. 관련 지을 수 있지 않은 경우는 null의 캐릭터 라인을 돌려줍니다.
     * QuaZip 개체 또는 아직 현재 파일이없는 경우. 이
     *는 setFileName ()을 호출했지만 해당 파일을 열지 않은 경우입니다.
     * 아직 파일. 그래서 이것은 완벽합니다.
     * \ code
     * QuaZipFile 파일 ( "somezip.zip");
     * file.setFileName ( "somefile");
     * QString name = file.getName (); // name == "somefile"
     * QString actual = file.getActualFileName (); // 실제는 null입니다. string
     * file.open (QIODevice :: ReadOnly);
     * QString actual = file.getActualFileName (); // Windows에서 실제는 "SoMeFiLe"일 수 있습니다.
     * \ endcode
     *
     * \ sa getZipName (), getFileName (), QuaZip :: CaseSensitivity
     * */
    QString getActualFileName()const;
    /// Sets the ZIP archive file name.
    /** Automatically creates internal QuaZip object and destroys
     * previously created internal QuaZip object, if any.
     *
     * Will do nothing if this file is already open. You must close() it
     * first.
     **/
    /// ZIP 아카이브 파일 이름을 설정합니다.
    /* * 자동으로 내부 QuaZip 객체를 생성하고 소멸시킵니다.
     * 이전에 생성 된 내부 QuaZip 객체 (있는 경우).
     *
     *이 파일이 이미 열려 있으면 아무 작업도 수행하지 않습니다. 그것을 닫아야합니다 ().
     * 처음.
     * */
    void setZipName(const QString& zipName);
    /// Returns \c true if the file was opened in raw mode.
    /** If the file is not open, the returned value is undefined.
     *
     * \sa open(OpenMode,int*,int*,bool,const char*)
     **/
    /// Returns \ c 파일이 원시 모드로 열려 있으면 true입니다.
    /* * 파일이 열려 있지 않으면 반환 값은 정의되지 않습니다.
     *
     * \ sa 오픈 (OpenMode, int *, int *, bool, const char *)
     * */
    bool isRaw() const;
    /// Binds to the existing QuaZip instance.
    /** This function destroys internal QuaZip object, if any, and makes
     * this QuaZipFile to use current file in the \a zip object for any
     * further operations. See QuaZipFile(QuaZip*,QObject*) for the
     * possible pitfalls.
     *
     * Will do nothing if the file is currently open. You must close()
     * it first.
     **/
    //기존 QuaZip 인스턴스에 바인딩합니다.
    /* *이 함수는 내부 QuaZip 객체를 없애고
     *이 QuaZipFile은 현재 파일을 \ zip 객체로 사용합니다.
     * 추가 작업. QuaZipFile (QuaZip *, QObject *)을 참조하십시오.
     * 가능한 함정.
     *
     * 파일이 현재 열려 있으면 아무 작업도 수행하지 않습니다. 당신은 ()
     * 처음.
     * */
    void setZip(QuaZip *zip);
    /// Sets the file name.
    /** Will do nothing if at least one of the following conditions is
     * met:
     * - ZIP name has not been set yet (getZipName() returns null
     *   string).
     * - This QuaZipFile is associated with external QuaZip. In this
     *   case you should call that QuaZip's setCurrentFile() function
     *   instead!
     * - File is already open so setting the name is meaningless.
     *
     * \sa QuaZip::setCurrentFile
     **/
    /// 파일 이름을 설정합니다.
    /* * 다음 조건 중 적어도 하나가 충족되면 아무 작업도 수행하지 않습니다.
     * 충족 됨 :
     * - ZIP 이름이 아직 설정되지 않았습니다 (getZipName ()이 null을 반환 함).
     * 문자열).
     * -이 QuaZip 파일은 외부 QuaZip과 연결됩니다. 이
     * 케이스 당신은 QuaZip의 setCurrentFile () 함수를 호출해야합니다.
     * 대신!
     * - 파일이 이미 열려 있으므로 이름을 설정하는 것은 의미가 없습니다.
     *
     * \ sa QuaZip :: setCurrentFile
     * */
    void setFileName(const QString& fileName, QuaZip::CaseSensitivity cs =QuaZip::csDefault);
    /// Opens a file for reading.
    /** Returns \c true on success, \c false otherwise.
     * Call getZipError() to get error code.
     *
     * \note Since ZIP/UNZIP API provides buffered reading only,
     * QuaZipFile does not support unbuffered reading. So do not pass
     * QIODevice::Unbuffered flag in \a mode, or open will fail.
     **/
    /// 읽을 파일을 엽니 다.
    /* * 성공하면 \ c를 반환하고 그렇지 않으면 false를 반환합니다.
     * 에러 코드를 얻으려면 getZipError ()를 호출하십시오.
     *
     * \ note ZIP / UNZIP API는 버퍼링 된 읽기 전용을 제공하기 때문에,
     * QuaZipFile은 버퍼링되지 않은 읽기를 지원하지 않습니다. 그러니지나 가지 마라.
     * QIODevice :: \ a 모드에서 버퍼링되지 않은 플래그 또는 open이 실패합니다.
     * */
    virtual bool open(OpenMode mode);
    /// Opens a file for reading.
    /** \overload
     * Argument \a password specifies a password to decrypt the file. If
     * it is NULL then this function behaves just like open(OpenMode).
     **/
    /// 읽을 파일을 엽니 다.
    /* * \ overload
     * Argument \ a password는 파일의 암호를 해독 할 암호를 지정합니다. 만약
     * NULL이면이 함수는 open (OpenMode)처럼 동작합니다.
     * */
    inline bool open(OpenMode mode, const char *password)
    {return open(mode, NULL, NULL, false, password);}
    /// Opens a file for reading.
    /** \overload
     * Argument \a password specifies a password to decrypt the file.
     *
     * An integers pointed by \a method and \a level will receive codes
     * of the compression method and level used. See unzip.h.
     *
     * If raw is \c true then no decompression is performed.
     *
     * \a method should not be \c NULL. \a level can be \c NULL if you
     * don't want to know the compression level.
     **/
    /// 읽을 파일을 엽니 다.
    /* * \ overload
     * Argument \ a password는 파일의 암호를 해독 할 암호를 지정합니다.
     *
     * 메소드와 \ a 레벨이 가리키는 정수는 코드를받습니다.
     * 사용 된 압축 방법 및 레벨. unzip.h를 참조하십시오.
     *
     * raw가 \ c true의 경우, 압축 해제는 실행되지 않습니다.
     *
     * \ 메소드는 \ c NULL이 아니어야합니다. \ a 레벨은 \ c NULL 일 수 있습니다.
     * 압축 수준을 알고 싶지 않습니다.
     * */
    bool open(OpenMode mode, int *method, int *level, bool raw, const char *password =NULL);
    /// Opens a file for writing.
    /** \a info argument specifies information about file. It should at
     * least specify a correct file name. Also, it is a good idea to
     * specify correct timestamp (by default, current time will be
     * used). See QuaZipNewInfo.
     *
     * The \a password argument specifies the password for crypting. Pass NULL
     * if you don't need any crypting. The \a crc argument was supposed
     * to be used for crypting too, but then it turned out that it's
     * false information, so you need to set it to 0 unless you want to
     * use the raw mode (see below).
     *
     * Arguments \a method and \a level specify compression method and
     * level. The only method supported is Z_DEFLATED, but you may also
     * specify 0 for no compression. If all of the files in the archive
     * use both method 0 and either level 0 is explicitly specified or
     * data descriptor writing is disabled with
     * QuaZip::setDataDescriptorWritingEnabled(), then the
     * resulting archive is supposed to be compatible with the 1.0 ZIP
     * format version, should you need that. Except for this, \a level
     * has no other effects with method 0.
     *
     * If \a raw is \c true, no compression is performed. In this case,
     * \a crc and uncompressedSize field of the \a info are required.
     *
     * Arguments \a windowBits, \a memLevel, \a strategy provide zlib
     * algorithms tuning. See deflateInit2() in zlib.
     **/
    /// 쓰기 위해 파일을 엽니 다.
    /* * \ info 인수는 파일에 대한 정보를 지정합니다. ~에서해야합니다.
     적어도 정확한 파일 이름을 지정하십시오. 또한,
     * 정확한 타임 스탬프를 지정하십시오 (기본적으로 현재 시간은
     * 사용). QuaZipNewInfo를보십시오.
     *
     * \ password 인수는 암호화할 암호를 지정합니다. 패스 NULL
     * 암호가 필요하지 않은 경우. \ crc 인수가 있어야합니다.
     * 암호를 해독 하는데도 사용되지만,
     * 잘못된 정보이므로 원하는 경우가 아니라면 0으로 설정해야합니다.
     * 원시 모드를 사용하십시오 (아래 참조).
     *
     * 인수 및 메서드 및 \ a 수준 압축 방법을 지정하고
     * 수준. 지원되는 유일한 방법은 Z_DEFLATED이지만,
     * 압축하지 않으려면 0을 지정하십시오. 아카이브의 모든 파일
     * 메소드 0을 모두 사용하고 레벨 0이 명시 적으로 지정되거나
     * 데이터 설명자 쓰기가 비활성화 됨
     * QuaZip :: setDataDescriptorWritingEnabled (), 그런 다음
     * 결과 아카이브는 1.0 ZIP과 호환 가능합니다.
     * 포맷 버전이 필요합니다. 이것을 제외하고는 \ a 레벨
     * 메소드 0에는 다른 효과가 없습니다.
     *
     * \ raw가 \ true이면 압축이 수행되지 않습니다. 이 경우,
     * \ a crc 및 \ a 정보의 uncompressedSize 필드가 필요합니다.
     *
     * 인수 \ a windowBits, \ a memLevel, \ z 전략 제공 zlib
     * 알고리즘 튜닝. zlib의 deflateInit2 ()를 참조하십시오.
     * */
    bool open(OpenMode mode, const QuaZipNewInfo& info,
        const char *password =NULL, quint32 crc =0,
        int method =Z_DEFLATED, int level =Z_DEFAULT_COMPRESSION, bool raw =false,
        int windowBits =-MAX_WBITS, int memLevel =DEF_MEM_LEVEL, int strategy =Z_DEFAULT_STRATEGY);
    /// Returns \c true, but \ref quazipfile-sequential "beware"!
    virtual bool isSequential()const;
    /// Returns current position in the file.
    /** Implementation of the QIODevice::pos(). When reading, this
     * function is a wrapper to the ZIP/UNZIP unztell(), therefore it is
     * unable to keep track of the ungetChar() calls (which is
     * non-virtual and therefore is dangerous to reimplement). So if you
     * are using ungetChar() feature of the QIODevice, this function
     * reports incorrect value until you get back characters which you
     * ungot.
     *
     * When writing, pos() returns number of bytes already written
     * (uncompressed unless you use raw mode).
     *
     * \note Although
     * \ref quazipfile-sequential "QuaZipFile is a sequential device"
     * and therefore pos() should always return zero, it does not,
     * because it would be misguiding. Keep this in mind.
     *
     * This function returns -1 if the file or archive is not open.
     *
     * Error code returned by getZipError() is not affected by this
     * function call.
     **/
    /// 파일의 현재 위치를 반환합니다.
    /* * QIODevice :: pos ()의 구현. 읽을 때,이
     * function은 ZIP / UNZIP unztell ()에 대한 래퍼입니다. 따라서
     * ungetChar () 호출을 추적 할 수 없습니다.
     * 가상이 아니므로 다시 구현하는 것은 위험합니다.) 그래서 네가
     * QIODevice의 ungetChar () 기능을 사용하고 있습니다.이 함수는
     * 잘못된 값을보고 할 때까지 잘못된 값을보고합니다.
     * 모른.
     *
     * 쓰는 경우, pos ()는 이미 기록 된 바이트 수를 반환합니다.
     * (원시 모드를 사용하지 않는 한 압축되지 않음).
     *
     * \ note
     * \ ref quazipfile-sequential "QuaZipFile은 순차적 장치입니다"
     * 따라서 pos ()는 항상 0을 반환해야합니다. 그렇지 않습니다.
     * 잘못된 길을 찾고 있기 때문입니다. 이를 명심하십시오.
     *
     *이 함수는 파일이나 아카이브가 열려 있지 않으면 -1을 반환합니다.
     *
     * getZipError ()에 의해 반환 된 에러 코드는 이것의 영향을받지 않습니다.
     * 함수 호출.
     * */
    virtual qint64 pos()const;
    /// Returns \c true if the end of file was reached.
    /** This function returns \c false in the case of error. This means
     * that you called this function on either not open file, or a file
     * in the not open archive or even on a QuaZipFile instance that
     * does not even have QuaZip instance associated. Do not do that
     * because there is no means to determine whether \c false is
     * returned because of error or because end of file was reached.
     * Well, on the other side you may interpret \c false return value
     * as "there is no file open to check for end of file and there is
     * no end of file therefore".
     *
     * When writing, this function always returns \c true (because you
     * are always writing to the end of file).
     *
     * Error code returned by getZipError() is not affected by this
     * function call.
     **/
    // 파일의 끝 부분에 도달하면 true를 반환합니다.
    /* *이 함수는 에러가 발생할 경우 \ c false를 반환합니다. 이것은
     *이 함수는 열린 파일이나 파일에서 호출하지 않았습니다.
     * 오픈 아카이브가 아니거나 QuaZipFile 인스턴스에서도
     *에는 QuaZip 인스턴스가 연결되어 있지 않습니다. 그거 하지마
     왜냐하면 \ c 거짓인지 아닌지를 결정할 수단이 없기 때문이다.
     * 오류로 인해 또는 파일 끝에 도달했기 때문에 반환되었습니다.
     * 글쎄, 다른 쪽에서는 \ c 거짓 값을 해석 할 수있다.
     * "파일의 끝을 확인할 수있는 파일이없고
     * 따라서 파일의 끝 ".
     *
     * 쓸 때이 함수는 항상 \ c true를 반환합니다 (왜냐하면
     *는 항상 파일의 끝에 쓰고).
     *
     * getZipError ()에 의해 반환 된 에러 코드는 이것의 영향을받지 않습니다.
     * 함수 호출.
     * */
    virtual bool atEnd()const;
    /// Returns file size.
    /** This function returns csize() if the file is open for reading in
     * raw mode, usize() if it is open for reading in normal mode and
     * pos() if it is open for writing.
     *
     * Returns -1 on error, call getZipError() to get error code.
     *
     * \note This function returns file size despite that
     * \ref quazipfile-sequential "QuaZipFile is considered to be sequential device",
     * for which size() should return bytesAvailable() instead. But its
     * name would be very misguiding otherwise, so just keep in mind
     * this inconsistence.
     **/
    /// 파일 크기를 반환합니다.
    /* *이 함수는 파일이 읽기 용으로 열린 경우 csize ()를 반환합니다.
     * raw 모드, usize () (정상 모드에서 읽기 위해 열려있는 경우)
     * pos ()가 쓰기 용으로 열려 있으면.
     *
     * 오류가 발생하면 -1을 반환하고 getZipError ()를 호출하여 오류 코드를 가져옵니다.
     *
     * \ note이 함수는 파일 크기를 반환하지만
     * \ ref quazipfile-sequential "QuaZipFile은 순차적 장치로 간주됩니다"
     * size ()는 bytesAvailable ()을 대신 반환해야합니다. 그러나 그것의
     * 이름은 다른 방법으로 잘못 인도하는 경우가 있으므로 염두에 두십시오.
     *이 불일치.
     * */
    virtual qint64 size()const;
    /// Returns compressed file size.
    /** Equivalent to calling getFileInfo() and then getting
     * compressedSize field, but more convenient and faster.
     *
     * File must be open for reading before calling this function.
     *
     * Returns -1 on error, call getZipError() to get error code.
     **/
    // 압축 된 파일 크기를 반환합니다.
    /* * getFileInfo ()를 호출 한 다음
     * compressedSize 필드가 더 편리하고 빠릅니다.
     *
     *이 함수를 호출하기 전에 파일을 읽기 위해 열어야합니다.
     *
     * 오류가 발생하면 -1을 반환하고 getZipError ()를 호출하여 오류 코드를 가져옵니다.
     * */
    qint64 csize()const;
    /// Returns uncompressed file size.
    /** Equivalent to calling getFileInfo() and then getting
     * uncompressedSize field, but more convenient and faster. See
     * getFileInfo() for a warning.
     *
     * File must be open for reading before calling this function.
     *
     * Returns -1 on error, call getZipError() to get error code.
     **/
    // 압축되지 않은 파일 크기를 반환합니다.
    /* * getFileInfo ()를 호출 한 다음
     * uncompressedSize 필드가 더 편리하고 빠릅니다. 만나다
     * 경고를위한 getFileInfo ().
     *
     *이 함수를 호출하기 전에 파일을 읽기 위해 열어야합니다.
     *
     * 오류가 발생하면 -1을 반환하고 getZipError ()를 호출하여 오류 코드를 가져옵니다.
     * */
    qint64 usize()const;
    /// Gets information about current file.
    /** This function does the same thing as calling
     * QuaZip::getCurrentFileInfo() on the associated QuaZip object,
     * but you can not call getCurrentFileInfo() if the associated
     * QuaZip is internal (because you do not have access to it), while
     * you still can call this function in that case.
     *
     * File must be open for reading before calling this function.
     *
     * Returns \c false in the case of an error.
     **/
    //현재 파일에 대한 정보를 가져옵니다.
    /* *이 함수는 호출과 같은 기능을한다.
     * QuaZip :: getCurrentFileInfo () 연관된 QuaZip 객체에 대해,
     *하지만 연결된 경우 getCurrentFileInfo ()를 호출 할 수 없습니다.
     * QuaZip은 내부에 있으므로 (액세스 권한이 없으므로),
     *이 경우에도이 함수를 호출 할 수 있습니다.
     *
     *이 함수를 호출하기 전에 파일을 읽기 위해 열어야합니다.
     *
     * 오류가 발생하면 \ c를 반환합니다.
     * */
    bool getFileInfo(QuaZipFileInfo *info);
    /// Closes the file.
    /** Call getZipError() to determine if the close was successful.
     **/
    /// 파일을 닫습니다.
    /* * getZipError ()를 호출하여 닫기가 성공적인지 여부를 확인하십시오.
     * */
    virtual void close();
    /// Returns the error code returned by the last ZIP/UNZIP API call.
    /// 마지막 ZIP / UNZIP API 호출에서 리턴 된 오류 코드를 리턴합니다.
    int getZipError() const;
    /// Returns the number of bytes available for reading.
    /// 읽기에 사용할 수있는 바이트 수를 반환합니다.
    virtual qint64 bytesAvailable() const;
};

#endif
