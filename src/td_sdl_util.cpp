/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_sdl_util.h

    Implementation of common functions for all SDL TDolphin's projects (Ansic C/C++ programs)

    created: 22.09.2005
       last: 12.02.2012

*/

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>

//#define __TD_DEBUG

#include "td_common_defines.h"
#include "td_sdl_util.h"

#define JOY_X 0
#define JOY_Y 1
#define JOY_MIN_VALUE   256

using namespace std;

// global variables


////////////////////////////////////////////////////////////////////////////////
// cTDsdlRect
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDsdlRect::cTDsdlRect
//
// Rafal Zabdyr, 14.12.2009
//==============================================================================
cTDsdlRect::cTDsdlRect()
{
   SDL_Rect::x = 0;
   SDL_Rect::y = 0;
   SDL_Rect::w = 0;
   SDL_Rect::h = 0;
}

//==============================================================================
// cTDsdlRect::cTDsdlRect
//
// Rafal Zabdyr, 14.12.2009
//==============================================================================
cTDsdlRect::cTDsdlRect(SDL_Rect &A_rcData)
{
   x = A_rcData.x;
   y = A_rcData.y;
   w = A_rcData.w;
   h = A_rcData.h;
}

//==============================================================================
// cTDsdlRect::operator=
//
// Rafal Zabdyr, 14.12.2009
//==============================================================================
cTDsdlRect& cTDsdlRect::operator=(const SDL_Rect &A_rcData)
{
   x = A_rcData.x;
   y = A_rcData.y;
   w = A_rcData.w;
   h = A_rcData.h;

   return *this;
}

//==============================================================================
// cTDsdlRect::operator+
//
// Rafal Zabdyr, 14.12.2009
//==============================================================================
cTDsdlRect& cTDsdlRect::operator+(const cTDsdlRect &A_rcData)
{
   TD_DEBUG(;)

   long int ax2 = x + w,
            ay2 = y + h,
            bx2 = A_rcData.x + A_rcData.w,
            by2 = A_rcData.y + A_rcData.h;

   x = min(x, A_rcData.x);
   y = min(y, A_rcData.y);

   long int maxx = max(ax2, bx2),
            maxy = max(ay2, by2);

   w = maxx - x;
   h = maxy - y;

   return *this;
}

//==============================================================================
// cTDsdlRect::operator+=
//
// Rafal Zabdyr, 1.01.2010
//==============================================================================
cTDsdlRect& cTDsdlRect::operator+=(const cTDsdlRect &A_rcData)
{
   TD_DEBUG(;)

   return this->operator+(A_rcData);
}


////////////////////////////////////////////////////////////////////////////////
// class cTDsdlScope
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDsdlScope::cTDsdlScope
//
// Rafal Zabdyr, 27.05.2006
//==============================================================================
cTDsdlScope::cTDsdlScope(Uint32 A_flags)
{
   TD_DEBUG(;)

   m_bInitStatus = !(SDL_Init(A_flags) < 0);

   if (!m_bInitStatus)
      cerr <<  "Couldn't initialize SDL: " << SDL_GetError() << "\n";
}

//==============================================================================
// cTDsdlScope::~cTDsdlScope
//
// Rafal Zabdyr, 27.05.2006
//==============================================================================
cTDsdlScope::~cTDsdlScope()
{
   TD_DEBUG(;)

   if (m_bInitStatus)
      SDL_Quit();
}


////////////////////////////////////////////////////////////////////////////////
// class cTDsdlTTFScope
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDsdlTTFScope::cTDsdlTTFScope
//
// Rafal Zabdyr, 27.05.2006
//==============================================================================
cTDsdlTTFScope::cTDsdlTTFScope()
{
   TD_DEBUG(;)

   m_bInitStatus = !(TTF_Init() < 0);

   if (!m_bInitStatus)
      cerr <<  "Couldn't initialize TTF: " << SDL_GetError() << "\n";
}

//==============================================================================
// cTDsdlTTFScope::~cTDsdlTTFScope
//
// Rafal Zabdyr, 27.05.2006
//==============================================================================
cTDsdlTTFScope::~cTDsdlTTFScope()
{
   TD_DEBUG(;)

   if (m_bInitStatus)
      TTF_Quit();
}


////////////////////////////////////////////////////////////////////////////////
// class cTDsdlJoyScope
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDsdlJoyScope::cTDsdlJoyScope
//
//  A_iDevice - joystick index
//
// Rafal Zabdyr, 13.11.2007
//==============================================================================
cTDsdlJoyScope::cTDsdlJoyScope(int A_iDevice)
: m_pJoy(NULL)
{
   TD_DEBUG(;)

   if (SDL_NumJoysticks() <= 0)
   {
      TD_DEBUG( cerr << "Warning: No joysticks available.\n"; )
      return;
   }

   m_pJoy = SDL_JoystickOpen(A_iDevice);

   if (!m_pJoy)
      cerr <<  "Couldn't open joystick " << A_iDevice << ": " << SDL_GetError() << "\n";
}

