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
#ifndef _linalg_pkg_h
#define _linalg_pkg_h
#include "ap.h"
#include "alglibinternal.h"
#include "alglibmisc.h"

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
    double r1;
    double rinf;
} matinvreport;
typedef struct
{
    ae_vector vals;
    ae_vector idx;
    ae_vector ridx;
    ae_vector didx;
    ae_vector uidx;
    ae_int_t matrixtype;
    ae_int_t m;
    ae_int_t n;
    ae_int_t nfree;
    ae_int_t ninitialized;
} sparsematrix;
typedef struct
{
    double e1;
    double e2;
    ae_vector x;
    ae_vector ax;
    double xax;
    ae_int_t n;
    ae_vector rk;
    ae_vector rk1;
    ae_vector xk;
    ae_vector xk1;
    ae_vector pk;
    ae_vector pk1;
    ae_vector b;
    rcommstate rstate;
    ae_vector tmp2;
} fblslincgstate;
typedef struct
{
    ae_int_t n;
    ae_int_t m;
    ae_int_t nstart;
    ae_int_t nits;
    ae_int_t seedval;
    ae_vector x0;
    ae_vector x1;
    ae_vector t;
    ae_vector xbest;
    hqrndstate r;
    ae_vector x;
    ae_vector mv;
    ae_vector mtv;
    ae_bool needmv;
    ae_bool needmtv;
    double repnorm;
    rcommstate rstate;
} normestimatorstate;

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
Matrix inverse report:
* R1    reciprocal of condition number in 1-norm
* RInf  reciprocal of condition number in inf-norm
*************************************************************************/

/* ************************************************ *************************
역행렬 보고서 :
* 1- 표준에서 조건 수의 역행렬
* 표준 조건에서 조건 수의 역행렬
*************************************************** ********************** */

class _matinvreport_owner
{
public:
    _matinvreport_owner();
    _matinvreport_owner(const _matinvreport_owner &rhs);
    _matinvreport_owner& operator=(const _matinvreport_owner &rhs);
    virtual ~_matinvreport_owner();
    alglib_impl::matinvreport* c_ptr();
    alglib_impl::matinvreport* c_ptr() const;
protected:
    alglib_impl::matinvreport *p_struct;
};
class matinvreport : public _matinvreport_owner
{
public:
    matinvreport();
    matinvreport(const matinvreport &rhs);
    matinvreport& operator=(const matinvreport &rhs);
    virtual ~matinvreport();
    double &r1;
    double &rinf;

};

/*************************************************************************
Sparse matrix

You should use ALGLIB functions to work with sparse matrix.
Never try to access its fields directly!
*************************************************************************/

/* ************************************************ *************************
스파 스 매트릭스
스파 스 매트릭스로 작업하려면 ALGLIB 함수를 사용해야합니다.
필드에 직접 액세스하지 마세요.
*************************************************** ********************** */

class _sparsematrix_owner
{
public:
    _sparsematrix_owner();
    _sparsematrix_owner(const _sparsematrix_owner &rhs);
    _sparsematrix_owner& operator=(const _sparsematrix_owner &rhs);
    virtual ~_sparsematrix_owner();
    alglib_impl::sparsematrix* c_ptr();
    alglib_impl::sparsematrix* c_ptr() const;
protected:
    alglib_impl::sparsematrix *p_struct;
};
class sparsematrix : public _sparsematrix_owner
{
public:
    sparsematrix();
    sparsematrix(const sparsematrix &rhs);
    sparsematrix& operator=(const sparsematrix &rhs);
    virtual ~sparsematrix();

};



/*************************************************************************
This object stores state of the iterative norm estimation algorithm.

You should use ALGLIB functions to work with this object.
*************************************************************************/

/* ************************************************ *************************
이 객체는 반복적인 추정 알고리즘의 상태를 저장합니다.
이 객체를 사용하려면 ALGLIB 함수를 사용해야합니다.
*************************************************** ********************** */

class _normestimatorstate_owner
{
public:
    _normestimatorstate_owner();
    _normestimatorstate_owner(const _normestimatorstate_owner &rhs);
    _normestimatorstate_owner& operator=(const _normestimatorstate_owner &rhs);
    virtual ~_normestimatorstate_owner();
    alglib_impl::normestimatorstate* c_ptr();
    alglib_impl::normestimatorstate* c_ptr() const;
protected:
    alglib_impl::normestimatorstate *p_struct;
};
class normestimatorstate : public _normestimatorstate_owner
{
public:
    normestimatorstate();
    normestimatorstate(const normestimatorstate &rhs);
    normestimatorstate& operator=(const normestimatorstate &rhs);
    virtual ~normestimatorstate();

};

/*************************************************************************
Cache-oblivous complex "copy-and-transpose"

Input parameters:
    M   -   number of rows
    N   -   number of columns
    A   -   source matrix, MxN submatrix is copied and transposed
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    B   -   destination matrix, must be large enough to store result
    IB  -   submatrix offset (row index)
    JB  -   submatrix offset (column index)
*************************************************************************/

/* ************************************************ *************************
캐시 - 망각 복합 "복사 - 및 - 전치"
입력 매개 변수 :
    M - 행 수
    N - 열 수
    A - 소스 행렬, MxN 서브 행렬이 복사되고 전치 됨
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    B - 목적지 행렬, 결과를 저장할만큼 커야 함
    IB - 부분 매트릭스 오프셋 (행 인덱스)
    JB - 서브 매트릭스 오프셋 (컬럼 인덱스)
*************************************************** ********************** */

void cmatrixtranspose(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, complex_2d_array &b, const ae_int_t ib, const ae_int_t jb);


/*************************************************************************
Cache-oblivous real "copy-and-transpose"

Input parameters:
    M   -   number of rows
    N   -   number of columns
    A   -   source matrix, MxN submatrix is copied and transposed
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    B   -   destination matrix, must be large enough to store result
    IB  -   submatrix offset (row index)
    JB  -   submatrix offset (column index)
*************************************************************************/

/* ************************************************ *************************
캐시가 필요없는 실제 "복사 및 변환"
입력 매개 변수 :
    M - 행 수
    N - 열 수
    A - 소스 행렬, MxN 서브 행렬이 복사되고 전치 됨
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    B - 목적지 행렬, 결과를 저장할만큼 커야 함
    IB - 부분 매트릭스 오프셋 (행 인덱스)
    JB - 서브 매트릭스 오프셋 (컬럼 인덱스)
*************************************************** ********************** */

void rmatrixtranspose(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, real_2d_array &b, const ae_int_t ib, const ae_int_t jb);


/*************************************************************************
This code enforces symmetricy of the matrix by copying Upper part to lower
one (or vice versa).

INPUT PARAMETERS:
    A   -   matrix
    N   -   number of rows/columns
    IsUpper - whether we want to copy upper triangle to lower one (True)
            or vice versa (False).
*************************************************************************/

/* ************************************************ *************************
이 코드는 위쪽 부분을 아래쪽 부분으로 복사하여 행렬의 대칭을 적용합니다.
하나 (또는 ​​그 반대).
입력 매개 변수 :
    A- 행렬
    N - 행 / 열 수
    IsUpper - 상한 삼각형을 아래로 복사할지 (True)
            또는 그 반대 (False).
*************************************************** ********************** */

void rmatrixenforcesymmetricity(const real_2d_array &a, const ae_int_t n, const bool isupper);


/*************************************************************************
Copy

Input parameters:
    M   -   number of rows
    N   -   number of columns
    A   -   source matrix, MxN submatrix is copied and transposed
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    B   -   destination matrix, must be large enough to store result
    IB  -   submatrix offset (row index)
    JB  -   submatrix offset (column index)
*************************************************************************/

/* ************************************************ *************************
부
입력 매개 변수 :
    M - 행 수
    N - 열 수
    A - 소스 행렬, MxN 서브 행렬이 복사되고 전치 됨
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    B - 목적지 행렬, 결과를 저장할만큼 커야 함
    IB - 부분 매트릭스 오프셋 (행 인덱스)
    JB - 서브 매트릭스 오프셋 (컬럼 인덱스)
*************************************************** ********************** */

void cmatrixcopy(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, complex_2d_array &b, const ae_int_t ib, const ae_int_t jb);


/*************************************************************************
Copy

Input parameters:
    M   -   number of rows
    N   -   number of columns
    A   -   source matrix, MxN submatrix is copied and transposed
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    B   -   destination matrix, must be large enough to store result
    IB  -   submatrix offset (row index)
    JB  -   submatrix offset (column index)
*************************************************************************/

/* ************************************************ *************************
부
입력 매개 변수 :
    M - 행 수
    N - 열 수
    A - 소스 행렬, MxN 서브 행렬이 복사되고 전치 됨
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    B - 목적지 행렬, 결과를 저장할만큼 커야 함
    IB - 부분 매트릭스 오프셋 (행 인덱스)
    JB - 서브 매트릭스 오프셋 (컬럼 인덱스)
*************************************************** ********************** */

void rmatrixcopy(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, real_2d_array &b, const ae_int_t ib, const ae_int_t jb);


/*************************************************************************
Rank-1 correction: A := A + u*v'

INPUT PARAMETERS:
    M   -   number of rows
    N   -   number of columns
    A   -   target matrix, MxN submatrix is updated
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    U   -   vector #1
    IU  -   subvector offset
    V   -   vector #2
    IV  -   subvector offset
*************************************************************************/

/* ************************************************ *************************
순위 1 보정 : A : = A + u * v '
입력 매개 변수 :
    M - 행 수
    N - 열 수
    A - 목표 행렬, MxN 부분 행렬이 업데이트 됨
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    유 - 벡터 # 1
    IU - 서브 벡터 오프셋
    브이 - 벡터 # 2
    IV - 서브 벡터 오프셋
*************************************************** ********************** */

void cmatrixrank1(const ae_int_t m, const ae_int_t n, complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, complex_1d_array &u, const ae_int_t iu, complex_1d_array &v, const ae_int_t iv);


/*************************************************************************
Rank-1 correction: A := A + u*v'

INPUT PARAMETERS:
    M   -   number of rows
    N   -   number of columns
    A   -   target matrix, MxN submatrix is updated
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    U   -   vector #1
    IU  -   subvector offset
    V   -   vector #2
    IV  -   subvector offset
*************************************************************************/

/* ************************************************ *************************
순위 1 보정 : A : = A + u * v '
입력 매개 변수 :
    M - 행 수
    N - 열 수
    A - 목표 행렬, MxN 부분 행렬이 업데이트 됨
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    유 - 벡터 # 1
    IU - 서브 벡터 오프셋
    브이 - 벡터 # 2
    IV - 서브 벡터 오프셋
*************************************************** ********************** */
void rmatrixrank1(const ae_int_t m, const ae_int_t n, real_2d_array &a, const ae_int_t ia, const ae_int_t ja, real_1d_array &u, const ae_int_t iu, real_1d_array &v, const ae_int_t iv);


/*************************************************************************
Matrix-vector product: y := op(A)*x

INPUT PARAMETERS:
    M   -   number of rows of op(A)
            M>=0
    N   -   number of columns of op(A)
            N>=0
    A   -   target matrix
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    OpA -   operation type:
            * OpA=0     =>  op(A) = A
            * OpA=1     =>  op(A) = A^T
            * OpA=2     =>  op(A) = A^H
    X   -   input vector
    IX  -   subvector offset
    IY  -   subvector offset
    Y   -   preallocated matrix, must be large enough to store result

OUTPUT PARAMETERS:
    Y   -   vector which stores result

if M=0, then subroutine does nothing.
if N=0, Y is filled by zeros.


  -- ALGLIB routine --

     28.01.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 - 벡터 곱 : y : = op (A) * x
입력 매개 변수 :
    M - op (A)의 행 수
            M> = 0
    N - op (A)의 열 수
            N> = 0
    A - 표적 행렬
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    OpA - 운영 유형 :
            * OpA = 0 => op (A) = A
            * OpA = 1 => op (A) = A ^ T
            * OpA = 2 => op (A) = A ^ H
    X - 입력 벡터
    IX - 서브 벡터 오프셋
    IY - 서브 벡터 오프셋
    Y - 사전 할당 된 행렬, 결과를 저장할만큼 커야 함
출력 매개 변수 :
    Y - 결과를 저장하는 벡터
M = 0이면 서브 루틴은 아무것도하지 않습니다.
N = 0이면 Y는 0으로 채워집니다.
  - ALGLIB 루틴 -
     28.01.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixmv(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t opa, const complex_1d_array &x, const ae_int_t ix, complex_1d_array &y, const ae_int_t iy);


/*************************************************************************
Matrix-vector product: y := op(A)*x

INPUT PARAMETERS:
    M   -   number of rows of op(A)
    N   -   number of columns of op(A)
    A   -   target matrix
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    OpA -   operation type:
            * OpA=0     =>  op(A) = A
            * OpA=1     =>  op(A) = A^T
    X   -   input vector
    IX  -   subvector offset
    IY  -   subvector offset
    Y   -   preallocated matrix, must be large enough to store result

OUTPUT PARAMETERS:
    Y   -   vector which stores result

if M=0, then subroutine does nothing.
if N=0, Y is filled by zeros.


  -- ALGLIB routine --

     28.01.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 - 벡터 곱 : y : = op (A) * x
입력 매개 변수 :
    M - op (A)의 행 수
    N - op (A)의 열 수
    A - 표적 행렬
    IA - 부분 매트릭스 오프셋 (행 인덱스)
    JA - 서브 매트릭스 옵셋 (열 인덱스)
    OpA - 운영 유형 :
            * OpA = 0 => op (A) = A
            * OpA = 1 => op (A) = A ^ T
    X - 입력 벡터
    IX - 서브 벡터 오프셋
    IY - 서브 벡터 오프셋
    Y - 사전 할당 된 행렬, 결과를 저장할만큼 커야 함
출력 매개 변수 :
    Y - 결과를 저장하는 벡터
M = 0이면 서브 루틴은 아무것도하지 않습니다.
N = 0이면 Y는 0으로 채워집니다.
  - ALGLIB 루틴 -
     28.01.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixmv(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t opa, const real_1d_array &x, const ae_int_t ix, real_1d_array &y, const ae_int_t iy);


/*************************************************************************

*************************************************************************/
void cmatrixrighttrsm(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const complex_2d_array &x, const ae_int_t i2, const ae_int_t j2);
void smp_cmatrixrighttrsm(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const complex_2d_array &x, const ae_int_t i2, const ae_int_t j2);


/*************************************************************************

*************************************************************************/
void cmatrixlefttrsm(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const complex_2d_array &x, const ae_int_t i2, const ae_int_t j2);
void smp_cmatrixlefttrsm(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const complex_2d_array &x, const ae_int_t i2, const ae_int_t j2);


/*************************************************************************

*************************************************************************/
void rmatrixrighttrsm(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const real_2d_array &x, const ae_int_t i2, const ae_int_t j2);
void smp_rmatrixrighttrsm(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const real_2d_array &x, const ae_int_t i2, const ae_int_t j2);


/*************************************************************************

*************************************************************************/
void rmatrixlefttrsm(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const real_2d_array &x, const ae_int_t i2, const ae_int_t j2);
void smp_rmatrixlefttrsm(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const real_2d_array &x, const ae_int_t i2, const ae_int_t j2);


/*************************************************************************

*************************************************************************/
void cmatrixsyrk(const ae_int_t n, const ae_int_t k, const double alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);
void smp_cmatrixsyrk(const ae_int_t n, const ae_int_t k, const double alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);


/*************************************************************************

*************************************************************************/
void rmatrixsyrk(const ae_int_t n, const ae_int_t k, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const real_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);
void smp_rmatrixsyrk(const ae_int_t n, const ae_int_t k, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const real_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);


/*************************************************************************

*************************************************************************/
void cmatrixgemm(const ae_int_t m, const ae_int_t n, const ae_int_t k, const alglib::complex alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const complex_2d_array &b, const ae_int_t ib, const ae_int_t jb, const ae_int_t optypeb, const alglib::complex beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc);
void smp_cmatrixgemm(const ae_int_t m, const ae_int_t n, const ae_int_t k, const alglib::complex alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const complex_2d_array &b, const ae_int_t ib, const ae_int_t jb, const ae_int_t optypeb, const alglib::complex beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc);


/*************************************************************************

*************************************************************************/
void rmatrixgemm(const ae_int_t m, const ae_int_t n, const ae_int_t k, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const real_2d_array &b, const ae_int_t ib, const ae_int_t jb, const ae_int_t optypeb, const double beta, const real_2d_array &c, const ae_int_t ic, const ae_int_t jc);
void smp_rmatrixgemm(const ae_int_t m, const ae_int_t n, const ae_int_t k, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const real_2d_array &b, const ae_int_t ib, const ae_int_t jb, const ae_int_t optypeb, const double beta, const real_2d_array &c, const ae_int_t ic, const ae_int_t jc);

/*************************************************************************
QR decomposition of a rectangular matrix of size MxN

Input parameters:
    A   -   matrix A whose indexes range within [0..M-1, 0..N-1].
    M   -   number of rows in matrix A.
    N   -   number of columns in matrix A.

Output parameters:
    A   -   matrices Q and R in compact form (see below).
    Tau -   array of scalar factors which are used to form
            matrix Q. Array whose index ranges within [0.. Min(M-1,N-1)].

Matrix A is represented as A = QR, where Q is an orthogonal matrix of size
MxM, R - upper triangular (or upper trapezoid) matrix of size M x N.

The elements of matrix R are located on and above the main diagonal of
matrix A. The elements which are located in Tau array and below the main
diagonal of matrix A are used to form matrix Q as follows:

Matrix Q is represented as a product of elementary reflections

Q = H(0)*H(2)*...*H(k-1),

where k = min(m,n), and each H(i) is in the form

H(i) = 1 - tau * v * (v^T)

where tau is a scalar stored in Tau[I]; v - real vector,
so that v(0:i-1) = 0, v(i) = 1, v(i+1:m-1) stored in A(i+1:m-1,i).

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
크기 MxN의 직사각형 행렬의 QR 분해
입력 매개 변수 :
    A - 인덱스가 [0..M-1, 0..N-1] 범위 인 행렬 A.
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 작은 형태의 행렬 Q와 R (아래 참조).
    Tau - 형성에 사용되는 스칼라 인자의 배열
            matrix Q. 인덱스 범위가 [0 .. Min (M-1, N-1)] 범위 인 배열.
행렬 A는 A = QR로 표현되며, Q는 크기의 직교 행렬
MxM, R - 크기 M x N의 위쪽 삼각형 (또는 위쪽 사다리꼴) 행렬
행렬 R의 원소들은의 주 대각선 위 및 위에 위치한다.
매트릭스 A. 타우 어레이에 위치하고 메인 아래에있는 요소
행렬 A의 대각선은 다음과 같이 행렬 Q를 형성하기 위해 사용됩니다.
행렬 Q는 기본 반사의 곱으로 표현됩니다.
Q = H (0) * H (2) * ... * H (k-1),
여기서, k = min (m, n)이고, 각각의 H (i)는
H (i) = 1 - τ * v * (ν ^ T)
여기서 tau는 Tau [I]에 저장된 스칼라이다. v - 실수 벡터,
A (i + 1 : m-1, i)에 저장된 v (0 : i-1) = 0, v (i) = 1, v (i + 1 : m-
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixqr(real_2d_array &a, const ae_int_t m, const ae_int_t n, real_1d_array &tau);


/*************************************************************************
LQ decomposition of a rectangular matrix of size MxN

Input parameters:
    A   -   matrix A whose indexes range within [0..M-1, 0..N-1].
    M   -   number of rows in matrix A.
    N   -   number of columns in matrix A.

Output parameters:
    A   -   matrices L and Q in compact form (see below)
    Tau -   array of scalar factors which are used to form
            matrix Q. Array whose index ranges within [0..Min(M,N)-1].

Matrix A is represented as A = LQ, where Q is an orthogonal matrix of size
MxM, L - lower triangular (or lower trapezoid) matrix of size M x N.

The elements of matrix L are located on and below  the  main  diagonal  of
matrix A. The elements which are located in Tau array and above  the  main
diagonal of matrix A are used to form matrix Q as follows:

Matrix Q is represented as a product of elementary reflections

Q = H(k-1)*H(k-2)*...*H(1)*H(0),

where k = min(m,n), and each H(i) is of the form

H(i) = 1 - tau * v * (v^T)

where tau is a scalar stored in Tau[I]; v - real vector, so that v(0:i-1)=0,
v(i) = 1, v(i+1:n-1) stored in A(i,i+1:n-1).

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
크기 MxN의 직사각형 행렬의 LQ 분해
입력 매개 변수 :
    A - 인덱스가 [0..M-1, 0..N-1] 범위 인 행렬 A.
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 조밀 한 모양에있는 모체 L와 Q (아래에보십시오)
    Tau - 형성에 사용되는 스칼라 인자의 배열
            행렬 Q. 인덱스가 [0..Min (M, N) -1] 범위에있는 배열.
행렬 A는 A = LQ로 표현되며, 여기서 Q는 크기의 직교 행렬
MxM, L - 크기가 M × N 인 하위 삼각형 (또는 더 낮은 사다리꼴) 행렬
행렬 L의 원소들은의 주 대각선 위 및 아래에 위치한다.
매트릭스 (matrix) A. 타우 (Tau) 배열 및 메인 (main) 위의 요소
행렬 A의 대각선은 다음과 같이 행렬 Q를 형성하기 위해 사용됩니다.
행렬 Q는 기본 반사의 곱으로 표현됩니다.
Q = H (k-1) * H (k-2) * ... * H (1) * H (0),
여기서, k = min (m, n)이고, 각각의 H (i)는
H (i) = 1 - τ * v * (ν ^ T)
여기서 tau는 Tau [I]에 저장된 스칼라이다. v - 실수 벡터이므로, v (0 : i-1) = 0,
A (i, i + 1 : n-1)에 저장된 v (i) = 1, v (i + 1 : n-1)이다.
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixlq(real_2d_array &a, const ae_int_t m, const ae_int_t n, real_1d_array &tau);


/*************************************************************************
QR decomposition of a rectangular complex matrix of size MxN

Input parameters:
    A   -   matrix A whose indexes range within [0..M-1, 0..N-1]
    M   -   number of rows in matrix A.
    N   -   number of columns in matrix A.

Output parameters:
    A   -   matrices Q and R in compact form
    Tau -   array of scalar factors which are used to form matrix Q. Array
            whose indexes range within [0.. Min(M,N)-1]

Matrix A is represented as A = QR, where Q is an orthogonal matrix of size
MxM, R - upper triangular (or upper trapezoid) matrix of size MxN.

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     September 30, 1994
*************************************************************************/

/* ************************************************ *************************
크기 MxN의 직사각형 복렬 행렬의 QR 분해
입력 매개 변수 :
    A - 인덱스가 [0..M-1, 0..N-1] 범위 인 행렬 A
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 컴팩트 형태의 행렬 Q와 R
    Tau - 행렬 Q를 형성하는 데 사용되는 스칼라 인자의 배열
            그의 인덱스 범위는 [0 .. Min (M, N) -1]
행렬 A는 A = QR로 표현되며, Q는 크기의 직교 행렬
MxM, R - MxN 크기의 위쪽 삼각형 (또는 위쪽 사다리꼴) 행렬.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1994 년 9 월 30 일
*************************************************** ********************** */

void cmatrixqr(complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_1d_array &tau);


/*************************************************************************
LQ decomposition of a rectangular complex matrix of size MxN

Input parameters:
    A   -   matrix A whose indexes range within [0..M-1, 0..N-1]
    M   -   number of rows in matrix A.
    N   -   number of columns in matrix A.

Output parameters:
    A   -   matrices Q and L in compact form
    Tau -   array of scalar factors which are used to form matrix Q. Array
            whose indexes range within [0.. Min(M,N)-1]

Matrix A is represented as A = LQ, where Q is an orthogonal matrix of size
MxM, L - lower triangular (or lower trapezoid) matrix of size MxN.

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     September 30, 1994
*************************************************************************/

/* ************************************************ *************************
크기 M × N의 직사각형 복렬 행렬의 LQ 분해
입력 매개 변수 :
    A - 인덱스가 [0..M-1, 0..N-1] 범위 인 행렬 A
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 조밀 한 모양에있는 모체 Q와 L
    Tau - 행렬 Q를 형성하는 데 사용되는 스칼라 인자의 배열
            그의 인덱스 범위는 [0 .. Min (M, N) -1]
행렬 A는 A = LQ로 표현되며, 여기서 Q는 크기의 직교 행렬
MxM, L - 크기가 MxN 인 하위 삼각형 (또는 더 낮은 사다리꼴) 행렬.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1994 년 9 월 30 일
*************************************************** ********************** */

void cmatrixlq(complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_1d_array &tau);


/*************************************************************************
Partial unpacking of matrix Q from the QR decomposition of a matrix A

Input parameters:
    A       -   matrices Q and R in compact form.
                Output of RMatrixQR subroutine.
    M       -   number of rows in given matrix A. M>=0.
    N       -   number of columns in given matrix A. N>=0.
    Tau     -   scalar factors which are used to form Q.
                Output of the RMatrixQR subroutine.
    QColumns -  required number of columns of matrix Q. M>=QColumns>=0.

Output parameters:
    Q       -   first QColumns columns of matrix Q.
                Array whose indexes range within [0..M-1, 0..QColumns-1].
                If QColumns=0, the array remains unchanged.

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A의 QR 분해로부터 행렬 Q의 부분적 언 패킹
입력 매개 변수 :
    A - 행렬 Q와 R은 간결한 형태입니다.
                RMatrixQR 서브 루틴의 출력.
    M - 주어진 행렬의 행 수 A. M> = 0.
    N - 주어진 행렬의 열 개수 A. N> = 0.
    Tau - Q를 형성하는 데 사용되는 스칼라 인자
                RMatrixQR 서브 루틴의 출력.
    QColumns - 행렬 Q의 열 수. M> = QColumns> = 0.
출력 매개 변수 :
    Q - 행렬 Q의 첫 번째 QColumns 열입니다.
                인덱스가 [0..M-1, 0..QColumns-1] 범위에있는 배열.
                QColumns = 0이면 배열은 변경되지 않습니다.
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixqrunpackq(const real_2d_array &a, const ae_int_t m, const ae_int_t n, const real_1d_array &tau, const ae_int_t qcolumns, real_2d_array &q);


/*************************************************************************
Unpacking of matrix R from the QR decomposition of a matrix A

Input parameters:
    A       -   matrices Q and R in compact form.
                Output of RMatrixQR subroutine.
    M       -   number of rows in given matrix A. M>=0.
    N       -   number of columns in given matrix A. N>=0.

Output parameters:
    R       -   matrix R, array[0..M-1, 0..N-1].

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A의 QR 분해로부터 행렬 R의 언 패킹
입력 매개 변수 :
    A - 행렬 Q와 R은 간결한 형태입니다.
                RMatrixQR 서브 루틴의 출력.
    M - 주어진 행렬의 행 수 A. M> = 0.
    N - 주어진 행렬의 열 개수 A. N> = 0.
출력 매개 변수 :
    R- 행렬 R, 어레이 [0..M-1, 0..N-1].
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixqrunpackr(const real_2d_array &a, const ae_int_t m, const ae_int_t n, real_2d_array &r);


/*************************************************************************
Partial unpacking of matrix Q from the LQ decomposition of a matrix A

Input parameters:
    A       -   matrices L and Q in compact form.
                Output of RMatrixLQ subroutine.
    M       -   number of rows in given matrix A. M>=0.
    N       -   number of columns in given matrix A. N>=0.
    Tau     -   scalar factors which are used to form Q.
                Output of the RMatrixLQ subroutine.
    QRows   -   required number of rows in matrix Q. N>=QRows>=0.

Output parameters:
    Q       -   first QRows rows of matrix Q. Array whose indexes range
                within [0..QRows-1, 0..N-1]. If QRows=0, the array remains
                unchanged.

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A의 LQ 분해로부터의 행렬 Q의 부분적 패킹
입력 매개 변수 :
    A - 행렬 L 및 Q는 간결한 형태입니다.
                RMatrixLQ 서브 루틴의 출력.
    M - 주어진 행렬의 행 수 A. M> = 0.
    N - 주어진 행렬의 열 개수 A. N> = 0.
    Tau - Q를 형성하는 데 사용되는 스칼라 인자
                RMatrixLQ 서브 루틴의 출력.
    QRows - 행렬의 필요한 행 수 Q. N> = QRows> = 0.
출력 매개 변수 :
    Q - 첫 번째 Q 행렬의 행을 줄입니다.
                [0..QRows-1, 0..N-1] 이내. QRows = 0이면 배열은 그대로 유지됩니다.
                변하지 않은.
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixlqunpackq(const real_2d_array &a, const ae_int_t m, const ae_int_t n, const real_1d_array &tau, const ae_int_t qrows, real_2d_array &q);


/*************************************************************************
Unpacking of matrix L from the LQ decomposition of a matrix A

Input parameters:
    A       -   matrices Q and L in compact form.
                Output of RMatrixLQ subroutine.
    M       -   number of rows in given matrix A. M>=0.
    N       -   number of columns in given matrix A. N>=0.

Output parameters:
    L       -   matrix L, array[0..M-1, 0..N-1].

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A의 LQ 분해로부터 행렬 L의 언 패킹
입력 매개 변수 :
    A - 행렬 Q와 L은 간결한 형태입니다.
                RMatrixLQ 서브 루틴의 출력.
    M - 주어진 행렬의 행 수 A. M> = 0.
    N - 주어진 행렬의 열 개수 A. N> = 0.
출력 매개 변수 :
    L- 행렬 L, 어레이 [0..M-1, 0..N-1].
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixlqunpackl(const real_2d_array &a, const ae_int_t m, const ae_int_t n, real_2d_array &l);


/*************************************************************************
Partial unpacking of matrix Q from QR decomposition of a complex matrix A.

Input parameters:
    A           -   matrices Q and R in compact form.
                    Output of CMatrixQR subroutine .
    M           -   number of rows in matrix A. M>=0.
    N           -   number of columns in matrix A. N>=0.
    Tau         -   scalar factors which are used to form Q.
                    Output of CMatrixQR subroutine .
    QColumns    -   required number of columns in matrix Q. M>=QColumns>=0.

Output parameters:
    Q           -   first QColumns columns of matrix Q.
                    Array whose index ranges within [0..M-1, 0..QColumns-1].
                    If QColumns=0, array isn't changed.

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
복소수 행렬의 QR 분해로부터 행렬 Q를 부분적으로 푸는 것.
입력 매개 변수 :
    A - 행렬 Q와 R은 간결한 형태입니다.
                    CMatrixQR 서브 루틴 출력.
    M - 행렬 A의 행 수. M> = 0.
    N - 행렬 A의 열 수입니다. N> = 0입니다.
    Tau - Q를 형성하는 데 사용되는 스칼라 인자
                    CMatrixQR 서브 루틴 출력.
    QColumns - 행렬 Q에 필요한 열의 수. M> = QColumns> = 0.
출력 매개 변수 :
    Q - 행렬 Q의 첫 번째 QColumns 열입니다.
                    인덱스 범위가 [0..M-1, 0..QColumns-1] 이내 인 배열.
                    QColumns = 0이면 배열은 변경되지 않습니다.
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */


void cmatrixqrunpackq(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, const complex_1d_array &tau, const ae_int_t qcolumns, complex_2d_array &q);


