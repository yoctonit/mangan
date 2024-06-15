#include <iostream>
#include "core/Base.h"


class Test_2_01 : public Base {
public:
    void initialize() override {
        std::cout << "Initializing program...\n";
    }

    void update() override {
        if (m_input.isClickedKey(MN_KEY_LEFT)) {
            std::cout << "Left arrow clicked.\n";
        }
    }
};

int main() {
    Test_2_01().run();
    return 0;
}
