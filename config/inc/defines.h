#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <stdio.h>
#include "types.h"

#define wmj_null (_I)-1

#define _chkargc(n, info, _label_END) do{\
    if (argc < n) {\
        fprintf(stderr, "%s\n", info);\
        goto _label_END;\
    }\
} while(0)


#define _OPENFILE(fp, fname, fmode, endpos) do{\
    if((fp = fopen(fname, fmode)) == 0) { \
        perror("open file error"); \
        goto endpos; \
    }\
} while(0)


#define _CLOSEFILE(fp) do {\
    if (fp) {\
        fclose(fp);\
    } \
} while (0);

#define _swap(a, b) do {\
    a = a + b;\
    b = a - b;\
    a = a - b;\
}while(0)

#define _min(a, b) (a) < (b) ? (a) : (b)
#define _max(a, b) (a) > (b) ? (a) : (b)

_I strxcpy(_s dst, _s src, _I n);


#endif