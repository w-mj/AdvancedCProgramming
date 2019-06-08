#ifndef _wmj_vector_H_
#define _wmj_vector_H_
/**
 * File: wmj_vector.h
 * Time: 2019年06月08日 星期六 16时11分04秒
 * Author: wmj
 * Comment: 
 **/
#include "wmj_types.h"
#include "wmj_delog.h"

int vector_err(int condition, char *msg, const char* file, const char *func, int line) {
    if (condition) {
        printf("[%s]<%s>(%d): %s\n", file, func, line, msg);
        exit(-1);
    }
    return 1;
}

#define is_out_of_range(x) vector_err(x, "vector index out of range.", __FILE__, __func__, __LINE__)

typedef struct {} XJBCSYDJGT;

#define defineVector(T) \
typedef struct {\
    _I _ele_size;\
    _I _max_ele_num;\
    _I _space_size;\
    _I _start_index;\
    _I _end_index;\
    T _data[];\
} _WMJ_VECTOR_STRUCT___##T; \
typedef _WMJ_VECTOR_STRUCT___##T *_WMJ_VECTOR_P_STRUCT___##T;\
_WMJ_VECTOR_P_STRUCT___##T vec_##T##_create() {\
    _WMJ_VECTOR_P_STRUCT___##T p;\
    p = malloc(sizeof(_WMJ_VECTOR_STRUCT___##T));\
    p->_ele_size=sizeof(T);\
    p->_space_size=0;\
    p->_start_index=0;\
    p->_max_ele_num=0;\
    p->_end_index=0;\
    if (__wmJ_vector_struct_size__ == 0) {\
       __wmJ_vector_struct_size__ = sizeof(_WMJ_VECTOR_STRUCT___XJBCSYDJGT) - sizeof(XJBCSYDJGT);\
    }\
    return p;\
}\

#define Vector(type) _WMJ_VECTOR_P_STRUCT___##type
#define CreateVector(type) vec_##type##_create()
#define DestroyVector(x) free(x)

#define vec_index(vec, i) (\
    is_out_of_range(i < 0 || i >= vec->_end_index), \
    vec->_data[i]\
)

#define vec_at(vec, i) vec_index(vec, i)

#define vec_trim(vec) do {\
    if (vec->_start_index == 0) break;\
    _I __gap = vec->_start_index;\
    while (vec->_start_index < vec->_end_index) {\
        vec->_data[vec->_start_index - __gap] = vec->_data[vec->_start_index];\
        vec->_start_index++;\
    }\
    vec->_start_index = 0;\
    vec->_end_index -= __gap;\
} while(0)

#define vec_reserve(vec, num) do {\
    /*_log_info("reserve space from %d to %d", vec->_max_ele_num, num);*/\
    if (vec->_max_ele_num >= (num)) break;\
    vec_trim(vec);\
    void* __p = realloc(vec, (num) * vec->_ele_size + __wmJ_vector_struct_size__);\
    _error_s(__p == NULL, "reverse space fail. from %d to %d", vec->_max_ele_num, num);\
    vec = __p;\
    vec->_space_size = (num) * vec->_ele_size;\
    vec->_max_ele_num = (num);\
} while(0)

#define vec_push_back(vec, i) do {\
    if (vec->_max_ele_num == vec->_end_index - vec->_start_index) { \
        vec_reserve(vec, vec->_max_ele_num == 0? 1:vec->_max_ele_num * 2);}\
    if (vec->_end_index == vec->_max_ele_num) {vec_trim(vec);}\
    vec->_data[vec->_end_index] = i;\
    vec->_end_index+=1;\
} while (0)

#define vec_pop_back(vec) do {\
    if (vec->_end_index > vec->_start_index) {\
        vec->_end_index--;\
        vec->_ele_num--;\
    }\
}while (0)

#define _vec_print_inner(vec) do {\
    printf("ele_size: %d\n", vec->_ele_size);\
    printf("max_ele_num: %d\n", vec->_max_ele_num);\
    printf("space_size: %d\n", vec->_space_size);\
    printf("start_index: %d\n", vec->_start_index);\
    printf("end_index: %d\n\n", vec->_end_index);\
} while(0)

static _I __wmJ_vector_struct_size__ = 0;
defineVector(XJBCSYDJGT);

#endif

