#ifndef _INFO_H_
#define _INFO_H_

#include <stdio.h>
#include <stdarg.h>

#define __info(fmt, ...) do {\
    printf("[%s]<%s>(%d):", __FILE__, __func__, __LINE__);\
    printf(fmt, __VA_ARGS__);\
    putchar('\n');\
} while(0)

#define mkstr(symbol) #symbol
#define _error(exp, fmt, ...) do {\
    if (exp) {\
        __info("***Error occurs*** | %s", mkstr(exp));\
        printf(fmt, __VA_ARGS__);\
        putchar('\n');\
    }\
} while(0)

#endif