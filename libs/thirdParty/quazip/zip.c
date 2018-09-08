/* zip.c -- IO on .zip files using zlib
   Version 1.01e, February 12th, 2005

   27 Dec 2004 Rolf Kalbermatter
   Modification to zipOpen2 to support globalComment retrieval.

   Copyright (C) 1998-2005 Gilles Vollant

   Read zip.h for more info

   Modified by Sergey A. Tachenov to integrate with Qt.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "zip.h"
#include "quazip_global.h"

#ifdef STDC
#  include <stddef.h>
#  include <string.h>
#  include <stdlib.h>
#endif
#ifdef NO_ERRNO_H
    extern int errno;
#else
#   include <errno.h>
#endif


#ifndef local
#  define local static
#endif
/* compile with -Dlocal if your debugger can't find static symbols 	/ * 디버거가 정적 기호를 찾을 수없는 경우 -Dlocal로 컴파일하십시오 * /*/

#ifndef VERSIONMADEBY
# define VERSIONMADEBY   (0x031e) /* best for standard pkware crypt 	/ * 표준 pkware 암호문에 가장 적합 * /*/
#endif

#ifndef Z_BUFSIZE
#define Z_BUFSIZE (16384)
#endif

#ifndef Z_MAXFILENAMEINZIP
#define Z_MAXFILENAMEINZIP (256)
#endif

#ifndef ALLOC
# define ALLOC(size) (malloc(size))
#endif
#ifndef TRYFREE
# define TRYFREE(p) {if (p) free(p);}
#endif

/*
#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)
*/

/* I've found an old Unix (a SunOS 4.1.3_U1) without all SEEK_* defined....	/ * 나는 모든 SEEK_ *가 정의되지 않은 오래된 Unix (SunOS 4.1.3_U1)를 발견했다. * / */

#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif

#ifndef DEF_MEM_LEVEL
#if MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#else
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#endif
#endif
const char zip_copyright[] =
   " zip 1.01 Copyright 1998-2004 Gilles Vollant - http://www.winimage.com/zLibDll";


#define SIZEDATA_INDATABLOCK (4096-(4*4))

#define LOCALHEADERMAGIC    (0x04034b50)
#define DESCRIPTORHEADERMAGIC    (0x08074b50)
#define CENTRALHEADERMAGIC  (0x02014b50)
#define ENDHEADERMAGIC      (0x06054b50)

#define FLAG_LOCALHEADER_OFFSET (0x06)
#define CRC_LOCALHEADER_OFFSET  (0x0e)

#define SIZECENTRALHEADER (0x2e) /* 46 */

typedef struct linkedlist_datablock_internal_s
{
  struct linkedlist_datablock_internal_s* next_datablock;
  uLong  avail_in_this_block;
  uLong  filled_in_this_block;
  uLong  unused; /* for future use and alignement */
  unsigned char data[SIZEDATA_INDATABLOCK];
} linkedlist_datablock_internal;

typedef struct linkedlist_data_s
{
    linkedlist_datablock_internal* first_block;
    linkedlist_datablock_internal* last_block;
} linkedlist_data;


typedef struct
{
    z_stream stream;            /* zLib stream structure for inflate 	/ * zLib inflate를위한 스트림 구조 * /*/
    int  stream_initialised;    /* 1 is stream is initialised 	/ * 1은 스트림이 초기화 됨 * /*/
    uInt pos_in_buffered_data;  /* last written byte in buffered_data 	/ * buffered_data에 마지막으로 기록 된 바이트 * /*/

    uLong pos_local_header;     /* offset of the local header of the file 	파일의 로컬 헤더의 오프셋
                                     currenty writing 	현재 쓰기*/

    char* central_header;       /* central header data for the current file 	/ * 현재 파일의 중앙 헤더 데이터 * /*/
    uLong size_centralheader;   /* size of the central header for cur file 	/ * cur 파일의 중앙 헤더 크기 * /*/
    uLong flag;                 /* flag of the file currently writing 	/ * 현재 쓰고있는 파일의 플래그 * /*/

    int  method;                /* compression method of file currenty wr.	/ * 현재 파일의 압축 방법. * /*/
    int  raw;                   /* 1 for directly writing raw data 	/ * 원시 데이터 직접 쓰기를위한 * 1 * /*/
    Byte buffered_data[Z_BUFSIZE];/* buffer contain compressed data to be writ	/ * 버퍼에는 압축 된 데이터가 저장됩니다. * /*/
    uLong dosDate;
    uLong crc32;
    int  encrypt;
#ifndef NOCRYPT
    unsigned long keys[3];     /* keys defining the pseudo-random sequence 	/ * 의사 랜덤 시퀀스를 정의하는 키 * /*/
    const unsigned long* pcrc_32_tab;
    int crypt_header_size;
#endif
} curfile_info;

typedef struct
{
    zlib_filefunc_def z_filefunc;
    voidpf filestream;        /* io structore of the zipfile 	/ * zip 파일의 구조체 * /*/
    linkedlist_data central_dir;/* datablock with central dir in construction	/ * 건설중인 중앙 디렉토리가있는 데이터 블록 * /*/
    int  in_opened_file_inzip;  /* 1 if a file in the zip is currently writ.	/ * zip 파일이 현재 작성된 경우 1입니다. * /*/
    curfile_info ci;            /* info on the file curretly writing 	/ * curretly write 파일에 대한 정보 * /*/

    uLong begin_pos;            /* position of the beginning of the zipfile 	/ * zip 파일의 시작 위치 * /*/
    uLong add_position_when_writting_offset;
    uLong number_entry;
#ifndef NO_ADDFILEINEXISTINGZIP
    char *globalcomment;
#endif
    unsigned flags;
} zip_internal;



