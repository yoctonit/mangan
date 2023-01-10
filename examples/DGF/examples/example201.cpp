//
// Created by ivan on 15.9.2021..
//
#include "../core/base.h"

class Test : public Base {
public:
    Test() : Base() {}

    void initialize() override {}

    void update() override {}
};

int main() {
    Test scene;

    scene.run();
}