//==============================================================================
// cTDsdlJoyScope::cTDsdlJoyScope
//
// Rafal Zabdyr, 13.11.2007
//==============================================================================
cTDsdlJoyScope::~cTDsdlJoyScope()
{
   TD_DEBUG(;)

   if (m_pJoy)
      SDL_JoystickClose(m_pJoy);
}


////////////////////////////////////////////////////////////////////////////////
// class cTDsdlSurfaceLockScope
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDsdlSurfaceLockScope::cTDsdlSurfaceLockScope
//
// Rafal Zabdyr, 19.03.2006
//==============================================================================
cTDsdlSurfaceLockScope::cTDsdlSurfaceLockScope(SDL_Surface *A_pSurface)
: m_pLockedSurface(A_pSurface)
{
   SDL_LockSurface(m_pLockedSurface);
}

//==============================================================================
// cTDsdlLockSurfaceScope::cTDsdlLockSurfaceScope
//
// Rafal Zabdyr, 19.03.2006
//==============================================================================
cTDsdlSurfaceLockScope::cTDsdlSurfaceLockScope(SDL_Surface &A_Surface)
: m_pLockedSurface(&A_Surface)
{
   SDL_LockSurface(m_pLockedSurface);
}

//==============================================================================
// cTDsdlSurfaceLockScope::~cTDsdlSurfaceLockScope
//
// Rafal Zabdyr, 19.03.2006
//==============================================================================
cTDsdlSurfaceLockScope::~cTDsdlSurfaceLockScope()
{
   SDL_UnlockSurface(m_pLockedSurface);
}

////////////////////////////////////////////////////////////////////////////////
// class cTDsdlScreen
////////////////////////////////////////////////////////////////////////////////

//      eBackgroundBuf = 0,
//      eAcionBuf = 1,
//      eSBMax = 2


//==============================================================================
// cTDsdlScreen::cTDsdlScreen
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
cTDsdlScreen::cTDsdlScreen()
: m_pMainScreen(NULL)
{
   reset();
}

//==============================================================================
// cTDsdlScreen::~cTDsdlScreen
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
cTDsdlScreen::~cTDsdlScreen()
{
   free_buffers();
}

//==============================================================================
// cTDsdlScreen::set_video_mode
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
long cTDsdlScreen::set_video_mode(int A_nWidth, int A_nHeight, int A_nBPP, Uint32 A_flagsVideo)
{
   m_nWidth = A_nWidth;
   m_nHeight = A_nHeight;
   m_nBPP = A_nBPP;
   m_flagsVideo = A_flagsVideo;

   m_pMainScreen = SDL_SetVideoMode(m_nWidth, m_nHeight, m_nBPP, m_flagsVideo);

   // open screen
   if (!m_pMainScreen)
   {
      cerr <<  "cTDsdlScreen::set_video_mode(): Couldn't initialize video mode: " << SDL_GetError() << "\n";
      return TD_ERR;
   }

   if (!alloc_buffers())
      return TD_ERR;

   return TD_OK;
}

//==============================================================================
// cTDsdlScreen::toggle_full_screen
//
//  full screen <--> window
//
// Rafal Zabdyr, 29.09.2006
//==============================================================================
void cTDsdlScreen::toggle_full_screen()
{
   if (!m_pMainScreen)
      return;

   m_flagsVideo ^= SDL_FULLSCREEN;

#ifdef WIN32
   SDL_SetVideoMode(m_nWidth, m_nHeight, m_nBPP, m_flagsVideo);
#else
   SDL_WM_ToggleFullScreen(m_pMainScreen);
#endif // WIN32
}

//==============================================================================
// cTDsdlScreen::clear
//
// Rafal Zabdyr, 16.09.2006
//==============================================================================
void cTDsdlScreen::clear(SDL_Color *A_pclrFg /*= NULL*/)
{
   if (!m_pMainScreen)
      return;

   SDL_Color clrBlack = { 0, 0, 0, 255 };

   if (!A_pclrFg)
      A_pclrFg = &clrBlack;

   boxRGBA(m_pMainScreen, 0, 0, m_pMainScreen->w, m_pMainScreen->h, A_pclrFg->r, A_pclrFg->g, A_pclrFg->b, A_pclrFg->unused);
}

