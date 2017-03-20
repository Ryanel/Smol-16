#include <cstring>
#include <string>
#include <color.hpp>
#include <input.hpp>
#include <smol16.hpp>
#include <SDL.h>
Input * Input::m_instance;
std::string Input::input_text;
bool Input::lastchar_submit = false;
Input * Input::instance()
{
   if(!m_instance) {m_instance = new Input();}
   return m_instance;
}

Input::Input() {
    getGlobalNamespace(CSystem::instance()->L)
   .beginNamespace("io")
       .addFunction("btn", &Input::LuaGetBtnDown)
       .addFunction("btnp", &Input::LuaGetBtnPress)
       .addFunction("mouse_x", &Input::LuaGetMouseX)
       .addFunction("mouse_y", &Input::LuaGetMouseY)
       .addFunction("text_start", &Input::LuaEnableTextInput)
       .addFunction("text_end", &Input::LuaDisableTextInput)
       .addFunction("text_get", &Input::LuaGetTextInput)
       .addFunction("text_flush", &Input::LuaFlushTextInput)
       .addFunction("text_flushf", &Input::LuaFlushFullInput)
       .addFunction("text_submit", &Input::LuaTextLastConfirm)
   .endNamespace();

}

// Is the button down NOW?
bool Input::GetButtonDown(int code) {
    return buttonStates[code];

}
// Is the button JUST NOW down. (in buttonStates but not buttonStatesLast)
bool Input::GetButtonPress(int code) {
    if(buttonStates[code]) {
        if(!buttonStatesLast[code]) {
            return true;
        }
    }
    return false;

}
bool Input::SetButton(int code, bool value) {
    return buttonStates[code] = value;
}

// Cycle from buttonStates -> buttonStatesLast.
void Input::Update() {
    for(int i = 0; i < NUM_BUTTONS; i++) {
        buttonStatesLast[i] = buttonStates[i];
    }
}

bool Input::LuaGetBtnDown(int code) {
    return instance()->GetButtonDown(code);
}
bool Input::LuaGetBtnPress(int code) {
    return instance()->GetButtonPress(code);
}

int Input::LuaGetMouseX() {
    return instance()->mouseX / CPPU::instance()->display_scale;
}

int Input::LuaGetMouseY() {
    return instance()->mouseY / CPPU::instance()->display_scale;
}

bool Input::LuaGetMouseBtn1() {
    return false;
}

bool Input::LuaGetMouseBtn2() {
    return false;
}

void Input::LuaEnableTextInput() {
    SDL_StartTextInput();
}


void Input::LuaDisableTextInput() {
    SDL_StopTextInput();
}


std::string Input::LuaFlushTextInput() {
    std::string ret = input_text;
    input_text = "";
    lastchar_submit = false;
    return ret;
}

std::string Input::LuaGetTextInput() {
    std::string ret = input_text;
    return ret;
}

std::string Input::LuaFlushFullInput() {
    if(lastchar_submit == true) {
        return LuaFlushTextInput();
    }
    return "";
}

bool Input::LuaTextLastConfirm() {
    return lastchar_submit;
}
