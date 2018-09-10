#ifndef LOGDATA_H
#define LOGDATA_H

#include <QHash>

/**
 * @brief The FormatLine struct describes an FMT line appearing in a dataflash log.
 *  Field names, type and length are retrieved from the line in case something
 * needs it.
 */

/*
 * @brief FormatLine 구조체는 데이터 플래쉬 로그에 나타나는 FMT 행을 설명합니다.
 * 필드 이름, 유형 및 길이는 행에서 검색됩니다.
 * 필요합니다.
*/

struct FormatLine {
    unsigned int type;
    unsigned int length;
    QString format;
    QString name;
    QStringList fields;

    bool hasData() {
        return (type > 0 && !name.isEmpty());
    }

    /**
     * @brief from initializes a FormatLine from a line of text.
     */

/*
     * @brief from은 텍스트 행에서 FormatLine을 초기화합니다.
*/

    static FormatLine from(QString& line);
};

/**
 * @brief The DataLine struct contains a hashtable of the values found in a line.
 * Before using it, you need a FormatLine for the type of line you're going to
 * read. Given that, call the readFields(FormatLine&, QString&) function to populate
 * the hashtable with the values in the line.
 */

/*
 * @brief DataLine 구조체는 한 행에있는 값의 해시 테이블을 포함합니다.
 * 사용하기 전에가는 행 유형에 대한 FormatLine이 필요합니다.
* 읽습니다. 이 경우 readFields (FormatLine & QString &) 함수를 호출하여 데이터를 채 웁니다.
 행의 값을 가지는 해시 테이블
*/

struct DataLine {
    QHash<QString, QString> values;

    virtual bool hasData() = 0;

protected:
    void readFields(FormatLine& format, QString& line);
};


#endif // LOGDATA_H
