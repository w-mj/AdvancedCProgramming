#ifndef _LEX_H_
#define _LEX_H_
#include <ctype.h>

enum {
    _LEX_COMMENTS,
    _LEX_SECNAME,
    _LEX_SECEND,
    _LEX_SYMBOL,
    _LEX_SPLIT,
    _LEX_STR,
    _MAX_LEX_MODE
};


#define _getchar(p) (p)->buf[(p)->h]
#define _cmpchar(c1, c2) ((c1) == (c2))
#define _cmpNchar(c1, c2) ((c1) != (c2))
#define _chkNtail(p) ((p)->h < (p)->t)
#define _chkchars(p, re, op, ...) do {\
    re = 0;\
    while (_chkNtail(p) && op(__VA_ARGS__)) {\
        p->h += 1;\
        re += 1;\
    }\
} while(0)

#define _chkSplit(p, re) do {\
    re = 0;\
    if (_cmpchar(_getchar(p), ':')) {\
        re++;\
        p->h += 1;\
    }\
}while(0)

#define _chkComments(p, re) do {\
    re = 0;\
    if (_cmpchar(_getchar(p), '#')) {\
        _chkchars(p, re, _cmpNchar, _getchar(p), '\n');\
    }\
} while (0)

#define _chkSymbol(p, re) _chkchars(p, re, isalnum, _getchar(p))

#define _chkEnd(p, re) do {\
    _s __str = (_s)&(_getchar(p));\
    _c __zero = 0;\
    _swap(__str[5], __zero);\
    if (strcmp(__str, "[end]") == 0) {\
        re = 5;\
        p->h += 5;\
    } else {\
        re = 0;\
    }\
    _swap(__str[5], __zero);\
}while(0)

#define _chkSecName(p, re) do{\
    re = 0;\
    if (_cmpNchar(_getchar(p), '[')) {break;}\
    p->h += 1;\
    _chkSymbol(p, re);\
    if (re == 0 || _cmpNchar(_getchar(p), ']')) {\
        re = wmj_null;\
        break;\
    }\
    re += 2;\
    p->h += 1;\
} while(0)

#define _isNstr(c) (isspace(c) == 0) && ((c) != '\"')

#define _chkStr(p, re) do {\
    if (_cmpNchar(_getchar(p), '\"')) {\
        _chkchars(p, re, _isNstr, _getchar(p));\
    } else {\
        re = 1;\
        p->h += 1;\
        while (_chkNtail(p)) {\
            if (_cmpchar(_getchar(p), '\\')) {\
                re += 2;\
                p->h += 2;\
            } else if (_cmpchar(_getchar(p), '\"')) {\
                p->h += 1;\
                re++;\
                break;\
            } else {\
                p->h += 1;\
                re++;\
            }\
        }\
        p->h = _min(p->h, p->t);\
        if (_chkNtail(p) == 0) {\
            re = wmj_null;\
        }\
    }\
}while(0)

#define _nextLine(p) do {\
    _I __re;\
    if (_chkNtail(p) == 0) {\
        break;\
    }\
    _chkchars(p, __re, _cmpNchar, _getchar(p), '\n');\
    if (_chkNtail(p)) {\
        p->h += 1;\
    }\
} while(0)

#define _trychk(len, re, type, label_END, op, p) do{\
    op(p, len);\
    if (len == wmj_null) {\
        error_f = 1;\
        goto label_END;\
    }\
    if (len) { \
        re = type;\
        goto label_END;\
    }\
}while(0)

#endif