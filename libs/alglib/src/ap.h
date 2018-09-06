/*************************************************************************
Copyright (c) Sergey Bochkanov (ALGLIB project).

>>> SOURCE LICENSE >>>
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation (www.fsf.org); either version 2 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

A copy of the GNU General Public License is available at
http://www.fsf.org/licensing/licenses
>>> END OF LICENSE >>>
*************************************************************************/

#ifndef _ap_h
#define _ap_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string>
#include <cstring>
extern "C" {
#include <math.h>
}

#ifdef __BORLANDC__
#include <list.h>
#include <vector.h>
#else
#include <list>
#include <vector>
#endif

#define AE_USE_CPP
/* Definitions */
#define AE_UNKNOWN 0
#define AE_MSVC 1
#define AE_GNUC 2
#define AE_SUNC 3
#define AE_INTEL 1
#define AE_SPARC 2
#define AE_WINDOWS 1
#define AE_POSIX 2
#define AE_LOCK_ALIGNMENT 16

/* in case no OS is defined, use AE_UNKNOWN */
#ifndef AE_OS
#define AE_OS AE_UNKNOWN
#endif

/* automatically determine compiler */
#define AE_COMPILER AE_UNKNOWN
#ifdef __GNUC__
#undef AE_COMPILER
#define AE_COMPILER AE_GNUC
#endif
#if defined(__SUNPRO_C)||defined(__SUNPRO_CC)
#undef AE_COMPILER
#define AE_COMPILER AE_SUNC
#endif
#ifdef _MSC_VER
#undef AE_COMPILER
#define AE_COMPILER AE_MSVC
#endif

/* now we are ready to include headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <math.h>
#include <stddef.h>

#if AE_OS==AE_WINDOWS
#include <windows.h>
#include <process.h>
#elif AE_OS==AE_POSIX
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#endif

#if defined(AE_HAVE_STDINT)
#include <stdint.h>
#endif

/*
 * SSE2 intrinsics
 *
 * Preprocessor directives below:
 * - include headers for SSE2 intrinsics
 * - define AE_HAS_SSE2_INTRINSICS definition
 *
 * These actions are performed when we have:
 * - x86 architecture definition (AE_CPU==AE_INTEL)
 * - compiler which supports intrinsics
 *
 * Presence of AE_HAS_SSE2_INTRINSICS does NOT mean that our CPU
 * actually supports SSE2 - such things should be determined at runtime
 * with ae_cpuid() call. It means that we are working under Intel and
 * out compiler can issue SSE2-capable code.
 *
 */
/*
 * SSE2 내장 함수
 *
 * 전처리 지시어 :
 * - SSE2 내장 함수의 헤더 포함
 * - AE_HAS_SSE2_INTRINSICS 정의 정의
 *
 * 이러한 조치는 다음과 같은 경우에 수행됩니다.
 * - x86 아키텍처 정의 (AE_CPU == AE_INTEL)
 * - 내장 함수를 지원하는 컴파일러
 *
 * AE_HAS_SSE2_INTRINSICS의 존재는 우리의 CPU
 * 실제로는 SSE2를 지원합니다. 이러한 것들은 런타임에 결정되어야합니다.
* ae_cpuid () 호출로. 인텔에서 근무하고 있다는 것을 의미합니다.
 * out 컴파일러는 SSE2 가능 코드를 발행 할 수 있습니다.
 *
 */
#if defined(AE_CPU)
#if AE_CPU==AE_INTEL
#if AE_COMPILER==AE_MSVC
#include <emmintrin.h>
#define AE_HAS_SSE2_INTRINSICS
#endif
#if AE_COMPILER==AE_GNUC
#include <xmmintrin.h>
#define AE_HAS_SSE2_INTRINSICS
#endif
#if AE_COMPILER==AE_SUNC
#include <xmmintrin.h>
#include <emmintrin.h>
#define AE_HAS_SSE2_INTRINSICS
#endif
#endif
#endif

/* Debugging helpers for Windows */
#ifdef AE_DEBUG4WINDOWS
#include <windows.h>
#include <stdio.h>
#endif



/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS DECLARATIONS FOR BASIC FUNCTIONALITY 
// LIKE MEMORY MANAGEMENT FOR VECTORS/MATRICES WHICH IS SHARED 
// BETWEEN C++ AND PURE C LIBRARIES
//
/////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 기본 기능에 대한 선언이 포함되어 있습니다.
// 공유되는 벡터 / 자료에 대한 메모리 관리와 비슷합니다.
// C ++과 순수 C 라이브러리 사이
//
// /////////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{

/* if we work under C++ environment, define several conditions */
#ifdef AE_USE_CPP
#define AE_USE_CPP_BOOL
#define AE_USE_CPP_ERROR_HANDLING
#define AE_USE_CPP_SERIALIZATION
#endif

/*
 * define ae_int32_t, ae_int64_t, ae_int_t, ae_bool, ae_complex, ae_error_type and ae_datatype
 */

#if defined(AE_INT32_T)
typedef AE_INT32_T ae_int32_t;
#endif
#if defined(AE_HAVE_STDINT) && !defined(AE_INT32_T)
typedef int32_t ae_int32_t;
#endif
#if !defined(AE_HAVE_STDINT) && !defined(AE_INT32_T)
#if AE_COMPILER==AE_MSVC
typedef _int32 ae_int32_t;
#endif
#if (AE_COMPILER==AE_GNUC) || (AE_COMPILER==AE_SUNC) || (AE_COMPILER==AE_UNKNOWN)
typedef int ae_int32_t;
#endif
#endif

#if defined(AE_INT64_T)
typedef AE_INT64_T ae_int64_t;
#endif
#if defined(AE_HAVE_STDINT) && !defined(AE_INT64_T)
typedef int64_t ae_int64_t;
#endif
#if !defined(AE_HAVE_STDINT) && !defined(AE_INT64_T)
#if AE_COMPILER==AE_MSVC
typedef _int64 ae_int64_t;
#endif
#if (AE_COMPILER==AE_GNUC) || (AE_COMPILER==AE_SUNC) || (AE_COMPILER==AE_UNKNOWN)
typedef signed long long ae_int64_t;
#endif
#endif

#if !defined(AE_INT_T)
typedef ptrdiff_t ae_int_t;
#endif

#if !defined(AE_USE_CPP_BOOL)
#define ae_bool char
#define ae_true 1
#define ae_false 0
#else
#define ae_bool bool
#define ae_true true
#define ae_false false
#endif

typedef struct { double x, y; } ae_complex;

typedef enum
{
    ERR_OK = 0,
    ERR_OUT_OF_MEMORY = 1,
    ERR_XARRAY_TOO_LARGE = 2,
    ERR_ASSERTION_FAILED = 3
} ae_error_type;

typedef ae_int_t ae_datatype;

/*
 * other definitions
 */
enum { OWN_CALLER=1, OWN_AE=2 };
enum { ACT_UNCHANGED=1, ACT_SAME_LOCATION=2, ACT_NEW_LOCATION=3 };
enum { DT_BOOL=1, DT_INT=2, DT_REAL=3, DT_COMPLEX=4 };
enum { CPU_SSE2=1 };

/************************************************************************
x-string (zero-terminated):
    owner       OWN_CALLER or OWN_AE. Determines what to do on realloc().
                If vector is owned by caller, X-interface  will  just set
                ptr to NULL before realloc(). If it is  owned  by  X,  it
                will call ae_free/x_free/aligned_free family functions.

    last_action ACT_UNCHANGED, ACT_SAME_LOCATION, ACT_NEW_LOCATION
                contents is either: unchanged, stored at the same location,
                stored at the new location.
                this field is set on return from X.

    ptr         pointer to the actual data

Members of this structure are ae_int64_t to avoid alignment problems.
************************************************************************/
/* ************************************************ ************************
x 문자열 (제로 종료 됨) :
    소유자 OWN_CALLER 또는 OWN_AE. realloc ()에서 수행 할 작업을 결정합니다.
                벡터가 호출자가 소유 한 경우 X 인터페이스가 설정됩니다.
                realloc () 전에 NULL로 ptr. X가 소유 한 경우
                ae_free / aligned_free 패밀리 함수를 호출합니다.
    last_action ACT_UNCHANGED, ACT_SAME_LOCATION, ACT_NEW_LOCATION
                내용은 변경되지 않고 동일한 위치에 저장되며,
                새 위치에 저장됩니다.
                이 필드는 X에서 돌아올 때 설정됩니다.
    ptr 실제 데이터 포인터
이 구조의 구성원은 정렬 문제를 피하기 위해 ae_int64_t입니다.
*************************************************** ********************* */
typedef struct
{
    ae_int64_t     owner;
    ae_int64_t     last_action;
    char *ptr;
} x_string;

