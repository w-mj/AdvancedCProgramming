#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "wmj_delog.h"

static _I get_current_date(_s buf, _I size) {
    time_t now;
    struct tm *timenow;
    time(&now);
    timenow = localtime(&now);
    return strftime(buf, size, "%Y-%m-%d", timenow);
}

static _I get_current_time(_s buf, _I size) {
    time_t now;
    struct tm *timenow;
    time(&now);
    timenow = localtime(&now);
    return strftime(buf, size, "%Y-%m-%d %H:%M:%S", timenow);
}


#define _chkPOSINFO(type) ((type) & _POS_INFOBITS)

static _I inited = 0;
#define MSG_SIZE 4096

static _I msgsize = MSG_SIZE;
static _c ms_buf[MSG_SIZE];
static _s ms_msg = ms_buf;
#define _initMSG() do {ms_msg = ms_buf; ms_buf[0] = 0; msgsize = MSG_SIZE; } while (0)
#define va_copy_statement(params, op, ...) do {\
    va_list _backup;\
    va_copy(_backup, params);\
    va_end(params);\
    op(__VA_ARGS__);\
    va_copy(params, _backup);\
    va_end(_backup);\
} while(0)

#define _init_delog(params, dbgname, logname) do{\
    if (inited == 0) {\
        va_copy_statement(params, s_init_delog, dbgname, logname);\
    }\
    _initMSG();\
} while(0)

#define fmt_str(s, n, ...) do {\
    _i32 __tlen = snprintf(s, n, __VA_ARGS__);\
    if(__tlen >= 0) {\
        s += __tlen;\
        n -= __tlen;\
    }\
} while (0)

#define fmt_vstr(s, n, params) do {\
    _s __fmt; \
    _i32 __tlen; \
    _getva_S(__fmt, params); \
    __tlen = vsnprintf(s, n, __fmt, params); \
    if (__tlen >= 0) {\
        s += __tlen;\
        n -= __tlen;\
    }\
} while(0)

#define getPosInfo(param) do {\
    _s __file, __func;\
    _I __line; \
    _getva_S(__file, params);\
    _getva_I(__line, params);\
    _getva_S(__func, params);\
    va_copy_statement(params, fmt_str, ms_msg, msgsize, "[%s]<%s>(%d):", __file, __func, __line);\
} while(0)


static FILE* fbug = 0;
static FILE* flog = 0;
static void destory_delog(void) {
    if (inited == 0) {
        goto _destory_delog_END;
    }
    _reg();
    inited = 0;
    fclose(fbug);
    fclose(flog);
_destory_delog_END:
    return;
}
static void s_init_delog(_s dbgname, _s logname) {
    _I len;
    _c buf[128];
    if (inited) {
        goto _s_init_delog_END;
    }
    inited = 1;
    atexit(destory_delog);
    get_current_time(buf, 128);
#if DELOG_MODE < 2
    if (dbgname == 0) {
        _initMSG();
        fmt_str(ms_msg, msgsize, "out/");
        len = get_current_date(ms_msg, msgsize);
        ms_msg += len;
        msgsize -= len;
        fmt_str(ms_msg, msgsize, ".dbg");
        dbgname = ms_buf;
    }
    _OPENFILE(fbug, dbgname, "a+", _s_init_delog_END);
    fprintf(fbug, "\n********** %s ***** %d(father %d) process run!\n", buf, getpid(), getppid());
#endif
    if (logname == 0) {
        _initMSG();
        fmt_str(ms_msg, msgsize, "out/");
        len = get_current_date(ms_msg, msgsize);
        ms_msg += len;
        msgsize -= len;
        fmt_str(ms_msg, msgsize, ".log");
        logname = ms_buf;
    }
    _OPENFILE(flog, logname, "a+", _s_init_delog_END);
    fprintf(flog, "\n********** %s ***** %d(father %d) process run!\n", buf, getpid(), getppid());
    _reg();
    // _pos_delog(_MAX_INFO_DELOG, "reg");

_s_init_delog_END:
    return;
}

static void out_info(_I mode) {
    if (mode == _DBG_INFO_DELOG) {
#if DELOG_MODE < 2
        if (fbug) {
            fprintf(fbug, "%s\n", ms_buf);
        }
#endif
#if DELOG_MODE == 0
        printf("%s\n", ms_buf);
#endif
        goto _out_info_END;
    }
    if (mode == _LOG_INFO_DELOG) {
        if (flog) {
            fprintf(flog, "%s\n", ms_buf);
        }
#if DELOG_MODE == 0
        printf("%s\n", ms_buf);
#endif
        goto _out_info_END;
    }

_out_info_END:
    return;
}

