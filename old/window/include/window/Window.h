#ifndef INCLUDED_MN_WINDOW_WINDOW_H
#define INCLUDED_MN_WINDOW_WINDOW_H

#include <glad/glad.h>
#include <string>
#include "Input.h"

class GLFWwindow;

namespace Mn {

    class Window {

    public:
        explicit Window(const std::string &title, int width = 800, int height = 600);

        ~Window();

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        [[nodiscard]] bool ShouldClose() const;

        template<class T>
        [[nodiscard]] int ShowStaticScene() const;

//        template<class T>
//        int ShowStaticScene(T &scene) const;

        template<class T>
        [[nodiscard]] int ShowScene() const;

    private:
        static void OnGlfwError(int error_code, const char *error_message);

        static void InitializeGlfw();

        static void TerminateGlfw();

        void CreateWindowGlfw(const std::string &title);

        void LoadOpenGlExtensions();

        void SetupCallbacks();

        static void PollEvents();

        void SwapBuffers() const;

        static unsigned windows_count_;
        static bool glfw_initialized_;

        static void KeyCallback_(GLFWwindow *window, int key, int scancode, int action, int mode);

        static void MouseCallback_(GLFWwindow *window, int button, int action, int mods);

        static void MousePositionCallback_(GLFWwindow *window, double x_pos, double y_pos);

        GLFWwindow *window_{};
        int width_;
        int height_;

        static Input input_;
    };

    template<class T>
    int Window::ShowStaticScene() const {
        T scene;

        scene.Initialize();
        scene.Draw();
        SwapBuffers();

        while (!ShouldClose()) {
            PollEvents();
        }

        scene.Release();
        return 0;
    }

//    template<class T>
//    int Window::ShowStaticScene(T &scene) const {
//
//        scene.Initialize();
//        scene.Draw();
//        SwapBuffers();
//
//        while (!ShouldClose()) {
//            PollEvents();
//        }
//
//        scene.Release();
//        return 0;
//    }

    template<class T>
    int Window::ShowScene() const {
        T scene;

        scene.Initialize(Width(), Height());

        while (!ShouldClose() && !scene.ShouldClose()) {
            input_.Update_();

            scene.Update(input_);
            scene.Draw();
            SwapBuffers();

            PollEvents();
        }

        scene.Release();
        return 0;
    }

}

#endif //INCLUDED_MN_WINDOW_WINDOW_H
