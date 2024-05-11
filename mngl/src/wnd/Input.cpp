#include "Input.h"

namespace Mn {

    bool Input::is_pressed(input::key key_code) const {
        return _key_pressed.at(static_cast<int>(key_code));
    }

    bool Input::is_clicked(input::key key_code) const {
        return _key_clicked.at(static_cast<int>(key_code));
    }

    bool Input::is_pressed(input::mouse::button button) const {
        return _button_pressed.at(static_cast<int>(button));
    }

    bool Input::is_clicked(input::mouse::button button) const {
        return _button_clicked.at(static_cast<int>(button));
    }

    float Input::mouse_x_position() const { return _mouse_x; }

    float Input::mouse_y_position() const { return _mouse_y; }

    Input::Input() :
            _key_previous_state(GLFW_KEY_LAST),
            _key_pressed(GLFW_KEY_LAST),
            _key_clicked(GLFW_KEY_LAST),
            _button_previous_state(GLFW_MOUSE_BUTTON_LAST),
            _button_pressed(GLFW_MOUSE_BUTTON_LAST),
            _button_clicked(GLFW_MOUSE_BUTTON_LAST) {}

    void Input::_update() {
        for (int i = 0; i < GLFW_KEY_LAST; i += 1) {
            _key_clicked[i] = (!_key_previous_state[i]) && _key_pressed[i];
            _key_previous_state[i] = _key_pressed[i];
        }

        for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i += 1) {
            _button_clicked[i] = (!_button_previous_state[i]) && _button_pressed[i];
            _button_previous_state[i] = _button_pressed[i];
        }
    }

    void Input::_on_key_down(int key_code) {
        _key_pressed[key_code] = true;
    }

    void Input::_on_key_up(int key_code) {
        _key_pressed[key_code] = false;
    }

    void Input::_on_mouse_down(int button) {
        _button_pressed[button] = true;
    }

    void Input::_on_mouse_up(int button) {
        _button_pressed[button] = false;
    }

    void Input::_on_mouse_move(float x_pos, float y_pos) {
        _mouse_x = x_pos;
        _mouse_y = y_pos;
    }

}
