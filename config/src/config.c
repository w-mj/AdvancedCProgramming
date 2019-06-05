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
#include "lex.h"

static _I error_f;

enum {
    _WAIT_STATUS,
    _GETSEC_STATUS,
    _GETEND_STATUS,
    _GETSYMBOL_STATUS,
    _GETSPLIT_STATUS,
    _GETINFO_STATUS,
    _FINISH_STATUS,
    _ERROR_STATUS,
    _MAX_STATUS
};
typedef _I (*pGRAMMERFUNC) (_CONFIG *pCfg, _s str, _I len, _I status);

static _I grammar_comments(_CONFIG *pCfg, _s str, _I len, _I status) {return _FINISH_STATUS;}
static _I grammar_split(_CONFIG *pCfg, _s str, _I len, _I status) {return _ERROR_STATUS;}
static _I grammar_secend(_CONFIG *pCfg, _s str, _I len, _I status) {return _GETEND_STATUS;}
static _I grammar_secname(_CONFIG *pCfg, _s str, _I len, _I status) {return _GETSEC_STATUS;}
static _I grammar_symbol(_CONFIG *pCfg, _s str, _I len, _I status) {return _GETINFO_STATUS;}
static _I grammar_str(_CONFIG *pCfg, _s str, _I len, _I status) {return _ERROR_STATUS;}

static pGRAMMERFUNC grammer_func[_MAX_LEX_MODE] = {
    grammar_comments, 
    grammar_secname, 
    grammar_secend,
    grammar_symbol,
    grammar_split,
    grammar_str
};


static _I analyse_lex(_sBUF *p, _s *str, _I *plen) {
    _I len;
    _I re = wmj_null;
    _c c = 1;
    while (_chkNtail(p)) {
        _trychk(len, re, _LEX_COMMENTS, _analyse_lex_END, _chkComments, p);
        _trychk(len, re, _LEX_SPLIT, _analyse_lex_END, _chkSplit, p);
        _trychk(len, re, _LEX_SECEND, _analyse_lex_END, _chkEnd, p);
        _trychk(len, re, _LEX_SECNAME, _analyse_lex_END, _chkSecName, p);
        _trychk(len, re, _LEX_SYMBOL, _analyse_lex_END, _chkSymbol, p);
        _trychk(len, re, _LEX_STR, _analyse_lex_END, _chkStr, p);

        p->h += 1;
    }

_analyse_lex_END:
    if (re != wmj_null) {
        *str = (_c*)&(_getchar(p)) - len;
        *plen = len;
    }
    return re;
}


_I load_config(_s infilename, _I is_init, _CONFIG *pCfg, pCFGFUNC pfunc, _p pm) {
    _I re = 0;
    _s str;
    _I len, type, status;
    _c zero = '\0';

    _sBUF *p = NULL;
    _CONFIG ptCfg[1];
    secfunc = pfunc;
    sec_pm = pm;
    init_config(ptCfg, is_init, pCfg);
    p = load_file(infilename);
    _error(p == NULL, _load_config_END, "load file error");
    status = _WAIT_STATUS;
    error_f = 0;
    while(1) {
        if ((type = analyse_lex(p, &str, &len)) == wmj_null) {
            if (error_f)
                fprintf(stdout, "<%s> have error.\n", infilename);
            break;
        }
        _swap(zero, str[len]);
        if ((status = grammer_func[status](ptCfg, str, len, status)) == _ERROR_STATUS) {
            fprintf(stdout, "<%s> have error.\n", infilename);
            break;
        }
        fprintf(stdout, "fount: \"%s\" type %d\n", str, type);
        _swap(zero, str[len]);
        switch (status) {
            case _FINISH_STATUS:
            case _GETINFO_STATUS:
            case _GETSEC_STATUS:
            case _GETEND_STATUS:
                _nextLine(p);
                status = _WAIT_STATUS;
        }
    }
    // printf("%s\n", p->buf);
    memcpy(pCfg, ptCfg, sizeof(_CONFIG));
    re = wmj_null;
_load_config_END:
    free_strbuf(&p);
    return re;
}
