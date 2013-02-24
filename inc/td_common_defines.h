/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_common_defines.h

    Common definitions for all TDolphin's projects (Ansic C/C++ programs)
    supported platforms:
     - MorphOS (gcc)
     - AmigaOS (gcc)
     - Win32 (msc)
     - Linux (gcc)

    created: 24.08.2005
       last: 12.02.2012

*/

#ifndef __TD_COMMON_DEFINES_H
#define __TD_COMMON_DEFINES_H


#ifndef LINUX
#ifndef WIN32
#include <exec/types.h>
#endif
#endif

//#define __TD_DEBUG

// defines

#ifdef WIN32
#ifndef __func__
#define __func__ "__FUNCTION__"
#endif
#endif

#ifdef __TD_DEBUG
#ifdef __cplusplus
#define TD_DEBUG(a)   std::cout << "[" << __FILE__ "; " << __func__ << "():" << __LINE__ << "]" << std::endl; a
#else
#define TD_DEBUG(a)   printf("[%s; %s():%d]\n", __FILE__, __func__, __LINE__); a
#endif // __cplusplus
#define TD_DEBUG_NEMO(a)  a
#else
#define TD_DEBUG(a)
#define TD_DEBUG_NEMO(a)
#endif

#ifdef __cplusplus
#define TD_ERROR(a)   std::cerr << "ERROR in [" << __FILE__ "; " << __func__ << "():" << __LINE__ << "]" << std::endl; a
#else
#define TD_ERROR(a)   printf("ERROR in [%s; %s():%d]\n", __FILE__, __func__, __LINE__); a
#endif // __cplusplus

#ifdef LINUX
typedef int BOOL;
#endif

#ifdef WIN32
typedef int BOOL;
#endif

#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#ifndef NULL
#define NULL 0
#endif

#define TD_OK   TRUE // true
#define TD_ERR  FALSE // false
#define TD_RETIDX_ERR -1 // used when return index but error occure

#ifdef WIN32
#define TD_SLASH  "\\"
#else // MorphOS, AmigaOS, Linux
#define TD_SLASH  "/"
#endif

#ifdef WIN32
#pragma warning(disable: 4761)
#pragma warning(disable: 4244)
#pragma warning(disable: 4761)
#endif // WIN32

#define TD_MAX_FILENAME          32 
#define TD_MAX_PATH              256
#define TD_MAX_PATH_FILENAME     256



#endif // __TD_COMMON_DEFINES_H