#ifndef NOCRYPT
#define INCLUDECRYPTINGCODE_IFCRYPTALLOWED
#include "crypt.h"
#endif

local linkedlist_datablock_internal* allocate_new_datablock()
{
    linkedlist_datablock_internal* ldi;
    ldi = (linkedlist_datablock_internal*)
                 ALLOC(sizeof(linkedlist_datablock_internal));
    if (ldi!=NULL)
    {
        ldi->next_datablock = NULL ;
        ldi->filled_in_this_block = 0 ;
        ldi->avail_in_this_block = SIZEDATA_INDATABLOCK ;
    }
    return ldi;
}

local void free_datablock(ldi)
    linkedlist_datablock_internal* ldi;
{
    while (ldi!=NULL)
    {
        linkedlist_datablock_internal* ldinext = ldi->next_datablock;
        TRYFREE(ldi);
        ldi = ldinext;
    }
}

local void init_linkedlist(ll)
    linkedlist_data* ll;
{
    ll->first_block = ll->last_block = NULL;
}

#if 0 // unused
local void free_linkedlist(ll)
    linkedlist_data* ll;
{
    free_datablock(ll->first_block);
    ll->first_block = ll->last_block = NULL;
}
#endif

local int add_data_in_datablock(ll,buf,len)
    linkedlist_data* ll;
    const void* buf;
    uLong len;
{
    linkedlist_datablock_internal* ldi;
    const unsigned char* from_copy;

    if (ll==NULL)
        return ZIP_INTERNALERROR;

    if (ll->last_block == NULL)
    {
        ll->first_block = ll->last_block = allocate_new_datablock();
        if (ll->first_block == NULL)
            return ZIP_INTERNALERROR;
    }

    ldi = ll->last_block;
    from_copy = (unsigned char*)buf;

    while (len>0)
    {
        uInt copy_this;
        uInt i;
        unsigned char* to_copy;

        if (ldi->avail_in_this_block==0)
        {
            ldi->next_datablock = allocate_new_datablock();
            if (ldi->next_datablock == NULL)
                return ZIP_INTERNALERROR;
            ldi = ldi->next_datablock ;
            ll->last_block = ldi;
        }

        if (ldi->avail_in_this_block < len)
            copy_this = (uInt)ldi->avail_in_this_block;
        else
            copy_this = (uInt)len;

        to_copy = &(ldi->data[ldi->filled_in_this_block]);

        for (i=0;i<copy_this;i++)
            *(to_copy+i)=*(from_copy+i);

        ldi->filled_in_this_block += copy_this;
        ldi->avail_in_this_block -= copy_this;
        from_copy += copy_this ;
        len -= copy_this;
    }
    return ZIP_OK;
}



/****************************************************************************/

#ifndef NO_ADDFILEINEXISTINGZIP
/* ===========================================================================
   Inputs a long in LSB order to the given file
   nbByte == 1, 2 or 4 (byte, short or long)
*/

/*
/ * ====================================== ===============
   주어진 파일에 LSB 순서로 long을 입력합니다.
   nbByte == 1, 2 또는 4 (바이트, 길이 또는 길이)
* /
*/

local int ziplocal_putValue OF((const zlib_filefunc_def* pzlib_filefunc_def,
                                voidpf filestream, uLong x, int nbByte));
local int ziplocal_putValue (pzlib_filefunc_def, filestream, x, nbByte)
    const zlib_filefunc_def* pzlib_filefunc_def;
    voidpf filestream;
    uLong x;
    int nbByte;
{
    unsigned char buf[4];
    int n;
    for (n = 0; n < nbByte; n++)
    {
        buf[n] = (unsigned char)(x & 0xff);
        x >>= 8;
    }
    if (x != 0)
      {     /* data overflow - hack for ZIP64 (X Roche) 	/ * 데이터 오버플로 - ZIP64 용 해킹 (X Roche) * /*/
      for (n = 0; n < nbByte; n++)
        {
          buf[n] = 0xff;
        }
      }

    if (ZWRITE(*pzlib_filefunc_def,filestream,buf,nbByte)!=(uLong)nbByte)
        return ZIP_ERRNO;
    else
        return ZIP_OK;
}

local void ziplocal_putValue_inmemory OF((void* dest, uLong x, int nbByte));
local void ziplocal_putValue_inmemory (dest, x, nbByte)
    void* dest;
    uLong x;
    int nbByte;
{
    unsigned char* buf=(unsigned char*)dest;
    int n;
    for (n = 0; n < nbByte; n++) {
        buf[n] = (unsigned char)(x & 0xff);
        x >>= 8;
    }

    if (x != 0)
    {     /* data overflow - hack for ZIP64 */
       for (n = 0; n < nbByte; n++)
       {
          buf[n] = 0xff;
       }
    }
}

/****************************************************************************/


local uLong ziplocal_TmzDateToDosDate(ptm,dosDate)
    const tm_zip* ptm;
    uLong dosDate UNUSED;
{
    uLong year = (uLong)ptm->tm_year;
    if (year>1980)
        year-=1980;
    else if (year>80)
        year-=80;
    return
      (uLong) (((ptm->tm_mday) + (32 * (ptm->tm_mon+1)) + (512 * year)) << 16) |
        ((ptm->tm_sec/2) + (32* ptm->tm_min) + (2048 * (uLong)ptm->tm_hour));
}


/****************************************************************************/

local int ziplocal_getByte OF((
    const zlib_filefunc_def* pzlib_filefunc_def,
    voidpf filestream,
    int *pi));

