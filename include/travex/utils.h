#ifndef tvx_utils_h
#define tvx_utils_h

#include "TError.h"


#define TVX_INFO(...)     ::Info(__func__, __VA_ARGS__)
#define TVX_WARNING(...)  ::Warning(__func__, __VA_ARGS__)
#define TVX_ERROR(...)    ::Error(__func__, __VA_ARGS__)
#define TVX_FATAL(...)    ::Fatal(__func__, __VA_ARGS__)


#endif
