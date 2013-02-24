/*

    TDolphin projects

    (c) TDolphin 2006-2008

    td_game_objects.h

    Base abstract classes for TDolphin's games. Classes declaration/definitions.

    created: 31.05.2006 (rewrite classes from tdbz_game_objects.h)
       last: 25.01.2008

*/

#ifndef __TD_GAME_OBJECTS_H
#define __TD_GAME_OBJECTS_H



// defines

#define MAX_TICK_DEFAULT  -1

// types/enums

enum tMove
{
   eMoveUp = 0,
   eMoveRight = 1,
   eMoveDown = 2,
   eMoveLeft = 3
};

enum tBitMove
{
   eBMoveNone = 0,
   eBMoveUp = 1,
   eBMoveRight = 2,
   eBMoveUpRight = 3,
   eBMoveDown = 4,
   eBMoveDownRight = 6,
   eBMoveLeft = 8,
   eBMoveUpLeft = 9,
   eBMoveDownLeft = 12
};

enum tLoop
{
   eNoneLoop = 0,
   eProgressLoop,
   ePingPongLoop
};


// structs/classes

////////////////////////////////////////////////////////////////////////////////
// class cTDPlayFieldBase (base class for all game playfields)
// offset, number of horizontal (X) and vertical (Y) fields, tile size
// in abstract pixels
////////////////////////////////////////////////////////////////////////////////
class cTDPlayFieldBase
{
public:
   cTDPlayFieldBase();
   cTDPlayFieldBase(int A_nOffsetX, int A_nOffsetY, unsigned int A_nFieldsX, unsigned int A_nFieldsY, unsigned int A_nTileSize);
   virtual ~cTDPlayFieldBase();

   void set_offset(int A_nOffsetX, int A_nOffsetY) { m_nOffsetX = A_nOffsetX;  m_nOffsetY = A_nOffsetY; }
   void set_size(unsigned int A_nFieldsX, unsigned int A_nFieldsY) { m_nFieldsX = A_nFieldsX; m_nFieldsY = A_nFieldsY; alloc_field(); }
   void set_tileSize(unsigned int A_nTileSize) { m_nTileSize = A_nTileSize; }

   int offsetX() const { return m_nOffsetX; }
   int offsetY() const { return m_nOffsetY; }
   unsigned int fieldsX() const { return m_nFieldsX; } 
   unsigned int fieldsY() const { return m_nFieldsY; }
   unsigned int tileSize() const { return m_nTileSize; }

   virtual int get_xy(unsigned int A_iX, unsigned int A_iY) const;

protected:
   virtual char alloc_field();

// members
protected:
   int m_nOffsetX, // field offset on screen
       m_nOffsetY; // ...
   unsigned int m_nFieldsX, // number of horizontal fields (X)
                m_nFieldsY, // ...
                m_nTileSize; // size (XxY) of one tile (field)
   int *m_aField; // pointer to X * Y array with content (in derived class should be used enums)
};

////////////////////////////////////////////////////////////////////////////////
// class cTDPlayFieldAndStuffBase (base class all game playfields)
// additionali have second array for use as stuff, first array in cTDPlayFieldBase
// can be use as background array of tiles
////////////////////////////////////////////////////////////////////////////////
class cTDPlayFieldAndStuffBase : public cTDPlayFieldBase
{
public:
   cTDPlayFieldAndStuffBase();
   cTDPlayFieldAndStuffBase(int A_nOffsetX, int A_nOffsetY, unsigned int A_nFieldsX, unsigned int A_nFieldsY, unsigned int A_nTileSize);
   virtual ~cTDPlayFieldAndStuffBase();

protected:
   virtual char alloc_field();

private:
   char alloc_fieldStuff();

// members
protected:
   int *m_aFieldStuff; // pointer to X * Y array with stuff located on playfiled (in derived class should be used enums)
};

