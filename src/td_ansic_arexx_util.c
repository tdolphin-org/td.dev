/*

    TDolphin projects

    (c) TDolphin 2007

    td_arexx_util.c

    functions for manipulate arexx (Amiga Rexx)
    (Ansi C/C++ programs)

    created: 23.11.2007
       last: 24.11.2007

*/

#include <stdio.h>
#include <stdlib.h>
#include <exec/ports.h>
#include <exec/types.h>
#include <rexx/rxslib.h>
#include <proto/exec.h>
#include <proto/rexxsyslib.h>

#include "td_ansic_arexx_util.h"


// global variables


//==============================================================================
// SendARexxCommand
//
// Rafal Zabdyr, 17.11.2007
//==============================================================================
const char *SendARexxCommand(struct MsgPort *A_pPort, const char *A_strDestPortName, const char *A_strCommand)
{
   const char *strRet = NULL;
   struct MsgPort *rexxport;
   struct RexxMsg *rxmsg, *retrxmsg;
   char command[256];

   if (A_pPort)
   {
      if (rxmsg = CreateRexxMsg(A_pPort, NULL, NULL))
      {
         sprintf(command, "%s", A_strCommand);
         rxmsg->rm_Action = RXCOMM | RXFF_RESULT; //RXCOMM | RXFB_NOIO;
         ARG0(rxmsg) = command;
         if (FillRexxMsg(rxmsg, 1, 0))
         {
            Forbid();
            rexxport = FindPort(A_strDestPortName);
            if (rexxport)
            {
               PutMsg(rexxport, (struct Message *)rxmsg);
               WaitPort(A_pPort);
            }
            Permit();
            retrxmsg = (struct RexxMsg *)GetMsg(A_pPort);
            //printf("0x%x\n", retrxmsg);
            //if (IsRexxMsg(retrxmsg))
            //   printf("ret is rexx cmd\n");

            if (retrxmsg)
            //printf("ret command: %x arg0: %x res2: %s\n", (char*)retrxmsg->rm_CommAddr, (char*)retrxmsg->rm_Args[0], (char*)retrxmsg->rm_Result2);
               strRet = (const char*)retrxmsg->rm_Result2;

            ClearRexxMsg(rxmsg,1);
         }
         DeleteRexxMsg(rxmsg);
      }
   }

   return strRet;
}

