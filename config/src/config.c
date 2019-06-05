#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "defines.h"
#include "types.h"
#include "delog.h"

typedef struct {
    _I h;  // current cursor
    _I t;  // max size
    _u8 buf[];
} _sBUF;

static pCFGFUNC secfunc = NULL;
static _p sec_pm;
static _I analyse_lex(_sBUF *p, _s *str, _I *plen);

static _sBUF *create_strbuf(_I num) {
    _sBUF *pre = NULL;
    pre = malloc(num + 1 + sizeof(_sBUF));
    _error(pre == 0, _create_strbuf_END, "malloc fail");
    pre->h = 0;
    pre->t = 0;
_create_strbuf_END:
    return pre;
}

static void free_strbuf(_sBUF **ppBuf) {
    if (*ppBuf) {
        free(*ppBuf);
        *ppBuf = NULL;
    }
    return ;    
}

static _sBUF *load_file(_s infilename) {
    _I fsize = 0;
    FILE *f = NULL;
    _sBUF *pre = NULL;
    _OPENFILE(f, infilename, "rb", _load_file_END);

    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    pre = create_strbuf(fsize);
    pre->t = fread(pre->buf, sizeof(_u8), fsize, f);
    pre->buf[pre->t] = 0;
_load_file_END:
    _CLOSEFILE(f);
    return pre;
}

static void init_config(_CONFIG *pcfg, _I is_init, _CONFIG *psrc) {
    if (is_init == 0) {
        memcpy(pcfg, psrc, sizeof(_CONFIG));
    } else {
        memset(pcfg, 0, sizeof(_CONFIG));
    }
    return ;
}

void print_config(_CONFIG *cfg, FILE *f) {
    fprintf(f, "config list:\n");
    fprintf(f, "test: %d\n", cfg->test);
    return;
}

_I load_config(_s infilename, _I is_init, _CONFIG *pCfg, pCFGFUNC pfunc, _p pm) {
    _I re = 0;
    _s str;
    _I len;
    _c zero = '\0';

    _sBUF *p = NULL;
    _CONFIG ptCfg[1];
    secfunc = pfunc;
    sec_pm = pm;
    init_config(ptCfg, is_init, pCfg);
    p = load_file(infilename);
    _error(p == NULL, _load_config_END, "load file error");
    while(1) {
        if (analyse_lex(p, &str, &len) == 0) {
            break;
        }
        _swap(zero, str[len]);
        fprintf(stdout, "fount: \"%s\"\n", str);
        _swap(zero, str[len]);
    }
    // printf("%s\n", p->buf);
    memcpy(pCfg, ptCfg, sizeof(_CONFIG));
    re = 0;
_load_config_END:
    free_strbuf(&p);
    return re;
}


#include "lex.h"
static _I analyse_lex(_sBUF *p, _s *str, _I *plen) {
    _I len;
    _I re = 0;
    while (_chkNtail(p)) {
        _trychk(len, re, _LEX_COMMENTS, _analyse_lex_END, _chkComments, p);
        p->h += 1;
    }

_analyse_lex_END:
    if (re != wmj_null) {
        *str = (_c*)&(_getchar(p)) - len;
        *plen = len;
    }
    return re;
}
