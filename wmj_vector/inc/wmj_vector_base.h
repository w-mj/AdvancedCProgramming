

#ifdef _WMJ_VECTOR_STRUCT_NAME_
#define _WMJ_VECTOR_PARSE(x) _VECTOR_STRUCT_##x
#undef _WMJ_VECTOR_STRUCT_NAME_
#endif