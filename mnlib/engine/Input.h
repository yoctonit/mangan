#ifndef INCLUDED_MN_ENGINE_INPUT_H
#define INCLUDED_MN_ENGINE_INPUT_H

#include <vector>
#include "InputCodes.h"

namespace Mn {

    struct Event {
        int type;
        int key;
    };

    struct MousePosition {
        float x, y;
        float window_size_x, window_size_y;
    };

    class Input {
    public:
        [[nodiscard]] bool IsPressedKey(int key) const;

        [[nodiscard]] bool IsClickedKey(int key) const;

        [[nodiscard]] bool IsPressedButton(int button) const;

        [[nodiscard]] bool IsClickedButton(int button) const;

        [[nodiscard]] MousePosition GetMousePosition() const;

        void Update();

        bool GetEvent(Event & event);

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

        std::vector<Event> events_;
        int current_event_pos_{};
        int last_event_pos_{};

        friend class Window;
    };

}

#endif //INCLUDED_MN_ENGINE_INPUT_H
