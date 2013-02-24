/*

    TDolphin projects

    -> STL internal new/delete for vector <-

    (c) TDolphin 2007

    td_stl_construct.h

    STL implementation by TDolphin for TDolphin's projets
    (it is very simple version, not all functionality is supported)
    author: Rafal Zabdyr / TDolphin


    created: 26.10.2007
       last: 27.10.2007

*/

#ifndef __TD_STL_CONSTRUCT
#define __TD_STL_CONSTRUCT



#include <new>


namespace std
{

template <typename T1>
inline void new_placement(T1 *_p)
{ ::new(static_cast<void*>(_p)) T1; };

template <typename T1, typename T2>
inline void new_placement(T1 *_p, const T2 &_val)
{ ::new(static_cast<void*>(_p)) T1(_val); };

};



#endif // __TD_STL_CONSTRUCT
