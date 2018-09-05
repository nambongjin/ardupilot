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
#ifndef _optimization_pkg_h
#define _optimization_pkg_h
#include "ap.h"
#include "alglibinternal.h"
#include "linalg.h"
#include "alglibmisc.h"
#include "solvers.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
typedef struct
{
    ae_int_t n;
    ae_int_t k;
    double alpha;
    double tau;
    double theta;
    ae_matrix a;
    ae_matrix q;
    ae_vector b;
    ae_vector r;
    ae_vector xc;
    ae_vector d;
    ae_vector activeset;
    ae_matrix tq2dense;
    ae_matrix tk2;
    ae_vector tq2diag;
    ae_vector tq1;
    ae_vector tk1;
    double tq0;
    double tk0;
    ae_vector txc;
    ae_vector tb;
    ae_int_t nfree;
    ae_int_t ecakind;
    ae_matrix ecadense;
    ae_matrix eq;
    ae_matrix eccm;
    ae_vector ecadiag;
    ae_vector eb;
    double ec;
    ae_vector tmp0;
    ae_vector tmp1;
    ae_vector tmpg;
    ae_matrix tmp2;
    ae_bool ismaintermchanged;
    ae_bool issecondarytermchanged;
    ae_bool islineartermchanged;
    ae_bool isactivesetchanged;
} convexquadraticmodel;
typedef struct
{
    ae_int_t ns;
    ae_int_t nd;
    ae_int_t nr;
    ae_matrix densea;
    ae_vector b;
    ae_vector nnc;
    ae_int_t refinementits;
    double debugflops;
    ae_int_t debugmaxnewton;
    ae_vector xn;
    ae_matrix tmpz;
    ae_matrix tmpca;
    ae_vector g;
    ae_vector d;
    ae_vector dx;
    ae_vector diagaa;
    ae_vector cb;
    ae_vector cx;
    ae_vector cborg;
    ae_vector columnmap;
    ae_vector rowmap;
    ae_vector tmpcholesky;
    ae_vector r;
} snnlssolver;
typedef struct
{
    ae_int_t n;
    ae_int_t algostate;
    ae_vector xc;
    ae_bool hasxc;
    ae_vector s;
    ae_vector h;
    ae_vector activeset;
    ae_bool basisisready;
    ae_matrix sbasis;
    ae_matrix pbasis;
    ae_matrix ibasis;
    ae_int_t basissize;
    ae_bool constraintschanged;
    ae_vector hasbndl;
    ae_vector hasbndu;
    ae_vector bndl;
    ae_vector bndu;
    ae_matrix cleic;
    ae_int_t nec;
    ae_int_t nic;
    ae_vector mtx;
    ae_vector mtas;
    ae_vector cdtmp;
    ae_vector corrtmp;
    ae_vector unitdiagonal;
    snnlssolver solver;
    ae_vector scntmp;
    ae_vector tmp0;
    ae_vector tmpfeas;
    ae_matrix tmpm0;
    ae_vector rctmps;
    ae_vector rctmpg;
    ae_vector rctmprightpart;
    ae_matrix rctmpdense0;
    ae_matrix rctmpdense1;
    ae_vector rctmpisequality;
    ae_vector rctmpconstraintidx;
    ae_vector rctmplambdas;
    ae_matrix tmpbasis;
} sactiveset;
typedef struct
{
    ae_int_t n;
    double epsg;
    double epsf;
    double epsx;
    ae_int_t maxits;
    double stpmax;
    double suggestedstep;
    ae_bool xrep;
    ae_bool drep;
    ae_int_t cgtype;
    ae_int_t prectype;
    ae_vector diagh;
    ae_vector diaghl2;
    ae_matrix vcorr;
    ae_int_t vcnt;
    ae_vector s;
    double diffstep;
    ae_int_t nfev;
    ae_int_t mcstage;
    ae_int_t k;
    ae_vector xk;
    ae_vector dk;
    ae_vector xn;
    ae_vector dn;
    ae_vector d;
    double fold;
    double stp;
    double curstpmax;
    ae_vector yk;
    double lastgoodstep;
    double lastscaledstep;
    ae_int_t mcinfo;
    ae_bool innerresetneeded;
    ae_bool terminationneeded;
    double trimthreshold;
    ae_int_t rstimer;
    ae_vector x;
    double f;
    ae_vector g;
    ae_bool needf;
    ae_bool needfg;
    ae_bool xupdated;
    ae_bool algpowerup;
    ae_bool lsstart;
    ae_bool lsend;
    double teststep;
    rcommstate rstate;
    ae_int_t repiterationscount;
    ae_int_t repnfev;
    ae_int_t repvaridx;
    ae_int_t repterminationtype;
    ae_int_t debugrestartscount;
    linminstate lstate;
    double fbase;
    double fm2;
    double fm1;
    double fp1;
    double fp2;
    double betahs;
    double betady;
    ae_vector work0;
    ae_vector work1;
} mincgstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nfev;
    ae_int_t varidx;
    ae_int_t terminationtype;
} mincgreport;
typedef struct
{
    ae_int_t nmain;
    ae_int_t nslack;
    double epsg;
    double epsf;
    double epsx;
    ae_int_t maxits;
    ae_bool xrep;
    ae_bool drep;
    double stpmax;
    double diffstep;
    sactiveset sas;
    ae_vector s;
    ae_int_t prectype;
    ae_vector diagh;
    ae_vector x;
    double f;
    ae_vector g;
    ae_bool needf;
    ae_bool needfg;
    ae_bool xupdated;
    ae_bool lsstart;
    ae_bool lbfgssearch;
    ae_bool boundedstep;
    double teststep;
    rcommstate rstate;
    ae_vector gc;
    ae_vector xn;
    ae_vector gn;
    ae_vector xp;
    ae_vector gp;
    double fc;
    double fn;
    double fp;
    ae_vector d;
    ae_matrix cleic;
    ae_int_t nec;
    ae_int_t nic;
    double lastgoodstep;
    double lastscaledgoodstep;
    double maxscaledgrad;
    ae_vector hasbndl;
    ae_vector hasbndu;
    ae_vector bndl;
    ae_vector bndu;
    ae_int_t repinneriterationscount;
    ae_int_t repouteriterationscount;
    ae_int_t repnfev;
    ae_int_t repvaridx;
    ae_int_t repterminationtype;
    double repdebugeqerr;
    double repdebugfs;
    double repdebugff;
    double repdebugdx;
    ae_int_t repdebugfeasqpits;
    ae_int_t repdebugfeasgpaits;
    ae_vector xstart;
    snnlssolver solver;
    double fbase;
    double fm2;
    double fm1;
    double fp1;
    double fp2;
    double xm1;
    double xp1;
    double gm1;
    double gp1;
    ae_int_t cidx;
    double cval;
    ae_vector tmpprec;
    ae_int_t nfev;
    ae_int_t mcstage;
    double stp;
    double curstpmax;
    double activationstep;
    ae_vector work;
    linminstate lstate;
    double trimthreshold;
    ae_int_t nonmonotoniccnt;
    ae_int_t k;
    ae_int_t q;
    ae_int_t p;
    ae_vector rho;
    ae_matrix yk;
    ae_matrix sk;
    ae_vector theta;
} minbleicstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nfev;
    ae_int_t varidx;
    ae_int_t terminationtype;
    double debugeqerr;
    double debugfs;
    double debugff;
    double debugdx;
    ae_int_t debugfeasqpits;
    ae_int_t debugfeasgpaits;
    ae_int_t inneriterationscount;
    ae_int_t outeriterationscount;
} minbleicreport;
typedef struct
{
    ae_int_t n;
    ae_int_t m;
    double epsg;
    double epsf;
    double epsx;
    ae_int_t maxits;
    ae_bool xrep;
    double stpmax;
    ae_vector s;
    double diffstep;
    ae_int_t nfev;
    ae_int_t mcstage;
    ae_int_t k;
    ae_int_t q;
    ae_int_t p;
    ae_vector rho;
    ae_matrix yk;
    ae_matrix sk;
    ae_vector theta;
    ae_vector d;
    double stp;
    ae_vector work;
    double fold;
    double trimthreshold;
    ae_int_t prectype;
    double gammak;
    ae_matrix denseh;
    ae_vector diagh;
    double fbase;
    double fm2;
    double fm1;
    double fp1;
    double fp2;
    ae_vector autobuf;
    ae_vector x;
    double f;
    ae_vector g;
    ae_bool needf;
    ae_bool needfg;
    ae_bool xupdated;
    double teststep;
    rcommstate rstate;
    ae_int_t repiterationscount;
    ae_int_t repnfev;
    ae_int_t repvaridx;
    ae_int_t repterminationtype;
    linminstate lstate;
} minlbfgsstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nfev;
    ae_int_t varidx;
    ae_int_t terminationtype;
} minlbfgsreport;
typedef struct
{
    ae_int_t n;
    ae_int_t algokind;
    ae_int_t akind;
    convexquadraticmodel a;
    sparsematrix sparsea;
    ae_bool sparseaupper;
    double anorm;
    ae_vector b;
    ae_vector bndl;
    ae_vector bndu;
    ae_vector s;
    ae_vector havebndl;
    ae_vector havebndu;
    ae_vector xorigin;
    ae_vector startx;
    ae_bool havex;
    ae_matrix cleic;
    ae_int_t nec;
    ae_int_t nic;
    double bleicepsg;
    double bleicepsf;
    double bleicepsx;
    ae_int_t bleicmaxits;
    sactiveset sas;
    ae_vector gc;
    ae_vector xn;
    ae_vector pg;
    ae_vector workbndl;
    ae_vector workbndu;
    ae_matrix workcleic;
    ae_vector xs;
    ae_int_t repinneriterationscount;
    ae_int_t repouteriterationscount;
    ae_int_t repncholesky;
    ae_int_t repnmv;
    ae_int_t repterminationtype;
    double debugphase1flops;
    double debugphase2flops;
    double debugphase3flops;
    ae_vector tmp0;
    ae_vector tmp1;
    ae_vector tmpb;
    ae_vector rctmpg;
    ae_vector tmpi;
    normestimatorstate estimator;
    minbleicstate solver;
    minbleicreport solverrep;
} minqpstate;
typedef struct
{
    ae_int_t inneriterationscount;
    ae_int_t outeriterationscount;
    ae_int_t nmv;
    ae_int_t ncholesky;
    ae_int_t terminationtype;
} minqpreport;
typedef struct
{
    ae_int_t n;
    ae_int_t m;
    double diffstep;
    double epsg;
    double epsf;
    double epsx;
    ae_int_t maxits;
    ae_bool xrep;
    double stpmax;
    ae_int_t maxmodelage;
    ae_bool makeadditers;
    ae_vector x;
    double f;
    ae_vector fi;
    ae_matrix j;
    ae_matrix h;
    ae_vector g;
    ae_bool needf;
    ae_bool needfg;
    ae_bool needfgh;
    ae_bool needfij;
    ae_bool needfi;
    ae_bool xupdated;
    ae_int_t algomode;
    ae_bool hasf;
    ae_bool hasfi;
    ae_bool hasg;
    ae_vector xbase;
    double fbase;
    ae_vector fibase;
    ae_vector gbase;
    ae_matrix quadraticmodel;
    ae_vector bndl;
    ae_vector bndu;
    ae_vector havebndl;
    ae_vector havebndu;
    ae_vector s;
    double lambdav;
    double nu;
    ae_int_t modelage;
    ae_vector xdir;
    ae_vector deltax;
    ae_vector deltaf;
    ae_bool deltaxready;
    ae_bool deltafready;
    double teststep;
    ae_int_t repiterationscount;
    ae_int_t repterminationtype;
    ae_int_t repfuncidx;
    ae_int_t repvaridx;
    ae_int_t repnfunc;
    ae_int_t repnjac;
    ae_int_t repngrad;
    ae_int_t repnhess;
    ae_int_t repncholesky;
    rcommstate rstate;
    ae_vector choleskybuf;
    ae_vector tmp0;
    double actualdecrease;
    double predicteddecrease;
    double xm1;
    double xp1;
    ae_vector fm1;
    ae_vector fp1;
    ae_vector fc1;
    ae_vector gm1;
    ae_vector gp1;
    ae_vector gc1;
    minlbfgsstate internalstate;
    minlbfgsreport internalrep;
    minqpstate qpstate;
    minqpreport qprep;
} minlmstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t terminationtype;
    ae_int_t funcidx;
    ae_int_t varidx;
    ae_int_t nfunc;
    ae_int_t njac;
    ae_int_t ngrad;
    ae_int_t nhess;
    ae_int_t ncholesky;
} minlmreport;
typedef struct
{
    ae_int_t n;
    double epsg;
    double epsf;
    double epsx;
    ae_int_t maxits;
    ae_bool xrep;
    double stpmax;
    ae_int_t cgtype;
    ae_int_t k;
    ae_int_t nfev;
    ae_int_t mcstage;
    ae_vector bndl;
    ae_vector bndu;
    ae_int_t curalgo;
    ae_int_t acount;
    double mu;
    double finit;
    double dginit;
    ae_vector ak;
    ae_vector xk;
    ae_vector dk;
    ae_vector an;
    ae_vector xn;
    ae_vector dn;
    ae_vector d;
    double fold;
    double stp;
    ae_vector work;
    ae_vector yk;
    ae_vector gc;
    double laststep;
    ae_vector x;
    double f;
    ae_vector g;
    ae_bool needfg;
    ae_bool xupdated;
    rcommstate rstate;
    ae_int_t repiterationscount;
    ae_int_t repnfev;
    ae_int_t repterminationtype;
    ae_int_t debugrestartscount;
    linminstate lstate;
    double betahs;
    double betady;
} minasastate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nfev;
    ae_int_t terminationtype;
    ae_int_t activeconstraints;
} minasareport;

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{









/*************************************************************************
This object stores state of the nonlinear CG optimizer.

You should use ALGLIB functions to work with this object.
*************************************************************************/
/**************************************************************************
이 객체는 비선형 CG 최적화 프로그램의 상태를 저장합니다.
이 객체를 사용하려면 ALGLIB 함수를 사용해야합니다.
**************************************************************************/
class _mincgstate_owner
{
public:
    _mincgstate_owner();
    _mincgstate_owner(const _mincgstate_owner &rhs);
    _mincgstate_owner& operator=(const _mincgstate_owner &rhs);
    virtual ~_mincgstate_owner();
    alglib_impl::mincgstate* c_ptr();
    alglib_impl::mincgstate* c_ptr() const;
protected:
    alglib_impl::mincgstate *p_struct;
};
class mincgstate : public _mincgstate_owner
{
public:
    mincgstate();
    mincgstate(const mincgstate &rhs);
    mincgstate& operator=(const mincgstate &rhs);
    virtual ~mincgstate();
    ae_bool &needf;
    ae_bool &needfg;
    ae_bool &xupdated;
    double &f;
    real_1d_array g;
    real_1d_array x;

};


/*************************************************************************

*************************************************************************/
class _mincgreport_owner
{
public:
    _mincgreport_owner();
    _mincgreport_owner(const _mincgreport_owner &rhs);
    _mincgreport_owner& operator=(const _mincgreport_owner &rhs);
    virtual ~_mincgreport_owner();
    alglib_impl::mincgreport* c_ptr();
    alglib_impl::mincgreport* c_ptr() const;
protected:
    alglib_impl::mincgreport *p_struct;
};
class mincgreport : public _mincgreport_owner
{
public:
    mincgreport();
    mincgreport(const mincgreport &rhs);
    mincgreport& operator=(const mincgreport &rhs);
    virtual ~mincgreport();
    ae_int_t &iterationscount;
    ae_int_t &nfev;
    ae_int_t &varidx;
    ae_int_t &terminationtype;

};

/*************************************************************************
This object stores nonlinear optimizer state.
You should use functions provided by MinBLEIC subpackage to work with this
object
*************************************************************************/
/**************************************************************************
이 객체는 비선형 최적화 기 상태를 저장합니다.
MinBLEIC 하위 패키지에서 제공하는 함수를 사용하여이 작업을 수행해야합니다.
목적
**************************************************************************/
class _minbleicstate_owner
{
public:
    _minbleicstate_owner();
    _minbleicstate_owner(const _minbleicstate_owner &rhs);
    _minbleicstate_owner& operator=(const _minbleicstate_owner &rhs);
    virtual ~_minbleicstate_owner();
    alglib_impl::minbleicstate* c_ptr();
    alglib_impl::minbleicstate* c_ptr() const;
protected:
    alglib_impl::minbleicstate *p_struct;
};
class minbleicstate : public _minbleicstate_owner
{
public:
    minbleicstate();
    minbleicstate(const minbleicstate &rhs);
    minbleicstate& operator=(const minbleicstate &rhs);
    virtual ~minbleicstate();
    ae_bool &needf;
    ae_bool &needfg;
    ae_bool &xupdated;
    double &f;
    real_1d_array g;
    real_1d_array x;

};


/*************************************************************************
This structure stores optimization report:
* IterationsCount           number of iterations
* NFEV                      number of gradient evaluations
* TerminationType           termination type (see below)

TERMINATION CODES

TerminationType field contains completion code, which can be:
  -7    gradient verification failed.
        See MinBLEICSetGradientCheck() for more information.
  -3    inconsistent constraints. Feasible point is
        either nonexistent or too hard to find. Try to
        restart optimizer with better initial approximation
   1    relative function improvement is no more than EpsF.
   2    relative step is no more than EpsX.
   4    gradient norm is no more than EpsG
   5    MaxIts steps was taken
   7    stopping conditions are too stringent,
        further improvement is impossible,
        X contains best point found so far.

ADDITIONAL FIELDS

There are additional fields which can be used for debugging:
* DebugEqErr                error in the equality constraints (2-norm)
* DebugFS                   f, calculated at projection of initial point
                            to the feasible set
* DebugFF                   f, calculated at the final point
* DebugDX                   |X_start-X_final|
*************************************************************************/
/**************************************************************************
이 구조체는 최적화 보고서를 저장합니다.
* IterationsCount 반복 횟수
* NFEV 그라디언트 평가 수
* 종단 유형 종단 유형 (아래 참조)
해지 코드
TerminationType 필드에는 다음과 같은 완료 코드가 포함됩니다.
  -7 그래디언트 확인에 실패했습니다.
        자세한 정보는 MinBLEICSetGradientCheck ()를 참조하십시오.
  -3 일관성없는 제약 조건. 실행할 수있는 요지는
        존재하지 않거나 찾기가 어렵습니다. 하려고 노력하다
        더 나은 초기 근사를 가진 최적화 프로그램 재시작
   1 상대적 기능 향상은 EpsF 이상입니다.
   2 상대 단계는 EpsX 이상입니다.
   4 그래디언트 표준은 EpsG 이상이 아닙니다.
   최대 5 단계가 수행되었습니다.
   7 개의 정지 조건은 너무 엄격합니다.
        더 이상의 개선은 불가능하다.
        X는 지금까지 발견 된 최상의 포인트를 포함합니다.
추가 필드
디버깅에 사용할 수있는 추가 필드가 있습니다.
* 동일 제약 조건 (2 표준)에서 DebugEqErr 오류
* 초기 점의 투영으로 계산 된 DebugFS f
                            실현 가능한 집합으로
* 최종 점에서 계산 된 DebugFF f
* DebugDX | X_start-X_final |
**************************************************************************/
class _minbleicreport_owner
{
public:
    _minbleicreport_owner();
    _minbleicreport_owner(const _minbleicreport_owner &rhs);
    _minbleicreport_owner& operator=(const _minbleicreport_owner &rhs);
    virtual ~_minbleicreport_owner();
    alglib_impl::minbleicreport* c_ptr();
    alglib_impl::minbleicreport* c_ptr() const;
protected:
    alglib_impl::minbleicreport *p_struct;
};
class minbleicreport : public _minbleicreport_owner
{
public:
    minbleicreport();
    minbleicreport(const minbleicreport &rhs);
    minbleicreport& operator=(const minbleicreport &rhs);
    virtual ~minbleicreport();
    ae_int_t &iterationscount;
    ae_int_t &nfev;
    ae_int_t &varidx;
    ae_int_t &terminationtype;
    double &debugeqerr;
    double &debugfs;
    double &debugff;
    double &debugdx;
    ae_int_t &debugfeasqpits;
    ae_int_t &debugfeasgpaits;
    ae_int_t &inneriterationscount;
    ae_int_t &outeriterationscount;

};

/*************************************************************************

*************************************************************************/
class _minlbfgsstate_owner
{
public:
    _minlbfgsstate_owner();
    _minlbfgsstate_owner(const _minlbfgsstate_owner &rhs);
    _minlbfgsstate_owner& operator=(const _minlbfgsstate_owner &rhs);
    virtual ~_minlbfgsstate_owner();
    alglib_impl::minlbfgsstate* c_ptr();
    alglib_impl::minlbfgsstate* c_ptr() const;
protected:
    alglib_impl::minlbfgsstate *p_struct;
};
class minlbfgsstate : public _minlbfgsstate_owner
{
public:
    minlbfgsstate();
    minlbfgsstate(const minlbfgsstate &rhs);
    minlbfgsstate& operator=(const minlbfgsstate &rhs);
    virtual ~minlbfgsstate();
    ae_bool &needf;
    ae_bool &needfg;
    ae_bool &xupdated;
    double &f;
    real_1d_array g;
    real_1d_array x;

};


/*************************************************************************

*************************************************************************/
class _minlbfgsreport_owner
{
public:
    _minlbfgsreport_owner();
    _minlbfgsreport_owner(const _minlbfgsreport_owner &rhs);
    _minlbfgsreport_owner& operator=(const _minlbfgsreport_owner &rhs);
    virtual ~_minlbfgsreport_owner();
    alglib_impl::minlbfgsreport* c_ptr();
    alglib_impl::minlbfgsreport* c_ptr() const;
protected:
    alglib_impl::minlbfgsreport *p_struct;
};
class minlbfgsreport : public _minlbfgsreport_owner
{
public:
    minlbfgsreport();
    minlbfgsreport(const minlbfgsreport &rhs);
    minlbfgsreport& operator=(const minlbfgsreport &rhs);
    virtual ~minlbfgsreport();
    ae_int_t &iterationscount;
    ae_int_t &nfev;
    ae_int_t &varidx;
    ae_int_t &terminationtype;

};

/*************************************************************************
This object stores nonlinear optimizer state.
You should use functions provided by MinQP subpackage to work with this
object
*************************************************************************/
/**************************************************************************
이 객체는 비선형 최적화 기 상태를 저장합니다.
MinQP 하위 패키지에서 제공하는 함수를 사용하여이 작업을 수행해야합니다.
목적
**************************************************************************/
class _minqpstate_owner
{
public:
    _minqpstate_owner();
    _minqpstate_owner(const _minqpstate_owner &rhs);
    _minqpstate_owner& operator=(const _minqpstate_owner &rhs);
    virtual ~_minqpstate_owner();
    alglib_impl::minqpstate* c_ptr();
    alglib_impl::minqpstate* c_ptr() const;
protected:
    alglib_impl::minqpstate *p_struct;
};
class minqpstate : public _minqpstate_owner
{
public:
    minqpstate();
    minqpstate(const minqpstate &rhs);
    minqpstate& operator=(const minqpstate &rhs);
    virtual ~minqpstate();

};


/*************************************************************************
This structure stores optimization report:
* InnerIterationsCount      number of inner iterations
* OuterIterationsCount      number of outer iterations
* NCholesky                 number of Cholesky decomposition
* NMV                       number of matrix-vector products
                            (only products calculated as part of iterative
                            process are counted)
* TerminationType           completion code (see below)

Completion codes:
* -5    inappropriate solver was used:
        * Cholesky solver for semidefinite or indefinite problems
        * Cholesky solver for problems with non-boundary constraints
* -4    BLEIC-QP algorithm found unconstrained direction
        of negative curvature (function is unbounded from
        below  even  under  constraints),  no  meaningful
        minimum can be found.
* -3    inconsistent constraints (or, maybe, feasible point is
        too hard to find). If you are sure that constraints are feasible,
        try to restart optimizer with better initial approximation.
* -1    solver error
*  4    successful completion
*  5    MaxIts steps was taken
*  7    stopping conditions are too stringent,
        further improvement is impossible,
        X contains best point found so far.
*************************************************************************/
/**************************************************************************
이 구조체는 최적화 보고서를 저장합니다.
* InnerIterationsCount 내부 반복 횟수
* OuterIterationsCount 외부 반복 횟수
* 콜레 스키 분해의 NCholesky 번호
매트릭스 - 벡터 제품의 NMV 번호
                            (반복 제품의 일부로 계산 된 제품 만
                            프로세스가 계산됩니다)
* 종료 유형 완료 코드 (아래 참조)
완료 코드 :
* -5 부적절한 해결사 사용 :
        * 세미 한정 또는 불명확 한 문제에 대한 oles레 스키 솔버
        * 경계가 아닌 제약 조건에 대한 Cholesky 솔버
* -4 BLEIC-QP 알고리즘이 제약없는 방향을 찾았습니다.
        음의 곡률 (함수는
        제약 하에서도 아래), 의미가 없음
        최소값을 찾을 수 있습니다.
* -3 일치하지 않는 제약 조건 (또는 어쩌면 실행 가능 시점이
        너무 찾기 힘들다). 제약이 가능하다고 확신한다면,
        더 나은 초기 근사값으로 최적화 프로그램을 다시 시작하십시오.
* -1 솔버 오류
* 4 성공적인 완료
* 5 MaxIts 단계가 수행되었습니다.
* 7 정지 조건은 너무 엄격합니다.
        더 이상의 개선은 불가능하다.
        X는 지금까지 발견 된 최상의 포인트를 포함합니다.
**************************************************************************/
class _minqpreport_owner
{
public:
    _minqpreport_owner();
    _minqpreport_owner(const _minqpreport_owner &rhs);
    _minqpreport_owner& operator=(const _minqpreport_owner &rhs);
    virtual ~_minqpreport_owner();
    alglib_impl::minqpreport* c_ptr();
    alglib_impl::minqpreport* c_ptr() const;
protected:
    alglib_impl::minqpreport *p_struct;
};
class minqpreport : public _minqpreport_owner
{
public:
    minqpreport();
    minqpreport(const minqpreport &rhs);
    minqpreport& operator=(const minqpreport &rhs);
    virtual ~minqpreport();
    ae_int_t &inneriterationscount;
    ae_int_t &outeriterationscount;
    ae_int_t &nmv;
    ae_int_t &ncholesky;
    ae_int_t &terminationtype;

};

/*************************************************************************
Levenberg-Marquardt optimizer.

This structure should be created using one of the MinLMCreate???()
functions. You should not access its fields directly; use ALGLIB functions
to work with it.
*************************************************************************/
/**************************************************************************
Levenberg-Marquardt 최적화 도구.
이 구조는 MinLMCreate ??? () 중 하나를 사용하여 만들어야합니다.
기능. 필드에 직접 액세스하면 안됩니다. ALGLIB 함수 사용
그것으로 작업 할 수 있습니다.
**************************************************************************/
class _minlmstate_owner
{
public:
    _minlmstate_owner();
    _minlmstate_owner(const _minlmstate_owner &rhs);
    _minlmstate_owner& operator=(const _minlmstate_owner &rhs);
    virtual ~_minlmstate_owner();
    alglib_impl::minlmstate* c_ptr();
    alglib_impl::minlmstate* c_ptr() const;
protected:
    alglib_impl::minlmstate *p_struct;
};
class minlmstate : public _minlmstate_owner
{
public:
    minlmstate();
    minlmstate(const minlmstate &rhs);
    minlmstate& operator=(const minlmstate &rhs);
    virtual ~minlmstate();
    ae_bool &needf;
    ae_bool &needfg;
    ae_bool &needfgh;
    ae_bool &needfi;
    ae_bool &needfij;
    ae_bool &xupdated;
    double &f;
    real_1d_array fi;
    real_1d_array g;
    real_2d_array h;
    real_2d_array j;
    real_1d_array x;

};


/*************************************************************************
Optimization report, filled by MinLMResults() function

FIELDS:
* TerminationType, completetion code:
    * -7    derivative correctness check failed;
            see Rep.WrongNum, Rep.WrongI, Rep.WrongJ for
            more information.
    *  1    relative function improvement is no more than
            EpsF.
    *  2    relative step is no more than EpsX.
    *  4    gradient is no more than EpsG.
    *  5    MaxIts steps was taken
    *  7    stopping conditions are too stringent,
            further improvement is impossible
* IterationsCount, contains iterations count
* NFunc, number of function calculations
* NJac, number of Jacobi matrix calculations
* NGrad, number of gradient calculations
* NHess, number of Hessian calculations
* NCholesky, number of Cholesky decomposition calculations
*************************************************************************/
/**************************************************************************
MinLMResults () 함수로 채워지는 최적화 보고서
전지:
* 종단 유형, 완성 코드 :
    * -7 미분 정확도 검사에 실패했습니다.
            Rep.WrongNum, Rep.WrongI, Rep.WrongJ를 참조하십시오.
            자세한 정보.
    * 1 상대 기능 개선은
            EpsF.
    * 2 상대 단계는 EpsX 이상입니다.
    * 4 그래디언트는 EpsG 이상입니다.
    * 5 MaxIts 단계가 수행되었습니다.
    * 7 정지 조건은 너무 엄격합니다.
            더 이상의 개선은 불가능하다.
* IterationsCount, 반복 횟수 포함
* NFunc, 함수 계산 수
* NJac, Jacobi 행렬 계산의 수
* NGrad, 그라디언트 계산 수
* NHess, 헤 시안 계산의 수
* NCholesky, 콜레 스키 분해 계산 횟수
**************************************************************************/
class _minlmreport_owner
{
public:
    _minlmreport_owner();
    _minlmreport_owner(const _minlmreport_owner &rhs);
    _minlmreport_owner& operator=(const _minlmreport_owner &rhs);
    virtual ~_minlmreport_owner();
    alglib_impl::minlmreport* c_ptr();
    alglib_impl::minlmreport* c_ptr() const;
protected:
    alglib_impl::minlmreport *p_struct;
};
class minlmreport : public _minlmreport_owner
{
public:
    minlmreport();
    minlmreport(const minlmreport &rhs);
    minlmreport& operator=(const minlmreport &rhs);
    virtual ~minlmreport();
    ae_int_t &iterationscount;
    ae_int_t &terminationtype;
    ae_int_t &funcidx;
    ae_int_t &varidx;
    ae_int_t &nfunc;
    ae_int_t &njac;
    ae_int_t &ngrad;
    ae_int_t &nhess;
    ae_int_t &ncholesky;

};

/*************************************************************************

*************************************************************************/
class _minasastate_owner
{
public:
    _minasastate_owner();
    _minasastate_owner(const _minasastate_owner &rhs);
    _minasastate_owner& operator=(const _minasastate_owner &rhs);
    virtual ~_minasastate_owner();
    alglib_impl::minasastate* c_ptr();
    alglib_impl::minasastate* c_ptr() const;
protected:
    alglib_impl::minasastate *p_struct;
};
class minasastate : public _minasastate_owner
{
public:
    minasastate();
    minasastate(const minasastate &rhs);
    minasastate& operator=(const minasastate &rhs);
    virtual ~minasastate();
    ae_bool &needfg;
    ae_bool &xupdated;
    double &f;
    real_1d_array g;
    real_1d_array x;

};


/*************************************************************************

*************************************************************************/
class _minasareport_owner
{
public:
    _minasareport_owner();
    _minasareport_owner(const _minasareport_owner &rhs);
    _minasareport_owner& operator=(const _minasareport_owner &rhs);
    virtual ~_minasareport_owner();
    alglib_impl::minasareport* c_ptr();
    alglib_impl::minasareport* c_ptr() const;
protected:
    alglib_impl::minasareport *p_struct;
};
class minasareport : public _minasareport_owner
{
public:
    minasareport();
    minasareport(const minasareport &rhs);
    minasareport& operator=(const minasareport &rhs);
    virtual ~minasareport();
    ae_int_t &iterationscount;
    ae_int_t &nfev;
    ae_int_t &terminationtype;
    ae_int_t &activeconstraints;

};









/*************************************************************************
        NONLINEAR CONJUGATE GRADIENT METHOD

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by using one of  the
nonlinear conjugate gradient methods.

These CG methods are globally convergent (even on non-convex functions) as
long as grad(f) is Lipschitz continuous in  a  some  neighborhood  of  the
L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinCGCreate() call
2. User tunes solver parameters with MinCGSetCond(), MinCGSetStpMax() and
   other functions
3. User calls MinCGOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinCGResults() to get solution
5. Optionally, user may call MinCGRestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinCGRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   starting point, array[0..N-1].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
        비 윤리적 준거법
기술:
서브 루틴은 N 개의 인수의 함수 F (x)를
비선형 공액 그라디언트 법.
이러한 CG 방법은 (비 볼록 함수에서도) 전역 적으로 수렴됩니다.
오래 동안 grad (f)는 립시츠 (Lipschitz)가
L = {x : f (x) <= f (x0)}.
요구 사항 :
알고리즘은 작동 중에 다음 정보를 요청합니다.
* 주어진 점 X에서 함수 값 F와 그 기울기 G (동시에)
용법:
1. MinCGCreate () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 MinCGSetCond (), MinCGSetStpMax () 및 Solver 매개 변수를 조정합니다.
   다른 기능들
3. 알고리즘 상태를 취하는 MinCGOptimize () 함수를 호출하고
   F / G를 계산하는 콜백 함수에 대한 포인터 (델리게이트 등).
4. 사용자가 MinCGResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 MinCGRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 N이지만 다른 시작점 및 / 또는 다른 기능을 사용합니다.
   MinCGRestartFrom ()은 이미 초기화 된 구조를 다시 사용할 수있게합니다.
입력 매개 변수 :
    N - 문제 차원, N> 0 :
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    X - 시작점, 배열 [0..N-1].
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 25.03.2010 Bochkanov Sergey
**************************************************************************/
void mincgcreate(const ae_int_t n, const real_1d_array &x, mincgstate &state);
void mincgcreate(const real_1d_array &x, mincgstate &state);


/*************************************************************************
The subroutine is finite difference variant of MinCGCreate(). It uses
finite differences in order to differentiate target function.

Description below contains information which is specific to this function
only. We recommend to read comments on MinCGCreate() in order to get more
information about creation of CG optimizer.

INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   starting point, array[0..N-1].
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. algorithm uses 4-point central formula for differentiation.
2. differentiation step along I-th axis is equal to DiffStep*S[I] where
   S[] is scaling vector which can be set by MinCGSetScale() call.
3. we recommend you to use moderate values of  differentiation  step.  Too
   large step will result in too large truncation  errors, while too small
   step will result in too large numerical  errors.  1.0E-6  can  be  good
   value to start with.
4. Numerical  differentiation  is   very   inefficient  -   one   gradient
   calculation needs 4*N function evaluations. This function will work for
   any N - either small (1...10), moderate (10...100) or  large  (100...).
   However, performance penalty will be too severe for any N's except  for
   small ones.
   We should also say that code which relies on numerical  differentiation
   is  less  robust  and  precise.  L-BFGS  needs  exact  gradient values.
   Imprecise  gradient may slow down  convergence,  especially  on  highly
   nonlinear problems.
   Thus  we  recommend to use this function for fast prototyping on small-
   dimensional problems only, and to implement analytical gradient as soon
   as possible.

  -- ALGLIB --
     Copyright 16.05.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
서브 루틴은 MinCGCreate ()의 유한 차분 변형입니다. 그것은 사용
목표 함수를 구별하기위한 유한 한 차이.
아래 설명에는이 기능과 관련된 정보가 포함되어 있습니다.
만. 더 많은 정보를 얻으려면 MinCGCreate ()에 대한 의견을 읽는 것이 좋습니다.
CG 최적화 프로그램 작성에 대한 정보.
입력 매개 변수 :
    N - 문제 차원, N> 0 :
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    X - 시작점, 배열 [0..N-1].
    DiffStep- 차별화 단계,> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. 알고리즘은 4 점 중앙 공식을 차별화에 사용합니다.
2. I 번째 축을 따른 미분 단계는 DiffStep * S [I]와 같습니다.
   S []는 MinCGSetScale () 호출로 설정할 수있는 스케일링 벡터입니다.
3. 차별화 단계의 중간 값을 사용하는 것이 좋습니다. 너무
   큰 단계는 너무 큰 잘라 내기 오류를 발생 시키지만 너무 작 으면
   단계를 수행하면 수치 오류가 너무 커집니다. 1.0E-6은 좋을 수 있습니다.
   시작 값.
4. 수치 차별화는 매우 비효율적입니다. 하나의 기울기
   계산에는 4 * N 함수 평가가 필요합니다. 이 함수는
   어떤 N - 작은 (1 ... 10), 보통 (10 ... 100) 또는 큰 (100 ...).
   그러나 성능상의 불이익은 N을 제외하고는
   작은 것들.
   우리는 또한 수치 차별화에 의존하는 코드
   덜 강력하고 정밀합니다. L-BFGS에는 정확한 그래디언트 값이 필요합니다.
   정확하지 않은 그라디언트가 수렴 속도를 늦출 수 있습니다.
   비선형 문제.
   따라서이 기능을 사용하여 소형 프로토 타이핑에 대한 빠른 프로토 타이핑을 권장합니다.
   차원 문제 만 해결하고 곧 분석 구배를 구현할 수 있습니다.
   가능한 한.
  - ALGLIB -
     Copyright 16.05.2011 Bochkanov Sergey
**************************************************************************/
void mincgcreatef(const ae_int_t n, const real_1d_array &x, const double diffstep, mincgstate &state);
void mincgcreatef(const real_1d_array &x, const double diffstep, mincgstate &state);


/*************************************************************************
This function sets stopping conditions for CG optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                |v|<EpsG is satisfied, where:
                * |.| means Euclidian norm
                * v - scaled gradient vector, v[i]=g[i]*s[i]
                * g - gradient
                * s - scaling coefficients set by MinCGSetScale()
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |v|<=EpsX is fulfilled, where:
                * |.| means Euclidian norm
                * v - scaled step vector, v[i]=dx[i]/s[i]
                * dx - ste pvector, dx=X(k+1)-X(k)
                * s - scaling coefficients set by MinCGSetScale()
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은 CG 최적화 알고리즘의 정지 조건을 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsG -> = 0
                서브 루틴은 조건
                | v | <EpsG가 만족되면,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 그래디언트 벡터, v [i] = g [i] * s [i]
                * g - 그래디언트
                * s - MinCGSetScale ()에 의해 설정된 스케일링 계수
    EpsF -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                조건 | F (k + 1) -F (k) | <= EpsF * max {| F (k) |, | F (k + 1) |, 1}
                만족한다.
    EpsX -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                | v | <= EpsX 조건이 충족됩니다. 여기서,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 스텝 벡터, v [i] = dx [i] / s [i]
                * dx - ste pvector, dx = X (k + 1) -X (k)
                * s - MinCGSetScale ()에 의해 설정된 스케일링 계수
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다.
EpsG = 0, EpsF = 0, EpsX = 0 및 MaxIts = 0 (동시에)을 전달하면
자동 정지 기준 선택 (작은 EpsX).
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void mincgsetcond(const mincgstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
This function sets scaling coefficients for CG optimizer.

ALGLIB optimizers use scaling matrices to test stopping  conditions  (step
size and gradient are scaled before comparison with tolerances).  Scale of
the I-th variable is a translation invariant measure of:
a) "how large" the variable is
b) how large the step should be to make significant changes in the function

Scaling is also used by finite difference variant of CG optimizer  -  step
along I-th axis is equal to DiffStep*S[I].

In   most   optimizers  (and  in  the  CG  too)  scaling is NOT a form  of
preconditioning. It just  affects  stopping  conditions.  You  should  set
preconditioner by separate call to one of the MinCGSetPrec...() functions.

There  is  special  preconditioning  mode, however,  which  uses   scaling
coefficients to form diagonal preconditioning matrix. You  can  turn  this
mode on, if you want.   But  you should understand that scaling is not the
same thing as preconditioning - these are two different, although  related
forms of tuning solver.

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    S       -   array[N], non-zero scaling coefficients
                S[i] may be negative, sign doesn't matter.

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 CG 최적화 프로그램의 스케일링 계수를 설정합니다.
ALGLIB 최적화 프로그램은 스케일링 매트릭스를 사용하여 정지 조건을 테스트합니다 (단계
크기 및 그래디언트는 공차와 비교하기 전에 크기가 조정됩니다.) 규모
I 번째 변수는 다음에 대한 변환 불변성 측정 값입니다.
a) 변수의 "크기"
b) 함수에서 중요한 변화를 만드는 단계는 얼마나 커야 하는가?
스케일링은 CG 옵티 마이저의 유한 차분 변형에서도 사용됩니다. - 단계
I 번째 축을 따라 DiffStep * S [I]와 같습니다.
대부분의 옵티 마이저 (및 CG에서도) 스케일링은
전제 조건. 그것은 단지 멈추는 조건에 영향을 미칩니다. 설정해야합니다.
MinCGSetPrec ... () 함수 중 하나를 별도로 호출하여 프리 컨디셔너를 호출합니다.
그러나 특수 preconditioning 모드는 스케일링을 사용합니다.
계수는 대각선 전처리 행렬을 형성한다. 너는 이것을 돌릴 수있다.
모드를 켜십시오. 그러나 스케일링은
전제 조건 (preconditioning)과 같은 것 - 이것은 서로 다르지만 관련이있다.
튜닝 솔버의 형태.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    S - 배열 [N], 0이 아닌 스케일링 계수
                S [i]는 음수 일 수 있습니다. 부호는 중요하지 않습니다.
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
**************************************************************************/
void mincgsetscale(const mincgstate &state, const real_1d_array &s);


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinCGOptimize ()에 제공됩니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void mincgsetxrep(const mincgstate &state, const bool needxrep);


/*************************************************************************
This function sets CG algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    CGType  -   algorithm type:
                * -1    automatic selection of the best algorithm
                * 0     DY (Dai and Yuan) algorithm
                * 1     Hybrid DY-HS algorithm

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은 CG 알고리즘을 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    CGType - 알고리즘 유형 :
                최고의 알고리즘의 * 1 자동 선택
                * 0 DY (Dai and Yuan) 알고리즘
                * 1 하이브리드 DY-HS 알고리즘
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void mincgsetcgtype(const mincgstate &state, const ae_int_t cgtype);


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

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
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
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void mincgsetstpmax(const mincgstate &state, const double stpmax);


/*************************************************************************
This function allows to suggest initial step length to the CG algorithm.

Suggested  step  length  is used as starting point for the line search. It
can be useful when you have  badly  scaled  problem,  i.e.  when  ||grad||
(which is used as initial estimate for the first step) is many  orders  of
magnitude different from the desired step.

Line search  may  fail  on  such problems without good estimate of initial
step length. Imagine, for example, problem with ||grad||=10^50 and desired
step equal to 0.1 Line  search function will use 10^50  as  initial  step,
then  it  will  decrease step length by 2 (up to 20 attempts) and will get
10^44, which is still too large.

This function allows us to tell than line search should  be  started  from
some moderate step length, like 1.0, so algorithm will be able  to  detect
desired step length in a several searches.

Default behavior (when no step is suggested) is to use preconditioner,  if
it is available, to generate initial estimate of step length.

This function influences only first iteration of algorithm. It  should  be
called between MinCGCreate/MinCGRestartFrom() call and MinCGOptimize call.
Suggested step is ignored if you have preconditioner.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state.
    Stp     -   initial estimate of the step length.
                Can be zero (no estimate).

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 CG 알고리즘의 초기 단계 길이를 제안합니다.
제안 된 단계 길이는 회선 검색의 시작점으로 사용됩니다. 그것
잘못 확장 된 문제가있을 때 유용 할 수 있습니다. 예를 들어 || grad ||
(첫 번째 단계의 초기 견적으로 사용됨)는
크기가 원하는 단계와 다릅니다.
이러한 문제에 대한 회선 검색은 초기 추정치가 좋지 않으면 실패 할 수 있습니다.
스텝 길이. 예를 들어, || grad || = 10 ^ 50의 문제를 상상해보십시오.
0.1 단계와 같은 단계 라인 검색 기능은 초기 단계로 10 ^ 50을 사용합니다.
다음 단계 길이를 2 줄이며 (최대 20 회 시도)
10 ^ 44, 여전히 너무 큽니다.
이 함수는 라인 검색이 시작되어야 함을 알려주는 역할을합니다.
1.0과 같이 약간의 단계 길이로 알고리즘이 탐지 할 수 있습니다.
여러 검색에서 원하는 단계 길이.
기본 동작 (단계가 제안되지 않은 경우)은 전치 조건을 사용하는 것입니다. if
스텝 길이의 초기 추정치를 생성하는 것이 가능하다.
이 함수는 알고리즘의 첫 번째 반복에만 영향을 미칩니다. 그것은해야한다
MinCGCreate / MinCGRestartFrom () 호출과 MinCGOptimize 호출 사이에서 호출됩니다.
선행 조건이있는 경우 제안 단계가 무시됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 데 사용되는 구조체입니다.
    Stp - 스텝 길이의 초기 추정치.
                0 일 수 있습니다 (추정치 없음).
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
**************************************************************************/
void mincgsuggeststep(const mincgstate &state, const double stp);


/*************************************************************************
Modification of the preconditioner: preconditioning is turned off.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
선행 조건의 수정 : 선행 조건이 해제됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참고 : 알고리즘 중에 사전 조건을 "즉시"변경할 수 있습니다.
반복.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void mincgsetprecdefault(const mincgstate &state);


/*************************************************************************
Modification  of  the  preconditioner:  diagonal of approximate Hessian is
used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    D       -   diagonal of the approximate Hessian, array[0..N-1],
                (if larger, only leading N elements are used).

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

NOTE 2: D[i] should be positive. Exception will be thrown otherwise.

NOTE 3: you should pass diagonal of approximate Hessian - NOT ITS INVERSE.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 대략적인 헤 시안의 대각선은 다음과 같습니다.
익숙한.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    D - 근사 헤센의 대각선, array [0..N-1],
                (더 큰 경우 N 개의 주요 요소 만 사용됨).
참고 : 알고리즘 중에 사전 조건을 "즉시"변경할 수 있습니다.
반복.
주 2 : D [i]는 양수이어야한다. 그렇지 않으면 예외가 발생합니다.
NOTE 3 : 대략적인 Hessian의 대각선을 통과해야한다 - ITS INVERSE가 아님.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void mincgsetprecdiag(const mincgstate &state, const real_1d_array &d);


/*************************************************************************
Modification of the preconditioner: scale-based diagonal preconditioning.

This preconditioning mode can be useful when you  don't  have  approximate
diagonal of Hessian, but you know that your  variables  are  badly  scaled
(for  example,  one  variable is in [1,10], and another in [1000,100000]),
and most part of the ill-conditioning comes from different scales of vars.

In this case simple  scale-based  preconditioner,  with H[i] = 1/(s[i]^2),
can greatly improve convergence.

IMPRTANT: you should set scale of your variables with MinCGSetScale() call
(before or after MinCGSetPrecScale() call). Without knowledge of the scale
of your variables scale-based preconditioner will be just unit matrix.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 스케일 기반 대각선 전제 조건.
이 사전 조절 모드는 근사치가 없을 때 유용 할 수 있습니다.
헤 시안 (Hessian)의 대각선이지만, 변수가 잘못 조정 된 것을 알고 있습니다.
(예를 들어, 하나의 변수는 [1,10]에 있고 다른 변수는 [1000,100000]에 있음)
그리고 불량 조절의 대부분은 다양한 범위의 바에서 비롯됩니다.
이 경우 H [i] = 1 / (s [i] ^ 2) 인 간단한 스케일 기반 전처리 기가
융합을 크게 향상시킬 수 있습니다.
IMPRTANT : MinCGSetScale () 호출로 변수의 스케일을 설정해야합니다.
(MinCGSetPrecScale () 호출 전후). 규모에 대한 지식이 없으면
변수의 스케일 기반 전처리 기는 단위 매트릭스 일뿐입니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참고 : 알고리즘 중에 사전 조건을 "즉시"변경할 수 있습니다.
반복.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
*************************************************************************/
void mincgsetprecscale(const mincgstate &state);


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
bool mincgiteration(const mincgstate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear optimizer

These functions accept following parameters:
    state   -   algorithm state
    func    -   callback which calculates function (or merit function)
                value func at given point x
    grad    -   callback which calculates function (or merit function)
                value func and gradient grad at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL

NOTES:

1. This function has two different implementations: one which  uses  exact
   (analytical) user-supplied  gradient, and one which uses function value
   only  and  numerically  differentiates  function  in  order  to  obtain
   gradient.

   Depending  on  the  specific  function  used to create optimizer object
   (either MinCGCreate()  for analytical gradient  or  MinCGCreateF()  for
   numerical differentiation) you should  choose  appropriate  variant  of
   MinCGOptimize() - one which accepts function AND gradient or one  which
   accepts function ONLY.

   Be careful to choose variant of MinCGOptimize()  which  corresponds  to
   your optimization scheme! Table below lists different  combinations  of
   callback (function/gradient) passed  to  MinCGOptimize()  and  specific
   function used to create optimizer.


                  |         USER PASSED TO MinCGOptimize()
   CREATED WITH   |  function only   |  function and gradient
   ------------------------------------------------------------
   MinCGCreateF() |     work                FAIL
   MinCGCreate()  |     FAIL                work

   Here "FAIL" denotes inappropriate combinations  of  optimizer  creation
   function and MinCGOptimize() version. Attemps to use  such  combination
   (for  example,  to create optimizer with  MinCGCreateF()  and  to  pass
   gradient information to MinCGOptimize()) will lead to  exception  being
   thrown. Either  you  did  not  pass  gradient when it WAS needed or you
   passed gradient when it was NOT needed.

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey

*************************************************************************/
/**************************************************************************
이 함수 계열은 비선형 최적화 알고리즘의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    func - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func
    grad - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func 및 gradient grad
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
노트:
1.이 함수는 두 가지 구현이 있습니다 :
   (분석적인) 사용자 제공 그래디언트와 함수 값을 사용하는 그래디언트
   오직 함수를 수치 적으로 구별하여 구하기 위해
   구배.
   최적화 프로그램 개체를 만드는 데 사용 된 특정 함수에 따라
   (분석 그라디언트의 경우 MinCGCreate () 또는 분석 그라디언트의 경우 MinCGCreateF ()
   수치 차별화) 당신은 적절한 변형을 선택해야합니다.
   MinCGOptimize () - 함수 및 그라디언트를 허용하는 함수 또는
   기능 만 허용합니다.
   MinCGOptimize ()의 변형을 선택하는 것에주의하십시오.
   귀하의 최적화 계획! 아래 표에는
   MinCGOptimize ()에 전달 된 콜백 (함수 / 그라디언트)
   최적화 프로그램을 만드는 데 사용되는 함수.
                  | 사용자가 MinCGOptimize ()에 전달했습니다.
   창조 된 | 기능 만 | 함수 및 그래디언트
   -------------------------------------------------- ----------
   MinCGCreateF () | 직장 불합격
   MinCGCreate () | FAIL 작업
   여기서 "FAIL"은 최적화 도구 작성의 부적절한 조합을 나타냅니다.
   함수 및 MinCGOptimize () 버전. 그러한 조합을 사용하려는 시도
   (예를 들어, MinCGCreateF ()를 사용하여 최적화 프로그램을 작성한 후
   그라디언트 정보를 MinCGOptimize ()로 보내면 예외가 발생합니다.
   던져. 당신이 그라데이션을 필요로 할 때 패스하지 않았거나
   필요하지 않을 때 그라디언트가 전달되었습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.04.2009
**************************************************************************/
void mincgoptimize(mincgstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void mincgoptimize(mincgstate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);


/*************************************************************************
Conjugate gradient results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -7    gradient verification failed.
                            See MinCGSetGradientCheck() for more information.
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible,
                            we return best X found so far
                    *  8    terminated by user
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
그라디언트 결과 공액
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -7 그래디언트 확인에 실패했습니다.
                            자세한 정보는 MinCGSetGradientCheck ()를 참조하십시오.
                    * 1 상대 기능 개선은
                            EpsF.
                    * 2 상대 단계는 EpsX 이상입니다.
                    * 4 그래디언트 표준은 EpsG 이상입니다.
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 정지 조건은 너무 엄격합니다.
                            더 이상의 개선은 불가능하다.
                            우리는 지금까지 발견 된 최고의 X를 반환합니다.
                    * 8 사용자에 의해 종료 됨
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                * NFEV countains 함수 계산 횟수
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.04.2009
**************************************************************************/
void mincgresults(const mincgstate &state, real_1d_array &x, mincgreport &rep);


/*************************************************************************
Conjugate gradient results

Buffered implementation of MinCGResults(), which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
그라디언트 결과 공액
미리 할당 된 버퍼를 사용하는 MinCGResults ()의 버퍼 된 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.04.2009
**************************************************************************/
void mincgresultsbuf(const mincgstate &state, real_1d_array &x, mincgreport &rep);


/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 새로운 지점에서 CG 알고리즘을 재시작합니다. 모든 최적화
매개 변수는 변경되지 않습니다.
이 함수는 여러 개의 최적화 문제를 해결할 수 있습니다.
오브젝트 재 할당 패널티가없는 동일한 수의 치수가 있어야합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 데 사용되는 구조체입니다.
    X - 새로운 출발점.
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
**************************************************************************/
void mincgrestartfrom(const mincgstate &state, const real_1d_array &x);


/*************************************************************************

This  subroutine  turns  on  verification  of  the  user-supplied analytic
gradient:
* user calls this subroutine before optimization begins
* MinCGOptimize() is called
* prior to  actual  optimization, for each component  of  parameters being
  optimized X[i] algorithm performs following steps:
  * two trial steps are made to X[i]-TestStep*S[i] and X[i]+TestStep*S[i],
    where X[i] is i-th component of the initial point and S[i] is a  scale
    of i-th parameter
  * F(X) is evaluated at these trial points
  * we perform one more evaluation in the middle point of the interval
  * we  build  cubic  model using function values and derivatives at trial
    points and we compare its prediction with actual value in  the  middle
    point
  * in case difference between prediction and actual value is higher  than
    some predetermined threshold, algorithm stops with completion code -7;
    Rep.VarIdx is set to index of the parameter with incorrect derivative.
* after verification is over, algorithm proceeds to the actual optimization.

NOTE 1: verification  needs  N (parameters count) gradient evaluations. It
        is very costly and you should use  it  only  for  low  dimensional
        problems,  when  you  want  to  be  sure  that  you've   correctly
        calculated  analytic  derivatives.  You  should  not use it in the
        production code (unless you want to check derivatives provided  by
        some third party).

NOTE 2: you  should  carefully  choose  TestStep. Value which is too large
        (so large that function behaviour is significantly non-cubic) will
        lead to false alarms. You may use  different  step  for  different
        parameters by means of setting scale with MinCGSetScale().

NOTE 3: this function may lead to false positives. In case it reports that
        I-th  derivative was calculated incorrectly, you may decrease test
        step  and  try  one  more  time  - maybe your function changes too
        sharply  and  your  step  is  too  large for such rapidly chanding
        function.

INPUT PARAMETERS:
    State       -   structure used to store algorithm state
    TestStep    -   verification step:
                    * TestStep=0 turns verification off
                    * TestStep>0 activates verification

  -- ALGLIB --
     Copyright 31.05.2012 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 사용자가 제공 한 분석의 검증을 켭니다.
구배:
* 최적화가 시작되기 전에 사용자가이 서브 루틴 호출
* MinCGOptimize ()가 호출됩니다.
* 매개 변수의 각 구성 요소에 대한 실제 최적화 이전
  최적화 된 X [i] 알고리즘은 다음 단계를 수행합니다.
  * X [i] -TestStep * S [i] 및 X [i] + TestStep * S [i]에 대해 두 번의 시험 단계가 수행됩니다.
    여기서 X [i]는 초기 점의 i 번째 구성 요소이고 S [i]는 스케일입니다
    i 번째 매개 변수
  * F (X)는 이러한 시험 포인트에서 평가됩니다.
  * 간격의 중간 지점에서 또 하나의 평가를 수행합니다.
  * 우리는 함수 값과 파생 상품을 사용하여 삼차원 모델을 시험해 보았다.
    우리는 예측치를 중간의 실제 값과 비교합니다
    포인트
  * 예상 값과 실제 값의 차이가
    소정의 소정의 임계 값, 알고리즘은 완료 코드 -7로 정지한다;
    Rep.VarIdx가 잘못된 파생어로 매개 변수의 인덱스로 설정됩니다.
* 검증이 끝나면 알고리즘은 실제 최적화로 진행합니다.
주 1 : 검증은 N (매개 변수 개수) 그라디언트 평가가 필요하다. 그것
        매우 비용이 많이 들며 낮은 차원에서만 사용해야합니다.
        문제, 당신이 당신이 올바르게했는지 알고 싶을 때
        계산 된 파생 상품. 당신은
        생산 코드 (귀하가 제공 한 파생 상품을 확인하고 싶지 않은 경우)
        제 3 자).
참고 2 : TestStep을 신중하게 선택해야합니다. 너무 큰 값
        (너무 커서 함수의 동작은 상당히 비 큐빅이다.)
        거짓 경보로 연결됩니다. 다른 단계를 사용할 수도 있습니다.
        MinCGSetScale ()을 사용하여 축척을 설정하여 매개 변수를 설정하십시오.
참고 3 :이 기능은 위양성을 유발할 수 있습니다. 보고서에
        I 차수 미분이 잘못 계산되었으므로 테스트를 줄일 수 있습니다.
        한 번 더 시도해보십시오. 아마도 기능이 변경 될 수도 있습니다.
        급격하게 그리고 당신의 발걸음이 그렇게 급속히 챈드하기에는 너무 큽니다.
        기능.
입력 매개 변수 :
    상태 - 알고리즘 상태를 저장하는 데 사용되는 구조
    TestStep - 확인 단계 :
                    * TestStep = 0으로 설정하면 인증이 해제됩니다.
                    * TestStep> 0으로 인증이 활성화됩니다.
  - ALGLIB -
     Copyright 31.05.2012 Bochkanov Sergey
**************************************************************************/
void mincgsetgradientcheck(const mincgstate &state, const double teststep);

/*************************************************************************
                     BOUND CONSTRAINED OPTIMIZATION
       WITH ADDITIONAL LINEAR EQUALITY AND INEQUALITY CONSTRAINTS

DESCRIPTION:
The  subroutine  minimizes  function   F(x)  of N arguments subject to any
combination of:
* bound constraints
* linear inequality constraints
* linear equality constraints

REQUIREMENTS:
* user must provide function value and gradient
* starting point X0 must be feasible or
  not too far away from the feasible set
* grad(f) must be Lipschitz continuous on a level set:
  L = { x : f(x)<=f(x0) }
* function must be defined everywhere on the feasible set F

USAGE:

Constrained optimization if far more complex than the unconstrained one.
Here we give very brief outline of the BLEIC optimizer. We strongly recommend
you to read examples in the ALGLIB Reference Manual and to read ALGLIB User Guide
on optimization, which is available at http://www.alglib.net/optimization/

1. User initializes algorithm state with MinBLEICCreate() call

2. USer adds boundary and/or linear constraints by calling
   MinBLEICSetBC() and MinBLEICSetLC() functions.

3. User sets stopping conditions with MinBLEICSetCond().

4. User calls MinBLEICOptimize() function which takes algorithm  state and
   pointer (delegate, etc.) to callback function which calculates F/G.

5. User calls MinBLEICResults() to get solution

6. Optionally user may call MinBLEICRestartFrom() to solve another problem
   with same N but another starting point.
   MinBLEICRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size ofX
    X       -   starting point, array[N]:
                * it is better to set X to a feasible point
                * but X can be infeasible, in which case algorithm will try
                  to find feasible point first, using X as initial
                  approximation.

OUTPUT PARAMETERS:
    State   -   structure stores algorithm state

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
                     제한된 최적화
       추가 선형 평형 및 비등 제한이있는
기술:
서브 루틴은 N 개 인수의 함수 F (x)를 최소화합니다.
조합 :
* 경계 제약
* 선형 부등식 제약
* 선형 동등 제약
요구 사항 :
* 사용자는 함수 값과 기울기를 제공해야합니다.
* 출발점 X0은 실행 가능해야합니다.
  실행 가능한 집합과 너무 멀리 떨어져 있지 않다.
* grad (f)는 레벨 세트에서 Lipschitz 연속이어야합니다.
  L = {x : f (x) <= f (x0)}
* 함수는 가능한 집합 F에있는 모든 곳에서 정의되어야합니다.
용법:
제한되지 않은 최적화보다 훨씬 복잡한 경우 제한된 최적화.
여기서 우리는 BLEIC 최적화 도구에 대한 간단한 개요를 제공합니다. 우리는 강력하게 추천한다.
ALGLIB Reference Manual에서 예제를 읽고 ALGLIB User Guide를 읽으십시오.
최적화에 관한 내용은 http://www.alglib.net/optimization/에서 확인할 수 있습니다.
1. MinBLEICCreate () 호출로 알고리즘 상태를 초기화합니다.
2. USer가 호출하여 경계 및 / 또는 선형 제약 조건을 추가합니다.
   MinBLEICSetBC () 및 MinBLEICSetLC () 함수.
3. 사용자가 MinBLEICSetCond ()로 정지 조건을 설정합니다.
4. 사용자는 알고리즘 상태를 취하는 MinBLEICOptimize () 함수를 호출하고
   F / G를 계산하는 콜백 함수에 대한 포인터 (델리게이트 등).
5. 사용자가 MinBLEICResults ()를 호출하여 솔루션을 얻습니다.
6. 선택적으로 사용자는 MinBLEICRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   같은 N이지만 다른 출발점이 있습니다.
   MinBLEICRestartFrom ()은 이미 초기화 된 구조를 다시 사용할 수있게합니다.
입력 매개 변수 :
    N - 문제 차원, N> 0 :
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 주어지지 않은 경우, X의 크기로부터 자동으로 결정됩니다.
    X - 시작점, 배열 [N] :
                * X를 가능한 지점으로 설정하는 것이 좋습니다.
                *하지만 X는 실행 불가능할 수 있습니다.이 경우 알고리즘이 시도합니다.
                  먼저 X를 초기 값으로 사용하여 실현 가능한 점을 찾는다.
                  근사.
출력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleiccreate(const ae_int_t n, const real_1d_array &x, minbleicstate &state);
void minbleiccreate(const real_1d_array &x, minbleicstate &state);


/*************************************************************************
The subroutine is finite difference variant of MinBLEICCreate().  It  uses
finite differences in order to differentiate target function.

Description below contains information which is specific to  this function
only. We recommend to read comments on MinBLEICCreate() in  order  to  get
more information about creation of BLEIC optimizer.

INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   starting point, array[0..N-1].
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. algorithm uses 4-point central formula for differentiation.
2. differentiation step along I-th axis is equal to DiffStep*S[I] where
   S[] is scaling vector which can be set by MinBLEICSetScale() call.
3. we recommend you to use moderate values of  differentiation  step.  Too
   large step will result in too large truncation  errors, while too small
   step will result in too large numerical  errors.  1.0E-6  can  be  good
   value to start with.
4. Numerical  differentiation  is   very   inefficient  -   one   gradient
   calculation needs 4*N function evaluations. This function will work for
   any N - either small (1...10), moderate (10...100) or  large  (100...).
   However, performance penalty will be too severe for any N's except  for
   small ones.
   We should also say that code which relies on numerical  differentiation
   is  less  robust and precise. CG needs exact gradient values. Imprecise
   gradient may slow  down  convergence, especially  on  highly  nonlinear
   problems.
   Thus  we  recommend to use this function for fast prototyping on small-
   dimensional problems only, and to implement analytical gradient as soon
   as possible.

  -- ALGLIB --
     Copyright 16.05.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 MinBLEICCreate ()의 유한 차분 변형입니다. 그것은 사용
목표 함수를 구별하기위한 유한 한 차이.
아래 설명에는이 기능과 관련된 정보가 포함되어 있습니다.
만. MinBLEICCreate ()에 대한 의견을 읽고
BLEIC 최적화 프로그램 작성에 대한 자세한 정보.
입력 매개 변수 :
    N - 문제 차원, N> 0 :
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    X - 시작점, 배열 [0..N-1].
    DiffStep- 차별화 단계,> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. 알고리즘은 4 점 중앙 공식을 차별화에 사용합니다.
2. I 번째 축을 따른 미분 단계는 DiffStep * S [I]와 같습니다.
   S []는 MinBLEICSetScale () 호출로 설정할 수있는 스케일링 벡터입니다.
3. 차별화 단계의 중간 값을 사용하는 것이 좋습니다. 너무
   큰 단계는 너무 큰 잘라 내기 오류를 발생 시키지만 너무 작 으면
   단계를 수행하면 수치 오류가 너무 커집니다. 1.0E-6은 좋을 수 있습니다.
   시작 값.
4. 수치 차별화는 매우 비효율적입니다. 하나의 기울기
   계산에는 4 * N 함수 평가가 필요합니다. 이 함수는
   어떤 N - 작은 (1 ... 10), 보통 (10 ... 100) 또는 큰 (100 ...).
   그러나 성능상의 불이익은 N을 제외하고는
   작은 것들.
   우리는 또한 수치 차별화에 의존하는 코드
   덜 강력하고 정밀합니다. CG는 정확한 그래디언트 값을 필요로합니다. 부정확 한
   그래디언트가 수렴 속도를 늦출 수 있습니다. 특히 매우 비선형 인 경우
   문제.
   따라서이 기능을 사용하여 소형 프로토 타이핑에 대한 빠른 프로토 타이핑을 권장합니다.
   차원 문제 만 해결하고 곧 분석 구배를 구현할 수 있습니다.
   가능한 한.
  - ALGLIB -
     Copyright 16.05.2011 Bochkanov Sergey
**************************************************************************/
void minbleiccreatef(const ae_int_t n, const real_1d_array &x, const double diffstep, minbleicstate &state);
void minbleiccreatef(const real_1d_array &x, const double diffstep, minbleicstate &state);


/*************************************************************************
This function sets boundary constraints for BLEIC optimizer.

Boundary constraints are inactive by default (after initial creation).
They are preserved after algorithm restart with MinBLEICRestartFrom().

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    BndL    -   lower bounds, array[N].
                If some (all) variables are unbounded, you may specify
                very small number or -INF.
    BndU    -   upper bounds, array[N].
                If some (all) variables are unbounded, you may specify
                very large number or +INF.

NOTE 1: it is possible to specify BndL[i]=BndU[i]. In this case I-th
variable will be "frozen" at X[i]=BndL[i]=BndU[i].

NOTE 2: this solver has following useful properties:
* bound constraints are always satisfied exactly
* function is evaluated only INSIDE area specified by  bound  constraints,
  even  when  numerical  differentiation is used (algorithm adjusts  nodes
  according to boundary constraints)

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 BLEIC 최적화 프로그램의 경계 제약 조건을 설정합니다.
경계 제약 조건은 기본적으로 비활성화됩니다 (초기 생성 후).
MinBLEICRestartFrom ()으로 알고리즘을 다시 시작하면 보존됩니다.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    BndL - 하한, 배열 [N].
                일부 (모든) 변수에 제한이없는 경우,
                아주 작은 숫자 또는 -INF.
    BndU - 상한, 배열 [N].
                일부 (모든) 변수에 제한이없는 경우,
                매우 큰 숫자 또는 + INF.
비고 1 : BndL [i] = BndU [i]를 지정할 수있다. 이 경우 I-th
변수는 X [i] = BndL [i] = BndU [i]에서 "고정"됩니다.
NOTE 2 :이 솔버는 다음과 같은 유용한 속성을 가지고있다.
* 경계 제약은 항상 정확하게 만족된다.
* 함수는 바인딩 된 제약 조건에 의해 지정된 INSIDE 영역 만 평가되고,
  수치 차별화가 사용되는 경우에도 (알고리즘은 노드
  경계 제약에 따라)
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetbc(const minbleicstate &state, const real_1d_array &bndl, const real_1d_array &bndu);


/*************************************************************************
This function sets linear constraints for BLEIC optimizer.

Linear constraints are inactive by default (after initial creation).
They are preserved after algorithm restart with MinBLEICRestartFrom().

INPUT PARAMETERS:
    State   -   structure previously allocated with MinBLEICCreate call.
    C       -   linear constraints, array[K,N+1].
                Each row of C represents one constraint, either equality
                or inequality (see below):
                * first N elements correspond to coefficients,
                * last element corresponds to the right part.
                All elements of C (including right part) must be finite.
    CT      -   type of constraints, array[K]:
                * if CT[i]>0, then I-th constraint is C[i,*]*x >= C[i,n+1]
                * if CT[i]=0, then I-th constraint is C[i,*]*x  = C[i,n+1]
                * if CT[i]<0, then I-th constraint is C[i,*]*x <= C[i,n+1]
    K       -   number of equality/inequality constraints, K>=0:
                * if given, only leading K elements of C/CT are used
                * if not given, automatically determined from sizes of C/CT

NOTE 1: linear (non-bound) constraints are satisfied only approximately:
* there always exists some minor violation (about Epsilon in magnitude)
  due to rounding errors
* numerical differentiation, if used, may  lead  to  function  evaluations
  outside  of the feasible  area,   because   algorithm  does  NOT  change
  numerical differentiation formula according to linear constraints.
If you want constraints to be  satisfied  exactly, try to reformulate your
problem  in  such  manner  that  all constraints will become boundary ones
(this kind of constraints is always satisfied exactly, both in  the  final
solution and in all intermediate points).

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 BLEIC 옵티 마이저에 대한 선형 제한 조건을 설정합니다.
선형 제약 조건은 기본적으로 비활성화됩니다 (초기 생성 후).
MinBLEICRestartFrom ()으로 알고리즘을 다시 시작하면 보존됩니다.
입력 매개 변수 :
    State - 이전에 MinBLEICCreate 호출로 할당 된 구조체.
    C - 선형 구속 조건, array [K, N + 1].
                C의 각 행은 하나의 제약 조건을 나타냅니다.
                또는 불평등 (아래 참조) :
                * 첫 번째 N 요소는 계수에 해당하고,
                * 마지막 요소는 오른쪽 부분에 해당합니다.
                C의 모든 요소 (오른쪽 부분 포함)는 유한해야합니다.
    CT - 제약 조건, 배열 [K] :
                * CT [i]> 0이면, I 번째 제약은 C [i, *] * x> = C [i, n + 1]
                * CT [i] = 0이면, I 번째 제약은 C [i, *] * x = C [i, n + 1]
                * CT [i] <0 인 경우, I 번째 제약은 C [i, *] * x <= C [i, n + 1]
    K - 평등 / 불평등 제약의 수, K> = 0 :
                * 주어진 경우 C / CT의 선행 K 요소 만 사용됩니다.
                * 주어지지 않은 경우, C / CT의 크기로부터 자동으로 결정됩니다.
비고 1 : 선형 (비 구속) 제약 조건은 대략 다음과 같이 만족된다 :
* 사소한 위반이 항상 존재합니다 (크기가 엡실론 인 경우)
  반올림 오류로 인해
* 수치 차별화를 사용하면 기능 평가로 이어질 수 있습니다.
  알고리즘이 변경되지 않기 때문에 가능한 영역 외부
  선형 제약에 따른 수치 미분 공식.
제약 조건을 정확하게 만족 시키려면,
모든 제약 조건이 경계 조건이되는 방식으로 문제
(이런 종류의 제약 조건은 항상 정확하게 만족된다.
솔루션 및 모든 중간 지점에서).
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetlc(const minbleicstate &state, const real_2d_array &c, const integer_1d_array &ct, const ae_int_t k);
void minbleicsetlc(const minbleicstate &state, const real_2d_array &c, const integer_1d_array &ct);


/*************************************************************************
This function sets stopping conditions for the optimizer.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                |v|<EpsG is satisfied, where:
                * |.| means Euclidian norm
                * v - scaled gradient vector, v[i]=g[i]*s[i]
                * g - gradient
                * s - scaling coefficients set by MinBLEICSetScale()
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |v|<=EpsX is fulfilled, where:
                * |.| means Euclidian norm
                * v - scaled step vector, v[i]=dx[i]/s[i]
                * dx - step vector, dx=X(k+1)-X(k)
                * s - scaling coefficients set by MinBLEICSetScale()
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0 and EpsX=0 and MaxIts=0 (simultaneously) will lead
to automatic stopping criterion selection.

NOTE: when SetCond() called with non-zero MaxIts, BLEIC solver may perform
      slightly more than MaxIts iterations. I.e., MaxIts  sets  non-strict
      limit on iterations count.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 최적화 프로그램의 중지 조건을 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsG -> = 0
                서브 루틴은 조건
                | v | <EpsG가 만족되면,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 그래디언트 벡터, v [i] = g [i] * s [i]
                * g - 그래디언트
                * s - MinBLEICSetScale ()에 의해 설정된 스케일링 계수
    EpsF -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                조건 | F (k + 1) -F (k) | <= EpsF * max {| F (k) |, | F (k + 1) |, 1}
                만족한다.
    EpsX -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                | v | <= EpsX 조건이 충족됩니다. 여기서,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 스텝 벡터, v [i] = dx [i] / s [i]
                * dx - 스텝 벡터, dx = X (k + 1) -X (k)
                * s - MinBLEICSetScale ()에 의해 설정된 스케일링 계수
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다.
EpsG = 0, EpsF = 0 및 EpsX = 0 및 MaxIts = 0 (동시에)을 전달하면
자동 정지 기준 선택.
참고 : 0이 아닌 MaxIts로 호출 된 SetCond ()가 BLEIC 해결자가 수행 할 수 있습니다.
      MaxIts 반복보다 약간. 즉, MaxIts는 비 엄격하게 설정합니다.
      반복 횟수 제한.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetcond(const minbleicstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
This function sets scaling coefficients for BLEIC optimizer.

ALGLIB optimizers use scaling matrices to test stopping  conditions  (step
size and gradient are scaled before comparison with tolerances).  Scale of
the I-th variable is a translation invariant measure of:
a) "how large" the variable is
b) how large the step should be to make significant changes in the function

Scaling is also used by finite difference variant of the optimizer  - step
along I-th axis is equal to DiffStep*S[I].

In  most  optimizers  (and  in  the  BLEIC  too)  scaling is NOT a form of
preconditioning. It just  affects  stopping  conditions.  You  should  set
preconditioner  by  separate  call  to  one  of  the  MinBLEICSetPrec...()
functions.

There is a special  preconditioning  mode, however,  which  uses   scaling
coefficients to form diagonal preconditioning matrix. You  can  turn  this
mode on, if you want.   But  you should understand that scaling is not the
same thing as preconditioning - these are two different, although  related
forms of tuning solver.

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    S       -   array[N], non-zero scaling coefficients
                S[i] may be negative, sign doesn't matter.

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 BLEIC 옵티 마이저의 스케일링 계수를 설정합니다.
ALGLIB 최적화 프로그램은 스케일링 매트릭스를 사용하여 정지 조건을 테스트합니다 (단계
크기 및 그래디언트는 공차와 비교하기 전에 크기가 조정됩니다.) 규모
I 번째 변수는 다음에 대한 변환 불변성 측정 값입니다.
a) 변수의 "크기"
b) 함수에서 중요한 변화를 만드는 단계는 얼마나 커야 하는가?
스케일링은 최적화 알고리즘의 유한 차분 변형에서도 사용됩니다. - 단계
I 번째 축을 따라 DiffStep * S [I]와 같습니다.
대부분의 옵티 마이저 (및 BLEIC에서도) 스케일링은
전제 조건. 그것은 단지 멈추는 조건에 영향을 미칩니다. 설정해야합니다.
전제 조건을 MinBLEICSetPrec ... ()
기능.
그러나 특수 preconditioning 모드는 스케일링을 사용합니다.
계수는 대각선 전처리 행렬을 형성한다. 너는 이것을 돌릴 수있다.
모드를 켜십시오. 그러나 스케일링은
전제 조건 (preconditioning)과 같은 것 - 이것은 서로 다르지만 관련이있다.
튜닝 솔버의 형태.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    S - 배열 [N], 0이 아닌 스케일링 계수
                S [i]는 음수 일 수 있습니다. 부호는 중요하지 않습니다.
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
**************************************************************************/
void minbleicsetscale(const minbleicstate &state, const real_1d_array &s);


/*************************************************************************
Modification of the preconditioner: preconditioning is turned off.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
선행 조건의 수정 : 선행 조건이 해제됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
*************************************************** ***********************/
void minbleicsetprecdefault(const minbleicstate &state);


/*************************************************************************
Modification  of  the  preconditioner:  diagonal of approximate Hessian is
used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    D       -   diagonal of the approximate Hessian, array[0..N-1],
                (if larger, only leading N elements are used).

NOTE 1: D[i] should be positive. Exception will be thrown otherwise.

NOTE 2: you should pass diagonal of approximate Hessian - NOT ITS INVERSE.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 대략적인 헤 시안의 대각선은 다음과 같습니다.
익숙한.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    D - 근사 헤센의 대각선, array [0..N-1],
                (더 큰 경우 N 개의 주요 요소 만 사용됨).
비고 1 : D [i]는 양수이어야한다. 그렇지 않으면 예외가 발생합니다.
NOTE 2 : 대략적인 Hessian의 대각선을 통과해야한다 - ITS INVERSE가 아니다.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetprecdiag(const minbleicstate &state, const real_1d_array &d);


/*************************************************************************
Modification of the preconditioner: scale-based diagonal preconditioning.

This preconditioning mode can be useful when you  don't  have  approximate
diagonal of Hessian, but you know that your  variables  are  badly  scaled
(for  example,  one  variable is in [1,10], and another in [1000,100000]),
and most part of the ill-conditioning comes from different scales of vars.

In this case simple  scale-based  preconditioner,  with H[i] = 1/(s[i]^2),
can greatly improve convergence.

IMPRTANT: you should set scale of your variables  with  MinBLEICSetScale()
call  (before  or after MinBLEICSetPrecScale() call). Without knowledge of
the scale of your variables scale-based preconditioner will be  just  unit
matrix.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 스케일 기반 대각선 전제 조건.
이 사전 조절 모드는 근사치가 없을 때 유용 할 수 있습니다.
헤 시안 (Hessian)의 대각선이지만, 변수가 잘못 조정 된 것을 알고 있습니다.
(예를 들어, 하나의 변수는 [1,10]에 있고 다른 변수는 [1000,100000]에 있음)
그리고 불량 조절의 대부분은 다양한 범위의 바에서 비롯됩니다.
이 경우 H [i] = 1 / (s [i] ^ 2) 인 간단한 스케일 기반 전처리 기가
융합을 크게 향상시킬 수 있습니다.
IMPRTANT : MinBLEICSetScale ()을 사용하여 변수의 스케일을 설정해야합니다.
call (MinBLEICSetPrecScale () 호출 전후). 지식이 없으면
변수의 스케일 규모 기반 전처리 부는 단지 단위 일 것입니다
매트릭스.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetprecscale(const minbleicstate &state);


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinBLEICOptimize().

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinBLEICOptimize ()에 제공됩니다.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetxrep(const minbleicstate &state, const bool needxrep);


/*************************************************************************
This function sets maximum step length

IMPORTANT: this feature is hard to combine with preconditioning. You can't
set upper limit on step length, when you solve optimization  problem  with
linear (non-boundary) constraints AND preconditioner turned on.

When  non-boundary  constraints  are  present,  you  have to either a) use
preconditioner, or b) use upper limit on step length.  YOU CAN'T USE BOTH!
In this case algorithm will terminate with appropriate error code.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  lead   to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 최대 스텝 길이를 설정합니다.
중요 :이 기능은 사전 컨디셔닝과 결합하기가 어렵습니다. 너는 할 수 없어.
최적화 문제를 해결할 때 단계 길이 상한을 설정하십시오.
선형 (경계가 아닌) 제약 조건과 선행 조건이 켜짐
비 경계 제약이 존재할 때, 당신은 a)
선행 조건, 또는 b) 스텝 길이의 상한값을 사용하십시오. 둘 다 사용할 수 없다!
이 경우 알고리즘은 적절한 오류 코드로 종료됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    StpMax - 최대 스텝 길이,> = 0. StpMax를 0.0으로 설정하십시오.
                스텝 길이를 제한하고 싶다.
exp ()가 포함 된 대상 함수를 최적화 할 때이 서브 루틴을 사용하십시오.
또는 다른 빠른 성장 기능 및 최적화 알고리즘을 만듭니다
오버 플로우로 이어지는 큰 단계. 이 기능을 사용하면 거부 할 수 있습니다.
너무 큰 단계 (가능한 한 우리를 노출시킵니다.
overflow) x + stp * d에서 실제로 함수 값을 계산하지 않아도된다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetstpmax(const minbleicstate &state, const double stpmax);


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
bool minbleiciteration(const minbleicstate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear optimizer

These functions accept following parameters:
    state   -   algorithm state
    func    -   callback which calculates function (or merit function)
                value func at given point x
    grad    -   callback which calculates function (or merit function)
                value func and gradient grad at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL

NOTES:

1. This function has two different implementations: one which  uses  exact
   (analytical) user-supplied gradient,  and one which uses function value
   only  and  numerically  differentiates  function  in  order  to  obtain
   gradient.

   Depending  on  the  specific  function  used to create optimizer object
   (either  MinBLEICCreate() for analytical gradient or  MinBLEICCreateF()
   for numerical differentiation) you should choose appropriate variant of
   MinBLEICOptimize() - one  which  accepts  function  AND gradient or one
   which accepts function ONLY.

   Be careful to choose variant of MinBLEICOptimize() which corresponds to
   your optimization scheme! Table below lists different  combinations  of
   callback (function/gradient) passed to MinBLEICOptimize()  and specific
   function used to create optimizer.


                     |         USER PASSED TO MinBLEICOptimize()
   CREATED WITH      |  function only   |  function and gradient
   ------------------------------------------------------------
   MinBLEICCreateF() |     work                FAIL
   MinBLEICCreate()  |     FAIL                work

   Here "FAIL" denotes inappropriate combinations  of  optimizer  creation
   function  and  MinBLEICOptimize()  version.   Attemps   to   use   such
   combination (for  example,  to  create optimizer with MinBLEICCreateF()
   and  to  pass  gradient  information  to  MinCGOptimize()) will lead to
   exception being thrown. Either  you  did  not pass gradient when it WAS
   needed or you passed gradient when it was NOT needed.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey

*************************************************************************/
/**************************************************************************
이 함수 계열은 비선형 최적화 알고리즘의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    func - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func
    grad - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func 및 gradient grad
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
노트:
1.이 함수는 두 가지 구현이 있습니다 :
   (분석적인) 사용자 제공 그래디언트와 함수 값을 사용하는 그래디언트
   오직 함수를 수치 적으로 구별하여 구하기 위해
   구배.
   최적화 프로그램 개체를 만드는 데 사용 된 특정 함수에 따라
   (분석 그라디언트의 경우 MinBLEICCreate () 또는 MinBLEICCreateF ()
   수치 차별화의 경우)의 적절한 변형을 선택해야합니다.
   MinBLEICOptimize () - 함수 AND 그레디언트 또는 하나를 허용하는 것
   기능 만 허용합니다.
   MinBLEICOptimize ()의 변형을 선택하는 것에주의하십시오.
   귀하의 최적화 계획! 아래 표에는
   MinBLEICOptimize ()에 전달 된 콜백 (함수 / 그라디언트)
   최적화 프로그램을 만드는 데 사용되는 함수.
                     | 사용자가 MinBLEICOptimize ()에 전달했습니다.
   창조 된 | 기능 만 | 함수 및 그래디언트
   -------------------------------------------------- ----------
   MinBLEICCreateF () | 직장 불합격
   MinBLEICCreate () | FAIL 작업
   여기서 "FAIL"은 최적화 도구 작성의 부적절한 조합을 나타냅니다.
   함수 및 MinBLEICOptimize () 버전. 그러한 시도를 시도하다.
   조합 (예 : MinBLEICCreateF ()를 사용하여 최적화 프로그램을 작성하는 경우)
   그라디언트 정보를 MinCGOptimize ()에 전달하면
   예외가 throw됩니다. 그라디언트를 통과시키지 않았습니까?
   필요한 경우 또는 그래디언트를 전달할 때 필요하지 않습니다.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicoptimize(minbleicstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void minbleicoptimize(minbleicstate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);


/*************************************************************************
BLEIC results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report. You should check Rep.TerminationType
                in  order  to  distinguish  successful  termination  from
                unsuccessful one:
                * -7   gradient verification failed.
                       See MinBLEICSetGradientCheck() for more information.
                * -3   inconsistent constraints. Feasible point is
                       either nonexistent or too hard to find. Try to
                       restart optimizer with better initial approximation
                *  1   relative function improvement is no more than EpsF.
                *  2   scaled step is no more than EpsX.
                *  4   scaled gradient norm is no more than EpsG.
                *  5   MaxIts steps was taken
                More information about fields of this  structure  can  be
                found in the comments on MinBLEICReport datatype.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
BLEIC 결과
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액
    담당자 최적화 보고서. Rep.TerminationType을 확인해야합니다.
                성공적인 해고를 구별하기 위해서
                실패한 것 :
                * -7 그래디언트 확인에 실패했습니다.
                       자세한 정보는 MinBLEICSetGradientCheck ()를 참조하십시오.
                * -3 일관성없는 제약 조건. 실행할 수있는 요지는
                       존재하지 않거나 찾기가 어렵습니다. 하려고 노력하다
                       더 나은 초기 근사를 가진 최적화 프로그램 재시작
                * 1 상대 기능 개선은 EpsF 이상입니다.
                * 2 단계는 EpsX 이상입니다.
                * 4 스케일 그라디언트 표준은 EpsG 이하입니다.
                * 5 MaxIts 단계가 수행되었습니다.
                이 구조의 필드에 대한 추가 정보는 다음과 같습니다.
                MinBLEICReport 데이터 유형에 대한 주석에 있습니다.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicresults(const minbleicstate &state, real_1d_array &x, minbleicreport &rep);


/*************************************************************************
BLEIC results

Buffered implementation of MinBLEICResults() which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
BLEIC 결과
미리 할당 된 버퍼를 사용하는 MinBLEICResults ()의 버퍼 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
*************************************************** ***********************/
void minbleicresultsbuf(const minbleicstate &state, real_1d_array &x, minbleicreport &rep);


/*************************************************************************
This subroutine restarts algorithm from new point.
All optimization parameters (including constraints) are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have  same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure previously allocated with MinBLEICCreate call.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 새 지점에서 알고리즘을 다시 시작합니다.
모든 최적화 매개 변수 (제약 조건 포함)는 변경되지 않습니다.
이 함수는 여러 개의 최적화 문제를 해결할 수 있습니다.
오브젝트 재 할당 패널티가없는 동일한 수의 치수가 있어야합니다.
입력 매개 변수 :
    State - 이전에 MinBLEICCreate 호출로 할당 된 구조체.
    X - 새로운 출발점.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicrestartfrom(const minbleicstate &state, const real_1d_array &x);


/*************************************************************************
This  subroutine  turns  on  verification  of  the  user-supplied analytic
gradient:
* user calls this subroutine before optimization begins
* MinBLEICOptimize() is called
* prior to  actual  optimization, for each component  of  parameters being
  optimized X[i] algorithm performs following steps:
  * two trial steps are made to X[i]-TestStep*S[i] and X[i]+TestStep*S[i],
    where X[i] is i-th component of the initial point and S[i] is a  scale
    of i-th parameter
  * if needed, steps are bounded with respect to constraints on X[]
  * F(X) is evaluated at these trial points
  * we perform one more evaluation in the middle point of the interval
  * we  build  cubic  model using function values and derivatives at trial
    points and we compare its prediction with actual value in  the  middle
    point
  * in case difference between prediction and actual value is higher  than
    some predetermined threshold, algorithm stops with completion code -7;
    Rep.VarIdx is set to index of the parameter with incorrect derivative.
* after verification is over, algorithm proceeds to the actual optimization.

NOTE 1: verification  needs  N (parameters count) gradient evaluations. It
        is very costly and you should use  it  only  for  low  dimensional
        problems,  when  you  want  to  be  sure  that  you've   correctly
        calculated  analytic  derivatives.  You  should  not use it in the
        production code (unless you want to check derivatives provided  by
        some third party).

NOTE 2: you  should  carefully  choose  TestStep. Value which is too large
        (so large that function behaviour is significantly non-cubic) will
        lead to false alarms. You may use  different  step  for  different
        parameters by means of setting scale with MinBLEICSetScale().

NOTE 3: this function may lead to false positives. In case it reports that
        I-th  derivative was calculated incorrectly, you may decrease test
        step  and  try  one  more  time  - maybe your function changes too
        sharply  and  your  step  is  too  large for such rapidly chanding
        function.

INPUT PARAMETERS:
    State       -   structure used to store algorithm state
    TestStep    -   verification step:
                    * TestStep=0 turns verification off
                    * TestStep>0 activates verification

  -- ALGLIB --
     Copyright 15.06.2012 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 사용자가 제공 한 분석의 검증을 켭니다.
구배:
* 최적화가 시작되기 전에 사용자가이 서브 루틴 호출
* MinBLEICOptimize ()가 호출되었습니다.
* 매개 변수의 각 구성 요소에 대한 실제 최적화 이전
  최적화 된 X [i] 알고리즘은 다음 단계를 수행합니다.
  * X [i] -TestStep * S [i] 및 X [i] + TestStep * S [i]에 대해 두 번의 시험 단계가 수행됩니다.
    여기서 X [i]는 초기 점의 i 번째 구성 요소이고 S [i]는 스케일입니다
    i 번째 매개 변수
  * 필요한 경우 단계는 X []에 대한 제약 조건에 따라 제한됩니다.
  * F (X)는 이러한 시험 포인트에서 평가됩니다.
  * 간격의 중간 지점에서 또 하나의 평가를 수행합니다.
  * 우리는 함수 값과 파생 상품을 사용하여 삼차원 모델을 시험해 보았다.
    우리는 예측치를 중간의 실제 값과 비교합니다
    포인트
  * 예상 값과 실제 값의 차이가
    소정의 소정의 임계 값, 알고리즘은 완료 코드 -7로 정지한다;
    Rep.VarIdx가 잘못된 파생어로 매개 변수의 인덱스로 설정됩니다.
* 검증이 끝나면 알고리즘은 실제 최적화로 진행합니다.
주 1 : 검증은 N (매개 변수 개수) 그라디언트 평가가 필요하다. 그것
        매우 비용이 많이 들며 낮은 차원에서만 사용해야합니다.
        문제, 당신이 당신이 올바르게했는지 알고 싶을 때
        계산 된 파생 상품. 당신은
        생산 코드 (귀하가 제공 한 파생 상품을 확인하고 싶지 않은 경우)
        제 3 자).
참고 2 : TestStep을 신중하게 선택해야합니다. 너무 큰 값
        (너무 커서 함수의 동작은 상당히 비 큐빅이다.)
        거짓 경보로 연결됩니다. 다른 단계를 사용할 수도 있습니다.
        매개 변수를 MinBLEICSetScale ()로 설정하여.
참고 3 :이 기능은 위양성을 유발할 수 있습니다. 보고서에
        I 차수 미분이 잘못 계산되었으므로 테스트를 줄일 수 있습니다.
        한 번 더 시도해보십시오. 아마도 기능이 변경 될 수도 있습니다.
        급격하게 그리고 당신의 발걸음이 그렇게 급속히 챈드하기에는 너무 큽니다.
        기능.
입력 매개 변수 :
    상태 - 알고리즘 상태를 저장하는 데 사용되는 구조
    TestStep - 확인 단계 :
                    * TestStep = 0으로 설정하면 인증이 해제됩니다.
                    * TestStep> 0으로 인증이 활성화됩니다.
  - ALGLIB -
     저작권 15.06.2012 Bochkanov Sergey
**************************************************************************/
void minbleicsetgradientcheck(const minbleicstate &state, const double teststep);

/*************************************************************************
        LIMITED MEMORY BFGS METHOD FOR LARGE SCALE OPTIMIZATION

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by  using  a  quasi-
Newton method (LBFGS scheme) which is optimized to use  a  minimum  amount
of memory.
The subroutine generates the approximation of an inverse Hessian matrix by
using information about the last M steps of the algorithm  (instead of N).
It lessens a required amount of memory from a value  of  order  N^2  to  a
value of order 2*N*M.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinLBFGSCreate() call
2. User tunes solver parameters with MinLBFGSSetCond() MinLBFGSSetStpMax()
   and other functions
3. User calls MinLBFGSOptimize() function which takes algorithm  state and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinLBFGSResults() to get solution
5. Optionally user may call MinLBFGSRestartFrom() to solve another problem
   with same N/M but another starting point and/or another function.
   MinLBFGSRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension. N>0
    M       -   number of corrections in the BFGS scheme of Hessian
                approximation update. Recommended value:  3<=M<=7. The smaller
                value causes worse convergence, the bigger will  not  cause  a
                considerably better convergence, but will cause a fall in  the
                performance. M<=N.
    X       -   initial solution approximation, array[0..N-1].


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTES:
1. you may tune stopping conditions with MinLBFGSSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLBFGSSetStpMax() function to bound algorithm's  steps.  However,
   L-BFGS rarely needs such a tuning.


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
        대규모 메모리 최적화를위한 대규모 메모리 최적화 방법
기술:
서브 루틴은 N 개의 인수의 함수 F (x)를 준 -
최소량을 사용하도록 최적화 된 뉴튼 방식 (LBFGS 방식)
메모리의.
서브 루틴은 다음과 같은 역 헤세 비안 행렬의 근사를 생성합니다.
(N 대신에) 알고리즘의 마지막 M 단계에 대한 정보를 사용하여.
필요로하는 메모리 양을 N ^ 2 차수에서
차수 2 * N * M의 값.
요구 사항 :
알고리즘은 작동 중에 다음 정보를 요청합니다.
* 주어진 점 X에서 함수 값 F와 그 기울기 G (동시에)
용법:
1. 사용자가 MinLBFGSCreate () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 MinLBFGSSetCond ()로 Solver 매개 변수를 조정합니다. MinLBFGSSetStpMax ()
   및 기타 기능
3. 사용자는 알고리즘 상태를 취하는 MinLBFGSOptimize () 함수를 호출하고
   F / G를 계산하는 콜백 함수에 대한 포인터 (델리게이트 등).
4. 사용자가 MinLBFGSResults ()를 호출하여 솔루션을 얻습니다.
5. 선택적으로 MinLBFGSRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 N / M이지만 다른 시작점 및 / 또는 다른 기능을 사용합니다.
   MinLBFGSRestartFrom ()은 이미 초기화 된 구조를 재사용 할 수있게합니다.
입력 매개 변수 :
    N - 문제 차원. N> 0
    M - 헤 시안의 BFGS 체계에서의 정정 횟수
                근사치 업데이트. 권장 값 : 3 <= M <= 7. 더 작은
                값이 더 나쁜 수렴을 일으키는 경우, 더 큰 수렴은
                상당히 좋은 수렴을하지만,
                공연. M <= N.
    X - 초기 해답 근사값, array [0..N-1].
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. MinLBFGSSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   MinLBFGSSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩하십시오. 하나,
   L-BFGS는 거의 그러한 튜닝이 필요하지 않습니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgscreate(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlbfgsstate &state);
void minlbfgscreate(const ae_int_t m, const real_1d_array &x, minlbfgsstate &state);


/*************************************************************************
The subroutine is finite difference variant of MinLBFGSCreate().  It  uses
finite differences in order to differentiate target function.

Description below contains information which is specific to  this function
only. We recommend to read comments on MinLBFGSCreate() in  order  to  get
more information about creation of LBFGS optimizer.

INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of corrections in the BFGS scheme of Hessian
                approximation update. Recommended value:  3<=M<=7. The smaller
                value causes worse convergence, the bigger will  not  cause  a
                considerably better convergence, but will cause a fall in  the
                performance. M<=N.
    X       -   starting point, array[0..N-1].
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. algorithm uses 4-point central formula for differentiation.
2. differentiation step along I-th axis is equal to DiffStep*S[I] where
   S[] is scaling vector which can be set by MinLBFGSSetScale() call.
3. we recommend you to use moderate values of  differentiation  step.  Too
   large step will result in too large truncation  errors, while too small
   step will result in too large numerical  errors.  1.0E-6  can  be  good
   value to start with.
4. Numerical  differentiation  is   very   inefficient  -   one   gradient
   calculation needs 4*N function evaluations. This function will work for
   any N - either small (1...10), moderate (10...100) or  large  (100...).
   However, performance penalty will be too severe for any N's except  for
   small ones.
   We should also say that code which relies on numerical  differentiation
   is   less  robust  and  precise.  LBFGS  needs  exact  gradient values.
   Imprecise gradient may slow  down  convergence,  especially  on  highly
   nonlinear problems.
   Thus  we  recommend to use this function for fast prototyping on small-
   dimensional problems only, and to implement analytical gradient as soon
   as possible.

  -- ALGLIB --
     Copyright 16.05.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
서브 루틴은 MinLBFGSCreate ()의 유한 차이 변형입니다. 그것은 사용
목표 함수를 구별하기위한 유한 한 차이.
아래 설명에는이 기능과 관련된 정보가 포함되어 있습니다.
만. MinLBFGSCreate ()에 대한 의견을 읽으십시오.
LBFGS 최적화 프로그램 작성에 대한 자세한 정보.
입력 매개 변수 :
    N - 문제 차원, N> 0 :
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    M - 헤 시안의 BFGS 체계에서의 정정 횟수
                근사치 업데이트. 권장 값 : 3 <= M <= 7. 더 작은
                값이 더 나쁜 수렴을 일으키는 경우, 더 큰 수렴은
                상당히 좋은 수렴을하지만,
                공연. M <= N.
    X - 시작점, 배열 [0..N-1].
    DiffStep- 차별화 단계,> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. 알고리즘은 4 점 중앙 공식을 차별화에 사용합니다.
2. I 번째 축을 따른 미분 단계는 DiffStep * S [I]와 같습니다.
   S []는 MinLBFGSSetScale () 호출로 설정할 수있는 스케일링 벡터입니다.
3. 차별화 단계의 중간 값을 사용하는 것이 좋습니다. 너무
   큰 단계는 너무 큰 잘라 내기 오류를 발생 시키지만 너무 작 으면
   단계를 수행하면 수치 오류가 너무 커집니다. 1.0E-6은 좋을 수 있습니다.
   시작 값.
4. 수치 차별화는 매우 비효율적입니다. 하나의 기울기
   계산에는 4 * N 함수 평가가 필요합니다. 이 함수는
   어떤 N - 작은 (1 ... 10), 보통 (10 ... 100) 또는 큰 (100 ...).
   그러나 성능상의 불이익은 N을 제외하고는
   작은 것들.
   우리는 또한 수치 차별화에 의존하는 코드
   덜 강력하고 정밀합니다. LBFGS에는 정확한 그래디언트 값이 필요합니다.
   정확하지 않은 그라디언트가 수렴 속도를 늦출 수 있습니다.
   비선형 문제.
   따라서이 기능을 사용하여 소형 프로토 타이핑에 대한 빠른 프로토 타이핑을 권장합니다.
   차원 문제 만 해결하고 곧 분석 구배를 구현할 수 있습니다.
   가능한 한.
  - ALGLIB -
     Copyright 16.05.2011 Bochkanov Sergey
**************************************************************************/
void minlbfgscreatef(const ae_int_t n, const ae_int_t m, const real_1d_array &x, const double diffstep, minlbfgsstate &state);
void minlbfgscreatef(const ae_int_t m, const real_1d_array &x, const double diffstep, minlbfgsstate &state);


/*************************************************************************
This function sets stopping conditions for L-BFGS optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                |v|<EpsG is satisfied, where:
                * |.| means Euclidian norm
                * v - scaled gradient vector, v[i]=g[i]*s[i]
                * g - gradient
                * s - scaling coefficients set by MinLBFGSSetScale()
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |v|<=EpsX is fulfilled, where:
                * |.| means Euclidian norm
                * v - scaled step vector, v[i]=dx[i]/s[i]
                * dx - ste pvector, dx=X(k+1)-X(k)
                * s - scaling coefficients set by MinLBFGSSetScale()
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은 L-BFGS 최적화 알고리즘의 정지 조건을 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsG -> = 0
                서브 루틴은 조건
                | v | <EpsG가 만족되면,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 그래디언트 벡터, v [i] = g [i] * s [i]
                * g - 그래디언트
                * s - MinLBFGSSetScale ()에 의해 설정된 스케일링 계수
    EpsF -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                조건 | F (k + 1) -F (k) | <= EpsF * max {| F (k) |, | F (k + 1) |, 1}
                만족한다.
    EpsX -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                | v | <= EpsX 조건이 충족됩니다. 여기서,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 스텝 벡터, v [i] = dx [i] / s [i]
                * dx - ste pvector, dx = X (k + 1) -X (k)
                * s - MinLBFGSSetScale ()에 의해 설정된 스케일링 계수
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다.
EpsG = 0, EpsF = 0, EpsX = 0 및 MaxIts = 0 (동시에)을 전달하면
자동 정지 기준 선택 (작은 EpsX).
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetcond(const minlbfgsstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinLBFGSOptimize().


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinLBFGSOptimize ()에 제공됩니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetxrep(const minlbfgsstate &state, const bool needxrep);


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0 (default),  if
                you don't want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 최대 스텝 길이를 설정합니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    StpMax - 최대 스텝 길이,> = 0. StpMax를 0.0 (기본값)으로 설정하십시오. if
                당신은 스텝 길이를 제한하고 싶지 않습니다.
exp ()가 포함 된 대상 함수를 최적화 할 때이 서브 루틴을 사용하십시오.
또는 다른 빠른 성장 기능 및 최적화 알고리즘을 만듭니다
오버 플로우로 이어지는 큰 단계. 이 기능을 사용하면 거부 할 수 있습니다.
너무 큰 단계 (가능한 한 우리를 노출시킵니다.
overflow) x + stp * d에서 실제로 함수 값을 계산하지 않아도된다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetstpmax(const minlbfgsstate &state, const double stpmax);


/*************************************************************************
This function sets scaling coefficients for LBFGS optimizer.

ALGLIB optimizers use scaling matrices to test stopping  conditions  (step
size and gradient are scaled before comparison with tolerances).  Scale of
the I-th variable is a translation invariant measure of:
a) "how large" the variable is
b) how large the step should be to make significant changes in the function

Scaling is also used by finite difference variant of the optimizer  - step
along I-th axis is equal to DiffStep*S[I].

In  most  optimizers  (and  in  the  LBFGS  too)  scaling is NOT a form of
preconditioning. It just  affects  stopping  conditions.  You  should  set
preconditioner  by  separate  call  to  one  of  the  MinLBFGSSetPrec...()
functions.

There  is  special  preconditioning  mode, however,  which  uses   scaling
coefficients to form diagonal preconditioning matrix. You  can  turn  this
mode on, if you want.   But  you should understand that scaling is not the
same thing as preconditioning - these are two different, although  related
forms of tuning solver.

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    S       -   array[N], non-zero scaling coefficients
                S[i] may be negative, sign doesn't matter.

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 LBFGS 옵티 마이저의 스케일링 계수를 설정합니다.
ALGLIB 최적화 프로그램은 스케일링 매트릭스를 사용하여 정지 조건을 테스트합니다 (단계
크기 및 그래디언트는 공차와 비교하기 전에 크기가 조정됩니다.) 규모
I 번째 변수는 다음에 대한 변환 불변성 측정 값입니다.
a) 변수의 "크기"
b) 함수에서 중요한 변화를 만드는 단계는 얼마나 커야 하는가?
스케일링은 최적화 알고리즘의 유한 차분 변형에서도 사용됩니다. - 단계
I 번째 축을 따라 DiffStep * S [I]와 같습니다.
대부분의 옵티 마이저 (LBFGS에서도) 스케일링은
전제 조건. 그것은 단지 멈추는 조건에 영향을 미칩니다. 설정해야합니다.
프리 컨디셔너를 MinLBFGSSetPrec ... ()
기능.
그러나 특수 preconditioning 모드는 스케일링을 사용합니다.
계수는 대각선 전처리 행렬을 형성한다. 너는 이것을 돌릴 수있다.
모드를 켜십시오. 그러나 스케일링은
전제 조건 (preconditioning)과 같은 것 - 이것은 서로 다르지만 관련이있다.
튜닝 솔버의 형태.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    S - 배열 [N], 0이 아닌 스케일링 계수
                S [i]는 음수 일 수 있습니다. 부호는 중요하지 않습니다.
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
**************************************************************************/
void minlbfgssetscale(const minlbfgsstate &state, const real_1d_array &s);


/*************************************************************************
Modification  of  the  preconditioner:  default  preconditioner    (simple
scaling, same for all elements of X) is used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 기본 전제 조건 (단순 조건
스케일링, X의 모든 요소에 대해 동일)가 사용됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
참고 : 알고리즘 중에 사전 조건을 "즉시"변경할 수 있습니다.
반복.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetprecdefault(const minlbfgsstate &state);


/*************************************************************************
Modification of the preconditioner: Cholesky factorization of  approximate
Hessian is used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    P       -   triangular preconditioner, Cholesky factorization of
                the approximate Hessian. array[0..N-1,0..N-1],
                (if larger, only leading N elements are used).
    IsUpper -   whether upper or lower triangle of P is given
                (other triangle is not referenced)

After call to this function preconditioner is changed to P  (P  is  copied
into the internal buffer).

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

NOTE 2:  P  should  be nonsingular. Exception will be thrown otherwise.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 근사치의 콜레 스키 인수 분해
헤 시안이 사용됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    P - 삼각형 선행 조건, Cholesky 분해
                대략적인 헤 시안. 어레이 [0..N-1,0 ... N-1],
                (더 큰 경우 N 개의 주요 요소 만 사용됨).
    IsUpper - P의 위 또는 아래 삼각형이 지정되는지 여부
                (다른 삼각형은 참조되지 않음)
이 함수를 호출 한 후 프리 컨디셔너가 P로 변경됩니다 (P는 복사 됨).
내부 버퍼로).
참고 : 알고리즘 중에 사전 조건을 "즉시"변경할 수 있습니다.
반복.
NOTE 2 : P는 정칙이어야한다. 그렇지 않으면 예외가 발생합니다.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetpreccholesky(const minlbfgsstate &state, const real_2d_array &p, const bool isupper);


/*************************************************************************
Modification  of  the  preconditioner:  diagonal of approximate Hessian is
used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    D       -   diagonal of the approximate Hessian, array[0..N-1],
                (if larger, only leading N elements are used).

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

NOTE 2: D[i] should be positive. Exception will be thrown otherwise.

NOTE 3: you should pass diagonal of approximate Hessian - NOT ITS INVERSE.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 대략적인 헤 시안의 대각선은 다음과 같습니다.
익숙한.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    D - 근사 헤센의 대각선, array [0..N-1],
                (더 큰 경우 N 개의 주요 요소 만 사용됨).
참고 : 알고리즘 중에 사전 조건을 "즉시"변경할 수 있습니다.
반복.
주 2 : D [i]는 양수이어야한다. 그렇지 않으면 예외가 발생합니다.
NOTE 3 : 대략적인 Hessian의 대각선을 통과해야한다 - ITS INVERSE가 아님.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetprecdiag(const minlbfgsstate &state, const real_1d_array &d);


/*************************************************************************
Modification of the preconditioner: scale-based diagonal preconditioning.

This preconditioning mode can be useful when you  don't  have  approximate
diagonal of Hessian, but you know that your  variables  are  badly  scaled
(for  example,  one  variable is in [1,10], and another in [1000,100000]),
and most part of the ill-conditioning comes from different scales of vars.

In this case simple  scale-based  preconditioner,  with H[i] = 1/(s[i]^2),
can greatly improve convergence.

IMPRTANT: you should set scale of your variables  with  MinLBFGSSetScale()
call  (before  or after MinLBFGSSetPrecScale() call). Without knowledge of
the scale of your variables scale-based preconditioner will be  just  unit
matrix.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
전제 조건의 수정 : 스케일 기반 대각선 전제 조건.
이 사전 조절 모드는 근사치가 없을 때 유용 할 수 있습니다.
헤 시안 (Hessian)의 대각선이지만, 변수가 잘못 조정 된 것을 알고 있습니다.
(예를 들어, 하나의 변수는 [1,10]에 있고 다른 변수는 [1000,100000]에 있음)
그리고 불량 조절의 대부분은 다양한 범위의 바에서 비롯됩니다.
이 경우 H [i] = 1 / (s [i] ^ 2) 인 간단한 스케일 기반 전처리 기가
융합을 크게 향상시킬 수 있습니다.
IMPLTANT : MinLBFGSSetScale ()을 사용하여 변수의 스케일을 설정해야합니다.
call (MinLBFGSSetPrecScale () 호출 전후). 지식이 없으면
변수의 스케일 규모 기반 전처리 부는 단지 단위 일 것입니다
매트릭스.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetprecscale(const minlbfgsstate &state);


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
bool minlbfgsiteration(const minlbfgsstate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear optimizer

These functions accept following parameters:
    state   -   algorithm state
    func    -   callback which calculates function (or merit function)
                value func at given point x
    grad    -   callback which calculates function (or merit function)
                value func and gradient grad at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL

NOTES:

1. This function has two different implementations: one which  uses  exact
   (analytical) user-supplied gradient,  and one which uses function value
   only  and  numerically  differentiates  function  in  order  to  obtain
   gradient.

   Depending  on  the  specific  function  used to create optimizer object
   (either MinLBFGSCreate() for analytical gradient  or  MinLBFGSCreateF()
   for numerical differentiation) you should choose appropriate variant of
   MinLBFGSOptimize() - one  which  accepts  function  AND gradient or one
   which accepts function ONLY.

   Be careful to choose variant of MinLBFGSOptimize() which corresponds to
   your optimization scheme! Table below lists different  combinations  of
   callback (function/gradient) passed to MinLBFGSOptimize()  and specific
   function used to create optimizer.


                     |         USER PASSED TO MinLBFGSOptimize()
   CREATED WITH      |  function only   |  function and gradient
   ------------------------------------------------------------
   MinLBFGSCreateF() |     work                FAIL
   MinLBFGSCreate()  |     FAIL                work

   Here "FAIL" denotes inappropriate combinations  of  optimizer  creation
   function  and  MinLBFGSOptimize()  version.   Attemps   to   use   such
   combination (for example, to create optimizer with MinLBFGSCreateF() and
   to pass gradient information to MinCGOptimize()) will lead to exception
   being thrown. Either  you  did  not pass gradient when it WAS needed or
   you passed gradient when it was NOT needed.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey

*************************************************************************/
/**************************************************************************
이 함수 계열은 비선형 최적화 알고리즘의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    func - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func
    grad - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func 및 gradient grad
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
노트:
1.이 함수는 두 가지 구현이 있습니다 :
   (분석적인) 사용자 제공 그래디언트와 함수 값을 사용하는 그래디언트
   오직 함수를 수치 적으로 구별하여 구하기 위해
   구배.
   최적화 프로그램 개체를 만드는 데 사용 된 특정 함수에 따라
   (분석 그래디언트의 경우 MinLBFGSCreate () 또는 MinLBFGSCreateF ()
   수치 차별화의 경우)의 적절한 변형을 선택해야합니다.
   MinLBFGSOptimize () - 함수 AND 기울기 또는 하나를 허용하는 함수
   기능 만 허용합니다.
   MinLBFGSOptimize ()의 변형을 선택하는 것에주의하십시오.
   귀하의 최적화 계획! 아래 표에는
   MinLBFGSOptimize ()에 전달 된 콜백 (함수 / 그래디언트) 및 특정
   최적화 프로그램을 만드는 데 사용되는 함수.
                     | 사용자가 MinLBFGSOptimize ()에 전달 함
   창조 된 | 기능 만 | 함수 및 그래디언트
   -------------------------------------------------- ----------
   MinLBFGSCreateF () | 직장 불합격
   MinLBFGSCreate () | FAIL 작업
   여기서 "FAIL"은 최적화 도구 작성의 부적절한 조합을 나타냅니다.
   함수 및 MinLBFGSOptimize () 버전. 그러한 시도를 시도하다.
   조합 (예 : MinLBFGSCreateF () 및
   그라디언트 정보를 MinCGOptimize ()에 전달하면 예외가 발생합니다.
   던져지고있다. 그라디언트가 필요하거나 필요할 때 그라데이션을 전달하지 않았거나
   필요하지 않을 때 그라데이션을 전달했습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.03.2009
**************************************************************************/
void minlbfgsoptimize(minlbfgsstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void minlbfgsoptimize(minlbfgsstate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);


/*************************************************************************
L-BFGS algorithm results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -7    gradient verification failed.
                            See MinLBFGSSetGradientCheck() for more information.
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
L-BFGS 알고리즘 결과
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액
    담당자 최적화 보고서 :
                * Rep.TerminationType 완성 코드 :
                    * -7 그래디언트 확인에 실패했습니다.
                            자세한 정보는 MinLBFGSSetGradientCheck ()를 참조하십시오.
                    * -2 반올림 오류로 인해 더 이상 개선되지 않습니다.
                            X는 가장 좋은 점을 발견했습니다.
                    * -1 잘못된 매개 변수가 지정되었습니다.
                    * 1 상대 기능 개선은
                            EpsF.
                    * 2 상대 단계는 EpsX 이상입니다.
                    * 4 그래디언트 표준은 EpsG 이상입니다.
                    * 5 MaxIts 단계가 수행되었습니다.
                    * 7 정지 조건은 너무 엄격합니다.
                            더 이상의 개선은 불가능하다.
                * Rep.IterationsCount에는 반복 횟수가 포함됩니다.
                * NFEV countains 함수 계산 횟수
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgsresults(const minlbfgsstate &state, real_1d_array &x, minlbfgsreport &rep);


/*************************************************************************
L-BFGS algorithm results

Buffered implementation of MinLBFGSResults which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
L-BFGS 알고리즘 결과
미리 할당 된 버퍼를 사용하는 MinLBFGSResults의 버퍼 된 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     저작권 20.08.2010 Bochkanov Sergey
*************************************************** ***********************/
void minlbfgsresultsbuf(const minlbfgsstate &state, real_1d_array &x, minlbfgsreport &rep);


/*************************************************************************
This  subroutine restarts LBFGS algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 LBFGS 알고리즘을 새 지점에서 다시 시작합니다. 모든 최적화
매개 변수는 변경되지 않습니다.
이 함수는 여러 개의 최적화 문제를 해결할 수 있습니다.
오브젝트 재 할당 패널티가없는 동일한 수의 치수가 있어야합니다.
입력 매개 변수 :
    상태 - 알고리즘 상태를 저장하는 데 사용되는 구조
    X - 새로운 출발점.
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgsrestartfrom(const minlbfgsstate &state, const real_1d_array &x);


/*************************************************************************
This  subroutine  turns  on  verification  of  the  user-supplied analytic
gradient:
* user calls this subroutine before optimization begins
* MinLBFGSOptimize() is called
* prior to  actual  optimization, for each component  of  parameters being
  optimized X[i] algorithm performs following steps:
  * two trial steps are made to X[i]-TestStep*S[i] and X[i]+TestStep*S[i],
    where X[i] is i-th component of the initial point and S[i] is a  scale
    of i-th parameter
  * if needed, steps are bounded with respect to constraints on X[]
  * F(X) is evaluated at these trial points
  * we perform one more evaluation in the middle point of the interval
  * we  build  cubic  model using function values and derivatives at trial
    points and we compare its prediction with actual value in  the  middle
    point
  * in case difference between prediction and actual value is higher  than
    some predetermined threshold, algorithm stops with completion code -7;
    Rep.VarIdx is set to index of the parameter with incorrect derivative.
* after verification is over, algorithm proceeds to the actual optimization.

NOTE 1: verification  needs  N (parameters count) gradient evaluations. It
        is very costly and you should use  it  only  for  low  dimensional
        problems,  when  you  want  to  be  sure  that  you've   correctly
        calculated  analytic  derivatives.  You  should  not use it in the
        production code (unless you want to check derivatives provided  by
        some third party).

NOTE 2: you  should  carefully  choose  TestStep. Value which is too large
        (so large that function behaviour is significantly non-cubic) will
        lead to false alarms. You may use  different  step  for  different
        parameters by means of setting scale with MinLBFGSSetScale().

NOTE 3: this function may lead to false positives. In case it reports that
        I-th  derivative was calculated incorrectly, you may decrease test
        step  and  try  one  more  time  - maybe your function changes too
        sharply  and  your  step  is  too  large for such rapidly chanding
        function.

INPUT PARAMETERS:
    State       -   structure used to store algorithm state
    TestStep    -   verification step:
                    * TestStep=0 turns verification off
                    * TestStep>0 activates verification

  -- ALGLIB --
     Copyright 24.05.2012 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 사용자가 제공 한 분석의 검증을 켭니다.
구배:
* 최적화가 시작되기 전에 사용자가이 서브 루틴 호출
* MinLBFGSOptimize ()가 호출됩니다.
* 매개 변수의 각 구성 요소에 대한 실제 최적화 이전
  최적화 된 X [i] 알고리즘은 다음 단계를 수행합니다.
  * X [i] -TestStep * S [i] 및 X [i] + TestStep * S [i]에 대해 두 번의 시험 단계가 수행됩니다.
    여기서 X [i]는 초기 점의 i 번째 구성 요소이고 S [i]는 스케일입니다
    i 번째 매개 변수
  * 필요한 경우 단계는 X []에 대한 제약 조건에 따라 제한됩니다.
  * F (X)는 이러한 시험 포인트에서 평가됩니다.
  * 간격의 중간 지점에서 또 하나의 평가를 수행합니다.
  * 우리는 함수 값과 파생 상품을 사용하여 삼차원 모델을 시험해 보았다.
    우리는 예측치를 중간의 실제 값과 비교합니다
    포인트
  * 예상 값과 실제 값의 차이가
    소정의 소정의 임계 값, 알고리즘은 완료 코드 -7로 정지한다;
    Rep.VarIdx가 잘못된 파생어로 매개 변수의 인덱스로 설정됩니다.
* 검증이 끝나면 알고리즘은 실제 최적화로 진행합니다.
주 1 : 검증은 N (매개 변수 개수) 그라디언트 평가가 필요하다. 그것
        매우 비용이 많이 들며 낮은 차원에서만 사용해야합니다.
        문제, 당신이 당신이 올바르게했는지 알고 싶을 때
        계산 된 파생 상품. 당신은
        생산 코드 (귀하가 제공 한 파생 상품을 확인하고 싶지 않은 경우)
        제 3 자).
참고 2 : TestStep을 신중하게 선택해야합니다. 너무 큰 값
        (너무 커서 함수의 동작은 상당히 비 큐빅이다.)
        거짓 경보로 연결됩니다. 다른 단계를 사용할 수도 있습니다.
        MinLBFGSSetScale ()을 사용하여 축척을 설정하여 매개 변수를 설정합니다.
참고 3 :이 기능은 위양성을 유발할 수 있습니다. 보고서에
        I 차수 미분이 잘못 계산되었으므로 테스트를 줄일 수 있습니다.
        한 번 더 시도해보십시오. 아마도 기능이 변경 될 수도 있습니다.
        급격하게 그리고 당신의 발걸음이 그렇게 급속히 챈드하기에는 너무 큽니다.
        기능.
입력 매개 변수 :
    상태 - 알고리즘 상태를 저장하는 데 사용되는 구조
    TestStep - 확인 단계 :
                    * TestStep = 0으로 설정하면 인증이 해제됩니다.
                    * TestStep> 0으로 인증이 활성화됩니다.
  - ALGLIB -
     Copyright 24.05.2012 Bochkanov Sergey
**************************************************************************/
void minlbfgssetgradientcheck(const minlbfgsstate &state, const double teststep);

/*************************************************************************
                    CONSTRAINED QUADRATIC PROGRAMMING

The subroutine creates QP optimizer. After initial creation,  it  contains
default optimization problem with zero quadratic and linear terms  and  no
constraints. You should set quadratic/linear terms with calls to functions
provided by MinQP subpackage.

INPUT PARAMETERS:
    N       -   problem size

OUTPUT PARAMETERS:
    State   -   optimizer with zero quadratic/linear terms
                and no constraints

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
                    제한된 방정식 프로그래밍
서브 루틴은 QP 최적화 프로그램을 작성합니다. 초기 생성 후
0 차 2 차 및 선형 항이있는 기본 최적화 문제
제약 조건. 함수에 대한 호출로 2 차 / 선형 항을 설정해야합니다.
MinQP 하위 패키지에서 제공됩니다.
입력 매개 변수 :
    N - 문제 크기
출력 매개 변수 :
    0 차 2 차 / 선형 항이있는 상태 최적화
                제약 조건 없음
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpcreate(const ae_int_t n, minqpstate &state);


/*************************************************************************
This function sets linear term for QP solver.

By default, linear term is zero.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    B       -   linear term, array[N].

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP 솔버의 선형 항을 설정합니다.
기본적으로 선형 항은 0입니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    B - 선형 항, array [N].
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
*************************************************** ***********************/
void minqpsetlinearterm(const minqpstate &state, const real_1d_array &b);


/*************************************************************************
This  function  sets  dense  quadratic  term  for  QP solver. By  default,
quadratic term is zero.

SUPPORT BY ALGLIB QP ALGORITHMS:

Dense quadratic term can be handled by any of the QP algorithms  supported
by ALGLIB QP Solver.

IMPORTANT:

This solver minimizes following  function:
    f(x) = 0.5*x'*A*x + b'*x.
Note that quadratic term has 0.5 before it. So if  you  want  to  minimize
    f(x) = x^2 + x
you should rewrite your problem as follows:
    f(x) = 0.5*(2*x^2) + x
and your matrix A will be equal to [[2.0]], not to [[1.0]]

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    A       -   matrix, array[N,N]
    IsUpper -   (optional) storage type:
                * if True, symmetric matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t used
                * if False, symmetric matrix  A  is  given  by  its lower
                  triangle, and the upper triangle isn\92t used
                * if not given, both lower and upper  triangles  must  be
                  filled.

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP solver에 대한 조밀 한 2 차 항을 설정합니다. 기본적으로,
2 차항은 0입니다.
ALGLIB QP 알고리즘에 의한 지원 :
조밀 한 2 차항은 지원되는 QP 알고리즘으로 처리 할 수 ​​있습니다.
ALGLIB QP 해법.
중대한:
이 솔버는 다음 기능을 최소화합니다.
    f (x) = 0.5 * x '* A * x + b'* x.
두 번째 항은 그 앞에 0.5가 있음에 유의하십시오. 그래서 당신이 최소화하고 싶다면
    f (x) = x ^ 2 + x
다음과 같이 문제점을 다시 작성해야합니다.
    f (x) = 0.5 * (2 * x ^ 2) + x
행렬 A는 [[2.0]]이 ​​아니라 [[1.0]]이됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    A - 행렬, 배열 [N, N]
    IsUpper - (선택 사항) 저장 유형 :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형, 아래 삼각형은 사용되지 않습니다
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형 및 위 삼각형은 사용되지 않습니다.
                * 주어지지 않았다면, 아래쪽 삼각형과 위 쪽 삼각형 모두
                  채우는.
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetquadraticterm(const minqpstate &state, const real_2d_array &a, const bool isupper);
void minqpsetquadraticterm(const minqpstate &state, const real_2d_array &a);


/*************************************************************************
This  function  sets  sparse  quadratic  term  for  QP solver. By default,
quadratic term is zero.

SUPPORT BY ALGLIB QP ALGORITHMS:

Sparse quadratic term is supported only by BLEIC-based QP  algorithm  (one
which is activated by MinQPSetAlgoBLEIC function). Cholesky-based QP  algo
won't be able to deal  with  sparse  quadratic  term  and  will  terminate
abnormally.

IF YOU CALLED THIS FUNCTION, YOU MUST SWITCH TO BLEIC-BASED  QP  ALGORITHM
BEFORE CALLING MINQPOPTIMIZE() FUNCTION.

IMPORTANT:

This solver minimizes following  function:
    f(x) = 0.5*x'*A*x + b'*x.
Note that quadratic term has 0.5 before it. So if  you  want  to  minimize
    f(x) = x^2 + x
you should rewrite your problem as follows:
    f(x) = 0.5*(2*x^2) + x
and your matrix A will be equal to [[2.0]], not to [[1.0]]

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    A       -   matrix, array[N,N]
    IsUpper -   (optional) storage type:
                * if True, symmetric matrix  A  is  given  by  its  upper
                  triangle, and the lower triangle isn\92t used
                * if False, symmetric matrix  A  is  given  by  its lower
                  triangle, and the upper triangle isn\92t used
                * if not given, both lower and upper  triangles  must  be
                  filled.

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP 솔버에 대한 희소 2 차 항을 설정합니다. 기본적으로,
2 차항은 0입니다.
ALGLIB QP 알고리즘에 의한 지원 :
스파 스 2 차항은 BLEIC 기반 QP 알고리즘 (하나
MinQPSetAlgoBLEIC 함수에 의해 활성화됩니다). 콜레 스키 기반 QP algo
스파 스 2 차항을 처리 할 수 ​​없으며 종료됩니다.
비정상적으로
이 기능을 호출했다면, 당신은 BLEIC 기반 QP 알고리즘으로 전환해야합니다.
MINQPOPTIMIZE () 함수를 호출하기 전에.
중대한:
이 솔버는 다음 기능을 최소화합니다.
    f (x) = 0.5 * x '* A * x + b'* x.
두 번째 항은 그 앞에 0.5가 있음에 유의하십시오. 그래서 당신이 최소화하고 싶다면
    f (x) = x ^ 2 + x
다음과 같이 문제점을 다시 작성해야합니다.
    f (x) = 0.5 * (2 * x ^ 2) + x
행렬 A는 [[2.0]]이 ​​아니라 [[1.0]]이됩니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    A - 행렬, 배열 [N, N]
    IsUpper - (선택 사항) 저장 유형 :
                * True이면 대칭 행렬 A가 그 대문자로 주어집니다.
                  삼각형, 아래 삼각형은 사용되지 않습니다
                * False 인 경우, 대칭 행렬 A는 그 lower에 의해 주어진다.
                  삼각형 및 위 삼각형은 사용되지 않습니다.
                * 주어지지 않았다면, 아래쪽 삼각형과 위 쪽 삼각형 모두
                  채우는.
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetquadratictermsparse(const minqpstate &state, const sparsematrix &a, const bool isupper);


/*************************************************************************
This function sets starting point for QP solver. It is useful to have
good initial approximation to the solution, because it will increase
speed of convergence and identification of active constraints.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    X       -   starting point, array[N].

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP 솔버의 시작점을 설정합니다. 가지고 다니는 것이 유용하다.
솔루션에 대한 좋은 초기 근사값. 증가 할 것이므로
수렴 속도와 능동적 인 구속 조건의 확인.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    X - 시작점, 배열 [N].
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetstartingpoint(const minqpstate &state, const real_1d_array &x);


/*************************************************************************
This  function sets origin for QP solver. By default, following QP program
is solved:

    min(0.5*x'*A*x+b'*x)

This function allows to solve different problem:

    min(0.5*(x-x_origin)'*A*(x-x_origin)+b'*(x-x_origin))

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    XOrigin -   origin, array[N].

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP 솔버의 원점을 설정합니다. 기본적으로 QP 프로그램에 따라
해결됨 :
    분 (0.5 * x '* A * x + b'* x)
이 함수는 다른 문제를 해결할 수 있습니다 :
    min (0.5 * (x-x_origin) * A * (x-x_origin) + b '* (x-x_origin))
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    XOrigin - 원점, 배열 [N].
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetorigin(const minqpstate &state, const real_1d_array &xorigin);


/*************************************************************************
This function sets scaling coefficients.

ALGLIB optimizers use scaling matrices to test stopping  conditions  (step
size and gradient are scaled before comparison with tolerances).  Scale of
the I-th variable is a translation invariant measure of:
a) "how large" the variable is
b) how large the step should be to make significant changes in the function

BLEIC-based QP solver uses scale for two purposes:
* to evaluate stopping conditions
* for preconditioning of the underlying BLEIC solver

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    S       -   array[N], non-zero scaling coefficients
                S[i] may be negative, sign doesn't matter.

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 스케일링 계수를 설정합니다.
ALGLIB 최적화 프로그램은 스케일링 매트릭스를 사용하여 정지 조건을 테스트합니다 (단계
크기 및 그래디언트는 공차와 비교하기 전에 크기가 조정됩니다.) 규모
I 번째 변수는 다음에 대한 변환 불변성 측정 값입니다.
a) 변수의 "크기"
b) 함수에서 중요한 변화를 만드는 단계는 얼마나 커야 하는가?
BLEIC 기반 QP 솔버는 두 가지 용도로 스케일을 사용합니다.
* 정지 조건 평가
* 기본 BLEIC 솔버의 전제 조건
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    S - 배열 [N], 0이 아닌 스케일링 계수
                S [i]는 음수 일 수 있습니다. 부호는 중요하지 않습니다.
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetscale(const minqpstate &state, const real_1d_array &s);


/*************************************************************************
This function tells solver to use Cholesky-based algorithm. This algorithm
is active by default.

DESCRIPTION:

Cholesky-based algorithm can be used only for problems which:
* have dense quadratic term, set  by  MinQPSetQuadraticTerm(),  sparse  or
  structured problems are not supported.
* are strictly convex, i.e. quadratic term is symmetric positive definite,
  indefinite or semidefinite problems are not supported by this algorithm.

If anything of what listed above is violated, you may use  BLEIC-based  QP
algorithm which can be activated by MinQPSetAlgoBLEIC().

BENEFITS AND DRAWBACKS:

This  algorithm  gives  best  precision amongst all QP solvers provided by
ALGLIB (Newton iterations  have  much  higher  precision  than  any  other
optimization algorithm). This solver also gracefully handles problems with
very large amount of constraints.

Performance of the algorithm is good because internally  it  uses  Level 3
Dense BLAS for its performance-critical parts.


From the other side, algorithm has  O(N^3)  complexity  for  unconstrained
problems and up to orders of  magnitude  slower  on  constrained  problems
(these additional iterations are needed to identify  active  constraints).
So, its running time depends on number of constraints active  at solution.

Furthermore, this algorithm can not solve problems with sparse matrices or
problems with semidefinite/indefinite matrices of any kind (dense/sparse).

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 Cholesky 기반 알고리즘을 사용하도록 솔버에 지시합니다. 이 알고리즘
기본적으로 활성화되어 있습니다.
기술:
콜레 스키 기반 알고리즘은 다음과 같은 문제에 대해서만 사용할 수 있습니다.
* MinQPSetQuadraticTerm ()에 의해 설정된 밀도가 높은 이차 항이 있음, 스파 스 또는
  구조화 된 문제점은 지원되지 않습니다.
*는 철저하게 볼록하다. 즉, 2 차항은 대칭적인 양의 확정적이다.
  이 알고리즘에서는 무기한 또는 semidefinite 문제가 지원되지 않습니다.
위에서 열거 한 사항 중 하나라도 위반하면 BLEIC 기반 QP를 사용할 수 있습니다
알고리즘은 MinQPSetAlgoBLEIC ()에 의해 활성화 될 수 있습니다.
이점과 단점 :
이 알고리즘은에 의해 제공되는 모든 QP 솔버 중에서 최고의 정밀도를 제공합니다.
ALGLIB (뉴턴 반복은 다른 어떤 것보다 훨씬 더 높은 정밀도를가집니다.
최적화 알고리즘). 이 솔버는 또한 다음과 같은 문제를 정상적으로 처리합니다.
매우 많은 양의 제약.
내부적으로 레벨 3을 사용하기 때문에 알고리즘의 성능이 좋습니다.
성능이 중요한 부품을위한 고밀도 BLAS.
다른 측면에서 알고리즘은 제약이없는 경우 O (N ^ 3)의 복잡성을 갖습니다.
제한된 문제로 인해 문제가 발생하고 최대 속도가 느려짐
(이러한 추가 반복은 활성 제한 조건을 식별하는 데 필요합니다).
따라서 실행 시간은 솔루션에서 활성화되는 제약 조건의 수에 따라 달라집니다.
또한,이 알고리즘은 희소 행렬 또는
어떤 종류의 고 유한 / 불명확 행렬 문제 (조밀 / 희소).
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetalgocholesky(const minqpstate &state);


/*************************************************************************
This function tells solver to use BLEIC-based algorithm and sets  stopping
criteria for the algorithm.

DESCRIPTION:

BLEIC-based QP algorithm can be used for any kind of QP problems:
* problems with both dense and sparse quadratic terms
* problems with positive definite, semidefinite, indefinite terms

BLEIC-based algorithm can solve even indefinite problems - as long as they
are bounded from below on the feasible set. Of course, global  minimum  is
found only  for  positive  definite  and  semidefinite  problems.  As  for
indefinite ones - only local minimum is found.

BENEFITS AND DRAWBACKS:

This algorithm can be used to solve both convex and indefinite QP problems
and it can utilize sparsity of the quadratic  term  (algorithm  calculates
matrix-vector products, which can be  performed  efficiently  in  case  of
sparse matrix).

Algorithm has iteration cost, which (assuming fixed amount of non-boundary
linear constraints) linearly depends on problem size. Boundary constraints
does not significantly change iteration cost.

Thus, it outperforms Cholesky-based QP algorithm (CQP) on high-dimensional
sparse problems with moderate amount of constraints.


From the other side, unlike CQP solver, this algorithm does NOT  make  use
of Level 3 Dense BLAS. Thus, its performance on dense problems is inferior
to that of CQP solver.

Its precision is also inferior to that of CQP. CQP performs  Newton  steps
which are know to achieve very good  precision. In many cases Newton  step
leads us exactly to the solution. BLEIC-QP performs LBFGS steps, which are
good at detecting neighborhood of the solution, buy need  many  iterations
to find solution with 6 digits of precision.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                |v|<EpsG is satisfied, where:
                * |.| means Euclidian norm
                * v - scaled constrained gradient vector, v[i]=g[i]*s[i]
                * g - gradient
                * s - scaling coefficients set by MinQPSetScale()
    EpsF    -   >=0
                The  subroutine  finishes  its work if exploratory steepest
                descent  step  on  k+1-th  iteration  satisfies   following
                condition:  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
    EpsX    -   >=0
                The  subroutine  finishes  its work if exploratory steepest
                descent  step  on  k+1-th  iteration  satisfies   following
                condition:
                * |.| means Euclidian norm
                * v - scaled step vector, v[i]=dx[i]/s[i]
                * dx - step vector, dx=X(k+1)-X(k)
                * s - scaling coefficients set by MinQPSetScale()
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0 and EpsX=0 and MaxIts=0 (simultaneously) will lead
to automatic stopping criterion selection (presently it is  small    step
length, but it may change in the future versions of ALGLIB).

IT IS VERY IMPORTANT THAT YOU CALL MinQPSetScale() WHEN YOU USE THIS ALGO!

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 Solver에게 BLEIC 기반 알고리즘을 사용하도록 지시하고 중지를 설정합니다.
알고리즘에 대한 기준.
기술:
BLEIC 기반 QP 알고리즘은 모든 종류의 QP 문제에 사용할 수 있습니다.
조밀하고 희소 한 2 차 항에 대한 문제
* 긍정적 인 명확한, semidefinite, 불명확 한 기간을 가진 문제
BLEIC 기반 알고리즘은 심지어 무기한 문제도 해결할 수 있습니다.
가능한 집합에서 아래로부터 경계를 이룬다. 물론 글로벌 최소값은
긍정적 인 명확하고 semidefinite 문제에서만 발견된다. ~에 관해서는
무기한 - 지역 최소값 만 발견됩니다.
이점과 단점 :
이 알고리즘은 볼록한 QP 문제와 불명확 한 QP 문제를 해결하는 데 사용할 수 있습니다.
2 차 항의 희소성을 이용할 수있다 (알고리즘은
행렬 - 벡터 곱을 효율적으로 수행 할 수있는
스파 스 매트릭스).
알고리즘은 반복 비용을 갖는다. (고정 된 양의 비 경계
선형 제약 조건)은 문제 크기에 선형 적으로 의존합니다. 경계 제약 조건
반복 비용을 크게 변경하지 않습니다.
따라서 Cholesky 기반의 QP 알고리즘 (CQP)을 고차원
적당한 양의 제약 조건을 가진 희소 한 문제
CQP 솔버와는 달리,이 알고리즘은 사용하지 않습니다.
레벨 3 밀도 BLAS. 따라서 밀도가 높은 문제에 대한 성능이 떨어집니다.
CQP 해결 자의 그것에.
그것의 정밀도는 CQP의 그것보다 열등합니다. CQP는 뉴턴 단계를 수행합니다.
이는 매우 우수한 정밀도를 달성하는 것으로 알려져 있습니다. 많은 경우에 뉴턴 단계
우리를 솔루션으로 정확하게 인도합니다. BLEIC-QP는 LBFGS 단계를 수행합니다.
솔루션 이웃을 감지하는 데 능숙하고 많은 반복이 필요합니다.
정밀도가 6 자리 인 솔루션을 찾으십시오.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsG -> = 0
                서브 루틴은 조건
                | v | <EpsG가 만족되면,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 구속 조건 벡터, v [i] = g [i] * s [i]
                * g - 그래디언트
                * s - MinQPSetScale ()에 의해 설정된 스케일링 계수
    EpsF -> = 0
                탐사선이 가장 가파른 경우 서브 루틴은 작업을 완료합니다.
                k + 1 번째 반복에 대한 하강 스텝은
                조건 : | F (k + 1) -F (k) | <= EpsF * max {| F (k) |, | F (k + 1) |, 1}
    EpsX -> = 0
                탐사선이 가장 가파른 경우 서브 루틴은 작업을 완료합니다.
                k + 1 번째 반복에 대한 하강 스텝은
                조건:
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 스텝 벡터, v [i] = dx [i] / s [i]
                * dx - 스텝 벡터, dx = X (k + 1) -X (k)
                * s - MinQPSetScale ()에 의해 설정된 스케일링 계수
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다.
EpsG = 0, EpsF = 0 및 EpsX = 0 및 MaxIts = 0 (동시에)을 전달하면
자동 정지 기준 선택 (현재 그것은 작은 단계입니다
길이이지만 ALGLIB의 향후 버전에서 변경 될 수 있음).
이 경고를 사용하면 MinQPSetScale ()을 호출하는 것이 중요합니다!
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetalgobleic(const minqpstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
This function sets boundary constraints for QP solver

Boundary constraints are inactive by default (after initial creation).
After  being  set,  they  are  preserved  until explicitly turned off with
another SetBC() call.

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    BndL    -   lower bounds, array[N].
                If some (all) variables are unbounded, you may specify
                very small number or -INF (latter is recommended because
                it will allow solver to use better algorithm).
    BndU    -   upper bounds, array[N].
                If some (all) variables are unbounded, you may specify
                very large number or +INF (latter is recommended because
                it will allow solver to use better algorithm).

NOTE: it is possible to specify BndL[i]=BndU[i]. In this case I-th
variable will be "frozen" at X[i]=BndL[i]=BndU[i].

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP 솔버의 경계 제약 조건을 설정합니다.
경계 제약 조건은 기본적으로 비활성화됩니다 (초기 생성 후).
설정 후 명시 적으로 해제 될 때까지 보존됩니다.
다른 SetBC () 호출.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    BndL - 하한, 배열 [N].
                일부 (모든) 변수에 제한이없는 경우,
                매우 작은 수 또는 -INF (후자가 권장됩니다.
                그것은 솔버가 더 나은 알고리즘을 사용할 수있게 해줍니다).
    BndU - 상한, 배열 [N].
                일부 (모든) 변수에 제한이없는 경우,
                매우 큰 숫자 또는 + INF (후자가 권장됩니다.
                그것은 솔버가 더 나은 알고리즘을 사용할 수있게 해줍니다).
참고 : BndL [i] = BndU [i]를 지정할 수 있습니다. 이 경우 I-th
변수는 X [i] = BndL [i] = BndU [i]에서 "고정"됩니다.
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpsetbc(const minqpstate &state, const real_1d_array &bndl, const real_1d_array &bndu);


/*************************************************************************
This function sets linear constraints for QP optimizer.

Linear constraints are inactive by default (after initial creation).

INPUT PARAMETERS:
    State   -   structure previously allocated with MinQPCreate call.
    C       -   linear constraints, array[K,N+1].
                Each row of C represents one constraint, either equality
                or inequality (see below):
                * first N elements correspond to coefficients,
                * last element corresponds to the right part.
                All elements of C (including right part) must be finite.
    CT      -   type of constraints, array[K]:
                * if CT[i]>0, then I-th constraint is C[i,*]*x >= C[i,n+1]
                * if CT[i]=0, then I-th constraint is C[i,*]*x  = C[i,n+1]
                * if CT[i]<0, then I-th constraint is C[i,*]*x <= C[i,n+1]
    K       -   number of equality/inequality constraints, K>=0:
                * if given, only leading K elements of C/CT are used
                * if not given, automatically determined from sizes of C/CT

NOTE 1: linear (non-bound) constraints are satisfied only approximately  -
        there always exists some minor violation (about 10^-10...10^-13)
        due to numerical errors.

  -- ALGLIB --
     Copyright 19.06.2012 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 QP 최적화 프로그램에 대한 선형 제한 조건을 설정합니다.
선형 제약 조건은 기본적으로 비활성화됩니다 (초기 생성 후).
입력 매개 변수 :
    상태 - 이전에 MinQPCreate 호출로 할당 된 구조체.
    C - 선형 구속 조건, array [K, N + 1].
                C의 각 행은 하나의 제약 조건을 나타냅니다.
                또는 불평등 (아래 참조) :
                * 첫 번째 N 요소는 계수에 해당하고,
                * 마지막 요소는 오른쪽 부분에 해당합니다.
                C의 모든 요소 (오른쪽 부분 포함)는 유한해야합니다.
    CT - 제약 조건, 배열 [K] :
                * CT [i]> 0이면, I 번째 제약은 C [i, *] * x> = C [i, n + 1]
                * CT [i] = 0이면, I 번째 제약은 C [i, *] * x = C [i, n + 1]
                * CT [i] <0 인 경우, I 번째 제약은 C [i, *] * x <= C [i, n + 1]
    K - 평등 / 불평등 제약의 수, K> = 0 :
                * 주어진 경우 C / CT의 선행 K 요소 만 사용됩니다.
                * 주어지지 않은 경우, C / CT의 크기로부터 자동으로 결정됩니다.
비고 1 : 선형 (비 구속) 제약 조건은 단지 대략 만족된다 -
        사소한 위반이 항상 존재합니다 (약 10 ^ -10 ... 10 ^ -13)
        수치 오류 때문입니다.
  - ALGLIB -
     저작권 19.06.2012 Bochkanov Sergey
**************************************************************************/
void minqpsetlc(const minqpstate &state, const real_2d_array &c, const integer_1d_array &ct, const ae_int_t k);
void minqpsetlc(const minqpstate &state, const real_2d_array &c, const integer_1d_array &ct);


/*************************************************************************
This function solves quadratic programming problem.
You should call it after setting solver options with MinQPSet...() calls.

INPUT PARAMETERS:
    State   -   algorithm state

You should use MinQPResults() function to access results after calls
to this function.

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey.
     Special thanks to Elvira Illarionova  for  important  suggestions  on
     the linearly constrained QP algorithm.
*************************************************************************/
/**************************************************************************
이 함수는 2 차 프로그래밍 문제를 해결합니다.
MinQPSet ... () 호출로 해석기 옵션을 설정 한 후에 호출해야합니다.
입력 매개 변수 :
    상태 - 알고리즘 상태
MinQPResults () 함수를 사용하여 호출 후 결과에 액세스해야합니다.
이 기능에.
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey.
     Elvira Illarionova에게 중요한 제안에 대한 감사드립니다.
     선형 제약 QP 알고리즘
**************************************************************************/
void minqpoptimize(const minqpstate &state);


/*************************************************************************
QP solver results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution.
                This array is allocated and initialized only when
                Rep.TerminationType parameter is positive (success).
    Rep     -   optimization report. You should check Rep.TerminationType,
                which contains completion code, and you may check  another
                fields which contain another information  about  algorithm
                functioning.

                Failure codes returned by algorithm are:
                * -5    inappropriate solver was used:
                        * Cholesky solver for (semi)indefinite problems
                        * Cholesky solver for problems with sparse matrix
                * -4    BLEIC-QP algorithm found unconstrained direction
                        of negative curvature (function is unbounded from
                        below  even  under  constraints),  no  meaningful
                        minimum can be found.
                * -3    inconsistent constraints (or maybe  feasible point
                        is too  hard  to  find).  If  you  are  sure  that
                        constraints are feasible, try to restart optimizer
                        with better initial approximation.

                Completion codes specific for Cholesky algorithm:
                *  4   successful completion

                Completion codes specific for BLEIC-based algorithm:
                *  1   relative function improvement is no more than EpsF.
                *  2   scaled step is no more than EpsX.
                *  4   scaled gradient norm is no more than EpsG.
                *  5   MaxIts steps was taken

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
QP 솔버 결과
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액.
                이 배열은, 다음의 경우에만 할당 및 초기화됩니다.
                Rep.TerminationType 매개 변수는 양수입니다 (성공).
    담당자 최적화 보고서. Rep.TerminationType을 확인해야합니다.
                완료 코드가 포함되어 있으며 다른 코드를 확인할 수 있습니다
                알고리즘에 관한 다른 정보를 포함한 필드
                작동.
                알고리즘에 의해 반환 된 오류 코드는 다음과 같습니다.
                * -5 부적절한 해결사 사용 :
                        * (세미) 무기한 문제에 대한 Cholesky 해결사
                        * 희소 매트릭스 문제에 대한 콜레 스키 솔버
                * -4 BLEIC-QP 알고리즘이 제약없는 방향을 찾았습니다.
                        음의 곡률 (함수는
                        제약 하에서도 아래), 의미가 없음
                        최소값을 찾을 수 있습니다.
                * -3 일치하지 않는 제약 조건 (또는 실현 가능성이있는 점
                        너무 찾기가 어렵습니다). 그게 확실하다면
                        제약 조건이 가능하면 최적화 프로그램을 다시 시작하십시오.
                        더 나은 초기 근사법.
                콜레 스키 알고리즘에 대한 완료 코드 :
                * 4 성공적인 완료
                BLEIC 기반 알고리즘에 대한 완료 코드 :
                * 1 상대 기능 개선은 EpsF 이상입니다.
                * 2 단계는 EpsX 이상입니다.
                * 4 스케일 그라디언트 표준은 EpsG 이하입니다.
                * 5 MaxIts 단계가 수행되었습니다.
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpresults(const minqpstate &state, real_1d_array &x, minqpreport &rep);


/*************************************************************************
QP results

Buffered implementation of MinQPResults() which uses pre-allocated  buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 11.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
QP 결과
미리 할당 된 버퍼를 사용하는 MinQPResults ()의 버퍼 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     저작권 11.01.2011 Bochkanov Sergey
**************************************************************************/
void minqpresultsbuf(const minqpstate &state, real_1d_array &x, minqpreport &rep);

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] and Jacobian of f[].


REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec()  and jac() callbacks.
First  one  is used to calculate f[] at given point, second one calculates
f[] and Jacobian df[i]/dx[j].

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
                향상된 LEVENBERG-MARQUARDT 방법
                 비선형 최단 스퀘어 최적화
기술:
이 함수는 다음과 같이 표현 된 함수의 최소값을 찾는 데 사용됩니다.
제곱의 합:
    x [0], ..., x [n-1]) + ... + f [m-1] ^ 2 (x [0], ...) , x [n-1])
함수 벡터 f []의 값과 f []의 Jacobian을 사용한다.
요구 사항 :
이 알고리즘은 작동 중 다음 정보를 요청합니다.
* 주어진 점 X에서의 함수 벡터 f []
* 주어진 점에서 f [] (동시에)의 함수 벡터 f []와 Jacobian
MinLMOptimize () 함수의 오버로드 된 버전은 여러 가지가 있습니다.
이것에 의해 제공된 다른 LM- 유사 최적화 알고리즘에 대응한다.
단위. fvec () 및 jac () 콜백을 허용하는 버전을 선택해야합니다.
첫 번째 점은 주어진 점에서 f []를 계산하는 데 사용되며, 두 번째 점은 주어진 점에서 f []를 계산하는 데 사용됩니다.
f [] 및 Jacobian df [i] / dx [j]로 구성된다.
VJ 함수를 사용하여 MinLMState 구조를 초기화하고
잘못된 버전의 MinLMOptimize ()를 사용하십시오 (예 : version
일반 형식 함수로 작동하고 Jacobian을 제공하지 않음).
처음 시도를 시도한 후에 예외가 발생합니다.
자코비언.
용법:
1. 사용자가 MinLMCreateVJ () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 MinLMSetCond (), MinLMSetStpMax () 및 Solver 매개 변수를 조정합니다.
   다른 기능들
3. 알고리즘 상태를 취하는 MinLMOptimize () 함수를 호출하고
   콜백 함수.
4. 사용자가 솔루션을 얻기 위해 MinLMResults ()를 호출합니다.
5. 선택적으로 MinLMRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 N / M이지만 다른 시작점 및 / 또는 다른 기능을 사용합니다.
   MinLMRestartFrom ()은 이미 초기화 된 구조를 다시 사용할 수있게합니다.
입력 매개 변수 :
    N - 차원, N> 1
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    M - 함수의 수 f [i]
    X - 초기 해, array [0..N-1]
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. MinLMSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   MinLMSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 30.03.2009
**************************************************************************/
void minlmcreatevj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state);
void minlmcreatevj(const ae_int_t m, const real_1d_array &x, minlmstate &state);