/************************************************************************
x-vector:
    cnt         number of elements

    datatype    one of the DT_XXXX values

    owner       OWN_CALLER or OWN_AE. Determines what to do on realloc().
                If vector is owned by caller, X-interface  will  just set
                ptr to NULL before realloc(). If it is  owned  by  X,  it
                will call ae_free/x_free/aligned_free family functions.

    last_action ACT_UNCHANGED, ACT_SAME_LOCATION, ACT_NEW_LOCATION
                contents is either: unchanged, stored at the same location,
                stored at the new location.
                this field is set on return from X interface and may be
                used by caller as hint when deciding what to do with data
                (if it was ACT_UNCHANGED or ACT_SAME_LOCATION, no array
                reallocation or copying is required).

    ptr         pointer to the actual data

Members of this structure are ae_int64_t to avoid alignment problems.
************************************************************************/
/* ************************************************ ************************
x 벡터 :
    요소의 cnt 수
    데이터 유형 DT_XXXX 값 중 하나
    소유자 OWN_CALLER 또는 OWN_AE. realloc ()에서 수행 할 작업을 결정합니다.
                벡터가 호출자가 소유 한 경우 X 인터페이스가 설정됩니다.
                realloc () 전에 NULL로 ptr. X가 소유 한 경우
                ae_free / aligned_free 패밀리 함수를 호출합니다.
    last_action ACT_UNCHANGED, ACT_SAME_LOCATION, ACT_NEW_LOCATION
                내용은 변경되지 않고 동일한 위치에 저장되며,
                새 위치에 저장됩니다.
                이 필드는 X 인터페이스에서 반환 될 때 설정되며
                데이터를 어떻게 처리할지 결정할 때 힌트로 호출자가 사용합니다.
                (ACT_UNCHANGED 또는 ACT_SAME_LOCATION 인 경우 배열 없음
                재 할당 또는 복사가 필요함).
    ptr 실제 데이터 포인터
이 구조의 구성원은 정렬 문제를 피하기 위해 ae_int64_t입니다.
*************************************************** ********************* */
typedef struct
{
    ae_int64_t     cnt;
    ae_int64_t     datatype;
    ae_int64_t     owner;
    ae_int64_t     last_action;
    void *ptr;
} x_vector;


/************************************************************************
x-matrix:
    rows        number of rows. may be zero only when cols is zero too.

    cols        number of columns. may be zero only when rows is zero too.

    stride      stride, i.e. distance between first elements of rows (in bytes)

    datatype    one of the DT_XXXX values

    owner       OWN_CALLER or OWN_AE. Determines what to do on realloc().
                If vector is owned by caller, X-interface  will  just set
                ptr to NULL before realloc(). If it is  owned  by  X,  it
                will call ae_free/x_free/aligned_free family functions.

    last_action ACT_UNCHANGED, ACT_SAME_LOCATION, ACT_NEW_LOCATION
                contents is either: unchanged, stored at the same location,
                stored at the new location.
                this field is set on return from X interface and may be
                used by caller as hint when deciding what to do with data
                (if it was ACT_UNCHANGED or ACT_SAME_LOCATION, no array
                reallocation or copying is required).

    ptr         pointer to the actual data, stored rowwise

Members of this structure are ae_int64_t to avoid alignment problems.
************************************************************************/
/* ************************************************ ************************
x- 매트릭스 :
    rows 행 수. cols가 0 일 때만 0이 될 수 있습니다.
    cols 열 수. 행이 0 일 때만 0이 될 수 있습니다.
    스트라이드 스트라이드, 즉 행의 첫 번째 요소 사이의 거리 (바이트 단위)
    데이터 유형 DT_XXXX 값 중 하나
    소유자 OWN_CALLER 또는 OWN_AE. realloc ()에서 수행 할 작업을 결정합니다.
                벡터가 호출자가 소유 한 경우 X 인터페이스가 설정됩니다.
                realloc () 전에 NULL로 ptr. X가 소유 한 경우
                ae_free / aligned_free 패밀리 함수를 호출합니다.
    last_action ACT_UNCHANGED, ACT_SAME_LOCATION, ACT_NEW_LOCATION
                내용은 변경되지 않고 동일한 위치에 저장되며,
                새 위치에 저장됩니다.
                이 필드는 X 인터페이스에서 반환 될 때 설정되며
                데이터를 어떻게 처리할지 결정할 때 힌트로 호출자가 사용합니다.
                (ACT_UNCHANGED 또는 ACT_SAME_LOCATION 인 경우 배열 없음
                재 할당 또는 복사가 필요함).
    ptr 실제 데이터에 대한 포인터.
이 구조의 구성원은 정렬 문제를 피하기 위해 ae_int64_t입니다.
*************************************************** ********************* */
typedef struct
{
    ae_int64_t     rows;
    ae_int64_t     cols;
    ae_int64_t     stride;
    ae_int64_t     datatype;
    ae_int64_t     owner;
    ae_int64_t     last_action;
    void *ptr;
} x_matrix;


/************************************************************************
dynamic block which may be automatically deallocated during stack unwinding

p_next          next block in the stack unwinding list.
                NULL means that this block is not in the list
deallocator     deallocator function which should be used to deallocate block.
                NULL for "special" blocks (frame/stack boundaries)
ptr             pointer which should be passed to the deallocator.
                may be null (for zero-size block), DYN_BOTTOM or DYN_FRAME
                for "special" blocks (frame/stack boundaries).

************************************************************************/
/* ************************************************ ************************
스택 해제 중에 자동으로 할당 해제 될 수있는 동적 블록
p_next 스택 해제 목록의 다음 블록.
                NULL은이 블록이 목록에 없음을 의미합니다.
블록을 할당 해제하는데 사용되어야하는 deallocator deallocator 함수.
                "특수"블록 (프레임 / 스택 경계)의 경우 NULL
deallocator에게 건네 져야 할 ptr 포인터.
                null (제로 사이즈의 블록의 경우), DYN_BOTTOM 또는 DYN_FRAME
                "특수"블록 (프레임 / 스택 경계).
*************************************************** ********************* */
typedef struct ae_dyn_block
{
    struct ae_dyn_block * volatile p_next;
    /* void *deallocator; */
    void (*deallocator)(void*);
    void * volatile ptr;
} ae_dyn_block;

/************************************************************************
frame marker
************************************************************************/
/* ************************************************ ************************
프레임 마커
*************************************************** ********************* */
typedef struct ae_frame
{
    ae_dyn_block db_marker;
} ae_frame;

/************************************************************************
ALGLIB environment state
************************************************************************/
/* ************************************************ ************************
ALGLIB 환경 상태
*************************************************** ********************* */
typedef struct ae_state
{
    /*
     * endianness type: AE_LITTLE_ENDIAN or AE_BIG_ENDIAN
     */
    ae_int_t endianness;
    
    /*
     * double value for NAN
     */
    double v_nan;
    
    /*
     * double value for +INF
     */
    double v_posinf;
    
    /*
     * double value for -INF
     */
    double v_neginf;
    
    /*
     * pointer to the top block in a stack of frames
     * which hold dynamically allocated objects
     */
    /*
     * 프레임 스택의 맨 위 블록에 대한 포인터
     동적으로 할당 된 객체를 보유하는 *
     */
    ae_dyn_block * volatile p_top_block;
    ae_dyn_block last_block;
    
    /*
     * jmp_buf for cases when C-style exception handling is used
     * C 스타일 예외 처리가 사용되는 경우 jmp_buf
     */
#ifndef AE_USE_CPP_ERROR_HANDLING
    jmp_buf * volatile break_jump;
#endif

    /*
     * ae_error_type of the last error (filled when exception is thrown) 
     *마지막 오류의 ae_error_type (예외가 발생하면 채워짐)
     */
    ae_error_type volatile last_error;
    
    /*
     * human-readable message (filled when exception is thrown)
     * 사람이 읽을 수있는 메시지 (예외가 발생할 때 채워짐)
     */
    const char* volatile error_msg;
    
    /*
     * threading information:
     * a) current thread pool
     * b) current worker thread
     * c) parent task (one we are solving right now)
     * d) thread exception handler (function which must be called
     *    by ae_assert before raising exception).
     *
     * NOTE: we use void* to store pointers in order to avoid explicit dependency on smp.h
     */
    /*
     * 스레딩 정보 :
     * a) 현재 스레드 풀
     * b) 현재 작업자 스레드
     * c) 부모 과제 (지금 당장 해결 중)
     * d) 스레드 예외 핸들러 (호출되어야하는 함수
     * 예외를 발생시키기 전에 ae_assert에 의해).
     *
     * 참고 : smp.h에 대한 명시 적 종속성을 피하기 위해 void *를 사용하여 포인터를 저장합니다.
     */

    void *worker_thread;
    void *parent_task;
    void (*thread_exception_handler)(void*);
    
} ae_state;

