#ifndef INCLUDED_MN_INPUT_H
#define INCLUDED_MN_INPUT_H

#define GLFW_INCLUDE_NONE

#include <vector>
#include <GLFW/glfw3.h>

namespace Mn {

    namespace input {

        enum class key {
            space = GLFW_KEY_SPACE,

            q = GLFW_KEY_Q,
            w = GLFW_KEY_W,
            e = GLFW_KEY_E,
            r = GLFW_KEY_R,
            t = GLFW_KEY_T,

            y = GLFW_KEY_Y,
            u = GLFW_KEY_U,
            i = GLFW_KEY_I,
            o = GLFW_KEY_O,
            p = GLFW_KEY_P,

            a = GLFW_KEY_A,
            s = GLFW_KEY_S,
            d = GLFW_KEY_D,
            f = GLFW_KEY_F,
            g = GLFW_KEY_G,

            h = GLFW_KEY_H,
            j = GLFW_KEY_J,
            k = GLFW_KEY_K,
            l = GLFW_KEY_L,
            semi_colon = GLFW_KEY_SEMICOLON,

            z = GLFW_KEY_Z,
            x = GLFW_KEY_X,
            c = GLFW_KEY_C,
            v = GLFW_KEY_V,
            b = GLFW_KEY_B,

            n = GLFW_KEY_N,
            m = GLFW_KEY_M,
            comma = GLFW_KEY_COMMA,
            period = GLFW_KEY_PERIOD,
            slash = GLFW_KEY_SLASH,

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
    }

    class Input {

    public:
        [[nodiscard]] bool is_pressed(input::key key_code) const;

        [[nodiscard]] bool is_clicked(input::key key_code) const;

        [[nodiscard]] bool is_pressed(input::mouse::button button) const;

        [[nodiscard]] bool is_clicked(input::mouse::button button) const;

        [[nodiscard]] float mouse_x_position() const;

        [[nodiscard]] float mouse_y_position() const;

    private:
        Input();

        void _update();

        void _on_key_down(int key_code);

        void _on_key_up(int key_code);

        void _on_mouse_down(int button);

        void _on_mouse_up(int button);

        void _on_mouse_move(float x_pos, float y_pos);

        float _mouse_x{};
        float _mouse_y{};

        std::vector<bool> _key_previous_state;
        std::vector<bool> _key_pressed;
        std::vector<bool> _key_clicked;

        std::vector<bool> _button_previous_state;
        std::vector<bool> _button_pressed;
        std::vector<bool> _button_clicked;

        friend class Window;
    };

}

#endif //INCLUDED_MN_INPUT_H