/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] only. Finite differences  are  used  to
calculate Jacobian.


REQUIREMENTS:
This algorithm will request following information during its operation:
* function vector f[] at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec() callback.

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works with general form function and does not accept function vector), but
it will  lead  to  exception being thrown after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateV() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

See also MinLMIteration, MinLMResults.

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
                향상된 LEVENBERG-MARQUARDT 방법
                 비선형 최단 스퀘어 최적화
기술:
이 함수는 다음과 같이 표현 된 함수의 최소값을 찾는 데 사용됩니다.
제곱의 합:
    x [0], ..., x [n-1]) + ... + f [m-1] ^ 2 (x [0], ...) , x [n-1])
함수 벡터 f []만의 값을 사용합니다. 유한 한 차이점은
Jacobian을 계산하라.
요구 사항 :
이 알고리즘은 작동 중 다음 정보를 요청합니다.
* 주어진 점 X에서의 함수 벡터 f []
MinLMOptimize () 함수의 오버로드 된 버전은 여러 가지가 있습니다.
이것에 의해 제공된 다른 LM- 유사 최적화 알고리즘에 대응한다.
단위. fvec () 콜백을 허용하는 버전을 선택해야합니다.
VJ 함수를 사용하여 MinLMState 구조를 초기화하고
잘못된 버전의 MinLMOptimize ()를 사용하십시오 (예 : version
일반 형식 함수로 작동하고 함수 벡터를 허용하지 않음)
첫 번째 시도를 시도한 후에 예외가 발생합니다.
자코비언.
용법:
1. 사용자가 MinLMCreateV () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 MinLMSetCond (), MinLMSetStpMax () 및 Solver 매개 변수를 조정합니다.
   다른 기능들
