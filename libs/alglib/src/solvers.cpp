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
#include "solvers.h"

// disable some irrelevant warnings
// 관련없는 경고를 해제합니다.
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
/////////////////////////////////////////////////////////////////////////
//
// 이 섹션은 C ++ 인터페이스의 구현을 포함한다.
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{


/*************************************************************************

*************************************************************************/
_densesolverreport_owner::_densesolverreport_owner()
{
    p_struct = (alglib_impl::densesolverreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::densesolverreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_densesolverreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_densesolverreport_owner::_densesolverreport_owner(const _densesolverreport_owner &rhs)
{
    p_struct = (alglib_impl::densesolverreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::densesolverreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_densesolverreport_init_copy(p_struct, const_cast<alglib_impl::densesolverreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_densesolverreport_owner& _densesolverreport_owner::operator=(const _densesolverreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_densesolverreport_clear(p_struct);
    if( !alglib_impl::_densesolverreport_init_copy(p_struct, const_cast<alglib_impl::densesolverreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_densesolverreport_owner::~_densesolverreport_owner()
{
    alglib_impl::_densesolverreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::densesolverreport* _densesolverreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::densesolverreport* _densesolverreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::densesolverreport*>(p_struct);
}
densesolverreport::densesolverreport() : _densesolverreport_owner() ,r1(p_struct->r1),rinf(p_struct->rinf)
{
}

densesolverreport::densesolverreport(const densesolverreport &rhs):_densesolverreport_owner(rhs) ,r1(p_struct->r1),rinf(p_struct->rinf)
{
}

densesolverreport& densesolverreport::operator=(const densesolverreport &rhs)
{
    if( this==&rhs )
        return *this;
    _densesolverreport_owner::operator=(rhs);
    return *this;
}

densesolverreport::~densesolverreport()
{
}


/*************************************************************************

*************************************************************************/
_densesolverlsreport_owner::_densesolverlsreport_owner()
{
    p_struct = (alglib_impl::densesolverlsreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::densesolverlsreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_densesolverlsreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_densesolverlsreport_owner::_densesolverlsreport_owner(const _densesolverlsreport_owner &rhs)
{
    p_struct = (alglib_impl::densesolverlsreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::densesolverlsreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_densesolverlsreport_init_copy(p_struct, const_cast<alglib_impl::densesolverlsreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_densesolverlsreport_owner& _densesolverlsreport_owner::operator=(const _densesolverlsreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_densesolverlsreport_clear(p_struct);
    if( !alglib_impl::_densesolverlsreport_init_copy(p_struct, const_cast<alglib_impl::densesolverlsreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_densesolverlsreport_owner::~_densesolverlsreport_owner()
{
    alglib_impl::_densesolverlsreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::densesolverlsreport* _densesolverlsreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::densesolverlsreport* _densesolverlsreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::densesolverlsreport*>(p_struct);
}
densesolverlsreport::densesolverlsreport() : _densesolverlsreport_owner() ,r2(p_struct->r2),cx(&p_struct->cx),n(p_struct->n),k(p_struct->k)
{
}

densesolverlsreport::densesolverlsreport(const densesolverlsreport &rhs):_densesolverlsreport_owner(rhs) ,r2(p_struct->r2),cx(&p_struct->cx),n(p_struct->n),k(p_struct->k)
{
}

densesolverlsreport& densesolverlsreport::operator=(const densesolverlsreport &rhs)
{
    if( this==&rhs )
        return *this;
    _densesolverlsreport_owner::operator=(rhs);
    return *this;
}

densesolverlsreport::~densesolverlsreport()
{
}

/*************************************************************************
Dense solver.

This  subroutine  solves  a  system  A*x=b,  where A is NxN non-denegerate
real matrix, x and b are vectors.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^3) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   return code:
                * -3    A is singular, or VERY close to singular.
                        X is filled by zeros in such cases.
                * -1    N<=0 was passed
                *  1    task is solved (but matrix A may be ill-conditioned,
                        check R1/RInf parameters for condition numbers).
    Rep     -   solver report, see below for more info
    X       -   array[0..N-1], it contains:
                * solution of A*x=b if A is non-singular (well-conditioned
                  or ill-conditioned, but not very close to singular)
                * zeros,  if  A  is  singular  or  VERY  close to singular
                  (in this case Info=-3).

SOLVER REPORT

Subroutine sets following fields of the Rep structure:
* R1        reciprocal of condition number: 1/cond(A), 1-norm.
* RInf      reciprocal of condition number: 1/cond(A), inf-norm.

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 시스템 A * x = b를 해결합니다. 여기서 A는 NxN 비 - 영속
실수 행렬, x와 b는 벡터입니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 3) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - 리턴 코드 :
                * -3 A는 단수이거나 매우 단수에 가깝습니다.
                        이 경우 X는 0으로 채워집니다.
                * -1 N <= 0을 통과했습니다.
                * 1 작업이 해결되었습니다 (단, 행렬 A는 상태가 좋지 않을 수 있으며,
                        조건 번호에 대한 R1 / RInf 매개 변수 확인).
    담당자 솔버 보고서, 자세한 정보는 아래를 참조하십시오.
    X - 배열 [0..N-1]은 다음을 포함합니다.
                A가 비 특이성 (well-conditioned) 인 경우 A * x = b의 해
                  또는 불량한 상태이지만 단수에 가깝지는 않음)
                * A가 단수이거나 매우 단수에 가까운 경우 0
                  (이 경우 Info = -3).
솔버 리포트
서브 루틴은 Rep 구조의 필드를 다음과 같이 설정합니다.
* R1은 조건 수의 역수입니다. 1 / cond (A), 1-norm.
* 조건 수의 역수 : 1 / cond (A), inf-norm.
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixsolve(const real_2d_array &a, const ae_int_t n, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixsolve(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver.

Similar to RMatrixSolve() but solves task with multiple right parts (where
b and x are NxM matrices).

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* optional iterative refinement
* O(N^3+M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size
    RFS     -   iterative refinement switch:
                * True - refinement is used.
                  Less performance, more precision.
                * False - refinement is not used.
                  More performance, less precision.

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
RMatrixSolve ()와 비슷하지만 여러 개의 오른쪽 부분으로 작업을 해결합니다 (여기서
b 및 x는 N × M 행렬이다).
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 선택적 반복적 인 정제
* O (N ^ 3 + M * N ^ 2) 복잡도
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
    RFS - 반복적 인 구체화 스위치 :
                * 진실 - 세련미가 사용됩니다.
                  성능이 떨어지며 정밀도가 높아집니다.
                * 거짓 - 세련미가 사용되지 않습니다.
                  성능이 향상되고 정확도는 떨어집니다.
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixsolvem(const real_2d_array &a, const ae_int_t n, const real_2d_array &b, const ae_int_t m, const bool rfs, ae_int_t &info, densesolverreport &rep, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixsolvem(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, rfs, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver.

This  subroutine  solves  a  system  A*X=B,  where A is NxN non-denegerate
real matrix given by its LU decomposition, X and B are NxM real matrices.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation

No iterative refinement  is provided because exact form of original matrix
is not known to subroutine. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 시스템 A * X = B를 해결합니다. 여기서 A는 NxN 비 - denegerate입니다.
그것의 LU 분해에 의해 주어진 실제 행렬, X와 B는 NxM 실수 행렬이다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixlusolve(const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixlusolve(const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver.

Similar to RMatrixLUSolve() but solves task with multiple right parts
(where b and x are NxM matrices).

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation

No iterative refinement  is provided because exact form of original matrix
is not known to subroutine. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
RMatrixLUSolve ()와 비슷하지만 여러 개의 오른쪽 부분으로 작업을 해결합니다.
(여기서 b와 x는 N × M 행렬 임).
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixlusolvem(const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixlusolvem(const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver.

This  subroutine  solves  a  system  A*x=b,  where BOTH ORIGINAL A AND ITS
LU DECOMPOSITION ARE KNOWN. You can use it if for some  reasons  you  have
both A and its LU decomposition.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 시스템 A * x = b를 해결합니다. 여기서 B는 원래 A와 ITS
LU DECODPOSITION을 (를) 알고 있습니다. 당신은 당신이 가지고있는 몇 가지 이유가 있다면 그것을 사용할 수 있습니다.
A와 LU 분해 모두.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixmixedsolve(const real_2d_array &a, const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixmixedsolve(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver.

Similar to RMatrixMixedSolve() but  solves task with multiple right  parts
(where b and x are NxM matrices).

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
RMatrixMixedSolve ()와 비슷하지만 여러 개의 오른쪽 부분으로 작업을 해결합니다.
(여기서 b와 x는 N × M 행렬 임).
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (M * N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixmixedsolvem(const real_2d_array &a, const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixmixedsolvem(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixSolveM(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^3+M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size
    RFS     -   iterative refinement switch:
                * True - refinement is used.
                  Less performance, more precision.
                * False - refinement is not used.
                  More performance, less precision.

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolveM ()과 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 3 + M * N ^ 2) 복잡도
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
    RFS - 반복적 인 구체화 스위치 :
                * 진실 - 세련미가 사용됩니다.
                  성능이 떨어지며 정밀도가 높아집니다.
                * 거짓 - 세련미가 사용되지 않습니다.
                  성능이 향상되고 정확도는 떨어집니다.
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixsolvem(const complex_2d_array &a, const ae_int_t n, const complex_2d_array &b, const ae_int_t m, const bool rfs, ae_int_t &info, densesolverreport &rep, complex_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::cmatrixsolvem(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, rfs, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixSolve(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^3) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolve ()와 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 3) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixsolve(const complex_2d_array &a, const ae_int_t n, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::cmatrixsolve(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixLUSolveM(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation

No iterative refinement  is provided because exact form of original matrix
is not known to subroutine. Use CMatrixSolve or CMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolveM ()과 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. CMatrixSolve 또는 CMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixlusolvem(const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::cmatrixlusolvem(const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixLUSolve(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation

No iterative refinement is provided because exact form of original matrix
is not known to subroutine. Use CMatrixSolve or CMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, CMatrixLU result
    P       -   array[0..N-1], pivots array, CMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolve ()와 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. CMatrixSolve 또는 CMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA- 어레이 [0..N-1.0..N-1], LU 분해, CMatrixLU 결과
    P- 배열 [0..N-1], 축 배열, CMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixlusolve(const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::cmatrixlusolve(const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixMixedSolveM(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, CMatrixLU result
    P       -   array[0..N-1], pivots array, CMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixMixedSolveM ()과 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (M * N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA- 어레이 [0..N-1.0..N-1], LU 분해, CMatrixLU 결과
    P- 배열 [0..N-1], 축 배열, CMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixmixedsolvem(const complex_2d_array &a, const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::cmatrixmixedsolvem(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixMixedSolve(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, CMatrixLU result
    P       -   array[0..N-1], pivots array, CMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixMixedSolve ()와 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA- 어레이 [0..N-1.0..N-1], LU 분해, CMatrixLU 결과
    P- 배열 [0..N-1], 축 배열, CMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */

void cmatrixmixedsolve(const complex_2d_array &a, const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::cmatrixmixedsolve(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), const_cast<alglib_impl::ae_matrix*>(lua.c_ptr()), const_cast<alglib_impl::ae_vector*>(p.c_ptr()), n, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixSolveM(), but for symmetric positive definite
matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3+M*N^2) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve.
                Returns -3 for non-SPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolveM ()과 동일하지만 대칭적인 양의 확정적
행렬.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3 + M * N ^ 2) 복잡도
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    Info - RMatrixSolve와 동일합니다.
                비 SPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixsolvem(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::spdmatrixsolvem(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, isupper, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixSolve(), but for SPD matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
                Returns -3 for non-SPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolve ()와 동일하지만 SPD 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3) 복잡성
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
                비 SPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixsolve(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::spdmatrixsolve(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, isupper, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixLUSolveM(), but for SPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                SPDMatrixCholesky result
    N       -   size of CHA
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolveM ()과 동일하지만 표현 된 SPD 행렬
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                SPDMatrixCholesky 결과
    CHA의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixcholeskysolvem(const real_2d_array &cha, const ae_int_t n, const bool isupper, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::spdmatrixcholeskysolvem(const_cast<alglib_impl::ae_matrix*>(cha.c_ptr()), n, isupper, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixLUSolve(), but for  SPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                SPDMatrixCholesky result
    N       -   size of A
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolve ()와 동일하지만 표현 된 SPD 행렬
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                SPDMatrixCholesky 결과
    A의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixcholeskysolve(const real_2d_array &cha, const ae_int_t n, const bool isupper, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::spdmatrixcholeskysolve(const_cast<alglib_impl::ae_matrix*>(cha.c_ptr()), n, isupper, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixSolveM(), but for Hermitian positive definite
matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3+M*N^2) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve.
                Returns -3 for non-HPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolveM ()과 동일하지만, Hermitian positive definite
행렬.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3 + M * N ^ 2) 복잡도
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    Info - RMatrixSolve와 동일합니다.
                비 HPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixsolvem(const complex_2d_array &a, const ae_int_t n, const bool isupper, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hpdmatrixsolvem(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, isupper, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixSolve(),  but for Hermitian positive definite
matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
                Returns -3 for non-HPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolve ()와 동일하지만, Hermitian positive definite
행렬.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3) 복잡성
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
                비 HPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixsolve(const complex_2d_array &a, const ae_int_t n, const bool isupper, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hpdmatrixsolve(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), n, isupper, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixLUSolveM(), but for HPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                HPDMatrixCholesky result
    N       -   size of CHA
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolveM ()과 동일하지만 HPD 행렬 표현
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                HPDMatrixCholesky 결과
    CHA의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixcholeskysolvem(const complex_2d_array &cha, const ae_int_t n, const bool isupper, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hpdmatrixcholeskysolvem(const_cast<alglib_impl::ae_matrix*>(cha.c_ptr()), n, isupper, const_cast<alglib_impl::ae_matrix*>(b.c_ptr()), m, &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_matrix*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver. Same as RMatrixLUSolve(), but for  HPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                SPDMatrixCholesky result
    N       -   size of A
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolve ()와 동일하지만 HPD 행렬 표현
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                SPDMatrixCholesky 결과
    A의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixcholeskysolve(const complex_2d_array &cha, const ae_int_t n, const bool isupper, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::hpdmatrixcholeskysolve(const_cast<alglib_impl::ae_matrix*>(cha.c_ptr()), n, isupper, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &info, const_cast<alglib_impl::densesolverreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Dense solver.

This subroutine finds solution of the linear system A*X=B with non-square,
possibly degenerate A.  System  is  solved in the least squares sense, and
general least squares solution  X = X0 + CX*y  which  minimizes |A*X-B| is
returned. If A is non-degenerate, solution in the usual sense is returned.

Algorithm features:
* automatic detection (and correct handling!) of degenerate cases
* iterative refinement
* O(N^3) complexity

INPUT PARAMETERS
    A       -   array[0..NRows-1,0..NCols-1], system matrix
    NRows   -   vertical size of A
    NCols   -   horizontal size of A
    B       -   array[0..NCols-1], right part
    Threshold-  a number in [0,1]. Singular values  beyond  Threshold  are
                considered  zero.  Set  it to 0.0, if you don't understand
                what it means, so the solver will choose good value on its
                own.

OUTPUT PARAMETERS
    Info    -   return code:
                * -4    SVD subroutine failed
                * -1    if NRows<=0 or NCols<=0 or Threshold<0 was passed
                *  1    if task is solved
    Rep     -   solver report, see below for more info
    X       -   array[0..N-1,0..M-1], it contains:
                * solution of A*X=B (even for singular A)
                * zeros, if SVD subroutine failed

SOLVER REPORT

Subroutine sets following fields of the Rep structure:
* R2        reciprocal of condition number: 1/cond(A), 2-norm.
* N         = NCols
* K         dim(Null(A))
* CX        array[0..N-1,0..K-1], kernel of A.
            Columns of CX store such vectors that A*CX[i]=0.

  -- ALGLIB --
     Copyright 24.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 선형 시스템 A * X = B의 해를 찾아서 비 -
아마도 A를 퇴보시킨다. 시스템은 최소 자승법으로 풀린다.
일반적인 최소 자승 해 X = X0 + CX * y | A * XB |를 최소화하는 솔루션 ~이다.
반환되었습니다. A가 비 축퇴이면, 일반적인 의미의 해답이 반환됩니다.
알고리즘 특징 :
* 축축한 사례의 자동 감지 (올바른 취급!)
* 반복적 인 정제
* O (N ^ 3) 복잡성
입력 매개 변수
    A 배열 [0..NRows-1.0 ... NCols-1], 시스템 행렬
    NRows - A의 세로 크기
    NCols - A의 가로 크기
    B- 배열 [0..NCols-1], 오른쪽 부분
    임계 값 - [0,1]의 숫자. 임계 값을 초과하는 단일 값은 다음과 같습니다.
                0으로 간주됩니다. 당신이 이해하지 못한다면 0.0으로 설정하십시오.
                그것이 의미하는 바는 솔버가 좋은 가치를 선택하게됩니다.
                개인적인.
출력 매개 변수
    정보 - 리턴 코드 :
                * -4 SVD 서브 루틴 실패
                * NRows <= 0 또는 NCols <= 0 또는 임계 값 <0 인 경우 -1
                * 과제가 해결되면 1
    담당자 솔버 보고서, 자세한 정보는 아래를 참조하십시오.
    X- 배열 [0..N-1.0..M-1]은 다음을 포함합니다.
                * A * X = B의 해 (단수 A에 대해서조차도)
                SVD 서브 루틴이 실패한 경우 * 0
솔버 리포트
서브 루틴은 Rep 구조의 필드를 다음과 같이 설정합니다.
* R2는 조건 수의 역수입니다. 1 / cond (A), 2-norm.
* N = NCols
* K dim (Null (A))
* CX 배열 [0..N-1.0..K-1], A. 커널
            CX의 열은 A * CX [i] = 0과 같은 벡터를 저장합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 24.08.2009
*************************************************** ********************** */
void rmatrixsolvels(const real_2d_array &a, const ae_int_t nrows, const ae_int_t ncols, const real_1d_array &b, const double threshold, ae_int_t &info, densesolverlsreport &rep, real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::rmatrixsolvels(const_cast<alglib_impl::ae_matrix*>(a.c_ptr()), nrows, ncols, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), threshold, &info, const_cast<alglib_impl::densesolverlsreport*>(rep.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This object stores state of the LinLSQR method.

You should use ALGLIB functions to work with this object.
*************************************************************************/
/* ************************************************ *************************
이 객체는 LinLSQR 메서드의 상태를 저장합니다.
이 객체를 사용하려면 ALGLIB 함수를 사용해야합니다.
*************************************************** ********************** */
_linlsqrstate_owner::_linlsqrstate_owner()
{
    p_struct = (alglib_impl::linlsqrstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::linlsqrstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_linlsqrstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_linlsqrstate_owner::_linlsqrstate_owner(const _linlsqrstate_owner &rhs)
{
    p_struct = (alglib_impl::linlsqrstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::linlsqrstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_linlsqrstate_init_copy(p_struct, const_cast<alglib_impl::linlsqrstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_linlsqrstate_owner& _linlsqrstate_owner::operator=(const _linlsqrstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_linlsqrstate_clear(p_struct);
    if( !alglib_impl::_linlsqrstate_init_copy(p_struct, const_cast<alglib_impl::linlsqrstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_linlsqrstate_owner::~_linlsqrstate_owner()
{
    alglib_impl::_linlsqrstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::linlsqrstate* _linlsqrstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::linlsqrstate* _linlsqrstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::linlsqrstate*>(p_struct);
}
linlsqrstate::linlsqrstate() : _linlsqrstate_owner() 
{
}

linlsqrstate::linlsqrstate(const linlsqrstate &rhs):_linlsqrstate_owner(rhs) 
{
}

linlsqrstate& linlsqrstate::operator=(const linlsqrstate &rhs)
{
    if( this==&rhs )
        return *this;
    _linlsqrstate_owner::operator=(rhs);
    return *this;
}

linlsqrstate::~linlsqrstate()
{
}


/*************************************************************************

*************************************************************************/
_linlsqrreport_owner::_linlsqrreport_owner()
{
    p_struct = (alglib_impl::linlsqrreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::linlsqrreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_linlsqrreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_linlsqrreport_owner::_linlsqrreport_owner(const _linlsqrreport_owner &rhs)
{
    p_struct = (alglib_impl::linlsqrreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::linlsqrreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_linlsqrreport_init_copy(p_struct, const_cast<alglib_impl::linlsqrreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_linlsqrreport_owner& _linlsqrreport_owner::operator=(const _linlsqrreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_linlsqrreport_clear(p_struct);
    if( !alglib_impl::_linlsqrreport_init_copy(p_struct, const_cast<alglib_impl::linlsqrreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_linlsqrreport_owner::~_linlsqrreport_owner()
{
    alglib_impl::_linlsqrreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::linlsqrreport* _linlsqrreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::linlsqrreport* _linlsqrreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::linlsqrreport*>(p_struct);
}
linlsqrreport::linlsqrreport() : _linlsqrreport_owner() ,iterationscount(p_struct->iterationscount),nmv(p_struct->nmv),terminationtype(p_struct->terminationtype)
{
}

linlsqrreport::linlsqrreport(const linlsqrreport &rhs):_linlsqrreport_owner(rhs) ,iterationscount(p_struct->iterationscount),nmv(p_struct->nmv),terminationtype(p_struct->terminationtype)
{
}

linlsqrreport& linlsqrreport::operator=(const linlsqrreport &rhs)
{
    if( this==&rhs )
        return *this;
    _linlsqrreport_owner::operator=(rhs);
    return *this;
}

linlsqrreport::~linlsqrreport()
{
}

/*************************************************************************
This function initializes linear LSQR Solver. This solver is used to solve
non-symmetric (and, possibly, non-square) problems. Least squares solution
is returned for non-compatible systems.

USAGE:
1. User initializes algorithm state with LinLSQRCreate() call
2. User tunes solver parameters with  LinLSQRSetCond() and other functions
3. User  calls  LinLSQRSolveSparse()  function which takes algorithm state
   and SparseMatrix object.
4. User calls LinLSQRResults() to get solution
5. Optionally, user may call LinLSQRSolveSparse() again to  solve  another
   problem  with different matrix and/or right part without reinitializing
   LinLSQRState structure.

INPUT PARAMETERS:
    M       -   number of rows in A
    N       -   number of variables, N>0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선형 LSQR 해를 초기화합니다. 이 솔버는
비대칭 (및, 아마도 비 정사각형) 문제. 최소 제곱 솔루션
호환되지 않는 시스템의 경우 반환됩니다.
용법:
1. 사용자가 LinLSQRCreate () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 LinLSQRSetCond () 및 기타 함수를 사용하여 해석기 매개 변수를 조정합니다.
3. 사용자가 알고리즘 상태를 취하는 LinLSQRSolveSparse () 함수를 호출
   및 SparseMatrix 개체입니다.
4. 사용자가 LinLSQRResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 사용자가 LinLSQRSolveSparse ()를 다시 호출하여 다른 문제를 해결할 수 있습니다
   재 초기화하지 않고 다른 행렬 및 / 또는 오른쪽 부분의 문제
   LinLSQRState 구조체입니다.
입력 매개 변수 :
    M - A의 행 수
    N - 변수의 수 N> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrcreate(const ae_int_t m, const ae_int_t n, linlsqrstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrcreate(m, n, const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This  function  changes  preconditioning  settings of LinLSQQSolveSparse()
function. By default, SolveSparse() uses diagonal preconditioner,  but  if
you want to use solver without preconditioning, you can call this function
which forces solver to use unit matrix for preconditioning.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinLSQQSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. 기본적으로 SolveSparse ()는 대각선 전치 조건자를 사용하지만 if
당신은 preconditioning없이 solver를 사용하기를 원한다.이 함수를 호출 할 수있다.
이는 솔버가 전처리를 위해 단위 행렬을 사용하게합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetprecunit(const linlsqrstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrsetprecunit(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This  function  changes  preconditioning  settings  of  LinCGSolveSparse()
function.  LinCGSolveSparse() will use diagonal of the  system  matrix  as
preconditioner. This preconditioning mode is active by default.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinCGSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. LinCGSolveSparse ()는 시스템 행렬의 대각선을 다음과 같이 사용합니다.
프리 컨디셔너. 이 사전 조절 모드는 기본적으로 활성화되어 있습니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetprecdiag(const linlsqrstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrsetprecdiag(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets optional Tikhonov regularization coefficient.
It is zero by default.

INPUT PARAMETERS:
    LambdaI -   regularization factor, LambdaI>=0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선택적 Tikhonov 정규화 계수를 설정합니다.
기본적으로 0입니다.
입력 매개 변수 :
    람다 - 정규화 인수, 람다> = 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetlambdai(const linlsqrstate &state, const double lambdai)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrsetlambdai(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), lambdai, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Procedure for solution of A*x=b with sparse A.

INPUT PARAMETERS:
    State   -   algorithm state
    A       -   sparse M*N matrix in the CRS format (you MUST contvert  it
                to CRS format  by  calling  SparseConvertToCRS()  function
                BEFORE you pass it to this function).
    B       -   right part, array[M]

RESULT:
    This function returns no result.
    You can get solution by calling LinCGResults()

NOTE: this function uses lightweight preconditioning -  multiplication  by
      inverse of diag(A). If you want, you can turn preconditioning off by
      calling LinLSQRSetPrecUnit(). However, preconditioning cost is   low
      and preconditioner is very important for solution  of  badly  scaled
      problems.

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
스파 스 A가있는 A * x = b의 해를 구하는 절차.
입력 매개 변수 :
    상태 - 알고리즘 상태
    A - CRS 형식의 희소 M * N 행렬 (반드시 변환해야합니다.)
                SparseConvertToCRS () 함수를 호출하여 CRS 형식으로 변환
                이 함수에 전달하기 전에).
    B - 오른쪽 부분, 배열 [M]
결과:
    이 함수는 결과를 반환하지 않습니다.
    LinCGResults ()를 호출하여 솔루션을 얻을 수 있습니다.
참고 :이 함수는 가벼운 전제 조건을 사용합니다.
      diag (A)의 역. 원하는 경우 사전 조건을 해제 할 수 있습니다.
      LinLSQRSetPrecUnit ()을 호출합니다. 그러나 사전 컨디셔닝 비용은 낮습니다.
      전처리 기는 잘못 조정 된 솔루션의 경우 매우 중요합니다.
      문제.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsolvesparse(const linlsqrstate &state, const sparsematrix &a, const real_1d_array &b)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrsolvesparse(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), const_cast<alglib_impl::sparsematrix*>(a.c_ptr()), const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets stopping criteria.

INPUT PARAMETERS:
    EpsA    -   algorithm will be stopped if ||A^T*Rk||/(||A||*||Rk||)<=EpsA.
    EpsB    -   algorithm will be stopped if ||Rk||<=EpsB*||B||
    MaxIts  -   algorithm will be stopped if number of iterations
                more than MaxIts.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTE: if EpsA,EpsB,EpsC and MaxIts are zero then these variables will
be setted as default values.

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 중지 기준을 설정합니다.
입력 매개 변수 :
    EpsA - | A ^ T * Rk || / (|| A || * || Rk ||) <= EpsA이면 알고리즘이 중지됩니다.
    EpsB - | Rk || <= EpsB * || B ||이면 알고리즘이 중지됩니다.
    MaxIts - 반복 횟수에 따라 알고리즘이 중지됩니다.
                MaxIts 이상.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참고 : EpsA, EpsB, EpsC 및 MaxIts가 0이면이 변수는
기본값으로 설정하십시오.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetcond(const linlsqrstate &state, const double epsa, const double epsb, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrsetcond(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), epsa, epsb, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
LSQR solver: results.

This function must be called after LinLSQRSolve

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[N], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    *  1    ||Rk||<=EpsB*||B||
                    *  4    ||A^T*Rk||/(||A||*||Rk||)<=EpsA
                    *  5    MaxIts steps was taken
                    *  7    rounding errors prevent further progress,
                            X contains best point found so far.
                            (sometimes returned on singular systems)
                * Rep.IterationsCount contains iterations count
                * NMV countains number of matrix-vector calculations

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
LSQR solver : 결과.
이 함수는 LinLSQRSolve 뒤에 호출해야합니다.
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X - 배열 [N], 솔루션
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * 1 || Rk || <= EpsB * || B ||
                    * 4 || A ^ T * Rk || / (|| A || * || Rk ||) <= EpsA
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 반올림 오류로 인해 더 이상 진행되지 않습니다.
                            X는 지금까지 발견 된 최상의 포인트를 포함합니다.
                            (때로는 단일 시스템에서 반환 됨)
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                NMV는 매트릭스 - 벡터 계산의 수를 카운트합니다.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrresults(const linlsqrstate &state, real_1d_array &x, linlsqrreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrresults(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::linlsqrreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinCGOptimize ()에 제공됩니다.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetxrep(const linlsqrstate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::linlsqrsetxrep(const_cast<alglib_impl::linlsqrstate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This object stores state of the linear CG method.

You should use ALGLIB functions to work with this object.
Never try to access its fields directly!
*************************************************************************/
/* ************************************************ *************************
이 객체는 선형 CG 방법의 상태를 저장합니다.
이 객체를 사용하려면 ALGLIB 함수를 사용해야합니다.
필드에 직접 액세스하지 마세요.
*************************************************** ********************** */
_lincgstate_owner::_lincgstate_owner()
{
    p_struct = (alglib_impl::lincgstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::lincgstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_lincgstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_lincgstate_owner::_lincgstate_owner(const _lincgstate_owner &rhs)
{
    p_struct = (alglib_impl::lincgstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::lincgstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_lincgstate_init_copy(p_struct, const_cast<alglib_impl::lincgstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_lincgstate_owner& _lincgstate_owner::operator=(const _lincgstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_lincgstate_clear(p_struct);
    if( !alglib_impl::_lincgstate_init_copy(p_struct, const_cast<alglib_impl::lincgstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_lincgstate_owner::~_lincgstate_owner()
{
    alglib_impl::_lincgstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::lincgstate* _lincgstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::lincgstate* _lincgstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::lincgstate*>(p_struct);
}
lincgstate::lincgstate() : _lincgstate_owner() 
{
}

lincgstate::lincgstate(const lincgstate &rhs):_lincgstate_owner(rhs) 
{
}

lincgstate& lincgstate::operator=(const lincgstate &rhs)
{
    if( this==&rhs )
        return *this;
    _lincgstate_owner::operator=(rhs);
    return *this;
}

lincgstate::~lincgstate()
{
}


/*************************************************************************

*************************************************************************/
_lincgreport_owner::_lincgreport_owner()
{
    p_struct = (alglib_impl::lincgreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::lincgreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_lincgreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_lincgreport_owner::_lincgreport_owner(const _lincgreport_owner &rhs)
{
    p_struct = (alglib_impl::lincgreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::lincgreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_lincgreport_init_copy(p_struct, const_cast<alglib_impl::lincgreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_lincgreport_owner& _lincgreport_owner::operator=(const _lincgreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_lincgreport_clear(p_struct);
    if( !alglib_impl::_lincgreport_init_copy(p_struct, const_cast<alglib_impl::lincgreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_lincgreport_owner::~_lincgreport_owner()
{
    alglib_impl::_lincgreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::lincgreport* _lincgreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::lincgreport* _lincgreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::lincgreport*>(p_struct);
}
lincgreport::lincgreport() : _lincgreport_owner() ,iterationscount(p_struct->iterationscount),nmv(p_struct->nmv),terminationtype(p_struct->terminationtype),r2(p_struct->r2)
{
}

lincgreport::lincgreport(const lincgreport &rhs):_lincgreport_owner(rhs) ,iterationscount(p_struct->iterationscount),nmv(p_struct->nmv),terminationtype(p_struct->terminationtype),r2(p_struct->r2)
{
}

lincgreport& lincgreport::operator=(const lincgreport &rhs)
{
    if( this==&rhs )
        return *this;
    _lincgreport_owner::operator=(rhs);
    return *this;
}

lincgreport::~lincgreport()
{
}

/*************************************************************************
This function initializes linear CG Solver. This solver is used  to  solve
symmetric positive definite problems. If you want  to  solve  nonsymmetric
(or non-positive definite) problem you may use LinLSQR solver provided  by
ALGLIB.

USAGE:
1. User initializes algorithm state with LinCGCreate() call
2. User tunes solver parameters with  LinCGSetCond() and other functions
3. Optionally, user sets starting point with LinCGSetStartingPoint()
4. User  calls LinCGSolveSparse() function which takes algorithm state and
   SparseMatrix object.
5. User calls LinCGResults() to get solution
6. Optionally, user may call LinCGSolveSparse()  again  to  solve  another
   problem  with different matrix and/or right part without reinitializing
   LinCGState structure.

INPUT PARAMETERS:
    N       -   problem dimension, N>0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선형 CG 해법을 초기화합니다. 이 솔버는
대칭 긍정적 인 명확한 문제. 비대칭 성을 풀고 싶다면
(또는 non-positive definite) 문제로 LinLSQR solver를 사용할 수 있습니다.
ALGLIB.
용법:
1. 사용자는 LinCGCreate () 호출로 알고리즘 상태를 초기화한다.
2. 사용자가 LinCGSetCond () 및 기타 함수로 솔버 매개 변수를 조정합니다.
3. 선택적으로 사용자가 LinCGSetStartingPoint ()로 시작점을 설정합니다.
4. 사용자는 알고리즘 상태를 취하는 LinCGSolveSparse () 함수를 호출하고
   SparseMatrix 객체입니다.
5. 사용자가 LinCGResults ()를 호출하여 솔루션을 얻습니다.
6. 선택적으로, 사용자는 LinCGSolveSparse ()를 다시 호출하여 다른 것을 해결할 수 있습니다
   재 초기화하지 않고 다른 행렬 및 / 또는 오른쪽 부분의 문제
   LinCGState 구조체.
입력 매개 변수 :
    N - 문제 차원, N> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */

void lincgcreate(const ae_int_t n, lincgstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgcreate(n, const_cast<alglib_impl::lincgstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets starting point.
By default, zero starting point is used.

INPUT PARAMETERS:
    X       -   starting point, array[N]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은 시작점을 설정합니다.
기본적으로 0의 시작점이 사용됩니다.
입력 매개 변수 :
    X - 시작점, 배열 [N]
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetstartingpoint(const lincgstate &state, const real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetstartingpoint(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This  function  changes  preconditioning  settings  of  LinCGSolveSparse()
function. By default, SolveSparse() uses diagonal preconditioner,  but  if
you want to use solver without preconditioning, you can call this function
which forces solver to use unit matrix for preconditioning.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinCGSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. 기본적으로 SolveSparse ()는 대각선 전치 조건자를 사용하지만 if
당신은 preconditioning없이 solver를 사용하기를 원한다.이 함수를 호출 할 수있다.
이는 솔버가 전처리를 위해 단위 행렬을 사용하게합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetprecunit(const lincgstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetprecunit(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This  function  changes  preconditioning  settings  of  LinCGSolveSparse()
function.  LinCGSolveSparse() will use diagonal of the  system  matrix  as
preconditioner. This preconditioning mode is active by default.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinCGSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. LinCGSolveSparse ()는 시스템 행렬의 대각선을 다음과 같이 사용합니다.
프리 컨디셔너. 이 사전 조절 모드는 기본적으로 활성화되어 있습니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetprecdiag(const lincgstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetprecdiag(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets stopping criteria.

INPUT PARAMETERS:
    EpsF    -   algorithm will be stopped if norm of residual is less than
                EpsF*||b||.
    MaxIts  -   algorithm will be stopped if number of iterations is  more
                than MaxIts.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
If  both  EpsF  and  MaxIts  are  zero then small EpsF will be set to small
value.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 중지 기준을 설정합니다.
입력 매개 변수 :
    EpsF - 잔여 기준이 미만인 경우 알고리즘이 중지됩니다.
                EpsF * || b ||.
    MaxIts - 반복 횟수가 더 많으면 알고리즘이 중지됩니다.
                MaxIts보다.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
EpsF와 MaxIts가 모두 0이면 작은 EpsF가 작게 설정됩니다
값.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */

void lincgsetcond(const lincgstate &state, const double epsf, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetcond(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), epsf, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
Procedure for solution of A*x=b with sparse A.

INPUT PARAMETERS:
    State   -   algorithm state
    A       -   sparse matrix in the CRS format (you MUST contvert  it  to
                CRS format by calling SparseConvertToCRS() function).
    IsUpper -   whether upper or lower triangle of A is used:
                * IsUpper=True  => only upper triangle is used and lower
                                   triangle is not referenced at all
                * IsUpper=False => only lower triangle is used and upper
                                   triangle is not referenced at all
    B       -   right part, array[N]

RESULT:
    This function returns no result.
    You can get solution by calling LinCGResults()

NOTE: this function uses lightweight preconditioning -  multiplication  by
      inverse of diag(A). If you want, you can turn preconditioning off by
      calling LinCGSetPrecUnit(). However, preconditioning cost is low and
      preconditioner  is  very  important  for  solution  of  badly scaled
      problems.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
스파 스 A가있는 A * x = b의 해를 구하는 절차.
입력 매개 변수 :
    상태 - 알고리즘 상태
    A - CRS 형식의 희소 행렬 (이를
                SparseConvertToCRS () 함수를 호출하여 CRS 형식).
    IsUpper - A의 위 또는 아래 삼각형 사용 여부 :
                * IsUpper = True => 위 삼각형 만 사용되고 더 낮습니다
                                   삼각형이 전혀 참조되지 않는다.
                * IsUpper = False => 아래쪽 삼각형 만 사용되고 위쪽
                                   삼각형이 전혀 참조되지 않는다.
    B - 오른쪽 파트, 배열 [N]
결과:
    이 함수는 결과를 반환하지 않습니다.
    LinCGResults ()를 호출하여 솔루션을 얻을 수 있습니다.
참고 :이 함수는 가벼운 전제 조건을 사용합니다.
      diag (A)의 역. 원하는 경우 사전 조건을 해제 할 수 있습니다.
      LinCGSetPrecUnit () 호출. 그러나 사전 컨디셔닝 비용이 낮고
      선 컨디셔너는 잘못 조정 된 솔루션에 매우 중요합니다.
      문제.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsolvesparse(const lincgstate &state, const sparsematrix &a, const bool isupper, const real_1d_array &b)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsolvesparse(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), const_cast<alglib_impl::sparsematrix*>(a.c_ptr()), isupper, const_cast<alglib_impl::ae_vector*>(b.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
CG-solver: results.

This function must be called after LinCGSolve

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[N], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -5    input matrix is either not positive definite,
                            too large or too small
                    * -4    overflow/underflow during solution
                            (ill conditioned problem)
                    *  1    ||residual||<=EpsF*||b||
                    *  5    MaxIts steps was taken
                    *  7    rounding errors prevent further progress,
                            best point found is returned
                * Rep.IterationsCount contains iterations count
                * NMV countains number of matrix-vector calculations

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
CG-solver : 결과.
이 함수는 LinCGSolve 후에 호출해야합니다.
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X - 배열 [N], 솔루션
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -5 입력 행렬은 양의 확률이 아니거나,
                            너무 크거나 너무 작음
                    * -4 솔루션 오버 플로우 / 언더 플로우
                            (아픈 컨디션 문제)
                    * 1 || 잔여 || <= EpsF * || b ||
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 반올림 오류로 인해 더 이상 진행되지 않습니다.
                            찾은 최고의 포인트가 반환됩니다.
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                NMV는 매트릭스 - 벡터 계산의 수를 카운트합니다.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */

void lincgresults(const lincgstate &state, real_1d_array &x, lincgreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgresults(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::lincgreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets restart frequency. By default, algorithm  is  restarted
after N subsequent iterations.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은 재시작 빈도를 설정합니다. 기본적으로 알고리즘은 다시 시작됩니다.
후속 반복 N 회.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetrestartfreq(const lincgstate &state, const ae_int_t srf)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetrestartfreq(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), srf, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets frequency of residual recalculations.

Algorithm updates residual r_k using iterative formula,  but  recalculates
it from scratch after each 10 iterations. It is done to avoid accumulation
of numerical errors and to stop algorithm when r_k starts to grow.

Such low update frequence (1/10) gives very  little  overhead,  but  makes
algorithm a bit more robust against numerical errors. However, you may
change it

INPUT PARAMETERS:
    Freq    -   desired update frequency, Freq>=0.
                Zero value means that no updates will be done.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 잔여 재 계산의 빈도를 설정합니다.
알고리즘은 반복 수식을 사용하여 잔여 r_k를 업데이트하지만 다시 계산합니다.
그것은 각 10 반복 후 처음부터. 누적을 피하기 위해 행해진 다.
r_k가 증가하기 시작할 때 알고리즘을 중지 할 수 있습니다.
낮은 업데이트 빈도 (1/10)는 오버 헤드가 거의 없지만
알고리즘은 수치 오류에 대해 조금 더 견고합니다. 그러나
그것을 바꿔라.
입력 매개 변수 :
    Freq - 원하는 업데이트 빈도, Freq> = 0.
                0 값은 업데이트가 수행되지 않음을 의미합니다.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetrupdatefreq(const lincgstate &state, const ae_int_t freq)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetrupdatefreq(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), freq, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinCGOptimize ()에 제공됩니다.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetxrep(const lincgstate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::lincgsetxrep(const_cast<alglib_impl::lincgstate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************

*************************************************************************/
_nleqstate_owner::_nleqstate_owner()
{
    p_struct = (alglib_impl::nleqstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::nleqstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_nleqstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_nleqstate_owner::_nleqstate_owner(const _nleqstate_owner &rhs)
{
    p_struct = (alglib_impl::nleqstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::nleqstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_nleqstate_init_copy(p_struct, const_cast<alglib_impl::nleqstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_nleqstate_owner& _nleqstate_owner::operator=(const _nleqstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_nleqstate_clear(p_struct);
    if( !alglib_impl::_nleqstate_init_copy(p_struct, const_cast<alglib_impl::nleqstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_nleqstate_owner::~_nleqstate_owner()
{
    alglib_impl::_nleqstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::nleqstate* _nleqstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::nleqstate* _nleqstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::nleqstate*>(p_struct);
}
nleqstate::nleqstate() : _nleqstate_owner() ,needf(p_struct->needf),needfij(p_struct->needfij),xupdated(p_struct->xupdated),f(p_struct->f),fi(&p_struct->fi),j(&p_struct->j),x(&p_struct->x)
{
}

nleqstate::nleqstate(const nleqstate &rhs):_nleqstate_owner(rhs) ,needf(p_struct->needf),needfij(p_struct->needfij),xupdated(p_struct->xupdated),f(p_struct->f),fi(&p_struct->fi),j(&p_struct->j),x(&p_struct->x)
{
}

nleqstate& nleqstate::operator=(const nleqstate &rhs)
{
    if( this==&rhs )
        return *this;
    _nleqstate_owner::operator=(rhs);
    return *this;
}

nleqstate::~nleqstate()
{
}


/*************************************************************************

*************************************************************************/
_nleqreport_owner::_nleqreport_owner()
{
    p_struct = (alglib_impl::nleqreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::nleqreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_nleqreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_nleqreport_owner::_nleqreport_owner(const _nleqreport_owner &rhs)
{
    p_struct = (alglib_impl::nleqreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::nleqreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_nleqreport_init_copy(p_struct, const_cast<alglib_impl::nleqreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_nleqreport_owner& _nleqreport_owner::operator=(const _nleqreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_nleqreport_clear(p_struct);
    if( !alglib_impl::_nleqreport_init_copy(p_struct, const_cast<alglib_impl::nleqreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_nleqreport_owner::~_nleqreport_owner()
{
    alglib_impl::_nleqreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::nleqreport* _nleqreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::nleqreport* _nleqreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::nleqreport*>(p_struct);
}
nleqreport::nleqreport() : _nleqreport_owner() ,iterationscount(p_struct->iterationscount),nfunc(p_struct->nfunc),njac(p_struct->njac),terminationtype(p_struct->terminationtype)
{
}

nleqreport::nleqreport(const nleqreport &rhs):_nleqreport_owner(rhs) ,iterationscount(p_struct->iterationscount),nfunc(p_struct->nfunc),njac(p_struct->njac),terminationtype(p_struct->terminationtype)
{
}

nleqreport& nleqreport::operator=(const nleqreport &rhs)
{
    if( this==&rhs )
        return *this;
    _nleqreport_owner::operator=(rhs);
    return *this;
}

nleqreport::~nleqreport()
{
}

/*************************************************************************
                LEVENBERG-MARQUARDT-LIKE NONLINEAR SOLVER

DESCRIPTION:
This algorithm solves system of nonlinear equations
    F[0](x[0], ..., x[n-1])   = 0
    F[1](x[0], ..., x[n-1])   = 0
    ...
    F[M-1](x[0], ..., x[n-1]) = 0
with M/N do not necessarily coincide.  Algorithm  converges  quadratically
under following conditions:
    * the solution set XS is nonempty
    * for some xs in XS there exist such neighbourhood N(xs) that:
      * vector function F(x) and its Jacobian J(x) are continuously
        differentiable on N
      * ||F(x)|| provides local error bound on N, i.e. there  exists  such
        c1, that ||F(x)||>c1*distance(x,XS)
Note that these conditions are much more weaker than usual non-singularity
conditions. For example, algorithm will converge for any  affine  function
F (whether its Jacobian singular or not).


REQUIREMENTS:
Algorithm will request following information during its operation:
* function vector F[] and Jacobian matrix at given point X
* value of merit function f(x)=F[0]^2(x)+...+F[M-1]^2(x) at given point X


USAGE:
1. User initializes algorithm state with NLEQCreateLM() call
2. User tunes solver parameters with  NLEQSetCond(),  NLEQSetStpMax()  and
   other functions
3. User  calls  NLEQSolve()  function  which  takes  algorithm  state  and
   pointers (delegates, etc.) to callback functions which calculate  merit
   function value and Jacobian.
4. User calls NLEQResults() to get solution
5. Optionally, user may call NLEQRestartFrom() to  solve  another  problem
   with same parameters (N/M) but another starting  point  and/or  another
   function vector. NLEQRestartFrom() allows to reuse already  initialized
   structure.


INPUT PARAMETERS:
    N       -   space dimension, N>1:
                * if provided, only leading N elements of X are used
                * if not provided, determined automatically from size of X
    M       -   system size
    X       -   starting point


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTES:
1. you may tune stopping conditions with NLEQSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use NLEQSetStpMax() function to bound algorithm's steps.
3. this  algorithm  is  a  slightly  modified implementation of the method
   described  in  'Levenberg-Marquardt  method  for constrained  nonlinear
   equations with strong local convergence properties' by Christian Kanzow
   Nobuo Yamashita and Masao Fukushima and further  developed  in  'On the
   convergence of a New Levenberg-Marquardt Method'  by  Jin-yan  Fan  and
   Ya-Xiang Yuan.


  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
                LEVENBERG-MARQUARD-LIKE 비선형 솔버
기술:
이 알고리즘은 비선형 방정식의 시스템을 해결합니다.
    F [0] (x [0], ..., x [n-1]) = 0
    F [1] (x [0], ..., x [n-1]) = 0
    ...
    F [M-1] (x [0], ..., x [n-1]) = 0
M / N과 반드시 ​​일치하지는 않습니다. 알고리즘은 2 차적으로 수렴한다.
다음 조건 하에서 :
    * 솔루션 세트 XS가 비어 있지 않습니다.
    * XS의 일부 xs에는 다음과 같은 이웃 N (xs)이 있습니다.
      * 벡터 함수 F (x)와 그 Jacobian J (x)는 연속적이다.
        N에서 구별 할 수있는
      * || F (x) || N에 국한된 에러를 제공한다.
        c1, that || F (x) ||> c1 * 거리 (x, XS)
이러한 조건은 일반적인 비 특이성보다 훨씬 약합니다.
정황. 예를 들어 알고리즘은 임의의 아핀 함수에 대해 수렴 할 것입니다
F (야 코비 행렬이 단수인지 아닌지).
요구 사항 :
알고리즘은 작동 중에 다음 정보를 요청합니다.
* 함수 벡터 F []와 주어진 점 X에서의 자 코비안 행렬
* 주어진 포인트 X에서 메리트 함수 f (x) = F [0] ^ 2 (x) + ... + F [M-1] ^ 2 (x)
용법:
1. 사용자는 NLEQCreateLM () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 NLEQSetCond (), NLEQSetStpMax () 및 NLEQSetStpMax ()를 사용하여 솔버 매개 변수를 조정합니다.
   다른 기능들
3. 사용자는 알고리즘 상태를 취하는 NLEQSolve () 함수를 호출하고
   메리트를 계산하는 콜백 함수에 대한 포인터 (델리게이트 등)
   함수 값과 Jacobian.
4. 사용자가 NLEQResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 사용자가 NLEQRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 매개 변수 (N / M)이지만 다른 시작점 및 / 또는 다른 점
   함수 벡터. NLEQRestartFrom ()은 이미 초기화 된 재사용을 허용합니다.
   구조.
입력 매개 변수 :
    N 공간 차원, N> 1 :
                * 제공되는 경우 X의 N 번째 요소 만 사용됩니다.
                * 제공되지 않을 경우 X의 크기에 따라 자동으로 결정됩니다.
    M - 시스템 크기
    X - 출발점
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. NLEQSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   NLEQSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩합니다.
3.이 알고리즘은 메소드의 약간 수정 된 구현입니다.
   '제한된 비선형을위한 Levenberg-Marquardt 방법
   강력한 지역 수렴 속성을 가진 방정식 'by Christian Kanzow
   야마시타 노부오와 후쿠시마 마사오는 "
   Jin-yan Fan의 New Levenberg-Marquardt Method의 수렴과
   Ya-Xiang Yuan.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqcreatelm(const ae_int_t n, const ae_int_t m, const real_1d_array &x, nleqstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqcreatelm(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::nleqstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
                LEVENBERG-MARQUARDT-LIKE NONLINEAR SOLVER

DESCRIPTION:
This algorithm solves system of nonlinear equations
    F[0](x[0], ..., x[n-1])   = 0
    F[1](x[0], ..., x[n-1])   = 0
    ...
    F[M-1](x[0], ..., x[n-1]) = 0
with M/N do not necessarily coincide.  Algorithm  converges  quadratically
under following conditions:
    * the solution set XS is nonempty
    * for some xs in XS there exist such neighbourhood N(xs) that:
      * vector function F(x) and its Jacobian J(x) are continuously
        differentiable on N
      * ||F(x)|| provides local error bound on N, i.e. there  exists  such
        c1, that ||F(x)||>c1*distance(x,XS)
Note that these conditions are much more weaker than usual non-singularity
conditions. For example, algorithm will converge for any  affine  function
F (whether its Jacobian singular or not).


REQUIREMENTS:
Algorithm will request following information during its operation:
* function vector F[] and Jacobian matrix at given point X
* value of merit function f(x)=F[0]^2(x)+...+F[M-1]^2(x) at given point X


USAGE:
1. User initializes algorithm state with NLEQCreateLM() call
2. User tunes solver parameters with  NLEQSetCond(),  NLEQSetStpMax()  and
   other functions
3. User  calls  NLEQSolve()  function  which  takes  algorithm  state  and
   pointers (delegates, etc.) to callback functions which calculate  merit
   function value and Jacobian.
4. User calls NLEQResults() to get solution
5. Optionally, user may call NLEQRestartFrom() to  solve  another  problem
   with same parameters (N/M) but another starting  point  and/or  another
   function vector. NLEQRestartFrom() allows to reuse already  initialized
   structure.


INPUT PARAMETERS:
    N       -   space dimension, N>1:
                * if provided, only leading N elements of X are used
                * if not provided, determined automatically from size of X
    M       -   system size
    X       -   starting point


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTES:
1. you may tune stopping conditions with NLEQSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use NLEQSetStpMax() function to bound algorithm's steps.
3. this  algorithm  is  a  slightly  modified implementation of the method
   described  in  'Levenberg-Marquardt  method  for constrained  nonlinear
   equations with strong local convergence properties' by Christian Kanzow
   Nobuo Yamashita and Masao Fukushima and further  developed  in  'On the
   convergence of a New Levenberg-Marquardt Method'  by  Jin-yan  Fan  and
   Ya-Xiang Yuan.


  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
                LEVENBERG-MARQUARD-LIKE 비선형 솔버
기술:
이 알고리즘은 비선형 방정식의 시스템을 해결합니다.
    F [0] (x [0], ..., x [n-1]) = 0
    F [1] (x [0], ..., x [n-1]) = 0
    ...
    F [M-1] (x [0], ..., x [n-1]) = 0
M / N과 반드시 ​​일치하지는 않습니다. 알고리즘은 2 차적으로 수렴한다.
다음 조건 하에서 :
    * 솔루션 세트 XS가 비어 있지 않습니다.
    * XS의 일부 xs에는 다음과 같은 이웃 N (xs)이 있습니다.
      * 벡터 함수 F (x)와 그 Jacobian J (x)는 연속적이다.
        N에서 구별 할 수있는
      * || F (x) || N에 국한된 에러를 제공한다.
        c1, that || F (x) ||> c1 * 거리 (x, XS)
이러한 조건은 일반적인 비 특이성보다 훨씬 약합니다.
정황. 예를 들어 알고리즘은 임의의 아핀 함수에 대해 수렴 할 것입니다
F (야 코비 행렬이 단수인지 아닌지).
요구 사항 :
알고리즘은 작동 중에 다음 정보를 요청합니다.
* 함수 벡터 F []와 주어진 점 X에서의 자 코비안 행렬
* 주어진 포인트 X에서 메리트 함수 f (x) = F [0] ^ 2 (x) + ... + F [M-1] ^ 2 (x)
용법:
1. 사용자는 NLEQCreateLM () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 NLEQSetCond (), NLEQSetStpMax () 및 NLEQSetStpMax ()를 사용하여 솔버 매개 변수를 조정합니다.
   다른 기능들
3. 사용자는 알고리즘 상태를 취하는 NLEQSolve () 함수를 호출하고
   메리트를 계산하는 콜백 함수에 대한 포인터 (델리게이트 등)
   함수 값과 Jacobian.
4. 사용자가 NLEQResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 사용자가 NLEQRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 매개 변수 (N / M)이지만 다른 시작점 및 / 또는 다른 점
   함수 벡터. NLEQRestartFrom ()은 이미 초기화 된 재사용을 허용합니다.
   구조.
입력 매개 변수 :
    N 공간 차원, N> 1 :
                * 제공되는 경우 X의 N 번째 요소 만 사용됩니다.
                * 제공되지 않을 경우 X의 크기에 따라 자동으로 결정됩니다.
    M - 시스템 크기
    X - 출발점
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. NLEQSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   NLEQSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩합니다.
3.이 알고리즘은 메소드의 약간 수정 된 구현입니다.
   '제한된 비선형을위한 Levenberg-Marquardt 방법
   강력한 지역 수렴 속성을 가진 방정식 'by Christian Kanzow
   야마시타 노부오와 후쿠시마 마사오는 "
   Jin-yan Fan의 New Levenberg-Marquardt Method의 수렴과
   Ya-Xiang Yuan.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqcreatelm(const ae_int_t m, const real_1d_array &x, nleqstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqcreatelm(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::nleqstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets stopping conditions for the nonlinear solver

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsF    -   >=0
                The subroutine finishes  its work if on k+1-th iteration
                the condition ||F||<=EpsF is satisfied
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsF=0 and MaxIts=0 simultaneously will lead to  automatic
stopping criterion selection (small EpsF).

NOTES:

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 비선형 해석을위한 정지 조건을 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsF -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                조건 || F || <= EpsF가 만족된다
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다.
EpsF = 0 및 MaxIts = 0을 동시에 전달하면 자동
중지 기준 선택 (작은 EpsF).
노트:
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqsetcond(const nleqstate &state, const double epsf, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqsetcond(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), epsf, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to NLEQSolve().

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
NLEQSolve ()에 제공됨.
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqsetxrep(const nleqstate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqsetxrep(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when target function  contains  exp()  or  other  fast
growing functions, and algorithm makes  too  large  steps  which  lead  to
overflow. This function allows us to reject steps that are too large  (and
therefore expose us to the possible overflow) without actually calculating
function value at the x+stp*d.

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 최대 스텝 길이를 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    StpMax - 최대 스텝 길이,> = 0. StpMax를 0.0으로 설정하십시오.
                스텝 길이를 제한하고 싶다.
대상 함수가 exp () 또는 다른 고속 함수를 포함 할 때이 서브 루틴을 사용하십시오.
성장하는 함수 및 알고리즘은 너무 큰 단계를 만들어
과다. 이 함수를 사용하면 너무 큰 단계를 거부 할 수 있습니다 (
따라서 실제로 오버 플로우가 발생할 수 있음)
x + stp * d에서의 함수 값.
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqsetstpmax(const nleqstate &state, const double stpmax)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqsetstpmax(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), stpmax, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This function provides reverse communication interface
Reverse communication interface is not documented or recommended to use.
See below for functions which provide better documented API
*************************************************************************/
/* ************************************************ *************************
이 기능은 역방향 통신 인터페이스를 제공합니다.
역방향 통신 인터페이스는 문서화되어 있지 않거나 사용하도록 권장되지 않습니다.
보다 잘 문서화 된 API를 제공하는 함수는 아래를 참조하십시오.
*************************************************** ********************** */
bool nleqiteration(const nleqstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        ae_bool result = alglib_impl::nleqiteration(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<bool*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}


void nleqsolve(nleqstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( func==NULL )
        throw ap_error("ALGLIB: error in 'nleqsolve()' (func is NULL)");
    if( jac==NULL )
        throw ap_error("ALGLIB: error in 'nleqsolve()' (jac is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::nleqiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needf )
            {
                func(state.x, state.f, ptr);
                continue;
            }
            if( state.needfij )
            {
                jac(state.x, state.fi, state.j, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'nleqsolve' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}



/*************************************************************************
NLEQ solver results

INPUT PARAMETERS:
    State   -   algorithm state.

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -4    ERROR:  algorithm   has   converged   to   the
                            stationary point Xf which is local minimum  of
                            f=F[0]^2+...+F[m-1]^2, but is not solution  of
                            nonlinear system.
                    *  1    sqrt(f)<=EpsF.
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations
                * ActiveConstraints contains number of active constraints

  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
NLEQ 해결사 결과
입력 매개 변수 :
    상태 - 알고리즘 상태.
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -4 오류 : 알고리즘이
                            국소 최소치 인 정지 점 Xf
                            f = F [0] ^ 2 + ... + F [m-1] ^ 2이지만,
                            비선형 시스템.
                    * 1 sqrt (f) <= EpsF.
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 정지 조건은 너무 엄격합니다.
                            더 이상의 개선은 불가능하다.
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                * NFEV countains 함수 계산 횟수
                * ActiveConstraints에는 활성 제약 조건 수가 포함됩니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqresults(const nleqstate &state, real_1d_array &x, nleqreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqresults(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::nleqreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
NLEQ solver results

Buffered implementation of NLEQResults(), which uses pre-allocated  buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
NLEQ 해결사 결과
미리 할당 된 버퍼를 사용하는 NLEQResults ()의 버퍼 된 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqresultsbuf(const nleqstate &state, real_1d_array &x, nleqreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqresultsbuf(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::nleqreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
}

/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used for reverse communication previously
                allocated with MinCGCreate call.
    X       -   new starting point.
    BndL    -   new lower bounds
    BndU    -   new upper bounds

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 새로운 지점에서 CG 알고리즘을 재시작합니다. 모든 최적화
매개 변수는 변경되지 않습니다.
이 함수는 여러 개의 최적화 문제를 해결할 수 있습니다.
오브젝트 재 할당 패널티가없는 동일한 수의 치수가 있어야합니다.
입력 매개 변수 :
    상태 - 이전에 역방향 통신에 사용 된 구조
                MinCGCreate 호출로 할당됩니다.
    X - 새로운 출발점.
    BndL - 새로운 하한
    BndU - 새로운 상한
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqrestartfrom(const nleqstate &state, const real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::nleqrestartfrom(const_cast<alglib_impl::nleqstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
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
/////////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 컴퓨팅 핵심 구현이 포함되어 있습니다.
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
static void densesolver_rmatrixlusolveinternal(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_bool havea,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
static void densesolver_spdmatrixcholeskysolveinternal(/* Real    */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* a,
     ae_bool havea,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
static void densesolver_cmatrixlusolveinternal(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_bool havea,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
static void densesolver_hpdmatrixcholeskysolveinternal(/* Complex */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_matrix* a,
     ae_bool havea,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
static ae_int_t densesolver_densesolverrfsmax(ae_int_t n,
     double r1,
     double rinf,
     ae_state *_state);
static ae_int_t densesolver_densesolverrfsmaxv2(ae_int_t n,
     double r2,
     ae_state *_state);
static void densesolver_rbasiclusolve(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Real    */ ae_vector* xb,
     /* Real    */ ae_vector* tmp,
     ae_state *_state);
static void densesolver_spdbasiccholeskysolve(/* Real    */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* xb,
     /* Real    */ ae_vector* tmp,
     ae_state *_state);
static void densesolver_cbasiclusolve(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Complex */ ae_vector* xb,
     /* Complex */ ae_vector* tmp,
     ae_state *_state);
static void densesolver_hpdbasiccholeskysolve(/* Complex */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* xb,
     /* Complex */ ae_vector* tmp,
     ae_state *_state);


static double linlsqr_atol = 1.0E-6;
static double linlsqr_btol = 1.0E-6;
static void linlsqr_clearrfields(linlsqrstate* state, ae_state *_state);


static double lincg_defaultprecision = 1.0E-6;
static void lincg_clearrfields(lincgstate* state, ae_state *_state);
static void lincg_updateitersdata(lincgstate* state, ae_state *_state);


static void nleq_clearrequestfields(nleqstate* state, ae_state *_state);
static ae_bool nleq_increaselambda(double* lambdav,
     double* nu,
     double lambdaup,
     ae_state *_state);
static void nleq_decreaselambda(double* lambdav,
     double* nu,
     double lambdadown,
     ae_state *_state);





/*************************************************************************
Dense solver.

This  subroutine  solves  a  system  A*x=b,  where A is NxN non-denegerate
real matrix, x and b are vectors.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^3) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   return code:
                * -3    A is singular, or VERY close to singular.
                        X is filled by zeros in such cases.
                * -1    N<=0 was passed
                *  1    task is solved (but matrix A may be ill-conditioned,
                        check R1/RInf parameters for condition numbers).
    Rep     -   solver report, see below for more info
    X       -   array[0..N-1], it contains:
                * solution of A*x=b if A is non-singular (well-conditioned
                  or ill-conditioned, but not very close to singular)
                * zeros,  if  A  is  singular  or  VERY  close to singular
                  (in this case Info=-3).

SOLVER REPORT

Subroutine sets following fields of the Rep structure:
* R1        reciprocal of condition number: 1/cond(A), 1-norm.
* RInf      reciprocal of condition number: 1/cond(A), inf-norm.

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 시스템 A * x = b를 해결합니다. 여기서 A는 NxN 비 - 영속
실수 행렬, x와 b는 벡터입니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 3) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - 리턴 코드 :
                * -3 A는 단수이거나 매우 단수에 가깝습니다.
                        이 경우 X는 0으로 채워집니다.
                * -1 N <= 0을 통과했습니다.
                * 1 작업이 해결되었습니다 (단, 행렬 A는 상태가 좋지 않을 수 있으며,
                        조건 번호에 대한 R1 / RInf 매개 변수 확인).
    담당자 솔버 보고서, 자세한 정보는 아래를 참조하십시오.
    X - 배열 [0..N-1]은 다음을 포함합니다.
                A가 비 특이성 (well-conditioned) 인 경우 A * x = b의 해
                  또는 불량한 상태이지만 단수에 가깝지는 않음)
                * A가 단수이거나 매우 단수에 가까운 경우 0
                  (이 경우 Info = -3).
솔버 리포트
서브 루틴은 Rep 구조의 필드를 다음과 같이 설정합니다.
* R1은 조건 수의 역수입니다. 1 / cond (A), 1-norm.
* 조건 수의 역수 : 1 / cond (A), inf-norm.
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixsolve(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_REAL, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_move(&bm.ptr.pp_double[0][0], bm.stride, &b->ptr.p_double[0], 1, ae_v_len(0,n-1));
    rmatrixsolvem(a, n, &bm, 1, ae_true, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_move(&x->ptr.p_double[0], 1, &xm.ptr.pp_double[0][0], xm.stride, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver.

Similar to RMatrixSolve() but solves task with multiple right parts (where
b and x are NxM matrices).

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* optional iterative refinement
* O(N^3+M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size
    RFS     -   iterative refinement switch:
                * True - refinement is used.
                  Less performance, more precision.
                * False - refinement is not used.
                  More performance, less precision.

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
RMatrixSolve ()와 비슷하지만 여러 개의 오른쪽 부분으로 작업을 해결합니다 (여기서
b 및 x는 N × M 행렬이다).
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 선택적 반복적 인 정제
* O (N ^ 3 + M * N ^ 2) 복잡도
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
    RFS - 반복적 인 구체화 스위치 :
                * 진실 - 세련미가 사용됩니다.
                  성능이 떨어지며 정밀도가 높아집니다.
                * 거짓 - 세련미가 사용되지 않습니다.
                  성능이 향상되고 정확도는 떨어집니다.
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixsolvem(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_bool rfs,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix da;
    ae_matrix emptya;
    ae_vector p;
    double scalea;
    ae_int_t i;
    ae_int_t j;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&da, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&emptya, 0, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&p, 0, DT_INT, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&da, n, n, _state);
    
    /*
     * 1. scale matrix, max(|A[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    scalea = 0;
    for(i=0; i<=n-1; i++)
    {
        for(j=0; j<=n-1; j++)
        {
            scalea = ae_maxreal(scalea, ae_fabs(a->ptr.pp_double[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(scalea,0) )
    {
        scalea = 1;
    }
    scalea = 1/scalea;
    for(i=0; i<=n-1; i++)
    {
        ae_v_move(&da.ptr.pp_double[i][0], 1, &a->ptr.pp_double[i][0], 1, ae_v_len(0,n-1));
    }
    rmatrixlu(&da, n, n, &p, _state);
    if( rfs )
    {
        densesolver_rmatrixlusolveinternal(&da, &p, scalea, n, a, ae_true, b, m, info, rep, x, _state);
    }
    else
    {
        densesolver_rmatrixlusolveinternal(&da, &p, scalea, n, &emptya, ae_false, b, m, info, rep, x, _state);
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver.

This  subroutine  solves  a  system  A*X=B,  where A is NxN non-denegerate
real matrix given by its LU decomposition, X and B are NxM real matrices.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation

No iterative refinement  is provided because exact form of original matrix
is not known to subroutine. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve
    
  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 시스템 A * X = B를 해결합니다. 여기서 A는 NxN 비 - denegerate입니다.
그것의 LU 분해에 의해 주어진 실제 행렬, X와 B는 NxM 실수 행렬이다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
    
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixlusolve(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_REAL, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_move(&bm.ptr.pp_double[0][0], bm.stride, &b->ptr.p_double[0], 1, ae_v_len(0,n-1));
    rmatrixlusolvem(lua, p, n, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_move(&x->ptr.p_double[0], 1, &xm.ptr.pp_double[0][0], xm.stride, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver.

Similar to RMatrixLUSolve() but solves task with multiple right parts
(where b and x are NxM matrices).

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation

No iterative refinement  is provided because exact form of original matrix
is not known to subroutine. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
RMatrixLUSolve ()와 비슷하지만 여러 개의 오른쪽 부분으로 작업을 해결합니다.
(여기서 b와 x는 N × M 행렬 임).
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixlusolvem(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix emptya;
    ae_int_t i;
    ae_int_t j;
    double scalea;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&emptya, 0, 0, DT_REAL, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    
    /*
     * 1. scale matrix, max(|U[i,j]|)
     *    we assume that LU is in its normal form, i.e. |L[i,j]|<=1
     * 2. solve
     */
    /*
     * 1. 스케일 행렬, max (| U [i, j] |)
     * LU는 정상적인 형태, 즉 | L [i, j] | <= 1이라고 가정합니다
     * 2. 해결하기
     */
    scalea = 0;
    for(i=0; i<=n-1; i++)
    {
        for(j=i; j<=n-1; j++)
        {
            scalea = ae_maxreal(scalea, ae_fabs(lua->ptr.pp_double[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(scalea,0) )
    {
        scalea = 1;
    }
    scalea = 1/scalea;
    densesolver_rmatrixlusolveinternal(lua, p, scalea, n, &emptya, ae_false, b, m, info, rep, x, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver.

This  subroutine  solves  a  system  A*x=b,  where BOTH ORIGINAL A AND ITS
LU DECOMPOSITION ARE KNOWN. You can use it if for some  reasons  you  have
both A and its LU decomposition.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 시스템 A * x = b를 해결합니다. 여기서 B는 원래 A와 ITS
LU DECODPOSITION을 (를) 알고 있습니다. 당신은 당신이 가지고있는 몇 가지 이유가 있다면 그것을 사용할 수 있습니다.
A와 LU 분해 모두.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixmixedsolve(/* Real    */ ae_matrix* a,
     /* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_REAL, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_move(&bm.ptr.pp_double[0][0], bm.stride, &b->ptr.p_double[0], 1, ae_v_len(0,n-1));
    rmatrixmixedsolvem(a, lua, p, n, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_move(&x->ptr.p_double[0], 1, &xm.ptr.pp_double[0][0], xm.stride, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver.

Similar to RMatrixMixedSolve() but  solves task with multiple right  parts
(where b and x are NxM matrices).

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
RMatrixMixedSolve ()와 비슷하지만 여러 개의 오른쪽 부분으로 작업을 해결합니다.
(여기서 b와 x는 N × M 행렬 임).
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (M * N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void rmatrixmixedsolvem(/* Real    */ ae_matrix* a,
     /* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    double scalea;
    ae_int_t i;
    ae_int_t j;

    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        return;
    }
    
    /*
     * 1. scale matrix, max(|A[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    /*
     * 1. 스케일 행렬, max (| A [i, j] |)
     * 2. 스케일 된 행렬을 인수 분해합니다.
     * 3. 해결하기
     */
    scalea = 0;
    for(i=0; i<=n-1; i++)
    {
        for(j=0; j<=n-1; j++)
        {
            scalea = ae_maxreal(scalea, ae_fabs(a->ptr.pp_double[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(scalea,0) )
    {
        scalea = 1;
    }
    scalea = 1/scalea;
    densesolver_rmatrixlusolveinternal(lua, p, scalea, n, a, ae_true, b, m, info, rep, x, _state);
}


/*************************************************************************
Dense solver. Same as RMatrixSolveM(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^3+M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size
    RFS     -   iterative refinement switch:
                * True - refinement is used.
                  Less performance, more precision.
                * False - refinement is not used.
                  More performance, less precision.

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolveM ()과 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 3 + M * N ^ 2) 복잡도
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
    RFS - 반복적 인 구체화 스위치 :
                * 진실 - 세련미가 사용됩니다.
                  성능이 떨어지며 정밀도가 높아집니다.
                * 거짓 - 세련미가 사용되지 않습니다.
                  성능이 향상되고 정확도는 떨어집니다.
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixsolvem(/* Complex */ ae_matrix* a,
     ae_int_t n,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_bool rfs,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix da;
    ae_matrix emptya;
    ae_vector p;
    double scalea;
    ae_int_t i;
    ae_int_t j;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&da, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_matrix_init(&emptya, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&p, 0, DT_INT, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&da, n, n, _state);
    
    /*
     * 1. scale matrix, max(|A[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    /*
     * 1. 스케일 행렬, max (| A [i, j] |)
     * 2. 스케일 된 행렬을 인수 분해합니다.
     * 3. 해결하기
     */
    scalea = 0;
    for(i=0; i<=n-1; i++)
    {
        for(j=0; j<=n-1; j++)
        {
            scalea = ae_maxreal(scalea, ae_c_abs(a->ptr.pp_complex[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(scalea,0) )
    {
        scalea = 1;
    }
    scalea = 1/scalea;
    for(i=0; i<=n-1; i++)
    {
        ae_v_cmove(&da.ptr.pp_complex[i][0], 1, &a->ptr.pp_complex[i][0], 1, "N", ae_v_len(0,n-1));
    }
    cmatrixlu(&da, n, n, &p, _state);
    if( rfs )
    {
        densesolver_cmatrixlusolveinternal(&da, &p, scalea, n, a, ae_true, b, m, info, rep, x, _state);
    }
    else
    {
        densesolver_cmatrixlusolveinternal(&da, &p, scalea, n, &emptya, ae_false, b, m, info, rep, x, _state);
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixSolve(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^3) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolve ()와 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 3) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */

void cmatrixsolve(/* Complex */ ae_matrix* a,
     ae_int_t n,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_COMPLEX, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_cmove(&bm.ptr.pp_complex[0][0], bm.stride, &b->ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
    cmatrixsolvem(a, n, &bm, 1, ae_true, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_cmove(&x->ptr.p_complex[0], 1, &xm.ptr.pp_complex[0][0], xm.stride, "N", ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixLUSolveM(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation

No iterative refinement  is provided because exact form of original matrix
is not known to subroutine. Use CMatrixSolve or CMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, RMatrixLU result
    P       -   array[0..N-1], pivots array, RMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolveM ()과 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. CMatrixSolve 또는 CMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA - 배열 [0..N-1.0..N-1], LU 분해, RMatrixLU 결과
    P - 배열 [0..N-1], 축 배열, RMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixlusolvem(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix emptya;
    ae_int_t i;
    ae_int_t j;
    double scalea;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&emptya, 0, 0, DT_COMPLEX, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    
    /*
     * 1. scale matrix, max(|U[i,j]|)
     *    we assume that LU is in its normal form, i.e. |L[i,j]|<=1
     * 2. solve
     */
    /*
     * 1. 스케일 행렬, max (| U [i, j] |)
     * LU는 정상적인 형태, 즉 | L [i, j] | <= 1이라고 가정합니다
     * 2. 해결하기
     */
    scalea = 0;
    for(i=0; i<=n-1; i++)
    {
        for(j=i; j<=n-1; j++)
        {
            scalea = ae_maxreal(scalea, ae_c_abs(lua->ptr.pp_complex[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(scalea,0) )
    {
        scalea = 1;
    }
    scalea = 1/scalea;
    densesolver_cmatrixlusolveinternal(lua, p, scalea, n, &emptya, ae_false, b, m, info, rep, x, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixLUSolve(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation

No iterative refinement is provided because exact form of original matrix
is not known to subroutine. Use CMatrixSolve or CMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    LUA     -   array[0..N-1,0..N-1], LU decomposition, CMatrixLU result
    P       -   array[0..N-1], pivots array, CMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolve ()와 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
원본 행렬의 정확한 형태 때문에 반복적 인 정제가 제공되지 않습니다.
서브 루틴으로 알려져 있지 않습니다. CMatrixSolve 또는 CMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    LUA- 어레이 [0..N-1.0..N-1], LU 분해, CMatrixLU 결과
    P- 배열 [0..N-1], 축 배열, CMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixlusolve(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_COMPLEX, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_cmove(&bm.ptr.pp_complex[0][0], bm.stride, &b->ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
    cmatrixlusolvem(lua, p, n, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_cmove(&x->ptr.p_complex[0], 1, &xm.ptr.pp_complex[0][0], xm.stride, "N", ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixMixedSolveM(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(M*N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, CMatrixLU result
    P       -   array[0..N-1], pivots array, CMatrixLU result
    N       -   size of A
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixMixedSolveM ()과 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (M * N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA- 어레이 [0..N-1.0..N-1], LU 분해, CMatrixLU 결과
    P- 배열 [0..N-1], 축 배열, CMatrixLU 결과
    A의 N - 크기
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixmixedsolvem(/* Complex */ ae_matrix* a,
     /* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    double scalea;
    ae_int_t i;
    ae_int_t j;

    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */


    if( n<=0||m<=0 )
    {
        *info = -1;
        return;
    }
    
    /*
     * 1. scale matrix, max(|A[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    /*
     * 1. 스케일 행렬, max (| A [i, j] |)
     * 2. 스케일 된 행렬을 인수 분해합니다.
     * 3. 해결하기
     */
    scalea = 0;
    for(i=0; i<=n-1; i++)
    {
        for(j=0; j<=n-1; j++)
        {
            scalea = ae_maxreal(scalea, ae_c_abs(a->ptr.pp_complex[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(scalea,0) )
    {
        scalea = 1;
    }
    scalea = 1/scalea;
    densesolver_cmatrixlusolveinternal(lua, p, scalea, n, a, ae_true, b, m, info, rep, x, _state);
}


/*************************************************************************
Dense solver. Same as RMatrixMixedSolve(), but for complex matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* iterative refinement
* O(N^2) complexity

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    LUA     -   array[0..N-1,0..N-1], LU decomposition, CMatrixLU result
    P       -   array[0..N-1], pivots array, CMatrixLU result
    N       -   size of A
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolveM
    Rep     -   same as in RMatrixSolveM
    X       -   same as in RMatrixSolveM

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixMixedSolve ()와 동일하지만 복잡한 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* 반복적 인 정제
* O (N ^ 2) 복잡성
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    LUA- 어레이 [0..N-1.0..N-1], LU 분해, CMatrixLU 결과
    P- 배열 [0..N-1], 축 배열, CMatrixLU 결과
    A의 N - 크기
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolveM과 동일
    Rep - RMatrixSolveM과 동일
    X - RMatrixSolveM과 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void cmatrixmixedsolve(/* Complex */ ae_matrix* a,
     /* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_COMPLEX, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_cmove(&bm.ptr.pp_complex[0][0], bm.stride, &b->ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
    cmatrixmixedsolvem(a, lua, p, n, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_cmove(&x->ptr.p_complex[0], 1, &xm.ptr.pp_complex[0][0], xm.stride, "N", ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixSolveM(), but for symmetric positive definite
matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3+M*N^2) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve.
                Returns -3 for non-SPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolveM ()과 동일하지만 대칭적인 양의 확정적
행렬.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3 + M * N ^ 2) 복잡도
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    Info - RMatrixSolve와 동일합니다.
                비 SPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixsolvem(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix da;
    double sqrtscalea;
    ae_int_t i;
    ae_int_t j;
    ae_int_t j1;
    ae_int_t j2;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&da, 0, 0, DT_REAL, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&da, n, n, _state);
    
    /*
     * 1. scale matrix, max(|A[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    sqrtscalea = 0;
    for(i=0; i<=n-1; i++)
    {
        if( isupper )
        {
            j1 = i;
            j2 = n-1;
        }
        else
        {
            j1 = 0;
            j2 = i;
        }
        for(j=j1; j<=j2; j++)
        {
            sqrtscalea = ae_maxreal(sqrtscalea, ae_fabs(a->ptr.pp_double[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(sqrtscalea,0) )
    {
        sqrtscalea = 1;
    }
    sqrtscalea = 1/sqrtscalea;
    sqrtscalea = ae_sqrt(sqrtscalea, _state);
    for(i=0; i<=n-1; i++)
    {
        if( isupper )
        {
            j1 = i;
            j2 = n-1;
        }
        else
        {
            j1 = 0;
            j2 = i;
        }
        ae_v_move(&da.ptr.pp_double[i][j1], 1, &a->ptr.pp_double[i][j1], 1, ae_v_len(j1,j2));
    }
    if( !spdmatrixcholesky(&da, n, isupper, _state) )
    {
        ae_matrix_set_length(x, n, m, _state);
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=m-1; j++)
            {
                x->ptr.pp_double[i][j] = 0;
            }
        }
        rep->r1 = 0;
        rep->rinf = 0;
        *info = -3;
        ae_frame_leave(_state);
        return;
    }
    *info = 1;
    densesolver_spdmatrixcholeskysolveinternal(&da, sqrtscalea, n, isupper, a, ae_true, b, m, info, rep, x, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixSolve(), but for SPD matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
                Returns -3 for non-SPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolve ()와 동일하지만 SPD 행렬에 사용됩니다.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3) 복잡성
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
                비 SPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixsolve(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_REAL, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_move(&bm.ptr.pp_double[0][0], bm.stride, &b->ptr.p_double[0], 1, ae_v_len(0,n-1));
    spdmatrixsolvem(a, n, isupper, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_move(&x->ptr.p_double[0], 1, &xm.ptr.pp_double[0][0], xm.stride, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixLUSolveM(), but for SPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                SPDMatrixCholesky result
    N       -   size of CHA
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolveM ()과 동일하지만 표현 된 SPD 행렬
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                SPDMatrixCholesky 결과
    CHA의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixcholeskysolvem(/* Real    */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix emptya;
    double sqrtscalea;
    ae_int_t i;
    ae_int_t j;
    ae_int_t j1;
    ae_int_t j2;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&emptya, 0, 0, DT_REAL, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    
    /*
     * 1. scale matrix, max(|U[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    /*
     * 1. 스케일 행렬, max (| U [i, j] |)
     * 2. 스케일 된 행렬을 인수 분해합니다.
     * 3. 해결하기
     */
    sqrtscalea = 0;
    for(i=0; i<=n-1; i++)
    {
        if( isupper )
        {
            j1 = i;
            j2 = n-1;
        }
        else
        {
            j1 = 0;
            j2 = i;
        }
        for(j=j1; j<=j2; j++)
        {
            sqrtscalea = ae_maxreal(sqrtscalea, ae_fabs(cha->ptr.pp_double[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(sqrtscalea,0) )
    {
        sqrtscalea = 1;
    }
    sqrtscalea = 1/sqrtscalea;
    densesolver_spdmatrixcholeskysolveinternal(cha, sqrtscalea, n, isupper, &emptya, ae_false, b, m, info, rep, x, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixLUSolve(), but for  SPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                SPDMatrixCholesky result
    N       -   size of A
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolve ()와 동일하지만 표현 된 SPD 행렬
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                SPDMatrixCholesky 결과
    A의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void spdmatrixcholeskysolve(/* Real    */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_REAL, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_move(&bm.ptr.pp_double[0][0], bm.stride, &b->ptr.p_double[0], 1, ae_v_len(0,n-1));
    spdmatrixcholeskysolvem(cha, n, isupper, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_move(&x->ptr.p_double[0], 1, &xm.ptr.pp_double[0][0], xm.stride, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixSolveM(), but for Hermitian positive definite
matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3+M*N^2) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve.
                Returns -3 for non-HPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolveM ()과 동일하지만, Hermitian positive definite
행렬.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3 + M * N ^ 2) 복잡도
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    Info - RMatrixSolve와 동일합니다.
                비 HPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixsolvem(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix da;
    double sqrtscalea;
    ae_int_t i;
    ae_int_t j;
    ae_int_t j1;
    ae_int_t j2;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&da, 0, 0, DT_COMPLEX, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&da, n, n, _state);
    
    /*
     * 1. scale matrix, max(|A[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    /*
     * 1. 스케일 행렬, max (| A [i, j] |)
     * 2. 스케일 된 행렬을 인수 분해합니다.
     * 3. 해결하기
     */
    sqrtscalea = 0;
    for(i=0; i<=n-1; i++)
    {
        if( isupper )
        {
            j1 = i;
            j2 = n-1;
        }
        else
        {
            j1 = 0;
            j2 = i;
        }
        for(j=j1; j<=j2; j++)
        {
            sqrtscalea = ae_maxreal(sqrtscalea, ae_c_abs(a->ptr.pp_complex[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(sqrtscalea,0) )
    {
        sqrtscalea = 1;
    }
    sqrtscalea = 1/sqrtscalea;
    sqrtscalea = ae_sqrt(sqrtscalea, _state);
    for(i=0; i<=n-1; i++)
    {
        if( isupper )
        {
            j1 = i;
            j2 = n-1;
        }
        else
        {
            j1 = 0;
            j2 = i;
        }
        ae_v_cmove(&da.ptr.pp_complex[i][j1], 1, &a->ptr.pp_complex[i][j1], 1, "N", ae_v_len(j1,j2));
    }
    if( !hpdmatrixcholesky(&da, n, isupper, _state) )
    {
        ae_matrix_set_length(x, n, m, _state);
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=m-1; j++)
            {
                x->ptr.pp_complex[i][j] = ae_complex_from_d(0);
            }
        }
        rep->r1 = 0;
        rep->rinf = 0;
        *info = -3;
        ae_frame_leave(_state);
        return;
    }
    *info = 1;
    densesolver_hpdmatrixcholeskysolveinternal(&da, sqrtscalea, n, isupper, a, ae_true, b, m, info, rep, x, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixSolve(),  but for Hermitian positive definite
matrices.

Algorithm features:
* automatic detection of degenerate cases
* condition number estimation
* O(N^3) complexity
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    A       -   array[0..N-1,0..N-1], system matrix
    N       -   size of A
    IsUpper -   what half of A is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
                Returns -3 for non-HPD matrices.
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixSolve ()와 동일하지만, Hermitian positive definite
행렬.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* 조건 번호 추정
* O (N ^ 3) 복잡성
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    A- 어레이 [0..N-1.0 ... N-1], 시스템 매트릭스
    A의 N - 크기
    IsUpper - A의 절반이 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
                비 HPD 행렬에 대해 -3을 반환합니다.
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */ 
void hpdmatrixsolve(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_COMPLEX, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_cmove(&bm.ptr.pp_complex[0][0], bm.stride, &b->ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
    hpdmatrixsolvem(a, n, isupper, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_cmove(&x->ptr.p_complex[0], 1, &xm.ptr.pp_complex[0][0], xm.stride, "N", ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixLUSolveM(), but for HPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(M*N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                HPDMatrixCholesky result
    N       -   size of CHA
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1,0..M-1], right part
    M       -   right part size

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolveM ()과 동일하지만 HPD 행렬 표현
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (M * N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                HPDMatrixCholesky 결과
    CHA의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 어레이 [0..N-1.0..M-1], 우측 부분
    M - 오른쪽 부분 크기
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixcholeskysolvem(/* Complex */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix emptya;
    double sqrtscalea;
    ae_int_t i;
    ae_int_t j;
    ae_int_t j1;
    ae_int_t j2;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_matrix_init(&emptya, 0, 0, DT_COMPLEX, _state, ae_true);

    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    
    /*
     * 1. scale matrix, max(|U[i,j]|)
     * 2. factorize scaled matrix
     * 3. solve
     */
    /*
     * 1. 스케일 행렬, max (| U [i, j] |)
     * 2. 스케일 된 행렬을 인수 분해합니다.
     * 3. 해결하기
     */
    sqrtscalea = 0;
    for(i=0; i<=n-1; i++)
    {
        if( isupper )
        {
            j1 = i;
            j2 = n-1;
        }
        else
        {
            j1 = 0;
            j2 = i;
        }
        for(j=j1; j<=j2; j++)
        {
            sqrtscalea = ae_maxreal(sqrtscalea, ae_c_abs(cha->ptr.pp_complex[i][j], _state), _state);
        }
    }
    if( ae_fp_eq(sqrtscalea,0) )
    {
        sqrtscalea = 1;
    }
    sqrtscalea = 1/sqrtscalea;
    densesolver_hpdmatrixcholeskysolveinternal(cha, sqrtscalea, n, isupper, &emptya, ae_false, b, m, info, rep, x, _state);
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver. Same as RMatrixLUSolve(), but for  HPD matrices  represented
by their Cholesky decomposition.

Algorithm features:
* automatic detection of degenerate cases
* O(N^2) complexity
* condition number estimation
* matrix is represented by its upper or lower triangle

No iterative refinement is provided because such partial representation of
matrix does not allow efficient calculation of extra-precise  matrix-vector
products for large matrices. Use RMatrixSolve or RMatrixMixedSolve  if  you
need iterative refinement.

INPUT PARAMETERS
    CHA     -   array[0..N-1,0..N-1], Cholesky decomposition,
                SPDMatrixCholesky result
    N       -   size of A
    IsUpper -   what half of CHA is provided
    B       -   array[0..N-1], right part

OUTPUT PARAMETERS
    Info    -   same as in RMatrixSolve
    Rep     -   same as in RMatrixSolve
    X       -   same as in RMatrixSolve

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석. RMatrixLUSolve ()와 동일하지만 HPD 행렬 표현
콜레 스키 (Cholesky) 분해.
알고리즘 특징 :
* 퇴보 사례 자동 탐지
* O (N ^ 2) 복잡성
* 조건 번호 추정
* 행렬은 위 또는 아래 삼각형으로 표시됩니다.
반복적 인 정제가 제공되지 않습니다.
행렬은 정밀도가 높은 행렬 벡터를 효율적으로 계산할 수 없습니다.
대형 매트릭스 용 제품. RMatrixSolve 또는 RMatrixMixedSolve를 사용하십시오.
반복적 인 정련이 필요하다.
입력 매개 변수
    CHA - 배열 [0..N-1.0..N-1], 콜레 스키 분해,
                SPDMatrixCholesky 결과
    A의 N - 크기
    IsUpper - CHA의 절반은 제공됩니다.
    B- 배열 [0..N-1], 오른쪽 부분
출력 매개 변수
    정보 - RMatrixSolve와 동일
    담당자 - RMatrixSolve와 동일
    X - RMatrixSolve와 동일
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
void hpdmatrixcholeskysolve(/* Complex */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_matrix bm;
    ae_matrix xm;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_vector_clear(x);
    ae_matrix_init(&bm, 0, 0, DT_COMPLEX, _state, ae_true);
    ae_matrix_init(&xm, 0, 0, DT_COMPLEX, _state, ae_true);

    if( n<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(&bm, n, 1, _state);
    ae_v_cmove(&bm.ptr.pp_complex[0][0], bm.stride, &b->ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
    hpdmatrixcholeskysolvem(cha, n, isupper, &bm, 1, info, rep, &xm, _state);
    ae_vector_set_length(x, n, _state);
    ae_v_cmove(&x->ptr.p_complex[0], 1, &xm.ptr.pp_complex[0][0], xm.stride, "N", ae_v_len(0,n-1));
    ae_frame_leave(_state);
}


/*************************************************************************
Dense solver.

This subroutine finds solution of the linear system A*X=B with non-square,
possibly degenerate A.  System  is  solved in the least squares sense, and
general least squares solution  X = X0 + CX*y  which  minimizes |A*X-B| is
returned. If A is non-degenerate, solution in the usual sense is returned.

Algorithm features:
* automatic detection (and correct handling!) of degenerate cases
* iterative refinement
* O(N^3) complexity

INPUT PARAMETERS
    A       -   array[0..NRows-1,0..NCols-1], system matrix
    NRows   -   vertical size of A
    NCols   -   horizontal size of A
    B       -   array[0..NCols-1], right part
    Threshold-  a number in [0,1]. Singular values  beyond  Threshold  are
                considered  zero.  Set  it to 0.0, if you don't understand
                what it means, so the solver will choose good value on its
                own.
                
OUTPUT PARAMETERS
    Info    -   return code:
                * -4    SVD subroutine failed
                * -1    if NRows<=0 or NCols<=0 or Threshold<0 was passed
                *  1    if task is solved
    Rep     -   solver report, see below for more info
    X       -   array[0..N-1,0..M-1], it contains:
                * solution of A*X=B (even for singular A)
                * zeros, if SVD subroutine failed

SOLVER REPORT

Subroutine sets following fields of the Rep structure:
* R2        reciprocal of condition number: 1/cond(A), 2-norm.
* N         = NCols
* K         dim(Null(A))
* CX        array[0..N-1,0..K-1], kernel of A.
            Columns of CX store such vectors that A*CX[i]=0.

  -- ALGLIB --
     Copyright 24.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
고밀도 해석.
이 서브 루틴은 선형 시스템 A * X = B의 해를 찾아서 비 -
아마도 A를 퇴보시킨다. 시스템은 최소 자승법으로 풀린다.
일반적인 최소 자승 해 X = X0 + CX * y | A * XB |를 최소화하는 솔루션 ~이다.
반환되었습니다. A가 비 축퇴이면, 일반적인 의미의 해답이 반환됩니다.
알고리즘 특징 :
* 축축한 사례의 자동 감지 (올바른 취급!)
* 반복적 인 정제
* O (N ^ 3) 복잡성
입력 매개 변수
    A 배열 [0..NRows-1.0 ... NCols-1], 시스템 행렬
    NRows - A의 세로 크기
    NCols - A의 가로 크기
    B- 배열 [0..NCols-1], 오른쪽 부분
    임계 값 - [0,1]의 숫자. 임계 값을 초과하는 단일 값은 다음과 같습니다.
                0으로 간주됩니다. 당신이 이해하지 못한다면 0.0으로 설정하십시오.
                그것이 의미하는 바는 솔버가 좋은 가치를 선택하게됩니다.
                개인적인.
                
출력 매개 변수
    정보 - 리턴 코드 :
                * -4 SVD 서브 루틴 실패
                * NRows <= 0 또는 NCols <= 0 또는 임계 값 <0 인 경우 -1
                * 과제가 해결되면 1
    담당자 솔버 보고서, 자세한 정보는 아래를 참조하십시오.
    X- 배열 [0..N-1.0..M-1]은 다음을 포함합니다.
                * A * X = B의 해 (단수 A에 대해서조차도)
                SVD 서브 루틴이 실패한 경우 * 0
솔버 리포트
서브 루틴은 Rep 구조의 필드를 다음과 같이 설정합니다.
* R2는 조건 수의 역수입니다. 1 / cond (A), 2-norm.
* N = NCols
* K dim (Null (A))
* CX 배열 [0..N-1.0..K-1], A. 커널
            CX의 열은 A * CX [i] = 0과 같은 벡터를 저장합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 24.08.2009
*************************************************** ********************** */
void rmatrixsolvels(/* Real    */ ae_matrix* a,
     ae_int_t nrows,
     ae_int_t ncols,
     /* Real    */ ae_vector* b,
     double threshold,
     ae_int_t* info,
     densesolverlsreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector sv;
    ae_matrix u;
    ae_matrix vt;
    ae_vector rp;
    ae_vector utb;
    ae_vector sutb;
    ae_vector tmp;
    ae_vector ta;
    ae_vector tx;
    ae_vector buf;
    ae_vector w;
    ae_int_t i;
    ae_int_t j;
    ae_int_t nsv;
    ae_int_t kernelidx;
    double v;
    double verr;
    ae_bool svdfailed;
    ae_bool zeroa;
    ae_int_t rfs;
    ae_int_t nrfs;
    ae_bool terminatenexttime;
    ae_bool smallerr;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverlsreport_clear(rep);
    ae_vector_clear(x);
    ae_vector_init(&sv, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&u, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&vt, 0, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&rp, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&utb, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&sutb, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tmp, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&ta, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tx, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&buf, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&w, 0, DT_REAL, _state, ae_true);

    if( (nrows<=0||ncols<=0)||ae_fp_less(threshold,0) )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    if( ae_fp_eq(threshold,0) )
    {
        threshold = 1000*ae_machineepsilon;
    }
    
    /*
     * Factorize A first
     */
    /*
     * 먼저 요소 분해
     */
    svdfailed = !rmatrixsvd(a, nrows, ncols, 1, 2, 2, &sv, &u, &vt, _state);
    zeroa = ae_fp_eq(sv.ptr.p_double[0],0);
    if( svdfailed||zeroa )
    {
        if( svdfailed )
        {
            *info = -4;
        }
        else
        {
            *info = 1;
        }
        ae_vector_set_length(x, ncols, _state);
        for(i=0; i<=ncols-1; i++)
        {
            x->ptr.p_double[i] = 0;
        }
        rep->n = ncols;
        rep->k = ncols;
        ae_matrix_set_length(&rep->cx, ncols, ncols, _state);
        for(i=0; i<=ncols-1; i++)
        {
            for(j=0; j<=ncols-1; j++)
            {
                if( i==j )
                {
                    rep->cx.ptr.pp_double[i][j] = 1;
                }
                else
                {
                    rep->cx.ptr.pp_double[i][j] = 0;
                }
            }
        }
        rep->r2 = 0;
        ae_frame_leave(_state);
        return;
    }
    nsv = ae_minint(ncols, nrows, _state);
    if( nsv==ncols )
    {
        rep->r2 = sv.ptr.p_double[nsv-1]/sv.ptr.p_double[0];
    }
    else
    {
        rep->r2 = 0;
    }
    rep->n = ncols;
    *info = 1;
    
    /*
     * Iterative refinement of xc combined with solution:
     * 1. xc = 0
     * 2. calculate r = bc-A*xc using extra-precise dot product
     * 3. solve A*y = r
     * 4. update x:=x+r
     * 5. goto 2
     *
     * This cycle is executed until one of two things happens:
     * 1. maximum number of iterations reached
     * 2. last iteration decreased error to the lower limit
     */
    /*
     * 솔루션과 결합 된 xc의 반복 정제 :
     * 1. xc = 0
     * 2. 정확한 정밀 내적을 사용하여 r = bc-A * xc를 계산하십시오.
     * 3. A * y = r를 푸십시오.
     * 4. 업데이트 x : = x + r
     * 5. goto 2
     *
     *이 사이클은 두 가지 중 하나가 발생할 때까지 실행됩니다.
     * 1. 최대 반복 횟수
     * 2. 마지막 반복은 오류를 하한까지 줄였습니다.
     */
    ae_vector_set_length(&utb, nsv, _state);
    ae_vector_set_length(&sutb, nsv, _state);
    ae_vector_set_length(x, ncols, _state);
    ae_vector_set_length(&tmp, ncols, _state);
    ae_vector_set_length(&ta, ncols+1, _state);
    ae_vector_set_length(&tx, ncols+1, _state);
    ae_vector_set_length(&buf, ncols+1, _state);
    for(i=0; i<=ncols-1; i++)
    {
        x->ptr.p_double[i] = 0;
    }
    kernelidx = nsv;
    for(i=0; i<=nsv-1; i++)
    {
        if( ae_fp_less_eq(sv.ptr.p_double[i],threshold*sv.ptr.p_double[0]) )
        {
            kernelidx = i;
            break;
        }
    }
    rep->k = ncols-kernelidx;
    nrfs = densesolver_densesolverrfsmaxv2(ncols, rep->r2, _state);
    terminatenexttime = ae_false;
    ae_vector_set_length(&rp, nrows, _state);
    for(rfs=0; rfs<=nrfs; rfs++)
    {
        if( terminatenexttime )
        {
            break;
        }
        
        /*
         * calculate right part
         */
        /*
         * 오른쪽 부분 계산
         */
        if( rfs==0 )
        {
            ae_v_move(&rp.ptr.p_double[0], 1, &b->ptr.p_double[0], 1, ae_v_len(0,nrows-1));
        }
        else
        {
            smallerr = ae_true;
            for(i=0; i<=nrows-1; i++)
            {
                ae_v_move(&ta.ptr.p_double[0], 1, &a->ptr.pp_double[i][0], 1, ae_v_len(0,ncols-1));
                ta.ptr.p_double[ncols] = -1;
                ae_v_move(&tx.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,ncols-1));
                tx.ptr.p_double[ncols] = b->ptr.p_double[i];
                xdot(&ta, &tx, ncols+1, &buf, &v, &verr, _state);
                rp.ptr.p_double[i] = -v;
                smallerr = smallerr&&ae_fp_less(ae_fabs(v, _state),4*verr);
            }
            if( smallerr )
            {
                terminatenexttime = ae_true;
            }
        }
        
        /*
         * solve A*dx = rp
         */
        /*
         * 해결 A * dx = rp
         */
        for(i=0; i<=ncols-1; i++)
        {
            tmp.ptr.p_double[i] = 0;
        }
        for(i=0; i<=nsv-1; i++)
        {
            utb.ptr.p_double[i] = 0;
        }
        for(i=0; i<=nrows-1; i++)
        {
            v = rp.ptr.p_double[i];
            ae_v_addd(&utb.ptr.p_double[0], 1, &u.ptr.pp_double[i][0], 1, ae_v_len(0,nsv-1), v);
        }
        for(i=0; i<=nsv-1; i++)
        {
            if( i<kernelidx )
            {
                sutb.ptr.p_double[i] = utb.ptr.p_double[i]/sv.ptr.p_double[i];
            }
            else
            {
                sutb.ptr.p_double[i] = 0;
            }
        }
        for(i=0; i<=nsv-1; i++)
        {
            v = sutb.ptr.p_double[i];
            ae_v_addd(&tmp.ptr.p_double[0], 1, &vt.ptr.pp_double[i][0], 1, ae_v_len(0,ncols-1), v);
        }
        
        /*
         * update x:  x:=x+dx
         */
        /*
         * 업데이트 x : x : = x + dx
         */
        ae_v_add(&x->ptr.p_double[0], 1, &tmp.ptr.p_double[0], 1, ae_v_len(0,ncols-1));
    }
    
    /*
     * fill CX
     */
    /*
     * 채우기 CX
     */
    if( rep->k>0 )
    {
        ae_matrix_set_length(&rep->cx, ncols, rep->k, _state);
        for(i=0; i<=rep->k-1; i++)
        {
            ae_v_move(&rep->cx.ptr.pp_double[0][i], rep->cx.stride, &vt.ptr.pp_double[kernelidx+i][0], 1, ae_v_len(0,ncols-1));
        }
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Internal LU solver

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
내부 LU 해석기
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static void densesolver_rmatrixlusolveinternal(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_bool havea,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t rfs;
    ae_int_t nrfs;
    ae_vector xc;
    ae_vector y;
    ae_vector bc;
    ae_vector xa;
    ae_vector xb;
    ae_vector tx;
    double v;
    double verr;
    double mxb;
    double scaleright;
    ae_bool smallerr;
    ae_bool terminatenexttime;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_vector_init(&xc, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&y, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&bc, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&xa, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&xb, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tx, 0, DT_REAL, _state, ae_true);

    ae_assert(ae_fp_greater(scalea,0), "Assertion failed", _state);
    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 추정 조건 번호, 가까운 특이점에 대한 테스트
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    for(i=0; i<=n-1; i++)
    {
        if( p->ptr.p_int[i]>n-1||p->ptr.p_int[i]<i )
        {
            *info = -1;
            ae_frame_leave(_state);
            return;
        }
    }
    ae_matrix_set_length(x, n, m, _state);
    ae_vector_set_length(&y, n, _state);
    ae_vector_set_length(&xc, n, _state);
    ae_vector_set_length(&bc, n, _state);
    ae_vector_set_length(&tx, n+1, _state);
    ae_vector_set_length(&xa, n+1, _state);
    ae_vector_set_length(&xb, n+1, _state);
    
    /*
     * estimate condition number, test for near singularity
     */
    /*
     * 추정 조건 번호, 가까운 특이점에 대한 테스트
     */

    rep->r1 = rmatrixlurcond1(lua, n, _state);
    rep->rinf = rmatrixlurcondinf(lua, n, _state);
    if( ae_fp_less(rep->r1,rcondthreshold(_state))||ae_fp_less(rep->rinf,rcondthreshold(_state)) )
    {
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=m-1; j++)
            {
                x->ptr.pp_double[i][j] = 0;
            }
        }
        rep->r1 = 0;
        rep->rinf = 0;
        *info = -3;
        ae_frame_leave(_state);
        return;
    }
    *info = 1;
    
    /*
     * solve
     */
    for(k=0; k<=m-1; k++)
    {
        
        /*
         * copy B to contiguous storage
         */
        /*
         * B를 연속 저장 영역에 복사
         */
        ae_v_move(&bc.ptr.p_double[0], 1, &b->ptr.pp_double[0][k], b->stride, ae_v_len(0,n-1));
        
        /*
         * Scale right part:
         * * MX stores max(|Bi|)
         * * ScaleRight stores actual scaling applied to B when solving systems
         *   it is chosen to make |scaleRight*b| close to 1.
         */
        /*
         * 오른쪽 부분 조정 :
         * * 최대 MX 저장 (| Bi |)
         * * ScaleRight는 시스템을 해결할 때 B에 적용된 실제 크기 조정을 저장합니다.
         * scaleRight * b를 만들기 위해 선택됩니다. 1에 가깝습니다.
         */
        mxb = 0;
        for(i=0; i<=n-1; i++)
        {
            mxb = ae_maxreal(mxb, ae_fabs(bc.ptr.p_double[i], _state), _state);
        }
        if( ae_fp_eq(mxb,0) )
        {
            mxb = 1;
        }
        scaleright = 1/mxb;
        
        /*
         * First, non-iterative part of solution process.
         * We use separate code for this task because
         * XDot is quite slow and we want to save time.
         */
        /*
         * 첫째, 솔루션 프로세스의 비 반복적 부분.
         * 우리는이 작업을 위해 별도의 코드를 사용하기 때문에
         * XDot는 매우 느리고 시간을 절약하고 싶습니다.
         */
        ae_v_moved(&xc.ptr.p_double[0], 1, &bc.ptr.p_double[0], 1, ae_v_len(0,n-1), scaleright);
        densesolver_rbasiclusolve(lua, p, scalea, n, &xc, &tx, _state);
        
        /*
         * Iterative refinement of xc:
         * * calculate r = bc-A*xc using extra-precise dot product
         * * solve A*y = r
         * * update x:=x+r
         *
         * This cycle is executed until one of two things happens:
         * 1. maximum number of iterations reached
         * 2. last iteration decreased error to the lower limit
         */
        /*
         xc의 반복적 인 정제 :
         * * r = bc-A * xc를 정밀도가 높은 내적 값을 사용하여 계산
         * * A * y = r를 푸십시오.
         * * 업데이트 x : = x + r
         *
         *이 사이클은 두 가지 중 하나가 발생할 때까지 실행됩니다.
         * 1. 최대 반복 횟수
         * 2. 마지막 반복은 오류를 하한까지 줄였습니다.
         */
        if( havea )
        {
            nrfs = densesolver_densesolverrfsmax(n, rep->r1, rep->rinf, _state);
            terminatenexttime = ae_false;
            for(rfs=0; rfs<=nrfs-1; rfs++)
            {
                if( terminatenexttime )
                {
                    break;
                }
                
                /*
                 * generate right part
                 */
                /*
                 * 오른쪽 부분 생성
                 */
                smallerr = ae_true;
                ae_v_move(&xb.ptr.p_double[0], 1, &xc.ptr.p_double[0], 1, ae_v_len(0,n-1));
                for(i=0; i<=n-1; i++)
                {
                    ae_v_moved(&xa.ptr.p_double[0], 1, &a->ptr.pp_double[i][0], 1, ae_v_len(0,n-1), scalea);
                    xa.ptr.p_double[n] = -1;
                    xb.ptr.p_double[n] = scaleright*bc.ptr.p_double[i];
                    xdot(&xa, &xb, n+1, &tx, &v, &verr, _state);
                    y.ptr.p_double[i] = -v;
                    smallerr = smallerr&&ae_fp_less(ae_fabs(v, _state),4*verr);
                }
                if( smallerr )
                {
                    terminatenexttime = ae_true;
                }
                
                /*
                 * solve and update
                 */
                /*
                 * 해결 및 업데이트
                 */
                densesolver_rbasiclusolve(lua, p, scalea, n, &y, &tx, _state);
                ae_v_add(&xc.ptr.p_double[0], 1, &y.ptr.p_double[0], 1, ae_v_len(0,n-1));
            }
        }
        
        /*
         * Store xc.
         * Post-scale result.
         */
        /*
         * xc를 저장하십시오.
         * 포스트 스케일 결과.
         */
        v = scalea*mxb;
        ae_v_moved(&x->ptr.pp_double[0][k], x->stride, &xc.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Internal Cholesky solver

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
내부 oles레 스키 솔버
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static void densesolver_spdmatrixcholeskysolveinternal(/* Real    */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* a,
     ae_bool havea,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state)
{
    (void)a;
    (void)havea;

    ae_frame _frame_block;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_vector xc;
    ae_vector y;
    ae_vector bc;
    ae_vector xa;
    ae_vector xb;
    ae_vector tx;
    double v;
    double mxb;
    double scaleright;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_vector_init(&xc, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&y, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&bc, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&xa, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&xb, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tx, 0, DT_REAL, _state, ae_true);

    ae_assert(ae_fp_greater(sqrtscalea,0), "Assertion failed", _state);
    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(x, n, m, _state);
    ae_vector_set_length(&y, n, _state);
    ae_vector_set_length(&xc, n, _state);
    ae_vector_set_length(&bc, n, _state);
    ae_vector_set_length(&tx, n+1, _state);
    ae_vector_set_length(&xa, n+1, _state);
    ae_vector_set_length(&xb, n+1, _state);
    
    /*
     * estimate condition number, test for near singularity
     */
    /*
     * 추정 조건 번호, 가까운 특이점에 대한 테스트
     */
    rep->r1 = spdmatrixcholeskyrcond(cha, n, isupper, _state);
    rep->rinf = rep->r1;
    if( ae_fp_less(rep->r1,rcondthreshold(_state)) )
    {
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=m-1; j++)
            {
                x->ptr.pp_double[i][j] = 0;
            }
        }
        rep->r1 = 0;
        rep->rinf = 0;
        *info = -3;
        ae_frame_leave(_state);
        return;
    }
    *info = 1;
    
    /*
     * solve
     */
    for(k=0; k<=m-1; k++)
    {
        
        /*
         * copy B to contiguous storage
         */
        /*
         * B를 연속 저장 영역에 복사
         */
        ae_v_move(&bc.ptr.p_double[0], 1, &b->ptr.pp_double[0][k], b->stride, ae_v_len(0,n-1));
        
        /*
         * Scale right part:
         * * MX stores max(|Bi|)
         * * ScaleRight stores actual scaling applied to B when solving systems
         *   it is chosen to make |scaleRight*b| close to 1.
         */
        /*
         * 오른쪽 부분 조정 :
         * * 최대 MX 저장 (| Bi |)
         * * ScaleRight는 시스템을 해결할 때 B에 적용된 실제 크기 조정을 저장합니다.
         * scaleRight * b를 만들기 위해 선택됩니다. 1에 가깝습니다.
         */
        mxb = 0;
        for(i=0; i<=n-1; i++)
        {
            mxb = ae_maxreal(mxb, ae_fabs(bc.ptr.p_double[i], _state), _state);
        }
        if( ae_fp_eq(mxb,0) )
        {
            mxb = 1;
        }
        scaleright = 1/mxb;
        
        /*
         * First, non-iterative part of solution process.
         * We use separate code for this task because
         * XDot is quite slow and we want to save time.
         */
        /*
         * 첫째, 솔루션 프로세스의 비 반복적 부분.
         * 우리는이 작업을 위해 별도의 코드를 사용하기 때문에
         * XDot는 매우 느리고 시간을 절약하고 싶습니다.
         */
        ae_v_moved(&xc.ptr.p_double[0], 1, &bc.ptr.p_double[0], 1, ae_v_len(0,n-1), scaleright);
        densesolver_spdbasiccholeskysolve(cha, sqrtscalea, n, isupper, &xc, &tx, _state);
        
        /*
         * Store xc.
         * Post-scale result.
         */
        /*
         * xc를 저장하십시오.
         * 포스트 스케일 결과.
         */
        v = ae_sqr(sqrtscalea, _state)*mxb;
        ae_v_moved(&x->ptr.pp_double[0][k], x->stride, &xc.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Internal LU solver

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
내부 LU 해석기
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static void densesolver_cmatrixlusolveinternal(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_bool havea,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t rfs;
    ae_int_t nrfs;
    ae_vector xc;
    ae_vector y;
    ae_vector bc;
    ae_vector xa;
    ae_vector xb;
    ae_vector tx;
    ae_vector tmpbuf;
    ae_complex v;
    double verr;
    double mxb;
    double scaleright;
    ae_bool smallerr;
    ae_bool terminatenexttime;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_vector_init(&xc, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&y, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&bc, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&xa, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&xb, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&tx, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&tmpbuf, 0, DT_REAL, _state, ae_true);

    ae_assert(ae_fp_greater(scalea,0), "Assertion failed", _state);
    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */

    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    for(i=0; i<=n-1; i++)
    {
        if( p->ptr.p_int[i]>n-1||p->ptr.p_int[i]<i )
        {
            *info = -1;
            ae_frame_leave(_state);
            return;
        }
    }
    ae_matrix_set_length(x, n, m, _state);
    ae_vector_set_length(&y, n, _state);
    ae_vector_set_length(&xc, n, _state);
    ae_vector_set_length(&bc, n, _state);
    ae_vector_set_length(&tx, n, _state);
    ae_vector_set_length(&xa, n+1, _state);
    ae_vector_set_length(&xb, n+1, _state);
    ae_vector_set_length(&tmpbuf, 2*n+2, _state);
    
    /*
     * estimate condition number, test for near singularity
     */
    /*
     * 추정 조건 번호, 가까운 특이점에 대한 테스트
     */
    rep->r1 = cmatrixlurcond1(lua, n, _state);
    rep->rinf = cmatrixlurcondinf(lua, n, _state);
    if( ae_fp_less(rep->r1,rcondthreshold(_state))||ae_fp_less(rep->rinf,rcondthreshold(_state)) )
    {
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=m-1; j++)
            {
                x->ptr.pp_complex[i][j] = ae_complex_from_d(0);
            }
        }
        rep->r1 = 0;
        rep->rinf = 0;
        *info = -3;
        ae_frame_leave(_state);
        return;
    }
    *info = 1;
    
    /*
     * solve
     */
    for(k=0; k<=m-1; k++)
    {
        
        /*
         * copy B to contiguous storage
         */
        /*
         * B를 연속 저장 영역에 복사
         */
        ae_v_cmove(&bc.ptr.p_complex[0], 1, &b->ptr.pp_complex[0][k], b->stride, "N", ae_v_len(0,n-1));
        
        /*
         * Scale right part:
         * * MX stores max(|Bi|)
         * * ScaleRight stores actual scaling applied to B when solving systems
         *   it is chosen to make |scaleRight*b| close to 1.
         */
        /*
         * 오른쪽 부분 조정 :
         * * 최대 MX 저장 (| Bi |)
         * * ScaleRight는 시스템을 해결할 때 B에 적용된 실제 크기 조정을 저장합니다.
         * scaleRight * b를 만들기 위해 선택됩니다. 1에 가깝습니다.
         */
        mxb = 0;
        for(i=0; i<=n-1; i++)
        {
            mxb = ae_maxreal(mxb, ae_c_abs(bc.ptr.p_complex[i], _state), _state);
        }
        if( ae_fp_eq(mxb,0) )
        {
            mxb = 1;
        }
        scaleright = 1/mxb;
        
        /*
         * First, non-iterative part of solution process.
         * We use separate code for this task because
         * XDot is quite slow and we want to save time.
         */
        /*
         * 첫째, 솔루션 프로세스의 비 반복적 부분.
         * 우리는이 작업을 위해 별도의 코드를 사용하기 때문에
         * XDot는 매우 느리고 시간을 절약하고 싶습니다.
         */
        ae_v_cmoved(&xc.ptr.p_complex[0], 1, &bc.ptr.p_complex[0], 1, "N", ae_v_len(0,n-1), scaleright);
        densesolver_cbasiclusolve(lua, p, scalea, n, &xc, &tx, _state);
        
        /*
         * Iterative refinement of xc:
         * * calculate r = bc-A*xc using extra-precise dot product
         * * solve A*y = r
         * * update x:=x+r
         *
         * This cycle is executed until one of two things happens:
         * 1. maximum number of iterations reached
         * 2. last iteration decreased error to the lower limit
         */
        /*
         xc의 반복적 인 정제 :
         * * r = bc-A * xc를 정밀도가 높은 내적 값을 사용하여 계산
         * * A * y = r를 푸십시오.
         * * 업데이트 x : = x + r
         *
         *이 사이클은 두 가지 중 하나가 발생할 때까지 실행됩니다.
         * 1. 최대 반복 횟수
         * 2. 마지막 반복은 오류를 하한까지 줄였습니다.
         */
        if( havea )
        {
            nrfs = densesolver_densesolverrfsmax(n, rep->r1, rep->rinf, _state);
            terminatenexttime = ae_false;
            for(rfs=0; rfs<=nrfs-1; rfs++)
            {
                if( terminatenexttime )
                {
                    break;
                }
                
                /*
                 * generate right part
                 */
                /*
                 * 오른쪽 부분 생성
                 */
                smallerr = ae_true;
                ae_v_cmove(&xb.ptr.p_complex[0], 1, &xc.ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
                for(i=0; i<=n-1; i++)
                {
                    ae_v_cmoved(&xa.ptr.p_complex[0], 1, &a->ptr.pp_complex[i][0], 1, "N", ae_v_len(0,n-1), scalea);
                    xa.ptr.p_complex[n] = ae_complex_from_d(-1);
                    xb.ptr.p_complex[n] = ae_c_mul_d(bc.ptr.p_complex[i],scaleright);
                    xcdot(&xa, &xb, n+1, &tmpbuf, &v, &verr, _state);
                    y.ptr.p_complex[i] = ae_c_neg(v);
                    smallerr = smallerr&&ae_fp_less(ae_c_abs(v, _state),4*verr);
                }
                if( smallerr )
                {
                    terminatenexttime = ae_true;
                }
                
                /*
                 * solve and update
                 */
                /*
                 * 해결 및 업데이트
                 */
                densesolver_cbasiclusolve(lua, p, scalea, n, &y, &tx, _state);
                ae_v_cadd(&xc.ptr.p_complex[0], 1, &y.ptr.p_complex[0], 1, "N", ae_v_len(0,n-1));
            }
        }
        
        /*
         * Store xc.
         * Post-scale result.
         */
        /*
         * xc를 저장하십시오.
         * 포스트 스케일 결과.
         */
        v = ae_complex_from_d(scalea*mxb);
        ae_v_cmovec(&x->ptr.pp_complex[0][k], x->stride, &xc.ptr.p_complex[0], 1, "N", ae_v_len(0,n-1), v);
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Internal Cholesky solver

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
내부 oles레 스키 솔버
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static void densesolver_hpdmatrixcholeskysolveinternal(/* Complex */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_matrix* a,
     ae_bool havea,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state)
{
    (void)a;
    (void)havea;

    ae_frame _frame_block;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_vector xc;
    ae_vector y;
    ae_vector bc;
    ae_vector xa;
    ae_vector xb;
    ae_vector tx;
    double v;
    double mxb;
    double scaleright;

    ae_frame_make(_state, &_frame_block);
    *info = 0;
    _densesolverreport_clear(rep);
    ae_matrix_clear(x);
    ae_vector_init(&xc, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&y, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&bc, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&xa, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&xb, 0, DT_COMPLEX, _state, ae_true);
    ae_vector_init(&tx, 0, DT_COMPLEX, _state, ae_true);

    ae_assert(ae_fp_greater(sqrtscalea,0), "Assertion failed", _state);
    
    /*
     * prepare: check inputs, allocate space...
     */
    /*
     * 준비 : 입력 확인, 공간 할당 ...
     */
    if( n<=0||m<=0 )
    {
        *info = -1;
        ae_frame_leave(_state);
        return;
    }
    ae_matrix_set_length(x, n, m, _state);
    ae_vector_set_length(&y, n, _state);
    ae_vector_set_length(&xc, n, _state);
    ae_vector_set_length(&bc, n, _state);
    ae_vector_set_length(&tx, n+1, _state);
    ae_vector_set_length(&xa, n+1, _state);
    ae_vector_set_length(&xb, n+1, _state);
    
    /*
     * estimate condition number, test for near singularity
     */
    /*
     * 추정 조건 번호, 가까운 특이점에 대한 테스트
     */
    rep->r1 = hpdmatrixcholeskyrcond(cha, n, isupper, _state);
    rep->rinf = rep->r1;
    if( ae_fp_less(rep->r1,rcondthreshold(_state)) )
    {
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=m-1; j++)
            {
                x->ptr.pp_complex[i][j] = ae_complex_from_d(0);
            }
        }
        rep->r1 = 0;
        rep->rinf = 0;
        *info = -3;
        ae_frame_leave(_state);
        return;
    }
    *info = 1;
    
    /*
     * solve
     */
    for(k=0; k<=m-1; k++)
    {
        
        /*
         * copy B to contiguous storage
         */
        /*
         * B를 연속 저장 영역에 복사
         */
        ae_v_cmove(&bc.ptr.p_complex[0], 1, &b->ptr.pp_complex[0][k], b->stride, "N", ae_v_len(0,n-1));
        
        /*
         * Scale right part:
         * * MX stores max(|Bi|)
         * * ScaleRight stores actual scaling applied to B when solving systems
         *   it is chosen to make |scaleRight*b| close to 1.
         */
        /*
         * 오른쪽 부분 조정 :
         * * 최대 MX 저장 (| Bi |)
         * * ScaleRight는 시스템을 해결할 때 B에 적용된 실제 크기 조정을 저장합니다.
         * scaleRight * b를 만들기 위해 선택됩니다. 1에 가깝습니다.
         */
        mxb = 0;
        for(i=0; i<=n-1; i++)
        {
            mxb = ae_maxreal(mxb, ae_c_abs(bc.ptr.p_complex[i], _state), _state);
        }
        if( ae_fp_eq(mxb,0) )
        {
            mxb = 1;
        }
        scaleright = 1/mxb;
        
        /*
         * First, non-iterative part of solution process.
         * We use separate code for this task because
         * XDot is quite slow and we want to save time.
         */
        /*
         * 첫째, 솔루션 프로세스의 비 반복적 부분.
         * 우리는이 작업을 위해 별도의 코드를 사용하기 때문에
         * XDot는 매우 느리고 시간을 절약하고 싶습니다.
         */
        ae_v_cmoved(&xc.ptr.p_complex[0], 1, &bc.ptr.p_complex[0], 1, "N", ae_v_len(0,n-1), scaleright);
        densesolver_hpdbasiccholeskysolve(cha, sqrtscalea, n, isupper, &xc, &tx, _state);
        
        /*
         * Store xc.
         * Post-scale result.
         */
        /*
         * xc를 저장하십시오.
         * 포스트 스케일 결과.
         */
        v = ae_sqr(sqrtscalea, _state)*mxb;
        ae_v_cmoved(&x->ptr.pp_complex[0][k], x->stride, &xc.ptr.p_complex[0], 1, "N", ae_v_len(0,n-1), v);
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Internal subroutine.
Returns maximum count of RFS iterations as function of:
1. machine epsilon
2. task size.
3. condition number

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
내부 서브 루틴.
다음 함수의 최대 반복 횟수를 반환합니다.
1. 기계 엡실론
2. 작업 크기.
3. 조건 번호
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static ae_int_t densesolver_densesolverrfsmax(ae_int_t n,
     double r1,
     double rinf,
     ae_state *_state)
{
    (void)n;
    (void)r1;
    (void)rinf;
    (void)_state;

    ae_int_t result;


    result = 5;
    return result;
}


/*************************************************************************
Internal subroutine.
Returns maximum count of RFS iterations as function of:
1. machine epsilon
2. task size.
3. norm-2 condition number

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
내부 서브 루틴.
다음 함수의 최대 반복 횟수를 반환합니다.
1. 기계 엡실론
2. 작업 크기.
3. 조건 번호
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static ae_int_t densesolver_densesolverrfsmaxv2(ae_int_t n,
     double r2,
     ae_state *_state)
{
    (void)r2;

    ae_int_t result;


    result = densesolver_densesolverrfsmax(n, 0, 0, _state);
    return result;
}


/*************************************************************************
Basic LU solver for ScaleA*PLU*x = y.

This subroutine assumes that:
* L is well-scaled, and it is U which needs scaling by ScaleA.
* A=PLU is well-conditioned, so no zero divisions or overflow may occur

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
ScaleA * PLU * x = y에 대한 기본 LU 솔버.
이 서브 루틴은 다음을 가정합니다.
* L은 스케일이 잘 맞으며 ScaleA에 의해 스케일링이 필요한 U입니다.
* A = PLU는 양호한 상태이므로 제로 분할 또는 오버 플로우가 발생할 수 없습니다.
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static void densesolver_rbasiclusolve(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Real    */ ae_vector* xb,
     /* Real    */ ae_vector* tmp,
     ae_state *_state)
{
    (void)_state;

    ae_int_t i;
    double v;


    for(i=0; i<=n-1; i++)
    {
        if( p->ptr.p_int[i]!=i )
        {
            v = xb->ptr.p_double[i];
            xb->ptr.p_double[i] = xb->ptr.p_double[p->ptr.p_int[i]];
            xb->ptr.p_double[p->ptr.p_int[i]] = v;
        }
    }
    for(i=1; i<=n-1; i++)
    {
        v = ae_v_dotproduct(&lua->ptr.pp_double[i][0], 1, &xb->ptr.p_double[0], 1, ae_v_len(0,i-1));
        xb->ptr.p_double[i] = xb->ptr.p_double[i]-v;
    }
    xb->ptr.p_double[n-1] = xb->ptr.p_double[n-1]/(scalea*lua->ptr.pp_double[n-1][n-1]);
    for(i=n-2; i>=0; i--)
    {
        ae_v_moved(&tmp->ptr.p_double[i+1], 1, &lua->ptr.pp_double[i][i+1], 1, ae_v_len(i+1,n-1), scalea);
        v = ae_v_dotproduct(&tmp->ptr.p_double[i+1], 1, &xb->ptr.p_double[i+1], 1, ae_v_len(i+1,n-1));
        xb->ptr.p_double[i] = (xb->ptr.p_double[i]-v)/(scalea*lua->ptr.pp_double[i][i]);
    }
}


/*************************************************************************
Basic Cholesky solver for ScaleA*Cholesky(A)'*x = y.

This subroutine assumes that:
* A*ScaleA is well scaled
* A is well-conditioned, so no zero divisions or overflow may occur

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
ScaleA * Cholesky (A)의 기본 Cholesky 솔버 '* x = y입니다.
이 서브 루틴은 다음을 가정합니다.
* A * ScaleA의 크기가 잘 조정되었습니다.
* A는 컨디셔닝이 잘되어있어 제로 나 오버 플로우가 발생하지 않습니다.
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */

static void densesolver_spdbasiccholeskysolve(/* Real    */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* xb,
     /* Real    */ ae_vector* tmp,
     ae_state *_state)
{
    (void)_state;

    ae_int_t i;
    double v;


    
    /*
     * A = L*L' or A=U'*U
     */
    if( isupper )
    {
        
        /*
         * Solve U'*y=b first.
         */
        for(i=0; i<=n-1; i++)
        {
            xb->ptr.p_double[i] = xb->ptr.p_double[i]/(sqrtscalea*cha->ptr.pp_double[i][i]);
            if( i<n-1 )
            {
                v = xb->ptr.p_double[i];
                ae_v_moved(&tmp->ptr.p_double[i+1], 1, &cha->ptr.pp_double[i][i+1], 1, ae_v_len(i+1,n-1), sqrtscalea);
                ae_v_subd(&xb->ptr.p_double[i+1], 1, &tmp->ptr.p_double[i+1], 1, ae_v_len(i+1,n-1), v);
            }
        }
        
        /*
         * Solve U*x=y then.
         */
        for(i=n-1; i>=0; i--)
        {
            if( i<n-1 )
            {
                ae_v_moved(&tmp->ptr.p_double[i+1], 1, &cha->ptr.pp_double[i][i+1], 1, ae_v_len(i+1,n-1), sqrtscalea);
                v = ae_v_dotproduct(&tmp->ptr.p_double[i+1], 1, &xb->ptr.p_double[i+1], 1, ae_v_len(i+1,n-1));
                xb->ptr.p_double[i] = xb->ptr.p_double[i]-v;
            }
            xb->ptr.p_double[i] = xb->ptr.p_double[i]/(sqrtscalea*cha->ptr.pp_double[i][i]);
        }
    }
    else
    {
        
        /*
         * Solve L*y=b first
         */
        for(i=0; i<=n-1; i++)
        {
            if( i>0 )
            {
                ae_v_moved(&tmp->ptr.p_double[0], 1, &cha->ptr.pp_double[i][0], 1, ae_v_len(0,i-1), sqrtscalea);
                v = ae_v_dotproduct(&tmp->ptr.p_double[0], 1, &xb->ptr.p_double[0], 1, ae_v_len(0,i-1));
                xb->ptr.p_double[i] = xb->ptr.p_double[i]-v;
            }
            xb->ptr.p_double[i] = xb->ptr.p_double[i]/(sqrtscalea*cha->ptr.pp_double[i][i]);
        }
        
        /*
         * Solve L'*x=y then.
         */
        for(i=n-1; i>=0; i--)
        {
            xb->ptr.p_double[i] = xb->ptr.p_double[i]/(sqrtscalea*cha->ptr.pp_double[i][i]);
            if( i>0 )
            {
                v = xb->ptr.p_double[i];
                ae_v_moved(&tmp->ptr.p_double[0], 1, &cha->ptr.pp_double[i][0], 1, ae_v_len(0,i-1), sqrtscalea);
                ae_v_subd(&xb->ptr.p_double[0], 1, &tmp->ptr.p_double[0], 1, ae_v_len(0,i-1), v);
            }
        }
    }
}


/*************************************************************************
Basic LU solver for ScaleA*PLU*x = y.

This subroutine assumes that:
* L is well-scaled, and it is U which needs scaling by ScaleA.
* A=PLU is well-conditioned, so no zero divisions or overflow may occur

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
ScaleA * PLU * x = y에 대한 기본 LU 솔버.
이 서브 루틴은 다음을 가정합니다.
* L은 스케일이 잘 맞으며 ScaleA에 의해 스케일링이 필요한 U입니다.
* A = PLU는 양호한 상태이므로 제로 분할 또는 오버 플로우가 발생할 수 없습니다.
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */

static void densesolver_cbasiclusolve(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     double scalea,
     ae_int_t n,
     /* Complex */ ae_vector* xb,
     /* Complex */ ae_vector* tmp,
     ae_state *_state)
{
    (void)_state;

    ae_int_t i;
    ae_complex v;


    for(i=0; i<=n-1; i++)
    {
        if( p->ptr.p_int[i]!=i )
        {
            v = xb->ptr.p_complex[i];
            xb->ptr.p_complex[i] = xb->ptr.p_complex[p->ptr.p_int[i]];
            xb->ptr.p_complex[p->ptr.p_int[i]] = v;
        }
    }
    for(i=1; i<=n-1; i++)
    {
        v = ae_v_cdotproduct(&lua->ptr.pp_complex[i][0], 1, "N", &xb->ptr.p_complex[0], 1, "N", ae_v_len(0,i-1));
        xb->ptr.p_complex[i] = ae_c_sub(xb->ptr.p_complex[i],v);
    }
    xb->ptr.p_complex[n-1] = ae_c_div(xb->ptr.p_complex[n-1],ae_c_mul_d(lua->ptr.pp_complex[n-1][n-1],scalea));
    for(i=n-2; i>=0; i--)
    {
        ae_v_cmoved(&tmp->ptr.p_complex[i+1], 1, &lua->ptr.pp_complex[i][i+1], 1, "N", ae_v_len(i+1,n-1), scalea);
        v = ae_v_cdotproduct(&tmp->ptr.p_complex[i+1], 1, "N", &xb->ptr.p_complex[i+1], 1, "N", ae_v_len(i+1,n-1));
        xb->ptr.p_complex[i] = ae_c_div(ae_c_sub(xb->ptr.p_complex[i],v),ae_c_mul_d(lua->ptr.pp_complex[i][i],scalea));
    }
}


/*************************************************************************
Basic Cholesky solver for ScaleA*Cholesky(A)'*x = y.

This subroutine assumes that:
* A*ScaleA is well scaled
* A is well-conditioned, so no zero divisions or overflow may occur

  -- ALGLIB --
     Copyright 27.01.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
ScaleA * Cholesky (A)의 기본 Cholesky 솔버 '* x = y입니다.
이 서브 루틴은 다음을 가정합니다.
* A * ScaleA의 크기가 잘 조정되었습니다.
* A는 컨디셔닝이 잘되어있어 제로 나 오버 플로우가 발생하지 않습니다.
  - ALGLIB -
     저작권 27.01.2010 Bochkanov Sergey
*************************************************** ********************** */
static void densesolver_hpdbasiccholeskysolve(/* Complex */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* xb,
     /* Complex */ ae_vector* tmp,
     ae_state *_state)
{
    ae_int_t i;
    ae_complex v;


    
    /*
     * A = L*L' or A=U'*U
     */
    if( isupper )
    {
        
        /*
         * Solve U'*y=b first.
         */
        for(i=0; i<=n-1; i++)
        {
            xb->ptr.p_complex[i] = ae_c_div(xb->ptr.p_complex[i],ae_c_mul_d(ae_c_conj(cha->ptr.pp_complex[i][i], _state),sqrtscalea));
            if( i<n-1 )
            {
                v = xb->ptr.p_complex[i];
                ae_v_cmoved(&tmp->ptr.p_complex[i+1], 1, &cha->ptr.pp_complex[i][i+1], 1, "Conj", ae_v_len(i+1,n-1), sqrtscalea);
                ae_v_csubc(&xb->ptr.p_complex[i+1], 1, &tmp->ptr.p_complex[i+1], 1, "N", ae_v_len(i+1,n-1), v);
            }
        }
        
        /*
         * Solve U*x=y then.
         */
        for(i=n-1; i>=0; i--)
        {
            if( i<n-1 )
            {
                ae_v_cmoved(&tmp->ptr.p_complex[i+1], 1, &cha->ptr.pp_complex[i][i+1], 1, "N", ae_v_len(i+1,n-1), sqrtscalea);
                v = ae_v_cdotproduct(&tmp->ptr.p_complex[i+1], 1, "N", &xb->ptr.p_complex[i+1], 1, "N", ae_v_len(i+1,n-1));
                xb->ptr.p_complex[i] = ae_c_sub(xb->ptr.p_complex[i],v);
            }
            xb->ptr.p_complex[i] = ae_c_div(xb->ptr.p_complex[i],ae_c_mul_d(cha->ptr.pp_complex[i][i],sqrtscalea));
        }
    }
    else
    {
        
        /*
         * Solve L*y=b first
         */
        for(i=0; i<=n-1; i++)
        {
            if( i>0 )
            {
                ae_v_cmoved(&tmp->ptr.p_complex[0], 1, &cha->ptr.pp_complex[i][0], 1, "N", ae_v_len(0,i-1), sqrtscalea);
                v = ae_v_cdotproduct(&tmp->ptr.p_complex[0], 1, "N", &xb->ptr.p_complex[0], 1, "N", ae_v_len(0,i-1));
                xb->ptr.p_complex[i] = ae_c_sub(xb->ptr.p_complex[i],v);
            }
            xb->ptr.p_complex[i] = ae_c_div(xb->ptr.p_complex[i],ae_c_mul_d(cha->ptr.pp_complex[i][i],sqrtscalea));
        }
        
        /*
         * Solve L'*x=y then.
         */
        for(i=n-1; i>=0; i--)
        {
            xb->ptr.p_complex[i] = ae_c_div(xb->ptr.p_complex[i],ae_c_mul_d(ae_c_conj(cha->ptr.pp_complex[i][i], _state),sqrtscalea));
            if( i>0 )
            {
                v = xb->ptr.p_complex[i];
                ae_v_cmoved(&tmp->ptr.p_complex[0], 1, &cha->ptr.pp_complex[i][0], 1, "Conj", ae_v_len(0,i-1), sqrtscalea);
                ae_v_csubc(&xb->ptr.p_complex[0], 1, &tmp->ptr.p_complex[0], 1, "N", ae_v_len(0,i-1), v);
            }
        }
    }
}


ae_bool _densesolverreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    densesolverreport *p = (densesolverreport*)_p;
    ae_touch_ptr((void*)p);
    return ae_true;
}


ae_bool _densesolverreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    densesolverreport *dst = (densesolverreport*)_dst;
    densesolverreport *src = (densesolverreport*)_src;
    dst->r1 = src->r1;
    dst->rinf = src->rinf;
    return ae_true;
}


void _densesolverreport_clear(void* _p)
{
    densesolverreport *p = (densesolverreport*)_p;
    ae_touch_ptr((void*)p);
}


void _densesolverreport_destroy(void* _p)
{
    densesolverreport *p = (densesolverreport*)_p;
    ae_touch_ptr((void*)p);
}


ae_bool _densesolverlsreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    densesolverlsreport *p = (densesolverlsreport*)_p;
    ae_touch_ptr((void*)p);
    if( !ae_matrix_init(&p->cx, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _densesolverlsreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    densesolverlsreport *dst = (densesolverlsreport*)_dst;
    densesolverlsreport *src = (densesolverlsreport*)_src;
    dst->r2 = src->r2;
    if( !ae_matrix_init_copy(&dst->cx, &src->cx, _state, make_automatic) )
        return ae_false;
    dst->n = src->n;
    dst->k = src->k;
    return ae_true;
}


void _densesolverlsreport_clear(void* _p)
{
    densesolverlsreport *p = (densesolverlsreport*)_p;
    ae_touch_ptr((void*)p);
    ae_matrix_clear(&p->cx);
}


void _densesolverlsreport_destroy(void* _p)
{
    densesolverlsreport *p = (densesolverlsreport*)_p;
    ae_touch_ptr((void*)p);
    ae_matrix_destroy(&p->cx);
}




/*************************************************************************
This function initializes linear LSQR Solver. This solver is used to solve
non-symmetric (and, possibly, non-square) problems. Least squares solution
is returned for non-compatible systems.

USAGE:
1. User initializes algorithm state with LinLSQRCreate() call
2. User tunes solver parameters with  LinLSQRSetCond() and other functions
3. User  calls  LinLSQRSolveSparse()  function which takes algorithm state 
   and SparseMatrix object.
4. User calls LinLSQRResults() to get solution
5. Optionally, user may call LinLSQRSolveSparse() again to  solve  another  
   problem  with different matrix and/or right part without reinitializing 
   LinLSQRState structure.
  
INPUT PARAMETERS:
    M       -   number of rows in A
    N       -   number of variables, N>0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선형 LSQR 해를 초기화합니다. 이 솔버는
비대칭 (및, 아마도 비 정사각형) 문제. 최소 제곱 솔루션
호환되지 않는 시스템의 경우 반환됩니다.
용법:
1. 사용자가 LinLSQRCreate () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 LinLSQRSetCond () 및 기타 함수를 사용하여 해석기 매개 변수를 조정합니다.
3. 사용자가 알고리즘 상태를 취하는 LinLSQRSolveSparse () 함수를 호출 
   및 SparseMatrix 개체입니다.
4. 사용자가 LinLSQRResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 사용자가 LinLSQRSolveSparse ()를 다시 호출하여 다른 문제를 해결할 수 있습니다  
   재 초기화하지 않고 다른 행렬 및 / 또는 오른쪽 부분의 문제 
   LinLSQRState 구조체입니다.
  
입력 매개 변수 :
    M - A의 행 수
    N - 변수의 수 N> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrcreate(ae_int_t m,
     ae_int_t n,
     linlsqrstate* state,
     ae_state *_state)
{
    ae_int_t i;

    _linlsqrstate_clear(state);

    ae_assert(m>0, "LinLSQRCreate: M<=0", _state);
    ae_assert(n>0, "LinLSQRCreate: N<=0", _state);
    state->m = m;
    state->n = n;
    state->prectype = 0;
    state->epsa = linlsqr_atol;
    state->epsb = linlsqr_btol;
    state->epsc = 1/ae_sqrt(ae_machineepsilon, _state);
    state->maxits = 0;
    state->lambdai = 0;
    state->xrep = ae_false;
    state->running = ae_false;
    
    /*
     * * allocate arrays
     * * set RX to NAN (just for the case user calls Results() without 
     *   calling SolveSparse()
     * * set B to zero
     */
    /*
     * * 배열 할당
     * * RX를 NAN으로 설정합니다 (사례 사용자가 Results ()를 호출하지 않고) 
     * SolveSparse ()를 호출합니다.
     * * B를 0으로 설정
     */
    normestimatorcreate(m, n, 2, 2, &state->nes, _state);
    ae_vector_set_length(&state->rx, state->n, _state);
    ae_vector_set_length(&state->ui, state->m+state->n, _state);
    ae_vector_set_length(&state->uip1, state->m+state->n, _state);
    ae_vector_set_length(&state->vip1, state->n, _state);
    ae_vector_set_length(&state->vi, state->n, _state);
    ae_vector_set_length(&state->omegai, state->n, _state);
    ae_vector_set_length(&state->omegaip1, state->n, _state);
    ae_vector_set_length(&state->d, state->n, _state);
    ae_vector_set_length(&state->x, state->m+state->n, _state);
    ae_vector_set_length(&state->mv, state->m+state->n, _state);
    ae_vector_set_length(&state->mtv, state->n, _state);
    ae_vector_set_length(&state->b, state->m, _state);
    for(i=0; i<=n-1; i++)
    {
        state->rx.ptr.p_double[i] = _state->v_nan;
    }
    for(i=0; i<=m-1; i++)
    {
        state->b.ptr.p_double[i] = 0;
    }
    ae_vector_set_length(&state->rstate.ia, 1+1, _state);
    ae_vector_set_length(&state->rstate.ra, 0+1, _state);
    state->rstate.stage = -1;
}


/*************************************************************************
This function sets right part. By default, right part is zero.

INPUT PARAMETERS:
    B       -   right part, array[N].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은 오른쪽 부분을 설정합니다. 기본적으로 오른쪽 부분은 0입니다.
입력 매개 변수 :
    B - 오른쪽 부분, 배열 [N].
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetb(linlsqrstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state)
{
    ae_int_t i;


    ae_assert(!state->running, "LinLSQRSetB: you can not change B when LinLSQRIteration is running", _state);
    ae_assert(state->m<=b->cnt, "LinLSQRSetB: Length(B)<M", _state);
    ae_assert(isfinitevector(b, state->m, _state), "LinLSQRSetB: B contains infinite or NaN values", _state);
    state->bnorm2 = 0;
    for(i=0; i<=state->m-1; i++)
    {
        state->b.ptr.p_double[i] = b->ptr.p_double[i];
        state->bnorm2 = state->bnorm2+b->ptr.p_double[i]*b->ptr.p_double[i];
    }
}


/*************************************************************************
This  function  changes  preconditioning  settings of LinLSQQSolveSparse()
function. By default, SolveSparse() uses diagonal preconditioner,  but  if
you want to use solver without preconditioning, you can call this function
which forces solver to use unit matrix for preconditioning.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinLSQQSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. 기본적으로 SolveSparse ()는 대각선 전치 조건자를 사용하지만 if
당신은 preconditioning없이 solver를 사용하기를 원한다.이 함수를 호출 할 수있다.
이는 솔버가 전처리를 위해 단위 행렬을 사용하게합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetprecunit(linlsqrstate* state, ae_state *_state)
{


    ae_assert(!state->running, "LinLSQRSetPrecUnit: you can not change preconditioner, because function LinLSQRIteration is running!", _state);
    state->prectype = -1;
}


/*************************************************************************
This  function  changes  preconditioning  settings  of  LinCGSolveSparse()
function.  LinCGSolveSparse() will use diagonal of the  system  matrix  as
preconditioner. This preconditioning mode is active by default.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinCGSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. LinCGSolveSparse ()는 시스템 행렬의 대각선을 다음과 같이 사용합니다.
프리 컨디셔너. 이 사전 조절 모드는 기본적으로 활성화되어 있습니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetprecdiag(linlsqrstate* state, ae_state *_state)
{


    ae_assert(!state->running, "LinLSQRSetPrecDiag: you can not change preconditioner, because function LinCGIteration is running!", _state);
    state->prectype = 0;
}


/*************************************************************************
This function sets optional Tikhonov regularization coefficient.
It is zero by default.

INPUT PARAMETERS:
    LambdaI -   regularization factor, LambdaI>=0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state
    
  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선택적 Tikhonov 정규화 계수를 설정합니다.
기본적으로 0입니다.
입력 매개 변수 :
    람다 - 정규화 인수, 람다> = 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetlambdai(linlsqrstate* state,
     double lambdai,
     ae_state *_state)
{


    ae_assert(!state->running, "LinLSQRSetLambdaI: you can not set LambdaI, because function LinLSQRIteration is running", _state);
    ae_assert(ae_isfinite(lambdai, _state)&&ae_fp_greater_eq(lambdai,0), "LinLSQRSetLambdaI: LambdaI is infinite or NaN", _state);
    state->lambdai = lambdai;
}


/*************************************************************************

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
ae_bool linlsqriteration(linlsqrstate* state, ae_state *_state)
{
    ae_int_t summn;
    double bnorm;
    ae_int_t i;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    /*
     * 역방향 커뮤니케이션 준비
     * 나는 못 생겼다는 것을 알고 있지만, 같은 방식으로 작동한다.
     * C ++에서 Python까지 모든 곳.
     *
     *이 코드는 지역 주민을 다음과 같이 초기화합니다.
     * * 코드에서 결정된 임의의 값
     * 생성 - 첫 번째 서브 루틴 호출
     * * 이전 통화의 값 - 이후 통화시
     */
    if( state->rstate.stage>=0 )
    {
        summn = state->rstate.ia.ptr.p_int[0];
        i = state->rstate.ia.ptr.p_int[1];
        bnorm = state->rstate.ra.ptr.p_double[0];
    }
    else
    {
        summn = -983;
        i = -989;
        bnorm = -834;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    if( state->rstate.stage==4 )
    {
        goto lbl_4;
    }
    if( state->rstate.stage==5 )
    {
        goto lbl_5;
    }
    if( state->rstate.stage==6 )
    {
        goto lbl_6;
    }
    
    /*
     * Routine body
     */
    /*
     * 일상적인 신체
     */
    ae_assert(state->b.cnt>0, "LinLSQRIteration: using non-allocated array B", _state);
    bnorm = ae_sqrt(state->bnorm2, _state);
    state->running = ae_true;
    state->repnmv = 0;
    linlsqr_clearrfields(state, _state);
    state->repiterationscount = 0;
    summn = state->m+state->n;
    state->r2 = state->bnorm2;
    
    /*
     *estimate for ANorm
     */
    /*
     * ANorm에 대한 추정치
     */
    normestimatorrestart(&state->nes, _state);
lbl_7:
    if( !normestimatoriteration(&state->nes, _state) )
    {
        goto lbl_8;
    }
    if( !state->nes.needmv )
    {
        goto lbl_9;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->nes.x.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmv = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needmv = ae_false;
    ae_v_move(&state->nes.mv.ptr.p_double[0], 1, &state->mv.ptr.p_double[0], 1, ae_v_len(0,state->m-1));
    goto lbl_7;
lbl_9:
    if( !state->nes.needmtv )
    {
        goto lbl_11;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->nes.x.ptr.p_double[0], 1, ae_v_len(0,state->m-1));
    
    /*
     *matrix-vector multiplication
     */
    /*
     * 행렬 - 벡터 곱셈
     */
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmtv = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->needmtv = ae_false;
    ae_v_move(&state->nes.mtv.ptr.p_double[0], 1, &state->mtv.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    goto lbl_7;
lbl_11:
    goto lbl_7;
lbl_8:
    normestimatorresults(&state->nes, &state->anorm, _state);
    
    /*
     *initialize .RX by zeros
     */
    /*
     * .RX를 0으로 초기화합니다.
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->rx.ptr.p_double[i] = 0;
    }
    
    /*
     *output first report
     */
    /*
     * 첫 번째 보고서 출력
     */
    if( !state->xrep )
    {
        goto lbl_13;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    linlsqr_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->xupdated = ae_false;
lbl_13:
    
    /*
     * LSQR, Step 0.
     *
     * Algorithm outline corresponds to one which was described at p.50 of
     * "LSQR - an algorithm for sparse linear equations and sparse least 
     * squares" by C.Paige and M.Saunders with one small addition - we
     * explicitly extend system matrix by additional N lines in order 
     * to handle non-zero lambda, i.e. original A is replaced by
     *         [ A        ]
     * A_mod = [          ]
     *         [ lambda*I ].
     *
     * Step 0:
     *     x[0]          = 0
     *     beta[1]*u[1]  = b
     *     alpha[1]*v[1] = A_mod'*u[1]
     *     w[1]          = v[1]
     *     phiBar[1]     = beta[1]
     *     rhoBar[1]     = alpha[1]
     *     d[0]          = 0
     *
     * NOTE:
     * There are three criteria for stopping:
     * (S0) maximum number of iterations
     * (S1) ||Rk||<=EpsB*||B||;
     * (S2) ||A^T*Rk||/(||A||*||Rk||)<=EpsA.
     * It is very important that S2 always checked AFTER S1. It is necessary
     * to avoid division by zero when Rk=0.
     */
    /*
     * LSQR, 0 단계.
     *
     * 알고리즘 개요는 p.50에서 설명한 알고리즘에 해당합니다.
     * "LSQR - 스파 스 선형 방정식 및 스파 스 최소 알고리즘 
     * 사각형 "C.Paige와 M.Saunders에 의해 하나의 작은 추가 - 우리는
     * 명시 적으로 추가 N 줄에 의해 시스템 행렬을 순서대로 확장 
     * 원래의 A가 0이 아닌 람다를 처리하기 위해
     * [A]
     * A_mod = []
     * [λ * I].
     *
     * 단계 0 :
     * x [0] = 0
     * 베타 [1] * u [1] = b
     * 알파 [1] * v [1] = A_mod '* u [1]
     * w [1] = v [1]
     * phiBar [1] = 베타 [1]
     * rhoBar [1] = alpha [1]
     * d [0] = 0
     *
     * 노트:
     * 중지 기준에는 세 가지가 있습니다.
     * (S0) 최대 반복 횟수
     * (S1) || Rk || <= EpsB * || B ||;
     * (S2) || A ^ T * Rk || / (|| A || * || Rk ||) <= EpsA.
     * S2가 항상 AFTER S1을 확인하는 것이 매우 중요합니다. 필요하다.
     * Rk = 0 인 경우 0으로 나누는 것을 피하십시오.
     */
    state->betai = bnorm;
    if( ae_fp_eq(state->betai,0) )
    {
        
        /*
         * Zero right part
         */
        /*
         * 제로 우측 부분
         */
        state->running = ae_false;
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    for(i=0; i<=summn-1; i++)
    {
        if( i<state->m )
        {
            state->ui.ptr.p_double[i] = state->b.ptr.p_double[i]/state->betai;
        }
        else
        {
            state->ui.ptr.p_double[i] = 0;
        }
        state->x.ptr.p_double[i] = state->ui.ptr.p_double[i];
    }
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmtv = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->needmtv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->mtv.ptr.p_double[i] = state->mtv.ptr.p_double[i]+state->lambdai*state->ui.ptr.p_double[state->m+i];
    }
    state->alphai = 0;
    for(i=0; i<=state->n-1; i++)
    {
        state->alphai = state->alphai+state->mtv.ptr.p_double[i]*state->mtv.ptr.p_double[i];
    }
    state->alphai = ae_sqrt(state->alphai, _state);
    if( ae_fp_eq(state->alphai,0) )
    {
        
        /*
         * Orthogonality stopping criterion is met
         */
        /*
         * 직교성 정지 기준 충족
         */
        state->running = ae_false;
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    for(i=0; i<=state->n-1; i++)
    {
        state->vi.ptr.p_double[i] = state->mtv.ptr.p_double[i]/state->alphai;
        state->omegai.ptr.p_double[i] = state->vi.ptr.p_double[i];
    }
    state->phibari = state->betai;
    state->rhobari = state->alphai;
    for(i=0; i<=state->n-1; i++)
    {
        state->d.ptr.p_double[i] = 0;
    }
    state->dnorm = 0;
    
    /*
     * Steps I=1, 2, ...
     */
    /*
     * 단계 I = 1, 2, ...
     */
lbl_15:
    if( ae_false )
    {
        goto lbl_16;
    }
    
    /*
     * At I-th step State.RepIterationsCount=I.
     */
    /*
     * I 단계에서 State.RepIterationsCount = I.
     */
    state->repiterationscount = state->repiterationscount+1;
    
    /*
     * Bidiagonalization part:
     *     beta[i+1]*u[i+1]  = A_mod*v[i]-alpha[i]*u[i]
     *     alpha[i+1]*v[i+1] = A_mod'*u[i+1] - beta[i+1]*v[i]
     *     
     * NOTE:  beta[i+1]=0 or alpha[i+1]=0 will lead to successful termination
     *        in the end of the current iteration. In this case u/v are zero.
     * NOTE2: algorithm won't fail on zero alpha or beta (there will be no
     *        division by zero because it will be stopped BEFORE division
     *        occurs). However, near-zero alpha and beta won't stop algorithm
     *        and, although no division by zero will happen, orthogonality 
     *        in U and V will be lost.
     */
    /*
     * 대각선 화 부분 :
     * β [i + 1] * u [i + 1] = A_mod * v [i] -alpha [i] * u [i]
     * [i + 1] * v [i + 1] = A_mod '* u [i +
     *     
     * 참고 : beta [i + 1] = 0 또는 alpha [i + 1] = 0은 성공적으로 종료됩니다
     * 현재 반복의 끝에. 이 경우 u / v는 0입니다.
     * NOTE2 : 알고리즘은 알파 또는 베타 0에서 실패하지 않습니다.
     * 나누기 전에 중지되므로 0으로 나누기
     * 발생). 그러나 거의 0에 가까운 알파와 베타는 알고리즘을 멈추지 않습니다.
     * 및 제로에 의한 분할은 일어나지 않지만, 직교성 
     U와 V의 *는 사라집니다.
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->vi.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmv = ae_true;
    state->rstate.stage = 4;
    goto lbl_rcomm;
lbl_4:
    state->needmv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->mv.ptr.p_double[state->m+i] = state->lambdai*state->vi.ptr.p_double[i];
    }
    state->betaip1 = 0;
    for(i=0; i<=summn-1; i++)
    {
        state->uip1.ptr.p_double[i] = state->mv.ptr.p_double[i]-state->alphai*state->ui.ptr.p_double[i];
        state->betaip1 = state->betaip1+state->uip1.ptr.p_double[i]*state->uip1.ptr.p_double[i];
    }
    if( ae_fp_neq(state->betaip1,0) )
    {
        state->betaip1 = ae_sqrt(state->betaip1, _state);
        for(i=0; i<=summn-1; i++)
        {
            state->uip1.ptr.p_double[i] = state->uip1.ptr.p_double[i]/state->betaip1;
        }
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->uip1.ptr.p_double[0], 1, ae_v_len(0,state->m-1));
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmtv = ae_true;
    state->rstate.stage = 5;
    goto lbl_rcomm;
lbl_5:
    state->needmtv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->mtv.ptr.p_double[i] = state->mtv.ptr.p_double[i]+state->lambdai*state->uip1.ptr.p_double[state->m+i];
    }
    state->alphaip1 = 0;
    for(i=0; i<=state->n-1; i++)
    {
        state->vip1.ptr.p_double[i] = state->mtv.ptr.p_double[i]-state->betaip1*state->vi.ptr.p_double[i];
        state->alphaip1 = state->alphaip1+state->vip1.ptr.p_double[i]*state->vip1.ptr.p_double[i];
    }
    if( ae_fp_neq(state->alphaip1,0) )
    {
        state->alphaip1 = ae_sqrt(state->alphaip1, _state);
        for(i=0; i<=state->n-1; i++)
        {
            state->vip1.ptr.p_double[i] = state->vip1.ptr.p_double[i]/state->alphaip1;
        }
    }
    
    /*
     * Build next orthogonal transformation
     */
    /*
     * 다음 직교 변환 구축
     */
    state->rhoi = safepythag2(state->rhobari, state->betaip1, _state);
    state->ci = state->rhobari/state->rhoi;
    state->si = state->betaip1/state->rhoi;
    state->theta = state->si*state->alphaip1;
    state->rhobarip1 = -state->ci*state->alphaip1;
    state->phii = state->ci*state->phibari;
    state->phibarip1 = state->si*state->phibari;
    
    /*
     * Update .RNorm
     *
     * This tricky  formula  is  necessary  because  simply  writing
     * State.R2:=State.PhiBarIP1*State.PhiBarIP1 does NOT guarantees
     * monotonic decrease of R2. Roundoff error combined with 80-bit
     * precision used internally by Intel chips allows R2 to increase
     * slightly in some rare, but possible cases. This property is
     * undesirable, so we prefer to guard against R increase.
     */
    /*
     * 업데이트 .RNorm
     *
     *이 까다로운 수식은 단순히 쓰는 것이기 때문에 필요합니다.
     * State.R2 : = State.PhiBarIP1 * State.PhiBarIP1은 보장하지 않습니다.
     * R2의 단조 감소. 80 비트와 결합 된 반올림 오류
     * 인텔 칩에 의해 내부적으로 사용되는 정밀도가 R2를 증가시킵니다.
     * 드문 경우지만 약간 있지만 가능한 경우. 이 속성은
     * 바람직하지 않으므로 R 증가를 방지하는 것이 좋습니다.
     */
    state->r2 = ae_minreal(state->r2, state->phibarip1*state->phibarip1, _state);
    
    /*
     * Update d and DNorm, check condition-related stopping criteria
     */
    /*
     * x 업데이트, 출력 보고서
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->d.ptr.p_double[i] = 1/state->rhoi*(state->vi.ptr.p_double[i]-state->theta*state->d.ptr.p_double[i]);
        state->dnorm = state->dnorm+state->d.ptr.p_double[i]*state->d.ptr.p_double[i];
    }
    if( ae_fp_greater_eq(ae_sqrt(state->dnorm, _state)*state->anorm,state->epsc) )
    {
        state->running = ae_false;
        state->repterminationtype = 7;
        result = ae_false;
        return result;
    }
    
    /*
     * Update x, output report
     */
    /*
     * x 업데이트, 출력 보고서
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->rx.ptr.p_double[i] = state->rx.ptr.p_double[i]+state->phii/state->rhoi*state->omegai.ptr.p_double[i];
    }
    if( !state->xrep )
    {
        goto lbl_17;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    linlsqr_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 6;
    goto lbl_rcomm;
lbl_6:
    state->xupdated = ae_false;
lbl_17:
    
    /*
     * Check stopping criteria
     * 1. achieved required number of iterations;
     * 2. ||Rk||<=EpsB*||B||;
     * 3. ||A^T*Rk||/(||A||*||Rk||)<=EpsA;
     */
    /*
     * 정지 기준 확인
     * 1. 필요한 반복 횟수를 달성했습니다.
     * 2. || Rk || <= EpsB * || B ||;
     * 3. || A ^ T * Rk || / (|| A || * || Rk ||) <= EpsA;
     */
    if( state->maxits>0&&state->repiterationscount>=state->maxits )
    {
        
        /*
         * Achieved required number of iterations
         */
        /*
         * 필요한 반복 횟수 달성
         */
        state->running = ae_false;
        state->repterminationtype = 5;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->phibarip1,state->epsb*bnorm) )
    {
        
        /*
         * ||Rk||<=EpsB*||B||, here ||Rk||=PhiBar
         */
        state->running = ae_false;
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->alphaip1*ae_fabs(state->ci, _state)/state->anorm,state->epsa) )
    {
        
        /*
         * ||A^T*Rk||/(||A||*||Rk||)<=EpsA, here ||A^T*Rk||=PhiBar*Alpha[i+1]*|.C|
         */
        state->running = ae_false;
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    
    /*
     * Update omega
     */
    /*
     * 오메가 업데이트
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->omegaip1.ptr.p_double[i] = state->vip1.ptr.p_double[i]-state->theta/state->rhoi*state->omegai.ptr.p_double[i];
    }
    
    /*
     * Prepare for the next iteration - rename variables:
     * u[i]   := u[i+1]
     * v[i]   := v[i+1]
     * rho[i] := rho[i+1]
     * ...
     */
    ae_v_move(&state->ui.ptr.p_double[0], 1, &state->uip1.ptr.p_double[0], 1, ae_v_len(0,summn-1));
    ae_v_move(&state->vi.ptr.p_double[0], 1, &state->vip1.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_v_move(&state->omegai.ptr.p_double[0], 1, &state->omegaip1.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->alphai = state->alphaip1;
    state->betai = state->betaip1;
    state->phibari = state->phibarip1;
    state->rhobari = state->rhobarip1;
    goto lbl_15;
lbl_16:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
    /*
     * 저장 상태
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = summn;
    state->rstate.ia.ptr.p_int[1] = i;
    state->rstate.ra.ptr.p_double[0] = bnorm;
    return result;
}


/*************************************************************************
Procedure for solution of A*x=b with sparse A.

INPUT PARAMETERS:
    State   -   algorithm state
    A       -   sparse M*N matrix in the CRS format (you MUST contvert  it 
                to CRS format  by  calling  SparseConvertToCRS()  function
                BEFORE you pass it to this function).
    B       -   right part, array[M]

RESULT:
    This function returns no result.
    You can get solution by calling LinCGResults()
    
NOTE: this function uses lightweight preconditioning -  multiplication  by
      inverse of diag(A). If you want, you can turn preconditioning off by
      calling LinLSQRSetPrecUnit(). However, preconditioning cost is   low
      and preconditioner is very important for solution  of  badly  scaled
      problems.

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
스파 스 A가있는 A * x = b의 해를 구하는 절차.
입력 매개 변수 :
    상태 - 알고리즘 상태
    A - CRS 형식의 희소 M * N 행렬 (반드시 변환해야합니다.) 
                SparseConvertToCRS () 함수를 호출하여 CRS 형식으로 변환
                이 함수에 전달하기 전에).
    B - 오른쪽 부분, 배열 [M]
결과:
    이 함수는 결과를 반환하지 않습니다.
    LinCGResults ()를 호출하여 솔루션을 얻을 수 있습니다.
    
참고 :이 함수는 가벼운 전제 조건을 사용합니다.
      diag (A)의 역. 원하는 경우 사전 조건을 해제 할 수 있습니다.
      LinLSQRSetPrecUnit ()을 호출합니다. 그러나 사전 컨디셔닝 비용은 낮습니다.
      전처리 기는 잘못 조정 된 솔루션의 경우 매우 중요합니다.
      문제.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsolvesparse(linlsqrstate* state,
     sparsematrix* a,
     /* Real    */ ae_vector* b,
     ae_state *_state)
{
    ae_int_t n;
    ae_int_t i;
    ae_int_t j;
    ae_int_t t0;
    ae_int_t t1;
    double v;


    n = state->n;
    ae_assert(!state->running, "LinLSQRSolveSparse: you can not call this function when LinLSQRIteration is running", _state);
    ae_assert(b->cnt>=state->m, "LinLSQRSolveSparse: Length(B)<M", _state);
    ae_assert(isfinitevector(b, state->m, _state), "LinLSQRSolveSparse: B contains infinite or NaN values", _state);
    
    /*
     * Allocate temporaries
     */
    /*
     * 임시 직원 할당
     */
    rvectorsetlengthatleast(&state->tmpd, n, _state);
    rvectorsetlengthatleast(&state->tmpx, n, _state);
    
    /*
     * Compute diagonal scaling matrix D
     */
    /*
     * 대각선 스케일링 행렬 D 계산
     */
    if( state->prectype==0 )
    {
        
        /*
         * Default preconditioner - inverse of column norms
         */
        /*
         * 기본 선행 조건 - 열 표준의 역함수
         */
        for(i=0; i<=n-1; i++)
        {
            state->tmpd.ptr.p_double[i] = 0;
        }
        t0 = 0;
        t1 = 0;
        while(sparseenumerate(a, &t0, &t1, &i, &j, &v, _state))
        {
            state->tmpd.ptr.p_double[j] = state->tmpd.ptr.p_double[j]+ae_sqr(v, _state);
        }
        for(i=0; i<=n-1; i++)
        {
            if( ae_fp_greater(state->tmpd.ptr.p_double[i],0) )
            {
                state->tmpd.ptr.p_double[i] = 1/ae_sqrt(state->tmpd.ptr.p_double[i], _state);
            }
            else
            {
                state->tmpd.ptr.p_double[i] = 1;
            }
        }
    }
    else
    {
        
        /*
         * No diagonal scaling
         */
        /*
         * 대각선 크기 조정 없음
         */
        for(i=0; i<=n-1; i++)
        {
            state->tmpd.ptr.p_double[i] = 1;
        }
    }
    
    /*
     * Solve.
     *
     * Instead of solving A*x=b we solve preconditioned system (A*D)*(inv(D)*x)=b.
     * Transformed A is not calculated explicitly, we just modify multiplication
     * by A or A'. After solution we modify State.RX so it will store untransformed
     * variables
     */

    /*
     * 해결.
     *
     * A * x = b를 푸는 대신 사전 조건화 된 시스템 (A * D) * (inv (D) * x) = b를 풀어 냄.
     * 변환 된 A는 명시 적으로 계산되지 않고 곱셈 만 수정합니다.
     * A 또는 A '. 솔루션 후에 State.RX를 수정하여 변환되지 않은 상태로 저장합니다.
     * 변수
     */
    linlsqrsetb(state, b, _state);
    linlsqrrestart(state, _state);
    while(linlsqriteration(state, _state))
    {
        if( state->needmv )
        {
            for(i=0; i<=n-1; i++)
            {
                state->tmpx.ptr.p_double[i] = state->tmpd.ptr.p_double[i]*state->x.ptr.p_double[i];
            }
            sparsemv(a, &state->tmpx, &state->mv, _state);
        }
        if( state->needmtv )
        {
            sparsemtv(a, &state->x, &state->mtv, _state);
            for(i=0; i<=n-1; i++)
            {
                state->mtv.ptr.p_double[i] = state->tmpd.ptr.p_double[i]*state->mtv.ptr.p_double[i];
            }
        }
    }
    for(i=0; i<=n-1; i++)
    {
        state->rx.ptr.p_double[i] = state->tmpd.ptr.p_double[i]*state->rx.ptr.p_double[i];
    }
}


/*************************************************************************
This function sets stopping criteria.

INPUT PARAMETERS:
    EpsA    -   algorithm will be stopped if ||A^T*Rk||/(||A||*||Rk||)<=EpsA.
    EpsB    -   algorithm will be stopped if ||Rk||<=EpsB*||B||
    MaxIts  -   algorithm will be stopped if number of iterations
                more than MaxIts.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTE: if EpsA,EpsB,EpsC and MaxIts are zero then these variables will
be setted as default values.
    
  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 중지 기준을 설정합니다.
입력 매개 변수 :
    EpsA - | A ^ T * Rk || / (|| A || * || Rk ||) <= EpsA이면 알고리즘이 중지됩니다.
    EpsB - | Rk || <= EpsB * || B ||이면 알고리즘이 중지됩니다.
    MaxIts - 반복 횟수에 따라 알고리즘이 중지됩니다.
                MaxIts 이상.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참고 : EpsA, EpsB, EpsC 및 MaxIts가 0이면이 변수는
기본값으로 설정하십시오.
    
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetcond(linlsqrstate* state,
     double epsa,
     double epsb,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(!state->running, "LinLSQRSetCond: you can not call this function when LinLSQRIteration is running", _state);
    ae_assert(ae_isfinite(epsa, _state)&&ae_fp_greater_eq(epsa,0), "LinLSQRSetCond: EpsA is negative, INF or NAN", _state);
    ae_assert(ae_isfinite(epsb, _state)&&ae_fp_greater_eq(epsb,0), "LinLSQRSetCond: EpsB is negative, INF or NAN", _state);
    ae_assert(maxits>=0, "LinLSQRSetCond: MaxIts is negative", _state);
    if( (ae_fp_eq(epsa,0)&&ae_fp_eq(epsb,0))&&maxits==0 )
    {
        state->epsa = linlsqr_atol;
        state->epsb = linlsqr_btol;
        state->maxits = state->n;
    }
    else
    {
        state->epsa = epsa;
        state->epsb = epsb;
        state->maxits = maxits;
    }
}


/*************************************************************************
LSQR solver: results.

This function must be called after LinLSQRSolve

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[N], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    *  1    ||Rk||<=EpsB*||B||
                    *  4    ||A^T*Rk||/(||A||*||Rk||)<=EpsA
                    *  5    MaxIts steps was taken
                    *  7    rounding errors prevent further progress,
                            X contains best point found so far.
                            (sometimes returned on singular systems)
                * Rep.IterationsCount contains iterations count
                * NMV countains number of matrix-vector calculations
                
  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
LSQR solver : 결과.
이 함수는 LinLSQRSolve 뒤에 호출해야합니다.
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X - 배열 [N], 솔루션
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * 1 || Rk || <= EpsB * || B ||
                    * 4 || A ^ T * Rk || / (|| A || * || Rk ||) <= EpsA
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 반올림 오류로 인해 더 이상 진행되지 않습니다.
                            X는 지금까지 발견 된 최상의 포인트를 포함합니다.
                            (때로는 단일 시스템에서 반환 됨)
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                NMV는 매트릭스 - 벡터 계산의 수를 카운트합니다.
                
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
************************************************************************* */
void linlsqrresults(linlsqrstate* state,
     /* Real    */ ae_vector* x,
     linlsqrreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _linlsqrreport_clear(rep);

    ae_assert(!state->running, "LinLSQRResult: you can not call this function when LinLSQRIteration is running", _state);
    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nmv = state->repnmv;
    rep->terminationtype = state->repterminationtype;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinCGOptimize ()에 제공됩니다.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void linlsqrsetxrep(linlsqrstate* state,
     ae_bool needxrep,
     ae_state *_state)
{
    (void)_state;

    state->xrep = needxrep;
}


/*************************************************************************
This function restarts LinLSQRIteration

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
/* *************************************************************************
이 함수는 LinLSQRteration을 다시 시작합니다.
  - ALGLIB -
     Copyright 30.11.2011 Bochkanov Sergey
************************************************************************* */
void linlsqrrestart(linlsqrstate* state, ae_state *_state)
{


    ae_vector_set_length(&state->rstate.ia, 1+1, _state);
    ae_vector_set_length(&state->rstate.ra, 0+1, _state);
    state->rstate.stage = -1;
    linlsqr_clearrfields(state, _state);
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
/* ************************************************ *************************
요청 된 파일을 지 웁니다. (우리가 무언가를 지우는 것을 잊지 않았는지 확인하기 위해)
*************************************************** ********************** */
static void linlsqr_clearrfields(linlsqrstate* state, ae_state *_state)
{
    (void)_state;

    state->xupdated = ae_false;
    state->needmv = ae_false;
    state->needmtv = ae_false;
    state->needmv2 = ae_false;
    state->needvmv = ae_false;
    state->needprec = ae_false;
}


ae_bool _linlsqrstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    linlsqrstate *p = (linlsqrstate*)_p;
    ae_touch_ptr((void*)p);
    if( !_normestimatorstate_init(&p->nes, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->rx, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->b, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->ui, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->uip1, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->vi, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->vip1, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->omegai, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->omegaip1, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->d, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->mv, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->mtv, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->tmpd, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->tmpx, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _linlsqrstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    linlsqrstate *dst = (linlsqrstate*)_dst;
    linlsqrstate *src = (linlsqrstate*)_src;
    if( !_normestimatorstate_init_copy(&dst->nes, &src->nes, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->rx, &src->rx, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->b, &src->b, _state, make_automatic) )
        return ae_false;
    dst->n = src->n;
    dst->m = src->m;
    dst->prectype = src->prectype;
    if( !ae_vector_init_copy(&dst->ui, &src->ui, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->uip1, &src->uip1, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->vi, &src->vi, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->vip1, &src->vip1, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->omegai, &src->omegai, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->omegaip1, &src->omegaip1, _state, make_automatic) )
        return ae_false;
    dst->alphai = src->alphai;
    dst->alphaip1 = src->alphaip1;
    dst->betai = src->betai;
    dst->betaip1 = src->betaip1;
    dst->phibari = src->phibari;
    dst->phibarip1 = src->phibarip1;
    dst->phii = src->phii;
    dst->rhobari = src->rhobari;
    dst->rhobarip1 = src->rhobarip1;
    dst->rhoi = src->rhoi;
    dst->ci = src->ci;
    dst->si = src->si;
    dst->theta = src->theta;
    dst->lambdai = src->lambdai;
    if( !ae_vector_init_copy(&dst->d, &src->d, _state, make_automatic) )
        return ae_false;
    dst->anorm = src->anorm;
    dst->bnorm2 = src->bnorm2;
    dst->dnorm = src->dnorm;
    dst->r2 = src->r2;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->mv, &src->mv, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->mtv, &src->mtv, _state, make_automatic) )
        return ae_false;
    dst->epsa = src->epsa;
    dst->epsb = src->epsb;
    dst->epsc = src->epsc;
    dst->maxits = src->maxits;
    dst->xrep = src->xrep;
    dst->xupdated = src->xupdated;
    dst->needmv = src->needmv;
    dst->needmtv = src->needmtv;
    dst->needmv2 = src->needmv2;
    dst->needvmv = src->needvmv;
    dst->needprec = src->needprec;
    dst->repiterationscount = src->repiterationscount;
    dst->repnmv = src->repnmv;
    dst->repterminationtype = src->repterminationtype;
    dst->running = src->running;
    if( !ae_vector_init_copy(&dst->tmpd, &src->tmpd, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->tmpx, &src->tmpx, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


void _linlsqrstate_clear(void* _p)
{
    linlsqrstate *p = (linlsqrstate*)_p;
    ae_touch_ptr((void*)p);
    _normestimatorstate_clear(&p->nes);
    ae_vector_clear(&p->rx);
    ae_vector_clear(&p->b);
    ae_vector_clear(&p->ui);
    ae_vector_clear(&p->uip1);
    ae_vector_clear(&p->vi);
    ae_vector_clear(&p->vip1);
    ae_vector_clear(&p->omegai);
    ae_vector_clear(&p->omegaip1);
    ae_vector_clear(&p->d);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->mv);
    ae_vector_clear(&p->mtv);
    ae_vector_clear(&p->tmpd);
    ae_vector_clear(&p->tmpx);
    _rcommstate_clear(&p->rstate);
}


void _linlsqrstate_destroy(void* _p)
{
    linlsqrstate *p = (linlsqrstate*)_p;
    ae_touch_ptr((void*)p);
    _normestimatorstate_destroy(&p->nes);
    ae_vector_destroy(&p->rx);
    ae_vector_destroy(&p->b);
    ae_vector_destroy(&p->ui);
    ae_vector_destroy(&p->uip1);
    ae_vector_destroy(&p->vi);
    ae_vector_destroy(&p->vip1);
    ae_vector_destroy(&p->omegai);
    ae_vector_destroy(&p->omegaip1);
    ae_vector_destroy(&p->d);
    ae_vector_destroy(&p->x);
    ae_vector_destroy(&p->mv);
    ae_vector_destroy(&p->mtv);
    ae_vector_destroy(&p->tmpd);
    ae_vector_destroy(&p->tmpx);
    _rcommstate_destroy(&p->rstate);
}


ae_bool _linlsqrreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    linlsqrreport *p = (linlsqrreport*)_p;
    ae_touch_ptr((void*)p);
    return ae_true;
}


ae_bool _linlsqrreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    linlsqrreport *dst = (linlsqrreport*)_dst;
    linlsqrreport *src = (linlsqrreport*)_src;
    dst->iterationscount = src->iterationscount;
    dst->nmv = src->nmv;
    dst->terminationtype = src->terminationtype;
    return ae_true;
}


void _linlsqrreport_clear(void* _p)
{
    linlsqrreport *p = (linlsqrreport*)_p;
    ae_touch_ptr((void*)p);
}


void _linlsqrreport_destroy(void* _p)
{
    linlsqrreport *p = (linlsqrreport*)_p;
    ae_touch_ptr((void*)p);
}




/*************************************************************************
This function initializes linear CG Solver. This solver is used  to  solve
symmetric positive definite problems. If you want  to  solve  nonsymmetric
(or non-positive definite) problem you may use LinLSQR solver provided  by
ALGLIB.

USAGE:
1. User initializes algorithm state with LinCGCreate() call
2. User tunes solver parameters with  LinCGSetCond() and other functions
3. Optionally, user sets starting point with LinCGSetStartingPoint()
4. User  calls LinCGSolveSparse() function which takes algorithm state and
   SparseMatrix object.
5. User calls LinCGResults() to get solution
6. Optionally, user may call LinCGSolveSparse()  again  to  solve  another
   problem  with different matrix and/or right part without reinitializing
   LinCGState structure.
  
INPUT PARAMETERS:
    N       -   problem dimension, N>0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선형 CG 해법을 초기화합니다. 이 솔버는
대칭 긍정적 인 명확한 문제. 비대칭 성을 풀고 싶다면
(또는 non-positive definite) 문제로 LinLSQR solver를 사용할 수 있습니다.
ALGLIB.
용법:
1. 사용자는 LinCGCreate () 호출로 알고리즘 상태를 초기화한다.
2. 사용자가 LinCGSetCond () 및 기타 함수로 솔버 매개 변수를 조정합니다.
3. 선택적으로 사용자가 LinCGSetStartingPoint ()로 시작점을 설정합니다.
4. 사용자는 알고리즘 상태를 취하는 LinCGSolveSparse () 함수를 호출하고
   SparseMatrix 객체입니다.
5. 사용자가 LinCGResults ()를 호출하여 솔루션을 얻습니다.
6. 선택적으로, 사용자는 LinCGSolveSparse ()를 다시 호출하여 다른 것을 해결할 수 있습니다
   재 초기화하지 않고 다른 행렬 및 / 또는 오른쪽 부분의 문제
   LinCGState 구조체.
  
입력 매개 변수 :
    N - 문제 차원, N> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgcreate(ae_int_t n, lincgstate* state, ae_state *_state)
{
    ae_int_t i;

    _lincgstate_clear(state);

    ae_assert(n>0, "LinCGCreate: N<=0", _state);
    state->n = n;
    state->prectype = 0;
    state->itsbeforerestart = n;
    state->itsbeforerupdate = 10;
    state->epsf = lincg_defaultprecision;
    state->maxits = 0;
    state->xrep = ae_false;
    state->running = ae_false;
    
    /*
     * * allocate arrays
     * * set RX to NAN (just for the case user calls Results() without 
     *   calling SolveSparse()
     * * set starting point to zero
     * * we do NOT initialize B here because we assume that user should
     *   initializate it using LinCGSetB() function. In case he forgets
     *   to do so, exception will be thrown in the LinCGIteration().
     */
    /*
     * * 배열 할당
     * * RX를 NAN으로 설정합니다 (사례 사용자가 Results ()를 호출하지 않고) 
     * SolveSparse ()를 호출합니다.
     * * 시작점을 0으로 설정
     * * B를 초기화하지 않는 이유는 사용자가
     * LinCGSetB () 함수를 사용하여 초기화하십시오. 그가 잊어 버린 경우에 대비해서
     * 이렇게하려면 LinCGIteration ()에서 예외가 throw됩니다.
     */

    ae_vector_set_length(&state->rx, state->n, _state);
    ae_vector_set_length(&state->startx, state->n, _state);
    ae_vector_set_length(&state->b, state->n, _state);
    for(i=0; i<=state->n-1; i++)
    {
        state->rx.ptr.p_double[i] = _state->v_nan;
        state->startx.ptr.p_double[i] = 0.0;
        state->b.ptr.p_double[i] = 0;
    }
    ae_vector_set_length(&state->cx, state->n, _state);
    ae_vector_set_length(&state->p, state->n, _state);
    ae_vector_set_length(&state->r, state->n, _state);
    ae_vector_set_length(&state->cr, state->n, _state);
    ae_vector_set_length(&state->z, state->n, _state);
    ae_vector_set_length(&state->cz, state->n, _state);
    ae_vector_set_length(&state->x, state->n, _state);
    ae_vector_set_length(&state->mv, state->n, _state);
    ae_vector_set_length(&state->pv, state->n, _state);
    lincg_updateitersdata(state, _state);
    ae_vector_set_length(&state->rstate.ia, 0+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
}


/*************************************************************************
This function sets starting point.
By default, zero starting point is used.

INPUT PARAMETERS:
    X       -   starting point, array[N]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은 시작점을 설정합니다.
기본적으로 0의 시작점이 사용됩니다.
입력 매개 변수 :
    X - 시작점, 배열 [N]
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */

void lincgsetstartingpoint(lincgstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetStartingPoint: you can not change starting point because LinCGIteration() function is running", _state);
    ae_assert(state->n<=x->cnt, "LinCGSetStartingPoint: Length(X)<N", _state);
    ae_assert(isfinitevector(x, state->n, _state), "LinCGSetStartingPoint: X contains infinite or NaN values!", _state);
    ae_v_move(&state->startx.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
}


/*************************************************************************
This function sets right part. By default, right part is zero.

INPUT PARAMETERS:
    B       -   right part, array[N].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은 오른쪽 부분을 설정합니다. 기본적으로 오른쪽 부분은 0입니다.
입력 매개 변수 :
    B - 오른쪽 부분, 배열 [N].
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */

void lincgsetb(lincgstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetB: you can not set B, because function LinCGIteration is running!", _state);
    ae_assert(b->cnt>=state->n, "LinCGSetB: Length(B)<N", _state);
    ae_assert(isfinitevector(b, state->n, _state), "LinCGSetB: B contains infinite or NaN values!", _state);
    ae_v_move(&state->b.ptr.p_double[0], 1, &b->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
}


/*************************************************************************
This  function  changes  preconditioning  settings  of  LinCGSolveSparse()
function. By default, SolveSparse() uses diagonal preconditioner,  but  if
you want to use solver without preconditioning, you can call this function
which forces solver to use unit matrix for preconditioning.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinCGSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. 기본적으로 SolveSparse ()는 대각선 전치 조건자를 사용하지만 if
당신은 preconditioning없이 solver를 사용하기를 원한다.이 함수를 호출 할 수있다.
이는 솔버가 전처리를 위해 단위 행렬을 사용하게합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */

void lincgsetprecunit(lincgstate* state, ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetPrecUnit: you can not change preconditioner, because function LinCGIteration is running!", _state);
    state->prectype = -1;
}


/*************************************************************************
This  function  changes  preconditioning  settings  of  LinCGSolveSparse()
function.  LinCGSolveSparse() will use diagonal of the  system  matrix  as
preconditioner. This preconditioning mode is active by default.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 19.11.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 LinCGSolveSparse ()의 사전 조건 설정을 변경합니다.
기능. LinCGSolveSparse ()는 시스템 행렬의 대각선을 다음과 같이 사용합니다.
프리 컨디셔너. 이 사전 조절 모드는 기본적으로 활성화되어 있습니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 19.11.2012 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetprecdiag(lincgstate* state, ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetPrecDiag: you can not change preconditioner, because function LinCGIteration is running!", _state);
    state->prectype = 0;
}


/*************************************************************************
This function sets stopping criteria.

INPUT PARAMETERS:
    EpsF    -   algorithm will be stopped if norm of residual is less than 
                EpsF*||b||.
    MaxIts  -   algorithm will be stopped if number of iterations is  more 
                than MaxIts.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
If  both  EpsF  and  MaxIts  are  zero then small EpsF will be set to small 
value.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 중지 기준을 설정합니다.
입력 매개 변수 :
    EpsF - 잔여 기준이 미만인 경우 알고리즘이 중지됩니다. 
                EpsF * || b ||.
    MaxIts - 반복 횟수가 더 많으면 알고리즘이 중지됩니다. 
                MaxIts보다.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
EpsF와 MaxIts가 모두 0이면 작은 EpsF가 작게 설정됩니다 
값.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetcond(lincgstate* state,
     double epsf,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetCond: you can not change stopping criteria when LinCGIteration() is running", _state);
    ae_assert(ae_isfinite(epsf, _state)&&ae_fp_greater_eq(epsf,0), "LinCGSetCond: EpsF is negative or contains infinite or NaN values", _state);
    ae_assert(maxits>=0, "LinCGSetCond: MaxIts is negative", _state);
    if( ae_fp_eq(epsf,0)&&maxits==0 )
    {
        state->epsf = lincg_defaultprecision;
        state->maxits = maxits;
    }
    else
    {
        state->epsf = epsf;
        state->maxits = maxits;
    }
}


/*************************************************************************
Reverse communication version of linear CG.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
선형 CG의 역방향 통신 버전.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
ae_bool lincgiteration(lincgstate* state, ae_state *_state)
{
    ae_int_t i;
    double uvar;
    double bnorm;
    double v;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    /*
     * 역방향 커뮤니케이션 준비
     * 나는 못 생겼다는 것을 알고 있지만, 같은 방식으로 작동한다.
     * C ++에서 Python까지 모든 곳.
     *
     *이 코드는 지역 주민을 다음과 같이 초기화합니다.
     * * 코드에서 결정된 임의의 값
     * 생성 - 첫 번째 서브 루틴 호출
     * * 이전 통화의 값 - 이후 통화시
     */
    if( state->rstate.stage>=0 )
    {
        i = state->rstate.ia.ptr.p_int[0];
        uvar = state->rstate.ra.ptr.p_double[0];
        bnorm = state->rstate.ra.ptr.p_double[1];
        v = state->rstate.ra.ptr.p_double[2];
    }
    else
    {
        i = -983;
        uvar = -989;
        bnorm = -834;
        v = 900;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    if( state->rstate.stage==4 )
    {
        goto lbl_4;
    }
    if( state->rstate.stage==5 )
    {
        goto lbl_5;
    }
    if( state->rstate.stage==6 )
    {
        goto lbl_6;
    }
    if( state->rstate.stage==7 )
    {
        goto lbl_7;
    }
    
    /*
     * Routine body
     */
    /*
     * 일상적인 신체
     */ 
    ae_assert(state->b.cnt>0, "LinCGIteration: B is not initialized (you must initialize B by LinCGSetB() call", _state);
    state->running = ae_true;
    state->repnmv = 0;
    lincg_clearrfields(state, _state);
    lincg_updateitersdata(state, _state);
    
    /*
     * Start 0-th iteration
     */
    /*
     * 시작 0 번째 반복
     */
    ae_v_move(&state->rx.ptr.p_double[0], 1, &state->startx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    lincg_clearrfields(state, _state);
    state->needvmv = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needvmv = ae_false;
    bnorm = 0;
    state->r2 = 0;
    state->meritfunction = 0;
    for(i=0; i<=state->n-1; i++)
    {
        state->r.ptr.p_double[i] = state->b.ptr.p_double[i]-state->mv.ptr.p_double[i];
        state->r2 = state->r2+state->r.ptr.p_double[i]*state->r.ptr.p_double[i];
        state->meritfunction = state->meritfunction+state->mv.ptr.p_double[i]*state->rx.ptr.p_double[i]-2*state->b.ptr.p_double[i]*state->rx.ptr.p_double[i];
        bnorm = bnorm+state->b.ptr.p_double[i]*state->b.ptr.p_double[i];
    }
    bnorm = ae_sqrt(bnorm, _state);
    
    /*
     * Output first report
     */
    /*
     * 첫 번째 보고서 출력
     */
    if( !state->xrep )
    {
        goto lbl_8;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    lincg_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->xupdated = ae_false;
lbl_8:
    
    /*
     * Is x0 a solution?
     */
    /*
     * x0는 해결책입니까?
     */
    if( !ae_isfinite(state->r2, _state)||ae_fp_less_eq(ae_sqrt(state->r2, _state),state->epsf*bnorm) )
    {
        state->running = ae_false;
        if( ae_isfinite(state->r2, _state) )
        {
            state->repterminationtype = 1;
        }
        else
        {
            state->repterminationtype = -4;
        }
        result = ae_false;
        return result;
    }
    
    /*
     * Calculate Z and P
     */
    /*
     * Z와 P를 계산합니다.
     */ 
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->r.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    lincg_clearrfields(state, _state);
    state->needprec = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->needprec = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->z.ptr.p_double[i] = state->pv.ptr.p_double[i];
        state->p.ptr.p_double[i] = state->z.ptr.p_double[i];
    }
    
    /*
     * Other iterations(1..N)
     */
    /*
     * 기타 반복 (1..N)
     */
    state->repiterationscount = 0;
lbl_10:
    if( ae_false )
    {
        goto lbl_11;
    }
    state->repiterationscount = state->repiterationscount+1;
    
    /*
     * Calculate Alpha
     */
    /*
     * 알파 계산
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->p.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    lincg_clearrfields(state, _state);
    state->needvmv = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->needvmv = ae_false;
    if( !ae_isfinite(state->vmv, _state)||ae_fp_less_eq(state->vmv,0) )
    {
        
        /*
         * a) Overflow when calculating VMV
         * b) non-positive VMV (non-SPD matrix)
         */
        /*
         * a) VMV 계산시 오버플로
         * b) 비 양성 VMV (비 SPD 매트릭스)
         */
        state->running = ae_false;
        if( ae_isfinite(state->vmv, _state) )
        {
            state->repterminationtype = -5;
        }
        else
        {
            state->repterminationtype = -4;
        }
        result = ae_false;
        return result;
    }
    state->alpha = 0;
    for(i=0; i<=state->n-1; i++)
    {
        state->alpha = state->alpha+state->r.ptr.p_double[i]*state->z.ptr.p_double[i];
    }
    state->alpha = state->alpha/state->vmv;
    if( !ae_isfinite(state->alpha, _state) )
    {
        
        /*
         * Overflow when calculating Alpha
         */
        /*
         알파 계산시 오버플로
         */
        state->running = ae_false;
        state->repterminationtype = -4;
        result = ae_false;
        return result;
    }
    
    /*
     * Next step toward solution
     */
    /*
     * 솔루션을 향한 다음 단계
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->cx.ptr.p_double[i] = state->rx.ptr.p_double[i]+state->alpha*state->p.ptr.p_double[i];
    }
    
    /*
     * Calculate R:
     * * use recurrent relation to update R
     * * at every ItsBeforeRUpdate-th iteration recalculate it from scratch, using matrix-vector product
     *   in case R grows instead of decreasing, algorithm is terminated with positive completion code
     */
    /*
     * R 계산 :
     * * 반복적 관계를 사용하여 R 업데이트
     * * 모든 ItBeforeRUpdate-it 반복은 행렬 - 벡터 제품을 사용하여 처음부터 다시 계산합니다.
     * R이 감소하는 대신 증가하는 경우 알고리즘은 긍정적 인 완료 코드로 종료됩니다.
     */
    if( !(state->itsbeforerupdate==0||state->repiterationscount%state->itsbeforerupdate!=0) )
    {
        goto lbl_12;
    }
    
    /*
     * Calculate R using recurrent formula
     */
    /*
     * 반복적 인 공식을 사용하여 R 계산
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->cr.ptr.p_double[i] = state->r.ptr.p_double[i]-state->alpha*state->mv.ptr.p_double[i];
        state->x.ptr.p_double[i] = state->cr.ptr.p_double[i];
    }
    goto lbl_13;
lbl_12:
    
    /*
     * Calculate R using matrix-vector multiplication
     */
    /*
     * 행렬 - 벡터 곱셈을 사용하여 R 계산
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->cx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    lincg_clearrfields(state, _state);
    state->needmv = ae_true;
    state->rstate.stage = 4;
    goto lbl_rcomm;
lbl_4:
    state->needmv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->cr.ptr.p_double[i] = state->b.ptr.p_double[i]-state->mv.ptr.p_double[i];
        state->x.ptr.p_double[i] = state->cr.ptr.p_double[i];
    }
    
    /*
     * Calculating merit function
     * Check emergency stopping criterion
     */
    /*
     * 장점 계산 기능
     * 비상 정지 기준 확인
     */
    v = 0;
    for(i=0; i<=state->n-1; i++)
    {
        v = v+state->mv.ptr.p_double[i]*state->cx.ptr.p_double[i]-2*state->b.ptr.p_double[i]*state->cx.ptr.p_double[i];
    }
    if( ae_fp_less(v,state->meritfunction) )
    {
        goto lbl_14;
    }
    for(i=0; i<=state->n-1; i++)
    {
        if( !ae_isfinite(state->rx.ptr.p_double[i], _state) )
        {
            state->running = ae_false;
            state->repterminationtype = -4;
            result = ae_false;
            return result;
        }
    }
    
    /*
     *output last report
     */
    /*
     * 마지막 보고서 출력
     */
    if( !state->xrep )
    {
        goto lbl_16;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    lincg_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 5;
    goto lbl_rcomm;
lbl_5:
    state->xupdated = ae_false;
lbl_16:
    state->running = ae_false;
    state->repterminationtype = 7;
    result = ae_false;
    return result;
lbl_14:
    state->meritfunction = v;
lbl_13:
    ae_v_move(&state->rx.ptr.p_double[0], 1, &state->cx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    
    /*
     * calculating RNorm
     *
     * NOTE: monotonic decrease of R2 is not guaranteed by algorithm.
     */
    /*
     * RNorm 계산
     *
     * 참고 : R2의 단조 감소는 알고리즘에 의해 보장되지 않습니다.
     */
    state->r2 = 0;
    for(i=0; i<=state->n-1; i++)
    {
        state->r2 = state->r2+state->cr.ptr.p_double[i]*state->cr.ptr.p_double[i];
    }
    
    /*
     *output report
     */
    /*
     * 출력 보고서
     */
    if( !state->xrep )
    {
        goto lbl_18;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    lincg_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 6;
    goto lbl_rcomm;
lbl_6:
    state->xupdated = ae_false;
lbl_18:
    
    /*
     *stopping criterion
     *achieved the required precision
     */
    /*
     * 정지 기준
     * 요구되는 정밀도 달성
     */
    if( !ae_isfinite(state->r2, _state)||ae_fp_less_eq(ae_sqrt(state->r2, _state),state->epsf*bnorm) )
    {
        state->running = ae_false;
        if( ae_isfinite(state->r2, _state) )
        {
            state->repterminationtype = 1;
        }
        else
        {
            state->repterminationtype = -4;
        }
        result = ae_false;
        return result;
    }
    if( state->repiterationscount>=state->maxits&&state->maxits>0 )
    {
        for(i=0; i<=state->n-1; i++)
        {
            if( !ae_isfinite(state->rx.ptr.p_double[i], _state) )
            {
                state->running = ae_false;
                state->repterminationtype = -4;
                result = ae_false;
                return result;
            }
        }
        
        /*
         *if X is finite number
         */
        /*
         * X가 유한 수인 경우
         */
        state->running = ae_false;
        state->repterminationtype = 5;
        result = ae_false;
        return result;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->cr.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    
    /*
     *prepere of parameters for next iteration
     */
    /*
     * 다음 반복을위한 매개 변수의 prepere
     */
    state->repnmv = state->repnmv+1;
    lincg_clearrfields(state, _state);
    state->needprec = ae_true;
    state->rstate.stage = 7;
    goto lbl_rcomm;
lbl_7:
    state->needprec = ae_false;
    ae_v_move(&state->cz.ptr.p_double[0], 1, &state->pv.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    if( state->repiterationscount%state->itsbeforerestart!=0 )
    {
        state->beta = 0;
        uvar = 0;
        for(i=0; i<=state->n-1; i++)
        {
            state->beta = state->beta+state->cz.ptr.p_double[i]*state->cr.ptr.p_double[i];
            uvar = uvar+state->z.ptr.p_double[i]*state->r.ptr.p_double[i];
        }
        
        /*
         *check that UVar is't INF or is't zero
         */
        /*
         * UVar가 INF인지 아니면 0인지 확인하십시오.
         */
        if( !ae_isfinite(uvar, _state)||ae_fp_eq(uvar,0) )
        {
            state->running = ae_false;
            state->repterminationtype = -4;
            result = ae_false;
            return result;
        }
        
        /*
         * 베타 계산
         */
        state->beta = state->beta/uvar;
        
        /*
         * .BETA가 INF인지 NaN인지 확인하십시오.
         */
        if( !ae_isfinite(state->beta, _state) )
        {
            state->running = ae_false;
            state->repterminationtype = -1;
            result = ae_false;
            return result;
        }
        for(i=0; i<=state->n-1; i++)
        {
            state->p.ptr.p_double[i] = state->cz.ptr.p_double[i]+state->beta*state->p.ptr.p_double[i];
        }
    }
    else
    {
        ae_v_move(&state->p.ptr.p_double[0], 1, &state->cz.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    }
    
    /*
     *prepere data for next iteration
     */
    /*
     * 다음 반복을위한 prepere 데이터
     */
    for(i=0; i<=state->n-1; i++)
    {
        
        /*
         *write (k+1)th iteration to (k )th iteration
         */
        state->r.ptr.p_double[i] = state->cr.ptr.p_double[i];
        state->z.ptr.p_double[i] = state->cz.ptr.p_double[i];
    }
    goto lbl_10;
lbl_11:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = i;
    state->rstate.ra.ptr.p_double[0] = uvar;
    state->rstate.ra.ptr.p_double[1] = bnorm;
    state->rstate.ra.ptr.p_double[2] = v;
    return result;
}


/*************************************************************************
Procedure for solution of A*x=b with sparse A.

INPUT PARAMETERS:
    State   -   algorithm state
    A       -   sparse matrix in the CRS format (you MUST contvert  it  to 
                CRS format by calling SparseConvertToCRS() function).
    IsUpper -   whether upper or lower triangle of A is used:
                * IsUpper=True  => only upper triangle is used and lower
                                   triangle is not referenced at all 
                * IsUpper=False => only lower triangle is used and upper
                                   triangle is not referenced at all
    B       -   right part, array[N]

RESULT:
    This function returns no result.
    You can get solution by calling LinCGResults()
    
NOTE: this function uses lightweight preconditioning -  multiplication  by
      inverse of diag(A). If you want, you can turn preconditioning off by
      calling LinCGSetPrecUnit(). However, preconditioning cost is low and
      preconditioner  is  very  important  for  solution  of  badly scaled
      problems.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* *************************************************************************
스파 스 A가있는 A * x = b의 해를 구하는 절차.
입력 매개 변수 :
    상태 - 알고리즘 상태
    A - CRS 형식의 희소 행렬 (이를 
                SparseConvertToCRS () 함수를 호출하여 CRS 형식).
    IsUpper - A의 위 또는 아래 삼각형 사용 여부 :
                * IsUpper = True => 위 삼각형 만 사용되고 더 낮습니다
                                   삼각형이 전혀 참조되지 않는다. 
                * IsUpper = False => 아래쪽 삼각형 만 사용되고 위쪽
                                   삼각형이 전혀 참조되지 않는다.
    B - 오른쪽 파트, 배열 [N]
결과:
    이 함수는 결과를 반환하지 않습니다.
    LinCGResults ()를 호출하여 솔루션을 얻을 수 있습니다.
    
참고 :이 함수는 가벼운 전제 조건을 사용합니다.
      diag (A)의 역. 원하는 경우 사전 조건을 해제 할 수 있습니다.
      LinCGSetPrecUnit () 호출. 그러나 사전 컨디셔닝 비용이 낮고
      선 컨디셔너는 잘못 조정 된 솔루션에 매우 중요합니다.
      문제.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
************************************************************************* */
void lincgsolvesparse(lincgstate* state,
     sparsematrix* a,
     ae_bool isupper,
     /* Real    */ ae_vector* b,
     ae_state *_state)
{
    ae_int_t n;
    ae_int_t i;
    double v;
    double vmv;


    n = state->n;
    ae_assert(b->cnt>=state->n, "LinCGSetB: Length(B)<N", _state);
    ae_assert(isfinitevector(b, state->n, _state), "LinCGSetB: B contains infinite or NaN values!", _state);
    
    /*
     * Allocate temporaries
     */
    /*
     * 임시 직원 할당
     */
    rvectorsetlengthatleast(&state->tmpd, n, _state);
    
    /*
     * Compute diagonal scaling matrix D
     */
    /*
     * 대각선 스케일링 행렬 D 계산
     */
    if( state->prectype==0 )
    {
        
        /*
         * Default preconditioner - inverse of matrix diagonal
         */
        /*
         * 기본 선행 조건 - 대각선 행렬의 역함수
         */
        for(i=0; i<=n-1; i++)
        {
            v = sparsegetdiagonal(a, i, _state);
            if( ae_fp_greater(v,0) )
            {
                state->tmpd.ptr.p_double[i] = 1/ae_sqrt(v, _state);
            }
            else
            {
                state->tmpd.ptr.p_double[i] = 1;
            }
        }
    }
    else
    {
        
        /*
         * No diagonal scaling
         */
        /*
         * 대각선 크기 조정 없음
         */
        for(i=0; i<=n-1; i++)
        {
            state->tmpd.ptr.p_double[i] = 1;
        }
    }
    
    /*
     * Solve
     */
    lincgrestart(state, _state);
    lincgsetb(state, b, _state);
    while(lincgiteration(state, _state))
    {
        
        /*
         * Process different requests from optimizer
         */
        /*
         * 옵티마이 저가 다른 요청을 처리합니다.
         */
        if( state->needmv )
        {
            sparsesmv(a, isupper, &state->x, &state->mv, _state);
        }
        if( state->needvmv )
        {
            sparsesmv(a, isupper, &state->x, &state->mv, _state);
            vmv = ae_v_dotproduct(&state->x.ptr.p_double[0], 1, &state->mv.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
            state->vmv = vmv;
        }
        if( state->needprec )
        {
            for(i=0; i<=n-1; i++)
            {
                state->pv.ptr.p_double[i] = state->x.ptr.p_double[i]*ae_sqr(state->tmpd.ptr.p_double[i], _state);
            }
        }
    }
}


/*************************************************************************
CG-solver: results.

This function must be called after LinCGSolve

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[N], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -5    input matrix is either not positive definite,
                            too large or too small                            
                    * -4    overflow/underflow during solution
                            (ill conditioned problem)
                    *  1    ||residual||<=EpsF*||b||
                    *  5    MaxIts steps was taken
                    *  7    rounding errors prevent further progress,
                            best point found is returned
                * Rep.IterationsCount contains iterations count
                * NMV countains number of matrix-vector calculations

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
CG-solver : 결과.
이 함수는 LinCGSolve 후에 호출해야합니다.
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X - 배열 [N], 솔루션
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -5 입력 행렬은 양의 확률이 아니거나,
                            너무 크거나 너무 작음                            
                    * -4 솔루션 오버 플로우 / 언더 플로우
                            (아픈 컨디션 문제)
                    * 1 || 잔여 || <= EpsF * || b ||
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 반올림 오류로 인해 더 이상 진행되지 않습니다.
                            찾은 최고의 포인트가 반환됩니다.
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                NMV는 매트릭스 - 벡터 계산의 수를 카운트합니다.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgresults(lincgstate* state,
     /* Real    */ ae_vector* x,
     lincgreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _lincgreport_clear(rep);

    ae_assert(!state->running, "LinCGResult: you can not get result, because function LinCGIteration has been launched!", _state);
    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nmv = state->repnmv;
    rep->terminationtype = state->repterminationtype;
    rep->r2 = state->r2;
}


/*************************************************************************
This function sets restart frequency. By default, algorithm  is  restarted
after N subsequent iterations.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은 재시작 빈도를 설정합니다. 기본적으로 알고리즘은 다시 시작됩니다.
후속 반복 N 회.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetrestartfreq(lincgstate* state,
     ae_int_t srf,
     ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetRestartFreq: you can not change restart frequency when LinCGIteration() is running", _state);
    ae_assert(srf>0, "LinCGSetRestartFreq: non-positive SRF", _state);
    state->itsbeforerestart = srf;
}


/*************************************************************************
This function sets frequency of residual recalculations.

Algorithm updates residual r_k using iterative formula,  but  recalculates
it from scratch after each 10 iterations. It is done to avoid accumulation
of numerical errors and to stop algorithm when r_k starts to grow.

Such low update frequence (1/10) gives very  little  overhead,  but  makes
algorithm a bit more robust against numerical errors. However, you may
change it 

INPUT PARAMETERS:
    Freq    -   desired update frequency, Freq>=0.
                Zero value means that no updates will be done.

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 잔여 재 계산의 빈도를 설정합니다.
알고리즘은 반복 수식을 사용하여 잔여 r_k를 업데이트하지만 다시 계산합니다.
그것은 각 10 반복 후 처음부터. 누적을 피하기 위해 행해진 다.
r_k가 증가하기 시작할 때 알고리즘을 중지 할 수 있습니다.
낮은 업데이트 빈도 (1/10)는 오버 헤드가 거의 없지만
알고리즘은 수치 오류에 대해 조금 더 견고합니다. 그러나
그것을 바꿔라. 
입력 매개 변수 :
    Freq - 원하는 업데이트 빈도, Freq> = 0.
                0 값은 업데이트가 수행되지 않음을 의미합니다.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetrupdatefreq(lincgstate* state,
     ae_int_t freq,
     ae_state *_state)
{


    ae_assert(!state->running, "LinCGSetRUpdateFreq: you can not change update frequency when LinCGIteration() is running", _state);
    ae_assert(freq>=0, "LinCGSetRUpdateFreq: non-positive Freq", _state);
    state->itsbeforerupdate = freq;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinCGOptimize ()에 제공됩니다.
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgsetxrep(lincgstate* state, ae_bool needxrep, ae_state *_state)
{
    (void)_state;

    state->xrep = needxrep;
}


/*************************************************************************
Procedure for restart function LinCGIteration

  -- ALGLIB --
     Copyright 14.11.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
재시작 기능을위한 절차 LinCGIteration
  - ALGLIB -
     저작권 14.11.2011 Bochkanov Sergey
*************************************************** ********************** */
void lincgrestart(lincgstate* state, ae_state *_state)
{


    ae_vector_set_length(&state->rstate.ia, 0+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
    lincg_clearrfields(state, _state);
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
/* ************************************************ *************************
요청 된 파일을 지 웁니다. (우리가 무언가를 지우는 것을 잊지 않았는지 확인하기 위해)
*************************************************** ********************** */
static void lincg_clearrfields(lincgstate* state, ae_state *_state)
{
    (void)_state;

    state->xupdated = ae_false;
    state->needmv = ae_false;
    state->needmtv = ae_false;
    state->needmv2 = ae_false;
    state->needvmv = ae_false;
    state->needprec = ae_false;
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
/* ************************************************ *************************
요청 된 파일을 지 웁니다. (우리가 무언가를 지우는 것을 잊지 않았는지 확인하기 위해)
*************************************************** ********************** */
static void lincg_updateitersdata(lincgstate* state, ae_state *_state)
{
    (void)_state;

    state->repiterationscount = 0;
    state->repnmv = 0;
    state->repterminationtype = 0;
}


ae_bool _lincgstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    lincgstate *p = (lincgstate*)_p;
    ae_touch_ptr((void*)p);
    if( !ae_vector_init(&p->rx, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->b, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->cx, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->cr, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->cz, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->p, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->r, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->z, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->mv, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->pv, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->startx, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->tmpd, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _lincgstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    lincgstate *dst = (lincgstate*)_dst;
    lincgstate *src = (lincgstate*)_src;
    if( !ae_vector_init_copy(&dst->rx, &src->rx, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->b, &src->b, _state, make_automatic) )
        return ae_false;
    dst->n = src->n;
    dst->prectype = src->prectype;
    if( !ae_vector_init_copy(&dst->cx, &src->cx, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->cr, &src->cr, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->cz, &src->cz, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->p, &src->p, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->r, &src->r, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->z, &src->z, _state, make_automatic) )
        return ae_false;
    dst->alpha = src->alpha;
    dst->beta = src->beta;
    dst->r2 = src->r2;
    dst->meritfunction = src->meritfunction;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->mv, &src->mv, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->pv, &src->pv, _state, make_automatic) )
        return ae_false;
    dst->vmv = src->vmv;
    if( !ae_vector_init_copy(&dst->startx, &src->startx, _state, make_automatic) )
        return ae_false;
    dst->epsf = src->epsf;
    dst->maxits = src->maxits;
    dst->itsbeforerestart = src->itsbeforerestart;
    dst->itsbeforerupdate = src->itsbeforerupdate;
    dst->xrep = src->xrep;
    dst->xupdated = src->xupdated;
    dst->needmv = src->needmv;
    dst->needmtv = src->needmtv;
    dst->needmv2 = src->needmv2;
    dst->needvmv = src->needvmv;
    dst->needprec = src->needprec;
    dst->repiterationscount = src->repiterationscount;
    dst->repnmv = src->repnmv;
    dst->repterminationtype = src->repterminationtype;
    dst->running = src->running;
    if( !ae_vector_init_copy(&dst->tmpd, &src->tmpd, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


void _lincgstate_clear(void* _p)
{
    lincgstate *p = (lincgstate*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_clear(&p->rx);
    ae_vector_clear(&p->b);
    ae_vector_clear(&p->cx);
    ae_vector_clear(&p->cr);
    ae_vector_clear(&p->cz);
    ae_vector_clear(&p->p);
    ae_vector_clear(&p->r);
    ae_vector_clear(&p->z);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->mv);
    ae_vector_clear(&p->pv);
    ae_vector_clear(&p->startx);
    ae_vector_clear(&p->tmpd);
    _rcommstate_clear(&p->rstate);
}


void _lincgstate_destroy(void* _p)
{
    lincgstate *p = (lincgstate*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_destroy(&p->rx);
    ae_vector_destroy(&p->b);
    ae_vector_destroy(&p->cx);
    ae_vector_destroy(&p->cr);
    ae_vector_destroy(&p->cz);
    ae_vector_destroy(&p->p);
    ae_vector_destroy(&p->r);
    ae_vector_destroy(&p->z);
    ae_vector_destroy(&p->x);
    ae_vector_destroy(&p->mv);
    ae_vector_destroy(&p->pv);
    ae_vector_destroy(&p->startx);
    ae_vector_destroy(&p->tmpd);
    _rcommstate_destroy(&p->rstate);
}


ae_bool _lincgreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    lincgreport *p = (lincgreport*)_p;
    ae_touch_ptr((void*)p);
    return ae_true;
}


ae_bool _lincgreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    lincgreport *dst = (lincgreport*)_dst;
    lincgreport *src = (lincgreport*)_src;
    dst->iterationscount = src->iterationscount;
    dst->nmv = src->nmv;
    dst->terminationtype = src->terminationtype;
    dst->r2 = src->r2;
    return ae_true;
}


void _lincgreport_clear(void* _p)
{
    lincgreport *p = (lincgreport*)_p;
    ae_touch_ptr((void*)p);
}


void _lincgreport_destroy(void* _p)
{
    lincgreport *p = (lincgreport*)_p;
    ae_touch_ptr((void*)p);
}




/*************************************************************************
                LEVENBERG-MARQUARDT-LIKE NONLINEAR SOLVER

DESCRIPTION:
This algorithm solves system of nonlinear equations
    F[0](x[0], ..., x[n-1])   = 0
    F[1](x[0], ..., x[n-1])   = 0
    ...
    F[M-1](x[0], ..., x[n-1]) = 0
with M/N do not necessarily coincide.  Algorithm  converges  quadratically
under following conditions:
    * the solution set XS is nonempty
    * for some xs in XS there exist such neighbourhood N(xs) that:
      * vector function F(x) and its Jacobian J(x) are continuously
        differentiable on N
      * ||F(x)|| provides local error bound on N, i.e. there  exists  such
        c1, that ||F(x)||>c1*distance(x,XS)
Note that these conditions are much more weaker than usual non-singularity
conditions. For example, algorithm will converge for any  affine  function
F (whether its Jacobian singular or not).


REQUIREMENTS:
Algorithm will request following information during its operation:
* function vector F[] and Jacobian matrix at given point X
* value of merit function f(x)=F[0]^2(x)+...+F[M-1]^2(x) at given point X


USAGE:
1. User initializes algorithm state with NLEQCreateLM() call
2. User tunes solver parameters with  NLEQSetCond(),  NLEQSetStpMax()  and
   other functions
3. User  calls  NLEQSolve()  function  which  takes  algorithm  state  and
   pointers (delegates, etc.) to callback functions which calculate  merit
   function value and Jacobian.
4. User calls NLEQResults() to get solution
5. Optionally, user may call NLEQRestartFrom() to  solve  another  problem
   with same parameters (N/M) but another starting  point  and/or  another
   function vector. NLEQRestartFrom() allows to reuse already  initialized
   structure.


INPUT PARAMETERS:
    N       -   space dimension, N>1:
                * if provided, only leading N elements of X are used
                * if not provided, determined automatically from size of X
    M       -   system size
    X       -   starting point


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTES:
1. you may tune stopping conditions with NLEQSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use NLEQSetStpMax() function to bound algorithm's steps.
3. this  algorithm  is  a  slightly  modified implementation of the method
   described  in  'Levenberg-Marquardt  method  for constrained  nonlinear
   equations with strong local convergence properties' by Christian Kanzow
   Nobuo Yamashita and Masao Fukushima and further  developed  in  'On the
   convergence of a New Levenberg-Marquardt Method'  by  Jin-yan  Fan  and
   Ya-Xiang Yuan.


  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
                LEVENBERG-MARQUARD-LIKE 비선형 솔버
기술:
이 알고리즘은 비선형 방정식의 시스템을 해결합니다.
    F [0] (x [0], ..., x [n-1]) = 0
    F [1] (x [0], ..., x [n-1]) = 0
    ...
    F [M-1] (x [0], ..., x [n-1]) = 0
M / N과 반드시 ​​일치하지는 않습니다. 알고리즘은 2 차적으로 수렴한다.
다음 조건 하에서 :
    * 솔루션 세트 XS가 비어 있지 않습니다.
    * XS의 일부 xs에는 다음과 같은 이웃 N (xs)이 있습니다.
      * 벡터 함수 F (x)와 그 Jacobian J (x)는 연속적이다.
        N에서 구별 할 수있는
      * || F (x) || N에 국한된 에러를 제공한다.
        c1, that || F (x) ||> c1 * 거리 (x, XS)
이러한 조건은 일반적인 비 특이성보다 훨씬 약합니다.
정황. 예를 들어 알고리즘은 임의의 아핀 함수에 대해 수렴 할 것입니다
F (야 코비 행렬이 단수인지 아닌지).
요구 사항 :
알고리즘은 작동 중에 다음 정보를 요청합니다.
* 함수 벡터 F []와 주어진 점 X에서의 자 코비안 행렬
* 주어진 포인트 X에서 메리트 함수 f (x) = F [0] ^ 2 (x) + ... + F [M-1] ^ 2 (x)
용법:
1. 사용자는 NLEQCreateLM () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 NLEQSetCond (), NLEQSetStpMax () 및 NLEQSetStpMax ()를 사용하여 솔버 매개 변수를 조정합니다.
   다른 기능들
3. 사용자는 알고리즘 상태를 취하는 NLEQSolve () 함수를 호출하고
   메리트를 계산하는 콜백 함수에 대한 포인터 (델리게이트 등)
   함수 값과 Jacobian.
4. 사용자가 NLEQResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 사용자가 NLEQRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 매개 변수 (N / M)이지만 다른 시작점 및 / 또는 다른 점
   함수 벡터. NLEQRestartFrom ()은 이미 초기화 된 재사용을 허용합니다.
   구조.
입력 매개 변수 :
    N 공간 차원, N> 1 :
                * 제공되는 경우 X의 N 번째 요소 만 사용됩니다.
                * 제공되지 않을 경우 X의 크기에 따라 자동으로 결정됩니다.
    M - 시스템 크기
    X - 출발점
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. NLEQSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   NLEQSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩합니다.
3.이 알고리즘은 메소드의 약간 수정 된 구현입니다.
   '제한된 비선형을위한 Levenberg-Marquardt 방법
   강력한 지역 수렴 속성을 가진 방정식 'by Christian Kanzow
   야마시타 노부오와 후쿠시마 마사오는 "
   Jin-yan Fan의 New Levenberg-Marquardt Method의 수렴과
   Ya-Xiang Yuan.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqcreatelm(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     nleqstate* state,
     ae_state *_state)
{

    _nleqstate_clear(state);

    ae_assert(n>=1, "NLEQCreateLM: N<1!", _state);
    ae_assert(m>=1, "NLEQCreateLM: M<1!", _state);
    ae_assert(x->cnt>=n, "NLEQCreateLM: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "NLEQCreateLM: X contains infinite or NaN values!", _state);
    
    /*
     * Initialize
     */
    state->n = n;
    state->m = m;
    nleqsetcond(state, 0, 0, _state);
    nleqsetxrep(state, ae_false, _state);
    nleqsetstpmax(state, 0, _state);
    ae_vector_set_length(&state->x, n, _state);
    ae_vector_set_length(&state->xbase, n, _state);
    ae_matrix_set_length(&state->j, m, n, _state);
    ae_vector_set_length(&state->fi, m, _state);
    ae_vector_set_length(&state->rightpart, n, _state);
    ae_vector_set_length(&state->candstep, n, _state);
    nleqrestartfrom(state, x, _state);
}


/*************************************************************************
This function sets stopping conditions for the nonlinear solver

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsF    -   >=0
                The subroutine finishes  its work if on k+1-th iteration
                the condition ||F||<=EpsF is satisfied
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsF=0 and MaxIts=0 simultaneously will lead to  automatic
stopping criterion selection (small EpsF).

NOTES:

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 비선형 해석을위한 정지 조건을 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsF -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                조건 || F || <= EpsF가 만족된다
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다.
EpsF = 0 및 MaxIts = 0을 동시에 전달하면 자동
중지 기준 선택 (작은 EpsF).
노트:
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqsetcond(nleqstate* state,
     double epsf,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(ae_isfinite(epsf, _state), "NLEQSetCond: EpsF is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsf,0), "NLEQSetCond: negative EpsF!", _state);
    ae_assert(maxits>=0, "NLEQSetCond: negative MaxIts!", _state);
    if( ae_fp_eq(epsf,0)&&maxits==0 )
    {
        epsf = 1.0E-6;
    }
    state->epsf = epsf;
    state->maxits = maxits;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to NLEQSolve().

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
NLEQSolve ()에 제공됨.
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqsetxrep(nleqstate* state, ae_bool needxrep, ae_state *_state)
{
    (void)_state;

    state->xrep = needxrep;
}


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when target function  contains  exp()  or  other  fast
growing functions, and algorithm makes  too  large  steps  which  lead  to
overflow. This function allows us to reject steps that are too large  (and
therefore expose us to the possible overflow) without actually calculating
function value at the x+stp*d.

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 최대 스텝 길이를 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    StpMax - 최대 스텝 길이,> = 0. StpMax를 0.0으로 설정하십시오.
                스텝 길이를 제한하고 싶다.
대상 함수가 exp () 또는 다른 고속 함수를 포함 할 때이 서브 루틴을 사용하십시오.
성장하는 함수 및 알고리즘은 너무 큰 단계를 만들어
과다. 이 함수를 사용하면 너무 큰 단계를 거부 할 수 있습니다 (
따라서 실제로 오버 플로우가 발생할 수 있음)
x + stp * d에서의 함수 값.
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqsetstpmax(nleqstate* state, double stpmax, ae_state *_state)
{


    ae_assert(ae_isfinite(stpmax, _state), "NLEQSetStpMax: StpMax is not finite!", _state);
    ae_assert(ae_fp_greater_eq(stpmax,0), "NLEQSetStpMax: StpMax<0!", _state);
    state->stpmax = stpmax;
}


/*************************************************************************

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
ae_bool nleqiteration(nleqstate* state, ae_state *_state)
{
    ae_int_t n;
    ae_int_t m;
    ae_int_t i;
    double lambdaup;
    double lambdadown;
    double lambdav;
    double rho;
    double mu;
    double stepnorm;
    ae_bool b;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    /*
     * 역방향 커뮤니케이션 준비
     * 나는 못 생겼다는 것을 알고 있지만, 같은 방식으로 작동한다.
     * C ++에서 Python까지 모든 곳.
     *
     *이 코드는 지역 주민을 다음과 같이 초기화합니다.
     * * 코드에서 결정된 임의의 값
     * 생성 - 첫 번째 서브 루틴 호출
     * * 이전 통화의 값 - 이후 통화시
     */
    if( state->rstate.stage>=0 )
    {
        n = state->rstate.ia.ptr.p_int[0];
        m = state->rstate.ia.ptr.p_int[1];
        i = state->rstate.ia.ptr.p_int[2];
        b = state->rstate.ba.ptr.p_bool[0];
        lambdaup = state->rstate.ra.ptr.p_double[0];
        lambdadown = state->rstate.ra.ptr.p_double[1];
        lambdav = state->rstate.ra.ptr.p_double[2];
        rho = state->rstate.ra.ptr.p_double[3];
        mu = state->rstate.ra.ptr.p_double[4];
        stepnorm = state->rstate.ra.ptr.p_double[5];
    }
    else
    {
        n = -983;
        m = -989;
        i = -834;
        b = ae_false;
        lambdaup = -287;
        lambdadown = 364;
        lambdav = 214;
        rho = -338;
        mu = -686;
        stepnorm = 912;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    if( state->rstate.stage==4 )
    {
        goto lbl_4;
    }
    
    /*
     * Routine body
     */
    /*
     * 일상적인 신체
     */
    
    /*
     * Prepare
     */
    /*
     * 준비
     */
    n = state->n;
    m = state->m;
    state->repterminationtype = 0;
    state->repiterationscount = 0;
    state->repnfunc = 0;
    state->repnjac = 0;
    
    /*
     * Calculate F/G, initialize algorithm
     */
    /*
     * F / G 계산, 알고리즘 초기화
     */
    nleq_clearrequestfields(state, _state);
    state->needf = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needf = ae_false;
    state->repnfunc = state->repnfunc+1;
    ae_v_move(&state->xbase.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->fbase = state->f;
    state->fprev = ae_maxrealnumber;
    if( !state->xrep )
    {
        goto lbl_5;
    }
    
    /*
     * progress report
     */
    /*
     * 주요주기
     */
    nleq_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->xupdated = ae_false;
lbl_5:
    if( ae_fp_less_eq(state->f,ae_sqr(state->epsf, _state)) )
    {
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    
    /*
     * Main cycle
     */
    /*
     * 내부주기 : 좋은 람다 찾기
     */
    lambdaup = 10;
    lambdadown = 0.3;
    lambdav = 0.001;
    rho = 1;
lbl_7:
    if( ae_false )
    {
        goto lbl_8;
    }
    
    /*
     * Get Jacobian;
     * before we get to this point we already have State.XBase filled
     * with current point and State.FBase filled with function value
     * at XBase
     */
    /*
     * Solve (J ^ T * J + (Lambda + Mu) * I) * y = J ^ T * F
     * 단계 d = -y를 얻는 곳 :
     * * Mu = || F || - 비선형 시스템의 댐핑 파라미터입니다.
     * * Lambda - 추가 Levenberg-Marquardt 매개 변수입니다.
     * 멀리 떨어져있을 때 더 나은 수렴을 위해
     */
    nleq_clearrequestfields(state, _state);
    state->needfij = ae_true;
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->needfij = ae_false;
    state->repnfunc = state->repnfunc+1;
    state->repnjac = state->repnjac+1;
    rmatrixmv(n, m, &state->j, 0, 0, 1, &state->fi, 0, &state->rightpart, 0, _state);
    ae_v_muld(&state->rightpart.ptr.p_double[0], 1, ae_v_len(0,n-1), -1);
    
    /*
     * Inner cycle: find good lambda
     */
    /*
     * 표준화 단계 (StpMax 이하 여야 함)
     */
lbl_9:
    if( ae_false )
    {
        goto lbl_10;
    }
    
    /*
     * Solve (J^T*J + (Lambda+Mu)*I)*y = J^T*F
     * to get step d=-y where:
     * * Mu=||F|| - is damping parameter for nonlinear system
     * * Lambda   - is additional Levenberg-Marquardt parameter
     *              for better convergence when far away from minimum
     */
    /*
     * Solve (J ^ T * J + (Lambda + Mu) * I) * y = J ^ T * F
     * 단계 d = -y를 얻는 곳 :
     * * Mu = || F || - 비선형 시스템의 댐핑 파라미터입니다.
     * * Lambda - 추가 Levenberg-Marquardt 매개 변수입니다.
     * 멀리 떨어져있을 때 더 나은 수렴을 위해
     */
    for(i=0; i<=n-1; i++)
    {
        state->candstep.ptr.p_double[i] = 0;
    }
    fblssolvecgx(&state->j, m, n, lambdav, &state->rightpart, &state->candstep, &state->cgbuf, _state);
    
    /*
     * Normalize step (it must be no more than StpMax)
     */

    /*
     * 표준화 단계 (StpMax 이하 여야 함)
     */
    stepnorm = 0;
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_neq(state->candstep.ptr.p_double[i],0) )
        {
            stepnorm = 1;
            break;
        }
    }
    linminnormalized(&state->candstep, &stepnorm, n, _state);
    if( ae_fp_neq(state->stpmax,0) )
    {
        stepnorm = ae_minreal(stepnorm, state->stpmax, _state);
    }
    
    /*
     * Test new step - is it good enough?
     * * if not, Lambda is increased and we try again.
     * * if step is good, we decrease Lambda and move on.
     *
     * We can break this cycle on two occasions:
     * * step is so small that x+step==x (in floating point arithmetics)
     * * lambda is so large
     */
    /*
     * 새로운 단계 테스트 - 충분합니까?
     * * 그렇지 않으면 람다가 증가하고 다시 시도합니다.
     * * 단계가 좋으면 람다를 줄이고 계속 나아 간다.
     *
     * 우리는 두 가지 경우에이주기를 깰 수 있습니다 :
     * * 단계가 너무 작아 x + step == x (부동 소수점 연산에서)
     * * 람다는 너무 큽니다.
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_addd(&state->x.ptr.p_double[0], 1, &state->candstep.ptr.p_double[0], 1, ae_v_len(0,n-1), stepnorm);
    b = ae_true;
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_neq(state->x.ptr.p_double[i],state->xbase.ptr.p_double[i]) )
        {
            b = ae_false;
            break;
        }
    }
    if( b )
    {
        
        /*
         * Step is too small, force zero step and break
         */
        /*
         * 스텝이 너무 작아 강제로 제로 스텝을하고 휴식을 취하십시오.
         */
        stepnorm = 0;
        ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
        state->f = state->fbase;
        goto lbl_10;
    }
    nleq_clearrequestfields(state, _state);
    state->needf = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->needf = ae_false;
    state->repnfunc = state->repnfunc+1;
    if( ae_fp_less(state->f,state->fbase) )
    {
        
        /*
         * function value decreased, move on
         */
        /*
         * 함수 값이 감소하고 계속 이동합니다.
         */
        nleq_decreaselambda(&lambdav, &rho, lambdadown, _state);
        goto lbl_10;
    }
    if( !nleq_increaselambda(&lambdav, &rho, lambdaup, _state) )
    {
        
        /*
         * Lambda is too large (near overflow), force zero step and break
         */
        /*
         * 람다가 너무 커서 (오버플로 근처에서) 강제로 0 단계로 이동하고 중단합니다.
         */
        stepnorm = 0;
        ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
        state->f = state->fbase;
        goto lbl_10;
    }
    goto lbl_9;
lbl_10:
    
    /*
     * Accept step:
     * * new position
     * * new function value
     */
    
    /*
     * 수락 단계 :
     * * 새 직책
     * * 새로운 함수 값
     */
    state->fbase = state->f;
    ae_v_addd(&state->xbase.ptr.p_double[0], 1, &state->candstep.ptr.p_double[0], 1, ae_v_len(0,n-1), stepnorm);
    state->repiterationscount = state->repiterationscount+1;
    
    /*
     * Report new iteration
     */
    /*
     * 새로운 반복 보고서
     */
    if( !state->xrep )
    {
        goto lbl_11;
    }
    nleq_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->f = state->fbase;
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->rstate.stage = 4;
    goto lbl_rcomm;
lbl_4:
    state->xupdated = ae_false;
lbl_11:
    
    /*
     * Test stopping conditions on F, step (zero/non-zero) and MaxIts;
     * If one of the conditions is met, RepTerminationType is changed.
     */
    /*
     * F, 스텝 (영 / 비 - 제로) 및 MaxIts에 대한 시험 정지 조건;
     * 조건 중 하나가 충족되면 RepTerminationType이 변경됩니다.
     */
    if( ae_fp_less_eq(ae_sqrt(state->f, _state),state->epsf) )
    {
        state->repterminationtype = 1;
    }
    if( ae_fp_eq(stepnorm,0)&&state->repterminationtype==0 )
    {
        state->repterminationtype = -4;
    }
    if( state->repiterationscount>=state->maxits&&state->maxits>0 )
    {
        state->repterminationtype = 5;
    }
    if( state->repterminationtype!=0 )
    {
        goto lbl_8;
    }
    
    /*
     * Now, iteration is finally over
     */
    /*
     * 이제 반복은 끝났습니다.
     */
    goto lbl_7;
lbl_8:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
    /*
     * 저장 상태
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = n;
    state->rstate.ia.ptr.p_int[1] = m;
    state->rstate.ia.ptr.p_int[2] = i;
    state->rstate.ba.ptr.p_bool[0] = b;
    state->rstate.ra.ptr.p_double[0] = lambdaup;
    state->rstate.ra.ptr.p_double[1] = lambdadown;
    state->rstate.ra.ptr.p_double[2] = lambdav;
    state->rstate.ra.ptr.p_double[3] = rho;
    state->rstate.ra.ptr.p_double[4] = mu;
    state->rstate.ra.ptr.p_double[5] = stepnorm;
    return result;
}


/*************************************************************************
NLEQ solver results

INPUT PARAMETERS:
    State   -   algorithm state.

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -4    ERROR:  algorithm   has   converged   to   the
                            stationary point Xf which is local minimum  of
                            f=F[0]^2+...+F[m-1]^2, but is not solution  of
                            nonlinear system.
                    *  1    sqrt(f)<=EpsF.
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations
                * ActiveConstraints contains number of active constraints

  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
NLEQ 해결사 결과
입력 매개 변수 :
    상태 - 알고리즘 상태.
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -4 오류 : 알고리즘이
                            국소 최소치 인 정지 점 Xf
                            f = F [0] ^ 2 + ... + F [m-1] ^ 2이지만,
                            비선형 시스템.
                    * 1 sqrt (f) <= EpsF.
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 정지 조건은 너무 엄격합니다.
                            더 이상의 개선은 불가능하다.
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                * NFEV countains 함수 계산 횟수
                * ActiveConstraints에는 활성 제약 조건 수가 포함됩니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqresults(nleqstate* state,
     /* Real    */ ae_vector* x,
     nleqreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _nleqreport_clear(rep);

    nleqresultsbuf(state, x, rep, _state);
}


/*************************************************************************
NLEQ solver results

Buffered implementation of NLEQResults(), which uses pre-allocated  buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
NLEQ 해결사 결과
미리 할당 된 버퍼를 사용하는 NLEQResults ()의 버퍼 된 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.08.2009
*************************************************** ********************** */
void nleqresultsbuf(nleqstate* state,
     /* Real    */ ae_vector* x,
     nleqreport* rep,
     ae_state *_state)
{


    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nfunc = state->repnfunc;
    rep->njac = state->repnjac;
    rep->terminationtype = state->repterminationtype;
}


/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used for reverse communication previously
                allocated with MinCGCreate call.
    X       -   new starting point.
    BndL    -   new lower bounds
    BndU    -   new upper bounds

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 새로운 지점에서 CG 알고리즘을 재시작합니다. 모든 최적화
매개 변수는 변경되지 않습니다.
이 함수는 여러 개의 최적화 문제를 해결할 수 있습니다.
오브젝트 재 할당 패널티가없는 동일한 수의 치수가 있어야합니다.
입력 매개 변수 :
    상태 - 이전에 역방향 통신에 사용 된 구조
                MinCGCreate 호출로 할당됩니다.
    X - 새로운 출발점.
    BndL - 새로운 하한
    BndU - 새로운 상한
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
*************************************************** ********************** */
void nleqrestartfrom(nleqstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{


    ae_assert(x->cnt>=state->n, "NLEQRestartFrom: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, state->n, _state), "NLEQRestartFrom: X contains infinite or NaN values!", _state);
    ae_v_move(&state->x.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_vector_set_length(&state->rstate.ia, 2+1, _state);
    ae_vector_set_length(&state->rstate.ba, 0+1, _state);
    ae_vector_set_length(&state->rstate.ra, 5+1, _state);
    state->rstate.stage = -1;
    nleq_clearrequestfields(state, _state);
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
/* ************************************************ ************************
요청 된 파일을 지 웁니다. (우리가 무언가를 지우는 것을 잊지 않았는지 확인하기 위해)
*************************************************** ********************** */
static void nleq_clearrequestfields(nleqstate* state, ae_state *_state)
{
    (void)_state;

    state->needf = ae_false;
    state->needfij = ae_false;
    state->xupdated = ae_false;
}


/*************************************************************************
Increases lambda, returns False when there is a danger of overflow
*************************************************************************/
/* ************************************************ *************************
오버플로의 위험이있을 때 람다를 증가시키고 False를 반환합니다.
*************************************************** ********************** */
static ae_bool nleq_increaselambda(double* lambdav,
     double* nu,
     double lambdaup,
     ae_state *_state)
{
    double lnlambda;
    double lnnu;
    double lnlambdaup;
    double lnmax;
    ae_bool result;


    result = ae_false;
    lnlambda = ae_log(*lambdav, _state);
    lnlambdaup = ae_log(lambdaup, _state);
    lnnu = ae_log(*nu, _state);
    lnmax = 0.5*ae_log(ae_maxrealnumber, _state);
    if( ae_fp_greater(lnlambda+lnlambdaup+lnnu,lnmax) )
    {
        return result;
    }
    if( ae_fp_greater(lnnu+ae_log(2, _state),lnmax) )
    {
        return result;
    }
    *lambdav = *lambdav*lambdaup*(*nu);
    *nu = *nu*2;
    result = ae_true;
    return result;
}


/*************************************************************************
Decreases lambda, but leaves it unchanged when there is danger of underflow.
*************************************************************************/
/* ************************************************ *************************
람다를 줄이지 만 언더 플로우의 위험이있을 때 변경하지 않습니다.
*************************************************** ********************** */
static void nleq_decreaselambda(double* lambdav,
     double* nu,
     double lambdadown,
     ae_state *_state)
{


    *nu = 1;
    if( ae_fp_less(ae_log(*lambdav, _state)+ae_log(lambdadown, _state),ae_log(ae_minrealnumber, _state)) )
    {
        *lambdav = ae_minrealnumber;
    }
    else
    {
        *lambdav = *lambdav*lambdadown;
    }
}


ae_bool _nleqstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    nleqstate *p = (nleqstate*)_p;
    ae_touch_ptr((void*)p);
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fi, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->j, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->xbase, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->candstep, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->rightpart, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->cgbuf, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _nleqstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    nleqstate *dst = (nleqstate*)_dst;
    nleqstate *src = (nleqstate*)_src;
    dst->n = src->n;
    dst->m = src->m;
    dst->epsf = src->epsf;
    dst->maxits = src->maxits;
    dst->xrep = src->xrep;
    dst->stpmax = src->stpmax;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    dst->f = src->f;
    if( !ae_vector_init_copy(&dst->fi, &src->fi, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init_copy(&dst->j, &src->j, _state, make_automatic) )
        return ae_false;
    dst->needf = src->needf;
    dst->needfij = src->needfij;
    dst->xupdated = src->xupdated;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    dst->repiterationscount = src->repiterationscount;
    dst->repnfunc = src->repnfunc;
    dst->repnjac = src->repnjac;
    dst->repterminationtype = src->repterminationtype;
    if( !ae_vector_init_copy(&dst->xbase, &src->xbase, _state, make_automatic) )
        return ae_false;
    dst->fbase = src->fbase;
    dst->fprev = src->fprev;
    if( !ae_vector_init_copy(&dst->candstep, &src->candstep, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->rightpart, &src->rightpart, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->cgbuf, &src->cgbuf, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


void _nleqstate_clear(void* _p)
{
    nleqstate *p = (nleqstate*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->fi);
    ae_matrix_clear(&p->j);
    _rcommstate_clear(&p->rstate);
    ae_vector_clear(&p->xbase);
    ae_vector_clear(&p->candstep);
    ae_vector_clear(&p->rightpart);
    ae_vector_clear(&p->cgbuf);
}


void _nleqstate_destroy(void* _p)
{
    nleqstate *p = (nleqstate*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_destroy(&p->x);
    ae_vector_destroy(&p->fi);
    ae_matrix_destroy(&p->j);
    _rcommstate_destroy(&p->rstate);
    ae_vector_destroy(&p->xbase);
    ae_vector_destroy(&p->candstep);
    ae_vector_destroy(&p->rightpart);
    ae_vector_destroy(&p->cgbuf);
}


ae_bool _nleqreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    nleqreport *p = (nleqreport*)_p;
    ae_touch_ptr((void*)p);
    return ae_true;
}


ae_bool _nleqreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    (void)_state;
    (void)make_automatic;

    nleqreport *dst = (nleqreport*)_dst;
    nleqreport *src = (nleqreport*)_src;
    dst->iterationscount = src->iterationscount;
    dst->nfunc = src->nfunc;
    dst->njac = src->njac;
    dst->terminationtype = src->terminationtype;
    return ae_true;
}


void _nleqreport_clear(void* _p)
{
    nleqreport *p = (nleqreport*)_p;
    ae_touch_ptr((void*)p);
}


void _nleqreport_destroy(void* _p)
{
    nleqreport *p = (nleqreport*)_p;
    ae_touch_ptr((void*)p);
}



}

