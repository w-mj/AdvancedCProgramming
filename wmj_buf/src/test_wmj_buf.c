/**
 * File: test_wmj_buf.c
 * Time: 2019年06月08日 星期六 13时01分14秒
 * Author: wmj
 * Comment: 模块wmj_buf的测试程序
 **/

#include <stdio.h>
#include <stdlib.h>
#include "wmj_buf.h"
#include "wmj_types.h"
#include "wmj_defines.h"
#include "wmj_delog.h"
#include "assert.h"

#define PARAM_NUM 2
void set_u32(void* p, _I size) {
    _I num = size / sizeof(_u32);
    _u32 *p32 = (_u32*)p;

    while (num) {
        num--;
        _sp(p32[num]);
        _si(num);
        p32[num] = num;
    }
    _sa(p, size);
}

void set_u8(void *p, _I size) {
    _I num = size / sizeof(_u8);
    _u8 *p8 = (_u8*)p;

    while (num) {
        num--;
        p8[num] = num;
    }
    _sa(p, size);
}

void *test_create(_I num) {
    void *pre = 0;
    _error_gs(num == 0, _test_create_END, "size is zero");
    pre = malloc(num);
    _error_g(pre == NULL, _test_create_END);
_test_create_END:
    return pre;
}

void test_free(void **p) {
    if (*p != NULL) {
        free(*p);
        *p = NULL;
    }
}
int main(int argc, char* argv[]) {
    void *p = 0;
    _I num;
    _I i = 0;
    _chkargc(2, "must have 2 params.", _main_END);
    p = test_create(num = atoi(argv[1]));
    if (p) {
        set_u32(p + 1, num - 1);
        set_u8(p, num);
    }
_main_END:
    test_free(&p);
    return 0;
}