/************************************************************************
Serializer
************************************************************************/
/* ************************************************ ************************
시리얼 화기
*************************************************** ********************* */
typedef struct
{
    ae_int_t mode;
    ae_int_t entries_needed;
    ae_int_t entries_saved;
    ae_int_t bytes_asked;
    ae_int_t bytes_written;

#ifdef AE_USE_CPP_SERIALIZATION
    std::string     *out_cppstr;
#endif
    char            *out_str;
    const char      *in_str;
} ae_serializer;

typedef void(*ae_deallocator)(void*);

typedef struct ae_vector
{
    ae_int_t cnt;
    ae_datatype datatype;
    ae_dyn_block data;
    union
    {
        void *p_ptr;
        ae_bool *p_bool;
        ae_int_t *p_int;
        double *p_double;
        ae_complex *p_complex;
    } ptr;
} ae_vector;

typedef struct ae_matrix
{
    ae_int_t rows;
    ae_int_t cols;
    ae_int_t stride;
    ae_datatype datatype;
    ae_dyn_block data;
    union
    {
        void *p_ptr;
        void **pp_void;
        ae_bool **pp_bool;
        ae_int_t **pp_int;
        double **pp_double;
        ae_complex **pp_complex;
    } ptr;
} ae_matrix;

typedef struct ae_smart_ptr
{
    /* pointer to subscriber; all changes in ptr are translated to subscriber */
    /* 가입자 포인터; ptr의 모든 변경 사항은 subscriber */
    void **subscriber;
    
    /* pointer to object */
    /* 객체에 대한 포인터 */
    void *ptr;
    
    /* whether smart pointer owns ptr */
    /* 스마트 포인터가 ptr을 소유하는지 여부 */
    ae_bool is_owner;
    
    /* whether object pointed by ptr is dynamic - clearing such object requires BOTH
       calling destructor function AND calling ae_free for memory occupied by object. */
    /* ptr이 가리키는 객체가 동적인지 여부 - 그러한 객체를 지우려면 양쪽 모두가 필요합니다.
       소멸자 함수 호출 및 객체에 의해 점유 된 메모리에 대해 ae_free 호출. */
    ae_bool is_dynamic;
    
    /* destructor function for pointer; clears all dynamically allocated memory */
    /* 포인터 소멸자 함수; 동적으로 할당 된 모든 메모리를 지 웁니다. */
    void (*destroy)(void*);
    
    /* frame entry; used to ensure automatic deallocation of smart pointer in case of exception/exit */
    /* 프레임 엔트리; 예외 / 종료시 스마트 포인터의 자동 할당 해제에 사용 */
    ae_dyn_block frame_entry;
} ae_smart_ptr;


/*************************************************************************
Lock.

This structure provides OS-independent non-reentrant lock:
* under Windows/Posix systems it uses system-provided locks
* under Boost it uses OS-independent lock provided by Boost package
* when no OS is defined, it uses "fake lock" (just stub which is not thread-safe):
  a) "fake lock" can be in locked or free mode
  b) "fake lock" can be used only from one thread - one which created lock
  c) when thread acquires free lock, it immediately returns
  d) when thread acquires busy lock, program is terminated
     (because lock is already acquired and no one else can free it)
*************************************************************************/
/* ************************************************ *************************
자물쇠.
이 구조체는 OS 독립적 인 재진입 불가능한 잠금을 제공합니다.
* Windows / Posix 시스템에서는 시스템 제공 잠금을 사용합니다.
* Boost에서는 Boost 패키지에서 제공하는 OS 독립적 잠금을 사용합니다.
* OS가 정의되어 있지 않은 경우, "fake lock"(쓰레드에 안전하지 않은 스텁)을 사용합니다 :
  a) "가짜 잠금 장치"는 잠긴 모드 또는 자유 모드 일 수 있습니다.
  b) "가짜 잠금"은 하나의 스레드에서만 사용할 수 있습니다 - 잠금을 생성 한 스레드
  c) 스레드가 자유 잠금을 획득하면 즉시 반환합니다.
  d) 쓰레드가 busy lock을 획득하면 프로그램은 종료된다.
     (잠금은 이미 획득되었으므로 잠금을 해제 할 수 없기 때문에)
*************************************************** ********************** */
typedef struct
{
#if AE_OS==AE_WINDOWS
    volatile ae_int_t * volatile p_lock;
    char buf[sizeof(ae_int_t)+AE_LOCK_ALIGNMENT];
#elif AE_OS==AE_POSIX
    pthread_mutex_t mutex;
#else
    ae_bool is_locked;
#endif
} ae_lock;


/*************************************************************************
Shared pool: data structure used to provide thread-safe access to pool  of
temporary variables.
*************************************************************************/
/* ************************************************ *************************
공유 풀 : 풀에 대한 스레드 안전 액세스를 제공하는 데 사용되는 데이터 구조
임시 변수.
*************************************************** ********************** */
typedef struct ae_shared_pool_entry
{
    void * volatile obj;
    void * volatile next_entry;
} ae_shared_pool_entry;

typedef struct ae_shared_pool
{
    /* lock object which protects pool */
    /* 풀을 보호하는 객체 잠금 */
    ae_lock pool_lock;
    
    /* seed object (used to create new instances of temporaries) */
    /* 시드 객체 (임시 객체의 새 인스턴스를 만드는 데 사용됨) */
    void                    * volatile seed_object;
    
    /*
     * list of recycled OBJECTS:
     * 1. entries in this list store pointers to recycled objects
     * 2. every time we retrieve object, we retrieve first entry from this list,
     *    move it to recycled_entries and return its obj field to caller/
     */
    /*
     * 재생 된 대상 목록 :
     * 1.이 목록의 항목은 재생 된 객체에 대한 포인터를 저장합니다.
     * 2. 우리는 객체를 가져올 때마다이 목록에서 첫 번째 항목을 가져옵니다.
     * recycled_entries로 이동하고 obj 필드를 호출자 /
     */
    ae_shared_pool_entry    * volatile recycled_objects;
    
    /* 
     * list of recycled ENTRIES:
     * 1. this list holds entries which are not used to store recycled objects;
     *    every time recycled object is retrieved, its entry is moved to this list.
     * 2. every time object is recycled, we try to fetch entry for him from this list
     *    before allocating it with malloc()
     */
    /* 
     * 재활용 된 항목 목록 :
     * 1.이 목록에는 재활용품을 보관하는 데 사용되지 않는 항목이 있습니다.
     * 재활용 된 물체가 회수 될 때마다 그 물체는이 목록으로 옮겨집니다.
     * 2. 개체가 재활용 될 때마다이 목록에서 해당 항목을 가져옵니다.
     * malloc ()으로 할당하기 전에
     */
    ae_shared_pool_entry    * volatile recycled_entries;
    
    /* enumeration pointer, points to current recycled object*/
    /* 열거 포인터, 현재 재활용 된 객체를 가리킴 */
    ae_shared_pool_entry    * volatile enumeration_counter;
    
    /* size of object; this field is used when we call malloc() for new objects */
    /* 객체의 크기; 이 필드는 새로운 객체에 대해 malloc ()을 호출 할 때 사용된다. */
    ae_int_t                size_of_object;
    
    /* initializer function; accepts pointer to malloc'ed object, initializes its fields */
    /* 초기화 함수. malloc 객체에 대한 포인터를 받아들이고, 필드를 초기화한다. */
    ae_bool (*init)(void* dst, ae_state* state, ae_bool make_automatic);
    
    /* copy constructor; accepts pointer to malloc'ed, but not initialized object */
    /* 복사 생성자; malloc 된 객체에 대한 포인터를 받지만 초기화되지 않은 객체 */
    ae_bool (*init_copy)(void* dst, void* src, ae_state* state, ae_bool make_automatic);
    
    /* destructor function; */
    /* 소멸자 함수; */
    void (*destroy)(void* ptr);
    
    /* frame entry; contains pointer to the pool object itself */
    /* 프레임 엔트리; 풀 객체 자체에 대한 포인터를 포함합니다. */
    ae_dyn_block frame_entry;
} ae_shared_pool;
 
ae_int_t ae_misalignment(const void *ptr, size_t alignment);
void* ae_align(void *ptr, size_t alignment);
void* aligned_malloc(size_t size, size_t alignment);
void  aligned_free(void *block);

void* ae_malloc(size_t size, ae_state *state);
void  ae_free(void *p);
ae_int_t ae_sizeof(ae_datatype datatype);
void ae_touch_ptr(void *p);

