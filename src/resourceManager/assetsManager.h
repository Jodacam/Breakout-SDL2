#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "../render/SDLRender.h"
namespace GameEngine {

    class AssetManager {
        private:
            static AssetManager* instance;
            std::unordered_map<const char* ,SDL_Texture*> textures;
            Renderer* actualRenderer;
            AssetManager() {
                textures =  std::unordered_map<const char*,SDL_Texture*>();
            }
        public:
             
            static AssetManager* getInstance();
            static AssetManager* InitInstance(Renderer* renderer) {
                AssetManager::getInstance()->Init(renderer);

                return AssetManager::getInstance();
            }
            inline SDL_Texture* getTexture(const char* key) {
                return textures[key];
            }
            SDL_Texture* AddTexture(const char* path,const char* key);
            inline bool Init(Renderer* renderer, bool clearTextures = false) {
                actualRenderer = renderer;
                if(clearTextures) {
                    //TODO clear all Texture data from the texture map.
                    textures.clear();
                }
                return true;
            }
            bool RemoveTexture(const char* key);
            bool ClearData();


    };


}

#endif