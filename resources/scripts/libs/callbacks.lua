-- This files stores the lua callback information
-- 

--- Registers a update function. It needs the light userdata pointer and a lua function to be called.
---@param object userdata
---@param func function
function Light_Canvas.RegisterUpdate(object,func) 
    --Obtain the pointer to the object.
    local p = object:GetNative();
    --If get native returns null, do not register anything
    if(p ~=nil) then Light_Canvas.__update_functions[p] = func end
end

---Calls the update function of a light userdata pointer
---@param object lightuserdata
---@param dt number
function Light_Canvas.CallUpdate(object,dt)
    Light_Canvas.__update_functions[object](dt)
end