static void print_debug(va_list params) {
    _I len;
    _p tp;
    _s fmt;
    _s exp;
    _s str;
    _I I;
    _i32 i;
    double d;
    _getva_S(fmt, params);
    _getva_S(exp, params);
    if (fmt[0] == 'n') {
        goto _print_debug_CON;
    }
    if (fmt[0] == 'e') {
        fmt_str(ms_msg, msgsize, "*** error occured *** | %s | ", exp);
        goto _print_debug_CON;
    }
    va_copy_statement(params, fmt_str, ms_msg, msgsize, " %s = ", exp);
_print_debug_CON:
    switch (fmt[0]) {
        case 'e':
            fmt_vstr(ms_msg, msgsize, params);
            break;
        case 'n':
            fmt_str(ms_msg, msgsize, " | (pos)");
            break;
        case 'x':
            _getva_I(I, params);
            fmt_str(ms_msg, msgsize, "0x%x", I);
            break;
        case 'f':
            _getva_double(d, params);
            fmt_str(ms_msg, msgsize, "%1f", d);
            break;  
        case 'd':
            _getva_I32(i, params);
            fmt_str(ms_msg, msgsize, "%d", i);
            break;
        case 'c':
            _getva_I32(i, params);
            fmt_str(ms_msg, msgsize, "%c", (_c)i);
            break;
        case 'p':
            _getva_P(tp, params);
            fmt_str(ms_msg, msgsize, "%p", tp);
            break;
        case 's':
            _getva_S(str, params);
            fmt_str(ms_msg, msgsize, "\"%s\"", str);
            break;
        case 'a':
            _getva_P(tp, params);
            _getva_I(len, params);
            fmt_str(ms_msg, msgsize, " (%d)", len);
            msgsize -= print_bin(ms_msg, msgsize, tp, len);
        break;
        default:
            fprintf(stderr, "Unknown fmt %c\n", fmt[0]);
    }
_print_debug_END:
    return ;
}

void _wmj_delog(_I type, ...) {
    va_list params;
    va_start(params, type);

    if (type == _INIT_INFO_DELOG) {
        _s dbgname, logname;
        _getva_S(dbgname, params);
        _getva_S(logname, params);
        _init_delog(params, dbgname, logname);
        goto _wmj_delog_END;
    }
    _init_delog(params, 0, 0);

    if (_chkPOSINFO(type)) {
        getPosInfo(params);
    }
    type = _Lclr(type, 1);

    switch(type) {
        case _DBG_INFO_DELOG:
            print_debug(params);
            break;
        case _LOG_INFO_DELOG:
            fmt_vstr(ms_msg, msgsize, params);
            break;
    }

_wmj_delog_END:
    va_end(params);
    out_info(type);
    // printf("test only: %s\n", ms_buf);
    return ;
}

#define fmt_one_hex(s, n, d) fmt_str(s, n, "%02x ", (_u8)(d))
#define fmt_ext_hex(s, n) fmt_str(s, n, "XX ")
#define fmt_continue(s, n, num) fmt_str(s, n, ".. (mode %d bytes not show)\n", num)
#define fmt_new_line(s, n, addr) fmt_str(s, n, "\n0x%08x : ", _Lclr(addr, 4))

#define DEF_SHOW_MAX 256
#define LINEBSIZE 4
#define LINENUM _BITS_SIZE(LINEBSIZE)
_I print_bin(_s s, _I size, _u8 *p, _I len) {
    //printf("in print bin\n");
    //printf("%s\n%d\n%s\n%d\nheihiehei\n", s, size, p, len);
    _I prefixnum = _LNclr((_u64)p, 4);
    _I suffixnum;
    _I i = 0, j = 0, re = 0, n = size;
    if (prefixnum) {
        fmt_new_line(s, n, (_u32)(_i64)(p + i));
    }
        //printf("%x\n%s\n", prefixnum, ms_buf);

    while (i < prefixnum) {
        fmt_ext_hex(s, n);
        i++;
    }

    while ((i < DEF_SHOW_MAX) && (len > 0)) {
        if ((i & _BITS_MASK(LINEBSIZE)) == 0) {
            fmt_new_line(s, n, (_u32)(_i64)(p + i));
        }
        fmt_one_hex(s, n, p[j]);
        i++;
        j++;
        len--;
    }
    suffixnum = _LNclr(LINENUM - i, 4);
    while (suffixnum) {
        fmt_ext_hex(s, n);
        suffixnum--;
    }
    if (len > 0) {
        fmt_new_line(s, n, (_u32)(_i64)(p + i));
        fmt_continue(s, n, len);
    }
    re = size - n;
    //printf("end print bin\n");
    return re;
}