local int ziplocal_getByte(pzlib_filefunc_def,filestream,pi)
    const zlib_filefunc_def* pzlib_filefunc_def;
    voidpf filestream;
    int *pi;
{
    unsigned char c;
    int err = (int)ZREAD(*pzlib_filefunc_def,filestream,&c,1);
    if (err==1)
    {
        *pi = (int)c;
        return ZIP_OK;
    }
    else
    {
        if (ZERROR(*pzlib_filefunc_def,filestream))
            return ZIP_ERRNO;
        else
            return ZIP_EOF;
    }
}


/* ===========================================================================
   Reads a long in LSB order from the given gz_stream. Sets
*/

/*
/ * ====================================== ===============
   주어진 gz_stream에서 LSB 순서로 long을 읽습니다. 세트
* /
*/

local int ziplocal_getShort OF((
    const zlib_filefunc_def* pzlib_filefunc_def,
    voidpf filestream,
    uLong *pX));

local int ziplocal_getShort (pzlib_filefunc_def,filestream,pX)
    const zlib_filefunc_def* pzlib_filefunc_def;
    voidpf filestream;
    uLong *pX;
{
    uLong x ;
    int i;
    int err;

    err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
    x = (uLong)i;

    if (err==ZIP_OK)
        err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
    x += ((uLong)i)<<8;

    if (err==ZIP_OK)
        *pX = x;
    else
        *pX = 0;
    return err;
}

local int ziplocal_getLong OF((
    const zlib_filefunc_def* pzlib_filefunc_def,
    voidpf filestream,
    uLong *pX));

local int ziplocal_getLong (pzlib_filefunc_def,filestream,pX)
    const zlib_filefunc_def* pzlib_filefunc_def;
    voidpf filestream;
    uLong *pX;
{
    uLong x ;
    int i;
    int err;

    err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
    x = (uLong)i;

    if (err==ZIP_OK)
        err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
    x += ((uLong)i)<<8;

    if (err==ZIP_OK)
        err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
    x += ((uLong)i)<<16;

    if (err==ZIP_OK)
        err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
    x += ((uLong)i)<<24;

    if (err==ZIP_OK)
        *pX = x;
    else
        *pX = 0;
    return err;
}

#ifndef BUFREADCOMMENT
#define BUFREADCOMMENT (0x400)
#endif
/*
  Locate the Central directory of a zipfile (at the end, just before
    the global comment)
*/

/*
/ *
  zip 파일의 중앙 디렉토리를 찾으십시오 (끝에, 바로 앞에
    글로벌 코멘트)
* /
*/

local uLong ziplocal_SearchCentralDir OF((
    const zlib_filefunc_def* pzlib_filefunc_def,
    voidpf filestream));

local uLong ziplocal_SearchCentralDir(pzlib_filefunc_def,filestream)
    const zlib_filefunc_def* pzlib_filefunc_def;
    voidpf filestream;
{
    unsigned char* buf;
    uLong uSizeFile;
    uLong uBackRead;
    uLong uMaxBack=0xffff; /* maximum size of global comment	/ * 전체 주석의 최대 크기 * / */
    uLong uPosFound=0;

    if (ZSEEK(*pzlib_filefunc_def,filestream,0,ZLIB_FILEFUNC_SEEK_END) != 0)
        return 0;


    uSizeFile = ZTELL(*pzlib_filefunc_def,filestream);

    if (uMaxBack>uSizeFile)
        uMaxBack = uSizeFile;

    buf = (unsigned char*)ALLOC(BUFREADCOMMENT+4);
    if (buf==NULL)
        return 0;

    uBackRead = 4;
    while (uBackRead<uMaxBack)
    {
        uLong uReadSize,uReadPos ;
        int i;
        if (uBackRead+BUFREADCOMMENT>uMaxBack)
            uBackRead = uMaxBack;
        else
            uBackRead+=BUFREADCOMMENT;
        uReadPos = uSizeFile-uBackRead ;

        uReadSize = ((BUFREADCOMMENT+4) < (uSizeFile-uReadPos)) ?
                     (BUFREADCOMMENT+4) : (uSizeFile-uReadPos);
        if (ZSEEK(*pzlib_filefunc_def,filestream,uReadPos,ZLIB_FILEFUNC_SEEK_SET)!=0)
            break;

        if (ZREAD(*pzlib_filefunc_def,filestream,buf,uReadSize)!=uReadSize)
            break;

        for (i=(int)uReadSize-3; (i--)>0;)
            if (((*(buf+i))==0x50) && ((*(buf+i+1))==0x4b) &&
                ((*(buf+i+2))==0x05) && ((*(buf+i+3))==0x06))
            {
                uPosFound = uReadPos+i;
                break;
            }

        if (uPosFound!=0)
            break;
    }
    TRYFREE(buf);
    return uPosFound;
}
#endif /* !NO_ADDFILEINEXISTINGZIP	*/

