#include <smol/sound.h>

Sound * Sound::m_instance;

Sound * Sound::instance()
{
   if(!m_instance) {m_instance = new Sound();}
   return m_instance;
}

Sound::Sound() {
}