////////////////////////////////////////////////////////////////////////////////
// class cTDItem (base class for any Item on playfield)
////////////////////////////////////////////////////////////////////////////////
class cTDItem
{
public:
   cTDItem(cTDPlayFieldBase *A_pPlayField, int A_iX = 0, int A_iY = 0);
   virtual ~cTDItem();

// interface
   virtual void reset(char A_bResetPostion = TRUE);

   virtual char draw_item(char A_bByEffect = FALSE) = 0;

   unsigned int x() const { return m_iX; }
   unsigned int y() const { return m_iY; }
   unsigned int w() const { return m_nWidth; }
   unsigned int h() const { return m_nHeight; }

// members
protected:
   cTDPlayFieldBase *m_pPlayField; // pointer (logical connection) to PlayField, which is parent for each item

   int m_iX, // position X (on field) < 0 means not placed
       m_iY; // position Y (...)
   unsigned int m_nWidth, // width in tiles (or in pixels, or in whatever else you want :) )
                m_nHeight; // height in tiles (...)
};

////////////////////////////////////////////////////////////////////////////////
// struct cTDAnimInfo (struct with info for animation - frames, loop type ... etc)
////////////////////////////////////////////////////////////////////////////////
struct cTDAnimInfo
{
   cTDAnimInfo(unsigned char A_nFrames = 1, unsigned int A_nTicksPerFrame = 1, tLoop A_eLoop = eNoneLoop, unsigned int A_nWaitLoopTicks = 0);

// interface
   unsigned char frames() const { return m_nFrames; }
   unsigned int ticks_per_frame() const { return m_nTicksPerFrame; }
   tLoop loop_kind() const { return m_eLoop; }
   unsigned int wait_loop_ticks() const { return m_nWaitLoopTicks; }

// members
protected:
   unsigned char m_nFrames; // number of frames (if 1 you will get no animation)
   unsigned int m_nTicksPerFrame; // number of ticks per each frame
   tLoop m_eLoop; // kind of loop for anim
   unsigned int m_nWaitLoopTicks; // delay betwean each loop (begin/end)
};

////////////////////////////////////////////////////////////////////////////////
// struct cTDAnimMovInfo (struct with info for animation with move - frames, loop type ... etc)
////////////////////////////////////////////////////////////////////////////////
struct cTDAnimMovInfo : public cTDAnimInfo
{
   cTDAnimMovInfo(unsigned char A_nFrames = 1, unsigned int A_nTicksPerFrame = 1, tLoop A_eLoop = eNoneLoop, unsigned int A_nWaitLoopTicks = 0,
                  unsigned int A_nTicksPerMove = 1);

// interface
   unsigned int ticks_per_move() const { return m_nTicksPerMove; }

// members
protected:
   unsigned int m_nTicksPerMove; // number of ticks per each move in given direction by one pixel (unit)
};

////////////////////////////////////////////////////////////////////////////////
// class cTDAnimItemBase (base class for any Animated (and movable) Item on playfield)
////////////////////////////////////////////////////////////////////////////////
class cTDAnimItemBase : public cTDItem
{
public:
   cTDAnimItemBase(cTDPlayFieldBase *A_pPlayField);
   cTDAnimItemBase(cTDPlayFieldBase *A_pPlayField, int A_iX, int A_iY);

   virtual ~cTDAnimItemBase();

// interface
   virtual void next_tick(char A_bDraw = TRUE) = 0;
   virtual char draw_item(char A_bByEffect = FALSE) = 0;

protected:
   void next_tick_core(const cTDAnimInfo &A_animInfo,
                       int &A_iTick, unsigned int &A_iCurrWaitLoopTick, unsigned int &A_iCurrFrame, char &A_bLoopUp,
                       int A_nTickMax, char A_bDraw);
};


