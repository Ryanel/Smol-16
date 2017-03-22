#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <string>

#define BUTTON_UP       0
#define BUTTON_RIGHT    1
#define BUTTON_DOWN     2
#define BUTTON_LEFT     3
#define BUTTON_A        4
#define BUTTON_B        5
#define BUTTON_X        6
#define BUTTON_Y        7
#define BUTTON_START    8
#define BUTTON_LMB      9
#define NUM_BUTTONS     10

class Input {
private:
    static Input *m_instance;

    Input();
    bool buttonStates[NUM_BUTTONS];
    bool buttonStatesLast[NUM_BUTTONS];
public:
    static Input *instance();

    static std::string input_text;
    static bool lastchar_submit;
    int mouseX = 0;
    int mouseY = 0;

    bool GetButtonDown(int code);
    bool GetButtonPress(int code);
    bool SetButton(int code, bool value);
    void Update();

    static bool LuaGetBtnDown(int code);
    static bool LuaGetBtnPress(int code);


    static void LuaEnableTextInput();
    static void LuaDisableTextInput();
    static int LuaGetMouseX();
    static int LuaGetMouseY();
    static bool LuaGetMouseBtn1();
    static bool LuaGetMouseBtn2();
    static std::string LuaGetTextInput();
    static std::string LuaFlushTextInput();
    static std::string LuaFlushFullInput();
    static bool LuaTextLastConfirm();
};
