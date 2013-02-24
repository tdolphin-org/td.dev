//
// unit tests for TDolphin's STL, MathUtil lib, ...
//
// (C) TDolphin 2007-2008
//
// created: 2.11.2007
//    last: 8.01.2008
//

#include <iostream>

using namespace std;


void UnitTest_STL(void);
void UnitTest_MathUtil(void);
void UnitTest_GameObjects(void);

int main(void)
{
   cout << "Select test:\n 1 - STL\n 2 - MathUtil\n 3 - GameObjects\n";

   int iTest;
   cin >> iTest;

   switch (iTest)
   {
      case 1: UnitTest_STL(); break;
      case 2: UnitTest_MathUtil(); break;
      case 3: UnitTest_GameObjects(); break;
   }

   return 0;
}
