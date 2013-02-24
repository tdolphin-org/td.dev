/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_sdl_util.h

    Common definitions/structs/classes/functions/... for all SDL TDolphin's projects (C++)

    // in methods/functions we mostly use pointers to surfaces (not const references),
    // becouse all SDL functions operate on pointers

    created: 22.09.2005
       last: 11.02.2012

*/

#ifndef __TD_SDL_UTIL_H
#define __TD_SDL_UTIL_H



#include "td_stl_vector.h"

// defines

// types/enums

enum tDirection
{
   eDirUp = 0,
   eDirRight = 1,
   eDirDown = 2,
   eDirLeft = 3
};

// functions
namespace tddsl
{
   template<typename T> void overlap_sum(const T& _x, const T& _y) { return _x < _y ? _x : _y; };
};

// structs/classes

////////////////////////////////////////////////////////////////////////////////
// cTDsdlRect
// wrapper class for SDL_Rect
////////////////////////////////////////////////////////////////////////////////
struct cTDsdlRect : public SDL_Rect
{
   cTDsdlRect();
   cTDsdlRect(SDL_Rect &A_rcData);

   cTDsdlRect& operator=(const SDL_Rect &A_rcData);
   cTDsdlRect& operator+(const cTDsdlRect &A_rcData);
   cTDsdlRect& operator+=(const cTDsdlRect &A_rcData);
};

////////////////////////////////////////////////////////////////////////////////
// cTDsdlScope
// scope class for SDL substems (SDL_Init(...), SDL_Quit)
////////////////////////////////////////////////////////////////////////////////
class cTDsdlScope
{
public:
   cTDsdlScope(Uint32 A_flags);
   ~cTDsdlScope();

   bool status() { return m_bInitStatus; }

protected:
   bool m_bInitStatus; // false => error ocurred, true => ok, system initiated
};

////////////////////////////////////////////////////////////////////////////////
// cTDsdlTTFScope
// scope class for TTF (TTF_Init, TTF_Quit)
////////////////////////////////////////////////////////////////////////////////

class cTDsdlTTFScope
{
public:
   cTDsdlTTFScope();
   ~cTDsdlTTFScope();

   bool status() { return m_bInitStatus; }

protected:
   bool m_bInitStatus; // false => error ocurred, true => ok, system initiated
};

////////////////////////////////////////////////////////////////////////////////
// cTDsdlJoyScope
// scope class for SDL (SDL_JoystickOpen(), SDL_JoystickClose()
////////////////////////////////////////////////////////////////////////////////

class cTDsdlJoyScope
{
public:
   cTDsdlJoyScope(int A_iDevice);
   ~cTDsdlJoyScope();

   SDL_Joystick *operator*() { return m_pJoy; }

protected:
   SDL_Joystick *m_pJoy;
};

////////////////////////////////////////////////////////////////////////////////
// cTDsdlSurfaceLockScope
// scope class for SDL_Surface
////////////////////////////////////////////////////////////////////////////////

class cTDsdlSurfaceLockScope
{
public:
   cTDsdlSurfaceLockScope(SDL_Surface *A_pSurface);
   cTDsdlSurfaceLockScope(SDL_Surface &A_Surface);
   ~cTDsdlSurfaceLockScope();

private:
   SDL_Surface *m_pLockedSurface;
};

////////////////////////////////////////////////////////////////////////////////
// cTDsdlScreen
// class (scope) for Main Screen with Buffers
////////////////////////////////////////////////////////////////////////////////

class cTDsdlScreen
{
public:
   enum tScreenBuffer
   {
      eBackgroundBuf = 0,
      eActionBuf = 1,
      eSBMax = 2
   };

   enum tUpdateEffect
   {
      eNone = 0, // no effect normal full update
      eScanLineBars,
      eRightLeftBars
   };

   cTDsdlScreen();
   ~cTDsdlScreen();

// methods
   long set_video_mode(int A_nWidth, int A_nHeight, int A_nBPP, Uint32 A_flagsVideo); // open or reopen screen
   void toggle_full_screen(); // switch beatwean window / fullscreen

   void clear(SDL_Color *A_pclrFg = NULL);
   void update(enum tUpdateEffect A_eEffect = eNone);
   bool copy_to_buffer(enum tScreenBuffer A_eBuffer);
   bool restore_from_buffer(enum tScreenBuffer A_eBuffer);

   SDL_Surface *screen() { return m_pMainScreen; }

   SDL_Surface *operator[](enum tScreenBuffer A_eBuffer) const;

private:
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


// namespaces/prototypes

namespace tdsdl
{
   void FillBackground(SDL_Surface *A_pScreen, SDL_Surface *A_pPattern, bool A_bDoFrame);
   void FillRect(SDL_Surface *A_pScreen, SDL_Surface *A_pPattern, SDL_Rect *A_pRect);

   void CenterSurfaceBlit(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_posX, long A_posY);
   void CenterSurfaceRestore(SDL_Surface *A_pScreen, SDL_Surface *A_pBuffer, SDL_Surface *A_pSurface, long A_posX, long A_posY);
   void CenterSurfaceUpdate(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_posX, long A_posY);

   void CenterOffXSurfaceBlit(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_offsetX, long A_posY);
   void CenterOffXSurfaceRestore(SDL_Surface *A_pScreen, SDL_Surface *A_pBuffer, SDL_Surface *A_pSurface, long A_offsetX, long A_posY);
   void CenterOffXSurfaceUpdate(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_offsetX, long A_posY);

   void CenterText(SDL_Surface *A_pScreen, const char *A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_posX, long A_posY, bool A_bUTF8 = false, bool A_bShaded = false, SDL_Color *A_pclrOutline = NULL);
   void CenterOffXText(SDL_Surface *A_pScreen, const char *A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_offsetX, long A_posY, bool A_bUTF8 = false, bool A_bShaded = false, SDL_Color *A_pclrOutline = NULL);
   void LeftText(SDL_Surface *A_pScreen, const char *A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_posX, long A_posY, bool A_bUTF8 = false, bool A_bShaded = false, SDL_Color *A_pclrOutline = NULL);
   void RightText(SDL_Surface *A_pScreen, const char *A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_posX, long A_posY, bool A_bUTF8 = false, bool A_bShaded = false, SDL_Color *A_pclrOutline = NULL);

   void SwapEndians(Uint8 *A_pData, int A_nLength);

   bool ExamineDirection(const SDL_Event &A_event, bool &A_bUp, bool &A_bDown, bool &A_bLeft, bool &A_bRight, bool A_bIgnoreJoy = true);

   SDL_Surface *PrepareAnimImg(SDL_Surface &A_imgInput, unsigned int A_nFrames, unsigned char A_nInputBorder, unsigned int A_nTileSizeX, unsigned int A_nTileSizeY,
                               tDirection A_eInputDir = eDirUp, bool A_bRotate4dirs = false);
};

namespace tdsdl_dbg
{
   void SurfaceInfo(SDL_Surface *A_pSurface);
   void RectangleInfo(SDL_Rect *A_pRect);
};



#endif // __TD_SDL_UTIL_H
