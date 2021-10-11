#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_
#define MAX_BUTTON_GAMEPAD 15
#define MAX_AXIS_GAMEPAD 4
#define AXIS_DEADZONE 2500
#define AXIS_UNIT_TRANSFORM 1.0f/(32767-AXIS_DEADZONE)
#include <SDL_gamecontroller.h>
#include <iostream>
namespace GameEngine
{
    struct GameButton
    {
        bool isPressed = false;
        bool pressed = false;
        bool released = false;
        bool wasPressed = false;
    };

    enum class GameButtonType : unsigned int
    {
        //INVALID = -1,
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        BACK = 4,
        GUIDE = 5,
        START = 6,
        LEFTSTICK = 7,
        RIGHTSTICK = 8,
        LEFTSHOULDER = 9,
        RIGHTSHOULDER = 10,
        DPAD_UP = 11,
        DPAD_DOWN = 12,
        DPAD_LEFT = 13,
        DPAD_RIGHT = 14

    };

    enum class GameAxisType : unsigned int
    {
        LEFT_X = 0,
        LEFT_Y = 1,
        RIGHT_X = 2,
        RIGHT_Y = 3,
    };
    class GameController
    {

    private:
        SDL_GameController *controller;
        GameButton buttons[MAX_BUTTON_GAMEPAD];
        const float axisConverterRate = AXIS_UNIT_TRANSFORM;
        float axisValues[MAX_AXIS_GAMEPAD] = {0.0f,0.0f,0.0f,0.0f};
    public:
        GameController(SDL_GameController *controller)
        {
            this->controller = controller;
        }
        SDL_GameController *GetNativeController() { return controller; }
        void UpdateControllerState();
        GameButton GetButton(GameButtonType b);
        float GetAxisValue(GameAxisType axis);
    };
}
#endif