3. 알고리즘 상태를 취하는 MinLMOptimize () 함수를 호출하고
   콜백 함수.
4. 사용자가 솔루션을 얻기 위해 MinLMResults ()를 호출합니다.
5. 선택적으로 MinLMRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 N / M이지만 다른 시작점 및 / 또는 다른 기능을 사용합니다.
   MinLMRestartFrom ()은 이미 초기화 된 구조를 다시 사용할 수있게합니다.
입력 매개 변수 :
    N - 차원, N> 1
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    M - 함수의 수 f [i]
    X - 초기 해, array [0..N-1]
    DiffStep- 차별화 단계,> 0
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
MinLMIteration, MinLMResults를 참고하십시오.
노트:
1. MinLMSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   MinLMSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 30.03.2009
**************************************************************************/
void minlmcreatev(const ae_int_t n, const ae_int_t m, const real_1d_array &x, const double diffstep, minlmstate &state);
void minlmcreatev(const ae_int_t m, const real_1d_array &x, const double diffstep, minlmstate &state);


/*************************************************************************
    LEVENBERG-MARQUARDT-LIKE METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This  function  is  used  to  find  minimum  of general form (not "sum-of-
-squares") function
    F = F(x[0], ..., x[n-1])
using  its  gradient  and  Hessian.  Levenberg-Marquardt modification with
L-BFGS pre-optimization and internal pre-conditioned  L-BFGS  optimization
after each Levenberg-Marquardt step is used.


REQUIREMENTS:
This algorithm will request following information during its operation:

* function value F at given point X
* F and gradient G (simultaneously) at given point X
* F, G and Hessian H (simultaneously) at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts func(),  grad()  and  hess()
function pointers. First pointer is used to calculate F  at  given  point,
second  one  calculates  F(x)  and  grad F(x),  third one calculates F(x),
grad F(x), hess F(x).

You can try to initialize MinLMState structure with FGH-function and  then
use incorrect version of MinLMOptimize() (for example, version which  does
not provide Hessian matrix), but it will lead to  exception  being  thrown
after first attempt to calculate Hessian.


USAGE:
1. User initializes algorithm state with MinLMCreateFGH() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   pointers (delegates, etc.) to callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
    비선형 최적화를위한 LEVENBERG-MARQUARDT-LIKE 방법
기술:
이 함수는 일반적인 형식의 최소값을 찾는 데 사용됩니다 ( "sum-of-
- 스퀘어 ") 함수
    F = F (x [0], ..., x [n-1])
그라디언트와 헤 시안을 사용합니다. Levenberg-Marquardt 수정
L-BFGS 사전 최적화 및 내부 사전 조건화 된 L-BFGS 최적화
각 Levenberg-Marquardt 단계가 사용 된 후에
요구 사항 :
이 알고리즘은 작동 중 다음 정보를 요청합니다.
* 주어진 점 X에서 함수 값 F
주어진 점 X에서 * F와 그래디언트 G (동시에)
* 주어진 점 X에서 F, G 및 Hessian H (동시에)
MinLMOptimize () 함수의 오버로드 된 버전은 여러 가지가 있습니다.
이것에 의해 제공된 다른 LM- 유사 최적화 알고리즘에 대응한다.
단위. func (), grad () 및 hess ()를 사용할 수있는 버전을 선택해야합니다.
함수 포인터. 첫 번째 포인터는 주어진 포인트에서 F를 계산하는 데 사용되며,
두 번째 것은 F (x)와 grad F (x)를 계산하고 세 번째 것은 F (x)를 계산하고
grad F (x), hess F (x).
FGH 함수를 사용하여 MinLMState 구조를 초기화하고
잘못된 버전의 MinLMOptimize ()를 사용하십시오 (예를 들어,
Hessian 행렬을 제공하지 않음), 예외가 발생합니다
헤 시안을 계산하려고 시도한 후
용법:
1. 사용자가 MinLMCreateFGH () 호출로 알고리즘 상태를 초기화합니다.
2. 사용자가 MinLMSetCond (), MinLMSetStpMax () 및 Solver 매개 변수를 조정합니다.
   다른 기능들
3. 알고리즘 상태를 취하는 MinLMOptimize () 함수를 호출하고
   포인터 (델리게이트 등)를 콜백 함수에 추가합니다.
4. 사용자가 솔루션을 얻기 위해 MinLMResults ()를 호출합니다.
5. 선택적으로 MinLMRestartFrom ()을 호출하여 다른 문제를 해결할 수 있습니다.
   동일한 N이지만 다른 시작점 및 / 또는 다른 기능을 사용합니다.
   MinLMRestartFrom ()은 이미 초기화 된 구조를 다시 사용할 수있게합니다.
입력 매개 변수 :
    N - 차원, N> 1
                * 주어진 경우 X의 선행 N 요소 만 사용됩니다.
                * 지정하지 않으면 X의 크기에서 자동으로 결정됩니다.
    X - 초기 해, array [0..N-1]
출력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
노트:
1. MinLMSetCond () 함수로 정지 조건을 조정할 수 있습니다.
2. 대상 함수가 exp () 또는 다른 빠르게 증가하는 함수를 포함하고
   최적화 알고리즘은 오버 플로우를 초래하는 너무 큰 단계를 만들고,
   MinLMSetStpMax () 함수를 사용하여 알고리즘의 단계를 바인딩합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 30.03.2009
**************************************************************************/
void minlmcreatefgh(const ae_int_t n, const real_1d_array &x, minlmstate &state);
void minlmcreatefgh(const real_1d_array &x, minlmstate &state);