/*************************************************************************
Unpacking of matrix R from the QR decomposition of a matrix A

Input parameters:
    A       -   matrices Q and R in compact form.
                Output of CMatrixQR subroutine.
    M       -   number of rows in given matrix A. M>=0.
    N       -   number of columns in given matrix A. N>=0.

Output parameters:
    R       -   matrix R, array[0..M-1, 0..N-1].

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A의 QR 분해로부터 행렬 R의 언 패킹
입력 매개 변수 :
    A - 행렬 Q와 R은 간결한 형태입니다.
                CMatrixQR 서브 루틴 출력.
    M - 주어진 행렬의 행 수 A. M> = 0.
    N - 주어진 행렬의 열 개수 A. N> = 0.
출력 매개 변수 :
    R- 행렬 R, 어레이 [0..M-1, 0..N-1].
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixqrunpackr(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_2d_array &r);


/*************************************************************************
Partial unpacking of matrix Q from LQ decomposition of a complex matrix A.

Input parameters:
    A           -   matrices Q and R in compact form.
                    Output of CMatrixLQ subroutine .
    M           -   number of rows in matrix A. M>=0.
    N           -   number of columns in matrix A. N>=0.
    Tau         -   scalar factors which are used to form Q.
                    Output of CMatrixLQ subroutine .
    QRows       -   required number of rows in matrix Q. N>=QColumns>=0.

Output parameters:
    Q           -   first QRows rows of matrix Q.
                    Array whose index ranges within [0..QRows-1, 0..N-1].
                    If QRows=0, array isn't changed.

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
복소수 행렬의 LQ 분해로부터 행렬 Q를 부분적으로 푸는 것.
입력 매개 변수 :
    A - 행렬 Q와 R은 간결한 형태입니다.
                    CMatrixLQ 서브 루틴의 출력.
    M - 행렬 A의 행 수. M> = 0.
    N - 행렬 A의 열 수입니다. N> = 0입니다.
    Tau - Q를 형성하는 데 사용되는 스칼라 인자
                    CMatrixLQ 서브 루틴의 출력.
    QRows - 행렬의 필요한 행 수 Q. N> = QColumns> = 0.
출력 매개 변수 :
    Q - 첫 번째 Q 행렬 Q의 행을 표시합니다.
                    인덱스 범위가 [0..QRows-1, 0..N-1] 이내 인 배열
                    QRows = 0이면 배열은 변경되지 않습니다.
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixlqunpackq(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, const complex_1d_array &tau, const ae_int_t qrows, complex_2d_array &q);


/*************************************************************************
Unpacking of matrix L from the LQ decomposition of a matrix A

Input parameters:
    A       -   matrices Q and L in compact form.
                Output of CMatrixLQ subroutine.
    M       -   number of rows in given matrix A. M>=0.
    N       -   number of columns in given matrix A. N>=0.

Output parameters:
    L       -   matrix L, array[0..M-1, 0..N-1].

  -- ALGLIB routine --
     17.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A의 LQ 분해로부터 행렬 L의 언 패킹
입력 매개 변수 :
    A - 행렬 Q와 L은 간결한 형태입니다.
                CMatrixLQ 서브 루틴의 출력.
    M - 주어진 행렬의 행 수 A. M> = 0.
    N - 주어진 행렬의 열 개수 A. N> = 0.
출력 매개 변수 :
    L- 행렬 L, 어레이 [0..M-1, 0..N-1].
  - ALGLIB 루틴 -
     17.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixlqunpackl(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_2d_array &l);


/*************************************************************************
Reduction of a rectangular matrix to  bidiagonal form

The algorithm reduces the rectangular matrix A to  bidiagonal form by
orthogonal transformations P and Q: A = Q*B*P.

Input parameters:
    A       -   source matrix. array[0..M-1, 0..N-1]
    M       -   number of rows in matrix A.
    N       -   number of columns in matrix A.

Output parameters:
    A       -   matrices Q, B, P in compact form (see below).
    TauQ    -   scalar factors which are used to form matrix Q.
    TauP    -   scalar factors which are used to form matrix P.

The main diagonal and one of the  secondary  diagonals  of  matrix  A  are
replaced with bidiagonal  matrix  B.  Other  elements  contain  elementary
reflections which form MxM matrix Q and NxN matrix P, respectively.

If M>=N, B is the upper  bidiagonal  MxN  matrix  and  is  stored  in  the
corresponding  elements  of  matrix  A.  Matrix  Q  is  represented  as  a
product   of   elementary   reflections   Q = H(0)*H(1)*...*H(n-1),  where
H(i) = 1-tau*v*v'. Here tau is a scalar which is stored  in  TauQ[i],  and
vector v has the following  structure:  v(0:i-1)=0, v(i)=1, v(i+1:m-1)  is
stored   in   elements   A(i+1:m-1,i).   Matrix   P  is  as  follows:  P =
G(0)*G(1)*...*G(n-2), where G(i) = 1 - tau*u*u'. Tau is stored in TauP[i],
u(0:i)=0, u(i+1)=1, u(i+2:n-1) is stored in elements A(i,i+2:n-1).

If M<N, B is the  lower  bidiagonal  MxN  matrix  and  is  stored  in  the
corresponding   elements  of  matrix  A.  Q = H(0)*H(1)*...*H(m-2),  where
H(i) = 1 - tau*v*v', tau is stored in TauQ, v(0:i)=0, v(i+1)=1, v(i+2:m-1)
is    stored    in   elements   A(i+2:m-1,i).    P = G(0)*G(1)*...*G(m-1),
G(i) = 1-tau*u*u', tau is stored in  TauP,  u(0:i-1)=0, u(i)=1, u(i+1:n-1)
is stored in A(i,i+1:n-1).

EXAMPLE:

m=6, n=5 (m > n):               m=5, n=6 (m < n):

(  d   e   u1  u1  u1 )         (  d   u1  u1  u1  u1  u1 )
(  v1  d   e   u2  u2 )         (  e   d   u2  u2  u2  u2 )
(  v1  v2  d   e   u3 )         (  v1  e   d   u3  u3  u3 )
(  v1  v2  v3  d   e  )         (  v1  v2  e   d   u4  u4 )
(  v1  v2  v3  v4  d  )         (  v1  v2  v3  e   d   u5 )
(  v1  v2  v3  v4  v5 )

Here vi and ui are vectors which form H(i) and G(i), and d and e -
are the diagonal and off-diagonal elements of matrix B.

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     September 30, 1994.
     Sergey Bochkanov, ALGLIB project, translation from FORTRAN to
     pseudocode, 2007-2010.
*************************************************************************/

/* ************************************************ *************************
직사각형 행렬을 이중 대각선 형태로 축소
이 알고리즘은 직사각형 행렬 A를
직교 변환 P 및 Q : A = Q * B * P.
입력 매개 변수 :
    A - 소스 행렬. 어레이 [0..M-1, 0..N-1]
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 행렬 Q, B, P를 콤팩트 형식으로 만듭니다 (아래 참조).
    TauQ - 매트릭스 Q를 형성하는 데 사용되는 스칼라 인자
    TauP - 행렬 P를 형성하기 위해 사용되는 스칼라 인자.
행렬 A의 주 대각선 및 보조 대각선 중 하나는 다음과 같습니다.
쌍대 행렬 B로 대체됩니다. 다른 요소에는 초등
반사는 각각 MxM 행렬 Q 및 NxN 행렬 P를 형성한다.
M> = N 인 경우 B는 상위 2 중 MxN 행렬이며
행렬 A의 대응하는 요소. 행렬 Q는
기본 반사의 곱 Q = H (0) * H (1) * ... * H (n-1), 여기서
H (i) = 1-tau * v * v '. 여기에서 tau는 TauQ [i]에 저장되는 스칼라이고
벡터 v는 다음 구조를 갖는다 : v (0 : i-1) = 0, v (i) = 1, v (i + 1 : m-1) is
요소 A (i + 1 : m-1, i)에 저장된다. 행렬 P는 다음과 같습니다. P =
G (i) = 1 - τ * u * u '인 G (0) * G (1) * ... * G (n-2) Tau는 TauP [i]에 저장된다.
1, u (i + 2 : n-1)은 요소 A (i, i + 2 : n-1)에 저장된다.
M <N 인 경우, B는 더 낮은 쌍 대각 M × N 행렬이고
Q = H (0) * H (1) * ... * H (m-2) 여기서,
tau는 TauQ에 저장되고, v (0 : i) = 0, v (i + 1) = 1, v (i + 2 : m-1)
요소 A (i + 2 : m-1, i)에 저장된다. P = G (0) * G (1) * ... * G (m-1),
tau는 TauP에 저장되고, u (0 : i-1) = 0, u (i) = 1, u (i + 1 : n-1)
A (i, i + 1 : n-1)에 저장된다.
예:
m = 6, n = 5 (m> n) : m = 5, n = 6 (m <n) :
(u1 u1 u1) (u1 u1 u1 u1 u1)
(v1 de u2 u2) (ed u2 u2 u2 u2)
(v1 v2 de u3) (v1 ed u3 u3 u3)
(v1 v2 v3 de) (v1 v2 ed u4 u4)
(v1 v2 v3 v4 d) (v1 v2 v3 ed u5)
(v1 v2 v3 v4 v5)
여기서 vi와 ui는 H (i)와 G (i)를 형성하는 벡터이고, d와 e -
행렬 B의 대각선 및 대각선 요소입니다.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1994 년 9 월 30 일
     Sergey Bochkanov, ALGLIB 프로젝트, FORTRAN에서 번역까지
     의사 코드 2007-2010.
*************************************************** ********************** */

void rmatrixbd(real_2d_array &a, const ae_int_t m, const ae_int_t n, real_1d_array &tauq, real_1d_array &taup);


/*************************************************************************
Unpacking matrix Q which reduces a matrix to bidiagonal form.

Input parameters:
    QP          -   matrices Q and P in compact form.
                    Output of ToBidiagonal subroutine.
    M           -   number of rows in matrix A.
    N           -   number of columns in matrix A.
    TAUQ        -   scalar factors which are used to form Q.
                    Output of ToBidiagonal subroutine.
    QColumns    -   required number of columns in matrix Q.
                    M>=QColumns>=0.

Output parameters:
    Q           -   first QColumns columns of matrix Q.
                    Array[0..M-1, 0..QColumns-1]
                    If QColumns=0, the array is not modified.

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/
void rmatrixbdunpackq(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &tauq, const ae_int_t qcolumns, real_2d_array &q);


/*************************************************************************
Multiplication by matrix Q which reduces matrix A to  bidiagonal form.

The algorithm allows pre- or post-multiply by Q or Q'.

Input parameters:
    QP          -   matrices Q and P in compact form.
                    Output of ToBidiagonal subroutine.
    M           -   number of rows in matrix A.
    N           -   number of columns in matrix A.
    TAUQ        -   scalar factors which are used to form Q.
                    Output of ToBidiagonal subroutine.
    Z           -   multiplied matrix.
                    array[0..ZRows-1,0..ZColumns-1]
    ZRows       -   number of rows in matrix Z. If FromTheRight=False,
                    ZRows=M, otherwise ZRows can be arbitrary.
    ZColumns    -   number of columns in matrix Z. If FromTheRight=True,
                    ZColumns=M, otherwise ZColumns can be arbitrary.
    FromTheRight -  pre- or post-multiply.
    DoTranspose -   multiply by Q or Q'.

Output parameters:
    Z           -   product of Z and Q.
                    Array[0..ZRows-1,0..ZColumns-1]
                    If ZRows=0 or ZColumns=0, the array is not modified.

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬을 이중 대각선 형태로 줄이는 행렬 Q를 푸는 것.
입력 매개 변수 :
    QP - 행렬 Q와 P가 간결한 형태로 나타납니다.
                    ToBidiagonal 서브 루틴의 출력.
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
    TAUQ - Q를 형성하는 데 사용되는 스칼라 팩터
                    ToBidiagonal 서브 루틴의 출력.
    QColumns - 행렬 Q에 필요한 열 수
                    M> = QColumns> = 0이다.
출력 매개 변수 :
    Q - 행렬 Q의 첫 번째 QColumns 열입니다.
                    배열 [0..M-1, 0..QColumns-1]
                    QColumns = 0이면 배열은 수정되지 않습니다.
  - ALGLIB -
     2005-2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixbdmultiplybyq(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &tauq, real_2d_array &z, const ae_int_t zrows, const ae_int_t zcolumns, const bool fromtheright, const bool dotranspose);


/*************************************************************************
Unpacking matrix P which reduces matrix A to bidiagonal form.
The subroutine returns transposed matrix P.

Input parameters:
    QP      -   matrices Q and P in compact form.
                Output of ToBidiagonal subroutine.
    M       -   number of rows in matrix A.
    N       -   number of columns in matrix A.
    TAUP    -   scalar factors which are used to form P.
                Output of ToBidiagonal subroutine.
    PTRows  -   required number of rows of matrix P^T. N >= PTRows >= 0.

Output parameters:
    PT      -   first PTRows columns of matrix P^T
                Array[0..PTRows-1, 0..N-1]
                If PTRows=0, the array is not modified.

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A를 양 대각선 형태로 감소시키는 행렬 Q에 의한 승산.
이 알고리즘은 Q 또는 Q '로 전 또는 후 곱셈을 허용합니다.
입력 매개 변수 :
    QP - 행렬 Q와 P가 간결한 형태로 나타납니다.
                    ToBidiagonal 서브 루틴의 출력.
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
    TAUQ - Q를 형성하는 데 사용되는 스칼라 팩터
                    ToBidiagonal 서브 루틴의 출력.
    Z - 곱해진 행렬.
                    배열 [0..ZRows-1.0..ZColumns-1]
    ZRows - 행렬 Z의 행 수입니다. FromTheRight = False 인 경우,
                    ZRows = M, 그렇지 않으면 ZRows는 임의적 일 수 있습니다.
    ZColumns - 행렬 Z의 열 수입니다. FromTheRight = True 인 경우,
                    ZColumns = M, 그렇지 않으면 ZColumns는 임의적 일 수 있습니다.
    FromTheRight - 사전 또는 사후 곱하기.
    DoTranspose - Q 또는 Q '를 곱하십시오.
출력 매개 변수 :
    Z - Z와 Q의 곱
                    배열 [0..ZRows-1.0..ZColumns-1]
                    ZRows = 0 또는 ZColumns = 0 인 경우 배열은 수정되지 않습니다.
  - ALGLIB -
     2005-2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixbdunpackpt(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &taup, const ae_int_t ptrows, real_2d_array &pt);


/*************************************************************************
Multiplication by matrix P which reduces matrix A to  bidiagonal form.

The algorithm allows pre- or post-multiply by P or P'.

Input parameters:
    QP          -   matrices Q and P in compact form.
                    Output of RMatrixBD subroutine.
    M           -   number of rows in matrix A.
    N           -   number of columns in matrix A.
    TAUP        -   scalar factors which are used to form P.
                    Output of RMatrixBD subroutine.
    Z           -   multiplied matrix.
                    Array whose indexes range within [0..ZRows-1,0..ZColumns-1].
    ZRows       -   number of rows in matrix Z. If FromTheRight=False,
                    ZRows=N, otherwise ZRows can be arbitrary.
    ZColumns    -   number of columns in matrix Z. If FromTheRight=True,
                    ZColumns=N, otherwise ZColumns can be arbitrary.
    FromTheRight -  pre- or post-multiply.
    DoTranspose -   multiply by P or P'.

Output parameters:
    Z - product of Z and P.
                Array whose indexes range within [0..ZRows-1,0..ZColumns-1].
                If ZRows=0 or ZColumns=0, the array is not modified.

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A를 이중 대각선 형태로 축소하는 행렬 P를 언 패킹합니다.
서브 루틴은 전치 행렬 P를 반환합니다.
입력 매개 변수 :
    QP - 행렬 Q와 P가 간결한 형태로 나타납니다.
                ToBidiagonal 서브 루틴의 출력.
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
    TAUP - P를 형성하는 데 사용되는 스칼라 팩터
                ToBidiagonal 서브 루틴의 출력.
    PTRows - 행렬 P ^ T의 필요한 행 수입니다. N> = PTRows> = 0.
출력 매개 변수 :
    PT - 행렬 P ^ T의 첫 번째 열
                배열 [0..PTRows-1, 0..N-1]
                PTRows = 0이면 배열이 수정되지 않습니다.
  - ALGLIB -
     2005-2010
     보흐 카 노브 세르게이
*************************************************** ********************** */


void rmatrixbdmultiplybyp(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &taup, real_2d_array &z, const ae_int_t zrows, const ae_int_t zcolumns, const bool fromtheright, const bool dotranspose);


/*************************************************************************
Unpacking of the main and secondary diagonals of bidiagonal decomposition
of matrix A.

Input parameters:
    B   -   output of RMatrixBD subroutine.
    M   -   number of rows in matrix B.
    N   -   number of columns in matrix B.

Output parameters:
    IsUpper -   True, if the matrix is upper bidiagonal.
                otherwise IsUpper is False.
    D       -   the main diagonal.
                Array whose index ranges within [0..Min(M,N)-1].
    E       -   the secondary diagonal (upper or lower, depending on
                the value of IsUpper).
                Array index ranges within [0..Min(M,N)-1], the last
                element is not used.

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이중 대각선 분해의 주요 및 2 차 대각선의 포장 풀기
행렬 A의
입력 매개 변수 :
    B - RMatrixBD 서브 루틴의 출력.
    M - 행렬 B의 행 수
    N - 행렬 B의 열 수입니다.
출력 매개 변수 :
    IsUpper - 행렬이 위쪽 양 대각선이면 참입니다.
                그렇지 않으면 IsUpper가 False입니다.
    D - 주 대각선.
                인덱스가 [0..Min (M, N) -1]의 범위에있는 배열.
    E - 2 차 대각선 (위 또는 아래,
                IsUpper의 값).
                배열 인덱스 범위는 [0..Min (M, N) -1], 마지막
                요소가 사용되지 않습니다.
  - ALGLIB -
     2005-2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixbdunpackdiagonals(const real_2d_array &b, const ae_int_t m, const ae_int_t n, bool &isupper, real_1d_array &d, real_1d_array &e);


/*************************************************************************
Reduction of a square matrix to  upper Hessenberg form: Q'*A*Q = H,
where Q is an orthogonal matrix, H - Hessenberg matrix.

Input parameters:
    A       -   matrix A with elements [0..N-1, 0..N-1]
    N       -   size of matrix A.

Output parameters:
    A       -   matrices Q and P in  compact form (see below).
    Tau     -   array of scalar factors which are used to form matrix Q.
                Array whose index ranges within [0..N-2]

Matrix H is located on the main diagonal, on the lower secondary  diagonal
and above the main diagonal of matrix A. The elements which are used to
form matrix Q are situated in array Tau and below the lower secondary
diagonal of matrix A as follows:

Matrix Q is represented as a product of elementary reflections

Q = H(0)*H(2)*...*H(n-2),

where each H(i) is given by

H(i) = 1 - tau * v * (v^T)

where tau is a scalar stored in Tau[I]; v - is a real vector,
so that v(0:i) = 0, v(i+1) = 1, v(i+2:n-1) stored in A(i+2:n-1,i).

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     October 31, 1992
*************************************************************************/

/* ************************************************ *************************
Hessenberg 형태의 정사각형 행렬의 감소 : Q '* A * Q = H,
Q는 직교 행렬, H - Hessenberg 행렬이다.
입력 매개 변수 :
    A - 원소 [0..N-1, 0..N-1]을 갖는 행렬 A
    행렬 A의 N 크기
출력 매개 변수 :
    A - 작은 형태의 행렬 Q와 P (아래 참조).
    Tau - 행렬 Q를 형성하기 위해 사용되는 스칼라 인자의 배열.
                인덱스 범위가 [0..N-2]
행렬 H는 주 대각선 상, 하부의 2 차 대각선 상에 위치한다
행렬 A의 주 대각선 위에 위치합니다.
형태 매트릭스 Q는 배열 Tau에 ​​위치하고 하위 2 차
다음과 같이 행렬 A의 대각선 :
행렬 Q는 기본 반사의 곱으로 표현됩니다.
Q = H (0) * H (2) * ... * H (n-2),
여기서 각 H (i)는
H (i) = 1 - τ * v * (ν ^ T)
여기서 tau는 Tau [I]에 저장된 스칼라이다. v -는 실수 벡터이며,
A (i + 2 : n-1, i)에 저장된 v (0 : i) = 0, v (i + 1) = 1, v (i + 2 : n-1)
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1992 년 10 월 31 일
*************************************************** ********************** */


void rmatrixhessenberg(real_2d_array &a, const ae_int_t n, real_1d_array &tau);


/*************************************************************************
Unpacking matrix Q which reduces matrix A to upper Hessenberg form

Input parameters:
    A   -   output of RMatrixHessenberg subroutine.
    N   -   size of matrix A.
    Tau -   scalar factors which are used to form Q.
            Output of RMatrixHessenberg subroutine.

Output parameters:
    Q   -   matrix Q.
            Array whose indexes range within [0..N-1, 0..N-1].

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 A를 위쪽 Hessenberg 형식으로 줄이는 행렬 Q를 언 패킹합니다.
입력 매개 변수 :
    A - RMatrixHessenberg 서브 루틴의 출력.
    행렬 A의 N 크기
    Tau - Q를 형성하는 데 사용되는 스칼라 인자
            RMatrixHessenberg 서브 루틴의 출력.
출력 매개 변수 :
    Q- 매트릭스 Q.
            인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
  - ALGLIB -
     2005-2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixhessenbergunpackq(const real_2d_array &a, const ae_int_t n, const real_1d_array &tau, real_2d_array &q);


/*************************************************************************
Unpacking matrix H (the result of matrix A reduction to upper Hessenberg form)

Input parameters:
    A   -   output of RMatrixHessenberg subroutine.
    N   -   size of matrix A.

Output parameters:
    H   -   matrix H. Array whose indexes range within [0..N-1, 0..N-1].

  -- ALGLIB --
     2005-2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 H를 풀면 (Hessenberg 형식의 행렬 A 감소 결과)
입력 매개 변수 :
    A - RMatrixHessenberg 서브 루틴의 출력.
    행렬 A의 N 크기
출력 매개 변수 :
    H- 행렬 H. 인덱스가 [0..N-1, 0..N-1] 범위에있는 배열.
  - ALGLIB -
     2005-2010
     보흐 카 노브 세르게이
*************************************************** **********************/

void rmatrixhessenbergunpackh(const real_2d_array &a, const ae_int_t n, real_2d_array &h);


/*************************************************************************
Reduction of a symmetric matrix which is given by its higher or lower
triangular part to a tridiagonal matrix using orthogonal similarity
transformation: Q'*A*Q=T.

Input parameters:
    A       -   matrix to be transformed
                array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   storage format. If IsUpper = True, then matrix A is given
                by its upper triangle, and the lower triangle is not used
                and not modified by the algorithm, and vice versa
                if IsUpper = False.

Output parameters:
    A       -   matrices T and Q in  compact form (see lower)
    Tau     -   array of factors which are forming matrices H(i)
                array with elements [0..N-2].
    D       -   main diagonal of symmetric matrix T.
                array with elements [0..N-1].
    E       -   secondary diagonal of symmetric matrix T.
                array with elements [0..N-2].


  If IsUpper=True, the matrix Q is represented as a product of elementary
  reflectors

     Q = H(n-2) . . . H(2) H(0).

  Each H(i) has the form

     H(i) = I - tau * v * v'

  where tau is a real scalar, and v is a real vector with
  v(i+1:n-1) = 0, v(i) = 1, v(0:i-1) is stored on exit in
  A(0:i-1,i+1), and tau in TAU(i).

  If IsUpper=False, the matrix Q is represented as a product of elementary
  reflectors

     Q = H(0) H(2) . . . H(n-2).

  Each H(i) has the form

     H(i) = I - tau * v * v'

  where tau is a real scalar, and v is a real vector with
  v(0:i) = 0, v(i+1) = 1, v(i+2:n-1) is stored on exit in A(i+2:n-1,i),
  and tau in TAU(i).

  The contents of A on exit are illustrated by the following examples
  with n = 5:

  if UPLO = 'U':                       if UPLO = 'L':

    (  d   e   v1  v2  v3 )              (  d                  )
    (      d   e   v2  v3 )              (  e   d              )
    (          d   e   v3 )              (  v0  e   d          )
    (              d   e  )              (  v0  v1  e   d      )
    (                  d  )              (  v0  v1  v2  e   d  )

  where d and e denote diagonal and off-diagonal elements of T, and vi
  denotes an element of the vector defining H(i).

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     October 31, 1992
*************************************************************************/

/* ************************************************ *************************
대칭 행렬의 상한 또는 하한에 의한 환원
직교 유사성을 이용한 삼각 부분 대 삼중 대각 행렬
변환 : Q '* A * Q = T.
입력 매개 변수 :
    A - 변환 대상의 행렬
                요소들 [0..N-1, 0..N-1]을 갖는 배열.
    행렬 A의 N 크기
    IsUpper - 저장소 형식입니다. IsUpper = True이면 행렬 A가 주어집니다.
                그것의 위 삼각형에 의해, 아래 삼각형은 사용되지 않는다.
                알고리즘에 의해 수정되지 않으며, 그 반대의 경우도 마찬가지입니다.
                IsUpper = False 인 경우.
출력 매개 변수 :
    A - 작은 형태의 행렬 T와 Q (아래 참조)
    Tau - 행렬 H (i)를 형성하는 인자들의 배열
                배열 요소 [0..N-2].
    D - 대칭 행렬 T의 주요 대각선.
                배열 요소 [0..N-1].
    E - 대칭 행렬 T의 2 차 대각
                배열 요소 [0..N-2].
  IsUpper = True이면 행렬 Q는 초등의 곱으로 표현됩니다.
  반사경
     Q = H (n-2). . . H (2) H (0).
  각각의 H (i)는
     H (i) = I - τ * v * v '
  여기서 tau는 실수 스칼라이고, v는
  v (i + 1 : n-1) = 0, v (i) = 1, v (0 : i-
  TAU (i)의 A (0 : i-1, i + 1) 및 tau.
  IsUpper = False이면 행렬 Q는 초등의 곱으로 표현됩니다.
  반사경
     Q = H (0) H (2). . . H (n-2)이다.
  각각의 H (i)는
     H (i) = I - τ * v * v '
  여기서 tau는 실수 스칼라이고, v는
  v (i + 2 : n-1)은 A (i + 2 : n-1, i)의 출구에 저장되고, v (0 : i)
  및 TAU (i)의 타우.
  이탈시 A의 내용은 다음 예제로 설명됩니다.
  n = 5 인 경우 :
  UPLO = 'U'인 경우 : UPLO = 'L'인 경우 :
    (v1 v2 v3) (d)
    (de v2 v3) (ed)
    (de v3) (v0 ed)
    (de) (v0 v1 ed)
    (d) (v0 v1 v2 ed)
  여기서 d와 e는 T의 대각선과 비대 각 요소를 나타내고, vi
  는 H (i)를 정의하는 벡터의 원소를 나타낸다.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1992 년 10 월 31 일
*************************************************** ********************** */

void smatrixtd(real_2d_array &a, const ae_int_t n, const bool isupper, real_1d_array &tau, real_1d_array &d, real_1d_array &e);


/*************************************************************************
Unpacking matrix Q which reduces symmetric matrix to a tridiagonal
form.

Input parameters:
    A       -   the result of a SMatrixTD subroutine
    N       -   size of matrix A.
    IsUpper -   storage format (a parameter of SMatrixTD subroutine)
    Tau     -   the result of a SMatrixTD subroutine

Output parameters:
    Q       -   transformation matrix.
                array with elements [0..N-1, 0..N-1].

  -- ALGLIB --
     Copyright 2005-2010 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭 행렬을 삼각형으로 줄이는 행렬 Q를 풀기
형태.
입력 매개 변수 :
    A - SMatrixTD 서브 루틴의 결과
    행렬 A의 N 크기
    IsUpper - 저장 형식 (SMatrixTD 서브 루틴의 매개 변수)
    Tau - SMatrixTD 서브 루틴의 결과
출력 매개 변수 :
    Q - 변환 행렬.
                요소들 [0..N-1, 0..N-1]을 갖는 배열.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2010
*************************************************** ********************** */

void smatrixtdunpackq(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_1d_array &tau, real_2d_array &q);


/*************************************************************************
Reduction of a Hermitian matrix which is given  by  its  higher  or  lower
triangular part to a real  tridiagonal  matrix  using  unitary  similarity
transformation: Q'*A*Q = T.

Input parameters:
    A       -   matrix to be transformed
                array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   storage format. If IsUpper = True, then matrix A is  given
                by its upper triangle, and the lower triangle is not  used
                and not modified by the algorithm, and vice versa
                if IsUpper = False.

Output parameters:
    A       -   matrices T and Q in  compact form (see lower)
    Tau     -   array of factors which are forming matrices H(i)
                array with elements [0..N-2].
    D       -   main diagonal of real symmetric matrix T.
                array with elements [0..N-1].
    E       -   secondary diagonal of real symmetric matrix T.
                array with elements [0..N-2].


  If IsUpper=True, the matrix Q is represented as a product of elementary
  reflectors

     Q = H(n-2) . . . H(2) H(0).

  Each H(i) has the form

     H(i) = I - tau * v * v'

  where tau is a complex scalar, and v is a complex vector with
  v(i+1:n-1) = 0, v(i) = 1, v(0:i-1) is stored on exit in
  A(0:i-1,i+1), and tau in TAU(i).

  If IsUpper=False, the matrix Q is represented as a product of elementary
  reflectors

     Q = H(0) H(2) . . . H(n-2).

  Each H(i) has the form

     H(i) = I - tau * v * v'

  where tau is a complex scalar, and v is a complex vector with
  v(0:i) = 0, v(i+1) = 1, v(i+2:n-1) is stored on exit in A(i+2:n-1,i),
  and tau in TAU(i).

  The contents of A on exit are illustrated by the following examples
  with n = 5:

  if UPLO = 'U':                       if UPLO = 'L':

    (  d   e   v1  v2  v3 )              (  d                  )
    (      d   e   v2  v3 )              (  e   d              )
    (          d   e   v3 )              (  v0  e   d          )
    (              d   e  )              (  v0  v1  e   d      )
    (                  d  )              (  v0  v1  v2  e   d  )

where d and e denote diagonal and off-diagonal elements of T, and vi
denotes an element of the vector defining H(i).

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     October 31, 1992
*************************************************************************/

/* ************************************************ *************************
대칭 행렬의 상한 또는 하한에 의한 환원
직교 유사성을 이용한 삼각 부분 대 삼중 대각 행렬
변환 : Q '* A * Q = T.
입력 매개 변수 :
    A - 변환 대상의 행렬
                요소들 [0..N-1, 0..N-1]을 갖는 배열.
    행렬 A의 N 크기
    IsUpper - 저장소 형식입니다. IsUpper = True이면 행렬 A가 주어집니다.
                그것의 위 삼각형에 의해, 아래 삼각형은 사용되지 않는다.
                알고리즘에 의해 수정되지 않으며, 그 반대의 경우도 마찬가지입니다.
                IsUpper = False 인 경우.
출력 매개 변수 :
    A - 작은 형태의 행렬 T와 Q (아래 참조)
    Tau - 행렬 H (i)를 형성하는 인자들의 배열
                배열 요소 [0..N-2].
    D - 대칭 행렬 T의 주요 대각선.
                배열 요소 [0..N-1].
    E - 대칭 행렬 T의 2 차 대각
                배열 요소 [0..N-2].
  IsUpper = True이면 행렬 Q는 초등의 곱으로 표현됩니다.
  반사경
     Q = H (n-2). . . H (2) H (0).
  각각의 H (i)는
     H (i) = I - τ * v * v '
  여기서 tau는 실수 스칼라이고, v는
  v (i + 1 : n-1) = 0, v (i) = 1, v (0 : i-
  TAU (i)의 A (0 : i-1, i + 1) 및 tau.
  IsUpper = False이면 행렬 Q는 초등의 곱으로 표현됩니다.
  반사경
     Q = H (0) H (2). . . H (n-2)이다.
  각각의 H (i)는
     H (i) = I - τ * v * v '
  여기서 tau는 실수 스칼라이고, v는
  v (i + 2 : n-1)은 A (i + 2 : n-1, i)의 출구에 저장되고, v (0 : i)
  및 TAU (i)의 타우.
  이탈시 A의 내용은 다음 예제로 설명됩니다.
  n = 5 인 경우 :
  

  if UPLO = 'U':                       if UPLO = 'L':

    (  d   e   v1  v2  v3 )              (  d                  )
    (      d   e   v2  v3 )              (  e   d              )

    (          d   e   v3 )              (  v0  e   d          )
    (              d   e  )              (  v0  v1  e   d      )
    (                  d  )              (  v0  v1  v2  e   d  )



  여기서 d와 e는 T의 대각선과 비대 각 요소를 나타내고, vi
  는 H (i)를 정의하는 벡터의 원소를 나타낸다.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1992 년 10 월 31 일
*************************************************** ********************** */