void ae_state_init(ae_state *state);
void ae_state_clear(ae_state *state);
#ifndef AE_USE_CPP_ERROR_HANDLING
void ae_state_set_break_jump(ae_state *state, jmp_buf *buf);
#endif
void ae_break(ae_state *state, ae_error_type error_type, const char *msg);

void ae_frame_make(ae_state *state, ae_frame *tmp);
void ae_frame_leave(ae_state *state);

void ae_db_attach(ae_dyn_block *block, ae_state *state);
ae_bool ae_db_malloc(ae_dyn_block *block, ae_int_t size, ae_state *state, ae_bool make_automatic);
ae_bool ae_db_realloc(ae_dyn_block *block, ae_int_t size, ae_state *state);
void ae_db_free(ae_dyn_block *block);
void ae_db_swap(ae_dyn_block *block1, ae_dyn_block *block2);

ae_bool ae_vector_init(ae_vector *dst, ae_int_t size, ae_datatype datatype, ae_state *state, ae_bool make_automatic);
ae_bool ae_vector_init_copy(ae_vector *dst, ae_vector *src, ae_state *state, ae_bool make_automatic);
void ae_vector_init_from_x(ae_vector *dst, x_vector *src, ae_state *state, ae_bool make_automatic);
ae_bool ae_vector_set_length(ae_vector *dst, ae_int_t newsize, ae_state *state);
void ae_vector_clear(ae_vector *dst);
void ae_vector_destroy(ae_vector *dst);
void ae_swap_vectors(ae_vector *vec1, ae_vector *vec2);

ae_bool ae_matrix_init(ae_matrix *dst, ae_int_t rows, ae_int_t cols, ae_datatype datatype, ae_state *state, ae_bool make_automatic);
ae_bool ae_matrix_init_copy(ae_matrix *dst, ae_matrix *src, ae_state *state, ae_bool make_automatic);
void ae_matrix_init_from_x(ae_matrix *dst, x_matrix *src, ae_state *state, ae_bool make_automatic);
ae_bool ae_matrix_set_length(ae_matrix *dst, ae_int_t rows, ae_int_t cols, ae_state *state);
void ae_matrix_clear(ae_matrix *dst);
void ae_matrix_destroy(ae_matrix *dst);
void ae_swap_matrices(ae_matrix *mat1, ae_matrix *mat2);

ae_bool ae_smart_ptr_init(ae_smart_ptr *dst, void **subscriber, ae_state *state, ae_bool make_automatic);
void ae_smart_ptr_clear(void *_dst); /* accepts ae_smart_ptr* ae_smart_ptr을 수락합니다 */
void ae_smart_ptr_destroy(void *_dst);
void ae_smart_ptr_assign(ae_smart_ptr *dst, void *new_ptr, ae_bool is_owner, ae_bool is_dynamic, void (*destroy)(void*));
void ae_smart_ptr_release(ae_smart_ptr *dst);

void ae_yield();
void ae_init_lock(ae_lock *lock);
void ae_acquire_lock(ae_lock *lock);
void ae_release_lock(ae_lock *lock);
void ae_free_lock(ae_lock *lock);

ae_bool ae_shared_pool_init(void *_dst, ae_state *state, ae_bool make_automatic);
ae_bool ae_shared_pool_init_copy(void *_dst, void *_src, ae_state *state, ae_bool make_automatic);
void ae_shared_pool_clear(void *dst);
void ae_shared_pool_destroy(void *dst);
ae_bool ae_shared_pool_is_initialized(void *_dst);
void ae_shared_pool_set_seed(
    ae_shared_pool  *dst,
    void            *seed_object,
    ae_int_t        size_of_object,
    ae_bool         (*init)(void* dst, ae_state* state, ae_bool make_automatic),
    ae_bool         (*init_copy)(void* dst, void* src, ae_state* state, ae_bool make_automatic),
    void            (*destroy)(void* ptr),
    ae_state        *state);
void ae_shared_pool_retrieve(
    ae_shared_pool  *pool,
    ae_smart_ptr    *pptr,
    ae_state        *state);
void ae_shared_pool_recycle(
    ae_shared_pool  *pool,
    ae_smart_ptr    *pptr,
    ae_state        *state);
void ae_shared_pool_clear_recycled(
    ae_shared_pool  *pool,
    ae_state        *state);
void ae_shared_pool_first_recycled(
    ae_shared_pool  *pool,
    ae_smart_ptr    *pptr,
    ae_state        *state);
void ae_shared_pool_next_recycled(
    ae_shared_pool  *pool,
    ae_smart_ptr    *pptr,
    ae_state        *state);
void ae_shared_pool_reset(
    ae_shared_pool  *pool,
    ae_state        *state);

void ae_x_set_vector(x_vector *dst, ae_vector *src, ae_state *state);
void ae_x_set_matrix(x_matrix *dst, ae_matrix *src, ae_state *state);
void ae_x_attach_to_vector(x_vector *dst, ae_vector *src);
void ae_x_attach_to_matrix(x_matrix *dst, ae_matrix *src);

void x_vector_clear(x_vector *dst);

ae_bool x_is_symmetric(x_matrix *a);
ae_bool x_is_hermitian(x_matrix *a);
ae_bool x_force_symmetric(x_matrix *a);
ae_bool x_force_hermitian(x_matrix *a);
ae_bool ae_is_symmetric(ae_matrix *a);
ae_bool ae_is_hermitian(ae_matrix *a);
ae_bool ae_force_symmetric(ae_matrix *a);
ae_bool ae_force_hermitian(ae_matrix *a);

void ae_serializer_init(ae_serializer *serializer);
void ae_serializer_clear(ae_serializer *serializer);

void ae_serializer_alloc_start(ae_serializer *serializer);
void ae_serializer_alloc_entry(ae_serializer *serializer);
ae_int_t ae_serializer_get_alloc_size(ae_serializer *serializer);

#ifdef AE_USE_CPP_SERIALIZATION
void ae_serializer_sstart_str(ae_serializer *serializer, std::string *buf);
void ae_serializer_ustart_str(ae_serializer *serializer, const std::string *buf);
#endif
void ae_serializer_sstart_str(ae_serializer *serializer, char *buf);
void ae_serializer_ustart_str(ae_serializer *serializer, const char *buf);

void ae_serializer_serialize_bool(ae_serializer *serializer, ae_bool v, ae_state *state);
void ae_serializer_serialize_int(ae_serializer *serializer, ae_int_t v, ae_state *state);
void ae_serializer_serialize_double(ae_serializer *serializer, double v, ae_state *state);
void ae_serializer_unserialize_bool(ae_serializer *serializer, ae_bool *v, ae_state *state);
void ae_serializer_unserialize_int(ae_serializer *serializer, ae_int_t *v, ae_state *state);
void ae_serializer_unserialize_double(ae_serializer *serializer, double *v, ae_state *state);

void ae_serializer_stop(ae_serializer *serializer);

/************************************************************************
Service functions
************************************************************************/
/* ************************************************ ************************
서비스 기능
*************************************************** ********************* */
void ae_assert(ae_bool cond, const char *msg, ae_state *state);
ae_int_t ae_cpuid();

/************************************************************************
Real math functions:
* IEEE-compliant floating point comparisons
* standard functions
************************************************************************/
/* ************************************************ ************************
실제 수학 함수 :
* IEEE 호환 부동 소수점 비교
* 표준 함수
*************************************************** ********************* */
ae_bool ae_fp_eq(double v1, double v2);
ae_bool ae_fp_neq(double v1, double v2);
ae_bool ae_fp_less(double v1, double v2);
ae_bool ae_fp_less_eq(double v1, double v2);
ae_bool ae_fp_greater(double v1, double v2);
ae_bool ae_fp_greater_eq(double v1, double v2);

ae_bool ae_isfinite_stateless(double x, ae_int_t endianness);
ae_bool ae_isnan_stateless(double x,    ae_int_t endianness);
ae_bool ae_isinf_stateless(double x,    ae_int_t endianness);
ae_bool ae_isposinf_stateless(double x, ae_int_t endianness);
ae_bool ae_isneginf_stateless(double x, ae_int_t endianness);

ae_int_t ae_get_endianness();

ae_bool ae_isfinite(double x,ae_state *state);
ae_bool ae_isnan(double x,   ae_state *state);
ae_bool ae_isinf(double x,   ae_state *state);
ae_bool ae_isposinf(double x,ae_state *state);
ae_bool ae_isneginf(double x,ae_state *state);

double   ae_fabs(double x,   ae_state *state);
ae_int_t ae_iabs(ae_int_t x, ae_state *state);
double   ae_sqr(double x,    ae_state *state);
double   ae_sqrt(double x,   ae_state *state);

ae_int_t ae_sign(double x,   ae_state *state);
ae_int_t ae_round(double x,  ae_state *state);
ae_int_t ae_trunc(double x,  ae_state *state);
ae_int_t ae_ifloor(double x, ae_state *state);
ae_int_t ae_iceil(double x,  ae_state *state);

