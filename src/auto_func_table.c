#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <wmj_types.h>

void funcA() {
    printf("this is function a\n");
}

void functionB() {
    printf("this is function b\n");
}

void ccc() {
    printf("this is function c\n");
}

enum {
    #define ENUM_INFO
    #include "paramDef.h"
    _MAX_MODE
};
const _s modestr[_MAX_MODE] = {
    #define MODESTR_INFO
    #include "paramDef.h"
};

typedef void(*ptype)(void);


static const ptype flist[_MAX_MODE] = {
    #define FUNCNAME_INFO
    #include "paramDef.h"
};

int main(int argc, char** argv) {
    assert(argc == 2);
    int i = 0;
    for (i = 0; i < _MAX_MODE; i++) {
        if (strcmp(argv[1], modestr[i]) == 0) {
            flist[i]();
            break;
        }
    }
    if (i >= _MAX_MODE) {
        printf("No such mode %s\n", argv[1]);
    }
    return 0;
}