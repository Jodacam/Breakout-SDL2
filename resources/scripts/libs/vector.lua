-- Vector Meta Table Definition
Vector = {}
Light_Canvas.Vector = {}

function Light_Canvas.Vector.New (x,y)
    local v = {x=x,y=y}
    setmetatable(v,Vector)
    if(getmetatable(v) ~= "Vector") then error("Not a metatable") end
    return v
end

function Light_Canvas.Vector.Add (v1,v2)
    if(getmetatable(v2) ~= "Vector") then return Light_Canvas.Vector.New(v1.x,v1.y) end
    local v = {x=v1.x+v2.x,y=v1.y+v2.y}
    setmetatable(v,Vector)
    return v
end

function Light_Canvas.Vector.Sub (v1,v2)
    local v = {x=v1.x-v2.x,y=v1.y-v2.y}
    setmetatable(v,Vector)
    return v
end

function Light_Canvas.Vector.Equal (v1,v2)
    if(getmetatable(v2) ~= "Vector") then return false end
    return v1.x == v2.x and v1.y == v2.y;
end

function Light_Canvas.Vector.Multiply (v1,n)

    local number = tonumber(n)

    if(number == 'fail') then return v1 end

    return Light_Canvas.Vector.New(v1.x*number,v1.y*number)

end

function Light_Canvas.Vector.Distance(v1,v2)
    if(getmetatable(v2) ~= "Vector") then return 0 end
    if(getmetatable(v1) ~= "Vector") then return 0 end
    local v = v2-v1;
    return v:Module()

end

function Light_Canvas.Vector.Module(v1)
    return math.sqrt(v1.x*v1.x + v1.y*v1.y)
end

Light_Canvas.Vector.mt = "Vector"

Vector.__add = Light_Canvas.Vector.Add
Vector.__sub = Light_Canvas.Vector.Sub
Vector.__eq  = Light_Canvas.Vector.Equal
Vector.__mul = Light_Canvas.Vector.Multiply
Vector.__metatable  = Light_Canvas.Vector.mt
Vector.__index = Light_Canvas.Vector
Vector.__tostring = function (v) return "Vector with -> X: ".. v.x .. " Y: " .. v.y .. "" end