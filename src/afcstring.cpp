/*==============================================================

 Amiga Foundation Classes (AFC) it is something like MFC for PC

 Amiga CString v0.07


 Rafaî Zabdyr
 (C) ARMO 2000

 start: 7.XII.2000
 last:  7.XII.2000 ; 9.XII.2000 ;
       11.XII.2000 ; 13.XII.2000 ; 16.XII.2000 ;
       23.XII.2000 ; 24.XII.2000 ; 25.XII.2000 ;
       26.XII.2000

 (c) TDolphin 2007

 created:  7.12.2000
    last: 23.05.2007

==============================================================*/

#include <stdlib.h>
#ifdef AMIGAOS
#include <exec/types.h>
#endif
#include <string.h>
#include <iostream>

#include "afcstring.h"


/*-------------------------------------------------------------+
| ACString::ACString()                                         |
|                                                              |
| Rafaî Zabdyr, 7.12.2000                                      |
+-------------------------------------------------------------*/
ACString::ACString():
m_pszString(NULL), m_nStringLen(0), m_nMemSize(0)
{
   char *pszTemp = new char[1]; // alloc memory for empty string (NULL terminated)

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString() }* ";
   cout << "allocated memory = #$" << 1 << "; pointer = $"
        << hex << long(pszTemp) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp) // not NULL
   {
      m_nStringLen = 0; // string is empty
      m_nMemSize = 1; // size of alocated memory
      m_pszString = pszTemp; // pointer to string
      pszTemp[0] = '\0'; // clear initialy
   }
} // ACString::ACString()

/*-------------------------------------------------------------+
| ACString::ACString(const ACString&)                          |
|                                                              |
| Rafaî Zabdyr, 7.12.2000                                      |
+-------------------------------------------------------------*/
ACString::ACString(const ACString& stringSrc):
m_pszString(NULL), m_nStringLen(0), m_nMemSize(0)
{
   if (this == &stringSrc) // the same ACString ?
      return; // yes, so bye

   int nStrLen = stringSrc.GetLength();
   int nSize = nStrLen+1; // 1 for NULL
   char *pszTemp = new char[nSize]; // alloc memory

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString(const ACString&) }* ";
   cout << "allocated memory = #$" << nSize << "; pointer = $"
        << hex << long(pszTemp) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp)
   {
      memcpy(pszTemp, stringSrc.LPCTSTR(), nStrLen); // copy
      pszTemp[nStrLen] = '\0'; // NULL
      m_nMemSize = nSize; // size of alocated memory
      m_nStringLen = nStrLen; // string lenght
      m_pszString = pszTemp; // pointer to string
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }
} // ACString::ACString(const ACString&)

/*-------------------------------------------------------------+
| ACString::ACString(char , int = 1)                           |
|                                                              |
| Rafaî Zabdyr, 7.12.2000                                      |
+-------------------------------------------------------------*/
ACString::ACString(char ch, int nRepeat /* =1 */):
m_pszString(NULL), m_nStringLen(0), m_nMemSize(0)
{
   if (nRepeat < 1)
   {
      ACString(); // make empty string
      return;
   }

   int nSize = nRepeat + 1; // 1 for NULL ('\0')
   char *pszTemp = new char[nSize]; // alloc memory

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString(char, int) }* ";
   cout << "allocated memory = #$" << nSize << "; pointer = $"
        << hex << long(pszTemp) << '\n';
   cout << "strlen =" << long(nRepeat) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp) // not NULL
   {
      memset(pszTemp, ch, nRepeat); // fill
      pszTemp[nRepeat] = '\0'; // set end of string (NULL)
      m_nStringLen = nRepeat;
      m_nMemSize = nSize; // size of alocated memory
      m_pszString = pszTemp; // pointer to string
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }
} // ACString::ACString(char , int = 1)

