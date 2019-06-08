/**
 * File: wmj_buf.c
 * Time: 2019年06月08日 星期六 13时01分14秒
 * Author: wmj
 * Comment: 
 **/
#include <stdlib.h>
#include "wmj_buf.h"
#include "wmj_delog.h"


_PX _alloc(_I size) {
    _PX p = NULL;
    p = malloc(sizeof(_BUFX) + size * sizeof(_u8));
    _error_g(p == NULL, _alloc_END);
    p->size = size;
_alloc_END:
    return p;
}
