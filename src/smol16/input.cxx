#include <cstring>
#include <string>
#include <color.h>
#include <smol/input.h>
#include <smol/smol16.h>
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
    sys->Register("btn", &Input::LuaGetBtnDown);
    sys->Register("btnp", &Input::LuaGetBtnPress);
    sys->Register("_get_mouse_x", &Input::LuaGetMouseX);
    sys->Register("_get_mouse_y", &Input::LuaGetMouseY);
    sys->Register("text_start", &Input::LuaEnableTextInput);
    sys->Register("text_end", &Input::LuaDisableTextInput);
    sys->Register("text_get", &Input::LuaGetTextInput);
    sys->Register("text_flush", &Input::LuaFlushTextInput);
    sys->Register("text_flushf", &Input::LuaFlushFullInput);
    sys->Register("text_submit", &Input::LuaTextLastConfirm);
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
    return instance()->mouseX / Display::scale;
}

int Input::LuaGetMouseY() {
    return instance()->mouseY / Display::scale;
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
