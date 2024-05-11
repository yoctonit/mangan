#include "window/Window.h"
#include <iostream>

class Example03 {
public:
    Example03() = default;

    void Initialize(int window_width, int window_height) {
    }

    void Draw() const {}

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(Mn::Input::Key::esc)) {
            should_close_ = true;
        }
        Mn::Input::MousePosition mp = input.Position();
        if (input.IsClickedButton(Mn::Input::Button::left)) {
            std::cout << mp.x << "/" << mp.window_size_x << ", "
                      << mp.y << "/" << mp.window_size_y << "\n";
        }
    }

    void Release() {}

    [[nodiscard]] bool ShouldClose() const {
        return should_close_;
    }

private:
    bool should_close_{};
};

int main() {
    Mn::Window wnd("Example03", 800, 600);
    return wnd.ShowScene<Example03>();
}