/*-------------------------------------------------------------+
| ACString::ACString(const char*, int)                         |
|                                                              |
| not NULL termainated array                                   |
|                                                              |
| Rafaî Zabdyr, 7.12.2000                                      |
+-------------------------------------------------------------*/
ACString::ACString(const char *psz, int nLength):
m_pszString(NULL), m_nStringLen(0), m_nMemSize(0)
{
   if ((psz == NULL) || (nLength < 1))
   {
      ACString(); // make empty string
      return;
   }

   int nSize = nLength + 1; // 1 for NULL ('\0')
   char *pszTemp = new char[nSize]; // alloc memory

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString(char*, int) }* ";
   cout << "allocated memory = #$" << nSize << "; pointer = $"
        << hex << long(pszTemp) << '\n';
   cout << "strlen =" << long(nLength) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp)
   {
      memcpy(pszTemp, psz, nLength); // copy
      pszTemp[nLength] = '\0'; // NULL
      m_nMemSize = nSize; // size of alocated memory
      m_nStringLen = nLength; // string lenght
      m_pszString = pszTemp; // pointer to string
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }
} // ACString::ACString(const char*, int)

/*-------------------------------------------------------------+
| ACString::ACString(const char*)                              |
|                                                              |
| NULL terminated                                              |
|                                                              |
| Rafaî Zabdyr, 7.12.2000                                      |
+-------------------------------------------------------------*/
ACString::ACString(const char *psz):
m_pszString(NULL), m_nStringLen(0), m_nMemSize(0)
{
   if (psz == NULL)
   {
      ACString(); // made empty string
      return;
   }

   int nStrLen = strlen(psz);
   int nSize = nStrLen + 1; // 1 for NULL ('\0')
   char *pszTemp = new char[nSize]; // alloc memory

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString(const char*) }* ";
   cout << "allocated memory = #$" << nSize << "; pointer = $"
        << hex << long(pszTemp) << '\n';
   cout << "strlen =" << long(nStrLen) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp)
   {
      memcpy(pszTemp, psz, nStrLen); // copy
      pszTemp[nStrLen] = '\0'; // NULL
      m_nMemSize = nSize; // size of alocated memory
      m_nStringLen = nStrLen; // string lenght
      m_pszString = pszTemp; // pointer to string
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }
} // ACString::ACString(const char*)

/*--------------------------------------------------------------+
| ACString::~ACString()                                         |
|                                                               |
| Rafaî Zabdyr, 7.12.2000                                       |
+--------------------------------------------------------------*/
ACString::~ACString()
{
   delete[] m_pszString; // remove
} // ACString::~ACString()

/*--------------------------------------------------------------+
| ACString::GetLength()                                         |
|                                                               |
| Rafaî Zabdyr, 9.12.2000                                       |
+--------------------------------------------------------------*/
inline int ACString::GetLength() const
{
   return m_nStringLen; // actuall length of string
} // ACString::GetLength()

/*--------------------------------------------------------------+
| ACString::IsEmpty()                                           |
|                                                               |
| Rafaî Zabdyr, 11.12.2000                                      |
+--------------------------------------------------------------*/
BOOL ACString::IsEmpty() const
{
   return m_nStringLen > 0 ? FALSE : TRUE;
} // ACString::IsEmpty()

/*--------------------------------------------------------------+
| ACString::Empty()                                             |
|                                                               |
| Rafaî Zabdyr, 11.12.2000                                      |
+--------------------------------------------------------------*/
void ACString::Empty()
{
   delete[] m_pszString;
   ACString();
} // ACString::Empty()

/*--------------------------------------------------------------+
| ACString::GetAt(int)                                          |
|                                                               |
| Rafaî Zabdyr, 11.12.2000                                      |
+--------------------------------------------------------------*/
char ACString::GetAt(int nIndex) const
{
   if ((nIndex < 0) || (nIndex > m_nStringLen))
      return '\0'; // error
   return m_pszString[nIndex];
} // ACString::GetAt(int)

