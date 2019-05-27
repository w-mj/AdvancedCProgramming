
#ifndef _TYPES_H_
#define _TYPES_H_


typedef signed char _i8;
typedef unsigned char _u8;
typedef signed short _i16;
typedef unsigned short _u16;
typedef signed int _i32;
typedef unsigned int _u32;
typedef _u32 _I;
typedef _u8 _c;
typedef _c* _s;

#define _getva_T_(P, params, _T_) do {P = (_T_)va_arg(params, _T_); }while(0)
#define _getva_S(s, params) _getva_T_(s, params, _s)
#define _getva_I(s, params) _getva_T_(s, params, _I)

#endif