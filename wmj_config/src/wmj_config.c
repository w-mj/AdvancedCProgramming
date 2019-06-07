#include <stdlib.h>
#include <string.h>
#include "wmj_config.h"
#include "wmj_defines.h"
#include "wmj_types.h"
#include "wmj_delog.h"
#include "wmj_string.h"

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
    #define PRINT_IPARAMS
    #include "configbase.h"
    #define PRINT_STRPARAMS
    #include "configbase.h"
    return;
}
#include "lex.h"

static _I error_f;

static _I secID = wmj_null;

#define SECNUM 2
enum {
    #define SECNAME_ENUM
    #include "configbase.h"
    MAX_SECNAME
};
static const _c*(SECNAME[MAX_SECNAME]) = {
    #define SECNAME_STRDEF
    #include "configbase.h"
};
#define MNAMESIZE 1024
static _c m_name[MNAMESIZE];
static _I set_section(_CONFIG *pcfg, _s str, _I len) {
    _I i, re = 0;
    _c zero = '\0';
    if ((str) && (len > 2)) {
        _swap(str[len - 1], zero);
        for (i = 0; i < MAX_SECNAME; i++) {
            if (strcmp(SECNAME[i], str + 1) == 0) {
                secID = i;
                // printf("found %s section !\n", str + 1);
                break;
            }
        }
        _swap(str[len - 1], zero);
        if (i >= MAX_SECNAME) {
            re = wmj_null;
        }
    } else {
        // print_config(pcfg, stdout);
        if (secfunc != 0) {
            re = secfunc(pcfg, sec_pm);
        }
        secID = wmj_null;
    }
    return re;
}
static _I set_memberName(_CONFIG *pcfg, _s str, _I len) {
    _I l, re = 0;
    l = strxcpy(m_name, (_s)SECNAME[secID], MNAMESIZE);
    l += strxcpy(m_name + l, ".", MNAMESIZE);
    l += strxcpy(m_name + l, str, MNAMESIZE);
    return re;
}
static _I set_memberInfo(_CONFIG *pcfg, _s str, _I len) {
    _I i, re = 0;
    #define CMP_STRPARAMS
    #include "configbase.h"
    #define CMP_IPARAMS
    #include "configbase.h"
    re = wmj_null;
_set_memberInfo_END:
    return re;
}
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
typedef _I (*pGRAMMERFUNC) (_CONFIG *pcfg, _s str, _I len, _I status);

static _I grammar_comments(_CONFIG *pcfg, _s str, _I len, _I status) {
    _I re = _ERROR_STATUS;
    if (status == _WAIT_STATUS) {
        re = _FINISH_STATUS;
    }
    return re;
}
static _I grammar_split(_CONFIG *pcfg, _s str, _I len, _I status) {
    _I re = _ERROR_STATUS;
    if (secID == wmj_null) {
        goto _grammar_split_END;
    }
    if (status == _GETSYMBOL_STATUS) {
        re = _GETSPLIT_STATUS;
    }
_grammar_split_END:
    return re;
}
static _I grammar_secend(_CONFIG *pcfg, _s str, _I len, _I status) {
    _I re = _ERROR_STATUS;
    if (secID == wmj_null) {
        goto _grammer_secend_END;
    }
    if (status != _WAIT_STATUS) {
        goto _grammer_secend_END;
    }
    if (set_section(pcfg, 0, 0) == wmj_null) {
        goto _grammer_secend_END;
    }
    re = _GETEND_STATUS;
_grammer_secend_END:
    return re;
}
static _I grammar_secname(_CONFIG *pcfg, _s str, _I len, _I status) {
    _I re = _ERROR_STATUS;
    if (secID != wmj_null) {
        goto _grammer_secname_END;
    }
    if (status != _WAIT_STATUS) {
        goto _grammer_secname_END;
    }
    if (set_section(pcfg, str, len) == wmj_null) {
        goto _grammer_secname_END;
    }
    re = _GETSEC_STATUS;
_grammer_secname_END:
    return re;
}
static _I grammar_symbol(_CONFIG *pcfg, _s str, _I len, _I status) {
    _I re = _ERROR_STATUS;
    if (secID == wmj_null) {
        goto _grammar_symbol_END;
    }
    if (status == _WAIT_STATUS) {
        if (set_memberName(pcfg, str, len) == wmj_null) {
            goto _grammar_symbol_END;
        }
        re = _GETSYMBOL_STATUS;
    } else if (status == _GETSPLIT_STATUS) {
        if (set_memberInfo(pcfg, str, len) == wmj_null) {
            goto _grammar_symbol_END;
        }
        re = _GETINFO_STATUS;
    }
_grammar_symbol_END:
    return re;
}
static _I grammar_str(_CONFIG *pcfg, _s str, _I len, _I status) {
    _I re = _ERROR_STATUS;
    if (secID == wmj_null) {
        goto _grammar_str_END;
    }
    if (status == _GETSPLIT_STATUS) {
        if (set_memberInfo(pcfg, str, len) == wmj_null) {
            goto _grammar_str_END;            
        }
        re = _GETINFO_STATUS;
    }
_grammar_str_END:
    return re;
}

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


_I load_config(_s infilename, _I is_init, _CONFIG *pcfg, pCFGFUNC pfunc, _p pm) {
    _I re = 0;
    _s str;
    _I len, type, status;
    _c zero = '\0';

    _sBUF *p = NULL;
    _CONFIG ptCfg[1];
    secfunc = pfunc;
    sec_pm = pm;
    init_config(ptCfg, is_init, pcfg);
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
        if ((status = grammer_func[type](ptCfg, str, len, status)) == _ERROR_STATUS) {
            fprintf(stdout, "<%s> have error.\n", infilename);
            break;
        }
        // fprintf(stdout, "found: \"%s\" type %d\n", str, type);
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
    memcpy(pcfg, ptCfg, sizeof(_CONFIG));
    re = wmj_null;
_load_config_END:
    free_strbuf(&p);
    return re;
}
