#ifndef tvx_utils_h
#define tvx_utils_h

#include "TROOT.h"

//namespace tvx {

//void Info(const char *method, const char *msgfmt, ...) const
//{
//   gROOT->Info();
//}

#define Info(msgfmt, ...) gROOT->Info(__FUNCTION__, msgfmt, __VA_ARGS__)
//char str[100];\
//sprintf(str, __VA_ARGS__);\
//std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << str << std::endl;\


//}

#endif
