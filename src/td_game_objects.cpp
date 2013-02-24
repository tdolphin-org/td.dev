/*

    TDolphin projects

    (c) TDolphin 2006-2008

    td_game_objects.cpp

    Base abstract classes for TDolphin's games. Classes implementation.

    created: 31.05.2006 (rewrite classes from tdbz_game_objects.cpp)
       last: 19.10.2008

*/


#include <iostream>
#include <math.h>

//#define __TD_DEBUG

#include "td_common_defines.h"
#include "td_game_objects.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class cTDPlayFieldBase
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDPlayFieldBase::cTDPlayFieldBase
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDPlayFieldBase::cTDPlayFieldBase()
: m_nOffsetX(0), m_nOffsetY(0), m_nFieldsX(0), m_nFieldsY(0), m_nTileSize(0), m_aField(NULL) // default
{
}

//==============================================================================
// cTDPlayFieldBase::cTDPlayFieldBase
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDPlayFieldBase::cTDPlayFieldBase(int A_nOffsetX, int A_nOffsetY, int unsigned A_nFieldsX, int unsigned A_nFieldsY, unsigned int A_nTileSize)
: m_nOffsetX(A_nOffsetX), m_nOffsetY(A_nOffsetY), m_nFieldsX(A_nFieldsX), m_nFieldsY(A_nFieldsY), m_nTileSize(A_nTileSize), m_aField(NULL)
{
   TD_DEBUG( cout << "cTDPlayFieldBase::cTDPlayFieldBase(): m_nOffsetX = " << m_nOffsetX << ", m_nOffsetY = " << m_nOffsetY
                  << ", m_nFieldsX = %d" << m_nFieldsX << ", m_nFieldsY = " << m_nFieldsY << "\n"; )

   cTDPlayFieldBase::alloc_field();
}

//==============================================================================
// cTDPlayFieldBase::~cTDPlayFieldBase
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDPlayFieldBase::~cTDPlayFieldBase()
{
   TD_DEBUG(;)
   
   if (m_aField)
      delete[] m_aField;
}

//==============================================================================
// cTDPlayFieldBase::alloc_field
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
char cTDPlayFieldBase::alloc_field()
{
   if (m_aField)
   {
      delete[] m_aField;
      m_aField = NULL;
   }

   if (m_nFieldsX > 0 && m_nFieldsY > 0)
   {
      m_aField = new int[m_nFieldsX * m_nFieldsY];

      if (!m_aField)
         cerr << "cTDPlayFieldBase::alloc_field(): allocating memory error!!\n";
   }

   return TRUE;
}

//==============================================================================
// cTDPlayFieldBase::get_xy
//
//  defaults return 0
//
// Rafal Zabdyr, 15.01.2008
//==============================================================================
int cTDPlayFieldBase::get_xy(unsigned int A_iX, unsigned int A_iY) const
{
   if (m_aField && A_iX < m_nFieldsX && A_iY < m_nFieldsY)
      return m_aField[A_iX + A_iY * m_nFieldsX];

   return 0;
}


////////////////////////////////////////////////////////////////////////////////
// class cTDPlayFieldAndStuffBase
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDPlayFieldAndStuffBase::cTDPlayFieldAndStuffBase
//
// Rafal Zabdyr, 14.07.2007
//==============================================================================
cTDPlayFieldAndStuffBase::cTDPlayFieldAndStuffBase()
: m_aFieldStuff(NULL) // default
{
}

//==============================================================================
// cTDPlayFieldAndStuffBase::cTDPlayFieldAndStuffBase
//
// Rafal Zabdyr, 14.07.2007
//==============================================================================
cTDPlayFieldAndStuffBase::cTDPlayFieldAndStuffBase(int A_nOffsetX, int A_nOffsetY, int unsigned A_nFieldsX, int unsigned A_nFieldsY, unsigned int A_nTileSize)
: cTDPlayFieldBase(A_nOffsetX, A_nOffsetY, A_nFieldsX, A_nFieldsY, A_nTileSize), m_aFieldStuff(NULL)
{
}

//==============================================================================
// cTDPlayFieldAndStuffBase::~cTDPlayFieldAndStuffBase
//
// Rafal Zabdyr, 14.07.2007
//==============================================================================
cTDPlayFieldAndStuffBase::~cTDPlayFieldAndStuffBase()
{
   TD_DEBUG(;)
   
   if (m_aFieldStuff)
      delete[] m_aFieldStuff;
}

