/* unzip.h -- IO for uncompress .zip files using zlib
   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   This unzip package allow extract file from .ZIP file, compatible with PKZip 2.04g
     WinZip, InfoZip tools and compatible.

   Multi volume ZipFile (span) are not supported.
   Encryption compatible with pkzip 2.04g only supported
   Old compressions used by old PKZip 1.x are not supported


   I WAIT FEEDBACK at mail info@winimage.com
   Visit also http://www.winimage.com/zLibDll/unzip.htm for evolution

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

#ifndef _unz_H
#define _unz_H

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

#if defined(STRICTUNZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
    from (void*) without cast */
/* WIN32의 STRICT처럼 변환 할 수없는 포인터를 정의한다.
    from (void *) from cast */
typedef struct TagunzFile__ { int unused; } unzFile__;
typedef unzFile__ *unzFile;
#else
typedef voidp unzFile;
#endif


#define UNZ_OK                          (0)
#define UNZ_END_OF_LIST_OF_FILE         (-100)
#define UNZ_ERRNO                       (Z_ERRNO)
#define UNZ_EOF                         (0)
#define UNZ_PARAMERROR                  (-102)
#define UNZ_BADZIPFILE                  (-103)
#define UNZ_INTERNALERROR               (-104)
#define UNZ_CRCERROR                    (-105)

/* tm_unz contain date/time info */
/* tm_unz에 날짜 / 시간 정보 포함 */
typedef struct tm_unz_s
{
    uInt tm_sec;            /* seconds after the minute - [0,59] */  /* 분 후 초 - [0,59] */
    uInt tm_min;            /* minutes after the hour - [0,59] */    /* 시간 후 분 - [0,59] */
    uInt tm_hour;           /* hours since midnight - [0,23] */      /* 자정 이후 시간 - [0,23] */
    uInt tm_mday;           /* day of the month - [1,31] */          /* 달의 일 - [1,31] */
    uInt tm_mon;            /* months since January - [0,11] */      /* 1 월 이후의 달 - [0,11] */
    uInt tm_year;           /* years - [1980..2044] */               /* 년 - [1980..2044] */
} tm_unz;

/* unz_global_info structure contain global data about the ZIPfile
   These data comes from the end of central dir */
/* unz_global_info 구조체는 ZIP 파일에 대한 전역 데이터를 포함합니다.
   이러한 데이터는 중앙 디렉터리의 끝에서옵니다 */
typedef struct unz_global_info_s
{
    uLong number_entry;         /* total number of entries in 
                       the central dir on this disk */            
    uLong size_comment;         /* size of the global comment of the zipfile */
} unz_global_info;
  /* 총 항목 수 이 디스크의 중앙 디렉토리 */
  /* zip 파일의 전체 주석 크기 */

/* unz_file_info contain information about a file in the zipfile */
/* unz_file_info에는 zip 파일의 파일에 대한 정보가 들어 있습니다. */
typedef struct unz_file_info_s
{
    uLong version;              /* version made by                 2 bytes */
    uLong version_needed;       /* version needed to extract       2 bytes */
    uLong flag;                 /* general purpose bit flag        2 bytes */
    uLong compression_method;   /* compression method              2 bytes */
    uLong dosDate;              /* last mod file date in Dos fmt   4 bytes */
    uLong crc;                  /* crc-32                          4 bytes */
    uLong compressed_size;      /* compressed size                 4 bytes */
    uLong uncompressed_size;    /* uncompressed size               4 bytes */
    uLong size_filename;        /* filename length                 2 bytes */
    uLong size_file_extra;      /* extra field length              2 bytes */
    uLong size_file_comment;    /* file comment length             2 bytes */

    uLong disk_num_start;       /* disk number start               2 bytes */
    uLong internal_fa;          /* internal file attributes        2 bytes */
    uLong external_fa;          /* external file attributes        4 bytes */

    tm_unz tmu_date;
} unz_file_info;

extern int ZEXPORT unzStringFileNameCompare OF ((const char* fileName1,
                                                 const char* fileName2,
                                                 int iCaseSensitivity));
/*
   Compare two filename (fileName1,fileName2).
   If iCaseSenisivity = 1, comparision is case sensitivity (like strcmp)
   If iCaseSenisivity = 2, comparision is not case sensitivity (like strcmpi
                                or strcasecmp)
   If iCaseSenisivity = 0, case sensitivity is defaut of your operating system
    (like 1 on Unix, 2 on Windows)
*/
/*
   두 파일 이름 (fileName1, fileName2)을 비교하십시오.
   iCaseSenisivity = 1 인 경우 비교는 대소 문자를 구분합니다 (예 : strcmp)
   iCaseSenisivity = 2 인 경우 비교는 대소 문자를 구분하지 않습니다 (예 : strcmpi
                                또는 strcasecmp)
   iCaseSenisivity = 0 인 경우 운영 체제에서 대소 문자를 구분하지 않습니다.
    (Unix의 경우 1, Windows의 경우 2)
*/


