#include "AssetsManager.h"
GameEngine::AssetManager *GameEngine::AssetManager::instance;
GameEngine::AssetManager *GameEngine::AssetManager::getInstance()
{

    if (!GameEngine::AssetManager::instance)
    {
        GameEngine::AssetManager::instance = new GameEngine::AssetManager();
    }

    return GameEngine::AssetManager::instance;
}

/**
 * \brief Adds a new Texture and loads it on the GPU.
 */
GameEngine::Image *GameEngine::AssetManager::AddTexture(const char *path, std::string key)
{

    //Load a Surface and copy pixels
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *text = SDL_CreateTextureFromSurface(actualRenderer->GetInternalRender(), surface);

    Image* image =new Image();
    image->texture=text;
    
    SDL_QueryTexture(text,NULL,NULL,&image->width,&image->height);

    if (text)
    {
        textures.insert(std::make_pair(key, image));
    }

    SDL_FreeSurface(surface);

    return image;
}
bool GameEngine::AssetManager::GetSprite(GameEngine::Sprite *outSprite, std::string imageKey)
{
    Image *image = getTexture(imageKey);

    if (image == NULL)
        return false;
    outSprite->x = 0;
    outSprite->y = 0;
    outSprite->width = image->width;
    outSprite->height = image->height;
    outSprite->source = image;
    return true;
}

bool GameEngine::AssetManager::GetSprite(GameEngine::Sprite *outSprite, std::string imageKey, int width, int height)
{
    if(GetSprite(outSprite, imageKey)) {
        outSprite->width = width;
        outSprite->height = height;
        return true;
    }

    return false;
    
}