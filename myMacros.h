#pragma once
#ifndef myMACROS_H
  #define myMACROS_H

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x)       DO_PRAGMA(message ("*** TODO *** " #x))
#define MESSAGE(x)    DO_PRAGMA(message (#x))


#define WITHIN(N,L,H)       ((N) >= (L) && (N) <= (H))
#define NUMERIC(a)          WITHIN(a, '0', '9')
#define DECIMAL(a)          (NUMERIC(a) || a == '.')
#define NUMERIC_SIGNED(a)   (NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL_SIGNED(a)   (DECIMAL(a) || (a) == '-' || (a) == '+')
#define COUNT(a)            (sizeof(a)/sizeof(*a))
#define ZERO(a)             memset(a,0,sizeof(a))

// 01234567890
// Jan 11 2020   -->  11 Jan 2020
#define BUILDDATE (char const[]){ __DATE__[4], __DATE__[5], ' ', __DATE__[0] , __DATE__[1], __DATE__[2] ,' ', __DATE__ [7], __DATE__ [8], __DATE__ [9], __DATE__ [10],'\0' }

//siehe auch  https://www.mikrocontroller.net/topic/315552
#endif
