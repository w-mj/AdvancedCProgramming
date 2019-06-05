#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include "types.h"
#include "defines.h"

typedef struct {
    _I test;
} _CONFIG;

typedef _I (*pCFGFUNC) (_CONFIG *pCfg, _p pm);

_I load_config(_s infilename, _I isInit, _CONFIG *pCfg, pCFGFUNC pfunc, _p pm);
void print_config(_CONFIG *cfg, FILE *f);

#endif