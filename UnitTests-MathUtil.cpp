//
// unit test for TDolphin's MathUtil lib
//
// (C) TDolphin 2007
//
// craeted: 2.11.2007
//    last: 2.11.2007
//

#include <iostream>

#include "td_math_util.h"


using namespace std;

void UnitTest_MathUtil(void)
{
   unsigned int i;

   cout << "================" << endl << "cGraph unit test" << endl;
   
   cIndirectGraph graph;
   cout << "graph size = " << graph.size() << endl;
   for (i = 0; i < 5; i++)
      graph.add_node();
   cout << "graph size = " << graph.size() << endl
        << "edge at (1,2) = " << graph.is_edge(1,2) << " (2,1) = " << graph.is_edge(2,1) << endl;
   cout << "add edge at (1,2)" << endl;
   graph.add_edge(1,2);
   cout << "edge at (1,2) = " << graph.is_edge(1,2) << " (2,1) = " << graph.is_edge(2,1) << endl;
   
   cout << "- THE END -" << endl;
}