//==============================================================================
// cTDsdlScreen::update
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
void cTDsdlScreen::update(enum tUpdateEffect A_eEffect /* = eNone*/)
{
   if (!m_pMainScreen)
      return;

   switch (A_eEffect)
   {
      case eScanLineBars:
         {
            long iTmpY,
                 nScreenW = m_pMainScreen->w,
                 nScreenH = m_pMainScreen->h;
            SDL_Rect rIntro;
            TD_DEBUG( cout << "S: " << nScreenW << " " << nScreenH << endl; )

            rIntro.x = 0;
            rIntro.y = 0;
            rIntro.w = nScreenW;
            rIntro.h = 4;

            for (rIntro.y = 0; rIntro.y + 4 < nScreenH; rIntro.y +=8)
            {
               //TD_DEBUG( cout << "A: " << rIntro.y << " " << ((rIntro.y + rIntro.h < nScreenH) ? rIntro.h : nScreenH - rIntro.y) << endl; )
               SDL_UpdateRect(m_pMainScreen, 0, rIntro.y, rIntro.w, (rIntro.y + rIntro.h < nScreenH) ? rIntro.h : nScreenH - rIntro.y);
               SDL_Delay(3);
            }
            for (rIntro.y -= 4; rIntro.y - 4 >= 0; rIntro.y -= 8)
            {
               //TD_DEBUG( cout << "B: " << rIntro.y << " " << ((rIntro.y + rIntro.h < nScreenH) ? rIntro.h : nScreenH - rIntro.y) << endl; )
               SDL_UpdateRect(m_pMainScreen, 0, rIntro.y, rIntro.w, (rIntro.y + rIntro.h < nScreenH) ? rIntro.h : nScreenH - rIntro.y);
               SDL_Delay(3);
            }
         }
         break;

      case eRightLeftBars:
         {
            long iTmpY, iTmpX, bLeftRight,
                 nScreenW = m_pMainScreen->w,
                 nScreenH = m_pMainScreen->h;
            SDL_Rect rIntro;

            for (iTmpX = 0; iTmpX < nScreenW/16; iTmpX++)
            {
               bLeftRight = 0;
               rIntro.w = 16;
               rIntro.h = 16;
               for (iTmpY = 0; iTmpY <= nScreenH/16; iTmpY++)
               {
                  rIntro.x = (bLeftRight == 0) ? (iTmpX * 16) : (nScreenW - (iTmpX + 1) * 16);
                  rIntro.y = iTmpY * 16;
                  rIntro.h = 16;
                  if (nScreenH < rIntro.y + 16) // clipping
                     rIntro.h = nScreenH - rIntro.y;
                  SDL_UpdateRect(m_pMainScreen, rIntro.x, rIntro.y, rIntro.w, rIntro.h);
                  bLeftRight = (bLeftRight == 0) ? 1 : 0;
               }
               SDL_Delay(3);
            }
         }
         break;

      case eNone:
      default:
         SDL_UpdateRect(m_pMainScreen, 0, 0, 0, 0);
   };
}

//==============================================================================
// cTDsdlScreen::copy_to_buffer
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
bool cTDsdlScreen::copy_to_buffer(enum tScreenBuffer A_eBuffer)
{
   if (!m_pMainScreen)
      return false;

   SDL_BlitSurface(m_pMainScreen, NULL, m_aBuffers[(int)A_eBuffer], NULL);
   SDL_UpdateRect(m_aBuffers[(int)A_eBuffer], 0, 0, 0, 0);

   return true;
}

//==============================================================================
// cTDsdlScreen::restore_from_buffer
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
bool cTDsdlScreen::restore_from_buffer(enum tScreenBuffer A_eBuffer)
{
   if (!m_pMainScreen)
      return false;

   SDL_BlitSurface(m_aBuffers[(int)A_eBuffer], NULL, m_pMainScreen, NULL);

   return true;
}

//==============================================================================
// cTDsdlScreen::operator[]
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
SDL_Surface *cTDsdlScreen::operator[](enum tScreenBuffer A_eBuffer) const
{
   return m_aBuffers[(int)A_eBuffer];
}

//==============================================================================
// cTDsdlScreen::alloc_buffers
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
char cTDsdlScreen::alloc_buffers()
{
   if (!m_pMainScreen)
      return false;

   free_buffers();

   for (int i = 0; i < eSBMax; i++)
   {
      m_aBuffers[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pMainScreen->w, m_pMainScreen->h,
      m_pMainScreen->format->BitsPerPixel,
      m_pMainScreen->format->Rmask,
      m_pMainScreen->format->Gmask,
      m_pMainScreen->format->Bmask,
      m_pMainScreen->format->Amask);

      if (!m_aBuffers[i])
      {
         cerr << "cTDsdlScreen::alloc_bufferse(): Can't create surface: \n" << SDL_GetError() << "\n";
         return false;
      }
   }

   return true;
}

