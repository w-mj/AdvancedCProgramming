#ifndef _WMJ_DELOG_H_
#define _WMJ_DELOG_H_

// #include <stdarg.h>
#include "wmj_types.h"
#define _POS_INFOBITS (_I)1
#define _NPOS_INFOBITS (~_POS_INFOBITS)
enum {
    _INIT_INFO_DELOG = 0,
    _DBG_INFO_DELOG,
    _MAX_INFO_DELOG,
};
#define _pos_delog(type, ...) _wmj_delog((type)|_POS_INFOBITS, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define _Npos_delog(type, ...) _wmj_delog((type)&_NPOS_INFOBITS, __VA_ARGS__)
// #define init_delog() do{_Npos_delog(_INIT_INFO_DELOG, 0);} while(0)
#define init_delog(dbgname, logname) do{_Npos_delog(_INIT_INFO_DELOG, dbgname, logname);}while(0)
#define _debug_info(expstr, m, ...) _pos_delog(_DBG_INFO_DELOG, m, expstr, __VA_ARGS__)
#define _sa(exp, len) _debug_info(mkstr(exp), "a", exp, len)

void _wmj_delog(_I type, ...);

/***
 * 将p所指位置连续len个字节的单元的值取出，以16进制放在str中，size为str的最大长度
 */
_I print_bin(_s str, _I size, _u8 *p, _I len);

#endif