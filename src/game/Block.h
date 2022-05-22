#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "math/Vector.h"
//#include "../engine/math/Vector.h"
#include <SDL2/SDL.h>
#include "../engine/render/SDLRender.h"
#include <string>
namespace GameEngine
{
    class Block
    {

    private:
        Vector position;
        Vector size;
        Image* sprite;
    public:
        Block(Vector position, std::string sprite);
        void Render(Renderer* renderer);
        void OnDestroy();
        Vector GetPosition() { return position; }
        Vector GetSize() { return size; }
        Vector SetSize(Vector s) { size = s; return size; }
    };

}
#endif // _BLOCK_H_