//==============================================================================
// cTDsdlScreen::free_buffers
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
void cTDsdlScreen::free_buffers()
{
   for (int i = 0; i < eSBMax; i++)
      if (m_aBuffers[i])
      {
         SDL_FreeSurface(m_aBuffers[i]);
         m_aBuffers[i] = NULL;
      }
}

//==============================================================================
// cTDsdlScreen::reset
//
// Rafal Zabdyr, 29.05.2006
//==============================================================================
void cTDsdlScreen::reset()
{
   for (int i = 0; i < eSBMax; i++)
      m_aBuffers[i] = NULL;
}


////////////////////////////////////////////////////////////////////////////////
// namespace tdsdl
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// tdsdl::FillBackground
//
// Rafal Zabdyr, 3.07.2005
//==============================================================================
void tdsdl::FillBackground(SDL_Surface *A_pScreen, SDL_Surface *A_pPattern, bool A_bDoFrame)
{
   unsigned long iX, iY,
                 nTimesX, nTimesY;
   SDL_Rect rCopy;

   if (!A_pScreen || !A_pPattern)
   {
      cerr << "tdps_FillBackground error!!\n";
      return;
   }

   nTimesX = A_pScreen->w / A_pPattern->w;
   nTimesY = A_pScreen->h / A_pPattern->h;

   rCopy.x = 0;
   rCopy.y = 0;
   rCopy.w = A_pPattern->w;
   rCopy.h = A_pPattern->h;

   for (iX = 0; iX <= nTimesX; iX++)
   {
      rCopy.y = 0;
      for (iY = 0; iY <= nTimesY; iY++)
      {
         SDL_BlitSurface(A_pPattern, NULL, A_pScreen, &rCopy);
         rCopy.y += A_pPattern->h;
      }
      rCopy.x += A_pPattern->w;
   }

   if (A_bDoFrame)
   {
      unsigned int i, j;
      for (i = 0, j = 1; i < 4; i++, j++)
      {
         hlineRGBA(A_pScreen, i, A_pScreen->w - j, i, 255, 255, 255, 230 - i * 60);
         vlineRGBA(A_pScreen, i, i, A_pScreen->h - j, 255, 255, 255, 230 - i * 60);
         hlineRGBA(A_pScreen, i, A_pScreen->w - j, A_pScreen->h - j, 20, 20, 20, 230 - i * 60);
         vlineRGBA(A_pScreen, A_pScreen->w - j, i, A_pScreen->h - j, 20, 20, 20, 230 - i * 60);
      }
   }
}

//==============================================================================
// tdsdl::FillRect
//
// Rafal Zabdyr, 3.07.2005
//==============================================================================
void tdsdl::FillRect(SDL_Surface *A_pScreen, SDL_Surface *A_pPattern, SDL_Rect *A_pRect)
{
   unsigned short iX, iY, nTimesX, nTimesY, nRestX, nRestY;
   SDL_Rect rCopy, rcPattern;

   if (!A_pScreen || !A_pPattern)
   {
      cerr << "td_sdl_FillRect error!!\n";
      return;
   }

   nTimesX = A_pRect->w / A_pPattern->w;
   nTimesY = A_pRect->h / A_pPattern->h;
   nRestX = A_pRect->w % A_pPattern->w;
   nRestY = A_pRect->h % A_pPattern->h;

   //printf("X times %d, Y times %d, X rest %d, Y rest %d\n", nTimesX, nTimesY, nRestX, nRestY);

   rCopy.x = A_pRect->x;
   rCopy.y = A_pRect->y;
   rCopy.w = A_pPattern->w;
   rCopy.h = A_pPattern->h;

   rcPattern.x = 0;
   rcPattern.y = 0;
   rcPattern.h = A_pPattern->w;
   rcPattern.w = A_pPattern->h;

   for (iX = 0; iX <= nTimesX; iX++)
   {
      rCopy.y = A_pRect->y;

      if (iX == nTimesX)
      {
         rCopy.w = nRestX;
         rcPattern.w = nRestX;
      }

      for (iY = 0; iY <= nTimesY; iY++)
      {
         if (iY == nTimesY)
         {
            rCopy.h = nRestY;
            rcPattern.h = nRestY;
         }
         SDL_BlitSurface(A_pPattern, &rcPattern, A_pScreen, &rCopy);
         rCopy.y += A_pPattern->h;
      }

      rCopy.x += A_pPattern->w;
      rCopy.h = A_pPattern->h;
      rcPattern.h = rCopy.h;
   }
}

//==============================================================================
// tdsdl::CenterSurfaceBlit
//
// Rafal Zabdyr, 8.09.2005
//==============================================================================
void tdsdl::CenterSurfaceBlit(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_posX, long A_posY)
{
   SDL_Rect rcDest = { A_posX - A_pSurface->w / 2, A_posY - A_pSurface->h / 2, 0, 0 };
   SDL_BlitSurface(A_pSurface, NULL, A_pScreen, &rcDest);
}

