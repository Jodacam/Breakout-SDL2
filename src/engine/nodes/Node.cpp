#include "Node.h"


void GameEngine::Node::Update(float dt) {


    if (enable) {
        //Calls children Update.
        for (auto&& i : children)
        {
            i->Update(dt);
        }
    }

    //Move all the children
    children.insert(children.end(),std::make_move_iterator(toPush.begin()),std::make_move_iterator(toPush.end()));
    toPush.clear();
}


void GameEngine::Node::Render(GameEngine::Renderer* renderer) {
    if (!enable) return;
    //Calls children render.
    for (auto&& i : children) {
        i->Render(renderer);
    }
}