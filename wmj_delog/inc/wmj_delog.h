#ifndef _WMJ_DELOG_H_
#define _WMJ_DELOG_H_

// #include <stdarg.h>
#include "wmj_types.h"
#define _POS_INFOBITS (_I)1
#define _NPOS_INFOBITS (~_POS_INFOBITS)
enum {
    _INIT_INFO_DELOG = 0,
    _MAX_INFO_DELOG,
};
#define _pos_delog(type, ...) _wmj_delog((type)|_POS_INFOBITS, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define _Npos_delog(type, ...) _wmj_delog((type)&_NPOS_INFOBITS, __VA_ARGS__)
#define init_delog() do{_Npos_delog(_INIT_INFO_DELOG, 0);} while(0)
void _wmj_delog(_I type, ...);

#endif