/************************************************************/
extern zipFile ZEXPORT zipOpen2 (file, append, globalcomment, pzlib_filefunc_def)
    voidpf file;
    int append;
    zipcharpc* globalcomment;
    zlib_filefunc_def* pzlib_filefunc_def;
{
    zip_internal ziinit;
    zip_internal* zi;
    int err=ZIP_OK;


    if (pzlib_filefunc_def==NULL)
        fill_qiodevice_filefunc(&ziinit.z_filefunc);
    else
        ziinit.z_filefunc = *pzlib_filefunc_def;

    ziinit.filestream = (*(ziinit.z_filefunc.zopen_file))
                 (ziinit.z_filefunc.opaque,
                  file,
                  (append == APPEND_STATUS_CREATE) ?
                  (ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_WRITE | ZLIB_FILEFUNC_MODE_CREATE) :
                    (ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_WRITE | ZLIB_FILEFUNC_MODE_EXISTING));

    if (ziinit.filestream == NULL)
        return NULL;
    ziinit.begin_pos = ZTELL(ziinit.z_filefunc,ziinit.filestream);
    ziinit.in_opened_file_inzip = 0;
    ziinit.ci.stream_initialised = 0;
    ziinit.number_entry = 0;
    ziinit.add_position_when_writting_offset = 0;
    ziinit.flags = ZIP_WRITE_DATA_DESCRIPTOR;
    init_linkedlist(&(ziinit.central_dir));


    zi = (zip_internal*)ALLOC(sizeof(zip_internal));
    if (zi==NULL)
    {
        ZCLOSE(ziinit.z_filefunc,ziinit.filestream);
        return NULL;
    }

    /* now we add file in a zipfile	  이제 파일을 zip 파일에 추가합니다. */
#    ifndef NO_ADDFILEINEXISTINGZIP
    ziinit.globalcomment = NULL;
    if (append == APPEND_STATUS_ADDINZIP)
    {
        uLong byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)	 / * 중앙 디렉토리 크기   * /*/

        uLong size_central_dir;     /* size of the central directory  	/ * 중앙 디렉토리 시작 오프셋 * /*/
        uLong offset_central_dir;   /* offset of start of central directory */
        uLong central_pos,uL;

        uLong number_disk;          /* number of the current dist, used for		
                                    spaning ZIP, unsupported, always 0*/

/*
 				    / * 현재 dist의 번호.
                                    스팬 ZIP, 지원되지 않음, 항상 0 * /
*/

        uLong number_disk_with_CD;  /* number the the disk with central dir, used
                                    for spaning ZIP, unsupported, always 0*/

/*
/				    * 사용 된 중앙 디렉토리가있는 디스크의 번호를 지정합니다.
                                    ZIP 스팬 용, 지원되지 않음, 항상 0 * /
*/

        uLong number_entry;
        uLong number_entry_CD;      /* total number of entries in
                                    the central dir
                                    (same than number_entry on nospan) */

/*
/ 				    * 총 항목 수
                                    중심 방향
                                    (nospan의 number_entry와 동일) * /
*/

        uLong size_comment;

        central_pos = ziplocal_SearchCentralDir(&ziinit.z_filefunc,ziinit.filestream);
        if (central_pos==0)
            err=ZIP_ERRNO;

        if (ZSEEK(ziinit.z_filefunc, ziinit.filestream,
                                        central_pos,ZLIB_FILEFUNC_SEEK_SET)!=0)
            err=ZIP_ERRNO;

        /* the signature, already checked	/ * 이미 체크 된 서명 * / */
        if (ziplocal_getLong(&ziinit.z_filefunc, ziinit.filestream,&uL)!=ZIP_OK)
            err=ZIP_ERRNO;

        /* number of this disk 	 / * 이 디스크의 번호 * /*/
        if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_disk)!=ZIP_OK)
            err=ZIP_ERRNO;

        /* number of the disk with the start of the central directory 	 / * 중앙 디렉토리 시작과 함께 디스크 번호 * /*/
        if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_disk_with_CD)!=ZIP_OK)
            err=ZIP_ERRNO;

        /* total number of entries in the central dir on this disk 	/ * 이 디스크의 중앙 디렉토리에있는 총 항목 수 * /*/
        if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_entry)!=ZIP_OK)
            err=ZIP_ERRNO;

        /* total number of entries in the central dir 	/ * 중앙 디렉토리의 총 항목 수 * /*/
        if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_entry_CD)!=ZIP_OK)
            err=ZIP_ERRNO;

        if ((number_entry_CD!=number_entry) ||
            (number_disk_with_CD!=0) ||
            (number_disk!=0))
            err=ZIP_BADZIPFILE;

        /* size of the central directory 	/ * 중앙 디렉토리 크기 * /*/
        if (ziplocal_getLong(&ziinit.z_filefunc, ziinit.filestream,&size_central_dir)!=ZIP_OK)
            err=ZIP_ERRNO;

        /* offset of start of central directory with respect to the
            starting disk number */

/*
        / * 해당 디렉토리에 대한 중앙 디렉토리의 시작 오프셋
            디스크 번호 시작 * /
*/

        if (ziplocal_getLong(&ziinit.z_filefunc, ziinit.filestream,&offset_central_dir)!=ZIP_OK)
            err=ZIP_ERRNO;

        /* zipfile global comment length 	/ * zipfile 전역 주석 길이 * /*/
        if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&size_comment)!=ZIP_OK)
            err=ZIP_ERRNO;

        if ((central_pos<offset_central_dir+size_central_dir) &&
            (err==ZIP_OK))
            err=ZIP_BADZIPFILE;

        if (err!=ZIP_OK)
        {
            ZCLOSE(ziinit.z_filefunc, ziinit.filestream);
            TRYFREE(zi);
            return NULL;
        }

        if (size_comment>0)
        {
            ziinit.globalcomment = ALLOC(size_comment+1);
            if (ziinit.globalcomment)
            {
               size_comment = ZREAD(ziinit.z_filefunc, ziinit.filestream,ziinit.globalcomment,size_comment);
               ziinit.globalcomment[size_comment]=0;
            }
        }

        byte_before_the_zipfile = central_pos -
                                (offset_central_dir+size_central_dir);
        ziinit.add_position_when_writting_offset = byte_before_the_zipfile;

        {
            uLong size_central_dir_to_read = size_central_dir;
            size_t buf_size = SIZEDATA_INDATABLOCK;
            void* buf_read = (void*)ALLOC(buf_size);
            if (ZSEEK(ziinit.z_filefunc, ziinit.filestream,
                  offset_central_dir + byte_before_the_zipfile,
                  ZLIB_FILEFUNC_SEEK_SET) != 0)
                  err=ZIP_ERRNO;

            while ((size_central_dir_to_read>0) && (err==ZIP_OK))
            {
                uLong read_this = SIZEDATA_INDATABLOCK;
                if (read_this > size_central_dir_to_read)
                    read_this = size_central_dir_to_read;
                if (ZREAD(ziinit.z_filefunc, ziinit.filestream,buf_read,read_this) != read_this)
                    err=ZIP_ERRNO;

                if (err==ZIP_OK)
                    err = add_data_in_datablock(&ziinit.central_dir,buf_read,
                                                (uLong)read_this);
                size_central_dir_to_read-=read_this;
            }
            TRYFREE(buf_read);
        }
        ziinit.begin_pos = byte_before_the_zipfile;
        ziinit.number_entry = number_entry_CD;

        if (ZSEEK(ziinit.z_filefunc, ziinit.filestream,
                  offset_central_dir+byte_before_the_zipfile,ZLIB_FILEFUNC_SEEK_SET)!=0)
            err=ZIP_ERRNO;
    }

    if (globalcomment)
    {
      *globalcomment = ziinit.globalcomment;
    }
