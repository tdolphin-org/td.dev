/*

    TDolphin projects

    (c) TDolphin 2005-2006

    td_templates.h

    Templates for TDolphin's projects (C++)

    created: 18.11.2005
       last: 03.02.2006

*/

#ifndef __TD_TEMPLATES_H
#define __TD_TEMPLATES_H



// defines

// types/enums

// structs/classes

class cListBaseIterator;
template <class T> class TListIterator;

////////////////////////////////////////////////////////////////////////////////
// class cConnection (connection list)
////////////////////////////////////////////////////////////////////////////////

struct cConnection
{
   cConnection() : m_pNext(NULL) {} //{ printf("cConnection::cConnection(): this = %ld\n", this); }
   cConnection(cConnection *A_pNext) : m_pNext(A_pNext) {}

// members
   cConnection *m_pNext;
};


////////////////////////////////////////////////////////////////////////////////
// class cListBase (base list)
////////////////////////////////////////////////////////////////////////////////

class cListBase
{
public:
   cListBase();
   char insert_begin(cConnection *A_pNew);
   char insert_end(cConnection *A_pNew);
   cConnection *get_at_begin();
   cConnection *get_at_end();

// members
private:
   cConnection *m_pFirst,
               *m_pLast;

friend class cListBaseIterator;
};


////////////////////////////////////////////////////////////////////////////////
// class cListBaseIterator
////////////////////////////////////////////////////////////////////////////////

class cListBaseIterator
{
public:
   cListBaseIterator(cListBase &A_List);

   void operator++();
   void operator++(int);
   cConnection *operator*();
   char isend();
   void restart();

// members
private:
   cListBase *m_pList;
   cConnection *m_pCurrentConnect;
};


// templates

////////////////////////////////////////////////////////////////////////////////
// template TConnection
////////////////////////////////////////////////////////////////////////////////

template <class T>
struct TConnection : public cConnection
{
   TConnection(const T& obj) : m_Object(obj) {} //{ printf("TConnection::TConnection(const T& obj): this = %ld, &obj = %ld, &m_Object = %ld\n", this, &obj, &m_Object); }

// members
   T m_Object;
};

////////////////////////////////////////////////////////////////////////////////
// template TList
////////////////////////////////////////////////////////////////////////////////
template <class T>
class TList : private cListBase
{
public:
   ~TList()
   {
      //printf("TList::~TList(): this = %ld\n", this);
      clear();
   }

   void push(const T& obj)
   {
      //printf("TList::push(const T& obj): this = %ld, &obj = %ld\n", this, &obj);
      cListBase::insert_end(new TConnection<T>(obj));
   }

   T pop()
   {
      // to do
   }

   void clear()
   {
      //printf("TList::clear(): this = %ld\n", this);
      TConnection<T> *pConnect = (TConnection<T>*)cListBase::get_at_begin();
      while(pConnect)
      {
         //printf("TList::clear(): pConnect = %ld\n", pConnect);
         delete pConnect; // remove connector
         //printf("TList::clear(): deleleted pConnect\n");
         pConnect = (TConnection<T>*)cListBase::get_at_begin();
      }
      //printf("TList::clear(): finished\n");
   }

friend class TListIterator<T>;
};

////////////////////////////////////////////////////////////////////////////////
// template TListIterator
////////////////////////////////////////////////////////////////////////////////

template <class T>
class TListIterator : public cListBaseIterator
{
public:
   inline TListIterator(TList<T> &A_List) : cListBaseIterator(A_List) {}
   inline T* operator*()
   {
      TConnection<T> *pConnect = (TConnection<T>*)cListBaseIterator::operator*();
      return (pConnect != NULL) ? &pConnect->m_Object : NULL;
   }
};



#endif // __TD_TEMPLATES_H

