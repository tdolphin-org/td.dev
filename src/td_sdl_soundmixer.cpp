/*

    TDolphin projects

    (c) TDolphin 2005-2008

    td_sdl_soundmixer.cpp

    SDL sound support (sound mixer) for all TDolphin's projects
    (C++ programs) using SDL

    Important Changes:

      02.09.2006 Rafal Zabdyr    standard SDL audio --> SDL_mixer
                                 I have decided to use SDL_mixer library for audio (sounds and music)
                                 instead of standard SDL audio routines for samples and etc.

    created: 7.09.2005
       last: 19.10.2008

*/


#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

//#define __TD_DEBUG

#include "td_common_defines.h"
#include "td_sdl_soundmixer.h"

using namespace std;

//==============================================================================
// struct sTDSample
//==============================================================================

//==============================================================================
// sTDSample::sTDSample
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
sTDSample::sTDSample()
{
   reset();
}

//==============================================================================
// sTDSample::~sTDSample
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
sTDSample::~sTDSample()
{
   TD_DEBUG(;)
   free();
}

//==============================================================================
// sTDSample::reset
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
void sTDSample::reset(void)
{
   m_pData = NULL;
}

//==============================================================================
// sTDSample::free
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
void sTDSample::free(void)
{
   if (m_pData)
   {
      TD_DEBUG(;)
      Mix_FreeChunk(m_pData);
      reset();
   }
}

//==============================================================================
// sTDSample::load
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
char sTDSample::load(const char *A_strFileName)
{
   free();

   m_pData = Mix_LoadWAV(A_strFileName);
   if (m_pData == NULL)
   {
      cerr << Mix_GetError() << "\n";
      return FALSE;
   }

   TD_DEBUG( cout << "loading sample ... ok\n"; )

   return TRUE;
}

//==============================================================================
// struct sTDMusic
//==============================================================================

//==============================================================================
// sTDMusic::sTDMusic
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
sTDMusic::sTDMusic()
{
   reset();
}

//==============================================================================
// sTDMusic::~sTDMusic
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
sTDMusic::~sTDMusic()
{
   TD_DEBUG(;)
   free();
}

//==============================================================================
// sTDMusic::reset
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
void sTDMusic::reset(void)
{
   m_pData = NULL;
}

//==============================================================================
// sTDMusic::free
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
void sTDMusic::free(void)
{
   if (m_pData)
   {
      TD_DEBUG( cout << m_pData << endl; )
      Mix_FreeMusic(m_pData); // to-do segmentation fault
      //TD_DEBUG(;)
      reset();
      //TD_DEBUG(;)
   }
}

//==============================================================================
// sTDMusic::load
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
char sTDMusic::load(const char *A_strFileName)
{
   free();

   m_pData = Mix_LoadMUS(A_strFileName);
   if (m_pData == NULL)
   {
      cerr << Mix_GetError() << "\n";
      return FALSE;
   }

   TD_DEBUG( cout << "loading music ... ok\n"; )

   return TRUE;
}


//==============================================================================
// class cTDSampleArray
//==============================================================================

//==============================================================================
// cTDSampleArray::cTDSampleArray
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
cTDSampleArray::cTDSampleArray()
{
   TD_DEBUG(;)

   reset();
}

//==============================================================================
// cTDSampleArray::~cTDSampleArray
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
cTDSampleArray::~cTDSampleArray()
{
   TD_DEBUG(;)

   s_free_all();
}

//==============================================================================
// cTDSampleArray::reset
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
void cTDSampleArray::reset(void)
{
   // for future
}

//==============================================================================
// cTDSampleArray::s_free_all
//
// Rafal Zabdyr, 20.03.2006
//==============================================================================
void cTDSampleArray::s_free_all(void)
{
   TD_DEBUG(;)

   for (int i = 0; i < __TD_SDL_MAX_SAMPLES; i++)
      m_aSamples[i].free();
}

