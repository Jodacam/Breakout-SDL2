#include "SpriteNode.h"

void GameEngine::SpriteNode::Update(float dt) {
    Node::Update(dt);
}

void GameEngine::SpriteNode::Render(GameEngine::Renderer* renderer) {
    Node::Render(renderer);
    renderer->DrawSprite(sprite, GetPosition(), Vector::LinearMultiply(GetScale(), Vector(sprite.width, sprite.height)));
}

bool GameEngine::SpriteNode::SetSprite(const std::string& sprite) {
    this->sprite = GameEngine::AssetManager::GetInstance()->GetSprite(sprite);
    return true;
}


int GameEngine::Lua_SpriteNode::CreateOne(GameEngine::ScriptManager* m) {
    auto L = m->GetInternalVM();

    //Get The Node name.
    const char* name = lua_tostring(L, 2);
    GameEngine::Node* parent = nullptr;

    if (lua_islightuserdata(L, 3)) {
        parent = (GameEngine::Node*)lua_touserdata(L, 3);
    }

    //Creates the pointer.
    void* p = lua_newuserdata(L, sizeof(GameEngine::Lua_SpriteNode));
    SpriteNode* native_node = new GameEngine::SpriteNode(name);
    new (p) GameEngine::Lua_SpriteNode(native_node);
    //Cast to the Node Class.
    return 1;
}

void GameEngine::Lua_SpriteNode::CreateLuaMetaInfo(GameEngine::ScriptManager* m) {

    auto L = m->GetInternalVM();

    lua_newtable(L);
    int index = lua_gettop(L);
    lua_pushvalue(L, index);
    lua_setglobal(L, "LC_SpriteNode");

    //Define all functions on one place
    //Sprite Node Derives from Lua_Node.
    Lua_Node::CreateLuaMetaTableFunctions(m);
    Lua_SpriteNode::CreateLuaMetaTableFunctions(m);

    luaL_newmetatable(L, "SpriteNode");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, index);
    lua_settable(L, -3);
}

#pragma region Table Functions
int Lua_SpriteNode_New(lua_State* L) {
    const char* name = lua_tostring(L, 1);
    GameEngine::Node* parent = nullptr;
    void* p = lua_newuserdata(L, sizeof(GameEngine::Lua_SpriteNode));
    GameEngine::SpriteNode* native_node = new GameEngine::SpriteNode(name);
    //Look if a sprite is set.
    if(lua_isstring(L,2)) {
        const char* sprite = lua_tostring(L,2);
        native_node->SetSprite(sprite);
    }
    new (p) GameEngine::Lua_SpriteNode(native_node);
    //Cast to the Node Class.
    luaL_setmetatable(L, "SpriteNode");
    return 1;
}
#pragma endregion

int GameEngine::Lua_SpriteNode::CreateLuaMetaTableFunctions(GameEngine::ScriptManager* m) {
    
    //Utility
    m->SetTableValue("New",Lua_SpriteNode_New);

    return 0;
}
