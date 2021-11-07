#ifndef _SCENE_H_
#define _SCENE_H_
#include "../../render/SDLRender.h"
#include <string>
namespace GameEngine
{
    class Scene
    {
    private:
        /* data */
        std::string name = "Scene";
    public:
        virtual void Render(GameEngine::Renderer *renderer) = 0;
        virtual void Update(float dt) = 0;
        virtual void OnAdd() = 0;
        virtual void OnStart() = 0;
    };

}
#endif // _SCENE_H_