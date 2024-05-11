#include "window/Window.h"
#include "window/Input.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

namespace Mn {

    bool Input::IsPressedKey(int key) const {
        return key_pressed_.at(key);
    }

    bool Input::IsClickedKey(int key) const {
        return key_clicked_.at(key);
    }

    bool Input::IsPressedButton(int button) const {
        return button_pressed_.at(button);
    }

    bool Input::IsClickedButton(int button) const {
        return button_clicked_.at(button);
    }

    Input::MousePosition Input::Position() const {
        return position_;
    }

    Input::Input() :
            key_previous_state_(GLFW_KEY_LAST),
            key_pressed_(GLFW_KEY_LAST),
            key_clicked_(GLFW_KEY_LAST),
            button_previous_state_(GLFW_MOUSE_BUTTON_LAST),
            button_pressed_(GLFW_MOUSE_BUTTON_LAST),
            button_clicked_(GLFW_MOUSE_BUTTON_LAST) {}

    void Input::Update_() {
        for (int i = 0; i < GLFW_KEY_LAST; i += 1) {
            key_clicked_[i] = (!key_previous_state_[i]) && key_pressed_[i];
            key_previous_state_[i] = key_pressed_[i];
        }

        for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i += 1) {
            button_clicked_[i] = (!button_previous_state_[i]) && button_pressed_[i];
            button_previous_state_[i] = button_pressed_[i];
        }
    }

    void Input::OnKeyDown_(int key) {
        key_pressed_[key] = true;
    }

    void Input::OnKeyUp_(int key) {
        key_pressed_[key] = false;
    }

    void Input::OnMouseDown_(int button) {
        button_pressed_[button] = true;
    }

    void Input::OnMouseUp_(int button) {
        button_pressed_[button] = false;
    }

    void Input::OnMouseMove_(float x_pos, float y_pos) {
        position_.x = x_pos;
        position_.y = position_.window_size_y - y_pos;
    }

    void Input::SetWindowSize_(int x_size, int y_size) {
        position_.window_size_x = static_cast<float>(x_size);
        position_.window_size_y = static_cast<float>(y_size);
    }

    int Input::Key::space = GLFW_KEY_SPACE;

    int Input::Key::one = GLFW_KEY_1;
    int Input::Key::two = GLFW_KEY_2;
    int Input::Key::three = GLFW_KEY_3;
    int Input::Key::four = GLFW_KEY_4;
    int Input::Key::five = GLFW_KEY_5;
    int Input::Key::six = GLFW_KEY_6;
    int Input::Key::seven = GLFW_KEY_7;
    int Input::Key::eight = GLFW_KEY_8;
    int Input::Key::nine = GLFW_KEY_9;
    int Input::Key::zero = GLFW_KEY_0;

    int Input::Key::q = GLFW_KEY_Q;
    int Input::Key::w = GLFW_KEY_W;
    int Input::Key::e = GLFW_KEY_E;
    int Input::Key::r = GLFW_KEY_R;
    int Input::Key::t = GLFW_KEY_R;

    int Input::Key::y = GLFW_KEY_Y;
    int Input::Key::u = GLFW_KEY_U;
    int Input::Key::i = GLFW_KEY_I;
    int Input::Key::o = GLFW_KEY_O;
    int Input::Key::p = GLFW_KEY_P;

    int Input::Key::a = GLFW_KEY_A;
    int Input::Key::s = GLFW_KEY_S;
    int Input::Key::d = GLFW_KEY_D;
    int Input::Key::f = GLFW_KEY_F;
    int Input::Key::g = GLFW_KEY_G;

    int Input::Key::h = GLFW_KEY_H;
    int Input::Key::j = GLFW_KEY_J;
    int Input::Key::k = GLFW_KEY_K;
    int Input::Key::l = GLFW_KEY_L;
    int Input::Key::semi_colon = GLFW_KEY_SEMICOLON;

    int Input::Key::z = GLFW_KEY_Z;
    int Input::Key::x = GLFW_KEY_X;
    int Input::Key::c = GLFW_KEY_C;
    int Input::Key::v = GLFW_KEY_V;
    int Input::Key::b = GLFW_KEY_B;

    int Input::Key::n = GLFW_KEY_N;
    int Input::Key::m = GLFW_KEY_M;
    int Input::Key::comma = GLFW_KEY_COMMA;
    int Input::Key::period = GLFW_KEY_PERIOD;
    int Input::Key::slash = GLFW_KEY_SLASH;

    int Input::Key::left = GLFW_KEY_LEFT;
    int Input::Key::right = GLFW_KEY_RIGHT;
    int Input::Key::up = GLFW_KEY_UP;
    int Input::Key::down = GLFW_KEY_DOWN;

    int Input::Key::esc = GLFW_KEY_ESCAPE;

    int Input::Button::left = GLFW_MOUSE_BUTTON_LEFT;
    int Input::Button::right = GLFW_MOUSE_BUTTON_RIGHT;
    int Input::Button::middle = GLFW_MOUSE_BUTTON_MIDDLE;

}
