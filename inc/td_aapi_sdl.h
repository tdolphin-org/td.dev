/*

    TDolphin projects

    (c) TDolphin 2007

    td_aapi_sdl.h

    Abstract API (graphics/sound/input) via SDL for TDolphin's projects (C++)

    created: 30.12.2007
       last: 31.12.2007

*/

#ifndef __TD_AAPI_SDL_H
#define __TD_AAPI_SDL_H



// defines

// types/enums

// structs/classes

////////////////////////////////////////////////////////////////////////////////
// sTDRect
////////////////////////////////////////////////////////////////////////////////

struct sTDRect : public SDL_Rect
{
   sTDRect() : x(0), y(0), w(0), h(0) { }
   sTDRect(Sint16 _x, Sint16 _y, Uint16 _w, Uint16 _h) : x(_x), y(_y), w(_w), h(_h) { }
};

////////////////////////////////////////////////////////////////////////////////
// sTDColor
////////////////////////////////////////////////////////////////////////////////

struct sTDColor : public SDL_Color
{
   sTDColor() : r(0), g(0), b(0) { }
   sTDColor(Uint8 _r, Uint8 _g, Uint8 _b) : r(_r), g(_g), b(_b) { }
   sTDColor(const SDL_Color &_obj) : r(_obj.r), g(_obj.g), b(_obj.b) { }
};

////////////////////////////////////////////////////////////////////////////////
// sTDPalette
////////////////////////////////////////////////////////////////////////////////

struct sTDPalette : private SDL_Palette
{
   int size() const { return ncolors; }
   sTDColor operator[](unsigned int _idx) const { return colors[_idx]; }
};

////////////////////////////////////////////////////////////////////////////////
// sTDPixelFormat
////////////////////////////////////////////////////////////////////////////////

struct sTDPixelFormat : private SDL_PixelFormat
{
}

typedef SDL_Surface sTDSurface; // ??? struct sTDSurface: public SDL_Surface { ... };

////////////////////////////////////////////////////////////////////////////////
// cTDsdlScreen
// class (scope) for Main Screen with Buffers
// don't use this class explicity in code, use : cTDScreen !!!
////////////////////////////////////////////////////////////////////////////////

class cTDsdlScreen : public iTDScreen
{
   friend class TDSingleton<cTDgapiScreen>;

   cTDsdlScreen();

public:
   ~cTDsdlScreen();

   // interface methods
   long Open(int A_nWidth, int A_nHeight, int A_nBitsPerPixel, unsigned int A_flags);
   void ToggleFullScreen();
   void Clear(const sTDColor &A_clrBg);
   void Update(const enum tUpdateEffect A_eEffect = eNone);
   char CopyToBuffer(const enum tScreenBuffer A_eBuffer);
   char RestoreFromBuffer(const enum tScreenBuffer A_eBuffer);

   void BlitSurface(const sTDSurface &A_surfFrom, const sTDRect &A_rcFrom, const enum tScreenBuffer A_eBufTo, const sTDRect &A_rcTo);
   void BlitSurface(const sTDSurface &A_surfFrom, const sTDRect &A_rcFrom, const sTDSurface &A_surfTo, const sTDRect &A_rcTo);

private:
   // ...
   sTDSurface *screen();
   sTDSurface *operator[](enum tScreenBuffer A_eBuffer) const;

   //SDL_Surface *screen() { return m_pMainScreen; }
   //SDL_Surface *operator[](enum tScreenBuffer A_eBuffer) const;

   char alloc_buffers();
   void free_buffers();

   void reset();

// members
private:
   int m_nWidth, m_nHeight, m_nBPP;
   Uint32 m_flagsVideo;
   SDL_Surface *m_pMainScreen;
   SDL_Surface *m_aBuffers[eSBMax]; // array of pointers to Buffers
};

typedef TDSingleton<cTDgapiScreen> cTDScreen;



#endif // __TD_AAPI_SDL_H
