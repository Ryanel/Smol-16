#pragma once
#include <cstdint>
#include <cstddef>

#define BUTTON_UP 0
#define BUTTON_RIGHT 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 3
#define BUTTON_A 4
#define BUTTON_B 5
#define BUTTON_X 6
#define BUTTON_Y 7
#define BUTTON_START 8

class Input {
private:
    static Input * m_instance;
    Input();
    bool buttonStates[8];
    bool buttonStatesLast[8];
public:
    static Input *instance();
    // Last keyboard keycode entered.
    char keyboardKeycode = 0x00;
    bool GetButtonDown(int code);
    bool GetButtonPress(int code);
    bool SetButton(int code, bool value);
    void Update();

    static bool LuaGetBtnDown(int code);
    static bool LuaGetBtnPress(int code);
};
