#include "Input.h"


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

    MousePosition Input::GetMousePosition() const {
        return position_;
    }

    void Input::Update() {
        for (int i = 0; i < MN_KEY_LAST; i += 1) {
            key_clicked_[i] = (!key_previous_state_[i]) && key_pressed_[i];
            key_previous_state_[i] = key_pressed_[i];
        }

        for (int i = 0; i < MN_MOUSE_BUTTON_LAST; i += 1) {
            button_clicked_[i] = (!button_previous_state_[i]) && button_pressed_[i];
            button_previous_state_[i] = button_pressed_[i];
        }

        current_event_pos_ = last_event_pos_ = 0;
    }

    bool Input::GetEvent(Event &event) {
        if (current_event_pos_ == last_event_pos_) {
            current_event_pos_ = last_event_pos_ = 0;
            return false;
        }
        event = events_[current_event_pos_++];
        return true;
    }

    Input::Input() :
            key_previous_state_(MN_KEY_LAST),
            key_pressed_(MN_KEY_LAST),
            key_clicked_(MN_KEY_LAST),
            button_previous_state_(MN_MOUSE_BUTTON_LAST),
            button_pressed_(MN_MOUSE_BUTTON_LAST),
            button_clicked_(MN_MOUSE_BUTTON_LAST),
            events_(100) {}

    void Input::OnKeyDown_(int key) {
        key_pressed_[key] = true;
        events_[last_event_pos_++] = Event{MN_PRESS, key};
    }

    void Input::OnKeyUp_(int key) {
        key_pressed_[key] = false;
        events_[last_event_pos_++] = Event{MN_RELEASE, key};
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

}
