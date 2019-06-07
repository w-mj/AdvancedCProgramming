#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include "wmj_types.h"
#include "wmj_defines.h"

#define PARAM_SECDEF
#include "configbase.h"

typedef struct {
    #define SECNAME_DEF
    #include "configbase.h"
} _CONFIG;

typedef _I (*pCFGFUNC) (_CONFIG *pCfg, _p pm);

_I load_config(_s infilename, _I isInit, _CONFIG *pCfg, pCFGFUNC pfunc, _p pm);
void print_config(_CONFIG *cfg, FILE *f);

#endif