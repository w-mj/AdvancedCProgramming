#ifndef _LEX_H_
#define _LEX_H_

enum {
    _LEX_NULL,
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

#define _chkComments(p, re) do {\
    re = 0;\
    if (_cmpchar(_getchar(p), '#')) {\
        _chkchars(p, re, _cmpNchar, _getchar(p), '\n');\
    }\
} while (0);

#define _trychk(len, re, type, label_END, op, p) do{\
    op(p, len);\
    if (len) { \
        re = type;\
        goto label_END;\
    }\
}while(0)

#endif