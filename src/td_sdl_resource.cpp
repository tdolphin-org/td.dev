/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_sdl_resource.cpp

    SDL resources (images/fonts) support (module) for all TDolphin's projects
    (C++ programs) using SDL

    created: 26.09.2005
       last: 12.02.2012

*/

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

//#define __TD_DEBUG

#include "td_common_defines.h"
#include "td_sdl_resource.h"

using namespace std;

// global variables


//==============================================================================
// class cTDResourceArray
//==============================================================================

//==============================================================================
// cTDResourceArray::cTDResourceArray
//
// Rafal Zabdyr, 15.10.2005
//==============================================================================
cTDResourceArray::cTDResourceArray()
{
   TD_DEBUG( cout << "cTDResourceArray::cTDResourceArray()" << endl; )

   reset();
}

//==============================================================================
// cTDResourceArray::~cTDResourceArray
//
// Rafal Zabdyr, 16.10.2005
//==============================================================================
cTDResourceArray::~cTDResourceArray()
{
   TD_DEBUG( cout << "cTDResourceArray::~cTDResourceArray()" << endl; )

   free_all();
}

//==============================================================================
// cTDResourceArray::reset
//
// Rafal Zabdyr, 27.09.2005
//==============================================================================
void cTDResourceArray::reset(void)
{
   TD_DEBUG( cout << "cTDResourceArray::reset()" << endl; )

   for (int i = 0; i < __TD_SDL_MAX_RESOURCES; i++)
      m_aImages[i] = NULL;

   m_colorTransparent.R = 0;
   m_colorTransparent.G = 0;
   m_colorTransparent.B = 0;
}

//==============================================================================
// cTDResourceArray::free_all
//
// free all resources
//
// Rafal Zabdyr, 27.09.2005
//==============================================================================
void cTDResourceArray::free_all(void)
{
   TD_DEBUG( cout << "cTDResourceArray::free_all()" << endl; )

   for (int i = 0; i < __TD_SDL_MAX_RESOURCES; i++)
      if (m_aImages[i])
         SDL_FreeSurface(m_aImages[i]);

   reset();
}

//==============================================================================
// cTDResourceArray::set_tcolor
//
// Rafal Zabdyr, 27.09.2005
//==============================================================================
void cTDResourceArray::set_tcolor(Uint8 A_colorR, Uint8 A_colorG, Uint8 A_colorB)
{
   m_colorTransparent.R = A_colorR;
   m_colorTransparent.G = A_colorG;
   m_colorTransparent.B = A_colorB;
}

