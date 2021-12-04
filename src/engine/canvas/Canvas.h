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
         * @tparam UIElementDerivate Object that inherits from UIElement. It will throw a compiler error if not
         * @return The newly created element into a shared_ptr so it can be changed
        */
        template <typename UIElementDerivate>
        std::shared_ptr<UIElementDerivate> AddElement(UIElementDerivate* p)
        {
            auto pointer = std::shared_ptr<UIElementDerivate>(p);

            elements.push_back(pointer);

            return pointer;
        }

        void AddElement(const std::shared_ptr<UIElement> &element);

        /**
         * @brief Add a new UI element to the array from scrach. Is usefull when we want to init a new type directly
         * With this method you don't have to work with raw pointers so its a bit easy to work with
         * @tparam UIElementDerivate Object that inherits from UIElement. It will throw a compiler error if not
         * @tparam ...Targs Args to create a new Object. They need to correspond to  the constructor arguments of the UIElementDerivate class.
         * @return The newly created element into a shared_ptr so it can be changed
        */
        template <typename UIElementDerivate,typename ...Targs>
        std::shared_ptr<UIElementDerivate> CreateElementOfType(Targs ...args)
        {

            //We make a new pointer from scrach
            auto p = std::make_shared<UIElementDerivate>(args...);
            elements.push_back(p);
            return p;
        }
    };

}

#endif