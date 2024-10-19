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

    MousePosition Input::GetMouseRelativePosition() const {
        MousePosition p{};
        p.x = position_.x / window_size_x;
        p.y = position_.y / window_size_y;
        return p;
    }

    MousePosition Input::GetMouseOffset() const {
        return {
                current_position_x - previous_position_x,
                current_position_y - previous_position_y
        };
    }

    MouseScroll Input::GetMouseScroll() const {
        MouseScroll tmp = offset_;
        // reset detected scroll
        offset_.x = 0.0f;
        offset_.y = 0.0f;
        return tmp;
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

//        if (!mouseMoved) {
//            previous_position_x = current_position_x = position_.x;
//            previous_position_y = current_position_y = position_.y;
//        } else {
//            if (firstUpdateCall) {
//                previous_position_x = current_position_x = position_.x;
//                previous_position_y = current_position_y = position_.y;
//                firstUpdateCall = false;
//            } else {
//                previous_position_x = current_position_x;
//                previous_position_y = current_position_y;
//                current_position_x = position_.x;
//                current_position_y = position_.y;
//            }
//        }
        // rewrite of above logic so that most executed case be first checked
        if (mouseMoved && !firstUpdateCall) {
            previous_position_x = current_position_x;
            previous_position_y = current_position_y;
            current_position_x = position_.x;
            current_position_y = position_.y;
        } else if (mouseMoved) { // mouseMoved && firstUpdateCall
            previous_position_x = current_position_x = position_.x;
            previous_position_y = current_position_y = position_.y;
            firstUpdateCall = false;
        } else { // !mouseMoved
            previous_position_x = current_position_x = position_.x;
            previous_position_y = current_position_y = position_.y;
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
        if (!mouseMoved) {
            mouseMoved = true;
        }
        position_.x = x_pos;
        position_.y = window_size_y - y_pos;
    }

    void Input::OnMouseScroll_(float x_offset, float y_offset) {
        offset_.x = x_offset;
        offset_.y = y_offset;
    }

    void Input::SetWindowSize_(int x_size, int y_size) {
        window_size_x = static_cast<float>(x_size);
        window_size_y = static_cast<float>(y_size);
    }

}
