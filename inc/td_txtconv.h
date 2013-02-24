/*

    TDolphin projects

    (c) TDolphin 2005-2006

    td_txtconv.h

    Text conversion routines (ISO, UNICODE, UTF8), only Polish letters!!!!.

    created: 2.09.2006
       last: 11.09.2006

*/

#ifndef __TD_TXTCONV_H
#define __TD_TXTCONV_H



// defines

// types/enums

// structs/classes

////////////////////////////////////////////////////////////////////////////////
// cCharScope
// class (scope) for char memory array
////////////////////////////////////////////////////////////////////////////////

class cCharScope
{
public:
   cCharScope(char *A_pMemory) : m_pMemory(A_pMemory) {}
   ~cCharScope() { if (m_pMemory) delete[] m_pMemory; }
   char *mem() { return m_pMemory; }

private:
   char *m_pMemory;
};

// namespaces/prototypes  

namespace tdtxtconv
{
  unsigned int *ConvertISO88592_TO_UNICODE(const char *A_strISO); // ISO 8859-2 to UNICODE
  char *ConvertISO88592_TO_UTF8(const char *A_strISO); // ISO 8859-2 to UTF8
};


#endif // __TD_TXTCONV_H
