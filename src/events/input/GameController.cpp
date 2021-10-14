#include "GameController.h"
void GameEngine::GameController::UpdateControllerState() {
    for (unsigned int i = 0; i < MAX_BUTTON_GAMEPAD; i++)
    {
        //Check the states
        GameButton button = this->buttons[i];
        bool wasPressedLastFrame = button.pressed;
        button.pressed = (bool)SDL_GameControllerGetButton(controller,(SDL_GameControllerButton)i);
        button.isPressed = wasPressedLastFrame && button.pressed;
        button.wasPressed = wasPressedLastFrame && !button.pressed;
        this->buttons[i] = button;
    }

    for (unsigned int i = 0; i < MAX_AXIS_GAMEPAD; i++)
    {

        axisValues[i] = 0.0f;
        auto value = SDL_GameControllerGetAxis(controller,(SDL_GameControllerAxis)i); 
        if(value > AXIS_DEADZONE || value < -AXIS_DEADZONE)
            axisValues[i] = (float)(value-AXIS_DEADZONE)*axisConverterRate;

    }
    
    
}

GameEngine::GameButton GameEngine::GameController::GetButton(GameButtonType button) {
    return buttons[static_cast<unsigned int>(button)];
}

float GameEngine::GameController::GetAxisValue(GameAxisType axis) {

    return axisValues[static_cast<unsigned int>(axis)];

}