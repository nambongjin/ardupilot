/* zip.h -- IO for compress .zip files using zlib
   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   This unzip package allow creates .ZIP file, compatible with PKZip 2.04g
     WinZip, InfoZip tools and compatible.
   Multi volume ZipFile (span) are not supported.
   Encryption compatible with pkzip 2.04g only supported
   Old compressions used by old PKZip 1.x are not supported

  For uncompress .zip file, look at unzip.h


   I WAIT FEEDBACK at mail info@winimage.com
   Visit also http://www.winimage.com/zLibDll/unzip.html for evolution

   Condition of use and distribution are the same than zlib :

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

   Modified by Sergey A. Tachenov to integrate with Qt.


*/

/* for more info about .ZIP format, see
      http://www.info-zip.org/pub/infozip/doc/appnote-981119-iz.zip
      http://www.info-zip.org/pub/infozip/doc/
   PkWare has also a specification at :
      ftp://ftp.pkware.com/probdesc.zip
*/

/*

.ZIP 형식에 대한 자세한 내용은
      http://www.info-zip.org/pub/infozip/doc/appnote-981119-iz.zip
      http://www.info-zip.org/pub/infozip/doc/
   PkWare는 다음에서 사양을 제공합니다.
      ftp://ftp.pkware.com/probdesc.zip
*/


#ifndef _zip_H
#define _zip_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ZLIB_H
#include <QtGlobal>
#ifdef Q_CC_MSVC
#include <QtZlib/zlib.h>
#else
#include "zlib.h"
#endif
#endif

#ifndef _ZLIBIOAPI_H
#include "ioapi.h"
#endif

#if defined(STRICTZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
    from (void*) without cast */

/*
/ * WIN32의 STRICT처럼 변환 할 수없는 포인터를 정의한다.
    from (void *) from cast * /
*/

typedef struct TagzipFile__ { int unused; } zipFile__;
typedef zipFile__ *zipFile;
#else
typedef voidp zipFile;
#endif

#define ZIP_OK                          (0)
#define ZIP_EOF                         (0)
#define ZIP_ERRNO                       (Z_ERRNO)
#define ZIP_PARAMERROR                  (-102)
#define ZIP_BADZIPFILE                  (-103)
#define ZIP_INTERNALERROR               (-104)

#define ZIP_WRITE_DATA_DESCRIPTOR 0x8u

#ifndef DEF_MEM_LEVEL
#  if MAX_MEM_LEVEL >= 8
#    define DEF_MEM_LEVEL 8
#  else
#    define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#  endif
#endif
/* default memLevel */

/* tm_zip contain date/time info */

/*
/ * tm_zip에 날짜 / 시간 정보 포함 * /
*/

typedef struct tm_zip_s
{
    uInt tm_sec;            /* seconds after the minute - [0,59] 	/ * 분 후 초 - [0,59] * /*/	
    uInt tm_min;            /* minutes after the hour - [0,59] 		시간 후 분 - [0,59]	*/
    uInt tm_hour;           /* hours since midnight - [0,23] 	 / * 자정 이후 시간 - [0,23] * /*/
    uInt tm_mday;           /* day of the month - [1,31] 	/ * 달의 일 - [1,31] * /*/
    uInt tm_mon;            /* months since January - [0,11] 	/ * 1 월 이후의 달 - [0,11] * /*/
    uInt tm_year;           /* years - [1980..2044] 	/ * 년 - [1980..2044] * /*/
} tm_zip;

typedef struct
{
    tm_zip      tmz_date;       /* date in understandable format          	/ * 이해할 수있는 형식의 날짜            * / */
    uLong       dosDate;       /* if dos_date == 0, tmu_date is used      	/ * dos_date == 0이면 tmu_date가 사용됩니다.       * /*/
/*    uLong       flag;        */   /* general purpose bit flag        2 bytes */

/*
/ *     uLong 플래그;        * /    / * 범용 비트 플래그 2 바이트 * /
*/


    uLong       internal_fa;    /* internal file attributes        2 bytes 	 / * 내부 파일 속성 2 바이트 * /*/
    uLong       external_fa;    /* external file attributes        4 bytes 	/ * 외부 파일 속성 4 바이트 * /*/
} zip_fileinfo;

