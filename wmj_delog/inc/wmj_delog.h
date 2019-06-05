#ifndef _WMJ_DELOG_H_
#define _WMJ_DELOG_H_

// #include <stdarg.h>
#include "wmj_types.h"
#include "wmj_info.h"
#define _POS_INFOBITS (_I)1
#define _NPOS_INFOBITS (~_POS_INFOBITS)
enum {
    _INIT_INFO_DELOG = 0,
    _LOG_INFO_DELOG = 2,
    _DBG_INFO_DELOG = 4,
    _MAX_INFO_DELOG,
};
#define _pos_delog(type, ...) _wmj_delog((type)|_POS_INFOBITS, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define _Npos_delog(type, ...) _wmj_delog((type)&_NPOS_INFOBITS, __VA_ARGS__)
// #define init_delog() do{_Npos_delog(_INIT_INFO_DELOG, 0);} while(0)
#define init_delog(dbgname, logname) do{_Npos_delog(_INIT_INFO_DELOG, dbgname, logname);}while(0)
#define _debug_info(expstr, m, ...) _pos_delog(_DBG_INFO_DELOG, m, expstr, __VA_ARGS__)
#define _log_info(...) _Npos_delog(_LOG_INFO_DELOG, __VA_ARGS__)
#define _reg() _log_info("[%s] run!", __func__)

#define _sa(exp, len) _debug_info(mkstr(exp), "a", exp, len)
#define _sI(exp) _debug_info(mkstr(exp), "I", exp)
#define _sx(exp) _debug_info(mkstr(exp), "x", (_u32)exp)
#define _sf(exp) _debug_info(mkstr(exp), "f", (double)exp)
#define _ss(exp) _debug_info(mkstr(exp), "s", (_s)exp)
#define _sp(exp) _debug_info(mkstr(exp), "p", &(exp))
#define _sc(exp) _debug_info(mkstr(exp), "c", (_i32)(exp))
#define _si(exp) _debug_info(mkstr(exp), "d", (_i32)exp)
#define _pos() _debug_info("", "n", "")

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define _error(exp, escape_label, ...) do {\
    if (exp) {\
        _debug_info(mkstr(exp), "e", __VA_ARGS__);\
        goto escape_label;\
    }\
} while(0)

#define _bug(exp) do {\
    if (exp) {\
        _debug_info(mkstr(exp), "e", "found bug!");\
        exit(2);\
    }\
} while(0);


void _wmj_delog(_I type, ...);

/***
 * 将p所指位置连续len个字节的单元的值取出，以16进制放在str中，size为str的最大长度
 */
_I print_bin(_s str, _I size, _u8 *p, _I len);

#endif