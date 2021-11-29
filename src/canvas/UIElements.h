#ifndef GAME_ENGINE_UIELEMENT_H
#define GAME_ENGINE_UIELEMENT_H
#include <memory>
#include "../math/Vector.h"
#include "../render/SDLRender.h"
namespace GameEngine
{
#pragma region UIElement

    /**
     * Abstract class use to work with the Canvas element. An UI element can be used outside the canvas, but it is recommended to
     * use it with it
    */
    class UIElement
    {
    protected:
        /* data */
        bool isDirty = true;
        Vector position;
        Vector size;

    public:
        bool visible;
        UIElement();
        virtual void Render(GameEngine::Renderer *renderer) = 0;
        virtual void Update(float dt) = 0;
        /**
         * @return The state of the UIElement. When is dirty a re-render will be trigger on the canvas element.
        */
        inline bool GetIsDirty() const { return isDirty; }
    };
#pragma endregion

#pragma region UIImage

    /**
     * Image element. It cointains a pointer to one image and the size/position of the image.
    */
    class UIImage : public UIElement
    {

    private:
        std::shared_ptr<Image> image;

    public:
        void Update(float dt);
        void Render(GameEngine::Renderer *renderer);
    };

#pragma endregion

}

#endif