#include "AssetsManager.h"
#include "../consts/logger.h"
LightCanvas::AssetManager *LightCanvas::AssetManager::instance;
LightCanvas::AssetManager *LightCanvas::AssetManager::GetInstance()
{

    if (!LightCanvas::AssetManager::instance)
    {
        LightCanvas::AssetManager::instance = new LightCanvas::AssetManager();
    }

    return LightCanvas::AssetManager::instance;
}

/**
 * \brief Adds a new Texture and loads it on the GPU.
 */
LightCanvas::Image *LightCanvas::AssetManager::AddTexture(const char *path, std::string key)
{

    //Load a Surface and copy pixels
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *text = SDL_CreateTextureFromSurface(actualRenderer->GetInternalRender(), surface);

    Image *image = new Image();
    image->texture = text;

    SDL_QueryTexture(text, NULL, NULL, &image->width, &image->height);

    if (text)
    {
        textures.insert(std::make_pair(key, image));
    }

    SDL_FreeSurface(surface);

    return image;
}
LightCanvas::Sprite LightCanvas::AssetManager::GetSprite(std::string imageKey)
{
    Image *image = getTexture(imageKey);

    if (image == NULL)
        throw "Error";
    Sprite outSprite;

    outSprite.x = 0;
    outSprite.y = 0;
    outSprite.width = image->width;
    outSprite.height = image->height;
    outSprite.source = image;
    return outSprite;
}

LightCanvas::Sprite LightCanvas::AssetManager::GetSprite(std::string imageKey, int width, int height)
{

    auto outSprite = GetSprite(imageKey);
    outSprite.width = width;
    outSprite.height = height;
    return outSprite;
}

std::shared_ptr<LightCanvas::Song> LightCanvas::AssetManager::AddSong(const char *path, std::string key)
{
    auto song = Mix_LoadMUS(path);

    if (song == NULL)
    {
        auto err = Mix_GetError();
        SDL_Log(err);

        printLog(err, LOG_TO_FILE);
    }



    if (song)
    {
        
        songs.insert(std::make_pair(key, std::make_shared<Song>(song)));
    }

    return songs[key];
}

std::shared_ptr<LightCanvas::SoundEffect> LightCanvas::AssetManager::AddSoundEffect(const char *path, std::string key)
{
    auto song = Mix_LoadWAV(path);

    if (song == NULL)
    {
        auto err = Mix_GetError();
        SDL_Log(err);

        printLog(err, LOG_TO_FILE);
    }

    if (song)
    {
        soundEffects.insert(std::make_pair(key, std::make_shared<SoundEffect>(song)));
    }

    return soundEffects[key];
}

bool LightCanvas::AssetManager::ClearData()
{
    return true;
}