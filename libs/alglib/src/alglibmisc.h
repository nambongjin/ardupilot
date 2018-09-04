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
#ifndef _alglibmisc_pkg_h
#define _alglibmisc_pkg_h
#include "ap.h"
#include "alglibinternal.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
typedef struct
{
    ae_int_t s1;
    ae_int_t s2;
    ae_int_t magicv;
} hqrndstate;
typedef struct
{
    ae_int_t n;
    ae_int_t nx;
    ae_int_t ny;
    ae_int_t normtype;
    ae_matrix xy;
    ae_vector tags;
    ae_vector boxmin;
    ae_vector boxmax;
    ae_vector nodes;
    ae_vector splits;
    ae_vector x;
    ae_int_t kneeded;
    double rneeded;
    ae_bool selfmatch;
    double approxf;
    ae_int_t kcur;
    ae_vector idx;
    ae_vector r;
    ae_vector buf;
    ae_vector curboxmin;
    ae_vector curboxmax;
    double curdist;
    ae_int_t debugcounter;
} kdtree;

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
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
/*************************************************************************
휴대용 고품질의 난수 생성기 상태.
HQRNDRandomize () 또는 HQRNDSeed ()로 초기화됩니다.
전지:
    S1, S2 - 시드 값
    V - 사전 계산 된 값
    MagicV - 국가 구조의 결정 여부를 결정하는 데 사용되는 '마법'값
                    올바르게 초기화되었습니다.
*************************************************************************/

class _hqrndstate_owner
{
public:
    _hqrndstate_owner();
    _hqrndstate_owner(const _hqrndstate_owner &rhs);
    _hqrndstate_owner& operator=(const _hqrndstate_owner &rhs);
    virtual ~_hqrndstate_owner();
    alglib_impl::hqrndstate* c_ptr();
    alglib_impl::hqrndstate* c_ptr() const;
protected:
    alglib_impl::hqrndstate *p_struct;
};
class hqrndstate : public _hqrndstate_owner
{
public:
    hqrndstate();
    hqrndstate(const hqrndstate &rhs);
    hqrndstate& operator=(const hqrndstate &rhs);
    virtual ~hqrndstate();

};

/*************************************************************************

*************************************************************************/
class _kdtree_owner
{
public:
    _kdtree_owner();
    _kdtree_owner(const _kdtree_owner &rhs);
    _kdtree_owner& operator=(const _kdtree_owner &rhs);
    virtual ~_kdtree_owner();
    alglib_impl::kdtree* c_ptr();
    alglib_impl::kdtree* c_ptr() const;
protected:
    alglib_impl::kdtree *p_struct;
};
class kdtree : public _kdtree_owner
{
public:
    kdtree();
    kdtree(const kdtree &rhs);
    kdtree& operator=(const kdtree &rhs);
    virtual ~kdtree();

};

/*************************************************************************
HQRNDState  initialization  with  random  values  which come from standard
RNG.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
HQRNDState 초기화 (표준에서 오는 임의의 값 사용)
RNG.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
void hqrndrandomize(hqrndstate &state);


/*************************************************************************
HQRNDState initialization with seed values

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
시드 값을 사용하는 HQRNDState 초기화
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
void hqrndseed(const ae_int_t s1, const ae_int_t s2, hqrndstate &state);


/*************************************************************************
This function generates random real number in (0,1),
not including interval boundaries

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
이 함수는 (0,1)에 임의의 실수를 생성합니다.
간격 경계를 포함하지 않음
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
double hqrnduniformr(const hqrndstate &state);


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
/*************************************************************************
이 함수는 [0, N]에 임의의 정수를 생성하고,
1. 상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화되어야합니다.
2. N은 매우 큰 숫자를 제외하고는 양수 일 수 있습니다.
   * 32 비트 시스템에서 2 ^ 31에 가깝습니다.
   * 64 비트 시스템에서는 2 ^ 62에 가깝습니다.
   N이 너무 큰 경우 예외가 생성됩니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
ae_int_t hqrnduniformi(const hqrndstate &state, const ae_int_t n);


/*************************************************************************
Random number generator: normal numbers

This function generates one random number from normal distribution.
Its performance is equal to that of HQRNDNormal2()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
난수 생성기 : 정상 수
이 함수는 정규 분포에서 하나의 난수를 생성합니다.
그 성능은 HQRNDNormal2 ()의 성능과 같습니다.
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
double hqrndnormal(const hqrndstate &state);


/*************************************************************************
Random number generator: random X and Y such that X^2+Y^2=1

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
난수 생성기 : X ^ 2 + Y ^ 2 = 1과 같은 임의의 X와 Y
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
void hqrndunit2(const hqrndstate &state, double &x, double &y);


/*************************************************************************
Random number generator: normal numbers

This function generates two independent random numbers from normal
distribution. Its performance is equal to that of HQRNDNormal()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
난수 생성기 : 정상 수
이 함수는 법선으로부터 2 개의 독립 난수를 생성합니다.
분포. 그 성능은 HQRNDNormal ()과 동일합니다.
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************************************/
void hqrndnormal2(const hqrndstate &state, double &x1, double &x2);