//==============================================================================
// cTDPlayFieldAndStuffBase::alloc_field
//
// Rafal Zabdyr, 14.07.2007
//==============================================================================
char cTDPlayFieldAndStuffBase::alloc_field()
{
   return (cTDPlayFieldBase::alloc_field() && alloc_fieldStuff());
}

//==============================================================================
// cTDPlayFieldAndStuffBase::alloc_fieldStuff
//
// Rafal Zabdyr, 14.07.2007
//==============================================================================
char cTDPlayFieldAndStuffBase::alloc_fieldStuff()
{
   if (m_aFieldStuff)
   {
      delete[] m_aFieldStuff;
      m_aFieldStuff = NULL;
   }

   if (m_nFieldsX > 0 && m_nFieldsY > 0)
   {
      m_aFieldStuff = new int[m_nFieldsX * m_nFieldsY];

      if (!m_aFieldStuff)
         cerr << __func__ << ": allocating memory error!!\n";
   }

   return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// class cTDItem
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDItem::cTDItem
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDItem::cTDItem(cTDPlayFieldBase *A_pPlayField, int A_iX /*= 0*/, int A_iY /*= 0*/)
: m_pPlayField(A_pPlayField), m_iX(A_iX), m_iY(A_iY), m_nWidth(0), m_nHeight(0)
{
   TD_DEBUG(;)

   reset(FALSE);
}

//==============================================================================
// cTDItem::~cTDItem
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDItem::~cTDItem()
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDItem::reset
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
void cTDItem::reset(char A_bResetPostion /*= TRUE*/)
{
   if (A_bResetPostion)
   {
      m_iX = -1;
      m_iY = -1;
   }
}


////////////////////////////////////////////////////////////////////////////////
// struct cTDAnimInfo (struct with info for animation - frames, loop type ... etc)
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDAnimInfo::cTDAnimInfo
//
// Rafal Zabdyr, 8.06.2006
//==============================================================================
cTDAnimInfo::cTDAnimInfo(unsigned char A_nFrames /*= 1*/, unsigned int A_nTicksPerFrame /*= 1*/, tLoop A_eLoop /*= eNoneLoop*/, unsigned int A_nWaitLoopTicks /*= 0*/)
: m_nFrames(A_nFrames), m_nTicksPerFrame(A_nTicksPerFrame), m_eLoop(A_eLoop), m_nWaitLoopTicks(A_nWaitLoopTicks)
{
}


////////////////////////////////////////////////////////////////////////////////
// struct cTDAnimMovInfo
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDAnimMovInfo::cTDAnimMovInfo
//
// Rafal Zabdyr, 8.06.2006
//==============================================================================
cTDAnimMovInfo::cTDAnimMovInfo(unsigned char A_nFrames /*= 1*/, unsigned int A_nTicksPerFrame /*= 1*/, tLoop A_eLoop /*= eNoneLoop*/, unsigned int A_nWaitLoopTicks /*= 0*/,
                               unsigned int A_nTicksPerMove /*= 1*/)
: cTDAnimInfo(A_nFrames, A_nTicksPerFrame, A_eLoop, A_nWaitLoopTicks), m_nTicksPerMove(A_nTicksPerMove)
{
}


////////////////////////////////////////////////////////////////////////////////
// class cTDAnimItemBase
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDAnimItemBase::cTDAnimItemBase
//
// Rafal Zabdyr, 11.01.2008
//==============================================================================
cTDAnimItemBase::cTDAnimItemBase(cTDPlayFieldBase *A_pPlayField)
: cTDItem(A_pPlayField)
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimItemBase::cTDAnimItemBase
//
// Rafal Zabdyr, 11.01.2008
//==============================================================================
cTDAnimItemBase::cTDAnimItemBase(cTDPlayFieldBase *A_pPlayField, int A_iX, int A_iY)
: cTDItem(A_pPlayField, A_iX, A_iY)
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimItemBase::~cTDAnimItemBase
//
// Rafal Zabdyr, 11.01.2008
//==============================================================================
cTDAnimItemBase::~cTDAnimItemBase()
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimItemBase::next_tick_core
//
//  if (A_nTickMax <= 0) => take default max value for ticks
//
// example:
//
//         fr0   fr1    ...frN             fr0
// frames:  | TPF |     ... | TPF |   WLT   |
// ticks:   | | | | | | ... | | | | | | | | |
//
// TPF - Ticks Per Frame
// WLT - Wait Loop Ticks
//
// Rafal Zabdyr, 1.06.2006
//==============================================================================
void cTDAnimItemBase::next_tick_core(const cTDAnimInfo &A_animInfo,
                                     int &A_iTick, unsigned int &A_iCurrWaitLoopTick, unsigned int &A_iCurrFrame, char &A_bLoopUp,
                                     int A_nTickMax, char A_bDraw)
{
   TD_DEBUG( cout << "curr_wait_loop_tick = " << A_iCurrWaitLoopTick << "\n"; )
   TD_DEBUG( cout << "A_iCurrFrame = " << A_iCurrFrame << "(up : " << int(A_bLoopUp) <<  ")\n"; )
   
   if (A_iCurrWaitLoopTick > 0)
   {
      A_iCurrWaitLoopTick--;
      return;
   }

   if (A_nTickMax <= 0)
      A_nTickMax = A_animInfo.ticks_per_frame(); // mod

   A_iTick++;
   A_iTick %= A_nTickMax;

   if (A_iTick % A_animInfo.ticks_per_frame() == 0) // next frame ?
   {
      TD_DEBUG( cout << "A_iCurrFrame = " << A_iCurrFrame << "(up : " << int(A_bLoopUp) <<  ") --> "; )

      if (A_bLoopUp)
      {
         A_iCurrFrame++;
         A_iCurrFrame %= A_animInfo.frames();
         if (A_iCurrFrame == 0)
         {
            switch (A_animInfo.loop_kind())
            {
               case ePingPongLoop:
                  A_bLoopUp = FALSE;
                  A_iCurrFrame = A_animInfo.frames() - (A_animInfo.frames() > 1 ? 2 : 1); // ping <-> pong 0->1->2->3->2->1->0->1
                  A_iCurrWaitLoopTick = A_animInfo.wait_loop_ticks();
                  break;

               case eProgressLoop:
               default:
                  ;
            }
         }
      }
      else
      {
         if (A_iCurrFrame == 0)
         {
            switch (A_animInfo.loop_kind())
            {
               case ePingPongLoop:
                  A_bLoopUp = TRUE;
                  A_iCurrFrame = (A_animInfo.frames() > 1 ? 2 : 1);
                  A_iCurrWaitLoopTick = A_animInfo.wait_loop_ticks();
                  break;

               case eProgressLoop:
               default:
                  A_iCurrFrame = A_animInfo.frames();
            }
         }
         A_iCurrFrame--;
      }

      TD_DEBUG( cout << " --> A_iCurrFrame = " << A_iCurrFrame << "(up : " << int(A_bLoopUp) <<  ")\n"; )

      if (A_bDraw)
         draw_item(TRUE);
   }
}


////////////////////////////////////////////////////////////////////////////////
// class cTDAnimItem
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDAnimItem::cTDAnimItem
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDAnimItem::cTDAnimItem(cTDPlayFieldBase *A_pPlayField, const cTDAnimInfo &A_animInfo)
: cTDAnimItemBase(A_pPlayField), m_animInfo(A_animInfo)
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimItem::cTDAnimItem
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDAnimItem::cTDAnimItem(cTDPlayFieldBase *A_pPlayField, int A_iX, int A_iY, const cTDAnimInfo &A_animInfo)
: cTDAnimItemBase(A_pPlayField, A_iX, A_iY), m_animInfo(A_animInfo)
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimItem::~cTDAnimItem
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
cTDAnimItem::~cTDAnimItem()
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimItem::reset
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
void cTDAnimItem::reset(char A_bResetPostion /*= TRUE*/)
{
   cTDItem::reset(A_bResetPostion);

   m_iCurrWaitLoopTick = 0;
   m_iCurrFrame = 0;
   m_bLoopUp = TRUE;
}

//==============================================================================
// cTDAnimItem::next_tick
//
// Rafal Zabdyr, 31.05.2006
//==============================================================================
void cTDAnimItem::next_tick(char A_bDraw /*= TRUE*/)
{
   next_tick_core(m_animInfo, m_iTick, m_iCurrWaitLoopTick, m_iCurrFrame, m_bLoopUp, MAX_TICK_DEFAULT, A_bDraw);

   TD_DEBUG( cout << "tick: " << m_iTick << endl; )
}


////////////////////////////////////////////////////////////////////////////////
// class cTDAnimMovItem
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// cTDAnimMovItem::cTDAnimMovItem
//
// Rafal Zabdyr, 9.06.2006
//==============================================================================
cTDAnimMovItem::cTDAnimMovItem(cTDPlayFieldBase *A_pPlayField, const cTDAnimMovInfo &A_animMovInfoX, const cTDAnimMovInfo &A_animMovInfoY)
: cTDAnimItemBase(A_pPlayField), m_animMovInfoX(A_animMovInfoX), m_animMovInfoY(A_animMovInfoY)
{
   TD_DEBUG(;)

   reset();
}

//==============================================================================
// cTDAnimMovItem::cTDAnimMovItem
//
// Rafal Zabdyr, 9.06.2006
//==============================================================================
cTDAnimMovItem::cTDAnimMovItem(cTDPlayFieldBase *A_pPlayField, int A_iX, int A_iY, const cTDAnimMovInfo &A_animMovInfoX, const cTDAnimMovInfo &A_animMovInfoY)
: cTDAnimItemBase(A_pPlayField, A_iX, A_iY), m_animMovInfoX(A_animMovInfoX), m_animMovInfoY(A_animMovInfoY)
{
   TD_DEBUG(;)

   reset(FALSE);
}

//==============================================================================
// cTDAnimMovItem::~cTDAnimMovItem
//
// Rafal Zabdyr, 9.06.2006
//==============================================================================
cTDAnimMovItem::~cTDAnimMovItem()
{
   TD_DEBUG(;)
}

//==============================================================================
// cTDAnimMovItem::reset
//
// Rafal Zabdyr, 9.06.2006
//==============================================================================
void cTDAnimMovItem::reset(char A_bResetPostion /*= TRUE*/)
{
   TD_DEBUG(;)

   cTDAnimItemBase::reset(A_bResetPostion);

   m_iPrevX = 0;
   m_iPrevY = 0;
   m_nMicroOffX = 0;
   m_nMicroOffY = 0;
   m_nPrevMicroOffX = 0;
   m_nPrevMicroOffY = 0;

   if (A_bResetPostion)
      m_eDirection = eMoveDown;

   m_iCurrWaitLoopTickX = 0;
   m_iCurrWaitLoopTickY = 0;
   m_iCurrFrameXY = 0;
   m_bLoopUpX = TRUE;
   m_bLoopUpY = TRUE;
   m_iTickX = 0;
   m_iTickY = 0;
}

//==============================================================================
// cTDAnimMovItem::next_tick
//
// Rafal Zabdyr, 9.06.2006
//==============================================================================
void cTDAnimMovItem::next_tick(char A_bDraw /*= TRUE*/)
{
   TD_DEBUG( ; )

   if (m_eDirection == eMoveLeft || m_eDirection == eMoveRight)
      next_tick_core(m_animMovInfoX,
                     m_iTickX, m_iCurrWaitLoopTickX, m_iCurrFrameXY, m_bLoopUpX, m_nMicroOffX, m_nPrevMicroOffX, MAX_TICK_DEFAULT, A_bDraw);
   else
      next_tick_core(m_animMovInfoY,
                     m_iTickY, m_iCurrWaitLoopTickY, m_iCurrFrameXY, m_bLoopUpY, m_nMicroOffY, m_nPrevMicroOffY, MAX_TICK_DEFAULT, A_bDraw);

   TD_DEBUG( cout << "tickX: " << m_iTickX << " ; " << "tickY: " << m_iTickY << endl; )
   TD_DEBUG( cout << "microOffX: " << m_nMicroOffX << " ; " << "microOffY: " << m_nMicroOffY << endl; )
}

//==============================================================================
// cTDAnimMovItem::go_up
//
// Rafal Zabdyr, 12.01.2008
//==============================================================================
void cTDAnimMovItem::go_up(unsigned int A_nMicroOff)
{
   cTDAnimItemBase::reset(FALSE);
   m_nMicroOffY = A_nMicroOff;
   m_nPrevMicroOffX = 0;
   m_nPrevMicroOffY = 0;
   m_iPrevY = m_iY;
   m_iY -= 1;
   m_eDirection = eMoveUp;
}

//==============================================================================
// cTDAnimMovItem::go_down
//
// Rafal Zabdyr, 12.01.2008
//==============================================================================
void cTDAnimMovItem::go_down(unsigned int A_nMicroOff)
{
   cTDAnimItemBase::reset(FALSE);
   m_nMicroOffY = -(int)A_nMicroOff;
   m_nPrevMicroOffX = 0;
   m_nPrevMicroOffY = 0;
   m_iPrevY = m_iY;
   m_iY += 1;
   m_eDirection = eMoveDown;
}

//==============================================================================
// cTDAnimMovItem::go_left
//
// Rafal Zabdyr, 12.01.2008
//==============================================================================
void cTDAnimMovItem::go_left(unsigned int A_nMicroOff)
{
   cTDAnimItemBase::reset(FALSE);
   m_nMicroOffX = A_nMicroOff;
   m_nPrevMicroOffX = 0;
   m_nPrevMicroOffY = 0;
   m_iPrevX = m_iX;
   m_iX -= 1;
   m_eDirection = eMoveLeft;
}

//==============================================================================
// cTDAnimMovItem::go_right
//
// Rafal Zabdyr, 12.01.2008
//==============================================================================
void cTDAnimMovItem::go_right(unsigned int A_nMicroOff)
{
   cTDAnimItemBase::reset(FALSE);
   m_nMicroOffX = -(int)A_nMicroOff;
   m_nPrevMicroOffX = 0;
   m_nPrevMicroOffY = 0;
   m_iPrevX = m_iX;
   m_iX += 1;
   m_eDirection = eMoveRight;
}

//==============================================================================
// cTDAnimMovItem::go_right
//
// Rafal Zabdyr, 25.01.2008
//==============================================================================
long cTDAnimMovItem::distance(const cTDAnimMovItem &A_objOther, unsigned int A_nMicroOff)
{
   long w, h;

   w = m_iX * A_nMicroOff + (m_nMicroOffX > 0 ? -m_nMicroOffX : m_nMicroOffX)
     - (A_objOther.m_iX * A_nMicroOff + (A_objOther.m_nMicroOffX > 0 ? -A_objOther.m_nMicroOffX : A_objOther.m_nMicroOffX));
   h = m_iY * A_nMicroOff + (m_nMicroOffY > 0 ? -m_nMicroOffY : m_nMicroOffY)
     - (A_objOther.m_iY * A_nMicroOff + (A_objOther.m_nMicroOffY > 0 ? -A_objOther.m_nMicroOffY : A_objOther.m_nMicroOffY));

   w *= w;
   h *= h;

   return (long)sqrt(double(w + h));
}

//==============================================================================
// cTDAnimMovItem::next_tick_core
//
// example:
//
//         fr0   fr1    ...frN             fr0
// frames:  | TPF |     ... | TPF |   WLT   |
// moves:   |TPM|   |   ...   |   |         |
// ticks:   | | | | | | ... | | | | | | | | |
//
// TPF - Ticks Per Frame
// WLT - Wait Loop Ticks
// TPM - Ticks Per Move
//
// Rafal Zabdyr, 9.06.2006
//==============================================================================
char cTDAnimMovItem::next_tick_core(const cTDAnimMovInfo &A_animInfo,
                                    int &A_iTick, unsigned int &A_iCurrWaitLoopTick, unsigned int &A_iCurrFrame, char &A_bLoopUp,
                                    int &A_nMicroOff, int &A_nPrevMicroOff,
                                    int A_nTickMax, char A_bDraw)
{
   TD_DEBUG( ; )

   char bMove = (A_nMicroOff != 0);

   if (A_nTickMax <= 0)
      A_nTickMax = A_animInfo.ticks_per_frame() * A_animInfo.ticks_per_move(); // mod

   A_nPrevMicroOff = A_nMicroOff;

   if (bMove) // is move ?
   { 
      cTDAnimItemBase::next_tick_core(A_animInfo, A_iTick, A_iCurrWaitLoopTick, A_iCurrFrame, A_bLoopUp, A_nTickMax, A_bDraw); // normal next tick core

      if (A_iTick % A_animInfo.ticks_per_move() == 0) // do next move+/-1 during move ?
      {
         if (A_nMicroOff < 0)
            A_nMicroOff++;
         else
            A_nMicroOff--;
      }
   }
   else
      A_iTick++;

   return bMove;
}
