//
// Created by ivan on 23.4.2020..
//

#ifndef INCLUDED_INPUT_H
#define INCLUDED_INPUT_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <vector>

namespace mn {

    enum class key {
        space = GLFW_KEY_SPACE,

        a = GLFW_KEY_A,
        s = GLFW_KEY_S,
        d = GLFW_KEY_D,
        w = GLFW_KEY_W,

        left = GLFW_KEY_LEFT,
        right = GLFW_KEY_RIGHT,
        up = GLFW_KEY_UP,
        down = GLFW_KEY_DOWN,
    };

    namespace mouse {
        enum class button {
            left = GLFW_MOUSE_BUTTON_LEFT,
            right = GLFW_MOUSE_BUTTON_RIGHT,
            middle = GLFW_MOUSE_BUTTON_MIDDLE,
        };
    }

    class input {

    public:
        // Function for GameEngine programmer to test if a key is pressed down
        [[nodiscard]] bool is_pressed(key key_code) const;
        [[nodiscard]] bool is_clicked(key key_code) const;

        [[nodiscard]] bool is_pressed(mouse::button button) const;
        [[nodiscard]] bool is_clicked(mouse::button button) const;

        [[nodiscard]] double get_mouse_x_position() const;
        [[nodiscard]] double get_mouse_y_position() const;

    private:
        input();

        void _set_screen_dimensions(int screen_width, int screen_height);
        void _update();

        // Event handler functions
        void _on_key_down(int key_code);
        void _on_key_up(int key_code);
        void _on_mouse_down(int button);
        void _on_mouse_up(int button);
        void _on_mouse_move(double x_pos, double y_pos);

        int LAST_KEY_CODE;
        int LAST_MOUSE_BUTTON;

        // Previous key state
        std::vector<bool> _key_previous_state;
        // The pressed keys.
        std::vector<bool> _key_pressed;
        // Click events: once an event is set, it will remain there until polled
        std::vector<bool> _key_clicked;

        // Mouse support
        std::vector<bool> _button_previous_state;
        std::vector<bool> _button_pressed;
        std::vector<bool> _button_clicked;
        double _mouse_x, _mouse_y;

        int _screen_width, _screen_height;

        friend class gl_window;
    };

}

#endif //INCLUDED_INPUT_H