/*************************************************************************
Random number generator: exponential distribution

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 11.08.2007 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
난수 생성기 : 지수 분포
상태 구조는 HQRNDRandomize () 또는 HQRNDSeed ()로 초기화해야합니다.
  - ALGLIB -
     저작권 2007 년 11 월 8 일 Bochkanov Sergey
*************************************************************************/
double hqrndexponential(const hqrndstate &state, const double lambdav);


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
/*************************************************************************
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
*************************************************************************/
double hqrnddiscrete(const hqrndstate &state, const real_1d_array &x, const ae_int_t n);


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
/*************************************************************************
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
*************************************************************************/
double hqrndcontinuous(const hqrndstate &state, const real_1d_array &x, const ae_int_t n);

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
/*************************************************************************
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
*************************************************************************/
void kdtreeserialize(kdtree &obj, std::string &s_out);


/*************************************************************************
This function unserializes data structure from string.
*************************************************************************/
/*************************************************************************
이 함수는 문자열에서 데이터 구조를 unserializes.
*************************************************************************/
void kdtreeunserialize(std::string &s_in, kdtree &obj);


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
/*************************************************************************
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
*************************************************************************/
void kdtreebuild(const real_2d_array &xy, const ae_int_t n, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt);
void kdtreebuild(const real_2d_array &xy, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt);


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
/*************************************************************************
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
*************************************************************************/
void kdtreebuildtagged(const real_2d_array &xy, const integer_1d_array &tags, const ae_int_t n, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt);
void kdtreebuildtagged(const real_2d_array &xy, const integer_1d_array &tags, const ae_int_t nx, const ae_int_t ny, const ae_int_t normtype, kdtree &kdt);


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
/*************************************************************************
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
*************************************************************************/
ae_int_t kdtreequeryknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k, const bool selfmatch);
ae_int_t kdtreequeryknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k);


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
/*************************************************************************
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
*************************************************************************/
ae_int_t kdtreequeryrnn(const kdtree &kdt, const real_1d_array &x, const double r, const bool selfmatch);
ae_int_t kdtreequeryrnn(const kdtree &kdt, const real_1d_array &x, const double r);


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
/*************************************************************************
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
*************************************************************************/
ae_int_t kdtreequeryaknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k, const bool selfmatch, const double eps);
ae_int_t kdtreequeryaknn(const kdtree &kdt, const real_1d_array &x, const ae_int_t k, const double eps);


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
/*************************************************************************
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
*************************************************************************/
void kdtreequeryresultsx(const kdtree &kdt, real_2d_array &x);


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
/*************************************************************************
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
*************************************************************************/
void kdtreequeryresultsxy(const kdtree &kdt, real_2d_array &xy);


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
/*************************************************************************
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
*************************************************************************/
void kdtreequeryresultstags(const kdtree &kdt, integer_1d_array &tags);


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
/*************************************************************************
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
*************************************************************************/
void kdtreequeryresultsdistances(const kdtree &kdt, real_1d_array &r);


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
/*************************************************************************
마지막 쿼리의 X 값; Python과 같은 언어를위한 'interactive'variant
"X = KDTreeQueryResultsXI (KDT)"와 같은 구조를 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
*************************************************************************/
void kdtreequeryresultsxi(const kdtree &kdt, real_2d_array &x);


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
/*************************************************************************
마지막 쿼리의 XY 값; Python과 같은 언어를위한 'interactive'variant
"XY = KDTreeQueryResultsXYI (KDT)"와 같은 구문을 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
*************************************************************************/
void kdtreequeryresultsxyi(const kdtree &kdt, real_2d_array &xy);


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
/*************************************************************************
마지막 쿼리의 태그. Python과 같은 언어를위한 'interactive'variant
"Tags = KDTreeQueryResultsTagsI (KDT)"와 같은 구조를 지원하고
대화식 인터프리터 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
*************************************************************************/
void kdtreequeryresultstagsi(const kdtree &kdt, integer_1d_array &tags);


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
/*************************************************************************
마지막 쿼리로부터의 거리; Python과 같은 언어를위한 'interactive'variant
"R = KDTreeQueryResultsDistancesI (KDT)"와 같은 구문을 지원합니다.
인터프리터 인터랙티브 모드.
이 함수는 각 호출에 새로운 배열을 할당하므로 상당히
'비대화 형'대응 제품보다 느리지 만 더 편리합니다.
명령 행에서 호출 할 때.
  - ALGLIB -
     Copyright 28.02.2010 Bochkanov Sergey
*************************************************************************/
void kdtreequeryresultsdistancesi(const kdtree &kdt, real_1d_array &r);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
void hqrndrandomize(hqrndstate* state, ae_state *_state);
void hqrndseed(ae_int_t s1,
     ae_int_t s2,
     hqrndstate* state,
     ae_state *_state);
