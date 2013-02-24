/*

    TDolphin projects

    (c) TDolphin 2005-2012

    td_sdl_soundmixer.h

    SDL sound support (sound mixer) for all TDolphin's projects
    (C++ programs) using SDL

    created: 7.09.2005
       last: 12.02.2012

*/

#ifndef __TD_SDL_SOUNDMIXER_H
#define __TD_SDL_SOUNDMIXER_H



#include "td_singleton_template.h"


// defines

#define __TD_SDL_MAX_SAMPLES     16
#define __TD_SDL_MAX_MUSICS      2
#define __TD_SDL_CHANNELS        2 // 2 - stereo, 3 = 2+1 .. etc
#define __TD_SDL_SOUND_FREQ      22050
#define __TD_SDL_AUDIO_BUFFERS   4096


// types/enums

// structs/classes

//==============================================================================
// struct sTDSample
//==============================================================================
struct sTDSample
{
   sTDSample();
   ~sTDSample();

protected:
   void reset();

public:
   void free();
   char load(const char *A_strFileName);
   
   // data interface
   Mix_Chunk *&data() { return m_pData; }

protected:
   Mix_Chunk *m_pData;
};

//==============================================================================
// struct sTDMusic
//==============================================================================
struct sTDMusic
{
   sTDMusic();
   ~sTDMusic();

protected:
   void reset();

public:
   void free();
   char load(const char *A_strFileName);

   // data interface
   Mix_Music *&data() { return m_pData; }

protected:
   Mix_Music *m_pData;
};

//==============================================================================
// class cTDSampleArray
//==============================================================================
class cTDSampleArray
{
public:
   cTDSampleArray();
   cTDSampleArray(const cTDSampleArray&);
   ~cTDSampleArray();

private:
   void reset();

public:
   void s_free_all(); // free all samples
   int s_load(const char *A_strFileName, int A_iSample = TD_RETIDX_ERR);
   char s_free(int A_iSample);

   sTDSample *operator[](int A_iSample) const;

// members
protected:
   sTDSample m_aSamples[__TD_SDL_MAX_SAMPLES]; // array of samples/sounds
};

//==============================================================================
// class cTDMusicArray
//==============================================================================
class cTDMusicArray
{
public:
   cTDMusicArray();
   cTDMusicArray(const cTDMusicArray&);
   ~cTDMusicArray();

private:
   void reset();

public:
   void m_free_all(); // free all musics
   int m_load(const char *A_strFileName, int A_iMusics = TD_RETIDX_ERR);
   char m_free(int A_iMusic);

   sTDMusic *operator[](int A_iMusic) const;

// members
protected:
   sTDMusic m_aMusics[__TD_SDL_MAX_MUSICS]; // array of musics
};

//==============================================================================
// class cTDSoundMixer
//==============================================================================
class cTDSoundMixer : public cTDSampleArray, public cTDMusicArray
{
   friend class TDSingleton<cTDSoundMixer>;

   cTDSoundMixer();
   cTDSoundMixer(const cTDSampleArray&);

public:
   ~cTDSoundMixer();

   char open();
   void close();

   int play_sample(int A_iChannel, unsigned int A_iSample, int A_iLoops, unsigned int A_nPercentVolume);
   void stop_sample(int A_iChannel);
   void play_music(unsigned int A_iMusic, int A_iLoops, unsigned int A_nPercentVolume);

// members
protected:
   char m_bInit, // initiated SDL_AUDIO
        m_bAudioAvailable; // audio opened
};

typedef TDSingleton<cTDSoundMixer> cTDMixer;

//==============================================================================
// class cTDMixerScope
//==============================================================================
class cTDMixerScope
{
public:
   cTDMixerScope() {}
   ~cTDMixerScope() { cTDMixer::instance().m_free_all(); cTDMixer::instance().s_free_all(); }
};


#endif // __TD_SDL_SOUNDMIXER_H

