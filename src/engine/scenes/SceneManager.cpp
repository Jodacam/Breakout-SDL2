#include "SceneManager.h"

using namespace LightCanvas;

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager() {
    
}

SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(Scene* scene) {
    _scenes.push_back(scene);
    scene->OnAdd();
}
Scene* SceneManager::ChangeScene(int index) {
    this->_actualScene = _scenes[index];
    _actualScene->OnStart();
    return _actualScene;
}