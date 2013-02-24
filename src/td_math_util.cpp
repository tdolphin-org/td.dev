/*

    TDolphin projects

    (c) TDolphin 2007-2009

    td_math_util.cpp

    classes/function for algorithms (matemathical)

    created: 30.07.2007
       last: 14.12.2009

*/

#include <iostream>

//#define __TD_DEBUG

#include "td_common_defines.h"
#include "td_math_util.h"

using namespace std;

// global variables


////////////////////////////////////////////////////////////////////////////////
// class cGraphBase
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cGraphBase::cGraphBase
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
cGraphBase::cGraphBase(unsigned int A_nNodes)
: m_nNodes(A_nNodes), m_nReserved(__TD_GRAPH_DEFAULT_INIT_RESERVE)
{
   if (m_nNodes > m_nReserved)
      m_nReserved = (m_nNodes / __TD_GRAPH_DEFAULT_RESIZE_STEP + 1) * __TD_GRAPH_DEFAULT_RESIZE_STEP;

   m_aEdgesMatrix = new int[m_nReserved * m_nReserved];

   if (!m_aEdgesMatrix)
      throw;

   clear();
}

//==============================================================================
// cGraphBase::cGraphBase
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
cGraphBase::~cGraphBase()
{
   if (m_aEdgesMatrix)
      delete[] m_aEdgesMatrix;
}

//==============================================================================
// cGraphBase::add_node
//
// Rafal Zabdyr, 31.07.2007
//==============================================================================
unsigned int cGraphBase::add_node()
{
   if (m_nNodes == m_nReserved)
      reserve(m_nReserved + __TD_GRAPH_DEFAULT_RESIZE_STEP);

   return (m_nNodes++);
}

//==============================================================================
// cGraphBase::reserve
//
// Rafal Zabdyr, 31.07.2007
//==============================================================================
void cGraphBase::reserve(unsigned int A_nReserve)
{
   // reserve only up
   if (A_nReserve < m_nReserved)
   {
      cerr << "cGraphBase::reserve() : wrong new reserve value = " << A_nReserve << ", smaller than reserved = " << m_nReserved << endl;
      return;
   }

   int *aVertex = new int[A_nReserve * A_nReserve];

   if (!aVertex)
      throw;

   // copy edges
   for (unsigned int j = 0; j < m_nReserved; j++)
      for (unsigned int i = 0; i < m_nReserved; i++)
         aVertex[i + j * A_nReserve] = m_aEdgesMatrix[i + j * m_nReserved];

   delete[] m_aEdgesMatrix;

   m_aEdgesMatrix = aVertex;
   m_nReserved = A_nReserve;
}

//==============================================================================
// cGraphBase::clear
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
void cGraphBase::clear()
{
   for (unsigned int i = 0; i < m_nReserved * m_nReserved; i++)
      m_aEdgesMatrix[i] = 0;
}

//==============================================================================
// cGraphBase::set_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
void cGraphBase::set_edge(unsigned int A_iNodeA, unsigned int A_iNodeB, int A_nWeight)
{
   if (A_iNodeA >= m_nNodes || A_iNodeB >= m_nNodes)
      throw;

   m_aEdgesMatrix[A_iNodeA + A_iNodeB * m_nReserved] = A_nWeight;
}

//==============================================================================
// cGraphBase::get_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
int cGraphBase::get_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) const
{
   if (A_iNodeA >= m_nNodes || A_iNodeB >= m_nNodes)
      throw;

   return m_aEdgesMatrix[A_iNodeA + A_iNodeB * m_nReserved];
}


////////////////////////////////////////////////////////////////////////////////
// class cIndirectGraph
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cIndirectGraph::cIndirectGraph
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
cIndirectGraph::cIndirectGraph(unsigned int A_nNodes /*= 0*/)
: cGraphBase(A_nNodes)
{
}

//==============================================================================
// cIndirectGraph::add_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
void cIndirectGraph::add_edge(unsigned int A_iNodeA, unsigned int A_iNodeB)
{
   set_edge(A_iNodeA, A_iNodeB, 1);
   set_edge(A_iNodeB, A_iNodeA, 1);
}

//==============================================================================
// cIndirectGraph::del_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
void cIndirectGraph::del_edge(unsigned int A_iNodeA, unsigned int A_iNodeB)
{
   set_edge(A_iNodeA, A_iNodeB, 0);
   set_edge(A_iNodeB, A_iNodeA, 0);
}

//==============================================================================
// cIndirectGraph::is_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
bool cIndirectGraph::is_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) const
{
   return (get_edge(A_iNodeA, A_iNodeB) != 0 && get_edge(A_iNodeB, A_iNodeA) != 0);
}

//==============================================================================
// cIndirectGraph::any_edge
//
// Rafal Zabdyr, 31.10.2007
//==============================================================================
bool cIndirectGraph::any_edge(unsigned int A_iNode) const
{
   for (unsigned int i = 0; i < size(); i++)
      if (is_edge(A_iNode, i))
      {
         TD_DEBUG( cout << "edge at (" << A_iNode << "," << i << ")" << endl; )
         return true;
      }
      
   TD_DEBUG( cout << "no edge" << endl; )

   return false;
}

//==============================================================================
// cIndirectGraph::all_visitable_from
//
// Rafal Zabdyr, 31.10.2007
//==============================================================================
bool cIndirectGraph::all_visitable_from(unsigned int A_iNode, unsigned int &A_iRetNodeNotVisited) const
{
   unsigned int i;
   std::vector<bool> vVisited;

   vVisited.resize(size(), false);
   visit(A_iNode, vVisited);
   
   for (i = 0; i < size(); i++)
   {
      TD_DEBUG( cout << vVisited[i] << "|"; )
      if (!vVisited[i]) // any not visited
      {
         A_iRetNodeNotVisited = i;
         return false;
      }
   }
      
   return true;
}

//==============================================================================
// cIndirectGraph::visit
//
// Rafal Zabdyr, 31.10.2007
//==============================================================================
void cIndirectGraph::visit(unsigned int A_iNode, std::vector<bool> &A_vVisited) const
{
   A_vVisited[A_iNode] = true;
   for (unsigned int i = 0; i < size(); i++)
      if (!A_vVisited[i] && is_edge(A_iNode, i)) // not visited and have edge to
         visit(i, A_vVisited);
}

////////////////////////////////////////////////////////////////////////////////
// class cDirectGraph
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cDirectGraph::cDirectGraph
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
cDirectGraph::cDirectGraph(unsigned int A_nNodes /*= 0*/)
: cGraphBase(A_nNodes)
{
}

//==============================================================================
// cDirectGraph::add_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
void cDirectGraph::add_edge(unsigned int A_iNodeA, unsigned int A_iNodeB)
{
   set_edge(A_iNodeA, A_iNodeB, 1);
}

//==============================================================================
// cDirectGraph::del_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
void cDirectGraph::del_edge(unsigned int A_iNodeA, unsigned int A_iNodeB)
{
   set_edge(A_iNodeA, A_iNodeB, 0);
}

//==============================================================================
// cDirectGraph::is_edge
//
// Rafal Zabdyr, 30.07.2007
//==============================================================================
bool cDirectGraph::is_edge(unsigned int A_iNodeA, unsigned int A_iNodeB) const
{
   return (get_edge(A_iNodeA, A_iNodeB) != 0);
}
