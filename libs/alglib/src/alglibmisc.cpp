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
#include "stdafx.h"
#include "alglibmisc.h"

// disable some irrelevant warnings
#if (AE_COMPILER==AE_MSVC)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4702)
#pragma warning(disable:4996)
#endif
using namespace std;

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{


/*************************************************************************
Portable high quality random number generator state.
Initialized with HQRNDRandomize() or HQRNDSeed().

Fields:
    S1, S2      -   seed values
    V           -   precomputed value
    MagicV      -   'magic' value used to determine whether State structure
                    was correctly initialized.
*************************************************************************/
/************************************************* *************************
휴대용 고품질의 난수 생성기 상태.
HQRNDRandomize () 또는 HQRNDSeed ()로 초기화됩니다.
전지:
    S1, S2 - 시드 값
    V - 사전 계산 된 값
    MagicV - 국가 구조의 결정 여부를 결정하는 데 사용되는 '마법'값
                    올바르게 초기화되었습니다.
**************************************************************************/
_hqrndstate_owner::_hqrndstate_owner()
{
    p_struct = (alglib_impl::hqrndstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::hqrndstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_hqrndstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_hqrndstate_owner::_hqrndstate_owner(const _hqrndstate_owner &rhs)
{
    p_struct = (alglib_impl::hqrndstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::hqrndstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_hqrndstate_init_copy(p_struct, const_cast<alglib_impl::hqrndstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_hqrndstate_owner& _hqrndstate_owner::operator=(const _hqrndstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_hqrndstate_clear(p_struct);
    if( !alglib_impl::_hqrndstate_init_copy(p_struct, const_cast<alglib_impl::hqrndstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_hqrndstate_owner::~_hqrndstate_owner()
{
    alglib_impl::_hqrndstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::hqrndstate* _hqrndstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::hqrndstate* _hqrndstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::hqrndstate*>(p_struct);
}
hqrndstate::hqrndstate() : _hqrndstate_owner() 
{
}

hqrndstate::hqrndstate(const hqrndstate &rhs):_hqrndstate_owner(rhs) 
{
}

hqrndstate& hqrndstate::operator=(const hqrndstate &rhs)
{
    if( this==&rhs )
        return *this;
    _hqrndstate_owner::operator=(rhs);
    return *this;
}

hqrndstate::~hqrndstate()
{
}

/*************************************************************************
HQRNDState  initialization  with  random  values  which come from standard
RNG.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
HQRNDState 초기화 (표준에서 오는 임의의 값 사용)
RNG.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndrandomize(hqrndstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hqrndrandomize(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
HQRNDState initialization with seed values

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
시드 값을 사용하는 HQRNDState 초기화
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndseed(const ae_int_t s1, const ae_int_t s2, hqrndstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hqrndseed(s1, s2, const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function generates random real number in (0,1),
not including interval boundaries

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 (0,1)에 임의의 실수를 생성합니다.
간격 경계를 포함하지 않음
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
double hqrnduniformr(const hqrndstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        double result = alglib_impl::hqrnduniformr(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<double*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function generates random integer number in [0, N)

1. State structure must be initialized with HQRNDRandomize() or HQRNDSeed()
2. N can be any positive number except for very large numbers:
   * close to 2^31 on 32-bit systems
   * close to 2^62 on 64-bit systems
   An exception will be generated if N is too large.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 [0, N]에 임의의 정수를 생성하고,
1. 상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화되어야합니다.
2. N은 매우 큰 숫자를 제외하고는 양수 일 수 있습니다.
   * 32 비트 시스템에서 2 ^ 31에 가깝습니다.
   * 64 비트 시스템에서는 2 ^ 62에 가깝습니다.
   N이 너무 큰 경우 예외가 생성됩니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
ae_int_t hqrnduniformi(const hqrndstate &state, const ae_int_t n)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::hqrnduniformi(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), n, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Random number generator: normal numbers

This function generates one random number from normal distribution.
Its performance is equal to that of HQRNDNormal2()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : 정상 수
이 함수는 정규 분포에서 하나의 난수를 생성합니다.
그 성능은 HQRNDNormal2 ()의 성능과 같습니다.
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
double hqrndnormal(const hqrndstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        double result = alglib_impl::hqrndnormal(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<double*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Random number generator: random X and Y such that X^2+Y^2=1

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : X ^ 2 + Y ^ 2 = 1과 같은 임의의 X와 Y
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndunit2(const hqrndstate &state, double &x, double &y)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hqrndunit2(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), &x, &y, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Random number generator: normal numbers

This function generates two independent random numbers from normal
distribution. Its performance is equal to that of HQRNDNormal()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : 정상 수
이 함수는 법선으로부터 2 개의 독립 난수를 생성합니다.
분포. 그 성능은 HQRNDNormal ()과 동일합니다.
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndnormal2(const hqrndstate &state, double &x1, double &x2)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hqrndnormal2(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), &x1, &x2, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Random number generator: exponential distribution

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 11.08.2007 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : 지수 분포
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 2007 년 11 월 8 일 Bochkanov Sergey
**************************************************************************/
double hqrndexponential(const hqrndstate &state, const double lambdav)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        double result = alglib_impl::hqrndexponential(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), lambdav, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<double*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function generates  random number from discrete distribution given by
finite sample X.

INPUT PARAMETERS
    State   -   high quality random number generator, must be
                initialized with HQRNDRandomize() or HQRNDSeed().
        X   -   finite sample
        N   -   number of elements to use, N>=1

RESULT
    this function returns one of the X[i] for random i=0..N-1

  -- ALGLIB --
     Copyright 08.11.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는에 의해 주어진 이산 분포로부터 난수를 생성합니다.
유한 샘플 X
입력 매개 변수
    상태 - 고품질 난수 생성기, 있어야합니다.
                HQRNDRandomize () 또는 HQRNDSeed ()로 초기화됩니다.
        X - 유한 샘플
        N - 사용할 요소 수, N> = 1
결과
    이 함수는 random i = 0..N-1에 대해 X [i] 중 하나를 반환합니다.
  - ALGLIB -
     저작권 08.11.2011 Bochkanov Sergey
**************************************************************************/
double hqrnddiscrete(const hqrndstate &state, const real_1d_array &x, const ae_int_t n)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        double result = alglib_impl::hqrnddiscrete(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), n, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<double*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function generates random number from continuous  distribution  given
by finite sample X.

INPUT PARAMETERS
    State   -   high quality random number generator, must be
                initialized with HQRNDRandomize() or HQRNDSeed().
        X   -   finite sample, array[N] (can be larger, in this  case only
                leading N elements are used). THIS ARRAY MUST BE SORTED BY
                ASCENDING.
        N   -   number of elements to use, N>=1

RESULT
    this function returns random number from continuous distribution which
    tries to approximate X as mush as possible. min(X)<=Result<=max(X).

  -- ALGLIB --
     Copyright 08.11.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 주어진 연속 분포로부터 난수를 생성합니다.
유한 샘플 X로.
입력 매개 변수
    상태 - 고품질 난수 생성기, 있어야합니다.
                HQRNDRandomize () 또는 HQRNDSeed ()로 초기화됩니다.
        X - 유한 샘플, 배열 [N] (이 경우에만 더 클 수 있습니다.
                선두의 N 요소가 사용된다). 이 배열은에 의해 정렬되어야합니다
                승천.
        N - 사용할 요소 수, N> = 1
결과
    이 함수는 연속적인 분포에서 난수를 반환한다.
    X를 최대한 근사해 보려고합니다. min (X) <= Result <= max (X).
  - ALGLIB -
     저작권 08.11.2011 Bochkanov Sergey
**************************************************************************/
double hqrndcontinuous(const hqrndstate &state, const real_1d_array &x, const ae_int_t n)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        double result = alglib_impl::hqrndcontinuous(const_cast<alglib_impl::hqrndstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), n, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<double*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************

*************************************************************************/
_kdtree_owner::_kdtree_owner()
{
    p_struct = (alglib_impl::kdtree*)alglib_impl::ae_malloc(sizeof(alglib_impl::kdtree), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_kdtree_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_kdtree_owner::_kdtree_owner(const _kdtree_owner &rhs)
{
    p_struct = (alglib_impl::kdtree*)alglib_impl::ae_malloc(sizeof(alglib_impl::kdtree), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_kdtree_init_copy(p_struct, const_cast<alglib_impl::kdtree*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_kdtree_owner& _kdtree_owner::operator=(const _kdtree_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_kdtree_clear(p_struct);
    if( !alglib_impl::_kdtree_init_copy(p_struct, const_cast<alglib_impl::kdtree*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_kdtree_owner::~_kdtree_owner()
{
    alglib_impl::_kdtree_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::kdtree* _kdtree_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::kdtree* _kdtree_owner::c_ptr() const
{
    return const_cast<alglib_impl::kdtree*>(p_struct);
}
kdtree::kdtree() : _kdtree_owner() 
{
}

kdtree::kdtree(const kdtree &rhs):_kdtree_owner(rhs) 
{
}

kdtree& kdtree::operator=(const kdtree &rhs)
{
    if( this==&rhs )
        return *this;
    _kdtree_owner::operator=(rhs);
    return *this;
}

kdtree::~kdtree()
{
}


/*************************************************************************
This function serializes data structure to string.

Important properties of s_out:
* it contains alphanumeric characters, dots, underscores, minus signs
* these symbols are grouped into words, which are separated by spaces
  and Windows-style (CR+LF) newlines
* although  serializer  uses  spaces and CR+LF as separators, you can 
  replace any separator character by arbitrary combination of spaces,
  tabs, Windows or Unix newlines. It allows flexible reformatting  of
  the  string  in  case you want to include it into text or XML file. 
  But you should not insert separators into the middle of the "words"
  nor you should change case of letters.
* s_out can be freely moved between 32-bit and 64-bit systems, little
  and big endian machines, and so on. You can serialize structure  on
  32-bit machine and unserialize it on 64-bit one (or vice versa), or
  serialize  it  on  SPARC  and  unserialize  on  x86.  You  can also 
  serialize  it  in  C++ version of ALGLIB and unserialize in C# one, 
  and vice versa.
*************************************************************************/
/**************************************************************************
이 함수는 데이터 구조를 문자열로 serialize합니다.
s_out의 중요한 속성 :
* 영숫자, 점, 밑줄, 빼기 부호가 포함되어 있습니다.
*이 기호는 공백으로 구분 된 단어로 그룹화됩니다.
  및 Windows 스타일 (CR + LF) 개행
* serializer는 공백과 CR + LF를 구분 기호로 사용하지만 
  공백을 임의로 조합하여 구분 문자를 대체하십시오.
  탭, Windows 또는 Unix 개행. 유연한 재 포맷이 가능합니다.
  텍스트 또는 XML 파일에 포함하려는 경우의 문자열입니다. 
  그러나 "단어"의 중간에 구분 기호를 삽입해서는 안됩니다.
  편지의 대소 문자를 변경해서는 안됩니다.
* s_out은 32 비트와 64 비트 시스템 사이에서 자유롭게 이동할 수 있습니다.
  빅 엔디안 머신 등이 있습니다. 구조를 직렬화 할 수 있습니다.
  32 비트 컴퓨터에서 실행하고 64 비트 컴퓨터에서 직렬화 해제하거나 그 반대의 경우
  SPARC에서 직렬화하고 x86에서 직렬화 해제하십시오. 당신은 또한 수
  ALGLIB의 C ++ 버전에서 직렬화하고 C # 하나에서 직렬화 해제하십시오. 
  그 반대.
**************************************************************************/
void kdtreeserialize(kdtree &obj, std::string &s_out)
{
    alglib_impl::ae_state state;
    alglib_impl::ae_serializer serializer;
    alglib_impl::ae_int_t ssize;

    alglib_impl::ae_state_init(&state);
    try
    {
        alglib_impl::ae_serializer_init(&serializer);
        alglib_impl::ae_serializer_alloc_start(&serializer);
        alglib_impl::kdtreealloc(&serializer, obj.c_ptr(), &state);
        ssize = alglib_impl::ae_serializer_get_alloc_size(&serializer);
        s_out.clear();
        s_out.reserve((size_t)(ssize+1));
        alglib_impl::ae_serializer_sstart_str(&serializer, &s_out);
        alglib_impl::kdtreeserialize(&serializer, obj.c_ptr(), &state);
        alglib_impl::ae_serializer_stop(&serializer);
        if( s_out.length()>(size_t)ssize )
            throw ap_error("ALGLIB: serialization integrity error");
        alglib_impl::ae_serializer_clear(&serializer);
        alglib_impl::ae_state_clear(&state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(state.error_msg);
    }
}
/*************************************************************************
This function unserializes data structure from string.
*************************************************************************/
/**************************************************************************
이 함수는 문자열에서 데이터 구조를 unserializes.
**************************************************************************/
void kdtreeunserialize(std::string &s_in, kdtree &obj)
{
    alglib_impl::ae_state state;
    alglib_impl::ae_serializer serializer;

    alglib_impl::ae_state_init(&state);
    try
    {
        alglib_impl::ae_serializer_init(&serializer);
        alglib_impl::ae_serializer_ustart_str(&serializer, &s_in);
        alglib_impl::kdtreeunserialize(&serializer, obj.c_ptr(), &state);
        alglib_impl::ae_serializer_stop(&serializer);
        alglib_impl::ae_serializer_clear(&serializer);
        alglib_impl::ae_state_clear(&state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(state.error_msg);
    }
}

/*************************************************************************
KD-tree creation

This subroutine creates KD-tree from set of X-values and optional Y-values

INPUT PARAMETERS
    XY      -   dataset, array[0..N-1,0..NX+NY-1].
                one row corresponds to one point.
                first NX columns contain X-values, next NY (NY may be zero)
                columns may contain associated Y-values
    N       -   number of points, N>=0.
    NX      -   space dimension, NX>=1.
    NY      -   number of optional Y-values, NY>=0.
    NormType-   norm type:
                * 0 denotes infinity-norm
                * 1 denotes 1-norm
                * 2 denotes 2-norm (Euclidean norm)

OUTPUT PARAMETERS
    KDT     -   KD-tree


NOTES

1. KD-tree  creation  have O(N*logN) complexity and O(N*(2*NX+NY))  memory
   requirements.
2. Although KD-trees may be used with any combination of N  and  NX,  they
   are more efficient than brute-force search only when N >> 4^NX. So they
   are most useful in low-dimensional tasks (NX=2, NX=3). NX=1  is another
   inefficient case, because  simple  binary  search  (without  additional
   structures) is much more efficient in such tasks than KD-trees.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
KD- 트리 생성
이 서브 루틴은 X 값의 집합과 선택적인 Y 값으로부터 KD 트리를 생성합니다
입력 매개 변수
    XY-dataset, array [0..N-1,0..NX + NY-1].
                한 행은 한 점에 해당합니다.
                첫 번째 NX 열에는 X 값이 포함되고 다음 NY (NY는 0이 될 수 있음)
                열은 연관된 Y 값을 포함 할 수 있습니다.
    N - 포인트 수, N> = 0.
    NX - 공간 차원, NX> = 1.
    NY - 선택적 Y 값의 수, NY> = 0.
    NormType- 노름 유형 :
                * 0은 무한대 - 표준을 나타냅니다.
                * 1은 1- 노름을 나타냅니다.
                * 2는 2- 노름 (유클리드 기준)
출력 매개 변수
    KDT - KD 트리
노트
1. KD 트리 생성은 O (N * logN) 복잡도와 O (N * (2 * NX + NY)) 메모리를 갖는다.
   요구 사항.
2. KD- 나무는 N과 NX의 조합과 함께 사용될 수 있지만,
   N >> 4 ^ NX 일 때만 무차별 강제 검색보다 더 효율적입니다. 그래서 그들은
   저 차원 작업 (NX = 2, NX = 3)에서 가장 유용합니다. NX = 1은 또 다른 것입니다.
   비효율적 인 경우, 간단한 이진 검색 (추가하지 않음
   구조)는 KD- 나무보다 훨씬 효율적입니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreebuild(const real_2d_array &xy, const ae_int_t n, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreebuild(const_cast<alglib_impl::ae_matrix*>(xy.c_ptr()), n, nx, ny, normtype, const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
KD-tree creation

This subroutine creates KD-tree from set of X-values and optional Y-values

INPUT PARAMETERS
    XY      -   dataset, array[0..N-1,0..NX+NY-1].
                one row corresponds to one point.
                first NX columns contain X-values, next NY (NY may be zero)
                columns may contain associated Y-values
    N       -   number of points, N>=0.
    NX      -   space dimension, NX>=1.
    NY      -   number of optional Y-values, NY>=0.
    NormType-   norm type:
                * 0 denotes infinity-norm
                * 1 denotes 1-norm
                * 2 denotes 2-norm (Euclidean norm)

OUTPUT PARAMETERS
    KDT     -   KD-tree


NOTES

1. KD-tree  creation  have O(N*logN) complexity and O(N*(2*NX+NY))  memory
   requirements.
2. Although KD-trees may be used with any combination of N  and  NX,  they
   are more efficient than brute-force search only when N >> 4^NX. So they
   are most useful in low-dimensional tasks (NX=2, NX=3). NX=1  is another
   inefficient case, because  simple  binary  search  (without  additional
   structures) is much more efficient in such tasks than KD-trees.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
KD- 트리 생성
이 서브 루틴은 X 값의 집합과 선택적인 Y 값으로부터 KD 트리를 생성합니다
입력 매개 변수
    XY-dataset, array [0..N-1,0..NX + NY-1].
                한 행은 한 점에 해당합니다.
                첫 번째 NX 열에는 X 값이 포함되고 다음 NY (NY는 0이 될 수 있음)
                열은 연관된 Y 값을 포함 할 수 있습니다.
    N - 포인트 수, N> = 0.
    NX - 공간 차원, NX> = 1.
    NY - 선택적 Y 값의 수, NY> = 0.
    NormType- 노름 유형 :
                * 0은 무한대 - 표준을 나타냅니다.
                * 1은 1- 노름을 나타냅니다.
                * 2는 2- 노름 (유클리드 기준)
출력 매개 변수
    KDT - KD 트리
노트
1. KD 트리 생성은 O (N * logN) 복잡도와 O (N * (2 * NX + NY)) 메모리를 갖는다.
   요구 사항.
2. KD- 나무는 N과 NX의 조합과 함께 사용될 수 있지만,
   N >> 4 ^ NX 일 때만 무차별 강제 검색보다 더 효율적입니다. 그래서 그들은
   저 차원 작업 (NX = 2, NX = 3)에서 가장 유용합니다. NX = 1은 또 다른 것입니다.
   비효율적 인 경우, 간단한 이진 검색 (추가하지 않음
   구조)는 KD- 나무보다 훨씬 효율적입니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreebuild(const real_2d_array &xy, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = xy.rows();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreebuild(const_cast<alglib_impl::ae_matrix*>(xy.c_ptr()), n, nx, ny, normtype, const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
KD-tree creation

This  subroutine  creates  KD-tree  from set of X-values, integer tags and
optional Y-values

INPUT PARAMETERS
    XY      -   dataset, array[0..N-1,0..NX+NY-1].
                one row corresponds to one point.
                first NX columns contain X-values, next NY (NY may be zero)
                columns may contain associated Y-values
    Tags    -   tags, array[0..N-1], contains integer tags associated
                with points.
    N       -   number of points, N>=0
    NX      -   space dimension, NX>=1.
    NY      -   number of optional Y-values, NY>=0.
    NormType-   norm type:
                * 0 denotes infinity-norm
                * 1 denotes 1-norm
                * 2 denotes 2-norm (Euclidean norm)

OUTPUT PARAMETERS
    KDT     -   KD-tree

NOTES

1. KD-tree  creation  have O(N*logN) complexity and O(N*(2*NX+NY))  memory
   requirements.
2. Although KD-trees may be used with any combination of N  and  NX,  they
   are more efficient than brute-force search only when N >> 4^NX. So they
   are most useful in low-dimensional tasks (NX=2, NX=3). NX=1  is another
   inefficient case, because  simple  binary  search  (without  additional
   structures) is much more efficient in such tasks than KD-trees.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
KD- 트리 생성
이 서브 루틴은 일련의 X 값, 정수 태그 및
선택적 Y 값
입력 매개 변수
    XY-dataset, array [0..N-1,0..NX + NY-1].
                한 행은 한 점에 해당합니다.
                첫 번째 NX 열에는 X 값이 포함되고 다음 NY (NY는 0이 될 수 있음)
                열은 연관된 Y 값을 포함 할 수 있습니다.
    태그 - 태그, 배열 [0..N-1], 관련 정수 태그 포함
                포인트로.
    N - 포인트 수, N> = 0
    NX - 공간 차원, NX> = 1.
    NY - 선택적 Y 값의 수, NY> = 0.
    NormType- 노름 유형 :
                * 0은 무한대 - 표준을 나타냅니다.
                * 1은 1- 노름을 나타냅니다.
                * 2는 2- 노름 (유클리드 기준)
출력 매개 변수
    KDT - KD 트리
노트
1. KD 트리 생성은 O (N * logN) 복잡도와 O (N * (2 * NX + NY)) 메모리를 갖는다.
   요구 사항.
2. KD- 나무는 N과 NX의 조합과 함께 사용될 수 있지만,
   N >> 4 ^ NX 일 때만 무차별 강제 검색보다 더 효율적입니다. 그래서 그들은
   저 차원 작업 (NX = 2, NX = 3)에서 가장 유용합니다. NX = 1은 또 다른 것입니다.
   비효율적 인 경우, 간단한 이진 검색 (추가하지 않음
   구조)는 KD- 나무보다 훨씬 효율적입니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreebuildtagged(const real_2d_array &xy, const integer_1d_array &tags, const ae_int_t n, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreebuildtagged(const_cast<alglib_impl::ae_matrix*>(xy.c_ptr()), const_cast<alglib_impl::ae_vector*>(tags.c_ptr()), n, nx, ny, normtype, const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
KD-tree creation

This  subroutine  creates  KD-tree  from set of X-values, integer tags and
optional Y-values

INPUT PARAMETERS
    XY      -   dataset, array[0..N-1,0..NX+NY-1].
                one row corresponds to one point.
                first NX columns contain X-values, next NY (NY may be zero)
                columns may contain associated Y-values
    Tags    -   tags, array[0..N-1], contains integer tags associated
                with points.
    N       -   number of points, N>=0
    NX      -   space dimension, NX>=1.
    NY      -   number of optional Y-values, NY>=0.
    NormType-   norm type:
                * 0 denotes infinity-norm
                * 1 denotes 1-norm
                * 2 denotes 2-norm (Euclidean norm)

OUTPUT PARAMETERS
    KDT     -   KD-tree

NOTES

1. KD-tree  creation  have O(N*logN) complexity and O(N*(2*NX+NY))  memory
   requirements.
2. Although KD-trees may be used with any combination of N  and  NX,  they
   are more efficient than brute-force search only when N >> 4^NX. So they
   are most useful in low-dimensional tasks (NX=2, NX=3). NX=1  is another
   inefficient case, because  simple  binary  search  (without  additional
   structures) is much more efficient in such tasks than KD-trees.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
KD- 트리 생성
이 서브 루틴은 일련의 X 값, 정수 태그 및
선택적 Y 값
입력 매개 변수
    XY-dataset, array [0..N-1,0..NX + NY-1].
                한 행은 한 점에 해당합니다.
                첫 번째 NX 열에는 X 값이 포함되고 다음 NY (NY는 0이 될 수 있음)
                열은 연관된 Y 값을 포함 할 수 있습니다.
    태그 - 태그, 배열 [0..N-1], 관련 정수 태그 포함
                포인트로.
    N - 포인트 수, N> = 0
    NX - 공간 차원, NX> = 1.
    NY - 선택적 Y 값의 수, NY> = 0.
    NormType- 노름 유형 :
                * 0은 무한대 - 표준을 나타냅니다.
                * 1은 1- 노름을 나타냅니다.
                * 2는 2- 노름 (유클리드 기준)
출력 매개 변수
    KDT - KD 트리
노트
1. KD 트리 생성은 O (N * logN) 복잡도와 O (N * (2 * NX + NY)) 메모리를 갖는다.
   요구 사항.
2. KD- 나무는 N과 NX의 조합과 함께 사용될 수 있지만,
   N >> 4 ^ NX 일 때만 무차별 강제 검색보다 더 효율적입니다. 그래서 그들은
   저 차원 작업 (NX = 2, NX = 3)에서 가장 유용합니다. NX = 1은 또 다른 것입니다.
   비효율적 인 경우, 간단한 이진 검색 (추가하지 않음
   구조)는 KD- 나무보다 훨씬 효율적입니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreebuildtagged(const real_2d_array &xy, const integer_1d_array &tags, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;
    if( (xy.rows()!=tags.length()))
        throw ap_error("Error while calling 'kdtreebuildtagged': looks like one of arguments has wrong size");
    n = xy.rows();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreebuildtagged(const_cast<alglib_impl::ae_matrix*>(xy.c_ptr()), const_cast<alglib_impl::ae_vector*>(tags.c_ptr()), n, nx, ny, normtype, const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
K-NN query: K nearest neighbors

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    K           -   number of neighbors to return, K>=1
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True

RESULT
    number of actual neighbors found (either K or N, if K>N).

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
these results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
K-NN 질의 : K 개의 가장 가까운 이웃
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    K - 반환 할 이웃 수, K> = 1
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
결과
    발견 된 실제 이웃의 수 (K> N 인 경우 K 또는 N 중 하나)
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
이러한 결과는 다음과 같습니다.
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k, const bool selfmatch)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::kdtreequeryknn(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), k, selfmatch, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
K-NN query: K nearest neighbors

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    K           -   number of neighbors to return, K>=1
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True

RESULT
    number of actual neighbors found (either K or N, if K>N).

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
these results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
K-NN 질의 : K 개의 가장 가까운 이웃
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    K - 반환 할 이웃 수, K> = 1
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
결과
    발견 된 실제 이웃의 수 (K> N 인 경우 K 또는 N 중 하나)
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
이러한 결과는 다음과 같습니다.
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k)
{
    alglib_impl::ae_state _alglib_env_state;    
    bool selfmatch;

    selfmatch = true;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::kdtreequeryknn(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), k, selfmatch, &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
R-NN query: all points within R-sphere centered at X

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    R           -   radius of sphere (in corresponding norm), R>0
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True

RESULT
    number of neighbors found, >=0

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
actual results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
R-NN 질의 : X를 중심으로 R- 구 내의 모든 점
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    R - 구의 반경 (해당 표준에서), R> 0
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
결과
    발견 된 이웃의 수,> = 0
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
실제 결과:
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryrnn(const kdtree &kdt, const real_1d_array &x, const double r, const bool selfmatch)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::kdtreequeryrnn(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), r, selfmatch, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
R-NN query: all points within R-sphere centered at X

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    R           -   radius of sphere (in corresponding norm), R>0
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True

RESULT
    number of neighbors found, >=0

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
actual results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
R-NN 질의 : X를 중심으로 R- 구 내의 모든 점
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    R - 구의 반경 (해당 표준에서), R> 0
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
결과
    발견 된 이웃의 수,> = 0
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
실제 결과:
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryrnn(const kdtree &kdt, const real_1d_array &x, const double r)
{
    alglib_impl::ae_state _alglib_env_state;    
    bool selfmatch;

    selfmatch = true;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::kdtreequeryrnn(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), r, selfmatch, &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
K-NN query: approximate K nearest neighbors

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    K           -   number of neighbors to return, K>=1
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True
    Eps         -   approximation factor, Eps>=0. eps-approximate  nearest
                    neighbor  is  a  neighbor  whose distance from X is at
                    most (1+eps) times distance of true nearest neighbor.

RESULT
    number of actual neighbors found (either K or N, if K>N).

NOTES
    significant performance gain may be achieved only when Eps  is  is  on
    the order of magnitude of 1 or larger.

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
these results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
K-NN 질의 : 근사 K 최근 접 이웃
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    K - 반환 할 이웃 수, K> = 1
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
    Eps - 근사 인수, Eps> = 0. 대략 eps- 근사치
                    이웃은 X와 거리가 먼 이웃입니다.
                    가장 가까운 (1 + eps) 배의 가장 가까운 이웃.
결과
    발견 된 실제 이웃의 수 (K> N 인 경우 K 또는 N 중 하나)
노트
    Eps가 켜져있을 때만 상당한 성능 향상을 얻을 수 있습니다.
    크기의 차수는 1 이상.
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
이러한 결과는 다음과 같습니다.
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryaknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k, const bool selfmatch, const double eps)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::kdtreequeryaknn(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), k, selfmatch, eps, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
K-NN query: approximate K nearest neighbors

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    K           -   number of neighbors to return, K>=1
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True
    Eps         -   approximation factor, Eps>=0. eps-approximate  nearest
                    neighbor  is  a  neighbor  whose distance from X is at
                    most (1+eps) times distance of true nearest neighbor.

RESULT
    number of actual neighbors found (either K or N, if K>N).

NOTES
    significant performance gain may be achieved only when Eps  is  is  on
    the order of magnitude of 1 or larger.

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
these results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
K-NN 질의 : 근사 K 최근 접 이웃
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    K - 반환 할 이웃 수, K> = 1
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
    Eps - 근사 인수, Eps> = 0. 대략 eps- 근사치
                    이웃은 X와 거리가 먼 이웃입니다.
                    가장 가까운 (1 + eps) 배의 가장 가까운 이웃.
결과
    발견 된 실제 이웃의 수 (K> N 인 경우 K 또는 N 중 하나)
노트
    Eps가 켜져있을 때만 상당한 성능 향상을 얻을 수 있습니다.
    크기의 차수는 1 이상.
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
이러한 결과는 다음과 같습니다.
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryaknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k, const double eps)
{
    alglib_impl::ae_state _alglib_env_state;    
    bool selfmatch;

    selfmatch = true;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::ae_int_t result = alglib_impl::kdtreequeryaknn(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), k, selfmatch, eps, &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<ae_int_t*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
X-values from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    X       -   possibly pre-allocated buffer. If X is too small to store
                result, it is resized. If size(X) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    X       -   rows are filled with X-values

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsXY()            X- and Y-values
* KDTreeQueryResultsTags()          tag values
* KDTreeQueryResultsDistances()     distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 X 값
입력 매개 변수
    KDT - KD 트리
    X - 사전에 할당 할 수 있었던 버퍼. X가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (X)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    X - 행은 X 값으로 채워집니다.
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsXY () X 및 Y 값
* KDTreeQueryResultsTags () 태그 값
* KDTreeQueryResultsDistances () 거리
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsx(const kdtree &kdt, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultsx(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
X- and Y-values from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    XY      -   possibly pre-allocated buffer. If XY is too small to store
                result, it is resized. If size(XY) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    XY      -   rows are filled with points: first NX columns with
                X-values, next NY columns - with Y-values.

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsX()             X-values
* KDTreeQueryResultsTags()          tag values
* KDTreeQueryResultsDistances()     distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 X 및 Y 값
입력 매개 변수
    KDT - KD 트리
    XY - 아마도 사전 할당 된 버퍼. XY가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (XY)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    XY - 행은 점으로 채워집니다. 첫 번째 NX 열은
                X 값, 다음 NY 컬럼 - Y 값.
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsX () X 값
* KDTreeQueryResultsTags () 태그 값
* KDTreeQueryResultsDistances () 거리
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsxy(const kdtree &kdt, real_2d_array &xy)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultsxy(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_matrix*>(xy.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Tags from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    Tags    -   possibly pre-allocated buffer. If X is too small to store
                result, it is resized. If size(X) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    Tags    -   filled with tags associated with points,
                or, when no tags were supplied, with zeros

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsX()             X-values
* KDTreeQueryResultsXY()            X- and Y-values
* KDTreeQueryResultsDistances()     distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 태그
입력 매개 변수
    KDT - KD 트리
    태그 - 사전 할당 된 버퍼 일 수 있습니다. X가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (X)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    태그 - 포인트와 관련된 태그로 채워짐,
                또는 태그가 제공되지 않은 경우 0으로
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsX () X 값
* KDTreeQueryResultsXY () X 및 Y 값
* KDTreeQueryResultsDistances () 거리
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultstags(const kdtree &kdt, integer_1d_array &tags)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultstags(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(tags.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Distances from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    R       -   possibly pre-allocated buffer. If X is too small to store
                result, it is resized. If size(X) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    R       -   filled with distances (in corresponding norm)

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsX()             X-values
* KDTreeQueryResultsXY()            X- and Y-values
* KDTreeQueryResultsTags()          tag values

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 거리
입력 매개 변수
    KDT - KD 트리
    R - 사전 할당 된 버퍼. X가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (X)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    R - 거리로 채워짐 (해당 기준)
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsX () X 값
* KDTreeQueryResultsXY () X 및 Y 값
* KDTreeQueryResultsTags () 태그 값
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsdistances(const kdtree &kdt, real_1d_array &r)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultsdistances(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(r.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
X-values from last query; 'interactive' variant for languages like  Python
which   support    constructs   like  "X = KDTreeQueryResultsXI(KDT)"  and
interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 X 값; Python과 같은 언어를위한 'interactive'variant
"X = KDTreeQueryResultsXI (KDT)"와 같은 구조를 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsxi(const kdtree &kdt, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultsxi(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
XY-values from last query; 'interactive' variant for languages like Python
which   support    constructs   like "XY = KDTreeQueryResultsXYI(KDT)" and
interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 XY 값; Python과 같은 언어를위한 'interactive'variant
"XY = KDTreeQueryResultsXYI (KDT)"와 같은 구문을 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsxyi(const kdtree &kdt, real_2d_array &xy)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultsxyi(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_matrix*>(xy.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Tags  from  last  query;  'interactive' variant for languages like  Python
which  support  constructs  like "Tags = KDTreeQueryResultsTagsI(KDT)" and
interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 태그. Python과 같은 언어를위한 'interactive'variant
"Tags = KDTreeQueryResultsTagsI (KDT)"와 같은 구조를 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultstagsi(const kdtree &kdt, integer_1d_array &tags)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultstagsi(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(tags.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Distances from last query; 'interactive' variant for languages like Python
which  support  constructs   like  "R = KDTreeQueryResultsDistancesI(KDT)"
and interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리로부터의 거리; Python과 같은 언어를위한 'interactive'variant
"R = KDTreeQueryResultsDistancesI (KDT)"와 같은 구문을 지원합니다.
인터프리터 인터랙티브 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsdistancesi(const kdtree &kdt, real_1d_array &r)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::kdtreequeryresultsdistancesi(const_cast<alglib_impl::kdtree*>(kdt.c_ptr()), const_cast<alglib_impl::ae_vector*>(r.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF COMPUTATIONAL CORE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
static ae_int_t hqrnd_hqrndmax = 2147483561;
static ae_int_t hqrnd_hqrndm1 = 2147483563;
static ae_int_t hqrnd_hqrndm2 = 2147483399;
static ae_int_t hqrnd_hqrndmagic = 1634357784;
static ae_int_t hqrnd_hqrndintegerbase(hqrndstate* state,
     ae_state *_state);


static ae_int_t nearestneighbor_splitnodesize = 6;
static ae_int_t nearestneighbor_kdtreefirstversion = 0;
static void nearestneighbor_kdtreesplit(kdtree* kdt,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t d,
     double s,
     ae_int_t* i3,
     ae_state *_state);
static void nearestneighbor_kdtreegeneratetreerec(kdtree* kdt,
     ae_int_t* nodesoffs,
     ae_int_t* splitsoffs,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t maxleafsize,
     ae_state *_state);
static void nearestneighbor_kdtreequerynnrec(kdtree* kdt,
     ae_int_t offs,
     ae_state *_state);
static void nearestneighbor_kdtreeinitbox(kdtree* kdt,
     /* Real    *//* 실수    */ ae_vector* x,
     ae_state *_state);
static void nearestneighbor_kdtreeallocdatasetindependent(kdtree* kdt,
     ae_int_t nx,
     ae_int_t ny,
     ae_state *_state);
static void nearestneighbor_kdtreeallocdatasetdependent(kdtree* kdt,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_state *_state);
static void nearestneighbor_kdtreealloctemporaries(kdtree* kdt,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_state *_state);





/*************************************************************************
HQRNDState  initialization  with  random  values  which come from standard
RNG.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
HQRNDState 초기화 (표준에서 오는 임의의 값 사용)
RNG.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndrandomize(hqrndstate* state, ae_state *_state)
{
    ae_int_t s0;
    ae_int_t s1;

    _hqrndstate_clear(state);

    s0 = ae_randominteger(hqrnd_hqrndm1, _state);
    s1 = ae_randominteger(hqrnd_hqrndm2, _state);
    hqrndseed(s0, s1, state, _state);
}


/*************************************************************************
HQRNDState initialization with seed values

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
시드 값을 사용하는 HQRNDState 초기화
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndseed(ae_int_t s1,
     ae_int_t s2,
     hqrndstate* state,
     ae_state *_state)
{
    (void)_state;

    _hqrndstate_clear(state);

    
    /*
     * Protection against negative seeds:
     *
     *     SEED := -(SEED+1)
     *
     * We can use just "-SEED" because there exists such integer number  N
     * that N<0, -N=N<0 too. (This number is equal to 0x800...000).   Need
     * to handle such seed correctly forces us to use  a  bit  complicated
     * formula.
     */
    /*
     * 부정적인 종자에 대한 보호 :
     *
     * SEED : = - (SEED + 1)
     *
     * 그러한 정수 N이 있기 때문에 "-SEED"만 사용할 수 있습니다.
     * N <0, -N = N <0. 이 숫자는 0x800 ... 000과 같습니다. 필요한 것
     * 그러한 씨앗을 처리하기 위해 우리는 조금 복잡하게 사용하도록 강제합니다.
     * 공식.
     */
    if( s1<0 )
    {
        s1 = -(s1+1);
    }
    if( s2<0 )
    {
        s2 = -(s2+1);
    }
    state->s1 = s1%(hqrnd_hqrndm1-1)+1;
    state->s2 = s2%(hqrnd_hqrndm2-1)+1;
    state->magicv = hqrnd_hqrndmagic;
}


/*************************************************************************
This function generates random real number in (0,1),
not including interval boundaries

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 (0,1)에 임의의 실수를 생성합니다.
간격 경계를 포함하지 않음
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
double hqrnduniformr(hqrndstate* state, ae_state *_state)
{
    double result;


    result = (double)(hqrnd_hqrndintegerbase(state, _state)+1)/(double)(hqrnd_hqrndmax+2);
    return result;
}


/*************************************************************************
This function generates random integer number in [0, N)

1. State structure must be initialized with HQRNDRandomize() or HQRNDSeed()
2. N can be any positive number except for very large numbers:
   * close to 2^31 on 32-bit systems
   * close to 2^62 on 64-bit systems
   An exception will be generated if N is too large.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 [0, N]에 임의의 정수를 생성하고,
1. 상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화되어야합니다.
2. N은 매우 큰 숫자를 제외하고는 양수 일 수 있습니다.
   * 32 비트 시스템에서 2 ^ 31에 가깝습니다.
   * 64 비트 시스템에서는 2 ^ 62에 가깝습니다.
   N이 너무 큰 경우 예외가 생성됩니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
ae_int_t hqrnduniformi(hqrndstate* state, ae_int_t n, ae_state *_state)
{
    ae_int_t maxcnt;
    ae_int_t mx;
    ae_int_t a;
    ae_int_t b;
    ae_int_t result;


    ae_assert(n>0, "HQRNDUniformI: N<=0!", _state);
    maxcnt = hqrnd_hqrndmax+1;
    
    /*
     * Two branches: one for N<=MaxCnt, another for N>MaxCnt.
     */
    /*
     * 두 개의 분기 : N <= MaxCnt, N> MaxCnt의 분기.
     */
    if( n>maxcnt )
    {
        
        /*
         * N>=MaxCnt.
         *
         * We have two options here:
         * a) N is exactly divisible by MaxCnt
         * b) N is not divisible by MaxCnt
         *
         * In both cases we reduce problem on interval spanning [0,N)
         * to several subproblems on intervals spanning [0,MaxCnt).
         */
        /*
         * N> = MaxCnt.
         *
         * 여기에는 두 가지 옵션이 있습니다.
         * a) N은 MaxCnt로 정확하게 나눌 수 있습니다.
         * b) N은 MaxCnt로 나눌 수 없습니다.
         *
         * 두 경우 모두 간격 스패닝 [0, N] 문제를 줄입니다.
         * [0, MaxCnt]에 걸치는 간격에서 몇 가지 하위 문제로.
         */
        if( n%maxcnt==0 )
        {
            
            /*
             * N is exactly divisible by MaxCnt.
             *
             * [0,N) range is dividided into N/MaxCnt bins,
             * each of them having length equal to MaxCnt.
             *
             * We generate:
             * * random bin number B
             * * random offset within bin A
             * Both random numbers are generated by recursively
             * calling HQRNDUniformI().
             *
             * Result is equal to A+MaxCnt*B.
             */
            /*
             * N은 MaxCnt로 정확하게 나눌 수 있습니다.
             *
             * [0, N) 범위는 N / MaxCnt bin으로 나뉘며,
             * 각각 길이가 MaxCnt와 같습니다.
             *
             * 우리는 생성 :
             * * 랜덤 빈 번호 B
             * bin A 내의 임의의 오프셋
             * 두 난수 모두 재귀 적으로 생성됩니다.
             * HQRNDUniformI () 호출.
             *
             * 결과는 A + MaxCnt * B와 같습니다.
             */
            ae_assert(n/maxcnt<=maxcnt, "HQRNDUniformI: N is too large", _state);
            a = hqrnduniformi(state, maxcnt, _state);
            b = hqrnduniformi(state, n/maxcnt, _state);
            result = a+maxcnt*b;
        }
        else
        {
            
            /*
             * N is NOT exactly divisible by MaxCnt.
             *
             * [0,N) range is dividided into Ceil(N/MaxCnt) bins,
             * each of them having length equal to MaxCnt.
             *
             * We generate:
             * * random bin number B in [0, Ceil(N/MaxCnt)-1]
             * * random offset within bin A
             * * if both of what is below is true
             *   1) bin number B is that of the last bin
             *   2) A >= N mod MaxCnt
             *   then we repeat generation of A/B.
             *   This stage is essential in order to avoid bias in the result.
             * * otherwise, we return A*MaxCnt+N
             */
            /*
             * N은 MaxCnt로 정확하게 나눌 수 없습니다.
             *
             * [0, N) 범위는 Ceil (N / MaxCnt) 빈으로 분할됩니다.
             * 각각 길이가 MaxCnt와 같습니다.
             *
             * 우리는 생성 :
             * [0, Ceil (N / MaxCnt) -1]의 임의의 빈 번호 B *
             * bin A 내의 임의의 오프셋
             * * 아래에있는 것이 모두 true 인 경우
             * 1) 빈 번호 B는 마지막 빈의 번호입니다.
             * 2) A> = N mod MaxCnt
             * A / B 생성을 반복합니다.
             *이 단계는 결과에 편향을 피하기 위해 필수적입니다.
             * 그렇지 않으면 A * MaxCnt + N을 반환합니다.
             */
            ae_assert(n/maxcnt+1<=maxcnt, "HQRNDUniformI: N is too large", _state);
            result = -1;
            do
            {
                a = hqrnduniformi(state, maxcnt, _state);
                b = hqrnduniformi(state, n/maxcnt+1, _state);
                if( b==n/maxcnt&&a>=n%maxcnt )
                {
                    continue;
                }
                result = a+maxcnt*b;
            }
            while(result<0);
        }
    }
    else
    {
        
        /*
         * N<=MaxCnt
         *
         * Code below is a bit complicated because we can not simply
         * return "HQRNDIntegerBase() mod N" - it will be skewed for
         * large N's in [0.1*HQRNDMax...HQRNDMax].
         */
        /*
         * N <= MaxCnt
         *
         아래의 코드는 우리가 간단히 할 수 없기 때문에 약간 복잡합니다.
         * "HQRNDIntegerBase () mod N"을 반환합니다. - 그것은 비뚤어 질 것입니다.
         * 큰 N은 [0.1 * HQRNDMax ... HQRNDMax]입니다.
         */
        mx = maxcnt-maxcnt%n;
        do
        {
            result = hqrnd_hqrndintegerbase(state, _state);
        }
        while(result>=mx);
        result = result%n;
    }
    return result;
}


/*************************************************************************
Random number generator: normal numbers

This function generates one random number from normal distribution.
Its performance is equal to that of HQRNDNormal2()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : 정상 수
이 함수는 정규 분포에서 하나의 난수를 생성합니다.
그 성능은 HQRNDNormal2 ()의 성능과 같습니다.
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
double hqrndnormal(hqrndstate* state, ae_state *_state)
{
    double v1;
    double v2;
    double result;


    hqrndnormal2(state, &v1, &v2, _state);
    result = v1;
    return result;
}


/*************************************************************************
Random number generator: random X and Y such that X^2+Y^2=1

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : X ^ 2 + Y ^ 2 = 1과 같은 임의의 X와 Y
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndunit2(hqrndstate* state, double* x, double* y, ae_state *_state)
{
    double v;
    double mx;
    double mn;

    *x = 0;
    *y = 0;

    do
    {
        hqrndnormal2(state, x, y, _state);
    }
    while(!(ae_fp_neq(*x,0)||ae_fp_neq(*y,0)));
    mx = ae_maxreal(ae_fabs(*x, _state), ae_fabs(*y, _state), _state);
    mn = ae_minreal(ae_fabs(*x, _state), ae_fabs(*y, _state), _state);
    v = mx*ae_sqrt(1+ae_sqr(mn/mx, _state), _state);
    *x = *x/v;
    *y = *y/v;
}


/*************************************************************************
Random number generator: normal numbers

This function generates two independent random numbers from normal
distribution. Its performance is equal to that of HQRNDNormal()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : 정상 수
이 함수는 법선으로부터 2 개의 독립 난수를 생성합니다.
분포. 그 성능은 HQRNDNormal ()과 동일합니다.
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
**************************************************************************/
void hqrndnormal2(hqrndstate* state,
     double* x1,
     double* x2,
     ae_state *_state)
{
    double u;
    double v;
    double s;

    *x1 = 0;
    *x2 = 0;

    for(;;)
    {
        u = 2*hqrnduniformr(state, _state)-1;
        v = 2*hqrnduniformr(state, _state)-1;
        s = ae_sqr(u, _state)+ae_sqr(v, _state);
        if( ae_fp_greater(s,0)&&ae_fp_less(s,1) )
        {
            
            /*
             * two Sqrt's instead of one to
             * avoid overflow when S is too small
             */
            /*
             * 1 대신에 2 Sqrt
             * S가 너무 작 으면 오버플로를 피하십시오.
             */
            s = ae_sqrt(-2*ae_log(s, _state), _state)/ae_sqrt(s, _state);
            *x1 = u*s;
            *x2 = v*s;
            return;
        }
    }
}


/*************************************************************************
Random number generator: exponential distribution

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 11.08.2007 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
난수 생성기 : 지수 분포
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 2007 년 11 월 8 일 Bochkanov Sergey
**************************************************************************/
double hqrndexponential(hqrndstate* state,
     double lambdav,
     ae_state *_state)
{
    double result;


    ae_assert(ae_fp_greater(lambdav,0), "HQRNDExponential: LambdaV<=0!", _state);
    result = -ae_log(hqrnduniformr(state, _state), _state)/lambdav;
    return result;
}


/*************************************************************************
This function generates  random number from discrete distribution given by
finite sample X.

INPUT PARAMETERS
    State   -   high quality random number generator, must be
                initialized with HQRNDRandomize() or HQRNDSeed().
        X   -   finite sample
        N   -   number of elements to use, N>=1

RESULT
    this function returns one of the X[i] for random i=0..N-1

  -- ALGLIB --
     Copyright 08.11.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는에 의해 주어진 이산 분포로부터 난수를 생성합니다.
유한 샘플 X
입력 매개 변수
    상태 - 고품질 난수 생성기, 있어야합니다.
                HQRNDRandomize () 또는 HQRNDSeed ()로 초기화됩니다.
        X - 유한 샘플
        N - 사용할 요소 수, N> = 1
결과
    이 함수는 random i = 0..N-1에 대해 X [i] 중 하나를 반환합니다.
  - ALGLIB -
     저작권 08.11.2011 Bochkanov Sergey
**************************************************************************/
double hqrnddiscrete(hqrndstate* state,
     /* Real    *//* 실수    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{
    double result;


    ae_assert(n>0, "HQRNDDiscrete: N<=0", _state);
    ae_assert(n<=x->cnt, "HQRNDDiscrete: Length(X)<N", _state);
    result = x->ptr.p_double[hqrnduniformi(state, n, _state)];
    return result;
}


/*************************************************************************
This function generates random number from continuous  distribution  given
by finite sample X.

INPUT PARAMETERS
    State   -   high quality random number generator, must be
                initialized with HQRNDRandomize() or HQRNDSeed().
        X   -   finite sample, array[N] (can be larger, in this  case only
                leading N elements are used). THIS ARRAY MUST BE SORTED BY
                ASCENDING.
        N   -   number of elements to use, N>=1

RESULT
    this function returns random number from continuous distribution which  
    tries to approximate X as mush as possible. min(X)<=Result<=max(X).

  -- ALGLIB --
     Copyright 08.11.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 주어진 연속 분포로부터 난수를 생성합니다.
유한 샘플 X로.
입력 매개 변수
    상태 - 고품질 난수 생성기, 있어야합니다.
                HQRNDRandomize () 또는 HQRNDSeed ()로 초기화됩니다.
        X - 유한 샘플, 배열 [N] (이 경우에만 더 클 수 있습니다.
                선두의 N 요소가 사용된다). 이 배열은에 의해 정렬되어야합니다
                승천.
        N - 사용할 요소 수, N> = 1
결과
    이 함수는 연속적인 분포에서 난수를 반환한다.  
    X를 최대한 근사해 보려고합니다. min (X) <= Result <= max (X).
  - ALGLIB -
     저작권 08.11.2011 Bochkanov Sergey
**************************************************************************/
double hqrndcontinuous(hqrndstate* state,
     /* Real    *//* 실수    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{
    double mx;
    double mn;
    ae_int_t i;
    double result;


    ae_assert(n>0, "HQRNDContinuous: N<=0", _state);
    ae_assert(n<=x->cnt, "HQRNDContinuous: Length(X)<N", _state);
    if( n==1 )
    {
        result = x->ptr.p_double[0];
        return result;
    }
    i = hqrnduniformi(state, n-1, _state);
    mn = x->ptr.p_double[i];
    mx = x->ptr.p_double[i+1];
    ae_assert(ae_fp_greater_eq(mx,mn), "HQRNDDiscrete: X is not sorted by ascending", _state);
    if( ae_fp_neq(mx,mn) )
    {
        result = (mx-mn)*hqrnduniformr(state, _state)+mn;
    }
    else
    {
        result = mn;
    }
    return result;
}


/*************************************************************************
This function returns random integer in [0,HQRNDMax]

L'Ecuyer, Efficient and portable combined random number generators
*************************************************************************/
/**************************************************************************
이 함수는 [0, HQRNDMax]에 임의의 정수를 반환합니다.
L' Ecuyer, 효율적이고 휴대 가능한 결합 난수 생성기
**************************************************************************/
static ae_int_t hqrnd_hqrndintegerbase(hqrndstate* state,
     ae_state *_state)
{
    ae_int_t k;
    ae_int_t result;


    ae_assert(state->magicv==hqrnd_hqrndmagic, "HQRNDIntegerBase: State is not correctly initialized!", _state);
    k = state->s1/53668;
    state->s1 = 40014*(state->s1-k*53668)-k*12211;
    if( state->s1<0 )
    {
        state->s1 = state->s1+2147483563;
    }
    k = state->s2/52774;
    state->s2 = 40692*(state->s2-k*52774)-k*3791;
    if( state->s2<0 )
    {
        state->s2 = state->s2+2147483399;
    }
    
    /*
     * Result
     */
    /*
     * 결과
     */
    result = state->s1-state->s2;
    if( result<1 )
    {
        result = result+2147483562;
    }
    result = result-1;
    return result;
}


ae_bool _hqrndstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    hqrndstate *p = (hqrndstate*)_p;
    ae_touch_ptr((void*)p);
    return ae_true;
}


ae_bool _hqrndstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    hqrndstate *dst = (hqrndstate*)_dst;
    hqrndstate *src = (hqrndstate*)_src;
    dst->s1 = src->s1;
    dst->s2 = src->s2;
    dst->magicv = src->magicv;
    return ae_true;
}


void _hqrndstate_clear(void* _p)
{
    hqrndstate *p = (hqrndstate*)_p;
    ae_touch_ptr((void*)p);
}


void _hqrndstate_destroy(void* _p)
{
    hqrndstate *p = (hqrndstate*)_p;
    ae_touch_ptr((void*)p);
}




/*************************************************************************
KD-tree creation

This subroutine creates KD-tree from set of X-values and optional Y-values

INPUT PARAMETERS
    XY      -   dataset, array[0..N-1,0..NX+NY-1].
                one row corresponds to one point.
                first NX columns contain X-values, next NY (NY may be zero)
                columns may contain associated Y-values
    N       -   number of points, N>=0.
    NX      -   space dimension, NX>=1.
    NY      -   number of optional Y-values, NY>=0.
    NormType-   norm type:
                * 0 denotes infinity-norm
                * 1 denotes 1-norm
                * 2 denotes 2-norm (Euclidean norm)
                
OUTPUT PARAMETERS
    KDT     -   KD-tree
    
    
NOTES

1. KD-tree  creation  have O(N*logN) complexity and O(N*(2*NX+NY))  memory
   requirements.
2. Although KD-trees may be used with any combination of N  and  NX,  they
   are more efficient than brute-force search only when N >> 4^NX. So they
   are most useful in low-dimensional tasks (NX=2, NX=3). NX=1  is another
   inefficient case, because  simple  binary  search  (without  additional
   structures) is much more efficient in such tasks than KD-trees.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
KD- 트리 생성
이 서브 루틴은 X 값의 집합과 선택적인 Y 값으로부터 KD 트리를 생성합니다
입력 매개 변수
    XY-dataset, array [0..N-1,0..NX + NY-1].
                한 행은 한 점에 해당합니다.
                첫 번째 NX 열에는 X 값이 포함되고 다음 NY (NY는 0이 될 수 있음)
                열은 연관된 Y 값을 포함 할 수 있습니다.
    N - 포인트 수, N> = 0.
    NX - 공간 차원, NX> = 1.
    NY - 선택적 Y 값의 수, NY> = 0.
    NormType- 노름 유형 :
                * 0은 무한대 - 표준을 나타냅니다.
                * 1은 1- 노름을 나타냅니다.
                * 2는 2- 노름 (유클리드 기준)
                
출력 매개 변수
    KDT - KD 트리
    
    
노트
1. KD 트리 생성은 O (N * logN) 복잡도와 O (N * (2 * NX + NY)) 메모리를 갖는다.
   요구 사항.
2. KD- 나무는 N과 NX의 조합과 함께 사용될 수 있지만,
   N >> 4 ^ NX 일 때만 무차별 강제 검색보다 더 효율적입니다. 그래서 그들은
   저 차원 작업 (NX = 2, NX = 3)에서 가장 유용합니다. NX = 1은 또 다른 것입니다.
   비효율적 인 경우, 간단한 이진 검색 (추가하지 않음
   구조)는 KD- 나무보다 훨씬 효율적입니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreebuild(/* Real    *//* 실수    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_int_t normtype,
     kdtree* kdt,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector tags;
    ae_int_t i;

    ae_frame_make(_state, &_frame_block);
    _kdtree_clear(kdt);
    ae_vector_init(&tags, 0, DT_INT, _state, ae_true);

    ae_assert(n>=0, "KDTreeBuild: N<0", _state);
    ae_assert(nx>=1, "KDTreeBuild: NX<1", _state);
    ae_assert(ny>=0, "KDTreeBuild: NY<0", _state);
    ae_assert(normtype>=0&&normtype<=2, "KDTreeBuild: incorrect NormType", _state);
    ae_assert(xy->rows>=n, "KDTreeBuild: rows(X)<N", _state);
    ae_assert(xy->cols>=nx+ny||n==0, "KDTreeBuild: cols(X)<NX+NY", _state);
    ae_assert(apservisfinitematrix(xy, n, nx+ny, _state), "KDTreeBuild: XY contains infinite or NaN values", _state);
    if( n>0 )
    {
        ae_vector_set_length(&tags, n, _state);
        for(i=0; i<=n-1; i++)
        {
            tags.ptr.p_int[i] = 0;
        }
    }
    kdtreebuildtagged(xy, &tags, n, nx, ny, normtype, kdt, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
KD-tree creation

This  subroutine  creates  KD-tree  from set of X-values, integer tags and
optional Y-values

INPUT PARAMETERS
    XY      -   dataset, array[0..N-1,0..NX+NY-1].
                one row corresponds to one point.
                first NX columns contain X-values, next NY (NY may be zero)
                columns may contain associated Y-values
    Tags    -   tags, array[0..N-1], contains integer tags associated
                with points.
    N       -   number of points, N>=0
    NX      -   space dimension, NX>=1.
    NY      -   number of optional Y-values, NY>=0.
    NormType-   norm type:
                * 0 denotes infinity-norm
                * 1 denotes 1-norm
                * 2 denotes 2-norm (Euclidean norm)

OUTPUT PARAMETERS
    KDT     -   KD-tree

NOTES

1. KD-tree  creation  have O(N*logN) complexity and O(N*(2*NX+NY))  memory
   requirements.
2. Although KD-trees may be used with any combination of N  and  NX,  they
   are more efficient than brute-force search only when N >> 4^NX. So they
   are most useful in low-dimensional tasks (NX=2, NX=3). NX=1  is another
   inefficient case, because  simple  binary  search  (without  additional
   structures) is much more efficient in such tasks than KD-trees.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
KD- 트리 생성
이 서브 루틴은 일련의 X 값, 정수 태그 및
선택적 Y 값
입력 매개 변수
    XY-dataset, array [0..N-1,0..NX + NY-1].
                한 행은 한 점에 해당합니다.
                첫 번째 NX 열에는 X 값이 포함되고 다음 NY (NY는 0이 될 수 있음)
                열은 연관된 Y 값을 포함 할 수 있습니다.
    태그 - 태그, 배열 [0..N-1], 관련 정수 태그 포함
                포인트로.
    N - 포인트 수, N> = 0
    NX - 공간 차원, NX> = 1.
    NY - 선택적 Y 값의 수, NY> = 0.
    NormType- 노름 유형 :
                * 0은 무한대 - 표준을 나타냅니다.
                * 1은 1- 노름을 나타냅니다.
                * 2는 2- 노름 (유클리드 기준)
출력 매개 변수
    KDT - KD 트리
노트
1. KD 트리 생성은 O (N * logN) 복잡도와 O (N * (2 * NX + NY)) 메모리를 갖는다.
   요구 사항.
2. KD- 나무는 N과 NX의 조합과 함께 사용될 수 있지만,
   N >> 4 ^ NX 일 때만 무차별 강제 검색보다 더 효율적입니다. 그래서 그들은
   저 차원 작업 (NX = 2, NX = 3)에서 가장 유용합니다. NX = 1은 또 다른 것입니다.
   비효율적 인 경우, 간단한 이진 검색 (추가하지 않음
   구조)는 KD- 나무보다 훨씬 효율적입니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreebuildtagged(/* Real    *//* 실수    */ ae_matrix* xy,
     /* Integer *//* 정수 */ ae_vector* tags,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_int_t normtype,
     kdtree* kdt,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t maxnodes;
    ae_int_t nodesoffs;
    ae_int_t splitsoffs;

    _kdtree_clear(kdt);

    ae_assert(n>=0, "KDTreeBuildTagged: N<0", _state);
    ae_assert(nx>=1, "KDTreeBuildTagged: NX<1", _state);
    ae_assert(ny>=0, "KDTreeBuildTagged: NY<0", _state);
    ae_assert(normtype>=0&&normtype<=2, "KDTreeBuildTagged: incorrect NormType", _state);
    ae_assert(xy->rows>=n, "KDTreeBuildTagged: rows(X)<N", _state);
    ae_assert(xy->cols>=nx+ny||n==0, "KDTreeBuildTagged: cols(X)<NX+NY", _state);
    ae_assert(apservisfinitematrix(xy, n, nx+ny, _state), "KDTreeBuildTagged: XY contains infinite or NaN values", _state);
    
    /*
     * initialize
     */
    /*
     * 초기화
     */
    kdt->n = n;
    kdt->nx = nx;
    kdt->ny = ny;
    kdt->normtype = normtype;
    kdt->kcur = 0;
    
    /*
     * N=0 => quick exit
     */
    /*
     * N = 0 => 빠른 종료
     */
    if( n==0 )
    {
        return;
    }
    
    /*
     * Allocate
     */
    /*
     * 할당
     */
    nearestneighbor_kdtreeallocdatasetindependent(kdt, nx, ny, _state);
    nearestneighbor_kdtreeallocdatasetdependent(kdt, n, nx, ny, _state);
    
    /*
     * Initial fill
     */
    /*
     * 초기 채우기
     */
    for(i=0; i<=n-1; i++)
    {
        ae_v_move(&kdt->xy.ptr.pp_double[i][0], 1, &xy->ptr.pp_double[i][0], 1, ae_v_len(0,nx-1));
        ae_v_move(&kdt->xy.ptr.pp_double[i][nx], 1, &xy->ptr.pp_double[i][0], 1, ae_v_len(nx,2*nx+ny-1));
        kdt->tags.ptr.p_int[i] = tags->ptr.p_int[i];
    }
    
    /*
     * Determine bounding box
     */
    /*
     * 경계 상자 결정
     */
    ae_v_move(&kdt->boxmin.ptr.p_double[0], 1, &kdt->xy.ptr.pp_double[0][0], 1, ae_v_len(0,nx-1));
    ae_v_move(&kdt->boxmax.ptr.p_double[0], 1, &kdt->xy.ptr.pp_double[0][0], 1, ae_v_len(0,nx-1));
    for(i=1; i<=n-1; i++)
    {
        for(j=0; j<=nx-1; j++)
        {
            kdt->boxmin.ptr.p_double[j] = ae_minreal(kdt->boxmin.ptr.p_double[j], kdt->xy.ptr.pp_double[i][j], _state);
            kdt->boxmax.ptr.p_double[j] = ae_maxreal(kdt->boxmax.ptr.p_double[j], kdt->xy.ptr.pp_double[i][j], _state);
        }
    }
    
    /*
     * prepare tree structure
     * * MaxNodes=N because we guarantee no trivial splits, i.e.
     *   every split will generate two non-empty boxes
     */
    /*
     * 나무 구조 준비
     * * 우리가 사소한 분리를 보장하지 않기 때문에 MaxNodes = N, 즉
     * 모든 분할은 두 개의 비어 있지 않은 상자를 생성합니다.
     */
    maxnodes = n;
    ae_vector_set_length(&kdt->nodes, nearestneighbor_splitnodesize*2*maxnodes, _state);
    ae_vector_set_length(&kdt->splits, 2*maxnodes, _state);
    nodesoffs = 0;
    splitsoffs = 0;
    ae_v_move(&kdt->curboxmin.ptr.p_double[0], 1, &kdt->boxmin.ptr.p_double[0], 1, ae_v_len(0,nx-1));
    ae_v_move(&kdt->curboxmax.ptr.p_double[0], 1, &kdt->boxmax.ptr.p_double[0], 1, ae_v_len(0,nx-1));
    nearestneighbor_kdtreegeneratetreerec(kdt, &nodesoffs, &splitsoffs, 0, n, 8, _state);
}


/*************************************************************************
K-NN query: K nearest neighbors

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    K           -   number of neighbors to return, K>=1
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True

RESULT
    number of actual neighbors found (either K or N, if K>N).

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
these results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
K-NN 질의 : K 개의 가장 가까운 이웃
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    K - 반환 할 이웃 수, K> = 1
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
결과
    발견 된 실제 이웃의 수 (K> N 인 경우 K 또는 N 중 하나)
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
이러한 결과는 다음과 같습니다.
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryknn(kdtree* kdt,
     /* Real    *//* 실수     */ ae_vector* x,
     ae_int_t k,
     ae_bool selfmatch,
     ae_state *_state)
{
    ae_int_t result;


    ae_assert(k>=1, "KDTreeQueryKNN: K<1!", _state);
    ae_assert(x->cnt>=kdt->nx, "KDTreeQueryKNN: Length(X)<NX!", _state);
    ae_assert(isfinitevector(x, kdt->nx, _state), "KDTreeQueryKNN: X contains infinite or NaN values!", _state);
    result = kdtreequeryaknn(kdt, x, k, selfmatch, 0.0, _state);
    return result;
}


/*************************************************************************
R-NN query: all points within R-sphere centered at X

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    R           -   radius of sphere (in corresponding norm), R>0
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True

RESULT
    number of neighbors found, >=0

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
actual results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
R-NN 질의 : X를 중심으로 R- 구 내의 모든 점
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    R - 구의 반경 (해당 표준에서), R> 0
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
결과
    발견 된 이웃의 수,> = 0
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
실제 결과:
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryrnn(kdtree* kdt,
     /* Real    *//* 실수     */ ae_vector* x,
     double r,
     ae_bool selfmatch,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t result;


    ae_assert(ae_fp_greater(r,0), "KDTreeQueryRNN: incorrect R!", _state);
    ae_assert(x->cnt>=kdt->nx, "KDTreeQueryRNN: Length(X)<NX!", _state);
    ae_assert(isfinitevector(x, kdt->nx, _state), "KDTreeQueryRNN: X contains infinite or NaN values!", _state);
    
    /*
     * Handle special case: KDT.N=0
     */
    /*
     * 특수 케이스 취급 : KDT.N = 0
     */
    if( kdt->n==0 )
    {
        kdt->kcur = 0;
        result = 0;
        return result;
    }
    
    /*
     * Prepare parameters
     */
    /*
     * 매개 변수 준비
     */
    kdt->kneeded = 0;
    if( kdt->normtype!=2 )
    {
        kdt->rneeded = r;
    }
    else
    {
        kdt->rneeded = ae_sqr(r, _state);
    }
    kdt->selfmatch = selfmatch;
    kdt->approxf = 1;
    kdt->kcur = 0;
    
    /*
     * calculate distance from point to current bounding box
     */
    /*
     * 점에서 현재 경계 상자까지의 거리를 계산합니다.
     */
    nearestneighbor_kdtreeinitbox(kdt, x, _state);
    
    /*
     * call recursive search
     * results are returned as heap
     */
    /*
     * 재귀 호출 호출
     * 결과는 힙으로 반환됩니다.
     */
    nearestneighbor_kdtreequerynnrec(kdt, 0, _state);
    
    /*
     * pop from heap to generate ordered representation
     *
     * last element is not pop'ed because it is already in
     * its place
     */
    /*
     * 힙에서 팝하여 정렬 된 표현을 생성합니다.
     *
     * 마지막 요소는 이미 있기 때문에 pop'ed되지 않습니다.
     * 그 장소
     */
    result = kdt->kcur;
    j = kdt->kcur;
    for(i=kdt->kcur; i>=2; i--)
    {
        tagheappopi(&kdt->r, &kdt->idx, &j, _state);
    }
    return result;
}


/*************************************************************************
K-NN query: approximate K nearest neighbors

INPUT PARAMETERS
    KDT         -   KD-tree
    X           -   point, array[0..NX-1].
    K           -   number of neighbors to return, K>=1
    SelfMatch   -   whether self-matches are allowed:
                    * if True, nearest neighbor may be the point itself
                      (if it exists in original dataset)
                    * if False, then only points with non-zero distance
                      are returned
                    * if not given, considered True
    Eps         -   approximation factor, Eps>=0. eps-approximate  nearest
                    neighbor  is  a  neighbor  whose distance from X is at
                    most (1+eps) times distance of true nearest neighbor.

RESULT
    number of actual neighbors found (either K or N, if K>N).
    
NOTES
    significant performance gain may be achieved only when Eps  is  is  on
    the order of magnitude of 1 or larger.

This  subroutine  performs  query  and  stores  its result in the internal
structures of the KD-tree. You can use  following  subroutines  to  obtain
these results:
* KDTreeQueryResultsX() to get X-values
* KDTreeQueryResultsXY() to get X- and Y-values
* KDTreeQueryResultsTags() to get tag values
* KDTreeQueryResultsDistances() to get distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
K-NN 질의 : 근사 K 최근 접 이웃
입력 매개 변수
    KDT - KD 트리
    X- 점, 배열 [0..NX-1].
    K - 반환 할 이웃 수, K> = 1
    SelfMatch - 자기 일치가 허용되는지 여부 :
                    * 참이면 가장 가까운 이웃이 포인트 자체 일 수 있습니다.
                      (원래 데이터 집합에있는 경우)
                    * 거짓이면 거리가 0이 아닌 점만 나타냅니다.
                      돌아왔다
                    * 주어지지 않았다면 True로 간주
    Eps - 근사 인수, Eps> = 0. 대략 eps- 근사치
                    이웃은 X와 거리가 먼 이웃입니다.
                    가장 가까운 (1 + eps) 배의 가장 가까운 이웃.
결과
    발견 된 실제 이웃의 수 (K> N 인 경우 K 또는 N 중 하나)
    
노트
    Eps가 켜져있을 때만 상당한 성능 향상을 얻을 수 있습니다.
    크기의 차수는 1 이상.
이 서브 루틴은 쿼리를 수행하고 결과를 내부에 저장합니다.
KD- 트리의 구조. 다음과 같은 서브 루틴을 사용하여
이러한 결과는 다음과 같습니다.
* X 값을 가져 오는 KDTreeQueryResultsX ()
* X 및 Y 값을 가져 오는 KDTreeQueryResultsXY ()
* 태그 값을 가져 오는 KDTreeQueryResultsTags ()
* 거리를 얻기위한 KDTreeQueryResultsDistances ()
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
ae_int_t kdtreequeryaknn(kdtree* kdt,
     /* Real    *//* 실수     */ ae_vector* x,
     ae_int_t k,
     ae_bool selfmatch,
     double eps,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t result;


    ae_assert(k>0, "KDTreeQueryAKNN: incorrect K!", _state);
    ae_assert(ae_fp_greater_eq(eps,0), "KDTreeQueryAKNN: incorrect Eps!", _state);
    ae_assert(x->cnt>=kdt->nx, "KDTreeQueryAKNN: Length(X)<NX!", _state);
    ae_assert(isfinitevector(x, kdt->nx, _state), "KDTreeQueryAKNN: X contains infinite or NaN values!", _state);
    
    /*
     * Handle special case: KDT.N=0
     */
    /*
     * 특수 케이스 취급 : KDT.N = 0
     */
    if( kdt->n==0 )
    {
        kdt->kcur = 0;
        result = 0;
        return result;
    }
    
    /*
     * Prepare parameters
     */
    /*
     * 매개 변수 준비
     */
    k = ae_minint(k, kdt->n, _state);
    kdt->kneeded = k;
    kdt->rneeded = 0;
    kdt->selfmatch = selfmatch;
    if( kdt->normtype==2 )
    {
        kdt->approxf = 1/ae_sqr(1+eps, _state);
    }
    else
    {
        kdt->approxf = 1/(1+eps);
    }
    kdt->kcur = 0;
    
    /*
     * calculate distance from point to current bounding box
     */
    /*
     * 점에서 현재 경계 상자까지의 거리를 계산합니다.
     */
    nearestneighbor_kdtreeinitbox(kdt, x, _state);
    
    /*
     * call recursive search
     * results are returned as heap
     */
    /*
     * 재귀 호출 호출
     * 결과는 힙으로 반환됩니다.
     */
    nearestneighbor_kdtreequerynnrec(kdt, 0, _state);
    
    /*
     * pop from heap to generate ordered representation
     *
     * last element is non pop'ed because it is already in
     * its place
     */
    /*
     * 힙에서 팝하여 정렬 된 표현을 생성합니다.
     *
     * 마지막 요소는 이미 poped되어 있기 때문에 pop'ed가 아닙니다.
     * 그 장소
     */
    result = kdt->kcur;
    j = kdt->kcur;
    for(i=kdt->kcur; i>=2; i--)
    {
        tagheappopi(&kdt->r, &kdt->idx, &j, _state);
    }
    return result;
}


/*************************************************************************
X-values from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    X       -   possibly pre-allocated buffer. If X is too small to store
                result, it is resized. If size(X) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    X       -   rows are filled with X-values

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsXY()            X- and Y-values
* KDTreeQueryResultsTags()          tag values
* KDTreeQueryResultsDistances()     distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 X 값
입력 매개 변수
    KDT - KD 트리
    X - 사전에 할당 할 수 있었던 버퍼. X가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (X)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    X - 행은 X 값으로 채워집니다.
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsXY () X 및 Y 값
* KDTreeQueryResultsTags () 태그 값
* KDTreeQueryResultsDistances () 거리
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsx(kdtree* kdt,
     /* Real    *//* 실수     */ ae_matrix* x,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t k;


    if( kdt->kcur==0 )
    {
        return;
    }
    if( x->rows<kdt->kcur||x->cols<kdt->nx )
    {
        ae_matrix_set_length(x, kdt->kcur, kdt->nx, _state);
    }
    k = kdt->kcur;
    for(i=0; i<=k-1; i++)
    {
        ae_v_move(&x->ptr.pp_double[i][0], 1, &kdt->xy.ptr.pp_double[kdt->idx.ptr.p_int[i]][kdt->nx], 1, ae_v_len(0,kdt->nx-1));
    }
}


/*************************************************************************
X- and Y-values from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    XY      -   possibly pre-allocated buffer. If XY is too small to store
                result, it is resized. If size(XY) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    XY      -   rows are filled with points: first NX columns with
                X-values, next NY columns - with Y-values.

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsX()             X-values
* KDTreeQueryResultsTags()          tag values
* KDTreeQueryResultsDistances()     distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 X 및 Y 값
입력 매개 변수
    KDT - KD 트리
    XY - 아마도 사전 할당 된 버퍼. XY가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (XY)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    XY - 행은 점으로 채워집니다. 첫 번째 NX 열은
                X 값, 다음 NY 컬럼 - Y 값.
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsX () X 값
* KDTreeQueryResultsTags () 태그 값
* KDTreeQueryResultsDistances () 거리
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsxy(kdtree* kdt,
     /* Real    *//* 실수     */ ae_matrix* xy,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t k;


    if( kdt->kcur==0 )
    {
        return;
    }
    if( xy->rows<kdt->kcur||xy->cols<kdt->nx+kdt->ny )
    {
        ae_matrix_set_length(xy, kdt->kcur, kdt->nx+kdt->ny, _state);
    }
    k = kdt->kcur;
    for(i=0; i<=k-1; i++)
    {
        ae_v_move(&xy->ptr.pp_double[i][0], 1, &kdt->xy.ptr.pp_double[kdt->idx.ptr.p_int[i]][kdt->nx], 1, ae_v_len(0,kdt->nx+kdt->ny-1));
    }
}


/*************************************************************************
Tags from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    Tags    -   possibly pre-allocated buffer. If X is too small to store
                result, it is resized. If size(X) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    Tags    -   filled with tags associated with points,
                or, when no tags were supplied, with zeros

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsX()             X-values
* KDTreeQueryResultsXY()            X- and Y-values
* KDTreeQueryResultsDistances()     distances

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 태그
입력 매개 변수
    KDT - KD 트리
    태그 - 사전 할당 된 버퍼 일 수 있습니다. X가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (X)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    태그 - 포인트와 관련된 태그로 채워짐,
                또는 태그가 제공되지 않은 경우 0으로
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsX () X 값
* KDTreeQueryResultsXY () X 및 Y 값
* KDTreeQueryResultsDistances () 거리
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultstags(kdtree* kdt,
     /* Integer *//* 정수 */ ae_vector* tags,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t k;


    if( kdt->kcur==0 )
    {
        return;
    }
    if( tags->cnt<kdt->kcur )
    {
        ae_vector_set_length(tags, kdt->kcur, _state);
    }
    k = kdt->kcur;
    for(i=0; i<=k-1; i++)
    {
        tags->ptr.p_int[i] = kdt->tags.ptr.p_int[kdt->idx.ptr.p_int[i]];
    }
}


/*************************************************************************
Distances from last query

INPUT PARAMETERS
    KDT     -   KD-tree
    R       -   possibly pre-allocated buffer. If X is too small to store
                result, it is resized. If size(X) is enough to store
                result, it is left unchanged.

OUTPUT PARAMETERS
    R       -   filled with distances (in corresponding norm)

NOTES
1. points are ordered by distance from the query point (first = closest)
2. if  XY is larger than required to store result, only leading part  will
   be overwritten; trailing part will be left unchanged. So  if  on  input
   XY = [[A,B],[C,D]], and result is [1,2],  then  on  exit  we  will  get
   XY = [[1,2],[C,D]]. This is done purposely to increase performance;  if
   you want function  to  resize  array  according  to  result  size,  use
   function with same name and suffix 'I'.

SEE ALSO
* KDTreeQueryResultsX()             X-values
* KDTreeQueryResultsXY()            X- and Y-values
* KDTreeQueryResultsTags()          tag values

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 거리
입력 매개 변수
    KDT - KD 트리
    R - 사전 할당 된 버퍼. X가 너무 작아서 저장할 수없는 경우
                결과, 크기가 조정됩니다. 크기 (X)가 저장하기에 충분하면
                결과, 변경되지 않습니다.
출력 매개 변수
    R - 거리로 채워짐 (해당 기준)
노트
1. 포인트는 쿼리 포인트로부터 거리에 따라 정렬됩니다 (첫 번째 = 가장 가까운 위치).
2. XY가 결과를 저장하는 데 필요한 것보다 큰 경우 선두 부분 만
   덮어 쓰기; 후행 부분은 변경되지 않습니다. 따라서 입력시
   XY = [[A, B], [C, D]]이고 결과는 [1,2]입니다.
   XY = [[1,2], [C, D]]. 이는 성능을 향상시키기 위해 의도적으로 수행됩니다. 만약
   결과 크기에 따라 배열의 크기를 조정하는 함수가 필요하다.
   함수는 동일한 이름과 접미사 'I'를 사용합니다.
관련 항목
* KDTreeQueryResultsX () X 값
* KDTreeQueryResultsXY () X 및 Y 값
* KDTreeQueryResultsTags () 태그 값
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsdistances(kdtree* kdt,
     /* Real    *//* 실수     */ ae_vector* r,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t k;


    if( kdt->kcur==0 )
    {
        return;
    }
    if( r->cnt<kdt->kcur )
    {
        ae_vector_set_length(r, kdt->kcur, _state);
    }
    k = kdt->kcur;
    
    /*
     * unload norms
     *
     * Abs() call is used to handle cases with negative norms
     * (generated during KFN requests)
     */
    /*
     * 언로드 규범
     *
     * Abs () 호출은 부정적인 규범을 가진 사례를 처리하는 데 사용됩니다.
     * (KFN 요청시 생성)
     */
    if( kdt->normtype==0 )
    {
        for(i=0; i<=k-1; i++)
        {
            r->ptr.p_double[i] = ae_fabs(kdt->r.ptr.p_double[i], _state);
        }
    }
    if( kdt->normtype==1 )
    {
        for(i=0; i<=k-1; i++)
        {
            r->ptr.p_double[i] = ae_fabs(kdt->r.ptr.p_double[i], _state);
        }
    }
    if( kdt->normtype==2 )
    {
        for(i=0; i<=k-1; i++)
        {
            r->ptr.p_double[i] = ae_sqrt(ae_fabs(kdt->r.ptr.p_double[i], _state), _state);
        }
    }
}


/*************************************************************************
X-values from last query; 'interactive' variant for languages like  Python
which   support    constructs   like  "X = KDTreeQueryResultsXI(KDT)"  and
interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 X 값; Python과 같은 언어를위한 'interactive'variant
"X = KDTreeQueryResultsXI (KDT)"와 같은 구조를 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsxi(kdtree* kdt,
     /* Real    *//* 실수    */ ae_matrix* x,
     ae_state *_state)
{

    ae_matrix_clear(x);

    kdtreequeryresultsx(kdt, x, _state);
}


/*************************************************************************
XY-values from last query; 'interactive' variant for languages like Python
which   support    constructs   like "XY = KDTreeQueryResultsXYI(KDT)" and
interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 XY 값; Python과 같은 언어를위한 'interactive'variant
"XY = KDTreeQueryResultsXYI (KDT)"와 같은 구문을 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsxyi(kdtree* kdt,
     /* Real    *//* 실수    */ ae_matrix* xy,
     ae_state *_state)
{

    ae_matrix_clear(xy);

    kdtreequeryresultsxy(kdt, xy, _state);
}


/*************************************************************************
Tags  from  last  query;  'interactive' variant for languages like  Python
which  support  constructs  like "Tags = KDTreeQueryResultsTagsI(KDT)" and
interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리의 태그. Python과 같은 언어를위한 'interactive'variant
"Tags = KDTreeQueryResultsTagsI (KDT)"와 같은 구조를 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultstagsi(kdtree* kdt,
     /* Integer *//* 정수 */ ae_vector* tags,
     ae_state *_state)
{

    ae_vector_clear(tags);

    kdtreequeryresultstags(kdt, tags, _state);
}


/*************************************************************************
Distances from last query; 'interactive' variant for languages like Python
which  support  constructs   like  "R = KDTreeQueryResultsDistancesI(KDT)"
and interactive mode of interpreter.

This function allocates new array on each call,  so  it  is  significantly
slower than its 'non-interactive' counterpart, but it is  more  convenient
when you call it from command line.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
마지막 쿼리로부터의 거리; Python과 같은 언어를위한 'interactive'variant
"R = KDTreeQueryResultsDistancesI (KDT)"와 같은 구문을 지원합니다.
인터프리터 인터랙티브 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
void kdtreequeryresultsdistancesi(kdtree* kdt,
     /* Real    *//* 실수    */ ae_vector* r,
     ae_state *_state)
{

    ae_vector_clear(r);

    kdtreequeryresultsdistances(kdt, r, _state);
}


/*************************************************************************
Serializer: allocation

  -- ALGLIB --
     Copyright 14.03.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
직렬화 기 : 할당
  - ALGLIB -
     Copyright 14.03.2011 Bochkanov Sergey
**************************************************************************/
void kdtreealloc(ae_serializer* s, kdtree* tree, ae_state *_state)
{


    
    /*
     * Header
     */
    /*
     * 머리글
     */
    ae_serializer_alloc_entry(s);
    ae_serializer_alloc_entry(s);
    
    /*
     * Data
     */
    /*
     * 데이터
     */
    ae_serializer_alloc_entry(s);
    ae_serializer_alloc_entry(s);
    ae_serializer_alloc_entry(s);
    ae_serializer_alloc_entry(s);
    allocrealmatrix(s, &tree->xy, -1, -1, _state);
    allocintegerarray(s, &tree->tags, -1, _state);
    allocrealarray(s, &tree->boxmin, -1, _state);
    allocrealarray(s, &tree->boxmax, -1, _state);
    allocintegerarray(s, &tree->nodes, -1, _state);
    allocrealarray(s, &tree->splits, -1, _state);
}


/*************************************************************************
Serializer: serialization

  -- ALGLIB --
     Copyright 14.03.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
직렬화 기 : 직렬화
  - ALGLIB -
     Copyright 14.03.2011 Bochkanov Sergey
**************************************************************************/
void kdtreeserialize(ae_serializer* s, kdtree* tree, ae_state *_state)
{


    
    /*
     * Header
     */
    /*
     * 머리글
     */
    ae_serializer_serialize_int(s, getkdtreeserializationcode(_state), _state);
    ae_serializer_serialize_int(s, nearestneighbor_kdtreefirstversion, _state);
    
    /*
     * Data
     */
    /*
     * 데이터
     */
    ae_serializer_serialize_int(s, tree->n, _state);
    ae_serializer_serialize_int(s, tree->nx, _state);
    ae_serializer_serialize_int(s, tree->ny, _state);
    ae_serializer_serialize_int(s, tree->normtype, _state);
    serializerealmatrix(s, &tree->xy, -1, -1, _state);
    serializeintegerarray(s, &tree->tags, -1, _state);
    serializerealarray(s, &tree->boxmin, -1, _state);
    serializerealarray(s, &tree->boxmax, -1, _state);
    serializeintegerarray(s, &tree->nodes, -1, _state);
    serializerealarray(s, &tree->splits, -1, _state);
}


/*************************************************************************
Serializer: unserialization

  -- ALGLIB --
     Copyright 14.03.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
직렬화 기 : 직렬화 해제
  - ALGLIB -
     Copyright 14.03.2011 Bochkanov Sergey
**************************************************************************/
void kdtreeunserialize(ae_serializer* s, kdtree* tree, ae_state *_state)
{
    ae_int_t i0;
    ae_int_t i1;

    _kdtree_clear(tree);

    
    /*
     * check correctness of header
     */
    /*
     * 헤더의 정확성 검사
     */
    ae_serializer_unserialize_int(s, &i0, _state);
    ae_assert(i0==getkdtreeserializationcode(_state), "KDTreeUnserialize: stream header corrupted", _state);
    ae_serializer_unserialize_int(s, &i1, _state);
    ae_assert(i1==nearestneighbor_kdtreefirstversion, "KDTreeUnserialize: stream header corrupted", _state);
    
    /*
     * Unserialize data
     */
    /*
     * 데이터 병합 해제
     */
    ae_serializer_unserialize_int(s, &tree->n, _state);
    ae_serializer_unserialize_int(s, &tree->nx, _state);
    ae_serializer_unserialize_int(s, &tree->ny, _state);
    ae_serializer_unserialize_int(s, &tree->normtype, _state);
    unserializerealmatrix(s, &tree->xy, _state);
    unserializeintegerarray(s, &tree->tags, _state);
    unserializerealarray(s, &tree->boxmin, _state);
    unserializerealarray(s, &tree->boxmax, _state);
    unserializeintegerarray(s, &tree->nodes, _state);
    unserializerealarray(s, &tree->splits, _state);
    nearestneighbor_kdtreealloctemporaries(tree, tree->n, tree->nx, tree->ny, _state);
}


/*************************************************************************
Rearranges nodes [I1,I2) using partition in D-th dimension with S as threshold.
Returns split position I3: [I1,I3) and [I3,I2) are created as result.

This subroutine doesn't create tree structures, just rearranges nodes.
*************************************************************************/
/**************************************************************************
임계 값을 S로하는 D 차원의 분할 영역을 사용하여 노드 [I1, I2]를 다시 정렬합니다.
분할 위치 I3을 반환합니다 : [I1, I3) 및 [I3, I2]가 결과로 생성됩니다.
이 서브 루틴은 트리 구조를 생성하지 않고 단지 노드를 재정렬합니다.
**************************************************************************/
static void nearestneighbor_kdtreesplit(kdtree* kdt,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t d,
     double s,
     ae_int_t* i3,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t ileft;
    ae_int_t iright;
    double v;

    *i3 = 0;

    ae_assert(kdt->n>0, "KDTreeSplit: internal error", _state);
    
    /*
     * split XY/Tags in two parts:
     * * [ILeft,IRight] is non-processed part of XY/Tags
     *
     * After cycle is done, we have Ileft=IRight. We deal with
     * this element separately.
     *
     * After this, [I1,ILeft) contains left part, and [ILeft,I2)
     * contains right part.
     */
    /*
     * 두 부분으로 XY / 태그 분할 :
     * * [ILeft, IRight]는 XY / 태그의 처리되지 않은 부분입니다.
     *
     * 사이클이 끝나면 Ileft = IRight가됩니다. 우리는
     *이 요소는 별도로.
     *
     * 이후, [I1, ILeft]는 왼쪽 부분을 포함하고 [ILeft, I2]
     * 오른쪽 부분을 포함합니다.
     */
    ileft = i1;
    iright = i2-1;
    while(ileft<iright)
    {
        if( ae_fp_less_eq(kdt->xy.ptr.pp_double[ileft][d],s) )
        {
            
            /*
             * XY[ILeft] is on its place.
             * Advance ILeft.
             */
            /*
             * XY [ILeft]가 있습니다.
             * 사전 ILeft.
             */
            ileft = ileft+1;
        }
        else
        {
            
            /*
             * XY[ILeft,..] must be at IRight.
             * Swap and advance IRight.
             */
            /*
             * XY [ILeft, ..]는 IRight에 있어야합니다.
             * 스왑 및 IRight 사전.
             */
            for(i=0; i<=2*kdt->nx+kdt->ny-1; i++)
            {
                v = kdt->xy.ptr.pp_double[ileft][i];
                kdt->xy.ptr.pp_double[ileft][i] = kdt->xy.ptr.pp_double[iright][i];
                kdt->xy.ptr.pp_double[iright][i] = v;
            }
            j = kdt->tags.ptr.p_int[ileft];
            kdt->tags.ptr.p_int[ileft] = kdt->tags.ptr.p_int[iright];
            kdt->tags.ptr.p_int[iright] = j;
            iright = iright-1;
        }
    }
    if( ae_fp_less_eq(kdt->xy.ptr.pp_double[ileft][d],s) )
    {
        ileft = ileft+1;
    }
    else
    {
        iright = iright-1;
    }
    *i3 = ileft;
}


/*************************************************************************
Recursive kd-tree generation subroutine.

PARAMETERS
    KDT         tree
    NodesOffs   unused part of Nodes[] which must be filled by tree
    SplitsOffs  unused part of Splits[]
    I1, I2      points from [I1,I2) are processed
    
NodesOffs[] and SplitsOffs[] must be large enough.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
재귀 kd 트리 생성 서브 루틴.
매개 변수
    KDT 트리
    노드는 트리로 채워야하는 노드 []의 사용되지 않는 부분을 비 웁니다.
    Splits []의 사용하지 않는 부분을 SplitsOffs합니다.
    I1, [I1, I2]로부터의 I2 포인트는
    
NodesOffs []와 SplitsOffs []는 충분히 커야합니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
static void nearestneighbor_kdtreegeneratetreerec(kdtree* kdt,
     ae_int_t* nodesoffs,
     ae_int_t* splitsoffs,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t maxleafsize,
     ae_state *_state)
{
    ae_int_t n;
    ae_int_t nx;
    ae_int_t ny;
    ae_int_t i;
    ae_int_t j;
    ae_int_t oldoffs;
    ae_int_t i3;
    ae_int_t cntless;
    ae_int_t cntgreater;
    double minv;
    double maxv;
    ae_int_t minidx;
    ae_int_t maxidx;
    ae_int_t d;
    double ds;
    double s;
    double v;
    double v0;
    double v1;


    ae_assert(kdt->n>0, "KDTreeGenerateTreeRec: internal error", _state);
    ae_assert(i2>i1, "KDTreeGenerateTreeRec: internal error", _state);
    
    /*
     * Generate leaf if needed
     */
    /*
     * 필요한 경우 리프 생성
     */
    if( i2-i1<=maxleafsize )
    {
        kdt->nodes.ptr.p_int[*nodesoffs+0] = i2-i1;
        kdt->nodes.ptr.p_int[*nodesoffs+1] = i1;
        *nodesoffs = *nodesoffs+2;
        return;
    }
    
    /*
     * Load values for easier access
     */
    /*
     *보다 쉽게 ​​액세스 할 수 있도록로드 값
     */
    nx = kdt->nx;
    ny = kdt->ny;
    
    /*
     * Select dimension to split:
     * * D is a dimension number
     * In case bounding box has zero size, we enforce creation of the leaf node.
     */
    /*
     * 분할 할 차원 선택 :
     * * D는 치수 숫자입니다.
     * 경계 상자의 크기가 0 인 경우 리프 노드 생성을 시행합니다.
     */
    d = 0;
    ds = kdt->curboxmax.ptr.p_double[0]-kdt->curboxmin.ptr.p_double[0];
    for(i=1; i<=nx-1; i++)
    {
        v = kdt->curboxmax.ptr.p_double[i]-kdt->curboxmin.ptr.p_double[i];
        if( ae_fp_greater(v,ds) )
        {
            ds = v;
            d = i;
        }
    }
    if( ae_fp_eq(ds,0) )
    {
        kdt->nodes.ptr.p_int[*nodesoffs+0] = i2-i1;
        kdt->nodes.ptr.p_int[*nodesoffs+1] = i1;
        *nodesoffs = *nodesoffs+2;
        return;
    }
    
    /*
     * Select split position S using sliding midpoint rule,
     * rearrange points into [I1,I3) and [I3,I2).
     *
     * In case all points has same value of D-th component
     * (MinV=MaxV) we enforce D-th dimension of bounding
     * box to become exactly zero and repeat tree construction.
     */
    /*
     * 슬라이딩 중간 점 규칙을 사용하여 분할 위치 S 선택,
     * [I1, I3) 및 [I3, I2]로 포인트 재배치.
     *
     * 모든 점의 D 번째 성분 값이 같은 경우
     * (MinV = MaxV) 경계의 D 번째 차원을 시행합니다.
     * 상자가 정확히 0이되고 트리 구조가 반복됩니다.
     */
    s = kdt->curboxmin.ptr.p_double[d]+0.5*ds;
    ae_v_move(&kdt->buf.ptr.p_double[0], 1, &kdt->xy.ptr.pp_double[i1][d], kdt->xy.stride, ae_v_len(0,i2-i1-1));
    n = i2-i1;
    cntless = 0;
    cntgreater = 0;
    minv = kdt->buf.ptr.p_double[0];
    maxv = kdt->buf.ptr.p_double[0];
    minidx = i1;
    maxidx = i1;
    for(i=0; i<=n-1; i++)
    {
        v = kdt->buf.ptr.p_double[i];
        if( ae_fp_less(v,minv) )
        {
            minv = v;
            minidx = i1+i;
        }
        if( ae_fp_greater(v,maxv) )
        {
            maxv = v;
            maxidx = i1+i;
        }
        if( ae_fp_less(v,s) )
        {
            cntless = cntless+1;
        }
        if( ae_fp_greater(v,s) )
        {
            cntgreater = cntgreater+1;
        }
    }
    if( ae_fp_eq(minv,maxv) )
    {
        
        /*
         * In case all points has same value of D-th component
         * (MinV=MaxV) we enforce D-th dimension of bounding
         * box to become exactly zero and repeat tree construction.
         */
        /*
         * 모든 점의 D 번째 성분 값이 같은 경우
         * (MinV = MaxV) 경계의 D 번째 차원을 시행합니다.
         * 상자가 정확히 0이되고 트리 구조가 반복됩니다.
         */
        v0 = kdt->curboxmin.ptr.p_double[d];
        v1 = kdt->curboxmax.ptr.p_double[d];
        kdt->curboxmin.ptr.p_double[d] = minv;
        kdt->curboxmax.ptr.p_double[d] = maxv;
        nearestneighbor_kdtreegeneratetreerec(kdt, nodesoffs, splitsoffs, i1, i2, maxleafsize, _state);
        kdt->curboxmin.ptr.p_double[d] = v0;
        kdt->curboxmax.ptr.p_double[d] = v1;
        return;
    }
    if( cntless>0&&cntgreater>0 )
    {
        
        /*
         * normal midpoint split
         */
        /*
         * 정상 중간 점 분리
         */
        nearestneighbor_kdtreesplit(kdt, i1, i2, d, s, &i3, _state);
    }
    else
    {
        
        /*
         * sliding midpoint
         */
        /*
         * 미끄럼 중점
         */
        if( cntless==0 )
        {
            
            /*
             * 1. move split to MinV,
             * 2. place one point to the left bin (move to I1),
             *    others - to the right bin
             */
            /*
             * 1. MinV로 분할 이동,
             * 2. 왼쪽 빈에 1 포인트를 놓습니다 (I1로 이동).
             * 기타 - 오른쪽 빈에
             */
            s = minv;
            if( minidx!=i1 )
            {
                for(i=0; i<=2*nx+ny-1; i++)
                {
                    v = kdt->xy.ptr.pp_double[minidx][i];
                    kdt->xy.ptr.pp_double[minidx][i] = kdt->xy.ptr.pp_double[i1][i];
                    kdt->xy.ptr.pp_double[i1][i] = v;
                }
                j = kdt->tags.ptr.p_int[minidx];
                kdt->tags.ptr.p_int[minidx] = kdt->tags.ptr.p_int[i1];
                kdt->tags.ptr.p_int[i1] = j;
            }
            i3 = i1+1;
        }
        else
        {
            
            /*
             * 1. move split to MaxV,
             * 2. place one point to the right bin (move to I2-1),
             *    others - to the left bin
             */
            /*
             * 1. MaxV로 분할 이동,
             * 2. 하나의 점을 오른쪽 bin에 놓습니다 (I2-1로 이동).
             * 다른 사람 - 왼쪽 빈에
             */
            s = maxv;
            if( maxidx!=i2-1 )
            {
                for(i=0; i<=2*nx+ny-1; i++)
                {
                    v = kdt->xy.ptr.pp_double[maxidx][i];
                    kdt->xy.ptr.pp_double[maxidx][i] = kdt->xy.ptr.pp_double[i2-1][i];
                    kdt->xy.ptr.pp_double[i2-1][i] = v;
                }
                j = kdt->tags.ptr.p_int[maxidx];
                kdt->tags.ptr.p_int[maxidx] = kdt->tags.ptr.p_int[i2-1];
                kdt->tags.ptr.p_int[i2-1] = j;
            }
            i3 = i2-1;
        }
    }
    
    /*
     * Generate 'split' node
     */
    /*
     * '분할'노드 생성
     */
    kdt->nodes.ptr.p_int[*nodesoffs+0] = 0;
    kdt->nodes.ptr.p_int[*nodesoffs+1] = d;
    kdt->nodes.ptr.p_int[*nodesoffs+2] = *splitsoffs;
    kdt->splits.ptr.p_double[*splitsoffs+0] = s;
    oldoffs = *nodesoffs;
    *nodesoffs = *nodesoffs+nearestneighbor_splitnodesize;
    *splitsoffs = *splitsoffs+1;
    
    /*
     * Recirsive generation:
     * * update CurBox
     * * call subroutine
     * * restore CurBox
     */
    /*
     * 재순환 세대 :
     * * CurBox 업데이트
     * * call 서브 루틴
     * * CurBox 복원
     */
    kdt->nodes.ptr.p_int[oldoffs+3] = *nodesoffs;
    v = kdt->curboxmax.ptr.p_double[d];
    kdt->curboxmax.ptr.p_double[d] = s;
    nearestneighbor_kdtreegeneratetreerec(kdt, nodesoffs, splitsoffs, i1, i3, maxleafsize, _state);
    kdt->curboxmax.ptr.p_double[d] = v;
    kdt->nodes.ptr.p_int[oldoffs+4] = *nodesoffs;
    v = kdt->curboxmin.ptr.p_double[d];
    kdt->curboxmin.ptr.p_double[d] = s;
    nearestneighbor_kdtreegeneratetreerec(kdt, nodesoffs, splitsoffs, i3, i2, maxleafsize, _state);
    kdt->curboxmin.ptr.p_double[d] = v;
}


/*************************************************************************
Recursive subroutine for NN queries.

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
NN 쿼리를위한 재귀 서브 루틴.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
static void nearestneighbor_kdtreequerynnrec(kdtree* kdt,
     ae_int_t offs,
     ae_state *_state)
{
    double ptdist;
    ae_int_t i;
    ae_int_t j;
    ae_int_t nx;
    ae_int_t i1;
    ae_int_t i2;
    ae_int_t d;
    double s;
    double v;
    double t1;
    ae_int_t childbestoffs;
    ae_int_t childworstoffs;
    ae_int_t childoffs;
    double prevdist;
    ae_bool todive;
    ae_bool bestisleft;
    ae_bool updatemin;


    ae_assert(kdt->n>0, "KDTreeQueryNNRec: internal error", _state);
    
    /*
     * Leaf node.
     * Process points.
     */
    /*
     * 리프 노드.
     * 프로세스 포인트.
     */
    if( kdt->nodes.ptr.p_int[offs]>0 )
    {
        i1 = kdt->nodes.ptr.p_int[offs+1];
        i2 = i1+kdt->nodes.ptr.p_int[offs];
        for(i=i1; i<=i2-1; i++)
        {
            
            /*
             * Calculate distance
             */
            /*
             * 거리 계산
             */
            ptdist = 0;
            nx = kdt->nx;
            if( kdt->normtype==0 )
            {
                for(j=0; j<=nx-1; j++)
                {
                    ptdist = ae_maxreal(ptdist, ae_fabs(kdt->xy.ptr.pp_double[i][j]-kdt->x.ptr.p_double[j], _state), _state);
                }
            }
            if( kdt->normtype==1 )
            {
                for(j=0; j<=nx-1; j++)
                {
                    ptdist = ptdist+ae_fabs(kdt->xy.ptr.pp_double[i][j]-kdt->x.ptr.p_double[j], _state);
                }
            }
            if( kdt->normtype==2 )
            {
                for(j=0; j<=nx-1; j++)
                {
                    ptdist = ptdist+ae_sqr(kdt->xy.ptr.pp_double[i][j]-kdt->x.ptr.p_double[j], _state);
                }
            }
            
            /*
             * Skip points with zero distance if self-matches are turned off
             */
            /*
             * 자기 일치가 해제 된 경우 거리가 0 인 지점 건너 뛰기
             */
            if( ae_fp_eq(ptdist,0)&&!kdt->selfmatch )
            {
                continue;
            }
            
            /*
             * We CAN'T process point if R-criterion isn't satisfied,
             * i.e. (RNeeded<>0) AND (PtDist>R).
             */
            /*
             * R- 기준이 충족되지 않으면 포인트를 처리 할 수 ​​없습니다.
             * 즉 (RNeeded <> 0) AND (PtDist> R).
             */
            if( ae_fp_eq(kdt->rneeded,0)||ae_fp_less_eq(ptdist,kdt->rneeded) )
            {
                
                /*
                 * R-criterion is satisfied, we must either:
                 * * replace worst point, if (KNeeded<>0) AND (KCur=KNeeded)
                 *   (or skip, if worst point is better)
                 * * add point without replacement otherwise
                 */
                /*
                 * R- 기준이 충족되면 다음 중 하나를 수행해야합니다.
                 * (KNeeded <> 0) AND (KCur = KNeeded) 인 경우 * 최악의 점을 바꿉니다.
                 * (또는 최악의 점이 더 좋으면 건너 뜁니다.)
                 * * 그렇지 않으면 교체하지 않고 점을 추가합니다.
                 */
                if( kdt->kcur<kdt->kneeded||kdt->kneeded==0 )
                {
                    
                    /*
                     * add current point to heap without replacement
                     */
                    /*
                     * 현재 위치를 교체하지 않고 힙에 추가합니다.
                     */
                    tagheappushi(&kdt->r, &kdt->idx, &kdt->kcur, ptdist, i, _state);
                }
                else
                {
                    
                    /*
                     * New points are added or not, depending on their distance.
                     * If added, they replace element at the top of the heap
                     */
                    /*
                     * 거리에 따라 새로운 포인트가 추가되거나 삭제됩니다.
                     * 추가 된 경우 힙의 맨 위에있는 요소를 대체합니다.
                     */
                    if( ae_fp_less(ptdist,kdt->r.ptr.p_double[0]) )
                    {
                        if( kdt->kneeded==1 )
                        {
                            kdt->idx.ptr.p_int[0] = i;
                            kdt->r.ptr.p_double[0] = ptdist;
                        }
                        else
                        {
                            tagheapreplacetopi(&kdt->r, &kdt->idx, kdt->kneeded, ptdist, i, _state);
                        }
                    }
                }
            }
        }
        return;
    }
    
    /*
     * Simple split
     */
    /*
     * 단순 분할
     */
    if( kdt->nodes.ptr.p_int[offs]==0 )
    {
        
        /*
         * Load:
         * * D  dimension to split
         * * S  split position
         */
        /*
         *로드 :
         * * 분할 할 차원
         * * 분할 위치
         */
        d = kdt->nodes.ptr.p_int[offs+1];
        s = kdt->splits.ptr.p_double[kdt->nodes.ptr.p_int[offs+2]];
        
        /*
         * Calculate:
         * * ChildBestOffs      child box with best chances
         * * ChildWorstOffs     child box with worst chances
         */
        /*
         * 계산하다:
         * 기회가 가장 많은 ChildBestOffs 자식 상자
         최악의 기회를 가진 * ChildWorstOffs 자식 상자
         */
        if( ae_fp_less_eq(kdt->x.ptr.p_double[d],s) )
        {
            childbestoffs = kdt->nodes.ptr.p_int[offs+3];
            childworstoffs = kdt->nodes.ptr.p_int[offs+4];
            bestisleft = ae_true;
        }
        else
        {
            childbestoffs = kdt->nodes.ptr.p_int[offs+4];
            childworstoffs = kdt->nodes.ptr.p_int[offs+3];
            bestisleft = ae_false;
        }
        
        /*
         * Navigate through childs
         */
        /*
         * 차일드 탐색
         */
        for(i=0; i<=1; i++)
        {
            
            /*
             * Select child to process:
             * * ChildOffs      current child offset in Nodes[]
             * * UpdateMin      whether minimum or maximum value
             *                  of bounding box is changed on update
             */
            /*
             * 처리 할 아동을 선택하십시오 :
             * * ChildOffs 노드에서 현재 자식 오프셋 []
             * * UpdateMin 최소값 또는 최대 값
             업데이트시 테두리 상자의 *가 변경됩니다.
             */
            if( i==0 )
            {
                childoffs = childbestoffs;
                updatemin = !bestisleft;
            }
            else
            {
                updatemin = bestisleft;
                childoffs = childworstoffs;
            }
            
            /*
             * Update bounding box and current distance
             */
            /*
             * 경계 상자 및 현재 거리 업데이트
             */
            if( updatemin )
            {
                prevdist = kdt->curdist;
                t1 = kdt->x.ptr.p_double[d];
                v = kdt->curboxmin.ptr.p_double[d];
                if( ae_fp_less_eq(t1,s) )
                {
                    if( kdt->normtype==0 )
                    {
                        kdt->curdist = ae_maxreal(kdt->curdist, s-t1, _state);
                    }
                    if( kdt->normtype==1 )
                    {
                        kdt->curdist = kdt->curdist-ae_maxreal(v-t1, 0, _state)+s-t1;
                    }
                    if( kdt->normtype==2 )
                    {
                        kdt->curdist = kdt->curdist-ae_sqr(ae_maxreal(v-t1, 0, _state), _state)+ae_sqr(s-t1, _state);
                    }
                }
                kdt->curboxmin.ptr.p_double[d] = s;
            }
            else
            {
                prevdist = kdt->curdist;
                t1 = kdt->x.ptr.p_double[d];
                v = kdt->curboxmax.ptr.p_double[d];
                if( ae_fp_greater_eq(t1,s) )
                {
                    if( kdt->normtype==0 )
                    {
                        kdt->curdist = ae_maxreal(kdt->curdist, t1-s, _state);
                    }
                    if( kdt->normtype==1 )
                    {
                        kdt->curdist = kdt->curdist-ae_maxreal(t1-v, 0, _state)+t1-s;
                    }
                    if( kdt->normtype==2 )
                    {
                        kdt->curdist = kdt->curdist-ae_sqr(ae_maxreal(t1-v, 0, _state), _state)+ae_sqr(t1-s, _state);
                    }
                }
                kdt->curboxmax.ptr.p_double[d] = s;
            }
            
            /*
             * Decide: to dive into cell or not to dive
             */
            /*
             * 결정 : 세포에 뛰어 들거나 잠수하지 마라.
             */
            if( ae_fp_neq(kdt->rneeded,0)&&ae_fp_greater(kdt->curdist,kdt->rneeded) )
            {
                todive = ae_false;
            }
            else
            {
                if( kdt->kcur<kdt->kneeded||kdt->kneeded==0 )
                {
                    
                    /*
                     * KCur<KNeeded (i.e. not all points are found)
                     */
                    /*
                     * KCur <KNeeded (즉, 모든 포인트가 발견되지는 않음)
                     */
                    todive = ae_true;
                }
                else
                {
                    
                    /*
                     * KCur=KNeeded, decide to dive or not to dive
                     * using point position relative to bounding box.
                     */
                    /*
                     * KCur = KNeeded, 다이빙을 결정하거나 다이빙하지 않기로 결정
                     * 경계 상자를 기준으로 점 위치를 사용합니다.
                     */
                    todive = ae_fp_less_eq(kdt->curdist,kdt->r.ptr.p_double[0]*kdt->approxf);
                }
            }
            if( todive )
            {
                nearestneighbor_kdtreequerynnrec(kdt, childoffs, _state);
            }
            
            /*
             * Restore bounding box and distance
             */
            /*
             * 경계 상자 및 거리 복원
             */
            if( updatemin )
            {
                kdt->curboxmin.ptr.p_double[d] = v;
            }
            else
            {
                kdt->curboxmax.ptr.p_double[d] = v;
            }
            kdt->curdist = prevdist;
        }
        return;
    }
}


/*************************************************************************
Copies X[] to KDT.X[]
Loads distance from X[] to bounding box.
Initializes CurBox[].

  -- ALGLIB --
     Copyright 28.02.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
X []를 KDT.X []에 복사합니다.
X []에서 경계 상자까지의 거리를로드합니다.
CurBox []를 초기화합니다.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
**************************************************************************/
static void nearestneighbor_kdtreeinitbox(kdtree* kdt,
     /* Real    *//* 실수     */ ae_vector* x,
     ae_state *_state)
{
    ae_int_t i;
    double vx;
    double vmin;
    double vmax;


    ae_assert(kdt->n>0, "KDTreeInitBox: internal error", _state);
    
    /*
     * calculate distance from point to current bounding box
     */
    /*
     * 점에서 현재 경계 상자까지의 거리를 계산합니다.
     */
    kdt->curdist = 0;
    if( kdt->normtype==0 )
    {
        for(i=0; i<=kdt->nx-1; i++)
        {
            vx = x->ptr.p_double[i];
            vmin = kdt->boxmin.ptr.p_double[i];
            vmax = kdt->boxmax.ptr.p_double[i];
            kdt->x.ptr.p_double[i] = vx;
            kdt->curboxmin.ptr.p_double[i] = vmin;
            kdt->curboxmax.ptr.p_double[i] = vmax;
            if( ae_fp_less(vx,vmin) )
            {
                kdt->curdist = ae_maxreal(kdt->curdist, vmin-vx, _state);
            }
            else
            {
                if( ae_fp_greater(vx,vmax) )
                {
                    kdt->curdist = ae_maxreal(kdt->curdist, vx-vmax, _state);
                }
            }
        }
    }
    if( kdt->normtype==1 )
    {
        for(i=0; i<=kdt->nx-1; i++)
        {
            vx = x->ptr.p_double[i];
            vmin = kdt->boxmin.ptr.p_double[i];
            vmax = kdt->boxmax.ptr.p_double[i];
            kdt->x.ptr.p_double[i] = vx;
            kdt->curboxmin.ptr.p_double[i] = vmin;
            kdt->curboxmax.ptr.p_double[i] = vmax;
            if( ae_fp_less(vx,vmin) )
            {
                kdt->curdist = kdt->curdist+vmin-vx;
            }
            else
            {
                if( ae_fp_greater(vx,vmax) )
                {
                    kdt->curdist = kdt->curdist+vx-vmax;
                }
            }
        }
    }
    if( kdt->normtype==2 )
    {
        for(i=0; i<=kdt->nx-1; i++)
        {
            vx = x->ptr.p_double[i];
            vmin = kdt->boxmin.ptr.p_double[i];
            vmax = kdt->boxmax.ptr.p_double[i];
            kdt->x.ptr.p_double[i] = vx;
            kdt->curboxmin.ptr.p_double[i] = vmin;
            kdt->curboxmax.ptr.p_double[i] = vmax;
            if( ae_fp_less(vx,vmin) )
            {
                kdt->curdist = kdt->curdist+ae_sqr(vmin-vx, _state);
            }
            else
            {
                if( ae_fp_greater(vx,vmax) )
                {
                    kdt->curdist = kdt->curdist+ae_sqr(vx-vmax, _state);
                }
            }
        }
    }
}


/*************************************************************************
This function allocates all dataset-independent array  fields  of  KDTree,
i.e.  such  array  fields  that  their dimensions do not depend on dataset
size.

This function do not sets KDT.NX or KDT.NY - it just allocates arrays

  -- ALGLIB --
     Copyright 14.03.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 KDTree의 모든 데이터 집합 독립 배열 필드를 할당하며,
즉, 차원이 데이터 집합에 의존하지 않는 배열 필드
크기.
이 함수는 KDT.NX 또는 KDT.NY를 설정하지 않습니다. 단지 배열을 할당합니다.
  - ALGLIB -
     Copyright 14.03.2011 Bochkanov Sergey
**************************************************************************/
static void nearestneighbor_kdtreeallocdatasetindependent(kdtree* kdt,
     ae_int_t nx,
     ae_int_t ny,
     ae_state *_state)
{
    (void)ny;

    ae_assert(kdt->n>0, "KDTreeAllocDatasetIndependent: internal error", _state);
    ae_vector_set_length(&kdt->x, nx, _state);
    ae_vector_set_length(&kdt->boxmin, nx, _state);
    ae_vector_set_length(&kdt->boxmax, nx, _state);
    ae_vector_set_length(&kdt->curboxmin, nx, _state);
    ae_vector_set_length(&kdt->curboxmax, nx, _state);
}


/*************************************************************************
This function allocates all dataset-dependent array fields of KDTree, i.e.
such array fields that their dimensions depend on dataset size.

This function do not sets KDT.N, KDT.NX or KDT.NY -
it just allocates arrays.

  -- ALGLIB --
     Copyright 14.03.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 KDTree의 모든 데이터 집합 종속 배열 필드를 할당합니다.
차원이 데이터 집합 크기에 의존하는 배열 필드
이 함수는 KDT.N, KDT.NX 또는 KDT.NY를 설정하지 않습니다.
그냥 배열을 할당합니다.
  - ALGLIB -
     Copyright 14.03.2011 Bochkanov Sergey
**************************************************************************/
static void nearestneighbor_kdtreeallocdatasetdependent(kdtree* kdt,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_state *_state)
{


    ae_assert(n>0, "KDTreeAllocDatasetDependent: internal error", _state);
    ae_matrix_set_length(&kdt->xy, n, 2*nx+ny, _state);
    ae_vector_set_length(&kdt->tags, n, _state);
    ae_vector_set_length(&kdt->idx, n, _state);
    ae_vector_set_length(&kdt->r, n, _state);
    ae_vector_set_length(&kdt->x, nx, _state);
    ae_vector_set_length(&kdt->buf, ae_maxint(n, nx, _state), _state);
    ae_vector_set_length(&kdt->nodes, nearestneighbor_splitnodesize*2*n, _state);
    ae_vector_set_length(&kdt->splits, 2*n, _state);
}


/*************************************************************************
This function allocates temporaries.

This function do not sets KDT.N, KDT.NX or KDT.NY -
it just allocates arrays.

  -- ALGLIB --
     Copyright 14.03.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 임시 변수를 할당합니다.
이 함수는 KDT.N, KDT.NX 또는 KDT.NY를 설정하지 않습니다.
그냥 배열을 할당합니다.
  - ALGLIB -
     Copyright 14.03.2011 Bochkanov Sergey
**************************************************************************/
static void nearestneighbor_kdtreealloctemporaries(kdtree* kdt,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_state *_state)
{
    (void)ny;

    ae_assert(n>0, "KDTreeAllocTemporaries: internal error", _state);
    ae_vector_set_length(&kdt->x, nx, _state);
    ae_vector_set_length(&kdt->idx, n, _state);
    ae_vector_set_length(&kdt->r, n, _state);
    ae_vector_set_length(&kdt->buf, ae_maxint(n, nx, _state), _state);
    ae_vector_set_length(&kdt->curboxmin, nx, _state);
    ae_vector_set_length(&kdt->curboxmax, nx, _state);
}


ae_bool _kdtree_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    kdtree *p = (kdtree*)_p;
    ae_touch_ptr((void*)p);
    if( !ae_matrix_init(&p->xy, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->tags, 0, DT_INT, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->boxmin, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->boxmax, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->nodes, 0, DT_INT, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->splits, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->idx, 0, DT_INT, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->r, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->buf, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->curboxmin, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->curboxmax, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _kdtree_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    kdtree *dst = (kdtree*)_dst;
    kdtree *src = (kdtree*)_src;
    dst->n = src->n;
    dst->nx = src->nx;
    dst->ny = src->ny;
    dst->normtype = src->normtype;
    if( !ae_matrix_init_copy(&dst->xy, &src->xy, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->tags, &src->tags, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->boxmin, &src->boxmin, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->boxmax, &src->boxmax, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->nodes, &src->nodes, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->splits, &src->splits, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    dst->kneeded = src->kneeded;
    dst->rneeded = src->rneeded;
    dst->selfmatch = src->selfmatch;
    dst->approxf = src->approxf;
    dst->kcur = src->kcur;
    if( !ae_vector_init_copy(&dst->idx, &src->idx, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->r, &src->r, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->buf, &src->buf, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->curboxmin, &src->curboxmin, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->curboxmax, &src->curboxmax, _state, make_automatic) )
        return ae_false;
    dst->curdist = src->curdist;
    dst->debugcounter = src->debugcounter;
    return ae_true;
}


void _kdtree_clear(void* _p)
{
    kdtree *p = (kdtree*)_p;
    ae_touch_ptr((void*)p);
    ae_matrix_clear(&p->xy);
    ae_vector_clear(&p->tags);
    ae_vector_clear(&p->boxmin);
    ae_vector_clear(&p->boxmax);
    ae_vector_clear(&p->nodes);
    ae_vector_clear(&p->splits);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->idx);
    ae_vector_clear(&p->r);
    ae_vector_clear(&p->buf);
    ae_vector_clear(&p->curboxmin);
    ae_vector_clear(&p->curboxmax);
}


void _kdtree_destroy(void* _p)
{
    kdtree *p = (kdtree*)_p;
    ae_touch_ptr((void*)p);
    ae_matrix_destroy(&p->xy);
    ae_vector_destroy(&p->tags);
    ae_vector_destroy(&p->boxmin);
    ae_vector_destroy(&p->boxmax);
    ae_vector_destroy(&p->nodes);
    ae_vector_destroy(&p->splits);
    ae_vector_destroy(&p->x);
    ae_vector_destroy(&p->idx);
    ae_vector_destroy(&p->r);
    ae_vector_destroy(&p->buf);
    ae_vector_destroy(&p->curboxmin);
    ae_vector_destroy(&p->curboxmax);
}



}