void hmatrixtd(complex_2d_array &a, const ae_int_t n, const bool isupper, complex_1d_array &tau, real_1d_array &d, real_1d_array &e);


/*************************************************************************
Unpacking matrix Q which reduces a Hermitian matrix to a real  tridiagonal
form.

Input parameters:
    A       -   the result of a HMatrixTD subroutine
    N       -   size of matrix A.
    IsUpper -   storage format (a parameter of HMatrixTD subroutine)
    Tau     -   the result of a HMatrixTD subroutine

Output parameters:
    Q       -   transformation matrix.
                array with elements [0..N-1, 0..N-1].

  -- ALGLIB --
     Copyright 2005-2010 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭 행렬을 삼각형으로 줄이는 행렬 Q를 풀기
형태.
입력 매개 변수 :
    A - SMatrixTD 서브 루틴의 결과
    행렬 A의 N 크기
    IsUpper - 저장 형식 (SMatrixTD 서브 루틴의 매개 변수)
    Tau - SMatrixTD 서브 루틴의 결과
출력 매개 변수 :
    Q - 변환 행렬.
                요소들 [0..N-1, 0..N-1]을 갖는 배열.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2010
*************************************************** ********************** */

void hmatrixtdunpackq(const complex_2d_array &a, const ae_int_t n, const bool isupper, const complex_1d_array &tau, complex_2d_array &q);

/*************************************************************************
Singular value decomposition of a bidiagonal matrix (extended algorithm)

The algorithm performs the singular value decomposition  of  a  bidiagonal
matrix B (upper or lower) representing it as B = Q*S*P^T, where Q and  P -
orthogonal matrices, S - diagonal matrix with non-negative elements on the
main diagonal, in descending order.

The  algorithm  finds  singular  values.  In  addition,  the algorithm can
calculate  matrices  Q  and P (more precisely, not the matrices, but their
product  with  given  matrices U and VT - U*Q and (P^T)*VT)).  Of  course,
matrices U and VT can be of any type, including identity. Furthermore, the
algorithm can calculate Q'*C (this product is calculated more  effectively
than U*Q,  because  this calculation operates with rows instead  of matrix
columns).

The feature of the algorithm is its ability to find  all  singular  values
including those which are arbitrarily close to 0  with  relative  accuracy
close to  machine precision. If the parameter IsFractionalAccuracyRequired
is set to True, all singular values will have high relative accuracy close
to machine precision. If the parameter is set to False, only  the  biggest
singular value will have relative accuracy  close  to  machine  precision.
The absolute error of other singular values is equal to the absolute error
of the biggest singular value.

Input parameters:
    D       -   main diagonal of matrix B.
                Array whose index ranges within [0..N-1].
    E       -   superdiagonal (or subdiagonal) of matrix B.
                Array whose index ranges within [0..N-2].
    N       -   size of matrix B.
    IsUpper -   True, if the matrix is upper bidiagonal.
    IsFractionalAccuracyRequired -
                THIS PARAMETER IS IGNORED SINCE ALGLIB 3.5.0
                SINGULAR VALUES ARE ALWAYS SEARCHED WITH HIGH ACCURACY.
    U       -   matrix to be multiplied by Q.
                Array whose indexes range within [0..NRU-1, 0..N-1].
                The matrix can be bigger, in that case only the  submatrix
                [0..NRU-1, 0..N-1] will be multiplied by Q.
    NRU     -   number of rows in matrix U.
    C       -   matrix to be multiplied by Q'.
                Array whose indexes range within [0..N-1, 0..NCC-1].
                The matrix can be bigger, in that case only the  submatrix
                [0..N-1, 0..NCC-1] will be multiplied by Q'.
    NCC     -   number of columns in matrix C.
    VT      -   matrix to be multiplied by P^T.
                Array whose indexes range within [0..N-1, 0..NCVT-1].
                The matrix can be bigger, in that case only the  submatrix
                [0..N-1, 0..NCVT-1] will be multiplied by P^T.
    NCVT    -   number of columns in matrix VT.

Output parameters:
    D       -   singular values of matrix B in descending order.
    U       -   if NRU>0, contains matrix U*Q.
    VT      -   if NCVT>0, contains matrix (P^T)*VT.
    C       -   if NCC>0, contains matrix Q'*C.

Result:
    True, if the algorithm has converged.
    False, if the algorithm hasn't converged (rare case).

Additional information:
    The type of convergence is controlled by the internal  parameter  TOL.
    If the parameter is greater than 0, the singular values will have
    relative accuracy TOL. If TOL<0, the singular values will have
    absolute accuracy ABS(TOL)*norm(B).
    By default, |TOL| falls within the range of 10*Epsilon and 100*Epsilon,
    where Epsilon is the machine precision. It is not  recommended  to  use
    TOL less than 10*Epsilon since this will  considerably  slow  down  the
    algorithm and may not lead to error decreasing.
History:
    * 31 March, 2007.
        changed MAXITR from 6 to 12.

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     October 31, 1999.
*************************************************************************/

/* ************************************************ *************************
이중 대각 행렬의 특이 값 분해 (확장 알고리즘)
이 알고리즘은 이중 대각선의 특이 값 분해를 수행합니다
B = Q * S * P ^ T로 나타내는 행렬 B (위 또는 아래). Q와 P -
직교 행렬, S - 비 음수 요소가있는 대각 행렬
주 대각선, 내림차순
이 알고리즘은 특이 값을 찾습니다. 또한, 알고리즘은
행렬 Q와 P를 계산합니다 (더 정확하게는 행렬이 아니라
주어진 행렬 U와 VT - U * Q와 (P ^ T) * VT)를 가진 곱이다. 당연하지,
행렬 U 및 VT는 신원을 포함하여 임의의 유형일 수있다. 또한,
알고리즘은 Q '* C를 계산할 수 있습니다 (이 제품은 더 효과적으로 계산됩니다
이 계산은 행렬 대신 행을 사용하기 때문에 U * Q보다 큽니다.
열).
알고리즘의 특징은 모든 특이 값을 찾을 수 있다는 것입니다.
상대 정확도가 0에 임의로 근접한 값 포함
기계 정밀도에 가깝습니다. IsFractionalAccuracyRequired 매개 변수
True로 설정하면 모든 특이 값의 상대 정확도가 높습니다.
기계 정밀도. 매개 변수가 False로 설정되면 가장 큰 매개 변수 만
특이 값은 기계 정밀도에 가까운 상대 정확도를 갖습니다.
다른 특이 값들의 절대 오차는 절대 오차와 동일하다.
가장 큰 특이 값.
입력 매개 변수 :
    D - 행렬 B의 주요 대각선
                인덱스 범위가 [0..N-1] 이내 인 배열.
    E - 행렬 B의 대각선 (또는 대각선)
                인덱스 범위가 [0..N-2] 이내 인 배열
    행렬 B의 N - 사이즈
    IsUpper - 행렬이 위쪽 양 대각선이면 참입니다.
    IsFractionalAccuracyRequired -
                이 매개 변수는 ALGLIB 3.5.0 이후로 무시됩니다.
                단수 값은 항상 높은 정밀도로 검색됩니다.
    U - Q로 곱해질 행렬
                인덱스가 [0..NRU-1, 0..N-1] 범위에있는 배열.
                행렬은 더 클 수 있습니다.
                [0..NRU-1, 0..N-1]에 Q를 곱합니다.
    NRU - 행렬 U의 행 수
    C - Q '로 곱해질 행렬.
                인덱스가 [0..N-1, 0..NCC-1] 범위에있는 배열.
                행렬은 더 클 수 있습니다.
                [0..N-1, 0..NCC-1]에 Q '를 곱합니다.
    NCC - 행렬 C의 열 수
    VT - P ^ T에 곱해질 행렬.
                인덱스가 [0..N-1, 0..NCVT-1] 범위의 배열입니다.
                행렬은 더 클 수 있습니다.
                [0..N-1, 0..NCVT-1]은 P ^ T로 곱해진다.
    NCVT - 행렬 VT의 열 수입니다.
출력 매개 변수 :
    D - 내림차순으로 B 행렬의 특이 값.
    U - NRU> 0 인 경우 행렬 U * Q를 포함합니다.
    VT - NCVT> 0 인 경우 행렬 (P ^ T) * VT를 포함합니다.
    C - NCC> 0 인 경우 행렬 Q '* C가 포함됩니다.
결과:
    알고리즘이 수렴했다면 참.
    알고리즘이 수렴하지 않은 경우 (드문 경우) False입니다.
추가 정보:
    수렴 유형은 내부 매개 변수 TOL로 제어됩니다.
    매개 변수가 0보다 큰 경우, 특이 값에는
    상대 정확도 TOL. TOL <0 인 경우, 특이 값은
    절대 정확도 ABS (TOL) * 표준 (B).
    기본적으로 TOL | 10 * 엡실론 및 100 * 엡실론의 범위 내에 있고,
    여기서 엡실론은 기계 정밀도입니다. 사용하지 않는 것이 좋습니다.
    TOL은 10 * Epsilon보다 작습니다.
    알고리즘을 사용하고 오류가 감소하지 않을 수도 있습니다.
역사:
    * 2007 년 3 월 31 일.
        MAXITR이 6에서 12로 변경되었습니다.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1999 년 10 월 31 일
*************************************************** ********************** */

bool rmatrixbdsvd(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const bool isupper, const bool isfractionalaccuracyrequired, real_2d_array &u, const ae_int_t nru, real_2d_array &c, const ae_int_t ncc, real_2d_array &vt, const ae_int_t ncvt);

/*************************************************************************
Singular value decomposition of a rectangular matrix.

The algorithm calculates the singular value decomposition of a matrix of
size MxN: A = U * S * V^T

The algorithm finds the singular values and, optionally, matrices U and V^T.
The algorithm can find both first min(M,N) columns of matrix U and rows of
matrix V^T (singular vectors), and matrices U and V^T wholly (of sizes MxM
and NxN respectively).

Take into account that the subroutine does not return matrix V but V^T.

Input parameters:
    A           -   matrix to be decomposed.
                    Array whose indexes range within [0..M-1, 0..N-1].
    M           -   number of rows in matrix A.
    N           -   number of columns in matrix A.
    UNeeded     -   0, 1 or 2. See the description of the parameter U.
    VTNeeded    -   0, 1 or 2. See the description of the parameter VT.
    AdditionalMemory -
                    If the parameter:
                     * equals 0, the algorithm doesn\92t use additional
                       memory (lower requirements, lower performance).
                     * equals 1, the algorithm uses additional
                       memory of size min(M,N)*min(M,N) of real numbers.
                       It often speeds up the algorithm.
                     * equals 2, the algorithm uses additional
                       memory of size M*min(M,N) of real numbers.
                       It allows to get a maximum performance.
                    The recommended value of the parameter is 2.

Output parameters:
    W           -   contains singular values in descending order.
    U           -   if UNeeded=0, U isn't changed, the left singular vectors
                    are not calculated.
                    if Uneeded=1, U contains left singular vectors (first
                    min(M,N) columns of matrix U). Array whose indexes range
                    within [0..M-1, 0..Min(M,N)-1].
                    if UNeeded=2, U contains matrix U wholly. Array whose
                    indexes range within [0..M-1, 0..M-1].
    VT          -   if VTNeeded=0, VT isn\92t changed, the right singular vectors
                    are not calculated.
                    if VTNeeded=1, VT contains right singular vectors (first
                    min(M,N) rows of matrix V^T). Array whose indexes range
                    within [0..min(M,N)-1, 0..N-1].
                    if VTNeeded=2, VT contains matrix V^T wholly. Array whose
                    indexes range within [0..N-1, 0..N-1].

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
직사각형 행렬의 단일 값 분해.
알고리즘은 행렬의 특이 값 분해를 계산합니다.
크기 M × N : A = U * S * V ^ T
이 알고리즘은 특이 값과 선택적으로 행렬 U 및 V ^ T를 찾습니다.
알고리즘은 행렬 U의 첫 번째 최소 (M, N) 열과 행렬 U의
행렬 V ^ T (특이 벡터), 및 행렬 U 및 V ^ T (전체 크기 M × M
및 NxN)를 포함한다.
서브 루틴은 행렬 V가 아니라 V ^ T를 리턴한다는 점을 고려하십시오.
입력 매개 변수 :
    A - 분해 할 행렬.
                    인덱스가 [0..M-1, 0..N-1] 범위에있는 배열.
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
    UNeeded - 0, 1 또는 2. 매개 변수 U에 대한 설명을 참조하십시오.
    VTNeeded - 0, 1 또는 2. 매개 변수 VT의 설명을 참조하십시오.
    추가 메모리 -
                    매개 변수 인 경우 :
                     *가 0이면 알고리즘은 추가 사용하지 않습니다.
                       메모리 (낮은 요구 사항, 낮은 성능).
                     *가 1이면 알고리즘은 추가 사용
                       실수의 크기 min (M, N) * min (M, N)의 메모리.
                       종종 알고리즘의 속도를 높입니다.
                     *가 2 인 경우, 알고리즘은 추가
                       실수의 크기 M * min (M, N)의 메모리.
                       그것은 최대 성능을 얻을 수 있습니다.
                    매개 변수의 권장 값은 2입니다.
출력 매개 변수 :
    W - 내림차순으로 단일 값을 포함합니다.
    U - UNeed = 0 인 경우 U는 변경되지 않고 왼쪽의 단일 벡터
                    계산되지 않습니다.
                    Uneeded = 1이면 U는 왼쪽 특이 벡터를 포함합니다 (첫 번째
                    행렬 U의 최소 (M, N) 열). 인덱스 범위가있는 배열
                    [0..M-1, 0..Min (M, N) -1] 이내.
                    UNeeded = 2이면, U는 전적으로 U 행렬을 포함한다. 누구의 배열
                    인덱스 범위는 [0..M-1, 0..M-1]입니다.
    VT - VTNeeded = 0이면 VT는 변경되지 않고, 오른쪽 특이 벡터
                    계산되지 않습니다.
                    VTNeeded = 1 인 경우 VT는 오른쪽 특이 벡터를 포함합니다 (첫 번째
                    행 V ^ T의 최소 (M, N) 행). 인덱스 범위가있는 배열
                    [0..min (M, N) -1, 0..N-1] 이내.
                    VTNeeded = 2이면 VT는 행렬 V ^ T를 전체적으로 포함합니다. 누구의 배열
                    인덱스 범위는 [0..N-1, 0..N-1]입니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

bool rmatrixsvd(const real_2d_array &a, const ae_int_t m, const ae_int_t n, const ae_int_t uneeded, const ae_int_t vtneeded, const ae_int_t additionalmemory, real_1d_array &w, real_2d_array &u, real_2d_array &vt);

/*************************************************************************
Finding the eigenvalues and eigenvectors of a symmetric matrix

The algorithm finds eigen pairs of a symmetric matrix by reducing it to
tridiagonal form and using the QL/QR algorithm.

Input parameters:
    A       -   symmetric matrix which is given by its upper or lower
                triangular part.
                Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    ZNeeded -   flag controlling whether the eigenvectors are needed or not.
                If ZNeeded is equal to:
                 * 0, the eigenvectors are not returned;
                 * 1, the eigenvectors are returned.
    IsUpper -   storage format.

Output parameters:
    D       -   eigenvalues in ascending order.
                Array whose index ranges within [0..N-1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains the eigenvectors.
                Array whose indexes range within [0..N-1, 0..N-1].
                The eigenvectors are stored in the matrix columns.

Result:
    True, if the algorithm has converged.
    False, if the algorithm hasn't converged (rare case).

  -- ALGLIB --
     Copyright 2005-2008 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭 행렬의 고유 값 및 고유 벡터 찾기
이 알고리즘은 대칭 행렬의 고유 쌍을
QL / QR 알고리즘을 사용하여 계산된다.
입력 매개 변수 :
    A - 상한 또는 하한에 의해 주어진 대칭 행렬
                삼각형 부분.
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    ZNeeded - 고유 벡터가 필요한지 아닌지를 제어하는 ​​플래그.
                ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 반환되지 않습니다.
                 * 1, 고유 벡터가 반환됩니다.
    IsUpper - 저장소 형식입니다.
출력 매개 변수 :
    D - 고유 값을 오름차순으로 표시합니다.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 고유 벡터를 포함합니다.
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
                고유 벡터는 행렬 열에 저장됩니다.
결과:
    알고리즘이 수렴했다면 참.
    알고리즘이 수렴하지 않은 경우 (드문 경우) False입니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2008
*************************************************** ********************** */

bool smatrixevd(const real_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, real_1d_array &d, real_2d_array &z);


/*************************************************************************
Subroutine for finding the eigenvalues (and eigenvectors) of  a  symmetric
matrix  in  a  given half open interval (A, B] by using  a  bisection  and
inverse iteration

Input parameters:
    A       -   symmetric matrix which is given by its upper or lower
                triangular part. Array [0..N-1, 0..N-1].
    N       -   size of matrix A.
    ZNeeded -   flag controlling whether the eigenvectors are needed or not.
                If ZNeeded is equal to:
                 * 0, the eigenvectors are not returned;
                 * 1, the eigenvectors are returned.
    IsUpperA -  storage format of matrix A.
    B1, B2 -    half open interval (B1, B2] to search eigenvalues in.

Output parameters:
    M       -   number of eigenvalues found in a given half-interval (M>=0).
    W       -   array of the eigenvalues found.
                Array whose index ranges within [0..M-1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains eigenvectors.
                Array whose indexes range within [0..N-1, 0..M-1].
                The eigenvectors are stored in the matrix columns.

Result:
    True, if successful. M contains the number of eigenvalues in the given
    half-interval (could be equal to 0), W contains the eigenvalues,
    Z contains the eigenvectors (if needed).

    False, if the bisection method subroutine wasn't able to find the
    eigenvalues in the given interval or if the inverse iteration subroutine
    wasn't able to find all the corresponding eigenvectors.
    In that case, the eigenvalues and eigenvectors are not returned,
    M is equal to 0.

  -- ALGLIB --
     Copyright 07.01.2006 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭의 고유 값 (및 고유 벡터)을 찾는 서브 루틴
행렬을 주어진 이분법 간격 (A, B)에서 이분법과
역 반복
입력 매개 변수 :
    A - 상한 또는 하한에 의해 주어진 대칭 행렬
                삼각형 부분. 어레이 [0..N-1, 0..N-1].
    행렬 A의 N 크기
    ZNeeded - 고유 벡터가 필요한지 아닌지를 제어하는 ​​플래그.
                ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 반환되지 않습니다.
                 * 1, 고유 벡터가 반환됩니다.
    IsUpperA - 행렬 A의 저장 형식입니다.
    B1, B2 -에있는 고유 값을 검색하기위한 반 개방 구간 (B1, B2).
출력 매개 변수 :
    M - 주어진 반 간격 (M> = 0)에서 발견 된 고유치의 수.
    W - 발견 된 고유치의 배열입니다.
                인덱스 범위가 [0..M-1] 이내 인 배열.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 고유 벡터를 포함합니다.
                인덱스가 [0..N-1, 0..M-1] 범위에있는 배열.
                고유 벡터는 행렬 열에 저장됩니다.
결과:
    성공하면 참. M은 주어진 고유 값의 수를 포함합니다.
    반 간격 (0과 같을 수 있음), W는 고유 값을 포함하고,
    Z는 고유 벡터를 포함합니다 (필요한 경우).
    거짓, 이진법 서브 루틴이
    주어진 간격의 고유 값 또는 역 반복 서브 루틴
    모든 해당 고유 벡터를 찾을 수 없었습니다.
    이 경우에, 고유치 및 고유 벡터는 리턴되지 않으며,
    M은 0입니다.
  - ALGLIB -
     저작권 2006 년 7 월 1 일 Bochkanov Sergey
*************************************************** ********************** */
bool smatrixevdr(const real_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const double b1, const double b2, ae_int_t &m, real_1d_array &w, real_2d_array &z);


/*************************************************************************
Subroutine for finding the eigenvalues and  eigenvectors  of  a  symmetric
matrix with given indexes by using bisection and inverse iteration methods.

Input parameters:
    A       -   symmetric matrix which is given by its upper or lower
                triangular part. Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    ZNeeded -   flag controlling whether the eigenvectors are needed or not.
                If ZNeeded is equal to:
                 * 0, the eigenvectors are not returned;
                 * 1, the eigenvectors are returned.
    IsUpperA -  storage format of matrix A.
    I1, I2 -    index interval for searching (from I1 to I2).
                0 <= I1 <= I2 <= N-1.

Output parameters:
    W       -   array of the eigenvalues found.
                Array whose index ranges within [0..I2-I1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains eigenvectors.
                Array whose indexes range within [0..N-1, 0..I2-I1].
                In that case, the eigenvectors are stored in the matrix columns.

Result:
    True, if successful. W contains the eigenvalues, Z contains the
    eigenvectors (if needed).

    False, if the bisection method subroutine wasn't able to find the
    eigenvalues in the given interval or if the inverse iteration subroutine
    wasn't able to find all the corresponding eigenvectors.
    In that case, the eigenvalues and eigenvectors are not returned.

  -- ALGLIB --
     Copyright 07.01.2006 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭의 고유 값과 고유 벡터를 찾는 서브 루틴
행렬을 이분법과 역 반복법을 사용하여 주어진 인덱스로 변환합니다.
입력 매개 변수 :
    A - 상한 또는 하한에 의해 주어진 대칭 행렬
                삼각형 부분. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    ZNeeded - 고유 벡터가 필요한지 아닌지를 제어하는 ​​플래그.
                ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 반환되지 않습니다.
                 * 1, 고유 벡터가 반환됩니다.
    IsUpperA - 행렬 A의 저장 형식입니다.
    I1, I2 - 검색을위한 색인 간격 (I1에서 I2까지).
                0 <= I1 <= I2 <= N-1.
출력 매개 변수 :
    W - 발견 된 고유치의 배열입니다.
                인덱스가 [0..I2-I1] 이내 인 배열
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 고유 벡터를 포함합니다.
                인덱스가 [0..N-1, 0..I2-I1] 범위에있는 배열.
                이 경우 고유 벡터는 행렬 열에 저장됩니다.
결과:
    성공하면 참. W는 고유 값을 포함하고, Z는
    고유 벡터 (필요한 경우).
    거짓, 이진법 서브 루틴이
    주어진 간격의 고유 값 또는 역 반복 서브 루틴
    모든 해당 고유 벡터를 찾을 수 없었습니다.
    이 경우 고유 값 및 고유 벡터가 반환되지 않습니다.
  - ALGLIB -
     저작권 2006 년 7 월 1 일 Bochkanov Sergey
*************************************************** ********************** */

bool smatrixevdi(const real_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const ae_int_t i1, const ae_int_t i2, real_1d_array &w, real_2d_array &z);


/*************************************************************************
Finding the eigenvalues and eigenvectors of a Hermitian matrix

The algorithm finds eigen pairs of a Hermitian matrix by  reducing  it  to
real tridiagonal form and using the QL/QR algorithm.

Input parameters:
    A       -   Hermitian matrix which is given  by  its  upper  or  lower
                triangular part.
                Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   storage format.
    ZNeeded -   flag controlling whether the eigenvectors  are  needed  or
                not. If ZNeeded is equal to:
                 * 0, the eigenvectors are not returned;
                 * 1, the eigenvectors are returned.

Output parameters:
    D       -   eigenvalues in ascending order.
                Array whose index ranges within [0..N-1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains the eigenvectors.
                Array whose indexes range within [0..N-1, 0..N-1].
                The eigenvectors are stored in the matrix columns.

Result:
    True, if the algorithm has converged.
    False, if the algorithm hasn't converged (rare case).

Note:
    eigenvectors of Hermitian matrix are defined up to  multiplication  by
    a complex number L, such that |L|=1.

  -- ALGLIB --
     Copyright 2005, 23 March 2007 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
Hermitian 행렬의 고유 값과 고유 벡터 찾기
이 알고리즘은 Hermitian 행렬의 고유 쌍을
QL / QR 알고리즘 사용
입력 매개 변수 :
    A - 위 또는 아래에 의해 주어진 은닉 행렬
                삼각형 부분.
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    IsUpper - 저장소 형식입니다.
    ZNeeded - 고유 벡터의 필요성을 제어하는 ​​플래그 또는
                아니. ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 반환되지 않습니다.
                 * 1, 고유 벡터가 반환됩니다.
출력 매개 변수 :
    D - 고유 값을 오름차순으로 표시합니다.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 고유 벡터를 포함합니다.
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
                고유 벡터는 행렬 열에 저장됩니다.
결과:
    알고리즘이 수렴했다면 참.
    알고리즘이 수렴하지 않은 경우 (드문 경우) False입니다.
노트 :
    Hermitian 행렬의 고유 벡터는 다음과 같은 곱셈으로 정의됩니다.
    | L | = 1이되는 복소수 L이다.
  - ALGLIB -
     저작권 2005 년 3 월 23 일 Bochkanov Sergey
*************************************************** ********************** */

bool hmatrixevd(const complex_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, real_1d_array &d, complex_2d_array &z);


/*************************************************************************
Subroutine for finding the eigenvalues (and eigenvectors) of  a  Hermitian
matrix  in  a  given half-interval (A, B] by using a bisection and inverse
iteration

Input parameters:
    A       -   Hermitian matrix which is given  by  its  upper  or  lower
                triangular  part.  Array  whose   indexes   range   within
                [0..N-1, 0..N-1].
    N       -   size of matrix A.
    ZNeeded -   flag controlling whether the eigenvectors  are  needed  or
                not. If ZNeeded is equal to:
                 * 0, the eigenvectors are not returned;
                 * 1, the eigenvectors are returned.
    IsUpperA -  storage format of matrix A.
    B1, B2 -    half-interval (B1, B2] to search eigenvalues in.

Output parameters:
    M       -   number of eigenvalues found in a given half-interval, M>=0
    W       -   array of the eigenvalues found.
                Array whose index ranges within [0..M-1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains eigenvectors.
                Array whose indexes range within [0..N-1, 0..M-1].
                The eigenvectors are stored in the matrix columns.

Result:
    True, if successful. M contains the number of eigenvalues in the given
    half-interval (could be equal to 0), W contains the eigenvalues,
    Z contains the eigenvectors (if needed).

    False, if the bisection method subroutine  wasn't  able  to  find  the
    eigenvalues  in  the  given  interval  or  if  the  inverse  iteration
    subroutine  wasn't  able  to  find all the corresponding eigenvectors.
    In that case, the eigenvalues and eigenvectors are not returned, M  is
    equal to 0.

Note:
    eigen vectors of Hermitian matrix are defined up to multiplication  by
    a complex number L, such as |L|=1.

  -- ALGLIB --
     Copyright 07.01.2006, 24.03.2007 by Bochkanov Sergey.
*************************************************************************/

/* ************************************************ *************************
Hermitian의 고유 값 (및 고유 벡터)을 찾는 서브 루틴
주어진 이분 간격 (A, B)에서 이진과 역행렬을 사용하여 행렬
되풀이
입력 매개 변수 :
    A - 위 또는 아래에 의해 주어진 은닉 행렬
                삼각형 부분. 인덱스가 범위 내에있는 배열
                [0..N-1, 0..N-1].
    행렬 A의 N 크기
    ZNeeded - 고유 벡터의 필요성을 제어하는 ​​플래그 또는
                아니. ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 반환되지 않습니다.
                 * 1, 고유 벡터가 반환됩니다.
    IsUpperA - 행렬 A의 저장 형식입니다.
    B1, B2 -에서의 고유 값을 검색하기위한 반 간격 (B1, B2).
출력 매개 변수 :
    M - 주어진 반 간격에서 발견 된 고유치의 수, M> = 0
    W - 발견 된 고유치의 배열입니다.
                인덱스 범위가 [0..M-1] 이내 인 배열.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 고유 벡터를 포함합니다.
                인덱스가 [0..N-1, 0..M-1] 범위에있는 배열.
                고유 벡터는 행렬 열에 저장됩니다.
결과:
    성공하면 참. M은 주어진 고유 값의 수를 포함합니다.
    반 간격 (0과 같을 수 있음), W는 고유 값을 포함하고,
    Z는 고유 벡터를 포함합니다 (필요한 경우).
    거짓, 이진법 서브 루틴이
    주어진 간격의 고유 값 또는 역 반복
    서브 루틴은 모든 해당 고유 벡터를 찾을 수 없었습니다.
    이 경우, 고유 값과 고유 벡터는 반환되지 않으며, M은이다.
    0과 같다.
노트 :
    허미 시안 행렬의 고유 벡터는
    | L | = 1과 같은 복소수 L입니다.
  - ALGLIB -
     저작권 2006 년 7 월 1 일, Bochkanov Sergey.
*************************************************** ********************** */

bool hmatrixevdr(const complex_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const double b1, const double b2, ae_int_t &m, real_1d_array &w, complex_2d_array &z);


/*************************************************************************
Subroutine for finding the eigenvalues and  eigenvectors  of  a  Hermitian
matrix with given indexes by using bisection and inverse iteration methods

Input parameters:
    A       -   Hermitian matrix which is given  by  its  upper  or  lower
                triangular part.
                Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    ZNeeded -   flag controlling whether the eigenvectors  are  needed  or
                not. If ZNeeded is equal to:
                 * 0, the eigenvectors are not returned;
                 * 1, the eigenvectors are returned.
    IsUpperA -  storage format of matrix A.
    I1, I2 -    index interval for searching (from I1 to I2).
                0 <= I1 <= I2 <= N-1.

Output parameters:
    W       -   array of the eigenvalues found.
                Array whose index ranges within [0..I2-I1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains eigenvectors.
                Array whose indexes range within [0..N-1, 0..I2-I1].
                In  that  case,  the eigenvectors are stored in the matrix
                columns.

Result:
    True, if successful. W contains the eigenvalues, Z contains the
    eigenvectors (if needed).

    False, if the bisection method subroutine  wasn't  able  to  find  the
    eigenvalues  in  the  given  interval  or  if  the  inverse  iteration
    subroutine wasn't able to find  all  the  corresponding  eigenvectors.
    In that case, the eigenvalues and eigenvectors are not returned.

Note:
    eigen vectors of Hermitian matrix are defined up to multiplication  by
    a complex number L, such as |L|=1.

  -- ALGLIB --
     Copyright 07.01.2006, 24.03.2007 by Bochkanov Sergey.
*************************************************************************/

/* ************************************************ *************************
Hermitian의 고유 값과 고유 벡터를 찾는 서브 루틴
이분법과 역 반복법을 사용하여 주어진 인덱스를 갖는 행렬
입력 매개 변수 :
    A - 위 또는 아래에 의해 주어진 은닉 행렬
                삼각형 부분.
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    ZNeeded - 고유 벡터의 필요성을 제어하는 ​​플래그 또는
                아니. ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 반환되지 않습니다.
                 * 1, 고유 벡터가 반환됩니다.
    IsUpperA - 행렬 A의 저장 형식입니다.
    I1, I2 - 검색을위한 색인 간격 (I1에서 I2까지).
                0 <= I1 <= I2 <= N-1.
출력 매개 변수 :
    W - 발견 된 고유치의 배열입니다.
                인덱스가 [0..I2-I1] 이내 인 배열
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 고유 벡터를 포함합니다.
                인덱스가 [0..N-1, 0..I2-I1] 범위에있는 배열.
                이 경우에, 고유 벡터는 행렬에 저장된다
                열.
결과:
    성공하면 참. W는 고유 값을 포함하고, Z는
    고유 벡터 (필요한 경우).
    거짓, 이진법 서브 루틴이
    주어진 간격의 고유 값 또는 역 반복
    서브 루틴은 모든 해당 고유 벡터를 찾을 수 없었습니다.
    이 경우 고유 값 및 고유 벡터가 반환되지 않습니다.
노트 :
    허미 시안 행렬의 고유 벡터는
    | L | = 1과 같은 복소수 L입니다.
  - ALGLIB -
     저작권 2006 년 7 월 1 일, Bochkanov Sergey.
*************************************************** ********************** */

