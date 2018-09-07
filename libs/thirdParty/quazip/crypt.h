/* crypt.h -- base code for crypt/uncrypt ZIPfile


   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   This code is a modified version of crypting code in Infozip distribution

   The encryption/decryption parts of this source code (as opposed to the
   non-echoing password parts) were originally written in Europe.  The
   whole source package can be freely distributed, including from the USA.
   (Prior to January 2000, re-export from the US was a violation of US law.)

   This encryption code is a direct transcription of the algorithm from
   Roger Schlafly, described by Phil Katz in the file appnote.txt.  This
   file (appnote.txt) is distributed with the PKZIP program (even in the
   version without encryption capabilities).

   If you don't need crypting in your application, just define symbols
   NOCRYPT and NOUNCRYPT.

   This code support the "Traditional PKWARE Encryption".

   The new AES encryption added on Zip format by Winzip (see the page
   http://www.winzip.com/aes_info.htm ) and PKWare PKZip 5.x Strong
   Encryption is not supported.
*/

#include "quazip_global.h"

#define CRC32(c, b) ((*(pcrc_32_tab+(((int)(c) ^ (b)) & 0xff))) ^ ((c) >> 8))

/***********************************************************************
 * Return the next byte in the pseudo-random sequence
 */
/* ************************************************ ***********************
 * 의사 랜덤 시퀀스에서 다음 바이트를 반환합니다.
 */
static int decrypt_byte(unsigned long* pkeys, const unsigned long* pcrc_32_tab UNUSED)
{
    //(void) pcrc_32_tab; /* avoid "unused parameter" warning */
    unsigned temp;  /* POTENTIAL BUG:  temp*(temp^1) may overflow in an
                     * unpredictable manner on 16-bit systems; not a problem
                     * with any known compiler so far, though */

    temp = ((unsigned)(*(pkeys+2)) & 0xffff) | 2;
    return (int)(((temp * (temp ^ 1)) >> 8) & 0xff);
}

/***********************************************************************
 * Update the encryption keys with the next byte of plain text
 */
/* ************************************************ ***********************
 * 일반 텍스트의 다음 바이트로 암호화 키 업데이트
 */
static int update_keys(unsigned long* pkeys,const unsigned long* pcrc_32_tab,int c)
{
    (*(pkeys+0)) = CRC32((*(pkeys+0)), c);
    (*(pkeys+1)) += (*(pkeys+0)) & 0xff;
    (*(pkeys+1)) = (*(pkeys+1)) * 134775813L + 1;
    {
      register int keyshift = (int)((*(pkeys+1)) >> 24);
      (*(pkeys+2)) = CRC32((*(pkeys+2)), keyshift);
    }
    return c;
}


/***********************************************************************
 * Initialize the encryption keys and the random header according to
 * the given password.
 */
/* ************************************************ ***********************
 *에 따라 암호화 키 및 임의 헤더를 초기화하십시오.
 * 주어진 패스워드.
 */
static void init_keys(const char* passwd,unsigned long* pkeys,const unsigned long* pcrc_32_tab)
{
    *(pkeys+0) = 305419896L;
    *(pkeys+1) = 591751049L;
    *(pkeys+2) = 878082192L;
    while (*passwd != '\0') {
        update_keys(pkeys,pcrc_32_tab,(int)*passwd);
        passwd++;
    }
}

#define zdecode(pkeys,pcrc_32_tab,c) \
    (update_keys(pkeys,pcrc_32_tab,c ^= decrypt_byte(pkeys,pcrc_32_tab)))

#define zencode(pkeys,pcrc_32_tab,c,t) \
    (t=decrypt_byte(pkeys,pcrc_32_tab), update_keys(pkeys,pcrc_32_tab,c), t^(c))

#ifdef INCLUDECRYPTINGCODE_IFCRYPTALLOWED

#define RAND_HEAD_LEN  12
   /* "last resort" source for second part of crypt seed pattern */
   /* 암호 시드 패턴의 두 번째 부분에 대한 "최후의 수단"소스 */
#  ifndef ZCR_SEED2
#    define ZCR_SEED2 3141592654UL     /* use PI as default pattern *//* PI를 기본 패턴으로 사용 */
#  endif

static int crypthead(passwd, buf, bufSize, pkeys, pcrc_32_tab, crcForCrypting)
    const char *passwd;         /* password string *//* 암호 문자열 */
    unsigned char *buf;         /* where to write header *//* 헤더를 쓸 곳 */
    int bufSize;
    unsigned long* pkeys;
    const unsigned long* pcrc_32_tab;
    unsigned long crcForCrypting;
{
    int n;                       /* index in random header *//* 임의의 헤더의 인덱스 */
    int t;                       /* temporary *//* 임시 */
    int c;                       /* random byte *//* 랜덤 바이트 */
    unsigned char header[RAND_HEAD_LEN-2]; /* random header *//* 임의의 헤더 */
    static unsigned calls = 0;   /* ensure different random header each time *//* 매번 다른 임의의 헤더를 보장 */

    if (bufSize<RAND_HEAD_LEN)
      return 0;

    /* First generate RAND_HEAD_LEN-2 random bytes. We encrypt the
     * output of rand() to get less predictability, since rand() is
     * often poorly implemented.
     */
    /* 먼저 RAND_HEAD_LEN-2 랜덤 바이트를 생성합니다. 우리는
     * rand ()의 출력은 예측 가능성이 낮습니다. 왜냐하면 rand ()가
     * 종종 제대로 구현되지 않았습니다.
     */
    if (++calls == 1)
    {
        srand((unsigned)(time(NULL) ^ ZCR_SEED2));
    }
    init_keys(passwd, pkeys, pcrc_32_tab);
    for (n = 0; n < RAND_HEAD_LEN-2; n++)
    {
        c = (rand() >> 7) & 0xff;
        header[n] = (unsigned char)zencode(pkeys, pcrc_32_tab, c, t);
    }
    /* Encrypt random header (last two bytes is high word of crc) */
    /* 임의의 헤더 암호화 (마지막 2 바이트는 crc의 상위 워드) */
    init_keys(passwd, pkeys, pcrc_32_tab);
    for (n = 0; n < RAND_HEAD_LEN-2; n++)
    {
        buf[n] = (unsigned char)zencode(pkeys, pcrc_32_tab, header[n], t);
    }
    buf[n++] = zencode(pkeys, pcrc_32_tab, (int)(crcForCrypting >> 16) & 0xff, t);
    buf[n++] = zencode(pkeys, pcrc_32_tab, (int)(crcForCrypting >> 24) & 0xff, t);
    return n;
}

#endif
