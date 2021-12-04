
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <vector>
#include "Scene.h"

namespace GameEngine
{
    class SceneManager
    {
    private:
        /* data */
        std::vector<Scene*> _scenes;
        Scene* _actualScene = NULL;
    protected:
        static SceneManager* instance;
    public:
        SceneManager(/* args */);
        ~SceneManager();
        void AddScene(Scene* scene);
        static SceneManager* Instance() {
            if(instance == NULL) 
                instance = new SceneManager(); 
            return instance;
        }
        inline Scene* GetActualScene() { return _actualScene; }
        Scene* ChangeScene(Scene* scene);
        Scene* ChangeScene(int index);
    };

    
}
#endif // _SCENEMANAGER_H_