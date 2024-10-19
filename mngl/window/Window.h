#ifndef INCLUDED_MN_ENGINE_WINDOW_H
#define INCLUDED_MN_ENGINE_WINDOW_H

#include <glad/glad.h>
#include <string>

#include "Input.h"


class GLFWwindow;

namespace Mn {

    class Window {
    public:
        Window(int width, int height, std::string title);

        ~Window();

        void Close();

        void Display() const;

        void CaptureCursor() const;

        [[nodiscard]] bool IsOpen() const;

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        static Input &GetInput();

        static void PollEvents();

    private:
        static void OnGlfwError(int error_code, const char *error_message);

        static void InitializeGlfw();

        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

        static void MouseCallback(GLFWwindow *window, int button, int action, int mods);

        static void MousePositionCallback(GLFWwindow *window, double x_pos, double y_pos);

        static void MouseScrollCallback(GLFWwindow *window, double x_offset, double y_offset);

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