ae_int_t ae_maxint(ae_int_t m1, ae_int_t m2, ae_state *state);
ae_int_t ae_minint(ae_int_t m1, ae_int_t m2, ae_state *state);
double   ae_maxreal(double m1, double m2, ae_state *state);
double   ae_minreal(double m1, double m2, ae_state *state);
double   ae_randomreal(ae_state *state);
ae_int_t ae_randominteger(ae_int_t maxv, ae_state *state);

double   ae_sin(double x, ae_state *state);
double   ae_cos(double x, ae_state *state);
double   ae_tan(double x, ae_state *state);
double   ae_sinh(double x, ae_state *state);
double   ae_cosh(double x, ae_state *state);
double   ae_tanh(double x, ae_state *state);
double   ae_asin(double x, ae_state *state);
double   ae_acos(double x, ae_state *state);
double   ae_atan(double x, ae_state *state);
double   ae_atan2(double y, double x, ae_state *state);

double   ae_log(double x, ae_state *state);
double   ae_pow(double x, double y, ae_state *state);
double   ae_exp(double x, ae_state *state);

/************************************************************************
Complex math functions:
* basic arithmetic operations
* standard functions
************************************************************************/
/* ************************************************ ************************
복잡한 수학 함수 :
* 기본 산술 연산
* 표준 함수
*************************************************** ********************* */
ae_complex ae_complex_from_d(double v);

ae_complex ae_c_neg(ae_complex lhs);
ae_bool ae_c_eq(ae_complex lhs,       ae_complex rhs);
ae_bool ae_c_neq(ae_complex lhs,      ae_complex rhs);
ae_complex ae_c_add(ae_complex lhs,   ae_complex rhs);
ae_complex ae_c_mul(ae_complex lhs,   ae_complex rhs);
ae_complex ae_c_sub(ae_complex lhs,   ae_complex rhs);
ae_complex ae_c_div(ae_complex lhs,   ae_complex rhs);
ae_bool ae_c_eq_d(ae_complex lhs,     double rhs);
ae_bool ae_c_neq_d(ae_complex lhs,    double rhs);
ae_complex ae_c_add_d(ae_complex lhs, double rhs);
ae_complex ae_c_mul_d(ae_complex lhs, double rhs);
ae_complex ae_c_sub_d(ae_complex lhs, double rhs);
ae_complex ae_c_d_sub(double lhs,     ae_complex rhs);
ae_complex ae_c_div_d(ae_complex lhs, double rhs);
ae_complex ae_c_d_div(double lhs,   ae_complex rhs);

ae_complex ae_c_conj(ae_complex lhs, ae_state *state);
ae_complex ae_c_sqr(ae_complex lhs, ae_state *state);
double     ae_c_abs(ae_complex z, ae_state *state);