//==============================================================================
// cTDSampleArray::s_load
//
// Rafal Zabdyr, 21.03.2006
//==============================================================================
int cTDSampleArray::s_load(const char *A_strFileName, int A_iSample /*= TD_RETIDX_ERR*/)
{
   int iFirstFree;

   TD_DEBUG( cout << "-> '" << A_strFileName << " '\n"; )

   if (!A_strFileName)
      return TD_RETIDX_ERR;

   if ((A_iSample < 0) || (A_iSample >= __TD_SDL_MAX_SAMPLES))
      A_iSample = TD_RETIDX_ERR;

   if (A_iSample == TD_RETIDX_ERR)
   {
      for (iFirstFree = 0; iFirstFree < __TD_SDL_MAX_SAMPLES; iFirstFree++)
         if (m_aSamples[iFirstFree].data())
            break;
   }
   else
   {
      if (A_iSample < 0)
         return TD_RETIDX_ERR;
      iFirstFree = A_iSample;
   }

   if (iFirstFree >= __TD_SDL_MAX_SAMPLES) // check if no more free sounds
      return TD_RETIDX_ERR;

   if (m_aSamples[iFirstFree].data()) // check if free (possile only when A_iSample != TD_RETIDX_ERR)
      return TD_RETIDX_ERR;

   TD_DEBUG( cout << " ... loading ... " << A_strFileName << " ... "; )

   // -->

   if (!m_aSamples[iFirstFree].load(A_strFileName))
   {
      // load error
      TD_DEBUG( cout << "failed\n"; )
      return TD_RETIDX_ERR;
   }

   TD_DEBUG( cout << "ok\n"; )

   return iFirstFree;
}

//==============================================================================
// cTDSampleArray::s_free
//
// Rafal Zabdyr, 21.03.2006
//==============================================================================
char cTDSampleArray::s_free(int A_iSample)
{
   if ((A_iSample < 0) || (A_iSample >= __TD_SDL_MAX_SAMPLES))
      return FALSE;

   m_aSamples[A_iSample].free();

   return TRUE;
}

//==============================================================================
// cTDSampleArray::operator[]
//
// Rafal Zabdyr, 21.03.2006
//==============================================================================
sTDSample *cTDSampleArray::operator[](int A_iSample) const
{
   if ((A_iSample < 0) || (A_iSample >= __TD_SDL_MAX_SAMPLES))
      return NULL;

   return (sTDSample *)&m_aSamples[A_iSample];
}


//==============================================================================
// class cTDMusicArray
//==============================================================================

//==============================================================================
// cTDMusicArray::cTDMusicArray
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
cTDMusicArray::cTDMusicArray()
{
   TD_DEBUG(;)

   reset();
}

//==============================================================================
// cTDMusicArray::~cTDMusicArray
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
cTDMusicArray::~cTDMusicArray()
{
   TD_DEBUG(;)

   m_free_all();
}

//==============================================================================
// cTDMusicArray::reset
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
void cTDMusicArray::reset(void)
{
   // for future
}

//==============================================================================
// cTDMusicArray::m_free_all
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
void cTDMusicArray::m_free_all(void)
{
   TD_DEBUG(;)

   for (int i = 0; i < __TD_SDL_MAX_MUSICS; i++)
      m_aMusics[i].free();
}

//==============================================================================
// cTDMusicArray::m_load
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
int cTDMusicArray::m_load(const char *A_strFileName, int A_iMusic /*= TD_RETIDX_ERR*/)
{
   int iFirstFree;

   TD_DEBUG( cout << "-> '" << A_strFileName << " '\n"; )

   if (!A_strFileName)
      return TD_RETIDX_ERR;

   if ((A_iMusic < 0) || (A_iMusic >= __TD_SDL_MAX_MUSICS))
      A_iMusic = TD_RETIDX_ERR;

   if (A_iMusic == TD_RETIDX_ERR)
   {
      for (iFirstFree = 0; iFirstFree < __TD_SDL_MAX_MUSICS; iFirstFree++)
         if (m_aMusics[iFirstFree].data())
            break;
   }
   else
   {
      if (A_iMusic < 0)
         return TD_RETIDX_ERR;
      iFirstFree = A_iMusic;
   }

   if (iFirstFree >= __TD_SDL_MAX_MUSICS) // check if no more free sounds
      return TD_RETIDX_ERR;

   if (m_aMusics[iFirstFree].data()) // check if free (possile only when A_iMusic != TD_RETIDX_ERR)
      return TD_RETIDX_ERR;

   TD_DEBUG( cout << " ... loading ... " << A_strFileName << " ... "; )

   // -->

   if (!m_aMusics[iFirstFree].load(A_strFileName))
   {
      // load error
      TD_DEBUG( cout << "failed\n"; )
      return TD_RETIDX_ERR;
   }

   TD_DEBUG( cout << "ok, idx: " << iFirstFree << endl; )

   return iFirstFree;
}

