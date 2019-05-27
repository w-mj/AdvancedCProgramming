#include <stdlib.h>

typedef unsigned int _I;
typedef unsigned int _u32;
typedef struct {
    _I num;
    _u32 p[];
} _BUF;

_BUF * create_buf(_I size) {
    // void* p = ;
    _BUF* pbuf = malloc(size + sizeof(_BUF));
    // pbuf->p = p;
    pbuf->num = size;
    return pbuf;
}