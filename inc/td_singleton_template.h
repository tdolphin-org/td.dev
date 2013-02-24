/*

    TDolphin projects

    (c) TDolphin 2005

    td_singleton_template.h

    Singleton Template for TDolphin's projects (C++)

    created: 15.10.2005
       last: 20.10.2005

*/

#ifndef __TD_SINGLETON_TEMPLATE_H
#define __TD_SINGLETON_TEMPLATE_H



// templates

template <typename T>
class TDSingleton
{
   TDSingleton() {};
   TDSingleton(const TDSingleton&) {};
   ~TDSingleton() {};

public:
   static T &instance()
   {
      static T inst;
      return inst;
   };
};



#endif // __TD_SINGLETON_TEMPLATE_H