////////////////////////////////////////////////////////////////////////////////
// class cTDAnimItem (Animated Item on playfield)
////////////////////////////////////////////////////////////////////////////////
class cTDAnimItem : public cTDAnimItemBase
{
public:
   cTDAnimItem(cTDPlayFieldBase *A_pPlayField, const cTDAnimInfo &A_animInfo);
   cTDAnimItem(cTDPlayFieldBase *A_pPlayField, int A_iX, int A_iY, const cTDAnimInfo &A_animInfo);
   virtual ~cTDAnimItem();

// interface
   virtual void reset(char A_bResetPostion = TRUE);
   virtual void next_tick(char A_bDraw = TRUE);
   virtual char draw_item(char A_bByEffect = FALSE) = 0;

// members
protected:
   cTDAnimInfo m_animInfo;

   unsigned int m_iCurrWaitLoopTick; // current delay betwean loops
   unsigned int m_iCurrFrame; // current frame to draw
   char m_bLoopUp; // direction order for changing frames in loop TRUE => 0 .. N-1

private:
   int m_iTick; // current tick for animation (max is: m_nFrames * m_nTicksPerFrame)
};

////////////////////////////////////////////////////////////////////////////////
// class cTDAnimMovItem (Animated Movable Item on playfield)
////////////////////////////////////////////////////////////////////////////////
class cTDAnimMovItem : public cTDAnimItemBase
{
public:
   cTDAnimMovItem(cTDPlayFieldBase *A_pPlayField, const cTDAnimMovInfo &A_animMovInfoX, const cTDAnimMovInfo &A_animMovInfoY);
   cTDAnimMovItem(cTDPlayFieldBase *A_pPlayField, int A_iX, int A_iY, const cTDAnimMovInfo &A_animMovInfoX, const cTDAnimMovInfo &A_animMovInfoY);
   virtual ~cTDAnimMovItem();

// interface
   virtual void reset(char A_bResetPostion = TRUE);
   virtual void next_tick(char A_bDraw = TRUE);
   virtual char draw_item(char A_bByEffect = FALSE) = 0;

   unsigned int px() const { return m_iPrevX; }
   unsigned int py() const { return m_iPrevY; }

   tMove &direction() { return m_eDirection; }

   char is_moving() { return (m_nMicroOffX != 0 || m_nMicroOffY != 0); }

   void go_up(unsigned int A_nMicroOff);
   void go_down(unsigned int A_nMicroOff);
   void go_left(unsigned int A_nMicroOff);
   void go_right(unsigned int A_nMicroOff);

   long distance(const cTDAnimMovItem &A_objOther, unsigned int A_nMicroOff);

protected:
   char next_tick_core(const cTDAnimMovInfo &A_animInfo,
                       int &A_iTick, unsigned int &A_iCurrWaitLoopTick, unsigned int &A_iCurrFrame, char &A_bLoopUp,
                       int &A_nMicroOff, int &A_nPrevMicroOff,
                       int A_nTickMax, char A_bDraw);

// members
protected:
   int m_iPrevX, // previous position X
       m_iPrevY; // ... Y

   tMove m_eDirection; // direction of move

   cTDAnimMovInfo m_animMovInfoX, // animated moveable item info for X (frames, ticks per frame, ... ect)
                  m_animMovInfoY; // ...

   unsigned int m_iCurrWaitLoopTickX, // current delay betwean loops X
                m_iCurrWaitLoopTickY; // ... Y ...
   unsigned int m_iCurrFrameXY; // current frame to draw (in X and Y - not possible to move in X and Y in the same time!!!)
   char m_bLoopUpX, // direction order for changing frames in loop X, TRUE => 0 .. N-1
        m_bLoopUpY; // ... Y ...

   int m_nMicroOffX, // X offset (in abstract pixels) for moving (during move is != 0)
       m_nMicroOffY, // Y ...
       m_nPrevMicroOffX, // previous X offset
       m_nPrevMicroOffY; //

private:
   int m_iTickX, // current tick for moving animation X (max is: m_nFrames * NWW(m_nTicksPerFrame * m_nTicksPerMove))
       m_iTickY; // ... Y ...
};



#endif // __TD_GAME_OBJECTS_H
