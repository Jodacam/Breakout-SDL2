#ifndef GAME_ENGINE_CANVAS_H
#define GAME_ENGINE_CANVAS_H
#include <vector>
#include <memory>
#include "../render/SDLRender.h"
#include "UIElements.h"
namespace GameEngine
{
    /**
     * A structure used for store UI Elements.
     * Stores a static texture of the UI and if any of the internal components changes it renders them again.
    */
    class Canvas
    {
    private:
        /* data */
        std::vector<std::shared_ptr<UIElement>> elements;
        /**
         * Internal texture.
        */
        SDL_Texture *texture;

    public:
        int width, height = 0;
        /**
         * Creates a new canvas with the respectives sizes.
        */
        Canvas(int w = 0, int h = 0);
        ~Canvas();

        void Update(float dt);
        void Render(Renderer *renderer);

        /**
         * @brief Add a new UI element to the array. If the element is already in the array it will create a new one.
         * @return The newly created element into a weak_ptr so it can be changed. It used weak pointers because
        */
        template <typename Ty,typename ...Targs>
        std::shared_ptr<Ty> AddElementOfType(Targs ...args)
        {
            auto pointer = std::shared_ptr<Ty>(args...);

            elements.push_back(pointer);

            return pointer;
        }

        void AddElement(const std::shared_ptr<UIElement> &element);

        /**
         * @brief Add a new UI element to the array from scrach. Is usefull when we want to init a new type
         * @return The newly created element into a weak_ptr so it can be changed. It used weak pointers because
        */
        template <typename T>
        std::shared_ptr<T> CreateElementOfType()
        {

            //We make a
            auto p = std::make_shared<T>();
            elements.push_back(p);
            return p;
        }
    };

}

#endif