/************************************************************************
Complex BLAS operations
************************************************************************/
/* ************************************************ ************************
복잡한 BLAS 운영
*************************************************** ********************* */
ae_complex ae_v_cdotproduct(const ae_complex *v0, ae_int_t stride0, const char *conj0, const ae_complex *v1, ae_int_t stride1, const char *conj1, ae_int_t n);
void ae_v_cmove(ae_complex *vdst,    ae_int_t stride_dst, const ae_complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void ae_v_cmoveneg(ae_complex *vdst, ae_int_t stride_dst, const ae_complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void ae_v_cmoved(ae_complex *vdst,   ae_int_t stride_dst, const ae_complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, double alpha);
void ae_v_cmovec(ae_complex *vdst,   ae_int_t stride_dst, const ae_complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, ae_complex alpha);
void ae_v_cadd(ae_complex *vdst,     ae_int_t stride_dst, const ae_complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void ae_v_caddd(ae_complex *vdst,    ae_int_t stride_dst, const ae_complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, double alpha);
void ae_v_caddc(ae_complex *vdst,    ae_int_t stride_dst, const ae_complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, ae_complex alpha);
void ae_v_csub(ae_complex *vdst,     ae_int_t stride_dst, const ae_complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void ae_v_csubd(ae_complex *vdst, ae_int_t stride_dst, const ae_complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, double alpha);
void ae_v_csubc(ae_complex *vdst, ae_int_t stride_dst, const ae_complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, ae_complex alpha);
void ae_v_cmuld(ae_complex *vdst, ae_int_t stride_dst, ae_int_t n, double alpha);
void ae_v_cmulc(ae_complex *vdst, ae_int_t stride_dst, ae_int_t n, ae_complex alpha);

/************************************************************************
Real BLAS operations
************************************************************************/
/* ************************************************ ************************
실제 BLAS 운영
*************************************************** ********************* */
double ae_v_dotproduct(const double *v0, ae_int_t stride0, const double *v1, ae_int_t stride1, ae_int_t n);
void ae_v_move(double *vdst,    ae_int_t stride_dst, const double* vsrc,  ae_int_t stride_src, ae_int_t n);
void ae_v_moveneg(double *vdst, ae_int_t stride_dst, const double* vsrc,  ae_int_t stride_src, ae_int_t n);
void ae_v_moved(double *vdst,   ae_int_t stride_dst, const double* vsrc,  ae_int_t stride_src, ae_int_t n, double alpha);
void ae_v_add(double *vdst,     ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n);
void ae_v_addd(double *vdst,    ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n, double alpha);
void ae_v_sub(double *vdst,     ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n);
void ae_v_subd(double *vdst,    ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n, double alpha);
void ae_v_muld(double *vdst,  ae_int_t stride_dst, ae_int_t n, double alpha);

/************************************************************************
Other functions
************************************************************************/
/* ************************************************ ************************
기타 기능
*************************************************** ********************* */
ae_int_t ae_v_len(ae_int_t a, ae_int_t b);

/*
extern const double ae_machineepsilon;
extern const double ae_maxrealnumber;
extern const double ae_minrealnumber;
extern const double ae_pi;
*/
#define ae_machineepsilon 5E-16
#define ae_maxrealnumber  1E300
#define ae_minrealnumber  1E-300
#define ae_pi 3.1415926535897932384626433832795


/************************************************************************
RComm functions
************************************************************************/
typedef struct rcommstate
{
    int stage;
    ae_vector ia;
    ae_vector ba;
    ae_vector ra;
    ae_vector ca;
} rcommstate;
ae_bool _rcommstate_init(rcommstate* p, ae_state *_state, ae_bool make_automatic);
ae_bool _rcommstate_init_copy(rcommstate* dst, rcommstate* src, ae_state *_state, ae_bool make_automatic);
void _rcommstate_clear(rcommstate* p);
void _rcommstate_destroy(rcommstate* p);

#ifdef AE_USE_ALLOC_COUNTER
extern ae_int64_t _alloc_counter;
#endif


/************************************************************************
debug functions (must be turned on by preprocessor definitions):
* tickcount(), which is wrapper around GetTickCount()
* flushconsole(), fluches console
* ae_debugrng(), returns random number generated with high-quality random numbers generator
* ae_set_seed(), sets seed of the debug RNG (NON-THREAD-SAFE!!!)
* ae_get_seed(), returns two seed values of the debug RNG (NON-THREAD-SAFE!!!)
************************************************************************/
/* ************************************************ ************************
디버그 기능 (선처리기 정의에 의해 켜져 있어야 함) :
* TickCount () : GetTickCount () 주위의 래퍼입니다.
* flushconsole (), fluches 콘솔
* ae_debugrng ()는 고품질 난수 생성기로 생성 된 난수를 반환합니다.
* ae_set_seed (), 디버그 RNG의 시드 (NON-THREAD-SAFE !!!)를 설정합니다.
* ae_get_seed ()는 디버그 RNG의 시드 값 두 개를 반환합니다 (NON-THREAD-SAFE !!!).
*************************************************** ********************* */
#ifdef AE_DEBUG4WINDOWS
#define flushconsole(s) fflush(stdout)
#define tickcount(s) _tickcount()
int _tickcount();
#endif
#ifdef AE_DEBUG4POSIX
#define flushconsole(s) fflush(stdout)
#define tickcount(s) _tickcount()
int _tickcount();
#endif
#ifdef AE_DEBUGRNG
ae_int_t ae_debugrng();
void ae_set_seed(ae_int_t s0, ae_int_t s1);
void ae_get_seed(ae_int_t *s0, ae_int_t *s1);
#endif


}


/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS DECLARATIONS FOR C++ RELATED FUNCTIONALITY
//
/////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////
//
// 이 절에는 C ++ 관련 기능에 대한 선언이 포함되어 있습니다.
//
// //////////////////////////////////////////////////////////////////////

namespace alglib
{

typedef alglib_impl::ae_int_t ae_int_t;

/********************************************************************
Class forwards
********************************************************************/
/* ************************************************ *******************
클래스 전달
*************************************************** **************** */
class complex;

ae_int_t vlen(ae_int_t n1, ae_int_t n2);

/********************************************************************
Exception class.
********************************************************************/
/* ************************************************ *******************
예외 클래스.
*************************************************** **************** */
class ap_error
{
public:
    std::string msg;
    
    ap_error();
    ap_error(const char *s);
    static void make_assertion(bool bClause);
    static void make_assertion(bool bClause, const char *msg);
private:
};

/********************************************************************
Complex number with double precision.
********************************************************************/
/* ************************************************ *******************
배정 밀도의 복소수
*************************************************** **************** */
class complex
{
public:
    complex();
    complex(const double &_x);
    complex(const double &_x, const double &_y);
    complex(const complex &z);

    complex& operator= (const double& v);
    complex& operator+=(const double& v);
    complex& operator-=(const double& v);
    complex& operator*=(const double& v);
    complex& operator/=(const double& v);

    complex& operator= (const complex& z);
    complex& operator+=(const complex& z);
    complex& operator-=(const complex& z);
    complex& operator*=(const complex& z);
    complex& operator/=(const complex& z);

    alglib_impl::ae_complex*       c_ptr();
    const alglib_impl::ae_complex* c_ptr() const;
    
    std::string tostring(int dps) const;

    double x, y;
};

const alglib::complex operator/(const alglib::complex& lhs, const alglib::complex& rhs);
bool operator==(const alglib::complex& lhs, const alglib::complex& rhs);
bool operator!=(const alglib::complex& lhs, const alglib::complex& rhs);
const alglib::complex operator+(const alglib::complex& lhs);
const alglib::complex operator-(const alglib::complex& lhs);
const alglib::complex operator+(const alglib::complex& lhs, const alglib::complex& rhs);
const alglib::complex operator+(const alglib::complex& lhs, const double& rhs);
const alglib::complex operator+(const double& lhs, const alglib::complex& rhs);
const alglib::complex operator-(const alglib::complex& lhs, const alglib::complex& rhs);
const alglib::complex operator-(const alglib::complex& lhs, const double& rhs);
const alglib::complex operator-(const double& lhs, const alglib::complex& rhs);
const alglib::complex operator*(const alglib::complex& lhs, const alglib::complex& rhs);
const alglib::complex operator*(const alglib::complex& lhs, const double& rhs);
const alglib::complex operator*(const double& lhs, const alglib::complex& rhs);
const alglib::complex operator/(const alglib::complex& lhs, const alglib::complex& rhs);
const alglib::complex operator/(const double& lhs, const alglib::complex& rhs);
const alglib::complex operator/(const alglib::complex& lhs, const double& rhs);
double abscomplex(const alglib::complex &z);
alglib::complex conj(const alglib::complex &z);
alglib::complex csqr(const alglib::complex &z);
void setnworkers(alglib::ae_int_t nworkers);

/********************************************************************
Level 1 BLAS functions

NOTES:
* destination and source should NOT overlap
* stride is assumed to be positive, but it is not 
  assert'ed within function
* conj_src parameter specifies whether complex source is conjugated 
  before processing or not. Pass string which starts with 'N' or 'n'
  ("No conj", for example) to use unmodified parameter. All other
  values will result in conjugation of input, but it is recommended
  to use "Conj" in such cases.
********************************************************************/
/* ************************************************ *******************
레벨 1 BLAS 기능
노트:
* 대상과 소스가 겹치지 않아야합니다.
* 보폭은 양수로 가정되지만, 그렇지 않습니다. 
  함수 내에서 assert'ed
* conj_src 매개 변수는 복합 원본을 공액으로 처리할지 여부를 지정합니다. 
  처리하기 전에. 'N'또는 'n'으로 시작하는 패스 문자열
  (예 : "conj") 수정되지 않은 매개 변수를 사용합니다. 그 외 모든 것들
  값은 입력의 컨쥬 게이션을 가져 오지만 권장됩니다
  그런 경우에는 "Conj"를 사용하십시오.
*************************************************** **************** */
double vdotproduct(const double *v0, ae_int_t stride0, const double *v1, ae_int_t stride1, ae_int_t n);
double vdotproduct(const double *v1, const double *v2, ae_int_t N);

alglib::complex vdotproduct(const alglib::complex *v0, ae_int_t stride0, const char *conj0, const alglib::complex *v1, ae_int_t stride1, const char *conj1, ae_int_t n);
alglib::complex vdotproduct(const alglib::complex *v1, const alglib::complex *v2, ae_int_t N);

void vmove(double *vdst,  ae_int_t stride_dst, const double* vsrc,  ae_int_t stride_src, ae_int_t n);
void vmove(double *vdst, const double* vsrc, ae_int_t N);

void vmove(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void vmove(alglib::complex *vdst, const alglib::complex* vsrc, ae_int_t N);

void vmoveneg(double *vdst,  ae_int_t stride_dst, const double* vsrc,  ae_int_t stride_src, ae_int_t n);
void vmoveneg(double *vdst, const double *vsrc, ae_int_t N);

void vmoveneg(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void vmoveneg(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N);

void vmove(double *vdst,  ae_int_t stride_dst, const double* vsrc,  ae_int_t stride_src, ae_int_t n, double alpha);
void vmove(double *vdst, const double *vsrc, ae_int_t N, double alpha);

void vmove(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, double alpha);
void vmove(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N, double alpha);

void vmove(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex* vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, alglib::complex alpha);
void vmove(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N, alglib::complex alpha);

void vadd(double *vdst,  ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n);
void vadd(double *vdst, const double *vsrc, ae_int_t N);

void vadd(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void vadd(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N);

void vadd(double *vdst,  ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n, double alpha);
void vadd(double *vdst, const double *vsrc, ae_int_t N, double alpha);

void vadd(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, double alpha);
void vadd(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N, double alpha);

void vadd(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, alglib::complex alpha);
void vadd(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N, alglib::complex alpha);

void vsub(double *vdst,  ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n);
void vsub(double *vdst, const double *vsrc, ae_int_t N);

void vsub(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n);
void vsub(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N);

void vsub(double *vdst,  ae_int_t stride_dst, const double *vsrc,  ae_int_t stride_src, ae_int_t n, double alpha);
void vsub(double *vdst, const double *vsrc, ae_int_t N, double alpha);

void vsub(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, double alpha);
void vsub(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N, double alpha);

void vsub(alglib::complex *vdst, ae_int_t stride_dst, const alglib::complex *vsrc, ae_int_t stride_src, const char *conj_src, ae_int_t n, alglib::complex alpha);
void vsub(alglib::complex *vdst, const alglib::complex *vsrc, ae_int_t N, alglib::complex alpha);

void vmul(double *vdst,  ae_int_t stride_dst, ae_int_t n, double alpha);
void vmul(double *vdst, ae_int_t N, double alpha);

void vmul(alglib::complex *vdst, ae_int_t stride_dst, ae_int_t n, double alpha);
void vmul(alglib::complex *vdst, ae_int_t N, double alpha);

void vmul(alglib::complex *vdst, ae_int_t stride_dst, ae_int_t n, alglib::complex alpha);
void vmul(alglib::complex *vdst, ae_int_t N, alglib::complex alpha);



/********************************************************************
string conversion functions !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
********************************************************************/
/* ************************************************ *******************
문자열 변환 함수 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*************************************************** **************** */

/********************************************************************
1- and 2-dimensional arrays
********************************************************************/
/* ************************************************ *******************
1 차원 및 2 차원 배열
*************************************************** **************** */
class ae_vector_wrapper
{
public:
    ae_vector_wrapper();
    virtual ~ae_vector_wrapper();

    void setlength(ae_int_t iLen);
    ae_int_t length() const;

    void attach_to(alglib_impl::ae_vector *ptr);
    void allocate_own(ae_int_t size, alglib_impl::ae_datatype datatype);
    const alglib_impl::ae_vector* c_ptr() const;
    alglib_impl::ae_vector* c_ptr();
private:
    ae_vector_wrapper(const ae_vector_wrapper &rhs);
    const ae_vector_wrapper& operator=(const ae_vector_wrapper &rhs);
protected:
    //
    // Copies source vector RHS into current object.
    //
    // Current object is considered empty (this function should be
    // called from copy constructor).
    //
    //
    // 소스 벡터 RHS를 현재 객체에 복사합니다.
    //
    // 현재 객체는 비어있는 것으로 간주됩니다 (이 함수는
    // 복사 생성자에서 호출 됨).
    //
    void create(const ae_vector_wrapper &rhs);
    
    //
    // Copies array given by string into current object. Additional
    // parameter DATATYPE contains information about type of the data
    // in S and type of the array to create.
    //
    // Current object is considered empty (this function should be
    // called from copy constructor).
    //
    //
    // string에 지정된 배열을 현재 객체에 복사합니다. 추가
    // DATATYPE 매개 변수에는 데이터 유형에 대한 정보가 들어 있습니다.
    // S로, 작성하는 배열의 형태.
    //
    // 현재 객체는 비어있는 것으로 간주됩니다 (이 함수는
    // 복사 생성자에서 호출 됨).
    //
    void create(const char *s, alglib_impl::ae_datatype datatype);
    
    //
    // Assigns RHS to current object.
    //
    // It has several branches depending on target object status:
    // * in case it is proxy object, data are copied into memory pointed by
    //   proxy. Function checks that source has exactly same size as target
    //   (exception is thrown on failure).
    // * in case it is non-proxy object, data allocated by object are cleared
    //   and a copy of RHS is created in target.
    //
    // NOTE: this function correctly handles assignments of the object to itself.
    //
    //
    // 현재 객체에 RHS를 지정합니다.
    //
    // 대상 객체 상태에 따라 여러 개의 분기가 있습니다.
    // 프록시 객체 인 경우, 데이터가 가리키는 메모리로 복사됩니다.
    //    proxy. 원본이 대상과 정확히 같은 크기인지 기능을 검사합니다.
    //    (실패시 예외가 발생 함).
    // * 비 프록시 객체 인 경우 객체에 의해 할당 된 데이터는 지워진다.
    //    타겟에 RHS 복사본이 생성됩니다.
    //
    // 참고 :이 함수는 객체 자체의 할당을 올바르게 처리합니다.
    //
    void assign(const ae_vector_wrapper &rhs);
    
    alglib_impl::ae_vector *p_vec;
    alglib_impl::ae_vector vec;
};

class boolean_1d_array : public ae_vector_wrapper
{
public:
    boolean_1d_array();
    boolean_1d_array(const char *s);
    boolean_1d_array(const boolean_1d_array &rhs);
    boolean_1d_array(alglib_impl::ae_vector *p);
    const boolean_1d_array& operator=(const boolean_1d_array &rhs);
    virtual ~boolean_1d_array() ;

    const ae_bool& operator()(ae_int_t i) const;
    ae_bool& operator()(ae_int_t i);

    const ae_bool& operator[](ae_int_t i) const;
    ae_bool& operator[](ae_int_t i);

    void setcontent(ae_int_t iLen, const bool *pContent );
    ae_bool* getcontent();
    const ae_bool* getcontent() const;

    std::string tostring() const;
};

class integer_1d_array : public ae_vector_wrapper
{
public:
    integer_1d_array();
    integer_1d_array(const char *s);
    integer_1d_array(const integer_1d_array &rhs);
    integer_1d_array(alglib_impl::ae_vector *p);
    const integer_1d_array& operator=(const integer_1d_array &rhs);
    virtual ~integer_1d_array();

    const ae_int_t& operator()(ae_int_t i) const;
    ae_int_t& operator()(ae_int_t i);

    const ae_int_t& operator[](ae_int_t i) const;
    ae_int_t& operator[](ae_int_t i);

    void setcontent(ae_int_t iLen, const ae_int_t *pContent );

    ae_int_t* getcontent();
    const ae_int_t* getcontent() const;

    std::string tostring() const;
};

class real_1d_array : public ae_vector_wrapper
{
public:
    real_1d_array();
    real_1d_array(const char *s);
    real_1d_array(const real_1d_array &rhs);
    real_1d_array(alglib_impl::ae_vector *p);
    const real_1d_array& operator=(const real_1d_array &rhs);
    virtual ~real_1d_array();

    const double& operator()(ae_int_t i) const;
    double& operator()(ae_int_t i);

    const double& operator[](ae_int_t i) const;
    double& operator[](ae_int_t i);

    void setcontent(ae_int_t iLen, const double *pContent );
    double* getcontent();
    const double* getcontent() const;

    std::string tostring(int dps) const;
};

class complex_1d_array : public ae_vector_wrapper
{
public:
    complex_1d_array();
    complex_1d_array(const char *s);
    complex_1d_array(const complex_1d_array &rhs);
    complex_1d_array(alglib_impl::ae_vector *p);
    const complex_1d_array& operator=(const complex_1d_array &rhs);
    virtual ~complex_1d_array();

    const alglib::complex& operator()(ae_int_t i) const;
    alglib::complex& operator()(ae_int_t i);

    const alglib::complex& operator[](ae_int_t i) const;
    alglib::complex& operator[](ae_int_t i);

    void setcontent(ae_int_t iLen, const alglib::complex *pContent );
    alglib::complex* getcontent();
    const alglib::complex* getcontent() const;

    std::string tostring(int dps) const;
};

class ae_matrix_wrapper
{
public:
    ae_matrix_wrapper();
    virtual ~ae_matrix_wrapper();
    const ae_matrix_wrapper& operator=(const ae_matrix_wrapper &rhs);

    void setlength(ae_int_t rows, ae_int_t cols);
    ae_int_t rows() const;
    ae_int_t cols() const;
    bool isempty() const;
	ae_int_t getstride() const;

    void attach_to(alglib_impl::ae_matrix *ptr);
    void allocate_own(ae_int_t rows, ae_int_t cols, alglib_impl::ae_datatype datatype);
    const alglib_impl::ae_matrix* c_ptr() const;
    alglib_impl::ae_matrix* c_ptr();
private:
    ae_matrix_wrapper(const ae_matrix_wrapper &rhs);
protected:
    //
    // Copies source matrix RHS into current object.
    //
    // Current object is considered empty (this function should be
    // called from copy constructor).
    //
    //
    // 소스 행렬 RHS를 현재 객체에 복사합니다.
    //
    // 현재 객체는 비어있는 것으로 간주됩니다 (이 함수는
    // 복사 생성자에서 호출 됨).
    //
    void create(const ae_matrix_wrapper &rhs);
    
    //
    // Copies array given by string into current object. Additional
    // parameter DATATYPE contains information about type of the data
    // in S and type of the array to create.
    //
    // Current object is considered empty (this function should be
    // called from copy constructor).
    //
    //
    // string에 지정된 배열을 현재 객체에 복사합니다. 추가
    // DATATYPE 매개 변수에는 데이터 유형에 대한 정보가 들어 있습니다.
    // S로, 작성하는 배열의 형태.
    //
    // 현재 객체는 비어있는 것으로 간주됩니다 (이 함수는
    // 복사 생성자에서 호출 됨).
    //
    void create(const char *s, alglib_impl::ae_datatype datatype);
    
    //
    // Assigns RHS to current object.
    //
    // It has several branches depending on target object status:
    // * in case it is proxy object, data are copied into memory pointed by
    //   proxy. Function checks that source has exactly same size as target
    //   (exception is thrown on failure).
    // * in case it is non-proxy object, data allocated by object are cleared
    //   and a copy of RHS is created in target.
    //
    // NOTE: this function correctly handles assignments of the object to itself.
    //
    //
    // 현재 객체에 RHS를 지정합니다.
    //
    // 대상 객체 상태에 따라 여러 개의 분기가 있습니다.
    // 프록시 객체 인 경우, 데이터가 가리키는 메모리로 복사됩니다.
    //    proxy. 원본이 대상과 정확히 같은 크기인지 기능을 검사합니다.
    //    (실패시 예외가 발생 함).
    // * 비 프록시 객체 인 경우 객체에 의해 할당 된 데이터는 지워진다.
    //    타겟에 RHS 복사본이 생성됩니다.
    //
    // 참고 :이 함수는 객체 자체의 할당을 올바르게 처리합니다.
    //
    void assign(const ae_matrix_wrapper &rhs);
    
    alglib_impl::ae_matrix *p_mat;
    alglib_impl::ae_matrix mat;
};

class boolean_2d_array : public ae_matrix_wrapper
{
public:
    boolean_2d_array();
    boolean_2d_array(const boolean_2d_array &rhs);
    boolean_2d_array(alglib_impl::ae_matrix *p);
    boolean_2d_array(const char *s);
    virtual ~boolean_2d_array();

    const ae_bool& operator()(ae_int_t i, ae_int_t j) const;
    ae_bool& operator()(ae_int_t i, ae_int_t j);

    const ae_bool* operator[](ae_int_t i) const;
    ae_bool* operator[](ae_int_t i);
    
    void setcontent(ae_int_t irows, ae_int_t icols, const bool *pContent );
    
    std::string tostring() const ;
};

class integer_2d_array : public ae_matrix_wrapper
{
public:
    integer_2d_array();
    integer_2d_array(const integer_2d_array &rhs);
    integer_2d_array(alglib_impl::ae_matrix *p);
    integer_2d_array(const char *s);
    virtual ~integer_2d_array();

    const ae_int_t& operator()(ae_int_t i, ae_int_t j) const;
    ae_int_t& operator()(ae_int_t i, ae_int_t j);

    const ae_int_t* operator[](ae_int_t i) const;
    ae_int_t* operator[](ae_int_t i);

    void setcontent(ae_int_t irows, ae_int_t icols, const ae_int_t *pContent );
    
    std::string tostring() const;
};

class real_2d_array : public ae_matrix_wrapper
{
public:
    real_2d_array();
    real_2d_array(const real_2d_array &rhs);
    real_2d_array(alglib_impl::ae_matrix *p);
    real_2d_array(const char *s);
    virtual ~real_2d_array();

    const double& operator()(ae_int_t i, ae_int_t j) const;
    double& operator()(ae_int_t i, ae_int_t j);

    const double* operator[](ae_int_t i) const;
    double* operator[](ae_int_t i);

    void setcontent(ae_int_t irows, ae_int_t icols, const double *pContent );

    std::string tostring(int dps) const;
};

class complex_2d_array : public ae_matrix_wrapper
{
public:
    complex_2d_array();
    complex_2d_array(const complex_2d_array &rhs);
    complex_2d_array(alglib_impl::ae_matrix *p);
    complex_2d_array(const char *s);
    virtual ~complex_2d_array();

    const alglib::complex& operator()(ae_int_t i, ae_int_t j) const;
    alglib::complex& operator()(ae_int_t i, ae_int_t j);

    const alglib::complex* operator[](ae_int_t i) const;
    alglib::complex* operator[](ae_int_t i);

    void setcontent(ae_int_t irows, ae_int_t icols, const alglib::complex *pContent );

    std::string tostring(int dps) const;
};



/********************************************************************
dataset information.

can store regression dataset, classification dataset, or non-labeled
task:
* nout==0 means non-labeled task (clustering, for example)
* nout>0 && nclasses==0 means regression task
* nout>0 && nclasses>0 means classification task
********************************************************************/
/* ************************************************ *******************
데이터 세트 정보.
회귀 데이터 집합, 분류 데이터 집합 또는 레이블이 지정되지 않은 데이터를 저장할 수 있습니다.
태스크:
* nout == 0은 레이블이 지정되지 않은 작업을 의미합니다 (예 : 클러스터링).
* nout> 0 && nclasses == 0은 회귀 작업을 의미합니다.
* nout> 0 && nclasses> 0은 분류 작업을 의미합니다.
*************************************************** **************** */
/*class dataset
{
public:
    dataset():nin(0), nout(0), nclasses(0), trnsize(0), valsize(0), tstsize(0), totalsize(0){};

    int nin, nout, nclasses;

    int trnsize;
    int valsize;
    int tstsize;
    int totalsize;

    alglib::real_2d_array trn;
    alglib::real_2d_array val;
    alglib::real_2d_array tst;
    alglib::real_2d_array all;
};

bool opendataset(std::string file, dataset *pdataset);

//
// internal functions
//
std::string strtolower(const std::string &s);
bool readstrings(std::string file, std::list<std::string> *pOutput);
bool readstrings(std::string file, std::list<std::string> *pOutput, std::string comment);
void explodestring(std::string s, char sep, std::vector<std::string> *pOutput);
std::string xtrim(std::string s);*/

/********************************************************************
Constants and functions introduced for compatibility with AlgoPascal
********************************************************************/
/* ************************************************ *******************
AlgoPascal과의 호환성을 위해 도입 된 상수 및 함수
*************************************************** **************** */
extern const double machineepsilon;
extern const double maxrealnumber;
extern const double minrealnumber;
extern const double fp_nan;
extern const double fp_posinf;
extern const double fp_neginf;
extern const ae_int_t endianness;

int sign(double x);
double randomreal();
ae_int_t randominteger(ae_int_t maxv);
int round(double x);
int trunc(double x);
int ifloor(double x);
int iceil(double x);
double pi();
double sqr(double x);
int maxint(int m1, int m2);
int minint(int m1, int m2);
double maxreal(double m1, double m2);
double minreal(double m1, double m2);

bool fp_eq(double v1, double v2);
bool fp_neq(double v1, double v2);
bool fp_less(double v1, double v2);
bool fp_less_eq(double v1, double v2);
bool fp_greater(double v1, double v2);
bool fp_greater_eq(double v1, double v2);

bool fp_isnan(double x);
bool fp_isposinf(double x);
bool fp_isneginf(double x);
bool fp_isinf(double x);
bool fp_isfinite(double x);


}//namespace alglib


/////////////////////////////////////////////////////////////////////////
//
// THIS SECTIONS CONTAINS DECLARATIONS FOR OPTIMIZED LINEAR ALGEBRA CODES
// IT IS SHARED BETWEEN C++ AND PURE C LIBRARIES
//
/////////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 최적화 된 선형 대수 코드의 선언이 포함되어 있습니다.
// C ++과 순수 C 라이브러리간에 공유됩니다.
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#define ALGLIB_INTERCEPTS_ABLAS
void _ialglib_vzero(ae_int_t n, double *p, ae_int_t stride);
void _ialglib_vzero_complex(ae_int_t n, ae_complex *p, ae_int_t stride);
void _ialglib_vcopy(ae_int_t n, const double *a, ae_int_t stridea, double *b, ae_int_t strideb);
void _ialglib_vcopy_complex(ae_int_t n, const ae_complex *a, ae_int_t stridea, double *b, ae_int_t strideb, const char *conj);
void _ialglib_vcopy_dcomplex(ae_int_t n, const double *a, ae_int_t stridea, double *b, ae_int_t strideb, const char *conj);
void _ialglib_mcopyblock(ae_int_t m, ae_int_t n, const double *a, ae_int_t op, ae_int_t stride, double *b);
void _ialglib_mcopyunblock(ae_int_t m, ae_int_t n, const double *a, ae_int_t op, double *b, ae_int_t stride);
void _ialglib_mcopyblock_complex(ae_int_t m, ae_int_t n, const ae_complex *a, ae_int_t op, ae_int_t stride, double *b);
void _ialglib_mcopyunblock_complex(ae_int_t m, ae_int_t n, const double *a, ae_int_t op, ae_complex* b, ae_int_t stride);

ae_bool _ialglib_i_rmatrixgemmf(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     ae_matrix *a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     ae_matrix *b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     ae_matrix *c,
     ae_int_t ic,
     ae_int_t jc);
ae_bool _ialglib_i_cmatrixgemmf(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     ae_complex alpha,
     ae_matrix *a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     ae_matrix *b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     ae_complex beta,
     ae_matrix *c,
     ae_int_t ic,
     ae_int_t jc);
ae_bool _ialglib_i_cmatrixrighttrsmf(ae_int_t m,
     ae_int_t n,
     ae_matrix *a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     ae_matrix *x,
     ae_int_t i2,
     ae_int_t j2);
ae_bool _ialglib_i_rmatrixrighttrsmf(ae_int_t m,
     ae_int_t n,
     ae_matrix *a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     ae_matrix *x,
     ae_int_t i2,
     ae_int_t j2);
ae_bool _ialglib_i_cmatrixlefttrsmf(ae_int_t m,
     ae_int_t n,
     ae_matrix *a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     ae_matrix *x,
     ae_int_t i2,
     ae_int_t j2);
ae_bool _ialglib_i_rmatrixlefttrsmf(ae_int_t m,
     ae_int_t n,
     ae_matrix *a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     ae_matrix *x,
     ae_int_t i2,
     ae_int_t j2);
ae_bool _ialglib_i_cmatrixsyrkf(ae_int_t n,
     ae_int_t k,
     double alpha,
     ae_matrix *a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     ae_matrix *c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper);
ae_bool _ialglib_i_rmatrixsyrkf(ae_int_t n,
     ae_int_t k,
     double alpha,
     ae_matrix *a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     ae_matrix *c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper);
ae_bool _ialglib_i_cmatrixrank1f(ae_int_t m,
     ae_int_t n,
     ae_matrix *a,
     ae_int_t ia,
     ae_int_t ja,
     ae_vector *u,
     ae_int_t uoffs,
     ae_vector *v,
     ae_int_t voffs);
ae_bool _ialglib_i_rmatrixrank1f(ae_int_t m,
     ae_int_t n,
     ae_matrix *a,
     ae_int_t ia,
     ae_int_t ja,
     ae_vector *u,
     ae_int_t uoffs,
     ae_vector *v,
     ae_int_t voffs);



}


/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS PARALLEL SUBROUTINES
//
/////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 여러 하위 그룹이 포함되어 있습니다.
//
// //////////////////////////////////////////////////////////////////////

namespace alglib_impl
{

}


#endif

