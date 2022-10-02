Player = {
    speed = 100
};

function Player:Update(dt)
    local sprite = self.node
    local pos = sprite:GetPosition()
    pos.x = pos.x + Light_Canvas.Input.GetAxis(Light_Canvas.Input.Axis.LEFT_X) * dt * self.speed
    sprite:SetPosition(pos)
end