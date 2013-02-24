//
// unit test for TDolphin's GameObjects lib
//
// (C) TDolphin 2008
//
// craeted: 8.01.2008
//    last: 8.01.2008
//

#include <iostream>

#include "td_common_defines.h"
#include "td_game_objects.h"


using namespace std;


class cTest : public cTDAnimMovItem
{
public:
   cTest(const cTDAnimMovInfo &A_animMovInfoX, const cTDAnimMovInfo &A_animMovInfoY)
   : cTDAnimMovItem(NULL, A_animMovInfoX, A_animMovInfoY)
   {
      m_nMicroOffX = 10;
   }
   ~cTest() {}

   // interface
   virtual void reset(char A_bResetPostion = TRUE) {}
   virtual char draw_item(char A_bByEffect = FALSE) { return TRUE; }
};

void UnitTest_GameObjects(void)
{
   cTest item1(cTDAnimMovInfo(6, 4, ePingPongLoop, 0, 1), cTDAnimMovInfo(6, 4, ePingPongLoop, 0, 1)),
         item2(cTDAnimMovInfo(6, 4, ePingPongLoop, 0, 2), cTDAnimMovInfo(6, 4, ePingPongLoop, 0, 2));

   for (int i = 0; i < 10; i++)
   {
      cout << "\n###### item1\n"; item1.next_tick();
      cout << "\n###### item2\n"; item2.next_tick();
   }
 
}

