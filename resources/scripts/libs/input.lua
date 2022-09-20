Light_Canvas.Input = {

    Buttons = {
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
    Axis = {
        LEFT_X = 0,
        LEFT_Y = 1,
        RIGHT_X = 2,
        RIGHT_Y = 3,
        LEFT_TRIGGER = 4,
        RIGHT_TRIGGER = 5
    };
    ---Gets the info of a button pressed this frame.
    ---@param button integer
    GetButton = function(button) print("Using lua def")
        return { isPressed = false; pressed = false; released = false;
            wasPressed = false; }
    end;

    ---Gets the info of an axis
    ---@param axis any
    ---@return number
    GetAxis = function(axis) print("Using lua def") return 0; end


}