#    endif /* !NO_ADDFILEINEXISTINGZIP*/

    if (err != ZIP_OK)
    {
#    ifndef NO_ADDFILEINEXISTINGZIP
        TRYFREE(ziinit.globalcomment);
#    endif /* !NO_ADDFILEINEXISTINGZIP*/
        TRYFREE(zi);
        return NULL;
    }
    else
    {
        *zi = ziinit;
        return (zipFile)zi;
    }
}

extern zipFile ZEXPORT zipOpen (file, append)
    voidpf file;
    int append;
{
    return zipOpen2(file,append,NULL,NULL);
}

extern int ZEXPORT zipOpenNewFileInZip3 (file, filename, zipfi,
                                         extrafield_local, size_extrafield_local,
                                         extrafield_global, size_extrafield_global,
                                         comment, method, level, raw,
                                         windowBits, memLevel, strategy,
                                         password, crcForCrypting)
    zipFile file;
    const char* filename;
    const zip_fileinfo* zipfi;
    const void* extrafield_local;
    uInt size_extrafield_local;
    const void* extrafield_global;
    uInt size_extrafield_global;
    const char* comment;
    int method;
    int level;
    int raw;
    int windowBits;
    int memLevel;
    int strategy;
    const char* password;
    uLong crcForCrypting;
{
    zip_internal* zi;
    uInt size_filename;
    uInt size_comment;
    uInt i;
    int err = ZIP_OK;
    uLong version_to_extract;

#    ifdef NOCRYPT
    if (password != NULL)
        return ZIP_PARAMERROR;
#    endif

    if (file == NULL)
        return ZIP_PARAMERROR;
    if ((method!=0) && (method!=Z_DEFLATED))
        return ZIP_PARAMERROR;

    zi = (zip_internal*)file;

    if (zi->in_opened_file_inzip == 1)
    {
        err = zipCloseFileInZip (file);
        if (err != ZIP_OK)
            return err;
    }

    if (method == 0
            && (level == 0 || (zi->flags & ZIP_WRITE_DATA_DESCRIPTOR) == 0))
    {
        version_to_extract = 10;
    }
    else
    {
        version_to_extract = 20;
    }


    if (filename==NULL)
        filename="-";

    if (comment==NULL)
        size_comment = 0;
    else
        size_comment = (uInt)strlen(comment);

    size_filename = (uInt)strlen(filename);

    if (zipfi == NULL)
        zi->ci.dosDate = 0;
    else
    {
        if (zipfi->dosDate != 0)
            zi->ci.dosDate = zipfi->dosDate;
        else zi->ci.dosDate = ziplocal_TmzDateToDosDate(&zipfi->tmz_date,zipfi->dosDate);
    }

    zi->ci.flag = 0;
    if ((level==8) || (level==9))
      zi->ci.flag |= 2;
    if ((level==2))
      zi->ci.flag |= 4;
    if ((level==1))
      zi->ci.flag |= 6;
    if (password != NULL)
    {
      zi->ci.flag |= 1;
    }
    if (version_to_extract >= 20
            && (zi->flags & ZIP_WRITE_DATA_DESCRIPTOR) != 0)
        zi->ci.flag |= 8;
    zi->ci.crc32 = 0;
    zi->ci.method = method;
    zi->ci.encrypt = 0;
    zi->ci.stream_initialised = 0;
    zi->ci.pos_in_buffered_data = 0;
    zi->ci.raw = raw;
    zi->ci.pos_local_header = ZTELL(zi->z_filefunc,zi->filestream) ;
    zi->ci.size_centralheader = SIZECENTRALHEADER + size_filename +
                                      size_extrafield_global + size_comment;
    zi->ci.central_header = (char*)ALLOC((uInt)zi->ci.size_centralheader);

    ziplocal_putValue_inmemory(zi->ci.central_header,(uLong)CENTRALHEADERMAGIC,4);
    /* version info 	 / * 버전 정보 * /*/
    ziplocal_putValue_inmemory(zi->ci.central_header+4,(uLong)VERSIONMADEBY,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+6,(uLong)version_to_extract,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+8,(uLong)zi->ci.flag,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+10,(uLong)zi->ci.method,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+12,(uLong)zi->ci.dosDate,4);
    ziplocal_putValue_inmemory(zi->ci.central_header+16,(uLong)0,4); /*crc*/
    ziplocal_putValue_inmemory(zi->ci.central_header+20,(uLong)0,4); /*compr size*/
    ziplocal_putValue_inmemory(zi->ci.central_header+24,(uLong)0,4); /*uncompr size*/
    ziplocal_putValue_inmemory(zi->ci.central_header+28,(uLong)size_filename,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+30,(uLong)size_extrafield_global,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+32,(uLong)size_comment,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+34,(uLong)0,2); /*disk nm start*/

    if (zipfi==NULL)
        ziplocal_putValue_inmemory(zi->ci.central_header+36,(uLong)0,2);
    else
        ziplocal_putValue_inmemory(zi->ci.central_header+36,(uLong)zipfi->internal_fa,2);

    if (zipfi==NULL)
        ziplocal_putValue_inmemory(zi->ci.central_header+38,(uLong)0,4);
    else
        ziplocal_putValue_inmemory(zi->ci.central_header+38,(uLong)zipfi->external_fa,4);

    ziplocal_putValue_inmemory(zi->ci.central_header+42,(uLong)zi->ci.pos_local_header- zi->add_position_when_writting_offset,4);

    for (i=0;i<size_filename;i++)
        *(zi->ci.central_header+SIZECENTRALHEADER+i) = *(filename+i);

    for (i=0;i<size_extrafield_global;i++)
        *(zi->ci.central_header+SIZECENTRALHEADER+size_filename+i) =
              *(((const char*)extrafield_global)+i);

    for (i=0;i<size_comment;i++)
        *(zi->ci.central_header+SIZECENTRALHEADER+size_filename+
              size_extrafield_global+i) = *(comment+i);
    if (zi->ci.central_header == NULL)
        return ZIP_INTERNALERROR;

    /* write the local header 	
    / * 로컬 헤더를 쓰십시오 * /*/
    err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)LOCALHEADERMAGIC,4);

    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)version_to_extract,2);
    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->ci.flag,2);

    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->ci.method,2);

    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->ci.dosDate,4);

    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4); /* crc 32, unknown */
    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4); /* compressed size, unknown */
    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4); /* uncompressed size, unknown */

    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_filename,2);

    if (err==ZIP_OK)
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_extrafield_local,2);

    if ((err==ZIP_OK) && (size_filename>0))
        if (ZWRITE(zi->z_filefunc,zi->filestream,filename,size_filename)!=size_filename)
                err = ZIP_ERRNO;

    if ((err==ZIP_OK) && (size_extrafield_local>0))
        if (ZWRITE(zi->z_filefunc,zi->filestream,extrafield_local,size_extrafield_local)
                                                                           !=size_extrafield_local)
                err = ZIP_ERRNO;

    memset(&zi->ci.stream, '\0', sizeof zi->ci.stream);
    zi->ci.stream.avail_in = (uInt)0;
    zi->ci.stream.avail_out = (uInt)Z_BUFSIZE;
    zi->ci.stream.next_out = zi->ci.buffered_data;
    zi->ci.stream.total_in = 0;
    zi->ci.stream.total_out = 0;

    if ((err==ZIP_OK) && (zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
    {
        zi->ci.stream.zalloc = (alloc_func)0;
        zi->ci.stream.zfree = (free_func)0;
        zi->ci.stream.opaque = (voidpf)0;

        if (windowBits>0)
            windowBits = -windowBits;

        err = deflateInit2(&zi->ci.stream, level,
               Z_DEFLATED, windowBits, memLevel, strategy);

        if (err==Z_OK)
            zi->ci.stream_initialised = 1;
    }
#    ifndef NOCRYPT
    zi->ci.crypt_header_size = 0;
    if ((err==Z_OK) && (password != NULL))
    {
        unsigned char bufHead[RAND_HEAD_LEN];
        unsigned int sizeHead;
        zi->ci.encrypt = 1;
        zi->ci.pcrc_32_tab = get_crc_table();
        /*init_keys(password,zi->ci.keys,zi->ci.pcrc_32_tab);*/

        crcForCrypting = (uLong)zi->ci.dosDate << 16; // ATTANTION! Without this row, you don't unpack your password protected archive in other app.
						      // ATTANTION! 이 행이 없으면 다른 앱에서 비밀번호로 보호 된 보관 파일의 압축을 푸지 않습니다.

																	
        sizeHead=crypthead(password,bufHead,RAND_HEAD_LEN,zi->ci.keys,zi->ci.pcrc_32_tab,crcForCrypting);
        zi->ci.crypt_header_size = sizeHead;

        if (ZWRITE(zi->z_filefunc,zi->filestream,bufHead,sizeHead) != sizeHead)
                err = ZIP_ERRNO;
    }
#    endif

    if (err==Z_OK)
        zi->in_opened_file_inzip = 1;
    return err;
}

extern int ZEXPORT zipOpenNewFileInZip2(file, filename, zipfi,
                                        extrafield_local, size_extrafield_local,
                                        extrafield_global, size_extrafield_global,
                                        comment, method, level, raw)
    zipFile file;
    const char* filename;
    const zip_fileinfo* zipfi;
    const void* extrafield_local;
    uInt size_extrafield_local;
    const void* extrafield_global;
    uInt size_extrafield_global;
    const char* comment;
    int method;
    int level;
    int raw;
{
    return zipOpenNewFileInZip3 (file, filename, zipfi,
                                 extrafield_local, size_extrafield_local,
                                 extrafield_global, size_extrafield_global,
                                 comment, method, level, raw,
                                 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                 NULL, 0);
}

extern int ZEXPORT zipOpenNewFileInZip (file, filename, zipfi,
                                        extrafield_local, size_extrafield_local,
                                        extrafield_global, size_extrafield_global,
                                        comment, method, level)
    zipFile file;
    const char* filename;
    const zip_fileinfo* zipfi;
    const void* extrafield_local;
    uInt size_extrafield_local;
    const void* extrafield_global;
    uInt size_extrafield_global;
    const char* comment;
    int method;
    int level;
{
    return zipOpenNewFileInZip2 (file, filename, zipfi,
                                 extrafield_local, size_extrafield_local,
                                 extrafield_global, size_extrafield_global,
                                 comment, method, level, 0);
}

local int zipFlushWriteBuffer(zi)
  zip_internal* zi;
{
    int err=ZIP_OK;

    if (zi->ci.encrypt != 0)
    {
#ifndef NOCRYPT
        uInt i;
        int t;
        for (i=0;i<zi->ci.pos_in_buffered_data;i++)
            zi->ci.buffered_data[i] = zencode(zi->ci.keys, zi->ci.pcrc_32_tab,
                                       zi->ci.buffered_data[i],t);
#endif
    }
    if (ZWRITE(zi->z_filefunc,zi->filestream,zi->ci.buffered_data,zi->ci.pos_in_buffered_data)
                                                                    !=zi->ci.pos_in_buffered_data)
      err = ZIP_ERRNO;
    zi->ci.pos_in_buffered_data = 0;
    return err;
}

extern int ZEXPORT zipWriteInFileInZip (file, buf, len)
    zipFile file;
    const void* buf;
    unsigned len;
{
    zip_internal* zi;
    int err=ZIP_OK;

    if (file == NULL)
        return ZIP_PARAMERROR;
    zi = (zip_internal*)file;

    if (zi->in_opened_file_inzip == 0)
        return ZIP_PARAMERROR;

    zi->ci.stream.next_in = (void*)buf;
    zi->ci.stream.avail_in = len;
    zi->ci.crc32 = crc32(zi->ci.crc32,buf,len);

    while ((err==ZIP_OK) && (zi->ci.stream.avail_in>0))
    {
        if (zi->ci.stream.avail_out == 0)
        {
            if (zipFlushWriteBuffer(zi) == ZIP_ERRNO)
                err = ZIP_ERRNO;
            zi->ci.stream.avail_out = (uInt)Z_BUFSIZE;
            zi->ci.stream.next_out = zi->ci.buffered_data;
        }


        if(err != ZIP_OK)
            break;

        if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
        {
            uLong uTotalOutBefore = zi->ci.stream.total_out;
            err=deflate(&zi->ci.stream,  Z_NO_FLUSH);
            zi->ci.pos_in_buffered_data += (uInt)(zi->ci.stream.total_out - uTotalOutBefore) ;

        }
        else
        {
            uInt copy_this,i;
            if (zi->ci.stream.avail_in < zi->ci.stream.avail_out)
                copy_this = zi->ci.stream.avail_in;
            else
                copy_this = zi->ci.stream.avail_out;
            for (i=0;i<copy_this;i++)
                *(((char*)zi->ci.stream.next_out)+i) =
                    *(((const char*)zi->ci.stream.next_in)+i);
            {
                zi->ci.stream.avail_in -= copy_this;
                zi->ci.stream.avail_out-= copy_this;
                zi->ci.stream.next_in+= copy_this;
                zi->ci.stream.next_out+= copy_this;
                zi->ci.stream.total_in+= copy_this;
                zi->ci.stream.total_out+= copy_this;
                zi->ci.pos_in_buffered_data += copy_this;
            }
        }
    }

    return err;
}

extern int ZEXPORT zipCloseFileInZipRaw (file, uncompressed_size, crc32)
    zipFile file;
    uLong uncompressed_size;
    uLong crc32;
{
    zip_internal* zi;
    uLong compressed_size;
    int err=ZIP_OK;

    if (file == NULL)
        return ZIP_PARAMERROR;
    zi = (zip_internal*)file;

    if (zi->in_opened_file_inzip == 0)
        return ZIP_PARAMERROR;
    zi->ci.stream.avail_in = 0;

    if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
        while (err==ZIP_OK)
    {
        uLong uTotalOutBefore;
        if (zi->ci.stream.avail_out == 0)
        {
            if (zipFlushWriteBuffer(zi) == ZIP_ERRNO)
                err = ZIP_ERRNO;
            zi->ci.stream.avail_out = (uInt)Z_BUFSIZE;
            zi->ci.stream.next_out = zi->ci.buffered_data;
        }
        uTotalOutBefore = zi->ci.stream.total_out;
        err=deflate(&zi->ci.stream,  Z_FINISH);
        zi->ci.pos_in_buffered_data += (uInt)(zi->ci.stream.total_out - uTotalOutBefore) ;
    }

    if (err==Z_STREAM_END)
        err=ZIP_OK; /* this is normal */

    if ((zi->ci.pos_in_buffered_data>0) && (err==ZIP_OK))
        if (zipFlushWriteBuffer(zi)==ZIP_ERRNO)
            err = ZIP_ERRNO;

    if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
    {
        err=deflateEnd(&zi->ci.stream);
        zi->ci.stream_initialised = 0;
    }

    if (!zi->ci.raw)
    {
        crc32 = (uLong)zi->ci.crc32;
        uncompressed_size = (uLong)zi->ci.stream.total_in;
    }
    compressed_size = (uLong)zi->ci.stream.total_out;
#    ifndef NOCRYPT
    compressed_size += zi->ci.crypt_header_size;
#    endif

    ziplocal_putValue_inmemory(zi->ci.central_header+16,crc32,4); /*crc*/
    ziplocal_putValue_inmemory(zi->ci.central_header+20,
                                compressed_size,4); /*compr size*/
    if (zi->ci.stream.data_type == Z_ASCII)
        ziplocal_putValue_inmemory(zi->ci.central_header+36,(uLong)Z_ASCII,2);
    ziplocal_putValue_inmemory(zi->ci.central_header+24,
                                uncompressed_size,4); /*uncompr size*/

    if (err==ZIP_OK)
        err = add_data_in_datablock(&zi->central_dir,zi->ci.central_header,
                                       (uLong)zi->ci.size_centralheader);
    free(zi->ci.central_header);

    if (err==ZIP_OK)
    {
        uLong cur_pos_inzip = ZTELL(zi->z_filefunc,zi->filestream);
        if (ZSEEK(zi->z_filefunc,zi->filestream,
                  zi->ci.pos_local_header + 14,ZLIB_FILEFUNC_SEEK_SET)!=0)
            err = ZIP_ERRNO;

        if (err==ZIP_OK)
            err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,crc32,4); /* crc 32, unknown */

        if (err==ZIP_OK) /* compressed size, unknown */
            err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,compressed_size,4);

        if (err==ZIP_OK) /* uncompressed size, unknown */
            err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,uncompressed_size,4);

        if (ZSEEK(zi->z_filefunc,zi->filestream,
                  cur_pos_inzip,ZLIB_FILEFUNC_SEEK_SET)!=0)
            err = ZIP_ERRNO;

        if ((zi->ci.flag & 8) != 0) {
            /* Write local Descriptor after file data */
            if (err==ZIP_OK)
                err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)DESCRIPTORHEADERMAGIC,4);

            if (err==ZIP_OK)
                err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,crc32,4); /* crc 32, unknown */

            if (err==ZIP_OK) /* compressed size, unknown */
                err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,compressed_size,4);

            if (err==ZIP_OK) /* uncompressed size, unknown */
                err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,uncompressed_size,4);
        }


    }

    zi->number_entry ++;
    zi->in_opened_file_inzip = 0;

    return err;
}

