/*

    TDolphin projects

    (c) TDolphin 2005-2009

    td_txtconv.cpp

    Text conversion routines (ISO, UNICODE, UTF8), only Polish letters!!!!.

    created: 2.09.2006
       last: 14.12.2009

*/

#include <iostream>

//#define __TD_DEBUG

#include "td_txtconv.h"
#include "td_common_defines.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
// namespace tdtxtconv
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// tdtxtconv::ConvertISO88592_TO_UNICODE
//
// Rafal Zabdyr, 11.09.2006
//==============================================================================
unsigned int *tdtxtconv::ConvertISO88592_TO_UNICODE(const char *A_strISO)
{
   /*if (!A_strISO)
      return;

   int nLen = strlen(A_strISO);
   unsigned int *strUNICODE = malloc((nLen+1) * sizeof(unsigned int));

   for (int i = 0; i <= nLen; i++)
      strUNICODE[i] = G_aISO2UNICODE[A_strISO[i]];

   return strUNICODE;*/

   return NULL;
}

//==============================================================================
// tdtxtconv::ConvertISO88592_TO_UTF8
//
// Rafal Zabdyr, 11.09.2006
//==============================================================================
char *tdtxtconv::ConvertISO88592_TO_UTF8(const char *A_strISO)
{
   if (!A_strISO)
      return NULL;

   int i, j = 0, nUTF8Len = 0, nLen = 0;
   unsigned char chElem;

   for (i = 0; ; i++)
   {
      chElem = A_strISO[i];
      if (chElem == '\0')
         break;

      if (chElem == 0xb1 || chElem == 0xa1 || chElem == 0xe6 || chElem == 0xc6 || chElem == 0xea || chElem == 0xca
         || chElem == 0xb3 || chElem == 0xa3 || chElem == 0xf3 || chElem == 0xd3 || chElem == 0xb6 || chElem == 0xa6
         || chElem == 0xbc || chElem == 0xac || chElem == 0xbf || chElem == 0xaf || chElem == 0xf1 || chElem == 0xd1)
         nUTF8Len++;

      nLen++;
      nUTF8Len++;
   }

   TD_DEBUG( cout << "nLen = " << nLen << " nUTF8Len = " << nUTF8Len << endl; )

   char *strUTF8 = new char[nUTF8Len + 1];
   char chA = 0, chB = 0;

   for (i = 0, j = 0; i <= nLen; i++, j++)
   {
      chA = 0; chB = 0;
      chElem = A_strISO[i];
      switch (chElem)
      {
         case 0xb1:
            chA = 0xc4;
            chB = 0x85;
            break;

         case 0xa1:
            chA = 0xc4;
            chB = 0x84;
            break;

         case 0xe6:
            chA = 0xc4;
            chB = 0x87;
            break;

         case 0xc6:
            chA = 0xc4;
            chB = 0x86;
            break;

         case 0xea:
            chA = 0xc4;
            chB = 0x99;
            break;

         case 0xca:
            chA = 0xc4;
            chB = 0x98;
            break;

         case 0xb3:
            chA = 0xc5;
            chB = 0x82;
            break;

         case 0xa3:
            chA = 0xc5;
            chB = 0x81;
            break;

         case 0xf3:
            chA = 0xc3;
            chB = 0xb3;
            break;

         case 0xd3:
            chA = 0xc3;
            chB = 0x93;
            break;

         case 0xb6:
            chA = 0xc5;
            chB = 0x9b;
            break;

         case 0xa6:
            chA = 0xc5;
            chB = 0x9a;
            break;

         case 0xbc:
            chA = 0xc5;
            chB = 0xba;
            break;

         case 0xac:
            chA = 0xc5;
            chB = 0xb9;
            break;

         case 0xbf:
            chA = 0xc5;
            chB = 0xbc;
            break;

         case 0xaf:
            chA = 0xc5;
            chB = 0xbb;
            break;

         case 0xf1:
            chA = 0xc5;
            chB = 0x84;
            break;

         case 0xd1:
            chA = 0xc5;
            chB = 0x83;
            break;

         default:
            strUTF8[j] = chElem;
      };

      if (chA != 0 || chB != 0)
      {
         strUTF8[j++] = chA;
         strUTF8[j] = chB;
      }
   }

   return strUTF8;
}