typedef const char* zipcharpc;


#define APPEND_STATUS_CREATE        (0)
#define APPEND_STATUS_CREATEAFTER   (1)
#define APPEND_STATUS_ADDINZIP      (2)

extern zipFile ZEXPORT zipOpen OF((voidpf file, int append));
/*
  Create a zipfile.
     file is whatever the IO API accepts. For Qt IO API it's a pointer to
       QIODevice. For fopen() IO API it's a file name (const char*).
     if the file pathname exist and append==APPEND_STATUS_CREATEAFTER, the zip
       will be created at the end of the file.
         (useful if the file contain a self extractor code)
     if the file pathname exist and append==APPEND_STATUS_ADDINZIP, we will
       add files in existing zip (be sure you don't add file that doesn't exist)
     If the zipfile cannot be opened, the return value is NULL.
     Else, the return value is a zipFile Handle, usable with other function
       of this zip package.
*/

/*
/ *
  zip 파일을 만듭니다.
     파일은 IO API가 받아들이는 것입니다. Qt IO API의 경우 포인터입니다.
       QIODevice. fopen () IO API의 경우 파일 이름 (const char *)입니다.
     파일 경로 이름이 존재하고 append == APPEND_STATUS_CREATEAFTER 인 경우, zip
       파일의 끝에 생성됩니다.
         (파일에 자체 추출 코드가 포함 된 경우 유용함)
     파일 경로 이름이 존재하고 == APPEND_STATUS_ADDINZIP을 추가하면
       기존 zip에 파일을 추가하십시오 (존재하지 않는 파일을 추가하지 마십시오).
     zip 파일을 열 수 없으면 반환 값은 NULL입니다.
     그렇지 않으면 반환 값은 다른 함수와 함께 사용할 수있는 zipFile Handle입니다.
       이 우편 패키지의
* /
*/


/* Note : there is no delete function into a zipfile.
   If you want delete file into a zipfile, you must open a zipfile, and create another
   Of couse, you can use RAW reading and writing to copy the file you did not want delte
*/

/*
/ * 참고 : zip 파일에는 삭제 기능이 없습니다.
   파일을 zip 파일로 삭제하려면 zip 파일을 열고 다른 파일을 만들어야합니다
   couse의 경우, RAW 읽기 및 쓰기를 사용하여 델타를 원하지 않는 파일을 복사 할 수 있습니다
* /
*/


extern zipFile ZEXPORT zipOpen2 OF((voidpf file,
                                   int append,
                                   zipcharpc* globalcomment,
                                   zlib_filefunc_def* pzlib_filefunc_def));

extern int ZEXPORT zipOpenNewFileInZip OF((zipFile file,
                       const char* filename,
                       const zip_fileinfo* zipfi,
                       const void* extrafield_local,
                       uInt size_extrafield_local,
                       const void* extrafield_global,
                       uInt size_extrafield_global,
                       const char* comment,
                       int method,
                       int level));
/*
  Open a file in the ZIP for writing.
  filename : the filename in zip (if NULL, '-' without quote will be used
  *zipfi contain supplemental information
  if extrafield_local!=NULL and size_extrafield_local>0, extrafield_local
    contains the extrafield data the the local header
  if extrafield_global!=NULL and size_extrafield_global>0, extrafield_global
    contains the extrafield data the the local header
  if comment != NULL, comment contain the comment string
  method contain the compression method (0 for store, Z_DEFLATED for deflate)
  level contain the level of compression (can be Z_DEFAULT_COMPRESSION)
*/

