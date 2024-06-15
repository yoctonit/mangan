#ifndef INCLUDED_MN_ENGINE_RUN_H
#define INCLUDED_MN_ENGINE_RUN_H

#include <glad/glad.h>
#include "Input.h"
#include "Window.h"


namespace Mn {

    template<class T>
    void ShowStaticScene(Window & window) {
        T scene;
        auto &input = Window::GetInput();

        scene.Render();
        window.Display();

        bool runScene = true;
        while (window.IsOpen() && runScene) {
            Window::PollEvents();

            input.Update();

            if (input.IsClickedKey(MN_KEY_ESCAPE)) {
                runScene = false;
            }
        }
    }

    template<class T>
    void ShowStaticScene(T &scene, Window & window) {
        auto &input = Window::GetInput();

        scene.Render();
        window.Display();

        bool runScene = true;
        while (window.IsOpen() && runScene) {
            Window::PollEvents();

            input.Update();

            if (input.IsClickedKey(MN_KEY_ESCAPE)) {
                runScene = false;
            }
        }
    }

    template<class T>
    void ShowScene(Window & window) {
        T scene;
        auto &input = Window::GetInput();

        while (window.IsOpen() && scene.IsRunning()) {
            Window::PollEvents();

            input.Update();

            scene.Update(input);
            scene.Render();
            window.Display();
        }
    }

    template<class T>
    void ShowScene(T &scene, Window & window) {
        auto &input = Window::GetInput();

        while (window.IsOpen() && scene.IsRunning()) {
            Window::PollEvents();

            input.Update();

            scene.Update(input);
            scene.Render();
            window.Display();
        }
    }

}

#endif //INCLUDED_MN_ENGINE_RUN_H
