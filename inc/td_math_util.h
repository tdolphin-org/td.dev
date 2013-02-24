/*

    TDolphin projects

    (c) TDolphin 2007

    td_math_util.h

    classes/function for algorithms (matemathical)

    created: 30.07.2007
       last: 3.11.2007

*/

#ifndef __TD_MATH_UTIL_H
#define __TD_MATH_UTIL_H



#include "td_stl_vector.h"

// defines

#define __TD_GRAPH_DEFAULT_INIT_RESERVE   32
#define __TD_GRAPH_DEFAULT_RESIZE_STEP    16


// types/enums

// functions
namespace tdmath
{

template<typename T>
inline T min(const T& _x, const T& _y) { return _x < _y ? _x : _y; };

template<typename T>
inline T max(const T& _x, const T& _y) { return _x < _y ? _y : _x; };

template<typename T>
inline T dist(const T& _x, const T& _y) { return _x < _y ? _y - _x : _x - _y; } 

};
 
// structs/classes

////////////////////////////////////////////////////////////////////////////////
// class cGraphBase (base class for Graphs -> indirect and direct)
////////////////////////////////////////////////////////////////////////////////
class cGraphBase
{
public:
   cGraphBase(unsigned int A_nNodes);
   ~cGraphBase();

   virtual void del_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) = 0;

   unsigned int add_node(); // return node index
   unsigned int size() const { return m_nNodes; }

private:
   void reserve(unsigned int A_nReserve);

protected:
   void clear();
   void set_edge(unsigned int A_iNodeA, unsigned int A_iNodeB, int A_nWeight);
   int get_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) const;

private:
   // members
   int *m_aEdgesMatrix;
   unsigned int m_nNodes; // size, number of nodes
   unsigned int m_nReserved; // max number without resize for nodes
};

////////////////////////////////////////////////////////////////////////////////
// class cGraphBase (base class for Graphs -> indirect and direct)
////////////////////////////////////////////////////////////////////////////////
class cIndirectGraph : public cGraphBase
{
public:
   cIndirectGraph(unsigned int A_nNodes = 0);

   void add_edge(unsigned int A_iNodeA, unsigned int A_iNodeB);
   virtual void del_edge(unsigned int A_iNodeA, unsigned int A_iNodeB);
   bool is_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) const;
   bool any_edge(unsigned int A_iNode) const;
   bool all_visitable_from(unsigned int A_iNode, unsigned int &A_iRetNodeNotVisited) const;

private:   
   void visit(unsigned int A_iNode, std::vector<bool> &A_vVisited) const;
};

////////////////////////////////////////////////////////////////////////////////
// class cGraphBase (base class for Graphs -> indirect and direct)
////////////////////////////////////////////////////////////////////////////////
class cDirectGraph : public cGraphBase
{
public:
   cDirectGraph(unsigned int A_nNodes = 0);

   void add_edge(unsigned int A_iNodeA, unsigned int A_iNodeB);
   virtual void del_edge(unsigned int A_iNodeA, unsigned int A_iNodeB);
   bool is_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) const;
};



#endif // __TD_MATH_UTIL_H
