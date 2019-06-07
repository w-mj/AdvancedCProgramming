/**
 * File: wmj_string.c
 * Time: 2019年06月07日 星期五 22时22分43秒
 * Author: wmj
 * Comment: 
 **/
#include "wmj_string.h"


_I strxcpy(_s dst, _s src, _I n) {
    _I i = 0;
    if (n == 0)
        return 0;
    n--;
    while (i < n && src[i]) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
    return i;
}