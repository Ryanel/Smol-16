#include <cstring>
#include <color.h>
#include <smol/input.h>
#include <smol/smol16.h>

Input * Input::m_instance;

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