/*--------------------------------------------------------------+
| ACString::operator[](int)                                     |
|                                                               |
| Rafaî Zabdyr, 13.12.2000                                      |
+--------------------------------------------------------------*/
char ACString::operator[](int nIndex) const
{
   if ((nIndex < 0) || (nIndex > m_nStringLen))
      return '\0'; // error
   return m_pszString[nIndex];
} // ACString::operator[](int)

/*--------------------------------------------------------------+
| ACString::SetAt(char, int)                                    |
|                                                               |
| Rafaî Zabdyr, 13.12.2000                                      |
+--------------------------------------------------------------*/
void ACString::SetAt(char ch, int nIndex)
{
   if ((nIndex < 0) || (nIndex > m_nStringLen))
      return; // error
   m_pszString[nIndex] = ch;
} // ACString::SetAt(char, int)

/*--------------------------------------------------------------+
| ACString::LPCTSTR()                                           |
|                                                               |
| Rafaî Zabdyr, 13.12.2000                                      |
+--------------------------------------------------------------*/
inline char *ACString::LPCTSTR() const
{
   return m_pszString;
} // ACString::LPCTSTR()

/*--------------------------------------------------------------+
| ACString::operator=(const ACString&)                          |
|                                                               |
| Rafaî Zabdyr, 13.12.2000                                      |
+--------------------------------------------------------------*/
const ACString& ACString::operator=(const ACString& stringSrc)
{
   if (this != &stringSrc) // the same ?
   {
      delete[] m_pszString;
      ACString(stringSrc);
   }
   return *this;
} // ACString::operator=(const ACString&)

/*--------------------------------------------------------------+
| ACString::operator=(char)                                     |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
/*const ACString& ACString::operator=(char ch)
{
   delete[] m_pszString;
   ACString((char)ch);
   return *this;
}*/ // ACString::operator=(char)

/*--------------------------------------------------------------+
| ACString::operator=(const char*)                              |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
/*const ACString& ACString::operator=(const char *psz)
{
   delete[] m_pszString;
   ACString((const char*)psz);
   return *this;
}*/ // ACString::operator=(const char*)

/*--------------------------------------------------------------+
| operator+(const ACString&, const ACString&)                   |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
ACString operator+(const ACString& string1, const ACString& string2)
{
   char* pszTemp = new char[string1.GetLength() + string2.GetLength() + 1]; // 1 for NULL

   memcpy(pszTemp, string1.LPCTSTR(), string1.GetLength()); // copy
   memcpy(pszTemp + string1.GetLength(), string2.LPCTSTR(), string2.GetLength()); // concatenate
   pszTemp[string1.GetLength() + string2.GetLength()] = '\0'; // NULL
   ACString sum(pszTemp);
   delete[] pszTemp;

   return sum;
} // operator+(const ACString&, const ACString&)

/*--------------------------------------------------------------+
| operator+(const ACString&, char)                              |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
/*ACString operator+(const ACString& string, char ch)
{
   char* pszTemp = new char[string.GetLength() + 2]; // 1 for ch & 1 for NULL (1+1=2)

   memcpy(pszTemp, string.LPCTSTR(), string.GetLength()); // copy
   pszTemp[string.GetLength()] = ch; // add ch
   pszTemp[string.GetLength() + 1] = '\0'; // NULL
   ACString sum(pszTemp);
   delete[] pszTemp;

   return sum;
}*/ // operator+(const ACString&, char)

/*--------------------------------------------------------------+
| operator+(char ch, const ACString&)                           |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
/*ACString operator+(char ch, const ACString& string)
{
   char* pszTemp = new char[string.GetLength() + 2]; // 1 for ch & 1 for NULL (1+1=2)

   pszTemp[0] = ch; // copy ch
   memcpy(pszTemp + 1, string.LPCTSTR(), string.GetLength()); // add (copy)
   pszTemp[string.GetLength() + 1] = '\0'; // NULL
   ACString sum(pszTemp);
   delete[] pszTemp;

   return sum;
}*/ // operator+(char ch, const ACString&)

