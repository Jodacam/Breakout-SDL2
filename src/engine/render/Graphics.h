#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include <SDL2/SDL.h>

namespace LightCanvas
{
    /**
     * Basic struct to store a full image of SDL.
    */
    struct Image
    {
        SDL_Texture *texture;
        int width, height = 0;
    };

    /**
     * Data structure to store a Sprite. It contains the source image of the sprite an also contains the srcRect dimensions.
     * To store posible animation data, it contains the index of the image and the initial width and height of the srcRect
    */
    struct Sprite {
        const Image *source;
        int width, height = 0;
        int x, y = 0;
    };
}
#endif