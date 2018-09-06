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
#ifndef _specialfunctions_pkg_h
#define _specialfunctions_pkg_h
#include "ap.h"
#include "alglibinternal.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////

/*// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////
//
// 이 섹션에는 컴퓨터 핵심 선언문 (데이터)이 포함되어 있습니다.
//
// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////*/

namespace alglib_impl
{

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////

/*// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////
//
// 이 섹션은 C ++ 인터페이스를 포함합니다.
//
// ///////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////*/

namespace alglib
{


/*************************************************************************
Gamma function

Input parameters:
    X   -   argument

Domain:
    0 < X < 171.6
    -170 < X < 0, X is not an integer.

Relative error:
 arithmetic   domain     # trials      peak         rms
    IEEE    -170,-33      20000       2.3e-15     3.3e-16
    IEEE     -33,  33     20000       9.4e-16     2.2e-16
    IEEE      33, 171.6   20000       2.3e-15     3.2e-16

Cephes Math Library Release 2.8:  June, 2000
Original copyright 1984, 1987, 1989, 1992, 2000 by Stephen L. Moshier
Translated to AlgoPascal by Bochkanov Sergey (2005, 2006, 2007).
*************************************************************************/

/*/ * ************************************************ *************************
감마 함수
입력 매개 변수 :
    X - 인수
도메인:
    0 <X <171.6
    -170 <X <0, X는 정수가 아닙니다.
상대 오류 :
 산술 도메인 # 시험 피크 rms
    IEEE -170, -33 20000 2.3e-15 3.3e-16
    IEEE-33, 33 20000 9.4e-16 2.2e-16
    IEEE 33, 171.6 20000 2.3e-15 3.2e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Original copyright 1984, 1987, 1989, 1992, 2000 Stephen L. Moshier
Bochkanov Sergey (2005, 2006, 2007)가 AlgoPascal로 번역했습니다.
*************************************************** ********************** * /*/

double gammafunction(const double x);


/*************************************************************************
Natural logarithm of gamma function

Input parameters:
    X       -   argument

Result:
    logarithm of the absolute value of the Gamma(X).

Output parameters:
    SgnGam  -   sign(Gamma(X))

Domain:
    0 < X < 2.55e305
    -2.55e305 < X < 0, X is not an integer.

ACCURACY:
arithmetic      domain        # trials     peak         rms
   IEEE    0, 3                 28000     5.4e-16     1.1e-16
   IEEE    2.718, 2.556e305     40000     3.5e-16     8.3e-17
The error criterion was relative when the function magnitude
was greater than one but absolute when it was less than one.

The following test used the relative error criterion, though
at certain points the relative error could be much higher than
indicated.
   IEEE    -200, -4             10000     4.8e-16     1.3e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 1992, 2000 by Stephen L. Moshier
Translated to AlgoPascal by Bochkanov Sergey (2005, 2006, 2007).
*************************************************************************/

/*/ * ************************************************ *************************
감마 함수의 자연 로그
입력 매개 변수 :
    X - 인수
결과:
    감마 (X)의 절대 값의 로그.
출력 매개 변수 :
    SgnGam - 부호 (감마 (X))
도메인:
    0 <X <2.55e305
    -2.55e305 <X <0, X는 정수가 아닙니다.
정확성:
산술 도메인 # 시험 피크 rms
   IEEE 0, 3 28000 5.4e-16 1.1e-16
   IEEE 2.718, 2.556e305 40000 3.5e-16 8.3e-17
오류 기준은 함수 크기
그것이 1보다 작을 때 1보다 크지 만 절대적이었다.
다음 테스트에서는 상대적 오류 기준을 사용했지만
특정 지점에서 상대 오차는
가리키는.
   IEEE -200, -4 10000 4.8e-16 1.3e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 1992, 2000 Stephen L. Moshier
Bochkanov Sergey (2005, 2006, 2007)가 AlgoPascal로 번역했습니다.
*************************************************** ********************** * /*/

double lngamma(const double x, double &sgngam);

/*************************************************************************
Error function

The integral is

                          x
                           -
                2         | |          2
  erf(x)  =  --------     |    exp( - t  ) dt.
             sqrt(pi)   | |
                         -
                          0

For 0 <= |x| < 1, erf(x) = x * P4(x**2)/Q5(x**2); otherwise
erf(x) = 1 - erfc(x).


ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0,1         30000       3.7e-16     1.0e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 1992, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
오류 기능
적분
                          엑스
                           -
                2 | | 2
  erf (x) = -------- | exp (- t) dt.
             sqrt (pi) | |
                         -
                          0
0 <= | x | <1, erf (x) = x * P4 (x ** 2) / Q5 (x ** 2); 그렇지 않으면
erf (x) = 1 - erfc (x).
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,1 30000 3.7e-16 1.0e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1988, 1992, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double errorfunction(const double x);


/*************************************************************************
Complementary error function

 1 - erf(x) =

                          inf.
                            -
                 2         | |          2
  erfc(x)  =  --------     |    exp( - t  ) dt
              sqrt(pi)   | |
                          -
                           x


For small x, erfc(x) = 1 - erf(x); otherwise rational
approximations are computed.


ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0,26.6417   30000       5.7e-14     1.5e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 1992, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
상보적인 에러 함수
 1 - erf (x) =
                          inf.
                            -
                 2 | | 2
  erfc (x) = -------- | exp (- t) dt
              sqrt (pi) | |
                          -
                           엑스
작은 x에 대해서, erfc (x) = 1 - erf (x); 그렇지 않으면 합리적인
근사치가 계산됩니다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,26.6417 30000 5.7e-14 1.5e-14
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1988, 1992, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double errorfunctionc(const double x);


/*************************************************************************
Normal distribution function

Returns the area under the Gaussian probability density
function, integrated from minus infinity to x:

                           x
                            -
                  1        | |          2
   ndtr(x)  = ---------    |    exp( - t /2 ) dt
              sqrt(2pi)  | |
                          -
                         -inf.

            =  ( 1 + erf(z) ) / 2
            =  erfc(z) / 2

where z = x/sqrt(2). Computation is via the functions
erf and erfc.


ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE     -13,0        30000       3.4e-14     6.7e-15

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 1992, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
정규 분포 함수
가우스 확률 밀도 영역을 반환합니다.
함수, 마이너스 무한대에서 x :
                           엑스
                            -
                  1 | | 2
   ndtr (x) = --------- | exp (-t / 2) dt
              sqrt (2pi) | |
                          -
                         -inf.
            = (1 + erf (z)) / 2
            = erfc (z) / 2
여기서 z = x / sqrt (2). 계산은 함수를 통해 이루어진다.
erf 및 erfc.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE -13,0 30000 3.4e-14 6.7e-15
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1988, 1992, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double normaldistribution(const double x);


/*************************************************************************
Inverse of the error function

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 1992, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
오류 함수의 반전
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1988, 1992, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double inverf(const double e);


/*************************************************************************
Inverse of Normal distribution function

Returns the argument, x, for which the area under the
Gaussian probability density function (integrated from
minus infinity to x) is equal to y.


For small arguments 0 < y < exp(-2), the program computes
z = sqrt( -2.0 * log(y) );  then the approximation is
x = z - log(z)/z  - (1/z) P(1/z) / Q(1/z).
There are two rational functions P/Q, one for 0 < y < exp(-32)
and the other for y up to exp(-2).  For larger arguments,
w = y - 0.5, and  x/sqrt(2pi) = w + w**3 R(w**2)/S(w**2)).

ACCURACY:

                     Relative error:
arithmetic   domain        # trials      peak         rms
   IEEE     0.125, 1        20000       7.2e-16     1.3e-16
   IEEE     3e-308, 0.135   50000       4.6e-16     9.8e-17

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 1992, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
정규 분포 함수의 역함수
인수 x를 반환합니다.
가우시안 확률 밀도 함수 (
x에서 무한대 마이너스)는 y와 같습니다.
작은 인수 0 <y <exp (-2)의 경우, 프로그램은
z = sqrt (-2.0 * log (y)); 근사값은 다음과 같습니다.
x = z - log (z) / z - (1 / z) P (1 / z) / Q (1 / z)
2 개의 합리적인 함수 P / Q가 있는데, 하나는 0 <y <exp (-32)
y는 exp (-2)까지입니다. 더 큰 논증을 위해,
w = y - 0.5이고, x / sqrt (2π) = w + w ** 3 R (w ** 2) / S (w ** 2)).
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0.125, 1 20000 7.2e-16 1.3e-16
   IEEE 3e-308, 0.135 50000 4.6e-16 9.8e-17
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1988, 1992, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invnormaldistribution(const double y0);

/*************************************************************************
Incomplete gamma integral

The function is defined by

                          x
                           -
                  1       | |  -t  a-1
 igam(a,x)  =   -----     |   e   t   dt.
                 -      | |
                | (a)    -
                          0


In this implementation both arguments must be positive.
The integral is evaluated by either a power series or
continued fraction expansion, depending on the relative
values of a and x.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0,30       200000       3.6e-14     2.9e-15
   IEEE      0,100      300000       9.9e-14     1.5e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
불완전한 감마 적분
함수는 다음과 같이 정의됩니다.
                          엑스
                           -
                  1 | | -t a-1
igam (a, x) = ----- | et dt.
                 - | |
                | (a) -
                          0
이 구현에서 두 인수는 양수 여야합니다.
적분은 멱급수 또는
친척에 따라 계속되는 분수 확장
a와 x의 값.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,30 200000 3.6e-14 2.9e-15
   IEEE 0,100 300000 9.9e-14 1.5e-14
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1985, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double incompletegamma(const double a, const double x);


/*************************************************************************
Complemented incomplete gamma integral

The function is defined by


 igamc(a,x)   =   1 - igam(a,x)

                           inf.
                             -
                    1       | |  -t  a-1
              =   -----     |   e   t   dt.
                   -      | |
                  | (a)    -
                            x


In this implementation both arguments must be positive.
The integral is evaluated by either a power series or
continued fraction expansion, depending on the relative
values of a and x.

ACCURACY:

Tested at random a, x.
               a         x                      Relative error:
arithmetic   domain   domain     # trials      peak         rms
   IEEE     0.5,100   0,100      200000       1.9e-14     1.7e-15
   IEEE     0.01,0.5  0,100      200000       1.4e-13     1.6e-15

Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
불완전한 감마 상수를 보완했습니다.
함수는 다음과 같이 정의됩니다.
 igamc (a, x) = 1 - igam (a, x)
                           inf.
                             -
                    1 | | -t a-1
              = ----- | et dt.
                   - | |
                  | (a) -
                            엑스
이 구현에서 두 인수는 양수 여야합니다.
적분은 멱급수 또는
친척에 따라 계속되는 분수 확장
a와 x의 값.
정확성:
임의로 a, x로 테스트했습니다.
               도끼 상대 오차 :
산술 도메인 도메인 # trials peak rms
   IEEE 0.5,100 0,100 200000 1.9e-14 1.7e-15
   IEEE 0.01,0.5 0,100 200000 1.4e-13 1.6e-15
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1985, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double incompletegammac(const double a, const double x);


/*************************************************************************
Inverse of complemented imcomplete gamma integral

Given p, the function finds x such that

 igamc( a, x ) = p.

Starting with the approximate value

        3
 x = a t

 where

 t = 1 - d - ndtri(p) sqrt(d)

and

 d = 1/9a,

the routine performs up to 10 Newton iterations to find the
root of igamc(a,x) - p = 0.

ACCURACY:

Tested at random a, p in the intervals indicated.

               a        p                      Relative error:
arithmetic   domain   domain     # trials      peak         rms
   IEEE     0.5,100   0,0.5       100000       1.0e-14     1.7e-15
   IEEE     0.01,0.5  0,0.5       100000       9.0e-14     3.4e-15
   IEEE    0.5,10000  0,0.5        20000       2.3e-13     3.8e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
보완 된 불완전한 감마 적분의 역
감안할 때,이 함수는 다음과 같은 x를 찾습니다.
 igamc (a, x) = p.
근사값으로 시작
        삼
 x = at
 어디에
 t = 1 - d - ndtri (p) sqrt (d)
과
 d = 1 / 9a,
루틴은 10 뉴턴 반복을 수행하여
igamc (a, x)의 뿌리 - p = 0.
정확성:
지정된 간격으로 임의의 a, p에서 테스트되었습니다.
               ap 상대 오류 :
산술 도메인 도메인 # trials peak rms
   IEEE 0.5,100 0,0.5 100000 1.0e-14 1.7e-15
   IEEE 0.01,0.5 0,0.5 100000 9.0e-14 3.4e-15
   IEEE 0.5,10000 0,0.5 20000 2.3e-13 3.8e-14
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invincompletegammac(const double a, const double y0);

/*************************************************************************
Airy function

Solution of the differential equation

y"(x) = xy.

The function returns the two independent solutions Ai, Bi
and their first derivatives Ai'(x), Bi'(x).

Evaluation is by power series summation for small x,
by rational minimax approximations for large x.



ACCURACY:
Error criterion is absolute when function <= 1, relative
when function > 1, except * denotes relative error criterion.
For large negative x, the absolute error increases as x^1.5.
For large positive x, the relative error increases as x^1.5.

Arithmetic  domain   function  # trials      peak         rms
IEEE        -10, 0     Ai        10000       1.6e-15     2.7e-16
IEEE          0, 10    Ai        10000       2.3e-14*    1.8e-15*
IEEE        -10, 0     Ai'       10000       4.6e-15     7.6e-16
IEEE          0, 10    Ai'       10000       1.8e-14*    1.5e-15*
IEEE        -10, 10    Bi        30000       4.2e-15     5.3e-16
IEEE        -10, 10    Bi'       30000       4.9e-15     7.3e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
통풍 기능
미분 방정식의 해법
y "(x) = xy.
이 함수는 두 개의 독립 솔루션 Ai, Bi를 반환합니다.
및 그들의 1 차 도함수 Ai '(x), Bi'(x).
평가는 작은 x에 대한 멱급수 합에 의한 것이며,
큰 x에 대한 합리적인 미니 맥스 근사법.
정확성:
오류 기준은 함수 <= 1 일 때 절대 값입니다.
function> 1 인 경우 *를 제외하고는 상대 오류 기준을 나타냅니다.
큰 음수 x의 경우, 절대 오차는 x ^ 1.5만큼 증가합니다.
큰 양수 x의 경우 상대 오차는 x ^ 1.5로 증가합니다.
산술 도메인 함수 # trials peak rms
IEEE -10, 0 Ai 10000 1.6e-15 2.7e-16
IEEE 0,10 Ai 10000 2.3e-14 * 1.8e-15 *
IEEE -10, 0Ai '10000 4.6e-15 7.6e-16
IEEE 0, 10 Ai '10000 1.8e-14 * 1.5e-15 *
IEEE -10, 10 Bi 30000 4.2e-15 5.3e-16
IEEE -10, 10 Bi '30000 4.9e-15 7.3e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

void airy(const double x, double &ai, double &aip, double &bi, double &bip);

/*************************************************************************
Bessel function of order zero

Returns Bessel function of order zero of the argument.

The domain is divided into the intervals [0, 5] and
(5, infinity). In the first interval the following rational
approximation is used:


       2         2
(w - r  ) (w - r  ) P (w) / Q (w)
      1         2    3       8

           2
where w = x  and the two r's are zeros of the function.

In the second interval, the Hankel asymptotic expansion
is employed with two rational functions of degree 6/6
and 7/7.

ACCURACY:

                     Absolute error:
arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       60000       4.2e-16     1.1e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
순서 0의 베셀 기능
인수 0 차의 Bessel 함수를 반환합니다.
도메인은 구간 [0, 5]와
(5, 무한대). 첫 번째 간격에서 다음 합리적인
근사가 사용됩니다.
       2 2
(w - r) (w - r) P (w) / Q (w)
      1 2 3 8
           2
여기서 w = x이고 두 r은 함수의 제로입니다.
두 번째 간격에서, Hankel asymptotic expansion
차수 6/6의 2 가지 유리 함수
7/7.
정확성:
                     절대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 60000 4.2e-16 1.1e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besselj0(const double x);


/*************************************************************************
Bessel function of order one

Returns Bessel function of order one of the argument.

The domain is divided into the intervals [0, 8] and
(8, infinity). In the first interval a 24 term Chebyshev
expansion is used. In the second, the asymptotic
trigonometric representation is employed using two
rational functions of degree 5/5.

ACCURACY:

                     Absolute error:
arithmetic   domain      # trials      peak         rms
   IEEE      0, 30       30000       2.6e-16     1.1e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
주문 하나의 베셀 기능
인수의 순서 1의 Bessel 함수를 반환합니다.
도메인은 구간 [0, 8]과
(8, 무한대). 첫 번째 구간에서는 24 기 체비 셰프
확장이 사용됩니다. 둘째, 점근선
삼각법 표현은 두 개
학위 5/5의 합리적인 기능.
정확성:
                     절대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 2.6e-16 1.1e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besselj1(const double x);


/*************************************************************************
Bessel function of integer order

Returns Bessel function of order n, where n is a
(possibly negative) integer.

The ratio of jn(x) to j0(x) is computed by backward
recurrence.  First the ratio jn/jn-1 is found by a
continued fraction expansion.  Then the recurrence
relating successive orders is applied until j0 or j1 is
reached.

If n = 0 or 1 the routine for j0 or j1 is called
directly.

ACCURACY:

                     Absolute error:
arithmetic   range      # trials      peak         rms
   IEEE      0, 30        5000       4.4e-16     7.9e-17


Not suitable for large n or x. Use jv() (fractional order) instead.

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
정수 순서의 베셀 함수
n 차의 베셀 함수를 반환합니다. 여기서 n은 a입니다.
(아마도 음수) 정수.
j0 (x)에 대한 jn (x)의 비율은 역방향으로 계산됩니다
회귀. 먼저 비율 jn / jn-1은
계속적인 분수 확장. 그런 다음 재발
j0 또는 j1이 될 때까지 연속 명령 관련
도달했습니다.
n = 0 또는 1이면 j0 또는 j1에 대한 루틴이 호출됩니다.
직접.
정확성:
                     절대 오류 :
산술 범위 # 시험 피크 RMS
   IEEE 0, 30 5000 4.4e-16 7.9e-17
큰 n 또는 x에는 적합하지 않습니다. 대신 jv () (소수점 순서)를 사용하십시오.
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besseljn(const ae_int_t n, const double x);


/*************************************************************************
Bessel function of the second kind, order zero

Returns Bessel function of the second kind, of order
zero, of the argument.

The domain is divided into the intervals [0, 5] and
(5, infinity). In the first interval a rational approximation
R(x) is employed to compute
  y0(x)  = R(x)  +   2 * log(x) * j0(x) / PI.
Thus a call to j0() is required.

In the second interval, the Hankel asymptotic expansion
is employed with two rational functions of degree 6/6
and 7/7.



ACCURACY:

 Absolute error, when y0(x) < 1; else relative error:

arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       30000       1.3e-15     1.6e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
두 번째 종류의 베셀 함수, 제로 순서
순서의 두 번째 종류의 베셀 함수를 반환합니다.
인수의 제로
도메인은 구간 [0, 5]와
(5, 무한대). 첫 번째 간격에서 합리적인 근사
R (x)는
  y0 (x) = R (x) + 2 * log (x) * j0 (x) / PI이다.
따라서 j0 ()에 대한 호출이 필요합니다.
두 번째 간격에서, Hankel asymptotic expansion
차수 6/6의 2 가지 유리 함수
7/7.
정확성:
절대 오류, y0 (x) <1; 그 밖의 상대적인 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 1.3e-15 1.6e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double bessely0(const double x);


/*************************************************************************
Bessel function of second kind of order one

Returns Bessel function of the second kind of order one
of the argument.

The domain is divided into the intervals [0, 8] and
(8, infinity). In the first interval a 25 term Chebyshev
expansion is used, and a call to j1() is required.
In the second, the asymptotic trigonometric representation
is employed using two rational functions of degree 5/5.

ACCURACY:

                     Absolute error:
arithmetic   domain      # trials      peak         rms
   IEEE      0, 30       30000       1.0e-15     1.3e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
두 번째 종류의 베셀 기능
두 번째 종류의 베셀 함수를 반환합니다.
인수의.
도메인은 구간 [0, 8]과
(8, 무한대). 첫 번째 간격에서 25 기 체비 셰프
확장이 사용되며 j1 ()에 대한 호출이 필요합니다.
두 번째로, 점근 적 삼각 함수 표현
차수 5/5의 두 가지 합리적인 함수를 사용하여 사용됩니다.
정확성:
                     절대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 1.0e-15 1.3e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double bessely1(const double x);


/*************************************************************************
Bessel function of second kind of integer order

Returns Bessel function of order n, where n is a
(possibly negative) integer.

The function is evaluated by forward recurrence on
n, starting with values computed by the routines
y0() and y1().

If n = 0 or 1 the routine for y0 or y1 is called
directly.

ACCURACY:
                     Absolute error, except relative
                     when y > 1:
arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       30000       3.4e-15     4.3e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
두 번째 종류의 정수 순서의 베셀 함수
n 차의 베셀 함수를 반환합니다. 여기서 n은 a입니다.
(아마도 음수) 정수.
이 기능은 다음에 대한 순방향 재발에 의해 평가됩니다.
n, 루틴에 의해 계산 된 값으로 시작
y0 () 및 y1 ().
n = 0 또는 1이면 y0 또는 y1에 대한 루틴이 호출됩니다.
직접.
정확성:
                     상대적 오류를 제외한 절대 오류
                     y> 1 일 때 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 3.4e-15 4.3e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besselyn(const ae_int_t n, const double x);


/*************************************************************************
Modified Bessel function of order zero

Returns modified Bessel function of order zero of the
argument.

The function is defined as i0(x) = j0( ix ).

The range is partitioned into the two intervals [0,8] and
(8, infinity).  Chebyshev polynomial expansions are employed
in each interval.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0,30        30000       5.8e-16     1.4e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
순서 0의 수정 된 베셀 기능
0 차의 수정 된 Bessel 함수를 반환합니다.
논의.
함수는 i0 (x) = j0 (ix)로 정의됩니다.
범위는 두 개의 간격 [0,8]과
(8, 무한대). Chebyshev 다항식 확장이 사용됩니다.
각 간격마다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,30 30000 5.8e-16 1.4e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besseli0(const double x);


/*************************************************************************
Modified Bessel function of order one

Returns modified Bessel function of order one of the
argument.

The function is defined as i1(x) = -i j1( ix ).

The range is partitioned into the two intervals [0,8] and
(8, infinity).  Chebyshev polynomial expansions are employed
in each interval.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       30000       1.9e-15     2.1e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
주문 하나의 변형 된 베셀 기능
주문 Bessel 함수를 반환합니다.
논의.
함수는 i1 (x) = -ij1 (ix)로 정의됩니다.
범위는 두 개의 간격 [0,8]과
(8, 무한대). Chebyshev 다항식 확장이 사용됩니다.
각 간격마다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 1.9e-15 2.1e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1985, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besseli1(const double x);


/*************************************************************************
Modified Bessel function, second kind, order zero

Returns modified Bessel function of the second kind
of order zero of the argument.

The range is partitioned into the two intervals [0,8] and
(8, infinity).  Chebyshev polynomial expansions are employed
in each interval.

ACCURACY:

Tested at 2000 random points between 0 and 8.  Peak absolute
error (relative when K0 > 1) was 1.46e-14; rms, 4.26e-15.
                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       30000       1.2e-15     1.6e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
수정 된 베셀 함수, 두 번째 종류, 순서 제로
두 번째 종류의 수정 된 베셀 함수를 반환합니다.
인수의 0 번째 순서
범위는 두 개의 간격 [0,8]과
(8, 무한대). Chebyshev 다항식 확장이 사용됩니다.
각 간격마다.
정확성:
0에서 8 사이의 2000 임의의 지점에서 테스트되었습니다. 피크 절대 값
오차 (K0> 1 일 때 상대적 임)는 1.46e-14; rms, 4.26e-15.
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 1.2e-15 1.6e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besselk0(const double x);


/*************************************************************************
Modified Bessel function, second kind, order one

Computes the modified Bessel function of the second kind
of order one of the argument.

The range is partitioned into the two intervals [0,2] and
(2, infinity).  Chebyshev polynomial expansions are employed
in each interval.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       30000       1.2e-15     1.6e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
수정 된 베셀 기능, 두 번째 종류, 주문 하나
두 번째 종류의 수정 된 베셀 함수를 계산합니다.
인수의 순서 중 하나.
범위는 두 개의 간격 [0,2]과
(2, 무한대). Chebyshev 다항식 확장이 사용됩니다.
각 간격마다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 30000 1.2e-15 1.6e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besselk1(const double x);


/*************************************************************************
Modified Bessel function, second kind, integer order

Returns modified Bessel function of the second kind
of order n of the argument.

The range is partitioned into the two intervals [0,9.55] and
(9.55, infinity).  An ascending power series is used in the
low range, and an asymptotic expansion in the high range.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0,30        90000       1.8e-8      3.0e-10

Error is high only near the crossover point x = 9.55
between the two expansions used.

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
수정 된 베셀 함수, 두 번째 종류, 정수 순서
두 번째 종류의 수정 된 베셀 함수를 반환합니다.
인수의 차수 n.
범위는 두 개의 간격 [0, 9.55]과
(9.55, 무한대). 오름차순 멱급수가
낮은 범위 및 높은 범위에서의 점근 적 확장을 포함한다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,30 90000 1.8e-8 3.0e-10
크로스 오버 포인트 x = 9.55 부근에서만 오차가 높습니다.
사용 된 두 확장 사이.
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1988, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double besselkn(const ae_int_t nn, const double x);

/*************************************************************************
Beta function


                  -     -
                 | (a) | (b)
beta( a, b )  =  -----------.
                    -
                   | (a+b)

For large arguments the logarithm of the function is
evaluated using lgam(), then exponentiated.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE       0,30       30000       8.1e-14     1.1e-14

Cephes Math Library Release 2.0:  April, 1987
Copyright 1984, 1987 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
베타 기능
                  - -
                 | (a) | (비)
베타 (a, b) = -----------.
                    -
                   | (a + b)
큰 인수의 경우 함수의 로그는 다음과 같습니다.
lgam ()을 사용하여 평가 한 다음 지수화합니다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,30 30000 8.1e-14 1.1e-14
Cephes 수학 라이브러리 릴리스 2.0 : 1987 년 4 월
Copyright 1984, Stephen L. Moshier의 1987 년
*************************************************** ********************** * /*/

double beta(const double a, const double b);

/*************************************************************************
Incomplete beta integral

Returns incomplete beta integral of the arguments, evaluated
from zero to x.  The function is defined as

                 x
    -            -
   | (a+b)      | |  a-1     b-1
 -----------    |   t   (1-t)   dt.
  -     -     | |
 | (a) | (b)   -
                0

The domain of definition is 0 <= x <= 1.  In this
implementation a and b are restricted to positive values.
The integral from x to 1 may be obtained by the symmetry
relation

   1 - incbet( a, b, x )  =  incbet( b, a, 1-x ).

The integral is evaluated by a continued fraction expansion
or, when b*x is small, by a power series.

ACCURACY:

Tested at uniformly distributed random points (a,b,x) with a and b
in "domain" and x between 0 and 1.
                                       Relative error
arithmetic   domain     # trials      peak         rms
   IEEE      0,5         10000       6.9e-15     4.5e-16
   IEEE      0,85       250000       2.2e-13     1.7e-14
   IEEE      0,1000      30000       5.3e-12     6.3e-13
   IEEE      0,10000    250000       9.3e-11     7.1e-12
   IEEE      0,100000    10000       8.7e-10     4.8e-11
Outputs smaller than the IEEE gradual underflow threshold
were excluded from these statistics.

Cephes Math Library, Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
불완전한 베타 적분
인수의 불완전한 베타 적분을 반환하고 계산합니다.
0부터 x까지. 이 함수는 다음과 같이 정의됩니다.
                 엑스
    - -
   | (a + b) | | a-1 b-1
----------- | t (1-t) dt이다.
  - - | |
| (a) | (b) -
                0
정의의 도메인은 0 <= x <= 1입니다.
구현 a와 b는 양수 값으로 제한됩니다.
x에서 1까지의 적분은 대칭에 의해 얻어 질 수있다.
관계
   1 - incbet (a, b, x) = incbet (b, a, 1-x).
적분은 연속 분수 확장에 의해 평가됩니다.
또는, b * x가 작은 경우에, 멱급수에 의해.
정확성:
균일 분포 된 임의의 점 (a, b, x)에서 a와 b를 사용하여 테스트
"도메인"에서 x는 0과 1 사이입니다.
                                       상대 오류
산술 도메인 # 시험 피크 rms
   IEEE 0,5 10000 6.9e-15 4.5e-16
   IEEE 0,85 250000 2.2e-13 1.7e-14
   IEEE 0,1000 30000 5.3e-12 6.3e-13
   IEEE 0,10000 250000 9.3e-11 7.1e-12
   IEEE 0,100000 10000 8.7e-10 4.8e-11
IEEE 점진적 언더 플로 임계 값보다 작은 출력
이 통계에서 제외되었습니다.
Cephes 수학 라이브러리, 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double incompletebeta(const double a, const double b, const double x);


/*************************************************************************
Inverse of imcomplete beta integral

Given y, the function finds x such that

 incbet( a, b, x ) = y .

The routine performs interval halving or Newton iterations to find the
root of incbet(a,b,x) - y = 0.


ACCURACY:

                     Relative error:
               x     a,b
arithmetic   domain  domain  # trials    peak       rms
   IEEE      0,1    .5,10000   50000    5.8e-12   1.3e-13
   IEEE      0,1   .25,100    100000    1.8e-13   3.9e-15
   IEEE      0,1     0,5       50000    1.1e-12   5.5e-15
With a and b constrained to half-integer or integer values:
   IEEE      0,1    .5,10000   50000    5.8e-12   1.1e-13
   IEEE      0,1    .5,100    100000    1.7e-14   7.9e-16
With a = .5, b constrained to half-integer or integer values:
   IEEE      0,1    .5,10000   10000    8.3e-11   1.0e-11

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1996, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
불완전한 베타 적분의 반전
주어진 y에서, 함수는 다음과 같은 x를 찾습니다.
 incbet (a, b, x) = y.
루틴은 간격 반감 또는 뉴턴 반복을 수행하여
incbet (a, b, x)의 루트 - y = 0.
정확성:
                     상대 오류 :
               xa, b
산술 도메인 도메인 # trials peak rms
   IEEE 0,1.5,10000 50000 5.8e-12 1.3e-13
   IEEE 0,1.25,100 100000 1.8e-13 3.9e-15
   IEEE 0,1 0,5 50000 1.1e-12 5.5e-15
a 및 b가 반 정수 또는 정수 값으로 제한되는 경우
   IEEE 0,1.5,10000 50000 5.8e-12 1.1e-13
   IEEE 0,1.5,100 100000 1.7e-14 7.9e-16
a = .5, b는 반 정수 또는 정수 값으로 제한됩니다.
   IEEE 0,1.5,10000 10000 8.3e-11 1.0e-11
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1996, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invincompletebeta(const double a, const double b, const double y);

/*************************************************************************
Binomial distribution

Returns the sum of the terms 0 through k of the Binomial
probability density:

  k
  --  ( n )   j      n-j
  >   (   )  p  (1-p)
  --  ( j )
 j=0

The terms are not summed directly; instead the incomplete
beta integral is employed, according to the formula

y = bdtr( k, n, p ) = incbet( n-k, k+1, 1-p ).

The arguments must be positive, with p ranging from 0 to 1.

ACCURACY:

Tested at random points (a,b,p), with p between 0 and 1.

              a,b                     Relative error:
arithmetic  domain     # trials      peak         rms
 For p between 0.001 and 1:
   IEEE     0,100       100000      4.3e-15     2.6e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
이항 분포
이항의 0부터 k까지의 항의 합을 구합니다.
확률 밀도 :
  케이
  - (n) j nj
  > () p (1-p)
  - (j)
 j = 0
용어는 직접적으로 합산되지 않습니다. 대신 불완전
베타 적분이 식
y = bdtr (k, n, p) = incbet (nk, k + 1, 1-p).
인수는 양수 여야하며 p는 0에서 1 사이입니다.
정확성:
임의의 점 (a, b, p)에서 0에서 1 사이의 p로 테스트합니다.
              a, b 상대 오류 :
산술 도메인 # 시험 피크 rms
 0.001에서 1 사이의 p의 경우 :
   IEEE 0,100 100000 4.3e-15 2.6e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double binomialdistribution(const ae_int_t k, const ae_int_t n, const double p);


/*************************************************************************
Complemented binomial distribution

Returns the sum of the terms k+1 through n of the Binomial
probability density:

  n
  --  ( n )   j      n-j
  >   (   )  p  (1-p)
  --  ( j )
 j=k+1

The terms are not summed directly; instead the incomplete
beta integral is employed, according to the formula

y = bdtrc( k, n, p ) = incbet( k+1, n-k, p ).

The arguments must be positive, with p ranging from 0 to 1.

ACCURACY:

Tested at random points (a,b,p).

              a,b                     Relative error:
arithmetic  domain     # trials      peak         rms
 For p between 0.001 and 1:
   IEEE     0,100       100000      6.7e-15     8.2e-16
 For p between 0 and .001:
   IEEE     0,100       100000      1.5e-13     2.7e-15

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
보간 된 이항 분포
이항의 k + 1부터 n까지의 항의 합을 구합니다.
확률 밀도 :
  엔
  - (n) j nj
  > () p (1-p)
  - (j)
 j = k + 1
용어는 직접적으로 합산되지 않습니다. 대신 불완전
베타 적분이 식
y = bdtrc (k, n, p) = incbet (k + 1, nk, p).
인수는 양수 여야하며 p는 0에서 1 사이입니다.
정확성:
임의의 지점 (a, b, p)에서 테스트되었습니다.
              a, b 상대 오류 :
산술 도메인 # 시험 피크 rms
 0.001에서 1 사이의 p의 경우 :
   IEEE 0,100 100000 6.7e-15 8.2e-16
 p가 0에서 .001 사이 인 경우 :
   IEEE 0,100 100000 1.5e-13 2.7e-15
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double binomialcdistribution(const ae_int_t k, const ae_int_t n, const double p);


/*************************************************************************
Inverse binomial distribution

Finds the event probability p such that the sum of the
terms 0 through k of the Binomial probability density
is equal to the given cumulative probability y.

This is accomplished using the inverse beta integral
function and the relation

1 - p = incbi( n-k, k+1, y ).

ACCURACY:

Tested at random points (a,b,p).

              a,b                     Relative error:
arithmetic  domain     # trials      peak         rms
 For p between 0.001 and 1:
   IEEE     0,100       100000      2.3e-14     6.4e-16
   IEEE     0,10000     100000      6.6e-12     1.2e-13
 For p between 10^-6 and 0.001:
   IEEE     0,100       100000      2.0e-12     1.3e-14
   IEEE     0,10000     100000      1.5e-12     3.2e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
역 이항 분포
이벤트 확률 p를 찾아서
이항 확률 밀도의 항 0부터 k까지
주어진 누적 확률 y와 같습니다.
이는 역 베타 적분을 사용하여 수행됩니다.
함수와 관계
1-p = incbi (nk, k + 1, y).
정확성:
임의의 지점 (a, b, p)에서 테스트되었습니다.
              a, b 상대 오류 :
산술 도메인 # 시험 피크 rms
 0.001에서 1 사이의 p의 경우 :
   IEEE 0,100 100000 2.3e-14 6.4e-16
   IEEE 0,10000 100000 6.6e-12 1.2e-13
 p가 10 ^ -6에서 0.001 사이 인 경우 :
   IEEE 0,100 100000 2.0e-12 1.3e-14
   IEEE 0,10000 100000 1.5e-12 3.2e-14
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invbinomialdistribution(const ae_int_t k, const ae_int_t n, const double y);

/*************************************************************************
Calculation of the value of the Chebyshev polynomials of the
first and second kinds.

Parameters:
    r   -   polynomial kind, either 1 or 2.
    n   -   degree, n>=0
    x   -   argument, -1 <= x <= 1

Result:
    the value of the Chebyshev polynomial at x
*************************************************************************/

/*/ * ************************************************ *************************
Chebyshev 다항식 값의 계산
첫 번째 및 두 번째 종류.
매개 변수 :
    r - 1 또는 2의 다항식 종류.
    n - degree, n> = 0
    x - 인수, -1 <= x <= 1
결과:
    x에서의 체비 셰프 다항식의 값
*************************************************** ********************** * /*/

double chebyshevcalculate(const ae_int_t r, const ae_int_t n, const double x);


/*************************************************************************
Summation of Chebyshev polynomials using Clenshaw\92s recurrence formula.

This routine calculates
    c[0]*T0(x) + c[1]*T1(x) + ... + c[N]*TN(x)
or
    c[0]*U0(x) + c[1]*U1(x) + ... + c[N]*UN(x)
depending on the R.

Parameters:
    r   -   polynomial kind, either 1 or 2.
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Chebyshev polynomial at x
*************************************************************************/

/*/ * ************************************************ *************************
Clenshaw의 반복 수식을 사용하여 Chebyshev 다항식의 합계.
이 루틴은
    T (x) + ... + c [N] * TN (x)
또는
    U (x) + ... + c [N] * UN (x)
R에 따라 다르다.
매개 변수 :
    r - 1 또는 2의 다항식 종류.
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 체비 셰프 다항식의 값
*************************************************** ********************** * /*/

double chebyshevsum(const real_1d_array &c, const ae_int_t r, const ae_int_t n, const double x);


/*************************************************************************
Representation of Tn as C[0] + C[1]*X + ... + C[N]*X^N

Input parameters:
    N   -   polynomial degree, n>=0

Output parameters:
    C   -   coefficients
*************************************************************************/

/* ************************************************ *************************
C[0] + C [1] * X + ... + C [N] * X ^ N 인 Tn의 표현
입력 매개 변수 :
    N - 다항식 차수, n> = 0
출력 매개 변수 :
    C - 계수
*************************************************** ********************** */

void chebyshevcoefficients(const ae_int_t n, real_1d_array &c);


/*************************************************************************
Conversion of a series of Chebyshev polynomials to a power series.

Represents A[0]*T0(x) + A[1]*T1(x) + ... + A[N]*Tn(x) as
B[0] + B[1]*X + ... + B[N]*X^N.

Input parameters:
    A   -   Chebyshev series coefficients
    N   -   degree, N>=0

Output parameters
    B   -   power series coefficients
*************************************************************************/

/*/ * ************************************************ *************************
일련의 Chebyshev 다항식을 멱급수로 변환.
A [0] * T0 (x) + A [1] * T1 (x) + ... + A [N] * Tn (x)를
B [0] + B [1] * X + ... + B [N] * X ^ N.
입력 매개 변수 :
    A - 체비 셰프 (Chebyshev) 계열 계수
    N -도, N> = 0
출력 매개 변수
    B - 멱급수 계수
*************************************************** ********************** * /*/

void fromchebyshev(const real_1d_array &a, const ae_int_t n, real_1d_array &b);

/*************************************************************************
Chi-square distribution

Returns the area under the left hand tail (from 0 to x)
of the Chi square probability density function with
v degrees of freedom.


                                  x
                                   -
                       1          | |  v/2-1  -t/2
 P( x | v )   =   -----------     |   t      e     dt
                   v/2  -       | |
                  2    | (v/2)   -
                                  0

where x is the Chi-square variable.

The incomplete gamma integral is used, according to the
formula

y = chdtr( v, x ) = igam( v/2.0, x/2.0 ).

The arguments must both be positive.

ACCURACY:

See incomplete gamma function


Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
카이 제곱 분포
왼쪽 꼬리 아래 영역을 반환합니다 (0에서 x까지).
Chi 제곱 확률 밀도 함수의
v 자유도.
                                  엑스
                                   -
                       1 | | v / 2-1 -t / 2
P (x | v) = ----------- | 테드
                   v / 2 - | |
                  2 | (v / 2) -
                                  0
여기서 x는 카이 제곱 변수입니다.
불완전한 감마 상수는
공식
y = chdtr (v, x) = igam (v / 2.0, x / 2.0).
논쟁은 모두 긍정적이어야합니다.
정확성:
불완전 감마 함수보기
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double chisquaredistribution(const double v, const double x);


/*************************************************************************
Complemented Chi-square distribution

Returns the area under the right hand tail (from x to
infinity) of the Chi square probability density function
with v degrees of freedom:

                                 inf.
                                   -
                       1          | |  v/2-1  -t/2
 P( x | v )   =   -----------     |   t      e     dt
                   v/2  -       | |
                  2    | (v/2)   -
                                  x

where x is the Chi-square variable.

The incomplete gamma integral is used, according to the
formula

y = chdtr( v, x ) = igamc( v/2.0, x/2.0 ).

The arguments must both be positive.

ACCURACY:

See incomplete gamma function

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
보완 된 카이 제곱 분포
오른손 꼬리 아래의 영역을 반환합니다 (x부터
무한대) Chi 제곱 확률 밀도 함수
v 자유도 :
                                 inf.
                                   -
                       1 | | v / 2-1 -t / 2
P (x | v) = ----------- | 테드
                   v / 2 - | |
                  2 | (v / 2) -
                                  엑스
여기서 x는 카이 제곱 변수입니다.
불완전한 감마 상수는
공식
y = chdtr (v, x) = igamc (v / 2.0, x / 2.0).
논쟁은 모두 긍정적이어야합니다.
정확성:
불완전 감마 함수보기
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double chisquarecdistribution(const double v, const double x);


/*************************************************************************
Inverse of complemented Chi-square distribution

Finds the Chi-square argument x such that the integral
from x to infinity of the Chi-square density is equal
to the given cumulative probability y.

This is accomplished using the inverse gamma integral
function and the relation

   x/2 = igami( df/2, y );

ACCURACY:

See inverse incomplete gamma function


Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
보완 된 카이 제곱 분포의 역
Chi-square 인수 x를 찾아서 적분
Chi-square 밀도의 x에서 무한대까지 동일하다.
주어진 누적 확률 y로.
이것은 역 감마 적분을 사용하여 수행됩니다
함수와 관계
   x / 2 = igami (df / 2, y);
정확성:
역 불완전 감마 함수보기
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invchisquaredistribution(const double v, const double y);

/*************************************************************************
Dawson's Integral

Approximates the integral

                            x
                            -
                     2     | |        2
 dawsn(x)  =  exp( -x  )   |    exp( t  ) dt
                         | |
                          -
                          0

Three different rational approximations are employed, for
the intervals 0 to 3.25; 3.25 to 6.25; and 6.25 up.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0,10        10000       6.9e-16     1.0e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
도슨의 정수
근사치
                            엑스
                            -
                     2 | | 2
dawsn (x) = exp (-x) | exp (t) dt
                         | |
                          -
                          0
세 가지 다른 합리적인 근사가 사용됩니다.
간격 0 내지 3.25; 3.25 내지 6.25; 6.25 상승.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,10 10000 6.9e-16 1.0e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double dawsonintegral(const double x);

/*************************************************************************
Complete elliptic integral of the first kind

Approximates the integral



           pi/2
            -
           | |
           |           dt
K(m)  =    |    ------------------
           |                   2
         | |    sqrt( 1 - m sin t )
          -
           0

using the approximation

    P(x)  -  log x Q(x).

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE       0,1        30000       2.5e-16     6.8e-17

Cephes Math Library, Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
첫 번째 종류의 완전한 타원 적분
근사치
           파이 / 2
            -
           | |
           | dt
K (m) = | ------------------
           | 2
         | | sqrt (1 - m sin t)
          -
           0
근사법을 사용하여
    P (x) - log x Q (x).
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,1 30000 2.5e-16 6.8e-17
Cephes 수학 라이브러리, 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double ellipticintegralk(const double m);


/*************************************************************************
Complete elliptic integral of the first kind

Approximates the integral



           pi/2
            -
           | |
           |           dt
K(m)  =    |    ------------------
           |                   2
         | |    sqrt( 1 - m sin t )
          -
           0

where m = 1 - m1, using the approximation

    P(x)  -  log x Q(x).

The argument m1 is used rather than m so that the logarithmic
singularity at m = 1 will be shifted to the origin; this
preserves maximum accuracy.

K(0) = pi/2.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE       0,1        30000       2.5e-16     6.8e-17

\C0\EB\E3\EE\F0\E8\F2\EC \E2\E7\FF\F2 \E8\E7 \E1\E8\E1\EB\E8\EE\F2\E5\EA\E8 Cephes
*************************************************************************/

/*/ * ************************************************ *************************
첫 번째 종류의 완전한 타원 적분
근사치
           파이 / 2
            -
           | |
           | dt
K (m) = | ------------------
           | 2
         | | sqrt (1 - m sin t)
          -
           0
여기서, m = 1 - m1, 근사법
    P (x) - log x Q (x).
m 대신에 인수 m1이 사용되므로 대수
m = 1의 특이점은 원점으로 이동합니다. 이
최대 정확도를 유지합니다.
K (0) = π / 2이다.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,1 30000 2.5e-16 6.8e-17

*************************************************** ********************** * /*/

double ellipticintegralkhighprecision(const double m1);


/*************************************************************************
Incomplete elliptic integral of the first kind F(phi|m)

Approximates the integral



               phi
                -
               | |
               |           dt
F(phi_\m)  =    |    ------------------
               |                   2
             | |    sqrt( 1 - m sin t )
              -
               0

of amplitude phi and modulus m, using the arithmetic -
geometric mean algorithm.




ACCURACY:

Tested at random points with m in [0, 1] and phi as indicated.

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE     -10,10       200000      7.4e-16     1.0e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
제 1 종류의 불완전 타원 적분 F (φ | m)
근사치
               파이
                -
               | |
               | dt
F (phi_m) = | ------------------
               | 2
             | | sqrt (1 - m sin t)
              -
               0
진폭 φ와 모듈러스 m의 산술 -
기하 평균 알고리즘.
정확성:
표시된대로 [0, 1] 및 phi에서 임의의 점에서 테스트되었습니다.
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE -10,10 200000 7.4e-16 1.0e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double incompleteellipticintegralk(const double phi, const double m);


/*************************************************************************
Complete elliptic integral of the second kind

Approximates the integral


           pi/2
            -
           | |                 2
E(m)  =    |    sqrt( 1 - m sin t ) dt
         | |
          -
           0

using the approximation

     P(x)  -  x log x Q(x).

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE       0, 1       10000       2.1e-16     7.3e-17

Cephes Math Library, Release 2.8: June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
두 번째 종류의 완전한 타원 적분
근사치
           파이 / 2
            -
           | | 2
E (m) = | sqrt (1 - m sin t) dt
         | |
          -
           0
근사법을 사용하여
     P (x) - x log x Q (x).
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 1 10000 2.1e-16 7.3e-17
Cephes 수학 라이브러리, 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double ellipticintegrale(const double m);


/*************************************************************************
Incomplete elliptic integral of the second kind

Approximates the integral


               phi
                -
               | |
               |                   2
E(phi_\m)  =    |    sqrt( 1 - m sin t ) dt
               |
             | |
              -
               0

of amplitude phi and modulus m, using the arithmetic -
geometric mean algorithm.

ACCURACY:

Tested at random arguments with phi in [-10, 10] and m in
[0, 1].
                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE     -10,10      150000       3.3e-15     1.4e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1993, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
두 번째 종류의 불완전한 타원 적분
근사치
               파이
                -
               | |
               | 2
E (phi_ \ m) = | sqrt (1 - m sin t) dt
               |
             | |
              -
               0
진폭 φ와 모듈러스 m의 산술 -
기하 평균 알고리즘.
정확성:
[-10, 10]에서 phi로 무작위 인수로 테스트하고
[0, 1].
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE -10,10 150000 3.3e-15 1.4e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1993, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double incompleteellipticintegrale(const double phi, const double m);

/*************************************************************************
Exponential integral Ei(x)

              x
               -     t
              | |   e
   Ei(x) =   -|-   ---  dt .
            | |     t
             -
            -inf

Not defined for x <= 0.
See also expn.c.



ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE       0,100       50000      8.6e-16     1.3e-16

Cephes Math Library Release 2.8:  May, 1999
Copyright 1999 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
지수 적분 Ei (x)
              엑스
               - t
              | | 이자형
   Ei (x) = - | - --- dt.
            | | 티
             -
            -inf
x <= 0에 대해 정의되지 않았습니다.
expn.c 참조
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0,100 50000 8.6e-16 1.3e-16
Cephes 수학 라이브러리 릴리스 2.8 : 1999 년 5 월
Copyright 1999 by Stephen L. Moshier
*************************************************** ********************** * /*/

double exponentialintegralei(const double x);


/*************************************************************************
Exponential integral En(x)

Evaluates the exponential integral

                inf.
                  -
                 | |   -xt
                 |    e
     E (x)  =    |    ----  dt.
      n          |      n
               | |     t
                -
                 1


Both n and x must be nonnegative.

The routine employs either a power series, a continued
fraction, or an asymptotic formula depending on the
relative values of n and x.

ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE      0, 30       10000       1.7e-15     3.6e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
지수 적분 En (x)
지수 적분을 계산합니다.
                inf.
                  -
                 | | -xt
                 | 이자형
     E (x) = | ---- dt.
      n | 엔
               | | 티
                -
                 1
n과 x는 음수가 아니어야합니다.
루틴은 멱급수, 계속
분수, 또는 점근선 수식
n과 x의 상대 값.
정확성:
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE 0, 30 10000 1.7e-15 3.6e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1985, 2000 by Stephen L. Moshier
*************************************************** ********************** * /*/

double exponentialintegralen(const double x, const ae_int_t n);

/*************************************************************************
F distribution

Returns the area from zero to x under the F density
function (also known as Snedcor's density or the
variance ratio density).  This is the density
of x = (u1/df1)/(u2/df2), where u1 and u2 are random
variables having Chi square distributions with df1
and df2 degrees of freedom, respectively.
The incomplete beta integral is used, according to the
formula

P(x) = incbet( df1/2, df2/2, (df1*x/(df2 + df1*x) ).


The arguments a and b are greater than zero, and x is
nonnegative.

ACCURACY:

Tested at random points (a,b,x).

               x     a,b                     Relative error:
arithmetic  domain  domain     # trials      peak         rms
   IEEE      0,1    0,100       100000      9.8e-15     1.7e-15
   IEEE      1,5    0,100       100000      6.5e-15     3.5e-16
   IEEE      0,1    1,10000     100000      2.2e-11     3.3e-12
   IEEE      1,5    1,10000     100000      1.1e-11     1.7e-13

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
F 분포
F 밀도에서 0부터 x까지의 영역을 반환합니다.
기능 (Snedcor의 밀도 또는
분산 비율 밀도). 이것은 밀도입니다.
x = (u1 / df1) / (u2 / df2) 여기서, u1 및 u2는 랜덤
df1을 갖는 카이 제곱 분포를 갖는 변수들
및 df2 자유도를 각각 나타낸다.
불완전한 베타 적분은
공식
P (x) = incbet (df1 / 2, df2 / 2, (df1 * x / (df2 + df1 * x)).
인수 a와 b는 0보다 크고 x는 다음과 같습니다.
비 음수.
정확성:
임의의 지점 (a, b, x)에서 테스트되었습니다.
               xa, b 상대 오류 :
산술 도메인 도메인 # trials peak rms
   IEEE 0,1 0,100 100000 9.8e-15 1.7e-15
   IEEE 1,5,100 100000 6.5e-15 3.5e-16
   IEEE 0,1 1,10000 100000 2.2e-11 3.3e-12
   IEEE 1,5 1,10000 100000 1.1e-11 1.7e-13
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double fdistribution(const ae_int_t a, const ae_int_t b, const double x);


/*************************************************************************
Complemented F distribution

Returns the area from x to infinity under the F density
function (also known as Snedcor's density or the
variance ratio density).


                     inf.
                      -
             1       | |  a-1      b-1
1-P(x)  =  ------    |   t    (1-t)    dt
           B(a,b)  | |
                    -
                     x


The incomplete beta integral is used, according to the
formula

P(x) = incbet( df2/2, df1/2, (df2/(df2 + df1*x) ).


ACCURACY:

Tested at random points (a,b,x) in the indicated intervals.
               x     a,b                     Relative error:
arithmetic  domain  domain     # trials      peak         rms
   IEEE      0,1    1,100       100000      3.7e-14     5.9e-16
   IEEE      1,5    1,100       100000      8.0e-15     1.6e-15
   IEEE      0,1    1,10000     100000      1.8e-11     3.5e-13
   IEEE      1,5    1,10000     100000      2.0e-11     3.0e-12

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
보완 된 F 분포
F 밀도에서 x에서 무한대까지 영역을 반환합니다.
기능 (Snedcor의 밀도 또는
분산 비율 밀도).
                     inf.
                      -
             1 | | a-1 b-1
1-P (x) = ------ | t (1-t) dt
           B (a, b) | |
                    -
                     엑스
불완전한 베타 적분은
공식
P (x) = incbet (df2 / 2, df1 / 2, (df2 / (df2 + df1 * x)).
정확성:
지정된 간격으로 임의의 지점 (a, b, x)에서 테스트합니다.
               xa, b 상대 오류 :
산술 도메인 도메인 # trials peak rms
   IEEE 0,1 1,100 100000 3.7e-14 5.9e-16
   IEEE 1,5 1,100 100000 8.0e-15 1.6e-15
   IEEE 0,1 1,10000 100000 1.8e-11 3.5e-13
   IEEE 1,5 1,10000 100000 2.0e-11 3.0e-12
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double fcdistribution(const ae_int_t a, const ae_int_t b, const double x);


/*************************************************************************
Inverse of complemented F distribution

Finds the F density argument x such that the integral
from x to infinity of the F density is equal to the
given probability p.

This is accomplished using the inverse beta integral
function and the relations

     z = incbi( df2/2, df1/2, p )
     x = df2 (1-z) / (df1 z).

Note: the following relations hold for the inverse of
the uncomplemented F distribution:

     z = incbi( df1/2, df2/2, p )
     x = df2 z / (df1 (1-z)).

ACCURACY:

Tested at random points (a,b,p).

             a,b                     Relative error:
arithmetic  domain     # trials      peak         rms
 For p between .001 and 1:
   IEEE     1,100       100000      8.3e-15     4.7e-16
   IEEE     1,10000     100000      2.1e-11     1.4e-13
 For p between 10^-6 and 10^-3:
   IEEE     1,100        50000      1.3e-12     8.4e-15
   IEEE     1,10000      50000      3.0e-12     4.8e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
보완 된 F 분포의 역
F 밀도 인수 x를 찾아서 적분
x에서 무한의 F 밀도는
주어진 확률 p.
이는 역 베타 적분을 사용하여 수행됩니다.
함수와 관계
     z = incbi (df2 / 2, df1 / 2, p)
     x = df2 (1-z) / (df1z)이다.
주 : 다음의 관계식은
보완되지 않은 F 분포 :
     z = incbi (df1 / 2, df2 / 2, p)
     x = df2z / (df1 (1-z))이다.
정확성:
임의의 지점 (a, b, p)에서 테스트되었습니다.
             a, b 상대 오류 :
산술 도메인 # 시험 피크 rms
 0.001에서 1 사이의 p의 경우 :
   IEEE 1,100 100000 8.3e-15 4.7e-16
   IEEE 1,10000 100000 2.1e-11 1.4e-13
 10 ^ -6에서 10 ^ -3 사이의 p의 경우 :
   IEEE 1,100 50000 1.3e-12 8.4e-15
   IEEE 1,10000 50000 3.0e-12 4.8e-14
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invfdistribution(const ae_int_t a, const ae_int_t b, const double y);

/*************************************************************************
Fresnel integral

Evaluates the Fresnel integrals

          x
          -
         | |
C(x) =   |   cos(pi/2 t**2) dt,
       | |
        -
         0

          x
          -
         | |
S(x) =   |   sin(pi/2 t**2) dt.
       | |
        -
         0


The integrals are evaluated by a power series for x < 1.
For x >= 1 auxiliary functions f(x) and g(x) are employed
such that

C(x) = 0.5 + f(x) sin( pi/2 x**2 ) - g(x) cos( pi/2 x**2 )
S(x) = 0.5 - f(x) cos( pi/2 x**2 ) - g(x) sin( pi/2 x**2 )



ACCURACY:

 Relative error.

Arithmetic  function   domain     # trials      peak         rms
  IEEE       S(x)      0, 10       10000       2.0e-15     3.2e-16
  IEEE       C(x)      0, 10       10000       1.8e-15     3.3e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
프레 넬 일체
프레 넬의 적분을 평가합니다.
          엑스
          -
         | |
C (x) = | cos (pi / 2t ** 2) dt,
       | |
        -
         0
          엑스
          -
         | |
S (x) = | sin (π / 2t ** 2) dt.
       | |
        -
         0
적분 값은 x <1 인 경우 멱급수로 계산됩니다.
x> = 1 인 경우 보조 함수 f (x) 및 g (x)가 사용됩니다
그렇게
C (x) = 0.5 + f (x) sin (π / 2 x ** 2) - g (x) cos (π / 2 x ** 2)
S (x) = 0.5 - f (x) cos (π / 2 x ** 2) - g (x) sin (π / 2 x ** 2)
정확성:
 상대 오류.
산술 함수 도메인 # trials peak rms
  IEEE S (x) 0, 10 10000 2.0e-15 3.2e-16
  IEEE C (x) 0, 10 10000 1.8e-15 3.3e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1989, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

void fresnelintegral(const double x, double &c, double &s);

/*************************************************************************
Calculation of the value of the Hermite polynomial.

Parameters:
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Hermite polynomial Hn at x
*************************************************************************/

/*/ * ************************************************ *************************
Hermite 다항식의 값 계산.
매개 변수 :
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 엘 미트 다항식 Hn의 값
*************************************************** ********************** * /*/

double hermitecalculate(const ae_int_t n, const double x);


/*************************************************************************
Summation of Hermite polynomials using Clenshaw\92s recurrence formula.

This routine calculates
    c[0]*H0(x) + c[1]*H1(x) + ... + c[N]*HN(x)

Parameters:
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Hermite polynomial at x
*************************************************************************/

/*/ * ************************************************ *************************
Clenshaw의 반복 수식을 사용하여 Hermite 다항식의 합계.
이 루틴은
    H0 (x) + ... + c [N] * HN (x)
매개 변수 :
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 엘 미트 다항식의 값
*************************************************** ********************** * /*/

double hermitesum(const real_1d_array &c, const ae_int_t n, const double x);


/*************************************************************************
Representation of Hn as C[0] + C[1]*X + ... + C[N]*X^N

Input parameters:
    N   -   polynomial degree, n>=0

Output parameters:
    C   -   coefficients
*************************************************************************/

/*/ * ************************************************ *************************
Hn의 C [0] + C [1] * X + ... + C [N] * X ^ N
입력 매개 변수 :
    N - 다항식 차수, n> = 0
출력 매개 변수 :
    C - 계수
*************************************************** ********************** * /*/

void hermitecoefficients(const ae_int_t n, real_1d_array &c);

/*************************************************************************
Jacobian Elliptic Functions

Evaluates the Jacobian elliptic functions sn(u|m), cn(u|m),
and dn(u|m) of parameter m between 0 and 1, and real
argument u.

These functions are periodic, with quarter-period on the
real axis equal to the complete elliptic integral
ellpk(1.0-m).

Relation to incomplete elliptic integral:
If u = ellik(phi,m), then sn(u|m) = sin(phi),
and cn(u|m) = cos(phi).  Phi is called the amplitude of u.

Computation is by means of the arithmetic-geometric mean
algorithm, except when m is within 1e-9 of 0 or 1.  In the
latter case with m close to 1, the approximation applies
only for phi < pi/2.

ACCURACY:

Tested at random points with u between 0 and 10, m between
0 and 1.

           Absolute error (* = relative error):
arithmetic   function   # trials      peak         rms
   IEEE      phi         10000       9.2e-16*    1.4e-16*
   IEEE      sn          50000       4.1e-15     4.6e-16
   IEEE      cn          40000       3.6e-15     4.4e-16
   IEEE      dn          10000       1.3e-12     1.8e-14

 Peak error observed in consistency check using addition
theorem for sn(u+v) was 4e-16 (absolute).  Also tested by
the above relation to the incomplete elliptic integral.
Accuracy deteriorates when u is large.

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
자 코비안 타원 함수
자 코비안 타원 함수 sn (u | m), cn (u | m)을 평가합니다.
0과 1 사이의 매개 변수 m의 dn (u | m)과 실제의
인수 u.
이 함수는 주기적으로 4 분의 1주기를
완전한 타원 적분과 같은 실수 축
ellpk (1.0-m).
불완전 타원 적분과의 관계 :
만약 u = ellik (phi, m)이라면 sn (u | m) = sin (phi),
및 cn (u | m) = cos (φ)이다. Phi는 u의 진폭이라고합니다.
계산은 산술 기하 평균에 의한 것입니다.
알고리즘을 사용합니다. 단, m이 1e-9 또는 0 인 경우는 예외입니다.
m이 1에 가까운 후자의 경우, 근사값이 적용됩니다.
단 phi <pi / 2 인 경우.
정확성:
임의의 점에서 0에서 10 사이의 u로 테스트합니다.
0 및 1이다.
           절대 오류 (* = 상대 오류) :
산술 기능 # 시도 피크 RMS
   IEEE phi 10000 9.2e-16 * 1.4e-16 *
   IEEE sn 50000 4.1e-15 4.6e-16
   IEEE cn 40000 3.6e-15 4.4e-16
   IEEE dn 10000 1.3e-12 1.8e-14
 추가를 사용하여 일관성 검사에서 관찰 된 피크 오류
sn (u + v)에 대한 정리는 4e-16 (절대)이었다. 또한에 의해 테스트
위의 불완전 타원 적분과의 관계.
u가 클 때 정확도가 떨어집니다.
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

void jacobianellipticfunctions(const double u, const double m, double &sn, double &cn, double &dn, double &ph);

/*************************************************************************
Calculation of the value of the Laguerre polynomial.

Parameters:
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Laguerre polynomial Ln at x
*************************************************************************/

/*/ * ************************************************ *************************
Laguerre 다항식의 값 계산.
매개 변수 :
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 라게르 다항식 Ln의 값
*************************************************** ********************** * /*/

double laguerrecalculate(const ae_int_t n, const double x);


/*************************************************************************
Summation of Laguerre polynomials using Clenshaw\92s recurrence formula.

This routine calculates c[0]*L0(x) + c[1]*L1(x) + ... + c[N]*LN(x)

Parameters:
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Laguerre polynomial at x
*************************************************************************/

/*/ * ************************************************ *************************
Clenshaw의 회귀 공식을 사용하여 라게르 다항식의 합.
이 루틴은 c [0] * L0 (x) + c [1] * L1 (x) + ... + c [N] * LN (x)
매개 변수 :
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 라게르 다항식의 값
*************************************************** ********************** * /*/

double laguerresum(const real_1d_array &c, const ae_int_t n, const double x);


/*************************************************************************
Representation of Ln as C[0] + C[1]*X + ... + C[N]*X^N

Input parameters:
    N   -   polynomial degree, n>=0

Output parameters:
    C   -   coefficients
*************************************************************************/

/*/ * ************************************************ *************************
C [0] + C [1] * X + ... + C [N] * X ^ N로서의 Ln의 표현
입력 매개 변수 :
    N - 다항식 차수, n> = 0
출력 매개 변수 :
    C - 계수
*************************************************** ********************** * /*/

void laguerrecoefficients(const ae_int_t n, real_1d_array &c);

/*************************************************************************
Calculation of the value of the Legendre polynomial Pn.

Parameters:
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Legendre polynomial Pn at x
*************************************************************************/

/*/ * ************************************************ *************************
Legendre 다항식 Pn의 값 계산.
매개 변수 :
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 Legendre 다항식 Pn의 값
*************************************************** ********************** * /*/

double legendrecalculate(const ae_int_t n, const double x);


/*************************************************************************
Summation of Legendre polynomials using Clenshaw\92s recurrence formula.

This routine calculates
    c[0]*P0(x) + c[1]*P1(x) + ... + c[N]*PN(x)

Parameters:
    n   -   degree, n>=0
    x   -   argument

Result:
    the value of the Legendre polynomial at x
*************************************************************************/

/*/ * ************************************************ *************************
Clenshaw의 반복 수식을 사용하여 Legendre 다항식의 합계.
이 루틴은
    p (x) + ... c [N] * PN (x)
매개 변수 :
    n - degree, n> = 0
    x - 인수
결과:
    x에서의 Legendre 다항식의 값
*************************************************** ********************** * /*/

double legendresum(const real_1d_array &c, const ae_int_t n, const double x);


/*************************************************************************
Representation of Pn as C[0] + C[1]*X + ... + C[N]*X^N

Input parameters:
    N   -   polynomial degree, n>=0

Output parameters:
    C   -   coefficients
*************************************************************************/

/*/ * ************************************************ *************************
C [0] + C [1] * X + ... + C [N] * X ^ N 인 Pn의 표현
입력 매개 변수 :
    N - 다항식 차수, n> = 0
출력 매개 변수 :
    C - 계수
*************************************************** ********************** * /*/

void legendrecoefficients(const ae_int_t n, real_1d_array &c);

/*************************************************************************
Poisson distribution

Returns the sum of the first k+1 terms of the Poisson
distribution:

  k         j
  --   -m  m
  >   e    --
  --       j!
 j=0

The terms are not summed directly; instead the incomplete
gamma integral is employed, according to the relation

y = pdtr( k, m ) = igamc( k+1, m ).

The arguments must both be positive.
ACCURACY:

See incomplete gamma function

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
푸 아송 분포
포아송의 첫 번째 k + 1 항의 합계를 구합니다.
분포:
  kj
  - -mm
  > e -
  - j!
 j = 0
용어는 직접적으로 합산되지 않습니다. 대신 불완전
감마 적분은 관계식
y = pdtr (k, m) = igamc (k + 1, m).
논쟁은 모두 긍정적이어야합니다.
정확성:
불완전 감마 함수보기
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double poissondistribution(const ae_int_t k, const double m);


/*************************************************************************
Complemented Poisson distribution

Returns the sum of the terms k+1 to infinity of the Poisson
distribution:

 inf.       j
  --   -m  m
  >   e    --
  --       j!
 j=k+1

The terms are not summed directly; instead the incomplete
gamma integral is employed, according to the formula

y = pdtrc( k, m ) = igam( k+1, m ).

The arguments must both be positive.

ACCURACY:

See incomplete gamma function

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
Poisson 분포 보완
포아송의 k + 1에서 무한대까지의 항을 구합니다.
분포:
inf. j
  - -mm
  > e -
  - j!
 j = k + 1
용어는 직접적으로 합산되지 않습니다. 대신 불완전
감마 적분은 식
y = pdtrc (k, m) = igam (k + 1, m).
논쟁은 모두 긍정적이어야합니다.
정확성:
불완전 감마 함수보기
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double poissoncdistribution(const ae_int_t k, const double m);


/*************************************************************************
Inverse Poisson distribution

Finds the Poisson variable x such that the integral
from 0 to x of the Poisson density is equal to the
given probability y.

This is accomplished using the inverse gamma integral
function and the relation

   m = igami( k+1, y ).

ACCURACY:

See inverse incomplete gamma function

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
역 푸 아송 분포
포아송 변수 x를 찾아서 적분
포아송 밀도의 0에서 x까지는 포아송 밀도의
주어진 확률 y.
이것은 역 감마 적분을 사용하여 수행됩니다
함수와 관계
   m = igami (k + 1, y).
정확성:
역 불완전 감마 함수보기
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invpoissondistribution(const ae_int_t k, const double y);

/*************************************************************************
Psi (digamma) function

             d      -
  psi(x)  =  -- ln | (x)
             dx

is the logarithmic derivative of the gamma function.
For integer x,
                  n-1
                   -
psi(n) = -EUL  +   >  1/k.
                   -
                  k=1

This formula is used for 0 < n <= 10.  If x is negative, it
is transformed to a positive argument by the reflection
formula  psi(1-x) = psi(x) + pi cot(pi x).
For general positive x, the argument is made greater than 10
using the recurrence  psi(x+1) = psi(x) + 1/x.
Then the following asymptotic expansion is applied:

                          inf.   B
                           -      2k
psi(x) = log(x) - 1/2x -   >   -------
                           -        2k
                          k=1   2k x

where the B2k are Bernoulli numbers.

ACCURACY:
   Relative error (except absolute when |psi| < 1):
arithmetic   domain     # trials      peak         rms
   IEEE      0,30        30000       1.3e-15     1.4e-16
   IEEE      -30,0       40000       1.5e-15     2.2e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1992, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
Psi (digamma) 기능
             d -
  psi (x) = - ln | (엑스)
             DX
감마 함수의 로그 파생입니다.
정수 x의 경우,
                  n-1
                   -
psi (n) = -EUL +> 1 / k.
                   -
                  k = 1
이 수식은 0 <n <= 10에 사용됩니다. x가 음수이면
반사에 의해 긍정적 인 주장으로 변형된다.
공식 psi (1-x) = psi (x) + pico (pi x).
일반적인 양수 x의 경우 인수가 10보다 커야합니다.
반복 psi (x + 1) = psi (x) + 1 / x를 사용하여.
다음의 점근 적 확장이 적용됩니다.
                          inf. 비
                           - 2k
psi (x) = log (x) - 1 / 2x -> -------
                           - 2k
                          k = 1 2k x
여기서 B2k는 베르누이 수이다.
정확성:
   상대 오차 (| psi | <1 일 때 절대 값 제외) :
산술 도메인 # 시험 피크 rms
   IEEE 0,30 30000 1.3e-15 1.4e-16
   IEEE-30,0400 1.5e-15 2.2e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1992, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double psi(const double x);

/*************************************************************************
Student's t distribution

Computes the integral from minus infinity to t of the Student
t distribution with integer k > 0 degrees of freedom:

                                     t
                                     -
                                    | |
             -                      |         2   -(k+1)/2
            | ( (k+1)/2 )           |  (     x   )
      ----------------------        |  ( 1 + --- )        dx
                    -               |  (      k  )
      sqrt( k pi ) | ( k/2 )        |
                                  | |
                                   -
                                  -inf.

Relation to incomplete beta integral:

       1 - stdtr(k,t) = 0.5 * incbet( k/2, 1/2, z )
where
       z = k/(k + t**2).

For t < -2, this is the method of computation.  For higher t,
a direct method is derived from integration by parts.
Since the function is symmetric about t=0, the area under the
right tail of the density is found by calling the function
with -t instead of t.

ACCURACY:

Tested at random 1 <= k <= 25.  The "domain" refers to t.
                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE     -100,-2      50000       5.9e-15     1.4e-15
   IEEE     -2,100      500000       2.7e-15     4.9e-17

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
학생 분포
학생의 마이너스 무한대에서 t 번째까지의 적분을 계산합니다.
정수 k> 0 자유도를 갖는 t 분포 :
                                     티
                                     -
                                    | |
             - | 2 - (k + 1) / 2
            | ((k + 1) / 2) | (x)
      ---------------------- | (1 + ---) dx
                    - | (k)
      sqrt (kπ) | (k / 2) |
                                  | |
                                   -
                                  -inf.
불완전한 베타 적분과의 관계 :
       1 - stdtr (k, t) = 0.5 * incbet (k / 2, 1 / 2, z)
어디에
       z = k / (k + t ** 2)이다.
t <-2 인 경우, 이것은 계산 방법입니다. 높은 t의 경우,
직접적인 방법은 부품에 의한 통합으로부터 파생됩니다.
이 함수는 t = 0에 대해 대칭이므로,
함수를 호출하여 밀도의 오른쪽 꼬리를 찾습니다.
t 대신에 -t를 붙인다.
정확성:
랜덤 1 <= k <= 25로 테스트되었습니다. "도메인"은 t를 나타냅니다.
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE -100, -2 50000 5.9e-15 1.4e-15
   IEEE -2,100 500000 2.7e-15 4.9e-17
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double studenttdistribution(const ae_int_t k, const double t);


/*************************************************************************
Functional inverse of Student's t distribution

Given probability p, finds the argument t such that stdtr(k,t)
is equal to p.

ACCURACY:

Tested at random 1 <= k <= 100.  The "domain" refers to p:
                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE    .001,.999     25000       5.7e-15     8.0e-16
   IEEE    10^-6,.001    25000       2.0e-12     2.9e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
학생의 t 분포의 함수 역함수
주어진 확률 p는 stdtr (k, t)
p와 같다.
정확성:
랜덤 1 <= k <= 100에서 테스트되었습니다. "도메인"은 p :
                     상대 오류 :
산술 도메인 # 시험 피크 rms
   IEEE .001, .999 25000 5.7e-15 8.0e-16
   IEEE 10 ^ -6, .001 25000 2.0e-12 2.9e-14
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 1995, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

double invstudenttdistribution(const ae_int_t k, const double p);

/*************************************************************************
Sine and cosine integrals

Evaluates the integrals

                         x
                         -
                        |  cos t - 1
  Ci(x) = eul + ln x +  |  --------- dt,
                        |      t
                       -
                        0
            x
            -
           |  sin t
  Si(x) =  |  ----- dt
           |    t
          -
           0

where eul = 0.57721566490153286061 is Euler's constant.
The integrals are approximated by rational functions.
For x > 8 auxiliary functions f(x) and g(x) are employed
such that

Ci(x) = f(x) sin(x) - g(x) cos(x)
Si(x) = pi/2 - f(x) cos(x) - g(x) sin(x)


ACCURACY:
   Test interval = [0,50].
Absolute error, except relative when > 1:
arithmetic   function   # trials      peak         rms
   IEEE        Si        30000       4.4e-16     7.3e-17
   IEEE        Ci        30000       6.9e-16     5.1e-17

Cephes Math Library Release 2.1:  January, 1989
Copyright 1984, 1987, 1989 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
사인 및 코사인 정수
적분을 평가합니다.
                         엑스
                         -
                        | cos t - 1
  Ci (x) = eul + ln x + | --------- dt,
                        | 티
                       -
                        0
            엑스
            -
           | 죄악
  Si (x) = | ----- dt
           | 티
          -
           0
여기서 eul = 0.57721566490153286061은 오일러의 상수입니다.
적분은 합리적인 함수로 근사됩니다.
x> 8 보조 함수 f (x) 및 g (x)에 대해
그렇게
Ci (x) = f (x) sin (x) - g (x) cos
x (x) = π / 2 - f (x) cos (x) - g (x) sin
정확성:
   테스트 간격 = [0,50].
상대적 오류를 제외한 절대 오류 (> 1 :
산술 기능 # 시도 피크 RMS
   IEEE Si 30000 4.4e-16 7.3e-17
   IEEE Ci 30000 6.9e-16 5.1e-17
Cephes 수학 라이브러리 릴리스 2.1 : 1989 년 1 월
Copyright 1984, 1987, 1989 Stephen L. Moshier
*************************************************** ********************** * /*/

void sinecosineintegrals(const double x, double &si, double &ci);


/*************************************************************************
Hyperbolic sine and cosine integrals

Approximates the integrals

                           x
                           -
                          | |   cosh t - 1
  Chi(x) = eul + ln x +   |    -----------  dt,
                        | |          t
                         -
                         0

              x
              -
             | |  sinh t
  Shi(x) =   |    ------  dt
           | |       t
            -
            0

where eul = 0.57721566490153286061 is Euler's constant.
The integrals are evaluated by power series for x < 8
and by Chebyshev expansions for x between 8 and 88.
For large x, both functions approach exp(x)/2x.
Arguments greater than 88 in magnitude return MAXNUM.


ACCURACY:

Test interval 0 to 88.
                     Relative error:
arithmetic   function  # trials      peak         rms
   IEEE         Shi      30000       6.9e-16     1.6e-16
       Absolute error, except relative when |Chi| > 1:
   IEEE         Chi      30000       8.4e-16     1.4e-16

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*************************************************************************/

/*/ * ************************************************ *************************
쌍곡선 사인 및 코사인 적분
적분법 근사
                           엑스
                           -
                          | | 코쉬 티 - 1
  Chi (x) = eul + ln x + | ----------- dt,
                        | | 티
                         -
                         0
              엑스
              -
             | | 죄가 없다
  Shi (x) = | ------ dt
           | | 티
            -
            0
여기서 eul = 0.57721566490153286061은 오일러의 상수입니다.
적분은 x <8 인 경우 멱급수로 평가됩니다
그리고 Chebyshev 확장에 의해 x와 8에서 88 사이.
큰 x의 경우 두 함수 모두 exp (x) / 2x에 접근합니다.
크기가 88보다 큰 인수는 MAXNUM을 리턴합니다.
정확성:
테스트 간격은 0에서 88까지입니다.
                     상대 오류 :
산술 기능 # 시도 피크 RMS
   IEEE Shi 30000 6.9e-16 1.6e-16
       절대 오류 | Chi | > 1 :
   IEEE Chi 30000 8.4e-16 1.4e-16
Cephes 수학 라이브러리 릴리스 2.8 : 2000 년 6 월
Copyright 1984, 1987, 2000 Stephen L. Moshier
*************************************************** ********************** * /*/

void hyperbolicsinecosineintegrals(const double x, double &shi, double &chi);
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
double gammafunction(double x, ae_state *_state);
double lngamma(double x, double* sgngam, ae_state *_state);
double errorfunction(double x, ae_state *_state);
double errorfunctionc(double x, ae_state *_state);
double normaldistribution(double x, ae_state *_state);
double inverf(double e, ae_state *_state);
double invnormaldistribution(double y0, ae_state *_state);
double incompletegamma(double a, double x, ae_state *_state);
double incompletegammac(double a, double x, ae_state *_state);
double invincompletegammac(double a, double y0, ae_state *_state);
void airy(double x,
     double* ai,
     double* aip,
     double* bi,
     double* bip,
     ae_state *_state);
double besselj0(double x, ae_state *_state);
double besselj1(double x, ae_state *_state);
double besseljn(ae_int_t n, double x, ae_state *_state);
double bessely0(double x, ae_state *_state);
double bessely1(double x, ae_state *_state);
double besselyn(ae_int_t n, double x, ae_state *_state);
double besseli0(double x, ae_state *_state);
double besseli1(double x, ae_state *_state);
double besselk0(double x, ae_state *_state);
double besselk1(double x, ae_state *_state);
double besselkn(ae_int_t nn, double x, ae_state *_state);
double beta(double a, double b, ae_state *_state);
double incompletebeta(double a, double b, double x, ae_state *_state);
double invincompletebeta(double a, double b, double y, ae_state *_state);
double binomialdistribution(ae_int_t k,
     ae_int_t n,
     double p,
     ae_state *_state);
double binomialcdistribution(ae_int_t k,
     ae_int_t n,
     double p,
     ae_state *_state);
double invbinomialdistribution(ae_int_t k,
     ae_int_t n,
     double y,
     ae_state *_state);
double chebyshevcalculate(ae_int_t r,
     ae_int_t n,
     double x,
     ae_state *_state);
double chebyshevsum(/* Real    */ ae_vector* c,
     ae_int_t r,
     ae_int_t n,
     double x,
     ae_state *_state);
void chebyshevcoefficients(ae_int_t n,
     /* Real    */ ae_vector* c,
     ae_state *_state);
void fromchebyshev(/* Real    */ ae_vector* a,
     ae_int_t n,
     /* Real    */ ae_vector* b,
     ae_state *_state);
double chisquaredistribution(double v, double x, ae_state *_state);
double chisquarecdistribution(double v, double x, ae_state *_state);
double invchisquaredistribution(double v, double y, ae_state *_state);
double dawsonintegral(double x, ae_state *_state);
double ellipticintegralk(double m, ae_state *_state);
double ellipticintegralkhighprecision(double m1, ae_state *_state);
double incompleteellipticintegralk(double phi, double m, ae_state *_state);
double ellipticintegrale(double m, ae_state *_state);
double incompleteellipticintegrale(double phi, double m, ae_state *_state);
double exponentialintegralei(double x, ae_state *_state);
double exponentialintegralen(double x, ae_int_t n, ae_state *_state);
double fdistribution(ae_int_t a, ae_int_t b, double x, ae_state *_state);
double fcdistribution(ae_int_t a, ae_int_t b, double x, ae_state *_state);
double invfdistribution(ae_int_t a,
     ae_int_t b,
     double y,
     ae_state *_state);
void fresnelintegral(double x, double* c, double* s, ae_state *_state);
double hermitecalculate(ae_int_t n, double x, ae_state *_state);
double hermitesum(/* Real    */ ae_vector* c,
     ae_int_t n,
     double x,
     ae_state *_state);
void hermitecoefficients(ae_int_t n,
     /* Real    */ ae_vector* c,
     ae_state *_state);
void jacobianellipticfunctions(double u,
     double m,
     double* sn,
     double* cn,
     double* dn,
     double* ph,
     ae_state *_state);
double laguerrecalculate(ae_int_t n, double x, ae_state *_state);
double laguerresum(/* Real    */ ae_vector* c,
     ae_int_t n,
     double x,
     ae_state *_state);
void laguerrecoefficients(ae_int_t n,
     /* Real    */ ae_vector* c,
     ae_state *_state);
double legendrecalculate(ae_int_t n, double x, ae_state *_state);
double legendresum(/* Real    */ ae_vector* c,
     ae_int_t n,
     double x,
     ae_state *_state);
void legendrecoefficients(ae_int_t n,
     /* Real    */ ae_vector* c,
     ae_state *_state);
double poissondistribution(ae_int_t k, double m, ae_state *_state);
double poissoncdistribution(ae_int_t k, double m, ae_state *_state);
double invpoissondistribution(ae_int_t k, double y, ae_state *_state);
double psi(double x, ae_state *_state);
double studenttdistribution(ae_int_t k, double t, ae_state *_state);
double invstudenttdistribution(ae_int_t k, double p, ae_state *_state);
void sinecosineintegrals(double x,
     double* si,
     double* ci,
     ae_state *_state);
void hyperbolicsinecosineintegrals(double x,
     double* shi,
     double* chi,
     ae_state *_state);

}
#endif