/*************************************************************************
This function sets stopping conditions for Levenberg-Marquardt optimization
algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                |v|<EpsG is satisfied, where:
                * |.| means Euclidian norm
                * v - scaled gradient vector, v[i]=g[i]*s[i]
                * g - gradient
                * s - scaling coefficients set by MinLMSetScale()
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |v|<=EpsX is fulfilled, where:
                * |.| means Euclidian norm
                * v - scaled step vector, v[i]=dx[i]/s[i]
                * dx - ste pvector, dx=X(k+1)-X(k)
                * s - scaling coefficients set by MinLMSetScale()
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations   is    unlimited.   Only   Levenberg-Marquardt
                iterations  are  counted  (L-BFGS/CG  iterations  are  NOT
                counted because their cost is very low compared to that of
                LM).

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 Levenberg-Marquardt 최적화를위한 정지 조건을 설정합니다.
연산.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    EpsG -> = 0
                서브 루틴은 조건
                | v | <EpsG가 만족되면,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 그래디언트 벡터, v [i] = g [i] * s [i]
                * g - 그래디언트
                * s - MinLMSetScale ()에 의해 설정된 스케일링 계수
    EpsF -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                조건 | F (k + 1) -F (k) | <= EpsF * max {| F (k) |, | F (k + 1) |, 1}
                만족한다.
    EpsX -> = 0
                서브 루틴은 k + 1 번째 반복에서 작업을 마칩니다.
                | v | <= EpsX 조건이 충족됩니다. 여기서,
                * |. | 유클리드 규범을 의미한다.
                * v - 스케일 된 스텝 벡터, v [i] = dx [i] / s [i]
                * dx - ste pvector, dx = X (k + 1) -X (k)
                * s - MinLMSetScale ()에 의해 설정된 스케일링 계수
    MaxIts - 최대 반복 횟수입니다. MaxIts = 0이면,
                반복은 무제한입니다. Levenberg-Marquardt 만
                반복 횟수가 계산됩니다 (L-BFGS / CG 반복은 불가능 함).
                그들의 비용이 그것의 비용에 비해 매우 낮기 때문에 계산됩니다.
                LM).
EpsG = 0, EpsF = 0, EpsX = 0 및 MaxIts = 0 (동시에)을 전달하면
자동 정지 기준 선택 (작은 EpsX).
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minlmsetcond(const minlmstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinLMOptimize(). Both Levenberg-Marquardt and internal  L-BFGS
iterations are reported.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은보고 기능을 켜거나 끕니다.
입력 매개 변수 :
    State - 알고리즘 상태를 저장하는 구조
    NeedXRep - 반복 보고서가 필요한지 아닌지
NeedXRep이 True이면 알고리즘은 rep () 콜백 함수를 호출합니다
MinLMOptimize ()에 제공됩니다. Levenberg-Marquardt와 내부 L-BFGS
반복이보고됩니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
*************************************************** ***********************/
void minlmsetxrep(const minlmstate &state, const bool needxrep);


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
/**************************************************************************
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
**************************************************************************/
void minlmsetstpmax(const minlmstate &state, const double stpmax);


