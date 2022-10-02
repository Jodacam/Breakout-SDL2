#include "SpriteNode.h"

void LightCanvas::SpriteNode::Update(float dt) {
    Node::Update(dt);
}

void LightCanvas::SpriteNode::Render(LightCanvas::Renderer* renderer) {
    Node::Render(renderer);
    renderer->DrawSprite(sprite, GetPosition(), Vector::LinearMultiply(GetScale(), Vector(sprite.width, sprite.height)));
}

bool LightCanvas::SpriteNode::SetSprite(const std::string& sprite) {
    this->sprite = LightCanvas::AssetManager::GetInstance()->GetSprite(sprite);
    return true;
}


int LightCanvas::Lua_SpriteNode::CreateOne(LightCanvas::ScriptManager* m) {
    auto L = m->GetInternalVM();

    //Get The Node name.
    const char* name = lua_tostring(L, 2);
    LightCanvas::Node* parent = nullptr;

    if (lua_islightuserdata(L, 3)) {
        parent = (LightCanvas::Node*)lua_touserdata(L, 3);
    }

    //Creates the pointer.
    void* p = lua_newuserdata(L, sizeof(LightCanvas::Lua_SpriteNode));
    SpriteNode* native_node = new LightCanvas::SpriteNode(name);
    new (p) LightCanvas::Lua_SpriteNode(native_node);
    //Cast to the Node Class.
    return 1;
}

void LightCanvas::Lua_SpriteNode::CreateLuaMetaInfo(LightCanvas::ScriptManager* m) {

    auto L = m->GetInternalVM();

    lua_getglobal(L, "Light_Canvas");
    int LC = lua_gettop(L);
    lua_newtable(L);
    int index = lua_gettop(L);
    lua_pushvalue(L, index);
    lua_setfield(L, LC, "SpriteNode");
    //Define all functions on one place
    //Sprite Node Derives from Lua_Node.
    Lua_Node::CreateLuaMetaTableFunctions(m);
    Lua_SpriteNode::CreateLuaMetaTableFunctions(m);

    luaL_newmetatable(L, "SpriteNode");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, index);
    lua_settable(L, -3);
    lua_settop(L, LC - 1);
}

#pragma region Table Functions
int Lua_SpriteNode_New(lua_State* L) {
    const char* name = lua_tostring(L, 1);
    LightCanvas::Node* parent = nullptr;
    void* p = lua_newuserdata(L, sizeof(LightCanvas::Lua_SpriteNode));
    LightCanvas::SpriteNode* native_node = new LightCanvas::SpriteNode(name);
    //Look if a sprite is set.
    if (lua_isstring(L, 2)) {
        const char* sprite = lua_tostring(L, 2);
        native_node->SetSprite(sprite);
    }
    new (p) LightCanvas::Lua_SpriteNode(native_node);
    //Cast to the Node Class.
    luaL_setmetatable(L, "SpriteNode");
    return 1;
}
#pragma endregion

int LightCanvas::Lua_SpriteNode::CreateLuaMetaTableFunctions(LightCanvas::ScriptManager* m) {

    //Utility
    m->SetTableValue("New", Lua_SpriteNode_New);

    return 0;
}
