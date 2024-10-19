#include <iostream>
#include "window/Window.h"


int main() {
    Mn::Window wnd(640, 320, "Example");

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n";

    float r{0.5f}, g{0.3f}, b{0.5f}, a{1.0f};

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
        }

        if (input.IsClickedKey(MN_KEY_R)) {
            r += 0.1f;
            if (r > 1.0f) r = 0.0f;
        }
        if (input.IsClickedKey(MN_KEY_G)) {
            g += 0.1f;
            if (g > 1.0f) g = 0.0f;
        }
        if (input.IsClickedKey(MN_KEY_B)) {
            b += 0.1f;
            if (b > 1.0f) b = 0.0f;
        }

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
        wnd.Display();
    }

    return 0;
}