//==============================================================================
// tdsdl::CenterSurfaceRestore
//
// Rafal Zabdyr, 8.09.2005
//==============================================================================
void tdsdl::CenterSurfaceRestore(SDL_Surface *A_pScreen, SDL_Surface *A_pBuffer, SDL_Surface *A_pSurface, long A_posX, long A_posY)
{
   SDL_Rect rcDest = { A_posX - A_pSurface->w / 2, A_posY - A_pSurface->h / 2, 0, 0 };
   SDL_BlitSurface(A_pBuffer, &rcDest, A_pScreen, &rcDest);
}

//==============================================================================
// tdsdl::CenterSurfaceUpdate
//
// Rafal Zabdyr, 8.09.2005
//==============================================================================
void tdsdl::CenterSurfaceUpdate(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_posX, long A_posY)
{
   SDL_Rect rcDest = { A_posX - A_pSurface->w / 2, A_posY - A_pSurface->h / 2, 0, 0 };
   SDL_UpdateRect(A_pScreen, rcDest.x, rcDest.y, rcDest.w, rcDest.h);
}

//==============================================================================
// tdsdl::CenterOffXSurfaceBlit
//
// Rafal Zabdyr, 12.07.2005
//==============================================================================
void tdsdl::CenterOffXSurfaceBlit(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_offsetX, long A_posY)
{
   SDL_Rect rcDest = { A_offsetX, A_posY - A_pSurface->h / 2, 0, 0 };
   SDL_BlitSurface(A_pSurface, NULL, A_pScreen, &rcDest);
}

//==============================================================================
// tdsdl::CenterOffXSurfaceRestore
//
// Rafal Zabdyr, 12.07.2005
//==============================================================================
void tdsdl::CenterOffXSurfaceRestore(SDL_Surface *A_pScreen, SDL_Surface *A_pBuffer, SDL_Surface *A_pSurface, long A_offsetX, long A_posY)
{
   SDL_Rect rcDest = { A_offsetX, A_posY - A_pSurface->h / 2, 0, 0 };
   SDL_BlitSurface(A_pBuffer, &rcDest, A_pScreen, &rcDest);
}

//==============================================================================
// tdsdl::CenterOffXSurfaceUpdate
//
// Rafal Zabdyr, 12.07.2005
//==============================================================================
void tdsdl::CenterOffXSurfaceUpdate(SDL_Surface *A_pScreen, SDL_Surface *A_pSurface, long A_offsetX, long A_posY)
{
   SDL_Rect rcDest = { A_offsetX, A_posY - A_pSurface->h / 2, 0, 0 };
   SDL_UpdateRect(A_pScreen, rcDest.x, rcDest.y, rcDest.w, rcDest.h);
}

//==============================================================================
// tdsdl::CenterText
//
// Rafal Zabdyr, 31.08.2006
//==============================================================================
void tdsdl::CenterText(SDL_Surface *A_pScreen, const char* A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_posX, long A_posY, bool A_bUTF8 /*= false*/,
                       bool A_bShaded /*= false*/, SDL_Color *A_pclrOutline /*= NULL*/)
{
   if (A_pclrOutline)
   {
      for (int ix = -1; ix <= 1; ix++)
         for (int iy = -1; iy <= 1; iy++)
               tdsdl::CenterText(A_pScreen, A_strText, A_pfntArial, A_pclrOutline, A_posX + ix, A_posY + iy, A_bUTF8);
   }

   SDL_Color clrBlack = { 0, 0, 0, 80 };

   SDL_Surface *pText = (A_bUTF8) ?
                        ((A_bShaded) ? TTF_RenderUTF8_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderUTF8_Blended(A_pfntArial, A_strText, *A_pclrFg)) :
                        ((A_bShaded) ? TTF_RenderText_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderText_Blended(A_pfntArial, A_strText, *A_pclrFg));
   CenterSurfaceBlit(A_pScreen, pText, A_posX, A_posY);
   //CenterSurfaceUpdate(A_pScreen, pText, A_posX, A_posY);
   SDL_FreeSurface(pText);
}

