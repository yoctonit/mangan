#ifndef INCLUDED_MN_ENGINE_WINDOW_H
#define INCLUDED_MN_ENGINE_WINDOW_H

#include <string>

#include "Input.h"


class GLFWwindow;

namespace Mn {

    class Window {
    public:
        Window();

        Window(int width, int height, std::string title);

        ~Window();

        void SetTitle(const std::string &title);

        void SetDimensions(int width, int height);

        void Create();

        void Close();

        void Display() const;

        [[nodiscard]] bool IsOpen() const;

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        static Input &GetInput();

        static void PollEvents();

    private:
        static void OnGlfwError(int error_code, const char *error_message);

        static void InitializeGlfw();

        static void TerminateGlfw();

        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

        static void MouseCallback(GLFWwindow *window, int button, int action, int mods);

        static void MousePositionCallback(GLFWwindow *window, double x_pos, double y_pos);

        void CreateGlfwWindow();

        void SetupCallbacks();

        void LoadOpenGlExtensions();

        GLFWwindow *window_{};
        int width_;
        int height_;
        std::string title_;

        static Input input_;
    };

}

#endif //INCLUDED_MN_ENGINE_WINDOW_H
