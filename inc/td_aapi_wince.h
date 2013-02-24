/*

    TDolphin projects

    (c) TDolphin 2007

    td_aapi_wince.h

    Abstract API (graphics/sound/input) via WindowsCE/GAPI for TDolphin's projects (C++)

    created: 30.12.2007
       last: 30.12.2007

*/

#ifndef __TD_AAPI_WINCE_H
#define __TD_AAPI_WINCE_H



// defines

// types/enums

typedef signed char Sint8;
typedef unsigned char Uint8;
typedef signed short Sint16; // do weryfikacji ze sizeof(short) = 2 (dla eVC)
typedef unsigned short Uint16; // jw
typedef signed int Sint32; // do weryfikacji ze sizeof(int) = 4 (dla eVC)
typedef unsigned int Uint32; // jw

// structs/classes

////////////////////////////////////////////////////////////////////////////////
// sTDRect
////////////////////////////////////////////////////////////////////////////////
struct sTDRect
{
   sTDRect() : x(0), y(0), w(0), h(0) { }
   sTDRect(Sint16 _x, Sint16 _y, Uint16 _w, Uint16 _h) : x(_x), y(_y), w(_w), h(_h) { }

   Sint16 x, y;
   Uint16 w, h;
};

////////////////////////////////////////////////////////////////////////////////
// sTDColor
////////////////////////////////////////////////////////////////////////////////
struct sTDColor
{
   sTDColor() : r(0), g(0), b(0) {}
   sTDColor(Uint8 _r, Uint8 _g, Uint8 _b) : r(_r), g(_g), b(_b) {}

   Uint8 r;
   Uint8 g;
   Uint8 b;
   Uint8 unused;
};

////////////////////////////////////////////////////////////////////////////////
// sTDPalette
////////////////////////////////////////////////////////////////////////////////
struct sTDPalette
{
   sTDPalette() : _aColors(NULL), nColors(0) {}
   sTDPalette(const sTDPalette &_obj)
   {
      aColors = new sTDColors[_obj.nColors];
      nColors = _obj.nColors;
      for(int i = 0; i < nColors; i++)
         aColors[i] = _obj.aColors[i];
   }
   ~sTDPalette() { delete[] aColors; }

   sTDPalette& operator=(const sTDPalette& _obj)
   {
      aColors = new sTDColors[_obj.nColors];
      nColors = _obj.nColors;
      for(int i = 0; i < nColors; i++)
         aColors[i] = _obj.aColors[i];
   }

   int size() const { return nColors; }
   sTDColor operator[](unsigned int _idx) const { return aColors[_idx]; } // nie sprawdza granic tablicy

private:
   sTDColor *aColors;
   int nColors;
}

////////////////////////////////////////////////////////////////////////////////
// sTDPixelFormat
////////////////////////////////////////////////////////////////////////////////
struct sTDPixelFormat
{
private:
   sTDPalette *palette;
   Uint8  BitsPerPixel;
   Uint8  BytesPerPixel;
   Uint8  Rloss;
   Uint8  Gloss;
   Uint8  Bloss;
   Uint8  Aloss;
   Uint8  Rshift;
   Uint8  Gshift;
   Uint8  Bshift;
   Uint8  Ashift;
   Uint32 Rmask;
   Uint32 Gmask;
   Uint32 Bmask;
   Uint32 Amask;

   /* RGB color key information */
   Uint32 colorkey;
   /* Alpha value information (per-surface alpha) */
   Uint8  alpha;
};

////////////////////////////////////////////////////////////////////////////////
// sTDSurface
////////////////////////////////////////////////////////////////////////////////
struct sTDSurface
{
   sTDSurface(unsigned int w, unsigned int h); // depth ?

   sTDPixelFormat *format;
   Uint16 w, h;
   void *pixels;
};

////////////////////////////////////////////////////////////////////////////////
// cTDgapiScreen
// don't use this class explicity in code, use : cTDScreen !!!
////////////////////////////////////////////////////////////////////////////////
class cTDgapiScreen : public iTDScreen
{
   friend class TDSingleton<cTDgapiScreen>;

   cTDgapiScreen();
   cTDgapiScreen(const cTDgapiScreen&);
   ~cTDgapiScreen();

public:
   // ...

};

typedef TDSingleton<cTDgapiScreen> cTDScreen;


#endif // __TD_AAPI_WINECE_H