extern int ZEXPORT zipCloseFileInZip (file)
    zipFile file;
{
    return zipCloseFileInZipRaw (file,0,0);
}

extern int ZEXPORT zipClose (file, global_comment)
    zipFile file;
    const char* global_comment;
{
    zip_internal* zi;
    int err = 0;
    uLong size_centraldir = 0;
    uLong centraldir_pos_inzip;
    uInt size_global_comment;
    if (file == NULL)
        return ZIP_PARAMERROR;
    zi = (zip_internal*)file;

    if (zi->in_opened_file_inzip == 1)
    {
        err = zipCloseFileInZip (file);
    }

#ifndef NO_ADDFILEINEXISTINGZIP
    if (global_comment==NULL)
        global_comment = zi->globalcomment;
#endif
    if (global_comment==NULL)
        size_global_comment = 0;
    else
        size_global_comment = (uInt)strlen(global_comment);

    centraldir_pos_inzip = ZTELL(zi->z_filefunc,zi->filestream);
    if (err==ZIP_OK)
    {
        linkedlist_datablock_internal* ldi = zi->central_dir.first_block ;
        while (ldi!=NULL)
        {
            if ((err==ZIP_OK) && (ldi->filled_in_this_block>0))
                if (ZWRITE(zi->z_filefunc,zi->filestream,
                           ldi->data,ldi->filled_in_this_block)
                              !=ldi->filled_in_this_block )
                    err = ZIP_ERRNO;

            size_centraldir += ldi->filled_in_this_block;
            ldi = ldi->next_datablock;
        }
    }
    free_datablock(zi->central_dir.first_block);

    if (err==ZIP_OK) /* Magic End */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)ENDHEADERMAGIC,4);

    if (err==ZIP_OK) /* number of this disk */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,2);

    if (err==ZIP_OK) /* number of the disk with the start of the central directory */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,2);

    if (err==ZIP_OK) /* total number of entries in the central dir on this disk */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->number_entry,2);

    if (err==ZIP_OK) /* total number of entries in the central dir */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->number_entry,2);

    if (err==ZIP_OK) /* size of the central directory */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_centraldir,4);

    if (err==ZIP_OK) /* offset of start of central directory with respect to the
                            starting disk number */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,
                                (uLong)(centraldir_pos_inzip - zi->add_position_when_writting_offset),4);

    if (err==ZIP_OK) /* zipfile comment length */
        err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_global_comment,2);

    if ((err==ZIP_OK) && (size_global_comment>0))
        if (ZWRITE(zi->z_filefunc,zi->filestream,
                   global_comment,size_global_comment) != size_global_comment)
                err = ZIP_ERRNO;

    if (ZCLOSE(zi->z_filefunc,zi->filestream) != 0)
        if (err == ZIP_OK)
            err = ZIP_ERRNO;

#ifndef NO_ADDFILEINEXISTINGZIP
    TRYFREE(zi->globalcomment);
#endif
    TRYFREE(zi);

    return err;
}

extern int ZEXPORT zipSetFlags(zipFile file, unsigned flags)
{
    zip_internal* zi;
    if (file == NULL)
        return ZIP_PARAMERROR;
    zi = (zip_internal*)file;
    zi->flags |= flags;
    return ZIP_OK;
}

extern int ZEXPORT zipClearFlags(zipFile file, unsigned flags)
{
    zip_internal* zi;
    if (file == NULL)
        return ZIP_PARAMERROR;
    zi = (zip_internal*)file;
    zi->flags &= ~flags;
    return ZIP_OK;
}
