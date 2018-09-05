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
#ifndef _integration_pkg_h
#define _integration_pkg_h
#include "ap.h"
#include "alglibinternal.h"
#include "linalg.h"
#include "specialfunctions.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
typedef struct
{
    ae_int_t terminationtype;
    ae_int_t nfev;
    ae_int_t nintervals;
} autogkreport;
typedef struct
{
    double a;
    double b;
    double eps;
    double xwidth;
    double x;
    double f;
    ae_int_t info;
    double r;
    ae_matrix heap;
    ae_int_t heapsize;
    ae_int_t heapwidth;
    ae_int_t heapused;
    double sumerr;
    double sumabs;
    ae_vector qn;
    ae_vector wg;
    ae_vector wk;
    ae_vector wr;
    ae_int_t n;
    rcommstate rstate;
} autogkinternalstate;
typedef struct
{
    double a;
    double b;
    double alpha;
    double beta;
    double xwidth;
    double x;
    double xminusa;
    double bminusx;
    ae_bool needf;
    double f;
    ae_int_t wrappermode;
    autogkinternalstate internalstate;
    rcommstate rstate;
    double v;
    ae_int_t terminationtype;
    ae_int_t nfev;
    ae_int_t nintervals;
} autogkstate;

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{





/*************************************************************************
Integration report:
* TerminationType = completetion code:
    * -5    non-convergence of Gauss-Kronrod nodes
            calculation subroutine.
    * -1    incorrect parameters were specified
    *  1    OK
* Rep.NFEV countains number of function calculations
* Rep.NIntervals contains number of intervals [a,b]
  was partitioned into.
*************************************************************************/
/*************************************************************************
통합 보고서 :
* TerminationType = 완성 코드 :
    * -5 Gauss-Kronrod 노드의 비 수렴
            계산 서브 루틴.
    * -1 잘못된 매개 변수가 지정되었습니다.
    * 1 OK
* Rep.NFEV 함수 계산 횟수 계산
* Rep.NIntervals에는 간격 수 [a, b]가 포함됩니다.
  분할되었습니다.
*************************************************************************/
class _autogkreport_owner
{
public:
    _autogkreport_owner();
    _autogkreport_owner(const _autogkreport_owner &rhs);
    _autogkreport_owner& operator=(const _autogkreport_owner &rhs);
    virtual ~_autogkreport_owner();
    alglib_impl::autogkreport* c_ptr();
    alglib_impl::autogkreport* c_ptr() const;
protected:
    alglib_impl::autogkreport *p_struct;
};
class autogkreport : public _autogkreport_owner
{
public:
    autogkreport();
    autogkreport(const autogkreport &rhs);
    autogkreport& operator=(const autogkreport &rhs);
    virtual ~autogkreport();
    ae_int_t &terminationtype;
    ae_int_t &nfev;
    ae_int_t &nintervals;

};


/*************************************************************************
This structure stores state of the integration algorithm.

Although this class has public fields,  they are not intended for external
use. You should use ALGLIB functions to work with this class:
* autogksmooth()/AutoGKSmoothW()/... to create objects
* autogkintegrate() to begin integration
* autogkresults() to get results
*************************************************************************/
/*************************************************************************
이 구조체는 통합 알고리즘의 상태를 저장합니다.
이 클래스에는 public 필드가 있지만 외부 용 필드는 아닙니다.
용도. 이 클래스로 작업하려면 ALGLIB 함수를 사용해야합니다.
* autogksmooth () / AutoGKSmoothW () / ... 객체를 만드는 방법
통합을 시작하려면 * autogkintegrate ()
* 결과를 얻으려면 autogkresults ()
*************************************************************************/
class _autogkstate_owner
{
public:
    _autogkstate_owner();
    _autogkstate_owner(const _autogkstate_owner &rhs);
    _autogkstate_owner& operator=(const _autogkstate_owner &rhs);
    virtual ~_autogkstate_owner();
    alglib_impl::autogkstate* c_ptr();
    alglib_impl::autogkstate* c_ptr() const;
protected:
    alglib_impl::autogkstate *p_struct;
};
class autogkstate : public _autogkstate_owner
{
public:
    autogkstate();
    autogkstate(const autogkstate &rhs);
    autogkstate& operator=(const autogkstate &rhs);
    virtual ~autogkstate();
    ae_bool &needf;
    double &x;
    double &xminusa;
    double &bminusx;
    double &f;

};

/*************************************************************************
Computation of nodes and weights for a Gauss quadrature formula

The algorithm generates the N-point Gauss quadrature formula  with  weight
function given by coefficients alpha and beta  of  a  recurrence  relation
which generates a system of orthogonal polynomials:

P-1(x)   =  0
P0(x)    =  1
Pn+1(x)  =  (x-alpha(n))*Pn(x)  -  beta(n)*Pn-1(x)

and zeroth moment Mu0

Mu0 = integral(W(x)dx,a,b)

INPUT PARAMETERS:
    Alpha   ?  array[0..N-1], alpha coefficients
    Beta    ?  array[0..N-1], beta coefficients
                Zero-indexed element is not used and may be arbitrary.
                Beta[I]>0.
    Mu0     ?  zeroth moment of the weight function.
    N       ?  number of nodes of the quadrature formula, N>=1

OUTPUT PARAMETERS:
    Info    -   error code:
                * -3    internal eigenproblem solver hasn't converged
                * -2    Beta[i]<=0
                * -1    incorrect N was passed
                *  1    OK
    X       -   array[0..N-1] - array of quadrature nodes,
                in ascending order.
    W       -   array[0..N-1] - array of quadrature weights.

  -- ALGLIB --
     Copyright 2005-2009 by Bochkanov Sergey
*************************************************************************/
/*************************************************************************
가우스 구적법에 대한 노드와 가중치의 계산
이 알고리즘은 가중치가있는 N 포인트 가우스 직교 수식을 생성합니다.
반복 관계의 계수 α 및 β에 의해 ​​주어진 함수
직교 다항식의 시스템을 생성하는 :
P-1 (x) = 0
P0 (x) = 1
Pn + 1 (x) = (x-α (n)) * Pn (x) - β (n) * Pn-
0 차 모멘트 Mu0
Mu0 = 적분 (W (x) dx, a, b)
입력 매개 변수 :
    알파 - 배열 [0..N-1], 알파 계수
    베타 - 배열 [0..N-1], 베타 계수
                0으로 색인 된 요소는 사용되지 않으며 임의적 일 수 있습니다.
                베타 [I]> 0.
    Mu0 - 가중치 함수의 0 차 순간.
    N - 직교 공식의 노드 수, N> = 1
출력 매개 변수 :
    정보 - 오류 코드 :
                * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                * -2 베타 [i] <= 0
                * -1 잘못된 N이 전달되었습니다.
                * 1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2009
*************************************************************************/
void gqgeneraterec(const real_1d_array &alpha, const real_1d_array &beta, const double mu0, const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &w);


/*************************************************************************
Computation of nodes and weights for a Gauss-Lobatto quadrature formula

The algorithm generates the N-point Gauss-Lobatto quadrature formula  with
weight function given by coefficients alpha and beta of a recurrence which
generates a system of orthogonal polynomials.

P-1(x)   =  0
P0(x)    =  1
Pn+1(x)  =  (x-alpha(n))*Pn(x)  -  beta(n)*Pn-1(x)

and zeroth moment Mu0

Mu0 = integral(W(x)dx,a,b)

INPUT PARAMETERS:
    Alpha   ?  array[0..N-2], alpha coefficients
    Beta    ?  array[0..N-2], beta coefficients.
                Zero-indexed element is not used, may be arbitrary.
                Beta[I]>0
    Mu0     ?  zeroth moment of the weighting function.
    A       ?  left boundary of the integration interval.
    B       ?  right boundary of the integration interval.
    N       ?  number of nodes of the quadrature formula, N>=3
                (including the left and right boundary nodes).

OUTPUT PARAMETERS:
    Info    -   error code:
                * -3    internal eigenproblem solver hasn't converged
                * -2    Beta[i]<=0
                * -1    incorrect N was passed
                *  1    OK
    X       -   array[0..N-1] - array of quadrature nodes,
                in ascending order.
    W       -   array[0..N-1] - array of quadrature weights.

  -- ALGLIB --
     Copyright 2005-2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Gauss-Lobatto 직교 수식의 노드 및 가중치 계산
이 알고리즘은 다음과 같이 N 포인트 Gauss-Lobatto 직교 위상 공식을 생성합니다.
반복 함수의 계수 α와 β에 의해 ​​주어진 가중치 함수.
직교 다항식의 시스템을 생성합니다.
P-1 (x) = 0
P0 (x) = 1
Pn + 1 (x) = (x-α (n)) * Pn (x) - β (n) * Pn-
0 차 모멘트 Mu0
Mu0 = 적분 (W (x) dx, a, b)
입력 매개 변수 :
    알파 - 배열 [0..N-2], 알파 계수
    베타 - 배열 [0..N-2], 베타 계수.
                0으로 색인 된 요소는 사용되지 않으며 임의적 일 수 있습니다.
                베타 [I]> 0
    Mu0 - 가중치 함수의 0 차 순간.
    A - 적분 간격의 왼쪽 경계.
    B - 적분 간격의 오른쪽 경계.
    N - 직교 공식의 노드 수, N> = 3
                (왼쪽 및 오른쪽 경계 노드 포함).
출력 매개 변수 :
    정보 - 오류 코드 :
                * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                * -2 베타 [i] <= 0
                * -1 잘못된 N이 전달되었습니다.
                * 1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2009
**************************************************************************/
void gqgenerategausslobattorec(const real_1d_array &alpha, const real_1d_array &beta, const double mu0, const double a, const double b, const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &w);


/*************************************************************************
Computation of nodes and weights for a Gauss-Radau quadrature formula

The algorithm generates the N-point Gauss-Radau  quadrature  formula  with
weight function given by the coefficients alpha and  beta  of a recurrence
which generates a system of orthogonal polynomials.

P-1(x)   =  0
P0(x)    =  1
Pn+1(x)  =  (x-alpha(n))*Pn(x)  -  beta(n)*Pn-1(x)

and zeroth moment Mu0

Mu0 = integral(W(x)dx,a,b)

INPUT PARAMETERS:
    Alpha   ?  array[0..N-2], alpha coefficients.
    Beta    ?  array[0..N-1], beta coefficients
                Zero-indexed element is not used.
                Beta[I]>0
    Mu0     ?  zeroth moment of the weighting function.
    A       ?  left boundary of the integration interval.
    N       ?  number of nodes of the quadrature formula, N>=2
                (including the left boundary node).

OUTPUT PARAMETERS:
    Info    -   error code:
                * -3    internal eigenproblem solver hasn't converged
                * -2    Beta[i]<=0
                * -1    incorrect N was passed
                *  1    OK
    X       -   array[0..N-1] - array of quadrature nodes,
                in ascending order.
    W       -   array[0..N-1] - array of quadrature weights.


  -- ALGLIB --
     Copyright 2005-2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Gauss-Radau 직각 위상 수식의 노드와 가중치 계산
이 알고리즘은 다음과 같이 N 포인트 Gauss-Radau 직교 위상 공식을 생성합니다.
재발의 계수 α와 β에 의해 ​​주어진 가중치 함수
이것은 직교 다항식의 시스템을 생성한다.
P-1 (x) = 0
P0 (x) = 1
Pn + 1 (x) = (x-α (n)) * Pn (x) - β (n) * Pn-
0 차 모멘트 Mu0
Mu0 = 적분 (W (x) dx, a, b)
입력 매개 변수 :
    알파 - 배열 [0..N-2], 알파 계수.
    베타 - 배열 [0..N-1], 베타 계수
                인덱스가없는 요소는 사용되지 않습니다.
                베타 [I]> 0
    Mu0 - 가중치 함수의 0 차 순간.
    A - 적분 간격의 왼쪽 경계.
    N - 직교 공식의 노드 수, N> = 2
                (왼쪽 경계 노드 포함).
출력 매개 변수 :
    정보 - 오류 코드 :
                * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                * -2 베타 [i] <= 0
                * -1 잘못된 N이 전달되었습니다.
                * 1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2009
**************************************************************************/
void gqgenerategaussradaurec(const real_1d_array &alpha, const real_1d_array &beta, const double mu0, const double a, const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &w);


/*************************************************************************
Returns nodes/weights for Gauss-Legendre quadrature on [-1,1] with N
nodes.

INPUT PARAMETERS:
    N           -   number of nodes, >=1

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -4    an  error   was   detected   when  calculating
                            weights/nodes.  N  is  too  large   to  obtain
                            weights/nodes  with  high   enough   accuracy.
                            Try  to   use   multiple   precision  version.
                    * -3    internal eigenproblem solver hasn't  converged
                    * -1    incorrect N was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes,
                    in ascending order.
    W           -   array[0..N-1] - array of quadrature weights.


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
[-1,1]에서 Gauss-Legendre 구적법의 노드 / 가중치를 N으로 반환합니다.
노드.
입력 매개 변수 :
    N - 노드 수,> = 1
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. N은 얻기에는 너무 큽니다.
                            정확도가 높은 가중치 / 노드
                            여러 정밀 버전을 사용해보십시오.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N이 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                    오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gqgenerategausslegendre(const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &w);


/*************************************************************************
Returns  nodes/weights  for  Gauss-Jacobi quadrature on [-1,1] with weight
function W(x)=Power(1-x,Alpha)*Power(1+x,Beta).

INPUT PARAMETERS:
    N           -   number of nodes, >=1
    Alpha       -   power-law coefficient, Alpha>-1
    Beta        -   power-law coefficient, Beta>-1

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -4    an  error  was   detected   when   calculating
                            weights/nodes. Alpha or  Beta  are  too  close
                            to -1 to obtain weights/nodes with high enough
                            accuracy, or, may be, N is too large.  Try  to
                            use multiple precision version.
                    * -3    internal eigenproblem solver hasn't converged
                    * -1    incorrect N/Alpha/Beta was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes,
                    in ascending order.
    W           -   array[0..N-1] - array of quadrature weights.


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
[-1,1]에서 Gauss-Jacobi 구적법에 대한 노드 / 가중치를 가중치로 반환합니다.
함수 W (x) = 힘 (1-x, 알파) * 힘 (1 + x, 베타).
입력 매개 변수 :
    N - 노드 수,> = 1
    알파 - 지수 법 계수, 알파> -1
    베타 - 전력 법 계수, 베타> -1
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. 알파 또는 베타가 너무 가까이 있습니다.
                            -1로 충분히 가중치 / 노드를 얻으려면 -1로 설정하십시오.
                            정확도 또는 N이 너무 클 수 있습니다. 하려고 노력하다
                            다중 정밀도 버전을 사용하십시오.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N / Alpha / Beta가 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                    오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gqgenerategaussjacobi(const ae_int_t n, const double alpha, const double beta, ae_int_t &info, real_1d_array &x, real_1d_array &w);


/*************************************************************************
Returns  nodes/weights  for  Gauss-Laguerre  quadrature  on  [0,+inf) with
weight function W(x)=Power(x,Alpha)*Exp(-x)

INPUT PARAMETERS:
    N           -   number of nodes, >=1
    Alpha       -   power-law coefficient, Alpha>-1

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -4    an  error  was   detected   when   calculating
                            weights/nodes. Alpha is too  close  to  -1  to
                            obtain weights/nodes with high enough accuracy
                            or, may  be,  N  is  too  large.  Try  to  use
                            multiple precision version.
                    * -3    internal eigenproblem solver hasn't converged
                    * -1    incorrect N/Alpha was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes,
                    in ascending order.
    W           -   array[0..N-1] - array of quadrature weights.


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
[0, + inf]에 Gauss-Laguerre 구적법의 노드 / 가중치를 반환합니다.
무게 함수 W (x) = 힘 (x, 알파) * Exp (-x)
입력 매개 변수 :
    N - 노드 수,> = 1
    알파 - 지수 법 계수, 알파> -1
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. 알파가 -1에 너무 가깝습니다.
                            충분히 높은 정확도를 가진 가중치 / 노드를 얻는다.
                            또는 N이 너무 클 수 있습니다. 사용하려고 시도하십시오.
                            다중 정밀도 버전.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N / Alpha가 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                    오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gqgenerategausslaguerre(const ae_int_t n, const double alpha, ae_int_t &info, real_1d_array &x, real_1d_array &w);


/*************************************************************************
Returns  nodes/weights  for  Gauss-Hermite  quadrature on (-inf,+inf) with
weight function W(x)=Exp(-x*x)

INPUT PARAMETERS:
    N           -   number of nodes, >=1

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -4    an  error  was   detected   when   calculating
                            weights/nodes.  May be, N is too large. Try to
                            use multiple precision version.
                    * -3    internal eigenproblem solver hasn't converged
                    * -1    incorrect N/Alpha was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes,
                    in ascending order.
    W           -   array[0..N-1] - array of quadrature weights.


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Gauss-Hermite 구적법의 노드 / 가중치 (-inf, + inf)를 반환합니다.
가중치 함수 W (x) = Exp (-x * x)
입력 매개 변수 :
    N - 노드 수,> = 1
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. N은 너무 큽니다. 하려고 노력하다
                            다중 정밀도 버전을 사용하십시오.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N / Alpha가 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                    오름차순으로
    W - 배열 [0..N-1] - 직교 가중치의 배열.
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gqgenerategausshermite(const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &w);

/*************************************************************************
Computation of nodes and weights of a Gauss-Kronrod quadrature formula

The algorithm generates the N-point Gauss-Kronrod quadrature formula  with
weight  function  given  by  coefficients  alpha  and beta of a recurrence
relation which generates a system of orthogonal polynomials:

    P-1(x)   =  0
    P0(x)    =  1
    Pn+1(x)  =  (x-alpha(n))*Pn(x)  -  beta(n)*Pn-1(x)

and zero moment Mu0

    Mu0 = integral(W(x)dx,a,b)


INPUT PARAMETERS:
    Alpha       ?  alpha coefficients, array[0..floor(3*K/2)].
    Beta        ?  beta coefficients,  array[0..ceil(3*K/2)].
                    Beta[0] is not used and may be arbitrary.
                    Beta[I]>0.
    Mu0         ?  zeroth moment of the weight function.
    N           ?  number of nodes of the Gauss-Kronrod quadrature formula,
                    N >= 3,
                    N =  2*K+1.

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -5    no real and positive Gauss-Kronrod formula can
                            be created for such a weight function  with  a
                            given number of nodes.
                    * -4    N is too large, task may be ill  conditioned -
                            x[i]=x[i+1] found.
                    * -3    internal eigenproblem solver hasn't converged
                    * -2    Beta[i]<=0
                    * -1    incorrect N was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes,
                    in ascending order.
    WKronrod    -   array[0..N-1] - Kronrod weights
    WGauss      -   array[0..N-1] - Gauss weights (interleaved with zeros
                    corresponding to extended Kronrod nodes).

  -- ALGLIB --
     Copyright 08.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
가우스 - 크로로드 직교 수식의 노드 및 가중치 계산
알고리즘은 다음과 같이 N 포인트 Gauss-Kronrod 직교 공식을 생성합니다.
재발의 계수 α와 beta에 의해 주어진 가중치 함수
직교 다항식의 시스템을 생성하는 관계 :
    P-1 (x) = 0
    P0 (x) = 1
    Pn + 1 (x) = (x-α (n)) * Pn (x) - β (n) * Pn-
0 차 모멘트 Mu0
    Mu0 = 적분 (W (x) dx, a, b)
입력 매개 변수 :
    알파 - 알파 계수, 배열 [0..floor (3 * K / 2)].
    베타 - 베타 계수, 배열 [0..ceil (3 * K / 2)].
                    베타 [0]은 사용되지 않으며 임의적 일 수 있습니다.
                    베타 [I]> 0.
    Mu0 - 가중치 함수의 0 차 순간.
    N - Gauss-Kronrod 구적 공식의 노드 수,
                    N> = 3,
                    N = 2 * K + 1이다.
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -5 실제 ​​및 양의 Gauss-Kronrod 수식은 없습니다.
                            그러한 가중치 함수에 대해
                            주어진 수의 노드.
                    * -4 N이 너무 크면 작업을 조절할 수 없습니다.
                            x [i] = x [i + 1]가 발견되었다.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -2 베타 [i] <= 0
                    * -1 잘못된 N이 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열,
                    오름차순으로
    WKronrod - 배열 [0..N-1] - Kronrod 가중치
    WGauss - 배열 [0..N-1] - 가우스 가중치 (0으로 인터리브 됨)
                    확장 된 Kronrod 노드에 해당).
  - ALGLIB -
     저작권 08.05.2009 Bochkanov Sergey
**************************************************************************/
void gkqgeneraterec(const real_1d_array &alpha, const real_1d_array &beta, const double mu0, const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &wkronrod, real_1d_array &wgauss);


/*************************************************************************
Returns   Gauss   and   Gauss-Kronrod   nodes/weights  for  Gauss-Legendre
quadrature with N points.

GKQLegendreCalc (calculation) or  GKQLegendreTbl  (precomputed  table)  is
used depending on machine precision and number of nodes.

INPUT PARAMETERS:
    N           -   number of Kronrod nodes, must be odd number, >=3.

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -4    an  error   was   detected   when  calculating
                            weights/nodes.  N  is  too  large   to  obtain
                            weights/nodes  with  high   enough   accuracy.
                            Try  to   use   multiple   precision  version.
                    * -3    internal eigenproblem solver hasn't converged
                    * -1    incorrect N was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes, ordered in
                    ascending order.
    WKronrod    -   array[0..N-1] - Kronrod weights
    WGauss      -   array[0..N-1] - Gauss weights (interleaved with zeros
                    corresponding to extended Kronrod nodes).


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Gauss-Legendre에 대한 Gauss 및 Gauss-Kronrod 노드 / 가중치를 반환합니다.
N 점을 가진 구적법.
GKQLegendreCalc (계산) 또는 GKQLegendreTbl (사전 계산 된 표)
기계 정밀도 및 노드 수에 따라 사용됩니다.
입력 매개 변수 :
    N - 숫자의 Kronrod 노드는 홀수 여야하며> = 3이어야합니다.
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. N은 얻기에는 너무 큽니다.
                            정확도가 높은 가중치 / 노드
                            여러 정밀 버전을 사용해보십시오.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N이 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열.
                    오름차순.
    WKronrod - 배열 [0..N-1] - Kronrod 가중치
    WGauss - 배열 [0..N-1] - 가우스 가중치 (0으로 인터리브 됨)
                    확장 된 Kronrod 노드에 해당).
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gkqgenerategausslegendre(const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &wkronrod, real_1d_array &wgauss);


/*************************************************************************
Returns   Gauss   and   Gauss-Kronrod   nodes/weights   for   Gauss-Jacobi
quadrature on [-1,1] with weight function

    W(x)=Power(1-x,Alpha)*Power(1+x,Beta).

INPUT PARAMETERS:
    N           -   number of Kronrod nodes, must be odd number, >=3.
    Alpha       -   power-law coefficient, Alpha>-1
    Beta        -   power-law coefficient, Beta>-1

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -5    no real and positive Gauss-Kronrod formula can
                            be created for such a weight function  with  a
                            given number of nodes.
                    * -4    an  error  was   detected   when   calculating
                            weights/nodes. Alpha or  Beta  are  too  close
                            to -1 to obtain weights/nodes with high enough
                            accuracy, or, may be, N is too large.  Try  to
                            use multiple precision version.
                    * -3    internal eigenproblem solver hasn't converged
                    * -1    incorrect N was passed
                    * +1    OK
                    * +2    OK, but quadrature rule have exterior  nodes,
                            x[0]<-1 or x[n-1]>+1
    X           -   array[0..N-1] - array of quadrature nodes, ordered in
                    ascending order.
    WKronrod    -   array[0..N-1] - Kronrod weights
    WGauss      -   array[0..N-1] - Gauss weights (interleaved with zeros
                    corresponding to extended Kronrod nodes).


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Gauss-Jacobi에 대한 Gauss 및 Gauss-Kronrod 노드 / 가중치를 반환합니다.
가중치 함수가있는 [-1,1]의 구적법
    W (x) = 힘 (1-x, 알파) * 힘 (1 + x, 베타).
입력 매개 변수 :
    N - 숫자의 Kronrod 노드는 홀수 여야하며> = 3이어야합니다.
    알파 - 지수 법 계수, 알파> -1
    베타 - 전력 법 계수, 베타> -1
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -5 실제 ​​및 양의 Gauss-Kronrod 수식은 없습니다.
                            그러한 가중치 함수에 대해
                            주어진 수의 노드.
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. 알파 또는 베타가 너무 가까이 있습니다.
                            -1로 충분히 가중치 / 노드를 얻으려면 -1로 설정하십시오.
                            정확도 또는 N이 너무 클 수 있습니다. 하려고 노력하다
                            다중 정밀도 버전을 사용하십시오.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N이 전달되었습니다.
                    * +1 OK
                    * +2 OK, 구적 법칙은 외부 노드를 가지고 있지만,
                            x [0] <- 1 또는 x [n-1]> +1
    X- 배열 [0..N-1] - 직교 노드의 배열.
                    오름차순.
    WKronrod - 배열 [0..N-1] - Kronrod 가중치
    WGauss - 배열 [0..N-1] - 가우스 가중치 (0으로 인터리브 됨)
                    확장 된 Kronrod 노드에 해당).
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gkqgenerategaussjacobi(const ae_int_t n, const double alpha, const double beta, ae_int_t &info, real_1d_array &x, real_1d_array &wkronrod, real_1d_array &wgauss);


/*************************************************************************
Returns Gauss and Gauss-Kronrod nodes for quadrature with N points.

Reduction to tridiagonal eigenproblem is used.

INPUT PARAMETERS:
    N           -   number of Kronrod nodes, must be odd number, >=3.

OUTPUT PARAMETERS:
    Info        -   error code:
                    * -4    an  error   was   detected   when  calculating
                            weights/nodes.  N  is  too  large   to  obtain
                            weights/nodes  with  high   enough   accuracy.
                            Try  to   use   multiple   precision  version.
                    * -3    internal eigenproblem solver hasn't converged
                    * -1    incorrect N was passed
                    * +1    OK
    X           -   array[0..N-1] - array of quadrature nodes, ordered in
                    ascending order.
    WKronrod    -   array[0..N-1] - Kronrod weights
    WGauss      -   array[0..N-1] - Gauss weights (interleaved with zeros
                    corresponding to extended Kronrod nodes).

  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
N 포인트가있는 구적법에 대해 Gauss 및 Gauss-Kronrod 노드를 반환합니다.
tridiagonal 고유 값 감소가 사용됩니다.
입력 매개 변수 :
    N - 숫자의 Kronrod 노드는 홀수 여야하며> = 3이어야합니다.
출력 매개 변수 :
    정보 - 오류 코드 :
                    * -4 계산시 오류가 감지되었습니다.
                            가중치 / 노드. N은 얻기에는 너무 큽니다.
                            정확도가 높은 가중치 / 노드
                            여러 정밀 버전을 사용해보십시오.
                    * -3 내부 고유 문제 해결사가 수렴하지 않았습니다.
                    * -1 잘못된 N이 전달되었습니다.
                    * +1 OK
    X- 배열 [0..N-1] - 직교 노드의 배열.
                    오름차순.
    WKronrod - 배열 [0..N-1] - Kronrod 가중치
    WGauss - 배열 [0..N-1] - 가우스 가중치 (0으로 인터리브 됨)
                    확장 된 Kronrod 노드에 해당).
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gkqlegendrecalc(const ae_int_t n, ae_int_t &info, real_1d_array &x, real_1d_array &wkronrod, real_1d_array &wgauss);


/*************************************************************************
Returns Gauss and Gauss-Kronrod nodes for quadrature with N  points  using
pre-calculated table. Nodes/weights were  computed  with  accuracy  up  to
1.0E-32 (if MPFR version of ALGLIB is used). In standard double  precision
accuracy reduces to something about 2.0E-16 (depending  on your compiler's
handling of long floating point constants).

INPUT PARAMETERS:
    N           -   number of Kronrod nodes.
                    N can be 15, 21, 31, 41, 51, 61.

OUTPUT PARAMETERS:
    X           -   array[0..N-1] - array of quadrature nodes, ordered in
                    ascending order.
    WKronrod    -   array[0..N-1] - Kronrod weights
    WGauss      -   array[0..N-1] - Gauss weights (interleaved with zeros
                    corresponding to extended Kronrod nodes).


  -- ALGLIB --
     Copyright 12.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
를 사용하여 N 포인트가있는 구적법에 대해 Gauss 및 Gauss-Kronrod 노드를 반환합니다.
사전 계산 된 테이블. 노드 / 가중치는 다음과 같은 정확도로 계산되었습니다.
1.0E-32 (ALGLIB의 MPFR 버전이 사용되는 경우). 표준 배정 밀도
정확도는 2.0E-16 정도가 될 것입니다 (컴파일러의
긴 부동 소수점 상수의 처리).
입력 매개 변수 :
    N 개의 Kronrod 노드.
                    N은 15, 21, 31, 41, 51, 61 일 수 있습니다.
출력 매개 변수 :
    X- 배열 [0..N-1] - 직교 노드의 배열.
                    오름차순.
    WKronrod - 배열 [0..N-1] - Kronrod 가중치
    WGauss - 배열 [0..N-1] - 가우스 가중치 (0으로 인터리브 됨)
                    확장 된 Kronrod 노드에 해당).
  - ALGLIB -
     Copyright 12.05.2009 Bochkanov Sergey
**************************************************************************/
void gkqlegendretbl(const ae_int_t n, real_1d_array &x, real_1d_array &wkronrod, real_1d_array &wgauss, double &eps);

/*************************************************************************
Integration of a smooth function F(x) on a finite interval [a,b].

Fast-convergent algorithm based on a Gauss-Kronrod formula is used. Result
is calculated with accuracy close to the machine precision.

Algorithm works well only with smooth integrands.  It  may  be  used  with
continuous non-smooth integrands, but with  less  performance.

It should never be used with integrands which have integrable singularities
at lower or upper limits - algorithm may crash. Use AutoGKSingular in such
cases.

INPUT PARAMETERS:
    A, B    -   interval boundaries (A<B, A=B or A>B)

OUTPUT PARAMETERS
    State   -   structure which stores algorithm state

SEE ALSO
    AutoGKSmoothW, AutoGKSingular, AutoGKResults.


  -- ALGLIB --
     Copyright 06.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
유한 구간 [a, b]에서의 부드러운 함수 F (x)의 적분.
Gauss-Kronrod 공식을 기반으로 한 빠른 수렴 알고리즘이 사용됩니다. 결과
기계 정밀도에 가까운 정확도로 계산됩니다.
알고리즘은 원활한 적분에서만 잘 작동합니다. 그것은 다음과 함께 사용될 수있다.
연속적인 비 매끄러 운 적분을 제공하지만 성능은 떨어집니다.
적분 특이점을 갖는 적분 함수와 절대로 사용해서는 안됩니다.
하한 또는 상한선에서 - 알고리즘이 중단 될 수 있습니다. 그런 용도로 AutoGKSingular 사용
사례.
입력 매개 변수 :
    A, B - 간격 경계 (A <B, A = B 또는 A> B)
출력 매개 변수
    State - 알고리즘 상태를 저장하는 구조
관련 항목
    AutoGKSmoothW, AutoGKSingular, AutoGKResults.
  - ALGLIB -
     저작권 06.05.2009 Bochkanov Sergey
**************************************************************************/
void autogksmooth(const double a, const double b, autogkstate &state);


/*************************************************************************
Integration of a smooth function F(x) on a finite interval [a,b].

This subroutine is same as AutoGKSmooth(), but it guarantees that interval
[a,b] is partitioned into subintervals which have width at most XWidth.

Subroutine  can  be  used  when  integrating nearly-constant function with
narrow "bumps" (about XWidth wide). If "bumps" are too narrow, AutoGKSmooth
subroutine can overlook them.

INPUT PARAMETERS:
    A, B    -   interval boundaries (A<B, A=B or A>B)

OUTPUT PARAMETERS
    State   -   structure which stores algorithm state

SEE ALSO
    AutoGKSmooth, AutoGKSingular, AutoGKResults.


  -- ALGLIB --
     Copyright 06.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
유한 구간 [a, b]에서의 부드러운 함수 F (x)의 적분.
이 서브 루틴은 AutoGKSmooth ()와 동일하지만, 그 간격
[a, b]는 너비 XWidth 이하의 서브 인터벌로 분할됩니다.
거의 일정한 함수를 다음과 같이 통합 할 때 서브 루틴을 사용할 수 있습니다.
좁은 "범프"(약 X 폭 너비). "범프"가 너무 좁은 경우 AutoGKSmooth
서브 루틴은 그것들을 간과 할 수 있습니다.
입력 매개 변수 :
    A, B - 간격 경계 (A <B, A = B 또는 A> B)
출력 매개 변수
    State - 알고리즘 상태를 저장하는 구조
관련 항목
    AutoGKSmooth, AutoGKSingular, AutoGKResults.
  - ALGLIB -
     저작권 06.05.2009 Bochkanov Sergey
**************************************************************************/
void autogksmoothw(const double a, const double b, const double xwidth, autogkstate &state);


/*************************************************************************
Integration on a finite interval [A,B].
Integrand have integrable singularities at A/B.

F(X) must diverge as "(x-A)^alpha" at A, as "(B-x)^beta" at B,  with known
alpha/beta (alpha>-1, beta>-1).  If alpha/beta  are  not known,  estimates
from below can be used (but these estimates should be greater than -1 too).

One  of  alpha/beta variables (or even both alpha/beta) may be equal to 0,
which means than function F(x) is non-singular at A/B. Anyway (singular at
bounds or not), function F(x) is supposed to be continuous on (A,B).

Fast-convergent algorithm based on a Gauss-Kronrod formula is used. Result
is calculated with accuracy close to the machine precision.

INPUT PARAMETERS:
    A, B    -   interval boundaries (A<B, A=B or A>B)
    Alpha   -   power-law coefficient of the F(x) at A,
                Alpha>-1
    Beta    -   power-law coefficient of the F(x) at B,
                Beta>-1

OUTPUT PARAMETERS
    State   -   structure which stores algorithm state

SEE ALSO
    AutoGKSmooth, AutoGKSmoothW, AutoGKResults.


  -- ALGLIB --
     Copyright 06.05.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
유한 구간에 대한 적분 [A, B].
Integrand는 A / B에서 적분 특이점을 갖는다.
F (X)는 A에서 "(xA) ^ alpha"로, B에서는 "(Bx) ^ beta"
알파 / 베타 (alpha> -1, beta> -1). 알파 / 베타가 알려지지 않은 경우 견적
아래에서 사용할 수 있습니다 (하지만이 추정치는 -1보다 커야합니다).
알파 / 베타 변수 중 하나 (또는 ​​알파 / 베타 모두)는 0과 같을 수 있지만,
이는 함수 F (x)가 A / B에서 비 특이 적이라는 것을 의미합니다. 어쨌든 (단수
bounds or not), 함수 F (x)는 연속 (A, B)로 가정된다.
Gauss-Kronrod 공식을 기반으로 한 빠른 수렴 알고리즘이 사용됩니다. 결과
기계 정밀도에 가까운 정확도로 계산됩니다.
입력 매개 변수 :
    A, B - 간격 경계 (A <B, A = B 또는 A> B)
    α에서의 F (x)의 알파 - 지수 법 계수,
                알파> -1
    베타 - B에서의 F (x)의 지수 함수 계수,
                베타> -1
출력 매개 변수
    State - 알고리즘 상태를 저장하는 구조
관련 항목
    AutoGKSmooth, AutoGKSmoothW, AutoGKResults.
  - ALGLIB -
     저작권 06.05.2009 Bochkanov Sergey
**************************************************************************/
void autogksingular(const double a, const double b, const double alpha, const double beta, autogkstate &state);


/*************************************************************************
This function provides reverse communication interface
Reverse communication interface is not documented or recommended to use.
See below for functions which provide better documented API
*************************************************************************/
/**************************************************************************
이 기능은 역방향 통신 인터페이스를 제공합니다.
역방향 통신 인터페이스는 문서화되어 있지 않거나 사용하도록 권장되지 않습니다.
보다 잘 문서화 된 API를 제공하는 함수는 아래를 참조하십시오.
**************************************************************************/
bool autogkiteration(const autogkstate &state);


/*************************************************************************
This function is used to launcn iterations of the 1-dimensional integrator

It accepts following parameters:
    func    -   callback which calculates f(x) for given x
    ptr     -   optional pointer which is passed to func; can be NULL


  -- ALGLIB --
     Copyright 07.05.2009 by Bochkanov Sergey

*************************************************************************/
/**************************************************************************
이 함수는 1 차원 적분기의 반복을 시작하는 데 사용됩니다.
다음 매개 변수를 허용합니다.
    func - 주어진 x에 대해 f (x)를 계산하는 콜백
    ptr - func에 전달되는 선택적 포인터. NULL 일 수있다.
  - ALGLIB -
     저작권 07.05.2009 Bochkanov Sergey
**************************************************************************/
void autogkintegrate(autogkstate &state,
    void (*func)(double x, double xminusa, double bminusx, double &y, void *ptr),
    void *ptr = NULL);


/*************************************************************************
Adaptive integration results

Called after AutoGKIteration returned False.

Input parameters:
    State   -   algorithm state (used by AutoGKIteration).

Output parameters:
    V       -   integral(f(x)dx,a,b)
    Rep     -   optimization report (see AutoGKReport description)

  -- ALGLIB --
     Copyright 14.11.2007 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
적응 형 통합 결과
AutoGKIteration 이후에 호출되어 False를 반환했습니다.
입력 매개 변수 :
    상태 - 알고리즘 상태 (AutoGKIteration에 의해 사용됨).
출력 매개 변수 :
    V - 적분 (f (x) dx, a, b)
    담당자 최적화 보고서 (AutoGKReport 설명 참조)
  - ALGLIB -
     Bochkanov Sergey의 Copyright 14.11.2007
**************************************************************************/
void autogkresults(const autogkstate &state, double &v, autogkreport &rep);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
void gqgeneraterec(/* Real    */ ae_vector* alpha,
     /* Real    */ ae_vector* beta,
     double mu0,
     ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gqgenerategausslobattorec(/* Real    */ ae_vector* alpha,
     /* Real    */ ae_vector* beta,
     double mu0,
     double a,
     double b,
     ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gqgenerategaussradaurec(/* Real    */ ae_vector* alpha,
     /* Real    */ ae_vector* beta,
     double mu0,
     double a,
     ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gqgenerategausslegendre(ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gqgenerategaussjacobi(ae_int_t n,
     double alpha,
     double beta,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gqgenerategausslaguerre(ae_int_t n,
     double alpha,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gqgenerategausshermite(ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void gkqgeneraterec(/* Real    */ ae_vector* alpha,
     /* Real    */ ae_vector* beta,
     double mu0,
     ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* wkronrod,
     /* Real    */ ae_vector* wgauss,
     ae_state *_state);
void gkqgenerategausslegendre(ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* wkronrod,
     /* Real    */ ae_vector* wgauss,
     ae_state *_state);
void gkqgenerategaussjacobi(ae_int_t n,
     double alpha,
     double beta,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* wkronrod,
     /* Real    */ ae_vector* wgauss,
     ae_state *_state);
void gkqlegendrecalc(ae_int_t n,
     ae_int_t* info,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* wkronrod,
     /* Real    */ ae_vector* wgauss,
     ae_state *_state);
void gkqlegendretbl(ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* wkronrod,
     /* Real    */ ae_vector* wgauss,
     double* eps,
     ae_state *_state);
void autogksmooth(double a,
     double b,
     autogkstate* state,
     ae_state *_state);
void autogksmoothw(double a,
     double b,
     double xwidth,
     autogkstate* state,
     ae_state *_state);
void autogksingular(double a,
     double b,
     double alpha,
     double beta,
     autogkstate* state,
     ae_state *_state);
ae_bool autogkiteration(autogkstate* state, ae_state *_state);
void autogkresults(autogkstate* state,
     double* v,
     autogkreport* rep,
     ae_state *_state);
ae_bool _autogkreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _autogkreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _autogkreport_clear(void* _p);
void _autogkreport_destroy(void* _p);
ae_bool _autogkinternalstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _autogkinternalstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _autogkinternalstate_clear(void* _p);
void _autogkinternalstate_destroy(void* _p);
ae_bool _autogkstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _autogkstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _autogkstate_clear(void* _p);
void _autogkstate_destroy(void* _p);

}
#endif