/*
  작성을 위해 ZIP 파일을여십시오.
  filename : zip 파일 이름 (NULL 인 경우 인용 부호없이 '-'사용)
  * zipfi는 보충 정보를 포함합니다.
  extrafield_local! = NULL 및 size_extrafield_local> 0 인 경우 extrafield_local
    여분의 데이터를 포함한다.
  extrafield_global! = NULL 및 size_extrafield_global> 0 인 경우 extrafield_global
    여분의 데이터를 포함한다.
  주석! = NULL이면 주석은 주석 문자열을 포함합니다.
  메소드에는 압축 메소드가 포함됩니다 (저장소의 경우 0, deflate의 경우 Z_DEFLATED).
  레벨은 압축 수준을 포함합니다 (Z_DEFAULT_COMPRESSION 일 수 있음).
*/



extern int ZEXPORT zipOpenNewFileInZip2 OF((zipFile file,
                                            const char* filename,
                                            const zip_fileinfo* zipfi,
                                            const void* extrafield_local,
                                            uInt size_extrafield_local,
                                            const void* extrafield_global,
                                            uInt size_extrafield_global,
                                            const char* comment,
                                            int method,
                                            int level,
                                            int raw));

/*
  Same than zipOpenNewFileInZip, except if raw=1, we write raw file
 */

/*
  zipOpenNewFileInZip과 동일합니다. raw = 1 인 경우를 제외하고는 raw 파일
*/


extern int ZEXPORT zipOpenNewFileInZip3 OF((zipFile file,
                                            const char* filename,
                                            const zip_fileinfo* zipfi,
                                            const void* extrafield_local,
                                            uInt size_extrafield_local,
                                            const void* extrafield_global,
                                            uInt size_extrafield_global,
                                            const char* comment,
                                            int method,
                                            int level,
                                            int raw,
                                            int windowBits,
                                            int memLevel,
                                            int strategy,
                                            const char* password,
                                            uLong crcForCtypting));

/*
  Same than zipOpenNewFileInZip2, except
    windowBits,memLevel,,strategy : see parameter strategy in deflateInit2
    password : crypting password (NULL for no crypting)
    crcForCtypting : crc of file to compress (needed for crypting)
 */

/*
  zipOpenNewFileInZip2와 동일합니다.
    windowBits, memLevel, strategy : deflateInit2의 매개 변수 전략 참조
    암호 : 암호 해독 (암호화하지 않을 경우 NULL)
    crcForCtypting : 압축 할 파일의 crc (암호화에 필요함)
*/



extern int ZEXPORT zipWriteInFileInZip OF((zipFile file,
                       const void* buf,
                       unsigned len));
/*
  Write data in the zipfile
*/

/*
  zip 파일에 데이터 쓰기
*/


extern int ZEXPORT zipCloseFileInZip OF((zipFile file));
/*
  Close the current file in the zipfile
*/

/*
  zip 파일에서 현재 파일 닫기
*/


extern int ZEXPORT zipCloseFileInZipRaw OF((zipFile file,
                                            uLong uncompressed_size,
                                            uLong crc32));
/*
  Close the current file in the zipfile, for fiel opened with
    parameter raw=1 in zipOpenNewFileInZip2
  uncompressed_size and crc32 are value for the uncompressed size
*/

/*
  zip 파일에서 현재 파일을 닫습니다.
    zipOpenNewFileInZip2에서 raw = 1 매개 변수
  uncompressed_size 및 crc32는 압축되지 않은 크기의 값입니다.
*/


extern int ZEXPORT zipClose OF((zipFile file,
                const char* global_comment));
/*
  Close the zipfile
*/

/*
  zip 파일 닫기
*/


/*
   Added by Sergey A. Tachenov to tweak zipping behaviour.
   */

/*
   지그재그 동작을 조정하기 위해 Sergey A. Tachenov에 의해 추가되었습니다.
*/

extern int ZEXPORT zipSetFlags(zipFile file, unsigned flags);
extern int ZEXPORT zipClearFlags(zipFile file, unsigned flags);

#ifdef __cplusplus
}
#endif

#endif /* _zip_H */
