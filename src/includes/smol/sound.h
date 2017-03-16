#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <color.h>
#include <config.h>

class Sound {
private:
    static Sound * m_instance;
    Sound();
public:

    static Sound *instance();

};
