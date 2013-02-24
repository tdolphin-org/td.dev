/*-------------------------------------------------------------+
| (c) ARMO 2000                                      cstring.h |
| (c) TDolphin 2007                                            |
|                                                              |
| created:  7.12.2000                                          |
|    last: 26.10.2007                                          |
+-------------------------------------------------------------*/

#ifndef  __AFCSTRING_H
#define  __AFCSTRING_H


#include "td_common_defines.h"



////////////////////////////////////////////////////////////////
// ACString

class ACString
{
   // constructors & destructor
public:
   ACString();
   ACString(const ACString& stringSrc);
   ACString(char ch, int nRepeat = 1);
   ACString(const char *psz, int nLength);
   ACString(const char *psz);
   ~ACString();

   // functions
public:

   /* The String as an Array */
   inline int GetLength() const; // length of string
   BOOL  IsEmpty() const; // is string empty
   void  Empty();
   char  GetAt(int nIndex) const; // return character at given position
   char operator[](int nIndex) const; // -..-
   void SetAt(char ch, int nIndex); // set character at given position
//   char *operator LPCTSTR() const; // not supported
   inline char *LPCTSTR() const; // return pointer to string

   /* Assignment/Concatenation */
   const ACString& operator=(const ACString& stringSrc);
//   const ACString& operator=(char ch);
//   const ACString& operator=(const char *psz);
   friend ACString operator+(const ACString& string1, const ACString& string2);
//   friend ACString operator+(const ACString& string, char ch);
//   friend ACString operator+(char ch, const ACString& string);
//   friend ACString operator+(const ACString& string, const char *psz);
//   friend ACString operator+(const char *psz, const ACString& string);
   const ACString& operator+=(const ACString& stringSrc);
//   const ACString& operator+=(char ch);
//   const ACString& operator+=(const char *psz);
// !!!! ^= those operators should be enough, becouse constructor do the rest !!!!

   /* Comparision */
   friend BOOL operator==(const ACString& string1, const ACString& string2);
   friend BOOL operator!=(const ACString& string1, const ACString& string2);
   friend BOOL operator<(const ACString& string1, const ACString& string2);
   friend BOOL operator>(const ACString& string1, const ACString& string2);
   friend BOOL operator<=(const ACString& string1, const ACString& string2);
   friend BOOL operator>=(const ACString& string1, const ACString& string2);
   int Compare(const ACString& string) const; // compare two strings (case insensitive)
   int Compare(const char *psz) const; // -..-
   int CompareNoCase(const ACString& string) const; // compare two strings (case insensitive)
   int CompareNoCase(const char *psz) const; // -..-
   // not supported
   int Collate(const ACString& string) const; // compare two locale-string (case insensitive)
   int CollateNoCase(const char *psz) const; // compare two locale-string (case sensitive)
   // not supported

   /* Extraction */
   ACString Mid(int nFirst) const; // extract from nFirst to end
   ACString Mid(int nFirst, int nCount) const; // extract from nFirst, nCount characters
   ACString Left(int nCount) const; // extract nCount characters from left
   ACString Right(int nCount) const; // extract nCount characters from right
   ACString SpanIncluding(const char *psz) const;
   ACString SpanExcluding(const char *psz) const;
   /* Other Conversions */
   void MakeUpper();
   void MakeLower();
   void Format(const char *pszString);

   /* Searching */
   int Find(char ch);
   int Find(const char *psz);

/* Buffer Access */

/* ... */

protected:
   void ClearString() { memset(m_pszString, '\0', m_nStringLen); }; // clear string
   void ClearMemory() { memset(m_pszString, '\0', m_nMemSize); } // clear memory

   // members
protected:
   char *m_pszString; // pointer to string (memory) NULL terminated
   int   m_nStringLen; // actuall size of string
   int   m_nMemSize; // size of allocated bytes (always = m_nStringLen+1)
private:
};


#endif // __AFCSTRING_H
