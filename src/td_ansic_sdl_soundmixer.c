/*

    TDolphin projects

    (c) TDolphin 2005-2007

    td_ansic_sdl_soundmixer.c

    SDL sound support (sound mixer) for all TDolphin's projects
    (Ansi C/C++ programs) using SDL

    created: 7.09.2005
       last: 23.04.2007

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "td_common_defines.h"

#include "td_ansic_sdl_soundmixer.h"


// global variables

sTDSample G_aSamples[__TD_SDL_MAX_SAMPLES];

char G_bAudioInitiated = FALSE, // is audio was initiated (SLD sub system)
     G_bSoundAvailable = FALSE; // if sound mixer was succesfully initialized


//==============================================================================
// td_sdl_sm_open
//
// Rafal Zabdyr, 7.09.2005
//==============================================================================
int td_sdl_sm_open(void)
{
   G_bAudioInitiated = FALSE;
   G_bSoundAvailable = FALSE;

   memset(G_aSamples, 0, sizeof(G_aSamples));

   G_bAudioInitiated = (SDL_InitSubSystem(SDL_INIT_AUDIO) >= 0);
   if (!G_bAudioInitiated)
      return -2;

   if (Mix_OpenAudio(__TD_SDL_SOUND_FREQ, AUDIO_S16SYS, __TD_SDL_CHANNELS, __TD_SDL_AUDIO_BUFFERS))
   {
      printf("%s\n",  Mix_GetError());
      return -1;
   }

   G_bSoundAvailable = TRUE;

   return 0;
}

//==============================================================================
// td_sdl_sm_close
//
// Rafal Zabdyr, 7.09.2005
//==============================================================================
void td_sdl_sm_close(void)
{
   int i;

   if (!G_bAudioInitiated)
      return;

   if (!G_bSoundAvailable)
      return;

   Mix_HaltChannel(-1); // stop all sound effects
   Mix_HaltMusic(); // stop music

   Mix_CloseAudio();

   for(i = 0; i < __TD_SDL_MAX_SAMPLES; ++i)
      Mix_FreeChunk(G_aSamples[i].m_pData);

   memset(G_aSamples, 0, sizeof(G_aSamples));

   G_bAudioInitiated = FALSE;
   G_bSoundAvailable = FALSE;
}

//==============================================================================
// td_sdl_sm_play
//
// Rafal Zabdyr, 7.09.2005
//==============================================================================
int td_sdl_sm_play_sample(int A_iChannel, unsigned int A_iSample, int A_iLoops, unsigned int A_nPercentVolume)
{
   int iChannel;

   if (!G_bSoundAvailable)
      return -1;

   if (A_iSample >= __TD_SDL_MAX_SAMPLES)
      return -1; 

   if (!G_aSamples[A_iSample].m_pData)
      return -1;

   if (A_nPercentVolume > 100)
      A_nPercentVolume = 100;

   iChannel = Mix_PlayChannel(-1, G_aSamples[A_iSample].m_pData, A_iLoops);
   Mix_Volume(iChannel, MIX_MAX_VOLUME * A_nPercentVolume / 100);

   return iChannel;
}

//==============================================================================
// td_sdl_sm_load_sample
//
// Rafal Zabdyr, 7.09.2005
//==============================================================================
int td_sdl_sm_load_sample(int A_iSample, const char *A_strFileName)
{
   if (A_iSample >= __TD_SDL_MAX_SAMPLES)
      return -1;

   G_aSamples[A_iSample].m_pData = Mix_LoadWAV(A_strFileName);
   if (G_aSamples[A_iSample].m_pData == NULL)
   {
      printf("%s\n",  Mix_GetError());
      return -1;
   }

   return 0;
}
