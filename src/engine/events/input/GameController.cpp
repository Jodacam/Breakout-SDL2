#include "GameController.h"
#include "../../consts/logger.h"
#include <string>
#include <sstream>
#ifndef PSP

void LightCanvas::GameController::UpdateControllerState()
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
void LightCanvas::GameController::UpdateControllerState()
{
    // Digital buttons.
    // Axis. Because the PSP only has one Axis control (the left stick) the readding only work for GameAxisType::LEFT_X and GameAxisType::LEFT_Y
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(1);
    int result = sceCtrlReadBufferPositive(&axisData, 1);
    axisValues[0] = 0.0f;
    axisValues[1] = 0.0f;

    std::stringstream s;


    if ((axisData.Lx-128) > AXIS_DEADZONE || (axisData.Lx-128) < -AXIS_DEADZONE)
        axisValues[0] = (float)((axisData.Lx-128) - AXIS_DEADZONE) * axisConverterRate;

    s << "El axis x es: " << axisData.Lx << "Con valor normalizado de "<<axisValues[0]<< " Y el axis y es: " << axisData.Ly;

    if (axisData.Buttons & PSP_CTRL_TRIANGLE)
    {
        printLog(s.str());
    }

    // Buttons
    SceCtrlLatch data;
    result = sceCtrlReadLatch(&data);

    for (unsigned int i = 0; i < MAX_BUTTON_GAMEPAD; i++)
    {
        buttons[i].isPressed = data.uiPress & PSP_BUTTONS[i];
        buttons[i].wasPressed = data.uiBreak & PSP_BUTTONS[i];
        buttons[i].released = data.uiRelease & PSP_BUTTONS[i];
        buttons[i].pressed = data.uiMake & PSP_BUTTONS[i];
    }
}
#endif

LightCanvas::GameButton LightCanvas::GameController::GetButton(GameButtonType button)
{
    return buttons[static_cast<unsigned int>(button)];
}
LightCanvas::GameButton LightCanvas::GameController::GetButton(unsigned int button)
{
    return buttons[button];
}

float LightCanvas::GameController::GetAxisValue(GameAxisType axis)
{

    return axisValues[static_cast<unsigned int>(axis)];
}

float LightCanvas::GameController::GetAxisValue(unsigned int axis)
{

    return axisValues[axis];
}