extern unzFile ZEXPORT unzOpen OF((voidpf file));
/*
  Open a Zip file. path contain whatever zopen_file from the IO API
  accepts. For Qt implementation it is a pointer to QIODevice, for
  fopen() implementation it's a file name.
     If the zipfile cannot be opened (file don't exist or in not valid), the
       return value is NULL.
     Else, the return value is a unzFile Handle, usable with other function
       of this unzip package.
*/
/*
  Zip 파일을 엽니 다. 경로는 IO API의 zopen_file을 포함합니다.
  받아 들인다. Qt 구현의 경우 QIODevice에 대한 포인터입니다.
  fopen () 구현은 파일 이름입니다.
     zip 파일을 열 수 없으면 (파일이 존재하지 않거나 유효하지 않음),
       반환 값은 NULL입니다.
     그렇지 않으면 반환 값은 unzFile Handle이며 다른 함수와 함께 사용할 수 있습니다.
       이 압축 패키지의.
*/
extern unzFile ZEXPORT unzOpen2 OF((voidpf file,
                                    zlib_filefunc_def* pzlib_filefunc_def));
/*
   Open a Zip file, like unzOpen, but provide a set of file low level API
      for read/write the zip file (see ioapi.h)
*/
/*
   unzOpen과 같은 Zip 파일 열기, 파일 저수준 API 세트 제공
      zip 파일 읽기 / 쓰기 (ioapi.h 참고)
*/

extern int ZEXPORT unzClose OF((unzFile file));
/*
  Close a ZipFile opened with unzipOpen.
  If there is files inside the .Zip opened with unzOpenCurrentFile (see later),
    these files MUST be closed with unzipCloseCurrentFile before call unzipClose.
  return UNZ_OK if there is no problem. */

/*
  unzipOpen으로 열린 ZipFile을 닫습니다.
  unzOpenCurrentFile로 열린 .Zip 안에 파일이 있다면 (나중에 보자),
    이러한 파일은 unzipClose를 호출하기 전에 unzipCloseCurrentFile로 닫혀 있어야합니다 (MUST).
  문제가 없으면 UNZ_OK를 리턴하십시오. */


extern int ZEXPORT unzGetGlobalInfo OF((unzFile file,
                                        unz_global_info *pglobal_info));
/*
  Write info about the ZipFile in the *pglobal_info structure.
  No preparation of the structure is needed
  return UNZ_OK if there is no problem. */
/*
  * pglobal_info 구조체에 ZipFile에 대한 정보를 작성하십시오.
  구조의 준비가 필요 없습니다.
  문제가 없으면 UNZ_OK를 리턴하십시오. */


extern int ZEXPORT unzGetGlobalComment OF((unzFile file,
                                           char *szComment,
                                           uLong uSizeBuf));
/*
  Get the global comment string of the ZipFile, in the szComment buffer.
  uSizeBuf is the size of the szComment buffer.
  return the number of byte copied or an error code <0
*/
/*
  szComment 버퍼에있는 ZipFile의 전역 주석 문자열을 가져옵니다.
  uSizeBuf는 szComment 버퍼의 크기입니다.
  카피 된 바이트 수 또는 에러 코드 <0을 리턴한다.
*/

/***************************************************************************/
/* Unzip package allow you browse the directory of the zipfile */
/* zip 파일의 디렉토리를 열람 할 수있는 패키지 압축 풀기 */


extern int ZEXPORT unzGoToFirstFile OF((unzFile file));
/*
  Set the current file of the zipfile to the first file.
  return UNZ_OK if there is no problem
*/
/*
  zip 파일의 현재 파일을 첫 번째 파일로 설정하십시오.
  문제가없는 경우 UNZ_OK를 반환합니다.
*/

extern int ZEXPORT unzGoToNextFile OF((unzFile file));
/*
  Set the current file of the zipfile to the next file.
  return UNZ_OK if there is no problem
  return UNZ_END_OF_LIST_OF_FILE if the actual file was the latest.
*/
/*
  zip 파일의 현재 파일을 다음 파일로 설정하십시오.
  문제가없는 경우 UNZ_OK를 반환합니다.
  실제 파일이 최신 파일이면 UNZ_END_OF_LIST_OF_FILE을 반환합니다.
*/

extern int ZEXPORT unzLocateFile OF((unzFile file,
                     const char *szFileName,
                     int iCaseSensitivity));