/*--------------------------------------------------------------+
| operator+(const ACString&, const char*)                       |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
/*ACString operator+(const ACString& string, const char *psz)
{
   int nStrLen = (psz == NULL) ? 0 : strlen(psz);
   char* pszTemp = new char[string.GetLength() + nStrLen + 1]; // 1 for NULL

   if (psz)
      memcpy(pszTemp, string.LPCTSTR(), string.GetLength()); // copy
   memcpy(pszTemp + string.GetLength(), psz, nStrLen); // concatenate
   pszTemp[string.GetLength() + nStrLen] = '\0'; // NULL
   ACString sum(pszTemp);
   delete[] pszTemp;

   return sum;
}*/ // operator+(const ACString&, const char*)

/*--------------------------------------------------------------+
| operator+(const ACString&, const char*)                       |
|                                                               |
| Rafaî Zabdyr, 16.12.2000                                      |
+--------------------------------------------------------------*/
/*ACString operator+(const char *psz, const ACString& string)
{
   int nStrLen = (psz == NULL) ? 0 : strlen(psz);
   char* pszTemp = new char[nStrLen + string.GetLength()+ 1]; // 1 for NULL

   if (psz)
      memcpy(pszTemp, psz, nStrLen); // copy
   memcpy(pszTemp + nStrLen, string.LPCTSTR(), string.GetLength()); // concatenate
   pszTemp[nStrLen + string.GetLength()] = '\0'; // NULL
   ACString sum(pszTemp);
   delete[] pszTemp;

   return sum;
}*/ // operator+(const ACString&, const char*)

/*--------------------------------------------------------------+
| ACString::operator+=(const ACString&)                         |
|                                                               |
| Rafaî Zabdyr, 23.12.2000                                      |
+--------------------------------------------------------------*/
const ACString& ACString::operator+=(const ACString& stringSrc)
{
   char *pszTemp = new char[m_nStringLen + stringSrc.GetLength() + 1]; // 1 for NULL

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString operator+=(const ACString&) }* ";
   cout << "allocated memory = #$" << m_nStringLen + stringSrc.GetLength() + 1
        << "; pointer = $" << hex << long(pszTemp) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp) // not NULL
   {
      memcpy(pszTemp, m_pszString, m_nStringLen); // first copy actuall string
      memcpy(pszTemp + m_nStringLen, stringSrc.LPCTSTR(), stringSrc.GetLength()); // concatenate
      pszTemp[m_nStringLen + stringSrc.GetLength()] = '\0'; // NULL
      delete[] m_pszString; // delete old
      m_nStringLen += stringSrc.GetLength(); // string lenght
      m_nMemSize = m_nStringLen + 1; // size of alocated memory
      m_pszString = pszTemp; // pointer
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }

   return *this;
} // ACString::operator+=(const ACString&)

/*--------------------------------------------------------------+
| ACString::operator+=(char)                                    |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
/*const ACString& ACString::operator+=(char ch)
{
   char *pszTemp = new char[m_nStringLen + 2]; // 1 for char & 1 for NULL

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString operator+=(char) }* ";
   cout << "allocated memory = #$" << m_nStringLen + 2 << "; pointer = $"
        << hex << long(pszTemp) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp) // not NULL
   {
      memcpy(pszTemp, m_pszString, m_nStringLen); // first copy actuall string
      pszTemp[m_nStringLen] = ch; // concatenate
      pszTemp[m_nStringLen + 1] = '\0'; // NULL
      delete[] m_pszString; // delete old
      m_nStringLen++; // string lenght
      m_nMemSize++; // size of alocated memory
      m_pszString = pszTemp; // pointer
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }

   return *this;
}*/ // ACString::operator+=(char)

