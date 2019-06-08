#ifndef _wmj_buf_H_
#define _wmj_buf_H_
/**
 * File: wmj_buf.h
 * Time: 2019年06月08日 星期六 13时01分14秒
 * Author: wmj
 * Comment: 
 **/
#include "wmj_types.h"

typedef struct {
    _I size;
    _u8 pd[];
}_BUFX;

typedef _BUFX *_PX;

_PX _alloc(_I size);

#endif
