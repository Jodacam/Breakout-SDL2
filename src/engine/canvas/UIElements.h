#ifndef GAME_ENGINE_UIELEMENT_H
#define GAME_ENGINE_UIELEMENT_H
#include <memory>
#include <string>
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
        virtual void Render(GameEngine::Renderer *renderer) = 0;
        virtual void Update(float dt) = 0;
        /**
         * @return The state of the UIElement. When is dirty a re-render will be trigger on the canvas element.
        */
        inline bool GetIsDirty() const { return isDirty; }
        inline Vector GetPosition() const { return position; }
        inline Vector GetSize() const { return size; }
        void SetPosition(const Vector &pos);
        void SetSize(const Vector &s);
    };
#pragma endregion

#pragma region UIImage

    /**
     * Image element. It cointains a pointer to one image and the size/position of the image.
    */
    class UIImage : public UIElement
    {

    protected:
        //TODO Change image API
        Sprite image;

    public:
        void Update(float dt);
        void Render(GameEngine::Renderer *renderer);
        UIImage(std::string asset);
        UIImage(std::string asset,const Vector &position);
    };

#pragma endregion

#pragma region UIText

    class UIText : public UIElement {
        protected:
            Text text;
        public:
            void Render(GameEngine::Renderer *renderer);
            bool SetText(const std::string &t,bool changeSize = false);
            inline std::string GetText() { return text.GetText();}
            void Update(float dt) {}
            UIText(const std::string &text);
            UIText(const std::string &text,const Vector &pos);
            UIText(const std::string &text, const Vector &pos,const Vector &s);
    };

#pragma endregion

}

#endif