//==============================================================================
// cTDResourceArray::load
//
//  A_iResource - if != TD_RETIDX_ERR then means forced index to load into
//
// Rafal Zabdyr, 27.09.2005
//==============================================================================
int cTDResourceArray::load(const char *A_strFileName, bool A_bTransparent, bool A_bConvert, int A_iResource /*= TD_RETIDX_ERR*/)
{
   int iFirstFree;
   
   TD_DEBUG( cout << "-> '" << A_strFileName << "' transparent=" << A_bTransparent << " convert=" << A_bConvert << " res_idx=" << A_iResource << endl; )

   if (!A_strFileName)
      return TD_RETIDX_ERR;

   if ((A_iResource < TD_RETIDX_ERR) || (A_iResource >= __TD_SDL_MAX_RESOURCES))
   {
      if (A_iResource >= __TD_SDL_MAX_RESOURCES)

      A_iResource = TD_RETIDX_ERR;
   }

   if (A_iResource == TD_RETIDX_ERR)
   {
      for (iFirstFree = 0; iFirstFree < __TD_SDL_MAX_RESOURCES; iFirstFree++)
         if (!m_aImages[iFirstFree])
            break;
   }
   else
   {
      if (A_iResource < 0)
      {
         TD_ERROR( cerr << "ERROR: negativ index" << endl; )
         return TD_RETIDX_ERR;
      }
      iFirstFree = A_iResource;
   }

   if (iFirstFree >= __TD_SDL_MAX_RESOURCES) // check if no more free resources
   {
      cerr << "ERROR: out of free resources [" << __TD_SDL_MAX_RESOURCES << "]" << endl;
      return TD_RETIDX_ERR;
   }

   if (m_aImages[iFirstFree]) // check if free (possile only when A_iResource != TD_RETIDX_ERR)
   {
      cerr << "ERROR: not free at : iFirstFree=" << iFirstFree << " m_aImages[iFirstFree]=" << m_aImages[iFirstFree] << endl;
      return TD_RETIDX_ERR;
   }

   TD_DEBUG( cout << " ... loading ... " << A_strFileName << " ..." << endl; )
   m_aImages[iFirstFree] = IMG_Load(A_strFileName);

   if (!m_aImages[iFirstFree]) // load error
   {
      TD_DEBUG( cout << "failed" << endl; )
      return TD_RETIDX_ERR;
   }

   TD_DEBUG( cout << "ok" << endl; )

   if (A_bConvert)
   {
      SDL_Surface *pSurface = SDL_DisplayFormat(m_aImages[iFirstFree]);
      if (pSurface) // convert error
      {
         SDL_FreeSurface(m_aImages[iFirstFree]);
         m_aImages[iFirstFree] = pSurface;
      }
   }

   if (A_bTransparent)
   {
      Uint32 colorTransparent = SDL_MapRGB(m_aImages[iFirstFree]->format, m_colorTransparent.R, m_colorTransparent.G, m_colorTransparent.B);
      SDL_SetColorKey(m_aImages[iFirstFree], SDL_SRCCOLORKEY, colorTransparent);
   }

   return iFirstFree;
}

//==============================================================================
// cTDResourceArray::add
//
//  A_iResource - if != TD_RETIDX_ERR then means forced index to add into
//
// Rafal Zabdyr, 19.10.2008
//==============================================================================
int cTDResourceArray::add(SDL_Surface *A_pSurface, int A_iResource /*= TD_RETIDX_ERR*/)
{
   int iFirstFree;
   
   TD_DEBUG( ; )

   if (!A_pSurface)
      return TD_RETIDX_ERR;

   if ((A_iResource < TD_RETIDX_ERR) || (A_iResource >= __TD_SDL_MAX_RESOURCES))
      A_iResource = TD_RETIDX_ERR;

   if (A_iResource == TD_RETIDX_ERR)
   {
      for (iFirstFree = 0; iFirstFree < __TD_SDL_MAX_RESOURCES; iFirstFree++)
         if (!m_aImages[iFirstFree])
            break;
   }
   else
   {
      if (A_iResource < 0)
         return TD_RETIDX_ERR;
      iFirstFree = A_iResource;
   }

   if (iFirstFree >= __TD_SDL_MAX_RESOURCES) // check if no more free resources
      return TD_RETIDX_ERR;

   if (m_aImages[iFirstFree]) // check if free (possile only when A_iResource != TD_RETIDX_ERR)
      return TD_RETIDX_ERR;

   m_aImages[iFirstFree] = A_pSurface;

   return iFirstFree;
}

//==============================================================================
// cTDResourceArray::free
//
// Rafal Zabdyr, 27.09.2005
//==============================================================================
char cTDResourceArray::free(int A_iResource)
{
   if ((A_iResource < 0) || (A_iResource >= __TD_SDL_MAX_RESOURCES))
      return FALSE;

   SDL_FreeSurface(m_aImages[A_iResource]);
   m_aImages[A_iResource] = NULL;

   return TRUE;
}

//==============================================================================
// cTDResourceArray::operator[]
//
// Rafal Zabdyr, 27.09.2005
//==============================================================================
SDL_Surface *cTDResourceArray::operator[](int A_iResource) const
{
   if ((A_iResource < 0) || (A_iResource >= __TD_SDL_MAX_RESOURCES))
      return NULL;

   return m_aImages[A_iResource];
}


