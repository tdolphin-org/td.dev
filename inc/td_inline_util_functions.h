/*

    TDolphin projects

    (c) TDolphin 2007

    td_inline_util_functions.h

    Inline Utility Functions with definitions for all TDolphin's projects (Ansic C/C++ programs)

    created: 25.07.2007
       last: 26.07.2007

*/

#ifndef __TD_INLINE_UTIL_FUNCTIONS_H
#define __TD_INLINE_UTIL_FUNCTIONS_H


#ifdef __cplusplus
namespace InlineUtil
{
#endif

inline unsigned int rand_range(unsigned int A_nMin, unsigned int A_nMax) { return (A_nMax == A_nMin ? A_nMax : rand() % (A_nMax - A_nMin) + A_nMin); }

#ifdef __cplusplus
};
#endif


#endif // __TD_INLINE_UTIL_FUNCTIONS_H
