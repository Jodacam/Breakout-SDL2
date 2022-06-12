#ifndef _NODE_H_
#define _NODE_H_
#include <string>
#include <vector>
#include <memory>
#include "../math/Vector.h"
#include "Transform.h"
#include "../render/SDLRender.h"
namespace GameEngine {
    class Node {
    public:
        Node() {
        }
        Node(const char* name) {
            this->name = std::string(name);
        }
        Node(const std::string& s) {
            this->name = std::string(s);
        }
        virtual ~Node() {};
        //Getters
        inline const Vector& GetPosition() const { return transform.GetPosition(); };
        inline const Vector& GetScale() const { return transform.GetScale(); };
        inline float GetRotation() const { return transform.GetRotation(); };
        inline const std::string& GetName() const { return name; };
        //Setters
        inline void SetPosition(const Vector pos) { transform.SetPosition(pos); };
        inline void SetScale(const Vector scale) { transform.SetScale(scale); };
        inline void SetRotation(const float rotation) { transform.SetRotation(rotation); };


        /**
         * @brief Updates the children and Executes all code on update.
         * @param dt Delta time. Time pased betwen this frame and others.
        */
        virtual void Update(float dt = 0.0f);
        virtual void Render(GameEngine::Renderer* renderer);


        template <typename NodeDerivate, typename ...Carg>
        std::shared_ptr<NodeDerivate> CreateChildren(Carg ...constructorArgs) {
            auto node = std::make_shared<NodeDerivate>(constructorArgs...);
            
            toPush.push_back(node);
            return node;
        };
        template <typename NodeDerivate>
        std::shared_ptr<Node> AddChildren(NodeDerivate* child) {
            auto node = std::make_shared<NodeDerivate>(child);
            toPush.push_back(node);
            return node;
        };
        template <typename NodeDerivate>
        std::shared_ptr<NodeDerivate> AddChildren(std::shared_ptr<NodeDerivate> child) {
            toPush.push_back(child);
            return child;
        }
    protected:
        bool enable = true;
        std::string name;
        Transform transform;
        std::vector<std::shared_ptr<Node>> children;
        std::vector<std::shared_ptr<Node>> toDelete;
        std::vector<std::shared_ptr<Node>> toPush;
        std::shared_ptr<Node> parent;
    };
}
#endif