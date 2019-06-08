/**
 * File: test_wmj_vector.c
 * Time: 2019年06月08日 星期六 16时11分04秒
 * Author: wmj
 * Comment: 模块wmj_vector的测试程序
 **/
#include <stdio.h>
#include <stdlib.h>
#include "wmj_types.h"
#include "wmj_defines.h"
#include "wmj_delog.h"

#include "wmj_vector.h"
defineVector(int);

int main(int argc, char* argv[]) {
    Vector(int) vv = CreateVector(int);
    // puts("create vector");

    vec_push_back(vv, 1);
    vec_push_back(vv, 2);
    vec_push_back(vv, 4);
    vec_push_back(vv, 3);
    
    _si(vec_index(vv, 0));
    _si(vec_index(vv, 1));
    _si(vec_index(vv, 3));
    _si(vec_index(vv, 2));

    //_vec_print_inner(vv);

_main_END:
    DestroyVector(vv);
    return 0;
}

