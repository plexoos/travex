#ifndef tvx_utils_h
#define tvx_utils_h

#include "TError.h"

namespace tvx {

#define Info(...)     Info(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Warning(...)  Warning(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Error(...)    Error(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Fatal(...)    Fatal(__PRETTY_FUNCTION__, __VA_ARGS__)

}

#endif
