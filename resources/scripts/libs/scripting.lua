Light_Canvas.Scripting = {
    ---Register a new type of Script into the lua engine. Then you can attach that script into a node and control its properties and behaviors
    ---@param path string
    ---@param class_name string
    RegisterScript = function(path, class_name)

        --Load the file into the machine.
        local error = dofile(path)

        --Then load the global script class into the __scripts var to use it

        local script_class = _G[class_name]

        --Add the new function to load classes as script.
        --The script parameters should go into the function to load that.
        function script_class:New(node, params)
            local script_object = params
            setmetatable(script_object, self)
            self.__index = self
            script_object.node = node
            return script_object
        end

        Light_Canvas.Scripting.__scripts[class_name] = script_class

    end,
    __scripts = {},
    ---Adds a previously loaded script to a node and register all the callbacks
    ---@param node any
    ---@param script_name any
    ---@param params any
    AddScript = function(node, script_name, params)

        local script_class = Light_Canvas.Scripting.__scripts[script_name]
        if script_class == nil then return end

        local script_object = script_class:New(node, params)

        --TODO register all the callbacks
        if (script_object.Update) then Light_Canvas.RegisterUpdate(node, script_object) end

    end
}
