#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <color.h>
#include <config.h>
#include <SDL2/SDL_mixer.h>
#include <spdlog/spdlog.h>

#define SND_NUM_TRACKS  6
#define SND_NUM_NOTES 64

typedef struct {
    int note; // Frequency, 0 being C-4, each +-1 being half-step (normal -> flat -> sharp -> nextnote)
    int sample_id;
    int effect_mask;
    int volume_set = 0; // 0 - 256
} note_t;
typedef struct {
    int assigned_channel = 0;
    note_t notes[SND_NUM_NOTES];
    int volume = 255;
} track_t; // Channel
typedef struct {
    track_t * tracks[SND_NUM_TRACKS];
    int playback_spd = 100;
} pattern_t;

typedef struct {
    Mix_Chunk * sample;
} sample_t;


class Sound {
private:
    static Sound * m_instance;
    static std::shared_ptr<spdlog::logger> _logger;
    Sound();
    ~Sound();
public:
    sample_t samples[256];
    static Sound *instance();
    void Init();
    void TrackerTick();
    void LoadSample(int id, std::string);
    void PlaySFX(int channel, int sample);
    int row = 0;


    static void LuaLoadSample(int id, std::string path);
    static void LuaPlaySFX(int id);
};
