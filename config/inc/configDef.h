#ifdef CMP_STRPARAMS
#ifdef PARAM_STRINFO
#error PARAM_STRINFO have defined!
#endif
#define PARAM_STRINFO(fullname) do {\
    if (strcmp(mkstr(fullname), m_name) == 0) {\
        strxcpy(pcfg->fullname, str, MNAMESIZE);\
        goto _set_memberInfo_END;\
    }\
} while(0);
#endif

#ifdef CMP_IPARAMS
#ifdef PARAM_IINFO
#error PARAM_IINFO have defined!
#endif
#define PARAM_IINFO(fullname, minvalue, maxvalue) do{\
    if (strcmp(mkstr(fullname), m_name) == 0) {\
        _i32 __t = atoi(str);\
        __t = _max(minvalue, _min(maxvalue, __t));\
        pcfg->fullname = __t;\
        goto _set_memberInfo_END;\
    }\
}while(0);
#endif

#ifdef SECNAME_STRDEF
#ifdef PARAM_SECINFO
#error PARAM_SECINFO have defined!
#endif
#define PARAM_SECINFO(_TNAME, mName) mkstr(mName),
#endif

#ifdef SECNAME_DEF
#ifdef PARAM_SECINFO
#error PARAM_SECINFO have defined!
#endif
#define PARAM_SECINFO(_TNAME, mName) _TNAME mName;
#endif

#ifdef SECNAME_ENUM
#ifdef PARAM_SECINFO
#error PARAM_SECINFO have defined!
#endif
#define PARAM_SECINFO(_TNAME, mName) ENUM_##mName,
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

#ifdef SECNAME_ENUM
#undef SECNAME_ENUM
#endif

#ifdef SECNAME_STRDEF
#undef SECNAME_STRDEF
#endif

#ifdef SECNAME_DEF
#undef SECNAME_DEF
#endif

#ifdef CMP_IPARAMS
#undef CMP_IPARAMS
#endif

#ifdef CMP_STRPARAMS
#undef CMP_STRPARAMS
#endif