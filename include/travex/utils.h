#ifndef tvx_utils_h
#define tvx_utils_h

#include "TError.h"

namespace tvx {

//void Info(const char *method, const char *msgfmt, ...) const
//{
//   gROOT->Info();
//}

#define Info(...)     Info(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Warning(...)  Warning(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Error(...)    Error(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Fatal(...)    Fatal(__PRETTY_FUNCTION__, __VA_ARGS__)

//char str[100];\
//sprintf(str, __VA_ARGS__);\
//std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << str << std::endl;\


}

#endif
