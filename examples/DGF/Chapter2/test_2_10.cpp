#include <iostream>
#include "core/Base.h"


class Test_2_10 : public Base {
public:
    void initialize() override {
        std::cout << "Initializing...\n";
    }

    void update() override {
        // typical usage
        if (m_input.isClickedKey(MN_KEY_SPACE))
            std::cout << "The 'space' key was just pressed down.\n";
        if (m_input.isPressedKey(MN_KEY_RIGHT))
            std::cout << "The 'right arrow' key is currently pressed.\n";
    }
};

int main() {
    Test_2_10().run();
    return 0;
}
