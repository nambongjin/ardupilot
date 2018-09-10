#ifndef JLCOMPRESSFOLDER_H_
#define JLCOMPRESSFOLDER_H_

#include "quazip.h"
#include "quazipfile.h"
#include "quazipfileinfo.h"
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QFile>

/// Utility class for typical operations.
/**
  This class contains a number of useful static functions to perform
  simple operations, such as mass ZIP packing or extraction.
  */

/*
// 일반적인 작업을위한 유틸리티 클래스.
/ * *
  이 클래스에는 수행 할 수있는 유용한 정적 함수가 많이 포함되어 있습니다.
  질량 ZIP 포장 또는 추출과 같은 간단한 작업.
  * /
*/

class QUAZIP_EXPORT JlCompress {
private:
    /// Compress a single file.
    /**
      \param zip Opened zip to compress the file to.
      \param fileName The full path to the source file.
      \param fileDest The full name of the file inside the archive.
      \return true if success, false otherwise.
      */

/*
    // / 하나의 파일을 압축합니다.
    / * *
      \ param zip 파일을 압축 할 우편 번호를 열었습니다.
      \ param fileName 소스 파일의 전체 경로입니다.
      \ param fileDest 아카이브 내의 파일의 전체 이름입니다.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
      * /
*/

    static bool compressFile(QuaZip* zip, QString fileName, QString fileDest);
    /// Compress a subdirectory.
    /**
      \param parentZip Opened zip containing the parent directory.
      \param dir The full path to the directory to pack.
      \param parentDir The full path to the directory corresponding to
      the root of the ZIP.
      \param recursive Whether to pack sub-directories as well or only
      files.
      \return true if success, false otherwise.
      */

/*
    // / 하위 디렉토리를 압축합니다.
    / * *
      \ param parentZip 상위 디렉토리가 포함 된 zip을 엽니 다.
      \ param dir 압축 할 디렉토리의 전체 경로.
      \ param parentDir에 해당하는 디렉토리의 전체 경로
      우편 번호의 루트
      \ param recursive 하위 디렉토리를 압축할지 여부 만 지정합니다.
      파일.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
      * /
*/

    static bool compressSubDir(QuaZip* parentZip, QString dir, QString parentDir, bool recursive = true);
    /// Extract a single file.
    /**
      \param zip The opened zip archive to extract from.
      \param fileName The full name of the file to extract.
      \param fileDest The full path to the destination file.
      \return true if success, false otherwise.
      */

/*
    // / 단일 파일을 추출합니다.
    / * *
      \ param zip 추출 할 Zip 압축 파일을 엽니 다.
      \ param fileName 추출 할 파일의 전체 이름입니다.
      \ param fileDest 대상 파일의 전체 경로입니다.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
      * /
*/

    static bool extractFile(QuaZip* zip, QString fileName, QString fileDest);
    /// Remove some files.
    /**
      \param listFile The list of files to remove.
      \return true if success, false otherwise.
      */

/*
    / / 일부 파일을 제거하십시오.
    / * *
      \ param listFile 제거 할 파일 목록.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
      * /
*/

    static bool removeFile(QStringList listFile);

public:
    /// Compress a single file.
    /**
      \param fileCompressed The name of the archive.
      \param file The file to compress.
      \return true if success, false otherwise.
      */

/*

      \ param fileCompressed 아카이브의 이름입니다.
      \ param file 압축 할 파일.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
*/

    static bool compressFile(QString fileCompressed, QString file);
    /// Compress a list of files.
    /**
      \param fileCompressed The name of the archive.
      \param files The file list to compress.
      \return true if success, false otherwise.
      */

/*
      \ param fileCompressed 아카이브의 이름입니다.
      \ param 파일 압축 할 파일 목록입니다.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
*/

    static bool compressFiles(QString fileCompressed, QStringList files);
    /// Compress a whole directory.
    /**
      \param fileCompressed The name of the archive.
      \param dir The directory to compress.
      \param recursive Whether to pack the subdirectories as well, or
      just regular files.
      \return true if success, false otherwise.
      */

/*
      \ param fileCompressed 아카이브의 이름입니다.
      \ param dir 압축 할 디렉토리입니다.
      \ param recursive 하위 디렉토리를 압축할지 여부 또는
      그냥 정규 파일.
      \ 성공하면 true를 반환하고 그렇지 않으면 false를 반환합니다.
*/

    static bool compressDir(QString fileCompressed, QString dir = QString(), bool recursive = true);

public:
    /// Extract a single file.
    /**
      \param fileCompressed The name of the archive.
      \param fileName The file to extract.
      \param fileDest The destination file, assumed to be identical to
      \a file if left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */

/*
      \ param fileCompressed 아카이브의 이름입니다.
      \ param fileName 추출 할 파일입니다.
      \ param fileDest 대상 파일은 다음과 같을 것으로 가정합니다.
      \ 공백으로두면 파일.
      \ return 추출 된 파일의 전체 경로 목록. 실패시 비어 있습니다.
*/

    static QString extractFile(QString fileCompressed, QString fileName, QString fileDest = QString());
    /// Extract a list of files.
    /**
      \param fileCompressed The name of the archive.
      \param files The file list to extract.
      \param dir The directory to put the files to, the current
      directory if left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */

/*
      \ param fileCompressed 아카이브의 이름입니다.
      \ param files 추출 할 파일 목록입니다.
      \ param dir 파일을 저장할 디렉토리, 현재 파일
      디렉토리가 비어있는 경우.
      \ return 추출 된 파일의 전체 경로 목록. 실패시 비어 있습니다.
*/

    static QStringList extractFiles(QString fileCompressed, QStringList files, QString dir = QString());
    /// Extract a whole archive.
    /**
      \param fileCompressed The name of the archive.
      \param dir The directory to extract to, the current directory if
      left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */

/*
      \ param fileCompressed 아카이브의 이름입니다.
      \ param dir 추출 할 디렉토리, 현재 디렉토리 if
      왼쪽 비어 있습니다.
      \ return 추출 된 파일의 전체 경로 목록. 실패시 비어 있습니다.
*/

    static QStringList extractDir(QString fileCompressed, QString dir = QString());
    /// Get the file list.	파일 목록을 가져옵니다.
    /**
      \return The list of the files in the archive, or, more precisely, the
      list of the entries, including both files and directories if they
      are present separately.
      */

/*
      \ return 아카이브의 파일 목록 또는 더 정확하게는
      파일 및 디렉토리를 포함한 항목 목록
      별도로 존재합니다.
*/

    static QStringList getFileList(QString fileCompressed);
};

#endif /* JLCOMPRESSFOLDER_H_ */
