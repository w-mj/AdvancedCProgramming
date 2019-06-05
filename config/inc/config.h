#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include "types.h"
#include "defines.h"

#define MAX_NAME_LEN 128

typedef struct {
    _c name[MAX_NAME_LEN];
    _i32 min;
    _i32 max;
    _i32 def;
} _NUM_PARAM;

typedef struct {
    _c name[MAX_NAME_LEN];
    _I bufsize;
} _STR_PARAM;

typedef struct {
    #define SECNAME_DEF
    #include "configDef.h"
} _CONFIG;

typedef _I (*pCFGFUNC) (_CONFIG *pCfg, _p pm);

_I load_config(_s infilename, _I isInit, _CONFIG *pCfg, pCFGFUNC pfunc, _p pm);
void print_config(_CONFIG *cfg, FILE *f);

#endif