/*
  Try locate the file szFileName in the zipfile.
  For the iCaseSensitivity signification, see unzStringFileNameCompare

  return value :
  UNZ_OK if the file is found. It becomes the current file.
  UNZ_END_OF_LIST_OF_FILE if the file is not found
*/
/*
  zip 파일에서 szFileName 파일을 찾으십시오.
  iCaseSensitivity의 의미는 unzStringFileNameCompare를 참조하십시오.
  반환 값 :
  파일이 발견되면 UNZ_OK입니다. 현재 파일이됩니다.
  파일을 찾을 수없는 경우 UNZ_END_OF_LIST_OF_FILE
*/


/* ****************************************** */
/* Ryan supplied functions */
/* unz_file_info contain information about a file in the zipfile */
/* Ryan이 제공 한 함수 */
/* unz_file_info에는 zip 파일의 파일에 대한 정보가 들어 있습니다. */
typedef struct unz_file_pos_s
{
    uLong pos_in_zip_directory;   /* offset in zip file directory */
    uLong num_of_file;            /* # of file */
} unz_file_pos;
/* zip 파일 디렉토리의 오프셋 */
/* 파일 수 */

extern int ZEXPORT unzGetFilePos(
    unzFile file,
    unz_file_pos* file_pos);

extern int ZEXPORT unzGoToFilePos(
    unzFile file,
    unz_file_pos* file_pos);

/* ****************************************** */

extern int ZEXPORT unzGetCurrentFileInfo OF((unzFile file,
                         unz_file_info *pfile_info,
                         char *szFileName,
                         uLong fileNameBufferSize,
                         void *extraField,
                         uLong extraFieldBufferSize,
                         char *szComment,
                         uLong commentBufferSize));
/*
  Get Info about the current file
  if pfile_info!=NULL, the *pfile_info structure will contain somes info about
        the current file
  if szFileName!=NULL, the filemane string will be copied in szFileName
            (fileNameBufferSize is the size of the buffer)
  if extraField!=NULL, the extra field information will be copied in extraField
            (extraFieldBufferSize is the size of the buffer).
            This is the Central-header version of the extra field
  if szComment!=NULL, the comment string of the file will be copied in szComment
            (commentBufferSize is the size of the buffer)
*/
/*
  현재 파일에 대한 정보 얻기
  pfile_info! = NULL의 경우, * pfile_info 구조체에 관한 정보가 포함됩니다.
        현재 파일
  szFileName! = NULL이면 filemane 문자열이 szFileName에 복사됩니다.
            (fileNameBufferSize는 버퍼의 크기입니다.)
  extraField! = NULL 인 경우 추가 필드 정보가 extraField에 복사됩니다.
            (extraFieldBufferSize는 버퍼의 크기입니다.)
            추가 필드의 중앙 헤더 버전입니다.
  szComment! = NULL이면 파일의 주석 문자열이 szComment에 복사됩니다.
            (commentBufferSize는 버퍼의 크기입니다)
*/

/***************************************************************************/
/* for reading the content of the current zipfile, you can open it, read data
   from it, and close it (you can close it before reading all the file)
   */
/* 현재 zip 파일의 내용을 읽으려면 열어서 데이터를 읽을 수 있습니다.
   그것을 닫고 닫으십시오 (모든 파일을 읽기 전에 닫을 수 있음).
   */

extern int ZEXPORT unzOpenCurrentFile OF((unzFile file));
/*
  Open for reading data the current file in the zipfile.
  If there is no error, the return value is UNZ_OK.
*/
/*
  zip 파일의 현재 파일을 읽기 위해 열립니다.
  오류가 없으면 반환 값은 UNZ_OK입니다.
*/
extern int ZEXPORT unzOpenCurrentFilePassword OF((unzFile file,
                                                  const char* password));
/*
  Open for reading data the current file in the zipfile.
  password is a crypting password
  If there is no error, the return value is UNZ_OK.
*/
/*
  zip 파일의 현재 파일을 읽기 위해 열립니다.
  암호는 암호입니다
  오류가 없으면 반환 값은 UNZ_OK입니다.
*/

extern int ZEXPORT unzOpenCurrentFile2 OF((unzFile file,
                                           int* method,
                                           int* level,
                                           int raw));
/*
  Same than unzOpenCurrentFile, but open for read raw the file (not uncompress)
    if raw==1
  *method will receive method of compression, *level will receive level of
     compression
  note : you can set level parameter as NULL (if you did not want known level,
         but you CANNOT set method parameter as NULL
*/
/*
  unzOpenCurrentFile과 동일하지만 파일을 원시 파일로 읽을 때 열립니다 (압축을 풀지 않음).
    if raw == 1
  * 메소드는 압축 메소드를받습니다. * 레벨은 레벨을받습니다.
     압축
  참고 : 레벨 매개 변수를 NULL로 설정할 수 있습니다 (알려진 수준을 원하지 않으면,
         그러나 메서드 매개 변수를 NULL로 설정할 수는 없습니다.
*/

