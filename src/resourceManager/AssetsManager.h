#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "../render/Graphics.h"
#include "../render/SDLRender.h"
#include "../audio/Audio.h"
namespace GameEngine
{

    class AssetManager
    {
    private:
        static AssetManager *instance;
        std::unordered_map<std::string, Image *> textures;
        std::unordered_map<std::string, Song> songs;
        std::unordered_map<std::string, SoundEffect> soundEffects;
        Renderer *actualRenderer;
        AssetManager()
        {
            textures = std::unordered_map<std::string, Image *>();
        }

    public:
        static AssetManager *GetInstance();
        static AssetManager *InitInstance(Renderer *renderer)
        {
            AssetManager::GetInstance()->Init(renderer);

            return AssetManager::GetInstance();
        }
        inline Image *getTexture(std::string key)
        {
            return textures[key];
        }
        inline Song GetSong(std::string key)
        {
            return songs[key];
        }
        inline SoundEffect GetSoundEffect(std::string key)
        {
            return soundEffects[key];
        }
        //Change to shared_pointer;
        Image *AddTexture(const char *path, std::string key);
        Song AddSong(const char *path, std::string key);
        SoundEffect AddSoundEffect(const char *path, std::string key);
        inline bool Init(Renderer *renderer, bool clearTextures = false)
        {
            actualRenderer = renderer;
            if (clearTextures)
            {
                //TODO clear all Texture data from the texture map.
                textures.clear();
            }
            return true;
        }
        bool GetSprite(Sprite *outSprite, std::string imageKey);
        bool GetSprite(Sprite *outSprite, std::string imageKey, int width, int height);
        bool RemoveTexture(const char *key);
        bool ClearData();
    };

}

#endif