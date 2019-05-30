
#ifdef ENUM_INFO
#define PARAM_INFO(mode, str, functioname) mode,
#endif

#ifdef MODESTR_INFO
#define PARAM_INFO(mode, str, function) str,
#endif

#ifdef FUNCNAME_INFO
#define PARAM_INFO(mode, str, function) function,
#endif

#ifdef PARAM_INFO

PARAM_INFO(_MODEA, "A", funcA)
PARAM_INFO(_MODEB, "B", functionB)
PARAM_INFO(_MODEC, "C", ccc)

#undef PARAM_INFO
#endif

#ifdef ENUM_INFO
#undef ENUM_INFO
#endif

#ifdef MODESTR_INFO
#undef MODESTR_INFO
#endif

#ifdef FUNCNAME_INFO
#undef FUNCNAME_INFO
#endif
