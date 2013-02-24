/*

    TDolphin projects

    (c) TDolphin 2005-2009

    td_templates.cpp

    Templates for TDolphin's projects (C++)

    created: 20.11.2005
       last: 14.12.2009

*/

#include <iostream>

#include "td_common_defines.h"
#include "td_templates.h"

using namespace std;

// globals


////////////////////////////////////////////////////////////////////////////////
// class cListBase
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cListBase::cListBase
//
// Rafal Zabdyr, 20.11.2005
//==============================================================================
cListBase::cListBase()
: m_pFirst(NULL), m_pLast(NULL)
{
}

//==============================================================================
// cListBase::insert_begin
//
//  insert at begin (push front)
//
// Rafal Zabdyr, 20.11.2005
//==============================================================================
char cListBase::insert_begin(cConnection *A_pNew)
{
   //printf("cListBase::insert_begin(cConnection *A_pNew) A_pNew = %ld, m_pFirst = %ld, m_pLast = %ld\n", A_pNew, m_pFirst, m_pLast);

   if (!m_pFirst) // => m_pLast == NULL
   {
      m_pFirst = A_pNew;
      m_pLast = A_pNew;
   }
   else
   {
      A_pNew->m_pNext = m_pFirst;
      m_pFirst = A_pNew;
   }

   return TRUE;
}

//==============================================================================
// cListBase::insert_end
//
//  insert at end (push back)
//
// Rafal Zabdyr, 20.11.2005
//==============================================================================
char cListBase::insert_end(cConnection *A_pNew)
{
   //printf("cListBase::insert_end(cConnection *A_pNew) A_pNew = %ld, m_pFirst = %ld, m_pLast = %ld\n", A_pNew, m_pFirst, m_pLast);

   if (!m_pFirst) // => m_pLast == NULL
   {
      m_pFirst = A_pNew;
      m_pLast = A_pNew;
   }
   else
   {
      m_pLast->m_pNext = A_pNew;
      m_pLast = A_pNew;
   }

   return TRUE;
}

//==============================================================================
// cListBase::get_at_begin
//
//  get (and remove) element at begin (pop front)
//
// Rafal Zabdyr, 1.12.2005
//==============================================================================
cConnection *cListBase::get_at_begin()
{
   //printf("cListBase::get_at_begin() m_pFirst = %ld, m_pLast = %ld\n", m_pFirst, m_pLast);

   if (!m_pFirst)
      return NULL;

   cConnection *pTmp = m_pFirst;
   m_pFirst = m_pFirst->m_pNext;

   if (m_pFirst == NULL)
      m_pLast = NULL;

   return pTmp;
}

//==============================================================================
// cListBase::get_at_end
//
//  get (and remove) element at end (pop end)
//
// Rafal Zabdyr, 1.12.2005
//==============================================================================
cConnection *cListBase::get_at_end()
{
   if (!m_pLast)
      return NULL;

/*   cConnection *pTmp = m_pLast;
   m_pFirst = m_pFirst->m_pNext;

   if (m_pFirst == NULL)
      m_pLast = NULL;

   return pTmp;*/

   //cout << "cListBase::get_at_end() not implemented" << endl;

   return NULL;
}


////////////////////////////////////////////////////////////////////////////////
// class cListBaseIterator
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cListBaseIterator::cListBaseIterator
//
// Rafal Zabdyr, 28.11.2005
//==============================================================================
cListBaseIterator::cListBaseIterator(cListBase &A_List)
{
   m_pList = &A_List;
   m_pCurrentConnect = A_List.m_pFirst;
}

//==============================================================================
// cListBaseIterator::operator++
//
// Rafal Zabdyr, 28.11.2005
//==============================================================================
void cListBaseIterator::operator++()
{
   if (m_pCurrentConnect)
      m_pCurrentConnect = m_pCurrentConnect->m_pNext;
}

//==============================================================================
// cListBaseIterator::operator++(int)
//
// Rafal Zabdyr, 28.11.2005
//==============================================================================
void cListBaseIterator::operator++(int)
{
   if (m_pCurrentConnect)
      m_pCurrentConnect = m_pCurrentConnect->m_pNext;
}

//==============================================================================
// cListBaseIterator::operator*()
//
// Rafal Zabdyr, 29.11.2005
//==============================================================================
cConnection *cListBaseIterator::operator*()
{
   return m_pCurrentConnect;
}

//==============================================================================
// cListBaseIterator::isend
//
// Rafal Zabdyr, 28.11.2005
//==============================================================================
char cListBaseIterator::isend()
{
   return (m_pCurrentConnect == NULL);
}

//==============================================================================
// cListBaseIterator::isend
//
//  set iterator to begin
//
// Rafal Zabdyr, 12.12.2005
//==============================================================================
void cListBaseIterator::restart()
{
   if (m_pList)
      m_pCurrentConnect = m_pList->m_pFirst;
}

