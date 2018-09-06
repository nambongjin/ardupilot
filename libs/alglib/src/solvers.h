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
#ifndef _solvers_pkg_h
#define _solvers_pkg_h
#include "ap.h"
#include "alglibinternal.h"
#include "linalg.h"
#include "alglibmisc.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (데이터)이 포함되어 있습니다.
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
typedef struct
{
    double r1;
    double rinf;
} densesolverreport;
typedef struct
{
    double r2;
    ae_matrix cx;
    ae_int_t n;
    ae_int_t k;
} densesolverlsreport;
typedef struct
{
    normestimatorstate nes;
    ae_vector rx;
    ae_vector b;
    ae_int_t n;
    ae_int_t m;
    ae_int_t prectype;
    ae_vector ui;
    ae_vector uip1;
    ae_vector vi;
    ae_vector vip1;
    ae_vector omegai;
    ae_vector omegaip1;
    double alphai;
    double alphaip1;
    double betai;
    double betaip1;
    double phibari;
    double phibarip1;
    double phii;
    double rhobari;
    double rhobarip1;
    double rhoi;
    double ci;
    double si;
    double theta;
    double lambdai;
    ae_vector d;
    double anorm;
    double bnorm2;
    double dnorm;
    double r2;
    ae_vector x;
    ae_vector mv;
    ae_vector mtv;
    double epsa;
    double epsb;
    double epsc;
    ae_int_t maxits;
    ae_bool xrep;
    ae_bool xupdated;
    ae_bool needmv;
    ae_bool needmtv;
    ae_bool needmv2;
    ae_bool needvmv;
    ae_bool needprec;
    ae_int_t repiterationscount;
    ae_int_t repnmv;
    ae_int_t repterminationtype;
    ae_bool running;
    ae_vector tmpd;
    ae_vector tmpx;
    rcommstate rstate;
} linlsqrstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nmv;
    ae_int_t terminationtype;
} linlsqrreport;
typedef struct
{
    ae_vector rx;
    ae_vector b;
    ae_int_t n;
    ae_int_t prectype;
    ae_vector cx;
    ae_vector cr;
    ae_vector cz;
    ae_vector p;
    ae_vector r;
    ae_vector z;
    double alpha;
    double beta;
    double r2;
    double meritfunction;
    ae_vector x;
    ae_vector mv;
    ae_vector pv;
    double vmv;
    ae_vector startx;
    double epsf;
    ae_int_t maxits;
    ae_int_t itsbeforerestart;
    ae_int_t itsbeforerupdate;
    ae_bool xrep;
    ae_bool xupdated;
    ae_bool needmv;
    ae_bool needmtv;
    ae_bool needmv2;
    ae_bool needvmv;
    ae_bool needprec;
    ae_int_t repiterationscount;
    ae_int_t repnmv;
    ae_int_t repterminationtype;
    ae_bool running;
    ae_vector tmpd;
    rcommstate rstate;
} lincgstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nmv;
    ae_int_t terminationtype;
    double r2;
} lincgreport;
typedef struct
{
    ae_int_t n;
    ae_int_t m;
    double epsf;
    ae_int_t maxits;
    ae_bool xrep;
    double stpmax;
    ae_vector x;
    double f;
    ae_vector fi;
    ae_matrix j;
    ae_bool needf;
    ae_bool needfij;
    ae_bool xupdated;
    rcommstate rstate;
    ae_int_t repiterationscount;
    ae_int_t repnfunc;
    ae_int_t repnjac;
    ae_int_t repterminationtype;
    ae_vector xbase;
    double fbase;
    double fprev;
    ae_vector candstep;
    ae_vector rightpart;
    ae_vector cgbuf;
} nleqstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nfunc;
    ae_int_t njac;
    ae_int_t terminationtype;
} nleqreport;

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// 이 섹션은 C ++ 인터페이스를 포함합니다.
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{

/*************************************************************************

*************************************************************************/
class _densesolverreport_owner
{
public:
    _densesolverreport_owner();
    _densesolverreport_owner(const _densesolverreport_owner &rhs);
    _densesolverreport_owner& operator=(const _densesolverreport_owner &rhs);
    virtual ~_densesolverreport_owner();
    alglib_impl::densesolverreport* c_ptr();
    alglib_impl::densesolverreport* c_ptr() const;
protected:
    alglib_impl::densesolverreport *p_struct;
};
class densesolverreport : public _densesolverreport_owner
{
public:
    densesolverreport();
    densesolverreport(const densesolverreport &rhs);
    densesolverreport& operator=(const densesolverreport &rhs);
    virtual ~densesolverreport();
    double &r1;
    double &rinf;

};


/*************************************************************************

*************************************************************************/
class _densesolverlsreport_owner
{
public:
    _densesolverlsreport_owner();
    _densesolverlsreport_owner(const _densesolverlsreport_owner &rhs);
    _densesolverlsreport_owner& operator=(const _densesolverlsreport_owner &rhs);
    virtual ~_densesolverlsreport_owner();
    alglib_impl::densesolverlsreport* c_ptr();
    alglib_impl::densesolverlsreport* c_ptr() const;
protected:
    alglib_impl::densesolverlsreport *p_struct;
};
class densesolverlsreport : public _densesolverlsreport_owner
{
public:
    densesolverlsreport();
    densesolverlsreport(const densesolverlsreport &rhs);
    densesolverlsreport& operator=(const densesolverlsreport &rhs);
    virtual ~densesolverlsreport();
    double &r2;
    real_2d_array cx;
    ae_int_t &n;
    ae_int_t &k;

};

/*************************************************************************
This object stores state of the LinLSQR method.

You should use ALGLIB functions to work with this object.
*************************************************************************/
/* ************************************************ *************************
이 객체는 LinLSQR 메서드의 상태를 저장합니다.
이 객체를 사용하려면 ALGLIB 함수를 사용해야합니다.
*************************************************** ********************** */
class _linlsqrstate_owner
{
public:
    _linlsqrstate_owner();
    _linlsqrstate_owner(const _linlsqrstate_owner &rhs);
    _linlsqrstate_owner& operator=(const _linlsqrstate_owner &rhs);
    virtual ~_linlsqrstate_owner();
    alglib_impl::linlsqrstate* c_ptr();
    alglib_impl::linlsqrstate* c_ptr() const;
protected:
    alglib_impl::linlsqrstate *p_struct;
};
class linlsqrstate : public _linlsqrstate_owner
{
public:
    linlsqrstate();
    linlsqrstate(const linlsqrstate &rhs);
    linlsqrstate& operator=(const linlsqrstate &rhs);
    virtual ~linlsqrstate();

};


/*************************************************************************

*************************************************************************/
class _linlsqrreport_owner
{
public:
    _linlsqrreport_owner();
    _linlsqrreport_owner(const _linlsqrreport_owner &rhs);
    _linlsqrreport_owner& operator=(const _linlsqrreport_owner &rhs);
    virtual ~_linlsqrreport_owner();
    alglib_impl::linlsqrreport* c_ptr();
    alglib_impl::linlsqrreport* c_ptr() const;
protected:
    alglib_impl::linlsqrreport *p_struct;
};
class linlsqrreport : public _linlsqrreport_owner
{
public:
    linlsqrreport();
    linlsqrreport(const linlsqrreport &rhs);
    linlsqrreport& operator=(const linlsqrreport &rhs);
    virtual ~linlsqrreport();
    ae_int_t &iterationscount;
    ae_int_t &nmv;
    ae_int_t &terminationtype;

};

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
class _lincgstate_owner
{
public:
    _lincgstate_owner();
    _lincgstate_owner(const _lincgstate_owner &rhs);
    _lincgstate_owner& operator=(const _lincgstate_owner &rhs);
    virtual ~_lincgstate_owner();
    alglib_impl::lincgstate* c_ptr();
    alglib_impl::lincgstate* c_ptr() const;
protected:
    alglib_impl::lincgstate *p_struct;
};
class lincgstate : public _lincgstate_owner
{
public:
    lincgstate();
    lincgstate(const lincgstate &rhs);
    lincgstate& operator=(const lincgstate &rhs);
    virtual ~lincgstate();

};


/*************************************************************************

*************************************************************************/
class _lincgreport_owner
{
public:
    _lincgreport_owner();
    _lincgreport_owner(const _lincgreport_owner &rhs);
    _lincgreport_owner& operator=(const _lincgreport_owner &rhs);
    virtual ~_lincgreport_owner();
    alglib_impl::lincgreport* c_ptr();
    alglib_impl::lincgreport* c_ptr() const;
protected:
    alglib_impl::lincgreport *p_struct;
};
class lincgreport : public _lincgreport_owner
{
public:
    lincgreport();
    lincgreport(const lincgreport &rhs);
    lincgreport& operator=(const lincgreport &rhs);
    virtual ~lincgreport();
    ae_int_t &iterationscount;
    ae_int_t &nmv;
    ae_int_t &terminationtype;
    double &r2;

};

/*************************************************************************

*************************************************************************/
class _nleqstate_owner
{
public:
    _nleqstate_owner();
    _nleqstate_owner(const _nleqstate_owner &rhs);
    _nleqstate_owner& operator=(const _nleqstate_owner &rhs);
    virtual ~_nleqstate_owner();
    alglib_impl::nleqstate* c_ptr();
    alglib_impl::nleqstate* c_ptr() const;
protected:
    alglib_impl::nleqstate *p_struct;
};
class nleqstate : public _nleqstate_owner
{
public:
    nleqstate();
    nleqstate(const nleqstate &rhs);
    nleqstate& operator=(const nleqstate &rhs);
    virtual ~nleqstate();
    ae_bool &needf;
    ae_bool &needfij;
    ae_bool &xupdated;
    double &f;
    real_1d_array fi;
    real_2d_array j;
    real_1d_array x;

};


/*************************************************************************

*************************************************************************/
class _nleqreport_owner
{
public:
    _nleqreport_owner();
    _nleqreport_owner(const _nleqreport_owner &rhs);
    _nleqreport_owner& operator=(const _nleqreport_owner &rhs);
    virtual ~_nleqreport_owner();
    alglib_impl::nleqreport* c_ptr();
    alglib_impl::nleqreport* c_ptr() const;
protected:
    alglib_impl::nleqreport *p_struct;
};
class nleqreport : public _nleqreport_owner
{
public:
    nleqreport();
    nleqreport(const nleqreport &rhs);
    nleqreport& operator=(const nleqreport &rhs);
    virtual ~nleqreport();
    ae_int_t &iterationscount;
    ae_int_t &nfunc;
    ae_int_t &njac;
    ae_int_t &terminationtype;

};

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
void rmatrixsolve(const real_2d_array &a, const ae_int_t n, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x);


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
void rmatrixsolvem(const real_2d_array &a, const ae_int_t n, const real_2d_array &b, const ae_int_t m, const bool rfs, ae_int_t &info, densesolverreport &rep, real_2d_array &x);


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
void rmatrixlusolve(const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x);


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
void rmatrixlusolvem(const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x);


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
void rmatrixmixedsolve(const real_2d_array &a, const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x);


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
void rmatrixmixedsolvem(const real_2d_array &a, const real_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x);


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
void cmatrixsolvem(const complex_2d_array &a, const ae_int_t n, const complex_2d_array &b, const ae_int_t m, const bool rfs, ae_int_t &info, densesolverreport &rep, complex_2d_array &x);


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
void cmatrixsolve(const complex_2d_array &a, const ae_int_t n, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x);


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
void cmatrixlusolvem(const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x);


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
void cmatrixlusolve(const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x);


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
void cmatrixmixedsolvem(const complex_2d_array &a, const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x);


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
void cmatrixmixedsolve(const complex_2d_array &a, const complex_2d_array &lua, const integer_1d_array &p, const ae_int_t n, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x);


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
void spdmatrixsolvem(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x);


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
void spdmatrixsolve(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x);


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
void spdmatrixcholeskysolvem(const real_2d_array &cha, const ae_int_t n, const bool isupper, const real_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, real_2d_array &x);


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
void spdmatrixcholeskysolve(const real_2d_array &cha, const ae_int_t n, const bool isupper, const real_1d_array &b, ae_int_t &info, densesolverreport &rep, real_1d_array &x);


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
void hpdmatrixsolvem(const complex_2d_array &a, const ae_int_t n, const bool isupper, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x);


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
void hpdmatrixsolve(const complex_2d_array &a, const ae_int_t n, const bool isupper, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x);


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
void hpdmatrixcholeskysolvem(const complex_2d_array &cha, const ae_int_t n, const bool isupper, const complex_2d_array &b, const ae_int_t m, ae_int_t &info, densesolverreport &rep, complex_2d_array &x);


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
void hpdmatrixcholeskysolve(const complex_2d_array &cha, const ae_int_t n, const bool isupper, const complex_1d_array &b, ae_int_t &info, densesolverreport &rep, complex_1d_array &x);


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
void rmatrixsolvels(const real_2d_array &a, const ae_int_t nrows, const ae_int_t ncols, const real_1d_array &b, const double threshold, ae_int_t &info, densesolverlsreport &rep, real_1d_array &x);

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
void linlsqrcreate(const ae_int_t m, const ae_int_t n, linlsqrstate &state);


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
void linlsqrsetprecunit(const linlsqrstate &state);


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
void linlsqrsetprecdiag(const linlsqrstate &state);


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
void linlsqrsetlambdai(const linlsqrstate &state, const double lambdai);


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
void linlsqrsolvesparse(const linlsqrstate &state, const sparsematrix &a, const real_1d_array &b);


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
void linlsqrsetcond(const linlsqrstate &state, const double epsa, const double epsb, const ae_int_t maxits);


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
void linlsqrresults(const linlsqrstate &state, real_1d_array &x, linlsqrreport &rep);


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
void linlsqrsetxrep(const linlsqrstate &state, const bool needxrep);

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
void lincgcreate(const ae_int_t n, lincgstate &state);


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
void lincgsetstartingpoint(const lincgstate &state, const real_1d_array &x);


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
void lincgsetprecunit(const lincgstate &state);


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
void lincgsetprecdiag(const lincgstate &state);


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
void lincgsetcond(const lincgstate &state, const double epsf, const ae_int_t maxits);


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
void lincgsolvesparse(const lincgstate &state, const sparsematrix &a, const bool isupper, const real_1d_array &b);


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
void lincgresults(const lincgstate &state, real_1d_array &x, lincgreport &rep);


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
void lincgsetrestartfreq(const lincgstate &state, const ae_int_t srf);


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
void lincgsetrupdatefreq(const lincgstate &state, const ae_int_t freq);


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
void lincgsetxrep(const lincgstate &state, const bool needxrep);

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
void nleqcreatelm(const ae_int_t n, const ae_int_t m, const real_1d_array &x, nleqstate &state);
void nleqcreatelm(const ae_int_t m, const real_1d_array &x, nleqstate &state);


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
void nleqsetcond(const nleqstate &state, const double epsf, const ae_int_t maxits);


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
void nleqsetxrep(const nleqstate &state, const bool needxrep);


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
void nleqsetstpmax(const nleqstate &state, const double stpmax);


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
bool nleqiteration(const nleqstate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear solver

These functions accept following parameters:
    state   -   algorithm state
    func    -   callback which calculates function (or merit function)
                value func at given point x
    jac     -   callback which calculates function vector fi[]
                and Jacobian jac at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL


  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey

*************************************************************************/
/* ************************************************ *************************
이 함수 계열은 비선형 솔버의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    func - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func
    jac - 함수 벡터 fi []를 계산하는 콜백
                주어진 점 x에서 Jacobian jac
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.03.2009
*************************************************** ********************** */
void nleqsolve(nleqstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);


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
void nleqresults(const nleqstate &state, real_1d_array &x, nleqreport &rep);


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
void nleqresultsbuf(const nleqstate &state, real_1d_array &x, nleqreport &rep);


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
void nleqrestartfrom(const nleqstate &state, const real_1d_array &x);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (기능)이 포함되어 있습니다.
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
void rmatrixsolve(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void rmatrixsolvem(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_bool rfs,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void rmatrixlusolve(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void rmatrixlusolvem(/* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void rmatrixmixedsolve(/* Real    */ ae_matrix* a,
     /* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void rmatrixmixedsolvem(/* Real    */ ae_matrix* a,
     /* Real    */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void cmatrixsolvem(/* Complex */ ae_matrix* a,
     ae_int_t n,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_bool rfs,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
void cmatrixsolve(/* Complex */ ae_matrix* a,
     ae_int_t n,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state);
void cmatrixlusolvem(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
void cmatrixlusolve(/* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state);
void cmatrixmixedsolvem(/* Complex */ ae_matrix* a,
     /* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
void cmatrixmixedsolve(/* Complex */ ae_matrix* a,
     /* Complex */ ae_matrix* lua,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state);
void spdmatrixsolvem(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void spdmatrixsolve(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void spdmatrixcholeskysolvem(/* Real    */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_matrix* x,
     ae_state *_state);
void spdmatrixcholeskysolve(/* Real    */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void hpdmatrixsolvem(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
void hpdmatrixsolve(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state);
void hpdmatrixcholeskysolvem(/* Complex */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_matrix* b,
     ae_int_t m,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_matrix* x,
     ae_state *_state);
void hpdmatrixcholeskysolve(/* Complex */ ae_matrix* cha,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* b,
     ae_int_t* info,
     densesolverreport* rep,
     /* Complex */ ae_vector* x,
     ae_state *_state);
void rmatrixsolvels(/* Real    */ ae_matrix* a,
     ae_int_t nrows,
     ae_int_t ncols,
     /* Real    */ ae_vector* b,
     double threshold,
     ae_int_t* info,
     densesolverlsreport* rep,
     /* Real    */ ae_vector* x,
     ae_state *_state);
ae_bool _densesolverreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _densesolverreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _densesolverreport_clear(void* _p);
void _densesolverreport_destroy(void* _p);
ae_bool _densesolverlsreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _densesolverlsreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _densesolverlsreport_clear(void* _p);
void _densesolverlsreport_destroy(void* _p);
void linlsqrcreate(ae_int_t m,
     ae_int_t n,
     linlsqrstate* state,
     ae_state *_state);
void linlsqrsetb(linlsqrstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void linlsqrsetprecunit(linlsqrstate* state, ae_state *_state);
void linlsqrsetprecdiag(linlsqrstate* state, ae_state *_state);
void linlsqrsetlambdai(linlsqrstate* state,
     double lambdai,
     ae_state *_state);
ae_bool linlsqriteration(linlsqrstate* state, ae_state *_state);
void linlsqrsolvesparse(linlsqrstate* state,
     sparsematrix* a,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void linlsqrsetcond(linlsqrstate* state,
     double epsa,
     double epsb,
     ae_int_t maxits,
     ae_state *_state);
void linlsqrresults(linlsqrstate* state,
     /* Real    */ ae_vector* x,
     linlsqrreport* rep,
     ae_state *_state);
void linlsqrsetxrep(linlsqrstate* state,
     ae_bool needxrep,
     ae_state *_state);
void linlsqrrestart(linlsqrstate* state, ae_state *_state);
ae_bool _linlsqrstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _linlsqrstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _linlsqrstate_clear(void* _p);
void _linlsqrstate_destroy(void* _p);
ae_bool _linlsqrreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _linlsqrreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _linlsqrreport_clear(void* _p);
void _linlsqrreport_destroy(void* _p);
void lincgcreate(ae_int_t n, lincgstate* state, ae_state *_state);
void lincgsetstartingpoint(lincgstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void lincgsetb(lincgstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void lincgsetprecunit(lincgstate* state, ae_state *_state);
void lincgsetprecdiag(lincgstate* state, ae_state *_state);
void lincgsetcond(lincgstate* state,
     double epsf,
     ae_int_t maxits,
     ae_state *_state);
ae_bool lincgiteration(lincgstate* state, ae_state *_state);
void lincgsolvesparse(lincgstate* state,
     sparsematrix* a,
     ae_bool isupper,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void lincgresults(lincgstate* state,
     /* Real    */ ae_vector* x,
     lincgreport* rep,
     ae_state *_state);
void lincgsetrestartfreq(lincgstate* state,
     ae_int_t srf,
     ae_state *_state);
void lincgsetrupdatefreq(lincgstate* state,
     ae_int_t freq,
     ae_state *_state);
void lincgsetxrep(lincgstate* state, ae_bool needxrep, ae_state *_state);
void lincgrestart(lincgstate* state, ae_state *_state);
ae_bool _lincgstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _lincgstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _lincgstate_clear(void* _p);
void _lincgstate_destroy(void* _p);
ae_bool _lincgreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _lincgreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _lincgreport_clear(void* _p);
void _lincgreport_destroy(void* _p);
void nleqcreatelm(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     nleqstate* state,
     ae_state *_state);
void nleqsetcond(nleqstate* state,
     double epsf,
     ae_int_t maxits,
     ae_state *_state);
void nleqsetxrep(nleqstate* state, ae_bool needxrep, ae_state *_state);
void nleqsetstpmax(nleqstate* state, double stpmax, ae_state *_state);
ae_bool nleqiteration(nleqstate* state, ae_state *_state);
void nleqresults(nleqstate* state,
     /* Real    */ ae_vector* x,
     nleqreport* rep,
     ae_state *_state);
void nleqresultsbuf(nleqstate* state,
     /* Real    */ ae_vector* x,
     nleqreport* rep,
     ae_state *_state);
void nleqrestartfrom(nleqstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
ae_bool _nleqstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _nleqstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _nleqstate_clear(void* _p);
void _nleqstate_destroy(void* _p);
ae_bool _nleqreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _nleqreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _nleqreport_clear(void* _p);
void _nleqreport_destroy(void* _p);

}
#endif