bool hmatrixevdi(const complex_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const ae_int_t i1, const ae_int_t i2, real_1d_array &w, complex_2d_array &z);


/*************************************************************************
Finding the eigenvalues and eigenvectors of a tridiagonal symmetric matrix

The algorithm finds the eigen pairs of a tridiagonal symmetric matrix by
using an QL/QR algorithm with implicit shifts.

Input parameters:
    D       -   the main diagonal of a tridiagonal matrix.
                Array whose index ranges within [0..N-1].
    E       -   the secondary diagonal of a tridiagonal matrix.
                Array whose index ranges within [0..N-2].
    N       -   size of matrix A.
    ZNeeded -   flag controlling whether the eigenvectors are needed or not.
                If ZNeeded is equal to:
                 * 0, the eigenvectors are not needed;
                 * 1, the eigenvectors of a tridiagonal matrix
                   are multiplied by the square matrix Z. It is used if the
                   tridiagonal matrix is obtained by the similarity
                   transformation of a symmetric matrix;
                 * 2, the eigenvectors of a tridiagonal matrix replace the
                   square matrix Z;
                 * 3, matrix Z contains the first row of the eigenvectors
                   matrix.
    Z       -   if ZNeeded=1, Z contains the square matrix by which the
                eigenvectors are multiplied.
                Array whose indexes range within [0..N-1, 0..N-1].

Output parameters:
    D       -   eigenvalues in ascending order.
                Array whose index ranges within [0..N-1].
    Z       -   if ZNeeded is equal to:
                 * 0, Z hasn\92t changed;
                 * 1, Z contains the product of a given matrix (from the left)
                   and the eigenvectors matrix (from the right);
                 * 2, Z contains the eigenvectors.
                 * 3, Z contains the first row of the eigenvectors matrix.
                If ZNeeded<3, Z is the array whose indexes range within [0..N-1, 0..N-1].
                In that case, the eigenvectors are stored in the matrix columns.
                If ZNeeded=3, Z is the array whose indexes range within [0..0, 0..N-1].

Result:
    True, if the algorithm has converged.
    False, if the algorithm hasn't converged.

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     September 30, 1994
*************************************************************************/

/* ************************************************ *************************
3 대칭 대칭 행렬의 고유 값과 고유 벡터 찾기
이 알고리즘은 삼중 대칭 대칭 행렬의 고유 쌍을
암시 적 교대로 QL / QR 알고리즘을 사용합니다.
입력 매개 변수 :
    D - 삼각 대각선 행렬의 주 대각선.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    E - 3 중 대각 행렬의 2 차 대각선.
                인덱스 범위가 [0..N-2] 이내 인 배열
    행렬 A의 N 크기
    ZNeeded - 고유 벡터가 필요한지 아닌지를 제어하는 ​​플래그.
                ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 필요하지 않습니다.
                 * 1, 3 중항 행렬의 고유 벡터
                   정사각 행렬 Z가 곱해진다.
                   유사도에 의해 삼중 대각 행렬을 얻는다
                   대칭 행렬의 변환;
                 * 2, 삼중 대각 행렬의 고유 벡터가
                   정사각형 행렬 Z;
                 * 3, 행렬 Z는 고유 벡터의 첫 번째 행을 포함합니다.
                   매트릭스.
    Z - ZNeeded = 1 인 경우, Z는
                고유 벡터가 곱해진다.
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
출력 매개 변수 :
    D - 고유 값을 오름차순으로 표시합니다.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 변경되지 않았습니다.
                 * 1, Z는 주어진 행렬의 곱을 포함합니다 (왼쪽부터)
                   와 고유 벡터 행렬 (오른쪽부터);
                 * 2, Z는 고유 벡터를 포함합니다.
                 * 3, Z는 고유 벡터 행렬의 첫 번째 행을 포함합니다.
                ZNeeded <3 인 경우 Z는 인덱스가 [0..N-1, 0..N-1] 범위에있는 배열입니다.
                이 경우 고유 벡터는 행렬 열에 저장됩니다.
                ZNeeded = 3이면 Z는 [0..0, 0..N-1] 범위의 인덱스를 갖는 배열입니다.
결과:
    알고리즘이 수렴했다면 참.
    알고리즘이 수렴하지 않은 경우 False입니다.
  - LAPACK 루틴 (버전 3.0) -
     Univ. 테네시, Univ. 캘리포니아 버클리, NAG Ltd.,
     Courant Institute, Argonne 국립 연구소, Rice University
     1994 년 9 월 30 일
*************************************************** ********************** */

bool smatrixtdevd(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const ae_int_t zneeded, real_2d_array &z);


/*************************************************************************
Subroutine for finding the tridiagonal matrix eigenvalues/vectors in a
given half-interval (A, B] by using bisection and inverse iteration.

Input parameters:
    D       -   the main diagonal of a tridiagonal matrix.
                Array whose index ranges within [0..N-1].
    E       -   the secondary diagonal of a tridiagonal matrix.
                Array whose index ranges within [0..N-2].
    N       -   size of matrix, N>=0.
    ZNeeded -   flag controlling whether the eigenvectors are needed or not.
                If ZNeeded is equal to:
                 * 0, the eigenvectors are not needed;
                 * 1, the eigenvectors of a tridiagonal matrix are multiplied
                   by the square matrix Z. It is used if the tridiagonal
                   matrix is obtained by the similarity transformation
                   of a symmetric matrix.
                 * 2, the eigenvectors of a tridiagonal matrix replace matrix Z.
    A, B    -   half-interval (A, B] to search eigenvalues in.
    Z       -   if ZNeeded is equal to:
                 * 0, Z isn't used and remains unchanged;
                 * 1, Z contains the square matrix (array whose indexes range
                   within [0..N-1, 0..N-1]) which reduces the given symmetric
                   matrix to tridiagonal form;
                 * 2, Z isn't used (but changed on the exit).

Output parameters:
    D       -   array of the eigenvalues found.
                Array whose index ranges within [0..M-1].
    M       -   number of eigenvalues found in the given half-interval (M>=0).
    Z       -   if ZNeeded is equal to:
                 * 0, doesn't contain any information;
                 * 1, contains the product of a given NxN matrix Z (from the
                   left) and NxM matrix of the eigenvectors found (from the
                   right). Array whose indexes range within [0..N-1, 0..M-1].
                 * 2, contains the matrix of the eigenvectors found.
                   Array whose indexes range within [0..N-1, 0..M-1].

Result:

    True, if successful. In that case, M contains the number of eigenvalues
    in the given half-interval (could be equal to 0), D contains the eigenvalues,
    Z contains the eigenvectors (if needed).
    It should be noted that the subroutine changes the size of arrays D and Z.

    False, if the bisection method subroutine wasn't able to find the
    eigenvalues in the given interval or if the inverse iteration subroutine
    wasn't able to find all the corresponding eigenvectors. In that case,
    the eigenvalues and eigenvectors are not returned, M is equal to 0.

  -- ALGLIB --
     Copyright 31.03.2008 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
tridiagonal 행렬의 eigenvalues ​​/ vectors를 찾기위한 서브 루틴
주어진 반 구간 (A, B)은 이분법과 역 반복을 사용합니다.
입력 매개 변수 :
    D - 삼각 대각선 행렬의 주 대각선.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    E - 3 중 대각 행렬의 2 차 대각선.
                인덱스 범위가 [0..N-2] 이내 인 배열
    N - 크기의 행렬, N> = 0.
    ZNeeded - 고유 벡터가 필요한지 아닌지를 제어하는 ​​플래그.
                ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 필요하지 않습니다.
                 * 1, 삼중 대각 행렬의 고유 벡터가 곱해진다.
                   정사각형 행렬 Z에 의해 결정된다. 삼중 대각선
                   유사성 변환에 의해 행렬을 얻는다
                   대칭 행렬의
                 * 2, 삼중 대각 행렬의 고유 벡터가 행렬 Z를 대체합니다.
    A, B -에있는 고유 값을 검색하기위한 반 간격 (A, B).
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 사용되지 않고 변경되지 않습니다.
                 * 1, Z는 정사각형 매트릭스 (인덱스 범위가
                   [0..N-1, 0..N-1] 내의) 주어진 대칭성을 감소시킨다.
                   tridiagonal 형태의 행렬;
                 * 2, Z는 사용되지 않습니다 (그러나 출구에서 변경됨).
출력 매개 변수 :
    D - 발견 된 고유치의 배열.
                인덱스 범위가 [0..M-1] 이내 인 배열.
    M - 주어진 반 간격 (M> = 0)에서 발견 된 고유치의 수.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0은 정보를 포함하지 않습니다.
                 * 1, 주어진 NxN 행렬 Z의 곱을 포함
                   왼쪽) 및 발견 된 고유 벡터의 N × M 행렬 (
                   권리). 인덱스가 [0..N-1, 0..M-1] 범위에있는 배열.
                 * 2, 발견 된 고유 벡터의 행렬을 포함합니다.
                   인덱스가 [0..N-1, 0..M-1] 범위에있는 배열.
결과:
    성공하면 참. 이 경우, M은 고유 값의 수를 포함한다.
    주어진 절반 간격 (0과 같을 수 있음)에서 D는 고유 값을 포함하고,
    Z는 고유 벡터를 포함합니다 (필요한 경우).
    서브 루틴은 배열 D와 Z의 크기를 변경한다는 점에 유의해야합니다.
    거짓, 이진법 서브 루틴이
    주어진 간격의 고유 값 또는 역 반복 서브 루틴
    모든 해당 고유 벡터를 찾을 수 없었습니다. 이 경우,
    고유 값과 고유 벡터는 반환되지 않으며, M은 0과 같습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 31.03.2008
*************************************************** ********************** */

bool smatrixtdevdr(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const ae_int_t zneeded, const double a, const double b, ae_int_t &m, real_2d_array &z);


/*************************************************************************
Subroutine for finding tridiagonal matrix eigenvalues/vectors with given
indexes (in ascending order) by using the bisection and inverse iteraion.

Input parameters:
    D       -   the main diagonal of a tridiagonal matrix.
                Array whose index ranges within [0..N-1].
    E       -   the secondary diagonal of a tridiagonal matrix.
                Array whose index ranges within [0..N-2].
    N       -   size of matrix. N>=0.
    ZNeeded -   flag controlling whether the eigenvectors are needed or not.
                If ZNeeded is equal to:
                 * 0, the eigenvectors are not needed;
                 * 1, the eigenvectors of a tridiagonal matrix are multiplied
                   by the square matrix Z. It is used if the
                   tridiagonal matrix is obtained by the similarity transformation
                   of a symmetric matrix.
                 * 2, the eigenvectors of a tridiagonal matrix replace
                   matrix Z.
    I1, I2  -   index interval for searching (from I1 to I2).
                0 <= I1 <= I2 <= N-1.
    Z       -   if ZNeeded is equal to:
                 * 0, Z isn't used and remains unchanged;
                 * 1, Z contains the square matrix (array whose indexes range within [0..N-1, 0..N-1])
                   which reduces the given symmetric matrix to  tridiagonal form;
                 * 2, Z isn't used (but changed on the exit).

Output parameters:
    D       -   array of the eigenvalues found.
                Array whose index ranges within [0..I2-I1].
    Z       -   if ZNeeded is equal to:
                 * 0, doesn't contain any information;
                 * 1, contains the product of a given NxN matrix Z (from the left) and
                   Nx(I2-I1) matrix of the eigenvectors found (from the right).
                   Array whose indexes range within [0..N-1, 0..I2-I1].
                 * 2, contains the matrix of the eigenvalues found.
                   Array whose indexes range within [0..N-1, 0..I2-I1].


Result:

    True, if successful. In that case, D contains the eigenvalues,
    Z contains the eigenvectors (if needed).
    It should be noted that the subroutine changes the size of arrays D and Z.

    False, if the bisection method subroutine wasn't able to find the eigenvalues
    in the given interval or if the inverse iteration subroutine wasn't able
    to find all the corresponding eigenvectors. In that case, the eigenvalues
    and eigenvectors are not returned.

  -- ALGLIB --
     Copyright 25.12.2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 tridiagonal 행렬 고유치 / 벡터를 찾는 서브 루틴
이분법과 역 iteredion을 사용하여 인덱스를 오름차순으로 정렬합니다.
입력 매개 변수 :
    D - 삼각 대각선 행렬의 주 대각선.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    E - 3 중 대각 행렬의 2 차 대각선.
                인덱스 범위가 [0..N-2] 이내 인 배열
    매트릭스의 N - 사이즈. N> = 0이다.
    ZNeeded - 고유 벡터가 필요한지 아닌지를 제어하는 ​​플래그.
                ZNeeded가 다음과 같은 경우 :
                 * 0이면 고유 벡터가 필요하지 않습니다.
                 * 1, 삼중 대각 행렬의 고유 벡터가 곱해진다.
                   정사각형 행렬 Z에 의해 정해진 다.
                   유사 변환에 의해 3 중 3 차원 행렬을 얻는다
                   대칭 행렬의
                 * 2, 3 중 대각 행렬의 고유 벡터 교체
                   행렬 Z
    I1, I2 - 검색을위한 색인 간격 (I1에서 I2까지).
                0 <= I1 <= I2 <= N-1.
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0, Z는 사용되지 않고 변경되지 않습니다.
                 * 1, Z는 정사각 행렬 ([0..N-1, 0..N-1] 범위의 인덱스를 갖는 배열)을 포함합니다.
                   주어진 대칭 행렬을 삼중 대각 형태로 감소시키는;
                 * 2, Z는 사용되지 않습니다 (그러나 출구에서 변경됨).
출력 매개 변수 :
    D - 발견 된 고유치의 배열.
                인덱스가 [0..I2-I1] 이내 인 배열
    Z - ZNeeded가 다음과 동일한 경우 :
                 * 0은 정보를 포함하지 않습니다.
                 * 1, 주어진 NxN 행렬 Z (왼쪽부터)와
                   발견 된 고유 벡터의 Nx (I2-I1) 행렬 (오른쪽에서).
                   인덱스가 [0..N-1, 0..I2-I1] 범위에있는 배열.
                 * 2는 발견 된 고유치의 행렬을 포함합니다.
                   인덱스가 [0..N-1, 0..I2-I1] 범위에있는 배열.
결과:
    성공하면 참. 이 경우, D는 고유 값을 포함하고,
    Z는 고유 벡터를 포함합니다 (필요한 경우).
    서브 루틴은 배열 D와 Z의 크기를 변경한다는 점에 유의해야합니다.
    False, 이진법 서브 루틴이 고유 값을 찾을 수없는 경우
    주어진 간격에서 또는 역 반복 서브 루틴이 불가능한 경우
    모든 해당 고유 벡터를 찾는다. 이 경우, 고유 값
    고유 벡터는 반환되지 않습니다.
  - ALGLIB -
     저작권 2005 년 12 월 25 일 Bochkanov Sergey
*************************************************** ********************** */

bool smatrixtdevdi(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const ae_int_t zneeded, const ae_int_t i1, const ae_int_t i2, real_2d_array &z);


/*************************************************************************
Finding eigenvalues and eigenvectors of a general matrix

The algorithm finds eigenvalues and eigenvectors of a general matrix by
using the QR algorithm with multiple shifts. The algorithm can find
eigenvalues and both left and right eigenvectors.

The right eigenvector is a vector x such that A*x = w*x, and the left
eigenvector is a vector y such that y'*A = w*y' (here y' implies a complex
conjugate transposition of vector y).

Input parameters:
    A       -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    VNeeded -   flag controlling whether eigenvectors are needed or not.
                If VNeeded is equal to:
                 * 0, eigenvectors are not returned;
                 * 1, right eigenvectors are returned;
                 * 2, left eigenvectors are returned;
                 * 3, both left and right eigenvectors are returned.

Output parameters:
    WR      -   real parts of eigenvalues.
                Array whose index ranges within [0..N-1].
    WR      -   imaginary parts of eigenvalues.
                Array whose index ranges within [0..N-1].
    VL, VR  -   arrays of left and right eigenvectors (if they are needed).
                If WI[i]=0, the respective eigenvalue is a real number,
                and it corresponds to the column number I of matrices VL/VR.
                If WI[i]>0, we have a pair of complex conjugate numbers with
                positive and negative imaginary parts:
                    the first eigenvalue WR[i] + sqrt(-1)*WI[i];
                    the second eigenvalue WR[i+1] + sqrt(-1)*WI[i+1];
                    WI[i]>0
                    WI[i+1] = -WI[i] < 0
                In that case, the eigenvector  corresponding to the first
                eigenvalue is located in i and i+1 columns of matrices
                VL/VR (the column number i contains the real part, and the
                column number i+1 contains the imaginary part), and the vector
                corresponding to the second eigenvalue is a complex conjugate to
                the first vector.
                Arrays whose indexes range within [0..N-1, 0..N-1].

Result:
    True, if the algorithm has converged.
    False, if the algorithm has not converged.

Note 1:
    Some users may ask the following question: what if WI[N-1]>0?
    WI[N] must contain an eigenvalue which is complex conjugate to the
    N-th eigenvalue, but the array has only size N?
    The answer is as follows: such a situation cannot occur because the
    algorithm finds a pairs of eigenvalues, therefore, if WI[i]>0, I is
    strictly less than N-1.

Note 2:
    The algorithm performance depends on the value of the internal parameter
    NS of the InternalSchurDecomposition subroutine which defines the number
    of shifts in the QR algorithm (similarly to the block width in block-matrix
    algorithms of linear algebra). If you require maximum performance
    on your machine, it is recommended to adjust this parameter manually.


See also the InternalTREVC subroutine.

The algorithm is based on the LAPACK 3.0 library.
*************************************************************************/

/* ************************************************ *************************
일반 행렬의 고유 값 및 고유 벡터 찾기
이 알고리즘은 일반 매트릭스의 고유 값과 고유 벡터를
여러 교대로 QR 알고리즘을 사용합니다. 알고리즘에서 찾을 수 있습니다.
고유 값 및 좌우 고유 벡터.
올바른 고유 벡터는 A * x = w * x와 같은 벡터 x이고, 왼쪽
고유 벡터 (eigenvector)는 y '* A = w * y'(여기서 y는 복소
벡터 y의 공액 전치).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    VNeeded - 고유 벡터가 필요한지 여부를 제어하는 ​​플래그.
                VNeeded가 다음과 같은 경우 :
                 * 0, 고유 벡터가 반환되지 않습니다.
                 * 1, 오른쪽 고유 벡터가 반환됩니다.
                 * 2, 왼쪽 고유 벡터가 반환됩니다.
                 * 3, 좌우 고유 벡터가 반환됩니다.
출력 매개 변수 :
    WR - 고유치의 실수 부분.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    WR - 고유치의 허수 부.
                인덱스 범위가 [0..N-1] 이내 인 배열.
    VL, VR - 왼쪽 및 오른쪽 고유 벡터 배열 (필요할 경우).
                WI [i] = 0이면, 각각의 고유치는 실수이고,
                행렬 VL / VR의 열 번호 I에 해당합니다.
                WI [i]> 0이면, 우리는 한 쌍의 복소 공액 수를 가지고있다.
                양수 및 음수 허수 부 :
                    제 1 고유 값 WR [i] + sqrt (-1) * WI [i];
                    제 2 고유 값 WR [i + 1] + sqrt (-1) * WI [i + 1];
                    WI [i]> 0
                    WI [i + 1] = -WI [i] <0
                이 경우, 첫 번째에 해당하는 고유 벡터
                고유 값은 행렬의 i와 i + 1 열에 위치합니다.
                VL / VR (열 번호 i는 실수 부분을 포함하고
                열 번호 i + 1은 허수 부를 포함 함), 벡터
                제 2 고유 값에 대응하는 켤레 복소 공액은
                첫 번째 벡터.
                인덱스가 [0..N-1, 0..N-1] 범위에있는 배열
결과:
    알고리즘이 수렴했다면 참.
    알고리즘이 수렴하지 않은 경우 False입니다.
참고 1 :
    일부 사용자는 다음 질문을 할 수 있습니다. WI [N-1]> 0 일 경우 어떻게해야합니까?
    WI [N]은 고유치를 포함해야합니다.
    N 번째 고유 값을 갖지만 배열의 크기는 N입니까?
    대답은 다음과 같습니다.
    알고리즘은 고유 값의 쌍을 찾는다. 그러므로 WI [i]> 0이면 I는
    엄격히 N-1보다 작다.
노트 2:
    알고리즘 성능은 내부 매개 변수의 값에 따라 달라집니다
    숫자를 정의하는 InternalSchurDecomposition 서브 루틴의 NS
    QR 알고리즘의 시프트 (블록 - 매트릭스의 블록 폭과 유사)
    선형 대수학의 알고리즘). 최대 성능이 필요한 경우
    on your machine, it is recommended to adjust this parameter manually.
See also the InternalTREVC subroutine.
The algorithm is based on the LAPACK 3.0 library.
*************************************************************************/

bool rmatrixevd(const real_2d_array &a, const ae_int_t n, const ae_int_t vneeded, real_1d_array &wr, real_1d_array &wi, real_2d_array &vl, real_2d_array &vr);

/*************************************************************************
Generation of a random uniformly distributed (Haar) orthogonal matrix

INPUT PARAMETERS:
    N   -   matrix size, N>=1

OUTPUT PARAMETERS:
    A   -   orthogonal NxN matrix, array[0..N-1,0..N-1]

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
임의로 균일하게 분포 된 (Haar) 직교 행렬의 생성
입력 매개 변수 :
    N - 행렬 크기, N> = 1
출력 매개 변수 :
    A - 직교 N × N 행렬, 어레이 [0..N-1.0 ... N-1]
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixrndorthogonal(const ae_int_t n, real_2d_array &a);


/*************************************************************************
Generation of random NxN matrix with given condition number and norm2(A)=1

INPUT PARAMETERS:
    N   -   matrix size
    C   -   condition number (in 2-norm)

OUTPUT PARAMETERS:
    A   -   random matrix with norm2(A)=1 and cond(A)=C

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 조건 수와 norm2 (A) = 1을 갖는 랜덤 N × N 행렬의 생성
입력 매개 변수 :
    N - 행렬 크기
    C - 조건 수 (2 표준)
출력 매개 변수 :
    A - norm2 (A) = 1이고 cond (A) = C 인 무작위 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixrndcond(const ae_int_t n, const double c, real_2d_array &a);


/*************************************************************************
Generation of a random Haar distributed orthogonal complex matrix

INPUT PARAMETERS:
    N   -   matrix size, N>=1

OUTPUT PARAMETERS:
    A   -   orthogonal NxN matrix, array[0..N-1,0..N-1]

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
랜덤 해어 분포 직교 복소수 행렬의 생성
입력 매개 변수 :
    N - 행렬 크기, N> = 1
출력 매개 변수 :
    A - 직교 N × N 행렬, 어레이 [0..N-1.0 ... N-1]
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixrndorthogonal(const ae_int_t n, complex_2d_array &a);


/*************************************************************************
Generation of random NxN complex matrix with given condition number C and
norm2(A)=1

INPUT PARAMETERS:
    N   -   matrix size
    C   -   condition number (in 2-norm)

OUTPUT PARAMETERS:
    A   -   random matrix with norm2(A)=1 and cond(A)=C

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 조건 수 C를 갖는 랜덤 N × N 복소 행렬 생성
norm2 (A) = 1
입력 매개 변수 :
    N - 행렬 크기
    C - 조건 수 (2 표준)
출력 매개 변수 :
    A - norm2 (A) = 1이고 cond (A) = C 인 무작위 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixrndcond(const ae_int_t n, const double c, complex_2d_array &a);


/*************************************************************************
Generation of random NxN symmetric matrix with given condition number  and
norm2(A)=1

INPUT PARAMETERS:
    N   -   matrix size
    C   -   condition number (in 2-norm)

OUTPUT PARAMETERS:
    A   -   random matrix with norm2(A)=1 and cond(A)=C

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 조건 수를 가진 무작위 NxN 대칭 행렬의 생성과
norm2 (A) = 1
입력 매개 변수 :
    N - 행렬 크기
    C - 조건 수 (2 표준)
출력 매개 변수 :
    A - norm2 (A) = 1이고 cond (A) = C 인 무작위 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void smatrixrndcond(const ae_int_t n, const double c, real_2d_array &a);


/*************************************************************************
Generation of random NxN symmetric positive definite matrix with given
condition number and norm2(A)=1

INPUT PARAMETERS:
    N   -   matrix size
    C   -   condition number (in 2-norm)

OUTPUT PARAMETERS:
    A   -   random SPD matrix with norm2(A)=1 and cond(A)=C

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 조건 수를 갖는 무작위 NxN Hermitian 행렬의 생성과
norm2 (A) = 1
입력 매개 변수 :
    N - 행렬 크기
    C - 조건 수 (2 표준)
출력 매개 변수 :
    A - norm2 (A) = 1이고 cond (A) = C 인 무작위 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void spdmatrixrndcond(const ae_int_t n, const double c, real_2d_array &a);


/*************************************************************************
Generation of random NxN Hermitian matrix with given condition number  and
norm2(A)=1

INPUT PARAMETERS:
    N   -   matrix size
    C   -   condition number (in 2-norm)

OUTPUT PARAMETERS:
    A   -   random matrix with norm2(A)=1 and cond(A)=C

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 임의의 NxN Hermitian positive definite matrix의 생성
조건 수와 norm2 (A) = 1
입력 매개 변수 :
    N - 행렬 크기
    C - 조건 수 (2 표준)
출력 매개 변수 :
    A - norm2 (A) = 1이고 cond (A) = C 인 무작위 HPD 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void hmatrixrndcond(const ae_int_t n, const double c, complex_2d_array &a);


/*************************************************************************
Generation of random NxN Hermitian positive definite matrix with given
condition number and norm2(A)=1

INPUT PARAMETERS:
    N   -   matrix size
    C   -   condition number (in 2-norm)

OUTPUT PARAMETERS:
    A   -   random HPD matrix with norm2(A)=1 and cond(A)=C

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
N × N 랜덤 Haar 분산 직교 행렬에 의한 M × N 행렬의 승산
입력 매개 변수 :
    A - 행렬, 배열 [0..M-1, 0..N-1]
    M, N- 매트릭스 크기
출력 매개 변수 :
    A - A * Q, 여기서 Q는 랜덤 NxN 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void hpdmatrixrndcond(const ae_int_t n, const double c, complex_2d_array &a);


/*************************************************************************
Multiplication of MxN matrix by NxN random Haar distributed orthogonal matrix

INPUT PARAMETERS:
    A   -   matrix, array[0..M-1, 0..N-1]
    M, N-   matrix size

OUTPUT PARAMETERS:
    A   -   A*Q, where Q is random NxN orthogonal matrix

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
M × M 랜덤 Haar 분산 직교 행렬에 의한 M × N 행렬의 승산
입력 매개 변수 :
    A - 행렬, 배열 [0..M-1, 0..N-1]
    M, N- 매트릭스 크기
출력 매개 변수 :
    A - Q * A, 여기서 Q는 임의의 MxM 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixrndorthogonalfromtheright(real_2d_array &a, const ae_int_t m, const ae_int_t n);


/*************************************************************************
Multiplication of MxN matrix by MxM random Haar distributed orthogonal matrix

INPUT PARAMETERS:
    A   -   matrix, array[0..M-1, 0..N-1]
    M, N-   matrix size

OUTPUT PARAMETERS:
    A   -   Q*A, where Q is random MxM orthogonal matrix

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
M × M 랜덤 Haar 분산 직교 행렬에 의한 M × N 행렬의 승산
입력 매개 변수 :
    A - 행렬, 배열 [0..M-1, 0..N-1]
    M, N- 매트릭스 크기
출력 매개 변수 :
    A - Q * A, 여기서 Q는 임의의 MxM 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixrndorthogonalfromtheleft(real_2d_array &a, const ae_int_t m, const ae_int_t n);


/*************************************************************************
Multiplication of MxN complex matrix by NxN random Haar distributed
complex orthogonal matrix

INPUT PARAMETERS:
    A   -   matrix, array[0..M-1, 0..N-1]
    M, N-   matrix size

OUTPUT PARAMETERS:
    A   -   A*Q, where Q is random NxN orthogonal matrix

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
MxM 무작위 Haar 분포에 의한 M × N 복소 행렬의 승산
복소 직교 행렬
입력 매개 변수 :
    A - 행렬, 배열 [0..M-1, 0..N-1]
    M, N- 매트릭스 크기
출력 매개 변수 :
    A - Q * A, 여기서 Q는 임의의 MxM 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixrndorthogonalfromtheright(complex_2d_array &a, const ae_int_t m, const ae_int_t n);


/*************************************************************************
Multiplication of MxN complex matrix by MxM random Haar distributed
complex orthogonal matrix

INPUT PARAMETERS:
    A   -   matrix, array[0..M-1, 0..N-1]
    M, N-   matrix size

OUTPUT PARAMETERS:
    A   -   Q*A, where Q is random MxM orthogonal matrix

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
MxM 무작위 Haar 분포에 의한 M × N 복소 행렬의 승산
복소 직교 행렬
입력 매개 변수 :
    A - 행렬, 배열 [0..M-1, 0..N-1]
    M, N- 매트릭스 크기
출력 매개 변수 :
    A - Q * A, 여기서 Q는 임의의 MxM 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */
void cmatrixrndorthogonalfromtheleft(complex_2d_array &a, const ae_int_t m, const ae_int_t n);


/*************************************************************************
Symmetric multiplication of NxN matrix by random Haar distributed
orthogonal  matrix

INPUT PARAMETERS:
    A   -   matrix, array[0..N-1, 0..N-1]
    N   -   matrix size

OUTPUT PARAMETERS:
    A   -   Q'*A*Q, where Q is random NxN orthogonal matrix

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
임의의 Haar 분산에 의한 N × N 행렬의 대칭 곱셈
직교 행렬
입력 매개 변수 :
    A- 행렬, 어레이 [0..N-1, 0..N-1]
    N - 행렬 크기
출력 매개 변수 :
    A - Q '* A * Q, 여기서 Q는 랜덤 NxN 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void smatrixrndmultiply(real_2d_array &a, const ae_int_t n);


/*************************************************************************
Hermitian multiplication of NxN matrix by random Haar distributed
complex orthogonal matrix

INPUT PARAMETERS:
    A   -   matrix, array[0..N-1, 0..N-1]
    N   -   matrix size

OUTPUT PARAMETERS:
    A   -   Q^H*A*Q, where Q is random NxN orthogonal matrix

  -- ALGLIB routine --
     04.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
무작위 Haar 분산에 의한 N × N 행렬의 은닉 곱셈
복소 직교 행렬
입력 매개 변수 :
    A- 행렬, 어레이 [0..N-1, 0..N-1]
    N - 행렬 크기
출력 매개 변수 :
    A - Q ^ H * A * Q, 여기서 Q는 랜덤 NxN 직교 행렬
  - ALGLIB 루틴 -
     2009 년 4 월 12 일
     보흐 카 노브 세르게이
*************************************************** ********************** */

void hmatrixrndmultiply(complex_2d_array &a, const ae_int_t n);

