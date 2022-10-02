time = 0;
function Update(dt)
    time = time + dt;
    local pos = sprite:GetPosition()
    pos.x = pos.x + Light_Canvas.Input.GetAxis(Light_Canvas.Input.Axis.LEFT_X) * dt * 100
    sprite:SetPosition(pos)
end

scene = Light_Canvas.Scene.GetActualScene()
print(scene)

--Light_Canvas.RegisterUpdate(scene,Update)

Light_Canvas.AssetManager.LoadImage("resources/img/Racket.png", "player")
sprite = Light_Canvas.SpriteNode.New("Sprite Lua Node!", "player")
sprite:SetPosition(Light_Canvas.Vector.New(0, 250))
scene:AddNode(sprite);

Light_Canvas.Scripting.RegisterScript("resources/scripts/player.lua", "Player")
print("Script registrado")
Light_Canvas.Scripting.AddScript(sprite, "Player", { speed = 50 })
print("Script Añádido")