/*************************************************************************
This function sets scaling coefficients for LM optimizer.

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
/**************************************************************************
이 함수는 LM 최적화 프로그램의 스케일링 계수를 설정합니다.
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
**************************************************************************/
void minlmsetscale(const minlmstate &state, const real_1d_array &s);


/*************************************************************************
This function sets boundary constraints for LM optimizer

Boundary constraints are inactive by default (after initial creation).
They are preserved until explicitly turned off with another SetBC() call.

INPUT PARAMETERS:
    State   -   structure stores algorithm state
    BndL    -   lower bounds, array[N].
                If some (all) variables are unbounded, you may specify
                very small number or -INF (latter is recommended because
                it will allow solver to use better algorithm).
    BndU    -   upper bounds, array[N].
                If some (all) variables are unbounded, you may specify
                very large number or +INF (latter is recommended because
                it will allow solver to use better algorithm).

NOTE 1: it is possible to specify BndL[i]=BndU[i]. In this case I-th
variable will be "frozen" at X[i]=BndL[i]=BndU[i].

NOTE 2: this solver has following useful properties:
* bound constraints are always satisfied exactly
* function is evaluated only INSIDE area specified by bound constraints
  or at its boundary

  -- ALGLIB --
     Copyright 14.01.2011 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 LM 최적화 프로그램의 경계 제약 조건을 설정합니다.
경계 제약 조건은 기본적으로 비활성화됩니다 (초기 생성 후).
다른 SetBC () 호출로 명시 적으로 해제 될 때까지 보존됩니다.
입력 매개 변수 :
    상태 - 구조 알고리즘 상태 저장
    BndL - 하한, 배열 [N].
                일부 (모든) 변수에 제한이없는 경우,
                매우 작은 수 또는 -INF (후자가 권장됩니다.
                그것은 솔버가 더 나은 알고리즘을 사용할 수있게 해줍니다).
    BndU - 상한, 배열 [N].
                일부 (모든) 변수에 제한이없는 경우,
                매우 큰 숫자 또는 + INF (후자가 권장됩니다.
                그것은 솔버가 더 나은 알고리즘을 사용할 수있게 해줍니다).
비고 1 : BndL [i] = BndU [i]를 지정할 수있다. 이 경우 I-th
변수는 X [i] = BndL [i] = BndU [i]에서 "고정"됩니다.
NOTE 2 :이 솔버는 다음과 같은 유용한 속성을 가지고있다.
* 경계 제약은 항상 정확하게 만족된다.
* 함수는 바인딩 된 제약 조건에 의해 지정된 INSIDE 영역에서만 평가됩니다.
  또는 경계에서
  - ALGLIB -
     저작권 14.01.2011 Bochkanov Sergey
**************************************************************************/
void minlmsetbc(const minlmstate &state, const real_1d_array &bndl, const real_1d_array &bndu);


