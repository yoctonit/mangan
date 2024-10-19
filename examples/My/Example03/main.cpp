#include "window/Window.h"
#include <iostream>

int main() {
    Mn::Window wnd(800, 600, "Example");

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
        }

        auto mp = input.GetMousePosition();
        if (input.IsClickedButton(MN_MOUSE_BUTTON_LEFT)) {
            std::cout << mp.x << "/" << wnd.Width() << ", "
                      << mp.y << "/" << wnd.Height() << "\n";
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        wnd.Display();
    }
}