/*************************************************************************
LU decomposition of a general real matrix with row pivoting

A is represented as A = P*L*U, where:
* L is lower unitriangular matrix
* U is upper triangular matrix
* P = P0*P1*...*PK, K=min(M,N)-1,
  Pi - permutation matrix for I and Pivots[I]

This is cache-oblivous implementation of LU decomposition.
It is optimized for square matrices. As for rectangular matrices:
* best case - M>>N
* worst case - N>>M, small M, large N, matrix does not fit in CPU cache

INPUT PARAMETERS:
    A       -   array[0..M-1, 0..N-1].
    M       -   number of rows in matrix A.
    N       -   number of columns in matrix A.


OUTPUT PARAMETERS:
    A       -   matrices L and U in compact form:
                * L is stored under main diagonal
                * U is stored on and above main diagonal
    Pivots  -   permutation matrix in compact form.
                array[0..Min(M-1,N-1)].

  -- ALGLIB routine --
     10.01.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행 피벗을 사용하는 일반 실수 행렬의 LU 분해
A는 A = P * L * U로 표현되며, 여기서 :
* L은 낮은 단위 행렬입니다.
* U는 상 삼각 행렬입니다.
* P = P0 * P1 * ... * PK, K = min (M, N) -1,
  I와 Pivots에 대한 Pi - 순열 행렬 [I]
이것은 LU 분해의 캐시 - 비 일관적인 구현입니다.
그것은 정사각형 행렬에 최적화되어 있습니다. 직사각형 행렬의 경우 :
* 최상의 케이스 - M >> N
* 최악의 경우 - N >> M, 작은 M, 큰 N, 매트릭스가 CPU 캐시에 맞지 않습니다.
입력 매개 변수 :
    A- 어레이 [0..M-1, 0..N-1].
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 조밀 한 모양에있는 모체 L와 U :
                * L은 주 대각선 아래에 저장됩니다.
                * U는 주 대각선 위에 저장됩니다.
    피벗 - 컴팩트 형식의 순열 행렬입니다.
                배열 [0..Min (M-1, N-1)].
  - ALGLIB 루틴 -
     10.01.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixlu(real_2d_array &a, const ae_int_t m, const ae_int_t n, integer_1d_array &pivots);


/*************************************************************************
LU decomposition of a general complex matrix with row pivoting

A is represented as A = P*L*U, where:
* L is lower unitriangular matrix
* U is upper triangular matrix
* P = P0*P1*...*PK, K=min(M,N)-1,
  Pi - permutation matrix for I and Pivots[I]

This is cache-oblivous implementation of LU decomposition. It is optimized
for square matrices. As for rectangular matrices:
* best case - M>>N
* worst case - N>>M, small M, large N, matrix does not fit in CPU cache

INPUT PARAMETERS:
    A       -   array[0..M-1, 0..N-1].
    M       -   number of rows in matrix A.
    N       -   number of columns in matrix A.


OUTPUT PARAMETERS:
    A       -   matrices L and U in compact form:
                * L is stored under main diagonal
                * U is stored on and above main diagonal
    Pivots  -   permutation matrix in compact form.
                array[0..Min(M-1,N-1)].

  -- ALGLIB routine --
     10.01.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행 피벗을 사용하는 일반 복소 행렬의 LU 분해
A는 A = P * L * U로 표현되며, 여기서 :
* L은 낮은 단위 행렬입니다.
* U는 상 삼각 행렬입니다.
* P = P0 * P1 * ... * PK, K = min (M, N) -1,
  I와 Pivots에 대한 Pi - 순열 행렬 [I]
이것은 LU 분해의 캐시 - 비 일관적인 구현입니다. 최적화되어있다.
정사각형 행렬에 대해서. 직사각형 행렬의 경우 :
* 최상의 케이스 - M >> N
* 최악의 경우 - N >> M, 작은 M, 큰 N, 매트릭스가 CPU 캐시에 맞지 않습니다.
입력 매개 변수 :
    A- 어레이 [0..M-1, 0..N-1].
    M - 행렬 A의 행 수
    N - 행렬 A의 열 수
출력 매개 변수 :
    A - 조밀 한 모양에있는 모체 L와 U :
                * L은 주 대각선 아래에 저장됩니다.
                * U는 주 대각선 위에 저장됩니다.
    피벗 - 컴팩트 형식의 순열 행렬입니다.
                배열 [0..Min (M-1, N-1)].
  - ALGLIB 루틴 -
     10.01.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixlu(complex_2d_array &a, const ae_int_t m, const ae_int_t n, integer_1d_array &pivots);


/*************************************************************************
Cache-oblivious Cholesky decomposition

The algorithm computes Cholesky decomposition  of  a  Hermitian  positive-
definite matrix. The result of an algorithm is a representation  of  A  as
A=U'*U  or A=L*L' (here X' detones conj(X^T)).

INPUT PARAMETERS:
    A       -   upper or lower triangle of a factorized matrix.
                array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   if IsUpper=True, then A contains an upper triangle of
                a symmetric matrix, otherwise A contains a lower one.

OUTPUT PARAMETERS:
    A       -   the result of factorization. If IsUpper=True, then
                the upper triangle contains matrix U, so that A = U'*U,
                and the elements below the main diagonal are not modified.
                Similarly, if IsUpper = False.

RESULT:
    If  the  matrix  is  positive-definite,  the  function  returns  True.
    Otherwise, the function returns False. Contents of A is not determined
    in such case.

  -- ALGLIB routine --
     15.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
캐시를 인식하지 못하는 콜레 스키 (Cholesky) 분해
이 알고리즘은 Hermitian positive-
명확한 행렬. 알고리즘의 결과는 A를 다음과 같이 나타냅니다.
A = U '* U 또는 A = L * L'(여기서 X '는 conj (X ^ T)를 나타냄).
입력 매개 변수 :
    A - 인수 분해 된 행렬의 위 또는 아래 삼각형.
                요소들 [0..N-1, 0..N-1]을 갖는 배열.
    행렬 A의 N 크기
    IsUpper - IsUpper = True 인 경우, A는 다음과 같은 상 삼각형을 포함합니다.
                대칭 행렬. 그렇지 않으면 A는 더 낮은 것을 포함합니다.
출력 매개 변수 :
    A - 인수 분해의 결과. IsUpper = True이면
                위 삼각형은 행렬 U를 포함하므로 A = U '* U,
                주 대각선 아래의 요소는 수정되지 않습니다.
                마찬가지로 IsUpper = False 인 경우
결과:
    행렬이 양의 값이면 함수는 True를 반환합니다.
    그렇지 않으면 False를 반환합니다. A의 내용이 결정되지 않았습니다.
    그런 경우에.
  - ALGLIB 루틴 -
     15.12.2009
     보흐 카 노브 세르게이
*************************************************** ********************** */

bool hpdmatrixcholesky(complex_2d_array &a, const ae_int_t n, const bool isupper);


/*************************************************************************
Cache-oblivious Cholesky decomposition

The algorithm computes Cholesky decomposition  of  a  symmetric  positive-
definite matrix. The result of an algorithm is a representation  of  A  as
A=U^T*U  or A=L*L^T

INPUT PARAMETERS:
    A       -   upper or lower triangle of a factorized matrix.
                array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   if IsUpper=True, then A contains an upper triangle of
                a symmetric matrix, otherwise A contains a lower one.

OUTPUT PARAMETERS:
    A       -   the result of factorization. If IsUpper=True, then
                the upper triangle contains matrix U, so that A = U^T*U,
                and the elements below the main diagonal are not modified.
                Similarly, if IsUpper = False.

RESULT:
    If  the  matrix  is  positive-definite,  the  function  returns  True.
    Otherwise, the function returns False. Contents of A is not determined
    in such case.

  -- ALGLIB routine --
     15.12.2009
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
캐시를 인식하지 못하는 콜레 스키 (Cholesky) 분해
이 알고리즘은 Cholesky 분해를 계산합니다.
명확한 행렬. 알고리즘의 결과는 A를 다음과 같이 나타냅니다.
A = U * T * U 또는 A = L * L * T
입력 매개 변수 :
    A - 인수 분해 된 행렬의 위 또는 아래 삼각형.
                요소들 [0..N-1, 0..N-1]을 갖는 배열.
    행렬 A의 N 크기
    IsUpper - IsUpper = True 인 경우, A는 다음과 같은 상 삼각형을 포함합니다.
                대칭 행렬. 그렇지 않으면 A는 더 낮은 것을 포함합니다.
출력 매개 변수 :
    A - 인수 분해의 결과. IsUpper = True이면
                위 삼각형은 행렬 U를 포함하므로 A = U ^ T * U,
                주 대각선 아래의 요소는 수정되지 않습니다.
                마찬가지로 IsUpper = False 인 경우
결과:
    행렬이 양의 값이면 함수는 True를 반환합니다.
    그렇지 않으면 False를 반환합니다. A의 내용이 결정되지 않았습니다.
    그런 경우에.
  - ALGLIB 루틴 -
     15.12.2009
     보흐 카 노브 세르게이
*************************************************** ********************** */

bool spdmatrixcholesky(real_2d_array &a, const ae_int_t n, const bool isupper);

/*************************************************************************
Estimate of a matrix condition number (1-norm)

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
행렬 조건 수 (1-norm)의 추정
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double rmatrixrcond1(const real_2d_array &a, const ae_int_t n);


/*************************************************************************
Estimate of a matrix condition number (infinity-norm).

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
행렬 조건 수 (무한대 - 표준)의 추정.
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double rmatrixrcondinf(const real_2d_array &a, const ae_int_t n);


/*************************************************************************
Condition number estimate of a symmetric positive definite matrix.

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

It should be noted that 1-norm and inf-norm of condition numbers of symmetric
matrices are equal, so the algorithm doesn't take into account the
differences between these types of norms.

Input parameters:
    A       -   symmetric positive definite matrix which is given by its
                upper or lower triangle depending on the value of
                IsUpper. Array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   storage format.

Result:
    1/LowerBound(cond(A)), if matrix A is positive definite,
   -1, if matrix A is not positive definite, and its condition number
    could not be found by this algorithm.

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
대칭 포지티브 한정 행렬의 조건 번호 추정.
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
대칭 (symmetric) 조건 수의 1 표준 및 inf 표준
행렬이 같기 때문에 알고리즘은
이러한 규범 유형의 차이.
입력 매개 변수 :
    A - 그 대칭 긍정적 인 명확한 매트릭스는 주어진
                의 값에 따라 위 또는 아래 삼각형
                IsUpper. 요소가있는 배열 [0..N-1, 0..N-1].
    행렬 A의 N 크기
    IsUpper - 저장소 형식입니다.
결과:
    1 / LowerBound (cond (A)), 행렬 A가 양의 값이면,
   -1, 행렬 A가 양의 확률이 아니고 조건 번호
    이 알고리즘으로는 찾을 수 없습니다.
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double spdmatrixrcond(const real_2d_array &a, const ae_int_t n, const bool isupper);


/*************************************************************************
Triangular matrix: estimate of a condition number (1-norm)

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A       -   matrix. Array[0..N-1, 0..N-1].
    N       -   size of A.
    IsUpper -   True, if the matrix is upper triangular.
    IsUnit  -   True, if the matrix has a unit diagonal.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
삼각 행렬 : 조건 수의 추정 (1- 표준)
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 어레이 [0..N-1, 0..N-1].
    A.의 N - 크기
    IsUpper - 행렬이 위쪽 삼각형이면 참입니다.
    IsUnit - 행렬이 대각선 단위 인 경우 참입니다.
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double rmatrixtrrcond1(const real_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);


/*************************************************************************
Triangular matrix: estimate of a matrix condition number (infinity-norm).

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of matrix A.
    IsUpper -   True, if the matrix is upper triangular.
    IsUnit  -   True, if the matrix has a unit diagonal.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
삼각 행렬 : 행렬 조건 수 (무한대 - 표준)의 추정.
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    IsUpper - 행렬이 위쪽 삼각형이면 참입니다.
    IsUnit - 행렬이 대각선 단위 인 경우 참입니다.
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double rmatrixtrrcondinf(const real_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);


/*************************************************************************
Condition number estimate of a Hermitian positive definite matrix.

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

It should be noted that 1-norm and inf-norm of condition numbers of symmetric
matrices are equal, so the algorithm doesn't take into account the
differences between these types of norms.

Input parameters:
    A       -   Hermitian positive definite matrix which is given by its
                upper or lower triangle depending on the value of
                IsUpper. Array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   storage format.

Result:
    1/LowerBound(cond(A)), if matrix A is positive definite,
   -1, if matrix A is not positive definite, and its condition number
    could not be found by this algorithm.

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
Hermitian positive definite matrix의 조건 번호 추정.
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
대칭 (symmetric) 조건 수의 1 표준 및 inf 표준
행렬이 같기 때문에 알고리즘은
이러한 규범 유형의 차이.
입력 매개 변수 :
    A - Hermitian positive definite 행렬.
                의 값에 따라 위 또는 아래 삼각형
                IsUpper. 요소가있는 배열 [0..N-1, 0..N-1].
    행렬 A의 N 크기
    IsUpper - 저장소 형식입니다.
결과:
    1 / LowerBound (cond (A)), 행렬 A가 양의 값이면,
   -1, 행렬 A가 양의 확률이 아니고 조건 번호
    이 알고리즘으로는 찾을 수 없습니다.
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double hpdmatrixrcond(const complex_2d_array &a, const ae_int_t n, const bool isupper);


/*************************************************************************
Estimate of a matrix condition number (1-norm)

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
행렬 조건 수 (1-norm)의 추정
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double cmatrixrcond1(const complex_2d_array &a, const ae_int_t n);


/*************************************************************************
Estimate of a matrix condition number (infinity-norm).

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
행렬 조건 수 (무한대 - 표준)의 추정.
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double cmatrixrcondinf(const complex_2d_array &a, const ae_int_t n);


/*************************************************************************
Estimate of the condition number of a matrix given by its LU decomposition (1-norm)

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    LUA         -   LU decomposition of a matrix in compact form. Output of
                    the RMatrixLU subroutine.
    N           -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
LU 분해 (1-norm)에 의해 주어진 행렬의 조건 수의 추정
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    LUA - 콤팩트 형태의 행렬 분해. 출력
                    RMatrixLU 서브 루틴.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double rmatrixlurcond1(const real_2d_array &lua, const ae_int_t n);


/*************************************************************************
Estimate of the condition number of a matrix given by its LU decomposition
(infinity norm).

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    LUA     -   LU decomposition of a matrix in compact form. Output of
                the RMatrixLU subroutine.
    N       -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
LU 분해에 의해 주어진 행렬의 조건 수의 추정
(무한 표준).
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    LUA - 콤팩트 형태의 행렬 분해. 출력
                RMatrixLU 서브 루틴.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double rmatrixlurcondinf(const real_2d_array &lua, const ae_int_t n);


/*************************************************************************
Condition number estimate of a symmetric positive definite matrix given by
Cholesky decomposition.

The algorithm calculates a lower bound of the condition number. In this
case, the algorithm does not return a lower bound of the condition number,
but an inverse number (to avoid an overflow in case of a singular matrix).

It should be noted that 1-norm and inf-norm condition numbers of symmetric
matrices are equal, so the algorithm doesn't take into account the
differences between these types of norms.

Input parameters:
    CD  - Cholesky decomposition of matrix A,
          output of SMatrixCholesky subroutine.
    N   - size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
대칭 포지티브 한정 행렬의 조건 수 추정
콜레 스키 분해.
알고리즘은 조건 번호의 하한을 계산합니다. 이
경우, 알고리즘은 조건 번호의 하한을 반환하지 않고,
그러나 역수 (singular matrix의 경우 오버플로를 피하기 위해).
대칭의 1- 놈 및 놈 - 표준 조건 수
행렬이 같기 때문에 알고리즘은
이러한 규범 유형의 차이.
입력 매개 변수 :
    CD - 행렬 A의 콜레 스키 분해,
          SMatrixCholesky 서브 루틴의 출력.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double spdmatrixcholeskyrcond(const real_2d_array &a, const ae_int_t n, const bool isupper);


/*************************************************************************
Condition number estimate of a Hermitian positive definite matrix given by
Cholesky decomposition.

The algorithm calculates a lower bound of the condition number. In this
case, the algorithm does not return a lower bound of the condition number,
but an inverse number (to avoid an overflow in case of a singular matrix).

It should be noted that 1-norm and inf-norm condition numbers of symmetric
matrices are equal, so the algorithm doesn't take into account the
differences between these types of norms.

Input parameters:
    CD  - Cholesky decomposition of matrix A,
          output of SMatrixCholesky subroutine.
    N   - size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
Hermitian positive definite matrix의 조건 번호 추정
콜레 스키 분해.
알고리즘은 조건 번호의 하한을 계산합니다. 이
경우, 알고리즘은 조건 번호의 하한을 반환하지 않고,
그러나 역수 (singular matrix의 경우 오버플로를 피하기 위해).
대칭의 1- 놈 및 놈 - 표준 조건 수
행렬이 같기 때문에 알고리즘은
이러한 규범 유형의 차이.
입력 매개 변수 :
    CD - 행렬 A의 콜레 스키 분해,
          SMatrixCholesky 서브 루틴의 출력.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */


double hpdmatrixcholeskyrcond(const complex_2d_array &a, const ae_int_t n, const bool isupper);


/*************************************************************************
Estimate of the condition number of a matrix given by its LU decomposition (1-norm)

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    LUA         -   LU decomposition of a matrix in compact form. Output of
                    the CMatrixLU subroutine.
    N           -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
LU 분해 (1-norm)에 의해 주어진 행렬의 조건 수의 추정
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    LUA - 콤팩트 형태의 행렬 분해. 출력
                    CMatrixLU 서브 루틴.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double cmatrixlurcond1(const complex_2d_array &lua, const ae_int_t n);


/*************************************************************************
Estimate of the condition number of a matrix given by its LU decomposition
(infinity norm).

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    LUA     -   LU decomposition of a matrix in compact form. Output of
                the CMatrixLU subroutine.
    N       -   size of matrix A.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
LU 분해에 의해 주어진 행렬의 조건 수의 추정
(무한 표준).
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    LUA - 콤팩트 형태의 행렬 분해. 출력
                CMatrixLU 서브 루틴.
    행렬 A의 N 크기
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double cmatrixlurcondinf(const complex_2d_array &lua, const ae_int_t n);


/*************************************************************************
Triangular matrix: estimate of a condition number (1-norm)

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A       -   matrix. Array[0..N-1, 0..N-1].
    N       -   size of A.
    IsUpper -   True, if the matrix is upper triangular.
    IsUnit  -   True, if the matrix has a unit diagonal.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
삼각 행렬 : 조건 수의 추정 (1- 표준)
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 어레이 [0..N-1, 0..N-1].
    A.의 N - 크기
    IsUpper - 행렬이 위쪽 삼각형이면 참입니다.
    IsUnit - 행렬이 대각선 단위 인 경우 참입니다.
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double cmatrixtrrcond1(const complex_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);


/*************************************************************************
Triangular matrix: estimate of a matrix condition number (infinity-norm).

The algorithm calculates a lower bound of the condition number. In this case,
the algorithm does not return a lower bound of the condition number, but an
inverse number (to avoid an overflow in case of a singular matrix).

Input parameters:
    A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of matrix A.
    IsUpper -   True, if the matrix is upper triangular.
    IsUnit  -   True, if the matrix has a unit diagonal.

Result: 1/LowerBound(cond(A))

NOTE:
    if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
    0.0 is returned in such cases.
*************************************************************************/

/* ************************************************ *************************
삼각 행렬 : 행렬 조건 수 (무한대 - 표준)의 추정.
알고리즘은 조건 번호의 하한을 계산합니다. 이 경우,
알고리즘은 조건 번호의 하한을 반환하지 않지만
역수 (특이 행렬의 경우 오버플로를 피하기 위해).
입력 매개 변수 :
    - 매트릭스. 인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    IsUpper - 행렬이 위쪽 삼각형이면 참입니다.
    IsUnit - 행렬이 대각선 단위 인 경우 참입니다.
결과 : 1 / LowerBound (cond (A))
노트:
    k (A)가 매우 큰 경우, 행렬은 축 퇴성으로 가정하고, k (A) = INF,
    이 경우 0.0이 리턴됩니다.
*************************************************** ********************** */

double cmatrixtrrcondinf(const complex_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);

/*************************************************************************
Inversion of a matrix given by its LU decomposition.

INPUT PARAMETERS:
    A       -   LU decomposition of the matrix
                (output of RMatrixLU subroutine).
    Pivots  -   table of permutations
                (the output of RMatrixLU subroutine).
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)

OUTPUT PARAMETERS:
    Info    -   return code:
                * -3    A is singular, or VERY close to singular.
                        it is filled by zeros in such cases.
                *  1    task is solved (but matrix A may be ill-conditioned,
                        check R1/RInf parameters for condition numbers).
    Rep     -   solver report, see below for more info
    A       -   inverse of matrix A.
                Array whose indexes range within [0..N-1, 0..N-1].

SOLVER REPORT

Subroutine sets following fields of the Rep structure:
* R1        reciprocal of condition number: 1/cond(A), 1-norm.
* RInf      reciprocal of condition number: 1/cond(A), inf-norm.

  -- ALGLIB routine --
     05.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
그것의 LU 분해에 의해 주어지는 행렬의 역행렬.
입력 매개 변수 :
    A - 행렬의 LU 분해
                (RMatrixLU 서브 루틴의 출력).
    피벗 - 순열표
                (RMatrixLU 서브 루틴의 출력).
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
출력 매개 변수 :
    정보 - 리턴 코드 :
                * -3 A는 단수이거나 매우 단수에 가깝습니다.
                        이 경우에는 0으로 채워집니다.
                * 1 작업이 해결되었습니다 (단, 행렬 A는 상태가 좋지 않을 수 있으며,
                        조건 번호에 대한 R1 / RInf 매개 변수 확인).
    담당자 솔버 보고서, 자세한 정보는 아래를 참조하십시오.
    A - 행렬 A의 역함수
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
솔버 리포트
서브 루틴은 Rep 구조의 필드를 다음과 같이 설정합니다.
* R1은 조건 수의 역수입니다. 1 / cond (A), 1-norm.
* 조건 수의 역수 : 1 / cond (A), inf-norm.
  - ALGLIB 루틴 -
     05.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void rmatrixluinverse(real_2d_array &a, const integer_1d_array &pivots, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void rmatrixluinverse(real_2d_array &a, const integer_1d_array &pivots, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a general matrix.

Input parameters:
    A       -   matrix.
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)

Output parameters:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

Result:
    True, if the matrix is not singular.
    False, if the matrix is singular.

  -- ALGLIB --
     Copyright 2005-2010 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
일반 행렬의 반전.
입력 매개 변수 :
    - 매트릭스.
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
결과:
    행렬이 단일이 아닌 경우 참.
    행렬이 단수이면 False입니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2010
*************************************************** ********************** */