//==============================================================================
// tdsdl::CenterOffXText
//
// Rafal Zabdyr, 31.08.2006
//==============================================================================
void tdsdl::CenterOffXText(SDL_Surface *A_pScreen, const char* A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_offsetX, long A_posY, bool A_bUTF8 /*= false*/,
                           bool A_bShaded /*= false*/, SDL_Color *A_pclrOutline /*= NULL*/)
{
   if (A_pclrOutline)
   {
      for (int ix = -1; ix <= 1; ix++)
         for (int iy = -1; iy <= 1; iy++)
               tdsdl::CenterOffXText(A_pScreen, A_strText, A_pfntArial, A_pclrOutline, A_offsetX + ix, A_posY + iy, A_bUTF8);
   }

   SDL_Color clrBlack = { 0, 0, 0, 80 };

   SDL_Surface *pText = (A_bUTF8) ?
                        ((A_bShaded) ? TTF_RenderUTF8_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderUTF8_Blended(A_pfntArial, A_strText, *A_pclrFg)) :
                        ((A_bShaded) ? TTF_RenderText_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderText_Blended(A_pfntArial, A_strText, *A_pclrFg));
   CenterOffXSurfaceBlit(A_pScreen, pText, A_offsetX, A_posY);
   //CenterOffXSurfaceUpdate(A_pScreen, pText, A_offsetX, A_posY);
   SDL_FreeSurface(pText);
}

//==============================================================================
// tdsdl::LeftText
//
// Rafal Zabdyr, 13.09.2006
//==============================================================================
void tdsdl::LeftText(SDL_Surface *A_pScreen, const char* A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_posX, long A_posY, bool A_bUTF8 /*= false*/,
                     bool A_bShaded /*= false*/, SDL_Color *A_pclrOutline /*= NULL*/)
{
   if (A_pclrOutline)
   {
      for (int ix = -1; ix <= 1; ix++)
         for (int iy = -1; iy <= 1; iy++)
               tdsdl::LeftText(A_pScreen, A_strText, A_pfntArial, A_pclrOutline, A_posX + ix, A_posY + iy, A_bUTF8);
   }

   SDL_Color clrBlack = { 0, 0, 0, 80 };

   SDL_Surface *pText = (A_bUTF8) ?
                        ((A_bShaded) ? TTF_RenderUTF8_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderUTF8_Blended(A_pfntArial, A_strText, *A_pclrFg)) :
                        ((A_bShaded) ? TTF_RenderText_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderText_Blended(A_pfntArial, A_strText, *A_pclrFg));

   SDL_Rect rcDest = { A_posX, A_posY, 0, 0 };
   SDL_BlitSurface(pText, NULL, A_pScreen, &rcDest);
   SDL_FreeSurface(pText);
}

//==============================================================================
// tdsdl::RightText
//
// Rafal Zabdyr, 21.08.2011
//==============================================================================
void tdsdl::RightText(SDL_Surface *A_pScreen, const char* A_strText, TTF_Font *A_pfntArial, SDL_Color *A_pclrFg, long A_posX, long A_posY, bool A_bUTF8 /*= false*/,
                      bool A_bShaded /*= false*/, SDL_Color *A_pclrOutline /*= NULL*/)
{
   if (A_pclrOutline)
   {
      for (int ix = -1; ix <= 1; ix++)
         for (int iy = -1; iy <= 1; iy++)
               tdsdl::RightText(A_pScreen, A_strText, A_pfntArial, A_pclrOutline, A_posX + ix, A_posY + iy, A_bUTF8);
   }

   SDL_Color clrBlack = { 0, 0, 0, 80 };

   SDL_Surface *pText = (A_bUTF8) ?
                        ((A_bShaded) ? TTF_RenderUTF8_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderUTF8_Blended(A_pfntArial, A_strText, *A_pclrFg)) :
                        ((A_bShaded) ? TTF_RenderText_Shaded(A_pfntArial, A_strText, *A_pclrFg, clrBlack) : TTF_RenderText_Blended(A_pfntArial, A_strText, *A_pclrFg));

   SDL_Rect rcDest = { A_posX - pText->w, A_posY, 0, 0 };
   SDL_BlitSurface(pText, NULL, A_pScreen, &rcDest);
   SDL_FreeSurface(pText);
}

//==============================================================================
// tdsdl::SwapEndians
//
// Rafal Zabdyr, 21.09.2005
//==============================================================================
void tdsdl::SwapEndians(Uint8 *A_pData, int A_nLength)
{
   Uint8 temp;

   for (int i = 0; i < A_nLength; i += 2)
   {
      temp = A_pData[i];
      A_pData[i] = A_pData[i + 1];
      A_pData[i + 1] = temp;
   }
}

