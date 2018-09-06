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
#ifndef _diffequations_pkg_h
#define _diffequations_pkg_h
#include "ap.h"
#include "alglibinternal.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (데이터)이 포함되어 있습니다.
//
// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////


namespace alglib_impl
{
typedef struct
{
    ae_int_t n;
    ae_int_t m;
    double xscale;
    double h;
    double eps;
    ae_bool fraceps;
    ae_vector yc;
    ae_vector escale;
    ae_vector xg;
    ae_int_t solvertype;
    ae_bool needdy;
    double x;
    ae_vector y;
    ae_vector dy;
    ae_matrix ytbl;
    ae_int_t repterminationtype;
    ae_int_t repnfev;
    ae_vector yn;
    ae_vector yns;
    ae_vector rka;
    ae_vector rkc;
    ae_vector rkcs;
    ae_matrix rkb;
    ae_matrix rkk;
    rcommstate rstate;
} odesolverstate;
typedef struct
{
    ae_int_t nfev;
    ae_int_t terminationtype;
} odesolverreport;

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////
//
// 이 섹션은 C ++ 인터페이스를 포함합니다.
//
// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////

namespace alglib
{

/*************************************************************************

*************************************************************************/
class _odesolverstate_owner
{
public:
    _odesolverstate_owner();
    _odesolverstate_owner(const _odesolverstate_owner &rhs);
    _odesolverstate_owner& operator=(const _odesolverstate_owner &rhs);
    virtual ~_odesolverstate_owner();
    alglib_impl::odesolverstate* c_ptr();
    alglib_impl::odesolverstate* c_ptr() const;
protected:
    alglib_impl::odesolverstate *p_struct;
};
class odesolverstate : public _odesolverstate_owner
{
public:
    odesolverstate();
    odesolverstate(const odesolverstate &rhs);
    odesolverstate& operator=(const odesolverstate &rhs);
    virtual ~odesolverstate();
    ae_bool &needdy;
    real_1d_array y;
    real_1d_array dy;
    double &x;

};


/*************************************************************************

*************************************************************************/
class _odesolverreport_owner
{
public:
    _odesolverreport_owner();
    _odesolverreport_owner(const _odesolverreport_owner &rhs);
    _odesolverreport_owner& operator=(const _odesolverreport_owner &rhs);
    virtual ~_odesolverreport_owner();
    alglib_impl::odesolverreport* c_ptr();
    alglib_impl::odesolverreport* c_ptr() const;
protected:
    alglib_impl::odesolverreport *p_struct;
};
class odesolverreport : public _odesolverreport_owner
{
public:
    odesolverreport();
    odesolverreport(const odesolverreport &rhs);
    odesolverreport& operator=(const odesolverreport &rhs);
    virtual ~odesolverreport();
    ae_int_t &nfev;
    ae_int_t &terminationtype;

};

/*************************************************************************
Cash-Karp adaptive ODE solver.

This subroutine solves ODE  Y'=f(Y,x)  with  initial  conditions  Y(xs)=Ys
(here Y may be single variable or vector of N variables).

INPUT PARAMETERS:
    Y       -   initial conditions, array[0..N-1].
                contains values of Y[] at X[0]
    N       -   system size
    X       -   points at which Y should be tabulated, array[0..M-1]
                integrations starts at X[0], ends at X[M-1],  intermediate
                values at X[i] are returned too.
                SHOULD BE ORDERED BY ASCENDING OR BY DESCENDING!!!!
    M       -   number of intermediate points + first point + last point:
                * M>2 means that you need both Y(X[M-1]) and M-2 values at
                  intermediate points
                * M=2 means that you want just to integrate from  X[0]  to
                  X[1] and don't interested in intermediate values.
                * M=1 means that you don't want to integrate :)
                  it is degenerate case, but it will be handled correctly.
                * M<1 means error
    Eps     -   tolerance (absolute/relative error on each  step  will  be
                less than Eps). When passing:
                * Eps>0, it means desired ABSOLUTE error
                * Eps<0, it means desired RELATIVE error.  Relative errors
                  are calculated with respect to maximum values of  Y seen
                  so far. Be careful to use this criterion  when  starting
                  from Y[] that are close to zero.
    H       -   initial  step  lenth,  it  will  be adjusted automatically
                after the first  step.  If  H=0,  step  will  be  selected
                automatically  (usualy  it  will  be  equal  to  0.001  of
                min(x[i]-x[j])).

OUTPUT PARAMETERS
    State   -   structure which stores algorithm state between  subsequent
                calls of OdeSolverIteration. Used for reverse communication.
                This structure should be passed  to the OdeSolverIteration
                subroutine.

SEE ALSO
    AutoGKSmoothW, AutoGKSingular, AutoGKIteration, AutoGKResults.


  -- ALGLIB --
     Copyright 01.09.2009 by Bochkanov Sergey
*************************************************************************/

/**************************************************************************
Cash-Karp 적용된 ODE 해석기.

이 서브 루틴은 초기 조건 Y (xs) = Ys로 ODE Y' = f (Y, x)
(여기서 Y는 단일 변수 또는 N 변수의 벡터 일 수 있음).

입력 매개 변수 :
    Y - 초기 조건, 배열 [0..N-1].
                X [0]에 Y []의 값을 포함한다.
    N - 시스템 크기
    X - Y를 표로 만들어야하는 배열, array [0..M-1]
                적분은 X [0]에서 시작하고 X [M-1]에서 종료, 중간
                X [i]의 값도 반환됩니다.
                오름차순 또는 오름차순으로 주문해야합니다 !!!!
    M - 중간 지점 수 + 첫 번째 점 + 마지막 점 :
                * M> 2는 Y (X [M-1])와 M-2 값이 모두 필요하다는 것을 의미합니다.
                  중간 지점
                * M = 2는 X [0]에서
                  X [1]이고 중간 값에 관심이 없다.
                * M = 1은 통합하고 싶지 않다는 것을 의미합니다. :)
                  퇴보 한 경우지만 올바르게 처리됩니다.
                * M <1은 오류를 의미합니다.
    Eps - tolerance (각 단계의 절대 / 상대 오차)
                미만 Eps). 전달할 때 :
                * Eps> 0, 원하는 ABSOLUTE 오류를 의미합니다.
                * Eps <0, 원하는 RELATIVE 오류를 의미합니다. 상대 오류
                  Y의 최대 값에 대하여 계산된다
                  지금까지. 시작시이 기준을 사용하도록주의하십시오.
                  0에 가까운 Y []로부터.
    H - 첫 번째 단계는 자동으로 조정됩니다.
                첫 번째 단계 후. H = 0이면 단계가 선택됩니다.
                자동으로 (일반적으로 0.001 of
                min (x [i] -x [j]))를 계산한다.
출력 매개 변수
    상태 - 후속 작업 사이에 알고리즘 상태를 저장하는 구조
                OdeSolverIteration의 호출. 역방향 통신에 사용됩니다.
                이 구조체는 OdeSolverIteration에 전달되어야합니다.
                서브 루틴.
관련 항목
    AutoGKSmoothW, AutoGKSingular, AutoGKIteration, AutoGKResults.
  - ALGLIB -
     Bochkanov Sergey의 01.09.2009 저작권
**************************************************************************/

void odesolverrkck(const real_1d_array &y, const ae_int_t n, const real_1d_array &x, const ae_int_t m, const double eps, const double h, odesolverstate &state);
void odesolverrkck(const real_1d_array &y, const real_1d_array &x, const double eps, const double h, odesolverstate &state);


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

bool odesolveriteration(const odesolverstate &state);


/*************************************************************************
This function is used to launcn iterations of ODE solver

It accepts following parameters:
    diff    -   callback which calculates dy/dx for given y and x
    ptr     -   optional pointer which is passed to diff; can be NULL


  -- ALGLIB --
     Copyright 01.09.2009 by Bochkanov Sergey

*************************************************************************/

/* ************************************************ *************************
이 함수는 ODE 해결사의 반복을 시작하는 데 사용됩니다.
다음 매개 변수를 허용합니다.
    diff - 주어진 y와 x에 대해 dy / dx를 계산하는 콜백
    ptr - diff에게 건네지는 옵션의 포인터. NULL 일 수있다.
  - ALGLIB -
     Bochkanov Sergey의 01.09.2009 저작권
*************************************************** ********************** */


void odesolversolve(odesolverstate &state,
    void (*diff)(const real_1d_array &y, double x, real_1d_array &dy, void *ptr),
    void *ptr = NULL);


/*************************************************************************
ODE solver results

Called after OdeSolverIteration returned False.

INPUT PARAMETERS:
    State   -   algorithm state (used by OdeSolverIteration).

OUTPUT PARAMETERS:
    M       -   number of tabulated values, M>=1
    XTbl    -   array[0..M-1], values of X
    YTbl    -   array[0..M-1,0..N-1], values of Y in X[i]
    Rep     -   solver report:
                * Rep.TerminationType completetion code:
                    * -2    X is not ordered  by  ascending/descending  or
                            there are non-distinct X[],  i.e.  X[i]=X[i+1]
                    * -1    incorrect parameters were specified
                    *  1    task has been solved
                * Rep.NFEV contains number of function calculations

  -- ALGLIB --
     Copyright 01.09.2009 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
ODE 해결사 결과
OdeSolverIteration이 False를 반환 한 후에 호출됩니다.
입력 매개 변수 :
    상태 - 알고리즘 상태입니다 (OdeSolverIteration에서 사용).
출력 매개 변수 :
    M - 도표화 된 값의 수, M> = 1
    XTbl - 배열 [0..M-1], X 값
    YTbl- 배열 [0..M-1,0 ... N-1], X [i]의 Y 값,
    담당자 솔버 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -2 X는 오름차순 / 내림차순으로 정렬되지 않습니다.
                            비 구분 X [], 즉 X [i] = X [i + 1]
                    * -1 잘못된 매개 변수가 지정되었습니다.
                    * 1 과제가 해결되었습니다.
                * Rep.NFEV는 함수 계산 횟수를 포함합니다.
  - ALGLIB -
     Bochkanov Sergey의 01.09.2009 저작권
*************************************************** ********************** */

void odesolverresults(const odesolverstate &state, ae_int_t &m, real_1d_array &xtbl, real_2d_array &ytbl, odesolverreport &rep);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (기능)이 포함되어 있습니다.
//
// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////


namespace alglib_impl
{
void odesolverrkck(/* Real    */ ae_vector* y,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     ae_int_t m,
     double eps,
     double h,
     odesolverstate* state,
     ae_state *_state);
ae_bool odesolveriteration(odesolverstate* state, ae_state *_state);
void odesolverresults(odesolverstate* state,
     ae_int_t* m,
     /* Real    */ ae_vector* xtbl,
     /* Real    */ ae_matrix* ytbl,
     odesolverreport* rep,
     ae_state *_state);
ae_bool _odesolverstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _odesolverstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _odesolverstate_clear(void* _p);
void _odesolverstate_destroy(void* _p);
ae_bool _odesolverreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _odesolverreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _odesolverreport_clear(void* _p);
void _odesolverreport_destroy(void* _p);

}
#endif