double hqrnduniformr(hqrndstate* state, ae_state *_state);
ae_int_t hqrnduniformi(hqrndstate* state, ae_int_t n, ae_state *_state);
double hqrndnormal(hqrndstate* state, ae_state *_state);
void hqrndunit2(hqrndstate* state, double* x, double* y, ae_state *_state);
void hqrndnormal2(hqrndstate* state,
     double* x1,
     double* x2,
     ae_state *_state);
double hqrndexponential(hqrndstate* state,
     double lambdav,
     ae_state *_state);
double hqrnddiscrete(hqrndstate* state,
     /* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
double hqrndcontinuous(hqrndstate* state,
     /* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
ae_bool _hqrndstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _hqrndstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _hqrndstate_clear(void* _p);
void _hqrndstate_destroy(void* _p);
void kdtreebuild(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_int_t normtype,
     kdtree* kdt,
     ae_state *_state);
void kdtreebuildtagged(/* Real    */ ae_matrix* xy,
     /* Integer */ ae_vector* tags,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_int_t normtype,
     kdtree* kdt,
     ae_state *_state);
ae_int_t kdtreequeryknn(kdtree* kdt,
     /* Real    */ ae_vector* x,
     ae_int_t k,
     ae_bool selfmatch,
     ae_state *_state);
ae_int_t kdtreequeryrnn(kdtree* kdt,
     /* Real    */ ae_vector* x,
     double r,
     ae_bool selfmatch,
     ae_state *_state);
ae_int_t kdtreequeryaknn(kdtree* kdt,
     /* Real    */ ae_vector* x,
     ae_int_t k,
     ae_bool selfmatch,
     double eps,
     ae_state *_state);
void kdtreequeryresultsx(kdtree* kdt,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void kdtreequeryresultsxy(kdtree* kdt,
     /* Real    */ ae_matrix* xy,
     ae_state *_state);
void kdtreequeryresultstags(kdtree* kdt,
     /* Integer */ ae_vector* tags,
     ae_state *_state);
void kdtreequeryresultsdistances(kdtree* kdt,
     /* Real    */ ae_vector* r,
     ae_state *_state);
void kdtreequeryresultsxi(kdtree* kdt,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void kdtreequeryresultsxyi(kdtree* kdt,
     /* Real    */ ae_matrix* xy,
     ae_state *_state);
void kdtreequeryresultstagsi(kdtree* kdt,
     /* Integer */ ae_vector* tags,
     ae_state *_state);
void kdtreequeryresultsdistancesi(kdtree* kdt,
     /* Real    */ ae_vector* r,
     ae_state *_state);
void kdtreealloc(ae_serializer* s, kdtree* tree, ae_state *_state);
void kdtreeserialize(ae_serializer* s, kdtree* tree, ae_state *_state);
void kdtreeunserialize(ae_serializer* s, kdtree* tree, ae_state *_state);
ae_bool _kdtree_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _kdtree_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _kdtree_clear(void* _p);
void _kdtree_destroy(void* _p);

}
#endif

