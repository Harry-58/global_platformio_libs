#pragma once
#ifndef myMACROS_H
  #define myMACROS_H

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

//https://www.mikrocontroller.net/topic/315552
#define COMPILE_HOUR          (((__TIME__[0]-'0')*10) + (__TIME__[1]-'0'))
#define COMPILE_MINUTE        (((__TIME__[3]-'0')*10) + (__TIME__[4]-'0'))
#define COMPILE_SECOND        (((__TIME__[6]-'0')*10) + (__TIME__[7]-'0'))
#define COMPILE_YEAR          ((((__DATE__ [7]-'0')*10+(__DATE__[8]-'0'))*10+(__DATE__ [9]-'0'))*10+(__DATE__ [10]-'0'))
#define COMPILE_MONTH         ((  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 0 : 5)   \
                                : __DATE__ [2] == 'b' ? 1                               \
                                : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ?  2 : 3)  \
                                : __DATE__ [2] == 'y' ? 4                               \
                                : __DATE__ [2] == 'l' ? 6                               \
                                : __DATE__ [2] == 'g' ? 7                               \
                                : __DATE__ [2] == 'p' ? 8                               \
                                : __DATE__ [2] == 't' ? 9                               \
                                : __DATE__ [2] == 'v' ? 10 : 11) +1)
#define COMPILE_DAY           ((__DATE__ [4]==' ' ? 0 : __DATE__  [4]-'0')*10+(__DATE__[5]-'0'))

#define MONAT \
(__DATE__[2] == 'b' ? "2" : \
(__DATE__[2] == 'y' ? "5" :\
(__DATE__[2] == 'l' ? "7" :\
(__DATE__[2] == 'g' ? "8" :\
(__DATE__[2] == 'p' ? "9" :\
(__DATE__[2] == 't' ? "10" :\
(__DATE__[2] == 'v' ? "11" :\
(__DATE__[2] == 'c' ? "12" :\
(__DATE__[2] == 'n' ?     \
(__DATE__[1] == 'a' ? "1" : "6") :\
(__DATE__[1] == 'a' ? "3" : "4"))))))))))

#define atoa(x) #x

#define COMPILEDATE1    (char const[]){__DATE__ [4],__DATE__[5],' ',MONAT,' ', __DATE__ [7], __DATE__ [8], __DATE__ [9], __DATE__ [10] ,'\0' }

#define COMPILEDATE2    __DATE__ [4],__DATE__[5],' ',MONAT,' ', __DATE__ [7], __DATE__ [8], __DATE__ [9], __DATE__ [10]


#endif