/*--------------------------------------------------------------+
| ACString::operator+=(const char*)                             |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
/*const ACString& ACString::operator+=(const char *psz)
{
   int nStrLen = (psz == NULL) ? 0 : strlen(psz);
   char *pszTemp = new char[m_nStringLen + nStrLen + 1]; // 1 for NULL

#ifdef _DEBUG_ACSTRING
   cout.flush();
   cout << "*debug{ ACString operator+=(const char*) }* ";
   cout << "allocated memory = #$" << m_nStringLen + nStrLen + 1
        << "; pointer = $" << hex << long(pszTemp) << '\n';
   cout.flush();
#endif // _DEBUG_ACSTRING

   if (pszTemp) // not NULL
   {
      memcpy(pszTemp, m_pszString, m_nStringLen); // first copy actuall string
      if (psz)
         memcpy(pszTemp + m_nStringLen, psz, nStrLen); // concatenate
      pszTemp[m_nStringLen + nStrLen] = '\0'; // NULL
      delete[] m_pszString; // delete old
      m_nStringLen += nStrLen; // string lenght
      m_nMemSize = m_nStringLen + 1; // size of alocated memory
      m_pszString = pszTemp; // pointer
#ifdef _DEBUG_ACSTRING
      cout << "string =\"" << m_pszString << "\"\n";
      cout.flush();
#endif // _DEBUG_ACSTRING
   }

   return *this;
}*/ // ACString::operator+=(const char*)

/*--------------------------------------------------------------+
| operator==(const ACString&)                                   |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
BOOL operator==(const ACString& string1, const ACString& string2)
{
   return (strcmp(string1.LPCTSTR(), string2.LPCTSTR()) == 0);
} // operator==(const ACString&)

/*--------------------------------------------------------------+
| operator!=(const ACString&)                                   |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
BOOL operator!=(const ACString& string1, const ACString& string2)
{
   return (strcmp(string1.LPCTSTR(), string2.LPCTSTR()) != 0);
} // operator!=(const ACString&)

/*--------------------------------------------------------------+
| operator<(const ACString&)                                    |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
BOOL operator<(const ACString& string1, const ACString& string2)
{
   return (strcmp(string1.LPCTSTR(), string2.LPCTSTR()) < 0);
} // operator<(const ACString&)

/*--------------------------------------------------------------+
| operator>(const ACString&)                                    |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
BOOL operator>(const ACString& string1, const ACString& string2)
{
   return (strcmp(string1.LPCTSTR(), string2.LPCTSTR()) > 0);
} // operator<(const ACString&)

/*--------------------------------------------------------------+
| operator<=(const ACString&)                                   |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
BOOL operator<=(const ACString& string1, const ACString& string2)
{
   return (strcmp(string1.LPCTSTR(), string2.LPCTSTR()) <= 0);
} // operator<=(const ACString&)

/*--------------------------------------------------------------+
| operator>=(const ACString&)                                   |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
BOOL operator>=(const ACString& string1, const ACString& string2)
{
   return (strcmp(string1.LPCTSTR(), string2.LPCTSTR()) >= 0);
} // operator>=(const ACString&)

/*--------------------------------------------------------------+
| ACString::Compare(const ACString&)                            |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
int ACString::Compare(const ACString& string) const
{
   return strcmp(m_pszString, string.LPCTSTR());
} // ACString::Compare(const ACString&)

/*--------------------------------------------------------------+
| ACString::Compare(const char*)                                |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
int ACString::Compare(const char *psz) const
{
   return strcmp(m_pszString, psz);
} // ACString::Compare(const char*)

/*--------------------------------------------------------------+
| ACString::CompareNoCase(const ACString&)                      |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
int ACString::CompareNoCase(const ACString& string) const
{
#ifdef LINUX
   return strcasecmp(m_pszString, string.LPCTSTR());
#else
   return stricmp(m_pszString, string.LPCTSTR());
#endif   
} // ACString::CompareNoCase(const ACString&)

/*--------------------------------------------------------------+
| ACString::CompareNoCase(const char*)                          |
|                                                               |
| Rafaî Zabdyr, 24.12.2000                                      |
+--------------------------------------------------------------*/
int ACString::CompareNoCase(const char *psz) const
{
#ifdef LINUX
   return strcasecmp(m_pszString, psz);
#else
   return stricmp(m_pszString, psz);
#endif
} // ACString::CompareNoCase(const char*)

