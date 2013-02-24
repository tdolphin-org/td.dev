/*

    TDolphin projects

    (c) TDolphin 2007

    td_stl_vector.h

    STL implementation by TDolphin for TDolphin's projets

    author: Rafal Zabdyr

    -> STL TRIPLET <-

    created: 1.08.2007
       last: 10.08.2007

*/

#ifndef __TD_STL_TRIPLET
#define __TD_STL_TRIPLET



namespace std
{

//
// triplet
//
template<typename T1, typename T2, typename T3>
struct triplet
{
   typedef T1 first_type;
   typedef T2 second_type;
   typedef T3 third_type;

   triplet() : first(T1()), second(T2()), third(T3())  {}
   triplet(const T1& _first, const T2& _second, T3 _third) : first(_first), second(_second), third(_third) {}

   T1 first;
   T2 second;
   T3 third;
};

template<typename T1, typename T2, typename T3>
inline int operator==(const triplet<T1, T2, T3>& _x, const triplet<T1, T2, T3>& _y)
{ return (_x.first == _y.first && _x.second == _y.second && _x.third == _y.third); }

template<typename T1, typename T2, typename T3>
inline int operator<(const triplet<T1, T2, T3>& _x, const triplet<T1, T2, T3>& _y)
{ return (_x.first < _y.first || (!(_y.first < _x.first) && _x.second < _y.second) || ((!(_y.first < _x.first) && !(_y.second < _x.second)) && _x.third < _y.third)); }

template<typename T1, typename T2, typename T3>
inline int operator!=(const triplet<T1, T2, T3>& _x, const triplet<T1, T2, T3>& _y) { return !(_x == _y); }

template<typename T1, typename T2, typename T3>
inline triplet<T2, T2, T3> make_triplet(const T1& _first, const T2& _second, const T3& _third) { return triplet<T1, T2, T3>(_first, _second, _third); }

};



#endif // __TD_STL_TRIPLET_H
