#include <stdio.h>
#include <stdlib.h>
#include "wmj_string.h"
#include "wmj_delog.h"

/**
 * File: test_wmj_string.c
 * Time: 2019年06月07日 星期五 22时22分43秒
 * Author: wmj
 * Comment: 模块wmj_string的测试程序
 **/
int main(int argc, char* argv[]) {
    char s1[128] = "errer", *s2 = "Hello world";
    _ss(s1);
    _ss(s2);
    strxcpy(s1, s2, 128);
    _ss(s1);
    return 0;
}