/*--------------------------------------------------------------+
| ACString::Mid(int)                                            |
|                                                               |
| Rafaî Zabdyr, 25.12.2000                                      |
+--------------------------------------------------------------*/
ACString ACString::Mid(int nFirst) const
{
   if ((nFirst >= 0) && (m_nStringLen > 0) && (nFirst < m_nStringLen)) // ok?
   {
      int nSize = m_nStringLen - nFirst; // chars number to extract
      char *pszTemp = new char[nSize];

      memcpy(pszTemp, m_pszString + nFirst, nSize);
      ACString string(pszTemp, nSize); // not NULL termainted string
      return string;
   }
   else // empty string
   {
      ACString string;
      return string;
   }
} // ACString::Mid(int)

/*--------------------------------------------------------------+
| ACString::Mid(int, int)                                       |
|                                                               |
| Rafaî Zabdyr, 25.12.2000                                      |
+--------------------------------------------------------------*/
ACString ACString::Mid(int nFirst, int nCount) const
{
   if ((nFirst >= 0) && (nCount > 0) && (m_nStringLen > 0) && (nFirst < m_nStringLen)) // ok?
   {
      int nSize = nFirst + nCount > m_nStringLen ? m_nStringLen - nFirst : nCount; // chars number to extract
      char *pszTemp = new char[nSize];

      memcpy(pszTemp, m_pszString + nFirst, nSize);
      ACString string(pszTemp, nSize); // not NULL termainted string
      return string;
   }
   else // empty string
   {
      ACString string;
      return string;
   }
} // ACString::Mid(int, int)

/*--------------------------------------------------------------+
| ACString::Left(int)                                           |
|                                                               |
| Rafaî Zabdyr, 25.12.2000                                      |
+--------------------------------------------------------------*/
ACString ACString::Left(int nCount) const
{
   if ((nCount > 0) && (m_nStringLen > 0))
   {
      if (nCount > m_nStringLen) // wants more characters than there is
         nCount = m_nStringLen;

      char *pszTemp = new char[nCount];

      memcpy(pszTemp, m_pszString, nCount);
      ACString string(pszTemp, nCount); // not NULL termainted string
      return string;
   }
   else // empty string
   {
      ACString string;
      return string;
   }
} // ACString::Left(int)

/*--------------------------------------------------------------+
| ACString::Right(int)                                          |
|                                                               |
| Rafaî Zabdyr, 26.12.2000                                      |
+--------------------------------------------------------------*/
ACString ACString::Right(int nCount) const
{
   if ((nCount > 0) && (m_nStringLen > 0))
   {
      if (nCount > m_nStringLen) // wants more characters than there is
         nCount = m_nStringLen;

      char *pszTemp = new char[nCount];

      memcpy(pszTemp, m_pszString + m_nStringLen - nCount, nCount);
      ACString string(pszTemp, nCount); // not NULL termainted string
      return string;
   }
   else // empty string
   {
      ACString string;
      return string;
   }
} // ACString::Right(int)

/*--------------------------------------------------------------+
| ACString::SpanIncluding(const char*)                          |
|                                                               |
| Rafaî Zabdyr, 26.12.2000                                      |
+--------------------------------------------------------------*/
ACString ACString::SpanIncluding(const char *psz) const
{
   return *this;
} // ACString::SpanIncluding(const char*)

/*--------------------------------------------------------------+
| ACString::SpanExcluding(const char*)                          |
|                                                               |
| Rafaî Zabdyr, 26.12.2000                                      |
+--------------------------------------------------------------*/
ACString ACString::SpanExcluding(const char *psz) const
{
   return *this;
} // ACString::SpanExcluding(const char*)
