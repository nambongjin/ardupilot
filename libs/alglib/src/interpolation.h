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
#ifndef _interpolation_pkg_h
#define _interpolation_pkg_h
#include "ap.h"
#include "alglibinternal.h"
#include "alglibmisc.h"
#include "linalg.h"
#include "solvers.h"
#include "optimization.h"
#include "specialfunctions.h"
#include "integration.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (데이터)이 포함되어 있습니다.
//
// //////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
typedef struct
{
    ae_int_t n;
    ae_int_t nx;
    ae_int_t d;
    double r;
    ae_int_t nw;
    kdtree tree;
    ae_int_t modeltype;
    ae_matrix q;
    ae_vector xbuf;
    ae_vector tbuf;
    ae_vector rbuf;
    ae_matrix xybuf;
    ae_int_t debugsolverfailures;
    double debugworstrcond;
    double debugbestrcond;
} idwinterpolant;
typedef struct
{
    ae_int_t n;
    double sy;
    ae_vector x;
    ae_vector y;
    ae_vector w;
} barycentricinterpolant;
typedef struct
{
    ae_bool periodic;
    ae_int_t n;
    ae_int_t k;
    ae_int_t continuity;
    ae_vector x;
    ae_vector c;
} spline1dinterpolant;
typedef struct
{
    double taskrcond;
    double rmserror;
    double avgerror;
    double avgrelerror;
    double maxerror;
} polynomialfitreport;
typedef struct
{
    double taskrcond;
    ae_int_t dbest;
    double rmserror;
    double avgerror;
    double avgrelerror;
    double maxerror;
} barycentricfitreport;
typedef struct
{
    double taskrcond;
    double rmserror;
    double avgerror;
    double avgrelerror;
    double maxerror;
} spline1dfitreport;
typedef struct
{
    double taskrcond;
    ae_int_t iterationscount;
    ae_int_t varidx;
    double rmserror;
    double avgerror;
    double avgrelerror;
    double maxerror;
    double wrmserror;
    ae_matrix covpar;
    ae_vector errpar;
    ae_vector errcurve;
    ae_vector noise;
    double r2;
} lsfitreport;
typedef struct
{
    ae_int_t optalgo;
    ae_int_t m;
    ae_int_t k;
    double epsf;
    double epsx;
    ae_int_t maxits;
    double stpmax;
    ae_bool xrep;
    ae_vector s;
    ae_vector bndl;
    ae_vector bndu;
    ae_matrix taskx;
    ae_vector tasky;
    ae_int_t npoints;
    ae_vector taskw;
    ae_int_t nweights;
    ae_int_t wkind;
    ae_int_t wits;
    double diffstep;
    double teststep;
    ae_bool xupdated;
    ae_bool needf;
    ae_bool needfg;
    ae_bool needfgh;
    ae_int_t pointindex;
    ae_vector x;
    ae_vector c;
    double f;
    ae_vector g;
    ae_matrix h;
    ae_vector wcur;
    ae_vector tmp;
    ae_vector tmpf;
    ae_matrix tmpjac;
    ae_matrix tmpjacw;
    double tmpnoise;
    matinvreport invrep;
    ae_int_t repiterationscount;
    ae_int_t repterminationtype;
    ae_int_t repvaridx;
    double reprmserror;
    double repavgerror;
    double repavgrelerror;
    double repmaxerror;
    double repwrmserror;
    lsfitreport rep;
    minlmstate optstate;
    minlmreport optrep;
    ae_int_t prevnpt;
    ae_int_t prevalgo;
    rcommstate rstate;
} lsfitstate;
typedef struct
{
    ae_int_t n;
    ae_bool periodic;
    ae_vector p;
    spline1dinterpolant x;
    spline1dinterpolant y;
} pspline2interpolant;
typedef struct
{
    ae_int_t n;
    ae_bool periodic;
    ae_vector p;
    spline1dinterpolant x;
    spline1dinterpolant y;
    spline1dinterpolant z;
} pspline3interpolant;
typedef struct
{
    ae_int_t ny;
    ae_int_t nx;
    ae_int_t nc;
    ae_int_t nl;
    kdtree tree;
    ae_matrix xc;
    ae_matrix wr;
    double rmax;
    ae_matrix v;
    ae_int_t gridtype;
    ae_bool fixrad;
    double lambdav;
    double radvalue;
    double radzvalue;
    ae_int_t nlayers;
    ae_int_t aterm;
    ae_int_t algorithmtype;
    double epsort;
    double epserr;
    ae_int_t maxits;
    double h;
    ae_int_t n;
    ae_matrix x;
    ae_matrix y;
    ae_vector calcbufxcx;
    ae_matrix calcbufx;
    ae_vector calcbuftags;
} rbfmodel;
typedef struct
{
    ae_int_t arows;
    ae_int_t acols;
    ae_int_t annz;
    ae_int_t iterationscount;
    ae_int_t nmv;
    ae_int_t terminationtype;
} rbfreport;
typedef struct
{
    ae_int_t k;
    ae_int_t stype;
    ae_int_t n;
    ae_int_t m;
    ae_int_t d;
    ae_vector x;
    ae_vector y;
    ae_vector f;
} spline2dinterpolant;
typedef struct
{
    ae_int_t k;
    ae_int_t stype;
    ae_int_t n;
    ae_int_t m;
    ae_int_t l;
    ae_int_t d;
    ae_vector x;
    ae_vector y;
    ae_vector z;
    ae_vector f;
} spline3dinterpolant;

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////// 
// 이 섹션은 C ++ 인터페이스를 포함합니다.
//
// ////////////////////////////////////////////////////////////////////// 
namespace alglib
{

/*************************************************************************
IDW interpolant.
*************************************************************************/
/* ************************************************ *************************
IDW 보간법.
*************************************************** ********************** */
class _idwinterpolant_owner
{
public:
    _idwinterpolant_owner();
    _idwinterpolant_owner(const _idwinterpolant_owner &rhs);
    _idwinterpolant_owner& operator=(const _idwinterpolant_owner &rhs);
    virtual ~_idwinterpolant_owner();
    alglib_impl::idwinterpolant* c_ptr();
    alglib_impl::idwinterpolant* c_ptr() const;
protected:
    alglib_impl::idwinterpolant *p_struct;
};
class idwinterpolant : public _idwinterpolant_owner
{
public:
    idwinterpolant();
    idwinterpolant(const idwinterpolant &rhs);
    idwinterpolant& operator=(const idwinterpolant &rhs);
    virtual ~idwinterpolant();

};

/*************************************************************************
Barycentric interpolant.
*************************************************************************/
/* ************************************************ *************************
중성분 보간법.
*************************************************** ********************** */
class _barycentricinterpolant_owner
{
public:
    _barycentricinterpolant_owner();
    _barycentricinterpolant_owner(const _barycentricinterpolant_owner &rhs);
    _barycentricinterpolant_owner& operator=(const _barycentricinterpolant_owner &rhs);
    virtual ~_barycentricinterpolant_owner();
    alglib_impl::barycentricinterpolant* c_ptr();
    alglib_impl::barycentricinterpolant* c_ptr() const;
protected:
    alglib_impl::barycentricinterpolant *p_struct;
};
class barycentricinterpolant : public _barycentricinterpolant_owner
{
public:
    barycentricinterpolant();
    barycentricinterpolant(const barycentricinterpolant &rhs);
    barycentricinterpolant& operator=(const barycentricinterpolant &rhs);
    virtual ~barycentricinterpolant();

};



/*************************************************************************
1-dimensional spline interpolant
*************************************************************************/
/* ************************************************ *************************
1 차원 스플라인 보간법
*************************************************** ********************** */
class _spline1dinterpolant_owner
{
public:
    _spline1dinterpolant_owner();
    _spline1dinterpolant_owner(const _spline1dinterpolant_owner &rhs);
    _spline1dinterpolant_owner& operator=(const _spline1dinterpolant_owner &rhs);
    virtual ~_spline1dinterpolant_owner();
    alglib_impl::spline1dinterpolant* c_ptr();
    alglib_impl::spline1dinterpolant* c_ptr() const;
protected:
    alglib_impl::spline1dinterpolant *p_struct;
};
class spline1dinterpolant : public _spline1dinterpolant_owner
{
public:
    spline1dinterpolant();
    spline1dinterpolant(const spline1dinterpolant &rhs);
    spline1dinterpolant& operator=(const spline1dinterpolant &rhs);
    virtual ~spline1dinterpolant();

};

/*************************************************************************
Polynomial fitting report:
    TaskRCond       reciprocal of task's condition number
    RMSError        RMS error
    AvgError        average error
    AvgRelError     average relative error (for non-zero Y[I])
    MaxError        maximum error
*************************************************************************/
/* ************************************************ *************************
다항식 피팅 보고서 :
    TaskRCond 작업 조건 번호의 역수입니다.
    RMSError RMS 오류
    평균 오류 평균 오류
    AvgRelError 평균 상대 오차 (0이 아닌 Y [I]의 경우)
    MaxError 최대 오류
*************************************************** ********************** */
class _polynomialfitreport_owner
{
public:
    _polynomialfitreport_owner();
    _polynomialfitreport_owner(const _polynomialfitreport_owner &rhs);
    _polynomialfitreport_owner& operator=(const _polynomialfitreport_owner &rhs);
    virtual ~_polynomialfitreport_owner();
    alglib_impl::polynomialfitreport* c_ptr();
    alglib_impl::polynomialfitreport* c_ptr() const;
protected:
    alglib_impl::polynomialfitreport *p_struct;
};
class polynomialfitreport : public _polynomialfitreport_owner
{
public:
    polynomialfitreport();
    polynomialfitreport(const polynomialfitreport &rhs);
    polynomialfitreport& operator=(const polynomialfitreport &rhs);
    virtual ~polynomialfitreport();
    double &taskrcond;
    double &rmserror;
    double &avgerror;
    double &avgrelerror;
    double &maxerror;

};


/*************************************************************************
Barycentric fitting report:
    RMSError        RMS error
    AvgError        average error
    AvgRelError     average relative error (for non-zero Y[I])
    MaxError        maximum error
    TaskRCond       reciprocal of task's condition number
*************************************************************************/
/* ************************************************ *************************
중풍 피팅 보고서 :
    RMSError RMS 오류
    평균 오류 평균 오류
    AvgRelError 평균 상대 오차 (0이 아닌 Y [I]의 경우)
    MaxError 최대 오류
    TaskRCond 작업 조건 번호의 역수입니다.
*************************************************** ********************** */
class _barycentricfitreport_owner
{
public:
    _barycentricfitreport_owner();
    _barycentricfitreport_owner(const _barycentricfitreport_owner &rhs);
    _barycentricfitreport_owner& operator=(const _barycentricfitreport_owner &rhs);
    virtual ~_barycentricfitreport_owner();
    alglib_impl::barycentricfitreport* c_ptr();
    alglib_impl::barycentricfitreport* c_ptr() const;
protected:
    alglib_impl::barycentricfitreport *p_struct;
};
class barycentricfitreport : public _barycentricfitreport_owner
{
public:
    barycentricfitreport();
    barycentricfitreport(const barycentricfitreport &rhs);
    barycentricfitreport& operator=(const barycentricfitreport &rhs);
    virtual ~barycentricfitreport();
    double &taskrcond;
    ae_int_t &dbest;
    double &rmserror;
    double &avgerror;
    double &avgrelerror;
    double &maxerror;

};


/*************************************************************************
Spline fitting report:
    RMSError        RMS error
    AvgError        average error
    AvgRelError     average relative error (for non-zero Y[I])
    MaxError        maximum error

Fields  below are  filled  by   obsolete    functions   (Spline1DFitCubic,
Spline1DFitHermite). Modern fitting functions do NOT fill these fields:
    TaskRCond       reciprocal of task's condition number
*************************************************************************/
/* ************************************************ *************************
스플라인 맞춤 보고서 :
    RMSError RMS 오류
    평균 오류 평균 오류
    AvgRelError 평균 상대 오차 (0이 아닌 Y [I]의 경우)
    MaxError 최대 오류
아래 필드는 쓸모없는 함수로 채워집니다 (Spline1DFitCubic,
스플라인 1DFitHermite). 현대 피팅 함수는 다음 필드를 채우지 않습니다.
    TaskRCond 작업 조건 번호의 역수입니다.
*************************************************** ********************** */
class _spline1dfitreport_owner
{
public:
    _spline1dfitreport_owner();
    _spline1dfitreport_owner(const _spline1dfitreport_owner &rhs);
    _spline1dfitreport_owner& operator=(const _spline1dfitreport_owner &rhs);
    virtual ~_spline1dfitreport_owner();
    alglib_impl::spline1dfitreport* c_ptr();
    alglib_impl::spline1dfitreport* c_ptr() const;
protected:
    alglib_impl::spline1dfitreport *p_struct;
};
class spline1dfitreport : public _spline1dfitreport_owner
{
public:
    spline1dfitreport();
    spline1dfitreport(const spline1dfitreport &rhs);
    spline1dfitreport& operator=(const spline1dfitreport &rhs);
    virtual ~spline1dfitreport();
    double &taskrcond;
    double &rmserror;
    double &avgerror;
    double &avgrelerror;
    double &maxerror;

};


/*************************************************************************
Least squares fitting report. This structure contains informational fields
which are set by fitting functions provided by this unit.

Different functions initialize different sets of  fields,  so  you  should
read documentation on specific function you used in order  to  know  which
fields are initialized.

    TaskRCond       reciprocal of task's condition number
    IterationsCount number of internal iterations

    VarIdx          if user-supplied gradient contains errors  which  were
                    detected by nonlinear fitter, this  field  is  set  to
                    index  of  the  first  component  of gradient which is
                    suspected to be spoiled by bugs.

    RMSError        RMS error
    AvgError        average error
    AvgRelError     average relative error (for non-zero Y[I])
    MaxError        maximum error

    WRMSError       weighted RMS error

    CovPar          covariance matrix for parameters, filled by some solvers
    ErrPar          vector of errors in parameters, filled by some solvers
    ErrCurve        vector of fit errors -  variability  of  the  best-fit
                    curve, filled by some solvers.
    Noise           vector of per-point noise estimates, filled by
                    some solvers.
    R2              coefficient of determination (non-weighted, non-adjusted),
                    filled by some solvers.
*************************************************************************/
/* ************************************************ *************************
최소 제곱합 보고서. 이 구조체는 정보 필드를 포함합니다.
본 기기가 제공하는 피팅 기능으로 설정됩니다.
다른 함수는 다른 필드 집합을 초기화하므로
어떤 기능을 사용했는지에 대한 문서를 읽으십시오.
필드가 초기화됩니다.
    TaskRCond 작업 조건 번호의 역수입니다.
    IterationsCount 내부 반복 횟수
    사용자 제공 그래디언트에 오류가있는 경우 VarIdx
                    비선형 채터에 의해 검출되면,이 필드는
                    기울기의 첫 번째 구성 요소 색인입니다.
                    벌레들에 의해 망쳐 놓은 것으로 의심된다.
    RMSError RMS 오류
    평균 오류 평균 오류
    AvgRelError 평균 상대 오차 (0이 아닌 Y [I]의 경우)
    MaxError 최대 오류
    WRMSError 가중 된 RMS 오류
    일부 해결사로 채워진 매개 변수에 대한 CovPar 공분산 행렬
    ErrPar 매개 변수의 오류 벡터, 일부 해결자가 채움
    ErrCurve 적합 오차 벡터 - 최적 적합성의 변동성
                    곡선, 일부 해법에 의해 채워진.
    로 채워지는 포인트 별 잡음 추정의 잡음 벡터
                    일부 해결사.
    R2 결정 계수 (비 가중치, 조정되지 않음),
                    몇 가지 해결사가 가득 찼습니다.
*************************************************** ********************** */
class _lsfitreport_owner
{
public:
    _lsfitreport_owner();
    _lsfitreport_owner(const _lsfitreport_owner &rhs);
    _lsfitreport_owner& operator=(const _lsfitreport_owner &rhs);
    virtual ~_lsfitreport_owner();
    alglib_impl::lsfitreport* c_ptr();
    alglib_impl::lsfitreport* c_ptr() const;
protected:
    alglib_impl::lsfitreport *p_struct;
};
class lsfitreport : public _lsfitreport_owner
{
public:
    lsfitreport();
    lsfitreport(const lsfitreport &rhs);
    lsfitreport& operator=(const lsfitreport &rhs);
    virtual ~lsfitreport();
    double &taskrcond;
    ae_int_t &iterationscount;
    ae_int_t &varidx;
    double &rmserror;
    double &avgerror;
    double &avgrelerror;
    double &maxerror;
    double &wrmserror;
    real_2d_array covpar;
    real_1d_array errpar;
    real_1d_array errcurve;
    real_1d_array noise;
    double &r2;

};


/*************************************************************************
Nonlinear fitter.

You should use ALGLIB functions to work with fitter.
Never try to access its fields directly!
*************************************************************************/
/* ************************************************ *************************
비선형 배관공.
ALGLIB 함수를 사용하여 작업자와 작업해야합니다.
필드에 직접 액세스하지 마세요.
*************************************************** ********************** */
class _lsfitstate_owner
{
public:
    _lsfitstate_owner();
    _lsfitstate_owner(const _lsfitstate_owner &rhs);
    _lsfitstate_owner& operator=(const _lsfitstate_owner &rhs);
    virtual ~_lsfitstate_owner();
    alglib_impl::lsfitstate* c_ptr();
    alglib_impl::lsfitstate* c_ptr() const;
protected:
    alglib_impl::lsfitstate *p_struct;
};
class lsfitstate : public _lsfitstate_owner
{
public:
    lsfitstate();
    lsfitstate(const lsfitstate &rhs);
    lsfitstate& operator=(const lsfitstate &rhs);
    virtual ~lsfitstate();
    ae_bool &needf;
    ae_bool &needfg;
    ae_bool &needfgh;
    ae_bool &xupdated;
    real_1d_array c;
    double &f;
    real_1d_array g;
    real_2d_array h;
    real_1d_array x;

};

/*************************************************************************
Parametric spline inteprolant: 2-dimensional curve.

You should not try to access its members directly - use PSpline2XXXXXXXX()
functions instead.
*************************************************************************/
/* ************************************************ *************************
파라 메트릭 스플라인 inteprolant : 2 차원 커브.
PSpline2XXXXXXXX ()를 사용하여 멤버에 직접 액세스해서는 안됩니다.
기능을 대신합니다.
*************************************************** ********************** */
class _pspline2interpolant_owner
{
public:
    _pspline2interpolant_owner();
    _pspline2interpolant_owner(const _pspline2interpolant_owner &rhs);
    _pspline2interpolant_owner& operator=(const _pspline2interpolant_owner &rhs);
    virtual ~_pspline2interpolant_owner();
    alglib_impl::pspline2interpolant* c_ptr();
    alglib_impl::pspline2interpolant* c_ptr() const;
protected:
    alglib_impl::pspline2interpolant *p_struct;
};
class pspline2interpolant : public _pspline2interpolant_owner
{
public:
    pspline2interpolant();
    pspline2interpolant(const pspline2interpolant &rhs);
    pspline2interpolant& operator=(const pspline2interpolant &rhs);
    virtual ~pspline2interpolant();

};


/*************************************************************************
Parametric spline inteprolant: 3-dimensional curve.

You should not try to access its members directly - use PSpline3XXXXXXXX()
functions instead.
*************************************************************************/
/* ************************************************ *************************
파라 메트릭 스플라인 inteprolant : 3 차원 커브.
PSpline3XXXXXXXX ()를 사용하여 멤버에 직접 액세스해서는 안됩니다.
기능을 대신합니다.
*************************************************** ********************** */
class _pspline3interpolant_owner
{
public:
    _pspline3interpolant_owner();
    _pspline3interpolant_owner(const _pspline3interpolant_owner &rhs);
    _pspline3interpolant_owner& operator=(const _pspline3interpolant_owner &rhs);
    virtual ~_pspline3interpolant_owner();
    alglib_impl::pspline3interpolant* c_ptr();
    alglib_impl::pspline3interpolant* c_ptr() const;
protected:
    alglib_impl::pspline3interpolant *p_struct;
};
class pspline3interpolant : public _pspline3interpolant_owner
{
public:
    pspline3interpolant();
    pspline3interpolant(const pspline3interpolant &rhs);
    pspline3interpolant& operator=(const pspline3interpolant &rhs);
    virtual ~pspline3interpolant();

};

/*************************************************************************
RBF model.

Never try to directly work with fields of this object - always use  ALGLIB
functions to use this object.
*************************************************************************/
/* ************************************************ *************************
RBF 모델.
이 객체의 필드를 직접 사용하지 마십시오. 항상 ALGLIB를 사용하십시오.
이 객체를 사용하는 함수.
*************************************************** ********************** */
class _rbfmodel_owner
{
public:
    _rbfmodel_owner();
    _rbfmodel_owner(const _rbfmodel_owner &rhs);
    _rbfmodel_owner& operator=(const _rbfmodel_owner &rhs);
    virtual ~_rbfmodel_owner();
    alglib_impl::rbfmodel* c_ptr();
    alglib_impl::rbfmodel* c_ptr() const;
protected:
    alglib_impl::rbfmodel *p_struct;
};
class rbfmodel : public _rbfmodel_owner
{
public:
    rbfmodel();
    rbfmodel(const rbfmodel &rhs);
    rbfmodel& operator=(const rbfmodel &rhs);
    virtual ~rbfmodel();

};


/*************************************************************************
RBF solution report:
* TerminationType   -   termination type, positive values - success,
                        non-positive - failure.
*************************************************************************/
/* ************************************************ *************************
RBF 솔루션 보고서 :
* TerminationType - 종료 유형, 양수 값 - 성공,
                        비 양성 - 실패.
*************************************************** ********************** */
class _rbfreport_owner
{
public:
    _rbfreport_owner();
    _rbfreport_owner(const _rbfreport_owner &rhs);
    _rbfreport_owner& operator=(const _rbfreport_owner &rhs);
    virtual ~_rbfreport_owner();
    alglib_impl::rbfreport* c_ptr();
    alglib_impl::rbfreport* c_ptr() const;
protected:
    alglib_impl::rbfreport *p_struct;
};
class rbfreport : public _rbfreport_owner
{
public:
    rbfreport();
    rbfreport(const rbfreport &rhs);
    rbfreport& operator=(const rbfreport &rhs);
    virtual ~rbfreport();
    ae_int_t &arows;
    ae_int_t &acols;
    ae_int_t &annz;
    ae_int_t &iterationscount;
    ae_int_t &nmv;
    ae_int_t &terminationtype;

};

/*************************************************************************
2-dimensional spline inteprolant
*************************************************************************/
/* ************************************************ *************************
2 차원 스플라인 인터 롤란 트
*************************************************** ********************** */
class _spline2dinterpolant_owner
{
public:
    _spline2dinterpolant_owner();
    _spline2dinterpolant_owner(const _spline2dinterpolant_owner &rhs);
    _spline2dinterpolant_owner& operator=(const _spline2dinterpolant_owner &rhs);
    virtual ~_spline2dinterpolant_owner();
    alglib_impl::spline2dinterpolant* c_ptr();
    alglib_impl::spline2dinterpolant* c_ptr() const;
protected:
    alglib_impl::spline2dinterpolant *p_struct;
};
class spline2dinterpolant : public _spline2dinterpolant_owner
{
public:
    spline2dinterpolant();
    spline2dinterpolant(const spline2dinterpolant &rhs);
    spline2dinterpolant& operator=(const spline2dinterpolant &rhs);
    virtual ~spline2dinterpolant();

};

/*************************************************************************
3-dimensional spline inteprolant
*************************************************************************/
/* ************************************************ *************************
3 차원 스플라인 혈행 세포
*************************************************** ********************** */
class _spline3dinterpolant_owner
{
public:
    _spline3dinterpolant_owner();
    _spline3dinterpolant_owner(const _spline3dinterpolant_owner &rhs);
    _spline3dinterpolant_owner& operator=(const _spline3dinterpolant_owner &rhs);
    virtual ~_spline3dinterpolant_owner();
    alglib_impl::spline3dinterpolant* c_ptr();
    alglib_impl::spline3dinterpolant* c_ptr() const;
protected:
    alglib_impl::spline3dinterpolant *p_struct;
};
class spline3dinterpolant : public _spline3dinterpolant_owner
{
public:
    spline3dinterpolant();
    spline3dinterpolant(const spline3dinterpolant &rhs);
    spline3dinterpolant& operator=(const spline3dinterpolant &rhs);
    virtual ~spline3dinterpolant();

};

/*************************************************************************
IDW interpolation

INPUT PARAMETERS:
    Z   -   IDW interpolant built with one of model building
            subroutines.
    X   -   array[0..NX-1], interpolation point

Result:
    IDW interpolant Z(X)

  -- ALGLIB --
     Copyright 02.03.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
IDW 보간법
입력 매개 변수 :
    모델 건물 중 하나와 함께 지어진 Z - IDW 보간
            서브 루틴.
    X- 배열 [0..NX-1], 보간 점
결과:
    IDW 보간 기 Z (X)
  - ALGLIB -
     저작권 02.03.2010 Bochkanov Sergey
*************************************************** ********************** */
double idwcalc(const idwinterpolant &z, const real_1d_array &x);


/*************************************************************************
IDW interpolant using modified Shepard method for uniform point
distributions.

INPUT PARAMETERS:
    XY  -   X and Y values, array[0..N-1,0..NX].
            First NX columns contain X-values, last column contain
            Y-values.
    N   -   number of nodes, N>0.
    NX  -   space dimension, NX>=1.
    D   -   nodal function type, either:
            * 0     constant  model.  Just  for  demonstration only, worst
                    model ever.
            * 1     linear model, least squares fitting. Simpe  model  for
                    datasets too small for quadratic models
            * 2     quadratic  model,  least  squares  fitting. Best model
                    available (if your dataset is large enough).
            * -1    "fast"  linear  model,  use  with  caution!!!   It  is
                    significantly  faster than linear/quadratic and better
                    than constant model. But it is less robust (especially
                    in the presence of noise).
    NQ  -   number of points used to calculate  nodal  functions  (ignored
            for constant models). NQ should be LARGER than:
            * max(1.5*(1+NX),2^NX+1) for linear model,
            * max(3/4*(NX+2)*(NX+1),2^NX+1) for quadratic model.
            Values less than this threshold will be silently increased.
    NW  -   number of points used to calculate weights and to interpolate.
            Required: >=2^NX+1, values less than this  threshold  will  be
            silently increased.
            Recommended value: about 2*NQ

OUTPUT PARAMETERS:
    Z   -   IDW interpolant.

NOTES:
  * best results are obtained with quadratic models, worst - with constant
    models
  * when N is large, NQ and NW must be significantly smaller than  N  both
    to obtain optimal performance and to obtain optimal accuracy. In 2  or
    3-dimensional tasks NQ=15 and NW=25 are good values to start with.
  * NQ  and  NW  may  be  greater  than  N.  In  such  cases  they will be
    automatically decreased.
  * this subroutine is always succeeds (as long as correct parameters  are
    passed).
  * see  'Multivariate  Interpolation  of Large Sets of Scattered Data' by
    Robert J. Renka for more information on this algorithm.
  * this subroutine assumes that point distribution is uniform at the small
    scales.  If  it  isn't  -  for  example,  points are concentrated along
    "lines", but "lines" distribution is uniform at the larger scale - then
    you should use IDWBuildModifiedShepardR()


  -- ALGLIB PROJECT --
     Copyright 02.03.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
균일 한 점에 대해 수정 된 셰퍼드 (Shepard) 방법을 사용한 IDW 보간
배포판.
입력 매개 변수 :
    XY - X 및 Y 값, array [0..N-1,0..NX].
            첫 번째 NX 열은 X 값을 포함하고 마지막 열은 X 값을 포함합니다.
            Y 값.
    N - 노드 수, N> 0.
    NX - 공간 차원, NX> = 1.
    D 조 - 노드 기능 유형 중 하나 :
            * 0 상수 모델. 데모 용으로 만, 최악의 경우에
                    모델.
            * 1 선형 모델, 최소 제곱 피팅. Simpe 모델 용
                    2 차 모델에 비해 너무 작은 데이터 세트
            * 2 2 차 모델, 최소 제곱 피팅. 최고의 모델
                    사용할 수 있습니다 (데이터 세트가 충분히 큰 경우).
            * -1 "빠른"선형 모델,주의해서 사용하십시오 !!! 그것은
                    선형 / 2 차 이상보다 훨씬 빠른 속도
                    상수 모델보다. 그러나 덜 강력합니다 (특히
                    노이즈가있는 경우).
    NQ - 노드 기능을 계산하는 데 사용 된 점의 수 (무시 됨)
            상수 모델의 경우). NQ는 다음보다 크다.
            선형 모델의 경우 max * (1.5 * (1 + NX), 2 ^ NX + 1)
            * 2 차 모델의 경우 max (3 / 4 * (NX + 2) * (NX + 1), 2 ^ NX + 1)
            이 임계 값보다 작은 값은 자동으로 증가합니다.
    NW - 가중치를 계산하고 보간하는 데 사용되는 점의 수입니다.
            필수 :> = 2 ^ NX + 1,이 임계 값보다 작은 값은
            조용히 증가했다.
            권장 값 : 약 2 * NQ
출력 매개 변수 :
    Z - IDW 보간.
노트:
  * 최상의 결과는 2 차 모델로 얻습니다. 최악 - ​​상수
    모델
  * N이 클 때 NQ와 NW는 N보다 훨씬 작아야합니다.
    최적의 성능을 얻고 최적의 정확도를 얻을 수 있습니다. 2 또는
    3 차원 작업 NQ = 15 및 NW = 25는 좋은 값입니다.
  * NQ와 NW는 N보다 클 수 있습니다.
    자동으로 감소했습니다.
  *이 서브 루틴은 항상 성공합니다 (올바른 매개 변수가
    통과).
  * '분산 된 데이터 세트의 다 변수 보간'을 참조하십시오.
    이 알고리즘에 대한 자세한 정보는 Robert J. Renka.
  *이 서브 루틴은 점 분포가 작은 점
    저울. 그렇지 않은 경우 - 예를 들어 점수가 집중되어있는 경우
    "선들"이지만, "선들"분포는 더 큰 축척에서 균일하다.
    IDWBuildModifiedShepardR ()을 사용해야합니다.
  - ALGLIB 프로젝트 -
     저작권 02.03.2010 Bochkanov Sergey
*************************************************** ********************** */
void idwbuildmodifiedshepard(const real_2d_array &xy, const ae_int_t n, const ae_int_t nx, const ae_int_t d, const ae_int_t nq, const ae_int_t nw, idwinterpolant &z);


/*************************************************************************
IDW interpolant using modified Shepard method for non-uniform datasets.

This type of model uses  constant  nodal  functions and interpolates using
all nodes which are closer than user-specified radius R. It  may  be  used
when points distribution is non-uniform at the small scale, but it  is  at
the distances as large as R.

INPUT PARAMETERS:
    XY  -   X and Y values, array[0..N-1,0..NX].
            First NX columns contain X-values, last column contain
            Y-values.
    N   -   number of nodes, N>0.
    NX  -   space dimension, NX>=1.
    R   -   radius, R>0

OUTPUT PARAMETERS:
    Z   -   IDW interpolant.

NOTES:
* if there is less than IDWKMin points within  R-ball,  algorithm  selects
  IDWKMin closest ones, so that continuity properties of  interpolant  are
  preserved even far from points.

  -- ALGLIB PROJECT --
     Copyright 11.04.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
비 균일 데이터 세트에 대해 수정 된 셰퍼드 방법을 사용하는 IDW 보간.
이 유형의 모델은 상수 노드 기능을 사용하고 다음을 사용하여 보간합니다.
사용자가 지정한 반지름 R보다 가까운 모든 노드
소규모에서는 점 분포가 균일하지 않지만
R만큼 큰 거리.
입력 매개 변수 :
    XY - X 및 Y 값, array [0..N-1,0..NX].
            첫 번째 NX 열은 X 값을 포함하고 마지막 열은 X 값을 포함합니다.
            Y 값.
    N - 노드 수, N> 0.
    NX - 공간 차원, NX> = 1.
    R - 반경, R> 0
출력 매개 변수 :
    Z - IDW 보간.
노트:
* R-ball 내에서 IDWKMin 포인트보다 작 으면 알고리즘은
  IDWK 가장 가까운 것, 그래서 보간의 연속성 속성은
  심지어 지점에서 멀리 보존.
  - ALGLIB 프로젝트 -
     Copyright 11.04.2010 Bochkanov Sergey
*************************************************** ********************** */
void idwbuildmodifiedshepardr(const real_2d_array &xy, const ae_int_t n, const ae_int_t nx, const double r, idwinterpolant &z);


/*************************************************************************
IDW model for noisy data.

This subroutine may be used to handle noisy data, i.e. data with noise  in
OUTPUT values.  It differs from IDWBuildModifiedShepard() in the following
aspects:
* nodal functions are not constrained to pass through  nodes:  Qi(xi)<>yi,
  i.e. we have fitting  instead  of  interpolation.
* weights which are used during least  squares fitting stage are all equal
  to 1.0 (independently of distance)
* "fast"-linear or constant nodal functions are not supported (either  not
  robust enough or too rigid)

This problem require far more complex tuning than interpolation  problems.
Below you can find some recommendations regarding this problem:
* focus on tuning NQ; it controls noise reduction. As for NW, you can just
  make it equal to 2*NQ.
* you can use cross-validation to determine optimal NQ.
* optimal NQ is a result of complex tradeoff  between  noise  level  (more
  noise = larger NQ required) and underlying  function  complexity  (given
  fixed N, larger NQ means smoothing of compex features in the data).  For
  example, NQ=N will reduce noise to the minimum level possible,  but  you
  will end up with just constant/linear/quadratic (depending on  D)  least
  squares model for the whole dataset.

INPUT PARAMETERS:
    XY  -   X and Y values, array[0..N-1,0..NX].
            First NX columns contain X-values, last column contain
            Y-values.
    N   -   number of nodes, N>0.
    NX  -   space dimension, NX>=1.
    D   -   nodal function degree, either:
            * 1     linear model, least squares fitting. Simpe  model  for
                    datasets too small for quadratic models (or  for  very
                    noisy problems).
            * 2     quadratic  model,  least  squares  fitting. Best model
                    available (if your dataset is large enough).
    NQ  -   number of points used to calculate nodal functions.  NQ should
            be  significantly   larger   than  1.5  times  the  number  of
            coefficients in a nodal function to overcome effects of noise:
            * larger than 1.5*(1+NX) for linear model,
            * larger than 3/4*(NX+2)*(NX+1) for quadratic model.
            Values less than this threshold will be silently increased.
    NW  -   number of points used to calculate weights and to interpolate.
            Required: >=2^NX+1, values less than this  threshold  will  be
            silently increased.
            Recommended value: about 2*NQ or larger

OUTPUT PARAMETERS:
    Z   -   IDW interpolant.

NOTES:
  * best results are obtained with quadratic models, linear models are not
    recommended to use unless you are pretty sure that it is what you want
  * this subroutine is always succeeds (as long as correct parameters  are
    passed).
  * see  'Multivariate  Interpolation  of Large Sets of Scattered Data' by
    Robert J. Renka for more information on this algorithm.


  -- ALGLIB PROJECT --
     Copyright 02.03.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
시끄러운 데이터를위한 IDW 모델.
이 서브 루틴은 잡음이 많은 데이터, 즉 잡음이있는 데이터를 처리하는 데 사용될 수 있습니다.
출력 값. IDWBuildModifiedShepard ()와 다음과 다릅니다.
상들:
* 노드 함수는 노드를 통과하도록 제한되지 않습니다. Qi (xi) <> yi,
  즉 우리는 보간 대신 피팅을합니다.
* 최소 제곱 피팅 단계에서 사용되는 가중치는 모두 동일합니다.
  ~ 1.0 (거리에 관계없이)
* "빠른"선형 또는 상수 노드 기능은 지원되지 않습니다 (
  충분히 견고하거나 너무 단단함)
이 문제는 보간 문제보다 훨씬 복잡한 튜닝을 필요로합니다.
아래에서이 문제와 관련된 몇 가지 권장 사항을 찾을 수 있습니다.
* NQ 튜닝에 중점을 둡니다. 그것은 소음 감소를 제어합니다. NW와 마찬가지로
  2 * NQ와 동일하게 만드십시오.
* 교차 유효성 검사를 사용하여 최적의 NQ를 결정할 수 있습니다.
* 최적의 NQ는 노이즈 레벨 (
  잡음 =보다 큰 NQ 요구) 및 기본 함수 복잡성 (주어진 NQ
  고정 N, 더 큰 NQ는 데이터에서 compex 기능의 평활화를 의미합니다). 에 대한
  예를 들어, NQ = N은 가능한 한 최소 수준으로 노이즈를 줄이지 만,
  (D에 따라) 상수 / 선형 / 2 차 함수로 끝날 것입니다.
  전체 데이터 세트에 대한 사각형 모델.
입력 매개 변수 :
    XY - X 및 Y 값, array [0..N-1,0..NX].
            첫 번째 NX 열은 X 값을 포함하고 마지막 열은 X 값을 포함합니다.
            Y 값.
    N - 노드 수, N> 0.
    NX - 공간 차원, NX> = 1.
    D 조 - 노드 기능 학위 중 하나 :
            * 1 선형 모델, 최소 제곱 피팅. Simpe 모델 용
                    2 차 모델의 경우 너무 작은 데이터 세트 (또는
                    시끄러운 문제).
            * 2 2 차 모델, 최소 제곱 피팅. 최고의 모델
                    사용할 수 있습니다 (데이터 세트가 충분히 큰 경우).
    NQ - 노드 기능을 계산하는 데 사용 된 점의 수입니다. NQ는해야한다.
            의 1.5 배보다 훨씬 클 수있다.
            잡음의 영향을 극복하기위한 노드 함수의 계수 :
            * 선형 모델의 경우 1.5 * (1 + NX)보다 크고,
            * 2 차 모델의 경우 3/4 * (NX + 2) * (NX + 1)보다 큽니다.
            이 임계 값보다 작은 값은 자동으로 증가합니다.
    NW - 가중치를 계산하고 보간하는 데 사용되는 점의 수입니다.
            필수 :> = 2 ^ NX + 1,이 임계 값보다 작은 값은
            조용히 증가했다.
            권장 값 : 약 2 * NQ 이상
출력 매개 변수 :
    Z - IDW 보간.
노트:
  * 최상의 결과는 2 차 모델로 얻어지며, 선형 모델은 그렇지 않습니다.
    그것이 당신이 원하는 것이라고 확신하지 않는 한 사용을 권장합니다.
  *이 서브 루틴은 항상 성공합니다 (올바른 매개 변수가
    통과).
  * '분산 된 데이터 세트의 다 변수 보간'을 참조하십시오.
    이 알고리즘에 대한 자세한 정보는 Robert J. Renka.
  - ALGLIB 프로젝트 -
     저작권 02.03.2010 Bochkanov Sergey
*************************************************** ********************** */
void idwbuildnoisy(const real_2d_array &xy, const ae_int_t n, const ae_int_t nx, const ae_int_t d, const ae_int_t nq, const ae_int_t nw, idwinterpolant &z);

/*************************************************************************
Rational interpolation using barycentric formula

F(t) = SUM(i=0,n-1,w[i]*f[i]/(t-x[i])) / SUM(i=0,n-1,w[i]/(t-x[i]))

Input parameters:
    B   -   barycentric interpolant built with one of model building
            subroutines.
    T   -   interpolation point

Result:
    barycentric interpolant F(t)

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
중성 수식을 사용한 합리적인 보간법
/ SUM (i = 0, n-1, w [i] / (tx [i])], F (t) = SUM (i = 0, n-1, w [i] [나는]))
입력 매개 변수 :
    B - 모델 건물 중 하나를 사용하여 빌드 된 중거리 보간법
            서브 루틴.
    T - 보간 점
결과:
    중력 보간법 F (t)
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
double barycentriccalc(const barycentricinterpolant &b, const double t);


/*************************************************************************
Differentiation of barycentric interpolant: first derivative.

Algorithm used in this subroutine is very robust and should not fail until
provided with values too close to MaxRealNumber  (usually  MaxRealNumber/N
or greater will overflow).

INPUT PARAMETERS:
    B   -   barycentric interpolant built with one of model building
            subroutines.
    T   -   interpolation point

OUTPUT PARAMETERS:
    F   -   barycentric interpolant at T
    DF  -   first derivative

NOTE


  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
barycentric interpolant의 차등화 : 1 차 미분.
이 서브 루틴에 사용 된 알고리즘은 매우 강력하며 실패 할 때까지 실패하지 않아야합니다.
MaxRealNumber에 너무 가까운 값을 제공합니다 (일반적으로 MaxRealNumber / N
이상이 오버 플로우됩니다).
입력 매개 변수 :
    B - 모델 건물 중 하나를 사용하여 빌드 된 중거리 보간법
            서브 루틴.
    T - 보간 점
출력 매개 변수 :
    F - T에서의 중성 삽입
    DF - 1 차 미분
노트
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void barycentricdiff1(const barycentricinterpolant &b, const double t, double &f, double &df);


/*************************************************************************
Differentiation of barycentric interpolant: first/second derivatives.

INPUT PARAMETERS:
    B   -   barycentric interpolant built with one of model building
            subroutines.
    T   -   interpolation point

OUTPUT PARAMETERS:
    F   -   barycentric interpolant at T
    DF  -   first derivative
    D2F -   second derivative

NOTE: this algorithm may fail due to overflow/underflor if  used  on  data
whose values are close to MaxRealNumber or MinRealNumber.  Use more robust
BarycentricDiff1() subroutine in such cases.


  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/*  ************************************************ *************************
barycentric interpolant의 차별화 : 1 차 / 2 차 파생 요소.
입력 매개 변수 :
    B - 모델 건물 중 하나를 사용하여 빌드 된 중거리 보간법
            서브 루틴.
    T - 보간 점
출력 매개 변수 :
    F - T에서의 중성 삽입
    DF - 1 차 미분
    D2F - 2 차 미분
참고 :이 알고리즘은 데이터에 사용되는 경우 오버플로 / 언더 플로로 인해 실패 할 수 있습니다.
값은 MaxRealNumber 또는 MinRealNumber에 가깝습니다. 보다 견고한 사용
그런 경우 BarycentricDiff1 () 서브 루틴.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void barycentricdiff2(const barycentricinterpolant &b, const double t, double &f, double &df, double &d2f);


/*************************************************************************
This subroutine performs linear transformation of the argument.

INPUT PARAMETERS:
    B       -   rational interpolant in barycentric form
    CA, CB  -   transformation coefficients: x = CA*t + CB

OUTPUT PARAMETERS:
    B       -   transformed interpolant with X replaced by T

  -- ALGLIB PROJECT --
     Copyright 19.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 인수의 선형 변환을 수행합니다.
입력 매개 변수 :
    B - 중성자 형태의 합리적인 보간법
    CA, CB - 변환 계수 : x = CA * t + CB
출력 매개 변수 :
    B - X로 대체 된 보간법을 T로 바꾼다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 19.08.2009
*************************************************** ********************** */
void barycentriclintransx(const barycentricinterpolant &b, const double ca, const double cb);


/*************************************************************************
This  subroutine   performs   linear  transformation  of  the  barycentric
interpolant.

INPUT PARAMETERS:
    B       -   rational interpolant in barycentric form
    CA, CB  -   transformation coefficients: B2(x) = CA*B(x) + CB

OUTPUT PARAMETERS:
    B       -   transformed interpolant

  -- ALGLIB PROJECT --
     Copyright 19.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 barycentric의 선형 변환을 수행합니다.
보간법.
입력 매개 변수 :
    B - 중성자 형태의 합리적인 보간법
    CA, CB - 변환 계수 : B2 (x) = CA * B (x) + CB
출력 매개 변수 :
    B - 변형 된 보간법
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 19.08.2009
*************************************************** ********************** */
void barycentriclintransy(const barycentricinterpolant &b, const double ca, const double cb);


/*************************************************************************
Extracts X/Y/W arrays from rational interpolant

INPUT PARAMETERS:
    B   -   barycentric interpolant

OUTPUT PARAMETERS:
    N   -   nodes count, N>0
    X   -   interpolation nodes, array[0..N-1]
    F   -   function values, array[0..N-1]
    W   -   barycentric weights, array[0..N-1]

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
합리적인 보간에서 X / Y / W 배열 추출
입력 매개 변수 :
    B - 중력 보간법
출력 매개 변수 :
    N - 노드 수, N> 0
    X - 보간 노드, array [0..N-1]
    F - 함수 값, array [0..N-1]
    W - 중력 가중치, 배열 [0..N-1]
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void barycentricunpack(const barycentricinterpolant &b, ae_int_t &n, real_1d_array &x, real_1d_array &y, real_1d_array &w);


/*************************************************************************
Rational interpolant from X/Y/W arrays

F(t) = SUM(i=0,n-1,w[i]*f[i]/(t-x[i])) / SUM(i=0,n-1,w[i]/(t-x[i]))

INPUT PARAMETERS:
    X   -   interpolation nodes, array[0..N-1]
    F   -   function values, array[0..N-1]
    W   -   barycentric weights, array[0..N-1]
    N   -   nodes count, N>0

OUTPUT PARAMETERS:
    B   -   barycentric interpolant built from (X, Y, W)

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
X / Y / W 배열의 Rational interpolant
/ SUM (i = 0, n-1, w [i] / (tx [i])], F (t) = SUM (i = 0, n-1, w [i] [나는]))
입력 매개 변수 :
    X - 보간 노드, array [0..N-1]
    F - 함수 값, array [0..N-1]
    W - 중력 가중치, 배열 [0..N-1]
    N - 노드 수, N> 0
출력 매개 변수 :
    B - (X, Y, W)에서 빌드 된 중거리 보간법
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void barycentricbuildxyw(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, barycentricinterpolant &b);


/*************************************************************************
Rational interpolant without poles

The subroutine constructs the rational interpolating function without real
poles  (see  'Barycentric rational interpolation with no  poles  and  high
rates of approximation', Michael S. Floater. and  Kai  Hormann,  for  more
information on this subject).

Input parameters:
    X   -   interpolation nodes, array[0..N-1].
    Y   -   function values, array[0..N-1].
    N   -   number of nodes, N>0.
    D   -   order of the interpolation scheme, 0 <= D <= N-1.
            D<0 will cause an error.
            D>=N it will be replaced with D=N-1.
            if you don't know what D to choose, use small value about 3-5.

Output parameters:
    B   -   barycentric interpolant.

Note:
    this algorithm always succeeds and calculates the weights  with  close
    to machine precision.

  -- ALGLIB PROJECT --
     Copyright 17.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
극이없는 합리적인 보간법
서브 루틴은 실제없이 합리적인 보간 함수를 만듭니다.
극점 (극점이없는 고저 평행 보간법 참조)
근사 율 ', Michael S. Floater. 카이 호르만 (Kai Hormann)
이 주제에 대한 정보).
입력 매개 변수 :
    X - 보간 노드, array [0..N-1].
    Y - 함수 값, array [0..N-1].
    N - 노드 수, N> 0.
    D - 보간 체계의 차수, 0 <= D <= N-1.
            D <0이면 오류가 발생합니다.
            D> = N이면 D = N-1로 바뀝니다.
            선택할 D를 모른다면 3-5 정도의 작은 값을 사용하십시오.
출력 매개 변수 :
    B - barycentric interpolant.
노트 :
    이 알고리즘은 항상 성공하고 닫음으로 가중치를 계산합니다.
    기계 정밀도.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 17.06.2007
*************************************************** ********************** */
void barycentricbuildfloaterhormann(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t d, barycentricinterpolant &b);

/*************************************************************************
Conversion from barycentric representation to Chebyshev basis.
This function has O(N^2) complexity.

INPUT PARAMETERS:
    P   -   polynomial in barycentric form
    A,B -   base interval for Chebyshev polynomials (see below)
            A<>B

OUTPUT PARAMETERS
    T   -   coefficients of Chebyshev representation;
            P(x) = sum { T[i]*Ti(2*(x-A)/(B-A)-1), i=0..N-1 },
            where Ti - I-th Chebyshev polynomial.

NOTES:
    barycentric interpolant passed as P may be either polynomial  obtained
    from  polynomial  interpolation/ fitting or rational function which is
    NOT polynomial. We can't distinguish between these two cases, and this
    algorithm just tries to work assuming that P IS a polynomial.  If not,
    algorithm will return results, but they won't have any meaning.

  -- ALGLIB --
     Copyright 30.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
barycentric representation에서 Chebyshev basis로 변환.
이 함수는 O (N ^ 2) 복잡도를가집니다.
입력 매개 변수 :
    P - 다항식 형태의 다항식
    A, B - Chebyshev 다항식의 기본 간격 (아래 참조)
            A <> B
출력 매개 변수
    T - Chebyshev 표현의 계수;
            P (x) = sum {T [i] * Ti (2 * (xA) / (BA) -1), i = 0..N-
            여기서 Ti - I - th Chebyshev 다항식.
노트:
    P로 전달 된 중성분 보간은 다항식이 될 수 있습니다.
    다항식 보간 / 피팅 또는 합리적인 함수로부터
    다항식이 아닙니다. 이 두 가지 경우를 구분할 수 없으며
    알고리즘은 P가 다항식이라고 가정하여 작업을 시도합니다. 그렇지 않은 경우,
    알고리즘은 결과를 반환하지만 아무런 의미가 없습니다.
  - ALGLIB -
     저작권 30.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void polynomialbar2cheb(const barycentricinterpolant &p, const double a, const double b, real_1d_array &t);


/*************************************************************************
Conversion from Chebyshev basis to barycentric representation.
This function has O(N^2) complexity.

INPUT PARAMETERS:
    T   -   coefficients of Chebyshev representation;
            P(x) = sum { T[i]*Ti(2*(x-A)/(B-A)-1), i=0..N },
            where Ti - I-th Chebyshev polynomial.
    N   -   number of coefficients:
            * if given, only leading N elements of T are used
            * if not given, automatically determined from size of T
    A,B -   base interval for Chebyshev polynomials (see above)
            A<B

OUTPUT PARAMETERS
    P   -   polynomial in barycentric form

  -- ALGLIB --
     Copyright 30.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Chebyshev 기초에서 중성 표상으로의 전환.
이 함수는 O (N ^ 2) 복잡도를가집니다.
입력 매개 변수 :
    T - Chebyshev 표현의 계수;
            P (x) = sum {T [i] * Ti (2 * (xA) / (BA) -1), i = 0..N}
            여기서 Ti - I - th Chebyshev 다항식.
    N - 계수의 수 :
            * 주어진 경우 T의 선행 N 요소 만 사용됩니다.
            * 주어지지 않은 경우, T의 크기로부터 자동으로 결정됩니다.
    A, B - Chebyshev 다항식의 기본 간격 (위 참조)
            A <B
출력 매개 변수
    P - 다항식 형태의 다항식
  - ALGLIB -
     저작권 30.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void polynomialcheb2bar(const real_1d_array &t, const ae_int_t n, const double a, const double b, barycentricinterpolant &p);
void polynomialcheb2bar(const real_1d_array &t, const double a, const double b, barycentricinterpolant &p);


/*************************************************************************
Conversion from barycentric representation to power basis.
This function has O(N^2) complexity.

INPUT PARAMETERS:
    P   -   polynomial in barycentric form
    C   -   offset (see below); 0.0 is used as default value.
    S   -   scale (see below);  1.0 is used as default value. S<>0.

OUTPUT PARAMETERS
    A   -   coefficients, P(x) = sum { A[i]*((X-C)/S)^i, i=0..N-1 }
    N   -   number of coefficients (polynomial degree plus 1)

NOTES:
1.  this function accepts offset and scale, which can be  set  to  improve
    numerical properties of polynomial. For example, if P was obtained  as
    result of interpolation on [-1,+1],  you  can  set  C=0  and  S=1  and
    represent  P  as sum of 1, x, x^2, x^3 and so on. In most cases you it
    is exactly what you need.

    However, if your interpolation model was built on [999,1001], you will
    see significant growth of numerical errors when using {1, x, x^2, x^3}
    as basis. Representing P as sum of 1, (x-1000), (x-1000)^2, (x-1000)^3
    will be better option. Such representation can be  obtained  by  using
    1000.0 as offset C and 1.0 as scale S.

2.  power basis is ill-conditioned and tricks described above can't  solve
    this problem completely. This function  will  return  coefficients  in
    any  case,  but  for  N>8  they  will  become unreliable. However, N's
    less than 5 are pretty safe.

3.  barycentric interpolant passed as P may be either polynomial  obtained
    from  polynomial  interpolation/ fitting or rational function which is
    NOT polynomial. We can't distinguish between these two cases, and this
    algorithm just tries to work assuming that P IS a polynomial.  If not,
    algorithm will return results, but they won't have any meaning.

  -- ALGLIB --
     Copyright 30.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
barycentric representation에서 power basis 로의 변환.
이 함수는 O (N ^ 2) 복잡도를가집니다.
입력 매개 변수 :
    P - 다항식 형태의 다항식
    C - 오프셋 (아래 참조). 0.0이 기본값으로 사용됩니다.
    S - 규모 (아래 참조); 1.0이 기본값으로 사용됩니다. S ≠ 0.
출력 매개 변수
    A-coefficient, P (x) = sum {A [i] * ((XC) / S) ^ i, i = 0..N-1}
    N - 계수의 수 (다항식 차수 + 1)
노트:
1.이 기능은 오프셋 및 스케일을 허용하며,이를 개선하도록 설정할 수 있습니다
    다항식의 수치 적 속성. 예를 들어, P가
    [-1, + 1]에 대한 보간 결과, C = 0과 S = 1을 설정할 수 있고
    P를 1, x, x ^ 2, x ^ 3 등의 합으로 나타냅니다. 대부분의 경우
    정확히 당신이 필요로하는 것입니다.
    그러나 보간 모델이 [999,1001]에 빌드 된 경우
    {1, x, x ^ 2, x ^ 3}을 사용할 때 수치 오류가 크게 증가하는 것을보십시오.
    기초로서. P를 1, (x-1000), (x-1000) ^ 2, (x-1000) ^ 3
    더 나은 옵션이 될 것입니다. 이러한 표현은 다음을 사용하여 얻을 수 있습니다.
    오프셋 C로 1000.0, 스케일 S로 1.0
2. 힘 기초는 아픈 조건이 있고 전술 한 트릭은 풀 수 없다.
    이 문제는 완전히. 이 함수는
    어떤 경우이든, N> 8 일 때 그들은 신뢰할 수 없게 될 것이다. 그러나, N 's
    5 개 미만은 꽤 안전합니다.
3. P로 전달 된 중성분 보간은 다항식이 될 수 있습니다.
    다항식 보간 / 피팅 또는 합리적인 함수로부터
    다항식이 아닙니다. 이 두 가지 경우를 구분할 수 없으며
    알고리즘은 P가 다항식이라고 가정하여 작업을 시도합니다. 그렇지 않은 경우,
    알고리즘은 결과를 반환하지만 아무런 의미가 없습니다.
  - ALGLIB -
     저작권 30.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void polynomialbar2pow(const barycentricinterpolant &p, const double c, const double s, real_1d_array &a);
void polynomialbar2pow(const barycentricinterpolant &p, real_1d_array &a);


/*************************************************************************
Conversion from power basis to barycentric representation.
This function has O(N^2) complexity.

INPUT PARAMETERS:
    A   -   coefficients, P(x) = sum { A[i]*((X-C)/S)^i, i=0..N-1 }
    N   -   number of coefficients (polynomial degree plus 1)
            * if given, only leading N elements of A are used
            * if not given, automatically determined from size of A
    C   -   offset (see below); 0.0 is used as default value.
    S   -   scale (see below);  1.0 is used as default value. S<>0.

OUTPUT PARAMETERS
    P   -   polynomial in barycentric form


NOTES:
1.  this function accepts offset and scale, which can be  set  to  improve
    numerical properties of polynomial. For example, if you interpolate on
    [-1,+1],  you  can  set C=0 and S=1 and convert from sum of 1, x, x^2,
    x^3 and so on. In most cases you it is exactly what you need.

    However, if your interpolation model was built on [999,1001], you will
    see significant growth of numerical errors when using {1, x, x^2, x^3}
    as  input  basis.  Converting  from  sum  of  1, (x-1000), (x-1000)^2,
    (x-1000)^3 will be better option (you have to specify 1000.0 as offset
    C and 1.0 as scale S).

2.  power basis is ill-conditioned and tricks described above can't  solve
    this problem completely. This function  will  return barycentric model
    in any case, but for N>8 accuracy well degrade. However, N's less than
    5 are pretty safe.

  -- ALGLIB --
     Copyright 30.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
힘 기반에서 중성 표상으로의 전환.
이 함수는 O (N ^ 2) 복잡도를가집니다.
입력 매개 변수 :
    A-coefficient, P (x) = sum {A [i] * ((XC) / S) ^ i, i = 0..N-1}
    N - 계수의 수 (다항식 차수 + 1)
            * 주어진 경우 A의 선행 N 요소 만 사용됩니다.
            * 주어지지 않은 경우 A의 크기로부터 자동으로 결정됩니다.
    C - 오프셋 (아래 참조). 0.0이 기본값으로 사용됩니다.
    S - 규모 (아래 참조); 1.0이 기본값으로 사용됩니다. S ≠ 0.
출력 매개 변수
    P - 다항식 형태의 다항식
노트:
1.이 기능은 오프셋 및 스케일을 허용하며,이를 개선하도록 설정할 수 있습니다
    다항식의 수치 적 속성. 예를 들어,
    [-1, + 1]로 설정하면 C = 0 및 S = 1을 설정하고 1, x, x ^ 2,
    x ^ 3 등등. 대부분의 경우 그것은 정확히 당신이 필요로하는 것입니다.
    그러나 보간 모델이 [999,1001]에 빌드 된 경우
    {1, x, x ^ 2, x ^ 3}을 사용할 때 수치 오류가 크게 증가하는 것을보십시오.
    입력 기준. 1, (x-1000), (x-1000) ^ 2,
    (x-1000) ^ 3이 더 좋은 옵션이 될 것입니다 (오프셋으로 1000.0을 지정해야합니다.
    C 및 1.0은 눈금 S로 표시).
2. 힘 기초는 아픈 조건이 있고 전술 한 트릭은 풀 수 없다.
    이 문제는 완전히. 이 함수는 barycentric 모델을 반환합니다.
    어떤 경우에도, 그러나 N> 8 정확도는 잘 떨어집니다. 그러나 N은
    5는 꽤 안전합니다.
  - ALGLIB -
     저작권 30.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void polynomialpow2bar(const real_1d_array &a, const ae_int_t n, const double c, const double s, barycentricinterpolant &p);
void polynomialpow2bar(const real_1d_array &a, barycentricinterpolant &p);


/*************************************************************************
Lagrange intepolant: generation of the model on the general grid.
This function has O(N^2) complexity.

INPUT PARAMETERS:
    X   -   abscissas, array[0..N-1]
    Y   -   function values, array[0..N-1]
    N   -   number of points, N>=1

OUTPUT PARAMETERS
    P   -   barycentric model which represents Lagrange interpolant
            (see ratint unit info and BarycentricCalc() description for
            more information).

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Lagrange intepolant : 일반 그리드에서 모델 생성.
이 함수는 O (N ^ 2) 복잡도를가집니다.
입력 매개 변수 :
    X - 가로 좌표, array [0..N-1]
    Y - 함수 값, 배열 [0..N-1]
    N - 포인트 수, N> = 1
출력 매개 변수
    P - 라그랑주 보간을 나타내는 바이 트 센 트릭 모델
            (ratint 단위 정보 및 BarycentricCalc () 설명을 참조하십시오.
            자세한 정보).
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************** ********************** */
void polynomialbuild(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuild(const real_1d_array &x, const real_1d_array &y, barycentricinterpolant &p);


/*************************************************************************
Lagrange intepolant: generation of the model on equidistant grid.
This function has O(N) complexity.

INPUT PARAMETERS:
    A   -   left boundary of [A,B]
    B   -   right boundary of [A,B]
    Y   -   function values at the nodes, array[0..N-1]
    N   -   number of points, N>=1
            for N=1 a constant model is constructed.

OUTPUT PARAMETERS
    P   -   barycentric model which represents Lagrange interpolant
            (see ratint unit info and BarycentricCalc() description for
            more information).

  -- ALGLIB --
     Copyright 03.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Lagrange intepolant : 등거리 그리드에서 모델 생성.
이 함수는 O (N) 복잡도를가집니다.
입력 매개 변수 :
    A - [A, B]의 왼쪽 경계
    B - [A, B]의 오른쪽 경계
    노드에서 Y - 함수 값, array [0..N-1]
    N - 포인트 수, N> = 1
            N = 1 인 경우 상수 모델이 구성됩니다.
출력 매개 변수
    P - 라그랑주 보간을 나타내는 바이 트 센 트릭 모델
            (ratint 단위 정보 및 BarycentricCalc () 설명을 참조하십시오.
            자세한 정보).
  - ALGLIB -
     Copyright 03.12.2009 Bochkanov Sergey
*************************************************** ********************** */
void polynomialbuildeqdist(const double a, const double b, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuildeqdist(const double a, const double b, const real_1d_array &y, barycentricinterpolant &p);


/*************************************************************************
Lagrange intepolant on Chebyshev grid (first kind).
This function has O(N) complexity.

INPUT PARAMETERS:
    A   -   left boundary of [A,B]
    B   -   right boundary of [A,B]
    Y   -   function values at the nodes, array[0..N-1],
            Y[I] = Y(0.5*(B+A) + 0.5*(B-A)*Cos(PI*(2*i+1)/(2*n)))
    N   -   number of points, N>=1
            for N=1 a constant model is constructed.

OUTPUT PARAMETERS
    P   -   barycentric model which represents Lagrange interpolant
            (see ratint unit info and BarycentricCalc() description for
            more information).

  -- ALGLIB --
     Copyright 03.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Chebyshev 격자 (첫 번째 종류)에 Lagrange intepolant.
이 함수는 O (N) 복잡도를가집니다.
입력 매개 변수 :
    A - [A, B]의 왼쪽 경계
    B - [A, B]의 오른쪽 경계
    노드에서 Y - 함수 값, array [0..N-1],
            (PI * (2 * i + 1) / (2 * n)))에 의해 결정된다 .Y [I] = Y (0.5 * (B + A)
    N - 포인트 수, N> = 1
            N = 1 인 경우 상수 모델이 구성됩니다.
출력 매개 변수
    P - 라그랑주 보간을 나타내는 바이 트 센 트릭 모델
            (ratint 단위 정보 및 BarycentricCalc () 설명을 참조하십시오.
            자세한 정보).
  - ALGLIB -
     Copyright 03.12.2009 Bochkanov Sergey
*************************************************** ********************** */
void polynomialbuildcheb1(const double a, const double b, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuildcheb1(const double a, const double b, const real_1d_array &y, barycentricinterpolant &p);


/*************************************************************************
Lagrange intepolant on Chebyshev grid (second kind).
This function has O(N) complexity.

INPUT PARAMETERS:
    A   -   left boundary of [A,B]
    B   -   right boundary of [A,B]
    Y   -   function values at the nodes, array[0..N-1],
            Y[I] = Y(0.5*(B+A) + 0.5*(B-A)*Cos(PI*i/(n-1)))
    N   -   number of points, N>=1
            for N=1 a constant model is constructed.

OUTPUT PARAMETERS
    P   -   barycentric model which represents Lagrange interpolant
            (see ratint unit info and BarycentricCalc() description for
            more information).

  -- ALGLIB --
     Copyright 03.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Chebyshev 그리드 (두 번째 종류)에 Lagrange intepolant.
이 함수는 O (N) 복잡도를가집니다.
입력 매개 변수 :
    A - [A, B]의 왼쪽 경계
    B - [A, B]의 오른쪽 경계
    노드에서 Y - 함수 값, array [0..N-1],
            (PI * i / (n-1))) Y [I] = Y (0.5 * (B + A) + 0.5 * (BA)
    N - 포인트 수, N> = 1
            N = 1 인 경우 상수 모델이 구성됩니다.
출력 매개 변수
    P - 라그랑주 보간을 나타내는 바이 트 센 트릭 모델
            (ratint 단위 정보 및 BarycentricCalc () 설명을 참조하십시오.
            자세한 정보).
  - ALGLIB -
     Copyright 03.12.2009 Bochkanov Sergey
*************************************************** ********************** */
void polynomialbuildcheb2(const double a, const double b, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuildcheb2(const double a, const double b, const real_1d_array &y, barycentricinterpolant &p);


/*************************************************************************
Fast equidistant polynomial interpolation function with O(N) complexity

INPUT PARAMETERS:
    A   -   left boundary of [A,B]
    B   -   right boundary of [A,B]
    F   -   function values, array[0..N-1]
    N   -   number of points on equidistant grid, N>=1
            for N=1 a constant model is constructed.
    T   -   position where P(x) is calculated

RESULT
    value of the Lagrange interpolant at T

IMPORTANT
    this function provides fast interface which is not overflow-safe
    nor it is very precise.
    the best option is to use  PolynomialBuildEqDist()/BarycentricCalc()
    subroutines unless you are pretty sure that your data will not result
    in overflow.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
O (N) 복잡도를 갖는 고속 등거리 다항식 보간 함수
입력 매개 변수 :
    A - [A, B]의 왼쪽 경계
    B - [A, B]의 오른쪽 경계
    F - 함수 값, array [0..N-1]
    N - 등거리 그리드상의 점의 수, N> = 1
            N = 1 인 경우 상수 모델이 구성됩니다.
    T - P (x)를 계산하는 위치
결과
    T에서의 Lagrange 보간 값
중대한
    이 함수는 오버 플로우 방지가 아닌 빠른 인터페이스를 제공합니다.
    매우 정확하지도 않습니다.
    가장 좋은 방법은 PolynomialBuildEqDist () / BarycentricCalc ()를 사용하는 것입니다.
    당신의 데이터가 결과가 나오지 않는다고 확신하지 않는 한 서브 루틴
    오버플로에서.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************** ********************** */
double polynomialcalceqdist(const double a, const double b, const real_1d_array &f, const ae_int_t n, const double t);
double polynomialcalceqdist(const double a, const double b, const real_1d_array &f, const double t);


/*************************************************************************
Fast polynomial interpolation function on Chebyshev points (first kind)
with O(N) complexity.

INPUT PARAMETERS:
    A   -   left boundary of [A,B]
    B   -   right boundary of [A,B]
    F   -   function values, array[0..N-1]
    N   -   number of points on Chebyshev grid (first kind),
            X[i] = 0.5*(B+A) + 0.5*(B-A)*Cos(PI*(2*i+1)/(2*n))
            for N=1 a constant model is constructed.
    T   -   position where P(x) is calculated

RESULT
    value of the Lagrange interpolant at T

IMPORTANT
    this function provides fast interface which is not overflow-safe
    nor it is very precise.
    the best option is to use  PolIntBuildCheb1()/BarycentricCalc()
    subroutines unless you are pretty sure that your data will not result
    in overflow.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Chebyshev 포인트에서의 빠른 다항식 보간 함수 (첫 번째 종류)
O (N) 복잡도.
입력 매개 변수 :
    A - [A, B]의 왼쪽 경계
    B - [A, B]의 오른쪽 경계
    F - 함수 값, array [0..N-1]
    N - Chebyshev 그리드 (첫 번째 종류)의 점수,
            X * [i] = 0.5 * (B + A) + 0.5 * (BA) * Cos (PI * (2 * i + 1) / (2 * n)
            N = 1 인 경우 상수 모델이 구성됩니다.
    T - P (x)를 계산하는 위치
결과
    T에서의 Lagrange 보간 값
중대한
    이 함수는 오버 플로우 방지가 아닌 빠른 인터페이스를 제공합니다.
    매우 정확하지도 않습니다.
    가장 좋은 방법은 PolIntBuildCheb1 () / BarycentricCalc ()를 사용하는 것입니다.
    당신의 데이터가 결과가 나오지 않는다고 확신하지 않는 한 서브 루틴
    오버플로에서.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************** ********************** */
double polynomialcalccheb1(const double a, const double b, const real_1d_array &f, const ae_int_t n, const double t);
double polynomialcalccheb1(const double a, const double b, const real_1d_array &f, const double t);


/*************************************************************************
Fast polynomial interpolation function on Chebyshev points (second kind)
with O(N) complexity.

INPUT PARAMETERS:
    A   -   left boundary of [A,B]
    B   -   right boundary of [A,B]
    F   -   function values, array[0..N-1]
    N   -   number of points on Chebyshev grid (second kind),
            X[i] = 0.5*(B+A) + 0.5*(B-A)*Cos(PI*i/(n-1))
            for N=1 a constant model is constructed.
    T   -   position where P(x) is calculated

RESULT
    value of the Lagrange interpolant at T

IMPORTANT
    this function provides fast interface which is not overflow-safe
    nor it is very precise.
    the best option is to use PolIntBuildCheb2()/BarycentricCalc()
    subroutines unless you are pretty sure that your data will not result
    in overflow.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Chebyshev 포인트에서의 빠른 다항식 보간 기능 (두 번째 종류)
O (N) 복잡도.
입력 매개 변수 :
    A - [A, B]의 왼쪽 경계
    B - [A, B]의 오른쪽 경계
    F - 함수 값, array [0..N-1]
    N - Chebyshev 격자 (두 번째 종류)의 점 수,
            X (i) = 0.5 * (B + A) + 0.5 * (BA) * Cos (PI * i / (n-1))
            N = 1 인 경우 상수 모델이 구성됩니다.
    T - P (x)를 계산하는 위치
결과
    T에서의 Lagrange 보간 값
중대한
    이 함수는 오버 플로우 방지가 아닌 빠른 인터페이스를 제공합니다.
    매우 정확하지도 않습니다.
    가장 좋은 방법은 PolIntBuildCheb2 () / BarycentricCalc ()를 사용하는 것입니다.
    당신의 데이터가 결과가 나오지 않는다고 확신하지 않는 한 서브 루틴
    오버플로에서.
  - ALGLIB -
     저작권 02.12.2009 Bochkanov Sergey
*************************************************** ********************** */
double polynomialcalccheb2(const double a, const double b, const real_1d_array &f, const ae_int_t n, const double t);
double polynomialcalccheb2(const double a, const double b, const real_1d_array &f, const double t);

/*************************************************************************
This subroutine builds linear spline interpolant

INPUT PARAMETERS:
    X   -   spline nodes, array[0..N-1]
    Y   -   function values, array[0..N-1]
    N   -   points count (optional):
            * N>=2
            * if given, only first N points are used to build spline
            * if not given, automatically detected from X/Y sizes
              (len(X) must be equal to len(Y))

OUTPUT PARAMETERS:
    C   -   spline interpolant


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

  -- ALGLIB PROJECT --
     Copyright 24.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 선형 스플라인 보간을 작성합니다.
입력 매개 변수 :
    X - 스플라인 노드, 배열 [0..N-1]
    Y - 함수 값, 배열 [0..N-1]
    N - 포인트 카운트 (옵션) :
            * N> = 2
            * 주어진 경우 첫 번째 N 점만이 스플라인을 작성하는 데 사용됩니다.
            * 지정하지 않으면 X / Y 크기에서 자동 감지
              (len (X)는 len (Y)와 같아야 함)
출력 매개 변수 :
    C - 스플라인 보간
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 24.06.2007
*************************************************** ********************** */
void spline1dbuildlinear(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildlinear(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);


/*************************************************************************
This subroutine builds cubic spline interpolant.

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1].
    Y           -   function values, array[0..N-1].

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points are used to build spline
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)

OUTPUT PARAMETERS:
    C           -   spline interpolant

ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 3 차 스플라인 보간을 만듭니다.
입력 매개 변수 :
    X - 스플라인 노드, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어진 경우 첫 번째 N 점만이 스플라인을 작성하는 데 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundLType - 왼쪽 경계의 경계 조건 유형
    BoundL - 왼쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundLType에 따라 다름)
    BoundRType - 오른쪽 경계의 경계 조건 타입
    BoundR - 오른쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundRType에 따라 다름)
출력 매개 변수 :
    C - 스플라인 보간
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
경계 값 설정 :
BoundLType / BoundRType 매개 변수의 값은 다음과 같습니다.
    * -1은주기적인 (주기적) 경계 조건에 해당합니다.
          이 경우 :
          BoundLType와 BoundRType는 모두 -1과 같아야합니다.
          * BoundL / BoundR은 무시됩니다.
          * Y [last]는 무시됩니다 (Y [first]와 같음).
    * 0은 파라볼 릭 종료 스플라인에 해당합니다.
          BoundL 및 / 또는 BoundR은 무시됩니다.
    * 1, 1 차 미분 경계 조건에 해당
    * 2, 이차 미분 경계 조건에 해당
    * 기본적으로 BoundType = 0이 사용됩니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 23.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline1dbuildcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, spline1dinterpolant &c);
void spline1dbuildcubic(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);


/*************************************************************************
This function solves following problem: given table y[] of function values
at nodes x[], it calculates and returns table of function derivatives  d[]
(calculated at the same nodes x[]).

This function yields same result as Spline1DBuildCubic() call followed  by
sequence of Spline1DDiff() calls, but it can be several times faster  when
called for ordered X[] and X2[].

INPUT PARAMETERS:
    X           -   spline nodes
    Y           -   function values

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points are used
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)

OUTPUT PARAMETERS:
    D           -   derivative values at X[]

ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.
Derivative values are correctly reordered on return, so  D[I]  is  always
equal to S'(X[I]) independently of points order.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 03.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 다음과 같은 문제를 해결합니다 : 주어진 테이블 y [] 함수 값
노드 x []에서 함수 파생 ​​테이블 d []를 계산하여 반환합니다.
(동일한 노드 x []에서 계산 됨).
이 함수는 Spline1DBuildCubic () 호출과 동일한 결과를 산출 한 다음
Spline1DDiff () 호출의 시퀀스를
순서가있는 X []와 X2 []를 호출했습니다.
입력 매개 변수 :
    X - 스플라인 노드
    Y - 함수 값
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어진 경우 첫 번째 N 점만 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundLType - 왼쪽 경계의 경계 조건 유형
    BoundL - 왼쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundLType에 따라 다름)
    BoundRType - 오른쪽 경계의 경계 조건 타입
    BoundR - 오른쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundRType에 따라 다름)
출력 매개 변수 :
    D - X []에서 미분 값
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
미분 값은 반환시 올바르게 재정렬되므로 D [I]는 항상
점 순서와 관계없이 S '(X [I])와 같습니다.
경계 값 설정 :
BoundLType / BoundRType 매개 변수의 값은 다음과 같습니다.
    * -1은주기적인 (주기적) 경계 조건에 해당합니다.
          이 경우 :
          BoundLType와 BoundRType는 모두 -1과 같아야합니다.
          * BoundL / BoundR은 무시됩니다.
          * Y [last]는 무시됩니다 (Y [first]와 같음).
    * 0은 파라볼 릭 종료 스플라인에 해당합니다.
          BoundL 및 / 또는 BoundR은 무시됩니다.
    * 1, 1 차 미분 경계 조건에 해당
    * 2, 이차 미분 경계 조건에 해당
    * 기본적으로 BoundType = 0이 사용됩니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 03.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void spline1dgriddiffcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, real_1d_array &d);
void spline1dgriddiffcubic(const real_1d_array &x, const real_1d_array &y, real_1d_array &d);


/*************************************************************************
This function solves following problem: given table y[] of function values
at  nodes  x[],  it  calculates  and  returns  tables  of first and second
function derivatives d1[] and d2[] (calculated at the same nodes x[]).

This function yields same result as Spline1DBuildCubic() call followed  by
sequence of Spline1DDiff() calls, but it can be several times faster  when
called for ordered X[] and X2[].

INPUT PARAMETERS:
    X           -   spline nodes
    Y           -   function values

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points are used
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)

OUTPUT PARAMETERS:
    D1          -   S' values at X[]
    D2          -   S'' values at X[]

ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.
Derivative values are correctly reordered on return, so  D[I]  is  always
equal to S'(X[I]) independently of points order.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 03.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 다음과 같은 문제를 해결합니다 : 주어진 테이블 y [] 함수 값
노드 x []에서 첫 번째 및 두 번째 테이블을 계산하여 반환합니다.
함수 파생 ​​d1 []과 d2 [] (같은 노드 x []에서 계산).
이 함수는 Spline1DBuildCubic () 호출과 동일한 결과를 산출 한 다음
Spline1DDiff () 호출의 시퀀스를
순서가있는 X []와 X2 []를 호출했습니다.
입력 매개 변수 :
    X - 스플라인 노드
    Y - 함수 값
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어진 경우 첫 번째 N 점만 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundLType - 왼쪽 경계의 경계 조건 유형
    BoundL - 왼쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundLType에 따라 다름)
    BoundRType - 오른쪽 경계의 경계 조건 타입
    BoundR - 오른쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundRType에 따라 다름)
출력 매개 변수 :
    X []에서 D1 - S '값
    X []에서 D2 - S "값
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
미분 값은 반환시 올바르게 재정렬되므로 D [I]는 항상
점 순서와 관계없이 S '(X [I])와 같습니다.
경계 값 설정 :
BoundLType / BoundRType 매개 변수의 값은 다음과 같습니다.
    * -1은주기적인 (주기적) 경계 조건에 해당합니다.
          이 경우 :
          BoundLType와 BoundRType는 모두 -1과 같아야합니다.
          * BoundL / BoundR은 무시됩니다.
          * Y [last]는 무시됩니다 (Y [first]와 같음).
    * 0은 파라볼 릭 종료 스플라인에 해당합니다.
          BoundL 및 / 또는 BoundR은 무시됩니다.
    * 1, 1 차 미분 경계 조건에 해당
    * 2, 이차 미분 경계 조건에 해당
    * 기본적으로 BoundType = 0이 사용됩니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 03.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void spline1dgriddiff2cubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, real_1d_array &d1, real_1d_array &d2);
void spline1dgriddiff2cubic(const real_1d_array &x, const real_1d_array &y, real_1d_array &d1, real_1d_array &d2);


/*************************************************************************
This function solves following problem: given table y[] of function values
at old nodes x[]  and new nodes  x2[],  it calculates and returns table of
function values y2[] (calculated at x2[]).

This function yields same result as Spline1DBuildCubic() call followed  by
sequence of Spline1DDiff() calls, but it can be several times faster  when
called for ordered X[] and X2[].

INPUT PARAMETERS:
    X           -   old spline nodes
    Y           -   function values
    X2           -  new spline nodes

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points from X/Y are used
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)
    N2          -   new points count:
                    * N2>=2
                    * if given, only first N2 points from X2 are used
                    * if not given, automatically detected from X2 size

OUTPUT PARAMETERS:
    F2          -   function values at X2[]

ORDER OF POINTS

Subroutine automatically sorts points, so caller  may pass unsorted array.
Function  values  are correctly reordered on  return, so F2[I]  is  always
equal to S(X2[I]) independently of points order.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 03.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 다음과 같은 문제를 해결합니다 : 주어진 테이블 y [] 함수 값
이전 노드 x []와 새로운 노드 x2 []에서,
함수 값 y2 [] (x2 []에서 계산).
이 함수는 Spline1DBuildCubic () 호출과 동일한 결과를 산출 한 다음
Spline1DDiff () 호출의 시퀀스를
순서가있는 X []와 X2 []를 호출했습니다.
입력 매개 변수 :
    X - 오래된 스플라인 노드
    Y - 함수 값
    X2 - 새로운 스플라인 노드
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어지면 X / Y에서 처음 N 포인트 만 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundLType - 왼쪽 경계의 경계 조건 유형
    BoundL - 왼쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundLType에 따라 다름)
    BoundRType - 오른쪽 경계의 경계 조건 타입
    BoundR - 오른쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundRType에 따라 다름)
    N2 - 새로운 점수 계산 :
                    * N2> = 2
                    * 주어진 경우 X2에서 첫 번째 N2 점만 사용됩니다.
                    * 지정하지 않으면 X2 크기에서 자동으로 감지됩니다.
출력 매개 변수 :
    F2 - X2 [에서 함수 값
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
함수 값은 반환시 올바르게 재정렬되므로 F2 [I]는 항상
점 순서와 관계없이 S (X2 [I])와 같습니다.
경계 값 설정 :
BoundLType / BoundRType 매개 변수의 값은 다음과 같습니다.
    * -1은주기적인 (주기적) 경계 조건에 해당합니다.
          이 경우 :
          BoundLType와 BoundRType는 모두 -1과 같아야합니다.
          * BoundL / BoundR은 무시됩니다.
          * Y [last]는 무시됩니다 (Y [first]와 같음).
    * 0은 파라볼 릭 종료 스플라인에 해당합니다.
          BoundL 및 / 또는 BoundR은 무시됩니다.
    * 1, 1 차 미분 경계 조건에 해당
    * 2, 이차 미분 경계 조건에 해당
    * 기본적으로 BoundType = 0이 사용됩니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 03.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void spline1dconvcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y2);
void spline1dconvcubic(const real_1d_array &x, const real_1d_array &y, const real_1d_array &x2, real_1d_array &y2);


/*************************************************************************
This function solves following problem: given table y[] of function values
at old nodes x[]  and new nodes  x2[],  it calculates and returns table of
function values y2[] and derivatives d2[] (calculated at x2[]).

This function yields same result as Spline1DBuildCubic() call followed  by
sequence of Spline1DDiff() calls, but it can be several times faster  when
called for ordered X[] and X2[].

INPUT PARAMETERS:
    X           -   old spline nodes
    Y           -   function values
    X2           -  new spline nodes

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points from X/Y are used
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)
    N2          -   new points count:
                    * N2>=2
                    * if given, only first N2 points from X2 are used
                    * if not given, automatically detected from X2 size

OUTPUT PARAMETERS:
    F2          -   function values at X2[]
    D2          -   first derivatives at X2[]

ORDER OF POINTS

Subroutine automatically sorts points, so caller  may pass unsorted array.
Function  values  are correctly reordered on  return, so F2[I]  is  always
equal to S(X2[I]) independently of points order.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 03.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 다음과 같은 문제를 해결합니다 : 주어진 테이블 y [] 함수 값
이전 노드 x []와 새로운 노드 x2 []에서,
함수 값 y2 []와 미분 d2 [] (x2 []에서 계산)입니다.
이 함수는 Spline1DBuildCubic () 호출과 동일한 결과를 산출 한 다음
Spline1DDiff () 호출의 시퀀스를
순서가있는 X []와 X2 []를 호출했습니다.
입력 매개 변수 :
    X - 오래된 스플라인 노드
    Y - 함수 값
    X2 - 새로운 스플라인 노드
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어지면 X / Y에서 처음 N 포인트 만 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundLType - 왼쪽 경계의 경계 조건 유형
    BoundL - 왼쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundLType에 따라 다름)
    BoundRType - 오른쪽 경계의 경계 조건 타입
    BoundR - 오른쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundRType에 따라 다름)
    N2 - 새로운 점수 계산 :
                    * N2> = 2
                    * 주어진 경우 X2에서 첫 번째 N2 점만 사용됩니다.
                    * 지정하지 않으면 X2 크기에서 자동으로 감지됩니다.
출력 매개 변수 :
    F2 - X2 [에서 함수 값
    D2 - X2에서의 1 차 미분 []
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
함수 값은 반환시 올바르게 재정렬되므로 F2 [I]는 항상
점 순서와 관계없이 S (X2 [I])와 같습니다.
경계 값 설정 :
BoundLType / BoundRType 매개 변수의 값은 다음과 같습니다.
    * -1은주기적인 (주기적) 경계 조건에 해당합니다.
          이 경우 :
          BoundLType와 BoundRType는 모두 -1과 같아야합니다.
          * BoundL / BoundR은 무시됩니다.
          * Y [last]는 무시됩니다 (Y [first]와 같음).
    * 0은 파라볼 릭 종료 스플라인에 해당합니다.
          BoundL 및 / 또는 BoundR은 무시됩니다.
    * 1, 1 차 미분 경계 조건에 해당
    * 2, 이차 미분 경계 조건에 해당
    * 기본적으로 BoundType = 0이 사용됩니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 03.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void spline1dconvdiffcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y2, real_1d_array &d2);
void spline1dconvdiffcubic(const real_1d_array &x, const real_1d_array &y, const real_1d_array &x2, real_1d_array &y2, real_1d_array &d2);


/*************************************************************************
This function solves following problem: given table y[] of function values
at old nodes x[]  and new nodes  x2[],  it calculates and returns table of
function  values  y2[],  first  and  second  derivatives  d2[]  and  dd2[]
(calculated at x2[]).

This function yields same result as Spline1DBuildCubic() call followed  by
sequence of Spline1DDiff() calls, but it can be several times faster  when
called for ordered X[] and X2[].

INPUT PARAMETERS:
    X           -   old spline nodes
    Y           -   function values
    X2           -  new spline nodes

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points from X/Y are used
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)
    N2          -   new points count:
                    * N2>=2
                    * if given, only first N2 points from X2 are used
                    * if not given, automatically detected from X2 size

OUTPUT PARAMETERS:
    F2          -   function values at X2[]
    D2          -   first derivatives at X2[]
    DD2         -   second derivatives at X2[]

ORDER OF POINTS

Subroutine automatically sorts points, so caller  may pass unsorted array.
Function  values  are correctly reordered on  return, so F2[I]  is  always
equal to S(X2[I]) independently of points order.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 03.09.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 다음과 같은 문제를 해결합니다 : 주어진 테이블 y [] 함수 값
이전 노드 x []와 새로운 노드 x2 []에서,
함수 값 y2 [], 제 1 및 제 2 미분 d2 [] 및 dd2 []
(x2 []에서 계산).
이 함수는 Spline1DBuildCubic () 호출과 동일한 결과를 산출 한 다음
Spline1DDiff () 호출의 시퀀스를
순서가있는 X []와 X2 []를 호출했습니다.
입력 매개 변수 :
    X - 오래된 스플라인 노드
    Y - 함수 값
    X2 - 새로운 스플라인 노드
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어지면 X / Y에서 처음 N 포인트 만 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundLType - 왼쪽 경계의 경계 조건 유형
    BoundL - 왼쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundLType에 따라 다름)
    BoundRType - 오른쪽 경계의 경계 조건 타입
    BoundR - 오른쪽 경계 조건 (1 차 또는 2 차 미분,
                    BoundRType에 따라 다름)
    N2 - 새로운 점수 계산 :
                    * N2> = 2
                    * 주어진 경우 X2에서 첫 번째 N2 점만 사용됩니다.
                    * 지정하지 않으면 X2 크기에서 자동으로 감지됩니다.
출력 매개 변수 :
    F2 - X2 [에서 함수 값
    D2 - X2에서의 1 차 미분 []
    DD2 - X2에서의 2 차 미분 []
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
함수 값은 반환시 올바르게 재정렬되므로 F2 [I]는 항상
점 순서와 관계없이 S (X2 [I])와 같습니다.
경계 값 설정 :
BoundLType / BoundRType 매개 변수의 값은 다음과 같습니다.
    * -1은주기적인 (주기적) 경계 조건에 해당합니다.
          이 경우 :
          BoundLType와 BoundRType는 모두 -1과 같아야합니다.
          * BoundL / BoundR은 무시됩니다.
          * Y [last]는 무시됩니다 (Y [first]와 같음).
    * 0은 파라볼 릭 종료 스플라인에 해당합니다.
          BoundL 및 / 또는 BoundR은 무시됩니다.
    * 1, 1 차 미분 경계 조건에 해당
    * 2, 이차 미분 경계 조건에 해당
    * 기본적으로 BoundType = 0이 사용됩니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 03.09.2010 Bochkanov Sergey
*************************************************** ********************** */
void spline1dconvdiff2cubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y2, real_1d_array &d2, real_1d_array &dd2);
void spline1dconvdiff2cubic(const real_1d_array &x, const real_1d_array &y, const real_1d_array &x2, real_1d_array &y2, real_1d_array &d2, real_1d_array &dd2);


/*************************************************************************
This subroutine builds Catmull-Rom spline interpolant.

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1].
    Y           -   function values, array[0..N-1].

OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points are used to build spline
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundType   -   boundary condition type:
                    * -1 for periodic boundary condition
                    *  0 for parabolically terminated spline (default)
    Tension     -   tension parameter:
                    * tension=0   corresponds to classic Catmull-Rom spline (default)
                    * 0<tension<1 corresponds to more general form - cardinal spline

OUTPUT PARAMETERS:
    C           -   spline interpolant


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 Catmull-Rom 스플라인 보간을 만듭니다.
입력 매개 변수 :
    X - 스플라인 노드, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
선택 가능한 매개 변수 :
    N - 점 수 :
                    * N> = 2
                    * 주어진 경우 첫 번째 N 점만이 스플라인을 작성하는 데 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
    BoundType - 경계 조건 유형 :
                    주기 경계 조건의 경우 -1
                    * 0 파라볼 릭 종료 스플라인 (기본값)
    장력 - 장력 매개 변수 :
                    * tension = 0은 기존 Catmull-Rom 스플라인에 해당 (기본값)
                    * 0 <장력 <1은보다 일반적인 형태에 해당 - 기본 스플라인
출력 매개 변수 :
    C - 스플라인 보간
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
정기적 인 경계 조건과 관련된 문제 :
주기적인 경계 조건의 문제는 Y [first_point] = Y [last_point]입니다.
그러나이 서브 루틴에서는 다음과 같은 값을 지정할 필요가 없습니다.
첫번째와 마지막 점 - 자동으로 그것들을 동일하게 만든다.
Y [first_point] (가장 왼쪽, 최소 X []에 해당)를
Y [last_point]. 그러나 Y []의 일관된 값을 전달하는 것이 좋습니다.
즉 Y [first_point] = Y [last_point]를 만들 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 23.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline1dbuildcatmullrom(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundtype, const double tension, spline1dinterpolant &c);
void spline1dbuildcatmullrom(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);


/*************************************************************************
This subroutine builds Hermite spline interpolant.

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1]
    Y           -   function values, array[0..N-1]
    D           -   derivatives, array[0..N-1]
    N           -   points count (optional):
                    * N>=2
                    * if given, only first N points are used to build spline
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))

OUTPUT PARAMETERS:
    C           -   spline interpolant.


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 Hermite 스플라인 보간을 만듭니다.
입력 매개 변수 :
    X - 스플라인 노드, 배열 [0..N-1]
    Y - 함수 값, 배열 [0..N-1]
    D- 유도체, 배열 [0..N-1]
    N - 포인트 카운트 (옵션) :
                    * N> = 2
                    * 주어진 경우 첫 번째 N 점만이 스플라인을 작성하는 데 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
출력 매개 변수 :
    C - 스플라인 보간.
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
  - ALGLIB 프로젝트 -
     저작권 23.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline1dbuildhermite(const real_1d_array &x, const real_1d_array &y, const real_1d_array &d, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildhermite(const real_1d_array &x, const real_1d_array &y, const real_1d_array &d, spline1dinterpolant &c);


/*************************************************************************
This subroutine builds Akima spline interpolant

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1]
    Y           -   function values, array[0..N-1]
    N           -   points count (optional):
                    * N>=2
                    * if given, only first N points are used to build spline
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))

OUTPUT PARAMETERS:
    C           -   spline interpolant


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

  -- ALGLIB PROJECT --
     Copyright 24.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 Akima 스플라인 보간을 만듭니다.
입력 매개 변수 :
    X - 스플라인 노드, 배열 [0..N-1]
    Y - 함수 값, 배열 [0..N-1]
    N - 포인트 카운트 (옵션) :
                    * N> = 2
                    * 주어진 경우 첫 번째 N 점만이 스플라인을 작성하는 데 사용됩니다.
                    * 지정하지 않으면 X / Y 크기에서 자동 감지
                      (len (X)는 len (Y)와 같아야 함)
출력 매개 변수 :
    C - 스플라인 보간
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 24.06.2007
*************************************************** ********************** */
void spline1dbuildakima(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildakima(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);


/*************************************************************************
This subroutine calculates the value of the spline at the given point X.

INPUT PARAMETERS:
    C   -   spline interpolant
    X   -   point

Result:
    S(x)

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 주어진 점 X에서 스플라인 값을 계산합니다.
입력 매개 변수 :
    C - 스플라인 보간
    X- 포인트
결과:
    S (x)
  - ALGLIB 프로젝트 -
     저작권 23.06.2007 Bochkanov Sergey
*************************************************** ********************** */
double spline1dcalc(const spline1dinterpolant &c, const double x);


/*************************************************************************
This subroutine differentiates the spline.

INPUT PARAMETERS:
    C   -   spline interpolant.
    X   -   point

Result:
    S   -   S(x)
    DS  -   S'(x)
    D2S -   S''(x)

  -- ALGLIB PROJECT --
     Copyright 24.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인을 구분합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    X- 포인트
결과:
    S - S (x)
    DS - S '(x)
    D2S - S "(x)
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 24.06.2007
*************************************************** ********************** */
void spline1ddiff(const spline1dinterpolant &c, const double x, double &s, double &ds, double &d2s);


/*************************************************************************
This subroutine unpacks the spline into the coefficients table.

INPUT PARAMETERS:
    C   -   spline interpolant.
    X   -   point

OUTPUT PARAMETERS:
    Tbl -   coefficients table, unpacked format, array[0..N-2, 0..5].
            For I = 0...N-2:
                Tbl[I,0] = X[i]
                Tbl[I,1] = X[i+1]
                Tbl[I,2] = C0
                Tbl[I,3] = C1
                Tbl[I,4] = C2
                Tbl[I,5] = C3
            On [x[i], x[i+1]] spline is equals to:
                S(x) = C0 + C1*t + C2*t^2 + C3*t^3
                t = x-x[i]

NOTE:
    You  can rebuild spline with  Spline1DBuildHermite()  function,  which
    accepts as inputs function values and derivatives at nodes, which  are
    easy to calculate when you have coefficients.

  -- ALGLIB PROJECT --
     Copyright 29.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인을 계수 테이블에 압축 해제합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    X- 포인트
출력 매개 변수 :
    Tbl - 계수 테이블, 언 패킹 된 포맷, 배열 [0..N-2, 0..5].
            I = 0 ... N-2 :
                Tbl [I, 0] = X [i]
                Tbl [1, 1] = X [i + 1]
                Tbl [1, 2] = C0
                Tbl [1, 3] = C1
                Tbl [1, 4] = C2
                Tbl [1, 5] = C3
            [x [i], x [i + 1]] 스플라인은 다음과 같습니다.
                S (x) = C0 + C1 * t + C2 * t ^ 2 + C3 * t ^ 3
                t = xx [i]
노트:
    Spline1DBuildHermite () 함수를 사용하여 스플라인을 다시 작성할 수 있습니다.
    노드로 함수 값과 미분을 입력으로 받아들입니다.
    계수가있을 때 쉽게 계산할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 29.06.2007
*************************************************** ********************** */
void spline1dunpack(const spline1dinterpolant &c, ae_int_t &n, real_2d_array &tbl);


/*************************************************************************
This subroutine performs linear transformation of the spline argument.

INPUT PARAMETERS:
    C   -   spline interpolant.
    A, B-   transformation coefficients: x = A*t + B
Result:
    C   -   transformed spline

  -- ALGLIB PROJECT --
     Copyright 30.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인 인수의 선형 변환을 수행합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    A, B- 변환 계수 : x = A * t + B
결과:
    C - 변형 된 스플라인
  - ALGLIB 프로젝트 -
     저작권 30.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline1dlintransx(const spline1dinterpolant &c, const double a, const double b);


/*************************************************************************
This subroutine performs linear transformation of the spline.

INPUT PARAMETERS:
    C   -   spline interpolant.
    A, B-   transformation coefficients: S2(x) = A*S(x) + B
Result:
    C   -   transformed spline

  -- ALGLIB PROJECT --
     Copyright 30.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인의 선형 변환을 수행합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    A, B- 변환 계수 : S2 (x) = A * S (x) + B
결과:
    C - 변형 된 스플라인
  - ALGLIB 프로젝트 -
     저작권 30.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline1dlintransy(const spline1dinterpolant &c, const double a, const double b);


/*************************************************************************
This subroutine integrates the spline.

INPUT PARAMETERS:
    C   -   spline interpolant.
    X   -   right bound of the integration interval [a, x],
            here 'a' denotes min(x[])
Result:
    integral(S(t)dt,a,x)

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인을 통합합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    X - 적분 구간 [a, x]의 오른쪽 경계
            여기서 'a'는 min (x [])을 나타냅니다.
결과:
    적분 (S (t) dt, a, x)
  - ALGLIB 프로젝트 -
     저작권 23.06.2007 Bochkanov Sergey
*************************************************** ********************** */
double spline1dintegrate(const spline1dinterpolant &c, const double x);


/*************************************************************************
This function builds monotone cubic Hermite interpolant. This interpolant
is monotonic in [x(0),x(n-1)] and is constant outside of this interval.

In  case  y[]  form  non-monotonic  sequence,  interpolant  is  piecewise
monotonic.  Say, for x=(0,1,2,3,4)  and  y=(0,1,2,1,0)  interpolant  will
monotonically grow at [0..2] and monotonically decrease at [2..4].

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1]. Subroutine automatically
                    sorts points, so caller may pass unsorted array.
    Y           -   function values, array[0..N-1]
    N           -   the number of points(N>=2).

OUTPUT PARAMETERS:
    C           -   spline interpolant.

 -- ALGLIB PROJECT --
     Copyright 21.06.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 단조 3 차원 Hermite 보간을 만듭니다. 이 보간법
[x (0), x (n-1)]에서 단조롭고이 구간의 바깥 쪽에서 일정하다.
y []가 비 단조 식 시퀀스를 구성하는 경우, 보간은
단조로운. x = (0,1,2,3,4) 및 y = (0,1,2,1,0) 보간 기가
단조롭게 [0..2]에서 성장하고 [2..4]에서 단조 감소한다.
입력 매개 변수 :
    X - 스플라인 노드, 배열 [0..N-1]. 자동으로 서브 루틴
                    점을 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
    Y - 함수 값, 배열 [0..N-1]
    N - 점의 수 (N> = 2)
출력 매개 변수 :
    C - 스플라인 보간.
 - ALGLIB 프로젝트 -
     저작권 21.06.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline1dbuildmonotone(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildmonotone(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);

/*************************************************************************
Fitting by polynomials in barycentric form. This function provides  simple
unterface for unconstrained unweighted fitting. See  PolynomialFitWC()  if
you need constrained fitting.

Task is linear, so linear least squares solver is used. Complexity of this
computational scheme is O(N*M^2), mostly dominated by least squares solver

SEE ALSO:
    PolynomialFitWC()

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    N   -   number of points, N>0
            * if given, only leading N elements of X/Y are used
            * if not given, automatically determined from sizes of X/Y
    M   -   number of basis functions (= polynomial_degree + 1), M>=1

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearW() subroutine:
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
    P   -   interpolant in barycentric form.
    Rep -   report, same format as in LSFitLinearW() subroutine.
            Following fields are set:
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

NOTES:
    you can convert P from barycentric form  to  the  power  or  Chebyshev
    basis with PolynomialBar2Pow() or PolynomialBar2Cheb() functions  from
    POLINT subpackage.

  -- ALGLIB PROJECT --
     Copyright 10.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
바이올린 중심의 다항식으로 피팅. 이 함수는 간단한
무제한 unweighted fitting을위한 unterface. PolynomialFitWC ()를 참조하십시오.
당신은 제한된 피팅이 필요합니다.
작업은 선형이므로 선형 최소 자 솔버가 사용됩니다. 이 복잡성
계산 방식은 O (N * M ^ 2)이며, 대부분 최소 자승법이 지배합니다
관련 항목 :
    PolynomialFitWC ()
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    N - 포인트 수, N> 0
            * 주어진 경우 X / Y의 선행 N 요소 만 사용됩니다.
            * 지정하지 않으면 X / Y의 크기에서 자동으로 결정됩니다.
    M - 기저 함수의 수 (= polynomial_degree + 1), M> = 1
출력 매개 변수 :
    LSFitLinearW () 서브 루틴에서와 같은 정보 포맷 :
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
    P - 중성자 형태의 보간법.
    Rep -보고, LSFitLinearW () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
노트:
    P를 중성 양식에서 힘 또는 체비 셰프로 변환 할 수 있습니다.
    PolynomialBar2Pow () 또는 PolynomialBar2Cheb () 함수의 기준은
    POLINT 하위 패키지.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 10.12.2009
*************************************************** ********************** */
void polynomialfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);
void polynomialfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);


/*************************************************************************
Weighted  fitting by polynomials in barycentric form, with constraints  on
function values or first derivatives.

Small regularizing term is used when solving constrained tasks (to improve
stability).

Task is linear, so linear least squares solver is used. Complexity of this
computational scheme is O(N*M^2), mostly dominated by least squares solver

SEE ALSO:
    PolynomialFit()

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    W   -   weights, array[0..N-1]
            Each summand in square  sum  of  approximation deviations from
            given  values  is  multiplied  by  the square of corresponding
            weight. Fill it by 1's if you don't  want  to  solve  weighted
            task.
    N   -   number of points, N>0.
            * if given, only leading N elements of X/Y/W are used
            * if not given, automatically determined from sizes of X/Y/W
    XC  -   points where polynomial values/derivatives are constrained,
            array[0..K-1].
    YC  -   values of constraints, array[0..K-1]
    DC  -   array[0..K-1], types of constraints:
            * DC[i]=0   means that P(XC[i])=YC[i]
            * DC[i]=1   means that P'(XC[i])=YC[i]
            SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
    K   -   number of constraints, 0<=K<M.
            K=0 means no constraints (XC/YC/DC are not used in such cases)
    M   -   number of basis functions (= polynomial_degree + 1), M>=1

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearW() subroutine:
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
                        -3 means inconsistent constraints
    P   -   interpolant in barycentric form.
    Rep -   report, same format as in LSFitLinearW() subroutine.
            Following fields are set:
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroitine doesn't calculate task's condition number for K<>0.

NOTES:
    you can convert P from barycentric form  to  the  power  or  Chebyshev
    basis with PolynomialBar2Pow() or PolynomialBar2Cheb() functions  from
    POLINT subpackage.

SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:

Setting constraints can lead  to undesired  results,  like ill-conditioned
behavior, or inconsistency being detected. From the other side,  it allows
us to improve quality of the fit. Here we summarize  our  experience  with
constrained regression splines:
* even simple constraints can be inconsistent, see  Wikipedia  article  on
  this subject: http://en.wikipedia.org/wiki/Birkhoff_interpolation
* the  greater  is  M (given  fixed  constraints),  the  more chances that
  constraints will be consistent
* in the general case, consistency of constraints is NOT GUARANTEED.
* in the one special cases, however, we can  guarantee  consistency.  This
  case  is:  M>1  and constraints on the function values (NOT DERIVATIVES)

Our final recommendation is to use constraints  WHEN  AND  ONLY  when  you
can't solve your task without them. Anything beyond  special  cases  given
above is not guaranteed and may result in inconsistency.

  -- ALGLIB PROJECT --
     Copyright 10.12.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
바이어 센 트릭 형태의 다항식에 의한 가중치 적용
함수 값 또는 1 차 미분.
작은 정규화 용어는 제한된 작업을 해결할 때 사용됩니다 (
안정).
작업은 선형이므로 선형 최소 자 솔버가 사용됩니다. 이 복잡성
계산 방식은 O (N * M ^ 2)이며, 대부분 최소 자승법이 지배합니다
관련 항목 :
    PolynomialFit ()
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    W - 가중치, 배열 [0..N-1]
            근사 편차의 제곱합에있는 각 summand
            주어진 값에 해당하는 제곱을 곱합니다.
            무게. 가중치를 풀고 싶지 않은 경우 1로 채우기
            태스크.
    N - 포인트 수, N> 0.
            * 주어진 경우 X / Y / W의 선행 N 요소 만 사용됩니다.
            * 지정하지 않으면 X / Y / W 크기에서 자동으로 결정됩니다.
    XC - 다항식 값 / 미분 값이 제한되는 지점,
            배열 [0..K-1].
    YC - 제약 조건 값, array [0..K-1]
    DC - 배열 [0..K-1], 제약 유형 :
            * DC [i] = 0은 P (XC [i]) = YC [i]
            * DC [i] = 1은 P '(XC [i]) = YC [i]
            제약 조건에 대한 중요한 정보는 아래를보십시오.
    K - 제약 수, 0 <= K <M.
            K = 0은 제약이 없음을 의미합니다 (XC / YC / DC는 이러한 경우 사용되지 않음)
    M - 기저 함수의 수 (= polynomial_degree + 1), M> = 1
출력 매개 변수 :
    LSFitLinearW () 서브 루틴에서와 같은 정보 포맷 :
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
                        -3은 일관성없는 제약 조건을 의미합니다.
    P - 중성자 형태의 보간법.
    Rep -보고, LSFitLinearW () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업의 조건 번호를 계산하지 않습니다.
노트:
    P를 중성 양식에서 힘 또는 체비 셰프로 변환 할 수 있습니다.
    PolynomialBar2Pow () 또는 PolynomialBar2Cheb () 함수의 기준은
    POLINT 하위 패키지.
제약 조건 설정 - 위험 및 기회 :
제약 조건 설정은 부적절한 결과처럼 바람직하지 않은 결과를 초래할 수 있습니다.
행동 또는 불일치가 감지됩니다. 다른면에서 보면
우리는 착용감을 향상시킬 수 있습니다. 여기에 우리는
구속 회귀 스플라인 :
* 단순한 제약조차도 일치하지 않을 수 있습니다. Wikipedia article on
  이 주제 : http://en.wikipedia.org/wiki/Birkhoff_interpolation
* M이 클수록 (고정 된 제약 조건이 주어짐), 더 많은 기회가 주어진다.
  제약 조건은 일관성이있다.
* 일반적으로 제약 조건의 일관성은 보장되지 않습니다.
* 한 가지 특수한 경우에는 일관성을 보장 할 수 있습니다. 이
  예 : M> 1이고 함수 값에 대한 제약 (NOT DERIVATIVES)
우리의 최종 권고는 제약 조건을 언제 어디서나 사용하는 것입니다.
그것들 없이는 당신의 과제를 해결할 수 없습니다. 주어진 특별한 경우를 넘어선 것
상기 보증은 보장되지 않으며 불일치가 발생할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 10.12.2009
*************************************************** ********************** */
void polynomialfitwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);
void polynomialfitwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);


/*************************************************************************
Weghted rational least  squares  fitting  using  Floater-Hormann  rational
functions  with  optimal  D  chosen  from  [0,9],  with  constraints   and
individual weights.

Equidistant  grid  with M node on [min(x),max(x)]  is  used to build basis
functions. Different values of D are tried, optimal D (least WEIGHTED root
mean square error) is chosen.  Task  is  linear,  so  linear least squares
solver  is  used.  Complexity  of  this  computational  scheme is O(N*M^2)
(mostly dominated by the least squares solver).

SEE ALSO
* BarycentricFitFloaterHormann(), "lightweight" fitting without invididual
  weights and constraints.

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    W   -   weights, array[0..N-1]
            Each summand in square  sum  of  approximation deviations from
            given  values  is  multiplied  by  the square of corresponding
            weight. Fill it by 1's if you don't  want  to  solve  weighted
            task.
    N   -   number of points, N>0.
    XC  -   points where function values/derivatives are constrained,
            array[0..K-1].
    YC  -   values of constraints, array[0..K-1]
    DC  -   array[0..K-1], types of constraints:
            * DC[i]=0   means that S(XC[i])=YC[i]
            * DC[i]=1   means that S'(XC[i])=YC[i]
            SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
    K   -   number of constraints, 0<=K<M.
            K=0 means no constraints (XC/YC/DC are not used in such cases)
    M   -   number of basis functions ( = number_of_nodes), M>=2.

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearWC() subroutine.
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
                        -3 means inconsistent constraints
                        -1 means another errors in parameters passed
                           (N<=0, for example)
    B   -   barycentric interpolant.
    Rep -   report, same format as in LSFitLinearWC() subroutine.
            Following fields are set:
            * DBest         best value of the D parameter
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroutine doesn't calculate task's condition number for K<>0.

SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:

Setting constraints can lead  to undesired  results,  like ill-conditioned
behavior, or inconsistency being detected. From the other side,  it allows
us to improve quality of the fit. Here we summarize  our  experience  with
constrained barycentric interpolants:
* excessive  constraints  can  be  inconsistent.   Floater-Hormann   basis
  functions aren't as flexible as splines (although they are very smooth).
* the more evenly constraints are spread across [min(x),max(x)],  the more
  chances that they will be consistent
* the  greater  is  M (given  fixed  constraints),  the  more chances that
  constraints will be consistent
* in the general case, consistency of constraints IS NOT GUARANTEED.
* in the several special cases, however, we CAN guarantee consistency.
* one of this cases is constraints on the function  VALUES at the interval
  boundaries. Note that consustency of the  constraints  on  the  function
  DERIVATIVES is NOT guaranteed (you can use in such cases  cubic  splines
  which are more flexible).
* another  special  case  is ONE constraint on the function value (OR, but
  not AND, derivative) anywhere in the interval

Our final recommendation is to use constraints  WHEN  AND  ONLY  WHEN  you
can't solve your task without them. Anything beyond  special  cases  given
above is not guaranteed and may result in inconsistency.

  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Floater-Hormann 합리적인 방법을 사용하여 합리적인 최소 제곱합 피팅
제약 조건과 함께 [0,9]에서 선택된 최적 D를 갖는 함수
개인적인 무게.
[min (x), max (x)]에 M 노드가있는 등전위 그리드는 기초를 만드는 데 사용됩니다
기능. D의 다른 값들이 시도되고, 최적의 D (가장 적게 가중 된 루트
평균 제곱 오차)가 선택된다. 작업은 선형이므로 선형 최소 자승
솔버가 사용됩니다. 이 계산 방식의 복잡도는 O (N * M ^ 2)
(대부분 최소 자승법에 의해 지배 됨).
관련 항목
* BarycentricFitFloaterHormann (), "경량"피팅없이 무조건 피팅
  가중치 및 제약 조건.
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    W - 가중치, 배열 [0..N-1]
            근사 편차의 제곱합에있는 각 summand
            주어진 값에 해당하는 제곱을 곱합니다.
            무게. 가중치를 풀고 싶지 않은 경우 1로 채우기
            태스크.
    N - 포인트 수, N> 0.
    XC - 함수 값 / 파생물이 제한되는 지점,
            배열 [0..K-1].
    YC - 제약 조건 값, array [0..K-1]
    DC - 배열 [0..K-1], 제약 유형 :
            * DC [i] = 0은 S (XC [i]) = YC [i]
            * DC [i] = 1은 S '(XC [i]) = YC [i]
            제약 조건에 대한 중요한 정보는 아래를보십시오.
    K - 제약 수, 0 <= K <M.
            K = 0은 제약이 없음을 의미합니다 (XC / YC / DC는 이러한 경우 사용되지 않음)
    M - 기본 함수의 수 (= number_of_nodes), M> = 2.
출력 매개 변수 :
    LSFitLinearWC () 서브 루틴과 같은 정보입니다.
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
                        -3은 일관성없는 제약 조건을 의미합니다.
                        -1은 전달 된 매개 변수의 다른 오류를 의미합니다.
                           (예 : N <= 0)
    B - barycentric interpolant.
    Rep -보고, LSFitLinearWC () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            D 매개 변수의 DBest 최적 값
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업 조건 번호를 계산하지 않습니다.
제약 조건 설정 - 위험 및 기회 :
제약 조건 설정은 부적절한 결과처럼 바람직하지 않은 결과를 초래할 수 있습니다.
행동 또는 불일치가 감지됩니다. 다른면에서 보면
우리는 착용감을 향상시킬 수 있습니다. 여기에 우리는
구속 된 barycentric interpolants :
* 과도한 제약 조건이 일치하지 않을 수 있습니다. 플로터 - 호르만 기초
  함수는 스플라인만큼 유연하지 않습니다 (매우 부드럽지만).
* 더 균등하게 제약 조건이 [min (x), max (x)]에 퍼지면 더 많은
  그들이 일관성있게 일할 수있는 기회
* M이 클수록 (고정 된 제약 조건이 주어짐), 더 많은 기회가 주어진다.
  제약 조건은 일관성이있다.
* 일반적으로 제약 조건의 일관성은 보장되지 않습니다.
* 몇 가지 특수한 경우에는 일관성을 보장 할 수 있습니다.
*이 경우 중 하나는 해당 간격의 함수 VALUES에 대한 제약입니다.
  경계. 함수에 대한 제약 조건의 절박함
  유도체는 보장되지 않습니다 (이러한 경우에는 3 차 스플라인을 사용할 수 있습니다
  더 유연합니다).
* 또 다른 특별한 경우는 함수 값에 대한 하나의 제약입니다 (OR, 그러나
  AND, 파생물이 아님)
우리의 최종 권고는 언제 어디서나 제약 조건을 사용하는 것입니다.
그것들 없이는 당신의 과제를 해결할 수 없습니다. 주어진 특별한 경우를 넘어선 것
상기 보증은 보장되지 않으며 불일치가 발생할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void barycentricfitfloaterhormannwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, barycentricinterpolant &b, barycentricfitreport &rep);


/*************************************************************************
Rational least squares fitting using  Floater-Hormann  rational  functions
with optimal D chosen from [0,9].

Equidistant  grid  with M node on [min(x),max(x)]  is  used to build basis
functions. Different values of D are tried, optimal  D  (least  root  mean
square error) is chosen.  Task  is  linear, so linear least squares solver
is used. Complexity  of  this  computational  scheme is  O(N*M^2)  (mostly
dominated by the least squares solver).

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    N   -   number of points, N>0.
    M   -   number of basis functions ( = number_of_nodes), M>=2.

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearWC() subroutine.
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
                        -3 means inconsistent constraints
    B   -   barycentric interpolant.
    Rep -   report, same format as in LSFitLinearWC() subroutine.
            Following fields are set:
            * DBest         best value of the D parameter
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Floater-Hormann 합리적인 함수를 사용하는 합리적인 최소 제곱 피팅
최적의 D는 [0,9]에서 선택된다.
[min (x), max (x)]에 M 노드가있는 등전위 그리드는 기초를 만드는 데 사용됩니다
기능. 다른 값의 D가 시도되고, 최적 D (최소 평균값
제곱 오차)가 선택된다. 작업은 선형이므로 선형 최소 자 솔버
사용. 이 계산 방식의 복잡도는 O (N * M ^ 2) (주로
최소 자승법에 의해 지배 됨).
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    N - 포인트 수, N> 0.
    M - 기본 함수의 수 (= number_of_nodes), M> = 2.
출력 매개 변수 :
    LSFitLinearWC () 서브 루틴과 같은 정보입니다.
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
                        -3은 일관성없는 제약 조건을 의미합니다.
    B - barycentric interpolant.
    Rep -보고, LSFitLinearWC () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            D 매개 변수의 DBest 최적 값
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void barycentricfitfloaterhormann(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, barycentricinterpolant &b, barycentricfitreport &rep);


/*************************************************************************
Rational least squares fitting using  Floater-Hormann  rational  functions
with optimal D chosen from [0,9].

Equidistant  grid  with M node on [min(x),max(x)]  is  used to build basis
functions. Different values of D are tried, optimal  D  (least  root  mean
square error) is chosen.  Task  is  linear, so linear least squares solver
is used. Complexity  of  this  computational  scheme is  O(N*M^2)  (mostly
dominated by the least squares solver).

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    N   -   number of points, N>0.
    M   -   number of basis functions ( = number_of_nodes), M>=2.

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearWC() subroutine.
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
                        -3 means inconsistent constraints
    B   -   barycentric interpolant.
    Rep -   report, same format as in LSFitLinearWC() subroutine.
            Following fields are set:
            * DBest         best value of the D parameter
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Floater-Hormann 합리적인 함수를 사용하는 합리적인 최소 제곱 피팅
최적의 D는 [0,9]에서 선택된다.
[min (x), max (x)]에 M 노드가있는 등전위 그리드는 기초를 만드는 데 사용됩니다
기능. 다른 값의 D가 시도되고, 최적 D (최소 평균값
제곱 오차)가 선택된다. 작업은 선형이므로 선형 최소 자 솔버
사용. 이 계산 방식의 복잡도는 O (N * M ^ 2) (주로
최소 자승법에 의해 지배 됨).
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    N - 포인트 수, N> 0.
    M - 기본 함수의 수 (= number_of_nodes), M> = 2.
출력 매개 변수 :
    LSFitLinearWC () 서브 루틴과 같은 정보입니다.
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
                        -3은 일관성없는 제약 조건을 의미합니다.
    B - barycentric interpolant.
    Rep -보고, LSFitLinearWC () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            D 매개 변수의 DBest 최적 값
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void spline1dfitpenalized(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitpenalized(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);


/*************************************************************************
Weighted fitting by penalized cubic spline.

Equidistant grid with M nodes on [min(x,xc),max(x,xc)] is  used  to  build
basis functions. Basis functions are cubic splines with  natural  boundary
conditions. Problem is regularized by  adding non-linearity penalty to the
usual least squares penalty function:

    S(x) = arg min { LS + P }, where
    LS   = SUM { w[i]^2*(y[i] - S(x[i]))^2 } - least squares penalty
    P    = C*10^rho*integral{ S''(x)^2*dx } - non-linearity penalty
    rho  - tunable constant given by user
    C    - automatically determined scale parameter,
           makes penalty invariant with respect to scaling of X, Y, W.

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    W   -   weights, array[0..N-1]
            Each summand in square  sum  of  approximation deviations from
            given  values  is  multiplied  by  the square of corresponding
            weight. Fill it by 1's if you don't  want  to  solve  weighted
            problem.
    N   -   number of points (optional):
            * N>0
            * if given, only first N elements of X/Y/W are processed
            * if not given, automatically determined from X/Y/W sizes
    M   -   number of basis functions ( = number_of_nodes), M>=4.
    Rho -   regularization  constant  passed   by   user.   It   penalizes
            nonlinearity in the regression spline. It  is  logarithmically
            scaled,  i.e.  actual  value  of  regularization  constant  is
            calculated as 10^Rho. It is automatically scaled so that:
            * Rho=2.0 corresponds to moderate amount of nonlinearity
            * generally, it should be somewhere in the [-8.0,+8.0]
            If you do not want to penalize nonlineary,
            pass small Rho. Values as low as -15 should work.

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearWC() subroutine.
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD or
                           Cholesky decomposition; problem may be
                           too ill-conditioned (very rare)
    S   -   spline interpolant.
    Rep -   Following fields are set:
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroitine doesn't calculate task's condition number for K<>0.

NOTE 1: additional nodes are added to the spline outside  of  the  fitting
interval to force linearity when x<min(x,xc) or x>max(x,xc).  It  is  done
for consistency - we penalize non-linearity  at [min(x,xc),max(x,xc)],  so
it is natural to force linearity outside of this interval.

NOTE 2: function automatically sorts points,  so  caller may pass unsorted
array.

  -- ALGLIB PROJECT --
     Copyright 19.10.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
페널티 입방 스플라인에 의한 가중치 적용.
[min (x, xc), max (x, xc)]에 M 노드가있는 등전위 그리드를 사용하여
기초 기능. 기본 함수는 자연 경계를 갖는 3 차 스플라인입니다.
정황. 문제는 비선형 성 패널티를 추가하여 정규화됩니다.
평소 최소 제곱 페널티 기능 :
    S (x) = arg min {LS + P}, 여기서,
    LS = SUM {w [i] ^ 2 * (y [i] - S (x [i])) ^ 2} - 최소 자승 페널티
    P = C * 10 ^ ρ * 적분 {S "(x) ^ 2 * dx} - 비선형 성 패널티
    rho - 사용자가 지정한 튜너 블 상수
    C - 자동으로 결정된 스케일 파라미터,
           X, Y, W의 스케일링과 관련하여 페널티를 불변으로 만듭니다.
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    W - 가중치, 배열 [0..N-1]
            근사 편차의 제곱합에있는 각 summand
            주어진 값에 해당하는 제곱을 곱합니다.
            무게. 가중치를 풀고 싶지 않은 경우 1로 채우기
            문제.
    N - 점수 (선택 사항) :
            * N> 0
            * 주어진 경우 X / Y / W의 처음 N 개 요소 만 처리됩니다.
            * 지정하지 않으면 X / Y / W 크기에서 자동 결정
    M - 기본 함수의 수 (= number_of_nodes), M> = 4.
    Rho - 사용자가 전달한 정규화 상수입니다. 벌칙이 부과된다.
            회귀 스플라인의 비선형 성. 대수적으로
            스케일 된, 즉 정규화 상수의 실제 값은이다.
            10 ^ Rho로 계산됩니다. 다음과 같이 자동으로 조정됩니다.
            * Rho = 2.0은 중간 정도의 비선형성에 해당합니다.
            * 일반적으로 [-8.0, + 8.0]
            비선형 적 처벌을 원하지 않는다면,
            작은 Rho. -15만큼 낮은 값을 사용해야합니다.
출력 매개 변수 :
    LSFitLinearWC () 서브 루틴과 같은 정보입니다.
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치 또는
                           콜레 스키 분해; 문제는
                           너무 아프다 (매우 드문 경우)
    S - 스플라인 보간.
    담당자 - 다음 필드가 설정됩니다.
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업의 조건 번호를 계산하지 않습니다.
비고 1 : 피팅 외부의 스플라인에 추가 노드가 추가됩니다.
x <min (x, xc) 또는 x> max (x, xc) 일 때 선형성을 강요하는 간격. 완료되었습니다.
일관성을 위해 - 우리는 [min (x, xc), max (x, xc)]에서 비선형 성을 처벌한다.
이 간격 밖에서 ​​선형성을 강요하는 것이 자연 스럽다.
참고 2 : 함수는 점을 자동으로 정렬하므로 호출자는 정렬되지 않은
정렬.
  - ALGLIB 프로젝트 -
     Copyright 19.10.2010 Bochkanov Sergey
*************************************************** ********************** */
void spline1dfitpenalizedw(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitpenalizedw(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);


/*************************************************************************
Weighted fitting by cubic  spline,  with constraints on function values or
derivatives.

Equidistant grid with M-2 nodes on [min(x,xc),max(x,xc)] is  used to build
basis functions. Basis functions are cubic splines with continuous  second
derivatives  and  non-fixed first  derivatives  at  interval  ends.  Small
regularizing term is used  when  solving  constrained  tasks  (to  improve
stability).

Task is linear, so linear least squares solver is used. Complexity of this
computational scheme is O(N*M^2), mostly dominated by least squares solver

SEE ALSO
    Spline1DFitHermiteWC()  -   fitting by Hermite splines (more flexible,
                                less smooth)
    Spline1DFitCubic()      -   "lightweight" fitting  by  cubic  splines,
                                without invididual weights and constraints

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    W   -   weights, array[0..N-1]
            Each summand in square  sum  of  approximation deviations from
            given  values  is  multiplied  by  the square of corresponding
            weight. Fill it by 1's if you don't  want  to  solve  weighted
            task.
    N   -   number of points (optional):
            * N>0
            * if given, only first N elements of X/Y/W are processed
            * if not given, automatically determined from X/Y/W sizes
    XC  -   points where spline values/derivatives are constrained,
            array[0..K-1].
    YC  -   values of constraints, array[0..K-1]
    DC  -   array[0..K-1], types of constraints:
            * DC[i]=0   means that S(XC[i])=YC[i]
            * DC[i]=1   means that S'(XC[i])=YC[i]
            SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
    K   -   number of constraints (optional):
            * 0<=K<M.
            * K=0 means no constraints (XC/YC/DC are not used)
            * if given, only first K elements of XC/YC/DC are used
            * if not given, automatically determined from XC/YC/DC
    M   -   number of basis functions ( = number_of_nodes+2), M>=4.

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearWC() subroutine.
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
                        -3 means inconsistent constraints
    S   -   spline interpolant.
    Rep -   report, same format as in LSFitLinearWC() subroutine.
            Following fields are set:
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroitine doesn't calculate task's condition number for K<>0.


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:

Setting constraints can lead  to undesired  results,  like ill-conditioned
behavior, or inconsistency being detected. From the other side,  it allows
us to improve quality of the fit. Here we summarize  our  experience  with
constrained regression splines:
* excessive constraints can be inconsistent. Splines are  piecewise  cubic
  functions, and it is easy to create an example, where  large  number  of
  constraints  concentrated  in  small  area will result in inconsistency.
  Just because spline is not flexible enough to satisfy all of  them.  And
  same constraints spread across the  [min(x),max(x)]  will  be  perfectly
  consistent.
* the more evenly constraints are spread across [min(x),max(x)],  the more
  chances that they will be consistent
* the  greater  is  M (given  fixed  constraints),  the  more chances that
  constraints will be consistent
* in the general case, consistency of constraints IS NOT GUARANTEED.
* in the several special cases, however, we CAN guarantee consistency.
* one of this cases is constraints  on  the  function  values  AND/OR  its
  derivatives at the interval boundaries.
* another  special  case  is ONE constraint on the function value (OR, but
  not AND, derivative) anywhere in the interval

Our final recommendation is to use constraints  WHEN  AND  ONLY  WHEN  you
can't solve your task without them. Anything beyond  special  cases  given
above is not guaranteed and may result in inconsistency.


  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
함수 값에 대한 제약이있는 3 차 스플라인에 의한 가중치 피팅 또는
파생 상품.
[min (x, xc), max (x, xc)]에 M-2 노드가있는 등전위 그리드를 사용하여
기초 기능. 기본 함수는 연속 2 초
간격 끝에서 유래 물과 비 고정 일차 파생물. 작은
정규화 용어는 제한된 작업을 해결할 때 사용됩니다 (
안정).
작업은 선형이므로 선형 최소 자 솔버가 사용됩니다. 이 복잡성
계산 방식은 O (N * M ^ 2)이며, 대부분 최소 자승법이 지배합니다
관련 항목
    Spline1DFitHermiteWC () - Hermite 스플라인으로 피팅 (더 유연함,
                                덜 부드러운)
    Spline1DFitCubic () - 입방 스플라인에 의한 "경량"피팅,
                                무의미한 가중치와 제약없이
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    W - 가중치, 배열 [0..N-1]
            근사 편차의 제곱합에있는 각 summand
            주어진 값에 해당하는 제곱을 곱합니다.
            무게. 가중치를 풀고 싶지 않은 경우 1로 채우기
            태스크.
    N - 점수 (선택 사항) :
            * N> 0
            * 주어진 경우 X / Y / W의 처음 N 개 요소 만 처리됩니다.
            * 지정하지 않으면 X / Y / W 크기에서 자동 결정
    XC - 스플라인 값 / 파생물이 제한되는 지점,
            배열 [0..K-1].
    YC - 제약 조건 값, array [0..K-1]
    DC - 배열 [0..K-1], 제약 유형 :
            * DC [i] = 0은 S (XC [i]) = YC [i]
            * DC [i] = 1은 S '(XC [i]) = YC [i]
            제약 조건에 대한 중요한 정보는 아래를보십시오.
    K - 제약 조건 수 (선택 사항) :
            * 0 <= K <M.
            * K = 0은 제약이 없음을 의미합니다 (XC / YC / DC가 사용되지 않음)
            * 주어진 경우 XC / YC / DC의 첫 번째 K 요소 만 사용됩니다.
            * 지정하지 않으면 XC / YC / DC에서 자동으로 결정됩니다.
    M - 기본 함수의 수 (= number_of_nodes + 2), M> = 4.
출력 매개 변수 :
    LSFitLinearWC () 서브 루틴과 같은 정보입니다.
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
                        -3은 일관성없는 제약 조건을 의미합니다.
    S - 스플라인 보간.
    Rep -보고, LSFitLinearWC () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업의 조건 번호를 계산하지 않습니다.
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
제약 조건 설정 - 위험 및 기회 :
제약 조건 설정은 부적절한 결과처럼 바람직하지 않은 결과를 초래할 수 있습니다.
행동 또는 불일치가 감지됩니다. 다른면에서 보면
우리는 착용감을 향상시킬 수 있습니다. 여기에 우리는
구속 회귀 스플라인 :
* 과도한 제약 조건이 일치하지 않을 수 있습니다. 스플라인은 조각 별 입방체입니다.
  함수를 사용하고 예제를 만드는 것이 쉽습니다.
  작은 영역에 제약이 집중되면 불일치가 발생합니다.
  스플라인은 모든 것을 만족시킬만큼 유연하지 않기 때문입니다. 과
  [최소 (x), 최대 (x)]에 걸쳐 동일한 제약 조건이 퍼지면 완벽하게됩니다.
  일관된.
* 더 균등하게 제약 조건이 [min (x), max (x)]에 퍼지면 더 많은
  그들이 일관성있게 일할 수있는 기회
* M이 클수록 (고정 된 제약 조건이 주어짐), 더 많은 기회가 주어진다.
  제약 조건은 일관성이있다.
* 일반적으로 제약 조건의 일관성은 보장되지 않습니다.
* 몇 가지 특수한 경우에는 일관성을 보장 할 수 있습니다.
*이 경우 중 하나는 함수 값에 대한 제약 및 / 또는
  간격 경계에서 파생 상품.
* 또 다른 특별한 경우는 함수 값에 대한 하나의 제약입니다 (OR, 그러나
  AND, 파생물이 아님)
우리의 최종 권고는 언제 어디서나 제약 조건을 사용하는 것입니다.
그것들 없이는 당신의 과제를 해결할 수 없습니다. 주어진 특별한 경우를 넘어선 것
상기 보증은 보장되지 않으며 불일치가 발생할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void spline1dfitcubicwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitcubicwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);


/*************************************************************************
Weighted  fitting  by Hermite spline,  with constraints on function values
or first derivatives.

Equidistant grid with M nodes on [min(x,xc),max(x,xc)] is  used  to  build
basis functions. Basis functions are Hermite splines.  Small  regularizing
term is used when solving constrained tasks (to improve stability).

Task is linear, so linear least squares solver is used. Complexity of this
computational scheme is O(N*M^2), mostly dominated by least squares solver

SEE ALSO
    Spline1DFitCubicWC()    -   fitting by Cubic splines (less flexible,
                                more smooth)
    Spline1DFitHermite()    -   "lightweight" Hermite fitting, without
                                invididual weights and constraints

INPUT PARAMETERS:
    X   -   points, array[0..N-1].
    Y   -   function values, array[0..N-1].
    W   -   weights, array[0..N-1]
            Each summand in square  sum  of  approximation deviations from
            given  values  is  multiplied  by  the square of corresponding
            weight. Fill it by 1's if you don't  want  to  solve  weighted
            task.
    N   -   number of points (optional):
            * N>0
            * if given, only first N elements of X/Y/W are processed
            * if not given, automatically determined from X/Y/W sizes
    XC  -   points where spline values/derivatives are constrained,
            array[0..K-1].
    YC  -   values of constraints, array[0..K-1]
    DC  -   array[0..K-1], types of constraints:
            * DC[i]=0   means that S(XC[i])=YC[i]
            * DC[i]=1   means that S'(XC[i])=YC[i]
            SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
    K   -   number of constraints (optional):
            * 0<=K<M.
            * K=0 means no constraints (XC/YC/DC are not used)
            * if given, only first K elements of XC/YC/DC are used
            * if not given, automatically determined from XC/YC/DC
    M   -   number of basis functions (= 2 * number of nodes),
            M>=4,
            M IS EVEN!

OUTPUT PARAMETERS:
    Info-   same format as in LSFitLinearW() subroutine:
            * Info>0    task is solved
            * Info<=0   an error occured:
                        -4 means inconvergence of internal SVD
                        -3 means inconsistent constraints
                        -2 means odd M was passed (which is not supported)
                        -1 means another errors in parameters passed
                           (N<=0, for example)
    S   -   spline interpolant.
    Rep -   report, same format as in LSFitLinearW() subroutine.
            Following fields are set:
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error
                            NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroitine doesn't calculate task's condition number for K<>0.

IMPORTANT:
    this subroitine supports only even M's


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:

Setting constraints can lead  to undesired  results,  like ill-conditioned
behavior, or inconsistency being detected. From the other side,  it allows
us to improve quality of the fit. Here we summarize  our  experience  with
constrained regression splines:
* excessive constraints can be inconsistent. Splines are  piecewise  cubic
  functions, and it is easy to create an example, where  large  number  of
  constraints  concentrated  in  small  area will result in inconsistency.
  Just because spline is not flexible enough to satisfy all of  them.  And
  same constraints spread across the  [min(x),max(x)]  will  be  perfectly
  consistent.
* the more evenly constraints are spread across [min(x),max(x)],  the more
  chances that they will be consistent
* the  greater  is  M (given  fixed  constraints),  the  more chances that
  constraints will be consistent
* in the general case, consistency of constraints is NOT GUARANTEED.
* in the several special cases, however, we can guarantee consistency.
* one of this cases is  M>=4  and   constraints  on   the  function  value
  (AND/OR its derivative) at the interval boundaries.
* another special case is M>=4  and  ONE  constraint on the function value
  (OR, BUT NOT AND, derivative) anywhere in [min(x),max(x)]

Our final recommendation is to use constraints  WHEN  AND  ONLY  when  you
can't solve your task without them. Anything beyond  special  cases  given
above is not guaranteed and may result in inconsistency.

  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Hermite 스플라인에 의한 가중치 피팅, 함수 값에 대한 제약 조건 포함
또는 일차 파생 상품.
[min (x, xc), max (x, xc)]에 M 노드가있는 등전위 그리드를 사용하여
기초 기능. 기본 함수는 Hermite 스플라인입니다. 작은 정규화
용어는 제한된 작업을 해결할 때 (안정성 향상을 위해) 사용됩니다.
작업은 선형이므로 선형 최소 자 솔버가 사용됩니다. 이 복잡성
계산 방식은 O (N * M ^ 2)이며, 대부분 최소 자승법이 지배합니다
관련 항목
    Spline1DFitCubicWC () - 큐빅 스플라인으로 피팅 (덜 유연한,
                                더 부드럽게)
    Spline1DFitHermite () -없는 "경량"Hermite 피팅
                                무의미한 가중치 및 제약
입력 매개 변수 :
    X- 점, 배열 [0..N-1].
    Y - 함수 값, array [0..N-1].
    W - 가중치, 배열 [0..N-1]
            근사 편차의 제곱합에있는 각 summand
            주어진 값에 해당하는 제곱을 곱합니다.
            무게. 가중치를 풀고 싶지 않은 경우 1로 채우기
            태스크.
    N - 점수 (선택 사항) :
            * N> 0
            * 주어진 경우 X / Y / W의 처음 N 개 요소 만 처리됩니다.
            * 지정하지 않으면 X / Y / W 크기에서 자동 결정
    XC - 스플라인 값 / 파생물이 제한되는 지점,
            배열 [0..K-1].
    YC - 제약 조건 값, array [0..K-1]
    DC - 배열 [0..K-1], 제약 유형 :
            * DC [i] = 0은 S (XC [i]) = YC [i]
            * DC [i] = 1은 S '(XC [i]) = YC [i]
            제약 조건에 대한 중요한 정보는 아래를보십시오.
    K - 제약 조건 수 (선택 사항) :
            * 0 <= K <M.
            * K = 0은 제약이 없음을 의미합니다 (XC / YC / DC가 사용되지 않음)
            * 주어진 경우 XC / YC / DC의 첫 번째 K 요소 만 사용됩니다.
            * 지정하지 않으면 XC / YC / DC에서 자동으로 결정됩니다.
    M - 기본 함수의 수 (= 2 * 노드 수),
            M> = 4,
            나도 그래!
출력 매개 변수 :
    LSFitLinearW () 서브 루틴에서와 같은 정보 포맷 :
            * 정보> 0 작업이 해결되었습니다.
            * 정보 <= 0 오류가 발생했습니다 :
                        -4는 내부 SVD의 불일치를 의미합니다.
                        -3은 일관성없는 제약 조건을 의미합니다.
                        -2는 홀수 M이 전달되었음을 의미합니다 (지원되지 않음).
                        -1은 전달 된 매개 변수의 다른 오류를 의미합니다.
                           (예 : N <= 0)
    S - 스플라인 보간.
    Rep -보고, LSFitLinearW () 서브 루틴과 동일한 형식.
            다음 필드가 설정됩니다.
            * (X, Y)에서 RMSError rms 오류가 발생했습니다.
            * (X, Y)에 대한 AvgError 평균 오류.
            * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
            * MaxError 최대 오류
                            중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업의 조건 번호를 계산하지 않습니다.
중대한:
    이 서브 루틴은 M
요점 순서
서브 루틴은 점을 자동으로 정렬하므로 호출자는 정렬되지 않은 배열을 전달할 수 있습니다.
제약 조건 설정 - 위험 및 기회 :
제약 조건 설정은 부적절한 결과처럼 바람직하지 않은 결과를 초래할 수 있습니다.
행동 또는 불일치가 감지됩니다. 다른면에서 보면
우리는 착용감을 향상시킬 수 있습니다. 여기에 우리는
구속 회귀 스플라인 :
* 과도한 제약 조건이 일치하지 않을 수 있습니다. 스플라인은 조각 별 입방체입니다.
  함수를 사용하고 예제를 만드는 것이 쉽습니다.
  작은 영역에 제약이 집중되면 불일치가 발생합니다.
  스플라인은 모든 것을 만족시킬만큼 유연하지 않기 때문입니다. 과
  [최소 (x), 최대 (x)]에 걸쳐 동일한 제약 조건이 퍼지면 완벽하게됩니다.
  일관된.
* 더 균등하게 제약 조건이 [min (x), max (x)]에 퍼지면 더 많은
  그들이 일관성있게 일할 수있는 기회
* M이 클수록 (고정 된 제약 조건이 주어짐), 더 많은 기회가 주어진다.
  제약 조건은 일관성이있다.
* 일반적으로 제약 조건의 일관성은 보장되지 않습니다.
* 몇몇 특별한 경우에는 일관성을 보장 할 수 있습니다.
*이 경우 중 하나는 M> = 4이고 함수 값에 대한 제약
  (AND / OR 그 파생물)을 간격 경계에서 찾는다.
* 또 다른 특별한 경우는 M> = 4이고 함수 값에 대한 하나의 제약 조건입니다
  [최소 (x), 최대 (x)]의 모든 위치에서 (OR, BUT NOT AND, 파생)
우리의 최종 권고는 제약 조건을 언제 어디서나 사용하는 것입니다.
그것들 없이는 당신의 과제를 해결할 수 없습니다. 주어진 특별한 경우를 넘어선 것
상기 보증은 보장되지 않으며 불일치가 발생할 수 있습니다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void spline1dfithermitewc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfithermitewc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);


/*************************************************************************
Least squares fitting by cubic spline.

This subroutine is "lightweight" alternative for more complex and feature-
rich Spline1DFitCubicWC().  See  Spline1DFitCubicWC() for more information
about subroutine parameters (we don't duplicate it here because of length)

  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
큐빅 스플라인으로 피팅 된 최소 제곱.
이 서브 루틴은 좀 더 복잡하고 기능이 많은 "
rich Spline1DFitCubicWC (). 자세한 내용은 Spline1DFitCubicWC ()를 참조하십시오.
서브 루틴 매개 변수에 대해 (길이 때문에 여기에 중복되지 않습니다)
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void spline1dfitcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);


/*************************************************************************
Least squares fitting by Hermite spline.

This subroutine is "lightweight" alternative for more complex and feature-
rich Spline1DFitHermiteWC().  See Spline1DFitHermiteWC()  description  for
more information about subroutine parameters (we don't duplicate  it  here
because of length).

  -- ALGLIB PROJECT --
     Copyright 18.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Hermite 스플라인으로 피팅 된 최소 제곱.
이 서브 루틴은 좀 더 복잡하고 기능이 많은 "
rich Spline1DFitHermiteWC (). 자세한 내용은 Spline1DFitHermiteWC () 설명을 참조하십시오.
서브 루틴 매개 변수에 대한 자세한 정보 (여기에 중복되지 않습니다.
길이 때문에).
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 18.08.2009
*************************************************** ********************** */
void spline1dfithermite(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfithermite(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);


/*************************************************************************
Weighted linear least squares fitting.

QR decomposition is used to reduce task to MxM, then triangular solver  or
SVD-based solver is used depending on condition number of the  system.  It
allows to maximize speed and retain decent accuracy.

IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
           convenient to use PolynomialFit() function. This function gives
           best  results  on  polynomial  problems  and  solves  numerical
           stability  issues  which  arise  when   you   fit   high-degree
           polynomials to your data.

INPUT PARAMETERS:
    Y       -   array[0..N-1] Function values in  N  points.
    W       -   array[0..N-1]  Weights  corresponding to function  values.
                Each summand in square  sum  of  approximation  deviations
                from  given  values  is  multiplied  by  the   square   of
                corresponding weight.
    FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
                FMatrix[I, J] - value of J-th basis function in I-th point.
    N       -   number of points used. N>=1.
    M       -   number of basis functions, M>=1.

OUTPUT PARAMETERS:
    Info    -   error code:
                * -4    internal SVD decomposition subroutine failed (very
                        rare and for degenerate systems only)
                * -1    incorrect N/M were specified
                *  1    task is solved
    C       -   decomposition coefficients, array[0..M-1]
    Rep     -   fitting report. Following fields are set:
                * Rep.TaskRCond     reciprocal of condition number
                * R2                non-adjusted coefficient of determination
                                    (non-weighted)
                * RMSError          rms error on the (X,Y).
                * AvgError          average error on the (X,Y).
                * AvgRelError       average relative error on the non-zero Y
                * MaxError          maximum error
                                    NON-WEIGHTED ERRORS ARE CALCULATED

ERRORS IN PARAMETERS

This  solver  also  calculates different kinds of errors in parameters and
fills corresponding fields of report:
* Rep.CovPar        covariance matrix for parameters, array[K,K].
* Rep.ErrPar        errors in parameters, array[K],
                    errpar = sqrt(diag(CovPar))
* Rep.ErrCurve      vector of fit errors - standard deviations of empirical
                    best-fit curve from "ideal" best-fit curve built  with
                    infinite number of samples, array[N].
                    errcurve = sqrt(diag(F*CovPar*F')),
                    where F is functions matrix.
* Rep.Noise         vector of per-point estimates of noise, array[N]

NOTE:       noise in the data is estimated as follows:
            * for fitting without user-supplied  weights  all  points  are
              assumed to have same level of noise, which is estimated from
              the data
            * for fitting with user-supplied weights we assume that  noise
              level in I-th point is inversely proportional to Ith weight.
              Coefficient of proportionality is estimated from the data.

NOTE:       we apply small amount of regularization when we invert squared
            Jacobian and calculate covariance matrix. It  guarantees  that
            algorithm won't divide by zero  during  inversion,  but  skews
            error estimates a bit (fractional error is about 10^-9).

            However, we believe that this difference is insignificant  for
            all practical purposes except for the situation when you  want
            to compare ALGLIB results with "reference"  implementation  up
            to the last significant digit.

NOTE:       covariance matrix is estimated using  correction  for  degrees
            of freedom (covariances are divided by N-M instead of dividing
            by N).

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
가중치가 적용된 선형 최소 제곱 피팅.
QR 분해는 작업을 MxM으로 줄이기 위해 사용 된 다음 삼각 솔버 또는
SVD 기반 솔버는 시스템의 조건 번호에 따라 사용됩니다. 그것
속도를 극대화하고 적절한 정확성을 유지할 수 있습니다.
중요 : 다항식 피팅을 수행하려는 경우
           PolynomialFit () 함수를 사용하면 편리합니다. 이 함수는
           다항식 문제에 대한 최상의 결과 및 수치 해석
           당신이 높은 학위에 맞을 때 발생하는 안정성 문제
           다항식을 데이터에 적용합니다.
입력 매개 변수 :
    Y - 배열 [0..N-1] N 개의 함수 값.
    W - 배열 [0..N-1] 함수 값에 해당하는 가중치.
                각 summand 근사치 편차의 제곱합
                주어진 값으로부터 제곱의
                해당 무게.
    FMatrix - 기본 함수 값의 테이블, array [0..N-1, 0..M-1].
                FMatrix [I, J] - I 번째 점에서 J 번째 기초 함수의 값.
    N - 사용 된 점의 수. N> = 1이다.
    M - 기저 함수의 수, M> = 1.
출력 매개 변수 :
    정보 - 오류 코드 :
                * -4 내부 SVD 분해 서브 루틴 실패 (매우
                        희귀 및 퇴화 시스템 전용)
                * -1 잘못된 N / M이 지정되었습니다.
                * 1 과제 해결
    C - 분해 계수, 배열 [0..M-1]
    신고서 제출. 다음 필드가 설정됩니다.
                * Rep.TaskRCond 조건 수의 역수
                * R2 비 조정 계수
                                    (가중치 제외)
                * (X, Y)에서 RMSError rms 오류가 발생했습니다.
                * (X, Y)에 대한 AvgError 평균 오류.
                * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
                * MaxError 최대 오류
                                    중요하지 않은 오류가 계산됩니다.
매개 변수의 오류
이 솔버는 또한 매개 변수에서 다양한 종류의 오류를 계산하고
보고서의 해당 필드를 채 웁니다.
* 매개 변수에 대한 Rep.CovPar 공분산 행렬, 배열 [K, K].
매개 변수의 Rep.ErrPar 오류, 배열 [K],
                    errpar = sqrt (diag (CovPar))
* Rep.ErrCurve 적합 오차 벡터 - 경험적 표준 편차
                    내장 된 "이상적인"최적 곡선의 최적 곡선
                    무한 개수의 샘플, 배열 [N].
                    errcurve = sqrt (diag (F * CovPar * F ')),
                    여기서 F는 함수 행렬입니다.
* Rep. 잡음 당 포인트 추정치의 잡음 벡터, 배열 [N]
참고 : 데이터의 노이즈는 다음과 같이 추정됩니다.
            * 사용자가 제공하는 무게없이 모든 피팅을 맞추기 위해
              동일한 수준의 잡음을 갖는 것으로 가정하며,
              자료
            * 사용자가 제공 한 무게로 피팅하기 위해 우리는 소음
              레벨은 Ith 가중치에 반비례합니다.
              비례 계수는 데이터로부터 추정됩니다.
참고 : 우리는 제곱을 반전 할 때 소량의 정규화를 적용합니다.
            자 코비안 (Jacobian)을 선택하고 공분산 행렬을 계산합니다. 그것은
            알고리즘은 반전시 0으로 나누지 않지만 비뚤어 짐
            오류 추정 조금 (분수 오류 약 10 ^ -9)입니다.
            그러나 우리는이 차이가
            원하는 상황을 제외한 모든 실제적인 목적
            ALGLIB 결과를 "참조"구현과 비교
            마지막 유효 숫자로
참고 : 공분산 행렬은도에 대한 보정을 사용하여 추정됩니다.
            자유의 (공분산은 나누기 대신에 NM으로 나누어진다.
            N에 의해).
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitlinearw(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, const ae_int_t n, const ae_int_t m, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinearw(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);


/*************************************************************************
Weighted constained linear least squares fitting.

This  is  variation  of LSFitLinearW(), which searchs for min|A*x=b| given
that  K  additional  constaints  C*x=bc are satisfied. It reduces original
task to modified one: min|B*y-d| WITHOUT constraints,  then LSFitLinearW()
is called.

IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
           convenient to use PolynomialFit() function. This function gives
           best  results  on  polynomial  problems  and  solves  numerical
           stability  issues  which  arise  when   you   fit   high-degree
           polynomials to your data.

INPUT PARAMETERS:
    Y       -   array[0..N-1] Function values in  N  points.
    W       -   array[0..N-1]  Weights  corresponding to function  values.
                Each summand in square  sum  of  approximation  deviations
                from  given  values  is  multiplied  by  the   square   of
                corresponding weight.
    FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
                FMatrix[I,J] - value of J-th basis function in I-th point.
    CMatrix -   a table of constaints, array[0..K-1,0..M].
                I-th row of CMatrix corresponds to I-th linear constraint:
                CMatrix[I,0]*C[0] + ... + CMatrix[I,M-1]*C[M-1] = CMatrix[I,M]
    N       -   number of points used. N>=1.
    M       -   number of basis functions, M>=1.
    K       -   number of constraints, 0 <= K < M
                K=0 corresponds to absence of constraints.

OUTPUT PARAMETERS:
    Info    -   error code:
                * -4    internal SVD decomposition subroutine failed (very
                        rare and for degenerate systems only)
                * -3    either   too   many  constraints  (M   or   more),
                        degenerate  constraints   (some   constraints  are
                        repetead twice) or inconsistent  constraints  were
                        specified.
                *  1    task is solved
    C       -   decomposition coefficients, array[0..M-1]
    Rep     -   fitting report. Following fields are set:
                * R2                non-adjusted coefficient of determination
                                    (non-weighted)
                * RMSError          rms error on the (X,Y).
                * AvgError          average error on the (X,Y).
                * AvgRelError       average relative error on the non-zero Y
                * MaxError          maximum error
                                    NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroitine doesn't calculate task's condition number for K<>0.

ERRORS IN PARAMETERS

This  solver  also  calculates different kinds of errors in parameters and
fills corresponding fields of report:
* Rep.CovPar        covariance matrix for parameters, array[K,K].
* Rep.ErrPar        errors in parameters, array[K],
                    errpar = sqrt(diag(CovPar))
* Rep.ErrCurve      vector of fit errors - standard deviations of empirical
                    best-fit curve from "ideal" best-fit curve built  with
                    infinite number of samples, array[N].
                    errcurve = sqrt(diag(F*CovPar*F')),
                    where F is functions matrix.
* Rep.Noise         vector of per-point estimates of noise, array[N]

IMPORTANT:  errors  in  parameters  are  calculated  without  taking  into
            account boundary/linear constraints! Presence  of  constraints
            changes distribution of errors, but there is no  easy  way  to
            account for constraints when you calculate covariance matrix.

NOTE:       noise in the data is estimated as follows:
            * for fitting without user-supplied  weights  all  points  are
              assumed to have same level of noise, which is estimated from
              the data
            * for fitting with user-supplied weights we assume that  noise
              level in I-th point is inversely proportional to Ith weight.
              Coefficient of proportionality is estimated from the data.

NOTE:       we apply small amount of regularization when we invert squared
            Jacobian and calculate covariance matrix. It  guarantees  that
            algorithm won't divide by zero  during  inversion,  but  skews
            error estimates a bit (fractional error is about 10^-9).

            However, we believe that this difference is insignificant  for
            all practical purposes except for the situation when you  want
            to compare ALGLIB results with "reference"  implementation  up
            to the last significant digit.

NOTE:       covariance matrix is estimated using  correction  for  degrees
            of freedom (covariances are divided by N-M instead of dividing
            by N).

  -- ALGLIB --
     Copyright 07.09.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
가중치 부여 된 선형 최소 자승 피팅.
이것은 LSFitLinearW ()의 변형으로 min | A * x = b |를 검색합니다. 주어진
그 K 추가 constaints C * x = bc가 만족된다. 원본을 줄입니다.
수정 된 작업 : min | B * yd | 제약없이 LSFitLinearW ()
호출됩니다.
중요 : 다항식 피팅을 수행하려는 경우
           PolynomialFit () 함수를 사용하면 편리합니다. 이 함수는
           다항식 문제에 대한 최상의 결과 및 수치 해석
           당신이 높은 학위에 맞을 때 발생하는 안정성 문제
           다항식을 데이터에 적용합니다.
입력 매개 변수 :
    Y - 배열 [0..N-1] N 개의 함수 값.
    W - 배열 [0..N-1] 함수 값에 해당하는 가중치.
                각 summand 근사치 편차의 제곱합
                주어진 값으로부터 제곱의
                해당 무게.
    FMatrix - 기본 함수 값의 테이블, array [0..N-1, 0..M-1].
                FMatrix [I, J] - I 번째 점에서 J 번째 기초 함수의 값.
    CMatrix - constaints 테이블, 배열 [0..K-1.0..M].
                CMatrix의 I 번째 행은 I 번째 선형 제약에 해당합니다.
                CMatrix [I, M] * C [M-1] = CMatrix [I, M]
    N - 사용 된 점의 수. N> = 1이다.
    M - 기저 함수의 수, M> = 1.
    K - 제약 수, 0 <= K <M
                K = 0은 제약 조건 없음에 해당합니다.
출력 매개 변수 :
    정보 - 오류 코드 :
                * -4 내부 SVD 분해 서브 루틴 실패 (매우
                        희귀 및 퇴화 시스템 전용)
                * -3 너무 많은 제약 조건 (M 이상),
                        축퇴 제약 조건 (일부 제약 조건은
                        반복 두 번) 또는 일관성없는 제약 조건
                        지정된.
                * 1 과제 해결
    C - 분해 계수, 배열 [0..M-1]
    신고서 제출. 다음 필드가 설정됩니다.
                * R2 비 조정 계수
                                    (가중치 제외)
                * (X, Y)에서 RMSError rms 오류가 발생했습니다.
                * (X, Y)에 대한 AvgError 평균 오류.
                * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
                * MaxError 최대 오류
                                    중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업의 조건 번호를 계산하지 않습니다.
매개 변수의 오류
이 솔버는 또한 매개 변수에서 다양한 종류의 오류를 계산하고
보고서의 해당 필드를 채 웁니다.
* 매개 변수에 대한 Rep.CovPar 공분산 행렬, 배열 [K, K].
매개 변수의 Rep.ErrPar 오류, 배열 [K],
                    errpar = sqrt (diag (CovPar))
* Rep.ErrCurve 적합 오차 벡터 - 경험적 표준 편차
                    내장 된 "이상적인"최적 곡선의 최적 곡선
                    무한 개수의 샘플, 배열 [N].
                    errcurve = sqrt (diag (F * CovPar * F ')),
                    여기서 F는 함수 행렬입니다.
* Rep. 잡음 당 포인트 추정치의 잡음 벡터, 배열 [N]
중요 : 매개 변수의 오류는
            계정 경계 / 선형 제약! 제약 조건의 존재
            오류 배포를 변경하지만 쉬운 방법은 없습니다.
            공분산 행렬을 계산할 때 제약 조건을 설명합니다.
참고 : 데이터의 노이즈는 다음과 같이 추정됩니다.
            * 사용자가 제공하는 무게없이 모든 피팅을 맞추기 위해
              동일한 수준의 잡음을 갖는 것으로 가정하며,
              자료
            * 사용자가 제공 한 무게로 피팅하기 위해 우리는 소음
              레벨은 Ith 가중치에 반비례합니다.
              비례 계수는 데이터로부터 추정됩니다.
참고 : 우리는 제곱을 반전 할 때 소량의 정규화를 적용합니다.
            자 코비안 (Jacobian)을 선택하고 공분산 행렬을 계산합니다. 그것은
            알고리즘은 반전시 0으로 나누지 않지만 비뚤어 짐
            오류 추정 조금 (분수 오류 약 10 ^ -9)입니다.
            그러나 우리는이 차이가
            원하는 상황을 제외한 모든 실제적인 목적
            ALGLIB 결과를 "참조"구현과 비교
            마지막 유효 숫자로
참고 : 공분산 행렬은도에 대한 보정을 사용하여 추정됩니다.
            자유의 (공분산은 나누기 대신에 NM으로 나누어진다.
            N에 의해).
  - ALGLIB -
     저작권 07.09.2009 Bochkanov Sergey
*************************************************** ********************** */
void lsfitlinearwc(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, const real_2d_array &cmatrix, const ae_int_t n, const ae_int_t m, const ae_int_t k, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinearwc(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, const real_2d_array &cmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);


/*************************************************************************
Linear least squares fitting.

QR decomposition is used to reduce task to MxM, then triangular solver  or
SVD-based solver is used depending on condition number of the  system.  It
allows to maximize speed and retain decent accuracy.

IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
           convenient to use PolynomialFit() function. This function gives
           best  results  on  polynomial  problems  and  solves  numerical
           stability  issues  which  arise  when   you   fit   high-degree
           polynomials to your data.

INPUT PARAMETERS:
    Y       -   array[0..N-1] Function values in  N  points.
    FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
                FMatrix[I, J] - value of J-th basis function in I-th point.
    N       -   number of points used. N>=1.
    M       -   number of basis functions, M>=1.

OUTPUT PARAMETERS:
    Info    -   error code:
                * -4    internal SVD decomposition subroutine failed (very
                        rare and for degenerate systems only)
                *  1    task is solved
    C       -   decomposition coefficients, array[0..M-1]
    Rep     -   fitting report. Following fields are set:
                * Rep.TaskRCond     reciprocal of condition number
                * R2                non-adjusted coefficient of determination
                                    (non-weighted)
                * RMSError          rms error on the (X,Y).
                * AvgError          average error on the (X,Y).
                * AvgRelError       average relative error on the non-zero Y
                * MaxError          maximum error
                                    NON-WEIGHTED ERRORS ARE CALCULATED

ERRORS IN PARAMETERS

This  solver  also  calculates different kinds of errors in parameters and
fills corresponding fields of report:
* Rep.CovPar        covariance matrix for parameters, array[K,K].
* Rep.ErrPar        errors in parameters, array[K],
                    errpar = sqrt(diag(CovPar))
* Rep.ErrCurve      vector of fit errors - standard deviations of empirical
                    best-fit curve from "ideal" best-fit curve built  with
                    infinite number of samples, array[N].
                    errcurve = sqrt(diag(F*CovPar*F')),
                    where F is functions matrix.
* Rep.Noise         vector of per-point estimates of noise, array[N]

NOTE:       noise in the data is estimated as follows:
            * for fitting without user-supplied  weights  all  points  are
              assumed to have same level of noise, which is estimated from
              the data
            * for fitting with user-supplied weights we assume that  noise
              level in I-th point is inversely proportional to Ith weight.
              Coefficient of proportionality is estimated from the data.

NOTE:       we apply small amount of regularization when we invert squared
            Jacobian and calculate covariance matrix. It  guarantees  that
            algorithm won't divide by zero  during  inversion,  but  skews
            error estimates a bit (fractional error is about 10^-9).

            However, we believe that this difference is insignificant  for
            all practical purposes except for the situation when you  want
            to compare ALGLIB results with "reference"  implementation  up
            to the last significant digit.

NOTE:       covariance matrix is estimated using  correction  for  degrees
            of freedom (covariances are divided by N-M instead of dividing
            by N).

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
선형 최소 제곱합.
QR 분해는 작업을 MxM으로 줄이기 위해 사용 된 다음 삼각 솔버 또는
SVD 기반 솔버는 시스템의 조건 번호에 따라 사용됩니다. 그것
속도를 극대화하고 적절한 정확성을 유지할 수 있습니다.
중요 : 다항식 피팅을 수행하려는 경우
           PolynomialFit () 함수를 사용하면 편리합니다. 이 함수는
           다항식 문제에 대한 최상의 결과 및 수치 해석
           당신이 높은 학위에 맞을 때 발생하는 안정성 문제
           다항식을 데이터에 적용합니다.
입력 매개 변수 :
    Y - 배열 [0..N-1] N 개의 함수 값.
    FMatrix - 기본 함수 값의 테이블, array [0..N-1, 0..M-1].
                FMatrix [I, J] - I 번째 점에서 J 번째 기초 함수의 값.
    N - 사용 된 점의 수. N> = 1이다.
    M - 기저 함수의 수, M> = 1.
출력 매개 변수 :
    정보 - 오류 코드 :
                * -4 내부 SVD 분해 서브 루틴 실패 (매우
                        희귀 및 퇴화 시스템 전용)
                * 1 과제 해결
    C - 분해 계수, 배열 [0..M-1]
    신고서 제출. 다음 필드가 설정됩니다.
                * Rep.TaskRCond 조건 수의 역수
                * R2 비 조정 계수
                                    (가중치 제외)
                * (X, Y)에서 RMSError rms 오류가 발생했습니다.
                * (X, Y)에 대한 AvgError 평균 오류.
                * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
                * MaxError 최대 오류
                                    중요하지 않은 오류가 계산됩니다.
매개 변수의 오류
이 솔버는 또한 매개 변수에서 다양한 종류의 오류를 계산하고
보고서의 해당 필드를 채 웁니다.
* 매개 변수에 대한 Rep.CovPar 공분산 행렬, 배열 [K, K].
매개 변수의 Rep.ErrPar 오류, 배열 [K],
                    errpar = sqrt (diag (CovPar))
* Rep.ErrCurve 적합 오차 벡터 - 경험적 표준 편차
                    내장 된 "이상적인"최적 곡선의 최적 곡선
                    무한 개수의 샘플, 배열 [N].
                    errcurve = sqrt (diag (F * CovPar * F ')),
                    여기서 F는 함수 행렬입니다.
* Rep. 잡음 당 포인트 추정치의 잡음 벡터, 배열 [N]
참고 : 데이터의 노이즈는 다음과 같이 추정됩니다.
            * 사용자가 제공하는 무게없이 모든 피팅을 맞추기 위해
              동일한 수준의 잡음을 갖는 것으로 가정하며,
              자료
            * 사용자가 제공 한 무게로 피팅하기 위해 우리는 소음
              레벨은 Ith 가중치에 반비례합니다.
              비례 계수는 데이터로부터 추정됩니다.
참고 : 우리는 제곱을 반전 할 때 소량의 정규화를 적용합니다.
            자 코비안 (Jacobian)을 선택하고 공분산 행렬을 계산합니다. 그것은
            알고리즘은 반전시 0으로 나누지 않지만 비뚤어 짐
            오류 추정 조금 (분수 오류 약 10 ^ -9)입니다.
            그러나 우리는이 차이가
            원하는 상황을 제외한 모든 실제적인 목적
            ALGLIB 결과를 "참조"구현과 비교
            마지막 유효 숫자로
참고 : 공분산 행렬은도에 대한 보정을 사용하여 추정됩니다.
            자유의 (공분산은 나누기 대신에 NM으로 나누어진다.
            N에 의해).
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitlinear(const real_1d_array &y, const real_2d_array &fmatrix, const ae_int_t n, const ae_int_t m, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinear(const real_1d_array &y, const real_2d_array &fmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);


/*************************************************************************
Constained linear least squares fitting.

This  is  variation  of LSFitLinear(),  which searchs for min|A*x=b| given
that  K  additional  constaints  C*x=bc are satisfied. It reduces original
task to modified one: min|B*y-d| WITHOUT constraints,  then  LSFitLinear()
is called.

IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
           convenient to use PolynomialFit() function. This function gives
           best  results  on  polynomial  problems  and  solves  numerical
           stability  issues  which  arise  when   you   fit   high-degree
           polynomials to your data.

INPUT PARAMETERS:
    Y       -   array[0..N-1] Function values in  N  points.
    FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
                FMatrix[I,J] - value of J-th basis function in I-th point.
    CMatrix -   a table of constaints, array[0..K-1,0..M].
                I-th row of CMatrix corresponds to I-th linear constraint:
                CMatrix[I,0]*C[0] + ... + CMatrix[I,M-1]*C[M-1] = CMatrix[I,M]
    N       -   number of points used. N>=1.
    M       -   number of basis functions, M>=1.
    K       -   number of constraints, 0 <= K < M
                K=0 corresponds to absence of constraints.

OUTPUT PARAMETERS:
    Info    -   error code:
                * -4    internal SVD decomposition subroutine failed (very
                        rare and for degenerate systems only)
                * -3    either   too   many  constraints  (M   or   more),
                        degenerate  constraints   (some   constraints  are
                        repetead twice) or inconsistent  constraints  were
                        specified.
                *  1    task is solved
    C       -   decomposition coefficients, array[0..M-1]
    Rep     -   fitting report. Following fields are set:
                * R2                non-adjusted coefficient of determination
                                    (non-weighted)
                * RMSError          rms error on the (X,Y).
                * AvgError          average error on the (X,Y).
                * AvgRelError       average relative error on the non-zero Y
                * MaxError          maximum error
                                    NON-WEIGHTED ERRORS ARE CALCULATED

IMPORTANT:
    this subroitine doesn't calculate task's condition number for K<>0.

ERRORS IN PARAMETERS

This  solver  also  calculates different kinds of errors in parameters and
fills corresponding fields of report:
* Rep.CovPar        covariance matrix for parameters, array[K,K].
* Rep.ErrPar        errors in parameters, array[K],
                    errpar = sqrt(diag(CovPar))
* Rep.ErrCurve      vector of fit errors - standard deviations of empirical
                    best-fit curve from "ideal" best-fit curve built  with
                    infinite number of samples, array[N].
                    errcurve = sqrt(diag(F*CovPar*F')),
                    where F is functions matrix.
* Rep.Noise         vector of per-point estimates of noise, array[N]

IMPORTANT:  errors  in  parameters  are  calculated  without  taking  into
            account boundary/linear constraints! Presence  of  constraints
            changes distribution of errors, but there is no  easy  way  to
            account for constraints when you calculate covariance matrix.

NOTE:       noise in the data is estimated as follows:
            * for fitting without user-supplied  weights  all  points  are
              assumed to have same level of noise, which is estimated from
              the data
            * for fitting with user-supplied weights we assume that  noise
              level in I-th point is inversely proportional to Ith weight.
              Coefficient of proportionality is estimated from the data.

NOTE:       we apply small amount of regularization when we invert squared
            Jacobian and calculate covariance matrix. It  guarantees  that
            algorithm won't divide by zero  during  inversion,  but  skews
            error estimates a bit (fractional error is about 10^-9).

            However, we believe that this difference is insignificant  for
            all practical purposes except for the situation when you  want
            to compare ALGLIB results with "reference"  implementation  up
            to the last significant digit.

NOTE:       covariance matrix is estimated using  correction  for  degrees
            of freedom (covariances are divided by N-M instead of dividing
            by N).

  -- ALGLIB --
     Copyright 07.09.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
Constained 선형 최소 제곱 피팅.
이것은 min | A * x = b |를 검색하는 LSFitLinear ()의 변형입니다. 주어진
그 K 추가 constaints C * x = bc가 만족된다. 원본을 줄입니다.
수정 된 작업 : min | B * yd | 제약없이 LSFitLinear ()
호출됩니다.
중요 : 다항식 피팅을 수행하려는 경우
           PolynomialFit () 함수를 사용하면 편리합니다. 이 함수는
           다항식 문제에 대한 최상의 결과 및 수치 해석
           당신이 높은 학위에 맞을 때 발생하는 안정성 문제
           다항식을 데이터에 적용합니다.
입력 매개 변수 :
    Y - 배열 [0..N-1] N 개의 함수 값.
    FMatrix - 기본 함수 값의 테이블, array [0..N-1, 0..M-1].
                FMatrix [I, J] - I 번째 점에서 J 번째 기초 함수의 값.
    CMatrix - constaints 테이블, 배열 [0..K-1.0..M].
                CMatrix의 I 번째 행은 I 번째 선형 제약에 해당합니다.
                CMatrix [I, M] * C [M-1] = CMatrix [I, M]
    N - 사용 된 점의 수. N> = 1이다.
    M - 기저 함수의 수, M> = 1.
    K - 제약 수, 0 <= K <M
                K = 0은 제약 조건 없음에 해당합니다.
출력 매개 변수 :
    정보 - 오류 코드 :
                * -4 내부 SVD 분해 서브 루틴 실패 (매우
                        희귀 및 퇴화 시스템 전용)
                * -3 너무 많은 제약 조건 (M 이상),
                        축퇴 제약 조건 (일부 제약 조건은
                        반복 두 번) 또는 일관성없는 제약 조건
                        지정된.
                * 1 과제 해결
    C - 분해 계수, 배열 [0..M-1]
    신고서 제출. 다음 필드가 설정됩니다.
                * R2 비 조정 계수
                                    (가중치 제외)
                * (X, Y)에서 RMSError rms 오류가 발생했습니다.
                * (X, Y)에 대한 AvgError 평균 오류.
                * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
                * MaxError 최대 오류
                                    중요하지 않은 오류가 계산됩니다.
중대한:
    이 서브 루틴은 K <> 0에 대한 작업의 조건 번호를 계산하지 않습니다.
매개 변수의 오류
이 솔버는 또한 매개 변수에서 다양한 종류의 오류를 계산하고
보고서의 해당 필드를 채 웁니다.
* 매개 변수에 대한 Rep.CovPar 공분산 행렬, 배열 [K, K].
매개 변수의 Rep.ErrPar 오류, 배열 [K],
                    errpar = sqrt (diag (CovPar))
* Rep.ErrCurve 적합 오차 벡터 - 경험적 표준 편차
                    내장 된 "이상적인"최적 곡선의 최적 곡선
                    무한 개수의 샘플, 배열 [N].
                    errcurve = sqrt (diag (F * CovPar * F ')),
                    여기서 F는 함수 행렬입니다.
* Rep. 잡음 당 포인트 추정치의 잡음 벡터, 배열 [N]
중요 : 매개 변수의 오류는
            계정 경계 / 선형 제약! 제약 조건의 존재
            오류 배포를 변경하지만 쉬운 방법은 없습니다.
            공분산 행렬을 계산할 때 제약 조건을 설명합니다.
참고 : 데이터의 노이즈는 다음과 같이 추정됩니다.
            * 사용자가 제공하는 무게없이 모든 피팅을 맞추기 위해
              동일한 수준의 잡음을 갖는 것으로 가정하며,
              자료
            * 사용자가 제공 한 무게로 피팅하기 위해 우리는 소음
              레벨은 Ith 가중치에 반비례합니다.
              비례 계수는 데이터로부터 추정됩니다.
참고 : 우리는 제곱을 반전 할 때 소량의 정규화를 적용합니다.
            자 코비안 (Jacobian)을 선택하고 공분산 행렬을 계산합니다. 그것은
            알고리즘은 반전시 0으로 나누지 않지만 비뚤어 짐
            오류 추정 조금 (분수 오류 약 10 ^ -9)입니다.
            그러나 우리는이 차이가
            원하는 상황을 제외한 모든 실제적인 목적
            ALGLIB 결과를 "참조"구현과 비교
            마지막 유효 숫자로
참고 : 공분산 행렬은도에 대한 보정을 사용하여 추정됩니다.
            자유의 (공분산은 나누기 대신에 NM으로 나누어진다.
            N에 의해).
  - ALGLIB -
     저작권 07.09.2009 Bochkanov Sergey
*************************************************** ********************** */
void lsfitlinearc(const real_1d_array &y, const real_2d_array &fmatrix, const real_2d_array &cmatrix, const ae_int_t n, const ae_int_t m, const ae_int_t k, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinearc(const real_1d_array &y, const real_2d_array &fmatrix, const real_2d_array &cmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);


/*************************************************************************
Weighted nonlinear least squares fitting using function values only.

Combination of numerical differentiation and secant updates is used to
obtain function Jacobian.

Nonlinear task min(F(c)) is solved, where

    F(c) = (w[0]*(f(c,x[0])-y[0]))^2 + ... + (w[n-1]*(f(c,x[n-1])-y[n-1]))^2,

    * N is a number of points,
    * M is a dimension of a space points belong to,
    * K is a dimension of a space of parameters being fitted,
    * w is an N-dimensional vector of weight coefficients,
    * x is a set of N points, each of them is an M-dimensional vector,
    * c is a K-dimensional vector of parameters being fitted

This subroutine uses only f(c,x[i]).

INPUT PARAMETERS:
    X       -   array[0..N-1,0..M-1], points (one row = one point)
    Y       -   array[0..N-1], function values.
    W       -   weights, array[0..N-1]
    C       -   array[0..K-1], initial approximation to the solution,
    N       -   number of points, N>1
    M       -   dimension of space
    K       -   number of parameters being fitted
    DiffStep-   numerical differentiation step;
                should not be very small or large;
                large = loss of accuracy
                small = growth of round-off errors

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 18.10.2008 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
함수 값만 사용하여 가중치가있는 비선형 최소 제곱 피팅.
숫자 차별화와 시컨트 업데이트의 조합은
함수 Jacobian을 얻는다.
비선형 작업 min (F (c))가 풀린다.
    2 + ... + (w [n-1] * (f (c, x [0]) - n-1]) - y [n-1])) ^ 2,
    * N은 포인트의 숫자입니다,
    * M은 공간 점의 차원이며,
    * K는 맞는 매개 변수 공간의 차원입니다.
    * w는 가중 계수의 N 차원 벡터이며,
    * x는 N 점의 집합이며, 각각은 M 차원 벡터이며,
    * c는 맞는 매개 변수의 K 차원 벡터입니다.
이 서브 루틴은 f (c, x [i]) 만 사용합니다.
입력 매개 변수 :
    X- 어레이 [0..N-1.0..M-1], 포인트 (1 행 = 1 포인트)
    Y- 배열 [0..N-1], 함수 값.
    W - 가중치, 배열 [0..N-1]
    C - 배열 [0..K-1], 솔루션에 대한 초기 근사,
    N - 점의 수, N> 1
    M - 공간의 차원
    K - 맞는 매개 변수의 수
    DiffStep- 수치 차별화 단계;
                아주 작거나 크지 않아야한다.
                큰 = 정확성의 상실
                작은 = 반올림 오류 증가
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Bochkanov Sergey의 Copyright 18.10.2008
*************************************************** ********************** */
void lsfitcreatewf(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const double diffstep, lsfitstate &state);
void lsfitcreatewf(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const double diffstep, lsfitstate &state);


/*************************************************************************
Nonlinear least squares fitting using function values only.

Combination of numerical differentiation and secant updates is used to
obtain function Jacobian.

Nonlinear task min(F(c)) is solved, where

    F(c) = (f(c,x[0])-y[0])^2 + ... + (f(c,x[n-1])-y[n-1])^2,

    * N is a number of points,
    * M is a dimension of a space points belong to,
    * K is a dimension of a space of parameters being fitted,
    * w is an N-dimensional vector of weight coefficients,
    * x is a set of N points, each of them is an M-dimensional vector,
    * c is a K-dimensional vector of parameters being fitted

This subroutine uses only f(c,x[i]).

INPUT PARAMETERS:
    X       -   array[0..N-1,0..M-1], points (one row = one point)
    Y       -   array[0..N-1], function values.
    C       -   array[0..K-1], initial approximation to the solution,
    N       -   number of points, N>1
    M       -   dimension of space
    K       -   number of parameters being fitted
    DiffStep-   numerical differentiation step;
                should not be very small or large;
                large = loss of accuracy
                small = growth of round-off errors

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 18.10.2008 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
함수 값만 사용하는 비선형 최소 자승 피팅.
숫자 차별화와 시컨트 업데이트의 조합은
함수 Jacobian을 얻는다.
비선형 작업 min (F (c))가 풀린다.
    2 + ... + (f (c, x [n-1]) - y [n-1]) ^ 2 (f (c) ,
    * N은 포인트의 숫자입니다,
    * M은 공간 점의 차원이며,
    * K는 맞는 매개 변수 공간의 차원입니다.
    * w는 가중 계수의 N 차원 벡터이며,
    * x는 N 점의 집합이며, 각각은 M 차원 벡터이며,
    * c는 맞는 매개 변수의 K 차원 벡터입니다.
이 서브 루틴은 f (c, x [i]) 만 사용합니다.
입력 매개 변수 :
    X- 어레이 [0..N-1.0..M-1], 포인트 (1 행 = 1 포인트)
    Y- 배열 [0..N-1], 함수 값.
    C - 배열 [0..K-1], 솔루션에 대한 초기 근사,
    N - 점의 수, N> 1
    M - 공간의 차원
    K - 맞는 매개 변수의 수
    DiffStep- 수치 차별화 단계;
                아주 작거나 크지 않아야한다.
                큰 = 정확성의 상실
                작은 = 반올림 오류 증가
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Bochkanov Sergey의 Copyright 18.10.2008
*************************************************** ********************** */
void lsfitcreatef(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const double diffstep, lsfitstate &state);
void lsfitcreatef(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const double diffstep, lsfitstate &state);


/*************************************************************************
Weighted nonlinear least squares fitting using gradient only.

Nonlinear task min(F(c)) is solved, where

    F(c) = (w[0]*(f(c,x[0])-y[0]))^2 + ... + (w[n-1]*(f(c,x[n-1])-y[n-1]))^2,

    * N is a number of points,
    * M is a dimension of a space points belong to,
    * K is a dimension of a space of parameters being fitted,
    * w is an N-dimensional vector of weight coefficients,
    * x is a set of N points, each of them is an M-dimensional vector,
    * c is a K-dimensional vector of parameters being fitted

This subroutine uses only f(c,x[i]) and its gradient.

INPUT PARAMETERS:
    X       -   array[0..N-1,0..M-1], points (one row = one point)
    Y       -   array[0..N-1], function values.
    W       -   weights, array[0..N-1]
    C       -   array[0..K-1], initial approximation to the solution,
    N       -   number of points, N>1
    M       -   dimension of space
    K       -   number of parameters being fitted
    CheapFG -   boolean flag, which is:
                * True  if both function and gradient calculation complexity
                        are less than O(M^2).  An improved  algorithm  can
                        be  used  which corresponds  to  FGJ  scheme  from
                        MINLM unit.
                * False otherwise.
                        Standard Jacibian-bases  Levenberg-Marquardt  algo
                        will be used (FJ scheme).

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

See also:
    LSFitResults
    LSFitCreateFG (fitting without weights)
    LSFitCreateWFGH (fitting using Hessian)
    LSFitCreateFGH (fitting using Hessian, without weights)

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
그라디언트 만 사용하는 가중치가있는 비선형 최소 제곱합입니다.
비선형 작업 min (F (c))가 풀린다.
    2 + ... + (w [n-1] * (f (c, x [0]) - n-1]) - y [n-1])) ^ 2,
    * N은 포인트의 숫자입니다,
    * M은 공간 점의 차원이며,
    * K는 맞는 매개 변수 공간의 차원입니다.
    * w는 가중 계수의 N 차원 벡터이며,
    * x는 N 점의 집합이며, 각각은 M 차원 벡터이며,
    * c는 맞는 매개 변수의 K 차원 벡터입니다.
이 서브 루틴은 f (c, x [i])와 그 그라디언트 만 사용합니다.
입력 매개 변수 :
    X- 어레이 [0..N-1.0..M-1], 포인트 (1 행 = 1 포인트)
    Y- 배열 [0..N-1], 함수 값.
    W - 가중치, 배열 [0..N-1]
    C - 배열 [0..K-1], 솔루션에 대한 초기 근사,
    N - 점의 수, N> 1
    M - 공간의 차원
    K - 맞는 매개 변수의 수
    CheapFG - 부울 값 플래그는 다음과 같습니다.
                * 함수 및 그래디언트 계산의 복잡성이 둘 다 맞다면 참입니다.
                        O (M ^ 2)보다 작다. 향상된 알고리즘으로
                        에서 FGJ 체계에 해당하는 사용
                        MINLM 장치.
                * 그렇지 않으면 거짓.
                        표준 Jaciberian-bases Levenberg-Marquardt algo
                        (FJ 체계)가 사용될 것입니다.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참조 :
    LSFitResults
    LSFitCreateFG (가중치없이 피팅)
    LSFitCreateWFGH (헤 시안을 사용하여 피팅)
    LSFitCreateFGH (가중치없이 헤 시안을 사용하여 피팅)
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitcreatewfg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const bool cheapfg, lsfitstate &state);
void lsfitcreatewfg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const bool cheapfg, lsfitstate &state);


/*************************************************************************
Nonlinear least squares fitting using gradient only, without individual
weights.

Nonlinear task min(F(c)) is solved, where

    F(c) = ((f(c,x[0])-y[0]))^2 + ... + ((f(c,x[n-1])-y[n-1]))^2,

    * N is a number of points,
    * M is a dimension of a space points belong to,
    * K is a dimension of a space of parameters being fitted,
    * x is a set of N points, each of them is an M-dimensional vector,
    * c is a K-dimensional vector of parameters being fitted

This subroutine uses only f(c,x[i]) and its gradient.

INPUT PARAMETERS:
    X       -   array[0..N-1,0..M-1], points (one row = one point)
    Y       -   array[0..N-1], function values.
    C       -   array[0..K-1], initial approximation to the solution,
    N       -   number of points, N>1
    M       -   dimension of space
    K       -   number of parameters being fitted
    CheapFG -   boolean flag, which is:
                * True  if both function and gradient calculation complexity
                        are less than O(M^2).  An improved  algorithm  can
                        be  used  which corresponds  to  FGJ  scheme  from
                        MINLM unit.
                * False otherwise.
                        Standard Jacibian-bases  Levenberg-Marquardt  algo
                        will be used (FJ scheme).

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
그라디언트 만 사용하는 비선형 최소 제곱 피팅, 개별 없음
무게.
비선형 작업 min (F (c))가 풀린다.
    2 + ... + (f (c, x [n-1]) - y [n-1] )) ^ 2,
    * N은 포인트의 숫자입니다,
    * M은 공간 점의 차원이며,
    * K는 맞는 매개 변수 공간의 차원입니다.
    * x는 N 점의 집합이며, 각각은 M 차원 벡터이며,
    * c는 맞는 매개 변수의 K 차원 벡터입니다.
이 서브 루틴은 f (c, x [i])와 그 그라디언트 만 사용합니다.
입력 매개 변수 :
    X- 어레이 [0..N-1.0..M-1], 포인트 (1 행 = 1 포인트)
    Y- 배열 [0..N-1], 함수 값.
    C - 배열 [0..K-1], 솔루션에 대한 초기 근사,
    N - 점의 수, N> 1
    M - 공간의 차원
    K - 맞는 매개 변수의 수
    CheapFG - 부울 값 플래그는 다음과 같습니다.
                * 함수 및 그래디언트 계산의 복잡성이 둘 다 맞다면 참입니다.
                        O (M ^ 2)보다 작다. 향상된 알고리즘으로
                        에서 FGJ 체계에 해당하는 사용
                        MINLM 장치.
                * 그렇지 않으면 거짓.
                        표준 Jaciberian-bases Levenberg-Marquardt algo
                        (FJ 체계)가 사용될 것입니다.
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitcreatefg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const bool cheapfg, lsfitstate &state);
void lsfitcreatefg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const bool cheapfg, lsfitstate &state);


/*************************************************************************
Weighted nonlinear least squares fitting using gradient/Hessian.

Nonlinear task min(F(c)) is solved, where

    F(c) = (w[0]*(f(c,x[0])-y[0]))^2 + ... + (w[n-1]*(f(c,x[n-1])-y[n-1]))^2,

    * N is a number of points,
    * M is a dimension of a space points belong to,
    * K is a dimension of a space of parameters being fitted,
    * w is an N-dimensional vector of weight coefficients,
    * x is a set of N points, each of them is an M-dimensional vector,
    * c is a K-dimensional vector of parameters being fitted

This subroutine uses f(c,x[i]), its gradient and its Hessian.

INPUT PARAMETERS:
    X       -   array[0..N-1,0..M-1], points (one row = one point)
    Y       -   array[0..N-1], function values.
    W       -   weights, array[0..N-1]
    C       -   array[0..K-1], initial approximation to the solution,
    N       -   number of points, N>1
    M       -   dimension of space
    K       -   number of parameters being fitted

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
그라디언트 / 헤 시안을 사용한 가중 비선형 최소 제곱 피팅.
비선형 작업 min (F (c))가 풀린다.
    2 + ... + (w [n-1] * (f (c, x [0]) - n-1]) - y [n-1])) ^ 2,
    * N은 포인트의 숫자입니다,
    * M은 공간 점의 차원이며,
    * K는 맞는 매개 변수 공간의 차원입니다.
    * w는 가중 계수의 N 차원 벡터이며,
    * x는 N 점의 집합이며, 각각은 M 차원 벡터이며,
    * c는 맞는 매개 변수의 K 차원 벡터입니다.
이 서브 루틴은 f (c, x [i]), 그 그라데이션 및 헤 시안을 사용합니다.
입력 매개 변수 :
    X- 어레이 [0..N-1.0..M-1], 포인트 (1 행 = 1 포인트)
    Y- 배열 [0..N-1], 함수 값.
    W - 가중치, 배열 [0..N-1]
    C - 배열 [0..K-1], 솔루션에 대한 초기 근사,
    N - 점의 수, N> 1
    M - 공간의 차원
    K - 맞는 매개 변수의 수
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitcreatewfgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, lsfitstate &state);
void lsfitcreatewfgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, lsfitstate &state);


/*************************************************************************
Nonlinear least squares fitting using gradient/Hessian, without individial
weights.

Nonlinear task min(F(c)) is solved, where

    F(c) = ((f(c,x[0])-y[0]))^2 + ... + ((f(c,x[n-1])-y[n-1]))^2,

    * N is a number of points,
    * M is a dimension of a space points belong to,
    * K is a dimension of a space of parameters being fitted,
    * x is a set of N points, each of them is an M-dimensional vector,
    * c is a K-dimensional vector of parameters being fitted

This subroutine uses f(c,x[i]), its gradient and its Hessian.

INPUT PARAMETERS:
    X       -   array[0..N-1,0..M-1], points (one row = one point)
    Y       -   array[0..N-1], function values.
    C       -   array[0..K-1], initial approximation to the solution,
    N       -   number of points, N>1
    M       -   dimension of space
    K       -   number of parameters being fitted

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
그라디언트 / 헤 시안을 사용하는 비선형 최소 제곱 피팅
무게.
비선형 작업 min (F (c))가 풀린다.
    2 + ... + (f (c, x [n-1]) - y [n-1] )) ^ 2,
    * N은 포인트의 숫자입니다,
    * M은 공간 점의 차원이며,
    * K는 맞는 매개 변수 공간의 차원입니다.
    * x는 N 점의 집합이며, 각각은 M 차원 벡터이며,
    * c는 맞는 매개 변수의 K 차원 벡터입니다.
이 서브 루틴은 f (c, x [i]), 그 그라데이션 및 헤 시안을 사용합니다.
입력 매개 변수 :
    X- 어레이 [0..N-1.0..M-1], 포인트 (1 행 = 1 포인트)
    Y- 배열 [0..N-1], 함수 값.
    C - 배열 [0..K-1], 솔루션에 대한 초기 근사,
    N - 점의 수, N> 1
    M - 공간의 차원
    K - 맞는 매개 변수의 수
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitcreatefgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, lsfitstate &state);
void lsfitcreatefgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, lsfitstate &state);


/*************************************************************************
Stopping conditions for nonlinear least squares fitting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsF    -   stopping criterion. Algorithm stops if
                |F(k+1)-F(k)| <= EpsF*max{|F(k)|, |F(k+1)|, 1}
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |v|<=EpsX is fulfilled, where:
                * |.| means Euclidian norm
                * v - scaled step vector, v[i]=dx[i]/s[i]
                * dx - ste pvector, dx=X(k+1)-X(k)
                * s - scaling coefficients set by LSFitSetScale()
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations   is    unlimited.   Only   Levenberg-Marquardt
                iterations  are  counted  (L-BFGS/CG  iterations  are  NOT
                counted because their cost is very low compared to that of
                LM).

NOTE

Passing EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to automatic
stopping criterion selection (according to the scheme used by MINLM unit).


  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
비선형 최소 제곱 피팅을위한 정지 조건.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsF - 중지 기준. 알고리즘 중지되는 경우
                | F (k + 1) -F (k) | <= EpsF * max {| F (k) |, | F (k + 1) |, 1}
    EpsX -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                | v | <= EpsX 조건이 충족됩니다. 여기서,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 스텝 벡터, v [i] = dx [i] / s [i]
                * dx - ste pvector, dx = X (k + 1) -X (k)
                * s - LSFitSetScale ()에 의해 설정된 스케일링 계수
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다. Levenberg-Marquardt 만
                반복 횟수가 계산됩니다 (L-BFGS / CG 반복은 불가능 함).
                그들의 비용이 그것의 비용에 비해 매우 낮기 때문에 계산됩니다.
                LM).
노트
EpsF = 0, EpsX = 0 및 MaxIts = 0 (동시에)을 전달하면 자동
정지 기준 선택 (MINLM 장치에서 사용되는 구성에 따라).
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitsetcond(const lsfitstate &state, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

NOTE: non-zero StpMax leads to moderate  performance  degradation  because
intermediate  step  of  preconditioned L-BFGS optimization is incompatible
with limits on step size.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 최대 스텝 길이를 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    StpMax - 최대 스텝 길이,> = 0. StpMax를 0.0으로 설정하십시오.
                스텝 길이를 제한하고 싶다.
exp ()가 포함 된 대상 함수를 최적화 할 때이 서브 루틴을 사용하십시오.
또는 다른 빠른 성장 기능 및 최적화 알고리즘을 만듭니다
오버 플로우로 이어지는 큰 단계. 이 기능을 사용하면 거부 할 수 있습니다.
너무 큰 단계 (가능한 한 우리를 노출시킵니다.
overflow) x + stp * d에서 실제로 함수 값을 계산하지 않아도된다.
참고 : 0이 아닌 StpMax는 성능 저하를 완화합니다.
사전 조건화 된 L-BFGS 최적화의 중간 단계는 호환되지 않습니다.
단계 크기에 제한이 있습니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
*************************************************** ********************** */
void lsfitsetstpmax(const lsfitstate &state, const double stpmax);


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

When reports are needed, State.C (current parameters) and State.F (current
value of fitting function) are reported.


  -- ALGLIB --
     Copyright 15.08.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
보고서가 필요할 때 State.C (현재 매개 변수) 및 State.F (현재
피팅 함수의 값)이보고됩니다.
  - ALGLIB -
     저작권 15.08.2010 Bochkanov Sergey
*************************************************** ********************** */
void lsfitsetxrep(const lsfitstate &state, const bool needxrep);


/*************************************************************************
This function sets scaling coefficients for underlying optimizer.

ALGLIB optimizers use scaling matrices to test stopping  conditions  (step
size and gradient are scaled before comparison with tolerances).  Scale of
the I-th variable is a translation invariant measure of:
a) "how large" the variable is
b) how large the step should be to make significant changes in the function

Generally, scale is NOT considered to be a form of preconditioner.  But LM
optimizer is unique in that it uses scaling matrix both  in  the  stopping
condition tests and as Marquardt damping factor.

Proper scaling is very important for the algorithm performance. It is less
important for the quality of results, but still has some influence (it  is
easier  to  converge  when  variables  are  properly  scaled, so premature
stopping is possible when very badly scalled variables are  combined  with
relaxed stopping conditions).

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    S       -   array[N], non-zero scaling coefficients
                S[i] may be negative, sign doesn't matter.

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 기본 최적화 프로그램의 크기 조정 계수를 설정합니다.
ALGLIB 최적화 프로그램은 스케일링 매트릭스를 사용하여 정지 조건을 테스트합니다 (단계
크기 및 그래디언트는 공차와 비교하기 전에 크기가 조정됩니다.) 규모
I 번째 변수는 다음에 대한 변환 불변성 측정 값입니다.
a) 변수의 "크기"
b) 함수에서 중요한 변화를 만드는 단계는 얼마나 커야 하는가?
일반적으로 규모는 전제 조건의 한 형태로 간주되지 않습니다. 하지만 LM
최적화 프로그램은 멈춤에서 스케일링 매트릭스를 사용한다는 점에서 독특합니다.
상태 테스트 및 마커드 댐핑 팩터로 사용됩니다.
적절한 스케일링은 알고리즘 성능에 매우 중요합니다. 그것은 적다.
결과의 품질에 중요하지만 여전히 영향력이 있습니다 (
변수가 적절하게 조정될 때 수렴하기 쉽기 때문에 조기에
매우 잘못된 scalled 변수가
완화 된 정지 조건).
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    S - 배열 [N], 0이 아닌 스케일링 계수
                S [i]는 음수 일 수 있습니다. 부호는 중요하지 않습니다.
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
*************************************************** ********************** */
void lsfitsetscale(const lsfitstate &state, const real_1d_array &s);


/*************************************************************************
This function sets boundary constraints for underlying optimizer

Boundary constraints are inactive by default (after initial creation).
They are preserved until explicitly turned off with another SetBC() call.

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    BndL    -   lower bounds, array[K].
                If some (all) variables are unbounded, you may specify
                very small number or -INF (latter is recommended because
                it will allow solver to use better algorithm).
    BndU    -   upper bounds, array[K].
                If some (all) variables are unbounded, you may specify
                very large number or +INF (latter is recommended because
                it will allow solver to use better algorithm).

NOTE 1: it is possible to specify BndL[i]=BndU[i]. In this case I-th
variable will be "frozen" at X[i]=BndL[i]=BndU[i].

NOTE 2: unlike other constrained optimization algorithms, this solver  has
following useful properties:
* bound constraints are always satisfied exactly
* function is evaluated only INSIDE area specified by bound constraints

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 기본 최적화 프로그램의 경계 제약 조건을 설정합니다.
경계 제약 조건은 기본적으로 비활성화됩니다 (초기 생성 후).
다른 SetBC () 호출로 명시 적으로 해제 될 때까지 보존됩니다.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    BndL - 하한, 배열 [K].
                일부 (모든) 변수에 제한이없는 경우,
                매우 작은 수 또는 -INF (후자가 권장됩니다.
                그것은 솔버가 더 나은 알고리즘을 사용할 수있게 해줍니다).
    BndU - 상한, 배열 [K].
                일부 (모든) 변수에 제한이없는 경우,
                매우 큰 숫자 또는 + INF (후자가 권장됩니다.
                그것은 솔버가 더 나은 알고리즘을 사용할 수있게 해줍니다).
비고 1 : BndL [i] = BndU [i]를 지정할 수있다. 이 경우 I-th
변수는 X [i] = BndL [i] = BndU [i]에서 "고정"됩니다.
NOTE 2 : 다른 제약 최적화 알고리즘과는 달리,이 해는 다음과 같다.
유용한 속성 다음 :
* 경계 제약은 항상 정확하게 만족된다.
* 함수는 바인딩 된 제약 조건에 의해 지정된 INSIDE 영역에서만 평가됩니다.
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
*************************************************** ********************** */
void lsfitsetbc(const lsfitstate &state, const real_1d_array &bndl, const real_1d_array &bndu);


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
bool lsfititeration(const lsfitstate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear fitter

These functions accept following parameters:
    state   -   algorithm state
    func    -   callback which calculates function (or merit function)
                value func at given point x
    grad    -   callback which calculates function (or merit function)
                value func and gradient grad at given point x
    hess    -   callback which calculates function (or merit function)
                value func, gradient grad and Hessian hess at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL

NOTES:

1. this algorithm is somewhat unusual because it works with  parameterized
   function f(C,X), where X is a function argument (we  have  many  points
   which are characterized by different  argument  values),  and  C  is  a
   parameter to fit.

   For example, if we want to do linear fit by f(c0,c1,x) = c0*x+c1,  then
   x will be argument, and {c0,c1} will be parameters.

   It is important to understand that this algorithm finds minimum in  the
   space of function PARAMETERS (not arguments), so it  needs  derivatives
   of f() with respect to C, not X.

   In the example above it will need f=c0*x+c1 and {df/dc0,df/dc1} = {x,1}
   instead of {df/dx} = {c0}.

2. Callback functions accept C as the first parameter, and X as the second

3. If  state  was  created  with  LSFitCreateFG(),  algorithm  needs  just
   function   and   its   gradient,   but   if   state   was  created with
   LSFitCreateFGH(), algorithm will need function, gradient and Hessian.

   According  to  the  said  above,  there  ase  several  versions of this
   function, which accept different sets of callbacks.

   This flexibility opens way to subtle errors - you may create state with
   LSFitCreateFGH() (optimization using Hessian), but call function  which
   does not accept Hessian. So when algorithm will request Hessian,  there
   will be no callback to call. In this case exception will be thrown.

   Be careful to avoid such errors because there is no way to find them at
   compile time - you can see them at runtime only.

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey

*************************************************************************/
/* ************************************************ *************************
이 함수 계열은 비선형 조정 함수의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    func - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func
    grad - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func 및 gradient grad
    hess - 함수 (또는 메리트 함수)를 계산하는 콜백
                값 func, 그라디언트 grad 및 주어진 포인트 x에서의 헤센 헤스
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
노트:
1.이 알고리즘은 매개 변수화 된 방식으로 작동하기 때문에 다소 이상합니다.
   함수 f (C, X), 여기서 X는 함수 인수입니다 (우리는 많은 점을 가지고 있습니다
   다른 인수 값으로 특징 지어 짐), C는
   매개 변수가 적합합니다.
   예를 들어, f (c0, c1, x) = c0 * x + c1에 의해 선형 피팅을 수행하려는 경우
   x는 인수가되고 {c0, c1}은 매개 변수가됩니다.
   이 알고리즘이 최소값을 찾는다는 것을 이해하는 것이 중요합니다.
   함수 PARAMETERS (인수가 아님)의 공간이므로 파생물이 필요합니다.
   X가 아니라 C에 대한 f ()
   위의 예제에서 f = c0 * x + c1과 {df / dc0, df / dc1} = {x, 1}
   {df / dx} = {c0} 대신.
2. 콜백 함수는 C를 첫 번째 매개 변수로 사용하고 X를 두 번째 매개 변수로 사용합니다.
3. 상태가 LSFitCreateFG ()로 생성 된 경우 알고리즘은
   함수와 그레디언트가 있지만 상태가
   LSFitCreateFGH (), 알고리즘은 함수, 그라데이션 및 헤 시안을 필요로합니다.
   위에서 말한 바에 따르면이 버전의 여러 버전이 있습니다.
   함수는 서로 다른 콜백 세트를 허용합니다.
   이러한 유연성 덕분에 미묘한 오류가 발생합니다.
   LSFitCreateFGH () (Hessian을 사용하여 최적화)를 호출하지만,
   헤 시안을 받아들이지 않는다. 알고리즘이 헤 시안을 요청할 때, 거기에
   전화 할 콜백이 없습니다. 이 경우 예외가 발생합니다.
   그러한 오류를 피하는 방법은 없기 때문에 이러한 오류를 피하십시오.
   컴파일 타임 - 런타임에만 볼 수 있습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitfit(lsfitstate &state,
    void (*func)(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr),
    void  (*rep)(const real_1d_array &c, double func, void *ptr) = NULL,
    void *ptr = NULL);
void lsfitfit(lsfitstate &state,
    void (*func)(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr),
    void (*grad)(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &c, double func, void *ptr) = NULL,
    void *ptr = NULL);
void lsfitfit(lsfitstate &state,
    void (*func)(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr),
    void (*grad)(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void (*hess)(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, real_2d_array &hess, void *ptr),
    void  (*rep)(const real_1d_array &c, double func, void *ptr) = NULL,
    void *ptr = NULL);


/*************************************************************************
Nonlinear least squares fitting results.

Called after return from LSFitFit().

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    Info    -   completion code:
                    * -7    gradient verification failed.
                            See LSFitSetGradientCheck() for more information.
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
    C       -   array[0..K-1], solution
    Rep     -   optimization report. On success following fields are set:
                * R2                non-adjusted coefficient of determination
                                    (non-weighted)
                * RMSError          rms error on the (X,Y).
                * AvgError          average error on the (X,Y).
                * AvgRelError       average relative error on the non-zero Y
                * MaxError          maximum error
                                    NON-WEIGHTED ERRORS ARE CALCULATED
                * WRMSError         weighted rms error on the (X,Y).

ERRORS IN PARAMETERS

This  solver  also  calculates different kinds of errors in parameters and
fills corresponding fields of report:
* Rep.CovPar        covariance matrix for parameters, array[K,K].
* Rep.ErrPar        errors in parameters, array[K],
                    errpar = sqrt(diag(CovPar))
* Rep.ErrCurve      vector of fit errors - standard deviations of empirical
                    best-fit curve from "ideal" best-fit curve built  with
                    infinite number of samples, array[N].
                    errcurve = sqrt(diag(J*CovPar*J')),
                    where J is Jacobian matrix.
* Rep.Noise         vector of per-point estimates of noise, array[N]

IMPORTANT:  errors  in  parameters  are  calculated  without  taking  into
            account boundary/linear constraints! Presence  of  constraints
            changes distribution of errors, but there is no  easy  way  to
            account for constraints when you calculate covariance matrix.

NOTE:       noise in the data is estimated as follows:
            * for fitting without user-supplied  weights  all  points  are
              assumed to have same level of noise, which is estimated from
              the data
            * for fitting with user-supplied weights we assume that  noise
              level in I-th point is inversely proportional to Ith weight.
              Coefficient of proportionality is estimated from the data.

NOTE:       we apply small amount of regularization when we invert squared
            Jacobian and calculate covariance matrix. It  guarantees  that
            algorithm won't divide by zero  during  inversion,  but  skews
            error estimates a bit (fractional error is about 10^-9).

            However, we believe that this difference is insignificant  for
            all practical purposes except for the situation when you  want
            to compare ALGLIB results with "reference"  implementation  up
            to the last significant digit.

NOTE:       covariance matrix is estimated using  correction  for  degrees
            of freedom (covariances are divided by N-M instead of dividing
            by N).

  -- ALGLIB --
     Copyright 17.08.2009 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
비선형 최소 자승 피팅 결과.
LSFitFit ()에서 반환 된 후에 호출됩니다.
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    정보 - 완료 코드 :
                    * -7 그래디언트 확인에 실패했습니다.
                            자세한 내용은 LSFitSetGradientCheck ()를 참조하십시오.
                    * 1 상대 기능 개선은
                            EpsF.
                    * 2 상대 단계는 EpsX 이상입니다.
                    * 4 그래디언트 표준은 EpsG 이상입니다.
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 정지 조건은 너무 엄격합니다.
                            더 이상의 개선은 불가능하다.
    C- 어레이 [0..K-1], 용액
    담당자 최적화 보고서. 성공시 다음 필드가 설정됩니다.
                * R2 비 조정 계수
                                    (가중치 제외)
                * (X, Y)에서 RMSError rms 오류가 발생했습니다.
                * (X, Y)에 대한 AvgError 평균 오류.
                * AvgRelError 0이 아닌 Y에 대한 평균 상대 오차
                * MaxError 최대 오류
                                    중요하지 않은 오류가 계산됩니다.
                * (X, Y)에서 WRMSError 가중치 rms 오류.
매개 변수의 오류
이 솔버는 또한 매개 변수에서 다양한 종류의 오류를 계산하고
보고서의 해당 필드를 채 웁니다.
* 매개 변수에 대한 Rep.CovPar 공분산 행렬, 배열 [K, K].
매개 변수의 Rep.ErrPar 오류, 배열 [K],
                    errpar = sqrt (diag (CovPar))
* Rep.ErrCurve 적합 오차 벡터 - 경험적 표준 편차
                    내장 된 "이상적인"최적 곡선의 최적 곡선
                    무한 개수의 샘플, 배열 [N].
                    errcurve = sqrt (diag (J * CovPar * J ')),
                    여기서 J는 자 코비안 행렬입니다.
* Rep. 잡음 당 포인트 추정치의 잡음 벡터, 배열 [N]
중요 : 매개 변수의 오류는
            계정 경계 / 선형 제약! 제약 조건의 존재
            오류 배포를 변경하지만 쉬운 방법은 없습니다.
            공분산 행렬을 계산할 때 제약 조건을 설명합니다.
참고 : 데이터의 노이즈는 다음과 같이 추정됩니다.
            * 사용자가 제공하는 무게없이 모든 피팅을 맞추기 위해
              동일한 수준의 잡음을 갖는 것으로 가정하며,
              자료
            * 사용자가 제공 한 무게로 피팅하기 위해 우리는 소음
              레벨은 Ith 가중치에 반비례합니다.
              비례 계수는 데이터로부터 추정됩니다.
참고 : 우리는 제곱을 반전 할 때 소량의 정규화를 적용합니다.
            자 코비안 (Jacobian)을 선택하고 공분산 행렬을 계산합니다. 그것은
            알고리즘은 반전시 0으로 나누지 않지만 비뚤어 짐
            오류 추정 조금 (분수 오류 약 10 ^ -9)입니다.
            그러나 우리는이 차이가
            원하는 상황을 제외한 모든 실제적인 목적
            ALGLIB 결과를 "참조"구현과 비교
            마지막 유효 숫자로
참고 : 공분산 행렬은도에 대한 보정을 사용하여 추정됩니다.
            자유의 (공분산은 나누기 대신에 NM으로 나누어진다.
            N에 의해).
  - ALGLIB -
     Bochkanov Sergey의 Copyright 17.08.2009
*************************************************** ********************** */
void lsfitresults(const lsfitstate &state, ae_int_t &info, real_1d_array &c, lsfitreport &rep);


/*************************************************************************
This  subroutine  turns  on  verification  of  the  user-supplied analytic
gradient:
* user calls this subroutine before fitting begins
* LSFitFit() is called
* prior to actual fitting, for  each  point  in  data  set  X_i  and  each
  component  of  parameters  being  fited C_j algorithm performs following
  steps:
  * two trial steps are made to C_j-TestStep*S[j] and C_j+TestStep*S[j],
    where C_j is j-th parameter and S[j] is a scale of j-th parameter
  * if needed, steps are bounded with respect to constraints on C[]
  * F(X_i|C) is evaluated at these trial points
  * we perform one more evaluation in the middle point of the interval
  * we  build  cubic  model using function values and derivatives at trial
    points and we compare its prediction with actual value in  the  middle
    point
  * in case difference between prediction and actual value is higher  than
    some predetermined threshold, algorithm stops with completion code -7;
    Rep.VarIdx is set to index of the parameter with incorrect derivative.
* after verification is over, algorithm proceeds to the actual optimization.

NOTE 1: verification needs N*K (points count * parameters count)  gradient
        evaluations. It is very costly and you should use it only for  low
        dimensional  problems,  when  you  want  to  be  sure  that you've
        correctly calculated analytic derivatives. You should not  use  it
        in the production code  (unless  you  want  to  check  derivatives
        provided by some third party).

NOTE 2: you  should  carefully  choose  TestStep. Value which is too large
        (so large that function behaviour is significantly non-cubic) will
        lead to false alarms. You may use  different  step  for  different
        parameters by means of setting scale with LSFitSetScale().

NOTE 3: this function may lead to false positives. In case it reports that
        I-th  derivative was calculated incorrectly, you may decrease test
        step  and  try  one  more  time  - maybe your function changes too
        sharply  and  your  step  is  too  large for such rapidly chanding
        function.

NOTE 4: this function works only for optimizers created with LSFitCreateWFG()
        or LSFitCreateFG() constructors.

INPUT PARAMETERS:
    State       -   structure used to store algorithm state
    TestStep    -   verification step:
                    * TestStep=0 turns verification off
                    * TestStep>0 activates verification

  -- ALGLIB --
     Copyright 15.06.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 사용자가 제공 한 분석의 검증을 켭니다.
구배:
* 사용자가 피팅이 시작되기 전에이 서브 루틴을 호출합니다.
* LSFitFit ()가 호출되었습니다.
* 실제 피팅에 앞서, 데이터 세트 X_i의 각 포인트에 대해
  C_j 알고리즘은 다음과 같이 수행됩니다.
  단계 :
  * C_j-TestStep * S [j]와 C_j + TestStep * S [j]에 대해 두 가지 시험 단계가 수행됩니다.
    여기서 C_j는 j 번째 매개 변수이고 S [j]는 j 번째 매개 변수의 눈금
  * 필요한 경우 단계는 C []의 제약 조건에 따라 제한됩니다.
  * F (X_i | C)는 이러한 시험 포인트에서 평가됩니다.
  * 간격의 중간 지점에서 또 하나의 평가를 수행합니다.
  * 우리는 함수 값과 파생 상품을 사용하여 삼차원 모델을 시험해 보았다.
    우리는 예측치를 중간의 실제 값과 비교합니다
    포인트
  * 예상 값과 실제 값의 차이가
    소정의 소정의 임계 값, 알고리즘은 완료 코드 -7로 정지한다;
    Rep.VarIdx가 잘못된 파생어로 매개 변수의 인덱스로 설정됩니다.
* 검증이 끝나면 알고리즘은 실제 최적화로 진행합니다.
비고 1 : 검증에는 N * K (포인트 카운트 * 파라미터 카운트) 그라디언트가 필요하다.
        평가. 그것은 매우 비싸고 당신은 낮은 것에 대해서만 사용해야합니다.
        3 차원 문제, 당신이 당신이
        올바르게 계산 된 파생 상품. 너는 그것을 사용하면 안된다.
        생산 코드에서 (파생 상품을 확인하고 싶지 않다면)
        제 3 자 제공).
참고 2 : TestStep을 신중하게 선택해야합니다. 너무 큰 값
        (너무 커서 함수의 동작은 상당히 비 큐빅이다.)
        거짓 경보로 연결됩니다. 다른 단계를 사용할 수도 있습니다.
        LSFitSetScale ()을 사용하여 축척을 설정하여 매개 변수를 설정합니다.
참고 3 :이 기능은 위양성을 유발할 수 있습니다. 보고서에
        I 차수 미분이 잘못 계산되었으므로 테스트를 줄일 수 있습니다.
        한 번 더 시도해보십시오. 아마도 기능이 변경 될 수도 있습니다.
        급격하게 그리고 당신의 발걸음이 그렇게 급속히 챈드하기에는 너무 큽니다.
        기능.
참고 4 :이 함수는 LSFitCreateWFG ()로 만든 최적화 프로그램에서만 작동합니다.
        또는 LSFitCreateFG () 생성자.
입력 매개 변수 :
    상태 - 알고리즘 상태를 저장하는 데 사용되는 구조
    TestStep - 확인 단계 :
                    * TestStep = 0으로 설정하면 인증이 해제됩니다.
                    * TestStep> 0으로 인증이 활성화됩니다.
  - ALGLIB -
     저작권 15.06.2012 Bochkanov Sergey
*************************************************** ********************** */
void lsfitsetgradientcheck(const lsfitstate &state, const double teststep);

/*************************************************************************
This function  builds  non-periodic 2-dimensional parametric spline  which
starts at (X[0],Y[0]) and ends at (X[N-1],Y[N-1]).

INPUT PARAMETERS:
    XY  -   points, array[0..N-1,0..1].
            XY[I,0:1] corresponds to the Ith point.
            Order of points is important!
    N   -   points count, N>=5 for Akima splines, N>=2 for other types  of
            splines.
    ST  -   spline type:
            * 0     Akima spline
            * 1     parabolically terminated Catmull-Rom spline (Tension=0)
            * 2     parabolically terminated cubic spline
    PT  -   parameterization type:
            * 0     uniform
            * 1     chord length
            * 2     centripetal

OUTPUT PARAMETERS:
    P   -   parametric spline interpolant


NOTES:
* this function  assumes  that  there all consequent points  are distinct.
  I.e. (x0,y0)<>(x1,y1),  (x1,y1)<>(x2,y2),  (x2,y2)<>(x3,y3)  and  so on.
  However, non-consequent points may coincide, i.e. we can  have  (x0,y0)=
  =(x2,y2).

  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 비주기적인 2 차원 파라 메트릭 스플라인을 만듭니다.
(X [0], Y [0])에서 시작하여 (X [N-1], Y [N-1])에서 끝납니다.
입력 매개 변수 :
    XY - 점, 배열 [0..N-1,0..1].
            XY [I, 0 : 1]은 I 포인트에 해당합니다.
            포인트 순서가 중요합니다!
    N 점 수, Akima 스플라인의 경우 N> = 5, 다른 유형의 경우 N> = 2
            스플라인.
    ST - 스플라인 유형 :
            * 0 아키마 스플라인
            * 1 Catmull-Rom 스플라인 포락선 (장력 = 0)
            * 2 파라볼 릭 종료 입방 스플라인
    PT - 매개 변수화 유형 :
            * 0 유니폼
            * 1 코드 길이
            * 2 구심
출력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
노트:
*이 함수는 모든 결과 포인트가 구별되어 있다고 가정합니다.
  즉 (x0, y0) <> (x1, y1), (x1, y1) <> (x2, y2), (x2, y2) <> (x3, y3) 등이다.
  그러나 비 연속적인 점들이 일치 할 수 있습니다. 즉, (x0, y0) =
  = (x2, y2)이다.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2build(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline2interpolant &p);


/*************************************************************************
This function  builds  non-periodic 3-dimensional parametric spline  which
starts at (X[0],Y[0],Z[0]) and ends at (X[N-1],Y[N-1],Z[N-1]).

Same as PSpline2Build() function, but for 3D, so we  won't  duplicate  its
description here.

  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 비주기적인 3 차원 파라 메트릭 스플라인을 만듭니다.
(X [0], Y [0], Z [0])에서 시작하여 (X [N-1], Y [N-1], Z [N-1])에서 끝난다.
PSpline2Build () 함수와 동일하지만 3D 용이므로 복제하지 않습니다.
여기에 설명.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3build(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline3interpolant &p);


/*************************************************************************
This  function  builds  periodic  2-dimensional  parametric  spline  which
starts at (X[0],Y[0]), goes through all points to (X[N-1],Y[N-1]) and then
back to (X[0],Y[0]).

INPUT PARAMETERS:
    XY  -   points, array[0..N-1,0..1].
            XY[I,0:1] corresponds to the Ith point.
            XY[N-1,0:1] must be different from XY[0,0:1].
            Order of points is important!
    N   -   points count, N>=3 for other types of splines.
    ST  -   spline type:
            * 1     Catmull-Rom spline (Tension=0) with cyclic boundary conditions
            * 2     cubic spline with cyclic boundary conditions
    PT  -   parameterization type:
            * 0     uniform
            * 1     chord length
            * 2     centripetal

OUTPUT PARAMETERS:
    P   -   parametric spline interpolant


NOTES:
* this function  assumes  that there all consequent points  are  distinct.
  I.e. (x0,y0)<>(x1,y1), (x1,y1)<>(x2,y2),  (x2,y2)<>(x3,y3)  and  so  on.
  However, non-consequent points may coincide, i.e. we can  have  (x0,y0)=
  =(x2,y2).
* last point of sequence is NOT equal to the first  point.  You  shouldn't
  make curve "explicitly periodic" by making them equal.

  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는주기적인 2 차원 매개 변수 스플라인을 만듭니다.
(X [0], Y [0])에서 시작하여 모든 점을 통과하여 (X [N-1], Y [N-1])
back to (X [0], Y [0]).
입력 매개 변수 :
    XY - 점, 배열 [0..N-1,0..1].
            XY [I, 0 : 1]은 I 포인트에 해당합니다.
            XY [N-1,0 : 1]은 XY [0,0 : 1]과 달라야합니다.
            포인트 순서가 중요합니다!
    다른 유형의 스플라인의 경우 N 포인트 수, N> = 3입니다.
    ST - 스플라인 유형 :
            * 1 순환 경계 조건이있는 Catmull-Rom 스플라인 (인장 = 0)
            순환 경계 조건을 갖는 * 2 입체 스플라인
    PT - 매개 변수화 유형 :
            * 0 유니폼
            * 1 코드 길이
            * 2 구심
출력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
노트:
*이 함수는 모든 결과 포인트가 구별되어 있다고 가정합니다.
  즉 (x0, y0) <> (x1, y1), (x1, y1) <> (x2, y2), (x2, y2) <> (x3, y3) 등이다.
  그러나 비 연속적인 점들이 일치 할 수 있습니다. 즉, (x0, y0) =
  = (x2, y2)이다.
* 순서의 마지막 점은 첫 번째 점과 동일하지 않습니다. 너는 안된다.
  그것들을 동일하게함으로써 "명시 적으로주기적인"곡선을 만든다.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2buildperiodic(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline2interpolant &p);


/*************************************************************************
This  function  builds  periodic  3-dimensional  parametric  spline  which
starts at (X[0],Y[0],Z[0]), goes through all points to (X[N-1],Y[N-1],Z[N-1])
and then back to (X[0],Y[0],Z[0]).

Same as PSpline2Build() function, but for 3D, so we  won't  duplicate  its
description here.

  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는주기적인 3 차원 매개 변수 스플라인을 빌드합니다.
(X [0], Y [0], Z [0])에서 시작하여 모든 점을 (X [N-1], Y [N-1], Z [N-1])
(X [0], Y [0], Z [0])로 돌아 간다.
PSpline2Build () 함수와 동일하지만 3D 용이므로 복제하지 않습니다.
여기에 설명.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3buildperiodic(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline3interpolant &p);


/*************************************************************************
This function returns vector of parameter values correspoding to points.

I.e. for P created from (X[0],Y[0])...(X[N-1],Y[N-1]) and U=TValues(P)  we
have
    (X[0],Y[0]) = PSpline2Calc(P,U[0]),
    (X[1],Y[1]) = PSpline2Calc(P,U[1]),
    (X[2],Y[2]) = PSpline2Calc(P,U[2]),
    ...

INPUT PARAMETERS:
    P   -   parametric spline interpolant

OUTPUT PARAMETERS:
    N   -   array size
    T   -   array[0..N-1]


NOTES:
* for non-periodic splines U[0]=0, U[0]<U[1]<...<U[N-1], U[N-1]=1
* for periodic splines     U[0]=0, U[0]<U[1]<...<U[N-1], U[N-1]<1

  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 점에 해당하는 매개 변수 값의 벡터를 반환합니다.
즉, (X [0], Y [0]) ... (X [N-1], Y [N-1]) 및 U = TValues ​​(P)로부터 생성 된 P
있다
    (X [0], Y [0]) = PSpline2Calc (P, U [0]),
    (X [1], Y [1]) = PSpline2Calc (P, U [1]),
    (X [2], Y [2]) = PSpline2Calc (P, U [2]),
    ...
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
출력 매개 변수 :
    N - 배열 크기
    T- 어레이 [0..N-1]
노트:
* 비 정기 스플라인 U [0] = 0, U [0] <U [1] <... <U [N-1], U [N-1] = 1
*주기 스프 라인 U [0] = 0, U [0] <U [1] <... <U [N-1], U [N-1] <1
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2parametervalues(const pspline2interpolant &p, ae_int_t &n, real_1d_array &t);


/*************************************************************************
This function returns vector of parameter values correspoding to points.

Same as PSpline2ParameterValues(), but for 3D.

  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 점에 해당하는 매개 변수 값의 벡터를 반환합니다.
PSpline2ParameterValues ​​()와 동일하지만 3D에 해당합니다.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3parametervalues(const pspline3interpolant &p, ae_int_t &n, real_1d_array &t);


/*************************************************************************
This function  calculates  the value of the parametric spline for a  given
value of parameter T

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X   -   X-position
    Y   -   Y-position


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 주어진 파라 메트릭 스플라인의 값을 계산합니다.
파라미터 T의 값
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - X 위치
    Y - Y 위치
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2calc(const pspline2interpolant &p, const double t, double &x, double &y);


/*************************************************************************
This function  calculates  the value of the parametric spline for a  given
value of parameter T.

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X   -   X-position
    Y   -   Y-position
    Z   -   Z-position


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 주어진 파라 메트릭 스플라인의 값을 계산합니다.
파라미터 T의 값.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - X 위치
    Y - Y 위치
    Z - Z 위치
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3calc(const pspline3interpolant &p, const double t, double &x, double &y, double &z);


/*************************************************************************
This function  calculates  tangent vector for a given value of parameter T

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X    -   X-component of tangent vector (normalized)
    Y    -   Y-component of tangent vector (normalized)

NOTE:
    X^2+Y^2 is either 1 (for non-zero tangent vector) or 0.


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 매개 변수 T의 주어진 값에 대한 접선 벡터를 계산합니다.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - 접선 벡터의 X- 성분 (정규화)
    Y - 접선 벡터의 Y 성분 (정규화)
노트:
    X ^ 2 + Y ^ 2는 1 (0이 아닌 탄젠트 벡터의 경우) 또는 0입니다.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2tangent(const pspline2interpolant &p, const double t, double &x, double &y);


/*************************************************************************
This function  calculates  tangent vector for a given value of parameter T

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X    -   X-component of tangent vector (normalized)
    Y    -   Y-component of tangent vector (normalized)
    Z    -   Z-component of tangent vector (normalized)

NOTE:
    X^2+Y^2+Z^2 is either 1 (for non-zero tangent vector) or 0.


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 매개 변수 T의 주어진 값에 대한 접선 벡터를 계산합니다.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - 접선 벡터의 X- 성분 (정규화)
    Y - 접선 벡터의 Y 성분 (정규화)
    Z - 접선 벡터의 Z- 성분 (정규화)
노트:
    X ^ 2 + Y ^ 2 + Z ^ 2는 1 (0이 아닌 탄젠트 벡터의 경우) 또는 0입니다.
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3tangent(const pspline3interpolant &p, const double t, double &x, double &y, double &z);


/*************************************************************************
This function calculates derivative, i.e. it returns (dX/dT,dY/dT).

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X   -   X-value
    DX  -   X-derivative
    Y   -   Y-value
    DY  -   Y-derivative


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 미분을 계산합니다. 즉, (dX / dT, dY / dT)를 반환합니다.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - X 값
    DX - X 미분
    Y - Y 값
    DY - Y 파생 상품
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2diff(const pspline2interpolant &p, const double t, double &x, double &dx, double &y, double &dy);


/*************************************************************************
This function calculates derivative, i.e. it returns (dX/dT,dY/dT,dZ/dT).

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X   -   X-value
    DX  -   X-derivative
    Y   -   Y-value
    DY  -   Y-derivative
    Z   -   Z-value
    DZ  -   Z-derivative


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 미분을 계산합니다. 즉, (dX / dT, dY / dT, dZ / dT)를 반환합니다.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - X 값
    DX - X 미분
    Y - Y 값
    DY - Y 파생 상품
    Z - Z 값
    DZ - Z 미분
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3diff(const pspline3interpolant &p, const double t, double &x, double &dx, double &y, double &dy, double &z, double &dz);


/*************************************************************************
This function calculates first and second derivative with respect to T.

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X   -   X-value
    DX  -   derivative
    D2X -   second derivative
    Y   -   Y-value
    DY  -   derivative
    D2Y -   second derivative


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 T에 대해 1 차 및 2 차 미분을 계산합니다.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - X 값
    DX - 파생물
    D2X - 2 차 미분
    Y - Y 값
    DY - 파생 상품
    D2Y - 2 차 미분
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline2diff2(const pspline2interpolant &p, const double t, double &x, double &dx, double &d2x, double &y, double &dy, double &d2y);


/*************************************************************************
This function calculates first and second derivative with respect to T.

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    T   -   point:
            * T in [0,1] corresponds to interval spanned by points
            * for non-periodic splines T<0 (or T>1) correspond to parts of
              the curve before the first (after the last) point
            * for periodic splines T<0 (or T>1) are projected  into  [0,1]
              by making T=T-floor(T).

OUTPUT PARAMETERS:
    X   -   X-value
    DX  -   derivative
    D2X -   second derivative
    Y   -   Y-value
    DY  -   derivative
    D2Y -   second derivative
    Z   -   Z-value
    DZ  -   derivative
    D2Z -   second derivative


  -- ALGLIB PROJECT --
     Copyright 28.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 T에 대해 1 차 및 2 차 미분을 계산합니다.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    T- 포인트 :
            * [0,1]의 T는 점들 사이의 간격에 해당합니다.
            * 비주기 스프 라인 T <0 (또는 T> 1)은
              첫 번째 (마지막 점 이후) 지점 앞의 곡선
            *주기 스프 라인 T <0 (또는 T> 1)은 [0,1]
              T = T-floor (T)로 만듦.
출력 매개 변수 :
    X - X 값
    DX - 파생물
    D2X - 2 차 미분
    Y - Y 값
    DY - 파생 상품
    D2Y - 2 차 미분
    Z - Z 값
    DZ - 파생 상품
    D2Z - 2 차 미분
  - ALGLIB 프로젝트 -
     Copyright 28.05.2010 Bochkanov Sergey
*************************************************** ********************** */
void pspline3diff2(const pspline3interpolant &p, const double t, double &x, double &dx, double &d2x, double &y, double &dy, double &d2y, double &z, double &dz, double &d2z);


/*************************************************************************
This function  calculates  arc length, i.e. length of  curve  between  t=a
and t=b.

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    A,B -   parameter values corresponding to arc ends:
            * B>A will result in positive length returned
            * B<A will result in negative length returned

RESULT:
    length of arc starting at T=A and ending at T=B.


  -- ALGLIB PROJECT --
     Copyright 30.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 호 길이, 즉 t = a 사이의 곡선 길이를 계산합니다.
그리고 t = b.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    A, B - 호 끝에 해당하는 매개 변수 값 :
            * B> A는 양의 길이를 반환합니다.
            * B <A는 음의 길이를 반환합니다.
결과:
    T = A에서 시작하여 T = B에서 끝나는 호의 길이.
  - ALGLIB 프로젝트 -
     Copyright 30.05.2010 Bochkanov Sergey
*************************************************** ********************** */
double pspline2arclength(const pspline2interpolant &p, const double a, const double b);


/*************************************************************************
This function  calculates  arc length, i.e. length of  curve  between  t=a
and t=b.

INPUT PARAMETERS:
    P   -   parametric spline interpolant
    A,B -   parameter values corresponding to arc ends:
            * B>A will result in positive length returned
            * B<A will result in negative length returned

RESULT:
    length of arc starting at T=A and ending at T=B.


  -- ALGLIB PROJECT --
     Copyright 30.05.2010 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 호 길이, 즉 t = a 사이의 곡선 길이를 계산합니다.
그리고 t = b.
입력 매개 변수 :
    P - 파라 메트릭 스플라인 보간
    A, B - 호 끝에 해당하는 매개 변수 값 :
            * B> A는 양의 길이를 반환합니다.
            * B <A는 음의 길이를 반환합니다.
결과:
    T = A에서 시작하여 T = B에서 끝나는 호의 길이.
  - ALGLIB 프로젝트 -
     Copyright 30.05.2010 Bochkanov Sergey
*************************************************** ********************** */
double pspline3arclength(const pspline3interpolant &p, const double a, const double b);

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
/* ************************************************ *************************
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
*************************************************** ********************** */
void rbfserialize(rbfmodel &obj, std::string &s_out);


/*************************************************************************
This function unserializes data structure from string.
*************************************************************************/
/* ************************************************ *************************
이 함수는 문자열에서 데이터 구조를 unserializes.
*************************************************** ********************** */
void rbfunserialize(std::string &s_in, rbfmodel &obj);


/*************************************************************************
This function creates RBF  model  for  a  scalar (NY=1)  or  vector (NY>1)
function in a NX-dimensional space (NX=2 or NX=3).

Newly created model is empty. It can be used for interpolation right after
creation, but it just returns zeros. You have to add points to the  model,
tune interpolation settings, and then  call  model  construction  function
RBFBuildModel() which will update model according to your specification.

USAGE:
1. User creates model with RBFCreate()
2. User adds dataset with RBFSetPoints() (points do NOT have to  be  on  a
   regular grid)
3. (OPTIONAL) User chooses polynomial term by calling:
   * RBFLinTerm() to set linear term
   * RBFConstTerm() to set constant term
   * RBFZeroTerm() to set zero term
   By default, linear term is used.
4. User chooses specific RBF algorithm to use: either QNN (RBFSetAlgoQNN)
   or ML (RBFSetAlgoMultiLayer).
5. User calls RBFBuildModel() function which rebuilds model  according  to
   the specification
6. User may call RBFCalc() to calculate model value at the specified point,
   RBFGridCalc() to  calculate   model  values at the points of the regular
   grid. User may extract model coefficients with RBFUnpack() call.

INPUT PARAMETERS:
    NX      -   dimension of the space, NX=2 or NX=3
    NY      -   function dimension, NY>=1

OUTPUT PARAMETERS:
    S       -   RBF model (initially equals to zero)

NOTE 1: memory requirements. RBF models require amount of memory  which is
        proportional  to  the  number  of data points. Memory is allocated
        during model construction, but most of this memory is freed  after
        model coefficients are calculated.

        Some approximate estimates for N centers with default settings are
        given below:
        * about 250*N*(sizeof(double)+2*sizeof(int)) bytes  of  memory  is
          needed during model construction stage.
        * about 15*N*sizeof(double) bytes is needed after model is built.
        For example, for N=100000 we may need 0.6 GB of memory  to  build
        model, but just about 0.012 GB to store it.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 스칼라 (NY = 1) 또는 벡터 (NY> 1)에 대한 RBF 모델을 만듭니다.
기능을 NX 차원 공간 (NX = 2 또는 NX = 3)에서 사용할 수 있습니다.
새로 생성 된 모델이 비어 있습니다. 다음 보간 직후에 사용할 수 있습니다.
생성하지만 단지 0을 반환합니다. 모델에 포인트를 추가해야합니다.
보간 설정을 조정 한 다음 모델 구성 함수를 호출합니다.
RBFBuildModel ()은 사양에 따라 모델을 업데이트합니다.
용법:
1. 사용자가 RBFCreate ()로 모델을 생성합니다.
2. 사용자가 RBFSetPoints ()를 사용하여 데이터 세트를 추가합니다 (포인트는
   정규 그리드)
3. (선택 사항) 사용자는 다음을 호출하여 다항식 항을 선택합니다.
   * 선형 항을 설정하는 RBFLinTerm ()
   * 상수를 설정하는 RBFConstTerm ()
   * 제로 기간을 설정하는 RBFZeroTerm ()
   기본적으로 선형 항이 사용됩니다.
4. 사용자가 사용할 특정 RBF 알고리즘을 선택합니다 : QNN (RBFSetAlgoQNN)
   또는 ML (RBFSetAlgoMultiLayer).
5. 사용자는 모델을 다시 빌드하는 RBFBuildModel () 함수를 호출합니다.
   명세
6. 사용자는 지정된 점에서 모델 값을 계산하기 위해 RBFCalc ()를 호출 할 수 있습니다.
   RBFGridCalc ()를 사용하여 일반 지점의 모델 값을 계산합니다.
   그리드. 사용자는 RBFUnpack () 호출로 모델 계수를 추출 할 수 있습니다.
입력 매개 변수 :
    NX - 공간 치수, NX = 2 또는 NX = 3
    NY - 함수 차원, NY> = 1
출력 매개 변수 :
    S - RBF 모델 (초기에는 0 임)
참고 1 : 메모리 요구 사항. RBF 모델은
        데이터 포인트의 수에 비례합니다. 메모리가 할당 됨
        모델을 만드는 동안이 메모리의 대부분은
        모델 계수가 계산됩니다.
        기본 설정이있는 N 개의 센터에 대한 대략적인 추정치는 다음과 같습니다.
        아래에 주어진다 :
        * 약 250 * N * (sizeof (double) + 2 * sizeof (int)) 바이트의 메모리가 있습니다.
          모델 제작 단계에서 필요합니다.
        * 모델 제작 후 약 15 * N * sizeof (double) 바이트가 필요합니다.
        예를 들어, N = 100000의 경우 빌드하는 데 0.6GB의 메모리가 필요할 수 있습니다.
        모델이지만 0.012GB 정도만 저장할 수 있습니다.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfcreate(const ae_int_t nx, const ae_int_t ny, rbfmodel &s);


/*************************************************************************
This function adds dataset.

This function overrides results of the previous calls, i.e. multiple calls
of this function will result in only the last set being added.

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call.
    XY      -   points, array[N,NX+NY]. One row corresponds to  one  point
                in the dataset. First NX elements  are  coordinates,  next
                NY elements are function values. Array may  be larger than
                specific,  in  this  case  only leading [N,NX+NY] elements
                will be used.
    N       -   number of points in the dataset

After you've added dataset and (optionally) tuned algorithm  settings  you
should call RBFBuildModel() in order to build a model for you.

NOTE: this   function  has   some   serialization-related  subtleties.  We
      recommend you to study serialization examples from ALGLIB  Reference
      Manual if you want to perform serialization of your models.


  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 데이터 집합을 추가합니다.
이 함수는 이전 호출의 결과, 즉 여러 호출을 무시합니다.
이 기능을 사용하면 마지막 세트 만 추가됩니다.
입력 매개 변수 :
    S - RBF 모델 (RBFCreate () 호출로 초기화 됨).
    XY - 점, 배열 [N, NX + NY]. 한 행은 한 점에 해당합니다.
                데이터 세트에서. 첫 번째 NX 요소는 좌표이며, 다음
                NY 요소는 함수 값입니다. 배열은 다음보다 클 수 있습니다.
                이 경우에는 [N, NX + NY] 요소 만 이끌어냅니다
                사용하게 될 것이다.
    N - 데이터 세트의 포인트 수
데이터 집합 및 (선택적으로) 조정 된 알고리즘 설정을 추가 한 후에는
모델을 빌드하기 위해 RBFBuildModel ()을 호출해야합니다.
참고 :이 함수에는 몇 가지 serialization 관련 미묘한 차이가 있습니다. 우리
      ALGLIB Reference에서 직렬화 예제를 공부하도록 권장합니다.
      모델의 직렬화를 수행하려면 수동으로하십시오.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfsetpoints(const rbfmodel &s, const real_2d_array &xy, const ae_int_t n);
void rbfsetpoints(const rbfmodel &s, const real_2d_array &xy);


/*************************************************************************
This  function  sets  RBF interpolation algorithm. ALGLIB supports several
RBF algorithms with different properties.

This algorithm is called RBF-QNN and  it  is  good  for  point  sets  with
following properties:
a) all points are distinct
b) all points are well separated.
c) points  distribution  is  approximately  uniform.  There is no "contour
   lines", clusters of points, or other small-scale structures.

Algorithm description:
1) interpolation centers are allocated to data points
2) interpolation radii are calculated as distances to the  nearest centers
   times Q coefficient (where Q is a value from [0.75,1.50]).
3) after  performing (2) radii are transformed in order to avoid situation
   when single outlier has very large radius and  influences  many  points
   across all dataset. Transformation has following form:
       new_r[i] = min(r[i],Z*median(r[]))
   where r[i] is I-th radius, median()  is a median  radius across  entire
   dataset, Z is user-specified value which controls amount  of  deviation
   from median radius.

When (a) is violated,  we  will  be unable to build RBF model. When (b) or
(c) are violated, model will be built, but interpolation quality  will  be
low. See http://www.alglib.net/interpolation/ for more information on this
subject.

This algorithm is used by default.

Additional Q parameter controls smoothness properties of the RBF basis:
* Q<0.75 will give perfectly conditioned basis,  but  terrible  smoothness
  properties (RBF interpolant will have sharp peaks around function values)
* Q around 1.0 gives good balance between smoothness and condition number
* Q>1.5 will lead to badly conditioned systems and slow convergence of the
  underlying linear solver (although smoothness will be very good)
* Q>2.0 will effectively make optimizer useless because it won't  converge
  within reasonable amount of iterations. It is possible to set such large
  Q, but it is advised not to do so.

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call
    Q       -   Q parameter, Q>0, recommended value - 1.0
    Z       -   Z parameter, Z>0, recommended value - 5.0

NOTE: this   function  has   some   serialization-related  subtleties.  We
      recommend you to study serialization examples from ALGLIB  Reference
      Manual if you want to perform serialization of your models.


  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 RBF 보간 알고리즘을 설정합니다. ALGLIB는 몇 가지를 지원합니다
다른 속성을 가진 RBF 알고리즘.
이 알고리즘은 RBF-QNN이라고하며,
다음 속성 :
a) 모든 점은 뚜렷하다.
b) 모든 점들은 잘 분리되어있다.
c) 점 분포는 거의 균일하다. '윤곽선이 없습니다.
   라인 ", 포인트 클러스터 또는 기타 소규모 구조.
알고리즘 설명 :
1) 보간 중심을 데이터 포인트에 할당
2) 보간 반경은 가장 가까운 중심까지의 거리로 계산됩니다
   시간 Q 계수 (여기서 Q는 [0.75,1.50]의 값).
3) (2) 반지름을 수행 한 후 상황을 피하기 위해 변환됩니다
   단일 이상치가 매우 큰 반경을 갖고 많은 점에 영향을 미칠 때
   모든 데이터 세트에서 변환 형식은 다음과 같습니다.
       new_r [i] = min (r [i], Z * median (r []))
   여기서 r [i]는 I 번째 반지름, median ()은 전체 반지름의 중앙 반지름
   데이터 세트에서 Z는 편차의 양을 제어하는 ​​사용자 지정 값입니다.
   중앙 반경에서.
(a)를 위반하면 RBF 모델을 구축 할 수 없습니다. (b) 또는
(c)를 위반하면 모델이 만들어 지지만 보간 품질은
낮은. 이에 대한 더 자세한 정보는 http://www.alglib.net/interpolation/을 참조하십시오.
제목.
이 알고리즘은 기본적으로 사용됩니다.
추가 Q 매개 변수는 RBF 기초의 부드러움 특성을 제어합니다.
* Q <0.75는 완벽하게 컨디셔닝 된 기초를 제공하지만 끔찍한 부드러움
  속성 (RBF 보간은 함수 값 주위에 날카로운 피크를 가짐)
* Q 약 1.0은 매끈함과 조건 수 사이에 좋은 균형을 제공합니다.
* Q> 1.5는 나쁘게 컨디셔닝 된 시스템과
  기본 선형 솔버 (부드러움은 아주 좋음)
* Q> 2.0은 효과적으로 수렴하지 않기 때문에 유용하지 않게 만듭니다.
  합리적인 양의 반복. 그러한 큰 값을 설정할 수 있습니다.
  Q,하지만 그렇게하지 않는 것이 좋습니다.
입력 매개 변수 :
    RBFCreate () 호출로 초기화 된 S - RBF 모델
    Q - Q 매개 변수, Q> 0, 권장 값 - 1.0
    Z - Z 매개 변수, Z> 0, 권장 값 - 5.0
참고 :이 함수에는 몇 가지 serialization 관련 미묘한 차이가 있습니다. 우리
      ALGLIB Reference에서 직렬화 예제를 공부하도록 권장합니다.
      모델의 직렬화를 수행하려면 수동으로하십시오.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfsetalgoqnn(const rbfmodel &s, const double q, const double z);
void rbfsetalgoqnn(const rbfmodel &s);


/*************************************************************************
This  function  sets  RBF interpolation algorithm. ALGLIB supports several
RBF algorithms with different properties.

This  algorithm is called RBF-ML. It builds  multilayer  RBF  model,  i.e.
model with subsequently decreasing  radii,  which  allows  us  to  combine
smoothness (due to  large radii of  the first layers) with  exactness (due
to small radii of the last layers) and fast convergence.

Internally RBF-ML uses many different  means  of acceleration, from sparse
matrices  to  KD-trees,  which  results in algorithm whose working time is
roughly proportional to N*log(N)*Density*RBase^2*NLayers,  where  N  is  a
number of points, Density is an average density if points per unit of  the
interpolation space, RBase is an initial radius, NLayers is  a  number  of
layers.

RBF-ML is good for following kinds of interpolation problems:
1. "exact" problems (perfect fit) with well separated points
2. least squares problems with arbitrary distribution of points (algorithm
   gives  perfect  fit  where it is possible, and resorts to least squares
   fit in the hard areas).
3. noisy problems where  we  want  to  apply  some  controlled  amount  of
   smoothing.

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call
    RBase   -   RBase parameter, RBase>0
    NLayers -   NLayers parameter, NLayers>0, recommended value  to  start
                with - about 5.
    LambdaV -   regularization value, can be useful when  solving  problem
                in the least squares sense.  Optimal  lambda  is  problem-
                dependent and require trial and error. In our  experience,
                good lambda can be as large as 0.1, and you can use  0.001
                as initial guess.
                Default  value  - 0.01, which is used when LambdaV is  not
                given.  You  can  specify  zero  value,  but  it  is   not
                recommended to do so.

TUNING ALGORITHM

In order to use this algorithm you have to choose three parameters:
* initial radius RBase
* number of layers in the model NLayers
* regularization coefficient LambdaV

Initial radius is easy to choose - you can pick any number  several  times
larger  than  the  average  distance between points. Algorithm won't break
down if you choose radius which is too large (model construction time will
increase, but model will be built correctly).

Choose such number of layers that RLast=RBase/2^(NLayers-1)  (radius  used
by  the  last  layer)  will  be  smaller than the typical distance between
points.  In  case  model  error  is  too large, you can increase number of
layers.  Having  more  layers  will make model construction and evaluation
proportionally slower, but it will allow you to have model which precisely
fits your data. From the other side, if you want to  suppress  noise,  you
can DECREASE number of layers to make your model less flexible.

Regularization coefficient LambdaV controls smoothness of  the  individual
models built for each layer. We recommend you to use default value in case
you don't want to tune this parameter,  because  having  non-zero  LambdaV
accelerates and stabilizes internal iterative algorithm. In case you  want
to suppress noise you can use  LambdaV  as  additional  parameter  (larger
value = more smoothness) to tune.

TYPICAL ERRORS

1. Using  initial  radius  which is too large. Memory requirements  of the
   RBF-ML are roughly proportional to N*Density*RBase^2 (where Density  is
   an average density of points per unit of the interpolation  space).  In
   the extreme case of the very large RBase we will need O(N^2)  units  of
   memory - and many layers in order to decrease radius to some reasonably
   small value.

2. Using too small number of layers - RBF models with large radius are not
   flexible enough to reproduce small variations in the  target  function.
   You  need  many  layers  with  different radii, from large to small, in
   order to have good model.

3. Using  initial  radius  which  is  too  small.  You will get model with
   "holes" in the areas which are too far away from interpolation centers.
   However, algorithm will work correctly (and quickly) in this case.

4. Using too many layers - you will get too large and too slow model. This
   model  will  perfectly  reproduce  your function, but maybe you will be
   able to achieve similar results with less layers (and less memory).

  -- ALGLIB --
     Copyright 02.03.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 RBF 보간 알고리즘을 설정합니다. ALGLIB는 몇 가지를 지원합니다
다른 속성을 가진 RBF 알고리즘.
이 알고리즘을 RBF-ML이라고합니다. 다층 RBF 모델, 즉
우리가 결합 할 수있게하는 반경을 줄이는 모델
정확도 (제 1 층의 큰 반경으로 인한)
마지막 층의 작은 반경) 및 빠른 수렴.
내부적으로 RBF-ML은 스파 스로부터 많은 다른 가속화 방법을 사용합니다.
행렬을 KD- 트리에 적용하면 알고리즘이 작동 시간이
대략적으로 N * log (N)에 비례 * 밀도 * RBase ^ 2 * NLayers, 여기서 N은
점의 수, 밀도는 단위의 점 당 평균 밀도입니다.
보간 공간, RBase는 초기 반경, NLayers는
레이어.
RBF-ML은 다음 종류의 보간 문제에 유용합니다.
1. 잘 맞는 점들로 "정확한"문제들 (완벽한 적합성)
2. 점의 임의적 분포에 대한 최소 제곱 문제 (알고리즘
   가능한 곳에서 완벽한 적합성을 제공하고 최소 제곱에 가깝다.
   단단한 지역에서 적합하십시오).
3. 우리가 통제 된 양을 적용하기를 원하는 시끄러운 문제
   부드럽게.
입력 매개 변수 :
    RBFCreate () 호출로 초기화 된 S - RBF 모델
    RBase - RBase 매개 변수, RBase> 0
    NLayers - NLayers 매개 변수, NLayers> 0, 시작할 값 권장
                약 5.
    LambdaV - 정규화 값, 문제를 해결할 때 유용 할 수 있습니다.
                최소 제곱의 의미로. 최적의 람다는 문제 -
                의존적이어서 시행 착오가 필요합니다. 우리의 경험에서,
                좋은 람다는 0.1만큼 클 수 있으며, 0.001
                초기 추측으로.
                기본값 - 0.01, LambdaV가 아닌 경우 사용됩니다.
                주어진. 0 값을 지정할 수는 있지만 0은 아닙니다.
                그렇게하는 것이 좋습니다.
튜닝 알고리즘
이 알고리즘을 사용하려면 세 가지 매개 변수를 선택해야합니다.
* 초기 반지름 RBase
* 모델 NLayers의 레이어 수
* 정규화 계수 LambdaV
초기 반경은 선택하기가 쉽습니다. 몇 번이라도 선택할 수 있습니다.
점 사이의 평균 거리보다 큽니다. 알고리즘이 중단되지 않습니다.
반경이 너무 큰 경우 모델 생성 시간이 단축됩니다.
증가하지만 모델은 올바르게 구축됩니다).
RLast = RBase / 2 ^ (NLayers-1) (사용한 반경)과 같은 레이어 수를 선택합니다.
마지막 레이어에 의해)은 일반적인 거리보다 작을 것입니다.
전철기. 모델 오류가 너무 큰 경우,
레이어. 더 많은 레이어가 있으면 모델 구성 및 평가가 가능합니다.
비례 적으로 느리지 만, 정확하게 모델을 가질 수 있습니다.
귀하의 데이터에 적합합니다. 다른 쪽에서는 소음을 억제하려면
모델의 유연성을 떨어 뜨리기 위해 레이어 수를 줄일 수 있습니다.
정규화 계수 LambdaV는 개인의 부드러움을 제어합니다.
각 레이어에 대해 만들어진 모델. 경우에 따라 기본값을 사용하는 것이 좋습니다.
이 매개 변수를 조정하고 싶지는 않습니다. 왜냐하면 0이 아닌 LambdaV
내부 반복 알고리즘을 가속화하고 안정화시킵니다. 원하는 경우에
노이즈를 억제하기 위해 LambdaV를 추가 매개 변수로 사용할 수 있습니다 (더 큰
값 = 더 부드러움)을 조정합니다.
일반적인 오류
1. 초기 반경이 너무 큽니다. 메모리 요구 사항
   RBF-ML은 대략적으로 N * Density * RBase ^ 2에 비례합니다 (여기서 밀도는
   보간 공간의 단위 당 평균 포인트 밀도). 에서
   매우 큰 RBase의 극단적 인 경우 우리는 O (N ^ 2) 단위의
   메모리 - 여러 레이어를 반경을 합리적으로 줄이기 위해
   작은 값.
2. 너무 적은 수의 레이어 사용 - 반경이 큰 RBF 모델은 그렇지 않습니다.
   목표 함수의 작은 변화를 재현 할만큼 충분히 유연합니다.
   큰 반지름에서 작은 반지름으로 여러 레이어가 필요합니다.
   좋은 모델을 갖기 위해서.
3. 초기 반경이 너무 작습니다. 당신은 모델을 얻을 것이다.
   보간 센터에서 너무 멀리 떨어져있는 영역에 "구멍"이 생깁니다.
   그러나 알고리즘은이 경우 올바르게 (그리고 빨리) 작동합니다.
4. 너무 많은 레이어를 사용하여 - 당신은 너무 크고 너무 느린 모델을 얻을 것이다. 이
   모델이 완벽하게 기능을 재현하지만 어쩌면 당신은
   더 적은 레이어 (그리고 적은 메모리)로 비슷한 결과를 얻을 수 있습니다.
  - ALGLIB -
     저작권 02.03.2012 Bochkanov Sergey
*************************************************** ********************** */
void rbfsetalgomultilayer(const rbfmodel &s, const double rbase, const ae_int_t nlayers, const double lambdav);
void rbfsetalgomultilayer(const rbfmodel &s, const double rbase, const ae_int_t nlayers);


/*************************************************************************
This function sets linear term (model is a sum of radial  basis  functions
plus linear polynomial). This function won't have effect until  next  call
to RBFBuildModel().

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call

NOTE: this   function  has   some   serialization-related  subtleties.  We
      recommend you to study serialization examples from ALGLIB  Reference
      Manual if you want to perform serialization of your models.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 선형 항을 설정합니다 (모델은 방사형 기본 함수
플러스 선형 다항식). 이 기능은 다음 호출 때까지 적용되지 않습니다.
RBFBuildModel ().
입력 매개 변수 :
    RBFCreate () 호출로 초기화 된 S - RBF 모델
참고 :이 함수에는 몇 가지 serialization 관련 미묘한 차이가 있습니다. 우리
      ALGLIB Reference에서 직렬화 예제를 공부하도록 권장합니다.
      모델의 직렬화를 수행하려면 수동으로하십시오.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfsetlinterm(const rbfmodel &s);


/*************************************************************************
This function sets constant term (model is a sum of radial basis functions
plus constant).  This  function  won't  have  effect  until  next  call to
RBFBuildModel().

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call

NOTE: this   function  has   some   serialization-related  subtleties.  We
      recommend you to study serialization examples from ALGLIB  Reference
      Manual if you want to perform serialization of your models.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 상수 항을 설정합니다 (모델은 방사형 기본 함수
상수). 이 함수는 다음에 호출 할 때까지 적용되지 않습니다.
RBFBuildModel ().
입력 매개 변수 :
    RBFCreate () 호출로 초기화 된 S - RBF 모델
참고 :이 함수에는 몇 가지 serialization 관련 미묘한 차이가 있습니다. 우리
      ALGLIB Reference에서 직렬화 예제를 공부하도록 권장합니다.
      모델의 직렬화를 수행하려면 수동으로하십시오.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfsetconstterm(const rbfmodel &s);


/*************************************************************************
This  function  sets  zero  term (model is a sum of radial basis functions
without polynomial term). This function won't have effect until next  call
to RBFBuildModel().

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call

NOTE: this   function  has   some   serialization-related  subtleties.  We
      recommend you to study serialization examples from ALGLIB  Reference
      Manual if you want to perform serialization of your models.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 0 항을 설정합니다 (모델은 방사형 기본 함수
다항식 용어 없음). 이 기능은 다음 호출 때까지 적용되지 않습니다.
RBFBuildModel ().
입력 매개 변수 :
    RBFCreate () 호출로 초기화 된 S - RBF 모델
참고 :이 함수에는 몇 가지 serialization 관련 미묘한 차이가 있습니다. 우리
      ALGLIB Reference에서 직렬화 예제를 공부하도록 권장합니다.
      모델의 직렬화를 수행하려면 수동으로하십시오.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfsetzeroterm(const rbfmodel &s);


/*************************************************************************
This   function  builds  RBF  model  and  returns  report  (contains  some
information which can be used for evaluation of the algorithm properties).

Call to this function modifies RBF model by calculating its centers/radii/
weights  and  saving  them  into  RBFModel  structure.  Initially RBFModel
contain zero coefficients, but after call to this function  we  will  have
coefficients which were calculated in order to fit our dataset.

After you called this function you can call RBFCalc(),  RBFGridCalc()  and
other model calculation functions.

INPUT PARAMETERS:
    S       -   RBF model, initialized by RBFCreate() call
    Rep     -   report:
                * Rep.TerminationType:
                  * -5 - non-distinct basis function centers were detected,
                         interpolation aborted
                  * -4 - nonconvergence of the internal SVD solver
                  *  1 - successful termination
                Fields are used for debugging purposes:
                * Rep.IterationsCount - iterations count of the LSQR solver
                * Rep.NMV - number of matrix-vector products
                * Rep.ARows - rows count for the system matrix
                * Rep.ACols - columns count for the system matrix
                * Rep.ANNZ - number of significantly non-zero elements
                  (elements above some algorithm-determined threshold)

NOTE:  failure  to  build  model will leave current state of the structure
unchanged.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 RBF 모델을 구축하고 보고서를 반환합니다 (일부 포함).
알고리즘 특성의 평가에 사용될 수있는 정보).
이 함수를 호출하면 RBF 모델의 중심 / 반지름 /
RBFModel 구조에 저장합니다. 처음에는 RBFModel
제로 계수를 포함하지만이 함수를 호출 한 후에는
계수는 우리의 데이터 세트에 적합하도록 계산되었습니다.
이 함수를 호출 한 후에는 RBFCalc (), RBFGridCalc () 및
다른 모델 계산 기능.
입력 매개 변수 :
    RBFCreate () 호출로 초기화 된 S - RBF 모델
    담당자 - 신고 :
                * Rep.TerminationType :
                  * -5 - 뚜렷하지 않은 기저 기능 센터가 발견되었습니다.
                         보간이 중단되었습니다.
                  * -4 - 내부 SVD 솔버의 비 집중
                  * 1 - 성공적인 종료
                필드는 디버깅 목적으로 사용됩니다.
                * Rep.IterationsCount - LSQR 솔버의 반복 횟수
                * Rep.NMV - 매트릭스 - 벡터 제품의 수
                * Rep.ARows - 시스템 행의 행 수
                * Rep.ACols - 시스템 행렬에 대한 열 수
                * Rep.ANNZ - 상당히 0이 아닌 요소의 수
                  (일부 알고리즘 결정 임계 값을 초과하는 요소)
참고 : 모델을 작성하지 않으면 구조의 현재 상태가 그대로 유지됩니다.
변하지 않은.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfbuildmodel(const rbfmodel &s, rbfreport &rep);


/*************************************************************************
This function calculates values of the RBF model in the given point.

This function should be used when we have NY=1 (scalar function) and  NX=2
(2-dimensional space). If you have 3-dimensional space, use RBFCalc3(). If
you have general situation (NX-dimensional space, NY-dimensional function)
you should use general, less efficient implementation RBFCalc().

If  you  want  to  calculate  function  values  many times, consider using
RBFGridCalc2(), which is far more efficient than many subsequent calls  to
RBFCalc2().

This function returns 0.0 when:
* model is not initialized
* NX<>2
 *NY<>1

INPUT PARAMETERS:
    S       -   RBF model
    X0      -   first coordinate, finite number
    X1      -   second coordinate, finite number

RESULT:
    value of the model or 0.0 (as defined above)

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 주어진 점에서 RBF 모델의 값을 계산합니다.
이 함수는 NY = 1 (스칼라 함수)이고 NX = 2 일 때 사용해야합니다.
(2 차원 공간). 3 차원 공간이 있다면 RBFCalc3 ()을 사용하십시오. 만약
당신은 일반적인 상황 (NX 차원 공간, NY 차원 함수)
RBFCalc ()를 덜 효율적으로 구현해야합니다.
함수 값을 여러 번 계산하려면 다음을 사용하십시오.
이후의 많은 호출보다 훨씬 효율적인 RBFGridCalc2 ()
RBFCalc2 ().
이 함수는 다음의 경우 0.0을 반환합니다.
* 모델이 초기화되지 않았습니다.
* NX <> 2
 * NY <> 1
입력 매개 변수 :
    S - RBF 모델
    X0 - 첫 번째 좌표, 유한 수
    X1 - 두 번째 좌표, 유한 수
결과:
    모델의 값 또는 0.0 (위에 정의 된대로)
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
double rbfcalc2(const rbfmodel &s, const double x0, const double x1);


/*************************************************************************
This function calculates values of the RBF model in the given point.

This function should be used when we have NY=1 (scalar function) and  NX=3
(3-dimensional space). If you have 2-dimensional space, use RBFCalc2(). If
you have general situation (NX-dimensional space, NY-dimensional function)
you should use general, less efficient implementation RBFCalc().

This function returns 0.0 when:
* model is not initialized
* NX<>3
 *NY<>1

INPUT PARAMETERS:
    S       -   RBF model
    X0      -   first coordinate, finite number
    X1      -   second coordinate, finite number
    X2      -   third coordinate, finite number

RESULT:
    value of the model or 0.0 (as defined above)

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 주어진 점에서 RBF 모델의 값을 계산합니다.
이 함수는 NY = 1 (스칼라 함수)이고 NX = 3 일 때 사용해야합니다.
(3 차원 공간). 2 차원 공간이 있다면 RBFCalc2 ()를 사용하십시오. 만약
당신은 일반적인 상황 (NX 차원 공간, NY 차원 함수)
RBFCalc ()를 덜 효율적으로 구현해야합니다.
이 함수는 다음의 경우 0.0을 반환합니다.
* 모델이 초기화되지 않았습니다.
* NX <> 3
 * NY <> 1
입력 매개 변수 :
    S - RBF 모델
    X0 - 첫 번째 좌표, 유한 수
    X1 - 두 번째 좌표, 유한 수
    X2 - 세 번째 좌표, 유한 수
결과:
    모델의 값 또는 0.0 (위에 정의 된대로)
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
double rbfcalc3(const rbfmodel &s, const double x0, const double x1, const double x2);


/*************************************************************************
This function calculates values of the RBF model at the given point.

This is general function which can be used for arbitrary NX (dimension  of
the space of arguments) and NY (dimension of the function itself). However
when  you  have  NY=1  you  may  find more convenient to use RBFCalc2() or
RBFCalc3().

This function returns 0.0 when model is not initialized.

INPUT PARAMETERS:
    S       -   RBF model
    X       -   coordinates, array[NX].
                X may have more than NX elements, in this case only
                leading NX will be used.

OUTPUT PARAMETERS:
    Y       -   function value, array[NY]. Y is out-parameter and
                reallocated after call to this function. In case you  want
                to reuse previously allocated Y, you may use RBFCalcBuf(),
                which reallocates Y only when it is too small.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 주어진 지점에서 RBF 모델의 값을 계산합니다.
이것은 임의의 NX (dimension of of NX)에 사용될 수있는 일반적인 함수입니다.
인수의 공간)과 NY (함수 자체의 차원). 하나
NY = 1 일 때 RBFCalc2 () 또는
RBFCalc3 ().
모델이 초기화되지 않은 경우이 함수는 0.0을 반환합니다.
입력 매개 변수 :
    S - RBF 모델
    X 좌표, 배열 [NX].
                X는 NX 개 이상의 요소를 가질 수 있습니다.이 경우에만
                선도적 인 NX가 사용됩니다.
출력 매개 변수 :
    Y - 함수 값, array [NY]. Y는 매개 변수가 아니며
                이 함수를 호출 한 후 다시 할당됩니다. 원하는 경우에
                이전에 할당 된 Y를 재사용하려면 RBFCalcBuf ()를 사용할 수 있습니다.
                Y가 너무 작을 때만 Y를 재 할당합니다.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfcalc(const rbfmodel &s, const real_1d_array &x, real_1d_array &y);


/*************************************************************************
This function calculates values of the RBF model at the given point.

Same as RBFCalc(), but does not reallocate Y when in is large enough to
store function values.

INPUT PARAMETERS:
    S       -   RBF model
    X       -   coordinates, array[NX].
                X may have more than NX elements, in this case only
                leading NX will be used.
    Y       -   possibly preallocated array

OUTPUT PARAMETERS:
    Y       -   function value, array[NY]. Y is not reallocated when it
                is larger than NY.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
void rbfcalcbuf(const rbfmodel &s, const real_1d_array &x, real_1d_array &y);


/*************************************************************************
This function calculates values of the RBF model at the regular grid.

Grid have N0*N1 points, with Point[I,J] = (X0[I], X1[J])

This function returns 0.0 when:
* model is not initialized
* NX<>2
 *NY<>1

INPUT PARAMETERS:
    S       -   RBF model
    X0      -   array of grid nodes, first coordinates, array[N0]
    N0      -   grid size (number of nodes) in the first dimension
    X1      -   array of grid nodes, second coordinates, array[N1]
    N1      -   grid size (number of nodes) in the second dimension

OUTPUT PARAMETERS:
    Y       -   function values, array[N0,N1]. Y is out-variable and
                is reallocated by this function.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 주어진 지점에서 RBF 모델의 값을 계산합니다.
RBFCalc ()와 동일하지만 in이 충분히 큰 경우 Y를 재 할당하지 않습니다.
함수 값을 저장하십시오.
입력 매개 변수 :
    S - RBF 모델
    X 좌표, 배열 [NX].
                X는 NX 개 이상의 요소를 가질 수 있습니다.이 경우에만
                선도적 인 NX가 사용됩니다.
    Y - 아마 사전 할당 된 배열
출력 매개 변수 :
    Y - 함수 값, array [NY]. Y는 재 할당되지 않습니다.
                NY보다 큽니다.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfgridcalc2(const rbfmodel &s, const real_1d_array &x0, const ae_int_t n0, const real_1d_array &x1, const ae_int_t n1, real_2d_array &y);


/*************************************************************************
This function "unpacks" RBF model by extracting its coefficients.

INPUT PARAMETERS:
    S       -   RBF model

OUTPUT PARAMETERS:
    NX      -   dimensionality of argument
    NY      -   dimensionality of the target function
    XWR     -   model information, array[NC,NX+NY+1].
                One row of the array corresponds to one basis function:
                * first NX columns  - coordinates of the center
                * next NY columns   - weights, one per dimension of the
                                      function being modelled
                * last column       - radius, same for all dimensions of
                                      the function being modelled
    NC      -   number of the centers
    V       -   polynomial  term , array[NY,NX+1]. One row per one
                dimension of the function being modelled. First NX
                elements are linear coefficients, V[NX] is equal to the
                constant part.

  -- ALGLIB --
     Copyright 13.12.2011 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 정규 그리드에서 RBF 모델의 값을 계산합니다.
Grid는 Point [I, J] = (X0 [I], X1 [J])와 함께 N0 * N1 점을 가진다.
이 함수는 다음의 경우 0.0을 반환합니다.
* 모델이 초기화되지 않았습니다.
* NX <> 2
 * NY <> 1
입력 매개 변수 :
    S - RBF 모델
    X0 - 그리드 노드의 배열, 첫 번째 좌표, 배열 [N0]
    N0 - 첫 번째 차원의 격자 크기 (노드 수)
    X1 - 그리드 노드의 배열, 두 번째 좌표, 배열 [N1]
    N1 - 두 번째 차원의 격자 크기 (노드 수)
출력 매개 변수 :
    Y - 함수 값, 배열 [N0, N1]. Y는 변수가 아니며
                이 함수에 의해 재 할당됩니다.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
void rbfunpack(const rbfmodel &s, ae_int_t &nx, ae_int_t &ny, real_2d_array &xwr, ae_int_t &nc, real_2d_array &v);

/*************************************************************************
This subroutine calculates the value of the bilinear or bicubic spline  at
the given point X.

Input parameters:
    C   -   coefficients table.
            Built by BuildBilinearSpline or BuildBicubicSpline.
    X, Y-   point

Result:
    S(x,y)

  -- ALGLIB PROJECT --
     Copyright 05.07.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 함수는 계수를 추출하여 RBF 모델을 "압축 해제"합니다.
입력 매개 변수 :
    S - RBF 모델
출력 매개 변수 :
    NX - 인수의 차원
    NY - 대상 함수의 차원
    XWR - 모델 정보, 배열 [NC, NX + NY + 1].
                배열의 한 행은 하나의 기저 함수에 해당합니다.
                * 첫 번째 NX 열 - 중심 좌표
                * 다음 뉴욕 칼럼 - 가중치,
                                      기능을 모델링하고있다.
                * 마지막 열 - 반경, 모든 치수에서 동일
                                      함수가 모델링되고있다.
    노스 캐롤라이나 - 센터의 수
    V - 다항식 항, array [NY, NX + 1]. 하나당 한 행
                모델링되는 함수의 차원. 첫 번째 NX
                요소는 선형 계수이며, V [NX]는
                일정 부분.
  - ALGLIB -
     저작권 13.12.2011 Bochkanov Sergey
*************************************************** ********************** */
double spline2dcalc(const spline2dinterpolant &c, const double x, const double y);


/*************************************************************************
This subroutine calculates the value of the bilinear or bicubic spline  at
the given point X and its derivatives.

Input parameters:
    C   -   spline interpolant.
    X, Y-   point

Output parameters:
    F   -   S(x,y)
    FX  -   dS(x,y)/dX
    FY  -   dS(x,y)/dY
    FXY -   d2S(x,y)/dXdY

  -- ALGLIB PROJECT --
     Copyright 05.07.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은에서 bilinear 또는 bicubic 스플라인의 값을 계산합니다.
주어진 점 X.
입력 매개 변수 :
    C - 계수 테이블.
            BuildBilinearSpline 또는 BuildBicubicSpline에 의해 작성됩니다.
    X, Y- 포인트
결과:
    S (x, y)
  - ALGLIB 프로젝트 -
     저작권 05.07.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline2ddiff(const spline2dinterpolant &c, const double x, const double y, double &f, double &fx, double &fy, double &fxy);


/*************************************************************************
This subroutine performs linear transformation of the spline argument.

Input parameters:
    C       -   spline interpolant
    AX, BX  -   transformation coefficients: x = A*t + B
    AY, BY  -   transformation coefficients: y = A*u + B
Result:
    C   -   transformed spline

  -- ALGLIB PROJECT --
     Copyright 30.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은에서 bilinear 또는 bicubic 스플라인의 값을 계산합니다.
주어진 점 X와 그 파생물
입력 매개 변수 :
    C - 스플라인 보간.
    X, Y- 포인트
출력 매개 변수 :
    F - S (x, y)
    FX - dS (x, y) / dX
    FY - dS (x, y) / dY
    FXY - d2S (x, y) / dXdY
  - ALGLIB 프로젝트 -
     저작권 05.07.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline2dlintransxy(const spline2dinterpolant &c, const double ax, const double bx, const double ay, const double by);


/*************************************************************************
This subroutine performs linear transformation of the spline.

Input parameters:
    C   -   spline interpolant.
    A, B-   transformation coefficients: S2(x,y) = A*S(x,y) + B

Output parameters:
    C   -   transformed spline

  -- ALGLIB PROJECT --
     Copyright 30.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인 인수의 선형 변환을 수행합니다.
입력 매개 변수 :
    C - 스플라인 보간
    AX, BX - 변환 계수 : x = A * t + B
    AY, BY - 변환 계수 : y = A * u + B
결과:
    C - 변형 된 스플라인
  - ALGLIB 프로젝트 -
     저작권 30.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline2dlintransf(const spline2dinterpolant &c, const double a, const double b);


/*************************************************************************
This subroutine makes the copy of the spline model.

Input parameters:
    C   -   spline interpolant

Output parameters:
    CC  -   spline copy

  -- ALGLIB PROJECT --
     Copyright 29.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인의 선형 변환을 수행합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    A, B 변환 계수 : S2 (x, y) = A * S (x, y) + B
출력 매개 변수 :
    C - 변형 된 스플라인
  - ALGLIB 프로젝트 -
     저작권 30.06.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline2dcopy(const spline2dinterpolant &c, spline2dinterpolant &cc);


/*************************************************************************
Bicubic spline resampling

Input parameters:
    A           -   function values at the old grid,
                    array[0..OldHeight-1, 0..OldWidth-1]
    OldHeight   -   old grid height, OldHeight>1
    OldWidth    -   old grid width, OldWidth>1
    NewHeight   -   new grid height, NewHeight>1
    NewWidth    -   new grid width, NewWidth>1

Output parameters:
    B           -   function values at the new grid,
                    array[0..NewHeight-1, 0..NewWidth-1]

  -- ALGLIB routine --
     15 May, 2007
     Copyright by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인 모델의 복사본을 만듭니다.
입력 매개 변수 :
    C - 스플라인 보간
출력 매개 변수 :
    CC - 스플라인 복사본
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 29.06.2007
*************************************************** ********************** */
void spline2dresamplebicubic(const real_2d_array &a, const ae_int_t oldheight, const ae_int_t oldwidth, real_2d_array &b, const ae_int_t newheight, const ae_int_t newwidth);


/*************************************************************************
Bilinear spline resampling

Input parameters:
    A           -   function values at the old grid,
                    array[0..OldHeight-1, 0..OldWidth-1]
    OldHeight   -   old grid height, OldHeight>1
    OldWidth    -   old grid width, OldWidth>1
    NewHeight   -   new grid height, NewHeight>1
    NewWidth    -   new grid width, NewWidth>1

Output parameters:
    B           -   function values at the new grid,
                    array[0..NewHeight-1, 0..NewWidth-1]

  -- ALGLIB routine --
     09.07.2007
     Copyright by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
바이 큐빅 스플라인 리샘플링
입력 매개 변수 :
    A - 기존 그리드에서의 함수 값,
                    배열 [0..OldHeight-1, 0..OldWidth-1]
    OldHeight - 오래된 그리드 높이, OldHeight> 1
    OldWidth - 이전 그리드 폭, OldWidth> 1
    NewHeight - 새로운 그리드 높이, NewHeight> 1
    NewWidth - 새로운 그리드 폭, NewWidth> 1
출력 매개 변수 :
    B - 새로운 그리드에서의 함수 값,
                    배열 [0..NewHeight-1, 0..NewWidth-1]
  - ALGLIB 루틴 -
     2007 년 5 월 15 일
     Bochkanov Sergey의 저작권
*************************************************** ********************** */
void spline2dresamplebilinear(const real_2d_array &a, const ae_int_t oldheight, const ae_int_t oldwidth, real_2d_array &b, const ae_int_t newheight, const ae_int_t newwidth);


/*************************************************************************
This subroutine builds bilinear vector-valued spline.

Input parameters:
    X   -   spline abscissas, array[0..N-1]
    Y   -   spline ordinates, array[0..M-1]
    F   -   function values, array[0..M*N*D-1]:
            * first D elements store D values at (X[0],Y[0])
            * next D elements store D values at (X[1],Y[0])
            * general form - D function values at (X[i],Y[j]) are stored
              at F[D*(J*N+I)...D*(J*N+I)+D-1].
    M,N -   grid size, M>=2, N>=2
    D   -   vector dimension, D>=1

Output parameters:
    C   -   spline interpolant

  -- ALGLIB PROJECT --
     Copyright 16.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
쌍 선형 스플라인 재 샘플링
입력 매개 변수 :
    A - 기존 그리드에서의 함수 값,
                    배열 [0..OldHeight-1, 0..OldWidth-1]
    OldHeight - 오래된 그리드 높이, OldHeight> 1
    OldWidth - 이전 그리드 폭, OldWidth> 1
    NewHeight - 새로운 그리드 높이, NewHeight> 1
    NewWidth - 새로운 그리드 폭, NewWidth> 1
출력 매개 변수 :
    B - 새로운 그리드에서의 함수 값,
                    배열 [0..NewHeight-1, 0..NewWidth-1]
  - ALGLIB 루틴 -
     09.07.2007
     Bochkanov Sergey의 저작권
*************************************************** ********************** */
void spline2dbuildbilinearv(const real_1d_array &x, const ae_int_t n, const real_1d_array &y, const ae_int_t m, const real_1d_array &f, const ae_int_t d, spline2dinterpolant &c);


/*************************************************************************
This subroutine builds bicubic vector-valued spline.

Input parameters:
    X   -   spline abscissas, array[0..N-1]
    Y   -   spline ordinates, array[0..M-1]
    F   -   function values, array[0..M*N*D-1]:
            * first D elements store D values at (X[0],Y[0])
            * next D elements store D values at (X[1],Y[0])
            * general form - D function values at (X[i],Y[j]) are stored
              at F[D*(J*N+I)...D*(J*N+I)+D-1].
    M,N -   grid size, M>=2, N>=2
    D   -   vector dimension, D>=1

Output parameters:
    C   -   spline interpolant

  -- ALGLIB PROJECT --
     Copyright 16.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 쌍 선형 벡터 값 스플라인을 작성합니다.
입력 매개 변수 :
    X - 스플라인 가로 좌표, 배열 [0..N-1]
    Y - 스플라인 세로 좌표, array [0..M-1]
    F - 함수 값, array [0..M * N * D-1] :
            * 첫 번째 D 요소는 D 값을 (X [0], Y [0])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [1], Y [0])에 저장합니다.
            * 일반 형식 - (X [i], Y [j])의 D 함수 값이 저장됩니다.
              F (D * (J * N + I) ... D * (J * N + I) + D-1).
    M, N - 격자 크기, M> = 2, N> = 2
    D - 벡터 차원, D> = 1
출력 매개 변수 :
    C - 스플라인 보간
  - ALGLIB 프로젝트 -
     Copyright 16.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline2dbuildbicubicv(const real_1d_array &x, const ae_int_t n, const real_1d_array &y, const ae_int_t m, const real_1d_array &f, const ae_int_t d, spline2dinterpolant &c);


/*************************************************************************
This subroutine calculates bilinear or bicubic vector-valued spline at the
given point (X,Y).

INPUT PARAMETERS:
    C   -   spline interpolant.
    X, Y-   point
    F   -   output buffer, possibly preallocated array. In case array size
            is large enough to store result, it is not reallocated.  Array
            which is too short will be reallocated

OUTPUT PARAMETERS:
    F   -   array[D] (or larger) which stores function values

  -- ALGLIB PROJECT --
     Copyright 16.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 바이 큐빅 벡터 값 스플라인을 만듭니다.
입력 매개 변수 :
    X - 스플라인 가로 좌표, 배열 [0..N-1]
    Y - 스플라인 세로 좌표, array [0..M-1]
    F - 함수 값, array [0..M * N * D-1] :
            * 첫 번째 D 요소는 D 값을 (X [0], Y [0])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [1], Y [0])에 저장합니다.
            * 일반 형식 - (X [i], Y [j])의 D 함수 값이 저장됩니다.
              F (D * (J * N + I) ... D * (J * N + I) + D-1).
    M, N - 격자 크기, M> = 2, N> = 2
    D - 벡터 차원, D> = 1
출력 매개 변수 :
    C - 스플라인 보간
  - ALGLIB 프로젝트 -
     Copyright 16.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline2dcalcvbuf(const spline2dinterpolant &c, const double x, const double y, real_1d_array &f);


/*************************************************************************
This subroutine calculates bilinear or bicubic vector-valued spline at the
given point (X,Y).

INPUT PARAMETERS:
    C   -   spline interpolant.
    X, Y-   point

OUTPUT PARAMETERS:
    F   -   array[D] which stores function values.  F is out-parameter and
            it  is  reallocated  after  call to this function. In case you
            want  to    reuse  previously  allocated  F,   you   may   use
            Spline2DCalcVBuf(),  which  reallocates  F only when it is too
            small.

  -- ALGLIB PROJECT --
     Copyright 16.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 bilinear 또는 bicubic 벡터 값 스플라인을
주어진 점 (X, Y).
입력 매개 변수 :
    C - 스플라인 보간.
    X, Y- 포인트
    F - 출력 버퍼, 사전 할당 된 배열. 배열 크기
            결과를 저장할만큼 충분히 크면 다시 할당되지 않습니다. 정렬
            너무 짧으면 재 할당됩니다.
출력 매개 변수 :
    F - 함수 값을 저장하는 배열 [D] (또는 그 이상)
  - ALGLIB 프로젝트 -
     Copyright 16.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline2dcalcv(const spline2dinterpolant &c, const double x, const double y, real_1d_array &f);


/*************************************************************************
This subroutine unpacks two-dimensional spline into the coefficients table

Input parameters:
    C   -   spline interpolant.

Result:
    M, N-   grid size (x-axis and y-axis)
    D   -   number of components
    Tbl -   coefficients table, unpacked format,
            D - components: [0..(N-1)*(M-1)*D-1, 0..19].
            For T=0..D-1 (component index), I = 0...N-2 (x index),
            J=0..M-2 (y index):
                K :=  T + I*D + J*D*(N-1)

                K-th row stores decomposition for T-th component of the
                vector-valued function

                Tbl[K,0] = X[i]
                Tbl[K,1] = X[i+1]
                Tbl[K,2] = Y[j]
                Tbl[K,3] = Y[j+1]
                Tbl[K,4] = C00
                Tbl[K,5] = C01
                Tbl[K,6] = C02
                Tbl[K,7] = C03
                Tbl[K,8] = C10
                Tbl[K,9] = C11
                ...
                Tbl[K,19] = C33
            On each grid square spline is equals to:
                S(x) = SUM(c[i,j]*(t^i)*(u^j), i=0..3, j=0..3)
                t = x-x[j]
                u = y-y[i]

  -- ALGLIB PROJECT --
     Copyright 16.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 2 차원 스플라인을 계수 테이블에 압축을 풉니 다.
입력 매개 변수 :
    C - 스플라인 보간.
결과:
    M, N- 그리드 크기 (x 축 및 y 축)
    D - 구성 요소의 수
    Tbl - 계수 테이블, 압축 해제 된 형식,
            D- 성분 : [0 .. (N-1) * (M-1) * D-1, 0..19].
            T = 0..D-1 (구성 요소 색인), I = 0 ... N-2 (x 색인),
            J = 0..M-2 (y 지수) :
                K : = T + I * D + J * D * (N-1)
                K 번째 행은 T 번째 구성 요소에 대한 분해를 저장합니다.
                벡터 값 함수
                Tbl [K, 0] = X [i]
                Tbl [K, 1] = X [i + 1]
                Tbl [K, 2] = Y [j]
                Tbl [K, 3] = Y [j + 1]
                Tbl [K, 4] = C00
                Tbl [K, 5] = C01
                Tbl [K, 6] = CO2
                Tbl [K, 7] = C03
                Tbl [K, 8] = C10
                Tbl [K, 9] = C11
                ...
                Tbl [K, 19] = C33
            각 격자 스퀘어에서 스플라인은 다음과 같습니다.
                S (x) = SUM (c [i, j] * (t ^ i) * (u ^ j), i = 0..3, j = 0..3)
                t = xx [j]
                u = yy [i]
  - ALGLIB 프로젝트 -
     Copyright 16.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void  spline2dunpackv ( const spline2dinterpolant & c, ae_int_t & m, ae_int_t & n, ae_int_t & d, real_2d_array & tbl);
void spline2dunpackv(const spline2dinterpolant &c, ae_int_t &m, ae_int_t &n, ae_int_t &d, real_2d_array &tbl);


/*************************************************************************
This subroutine was deprecated in ALGLIB 3.6.0

We recommend you to switch  to  Spline2DBuildBilinearV(),  which  is  more
flexible and accepts its arguments in more convenient order.

  -- ALGLIB PROJECT --
     Copyright 05.07.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 ALGLIB 3.6.0에서 더 이상 사용되지 않습니다.
Spline2DBuildBilinearV ()로 전환하는 것이 좋습니다.
유연하고 인수를보다 편리한 순서로 받아들입니다.
  - ALGLIB 프로젝트 -
     저작권 05.07.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline2dbuildbilinear(const real_1d_array &x, const real_1d_array &y, const real_2d_array &f, const ae_int_t m, const ae_int_t n, spline2dinterpolant &c);


/*************************************************************************
This subroutine was deprecated in ALGLIB 3.6.0

We recommend you to switch  to  Spline2DBuildBicubicV(),  which  is  more
flexible and accepts its arguments in more convenient order.

  -- ALGLIB PROJECT --
     Copyright 05.07.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 ALGLIB 3.6.0에서 더 이상 사용되지 않습니다.
Spline2DBuildBicubicV ()로 전환하는 것이 좋습니다.
유연하고 인수를보다 편리한 순서로 받아들입니다.
  - ALGLIB 프로젝트 -
     저작권 05.07.2007 Bochkanov Sergey
*************************************************** ********************** */
void spline2dbuildbicubic(const real_1d_array &x, const real_1d_array &y, const real_2d_array &f, const ae_int_t m, const ae_int_t n, spline2dinterpolant &c);


/*************************************************************************
This subroutine was deprecated in ALGLIB 3.6.0

We recommend you to switch  to  Spline2DUnpackV(),  which is more flexible
and accepts its arguments in more convenient order.

  -- ALGLIB PROJECT --
     Copyright 29.06.2007 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 ALGLIB 3.6.0에서 더 이상 사용되지 않습니다.
유연한 Spline2DUnpackV ()로 전환하는 것이 좋습니다.
그 주장을보다 편리한 순서로 받아 들인다.
  - ALGLIB 프로젝트 -
     Bochkanov Sergey의 Copyright 29.06.2007
*************************************************** ********************** */
void spline2dunpack(const spline2dinterpolant &c, ae_int_t &m, ae_int_t &n, real_2d_array &tbl);

/*************************************************************************
This subroutine calculates the value of the trilinear or tricubic spline at
the given point (X,Y,Z).

INPUT PARAMETERS:
    C   -   coefficients table.
            Built by BuildBilinearSpline or BuildBicubicSpline.
    X, Y,
    Z   -   point

Result:
    S(x,y,z)

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은에서 삼선 형 또는 삼차 정형 스플라인의 값을 계산합니다.
주어진 점 (X, Y, Z).
입력 매개 변수 :
    C - 계수 테이블.
            BuildBilinearSpline 또는 BuildBicubicSpline에 의해 작성됩니다.
    X, Y,
    Z- 지점
결과:
    S (x, y, z)
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
double spline3dcalc(const spline3dinterpolant &c, const double x, const double y, const double z);


/*************************************************************************
This subroutine performs linear transformation of the spline argument.

INPUT PARAMETERS:
    C       -   spline interpolant
    AX, BX  -   transformation coefficients: x = A*u + B
    AY, BY  -   transformation coefficients: y = A*v + B
    AZ, BZ  -   transformation coefficients: z = A*w + B

OUTPUT PARAMETERS:
    C   -   transformed spline

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인 인수의 선형 변환을 수행합니다.
입력 매개 변수 :
    C - 스플라인 보간
    AX, BX - 변환 계수 : x = A * u + B
    AY, BY - 변환 계수 : y = A * v + B
    AZ, BZ - 변환 계수 : z = A * w + B
출력 매개 변수 :
    C - 변형 된 스플라인
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline3dlintransxyz(const spline3dinterpolant &c, const double ax, const double bx, const double ay, const double by, const double az, const double bz);


/*************************************************************************
This subroutine performs linear transformation of the spline.

INPUT PARAMETERS:
    C   -   spline interpolant.
    A, B-   transformation coefficients: S2(x,y) = A*S(x,y,z) + B

OUTPUT PARAMETERS:
    C   -   transformed spline

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 스플라인의 선형 변환을 수행합니다.
입력 매개 변수 :
    C - 스플라인 보간.
    A, B- 변환 계수 : S2 (x, y) = A * S (x, y, z) + B
출력 매개 변수 :
    C - 변형 된 스플라인
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline3dlintransf(const spline3dinterpolant &c, const double a, const double b);


/*************************************************************************
Trilinear spline resampling

INPUT PARAMETERS:
    A           -   array[0..OldXCount*OldYCount*OldZCount-1], function
                    values at the old grid, :
                        A[0]        x=0,y=0,z=0
                        A[1]        x=1,y=0,z=0
                        A[..]       ...
                        A[..]       x=oldxcount-1,y=0,z=0
                        A[..]       x=0,y=1,z=0
                        A[..]       ...
                        ...
    OldZCount   -   old Z-count, OldZCount>1
    OldYCount   -   old Y-count, OldYCount>1
    OldXCount   -   old X-count, OldXCount>1
    NewZCount   -   new Z-count, NewZCount>1
    NewYCount   -   new Y-count, NewYCount>1
    NewXCount   -   new X-count, NewXCount>1

OUTPUT PARAMETERS:
    B           -   array[0..NewXCount*NewYCount*NewZCount-1], function
                    values at the new grid:
                        B[0]        x=0,y=0,z=0
                        B[1]        x=1,y=0,z=0
                        B[..]       ...
                        B[..]       x=newxcount-1,y=0,z=0
                        B[..]       x=0,y=1,z=0
                        B[..]       ...
                        ...

  -- ALGLIB routine --
     26.04.2012
     Copyright by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
삼선 형 스플라인 리샘플링
입력 매개 변수 :
    A - 배열 [0..OldXCount * OldYCount * OldZCount-1], 함수
                    이전 그리드의 값 :
                        A [0] x = 0, y = 0, z = 0
                        A [1] x = 1, y = 0, z = 0
                        [...] ...
                        A [..] x = oldxcount-1, y = 0, z = 0
                        A [..] x = 0, y = 1, z = 0
                        [...] ...
                        ...
    OldZCount - 오래된 Z- 카운트, OldZCount> 1
    OldYCount - 이전 Y- 계수, OldYCount> 1
    OldXCount - 이전 X- 개수, OldXCount> 1
    NewZCount - 새로운 Z- 카운트, NewZCount> 1
    NewYCount - 새로운 Y- 카운트, NewYCount> 1
    NewXCount - 새로운 X- 카운트, NewXCount> 1
출력 매개 변수 :
    B- 배열 [0..NewXCount * NewYCount * NewZCount-1], 함수
                    새 그리드의 값 :
                        B [0] x = 0, y = 0, z = 0
                        B [1] x = 1, y = 0, z = 0
                        B [..] ...
                        B [..] x = newxcount-1, y = 0, z = 0
                        B [..] x = 0, y = 1, z = 0
                        B [..] ...
                        ...
  - ALGLIB 루틴 -
     26.04.2012
     Bochkanov Sergey의 저작권
*************************************************** ********************** */
void spline3dresampletrilinear(const real_1d_array &a, const ae_int_t oldzcount, const ae_int_t oldycount, const ae_int_t oldxcount, const ae_int_t newzcount, const ae_int_t newycount, const ae_int_t newxcount, real_1d_array &b);


/*************************************************************************
This subroutine builds trilinear vector-valued spline.

INPUT PARAMETERS:
    X   -   spline abscissas,  array[0..N-1]
    Y   -   spline ordinates,  array[0..M-1]
    Z   -   spline applicates, array[0..L-1]
    F   -   function values, array[0..M*N*L*D-1]:
            * first D elements store D values at (X[0],Y[0],Z[0])
            * next D elements store D values at (X[1],Y[0],Z[0])
            * next D elements store D values at (X[2],Y[0],Z[0])
            * ...
            * next D elements store D values at (X[0],Y[1],Z[0])
            * next D elements store D values at (X[1],Y[1],Z[0])
            * next D elements store D values at (X[2],Y[1],Z[0])
            * ...
            * next D elements store D values at (X[0],Y[0],Z[1])
            * next D elements store D values at (X[1],Y[0],Z[1])
            * next D elements store D values at (X[2],Y[0],Z[1])
            * ...
            * general form - D function values at (X[i],Y[j]) are stored
              at F[D*(N*(M*K+J)+I)...D*(N*(M*K+J)+I)+D-1].
    M,N,
    L   -   grid size, M>=2, N>=2, L>=2
    D   -   vector dimension, D>=1

OUTPUT PARAMETERS:
    C   -   spline interpolant

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 삼선 형 벡터 값 스플라인을 작성합니다.
입력 매개 변수 :
    X - 스플라인 가로 좌표, 배열 [0..N-1]
    Y - 스플라인 세로 좌표, array [0..M-1]
    Z-spline applicates, array [0..L-1]
    F - 함수 값, array [0..M * N * L * D-1] :
            * 첫 번째 D 요소는 (X [0], Y [0], Z [0])에 D 값을 저장합니다.
            * 다음 D 요소는 D 값을 (X [1], Y [0], Z [0])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [2], Y [0], Z [0])에 저장합니다.
            * ...
            * 다음 D 요소는 D 값을 (X [0], Y [1], Z [0])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [1], Y [1], Z [0])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [2], Y [1], Z [0])에 저장합니다.
            * ...
            * 다음 D 요소는 D 값을 (X [0], Y [0], Z [1])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [1], Y [0], Z [1])에 저장합니다.
            * 다음 D 요소는 D 값을 (X [2], Y [0], Z [1])에 저장합니다.
            * ...
            * 일반 형식 - (X [i], Y [j])의 D 함수 값이 저장됩니다.
              D * (N * (M * K + J) + I) + D-1]에서 F [D * (N * (M * K + J) + I)
    M, N,
    L - 그리드 크기, M> = 2, N> = 2, L> = 2
    D - 벡터 차원, D> = 1
출력 매개 변수 :
    C - 스플라인 보간
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline3dbuildtrilinearv(const real_1d_array &x, const ae_int_t n, const real_1d_array &y, const ae_int_t m, const real_1d_array &z, const ae_int_t l, const real_1d_array &f, const ae_int_t d, spline3dinterpolant &c);


/*************************************************************************
This subroutine calculates bilinear or bicubic vector-valued spline at the
given point (X,Y,Z).

INPUT PARAMETERS:
    C   -   spline interpolant.
    X, Y,
    Z   -   point
    F   -   output buffer, possibly preallocated array. In case array size
            is large enough to store result, it is not reallocated.  Array
            which is too short will be reallocated

OUTPUT PARAMETERS:
    F   -   array[D] (or larger) which stores function values

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 bilinear 또는 bicubic 벡터 값 스플라인을
주어진 점 (X, Y, Z).
입력 매개 변수 :
    C - 스플라인 보간.
    X, Y,
    Z- 지점
    F - 출력 버퍼, 사전 할당 된 배열. 배열 크기
            결과를 저장할만큼 충분히 크면 다시 할당되지 않습니다. 정렬
            너무 짧으면 재 할당됩니다.
출력 매개 변수 :
    F - 함수 값을 저장하는 배열 [D] (또는 그 이상)
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline3dcalcvbuf(const spline3dinterpolant &c, const double x, const double y, const double z, real_1d_array &f);


/*************************************************************************
This subroutine calculates trilinear or tricubic vector-valued spline at the
given point (X,Y,Z).

INPUT PARAMETERS:
    C   -   spline interpolant.
    X, Y,
    Z   -   point

OUTPUT PARAMETERS:
    F   -   array[D] which stores function values.  F is out-parameter and
            it  is  reallocated  after  call to this function. In case you
            want  to    reuse  previously  allocated  F,   you   may   use
            Spline2DCalcVBuf(),  which  reallocates  F only when it is too
            small.

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 삼각형 또는 삼차 벡터 벡터 값 스플라인을
주어진 점 (X, Y, Z).
입력 매개 변수 :
    C - 스플라인 보간.
    X, Y,
    Z- 지점
출력 매개 변수 :
    F - 함수 값을 저장하는 배열 [D]. F는 매개 변수가 아니며
            이 함수를 호출 한 후에 재 할당됩니다. 당신이
            이전에 할당 된 F를 다시 사용하려면
            Spline2DCalcVBuf () : F가있을 때만 F를 다시 할당합니다.
            작은.
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline3dcalcv(const spline3dinterpolant &c, const double x, const double y, const double z, real_1d_array &f);


/*************************************************************************
This subroutine unpacks tri-dimensional spline into the coefficients table

INPUT PARAMETERS:
    C   -   spline interpolant.

Result:
    N   -   grid size (X)
    M   -   grid size (Y)
    L   -   grid size (Z)
    D   -   number of components
    SType-  spline type. Currently, only one spline type is supported:
            trilinear spline, as indicated by SType=1.
    Tbl -   spline coefficients: [0..(N-1)*(M-1)*(L-1)*D-1, 0..13].
            For T=0..D-1 (component index), I = 0...N-2 (x index),
            J=0..M-2 (y index), K=0..L-2 (z index):
                Q := T + I*D + J*D*(N-1) + K*D*(N-1)*(M-1),

                Q-th row stores decomposition for T-th component of the
                vector-valued function

                Tbl[Q,0] = X[i]
                Tbl[Q,1] = X[i+1]
                Tbl[Q,2] = Y[j]
                Tbl[Q,3] = Y[j+1]
                Tbl[Q,4] = Z[k]
                Tbl[Q,5] = Z[k+1]

                Tbl[Q,6] = C000
                Tbl[Q,7] = C100
                Tbl[Q,8] = C010
                Tbl[Q,9] = C110
                Tbl[Q,10]= C001
                Tbl[Q,11]= C101
                Tbl[Q,12]= C011
                Tbl[Q,13]= C111
            On each grid square spline is equals to:
                S(x) = SUM(c[i,j,k]*(x^i)*(y^j)*(z^k), i=0..1, j=0..1, k=0..1)
                t = x-x[j]
                u = y-y[i]
                v = z-z[k]

            NOTE: format of Tbl is given for SType=1. Future versions of
                  ALGLIB can use different formats for different values of
                  SType.

  -- ALGLIB PROJECT --
     Copyright 26.04.2012 by Bochkanov Sergey
*************************************************************************/
/* ************************************************ *************************
이 서브 루틴은 3 차원 스플라인을 계수 테이블에 압축을 풉니 다.
입력 매개 변수 :
    C - 스플라인 보간.
결과:
    N - 그리드 크기 (X)
    M - 격자 크기 (Y)
    L - 그리드 크기 (Z)
    D - 구성 요소의 수
    SType- 스플라인 유형. 현재 하나의 스플라인 유형 만 지원됩니다.
            SType = 1로 표시된 것처럼 삼선 형 스플라인
    Tbl- 스플라인 계수 : [0 .. (N-1) * (M-1) * (L-1) * D-1, 0..13].
            T = 0..D-1 (구성 요소 색인), I = 0 ... N-2 (x 색인),
            J = 0..M-2 (y 인덱스), K = 0..L-2 (z 인덱스)
                Q : = T + I * D + J * D * (N-1) + K * D * (N-1) * (M-1)
                Q 번째 행은 T 번째 열의 분해를 저장합니다.
                벡터 값 함수
                Tbl [Q, 0] = X [i]
                Tbl [Q, 1] = X [i + 1]
                Tbl [Q, 2] = Y [j]
                Tbl [Q, 3] = Y [j + 1]
                Tbl [Q, 4] = Z [k]
                Tbl [Q, 5] = Z [k + 1]
                Tbl [Q, 6] = C000
                Tbl [Q, 7] = C100
                Tbl [Q, 8] = C010
                Tbl [Q, 9] = C110
                Tbl [Q, 10] = C001
                Tbl [Q, 11] = C101
                Tbl [Q, 12] = C011
                Tbl [Q, 13] = C111
            각 격자 스퀘어에서 스플라인은 다음과 같습니다.
                S (x) = SUM (c [i, j, k) * (x ^ i) * (y ^ j) * (z ^ k), i = 0..1, j = 0..1, k = 0..1)
                t = xx [j]
                u = yy [i]
                v = zz [k]
            참고 : Tbl의 형식은 SType = 1에 대해 제공됩니다. 다음 버전의
                  ALGLIB는 다양한 값에 대해 다른 형식을 사용할 수 있습니다.
                  SType.
  - ALGLIB 프로젝트 -
     Copyright 26.04.2012 Bochkanov Sergey
*************************************************** ********************** */
void spline3dunpackv(const spline3dinterpolant &c, ae_int_t &n, ae_int_t &m, ae_int_t &l, ae_int_t &d, ae_int_t &stype, real_2d_array &tbl);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (기능)이 포함되어 있습니다.
//
// /////////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
double idwcalc(idwinterpolant* z,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void idwbuildmodifiedshepard(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t d,
     ae_int_t nq,
     ae_int_t nw,
     idwinterpolant* z,
     ae_state *_state);
void idwbuildmodifiedshepardr(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t nx,
     double r,
     idwinterpolant* z,
     ae_state *_state);
void idwbuildnoisy(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t d,
     ae_int_t nq,
     ae_int_t nw,
     idwinterpolant* z,
     ae_state *_state);
ae_bool _idwinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _idwinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _idwinterpolant_clear(void* _p);
void _idwinterpolant_destroy(void* _p);
double barycentriccalc(barycentricinterpolant* b,
     double t,
     ae_state *_state);
void barycentricdiff1(barycentricinterpolant* b,
     double t,
     double* f,
     double* df,
     ae_state *_state);
void barycentricdiff2(barycentricinterpolant* b,
     double t,
     double* f,
     double* df,
     double* d2f,
     ae_state *_state);
void barycentriclintransx(barycentricinterpolant* b,
     double ca,
     double cb,
     ae_state *_state);
void barycentriclintransy(barycentricinterpolant* b,
     double ca,
     double cb,
     ae_state *_state);
void barycentricunpack(barycentricinterpolant* b,
     ae_int_t* n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_state *_state);
void barycentricbuildxyw(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     barycentricinterpolant* b,
     ae_state *_state);
void barycentricbuildfloaterhormann(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t d,
     barycentricinterpolant* b,
     ae_state *_state);
void barycentriccopy(barycentricinterpolant* b,
     barycentricinterpolant* b2,
     ae_state *_state);
ae_bool _barycentricinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _barycentricinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _barycentricinterpolant_clear(void* _p);
void _barycentricinterpolant_destroy(void* _p);
void polynomialbar2cheb(barycentricinterpolant* p,
     double a,
     double b,
     /* Real    */ ae_vector* t,
     ae_state *_state);
void polynomialcheb2bar(/* Real    */ ae_vector* t,
     ae_int_t n,
     double a,
     double b,
     barycentricinterpolant* p,
     ae_state *_state);
void polynomialbar2pow(barycentricinterpolant* p,
     double c,
     double s,
     /* Real    */ ae_vector* a,
     ae_state *_state);
void polynomialpow2bar(/* Real    */ ae_vector* a,
     ae_int_t n,
     double c,
     double s,
     barycentricinterpolant* p,
     ae_state *_state);
void polynomialbuild(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     barycentricinterpolant* p,
     ae_state *_state);
void polynomialbuildeqdist(double a,
     double b,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     barycentricinterpolant* p,
     ae_state *_state);
void polynomialbuildcheb1(double a,
     double b,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     barycentricinterpolant* p,
     ae_state *_state);
void polynomialbuildcheb2(double a,
     double b,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     barycentricinterpolant* p,
     ae_state *_state);
double polynomialcalceqdist(double a,
     double b,
     /* Real    */ ae_vector* f,
     ae_int_t n,
     double t,
     ae_state *_state);
double polynomialcalccheb1(double a,
     double b,
     /* Real    */ ae_vector* f,
     ae_int_t n,
     double t,
     ae_state *_state);
double polynomialcalccheb2(double a,
     double b,
     /* Real    */ ae_vector* f,
     ae_int_t n,
     double t,
     ae_state *_state);
void spline1dbuildlinear(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     spline1dinterpolant* c,
     ae_state *_state);
void spline1dbuildcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     spline1dinterpolant* c,
     ae_state *_state);
void spline1dgriddiffcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void spline1dgriddiff2cubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* d1,
     /* Real    */ ae_vector* d2,
     ae_state *_state);
void spline1dconvcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* x2,
     ae_int_t n2,
     /* Real    */ ae_vector* y2,
     ae_state *_state);
void spline1dconvdiffcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* x2,
     ae_int_t n2,
     /* Real    */ ae_vector* y2,
     /* Real    */ ae_vector* d2,
     ae_state *_state);
void spline1dconvdiff2cubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* x2,
     ae_int_t n2,
     /* Real    */ ae_vector* y2,
     /* Real    */ ae_vector* d2,
     /* Real    */ ae_vector* dd2,
     ae_state *_state);
void spline1dbuildcatmullrom(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundtype,
     double tension,
     spline1dinterpolant* c,
     ae_state *_state);
void spline1dbuildhermite(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     spline1dinterpolant* c,
     ae_state *_state);
void spline1dbuildakima(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     spline1dinterpolant* c,
     ae_state *_state);
double spline1dcalc(spline1dinterpolant* c, double x, ae_state *_state);
void spline1ddiff(spline1dinterpolant* c,
     double x,
     double* s,
     double* ds,
     double* d2s,
     ae_state *_state);
void spline1dcopy(spline1dinterpolant* c,
     spline1dinterpolant* cc,
     ae_state *_state);
void spline1dunpack(spline1dinterpolant* c,
     ae_int_t* n,
     /* Real    */ ae_matrix* tbl,
     ae_state *_state);
void spline1dlintransx(spline1dinterpolant* c,
     double a,
     double b,
     ae_state *_state);
void spline1dlintransy(spline1dinterpolant* c,
     double a,
     double b,
     ae_state *_state);
double spline1dintegrate(spline1dinterpolant* c,
     double x,
     ae_state *_state);
void spline1dconvdiffinternal(/* Real    */ ae_vector* xold,
     /* Real    */ ae_vector* yold,
     /* Real    */ ae_vector* dold,
     ae_int_t n,
     /* Real    */ ae_vector* x2,
     ae_int_t n2,
     /* Real    */ ae_vector* y,
     ae_bool needy,
     /* Real    */ ae_vector* d1,
     ae_bool needd1,
     /* Real    */ ae_vector* d2,
     ae_bool needd2,
     ae_state *_state);
void spline1drootsandextrema(spline1dinterpolant* c,
     /* Real    */ ae_vector* r,
     ae_int_t* nr,
     ae_bool* dr,
     /* Real    */ ae_vector* e,
     /* Integer */ ae_vector* et,
     ae_int_t* ne,
     ae_bool* de,
     ae_state *_state);
void heapsortdpoints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     ae_state *_state);
void solvepolinom2(double p0,
     double m0,
     double p1,
     double m1,
     double* x0,
     double* x1,
     ae_int_t* nr,
     ae_state *_state);
void solvecubicpolinom(double pa,
     double ma,
     double pb,
     double mb,
     double a,
     double b,
     double* x0,
     double* x1,
     double* x2,
     double* ex0,
     double* ex1,
     ae_int_t* nr,
     ae_int_t* ne,
     /* Real    */ ae_vector* tempdata,
     ae_state *_state);
ae_int_t bisectmethod(double pa,
     double ma,
     double pb,
     double mb,
     double a,
     double b,
     double* x,
     ae_state *_state);
void spline1dbuildmonotone(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     spline1dinterpolant* c,
     ae_state *_state);
ae_bool _spline1dinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _spline1dinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _spline1dinterpolant_clear(void* _p);
void _spline1dinterpolant_destroy(void* _p);
void polynomialfit(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     ae_int_t* info,
     barycentricinterpolant* p,
     polynomialfitreport* rep,
     ae_state *_state);
void polynomialfitwc(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     /* Real    */ ae_vector* xc,
     /* Real    */ ae_vector* yc,
     /* Integer */ ae_vector* dc,
     ae_int_t k,
     ae_int_t m,
     ae_int_t* info,
     barycentricinterpolant* p,
     polynomialfitreport* rep,
     ae_state *_state);
void barycentricfitfloaterhormannwc(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     /* Real    */ ae_vector* xc,
     /* Real    */ ae_vector* yc,
     /* Integer */ ae_vector* dc,
     ae_int_t k,
     ae_int_t m,
     ae_int_t* info,
     barycentricinterpolant* b,
     barycentricfitreport* rep,
     ae_state *_state);
void barycentricfitfloaterhormann(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     ae_int_t* info,
     barycentricinterpolant* b,
     barycentricfitreport* rep,
     ae_state *_state);
void spline1dfitpenalized(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     double rho,
     ae_int_t* info,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);
void spline1dfitpenalizedw(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     ae_int_t m,
     double rho,
     ae_int_t* info,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);
void spline1dfitcubicwc(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     /* Real    */ ae_vector* xc,
     /* Real    */ ae_vector* yc,
     /* Integer */ ae_vector* dc,
     ae_int_t k,
     ae_int_t m,
     ae_int_t* info,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);
void spline1dfithermitewc(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     /* Real    */ ae_vector* xc,
     /* Real    */ ae_vector* yc,
     /* Integer */ ae_vector* dc,
     ae_int_t k,
     ae_int_t m,
     ae_int_t* info,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);
void spline1dfitcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     ae_int_t* info,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);
void spline1dfithermite(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     ae_int_t* info,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);
void lsfitlinearw(/* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_matrix* fmatrix,
     ae_int_t n,
     ae_int_t m,
     ae_int_t* info,
     /* Real    */ ae_vector* c,
     lsfitreport* rep,
     ae_state *_state);
void lsfitlinearwc(/* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_matrix* fmatrix,
     /* Real    */ ae_matrix* cmatrix,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     ae_int_t* info,
     /* Real    */ ae_vector* c,
     lsfitreport* rep,
     ae_state *_state);
void lsfitlinear(/* Real    */ ae_vector* y,
     /* Real    */ ae_matrix* fmatrix,
     ae_int_t n,
     ae_int_t m,
     ae_int_t* info,
     /* Real    */ ae_vector* c,
     lsfitreport* rep,
     ae_state *_state);
void lsfitlinearc(/* Real    */ ae_vector* y,
     /* Real    */ ae_matrix* fmatrix,
     /* Real    */ ae_matrix* cmatrix,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     ae_int_t* info,
     /* Real    */ ae_vector* c,
     lsfitreport* rep,
     ae_state *_state);
void lsfitcreatewf(/* Real    */ ae_matrix* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_vector* c,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     double diffstep,
     lsfitstate* state,
     ae_state *_state);
void lsfitcreatef(/* Real    */ ae_matrix* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* c,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     double diffstep,
     lsfitstate* state,
     ae_state *_state);
void lsfitcreatewfg(/* Real    */ ae_matrix* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_vector* c,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     ae_bool cheapfg,
     lsfitstate* state,
     ae_state *_state);
void lsfitcreatefg(/* Real    */ ae_matrix* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* c,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     ae_bool cheapfg,
     lsfitstate* state,
     ae_state *_state);
void lsfitcreatewfgh(/* Real    */ ae_matrix* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     /* Real    */ ae_vector* c,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     lsfitstate* state,
     ae_state *_state);
void lsfitcreatefgh(/* Real    */ ae_matrix* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* c,
     ae_int_t n,
     ae_int_t m,
     ae_int_t k,
     lsfitstate* state,
     ae_state *_state);
void lsfitsetcond(lsfitstate* state,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void lsfitsetstpmax(lsfitstate* state, double stpmax, ae_state *_state);
void lsfitsetxrep(lsfitstate* state, ae_bool needxrep, ae_state *_state);
void lsfitsetscale(lsfitstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void lsfitsetbc(lsfitstate* state,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state);
ae_bool lsfititeration(lsfitstate* state, ae_state *_state);
void lsfitresults(lsfitstate* state,
     ae_int_t* info,
     /* Real    */ ae_vector* c,
     lsfitreport* rep,
     ae_state *_state);
void lsfitsetgradientcheck(lsfitstate* state,
     double teststep,
     ae_state *_state);
void lsfitscalexy(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* w,
     ae_int_t n,
     /* Real    */ ae_vector* xc,
     /* Real    */ ae_vector* yc,
     /* Integer */ ae_vector* dc,
     ae_int_t k,
     double* xa,
     double* xb,
     double* sa,
     double* sb,
     /* Real    */ ae_vector* xoriginal,
     /* Real    */ ae_vector* yoriginal,
     ae_state *_state);
ae_bool _polynomialfitreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _polynomialfitreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _polynomialfitreport_clear(void* _p);
void _polynomialfitreport_destroy(void* _p);
ae_bool _barycentricfitreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _barycentricfitreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _barycentricfitreport_clear(void* _p);
void _barycentricfitreport_destroy(void* _p);
ae_bool _spline1dfitreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _spline1dfitreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _spline1dfitreport_clear(void* _p);
void _spline1dfitreport_destroy(void* _p);
ae_bool _lsfitreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _lsfitreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _lsfitreport_clear(void* _p);
void _lsfitreport_destroy(void* _p);
ae_bool _lsfitstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _lsfitstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _lsfitstate_clear(void* _p);
void _lsfitstate_destroy(void* _p);
void pspline2build(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t st,
     ae_int_t pt,
     pspline2interpolant* p,
     ae_state *_state);
void pspline3build(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t st,
     ae_int_t pt,
     pspline3interpolant* p,
     ae_state *_state);
void pspline2buildperiodic(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t st,
     ae_int_t pt,
     pspline2interpolant* p,
     ae_state *_state);
void pspline3buildperiodic(/* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_int_t st,
     ae_int_t pt,
     pspline3interpolant* p,
     ae_state *_state);
void pspline2parametervalues(pspline2interpolant* p,
     ae_int_t* n,
     /* Real    */ ae_vector* t,
     ae_state *_state);
void pspline3parametervalues(pspline3interpolant* p,
     ae_int_t* n,
     /* Real    */ ae_vector* t,
     ae_state *_state);
void pspline2calc(pspline2interpolant* p,
     double t,
     double* x,
     double* y,
     ae_state *_state);
void pspline3calc(pspline3interpolant* p,
     double t,
     double* x,
     double* y,
     double* z,
     ae_state *_state);
void pspline2tangent(pspline2interpolant* p,
     double t,
     double* x,
     double* y,
     ae_state *_state);
void pspline3tangent(pspline3interpolant* p,
     double t,
     double* x,
     double* y,
     double* z,
     ae_state *_state);
void pspline2diff(pspline2interpolant* p,
     double t,
     double* x,
     double* dx,
     double* y,
     double* dy,
     ae_state *_state);
void pspline3diff(pspline3interpolant* p,
     double t,
     double* x,
     double* dx,
     double* y,
     double* dy,
     double* z,
     double* dz,
     ae_state *_state);
void pspline2diff2(pspline2interpolant* p,
     double t,
     double* x,
     double* dx,
     double* d2x,
     double* y,
     double* dy,
     double* d2y,
     ae_state *_state);
void pspline3diff2(pspline3interpolant* p,
     double t,
     double* x,
     double* dx,
     double* d2x,
     double* y,
     double* dy,
     double* d2y,
     double* z,
     double* dz,
     double* d2z,
     ae_state *_state);
double pspline2arclength(pspline2interpolant* p,
     double a,
     double b,
     ae_state *_state);
double pspline3arclength(pspline3interpolant* p,
     double a,
     double b,
     ae_state *_state);
ae_bool _pspline2interpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _pspline2interpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _pspline2interpolant_clear(void* _p);
void _pspline2interpolant_destroy(void* _p);
ae_bool _pspline3interpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _pspline3interpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _pspline3interpolant_clear(void* _p);
void _pspline3interpolant_destroy(void* _p);
void rbfcreate(ae_int_t nx, ae_int_t ny, rbfmodel* s, ae_state *_state);
void rbfsetpoints(rbfmodel* s,
     /* Real    */ ae_matrix* xy,
     ae_int_t n,
     ae_state *_state);
void rbfsetalgoqnn(rbfmodel* s, double q, double z, ae_state *_state);
void rbfsetalgomultilayer(rbfmodel* s,
     double rbase,
     ae_int_t nlayers,
     double lambdav,
     ae_state *_state);
void rbfsetlinterm(rbfmodel* s, ae_state *_state);
void rbfsetconstterm(rbfmodel* s, ae_state *_state);
void rbfsetzeroterm(rbfmodel* s, ae_state *_state);
void rbfsetcond(rbfmodel* s,
     double epsort,
     double epserr,
     ae_int_t maxits,
     ae_state *_state);
void rbfbuildmodel(rbfmodel* s, rbfreport* rep, ae_state *_state);
double rbfcalc2(rbfmodel* s, double x0, double x1, ae_state *_state);
double rbfcalc3(rbfmodel* s,
     double x0,
     double x1,
     double x2,
     ae_state *_state);
void rbfcalc(rbfmodel* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void rbfcalcbuf(rbfmodel* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void rbfgridcalc2(rbfmodel* s,
     /* Real    */ ae_vector* x0,
     ae_int_t n0,
     /* Real    */ ae_vector* x1,
     ae_int_t n1,
     /* Real    */ ae_matrix* y,
     ae_state *_state);
void rbfunpack(rbfmodel* s,
     ae_int_t* nx,
     ae_int_t* ny,
     /* Real    */ ae_matrix* xwr,
     ae_int_t* nc,
     /* Real    */ ae_matrix* v,
     ae_state *_state);
void rbfalloc(ae_serializer* s, rbfmodel* model, ae_state *_state);
void rbfserialize(ae_serializer* s, rbfmodel* model, ae_state *_state);
void rbfunserialize(ae_serializer* s, rbfmodel* model, ae_state *_state);
ae_bool _rbfmodel_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _rbfmodel_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _rbfmodel_clear(void* _p);
void _rbfmodel_destroy(void* _p);
ae_bool _rbfreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _rbfreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _rbfreport_clear(void* _p);
void _rbfreport_destroy(void* _p);
double spline2dcalc(spline2dinterpolant* c,
     double x,
     double y,
     ae_state *_state);
void spline2ddiff(spline2dinterpolant* c,
     double x,
     double y,
     double* f,
     double* fx,
     double* fy,
     double* fxy,
     ae_state *_state);
void spline2dlintransxy(spline2dinterpolant* c,
     double ax,
     double bx,
     double ay,
     double by,
     ae_state *_state);
void spline2dlintransf(spline2dinterpolant* c,
     double a,
     double b,
     ae_state *_state);
void spline2dcopy(spline2dinterpolant* c,
     spline2dinterpolant* cc,
     ae_state *_state);
void spline2dresamplebicubic(/* Real    */ ae_matrix* a,
     ae_int_t oldheight,
     ae_int_t oldwidth,
     /* Real    */ ae_matrix* b,
     ae_int_t newheight,
     ae_int_t newwidth,
     ae_state *_state);
void spline2dresamplebilinear(/* Real    */ ae_matrix* a,
     ae_int_t oldheight,
     ae_int_t oldwidth,
     /* Real    */ ae_matrix* b,
     ae_int_t newheight,
     ae_int_t newwidth,
     ae_state *_state);
void spline2dbuildbilinearv(/* Real    */ ae_vector* x,
     ae_int_t n,
     /* Real    */ ae_vector* y,
     ae_int_t m,
     /* Real    */ ae_vector* f,
     ae_int_t d,
     spline2dinterpolant* c,
     ae_state *_state);
void spline2dbuildbicubicv(/* Real    */ ae_vector* x,
     ae_int_t n,
     /* Real    */ ae_vector* y,
     ae_int_t m,
     /* Real    */ ae_vector* f,
     ae_int_t d,
     spline2dinterpolant* c,
     ae_state *_state);
void spline2dcalcvbuf(spline2dinterpolant* c,
     double x,
     double y,
     /* Real    */ ae_vector* f,
     ae_state *_state);
void spline2dcalcv(spline2dinterpolant* c,
     double x,
     double y,
     /* Real    */ ae_vector* f,
     ae_state *_state);
void spline2dunpackv(spline2dinterpolant* c,
     ae_int_t* m,
     ae_int_t* n,
     ae_int_t* d,
     /* Real    */ ae_matrix* tbl,
     ae_state *_state);
void spline2dbuildbilinear(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_matrix* f,
     ae_int_t m,
     ae_int_t n,
     spline2dinterpolant* c,
     ae_state *_state);
void spline2dbuildbicubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_matrix* f,
     ae_int_t m,
     ae_int_t n,
     spline2dinterpolant* c,
     ae_state *_state);
void spline2dunpack(spline2dinterpolant* c,
     ae_int_t* m,
     ae_int_t* n,
     /* Real    */ ae_matrix* tbl,
     ae_state *_state);
ae_bool _spline2dinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _spline2dinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _spline2dinterpolant_clear(void* _p);
void _spline2dinterpolant_destroy(void* _p);
double spline3dcalc(spline3dinterpolant* c,
     double x,
     double y,
     double z,
     ae_state *_state);
void spline3dlintransxyz(spline3dinterpolant* c,
     double ax,
     double bx,
     double ay,
     double by,
     double az,
     double bz,
     ae_state *_state);
void spline3dlintransf(spline3dinterpolant* c,
     double a,
     double b,
     ae_state *_state);
void spline3dcopy(spline3dinterpolant* c,
     spline3dinterpolant* cc,
     ae_state *_state);
void spline3dresampletrilinear(/* Real    */ ae_vector* a,
     ae_int_t oldzcount,
     ae_int_t oldycount,
     ae_int_t oldxcount,
     ae_int_t newzcount,
     ae_int_t newycount,
     ae_int_t newxcount,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void spline3dbuildtrilinearv(/* Real    */ ae_vector* x,
     ae_int_t n,
     /* Real    */ ae_vector* y,
     ae_int_t m,
     /* Real    */ ae_vector* z,
     ae_int_t l,
     /* Real    */ ae_vector* f,
     ae_int_t d,
     spline3dinterpolant* c,
     ae_state *_state);
void spline3dcalcvbuf(spline3dinterpolant* c,
     double x,
     double y,
     double z,
     /* Real    */ ae_vector* f,
     ae_state *_state);
void spline3dcalcv(spline3dinterpolant* c,
     double x,
     double y,
     double z,
     /* Real    */ ae_vector* f,
     ae_state *_state);
void spline3dunpackv(spline3dinterpolant* c,
     ae_int_t* n,
     ae_int_t* m,
     ae_int_t* l,
     ae_int_t* d,
     ae_int_t* stype,
     /* Real    */ ae_matrix* tbl,
     ae_state *_state);
ae_bool _spline3dinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _spline3dinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _spline3dinterpolant_clear(void* _p);
void _spline3dinterpolant_destroy(void* _p);

}
#endif

