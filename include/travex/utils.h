#ifndef tvx_utils_h
#define tvx_utils_h

#include "TError.h"

namespace tvx {

template<typename... Arguments>
void Info(Arguments... args)     { ::Info(__PRETTY_FUNCTION__, args...); }

template<typename... Arguments>
void Warning(Arguments... args)  { ::Warning(__PRETTY_FUNCTION__, args...); }

template<typename... Arguments>
void Error(Arguments... args)    { ::Error(__PRETTY_FUNCTION__, args...); }

template<typename... Arguments>
void Fatal(Arguments... args)    { ::Fatal(__PRETTY_FUNCTION__, args...); }

}

#endif
