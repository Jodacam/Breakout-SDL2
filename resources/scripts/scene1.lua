time = 0;
function Update(dt)
    time = time + dt;
    local pos = sprite:GetPosition();
    pos.x = pos.x + Light_Canvas.Input.GetAxis(Light_Canvas.Input.Axis.LEFT_X) * dt * 100;
    sprite:SetPosition(pos)

    local input = Light_Canvas.Input.GetButton(Light_Canvas.Input.Buttons.A)
    print("Valor: ",input.isPressed)

end

scene = Light_Canvas.Scene.GetActualScene();
print(scene);

Light_Canvas.RegisterUpdate(scene,Update)
--LC_RegisterUpdate(scene, Update);

--  LC_CreateNode("node", "First Lua Node!")
node =  LC_Node.New("First Lua Node!");
sprite =  LC_SpriteNode.New("Sprite Lua Node!","player");

scene:AddNode(sprite);
scene:AddNode(node);


Light_Canvas.Input.GetButton(Light_Canvas.Input.Buttons.A);
Light_Canvas.Input.GetButton(Light_Canvas.Input.Buttons.START);