extern int ZEXPORT unzOpenCurrentFile3 OF((unzFile file,
                                           int* method,
                                           int* level,
                                           int raw,
                                           const char* password));
/*
  Same than unzOpenCurrentFile, but open for read raw the file (not uncompress)
    if raw==1
  *method will receive method of compression, *level will receive level of
     compression
  note : you can set level parameter as NULL (if you did not want known level,
         but you CANNOT set method parameter as NULL
*/
/*
  unzOpenCurrentFile과 동일하지만 파일을 원시 파일로 읽을 때 열립니다 (압축을 풀지 않음).
    if raw == 1
  * 메소드는 압축 메소드를받습니다. * 레벨은 레벨을받습니다.
     압축
  참고 : 레벨 매개 변수를 NULL로 설정할 수 있습니다 (알려진 수준을 원하지 않으면,
         그러나 메서드 매개 변수를 NULL로 설정할 수는 없습니다.
*/


extern int ZEXPORT unzCloseCurrentFile OF((unzFile file));
/*
  Close the file in zip opened with unzOpenCurrentFile
  Return UNZ_CRCERROR if all the file was read but the CRC is not good
*/
/*
  unzOpenCurrentFile로 열린 zip 파일을 닫습니다.
  모든 파일을 읽었지만 CRC가 좋지 않으면 UNZ_CRCERROR를 반환합니다.
*/
extern int ZEXPORT unzReadCurrentFile OF((unzFile file,
                      voidp buf,
                      unsigned len));
/*
  Read bytes from the current file (opened by unzOpenCurrentFile)
  buf contain buffer where data must be copied
  len the size of buf.

  return the number of byte copied if somes bytes are copied
  return 0 if the end of file was reached
  return <0 with error code if there is an error
    (UNZ_ERRNO for IO error, or zLib error for uncompress error)
*/
/*
  현재 파일에서 바이트 읽기 (unzOpenCurrentFile에 의해 열림)
  buf는 데이터를 복사해야하는 버퍼를 포함합니다.
  buf의 크기.
  일부 바이트가 복사 된 경우 복사 된 바이트 수를 반환합니다.
  파일의 끝에 도달하면 0을 반환한다.
  오류가 있으면 오류 코드와 함께 <0을 반환합니다.
    (IO 오류의 경우 UNZ_ERRNO, 압축 해제 오류의 경우 zLib 오류)
*/
extern z_off_t ZEXPORT unztell OF((unzFile file));
/*
  Give the current position in uncompressed data
*/
/*
  압축되지 않은 데이터의 현재 위치 지정
*/
extern int ZEXPORT unzeof OF((unzFile file));
/*
  return 1 if the end of file was reached, 0 elsewhere
*/
/*
  파일의 끝에 도달하면 1을 반환하고, 다른 곳에 0을 반환합니다.
*/
extern int ZEXPORT unzGetLocalExtrafield OF((unzFile file,
                                             voidp buf,
                                             unsigned len));
/*
  Read extra field from the current file (opened by unzOpenCurrentFile)
  This is the local-header version of the extra field (sometimes, there is
    more info in the local-header version than in the central-header)

  if buf==NULL, it return the size of the local extra field

  if buf!=NULL, len is the size of the buffer, the extra header is copied in
    buf.
  the return value is the number of bytes copied in buf, or (if <0)
    the error code
*/
/*
  현재 파일에서 추가 필드 읽기 (unzOpenCurrentFile에 의해 열림)
  추가 필드의 로컬 헤더 버전입니다 (때로는
    중앙 헤더보다 로컬 헤더 버전에 더 많은 정보가 있음)
  buf == NULL의 경우, 로컬의 여분의 필드의 사이즈를 돌려 준다
  buf! = NULL의 경우, len는 버퍼의 사이즈, 여분의 헤더는 in
    buf.
  반환 값은 buf에 복사 된 바이트 수이거나 (0보다 작은 경우)
    오류 코드
*/

/***************************************************************************/

/* Get the current file offset */
/* 현재 파일 오프셋 가져 오기 */
extern uLong ZEXPORT unzGetOffset (unzFile file);

/* Set the current file offset */
/* 현재 파일 오프셋 설정 */
extern int ZEXPORT unzSetOffset (unzFile file, uLong pos);



#ifdef __cplusplus
}
#endif

#endif /* _unz_H */
