#ifndef QUACHECKSUM32_H
#define QUACHECKSUM32_H

#include <QByteArray>
#include "quazip_global.h"

/// Checksum interface.
/** \class QuaChecksum32 quachecksum32.h <quazip/quachecksum32.h>
 * This is an interface for 32 bit checksums.
 * Classes implementing this interface can calcunate a certin
 * checksum in a single step:
 * \code
 * QChecksum32 *crc32 = new QuaCrc32(); 
 * rasoult = crc32->calculate(data);
 * \endcode
 * or by streaming the data:
 * \code
 * QChecksum32 *crc32 = new QuaCrc32(); 
 * while(!fileA.atEnd())
 *     crc32->update(fileA.read(bufSize));
 * resoultA = crc32->value();
 * crc32->reset();
 * while(!fileB.atEnd())
 *     crc32->update(fileB.read(bufSize));
 * resoultB = crc32->value();
 * \endcode
 */
// / Checksum 인터페이스.
/** \ class QuaChecksum32 quachecksum32.h <quazip / quachecksum32.h>
 * 이것은 32 비트 체크섬을위한 인터페이스입니다.
 이 인터페이스를 구현하는 클래스는, 증명서를 계산할 수 있습니다.
 하나의 단계에서 * 체크섬 :
 * \ code
 * QChecksum32 * crc32 = 새로운 QuaCrc32 (); 
 * rasoult = crc32 -> calculate (데이터);
 * \ endcode
 * 또는 데이터 스트리밍 :
 * \ code
 * QChecksum32 * crc32 = 새로운 QuaCrc32 (); 
 * while (! fileA.atEnd ())
 * crc32 -> 업데이트 (fileA.read (bufSize));
 * resoultA = crc32-> value ();
 * crc32-> reset ();
 * while (! fileB.atEnd ())
 * crc32-> update (fileB.read (bufSize));
 * resoultB = crc32-> value ();
 * \ endcode
 */
class QUAZIP_EXPORT QuaChecksum32
{

public:
	///Calculates the checksum for data.
	/** \a data source data
	 * \return data checksum
	 *
	 * This function has no efect on the value returned by value().
	 */
        /// 데이터의 체크섬을 계산합니다.
	/* * \ a 데이터 소스 데이터
	 * \ return 데이터 체크섬
	 *
	 *이 함수는 value ()가 반환 한 값에 영향을주지 않습니다.
	 */

	virtual quint32 calculate(const QByteArray &data) = 0;

	///Resets the calculation on a checksun for a stream.
        /// 스트림의 체크섬에 대한 계산을 다시 설정합니다.
	virtual void reset() = 0;

	///Updates the calculated checksum for the stream
	/** \a buf next portion of data from the stream
	 */
        /// 스트림에 대해 계산 된 체크섬을 업데이트합니다.
	/* * \ buf 스트림의 다음 데이터 부분
	 */
	virtual void update(const QByteArray &buf) = 0;

	///Value of the checksum calculated for the stream passed throw update().
	/** \return checksum
	 */
        // 전달 된 스트림에 대해 계산 된 체크섬 값입니다. update ()를 throw합니다.
	/* * \ 리턴 체크섬
	 */
	virtual quint32 value() = 0;
};

#endif //QUACHECKSUM32_H
