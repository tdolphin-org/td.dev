/*

    TDolphin projects

    (c) TDolphin 2007

    td_aapi.h

    Abstract API (graphics/sound/input) via SDL for TDolphin's projects (C++)
    main include, interfaces
    must be defined TD_SDL or TD_WINCE

    created: 30.12.2007
       last: 31.12.2007

*/

#ifndef __TD_AAPI_H
#define __TD_AAPI_H



class sTDRect;
class sTDColor;
class sTDPalette;
class sTDPixelFormat;
class sTDSurface;

// interfaces

////////////////////////////////////////////////////////////////////////////////
// iTDScreen
// interface for screen (have to be a scope, private constructor !!!), with basic functionality
////////////////////////////////////////////////////////////////////////////////
class iTDScreen // interface
{
public:
   enum tResolution
   {
      e320x240, // np. dla PDA 320 x 240
      e640x480, // dla PDA lub innych
      eVGA, // inna nazwa 640x480
      e800x600,
      eSVGA,
      e1024x768,
      eXGA,
      e1280x1024,
      eSXGA,
      e1600x1200

      // other resolutions
      e640x240, // dla PDA
   };

   enum tScreenBuffer
   {
      eBackgroundBuf = 0,
      eActionBuf = 1,
      eSBMax = 2
   };

   enum tUpdateEffect
   {
      eNone, // no effect normal full update
      eScanLineBars,
      eRightLeftBars
   };

   virtual ~iTDScreen() {}

   virtual long Open(int A_nWidth, int A_nHeight, int A_nBitsPerPixel, unsigned int A_flags) = 0;
   virtual void ToggleFullScreen() = 0;
   virtual void Clear(const sTDColor &A_clrBg) = 0;
   virtual void Update(const enum tUpdateEffect A_eEffect = eNone) = 0;
   virtual char CopyToBuffer(const enum tScreenBuffer A_eBuffer) = 0;
   virtual char RestoreFromBuffer(const enum tScreenBuffer A_eBuffer) = 0;

   // blitting functions
   virtual void BlitSurface(const sTDSurface &A_surfFrom, const sTDRect &A_rcFrom, const enum tScreenBuffer A_eBufTo, const sTDRect &A_rcTo) = 0;
   virtual void BlitSurface(const sTDSurface &A_surfFrom, const sTDRect &A_rcFrom, const sTDSurface &A_surfTo, const sTDRect &A_rcTo) = 0;

   // ...
private:
   virtual sTDSurface *screen() = 0;
   virtual sTDSurface *operator[](enum tScreenBuffer A_eBuffer) const = 0;
};

// structs/classes

#ifdef TD_SDL
#include "td_sdl_aapi.h"
#elif TD_WINCE
#include "td_wince_aapi.h"
#else
#error "Not defined any base graphics System (SDL/WINCE), use -DTD_SDL or -DTD_WINCE !!!"
#endif // TD_SDL


#endif // __TD_AAPI_H
