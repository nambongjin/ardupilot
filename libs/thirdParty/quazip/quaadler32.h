#ifndef QUAADLER32_H
#define QUAADLER32_H

#include <QByteArray>

#include "quachecksum32.h"

/// Adler32 checksum
/** \class QuaAdler32 quaadler32.h <quazip/quaadler32.h>
 * This class wrappers the adler32 function with the QuaChecksum32 interface.
 * See QuaChecksum32 for more info.
 */
// / Adler32 체크섬
/* * \ class QuaAdler32 quaadler32.h <quazip / quaadler32.h>
 *이 클래스는 QuadChecksum32 인터페이스로 adler32 함수를 래퍼합니다.
 * 자세한 정보는 QuaChecksum32를 참조하십시오.
 */
class QUAZIP_EXPORT QuaAdler32 : public QuaChecksum32
{

public:
	QuaAdler32();

	quint32 calculate(const QByteArray &data);

	void reset();
	void update(const QByteArray &buf);
	quint32 value();

private:
	quint32 checksum;
};

#endif //QUAADLER32_H
