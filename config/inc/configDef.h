#ifdef PARAM_SECDEF
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
#undef PARAM_SECDEF
#endif

#ifdef PARAM_SECINFO
PARAM_SECINFO(_NUM_PARAM, num)
PARAM_SECINFO(_STR_PARAM, str)
#undef PARAM_SECINFO
#endif

#ifdef PARAM_STRINFO
PARAM_STRINFO(num.name)
PARAM_STRINFO(str.name)
#undef PARAM_STRINFO
#endif

#ifdef PARAM_IINFO
PARAM_IINFO(num.min, 0, 100)
PARAM_IINFO(num.max, 0, 100)
PARAM_IINFO(num.def, 0, 100)
PARAM_IINFO(str.bufsize, 0, 80)
#undef PARAM_IINFO
#endif