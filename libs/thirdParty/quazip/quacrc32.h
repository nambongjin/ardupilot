#ifndef QUACRC32_H
#define QUACRC32_H

#include "quachecksum32.h"

///CRC32 checksum
/** \class QuaCrc32 quacrc32.h <quazip/quacrc32.h>
* This class wrappers the crc32 function with the QuaChecksum32 interface.
* See QuaChecksum32 for more info.
*/

/*

*이 클래스는 QuaChecksum32 인터페이스가있는 crc32 함수를 래퍼합니다.
* 자세한 정보는 QuaChecksum32를 참조하십시오.*/

class QUAZIP_EXPORT QuaCrc32 : public QuaChecksum32 {

public:
	QuaCrc32();

	quint32 calculate(const QByteArray &data);

	void reset();
	void update(const QByteArray &buf);
	quint32 value();

private:
	quint32 checksum;
};

#endif //QUACRC32_H