void rmatrixinverse(real_2d_array &a, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void rmatrixinverse(real_2d_array &a, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a matrix given by its LU decomposition.

INPUT PARAMETERS:
    A       -   LU decomposition of the matrix
                (output of CMatrixLU subroutine).
    Pivots  -   table of permutations
                (the output of CMatrixLU subroutine).
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)

OUTPUT PARAMETERS:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

  -- ALGLIB routine --
     05.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
그것의 LU 분해에 의해 주어지는 행렬의 역행렬.
입력 매개 변수 :
    A - 행렬의 LU 분해
                (CMatrixLU 서브 루틴의 출력).
    피벗 - 순열표
                (CMatrixLU 서브 루틴의 출력).
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
  - ALGLIB 루틴 -
     05.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void cmatrixluinverse(complex_2d_array &a, const integer_1d_array &pivots, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void cmatrixluinverse(complex_2d_array &a, const integer_1d_array &pivots, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a general matrix.

Input parameters:
    A       -   matrix
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)

Output parameters:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
일반 행렬의 반전.
입력 매개 변수 :
    A- 행렬
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

void cmatrixinverse(complex_2d_array &a, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void cmatrixinverse(complex_2d_array &a, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a symmetric positive definite matrix which is given
by Cholesky decomposition.

Input parameters:
    A       -   Cholesky decomposition of the matrix to be inverted:
                A=U\92*U or A = L*L'.
                Output of  SPDMatrixCholesky subroutine.
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)
    IsUpper -   storage type (optional):
                * if True, symmetric  matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t  used/changed  by
                  function
                * if False,  symmetric matrix  A  is  given  by  its lower
                  triangle, and the  upper triangle isn\92t used/changed  by
                  function
                * if not given, lower half is used.

Output parameters:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

  -- ALGLIB routine --
     10.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 대칭 포지티브 행렬의 역함수
콜레 스키 분해.
입력 매개 변수 :
    A - 뒤집을 행렬의 콜레 스키 분해 :
                A = U * U 또는 A = L * L '.
                SPDMatrixCholesky 서브 루틴의 출력.
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
    IsUpper - 저장소 유형 (선택 사항) :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형 및 아래 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형, 위 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * 주어지지 않았다면, 아래쪽 절반이 사용됩니다.
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
  - ALGLIB 루틴 -
     10.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void spdmatrixcholeskyinverse(real_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void spdmatrixcholeskyinverse(real_2d_array &a, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a symmetric positive definite matrix.

Given an upper or lower triangle of a symmetric positive definite matrix,
the algorithm generates matrix A^-1 and saves the upper or lower triangle
depending on the input.

Input parameters:
    A       -   matrix to be inverted (upper or lower triangle).
                Array with elements [0..N-1,0..N-1].
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)
    IsUpper -   storage type (optional):
                * if True, symmetric  matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t  used/changed  by
                  function
                * if False,  symmetric matrix  A  is  given  by  its lower
                  triangle, and the  upper triangle isn\92t used/changed  by
                  function
                * if not given,  both lower and upper  triangles  must  be
                  filled.

Output parameters:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

  -- ALGLIB routine --
     10.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭 포지티브 한정 행렬의 역전.
대칭 포지티브 한정 행렬의 상부 또는 하부 삼각형이 주어지면,
알고리즘은 행렬 A ^ -1을 생성하고 위 또는 아래 삼각형을 저장합니다
입력에 따라 다릅니다.
입력 매개 변수 :
    A - 뒤집을 수있는 행렬 (위쪽 또는 아래쪽 삼각형).
                요소가있는 배열 [0..N-1,0..N-1].
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
    IsUpper - 저장소 유형 (선택 사항) :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형 및 아래 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형, 위 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * 주어지지 않았다면, 아래쪽 삼각형과 위 쪽 삼각형 모두
                  채우는.
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
  - ALGLIB 루틴 -
     10.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void spdmatrixinverse(real_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void spdmatrixinverse(real_2d_array &a, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a Hermitian positive definite matrix which is given
by Cholesky decomposition.

Input parameters:
    A       -   Cholesky decomposition of the matrix to be inverted:
                A=U\92*U or A = L*L'.
                Output of  HPDMatrixCholesky subroutine.
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)
    IsUpper -   storage type (optional):
                * if True, symmetric  matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t  used/changed  by
                  function
                * if False,  symmetric matrix  A  is  given  by  its lower
                  triangle, and the  upper triangle isn\92t used/changed  by
                  function
                * if not given, lower half is used.

Output parameters:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

  -- ALGLIB routine --
     10.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
주어진 허미 시안 양의 정한 행렬의 역전
콜레 스키 분해.
입력 매개 변수 :
    A - 뒤집을 행렬의 콜레 스키 분해 :
                A = U * U 또는 A = L * L '.
                HPDMatrixCholesky 서브 루틴의 출력.
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
    IsUpper - 저장소 유형 (선택 사항) :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형 및 아래 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형, 위 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * 주어지지 않았다면, 아래쪽 절반이 사용됩니다.
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
  - ALGLIB 루틴 -
     10.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void hpdmatrixcholeskyinverse(complex_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void hpdmatrixcholeskyinverse(complex_2d_array &a, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Inversion of a Hermitian positive definite matrix.

Given an upper or lower triangle of a Hermitian positive definite matrix,
the algorithm generates matrix A^-1 and saves the upper or lower triangle
depending on the input.

Input parameters:
    A       -   matrix to be inverted (upper or lower triangle).
                Array with elements [0..N-1,0..N-1].
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)
    IsUpper -   storage type (optional):
                * if True, symmetric  matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t  used/changed  by
                  function
                * if False,  symmetric matrix  A  is  given  by  its lower
                  triangle, and the  upper triangle isn\92t used/changed  by
                  function
                * if not given,  both lower and upper  triangles  must  be
                  filled.

Output parameters:
    Info    -   return code, same as in RMatrixLUInverse
    Rep     -   solver report, same as in RMatrixLUInverse
    A       -   inverse of matrix A, same as in RMatrixLUInverse

  -- ALGLIB routine --
     10.02.2010
     Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
Hermitian positive definite matrix의 역전.
Hermitian positive definite matrix의 위 또는 아래 삼각형이 주어진다면,
알고리즘은 행렬 A ^ -1을 생성하고 위 또는 아래 삼각형을 저장합니다
입력에 따라 다릅니다.
입력 매개 변수 :
    A - 뒤집을 수있는 행렬 (위쪽 또는 아래쪽 삼각형).
                요소가있는 배열 [0..N-1,0..N-1].
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
    IsUpper - 저장소 유형 (선택 사항) :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형 및 아래 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형, 위 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * 주어지지 않았다면, 아래쪽 삼각형과 위 쪽 삼각형 모두
                  채우는.
출력 매개 변수 :
    Info - RMatrixLUInverse와 같은 리턴 코드
    Rep-solver report, RMatrixLUInverse와 동일
    A - 행렬 A의 역행렬, RMatrixLUInverse와 동일
  - ALGLIB 루틴 -
     10.02.2010
     보흐 카 노브 세르게이
*************************************************** ********************** */

void hpdmatrixinverse(complex_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void hpdmatrixinverse(complex_2d_array &a, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Triangular matrix inverse (real)

The subroutine inverts the following types of matrices:
    * upper triangular
    * upper triangular with unit diagonal
    * lower triangular
    * lower triangular with unit diagonal

In case of an upper (lower) triangular matrix,  the  inverse  matrix  will
also be upper (lower) triangular, and after the end of the algorithm,  the
inverse matrix replaces the source matrix. The elements  below (above) the
main diagonal are not changed by the algorithm.

If  the matrix  has a unit diagonal, the inverse matrix also  has  a  unit
diagonal, and the diagonal elements are not passed to the algorithm.

Input parameters:
    A       -   matrix, array[0..N-1, 0..N-1].
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)
    IsUpper -   True, if the matrix is upper triangular.
    IsUnit  -   diagonal type (optional):
                * if True, matrix has unit diagonal (a[i,i] are NOT used)
                * if False, matrix diagonal is arbitrary
                * if not given, False is assumed

Output parameters:
    Info    -   same as for RMatrixLUInverse
    Rep     -   same as for RMatrixLUInverse
    A       -   same as for RMatrixLUInverse.

  -- ALGLIB --
     Copyright 05.02.2010 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
삼각 행렬 역 (실수)
서브 루틴은 다음과 같은 유형의 행렬을 반전합니다.
    * 위 삼각형
    * 대각선의 위 삼각형
    * 낮은 삼각형
    * 대각선 길이가있는 삼각형의 하단
위 (아래) 삼각형 행렬의 경우 역행렬은
또한 위 (아래) 삼각형이고, 알고리즘의 끝 후에,
역행렬은 원 행렬을 대체합니다. 아래 (위) 요소는
주요 대각선은 알고리즘에 의해 변경되지 않습니다.
행렬이 대각선 단위 인 경우, 역행렬은 또한 유닛
대각선이며 대각선 요소는 알고리즘에 전달되지 않습니다.
입력 매개 변수 :
    A- 행렬, 어레이 [0..N-1, 0..N-1].
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
    IsUpper - 행렬이 위쪽 삼각형이면 참입니다.
    IsUnit - 대각선 타입 (옵션) :
                * True 인 경우 행렬은 단위 대각선을가집니다 (a [i, i]는 사용되지 않습니다)
                * 거짓 인 경우 대각선 행렬은 임의입니다.
                * 주어지지 않으면 False가 가정 됨
출력 매개 변수 :
    정보 - RMatrixLUInverse와 동일
    담당자 - RMatrixLUInverse와 동일
    A - RMatrixLUInverse와 동일합니다.
  - ALGLIB -
     저작권 05.02.2010 Bochkanov Sergey
*************************************************** ********************** */

void rmatrixtrinverse(real_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit, ae_int_t &info, matinvreport &rep);
void rmatrixtrinverse(real_2d_array &a, const bool isupper, ae_int_t &info, matinvreport &rep);


/*************************************************************************
Triangular matrix inverse (complex)

The subroutine inverts the following types of matrices:
    * upper triangular
    * upper triangular with unit diagonal
    * lower triangular
    * lower triangular with unit diagonal

In case of an upper (lower) triangular matrix,  the  inverse  matrix  will
also be upper (lower) triangular, and after the end of the algorithm,  the
inverse matrix replaces the source matrix. The elements  below (above) the
main diagonal are not changed by the algorithm.

If  the matrix  has a unit diagonal, the inverse matrix also  has  a  unit
diagonal, and the diagonal elements are not passed to the algorithm.

Input parameters:
    A       -   matrix, array[0..N-1, 0..N-1].
    N       -   size of matrix A (optional) :
                * if given, only principal NxN submatrix is processed  and
                  overwritten. other elements are unchanged.
                * if not given,  size  is  automatically  determined  from
                  matrix size (A must be square matrix)
    IsUpper -   True, if the matrix is upper triangular.
    IsUnit  -   diagonal type (optional):
                * if True, matrix has unit diagonal (a[i,i] are NOT used)
                * if False, matrix diagonal is arbitrary
                * if not given, False is assumed

Output parameters:
    Info    -   same as for RMatrixLUInverse
    Rep     -   same as for RMatrixLUInverse
    A       -   same as for RMatrixLUInverse.

  -- ALGLIB --
     Copyright 05.02.2010 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
삼각 행렬 역 (복소수)
서브 루틴은 다음과 같은 유형의 행렬을 반전합니다.
    * 위 삼각형
    * 대각선의 위 삼각형
    * 낮은 삼각형
    * 대각선 길이가있는 삼각형의 하단
위 (아래) 삼각형 행렬의 경우 역행렬은
또한 위 (아래) 삼각형이고, 알고리즘의 끝 후에,
역행렬은 원 행렬을 대체합니다. 아래 (위) 요소는
주요 대각선은 알고리즘에 의해 변경되지 않습니다.
행렬이 대각선 단위 인 경우, 역행렬은 또한 유닛
대각선이며 대각선 요소는 알고리즘에 전달되지 않습니다.
입력 매개 변수 :
    A- 행렬, 어레이 [0..N-1, 0..N-1].
    행렬 A의 N - 크기 (선택 사항) :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 지정하지 않으면 사이즈는 자동으로 결정됩니다.
                  행렬 크기 (A는 정사각형 행렬이어야 함)
    IsUpper - 행렬이 위쪽 삼각형이면 참입니다.
    IsUnit - 대각선 타입 (옵션) :
                * True 인 경우 행렬은 단위 대각선을가집니다 (a [i, i]는 사용되지 않습니다)
                * 거짓 인 경우 대각선 행렬은 임의입니다.
                * 주어지지 않으면 False가 가정 됨
출력 매개 변수 :
    정보 - RMatrixLUInverse와 동일
    담당자 - RMatrixLUInverse와 동일
    A - RMatrixLUInverse와 동일합니다.
  - ALGLIB -
     저작권 05.02.2010 Bochkanov Sergey
*************************************************** ********************** */

void cmatrixtrinverse(complex_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit, ae_int_t &info, matinvreport &rep);
void cmatrixtrinverse(complex_2d_array &a, const bool isupper, ae_int_t &info, matinvreport &rep);

/*************************************************************************
This function creates sparse matrix in a Hash-Table format.

This function creates Hast-Table matrix, which can be  converted  to  CRS
format after its initialization is over. Typical  usage  scenario  for  a
sparse matrix is:
1. creation in a Hash-Table format
2. insertion of the matrix elements
3. conversion to the CRS representation
4. matrix is passed to some linear algebra algorithm

Some  information  about  different matrix formats can be found below, in
the "NOTES" section.

INPUT PARAMETERS
    M           -   number of rows in a matrix, M>=1
    N           -   number of columns in a matrix, N>=1
    K           -   K>=0, expected number of non-zero elements in a matrix.
                    K can be inexact approximation, can be less than actual
                    number  of  elements  (table will grow when needed) or
                    even zero).
                    It is important to understand that although hash-table
                    may grow automatically, it is better to  provide  good
                    estimate of data size.

OUTPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table representation.
                    All elements of the matrix are zero.

NOTE 1.

Sparse matrices can be stored using either Hash-Table  representation  or
Compressed  Row  Storage  representation. Hast-table is better suited for
querying   and   dynamic   operations   (thus,  it  is  used  for  matrix
initialization), but it is inefficient when you want to make some  linear
algebra operations.

From the other side, CRS is better suited for linear algebra  operations,
but initialization is less convenient - you have to tell row sizes at the
initialization,  and  you  can  fill matrix only row by row, from left to
right. CRS is also very inefficient when you want to find matrix  element
by its index.

Thus,  Hash-Table  representation   does   not   support  linear  algebra
operations, while CRS format does not support modification of the  table.
Tables below outline information about these two formats:

    OPERATIONS WITH MATRIX      HASH        CRS
    create                      +           +
    read element                +           +
    modify element              +
    add value to element        +
    A*x  (dense vector)                     +
    A'*x (dense vector)                     +
    A*X  (dense matrix)                     +
    A'*X (dense matrix)                     +

NOTE 2.

Hash-tables use memory inefficiently, and they have to keep  some  amount
of the "spare memory" in order to have good performance. Hash  table  for
matrix with K non-zero elements will  need  C*K*(8+2*sizeof(int))  bytes,
where C is a small constant, about 1.5-2 in magnitude.

CRS storage, from the other side, is  more  memory-efficient,  and  needs
just K*(8+sizeof(int))+M*sizeof(int) bytes, where M is a number  of  rows
in a matrix.

When you convert from the Hash-Table to CRS  representation, all unneeded
memory will be freed.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 Hash-Table 형식으로 희소 행렬을 만듭니다.
이 함수는 CRS로 변환 될 수있는 Hast-Table 행렬을 생성합니다.
형식이 초기화 된 후에 종료됩니다. 일반적인 사용 시나리오
스파 스 매트릭스는 다음과 같습니다.
1. 해시 테이블 형식으로 생성
2. 행렬 요소 삽입
3. CRS 표현으로 변환
4. 행렬이 선형 대수 알고리즘으로 전달됩니다.
다른 행렬 형식에 대한 정보는 아래에서 확인할 수 있습니다.
"NOTES"섹션.
입력 매개 변수
    M - 행렬의 행 수, M> = 1
    N - 행렬의 열 수, N> = 1
    K - K> = 0, 행렬에서 예상되지 않은 원소의 예상 개수.
                    K는 정확하지 않은 근사값이 될 수 있으며 실제보다 작을 수 있습니다.
                    요소 수 (필요할 때 표가 늘어남) 또는
                    심지어 제로).
                    해시 테이블
                    자동으로 성장할 수 있습니다. 좋은 것을 제공하는 것이 좋습니다.
                    데이터 크기의 추정치.
출력 매개 변수
    S - 해시 테이블 표현의 M * N 행렬
                    행렬의 모든 원소는 0입니다.
참고 1.
스파 스 행렬은 해시 테이블 표현 또는
압축 된 행 저장 표현. Hast 테이블이 더 적합합니다.
질의 및 동적 연산 (따라서, 행렬
초기화), 선형화를 원할 때 비효율적입니다
대수 연산.
다른면에서 CRS는 선형 대수 연산에 더 적합하며,
하지만 초기화가 덜 편리합니다. 행 크기를
초기화 및 행을 행 단위로 채울 수 있습니다. 왼쪽에서 행까지
권리. CRS는 또한 행렬 요소를 찾고 싶을 때 매우 비효율적입니다.
그것의 색인에 의하여.
따라서 해시 테이블 표현은 선형 대수를 지원하지 않습니다.
CRS 형식은 테이블 수정을 지원하지 않습니다.
아래 표는이 두 가지 형식에 대한 개요 정보입니다.
    매트릭스 해시 CRS 작동
    + + 생성
    읽기 요소 + +
    수정 요소 +
    요소에 값 추가 +
    A * x (조밀 한 벡터) +
    A '* x (dense vector) +
    A * X (조밀 한 모체) +
    A '* X (dense matrix) +
노트 2.
해시 테이블은 메모리를 비효율적으로 사용하며 일정량을 유지해야합니다.
좋은 성능을 위해서는 "예비 메모리"가 필요합니다. 해시 테이블
K가 아닌 0 요소가있는 행렬은 C * K * (8 + 2 * sizeof (int)) 바이트가 필요하며,
여기서 C는 크기가 약 1.5-2 인 작은 상수입니다.
다른 측면에서 보면 CRS 저장소는 메모리 효율성이 높으며 필요성이 높습니다.
그냥 K * (8 + sizeof (int)) + M * sizeof (int) 바이트. 여기서 M은 행 수
행렬에.
해시 테이블에서 CRS로 변환 할 때 모든 불필요한
메모리가 해제됩니다.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsecreate(const ae_int_t m, const ae_int_t n, const ae_int_t k, sparsematrix &s);
void sparsecreate(const ae_int_t m, const ae_int_t n, sparsematrix &s);


/*************************************************************************
This function creates sparse matrix in a CRS format (expert function for
situations when you are running out of memory).

This function creates CRS matrix. Typical usage scenario for a CRS matrix
is:
1. creation (you have to tell number of non-zero elements at each row  at
   this moment)
2. insertion of the matrix elements (row by row, from left to right)
3. matrix is passed to some linear algebra algorithm

This function is a memory-efficient alternative to SparseCreate(), but it
is more complex because it requires you to know in advance how large your
matrix is. Some  information about  different matrix formats can be found
below, in the "NOTES" section.

INPUT PARAMETERS
    M           -   number of rows in a matrix, M>=1
    N           -   number of columns in a matrix, N>=1
    NER         -   number of elements at each row, array[M], NER[I]>=0

OUTPUT PARAMETERS
    S           -   sparse M*N matrix in CRS representation.
                    You have to fill ALL non-zero elements by calling
                    SparseSet() BEFORE you try to use this matrix.

NOTE 1.

Sparse matrices can be stored using either Hash-Table  representation  or
Compressed  Row  Storage  representation. Hast-table is better suited for
querying   and   dynamic   operations   (thus,  it  is  used  for  matrix
initialization), but it is inefficient when you want to make some  linear
algebra operations.

From the other side, CRS is better suited for linear algebra  operations,
but initialization is less convenient - you have to tell row sizes at the
initialization,  and  you  can  fill matrix only row by row, from left to
right. CRS is also very inefficient when you want to find matrix  element
by its index.

Thus,  Hash-Table  representation   does   not   support  linear  algebra
operations, while CRS format does not support modification of the  table.
Tables below outline information about these two formats:

    OPERATIONS WITH MATRIX      HASH        CRS
    create                      +           +
    read element                +           +
    modify element              +
    add value to element        +
    A*x  (dense vector)                     +
    A'*x (dense vector)                     +
    A*X  (dense matrix)                     +
    A'*X (dense matrix)                     +

NOTE 2.

Hash-tables use memory inefficiently, and they have to keep  some  amount
of the "spare memory" in order to have good performance. Hash  table  for
matrix with K non-zero elements will  need  C*K*(8+2*sizeof(int))  bytes,
where C is a small constant, about 1.5-2 in magnitude.

CRS storage, from the other side, is  more  memory-efficient,  and  needs
just K*(8+sizeof(int))+M*sizeof(int) bytes, where M is a number  of  rows
in a matrix.

When you convert from the Hash-Table to CRS  representation, all unneeded
memory will be freed.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 CRS 형식의 희소 행렬을 만듭니다 (
메모리가 부족한 상황).
이 함수는 CRS 행렬을 만듭니다. CRS 매트릭스의 일반적인 사용 시나리오
:
1. 생성 (각 행에서 0이 아닌 요소의 수를
   이 순간)
2. 행렬 요소 삽입 (행 단위, 왼쪽에서 오른쪽으로)
3. 행렬이 선형 대수 알고리즘으로 전달됩니다.
이 함수는 SparseCreate ()에 대한 메모리 효율적인 대안이지만,
더 복잡합니다. 사전에 얼마나 큰
행렬입니다. 다양한 매트릭스 형식에 대한 정보를 찾을 수 있습니다.
아래의 "메모"섹션에 나와 있습니다.
입력 매개 변수
    M - 행렬의 행 수, M> = 1
    N - 행렬의 열 수, N> = 1
    NER - 각 행의 요소 수, 배열 [M], NER [I]> = 0
출력 매개 변수
    S - CRS 표현의 M * N 매트릭스가 희박합니다.
                    호출로 모든 0이 아닌 요소를 채워야합니다.
                    SparseSet ()이 행렬을 사용하기 전에 시도하십시오.
참고 1.
스파 스 행렬은 해시 테이블 표현 또는
압축 된 행 저장 표현. Hast 테이블이 더 적합합니다.
질의 및 동적 연산 (따라서, 행렬
초기화), 선형화를 원할 때 비효율적입니다
대수 연산.
다른면에서 CRS는 선형 대수 연산에 더 적합하며,
하지만 초기화가 덜 편리합니다. 행 크기를
초기화 및 행을 행 단위로 채울 수 있습니다. 왼쪽에서 행까지
권리. CRS는 또한 행렬 요소를 찾고 싶을 때 매우 비효율적입니다.
그것의 색인에 의하여.
따라서 해시 테이블 표현은 선형 대수를 지원하지 않습니다.
CRS 형식은 테이블 수정을 지원하지 않습니다.
아래 표는이 두 가지 형식에 대한 개요 정보입니다.
    매트릭스 해시 CRS 작동
    + + 생성
    읽기 요소 + +
    수정 요소 +
    요소에 값 추가 +
    A * x (조밀 한 벡터) +
    A '* x (dense vector) +
    A * X (조밀 한 모체) +
    A '* X (dense matrix) +
노트 2.
해시 테이블은 메모리를 비효율적으로 사용하며 일정량을 유지해야합니다.
좋은 성능을 위해서는 "예비 메모리"가 필요합니다. 해시 테이블
K가 아닌 0 요소가있는 행렬은 C * K * (8 + 2 * sizeof (int)) 바이트가 필요하며,
여기서 C는 크기가 약 1.5-2 인 작은 상수입니다.
다른 측면에서 보면 CRS 저장소는 메모리 효율성이 높으며 필요성이 높습니다.
그냥 K * (8 + sizeof (int)) + M * sizeof (int) 바이트. 여기서 M은 행 수
행렬에.
해시 테이블에서 CRS로 변환 할 때 모든 불필요한
메모리가 해제됩니다.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsecreatecrs(const ae_int_t m, const ae_int_t n, const integer_1d_array &ner, sparsematrix &s);


/*************************************************************************
This function copies S0 to S1.

NOTE:  this  function  does  not verify its arguments, it just copies all
fields of the structure.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 기능은 S0를 S1로 복사합니다.
참고 :이 함수는 인수를 확인하지 않고 모든 인수를 확인합니다.
구조의 필드.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsecopy(const sparsematrix &s0, sparsematrix &s1);


/*************************************************************************
This function adds value to S[i,j] - element of the sparse matrix. Matrix
must be in a Hash-Table mode.

In case S[i,j] already exists in the table, V i added to  its  value.  In
case  S[i,j]  is  non-existent,  it  is  inserted  in  the  table.  Table
automatically grows when necessary.

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table representation.
                    Exception will be thrown for CRS matrix.
    I           -   row index of the element to modify, 0<=I<M
    J           -   column index of the element to modify, 0<=J<N
    V           -   value to add, must be finite number

OUTPUT PARAMETERS
    S           -   modified matrix

NOTE 1:  when  S[i,j]  is exactly zero after modification, it is  deleted
from the table.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 행렬의 S [i, j] 요소에 값을 추가합니다. 매트릭스
해시 테이블 모드 여야합니다.
S [i, j]가 이미 표에 존재하는 경우, V i는 그 값에 더해진다. 에서
케이스 S [i, j]가 존재하지 않으면 테이블에 삽입됩니다. 표
필요한 경우 자동으로 증가합니다.
입력 매개 변수
    S - 해시 테이블 표현의 M * N 행렬
                    CRS 행렬에 예외가 발생합니다.
    I - 수정할 요소의 행 인덱스, 0 ​​<= I <M
    J - 변경하는 요소의 열 인덱스, 0 ​​<= J <N
    V - 값을 추가하려면 유한 수 여야합니다.
출력 매개 변수
    S - 수정 된 매트릭스
NOTE 1 : S [i, j]가 수정 후 정확히 0 일 때, 그것은 삭제된다.
테이블에서.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparseadd(const sparsematrix &s, const ae_int_t i, const ae_int_t j, const double v);


/*************************************************************************
This function modifies S[i,j] - element of the sparse matrix.

For Hash-based storage format:
* new value can be zero or non-zero.  In case new value of S[i,j] is zero,
  this element is deleted from the table.
* this  function  has  no  effect when called with zero V for non-existent
  element.

For CRS-bases storage format:
* new value MUST be non-zero. Exception will be thrown for zero V.
* elements must be initialized in correct order -  from top row to bottom,
  within row - from left to right.

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table or CRS representation.
    I           -   row index of the element to modify, 0<=I<M
    J           -   column index of the element to modify, 0<=J<N
    V           -   value to set, must be finite number, can be zero

OUTPUT PARAMETERS
    S           -   modified matrix

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 행렬의 S [i, j] 요소를 수정합니다.
해시 기반 저장 형식 :
* 새 값은 0 또는 0이 될 수 없습니다. S [i, j]의 새로운 값이 0 인 경우,
  이 요소는 테이블에서 삭제됩니다.
*이 함수는 존재하지 않는 경우 0V로 호출하면 아무런 효과가 없습니다.
  요소.
CRS-base 저장 형식의 경우 :
* 새로운 값은 0이 아니어야합니다. V의 제로에 예외가 슬로우됩니다.
* 요소는 올바른 순서로 초기화되어야합니다 (상단 행에서 하단으로,
  행 내에서 - 왼쪽에서 오른쪽으로.
입력 매개 변수
    S - 해시 테이블 또는 CRS 표현의 M * N 매트릭스가 희박합니다.
    I - 수정할 요소의 행 인덱스, 0 ​​<= I <M
    J - 변경하는 요소의 열 인덱스, 0 ​​<= J <N
    V - 값을 설정하려면 유한 수 여야합니다.
출력 매개 변수
    S - 수정 된 매트릭스
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparseset(const sparsematrix &s, const ae_int_t i, const ae_int_t j, const double v);


/*************************************************************************
This function returns S[i,j] - element of the sparse matrix.  Matrix  can
be in any mode (Hash-Table or CRS), but this function is  less  efficient
for CRS matrices.  Hash-Table  matrices can  find element  in O(1)  time,
while  CRS  matrices  need O(log(RS)) time, where RS is an number of non-
zero elements in a row.

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table representation.
                    Exception will be thrown for CRS matrix.
    I           -   row index of the element to modify, 0<=I<M
    J           -   column index of the element to modify, 0<=J<N

RESULT
    value of S[I,J] or zero (in case no element with such index is found)

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 매트릭스의 원소 S [i, j]를 반환합니다. 행렬 수
어떤 모드 (Hash-Table 또는 CRS)에 있더라도이 기능은 비효율적입니다
CRS 행렬에 대해서. 해시 테이블 행렬은 O (1) 시간에 요소를 찾을 수 있으며,
CRS 행렬은 O (log (RS)) 시간을 필요로하는데, 여기서 RS는 비 -
연속적으로 제로 요소.
입력 매개 변수
    S - 해시 테이블 표현의 M * N 행렬
                    CRS 행렬에 예외가 발생합니다.
    I - 수정할 요소의 행 인덱스, 0 ​​<= I <M
    J - 변경하는 요소의 열 인덱스, 0 ​​<= J <N
결과
    S [I, J]의 값 또는 제로 (그러한 인덱스를 갖는 요소가 발견되지 않는 경우)
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

double sparseget(const sparsematrix &s, const ae_int_t i, const ae_int_t j);


/*************************************************************************
This function returns I-th diagonal element of the sparse matrix.

Matrix can be in any mode (Hash-Table or CRS storage), but this  function
is most efficient for CRS matrices - it requires less than 50 CPU  cycles
to extract diagonal element. For Hash-Table matrices we still  have  O(1)
query time, but function is many times slower.

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table representation.
                    Exception will be thrown for CRS matrix.
    I           -   index of the element to modify, 0<=I<min(M,N)

RESULT
    value of S[I,I] or zero (in case no element with such index is found)

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 행렬의 I 번째 대각 요소를 반환합니다.
매트릭스는 모든 모드 (해시 테이블 또는 CRS 저장소) 일 수 있지만이 기능
CRS 행렬에 대해 가장 효율적입니다. 50 개 미만의 CPU 사이클이 필요합니다.
대각선 성분을 추출한다. 해시 테이블 행렬에 대해서는 여전히 O (1)
쿼리 시간이지만 함수가 여러 번 느려집니다.
입력 매개 변수
    S - 해시 테이블 표현의 M * N 행렬
                    CRS 행렬에 예외가 발생합니다.
    I - 수정하는 요소의 인덱스, 0 ​​<= I <min (M, N)
결과
    S [I, I]의 값 또는 0 (그러한 색인을 가진 요소가 발견되지 않는 경우)
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

double sparsegetdiagonal(const sparsematrix &s, const ae_int_t i);


/*************************************************************************
This function converts matrix to CRS format.

Some  algorithms  (linear  algebra ones, for example) require matrices in
CRS format.

INPUT PARAMETERS
    S           -   sparse M*N matrix in any format

OUTPUT PARAMETERS
    S           -   matrix in CRS format

NOTE:  this  function  has  no  effect  when  called with matrix which is
already in CRS mode.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬을 CRS 형식으로 변환합니다.
일부 알고리즘 (예 : 선형 대수학)에서는 행렬을 필요로합니다.
CRS 형식.
입력 매개 변수
    모든 형식의 S - 드문 드문 한 M * N 행렬
출력 매개 변수
    CRS 형식의 S- 행렬
참고 :이 함수는 행렬과 함께 호출 할 때 아무 효과가 없습니다.
이미 CRS 모드입니다.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparseconverttocrs(const sparsematrix &s);


/*************************************************************************
This function calculates matrix-vector product  S*x.  Matrix  S  must  be
stored in CRS format (exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*N matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    X           -   array[N], input vector. For  performance  reasons  we
                    make only quick checks - we check that array size  is
                    at least N, but we do not check for NAN's or INF's.
    Y           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    Y           -   array[M], S*x

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 - 벡터 곱 S * x를 계산합니다. 행렬 S는 반드시 있어야합니다.
CRS 형식으로 저장됩니다 (예외가 발생합니다).
입력 매개 변수
    CRS 형식의 S - 희소 M * N 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    X - 배열 [N], 입력 벡터. 성능상의 이유로
                    빠른 검사 만하면됩니다. 배열 크기가
                    적어도 N,하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    Y - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    Y- 배열 [M], S * x
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsemv(const sparsematrix &s, const real_1d_array &x, real_1d_array &y);


/*************************************************************************
This function calculates matrix-vector product  S^T*x. Matrix S  must  be
stored in CRS format (exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*N matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    X           -   array[M], input vector. For  performance  reasons  we
                    make only quick checks - we check that array size  is
                    at least M, but we do not check for NAN's or INF's.
    Y           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    Y           -   array[N], S^T*x

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 - 벡터 곱 S ^ T * x를 계산합니다. 행렬 S는 반드시 있어야합니다.
CRS 형식으로 저장됩니다 (예외가 발생합니다).
입력 매개 변수
    CRS 형식의 S - 희소 M * N 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    X - 배열 [M], 입력 벡터. 성능상의 이유로
                    빠른 검사 만하면됩니다. 배열 크기가
                    적어도 M이긴하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    Y - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    Y - 배열 [N], S ^ T * x
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsemtv(const sparsematrix &s, const real_1d_array &x, real_1d_array &y);


/*************************************************************************
This function simultaneously calculates two matrix-vector products:
    S*x and S^T*x.
S must be square (non-rectangular) matrix stored in CRS format (exception
will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse N*N matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    X           -   array[N], input vector. For  performance  reasons  we
                    make only quick checks - we check that array size  is
                    at least N, but we do not check for NAN's or INF's.
    Y0          -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.
    Y1          -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    Y0          -   array[N], S*x
    Y1          -   array[N], S^T*x

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function. It also throws exception when S is non-square.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 두 개의 행렬 - 벡터 곱을 동시에 계산합니다.
    S * x와 S * T * x.
S는 CRS 형식으로 저장된 정사각형 (비 직사각형) 행렬이어야합니다 (예외
그렇지 않으면 던져 질 것이다).
입력 매개 변수
    CRS 형식의 S - 희소 N * N 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    X - 배열 [N], 입력 벡터. 성능상의 이유로
                    빠른 검사 만하면됩니다. 배열 크기가
                    적어도 N,하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    Y0 - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
    Y1 - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    Y0 - 배열 [N], S * x
    Y1 - 배열 [N], S ^ T * x
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능. S가 정사각형이 아닌 경우에도 예외가 발생합니다.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsemv2(const sparsematrix &s, const real_1d_array &x, real_1d_array &y0, real_1d_array &y1);


/*************************************************************************
This function calculates matrix-vector product  S*x, when S is  symmetric
matrix.  Matrix  S  must  be stored in  CRS  format  (exception  will  be
thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*M matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    IsUpper     -   whether upper or lower triangle of S is given:
                    * if upper triangle is given,  only   S[i,j] for j>=i
                      are used, and lower triangle is ignored (it can  be
                      empty - these elements are not referenced at all).
                    * if lower triangle is given,  only   S[i,j] for j<=i
                      are used, and upper triangle is ignored.
    X           -   array[N], input vector. For  performance  reasons  we
                    make only quick checks - we check that array size  is
                    at least N, but we do not check for NAN's or INF's.
    Y           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    Y           -   array[M], S*x

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 S가 대칭 일 때 행렬 - 벡터 곱 S * x를 계산합니다.
매트릭스. 매트릭스 S는 CRS 형식으로 저장해야합니다 (예외는
달리 던져).
입력 매개 변수
    CRS 형식의 S - 희소 M * M 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    IsUpper - S의 위 또는 아래 삼각형이 있는지 여부 :
                    * 상 삼각형이 주어지면, j> = i에 대해서 S [i, j] 만
                      가 사용되며, 아래 삼각형은 무시됩니다 (
                      비어 있음 -이 요소는 전혀 참조되지 않음).
                    * 아래 삼각형이 주어지면 j <= i에 대해서 S [i, j] 만
                      가 사용되고, 위 삼각형은 무시됩니다.
    X - 배열 [N], 입력 벡터. 성능상의 이유로
                    빠른 검사 만하면됩니다. 배열 크기가
                    적어도 N,하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    Y - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    Y- 배열 [M], S * x
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsesmv(const sparsematrix &s, const bool isupper, const real_1d_array &x, real_1d_array &y);


/*************************************************************************
This function calculates matrix-matrix product  S*A.  Matrix  S  must  be
stored in CRS format (exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*N matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    A           -   array[N][K], input dense matrix. For  performance reasons
                    we make only quick checks - we check that array size
                    is at least N, but we do not check for NAN's or INF's.
    K           -   number of columns of matrix (A).
    B           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    B           -   array[M][K], S*A

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 - 행렬 곱 S * A를 계산합니다. 행렬 S는 반드시 있어야합니다.
CRS 형식으로 저장됩니다 (예외가 발생합니다).
입력 매개 변수
    CRS 형식의 S - 희소 M * N 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    A - 배열 [N] [K], 조밀 한 행렬을 입력하십시오. 성능상의 이유로
                    우리는 빠른 검사 만합니다. 배열 크기를 확인합니다.
                    N 이상이지만 NAN이나 INF를 확인하지 않습니다.
    K - 행렬의 열 수 (A)
    B - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    B - 배열 [M] [K], S * A
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsemm(const sparsematrix &s, const real_2d_array &a, const ae_int_t k, real_2d_array &b);


/*************************************************************************
This function calculates matrix-matrix product  S^T*A. Matrix S  must  be
stored in CRS format (exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*N matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    A           -   array[M][K], input dense matrix. For performance reasons
                    we make only quick checks - we check that array size  is
                    at least M, but we do not check for NAN's or INF's.
    K           -   number of columns of matrix (A).
    B           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    B           -   array[N][K], S^T*A

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 - 행렬 곱 S ^ T * A를 계산합니다. 행렬 S는 반드시 있어야합니다.
CRS 형식으로 저장됩니다 (예외가 발생합니다).
입력 매개 변수
    CRS 형식의 S - 희소 M * N 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    A - 배열 [M] [K], 조밀 한 행렬을 입력하십시오. 성능상의 이유로
                    우리는 빠른 검사 만합니다. 배열 크기가
                    적어도 M이긴하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    K - 행렬의 열 수 (A)
    B - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    B - 배열 [N] [K], S ^ T * A
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */
void sparsemtm(const sparsematrix &s, const real_2d_array &a, const ae_int_t k, real_2d_array &b);


/*************************************************************************
This function simultaneously calculates two matrix-matrix products:
    S*A and S^T*A.
S must be square (non-rectangular) matrix stored in CRS format (exception
will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse N*N matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    A           -   array[N][K], input dense matrix. For performance reasons
                    we make only quick checks - we check that array size  is
                    at least N, but we do not check for NAN's or INF's.
    K           -   number of columns of matrix (A).
    B0          -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.
    B1          -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    B0          -   array[N][K], S*A
    B1          -   array[N][K], S^T*A

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function. It also throws exception when S is non-square.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 두 개의 행렬 - 행렬 곱을 동시에 계산합니다.
    S * A 및 S * T * A.
S는 CRS 형식으로 저장된 정사각형 (비 직사각형) 행렬이어야합니다 (예외
그렇지 않으면 던져 질 것이다).
입력 매개 변수
    CRS 형식의 S - 희소 N * N 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    A - 배열 [N] [K], 조밀 한 행렬을 입력하십시오. 성능상의 이유로
                    우리는 빠른 검사 만합니다. 배열 크기가
                    적어도 N,하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    K - 행렬의 열 수 (A)
    B0 - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
    B1 - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    B0 - 배열 [N] [K], S * A
    B1 - 배열 [N] [K], S ^ T * A
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능. S가 정사각형이 아닌 경우에도 예외가 발생합니다.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsemm2(const sparsematrix &s, const real_2d_array &a, const ae_int_t k, real_2d_array &b0, real_2d_array &b1);


/*************************************************************************
This function calculates matrix-matrix product  S*A, when S  is  symmetric
matrix.  Matrix  S  must  be stored  in  CRS  format  (exception  will  be
thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*M matrix in CRS format (you MUST convert  it
                    to CRS before calling this function).
    IsUpper     -   whether upper or lower triangle of S is given:
                    * if upper triangle is given,  only   S[i,j] for j>=i
                      are used, and lower triangle is ignored (it can  be
                      empty - these elements are not referenced at all).
                    * if lower triangle is given,  only   S[i,j] for j<=i
                      are used, and upper triangle is ignored.
    A           -   array[N][K], input dense matrix. For performance reasons
                    we make only quick checks - we check that array size is
                    at least N, but we do not check for NAN's or INF's.
    K           -   number of columns of matrix (A).
    B           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.

OUTPUT PARAMETERS
    B           -   array[M][K], S*A

NOTE: this function throws exception when called for non-CRS matrix.  You
must convert your matrix  with  SparseConvertToCRS()  before  using  this
function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 S가 대칭 일 때 행렬 행렬 곱 S * A를 계산합니다.
매트릭스. 매트릭스 S는 CRS 형식으로 저장해야합니다 (예외는
달리 던져).
입력 매개 변수
    CRS 형식의 S - 희소 M * M 행렬 (변환해야합니다
                    이 함수를 호출하기 전에 CRS에).
    IsUpper - S의 위 또는 아래 삼각형이 있는지 여부 :
                    * 상 삼각형이 주어지면, j> = i에 대해서 S [i, j] 만
                      가 사용되며, 아래 삼각형은 무시됩니다 (
                      비어 있음 -이 요소는 전혀 참조되지 않음).
                    * 아래 삼각형이 주어지면 j <= i에 대해서 S [i, j] 만
                      가 사용되고, 위 삼각형은 무시됩니다.
    A - 배열 [N] [K], 조밀 한 행렬을 입력하십시오. 성능상의 이유로
                    우리는 빠른 검사 만합니다. 배열 크기가
                    적어도 N,하지만 우리는 NAN이나 INF를 확인하지 않습니다.
    K - 행렬의 열 수 (A)
    B - 사전에 할당 된 출력 버퍼. 케이스 버퍼
                    크기가 너무 작아 결과를 저장할 수 없으면이 버퍼는
                    자동으로 크기가 조정됩니다.
출력 매개 변수
    B - 배열 [M] [K], S * A
참고 :이 함수는 non-CRS 행렬에 대해 호출 될 때 예외를 throw합니다. 당신
이것을 사용하기 전에 SparseConvertToCRS ()로 행렬을 변환해야합니다.
기능.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparsesmm(const sparsematrix &s, const bool isupper, const real_2d_array &a, const ae_int_t k, real_2d_array &b);


/*************************************************************************
This procedure resizes Hash-Table matrix. It can be called when you  have
deleted too many elements from the matrix, and you want to  free unneeded
memory.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 절차는 해시 테이블 행렬의 크기를 조정합니다. 가지고있을 때 호출 할 수 있습니다.
행렬에서 너무 많은 요소를 삭제했으며 불필요한 요소를 제거하려고합니다.
기억.
  - ALGLIB 프로젝트 -
     저작권 14.10.2011 Bochkanov Sergey
*************************************************** ********************** */

void sparseresizematrix(const sparsematrix &s);


/*************************************************************************
This  function  is  used  to enumerate all elements of the sparse matrix.
Before  first  call  user  initializes  T0 and T1 counters by zero. These
counters are used to remember current position in a  matrix;  after  each
call they are updated by the function.

Subsequent calls to this function return non-zero elements of the  sparse
matrix, one by one. If you enumerate CRS matrix, matrix is traversed from
left to right, from top to bottom. In case you enumerate matrix stored as
Hash table, elements are returned in random order.

EXAMPLE
    > T0=0
    > T1=0
    > while SparseEnumerate(S,T0,T1,I,J,V) do
    >     ....do something with I,J,V

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table or CRS representation.
    T0          -   internal counter
    T1          -   internal counter

OUTPUT PARAMETERS
    T0          -   new value of the internal counter
    T1          -   new value of the internal counter
    I           -   row index of non-zero element, 0<=I<M.
    J           -   column index of non-zero element, 0<=J<N
    V           -   value of the T-th element

RESULT
    True in case of success (next non-zero element was retrieved)
    False in case all non-zero elements were enumerated

  -- ALGLIB PROJECT --
     Copyright 14.03.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 행렬의 모든 요소를 ​​열거하기 위해 사용됩니다.
처음 호출하기 전에 사용자는 T0 및 T1 카운터를 0으로 초기화합니다. 이들
카운터는 행렬의 현재 위치를 기억하는 데 사용됩니다. 각 후
함수에 의해 업데이트됩니다.
이 함수에 대한 후속 호출은 스파 스의 0이 아닌 요소를 반환합니다.
매트릭스, 하나씩. CRS 행렬을 열거하면, 행렬은
왼쪽에서 오른쪽으로, 위에서 아래로. 당신이 행렬을 열거 한 경우
해시 테이블, 요소는 임의의 순서로 반환됩니다.
예
    > T0 = 0
    > T1 = 0
    > 반면 SparseEnumerate (S, T0, T1, I, J, V)는 다음을 수행합니다.
    > .... I, J, V로 뭔가해라.
입력 매개 변수
    S - 해시 테이블 또는 CRS 표현의 M * N 매트릭스가 희박합니다.
    T0 - 내부 카운터
    T1 - 내부 카운터
출력 매개 변수
    T0 - 내부 카운터의 새로운 값
    T1 - 내부 카운터의 새로운 값
    I - 0이 아닌 요소의 행 인덱스, 0 ​​<= I <M.
    J - 0이 아닌 요소의 열 색인, 0 <= J <N
    V - T 번째 요소의 값
결과
    성공의 경우 참 (다음 0이 아닌 요소가 검색 됨)
    모든 0이 아닌 요소가 열거 된 경우 거짓
  - ALGLIB 프로젝트 -
     Copyright 14.03.2012 Bochkanov Sergey
*************************************************** ********************** */

bool sparseenumerate(const sparsematrix &s, ae_int_t &t0, ae_int_t &t1, ae_int_t &i, ae_int_t &j, double &v);


/*************************************************************************
This function rewrites existing (non-zero) element. It  returns  True   if
element  exists  or  False,  when  it  is  called for non-existing  (zero)
element.

The purpose of this function is to provide convenient thread-safe  way  to
modify  sparse  matrix.  Such  modification  (already  existing element is
rewritten) is guaranteed to be thread-safe without any synchronization, as
long as different threads modify different elements.

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table or CRS representation.
    I           -   row index of non-zero element to modify, 0<=I<M
    J           -   column index of non-zero element to modify, 0<=J<N
    V           -   value to rewrite, must be finite number

OUTPUT PARAMETERS
    S           -   modified matrix
RESULT
    True in case when element exists
    False in case when element doesn't exist or it is zero

  -- ALGLIB PROJECT --
     Copyright 14.03.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 기존 (0이 아닌) 요소를 다시 씁니다. True를 반환하는 경우 if
요소가 존재하지 않거나 거짓이면, 존재하지 않는 (제로)
요소.
이 함수의 목적은 스레드에 대한 편리한 방법을 제공하는 것입니다.
스파 스 매트릭스를 수정하십시오. 그러한 수정 (이미 존재하는 요소는
재 작성)은, 동기를 가지지 않는 thread 세이프 인 것이 보증되고 있습니다.
서로 다른 스레드가 다른 요소를 수정하면 오래.
입력 매개 변수
    S - 해시 테이블 또는 CRS 표현의 M * N 매트릭스가 희박합니다.
    I - 수정할 0이 아닌 요소의 행 인덱스, 0 ​​<= I <M
    J - 변경하는 0이 아닌 요소의 열 색인, 0 <= J <N
    V - 재 작성 값은 유한 수 여야합니다.
출력 매개 변수
    S - 수정 된 매트릭스
결과
    요소가있는 경우 true
    요소가 없거나 0 인 경우 거짓입니다.
  - ALGLIB 프로젝트 -
     Copyright 14.03.2012 Bochkanov Sergey
*************************************************** ********************** */

bool sparserewriteexisting(const sparsematrix &s, const ae_int_t i, const ae_int_t j, const double v);


/*************************************************************************
This function returns I-th row of the sparse matrix stored in CRS format.

NOTE: when  incorrect  I  (outside  of  [0,M-1]) or  matrix (non-CRS)  are
      passed, this function throws exception.

INPUT PARAMETERS:
    S           -   sparse M*N matrix in CRS format
    I           -   row index, 0<=I<M
    IRow        -   output buffer, can be  preallocated.  In  case  buffer
                    size  is  too  small  to  store  I-th   row,   it   is
                    automatically reallocated.

OUTPUT PARAMETERS:
    IRow        -   array[M], I-th row.


  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 CRS 형식으로 저장된 스파 스 행렬의 I 번째 행을 반환합니다.
참고 : 잘못된 I ([0, M-1] 외부) 또는 행렬 (비 CRS)이
      이 함수는 예외를 throw합니다.
입력 매개 변수 :
    CRS 형식의 S - 드문 드문 한 M * N 행렬
    I - 행 인덱스, 0 ​​<= I <M
    IRow - 출력 버퍼. 미리 할당 할 수 있습니다. 케이스 버퍼
                    크기가 너무 커서 I 번째 행을 저장할 수 없습니다.
                    자동으로 재 할당됩니다.
출력 매개 변수 :
    IRow 배열 [M], I 행.
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

void sparsegetrow(const sparsematrix &s, const ae_int_t i, real_1d_array &irow);


/*************************************************************************
This function performs in-place conversion from CRS format to  Hash  table
storage.

INPUT PARAMETERS
    S           -   sparse matrix in CRS format.

OUTPUT PARAMETERS
    S           -   sparse matrix in Hash table format.

NOTE:  this  function  has  no  effect  when  called with matrix which is
already in Hash table mode.

  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 CRS 형식에서 해시 테이블로 내부 변환을 수행합니다.
저장.
입력 매개 변수
    S - CRS 형식의 희소 행렬
출력 매개 변수
    S - 해시 테이블 형식의 희소 매트릭스.
참고 :이 함수는 행렬과 함께 호출 할 때 아무 효과가 없습니다.
이미 해시 테이블 모드입니다.
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

void sparseconverttohash(const sparsematrix &s);


/*************************************************************************
This  function  performs  out-of-place  conversion  to  Hash table storage
format. S0 is copied to S1 and converted on-the-fly.

INPUT PARAMETERS
    S0          -   sparse matrix in any format.

OUTPUT PARAMETERS
    S1          -   sparse matrix in Hash table format.

NOTE: if S0 is stored as Hash-table, it is just copied without conversion.

  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 해시 테이블 저장소로의 임시 변환을 수행합니다.
체재. S0가 S1로 복사되고 직접 변환됩니다.
입력 매개 변수
    S0 - 모든 형식의 희소 행렬
출력 매개 변수
    S1 - 해시 테이블 형식의 희소 매트릭스.
참고 : S0가 해시 테이블로 저장되면 변환없이 복사됩니다.
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

void sparsecopytohash(const sparsematrix &s0, sparsematrix &s1);


/*************************************************************************
This  function  performs  out-of-place  conversion  to  CRS format.  S0 is
copied to S1 and converted on-the-fly.

INPUT PARAMETERS
    S0          -   sparse matrix in any format.

OUTPUT PARAMETERS
    S1          -   sparse matrix in CRS format.

NOTE: if S0 is stored as CRS, it is just copied without conversion.

  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 CRS 형식으로 부재 중 변환을 수행합니다. S0는
S1로 복사되고 직접 변환됩니다.
입력 매개 변수
    S0 - 모든 형식의 희소 행렬
출력 매개 변수
    S1 - CRS 형식의 희소 행렬
참고 : S0이 CRS로 저장되면 변환없이 복사됩니다.
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

void sparsecopytocrs(const sparsematrix &s0, sparsematrix &s1);


/*************************************************************************
This function returns type of the matrix storage format.

INPUT PARAMETERS:
    S           -   sparse matrix.

RESULT:
    sparse storage format used by matrix:
        0   -   Hash-table
        1   -   CRS-format

NOTE: future  versions  of  ALGLIB  may  include additional sparse storage
      formats.


  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 저장 형식의 형식을 반환합니다.
입력 매개 변수 :
    S - 드문 드문 한 행렬.
결과:
    행렬에 사용되는 스파 스 저장 형식 :
        0 - 해시 테이블
        1 - CRS 형식
참고 : 이후 버전의 ALGLIB 추가 스파 스 저장소를 포함 할 수 있습니다
      형식.
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

ae_int_t sparsegetmatrixtype(const sparsematrix &s);


/*************************************************************************
This function checks matrix storage format and returns True when matrix is
stored using Hash table representation.

INPUT PARAMETERS:
    S   -   sparse matrix.

RESULT:
    True if matrix type is Hash table
    False if matrix type is not Hash table

  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 저장 형식을 검사하고 행렬이있는 경우 True를 반환합니다.
해시 테이블 표현을 사용하여 저장됩니다.
입력 매개 변수 :
    S - 드문 드문 한 행렬.
결과:
    행렬 타입이 해시 테이블 인 경우 참
    행렬 유형이 해시 테이블이 아닌 경우 거짓
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

bool sparseishash(const sparsematrix &s);


/*************************************************************************
This function checks matrix storage format and returns True when matrix is
stored using CRS representation.

INPUT PARAMETERS:
    S   -   sparse matrix.

RESULT:
    True if matrix type is CRS
    False if matrix type is not CRS

  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 행렬 저장 형식을 검사하고 행렬이있는 경우 True를 반환합니다.
CRS 표현을 사용하여 저장.
입력 매개 변수 :
    S - 드문 드문 한 행렬.
결과:
    행렬 유형이 CRS이면 참
    행렬 유형이 CRS가 아닌 경우 거짓
  - ALGLIB 프로젝트 -
     저작권 20.07.2012 Bochkanov Sergey
*************************************************** ********************** */

bool sparseiscrs(const sparsematrix &s);


/*************************************************************************
The function frees all memory occupied by  sparse  matrix.  Sparse  matrix
structure becomes unusable after this call.

OUTPUT PARAMETERS
    S   -   sparse matrix to delete

  -- ALGLIB PROJECT --
     Copyright 24.07.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 희소 행렬에 의해 점유 된 모든 메모리를 해제합니다. 스파 스 매트릭스
이 호출 후에 구조체를 사용할 수 없게됩니다.
출력 매개 변수
    S - 삭제할 희소 행렬
  - ALGLIB 프로젝트 -
     Copyright 24.07.2012 Bochkanov Sergey
*************************************************** ********************** */

void sparsefree(sparsematrix &s);


/*************************************************************************
The function returns number of rows of a sparse matrix.

RESULT: number of rows of a sparse matrix.

  -- ALGLIB PROJECT --
     Copyright 23.08.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 행렬의 행 수를 반환합니다.
결과 : 스파 스 매트릭스의 행 수입니다.
  - ALGLIB 프로젝트 -
     저작권 23.08.2012 Bochkanov Sergey
*************************************************** ********************** */

ae_int_t sparsegetnrows(const sparsematrix &s);


/*************************************************************************
The function returns number of columns of a sparse matrix.

RESULT: number of columns of a sparse matrix.

  -- ALGLIB PROJECT --
     Copyright 23.08.2012 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 행렬의 열 수를 반환합니다.
결과 : 스파 스 매트릭스의 열 수입니다.
  - ALGLIB 프로젝트 -
     저작권 23.08.2012 Bochkanov Sergey
*************************************************** ********************** */

ae_int_t sparsegetncols(const sparsematrix &s);


/*************************************************************************
This procedure initializes matrix norm estimator.

USAGE:
1. User initializes algorithm state with NormEstimatorCreate() call
2. User calls NormEstimatorEstimateSparse() (or NormEstimatorIteration())
3. User calls NormEstimatorResults() to get solution.

INPUT PARAMETERS:
    M       -   number of rows in the matrix being estimated, M>0
    N       -   number of columns in the matrix being estimated, N>0
    NStart  -   number of random starting vectors
                recommended value - at least 5.
    NIts    -   number of iterations to do with best starting vector
                recommended value - at least 5.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTE: this algorithm is effectively deterministic, i.e. it always  returns
same result when repeatedly called for the same matrix. In fact, algorithm
uses randomized starting vectors, but internal  random  numbers  generator
always generates same sequence of the random values (it is a  feature, not
bug).

Algorithm can be made non-deterministic with NormEstimatorSetSeed(0) call.

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 절차는 행렬 노멀 추정량을 초기화합니다.
용법:
1. 사용자는 NormEstimatorCreate () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자 호출 NormEstimatorEstimateSparse () (또는 NormEstimatorIteration ())
3. 사용자가 NormEstimatorResults ()를 호출하여 솔루션을 얻습니다.
입력 매개 변수 :
    M - 추정되는 행렬의 행 수, M> 0
    N - 추정되는 행렬의 열 수, N> 0
    NStart - 임의 시작 벡터의 수
                권장 값 - 적어도 5.
    NIts - 최고의 시작 벡터와 관련된 반복 횟수
                권장 값 - 적어도 5.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참고 :이 알고리즘은 효과적으로 결정적입니다. 즉 항상 반환합니다.
동일한 행렬에 대해 반복적으로 호출 될 때 동일한 결과가 나타납니다. 사실, 알고리즘
랜덤 화 된 시작 벡터를 사용하지만 내부 난수 생성기
항상 랜덤 값의 동일한 시퀀스를 생성합니다 (이 기능은
곤충).
NormEstimatorSetSeed (0) 호출로 알고리즘을 비 결정적으로 만들 수 있습니다.
  - ALGLIB -
     저작권 06.12.2011 Bochkanov Sergey
*************************************************** ********************** */

void normestimatorcreate(const ae_int_t m, const ae_int_t n, const ae_int_t nstart, const ae_int_t nits, normestimatorstate &state);


/*************************************************************************
This function changes seed value used by algorithm. In some cases we  need
deterministic processing, i.e. subsequent calls must return equal results,
in other cases we need non-deterministic algorithm which returns different
results for the same matrix on every pass.

Setting zero seed will lead to non-deterministic algorithm, while non-zero
value will make our algorithm deterministic.

INPUT PARAMETERS:
    State       -   norm estimator state, must be initialized with a  call
                    to NormEstimatorCreate()
    SeedVal     -   seed value, >=0. Zero value = non-deterministic algo.

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 알고리즘에 사용되는 시드 값을 변경합니다. 어떤 경우에는 우리가 필요로한다.
즉 후속 호출은 동일한 결과를 반환해야하며,
다른 경우에는 다른 것을 반환하는 비 결정적 알고리즘이 필요합니다.
매 패스마다 같은 매트릭스에 대한 결과.
제로 시드를 설정하면 비 결정적 알고리즘으로 이어지며 0이 아닌 값은
값은 알고리즘을 결정적으로 만듭니다.
입력 매개 변수 :
    상태 - 표준 추정기 상태, 호출로 초기화되어야 함
                    NormEstimatorCreate ()에
    SeedVal - 시드 값,> = 0. 0 값 = 비 결정적 알 고.
  - ALGLIB -
     저작권 06.12.2011 Bochkanov Sergey
*************************************************** ********************** */

void normestimatorsetseed(const normestimatorstate &state, const ae_int_t seedval);


/*************************************************************************
This function estimates norm of the sparse M*N matrix A.

INPUT PARAMETERS:
    State       -   norm estimator state, must be initialized with a  call
                    to NormEstimatorCreate()
    A           -   sparse M*N matrix, must be converted to CRS format
                    prior to calling this function.

After this function  is  over  you can call NormEstimatorResults() to get
estimate of the norm(A).

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
이 함수는 스파 스 M * N 행렬 A의 노름을 추정합니다.
입력 매개 변수 :
    상태 - 표준 추정기 상태, 호출로 초기화되어야 함
                    NormEstimatorCreate ()에
    A - 희소 M * N 행렬, CRS 형식으로 변환해야 함
                    이 함수를 호출하기 전에
이 함수가 끝나면 NormEstimatorResults ()를 호출하여
규범 (A)의 추정치.
  - ALGLIB -
     저작권 06.12.2011 Bochkanov Sergey
*************************************************** ********************** */

void normestimatorestimatesparse(const normestimatorstate &state, const sparsematrix &a);


/*************************************************************************
Matrix norm estimation results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    Nrm     -   estimate of the matrix norm, Nrm>=0

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
행렬 규범 추정 결과
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    Nrm - 행렬 노름의 추정치, Nrm> = 0
  - ALGLIB -
     저작권 06.12.2011 Bochkanov Sergey
*************************************************** **********************/

void normestimatorresults(const normestimatorstate &state, double &nrm);

/*************************************************************************
Determinant calculation of the matrix given by its LU decomposition.

Input parameters:
    A       -   LU decomposition of the matrix (output of
                RMatrixLU subroutine).
    Pivots  -   table of permutations which were made during
                the LU decomposition.
                Output of RMatrixLU subroutine.
    N       -   (optional) size of matrix A:
                * if given, only principal NxN submatrix is processed and
                  overwritten. other elements are unchanged.
                * if not given, automatically determined from matrix size
                  (A must be square matrix)

Result: matrix determinant.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
그것의 LU 분해에 의해 주어진 매트릭스의 결정 인자 계산.
입력 매개 변수 :
    A - 매트릭스의 LU 분해 (
                RMatrixLU 서브 루틴).
    피벗 (Pivots) - 진행되는 순열 표
                LU 분해.
                RMatrixLU 서브 루틴의 출력.
    N - (선택 사항) 행렬 A의 크기 :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 주어지지 않은 경우 행렬 크기에서 자동으로 결정됩니다.
                  (A는 정사각형 행렬이어야 함)
결과 : 행렬식.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

double rmatrixludet(const real_2d_array &a, const integer_1d_array &pivots, const ae_int_t n);
double rmatrixludet(const real_2d_array &a, const integer_1d_array &pivots);


/*************************************************************************
Calculation of the determinant of a general matrix

Input parameters:
    A       -   matrix, array[0..N-1, 0..N-1]
    N       -   (optional) size of matrix A:
                * if given, only principal NxN submatrix is processed and
                  overwritten. other elements are unchanged.
                * if not given, automatically determined from matrix size
                  (A must be square matrix)

Result: determinant of matrix A.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
일반 행렬의 행렬식의 계산
입력 매개 변수 :
    A- 행렬, 어레이 [0..N-1, 0..N-1]
    N - (선택 사항) 행렬 A의 크기 :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 주어지지 않은 경우 행렬 크기에서 자동으로 결정됩니다.
                  (A는 정사각형 행렬이어야 함)
결과 : 행렬 A의 행렬식
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

double rmatrixdet(const real_2d_array &a, const ae_int_t n);
double rmatrixdet(const real_2d_array &a);


/*************************************************************************
Determinant calculation of the matrix given by its LU decomposition.

Input parameters:
    A       -   LU decomposition of the matrix (output of
                RMatrixLU subroutine).
    Pivots  -   table of permutations which were made during
                the LU decomposition.
                Output of RMatrixLU subroutine.
    N       -   (optional) size of matrix A:
                * if given, only principal NxN submatrix is processed and
                  overwritten. other elements are unchanged.
                * if not given, automatically determined from matrix size
                  (A must be square matrix)

Result: matrix determinant.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
그것의 LU 분해에 의해 주어진 매트릭스의 결정 인자 계산.
입력 매개 변수 :
    A - 매트릭스의 LU 분해 (
                RMatrixLU 서브 루틴).
    피벗 (Pivots) - 진행되는 순열 표
                LU 분해.
                RMatrixLU 서브 루틴의 출력.
    N - (선택 사항) 행렬 A의 크기 :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 주어지지 않은 경우 행렬 크기에서 자동으로 결정됩니다.
                  (A는 정사각형 행렬이어야 함)
결과 : 행렬식.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

alglib::complex cmatrixludet(const complex_2d_array &a, const integer_1d_array &pivots, const ae_int_t n);
alglib::complex cmatrixludet(const complex_2d_array &a, const integer_1d_array &pivots);


/*************************************************************************
Calculation of the determinant of a general matrix

Input parameters:
    A       -   matrix, array[0..N-1, 0..N-1]
    N       -   (optional) size of matrix A:
                * if given, only principal NxN submatrix is processed and
                  overwritten. other elements are unchanged.
                * if not given, automatically determined from matrix size
                  (A must be square matrix)

Result: determinant of matrix A.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
일반 행렬의 행렬식의 계산
입력 매개 변수 :
    A- 행렬, 어레이 [0..N-1, 0..N-1]
    N - (선택 사항) 행렬 A의 크기 :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 주어지지 않은 경우 행렬 크기에서 자동으로 결정됩니다.
                  (A는 정사각형 행렬이어야 함)
결과 : 행렬 A의 행렬식
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

alglib::complex cmatrixdet(const complex_2d_array &a, const ae_int_t n);
alglib::complex cmatrixdet(const complex_2d_array &a);


/*************************************************************************
Determinant calculation of the matrix given by the Cholesky decomposition.

Input parameters:
    A       -   Cholesky decomposition,
                output of SMatrixCholesky subroutine.
    N       -   (optional) size of matrix A:
                * if given, only principal NxN submatrix is processed and
                  overwritten. other elements are unchanged.
                * if not given, automatically determined from matrix size
                  (A must be square matrix)

As the determinant is equal to the product of squares of diagonal elements,
it\92s not necessary to specify which triangle - lower or upper - the matrix
is stored in.

Result:
    matrix determinant.

  -- ALGLIB --
     Copyright 2005-2008 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
oles레 스키 분해에 의해 주어진 행렬의 결정 계수 계산.
입력 매개 변수 :
    A - 콜레 스키 분해,
                SMatrixCholesky 서브 루틴의 출력.
    N - (선택 사항) 행렬 A의 크기 :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 주어지지 않은 경우 행렬 크기에서 자동으로 결정됩니다.
                  (A는 정사각형 행렬이어야 함)
행렬식이 대각 원소의 제곱의 곱과 동일하기 때문에,
그것은 삼각형을 지정하는 데 필요하지 않습니다 - 위 또는 아래 - 행렬
에 저장됩니다.
결과:
    행렬식 결정자.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2008
*************************************************** ********************** */

double spdmatrixcholeskydet(const real_2d_array &a, const ae_int_t n);
double spdmatrixcholeskydet(const real_2d_array &a);


/*************************************************************************
Determinant calculation of the symmetric positive definite matrix.

Input parameters:
    A       -   matrix. Array with elements [0..N-1, 0..N-1].
    N       -   (optional) size of matrix A:
                * if given, only principal NxN submatrix is processed and
                  overwritten. other elements are unchanged.
                * if not given, automatically determined from matrix size
                  (A must be square matrix)
    IsUpper -   (optional) storage type:
                * if True, symmetric matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t used/changed  by
                  function
                * if False, symmetric matrix  A  is  given  by  its lower
                  triangle, and the upper triangle isn\92t used/changed  by
                  function
                * if not given, both lower and upper  triangles  must  be
                  filled.

Result:
    determinant of matrix A.
    If matrix A is not positive definite, exception is thrown.

  -- ALGLIB --
     Copyright 2005-2008 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
대칭 positive definite matrix의 결정자 계산.
입력 매개 변수 :
    - 매트릭스. 요소가있는 배열 [0..N-1, 0..N-1].
    N - (선택 사항) 행렬 A의 크기 :
                * 주어진 경우 주 NxN 서브 매트릭스 만 처리되고
                  덮어 쓴. 다른 요소는 변경되지 않습니다.
                * 주어지지 않은 경우 행렬 크기에서 자동으로 결정됩니다.
                  (A는 정사각형 행렬이어야 함)
    IsUpper - (선택 사항) 저장 유형 :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형 및 아래 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형, 위 삼각형은 사용 / 변경자가 아닙니다.
                  기능
                * 주어지지 않았다면, 아래쪽 삼각형과 위 쪽 삼각형 모두
                  채우는.
결과:
    행렬 A의 행렬식
    행렬 A가 양의 확정적이지 않으면 예외가 발생합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005-2008
*************************************************** ********************** */

double spdmatrixdet(const real_2d_array &a, const ae_int_t n, const bool isupper);
double spdmatrixdet(const real_2d_array &a);

/*************************************************************************
Algorithm for solving the following generalized symmetric positive-definite
eigenproblem:
    A*x = lambda*B*x (1) or
    A*B*x = lambda*x (2) or
    B*A*x = lambda*x (3).
where A is a symmetric matrix, B - symmetric positive-definite matrix.
The problem is solved by reducing it to an ordinary  symmetric  eigenvalue
problem.

Input parameters:
    A           -   symmetric matrix which is given by its upper or lower
                    triangular part.
                    Array whose indexes range within [0..N-1, 0..N-1].
    N           -   size of matrices A and B.
    IsUpperA    -   storage format of matrix A.
    B           -   symmetric positive-definite matrix which is given by
                    its upper or lower triangular part.
                    Array whose indexes range within [0..N-1, 0..N-1].
    IsUpperB    -   storage format of matrix B.
    ZNeeded     -   if ZNeeded is equal to:
                     * 0, the eigenvectors are not returned;
                     * 1, the eigenvectors are returned.
    ProblemType -   if ProblemType is equal to:
                     * 1, the following problem is solved: A*x = lambda*B*x;
                     * 2, the following problem is solved: A*B*x = lambda*x;
                     * 3, the following problem is solved: B*A*x = lambda*x.

Output parameters:
    D           -   eigenvalues in ascending order.
                    Array whose index ranges within [0..N-1].
    Z           -   if ZNeeded is equal to:
                     * 0, Z hasn\92t changed;
                     * 1, Z contains eigenvectors.
                    Array whose indexes range within [0..N-1, 0..N-1].
                    The eigenvectors are stored in matrix columns. It should
                    be noted that the eigenvectors in such problems do not
                    form an orthogonal system.

Result:
    True, if the problem was solved successfully.
    False, if the error occurred during the Cholesky decomposition of matrix
    B (the matrix isn\92t positive-definite) or during the work of the iterative
    algorithm for solving the symmetric eigenproblem.

See also the GeneralizedSymmetricDefiniteEVDReduce subroutine.

  -- ALGLIB --
     Copyright 1.28.2006 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
다음과 같은 일반화 된 대칭 포지티브 정리 알고리즘
고유 문제점 :
    A * x = λ * B * x (1) 또는
    A * B * x = λ * x (2) 또는
    B * A * x = λ * x (3).
여기서 A는 대칭 행렬, B - 대칭 포지티브 행렬입니다.
문제는 그것을 대칭 고유 값으로 줄임으로써 해결됩니다.
문제.
입력 매개 변수 :
    A - 상한 또는 하한에 의해 주어진 대칭 행렬
                    삼각형 부분.
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A와 B의 N - 크기
    IsUpperA - 행렬 A의 저장 형식입니다.
    B -에 의해 주어지는 대칭 포지티브 행렬
                    그것의 위 또는 아래 삼각형 부분.
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    IsUpperB - 행렬 B의 저장 형식
    ZNeeded - ZNeeded가 다음과 동일한 경우 :
                     * 0이면 고유 벡터가 반환되지 않습니다.
                     * 1, 고유 벡터가 반환됩니다.
    ProblemType - ProblemType이 다음과 같은 경우 :
                     * 1, 다음과 같은 문제가 해결되었습니다. A * x = lambda * B * x;
                     * 2, 다음과 같은 문제가 해결되었습니다. A * B * x = lambda * x;
                     * 3, 다음과 같은 문제가 해결됩니다. B * A * x = lambda * x.
출력 매개 변수 :
    D - 고유 값을 오름차순으로 표시합니다.
                    인덱스 범위가 [0..N-1] 이내 인 배열.
    Z - ZNeeded가 다음과 동일한 경우 :
                     * 0, Z는 변경되지 않았습니다.
                     * 1, Z는 고유 벡터를 포함합니다.
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
                    고유 벡터는 행렬 열에 저장됩니다. 그것은해야한다
                    이러한 문제의 고유 벡터는
                    직교 시스템을 형성한다.
결과:
    문제가 성공적으로 해결 된 경우 참.
    행렬의 콜레 스키 분해 중에 오류가 발생하면 False입니다.
    B (행렬은 양의 정수이다) 또는 반복의 작업 동안
    대칭 고유 문제를 푸는 알고리즘.
GeneralizedSymmetricDefiniteEVDReduce 서브 루틴을 참조하십시오.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 1.28.2006
*************************************************** **********************/

bool smatrixgevd(const real_2d_array &a, const ae_int_t n, const bool isuppera, const real_2d_array &b, const bool isupperb, const ae_int_t zneeded, const ae_int_t problemtype, real_1d_array &d, real_2d_array &z);


/*************************************************************************
Algorithm for reduction of the following generalized symmetric positive-
definite eigenvalue problem:
    A*x = lambda*B*x (1) or
    A*B*x = lambda*x (2) or
    B*A*x = lambda*x (3)
to the symmetric eigenvalues problem C*y = lambda*y (eigenvalues of this and
the given problems are the same, and the eigenvectors of the given problem
could be obtained by multiplying the obtained eigenvectors by the
transformation matrix x = R*y).

Here A is a symmetric matrix, B - symmetric positive-definite matrix.

Input parameters:
    A           -   symmetric matrix which is given by its upper or lower
                    triangular part.
                    Array whose indexes range within [0..N-1, 0..N-1].
    N           -   size of matrices A and B.
    IsUpperA    -   storage format of matrix A.
    B           -   symmetric positive-definite matrix which is given by
                    its upper or lower triangular part.
                    Array whose indexes range within [0..N-1, 0..N-1].
    IsUpperB    -   storage format of matrix B.
    ProblemType -   if ProblemType is equal to:
                     * 1, the following problem is solved: A*x = lambda*B*x;
                     * 2, the following problem is solved: A*B*x = lambda*x;
                     * 3, the following problem is solved: B*A*x = lambda*x.

Output parameters:
    A           -   symmetric matrix which is given by its upper or lower
                    triangle depending on IsUpperA. Contains matrix C.
                    Array whose indexes range within [0..N-1, 0..N-1].
    R           -   upper triangular or low triangular transformation matrix
                    which is used to obtain the eigenvectors of a given problem
                    as the product of eigenvectors of C (from the right) and
                    matrix R (from the left). If the matrix is upper
                    triangular, the elements below the main diagonal
                    are equal to 0 (and vice versa). Thus, we can perform
                    the multiplication without taking into account the
                    internal structure (which is an easier though less
                    effective way).
                    Array whose indexes range within [0..N-1, 0..N-1].
    IsUpperR    -   type of matrix R (upper or lower triangular).

Result:
    True, if the problem was reduced successfully.
    False, if the error occurred during the Cholesky decomposition of
        matrix B (the matrix is not positive-definite).

  -- ALGLIB --
     Copyright 1.28.2006 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
다음과 같은 일반화 된 대칭 포지티브 -
명확한 고유치 문제 :
    A * x = λ * B * x (1) 또는
    A * B * x = λ * x (2) 또는
    B * A * x = λ * x (3)
대칭 고유치 문제 C * y = λ * y (이것의 고유 값과
주어진 문제는 동일하며, 주어진 문제의 고유 벡터
얻어진 고유 벡터에
변환 행렬 x = R * y).
여기서 A는 대칭 행렬, B - 대칭 포지티브 행렬이다.
입력 매개 변수 :
    A - 상한 또는 하한에 의해 주어진 대칭 행렬
                    삼각형 부분.
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A와 B의 N - 크기
    IsUpperA - 행렬 A의 저장 형식입니다.
    B -에 의해 주어지는 대칭 포지티브 행렬
                    그것의 위 또는 아래 삼각형 부분.
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    IsUpperB - 행렬 B의 저장 형식
    ProblemType - ProblemType이 다음과 같은 경우 :
                     * 1, 다음과 같은 문제가 해결되었습니다. A * x = lambda * B * x;
                     * 2, 다음과 같은 문제가 해결되었습니다. A * B * x = lambda * x;
                     * 3, 다음과 같은 문제가 해결됩니다. B * A * x = lambda * x.
출력 매개 변수 :
    A - 상한 또는 하한에 의해 주어진 대칭 행렬
                    삼각형은 IsUpperA에 따라 다릅니다. 행렬 C가 포함되어 있습니다.
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    R - 위쪽 삼각형 또는 낮은 삼각형 변환 행렬
                    주어진 문제의 고유 벡터를 얻는데 사용된다.
                    C의 고유 벡터의 곱 (오른쪽부터)과
                    행렬 R (왼쪽부터). 행렬이 위쪽 인 경우
                    삼각형, 주요 대각선 아래 요소
                    0이면 (반대의 경우도 마찬가지 임). 따라서 우리는
                    고려하지 않고 곱셈
                    내부 구조 (덜 쉬울지라도)
                    효과적인 방법).
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    IsUpperR - 행렬 R의 유형입니다 (위쪽 또는 아래쪽 삼각형).
결과:
    문제가 성공적으로 감소 된 경우 참.
    Cholesky 분해 중에 오류가 발생하면 False입니다.
        행렬 B (행렬은 양의 정수가 아님).
  - ALGLIB -
     Bochkanov Sergey의 Copyright 1.28.2006
*************************************************** ********************** */

bool smatrixgevdreduce(real_2d_array &a, const ae_int_t n, const bool isuppera, const real_2d_array &b, const bool isupperb, const ae_int_t problemtype, real_2d_array &r, bool &isupperr);

/*************************************************************************
Inverse matrix update by the Sherman-Morrison formula

The algorithm updates matrix A^-1 when adding a number to an element
of matrix A.

Input parameters:
    InvA    -   inverse of matrix A.
                Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    UpdRow  -   row where the element to be updated is stored.
    UpdColumn - column where the element to be updated is stored.
    UpdVal  -   a number to be added to the element.


Output parameters:
    InvA    -   inverse of modified matrix A.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
Sherman-Morrison 공식에 의한 역 행렬 업데이트
알고리즘은 요소에 숫자를 추가 할 때 행렬 A ^ -1을 업데이트합니다.
행렬 A의
입력 매개 변수 :
    InvA - 행렬 A의 역함수
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    UpdRow - 업데이트 할 요소가 저장된 행입니다.
    UpdColumn - 업데이트 할 요소가 저장되는 열입니다.
    UpdVal - 요소에 추가 할 숫자입니다.
출력 매개 변수 :
    InvA - 수정 된 행렬 A의 역입니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

void rmatrixinvupdatesimple(real_2d_array &inva, const ae_int_t n, const ae_int_t updrow, const ae_int_t updcolumn, const double updval);


/*************************************************************************
Inverse matrix update by the Sherman-Morrison formula

The algorithm updates matrix A^-1 when adding a vector to a row
of matrix A.

Input parameters:
    InvA    -   inverse of matrix A.
                Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    UpdRow  -   the row of A whose vector V was added.
                0 <= Row <= N-1
    V       -   the vector to be added to a row.
                Array whose index ranges within [0..N-1].

Output parameters:
    InvA    -   inverse of modified matrix A.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/* ************************************************ *************************
Sherman-Morrison 공식에 의한 역 행렬 업데이트
알고리즘은 행에 벡터를 추가 할 때 행렬 A ^ -1을 업데이트합니다.
행렬 A의
입력 매개 변수 :
    InvA - 행렬 A의 역함수
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    UpdRow - 벡터 V가 추가 된 A의 행입니다.
                0 <= 행 <= N-1
    V - 행에 추가되는 벡터
                인덱스 범위가 [0..N-1] 이내 인 배열.
출력 매개 변수 :
    InvA - 수정 된 행렬 A의 역입니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** */

void rmatrixinvupdaterow(real_2d_array &inva, const ae_int_t n, const ae_int_t updrow, const real_1d_array &v);


/*************************************************************************
Inverse matrix update by the Sherman-Morrison formula

The algorithm updates matrix A^-1 when adding a vector to a column
of matrix A.

Input parameters:
    InvA        -   inverse of matrix A.
                    Array whose indexes range within [0..N-1, 0..N-1].
    N           -   size of matrix A.
    UpdColumn   -   the column of A whose vector U was added.
                    0 <= UpdColumn <= N-1
    U           -   the vector to be added to a column.
                    Array whose index ranges within [0..N-1].

Output parameters:
    InvA        -   inverse of modified matrix A.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/*
/ * ************************************************ *************************
Sherman-Morrison 공식에 의한 역 행렬 업데이트
알고리즘은 행렬을 벡터에 추가 할 때 행렬 A ^ -1을 업데이트합니다.
행렬 A의
입력 매개 변수 :
    InvA - 행렬 A의 역함수
                    인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    UpdColumn - 벡터 U가 추가 된 A의 열입니다.
                    0 <= UpdColumn <= N-1
    U - 열에 추가되는 벡터
                    인덱스 범위가 [0..N-1] 이내 인 배열.
출력 매개 변수 :
    InvA - 수정 된 행렬 A의 역입니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** * /*/
void rmatrixinvupdatecolumn(real_2d_array &inva, const ae_int_t n, const ae_int_t updcolumn, const real_1d_array &u);


/*************************************************************************
Inverse matrix update by the Sherman-Morrison formula

The algorithm computes the inverse of matrix A+u*v\92 by using the given matrix
A^-1 and the vectors u and v.

Input parameters:
    InvA    -   inverse of matrix A.
                Array whose indexes range within [0..N-1, 0..N-1].
    N       -   size of matrix A.
    U       -   the vector modifying the matrix.
                Array whose index ranges within [0..N-1].
    V       -   the vector modifying the matrix.
                Array whose index ranges within [0..N-1].

Output parameters:
    InvA - inverse of matrix A + u*v'.

  -- ALGLIB --
     Copyright 2005 by Bochkanov Sergey
*************************************************************************/

/*/ * ************************************************ *************************
Sherman-Morrison 공식에 의한 역 행렬 업데이트
이 알고리즘은 행렬 A + u * v의 역행렬을 계산합니다. 주어진 행렬을 사용하여
A ^ -1 및 벡터 u와 v.
입력 매개 변수 :
    InvA - 행렬 A의 역함수
                인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    행렬 A의 N 크기
    U - 행렬을 변경하는 벡터
                인덱스 범위가 [0..N-1] 이내 인 배열.
    V - 행렬을 변경하는 벡터
                인덱스 범위가 [0..N-1] 이내 인 배열.
출력 매개 변수 :
    InvA - 행렬 A + u * v '의 역.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 2005
*************************************************** ********************** * /*/

void rmatrixinvupdateuv(real_2d_array &inva, const ae_int_t n, const real_1d_array &u, const real_1d_array &v);

/*************************************************************************
Subroutine performing the Schur decomposition of a general matrix by using
the QR algorithm with multiple shifts.

The source matrix A is represented as S'*A*S = T, where S is an orthogonal
matrix (Schur vectors), T - upper quasi-triangular matrix (with blocks of
sizes 1x1 and 2x2 on the main diagonal).

Input parameters:
    A   -   matrix to be decomposed.
            Array whose indexes range within [0..N-1, 0..N-1].
    N   -   size of A, N>=0.


Output parameters:
    A   -   contains matrix T.
            Array whose indexes range within [0..N-1, 0..N-1].
    S   -   contains Schur vectors.
            Array whose indexes range within [0..N-1, 0..N-1].

Note 1:
    The block structure of matrix T can be easily recognized: since all
    the elements below the blocks are zeros, the elements a[i+1,i] which
    are equal to 0 show the block border.

Note 2:
    The algorithm performance depends on the value of the internal parameter
    NS of the InternalSchurDecomposition subroutine which defines the number
    of shifts in the QR algorithm (similarly to the block width in block-matrix
    algorithms in linear algebra). If you require maximum performance on
    your machine, it is recommended to adjust this parameter manually.

Result:
    True,
        if the algorithm has converged and parameters A and S contain the result.
    False,
        if the algorithm has not converged.

Algorithm implemented on the basis of the DHSEQR subroutine (LAPACK 3.0 library).
*************************************************************************/

/*/ * ************************************************ *************************
서브 루틴은 다음을 사용하여 일반 행렬의 Schur 분해를 수행합니다.
여러 교대로 QR 알고리즘.
소스 행렬 A는 S '* A * S = T로 표현되며, 여기서 S는 직교
행렬 (슈어 벡터), T - 위 준 삼각 행렬 (
주 대각선에서 1x1 및 2x2 크기).
입력 매개 변수 :
    A - 분해 할 행렬.
            인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    N - size of A, N> = 0.
출력 매개 변수 :
    A - 행렬 T를 포함합니다.
            인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
    S - Schur 벡터를 포함합니다.
            인덱스가 [0..N-1, 0..N-1]의 범위에있는 배열.
참고 1 :
    행렬 T의 블록 구조는 쉽게 인식 할 수 있습니다.
    블록 아래의 요소는 0이고, 요소 a [i + 1, i]는
    블록 경계를 나타내는 0과 같습니다.
노트 2:
    알고리즘 성능은 내부 매개 변수의 값에 따라 달라집니다
    숫자를 정의하는 InternalSchurDecomposition 서브 루틴의 NS
    QR 알고리즘의 시프트 (블록 - 매트릭스의 블록 폭과 유사)
    선형 대수학의 알고리즘). 최대 성능이 필요한 경우
    이 매개 변수를 수동으로 조정하는 것이 좋습니다.
결과:
    참된,
        알고리즘이 수렴하고 매개 변수 A와 S가 결과를 포함하면.
    그릇된,
        알고리즘이 수렴하지 않은 경우
알고리즘은 DHSEQR 서브 루틴 (LAPACK 3.0 라이브러리)을 기반으로 구현됩니다.
*************************************************** ********************** * /*/

bool rmatrixschur(real_2d_array &a, const ae_int_t n, real_2d_array &s);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////

/*// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (기능)이 포함되어 있습니다.
//
// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////*/

namespace alglib_impl
{
void ablassplitlength(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t* n1,
     ae_int_t* n2,
     ae_state *_state);
void ablascomplexsplitlength(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_int_t* n1,
     ae_int_t* n2,
     ae_state *_state);
ae_int_t ablasblocksize(/* Real    */ ae_matrix* a, ae_state *_state);
ae_int_t ablascomplexblocksize(/* Complex */ ae_matrix* a,
     ae_state *_state);
ae_int_t ablasmicroblocksize(ae_state *_state);
void cmatrixtranspose(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Complex */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_state *_state);
void rmatrixtranspose(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_state *_state);
void rmatrixenforcesymmetricity(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
void cmatrixcopy(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Complex */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_state *_state);
void rmatrixcopy(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_state *_state);
void cmatrixrank1(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Complex */ ae_vector* u,
     ae_int_t iu,
     /* Complex */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
void rmatrixrank1(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_vector* u,
     ae_int_t iu,
     /* Real    */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
void cmatrixmv(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t opa,
     /* Complex */ ae_vector* x,
     ae_int_t ix,
     /* Complex */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
void rmatrixmv(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t opa,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
void cmatrixrighttrsm(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Complex */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
void _pexec_cmatrixrighttrsm(ae_int_t m,
    ae_int_t n,
    /* Complex */ ae_matrix* a,
    ae_int_t i1,
    ae_int_t j1,
    ae_bool isupper,
    ae_bool isunit,
    ae_int_t optype,
    /* Complex */ ae_matrix* x,
    ae_int_t i2,
    ae_int_t j2, ae_state *_state);
void cmatrixlefttrsm(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Complex */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
void _pexec_cmatrixlefttrsm(ae_int_t m,
    ae_int_t n,
    /* Complex */ ae_matrix* a,
    ae_int_t i1,
    ae_int_t j1,
    ae_bool isupper,
    ae_bool isunit,
    ae_int_t optype,
    /* Complex */ ae_matrix* x,
    ae_int_t i2,
    ae_int_t j2, ae_state *_state);
void rmatrixrighttrsm(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
void _pexec_rmatrixrighttrsm(ae_int_t m,
    ae_int_t n,
    /* Real    */ ae_matrix* a,
    ae_int_t i1,
    ae_int_t j1,
    ae_bool isupper,
    ae_bool isunit,
    ae_int_t optype,
    /* Real    */ ae_matrix* x,
    ae_int_t i2,
    ae_int_t j2, ae_state *_state);
void rmatrixlefttrsm(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
void _pexec_rmatrixlefttrsm(ae_int_t m,
    ae_int_t n,
    /* Real    */ ae_matrix* a,
    ae_int_t i1,
    ae_int_t j1,
    ae_bool isupper,
    ae_bool isunit,
    ae_int_t optype,
    /* Real    */ ae_matrix* x,
    ae_int_t i2,
    ae_int_t j2, ae_state *_state);
void cmatrixsyrk(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state);
void _pexec_cmatrixsyrk(ae_int_t n,
    ae_int_t k,
    double alpha,
    /* Complex */ ae_matrix* a,
    ae_int_t ia,
    ae_int_t ja,
    ae_int_t optypea,
    double beta,
    /* Complex */ ae_matrix* c,
    ae_int_t ic,
    ae_int_t jc,
    ae_bool isupper, ae_state *_state);
void rmatrixsyrk(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state);
void _pexec_rmatrixsyrk(ae_int_t n,
    ae_int_t k,
    double alpha,
    /* Real    */ ae_matrix* a,
    ae_int_t ia,
    ae_int_t ja,
    ae_int_t optypea,
    double beta,
    /* Real    */ ae_matrix* c,
    ae_int_t ic,
    ae_int_t jc,
    ae_bool isupper, ae_state *_state);
void cmatrixgemm(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     ae_complex alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Complex */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     ae_complex beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
void _pexec_cmatrixgemm(ae_int_t m,
    ae_int_t n,
    ae_int_t k,
    ae_complex alpha,
    /* Complex */ ae_matrix* a,
    ae_int_t ia,
    ae_int_t ja,
    ae_int_t optypea,
    /* Complex */ ae_matrix* b,
    ae_int_t ib,
    ae_int_t jb,
    ae_int_t optypeb,
    ae_complex beta,
    /* Complex */ ae_matrix* c,
    ae_int_t ic,
    ae_int_t jc, ae_state *_state);
void rmatrixgemm(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
void _pexec_rmatrixgemm(ae_int_t m,
    ae_int_t n,
    ae_int_t k,
    double alpha,
    /* Real    */ ae_matrix* a,
    ae_int_t ia,
    ae_int_t ja,
    ae_int_t optypea,
    /* Real    */ ae_matrix* b,
    ae_int_t ib,
    ae_int_t jb,
    ae_int_t optypeb,
    double beta,
    /* Real    */ ae_matrix* c,
    ae_int_t ic,
    ae_int_t jc, ae_state *_state);
void rmatrixqr(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     ae_state *_state);
void rmatrixlq(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     ae_state *_state);
void cmatrixqr(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_vector* tau,
     ae_state *_state);
void cmatrixlq(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_vector* tau,
     ae_state *_state);
void rmatrixqrunpackq(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     ae_int_t qcolumns,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
void rmatrixqrunpackr(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* r,
     ae_state *_state);
void rmatrixlqunpackq(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     ae_int_t qrows,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
void rmatrixlqunpackl(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* l,
     ae_state *_state);
void cmatrixqrunpackq(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_vector* tau,
     ae_int_t qcolumns,
     /* Complex */ ae_matrix* q,
     ae_state *_state);
void cmatrixqrunpackr(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* r,
     ae_state *_state);
void cmatrixlqunpackq(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_vector* tau,
     ae_int_t qrows,
     /* Complex */ ae_matrix* q,
     ae_state *_state);
void cmatrixlqunpackl(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* l,
     ae_state *_state);
void rmatrixqrbasecase(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* work,
     /* Real    */ ae_vector* t,
     /* Real    */ ae_vector* tau,
     ae_state *_state);
void rmatrixlqbasecase(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* work,
     /* Real    */ ae_vector* t,
     /* Real    */ ae_vector* tau,
     ae_state *_state);
void rmatrixbd(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tauq,
     /* Real    */ ae_vector* taup,
     ae_state *_state);
void rmatrixbdunpackq(/* Real    */ ae_matrix* qp,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tauq,
     ae_int_t qcolumns,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
void rmatrixbdmultiplybyq(/* Real    */ ae_matrix* qp,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tauq,
     /* Real    */ ae_matrix* z,
     ae_int_t zrows,
     ae_int_t zcolumns,
     ae_bool fromtheright,
     ae_bool dotranspose,
     ae_state *_state);
void rmatrixbdunpackpt(/* Real    */ ae_matrix* qp,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* taup,
     ae_int_t ptrows,
     /* Real    */ ae_matrix* pt,
     ae_state *_state);
void rmatrixbdmultiplybyp(/* Real    */ ae_matrix* qp,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* taup,
     /* Real    */ ae_matrix* z,
     ae_int_t zrows,
     ae_int_t zcolumns,
     ae_bool fromtheright,
     ae_bool dotranspose,
     ae_state *_state);
void rmatrixbdunpackdiagonals(/* Real    */ ae_matrix* b,
     ae_int_t m,
     ae_int_t n,
     ae_bool* isupper,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_state *_state);
void rmatrixhessenberg(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     ae_state *_state);
void rmatrixhessenbergunpackq(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
void rmatrixhessenbergunpackh(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_matrix* h,
     ae_state *_state);
void smatrixtd(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tau,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_state *_state);
void smatrixtdunpackq(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tau,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
void hmatrixtd(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* tau,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_state *_state);
void hmatrixtdunpackq(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* tau,
     /* Complex */ ae_matrix* q,
     ae_state *_state);
ae_bool rmatrixbdsvd(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isfractionalaccuracyrequired,
     /* Real    */ ae_matrix* u,
     ae_int_t nru,
     /* Real    */ ae_matrix* c,
     ae_int_t ncc,
     /* Real    */ ae_matrix* vt,
     ae_int_t ncvt,
     ae_state *_state);
ae_bool bidiagonalsvddecomposition(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isfractionalaccuracyrequired,
     /* Real    */ ae_matrix* u,
     ae_int_t nru,
     /* Real    */ ae_matrix* c,
     ae_int_t ncc,
     /* Real    */ ae_matrix* vt,
     ae_int_t ncvt,
     ae_state *_state);
ae_bool rmatrixsvd(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     ae_int_t uneeded,
     ae_int_t vtneeded,
     ae_int_t additionalmemory,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_matrix* u,
     /* Real    */ ae_matrix* vt,
     ae_state *_state);
ae_bool smatrixevd(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t zneeded,
     ae_bool isupper,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool smatrixevdr(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t zneeded,
     ae_bool isupper,
     double b1,
     double b2,
     ae_int_t* m,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool smatrixevdi(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t zneeded,
     ae_bool isupper,
     ae_int_t i1,
     ae_int_t i2,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool hmatrixevd(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_int_t zneeded,
     ae_bool isupper,
     /* Real    */ ae_vector* d,
     /* Complex */ ae_matrix* z,
     ae_state *_state);
ae_bool hmatrixevdr(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_int_t zneeded,
     ae_bool isupper,
     double b1,
     double b2,
     ae_int_t* m,
     /* Real    */ ae_vector* w,
     /* Complex */ ae_matrix* z,
     ae_state *_state);
ae_bool hmatrixevdi(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_int_t zneeded,
     ae_bool isupper,
     ae_int_t i1,
     ae_int_t i2,
     /* Real    */ ae_vector* w,
     /* Complex */ ae_matrix* z,
     ae_state *_state);
ae_bool smatrixtdevd(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_int_t zneeded,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool smatrixtdevdr(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_int_t zneeded,
     double a,
     double b,
     ae_int_t* m,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool smatrixtdevdi(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_int_t zneeded,
     ae_int_t i1,
     ae_int_t i2,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool rmatrixevd(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t vneeded,
     /* Real    */ ae_vector* wr,
     /* Real    */ ae_vector* wi,
     /* Real    */ ae_matrix* vl,
     /* Real    */ ae_matrix* vr,
     ae_state *_state);
void rmatrixrndorthogonal(ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_state *_state);
void rmatrixrndcond(ae_int_t n,
     double c,
     /* Real    */ ae_matrix* a,
     ae_state *_state);
void cmatrixrndorthogonal(ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_state *_state);
void cmatrixrndcond(ae_int_t n,
     double c,
     /* Complex */ ae_matrix* a,
     ae_state *_state);
void smatrixrndcond(ae_int_t n,
     double c,
     /* Real    */ ae_matrix* a,
     ae_state *_state);
void spdmatrixrndcond(ae_int_t n,
     double c,
     /* Real    */ ae_matrix* a,
     ae_state *_state);
void hmatrixrndcond(ae_int_t n,
     double c,
     /* Complex */ ae_matrix* a,
     ae_state *_state);
void hpdmatrixrndcond(ae_int_t n,
     double c,
     /* Complex */ ae_matrix* a,
     ae_state *_state);
void rmatrixrndorthogonalfromtheright(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void rmatrixrndorthogonalfromtheleft(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void cmatrixrndorthogonalfromtheright(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void cmatrixrndorthogonalfromtheleft(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void smatrixrndmultiply(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
void hmatrixrndmultiply(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
void rmatrixlu(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
void cmatrixlu(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
ae_bool hpdmatrixcholesky(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
ae_bool spdmatrixcholesky(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
void rmatrixlup(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
void cmatrixlup(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
void rmatrixplu(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
void cmatrixplu(/* Complex */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
ae_bool spdmatrixcholeskyrec(/* Real    */ ae_matrix* a,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tmp,
     ae_state *_state);
double rmatrixrcond1(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
double rmatrixrcondinf(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
double spdmatrixrcond(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
double rmatrixtrrcond1(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isunit,
     ae_state *_state);
double rmatrixtrrcondinf(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isunit,
     ae_state *_state);
double hpdmatrixrcond(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
double cmatrixrcond1(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
double cmatrixrcondinf(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
double rmatrixlurcond1(/* Real    */ ae_matrix* lua,
     ae_int_t n,
     ae_state *_state);
double rmatrixlurcondinf(/* Real    */ ae_matrix* lua,
     ae_int_t n,
     ae_state *_state);
double spdmatrixcholeskyrcond(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
double hpdmatrixcholeskyrcond(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
double cmatrixlurcond1(/* Complex */ ae_matrix* lua,
     ae_int_t n,
     ae_state *_state);
double cmatrixlurcondinf(/* Complex */ ae_matrix* lua,
     ae_int_t n,
     ae_state *_state);
double cmatrixtrrcond1(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isunit,
     ae_state *_state);
double cmatrixtrrcondinf(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isunit,
     ae_state *_state);
double rcondthreshold(ae_state *_state);
void rmatrixluinverse(/* Real    */ ae_matrix* a,
     /* Integer */ ae_vector* pivots,
     ae_int_t n,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void rmatrixinverse(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void cmatrixluinverse(/* Complex */ ae_matrix* a,
     /* Integer */ ae_vector* pivots,
     ae_int_t n,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void cmatrixinverse(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void spdmatrixcholeskyinverse(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void spdmatrixinverse(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void hpdmatrixcholeskyinverse(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void hpdmatrixinverse(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void rmatrixtrinverse(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
void cmatrixtrinverse(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t* info,
     matinvreport* rep,
     ae_state *_state);
ae_bool _matinvreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _matinvreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _matinvreport_clear(void* _p);
void _matinvreport_destroy(void* _p);
void sparsecreate(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     sparsematrix* s,
     ae_state *_state);
void sparsecreatecrs(ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* ner,
     sparsematrix* s,
     ae_state *_state);
void sparsecopy(sparsematrix* s0, sparsematrix* s1, ae_state *_state);
void sparseadd(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state);
void sparseset(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state);
double sparseget(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     ae_state *_state);
double sparsegetdiagonal(sparsematrix* s, ae_int_t i, ae_state *_state);
void sparseconverttocrs(sparsematrix* s, ae_state *_state);
void sparsemv(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void sparsemtv(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void sparsemv2(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y0,
     /* Real    */ ae_vector* y1,
     ae_state *_state);
void sparsesmv(sparsematrix* s,
     ae_bool isupper,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void sparsemm(sparsematrix* s,
     /* Real    */ ae_matrix* a,
     ae_int_t k,
     /* Real    */ ae_matrix* b,
     ae_state *_state);
void sparsemtm(sparsematrix* s,
     /* Real    */ ae_matrix* a,
     ae_int_t k,
     /* Real    */ ae_matrix* b,
     ae_state *_state);
void sparsemm2(sparsematrix* s,
     /* Real    */ ae_matrix* a,
     ae_int_t k,
     /* Real    */ ae_matrix* b0,
     /* Real    */ ae_matrix* b1,
     ae_state *_state);
void sparsesmm(sparsematrix* s,
     ae_bool isupper,
     /* Real    */ ae_matrix* a,
     ae_int_t k,
     /* Real    */ ae_matrix* b,
     ae_state *_state);
void sparseresizematrix(sparsematrix* s, ae_state *_state);
double sparsegetaveragelengthofchain(sparsematrix* s, ae_state *_state);
ae_bool sparseenumerate(sparsematrix* s,
     ae_int_t* t0,
     ae_int_t* t1,
     ae_int_t* i,
     ae_int_t* j,
     double* v,
     ae_state *_state);
ae_bool sparserewriteexisting(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state);
void sparsegetrow(sparsematrix* s,
     ae_int_t i,
     /* Real    */ ae_vector* irow,
     ae_state *_state);
void sparseconverttohash(sparsematrix* s, ae_state *_state);
void sparsecopytohash(sparsematrix* s0,
     sparsematrix* s1,
     ae_state *_state);
void sparsecopytocrs(sparsematrix* s0, sparsematrix* s1, ae_state *_state);
ae_int_t sparsegetmatrixtype(sparsematrix* s, ae_state *_state);
ae_bool sparseishash(sparsematrix* s, ae_state *_state);
ae_bool sparseiscrs(sparsematrix* s, ae_state *_state);
void sparsefree(sparsematrix* s, ae_state *_state);
ae_int_t sparsegetnrows(sparsematrix* s, ae_state *_state);
ae_int_t sparsegetncols(sparsematrix* s, ae_state *_state);
ae_bool _sparsematrix_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _sparsematrix_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _sparsematrix_clear(void* _p);
void _sparsematrix_destroy(void* _p);
void fblscholeskysolve(/* Real    */ ae_matrix* cha,
     double sqrtscalea,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* xb,
     /* Real    */ ae_vector* tmp,
     ae_state *_state);
void fblssolvecgx(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     double alpha,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* buf,
     ae_state *_state);
void fblscgcreate(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* b,
     ae_int_t n,
     fblslincgstate* state,
     ae_state *_state);
ae_bool fblscgiteration(fblslincgstate* state, ae_state *_state);
void fblssolvels(/* Real    */ ae_matrix* a,
     /* Real    */ ae_vector* b,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tmp0,
     /* Real    */ ae_vector* tmp1,
     /* Real    */ ae_vector* tmp2,
     ae_state *_state);
ae_bool _fblslincgstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _fblslincgstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _fblslincgstate_clear(void* _p);
void _fblslincgstate_destroy(void* _p);
void normestimatorcreate(ae_int_t m,
     ae_int_t n,
     ae_int_t nstart,
     ae_int_t nits,
     normestimatorstate* state,
     ae_state *_state);
void normestimatorsetseed(normestimatorstate* state,
     ae_int_t seedval,
     ae_state *_state);
ae_bool normestimatoriteration(normestimatorstate* state,
     ae_state *_state);
void normestimatorestimatesparse(normestimatorstate* state,
     sparsematrix* a,
     ae_state *_state);
void normestimatorresults(normestimatorstate* state,
     double* nrm,
     ae_state *_state);
void normestimatorrestart(normestimatorstate* state, ae_state *_state);
ae_bool _normestimatorstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _normestimatorstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _normestimatorstate_clear(void* _p);
void _normestimatorstate_destroy(void* _p);
double rmatrixludet(/* Real    */ ae_matrix* a,
     /* Integer */ ae_vector* pivots,
     ae_int_t n,
     ae_state *_state);
double rmatrixdet(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
ae_complex cmatrixludet(/* Complex */ ae_matrix* a,
     /* Integer */ ae_vector* pivots,
     ae_int_t n,
     ae_state *_state);
ae_complex cmatrixdet(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
double spdmatrixcholeskydet(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_state *_state);
double spdmatrixdet(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
ae_bool smatrixgevd(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isuppera,
     /* Real    */ ae_matrix* b,
     ae_bool isupperb,
     ae_int_t zneeded,
     ae_int_t problemtype,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_matrix* z,
     ae_state *_state);
ae_bool smatrixgevdreduce(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isuppera,
     /* Real    */ ae_matrix* b,
     ae_bool isupperb,
     ae_int_t problemtype,
     /* Real    */ ae_matrix* r,
     ae_bool* isupperr,
     ae_state *_state);
void rmatrixinvupdatesimple(/* Real    */ ae_matrix* inva,
     ae_int_t n,
     ae_int_t updrow,
     ae_int_t updcolumn,
     double updval,
     ae_state *_state);
void rmatrixinvupdaterow(/* Real    */ ae_matrix* inva,
     ae_int_t n,
     ae_int_t updrow,
     /* Real    */ ae_vector* v,
     ae_state *_state);
void rmatrixinvupdatecolumn(/* Real    */ ae_matrix* inva,
     ae_int_t n,
     ae_int_t updcolumn,
     /* Real    */ ae_vector* u,
     ae_state *_state);
void rmatrixinvupdateuv(/* Real    */ ae_matrix* inva,
     ae_int_t n,
     /* Real    */ ae_vector* u,
     /* Real    */ ae_vector* v,
     ae_state *_state);
ae_bool rmatrixschur(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_matrix* s,
     ae_state *_state);

}
#endif