//==============================================================================
// tdsdl::ExamineDirection
//
// Rafal Zabdyr, 9.11.2007
//==============================================================================
bool tdsdl::ExamineDirection(const SDL_Event &A_event, bool &A_bUp, bool &A_bDown, bool &A_bLeft, bool &A_bRight, bool A_bIgnoreJoy /*= true*/)
{
   bool bUp = A_bUp, bDown = A_bDown, bLeft = A_bLeft, bRight = A_bRight;
   switch(A_event.type)
   {
      case SDL_KEYDOWN:
         switch (A_event.key.keysym.sym)
         {
            case SDLK_UP:
               A_bUp = true;
               break;
            case SDLK_DOWN:
               A_bDown = true;
               break;
            case SDLK_LEFT:
               A_bLeft = true;
               break;
            case SDLK_RIGHT:
               A_bRight = true;
               break;
         }
      break;

      case SDL_KEYUP:
         switch (A_event.key.keysym.sym)
         {
            case SDLK_UP:
               A_bUp = false;
               break;
            case SDLK_DOWN:
               A_bDown = false;
               break;
            case SDLK_LEFT:
               A_bLeft = false;
               break;
            case SDLK_RIGHT:
               A_bRight = false;
               break;
         }
         break;

      case SDL_JOYAXISMOTION:
         if (A_bIgnoreJoy)
            break;

         TD_DEBUG( cout << int(A_event.jaxis.axis) << " : " << A_event.jaxis.value << endl; )
         if (A_event.jaxis.axis == JOY_X) // horizontal
         {
            if (A_event.jaxis.value > JOY_MIN_VALUE)
            {
               A_bRight = true;
               A_bLeft = false;
            }
            else if (A_event.jaxis.value < -JOY_MIN_VALUE)
            {
               A_bRight = false;
               A_bLeft = true;
            }
            else
            {
               A_bRight = false;
               A_bLeft = false;
            }
         }
         else if (A_event.jaxis.axis == JOY_Y) // vertical
         {
            if (A_event.jaxis.value < -JOY_MIN_VALUE)
            {
               A_bUp = true;
               A_bDown = false;
            }
            else if (A_event.jaxis.value > JOY_MIN_VALUE)
            {
               A_bUp = false;
               A_bDown = true;
            }
            else
            {
               A_bUp = false;
               A_bDown = false;
            }
         }
         break;
   }

   return (bUp != A_bUp || bDown != A_bDown || bLeft != A_bLeft || bRight != A_bRight);
}

