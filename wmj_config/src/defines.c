#include "defines.h"

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