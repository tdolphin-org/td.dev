/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_sdl_resource.h

    SDL resources (images/fonts) support (module) for all TDolphin's projects
    (C++ programs) using SDL

    created: 26.09.2005
       last: 12.02.2012

*/

#ifndef __TD_SDL_RESOURCE_H
#define __TD_SDL_RESOURCE_H



#include "td_singleton_template.h"


// defines

#define __TD_SDL_MAX_RESOURCES   32
#define __TD_SDL_MAX_FONTS       8


// types/enums

// structs/classes

//==============================================================================
// class cTDResourceArray
//==============================================================================
class cTDResourceArray
{
   friend class TDSingleton<cTDResourceArray>;

   cTDResourceArray();
   cTDResourceArray(const cTDResourceArray&);

   void reset(void);

public:
   ~cTDResourceArray();

   void free_all(void); // free all resources
   void set_tcolor(Uint8 A_colorR, Uint8 A_colorG, Uint8 A_colorB);
   int load(const char *A_strFileName, bool A_bTransparent, bool A_bConvert, int A_iResource = TD_RETIDX_ERR);
   int add(SDL_Surface *A_pSurface, int A_iResource = TD_RETIDX_ERR);
   char free(int A_iResource);

   SDL_Surface *operator[](int A_iResource) const;

// members
private:
   SDL_Surface *m_aImages[__TD_SDL_MAX_RESOURCES]; // array of images
   struct 
   {
      Uint8 R, // transparent color
            G,
            B;
   } m_colorTransparent;
};

typedef TDSingleton<cTDResourceArray> cTDResources;

//==============================================================================
// class cTDResourcesScope
//==============================================================================
class cTDResourcesScope
{
public:
   cTDResourcesScope() {}
   ~cTDResourcesScope() { cTDResources::instance().free_all(); }
};

//==============================================================================
// class cTDFontArray
//==============================================================================

class cTDFontArray
{
   friend class TDSingleton<cTDFontArray>;

   cTDFontArray();
   cTDFontArray(const cTDFontArray&);

   void reset(void);
public:
   ~cTDFontArray();

   void close_all(void); // free all resources
   int open(const char *A_strFontName, unsigned int A_nSize, int A_iFont = TD_RETIDX_ERR);
   char close(int A_iFont);

   TTF_Font *operator[](int A_iFont) const;

// members
private:
   TTF_Font *m_aFonts[__TD_SDL_MAX_FONTS]; // array of fonts
};

typedef TDSingleton<cTDFontArray> cTDFonts;

//==============================================================================
// class cTDFontsScope
//==============================================================================
class cTDFontsScope
{
public:
   cTDFontsScope() {}
   ~cTDFontsScope() { cTDFonts::instance().close_all(); }
};


// prototypes



#endif // __TD_SDL_RESOURCE_H

