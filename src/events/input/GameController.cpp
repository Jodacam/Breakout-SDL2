#include "GameController.h"

#ifndef PSP

void GameEngine::GameController::UpdateControllerState()
{
    for (unsigned int i = 0; i < MAX_BUTTON_GAMEPAD; i++)
    {
        // Check the states
        GameButton button = this->buttons[i];
        bool wasPressedLastFrame = button.pressed;
        button.pressed = (bool)SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)i);
        button.isPressed = wasPressedLastFrame && button.pressed;
        button.wasPressed = wasPressedLastFrame && !button.pressed;
        this->buttons[i] = button;
    }

    for (unsigned int i = 0; i < MAX_AXIS_GAMEPAD; i++)
    {

        axisValues[i] = 0.0f;
        auto value = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)i);
        if (value > AXIS_DEADZONE || value < -AXIS_DEADZONE)
            axisValues[i] = (float)(value - AXIS_DEADZONE) * axisConverterRate;
    }
}

#endif

#ifdef PSP
void GameEngine::GameController::UpdateControllerState()
{
    SceCtrlLatch data;
    int result = sceCtrlReadLatch(&data);
    
    for (unsigned int i = 0; i < MAX_BUTTON_GAMEPAD; i++)
    {
        buttons[i].isPressed = data.uiPress & PSP_BUTTONS[i];
        buttons[i].wasPressed = data.uiBreak & PSP_BUTTONS[i];
        buttons[i].released = data.uiRelease & PSP_BUTTONS[i];
        buttons[i].pressed = data.uiMake & PSP_BUTTONS[i];
    }
}
#endif

GameEngine::GameButton GameEngine::GameController::GetButton(GameButtonType button)
{
    return buttons[static_cast<unsigned int>(button)];
}

float GameEngine::GameController::GetAxisValue(GameAxisType axis)
{

    return axisValues[static_cast<unsigned int>(axis)];
}