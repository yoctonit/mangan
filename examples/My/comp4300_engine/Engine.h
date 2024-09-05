#ifndef INCLUDED_MN_ENGINE_H
#define INCLUDED_MN_ENGINE_H

#include <memory>
#include <string>
#include <iostream>

#include "Input.h"
#include "Scene.h"
#include "Window.h"


namespace Mn {

    class Engine {
    private:
        Window window_{};

        Input &input_;

        std::shared_ptr<Scene> scene_{};

        void InputSystem();

    public:
        struct Config {
            int width;
            int height;
            std::string title;

            Config(int w, int h, std::string t);
        };

        explicit Engine(const Config &config = Config(800, 600, "Example"));

        ~Engine();

        Engine &SetScene(std::shared_ptr<Scene> scene);

        void Run();

        template<class T>
        void ShowStaticScene();

        template<class T>
        void ShowStaticScene(T &scene);

        template<class T>
        void ShowScene();

        template<class T>
        void ShowScene(T &scene);
    };

    template<class T>
    void Engine::ShowStaticScene() {
        T scene;

        scene.Render();
        window_.Display();

        bool runScene = true;
        while (window_.IsOpen() && runScene) {
            Window::PollEvents();

            input_.Update();

            if (input_.IsClickedKey(MN_KEY_ESCAPE)) {
                runScene = false;
            }
        }
    }

    template<class T>
    void Engine::ShowStaticScene(T &scene) {

        scene.Render();
        window_.Display();

        bool runScene = true;
        while (window_.IsOpen() && runScene) {
            Window::PollEvents();

            input_.Update();

            if (input_.IsClickedKey(MN_KEY_ESCAPE)) {
                runScene = false;
            }
        }
    }

    template<class T>
    void Engine::ShowScene() {
        T scene;

        while (window_.IsOpen() && scene.IsRunning()) {
            Window::PollEvents();

            input_.Update();

            scene.Update(input_);
            scene.Render();
            window_.Display();
        }
    }

    template<class T>
    void Engine::ShowScene(T &scene) {

        while (window_.IsOpen() && scene.IsRunning()) {
            Window::PollEvents();

            input_.Update();

            scene.Update(input_);
            scene.Render();
            window_.Display();
        }
    }

}

#endif //INCLUDED_MN_ENGINE_H