/*************************************************************************
This function is used to change acceleration settings

You can choose between three acceleration strategies:
* AccType=0, no acceleration.
* AccType=1, secant updates are used to update quadratic model after  each
  iteration. After fixed number of iterations (or after  model  breakdown)
  we  recalculate  quadratic  model  using  analytic  Jacobian  or  finite
  differences. Number of secant-based iterations depends  on  optimization
  settings: about 3 iterations - when we have analytic Jacobian, up to 2*N
  iterations - when we use finite differences to calculate Jacobian.

AccType=1 is recommended when Jacobian  calculation  cost  is  prohibitive
high (several Mx1 function vector calculations  followed  by  several  NxN
Cholesky factorizations are faster than calculation of one M*N  Jacobian).
It should also be used when we have no Jacobian, because finite difference
approximation takes too much time to compute.

Table below list  optimization  protocols  (XYZ  protocol  corresponds  to
MinLMCreateXYZ) and acceleration types they support (and use by  default).

ACCELERATION TYPES SUPPORTED BY OPTIMIZATION PROTOCOLS:

protocol    0   1   comment
V           +   +
VJ          +   +
FGH         +

DAFAULT VALUES:

protocol    0   1   comment
V               x   without acceleration it is so slooooooooow
VJ          x
FGH         x

NOTE: this  function should be called before optimization. Attempt to call
it during algorithm iterations may result in unexpected behavior.

NOTE: attempt to call this function with unsupported protocol/acceleration
combination will result in exception being thrown.

  -- ALGLIB --
     Copyright 14.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 기능은 가속 설정을 변경하는 데 사용됩니다
세 가지 가속 전략 중에서 선택할 수 있습니다.
* AccType = 0, 가속 없음.
* AccType = 1, 시컨트 업데이트는 각 후 2 차 모델을 업데이트하는 데 사용됩니다.
  되풀이. 고정 된 수의 반복 (또는 모델 고장 후)
  분석적 자 코비안 또는 유한 값을 사용하여 2 차 모델을 다시 계산합니다.
  차이. 세컨트 기반 반복의 수는 최적화에 달려 있습니다.
  설정 : 약 3 회 반복 - 분석 자 코비안이있는 경우 최대 2 * N
  반복 - 유한 차분을 사용하여 자 코비안을 계산할 때.
야 코비 계산 비용이 많이들 때 AccType = 1을 권장합니다.
높음 (여러 Mx1 함수 벡터 계산 다음에 여러 NxN
콜레 스키 인수 분해는 하나의 M * N Jacobian 계산보다 빠릅니다.
또한 야 코비 행렬이 없을 때 사용되어야합니다. 왜냐하면 유한 차이
근사는 계산하는 데 너무 많은 시간이 걸립니다.
아래 표는 목록 최적화 프로토콜입니다 (XYZ 프로토콜은
MinLMCreateXYZ) 및 지원하는 가속 유형 (기본적으로 사용)을 제공합니다.
최적화 프로토콜에 의해 지원되는 가속 유형 :
프로토콜 0 1 개의 덧글
V + +
VJ + +
FGH +
일회성 가치 :
프로토콜 0 1 개의 덧글
V x는 가속이 없으므로 slooooooooow입니다.
VJ x
FGH x
참고 :이 함수는 최적화 전에 호출되어야합니다. 전화 시도
알고리즘 반복 중에 예기치 않은 동작이 발생할 수 있습니다.
참고 : 지원되지 않는 프로토콜 / 가속 기능으로이 함수를 호출 해 봅니다.
조합을하면 예외가 발생합니다.
  - ALGLIB -
     저작권 14.10.2010 Bochkanov Sergey
**************************************************************************/
void minlmsetacctype(const minlmstate &state, const ae_int_t acctype);


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
bool minlmiteration(const minlmstate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear optimizer

These functions accept following parameters:
    state   -   algorithm state
    func    -   callback which calculates function (or merit function)
                value func at given point x
    grad    -   callback which calculates function (or merit function)
                value func and gradient grad at given point x
    hess    -   callback which calculates function (or merit function)
                value func, gradient grad and Hessian hess at given point x
    fvec    -   callback which calculates function vector fi[]
                at given point x
    jac     -   callback which calculates function vector fi[]
                and Jacobian jac at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL

NOTES:

1. Depending on function used to create state  structure,  this  algorithm
   may accept Jacobian and/or Hessian and/or gradient.  According  to  the
   said above, there ase several versions of this function,  which  accept
   different sets of callbacks.

   This flexibility opens way to subtle errors - you may create state with
   MinLMCreateFGH() (optimization using Hessian), but call function  which
   does not accept Hessian. So when algorithm will request Hessian,  there
   will be no callback to call. In this case exception will be thrown.

   Be careful to avoid such errors because there is no way to find them at
   compile time - you can see them at runtime only.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey

*************************************************************************/
/**************************************************************************
이 함수 계열은 비선형 최적화 알고리즘의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    func - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func
    grad - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func 및 gradient grad
    hess - 함수 (또는 메리트 함수)를 계산하는 콜백
                값 func, 그라디언트 grad 및 주어진 포인트 x에서의 헤센 헤스
    fvec - 함수 벡터 fi []를 계산하는 콜백
                주어진 점 x에서
    jac - 함수 벡터 fi []를 계산하는 콜백
                주어진 점 x에서 Jacobian jac
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
노트:
1. 상태 구조를 생성하는 데 사용되는 함수에 따라이 알고리즘
   Jacobian 및 / 또는 Hessian 및 / 또는 그라디언트를 허용 할 수 있습니다. 에 따르면
   위에서 말했듯이,이 함수의 여러 버전이 있습니다.
   다른 콜백 세트.
   이러한 유연성 덕분에 미묘한 오류가 발생합니다.
   MinLMCreateFGH () (Hessian을 사용하여 최적화)를 호출하지만,
   헤 시안을 받아들이지 않는다. 알고리즘이 헤 시안을 요청할 때, 거기에
   전화 할 콜백이 없습니다. 이 경우 예외가 발생합니다.
   그러한 오류를 피하는 방법은 없기 때문에 이러한 오류를 피하십시오.
   컴파일 타임 - 런타임에만 볼 수 있습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright.103.2009
**************************************************************************/
void minlmoptimize(minlmstate &state,
    void (*fvec)(const real_1d_array &x, real_1d_array &fi, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void minlmoptimize(minlmstate &state,
    void (*fvec)(const real_1d_array &x, real_1d_array &fi, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void minlmoptimize(minlmstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void (*hess)(const real_1d_array &x, double &func, real_1d_array &grad, real_2d_array &hess, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void minlmoptimize(minlmstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);
void minlmoptimize(minlmstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);


/*************************************************************************
Levenberg-Marquardt algorithm results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report;
                see comments for this structure for more info.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Levenberg-Marquardt 알고리즘 결과
입력 매개 변수 :
    상태 - 알고리즘 상태
출력 매개 변수 :
    X- 어레이 [0..N-1], 용액
    담당자 최적화 보고서;
                자세한 내용은이 구조에 대한 설명을 참조하십시오.
  - ALGLIB -
     Bochkanov Sergey의 Copyright.103.2009
**************************************************************************/
void minlmresults(const minlmstate &state, real_1d_array &x, minlmreport &rep);


/*************************************************************************
Levenberg-Marquardt algorithm results

Buffered implementation of MinLMResults(), which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
Levenberg-Marquardt 알고리즘 결과
미리 할당 된 버퍼를 사용하는 MinLMResults ()의 버퍼 된 구현
X []를 저장합니다. 버퍼 크기가 너무 작 으면 버퍼의 크기를 조정합니다. 그것은
성능에 중요한 알고리즘의 내부주기에 사용하기위한 것
배열 재 할당 패널티가 너무 커서 무시할 수 없습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright.103.2009
**************************************************************************/
void minlmresultsbuf(const minlmstate &state, real_1d_array &x, minlmreport &rep);


/*************************************************************************
This  subroutine  restarts  LM  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used for reverse communication previously
                allocated with MinLMCreateXXX call.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 새로운 지점에서 LM 알고리즘을 재시작합니다. 모든 최적화
매개 변수는 변경되지 않습니다.
이 함수는 여러 개의 최적화 문제를 해결할 수 있습니다.
오브젝트 재 할당 패널티가없는 동일한 수의 치수가 있어야합니다.
입력 매개 변수 :
    상태 - 이전에 역방향 통신에 사용 된 구조
                MinLMCreateXXX 호출로 할당됩니다.
    X - 새로운 출발점.
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
**************************************************************************/
void minlmrestartfrom(const minlmstate &state, const real_1d_array &x);


/*************************************************************************
This is obsolete function.

Since ALGLIB 3.3 it is equivalent to MinLMCreateVJ().

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이것은 쓸모없는 기능입니다.
ALGLIB 3.3부터 MinLMCreateVJ ()와 같습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 30.03.2009
**************************************************************************/
void minlmcreatevgj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state);
void minlmcreatevgj(const ae_int_t m, const real_1d_array &x, minlmstate &state);


/*************************************************************************
This is obsolete function.

Since ALGLIB 3.3 it is equivalent to MinLMCreateFJ().

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이것은 쓸모없는 기능입니다.
ALGLIB 3.3부터 MinLMCreateFJ ()와 같습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 30.03.2009
**************************************************************************/
void minlmcreatefgj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state);
void minlmcreatefgj(const ae_int_t m, const real_1d_array &x, minlmstate &state);


/*************************************************************************
This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend  to use MinLMCreateVJ, which
provides similar, but more consistent and feature-rich interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 함수는 ALGLIB 3.1.0부터 존재하지 않는 것으로 간주됩니다.
하위 호환성. MinLMCreateVJ를 사용하는 것이 좋습니다.
비슷하지만보다 일관되고 풍부한 기능의 인터페이스를 제공합니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 30.03.2009
**************************************************************************/
void minlmcreatefj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state);
void minlmcreatefj(const ae_int_t m, const real_1d_array &x, minlmstate &state);


/*************************************************************************
This  subroutine  turns  on  verification  of  the  user-supplied analytic
gradient:
* user calls this subroutine before optimization begins
* MinLMOptimize() is called
* prior to actual optimization, for  each  function Fi and each  component
  of parameters  being  optimized X[j] algorithm performs following steps:
  * two trial steps are made to X[j]-TestStep*S[j] and X[j]+TestStep*S[j],
    where X[j] is j-th parameter and S[j] is a scale of j-th parameter
  * if needed, steps are bounded with respect to constraints on X[]
  * Fi(X) is evaluated at these trial points
  * we perform one more evaluation in the middle point of the interval
  * we  build  cubic  model using function values and derivatives at trial
    points and we compare its prediction with actual value in  the  middle
    point
  * in case difference between prediction and actual value is higher  than
    some predetermined threshold, algorithm stops with completion code -7;
    Rep.VarIdx is set to index of the parameter with incorrect derivative,
    Rep.FuncIdx is set to index of the function.
* after verification is over, algorithm proceeds to the actual optimization.

NOTE 1: verification  needs  N (parameters count) Jacobian evaluations. It
        is  very  costly  and  you  should use it only for low dimensional
        problems,  when  you  want  to  be  sure  that  you've   correctly
        calculated  analytic  derivatives.  You should not  use  it in the
        production code  (unless  you  want  to check derivatives provided
        by some third party).

NOTE 2: you  should  carefully  choose  TestStep. Value which is too large
        (so large that function behaviour is significantly non-cubic) will
        lead to false alarms. You may use  different  step  for  different
        parameters by means of setting scale with MinLMSetScale().

NOTE 3: this function may lead to false positives. In case it reports that
        I-th  derivative was calculated incorrectly, you may decrease test
        step  and  try  one  more  time  - maybe your function changes too
        sharply  and  your  step  is  too  large for such rapidly chanding
        function.

INPUT PARAMETERS:
    State       -   structure used to store algorithm state
    TestStep    -   verification step:
                    * TestStep=0 turns verification off
                    * TestStep>0 activates verification

  -- ALGLIB --
     Copyright 15.06.2012 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이 서브 루틴은 사용자가 제공 한 분석의 검증을 켭니다.
구배:
* 최적화가 시작되기 전에 사용자가이 서브 루틴 호출
* MinLMOptimize ()가 호출됩니다.
* 실제 최적화에 앞서 각 기능 Fi 및 각 구성 요소에 대해
  최적화 된 매개 변수 X [j] 알고리즘은 다음 단계를 수행합니다.
  * X [j] -TestStep * S [j] 및 X [j] + TestStep * S [j]에 대해 두 가지 시험 단계가 수행됩니다.
    여기서 X [j]는 j 번째 매개 변수이고 S [j]는 j 번째 매개 변수의 눈금입니다
  * 필요한 경우 단계는 X []에 대한 제약 조건에 따라 제한됩니다.
  * Fi (X)는 평가판에서 평가됩니다.
  * 간격의 중간 지점에서 또 하나의 평가를 수행합니다.
  * 우리는 함수 값과 파생 상품을 사용하여 삼차원 모델을 시험해 보았다.
    우리는 예측치를 중간의 실제 값과 비교합니다
    포인트
  * 예상 값과 실제 값의 차이가
    소정의 소정의 임계 값, 알고리즘은 완료 코드 -7로 정지한다;
    Rep.VarIdx가 잘못된 파생어로 매개 변수의 인덱스로 설정됩니다.
    Rep.FuncIdx는 함수의 인덱스로 설정됩니다.
* 검증이 끝나면 알고리즘은 실제 최적화로 진행합니다.
비고 1 : 검증을 위해서는 N (매개 변수 개수) 자 코비안 평가가 필요하다. 그것
        매우 비용이 많이 들며 낮은 차원에서만 사용해야합니다.
        문제, 당신이 당신이 올바르게했는지 알고 싶을 때
        계산 된 파생 상품. 당신은
        생산 코드 (제공된 파생 상품을 확인하고 싶지 않은 경우)
        제 3 자에 의해).
참고 2 : TestStep을 신중하게 선택해야합니다. 너무 큰 값
        (너무 커서 함수의 동작은 상당히 비 큐빅이다.)
        거짓 경보로 연결됩니다. 다른 단계를 사용할 수도 있습니다.
        MinLMSetScale ()을 사용하여 축척을 설정하여 매개 변수를 설정합니다.
참고 3 :이 기능은 위양성을 유발할 수 있습니다. 보고서에
        I 차수 미분이 잘못 계산되었으므로 테스트를 줄일 수 있습니다.
        한 번 더 시도해보십시오. 아마도 기능이 변경 될 수도 있습니다.
        급격하게 그리고 당신의 발걸음이 그렇게 급속히 챈드하기에는 너무 큽니다.
        기능.
입력 매개 변수 :
    상태 - 알고리즘 상태를 저장하는 데 사용되는 구조
    TestStep - 확인 단계 :
                    * TestStep = 0으로 설정하면 인증이 해제됩니다.
                    * TestStep> 0으로 인증이 활성화됩니다.
  - ALGLIB -
     저작권 15.06.2012 Bochkanov Sergey
**************************************************************************/
void minlmsetgradientcheck(const minlmstate &state, const double teststep);

/*************************************************************************
Obsolete function, use MinLBFGSSetPrecDefault() instead.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
더 이상 사용되지 않는 함수 대신 MinLBFGSSetPrecDefault ()를 사용하십시오.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetdefaultpreconditioner(const minlbfgsstate &state);


/*************************************************************************
Obsolete function, use MinLBFGSSetCholeskyPreconditioner() instead.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
사용되지 않는 함수 대신 MinLBFGSSetCholeskyPreconditioner ()를 사용하십시오.
  - ALGLIB -
     Copyright 13.10.2010 Bochkanov Sergey
**************************************************************************/
void minlbfgssetcholeskypreconditioner(const minlbfgsstate &state, const real_2d_array &p, const bool isupper);


/*************************************************************************
This is obsolete function which was used by previous version of the  BLEIC
optimizer. It does nothing in the current version of BLEIC.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이것은 이전 버전의 BLEIC에서 사용 된 구식 기능입니다.
최적화 도구. 그것은 현재 버전의 BLEIC에서는 아무것도하지 않습니다.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetbarrierwidth(const minbleicstate &state, const double mu);


/*************************************************************************
This is obsolete function which was used by previous version of the  BLEIC
optimizer. It does nothing in the current version of BLEIC.

  -- ALGLIB --
     Copyright 28.11.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
이것은 이전 버전의 BLEIC에서 사용 된 구식 기능입니다.
최적화 도구. 그것은 현재 버전의 BLEIC에서는 아무것도하지 않습니다.
  - ALGLIB -
     Copyright 28.11.2010 Bochkanov Sergey
**************************************************************************/
void minbleicsetbarrierdecay(const minbleicstate &state, const double mudecay);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     Copyright 25.03.2010 Bochkanov Sergey
**************************************************************************/
void minasacreate(const ae_int_t n, const real_1d_array &x, const real_1d_array &bndl, const real_1d_array &bndu, minasastate &state);
void minasacreate(const real_1d_array &x, const real_1d_array &bndl, const real_1d_array &bndu, minasastate &state);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minasasetcond(const minasastate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minasasetxrep(const minasastate &state, const bool needxrep);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minasasetalgorithm(const minasastate &state, const ae_int_t algotype);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     저작권 02.04.2010 Bochkanov Sergey
**************************************************************************/
void minasasetstpmax(const minasastate &state, const double stpmax);


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
bool minasaiteration(const minasastate &state);


/*************************************************************************
This family of functions is used to launcn iterations of nonlinear optimizer

These functions accept following parameters:
    state   -   algorithm state
    grad    -   callback which calculates function (or merit function)
                value func and gradient grad at given point x
    rep     -   optional callback which is called after each iteration
                can be NULL
    ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
                can be NULL


  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey

*************************************************************************/
/**************************************************************************
이 함수 계열은 비선형 최적화 알고리즘의 반복을 시작하는 데 사용됩니다.
이 함수는 다음 매개 변수를 허용합니다.
    상태 - 알고리즘 상태
    grad - 함수 (또는 메리트 함수)를 계산하는 콜백
                주어진 점 x에서 값 func 및 gradient grad
    rep - 각 반복 후에 호출되는 선택적 콜백
                NULL 일 수있다.
    ptr - func / grad / hess / jac / rep에 전달되는 선택적 포인터.
                NULL 일 수있다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.03.2009
**************************************************************************/
void minasaoptimize(minasastate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr) = NULL,
    void *ptr = NULL);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.03.2009
**************************************************************************/
void minasaresults(const minasastate &state, real_1d_array &x, minasareport &rep);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     Bochkanov Sergey의 Copyright 20.03.2009
**************************************************************************/
void minasaresultsbuf(const minasastate &state, real_1d_array &x, minasareport &rep);


/*************************************************************************
Obsolete optimization algorithm.
Was replaced by MinBLEIC subpackage.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
/**************************************************************************
쓸모없는 최적화 알고리즘.
MinBLEIC 하위 패키지로 대체되었습니다.
  - ALGLIB -
     저작권 30.07.2010 Bochkanov Sergey
**************************************************************************/
void minasarestartfrom(const minasastate &state, const real_1d_array &x, const real_1d_array &bndl, const real_1d_array &bndu);
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
void trimprepare(double f, double* threshold, ae_state *_state);
void trimfunction(double* f,
     /* Real    */ ae_vector* g,
     ae_int_t n,
     double threshold,
     ae_state *_state);
ae_bool enforceboundaryconstraints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bl,
     /* Boolean */ ae_vector* havebl,
     /* Real    */ ae_vector* bu,
     /* Boolean */ ae_vector* havebu,
     ae_int_t nmain,
     ae_int_t nslack,
     ae_state *_state);
void projectgradientintobc(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* g,
     /* Real    */ ae_vector* bl,
     /* Boolean */ ae_vector* havebl,
     /* Real    */ ae_vector* bu,
     /* Boolean */ ae_vector* havebu,
     ae_int_t nmain,
     ae_int_t nslack,
     ae_state *_state);
void calculatestepbound(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* d,
     double alpha,
     /* Real    */ ae_vector* bndl,
     /* Boolean */ ae_vector* havebndl,
     /* Real    */ ae_vector* bndu,
     /* Boolean */ ae_vector* havebndu,
     ae_int_t nmain,
     ae_int_t nslack,
     ae_int_t* variabletofreeze,
     double* valuetofreeze,
     double* maxsteplen,
     ae_state *_state);
ae_int_t postprocessboundedstep(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* xprev,
     /* Real    */ ae_vector* bndl,
     /* Boolean */ ae_vector* havebndl,
     /* Real    */ ae_vector* bndu,
     /* Boolean */ ae_vector* havebndu,
     ae_int_t nmain,
     ae_int_t nslack,
     ae_int_t variabletofreeze,
     double valuetofreeze,
     double steptaken,
     double maxsteplen,
     ae_state *_state);
void filterdirection(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bndl,
     /* Boolean */ ae_vector* havebndl,
     /* Real    */ ae_vector* bndu,
     /* Boolean */ ae_vector* havebndu,
     /* Real    */ ae_vector* s,
     ae_int_t nmain,
     ae_int_t nslack,
     double droptol,
     ae_state *_state);
ae_int_t numberofchangedconstraints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* xprev,
     /* Real    */ ae_vector* bndl,
     /* Boolean */ ae_vector* havebndl,
     /* Real    */ ae_vector* bndu,
     /* Boolean */ ae_vector* havebndu,
     ae_int_t nmain,
     ae_int_t nslack,
     ae_state *_state);
ae_bool findfeasiblepoint(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bndl,
     /* Boolean */ ae_vector* havebndl,
     /* Real    */ ae_vector* bndu,
     /* Boolean */ ae_vector* havebndu,
     ae_int_t nmain,
     ae_int_t nslack,
     /* Real    */ ae_matrix* ce,
     ae_int_t k,
     double epsi,
     ae_int_t* qpits,
     ae_int_t* gpaits,
     ae_state *_state);
ae_bool derivativecheck(double f0,
     double df0,
     double f1,
     double df1,
     double f,
     double df,
     double width,
     ae_state *_state);
void cqminit(ae_int_t n, convexquadraticmodel* s, ae_state *_state);
void cqmseta(convexquadraticmodel* s,
     /* Real    */ ae_matrix* a,
     ae_bool isupper,
     double alpha,
     ae_state *_state);
void cqmrewritedensediagonal(convexquadraticmodel* s,
     /* Real    */ ae_vector* z,
     ae_state *_state);
void cqmsetd(convexquadraticmodel* s,
     /* Real    */ ae_vector* d,
     double tau,
     ae_state *_state);
void cqmdropa(convexquadraticmodel* s, ae_state *_state);
void cqmsetb(convexquadraticmodel* s,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void cqmsetq(convexquadraticmodel* s,
     /* Real    */ ae_matrix* q,
     /* Real    */ ae_vector* r,
     ae_int_t k,
     double theta,
     ae_state *_state);
void cqmsetactiveset(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     /* Boolean */ ae_vector* activeset,
     ae_state *_state);
double cqmeval(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void cqmevalx(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     double* r,
     double* noise,
     ae_state *_state);
void cqmgradunconstrained(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* g,
     ae_state *_state);
double cqmxtadx2(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void cqmadx(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
ae_bool cqmconstrainedoptimum(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void cqmscalevector(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
double cqmdebugconstrainedevalt(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
double cqmdebugconstrainedevale(convexquadraticmodel* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
ae_bool _convexquadraticmodel_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _convexquadraticmodel_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _convexquadraticmodel_clear(void* _p);
void _convexquadraticmodel_destroy(void* _p);
void snnlsinit(ae_int_t nsmax,
     ae_int_t ndmax,
     ae_int_t nrmax,
     snnlssolver* s,
     ae_state *_state);
void snnlssetproblem(snnlssolver* s,
     /* Real    */ ae_matrix* a,
     /* Real    */ ae_vector* b,
     ae_int_t ns,
     ae_int_t nd,
     ae_int_t nr,
     ae_state *_state);
void snnlsdropnnc(snnlssolver* s, ae_int_t idx, ae_state *_state);
void snnlssolve(snnlssolver* s,
     /* Real    */ ae_vector* x,
     ae_state *_state);
ae_bool _snnlssolver_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _snnlssolver_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _snnlssolver_clear(void* _p);
void _snnlssolver_destroy(void* _p);
void sasinit(ae_int_t n, sactiveset* s, ae_state *_state);
void sassetscale(sactiveset* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void sassetprecdiag(sactiveset* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void sassetbc(sactiveset* state,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state);
void sassetlc(sactiveset* state,
     /* Real    */ ae_matrix* c,
     /* Integer */ ae_vector* ct,
     ae_int_t k,
     ae_state *_state);
void sassetlcx(sactiveset* state,
     /* Real    */ ae_matrix* cleic,
     ae_int_t nec,
     ae_int_t nic,
     ae_state *_state);
ae_bool sasstartoptimization(sactiveset* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void sasexploredirection(sactiveset* state,
     /* Real    */ ae_vector* d,
     double* stpmax,
     ae_int_t* cidx,
     double* vval,
     ae_state *_state);
ae_int_t sasmoveto(sactiveset* state,
     /* Real    */ ae_vector* xn,
     ae_bool needact,
     ae_int_t cidx,
     double cval,
     ae_state *_state);
void sasimmediateactivation(sactiveset* state,
     ae_int_t cidx,
     double cval,
     ae_state *_state);
void sasconstraineddescent(sactiveset* state,
     /* Real    */ ae_vector* g,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void sasconstraineddescentprec(sactiveset* state,
     /* Real    */ ae_vector* g,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void sasconstraineddirection(sactiveset* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void sasconstraineddirectionprec(sactiveset* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void sascorrection(sactiveset* state,
     /* Real    */ ae_vector* x,
     double* penalty,
     ae_state *_state);
double sasactivelcpenalty1(sactiveset* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
double sasscaledconstrainednorm(sactiveset* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void sasstopoptimization(sactiveset* state, ae_state *_state);
void sasreactivateconstraints(sactiveset* state,
     /* Real    */ ae_vector* gc,
     ae_state *_state);
void sasreactivateconstraintsprec(sactiveset* state,
     /* Real    */ ae_vector* gc,
     ae_state *_state);
void sasrebuildbasis(sactiveset* state, ae_state *_state);
ae_bool _sactiveset_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _sactiveset_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _sactiveset_clear(void* _p);
void _sactiveset_destroy(void* _p);
void mincgcreate(ae_int_t n,
     /* Real    */ ae_vector* x,
     mincgstate* state,
     ae_state *_state);
void mincgcreatef(ae_int_t n,
     /* Real    */ ae_vector* x,
     double diffstep,
     mincgstate* state,
     ae_state *_state);
void mincgsetcond(mincgstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void mincgsetscale(mincgstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void mincgsetxrep(mincgstate* state, ae_bool needxrep, ae_state *_state);
void mincgsetdrep(mincgstate* state, ae_bool needdrep, ae_state *_state);
void mincgsetcgtype(mincgstate* state, ae_int_t cgtype, ae_state *_state);
void mincgsetstpmax(mincgstate* state, double stpmax, ae_state *_state);
void mincgsuggeststep(mincgstate* state, double stp, ae_state *_state);
void mincgsetprecdefault(mincgstate* state, ae_state *_state);
void mincgsetprecdiag(mincgstate* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void mincgsetprecscale(mincgstate* state, ae_state *_state);
ae_bool mincgiteration(mincgstate* state, ae_state *_state);
void mincgresults(mincgstate* state,
     /* Real    */ ae_vector* x,
     mincgreport* rep,
     ae_state *_state);
void mincgresultsbuf(mincgstate* state,
     /* Real    */ ae_vector* x,
     mincgreport* rep,
     ae_state *_state);
void mincgrestartfrom(mincgstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void mincgsetprecdiagfast(mincgstate* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void mincgsetpreclowrankfast(mincgstate* state,
     /* Real    */ ae_vector* d1,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_matrix* v,
     ae_int_t vcnt,
     ae_state *_state);
void mincgsetprecvarpart(mincgstate* state,
     /* Real    */ ae_vector* d2,
     ae_state *_state);
void mincgsetgradientcheck(mincgstate* state,
     double teststep,
     ae_state *_state);
ae_bool _mincgstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _mincgstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _mincgstate_clear(void* _p);
void _mincgstate_destroy(void* _p);
ae_bool _mincgreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _mincgreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _mincgreport_clear(void* _p);
void _mincgreport_destroy(void* _p);
void minbleiccreate(ae_int_t n,
     /* Real    */ ae_vector* x,
     minbleicstate* state,
     ae_state *_state);
void minbleiccreatef(ae_int_t n,
     /* Real    */ ae_vector* x,
     double diffstep,
     minbleicstate* state,
     ae_state *_state);
void minbleicsetbc(minbleicstate* state,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state);
void minbleicsetlc(minbleicstate* state,
     /* Real    */ ae_matrix* c,
     /* Integer */ ae_vector* ct,
     ae_int_t k,
     ae_state *_state);
void minbleicsetcond(minbleicstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void minbleicsetscale(minbleicstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void minbleicsetprecdefault(minbleicstate* state, ae_state *_state);
void minbleicsetprecdiag(minbleicstate* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void minbleicsetprecscale(minbleicstate* state, ae_state *_state);
void minbleicsetxrep(minbleicstate* state,
     ae_bool needxrep,
     ae_state *_state);
void minbleicsetdrep(minbleicstate* state,
     ae_bool needdrep,
     ae_state *_state);
void minbleicsetstpmax(minbleicstate* state,
     double stpmax,
     ae_state *_state);
ae_bool minbleiciteration(minbleicstate* state, ae_state *_state);
void minbleicresults(minbleicstate* state,
     /* Real    */ ae_vector* x,
     minbleicreport* rep,
     ae_state *_state);
void minbleicresultsbuf(minbleicstate* state,
     /* Real    */ ae_vector* x,
     minbleicreport* rep,
     ae_state *_state);
void minbleicrestartfrom(minbleicstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void minbleicemergencytermination(minbleicstate* state, ae_state *_state);
void minbleicsetgradientcheck(minbleicstate* state,
     double teststep,
     ae_state *_state);
ae_bool _minbleicstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minbleicstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minbleicstate_clear(void* _p);
void _minbleicstate_destroy(void* _p);
ae_bool _minbleicreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minbleicreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minbleicreport_clear(void* _p);
void _minbleicreport_destroy(void* _p);
void minlbfgscreate(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlbfgsstate* state,
     ae_state *_state);
void minlbfgscreatef(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     double diffstep,
     minlbfgsstate* state,
     ae_state *_state);
void minlbfgssetcond(minlbfgsstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void minlbfgssetxrep(minlbfgsstate* state,
     ae_bool needxrep,
     ae_state *_state);
void minlbfgssetstpmax(minlbfgsstate* state,
     double stpmax,
     ae_state *_state);
void minlbfgssetscale(minlbfgsstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void minlbfgscreatex(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     ae_int_t flags,
     double diffstep,
     minlbfgsstate* state,
     ae_state *_state);
void minlbfgssetprecdefault(minlbfgsstate* state, ae_state *_state);
void minlbfgssetpreccholesky(minlbfgsstate* state,
     /* Real    */ ae_matrix* p,
     ae_bool isupper,
     ae_state *_state);
void minlbfgssetprecdiag(minlbfgsstate* state,
     /* Real    */ ae_vector* d,
     ae_state *_state);
void minlbfgssetprecscale(minlbfgsstate* state, ae_state *_state);
ae_bool minlbfgsiteration(minlbfgsstate* state, ae_state *_state);
void minlbfgsresults(minlbfgsstate* state,
     /* Real    */ ae_vector* x,
     minlbfgsreport* rep,
     ae_state *_state);
void minlbfgsresultsbuf(minlbfgsstate* state,
     /* Real    */ ae_vector* x,
     minlbfgsreport* rep,
     ae_state *_state);
void minlbfgsrestartfrom(minlbfgsstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void minlbfgssetgradientcheck(minlbfgsstate* state,
     double teststep,
     ae_state *_state);
ae_bool _minlbfgsstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minlbfgsstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minlbfgsstate_clear(void* _p);
void _minlbfgsstate_destroy(void* _p);
ae_bool _minlbfgsreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minlbfgsreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minlbfgsreport_clear(void* _p);
void _minlbfgsreport_destroy(void* _p);
void minqpcreate(ae_int_t n, minqpstate* state, ae_state *_state);
void minqpsetlinearterm(minqpstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void minqpsetquadraticterm(minqpstate* state,
     /* Real    */ ae_matrix* a,
     ae_bool isupper,
     ae_state *_state);
void minqpsetquadratictermsparse(minqpstate* state,
     sparsematrix* a,
     ae_bool isupper,
     ae_state *_state);
void minqpsetstartingpoint(minqpstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void minqpsetorigin(minqpstate* state,
     /* Real    */ ae_vector* xorigin,
     ae_state *_state);
void minqpsetscale(minqpstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void minqpsetalgocholesky(minqpstate* state, ae_state *_state);
void minqpsetalgobleic(minqpstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void minqpsetbc(minqpstate* state,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state);
void minqpsetlc(minqpstate* state,
     /* Real    */ ae_matrix* c,
     /* Integer */ ae_vector* ct,
     ae_int_t k,
     ae_state *_state);
void minqpoptimize(minqpstate* state, ae_state *_state);
void minqpresults(minqpstate* state,
     /* Real    */ ae_vector* x,
     minqpreport* rep,
     ae_state *_state);
void minqpresultsbuf(minqpstate* state,
     /* Real    */ ae_vector* x,
     minqpreport* rep,
     ae_state *_state);
void minqpsetlineartermfast(minqpstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void minqpsetquadratictermfast(minqpstate* state,
     /* Real    */ ae_matrix* a,
     ae_bool isupper,
     double s,
     ae_state *_state);
void minqprewritediagonal(minqpstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void minqpsetstartingpointfast(minqpstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void minqpsetoriginfast(minqpstate* state,
     /* Real    */ ae_vector* xorigin,
     ae_state *_state);
ae_bool _minqpstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minqpstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minqpstate_clear(void* _p);
void _minqpstate_destroy(void* _p);
ae_bool _minqpreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minqpreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minqpreport_clear(void* _p);
void _minqpreport_destroy(void* _p);
void minlmcreatevj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state);
void minlmcreatev(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     double diffstep,
     minlmstate* state,
     ae_state *_state);
void minlmcreatefgh(ae_int_t n,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state);
void minlmsetcond(minlmstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void minlmsetxrep(minlmstate* state, ae_bool needxrep, ae_state *_state);
void minlmsetstpmax(minlmstate* state, double stpmax, ae_state *_state);
void minlmsetscale(minlmstate* state,
     /* Real    */ ae_vector* s,
     ae_state *_state);
void minlmsetbc(minlmstate* state,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state);
void minlmsetacctype(minlmstate* state,
     ae_int_t acctype,
     ae_state *_state);
ae_bool minlmiteration(minlmstate* state, ae_state *_state);
void minlmresults(minlmstate* state,
     /* Real    */ ae_vector* x,
     minlmreport* rep,
     ae_state *_state);
void minlmresultsbuf(minlmstate* state,
     /* Real    */ ae_vector* x,
     minlmreport* rep,
     ae_state *_state);
void minlmrestartfrom(minlmstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void minlmcreatevgj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state);
void minlmcreatefgj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state);
void minlmcreatefj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state);
void minlmsetgradientcheck(minlmstate* state,
     double teststep,
     ae_state *_state);
ae_bool _minlmstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minlmstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minlmstate_clear(void* _p);
void _minlmstate_destroy(void* _p);
ae_bool _minlmreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minlmreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minlmreport_clear(void* _p);
void _minlmreport_destroy(void* _p);
void minlbfgssetdefaultpreconditioner(minlbfgsstate* state,
     ae_state *_state);
void minlbfgssetcholeskypreconditioner(minlbfgsstate* state,
     /* Real    */ ae_matrix* p,
     ae_bool isupper,
     ae_state *_state);
void minbleicsetbarrierwidth(minbleicstate* state,
     double mu,
     ae_state *_state);
void minbleicsetbarrierdecay(minbleicstate* state,
     double mudecay,
     ae_state *_state);
void minasacreate(ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     minasastate* state,
     ae_state *_state);
void minasasetcond(minasastate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state);
void minasasetxrep(minasastate* state, ae_bool needxrep, ae_state *_state);
void minasasetalgorithm(minasastate* state,
     ae_int_t algotype,
     ae_state *_state);
void minasasetstpmax(minasastate* state, double stpmax, ae_state *_state);
ae_bool minasaiteration(minasastate* state, ae_state *_state);
void minasaresults(minasastate* state,
     /* Real    */ ae_vector* x,
     minasareport* rep,
     ae_state *_state);
void minasaresultsbuf(minasastate* state,
     /* Real    */ ae_vector* x,
     minasareport* rep,
     ae_state *_state);
void minasarestartfrom(minasastate* state,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state);
ae_bool _minasastate_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minasastate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minasastate_clear(void* _p);
void _minasastate_destroy(void* _p);
ae_bool _minasareport_init(void* _p, ae_state *_state, ae_bool make_automatic);
ae_bool _minasareport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _minasareport_clear(void* _p);
void _minasareport_destroy(void* _p);

}
#endif

