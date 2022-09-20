-- Vector Meta Table Definition
Vector = {}
LC_Vector = {}

function LC_Vector.New (x,y)
    local v = {x=x,y=y}
    setmetatable(v,Vector)
    if(getmetatable(v) ~= Vector) then error("Not a metatable") end
    return v
end

function LC_Vector.Add (v1,v2)
    if(getmetatable(v2) ~= Vector) then return LC_Vector.New(v1.x,v1.y) end
    local v = {x=v1.x+v2.x,y=v1.y+v2.y}
    setmetatable(v,Vector)
    return v
end

function LC_Vector.Sub (v1,v2)
    local v = {x=v1.x-v2.x,y=v1.y-v2.y}
    setmetatable(v,Vector)
    return v
end

function LC_Vector.Equal (v1,v2)
    if(getmetatable(v2) ~= Vector) then return false end
    return v1.x == v2.x and v1.y == v2.y;
end

function LC_Vector.Multiply (v1,n) 

    local number = tonumber(n)

    if(number == 'fail') then return v1 end

    return LC_Vector.New(v1.x*number,v1.y*number)

end

function LC_Vector.Distance(v1,v2) 
    if(getmetatable(v2) ~= LC_Vector.mt) then return 0 end
    if(getmetatable(v1) ~= LC_Vector.mt) then return 0 end
    local v = v2-v1;
    return v:Module()

end

function LC_Vector.Module(v1) 

    return math.sqrt(v1.x*v1.x + v1.y*v1.y)

end

Vector.__add = LC_Vector.Add
Vector.__sub = LC_Vector.Sub
Vector.__eq  = LC_Vector.Equal
Vector.__mul = LC_Vector.Multiply

Vector.__index = LC_Vector
Vector.__tostring = function (v) return "Vector with -> X: ".. v.x .. " Y: " .. v.y .. "" end