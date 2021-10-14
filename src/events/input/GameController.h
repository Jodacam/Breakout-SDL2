#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_
#define MAX_BUTTON_GAMEPAD 15
#define MAX_AXIS_GAMEPAD 4
#define AXIS_DEADZONE 2500
#define AXIS_UNIT_TRANSFORM 1.0f / (32767 - AXIS_DEADZONE)
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
    /**
     * Button for the controller. It uses the XBOX Gamecontroller Scheme. So A is the bottom button, X is the left button, Y is the top one and B is the right.
     * DPAD are detected as buttons, but also can be detected as AXIS movement
     */
    enum class GameButtonType : unsigned int
    {
        // INVALID = -1,
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
    /**
     * Like the buttons the axis use the XBOX scheme.
     */
    enum class GameAxisType : unsigned int
    {
        LEFT_X = 0,
        LEFT_Y = 1,
        RIGHT_X = 2,
        RIGHT_Y = 3,
        LEFT_TRIGGER = 4,
        RIGHT_TRIGGER = 5
    };
    class GameController
    {

    private:
        SDL_GameController *controller;
        GameButton buttons[MAX_BUTTON_GAMEPAD];
        const float axisConverterRate = AXIS_UNIT_TRANSFORM;
        float axisValues[MAX_AXIS_GAMEPAD] = {0.0f, 0.0f, 0.0f, 0.0f};

    public:
        GameController(SDL_GameController *controller)
        {
            this->controller = controller;
        }
        SDL_GameController *GetNativeController() { return controller; }
        /**
         * Updates the game controller state. It fills the GameButton structs.
         * The GameButtonType should have the same index as the SDL_GameControllerButton enum. So it uses the int result to get the array.
         * Also, Keyboard keys can be bind to GameButtonType so the two work.
         */
        void UpdateControllerState();
        /**
         * Retrieves a GameButton state for the "actual" frame. If it is called before UpdateContollerState it will have the same values as the previos frame.
         *
         */
        GameButton GetButton(GameButtonType b);
        /**
         *Retrieves a Axis value for the "actual" frame. If it is called before UpdateContollerState it will have the same values as the previos frame.
         *The range of the value is normaliced and it is between -1 and 1. (The triggers are a special case where they can not be less than 0)
         *If the GameController is configured to use the DPAD as an Axis and the DPAD is trigger, the value would be 1 or -1 respectively
         */
        float GetAxisValue(GameAxisType axis);
    };
}
#endif