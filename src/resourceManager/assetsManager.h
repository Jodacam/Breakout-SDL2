#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_
#include <SDL.h>
#include <unordered_map>
namespace GameEngine {

    class AssetManager {
        private:
            static AssetManager instance;
            std::unordered_map<const char* ,SDL_Texture*> textures;
            AssetManager() {
                textures =  std::unordered_map<const char*,SDL_Texture*>();
            }
        public:
            static AssetManager getInstance();
            inline SDL_Texture* getTexture(const char* key) {
                return textures[key];
            }
            SDL_Texture* AddTexture(const char* path,const char* key);
            bool RemoveTexture();


    };


}

#endif