#ifndef INCLUDED_MN_WINDOW_INPUT_H
#define INCLUDED_MN_WINDOW_INPUT_H

#include <vector>

namespace Mn {

    class Input {
    public:
        struct Key {
            static int space;

            static int one;
            static int two;
            static int three;
            static int four;
            static int five;
            static int six;
            static int seven;
            static int eight;
            static int nine;
            static int zero;

            static int q;
            static int w;
            static int e;
            static int r;
            static int t;

            static int y;
            static int u;
            static int i;
            static int o;
            static int p;

            static int a;
            static int s;
            static int d;
            static int f;
            static int g;

            static int h;
            static int j;
            static int k;
            static int l;
            static int semi_colon;

            static int z;
            static int x;
            static int c;
            static int v;
            static int b;

            static int n;
            static int m;
            static int comma;
            static int period;
            static int slash;

            static int left;
            static int right;
            static int up;
            static int down;

            static int esc;
        };

        struct Button {
            static int left;
            static int right;
            static int middle;
        };

        struct MousePosition {
            float x, y;
            float window_size_x, window_size_y;
        };

        [[nodiscard]] bool IsPressedKey(int key) const;

        [[nodiscard]] bool IsClickedKey(int key) const;

        [[nodiscard]] bool IsPressedButton(int button) const;

        [[nodiscard]] bool IsClickedButton(int button) const;

        [[nodiscard]] MousePosition Position() const;

    private:
        Input();

        void Update_();

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

        friend class Window;
    };

}

#endif //INCLUDED_MN_WINDOW_INPUT_H
