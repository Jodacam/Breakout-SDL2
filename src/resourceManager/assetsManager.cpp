#include "assetsManager.h"
GameEngine::AssetManager* GameEngine::AssetManager::instance;
GameEngine::AssetManager* GameEngine::AssetManager::getInstance() {

    if(!GameEngine::AssetManager::instance) { 
        GameEngine::AssetManager::instance = new GameEngine::AssetManager();
    }

    return GameEngine::AssetManager::instance;

}

/**
 * \brief Adds a new Texture and loads it on the GPU.
 */
SDL_Texture* GameEngine::AssetManager::AddTexture(const char* path,const char* key) {

    //Load a Surface and copy pixels
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *text = SDL_CreateTextureFromSurface(actualRenderer->getInternalRender(), surface);
    

    if(text) {
        textures.insert(std::make_pair(key,text));
    }

    SDL_FreeSurface(surface);

    return text;
}