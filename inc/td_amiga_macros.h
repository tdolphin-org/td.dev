/*

    TDolphin projects

    (c) TDolphin 2007

    td_amiga_macros.h

    AmigaOS related macros for all TDolphin's projects (Ansic C/C++ programs)
    supported platforms:
     - MorphOS
     - AmigaOS
   (future)
     - AROS
     - AmigaOS4

    created: 18.11.2007
       last: 18.11.2007

*/

#ifndef __TD_AMIGA_MACROS_H
#define __TD_AMIGA_MACROS_H



#ifdef __MORPHOS__
#define SAVEDS   __saveds
#define REGARGS  __regargs
#define STDARGS  __attribute__((stkparm))
#define INLINE   __inline
#define REG(x,p) p __asm( #x )
#define REGARRAY
#define ASM

#define M_HOOK(n,y,z) \
    static LONG n##_GATE(void); \
    static LONG n##_GATE2(struct Hook *hook,y,z); \
    static struct EmulLibEntry n = {TRAP_LIB,0,(void (*)(void))n##_GATE}; \
    static LONG n##_GATE(void) {return (n##_GATE2((void *)REG_A0,(void *)REG_A2,(void *)REG_A1));} \
    static struct Hook n##_hook = {{0,0},(void *)&n}; \
    static LONG n##_GATE2(struct Hook *hook, y, z)

#define M_DISP(n) static ULONG _##n(void)
#define M_DISPSTART \
    struct IClass *cl = (struct IClass *)REG_A0; \
    Object        *obj = (Object *)REG_A2; \
    Msg            msg  = (Msg)REG_A1;
#define M_DISPEND(n) static struct EmulLibEntry n = {TRAP_LIB,0,(void *)&_##n};
#define DISP(n) ((APTR)&n)

#define copymem(to,from,len) CopyMem((APTR)(from),(APTR)(to),(ULONG)(len))

#else // __MORPHOS__

#define SAVEDS   __saveds
#define ASM      __asm
#define REGARGS  __regargs
#define STDARGS  __stdargs
#define INLINE   __inline
#define REG(x,p) register __ ## x p
#define REGARRAY register

#define max(a,b) __builtin_max(a,b)
#define min(a,b) __builtin_min(a,b)

#define M_HOOK(n,y,z) \
    static LONG SAVEDS ASM n##_func(REG(a0,struct Hook *hook),REG(a2,y),REG(a1,z)); \
    static struct Hook n##_hook = {0,0,(HOOKFUNC)n##_func}; \
    static LONG ASM SAVEDS n##_func(REG(a0,struct Hook *hook),REG(a2,y),REG(a1,z))

#define M_DISP(n) static ULONG ASM SAVEDS n(REG(a0,struct IClass *cl),REG(a2,Object *obj),REG(a1,Msg msg))
#define M_DISPSTART
#define M_DISPEND(n)
#define DISP(n) (n)

#define copymem(to,from,len) memcpy((APTR)(to),(APTR)(from),(ULONG)(len))

#endif //__MORPHOS__


#ifndef MAKE_ID
#define MAKE_ID(a,b,c,d) ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))
#endif



#endif // __TD_AMIGA_MACROS_H