//==============================================================================
// class cTDFontArray
//==============================================================================

//==============================================================================
// cTDFontArray::cTDFontArray
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
cTDFontArray::cTDFontArray()
{
   TD_DEBUG( cout << "cTDFontArray::cTDFontArray() &" << (int *)this << endl; )

   reset();
}

//==============================================================================
// cTDFontArray::~cTDFontArray
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
cTDFontArray::~cTDFontArray()
{
   TD_DEBUG( cout << "cTDFontArray::~cTDFontArray()" << endl; )

   close_all();
}

//==============================================================================
// cTDFontArray::reset
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
void cTDFontArray::reset(void)
{
   TD_DEBUG( cout << "cTDFontArray::reset()" << endl; )

   for (int i = 0; i < __TD_SDL_MAX_FONTS; i++)
      m_aFonts[i] = NULL;
}

//==============================================================================
// cTDFontArray::close_all
//
// free all resources
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
void cTDFontArray::close_all(void)
{
   TD_DEBUG( cout << "cTDFontArray::close_all()" << endl; )

   for (int i = 0; i < __TD_SDL_MAX_FONTS; i++)
      if (m_aFonts[i])
         TTF_CloseFont(m_aFonts[i]);

   reset();
}

//==============================================================================
// cTDFontArray::open
//
//  A_iFont - if != TD_RETIDX_ERR then means forced index to load into
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
int cTDFontArray::open(const char *A_strFontName, unsigned int A_nSize, int A_iFont /*= TD_RETIDX_ERR*/)
{
   int iFirstFree;
   
   TD_DEBUG( cout << "-> '" << A_strFontName << "' size: " << A_nSize << " idx:" << A_iFont << endl; )

   if (!A_strFontName)
      return TD_RETIDX_ERR;

   if ((A_iFont < TD_RETIDX_ERR) || (A_iFont >= __TD_SDL_MAX_FONTS))
      A_iFont = TD_RETIDX_ERR;

   if (A_iFont == TD_RETIDX_ERR)
   {
      for (iFirstFree = 0; iFirstFree < __TD_SDL_MAX_FONTS; iFirstFree++)
         if (!m_aFonts[iFirstFree])
            break;
   }
   else
   {
      if (A_iFont < 0)
         return TD_RETIDX_ERR;
      iFirstFree = A_iFont;
   }

   if (iFirstFree >= __TD_SDL_MAX_FONTS) // check if no more free fonts resources
      return TD_RETIDX_ERR;

   if (m_aFonts[iFirstFree]) // check if free (possile only when A_iFont != TD_RETIDX_ERR)
   {
      TD_ERROR( cerr << "index already in use" << endl; )
      return TD_RETIDX_ERR;
   }

   TD_DEBUG( cout << " ... opening font ... " << A_strFontName << " ..." << cout; )
   m_aFonts[iFirstFree] = TTF_OpenFont(A_strFontName, A_nSize);

   if (!m_aFonts[iFirstFree]) // load error
   {
      TD_ERROR( cerr << "failed" << endl; )
      return TD_RETIDX_ERR;
   }

   TD_DEBUG( cout << "ok" << endl; )

   return iFirstFree;
}

//==============================================================================
// cTDFontArray::close
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
char cTDFontArray::close(int A_iFont)
{
   if ((A_iFont < 0) || (A_iFont >= __TD_SDL_MAX_FONTS))
      return FALSE;

   TTF_CloseFont(m_aFonts[A_iFont]);
   m_aFonts[A_iFont] = NULL;

   return TRUE;
}

//==============================================================================
// cTDFontArray::operator[]
//
// Rafal Zabdyr, 28.03.2006
//==============================================================================
TTF_Font *cTDFontArray::operator[](int A_iFont) const
{
   if ((A_iFont < 0) || (A_iFont >= __TD_SDL_MAX_FONTS))
      return NULL;

   return m_aFonts[A_iFont];
}
