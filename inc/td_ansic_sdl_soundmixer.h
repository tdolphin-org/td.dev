/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_ansic_sdl_soundmixer.h

    SDL sound support (sound mixer) for all TDolphin's projects
    (Ansi C/C++ programs) using SDL

    created: 7.09.2005
       last: 10.02.2012

*/

#ifndef __TD_ANSIC_SDL_SOUNDMIXER_H
#define __TD_ANSIC_SDL_SOUNDMIXER_H



// defines

#define __TD_SDL_MAX_SAMPLES     16
#define __TD_SDL_CHANNELS        2 // 2 - stereo, 3 = 2+1 .. etc
#define __TD_SDL_SOUND_FREQ      22050 // 22050 44100
#ifdef LINUX
#define __TD_SDL_AUDIO_BUFFERS   512 // for smaller lag (delay in playing)!!!
#else
#define __TD_SDL_AUDIO_BUFFERS   4096 // for MorphOS is ok (?)
#endif

// types/enums

enum TChannel { eCh0 = 0, eCh1 = 1 };

typedef struct
{
   Mix_Chunk *m_pData;
} sTDSample;


// prototypes

int td_sdl_sm_open(void);
void td_sdl_sm_close(void);
int td_sdl_sm_play_sample(int A_iChannel, unsigned int A_iSample, int A_iLoops, unsigned int A_nPrecentVolume);
int td_sdl_sm_load_sample(int A_iSample, const char *A_strFileName);



#endif // __TD_ANSIC_SDL_SOUNDMIXER_H

