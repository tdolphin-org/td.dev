/*

    TDolphin projects

    (c) TDolphin 2007

    td_stl_vector.h

    STL implementation by TDolphin for TDolphin's projets

    author: Rafal Zabdyr

    -> STL PAIR <-

    created: 1.08.2007
       last: 10.08.2007

*/

#ifndef __TD_STL_PAIR
#define __TD_STL_PAIR



namespace std
{

//
// pair
//
template<typename T1, typename T2>
struct pair
{
   typedef T1 first_type;
   typedef T2 second_type;

   pair() : first(T1()), second(T2()) {}
   pair(const T1& _first, const T2& _second) : first(_first), second(_second) {}

   T1 first;
   T2 second;
};

template<typename T1, typename T2>
inline int operator==(const pair<T1, T2>& _x, const pair<T1, T2>& _y)
{ return (_x.first == _y.first && _x.second == _y.second); }

template<typename T1, typename T2>
inline int operator<(const pair<T1, T2>& _x, const pair<T1, T2>& _y)
{ return (_x.first < _y.first || (!(_y.first < _x.first) && _x.second < _y.second)); }

template<typename T1, typename T2>
inline int operator!=(const pair<T1, T2>& _x, const pair<T1, T2>& _y)
{ return !(_x == _y); }

template<typename T1, typename T2>
inline pair<T2, T2> make_pair(const T1& _x, const T2& _y)
{ return pair<T1, T2>(_x, _y); }

};



#endif // __TD_STL_PAIR_H