//==============================================================================
// cTDMusicArray::m_free
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
char cTDMusicArray::m_free(int A_iMusic)
{
   if ((A_iMusic < 0) || (A_iMusic >= __TD_SDL_MAX_MUSICS))
      return FALSE;

   m_aMusics[A_iMusic].free();

   return TRUE;
}

//==============================================================================
// cTDMusicArray::operator[]
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
sTDMusic *cTDMusicArray::operator[](int A_iMusic) const
{
   if ((A_iMusic < 0) || (A_iMusic >= __TD_SDL_MAX_MUSICS))
      return NULL;

   return (sTDMusic *)&m_aMusics[A_iMusic];
}


//==============================================================================
// class cTDSoundMixer
//==============================================================================

//==============================================================================
// cTDSoundMixer::cTDSoundMixer
//
// Rafal Zabdyr, 21.03.2006
//==============================================================================
cTDSoundMixer::cTDSoundMixer()
: m_bAudioAvailable(FALSE)
{
   TD_DEBUG( cout << "SoundMixer : initialization ..."; )
   m_bInit = (SDL_InitSubSystem(SDL_INIT_AUDIO) >= 0);
   if (m_bInit)
      { TD_DEBUG( cout << "ok\n"; ) }
   else
      cout << "error (" << SDL_GetError() << ")\n";
}

//==============================================================================
// cTDSoundMixer::~cTDSoundMixer
//
// Rafal Zabdyr, 21.03.2006
//==============================================================================
cTDSoundMixer::~cTDSoundMixer()
{
   TD_DEBUG(;)
   close();
}

//==============================================================================
// cTDSoundMixer::open
//
// Rafal Zabdyr, 7.09.2005, 21.03.2006 (c++)
//==============================================================================
char cTDSoundMixer::open()
{
   if (!m_bInit)
      return FALSE;

   TD_DEBUG( cout << "SoundMixer : openaudio ..."; )

   if (Mix_OpenAudio(__TD_SDL_SOUND_FREQ, AUDIO_S16SYS, __TD_SDL_CHANNELS, __TD_SDL_AUDIO_BUFFERS))
   {
      cout << "failed (" << Mix_GetError() << ")\n";
      return FALSE;
   }
   TD_DEBUG( cout << "ok\n"; )

   m_bAudioAvailable = TRUE;

   return TRUE;
}

//==============================================================================
// cTDSoundMixer::close
//
// Rafal Zabdyr, 7.09.2005, 23.03.2006 (c++)
//==============================================================================
void cTDSoundMixer::close()
{
   TD_DEBUG(;)

   if (!m_bInit) // no init
      return;

   if (!m_bAudioAvailable) // no audio
      return;

   Mix_HaltChannel(-1); // stop all sound effects
   Mix_HaltMusic(); // stop music

   Mix_CloseAudio();
   
   m_free_all();
   s_free_all();

   m_bAudioAvailable = FALSE;
}

//==============================================================================
// cTDSoundMixer::play_sample
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
int cTDSoundMixer::play_sample(int A_iChannel, unsigned int A_iSample, int A_iLoops, unsigned int A_nPercentVolume)
{
   if (!m_bAudioAvailable) // no audio
      return -1;

   if (A_iSample >= __TD_SDL_MAX_SAMPLES)
      return -1;

   if (A_nPercentVolume > 100)
      A_nPercentVolume = 100;

   int iChannel = Mix_PlayChannel(-1, m_aSamples[A_iSample].data(), A_iLoops);
   Mix_Volume(iChannel, MIX_MAX_VOLUME * A_nPercentVolume / 100);

   return iChannel;
}

//==============================================================================
// cTDSoundMixer::stop_sample
//
// Rafal Zabdyr, 10.09.2006
//==============================================================================
void cTDSoundMixer::stop_sample(int A_iChannel)
{
   Mix_HaltChannel(A_iChannel);
}

//==============================================================================
// cTDSoundMixer::play_music
//
// Rafal Zabdyr, 2.09.2006
//==============================================================================
void cTDSoundMixer::play_music(unsigned int A_iMusic, int A_iLoops, unsigned int A_nPercentVolume)
{
   if (!m_bAudioAvailable) // no audio
      return;

   if (A_iMusic >= __TD_SDL_MAX_MUSICS)
      return;

   if (A_nPercentVolume > 100)
      A_nPercentVolume = 100;

   Mix_VolumeMusic(MIX_MAX_VOLUME * A_nPercentVolume / 100);
   Mix_PlayMusic(m_aMusics[A_iMusic].data(), A_iLoops);
}


