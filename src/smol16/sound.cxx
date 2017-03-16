#include <smol/sound.h>
#include <smol/smol16.h>
Sound * Sound::m_instance;
std::shared_ptr<spdlog::logger> Sound::_logger;
Sound * Sound::instance()
{
   if(!m_instance) {m_instance = new Sound();}
   return m_instance;
}

Sound::Sound() {
    sys->Register("snd_loadsample", &Sound::LuaLoadSample);
    sys->Register("snd_sfx", &Sound::LuaPlaySFX);
}

Sound::~Sound() {
    Mix_CloseAudio();
}

void Sound::Init() {
    _logger = spdlog::get("sdl");
    int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    result = Mix_AllocateChannels(8);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        exit(-1);
    }
    _logger->info("Sound initialised");
}

void Sound::LoadSample(int id, std::string path) {
    samples[id].sample = Mix_LoadWAV(path.c_str());
}
void Sound::PlaySFX(int channel, int sample) {
    Mix_PlayChannel(channel,samples[sample].sample, 0);

}
void Sound::LuaLoadSample(int id, std::string path) {
    Sound::instance()->LoadSample(id, path);
}
void Sound::LuaPlaySFX(int id) {
    Sound::instance()->PlaySFX(-1, id);
}
