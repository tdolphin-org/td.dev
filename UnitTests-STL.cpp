//
// unit test for TDolphin's STL
//
// (C) TDolphin 2007-2008
//
// craeted: 9.08.2007
//    last: 24.01.2008
//

#ifdef LINUX
#include <stdlib.h>
#include <stdio.h>
#else
#include <iostream>
#endif
#include "td_stl_vector.h"
#include "td_stl_pair.h"
#include "td_stl_triplet.h"


#ifdef LINUX

namespace std
{

class ENDL { };

ENDL endl;

class ostream
{
   public:
      ostream() {}
      ostream &operator<<(ENDL);
      ostream &operator<<(char *);
      ostream &operator<<(unsigned int);
      ostream &operator<<(int);
      ostream &operator<<(double);
};

ostream &ostream::operator<<(ENDL _obj)
{
   printf("\n");
   return *this;
}

ostream &ostream::operator<<(char *_str)
{
   printf("%s", _str);
   return *this;
}

ostream &ostream::operator<<(unsigned int _val)
{
   printf("%d", _val);
   return *this;
}

ostream &ostream::operator<<(int _val)
{
   printf("%d", _val);
   return *this;
}

ostream &ostream::operator<<(double _val)
{
   printf("%f", _val);
   return *this;
}

// global streams
ostream cout;

};

#endif


using namespace std;

void print_int_vector(vector <unsigned int> &vect)
{
   cout << "vector size:" << vect.size() << " :: ";
   for (int i = 0; i < vect.size(); i++)
      cout << (int)vect[i] << ";";
   cout << endl;
}

struct sTest
{
   int a;
   int b;
   int c;
};

void UnitTest_STL(void)
{
   unsigned int i;

   cout << "================" << endl << "STL unit test" << endl;

   // pair
   pair<unsigned int, char> pairTest(10, 'z');
   cout << "pair = (" << pairTest.first << ",'" << pairTest.second << "')" << endl << endl;

   // triplet
   triplet<unsigned int, char, double> tripTest(10, 'z', 3.1415);
   cout << "triplet = (" << tripTest.first << ",'" << tripTest.second << ",'" << tripTest.third << "')" << endl << endl;

   // vector
   vector <unsigned int> vectTest;
   vector <unsigned int> vectTest2(vectTest);
   
   cout << "init vector  ..." << endl;
   print_int_vector(vectTest);

   cout << "let's resize(20) ..." << endl;
   vectTest.resize(20);
   print_int_vector(vectTest);

   cout << "let's resize(0) ..." << endl;
   vectTest.resize(0);
   print_int_vector(vectTest);

//   char test[sizeof(sTest)];
//   sTest *p = new ((size_t)test) sTest;
   
   vector <unsigned int> vectCopy;
   vectCopy = vectTest;

//   printf("vectTest mem at %x\n", vectTest.m_pArray);
//   printf("vectTest2 mem at %x\n", vectTest2.m_pArray);
//   printf("vectCopy mem at %x\n", vectCopy.m_pArray);

   cout << "let's push_back 30 ints ..." << endl;
   for (i = 0; i < 30; i++)
      vectTest.push_back(i);
   print_int_vector(vectTest);

   cout << "let's erase first one ..." << endl;
   vector<unsigned int>::iterator iter = vectTest.begin();
   iter = vectTest.erase(iter);
   print_int_vector(vectTest);

   cout << "let's erase second one ..." << endl;
   ++iter;
   vectTest.erase(iter);
   print_int_vector(vectTest);

   cout << "let's erase last one ..." << endl;
   iter = vectTest.end();
   vectTest.erase(--iter);
   print_int_vector(vectTest);

   cout << "- THE END -" << endl;
}