//==============================================================================
// tdsdl::ExamineDirection
//
// example: n = 1 (n is A_nInputBorder) there is:
//
// 1111111
// 1++1++1
// 1111111
//
// Rafal Zabdyr, 10.01.2008 (moved from xxxx_game_objects.cpp)
//==============================================================================
SDL_Surface *tdsdl::PrepareAnimImg(SDL_Surface &A_imgInput, unsigned int A_nFrames, unsigned char A_nInputBorder, unsigned int A_nTileSizeX, unsigned int A_nTileSizeY,
                                   tDirection A_eInputDir /*= eDirUp*/, bool A_bRotate4dirs /*= false*/)
{
   TD_DEBUG(cout << "A_imgInput=" << &A_imgInput << " frames=" << A_nFrames << " border=" << int(A_nInputBorder) << " tilesizeX=" << A_nTileSizeX << " tilesizeY" << A_nTileSizeY
                 << " dir=" << A_eInputDir << " rotate=" << A_bRotate4dirs << endl;)

   if (A_bRotate4dirs && A_nTileSizeX != A_nTileSizeY)
   {
      cerr << "tdsdl::PrepareAnimImg() --> A_nTileSizeX != A_nTileSizeY not supported yet" << endl;
      return NULL;
   }

   SDL_Surface *pImgPrepared = NULL;

   unsigned int n = A_nInputBorder,
                nDirs = A_bRotate4dirs ? 4 : 1; // 4 or 1 direction(s)

   // prepare surface with all direction anims
   pImgPrepared = SDL_CreateRGBSurface(SDL_SWSURFACE, A_nTileSizeX * A_nFrames, A_nTileSizeY * nDirs, A_imgInput.format->BitsPerPixel,
                                       A_imgInput.format->Rmask, A_imgInput.format->Gmask, A_imgInput.format->Bmask, A_imgInput.format->Amask);
   Uint32 colorTransparent = SDL_MapRGB(A_imgInput.format, 255, 0, 255); // purple

   TD_DEBUG(cout << "pImgPrepared=" << pImgPrepared << endl;)

   if (pImgPrepared)
   {
      SDL_Rect rcTo, rcFrom;

      TD_DEBUG( cout << "imgInput->format->BitsPerPixel = " << int(A_imgInput.format->BitsPerPixel) << "\n"; )
      TD_DEBUG( cout << "imgPrepared->format->BitsPerPixel = " << int(pImgPrepared->format->BitsPerPixel) << "\n"; )

      //rcTo.x = rcTo.y = 0;
      //rcTo.w = __TD_FIELD_SIZE * m_animMovInfoX.frames(); // 6 frames
      //rcTo.h = __TD_FIELD_SIZE;

      // support 8 bits per pixel
      if (A_imgInput.format->BitsPerPixel == 8)
      {
         SDL_SetColors(pImgPrepared, A_imgInput.format->palette->colors, 0, A_imgInput.format->palette->ncolors);
         SDL_SetColorKey(pImgPrepared, SDL_SRCCOLORKEY, colorTransparent);
      }

      SDL_FillRect(pImgPrepared, NULL, colorTransparent);
      
      //SDL_BlitSurface(m_pImg, NULL, m_pImgPrepared, &rcTo); // direction "up"
      //rcTo.y += __TD_FIELD_SIZE;

      rcFrom.w = rcFrom.h = rcTo.w = rcTo.h = 1;

      for (unsigned int iTile = 0; iTile < A_nFrames; iTile++)
         for (unsigned int ix = 0; ix < A_nTileSizeX; ix++)
            for (unsigned int iy = 0; iy < A_nTileSizeY; iy++)
            {
               rcFrom.x = n + (A_nTileSizeX + n) * iTile + ix;
               rcFrom.y = n + iy;

               if (nDirs == 1)
               {
                  // direction not changed only remap
                  rcTo.x = A_nTileSizeX * iTile + ix;
                  rcTo.y = iy;
                  SDL_BlitSurface(&A_imgInput, &rcFrom, pImgPrepared, &rcTo);
                  continue;
               }

               // 4 dirs

               // direction "up"
               switch(A_eInputDir)
               {
                  case eDirLeft:
                     rcTo.x = A_nTileSizeX * iTile + iy;
                     rcTo.y = ix;
                     break;
                  case eDirUp:
                  default:
                     rcTo.x = A_nTileSizeX * iTile + ix;
                     rcTo.y = iy;
               }
               SDL_BlitSurface(&A_imgInput, &rcFrom, pImgPrepared, &rcTo);

               // direction "right"
               switch(A_eInputDir)
               {
                  case eDirUp:
                     rcTo.x = A_nTileSizeX * (iTile + 1) - iy;
                     rcTo.y = A_nTileSizeY + ix;
                     break;
                  case eDirLeft:
                     rcTo.x = A_nTileSizeX * (iTile + 1) - ix;
                     rcTo.y = A_nTileSizeY + iy;
                     break;
                  case eDirRight:
                  default:
                     rcTo.x = A_nTileSizeX * iTile + ix;
                     rcTo.y = A_nTileSizeY + iy;
               }
               SDL_BlitSurface(&A_imgInput, &rcFrom, pImgPrepared, &rcTo);

               // direction "down"
               switch(A_eInputDir)
               {
                  case eDirUp:
                     rcTo.x = A_nTileSizeX * iTile + ix;
                     rcTo.y = A_nTileSizeY * (2 + 1) - iy;
                     break;
                  case eDirLeft:
                     rcTo.x = A_nTileSizeX * iTile + iy;
                     rcTo.y = A_nTileSizeY * (2 + 1) - ix;
                     break;
                  case eDirDown:
                  default:
                     rcTo.x = A_nTileSizeX * iTile + ix;
                     rcTo.y = A_nTileSizeY * 2 + iy;
               }
               SDL_BlitSurface(&A_imgInput, &rcFrom, pImgPrepared, &rcTo);

               // direction "left"
               switch(A_eInputDir)
               {
                  case eDirUp:
                     rcTo.x = A_nTileSizeX * iTile + iy;
                     rcTo.y = A_nTileSizeY * 3 + ix;
                     break;
                  case eDirLeft:
                  default:
                     rcTo.x = A_nTileSizeX * iTile + ix;
                     rcTo.y = A_nTileSizeY * 3 + iy;
                     break;
               }
               SDL_BlitSurface(&A_imgInput, &rcFrom, pImgPrepared, &rcTo);
            }
   }

   return pImgPrepared;
}


////////////////////////////////////////////////////////////////////////////////
// namespace tdsdl_dbg
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// tdsdl_dbg::SurfaceInfo
//
// Rafal Zabdyr, 11.03.2006
//==============================================================================
void tdsdl_dbg::SurfaceInfo(SDL_Surface *A_pSurface)
{
   if (A_pSurface)
      cout << "surface: (w,h) = (" << A_pSurface->w << "," << A_pSurface->h << ")\n";
}

//==============================================================================
// tdsdl_dbg::RectangleInfo
//
// Rafal Zabdyr, 11.03.2006
//==============================================================================
void tdsdl_dbg::RectangleInfo(SDL_Rect *A_pRect)
{
   if (A_pRect)
      cout << "rectangle: (x,y) = (" << A_pRect->x <<  "," << A_pRect->y << "), (w,h) = (" <<A_pRect->w << "," << A_pRect->h << ")\n";
}
