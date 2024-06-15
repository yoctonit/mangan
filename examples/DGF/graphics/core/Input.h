#ifndef DGF_GRAPHICS_CORE_INPUT_H
#define DGF_GRAPHICS_CORE_INPUT_H

#include <vector>
#include "InputCodes.h"


struct MousePosition {
    float x, y;
    float window_size_x, window_size_y;
};

class Input {
public:
    [[nodiscard]] bool isPressedKey(int key) const;

    [[nodiscard]] bool isClickedKey(int key) const;

    [[nodiscard]] bool isPressedButton(int button) const;

    [[nodiscard]] bool isClickedButton(int button) const;

    [[nodiscard]] MousePosition getMousePosition() const;

    void update();

private:
    Input();

    void OnKeyDown_(int key);

    void OnKeyUp_(int key);

    void OnMouseDown_(int button);

    void OnMouseUp_(int button);

    void OnMouseMove_(float x_pos, float y_pos);

    void SetWindowSize_(int x_size, int y_size);

    MousePosition position_{};

    std::vector<bool> key_previous_state_;
    std::vector<bool> key_pressed_;
    std::vector<bool> key_clicked_;

    std::vector<bool> button_previous_state_;
    std::vector<bool> button_pressed_;
    std::vector<bool> button_clicked_;

    friend class Base;
};


#endif //DGF_GRAPHICS_CORE_INPUT_H
