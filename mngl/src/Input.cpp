//
// Created by ivan on 23.4.2020..
//

#include "Input.h"
//#include <iostream>

namespace Mn {

    bool Input::is_pressed(key key_code) const {
        return _key_pressed[static_cast<int>(key_code)];
        // return _key_pressed[key_code];
    }

    bool Input::is_clicked(key key_code) const {
        return _key_clicked[static_cast<int>(key_code)];
        // return _key_clicked[key_code];
    }

    bool Input::is_pressed(mouse::button button) const {
        return _button_pressed[static_cast<int>(button)];
        // return _button_pressed[button];
    }

    bool Input::is_clicked(mouse::button button) const {
        return _button_clicked[static_cast<int>(button)];
        // return _button_clicked[button];
    }

    double Input::get_mouse_x_position() const { return _mouse_x; }
    double Input::get_mouse_x_screen_position() const { return _mouse_screen_x; }

    double Input::get_mouse_y_position() const { return _mouse_y; }
    double Input::get_mouse_y_screen_position() const { return _mouse_screen_y; }

    Input::Input() {
        LAST_KEY_CODE = GLFW_KEY_LAST;
        LAST_MOUSE_BUTTON = GLFW_MOUSE_BUTTON_LAST;

        _screen_width = 0;
        _screen_height = 0;
        _mouse_x = 0;
        _mouse_screen_x = 0;
        _mouse_y = 0;
        _mouse_screen_y = 0;

        for (int i = 0; i < LAST_KEY_CODE; i += 1) {
            _key_previous_state.push_back(false);
            _key_pressed.push_back(false);
            _key_clicked.push_back(false);
        }

        for (int i = 0; i < LAST_MOUSE_BUTTON; i += 1) {
            _button_previous_state.push_back(false);
            _button_pressed.push_back(false);
            _button_clicked.push_back(false);
        }
    }

    void Input::_set_screen_dimensions(int screen_width, int screen_height) {
        _screen_width = screen_width;
        _screen_height = screen_height;
    }

    void Input::_update() {
        for (int i = 0; i < LAST_KEY_CODE; i += 1) {
            _key_clicked[i] = (!_key_previous_state[i]) && _key_pressed[i];
            _key_previous_state[i] = _key_pressed[i];
        }

        for (int i = 0; i < LAST_MOUSE_BUTTON; i += 1) {
            _button_clicked[i] = (!_button_previous_state[i]) && _button_pressed[i];
            _button_previous_state[i] = _button_pressed[i];
        }
    }

    // Event handler functions

    void Input::_on_key_down(int key_code) {
        _key_pressed[key_code] = true;
    }

    void Input::_on_key_up(int key_code) {
        _key_pressed[key_code] = false;
    }

    void Input::_on_mouse_down(int button) {
        // this._onMouseMove(event);
        _button_pressed[button] = true;
    }

    void Input::_on_mouse_up(int button) {
        // this._onMouseMove(event);
        _button_pressed[button] = false;
    }

    void Input::_on_mouse_move(double x_pos, double y_pos) {
        y_pos = _screen_height - y_pos;    // flip y so 0 is at a bottom of a window

        double screen_half_width = (double) _screen_width / 2;
        double screen_half_height = (double) _screen_height / 2;

        _mouse_screen_x = x_pos;
        _mouse_screen_y = y_pos;

        _mouse_x = (x_pos - screen_half_width) / screen_half_width;
        _mouse_y = (y_pos - screen_half_height) / screen_half_height;

//        std::cout << "(mouse_x, mouse_y): (" << _mouse_x << ", " << _mouse_y << ")\n";
    }

}
