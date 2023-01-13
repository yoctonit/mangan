//
// Created by ivan on 13.1.2023..
//

#ifndef INCLUDED_MN_MOVEMENT_RIG_H
#define INCLUDED_MN_MOVEMENT_RIG_H

#include "Object3D.h"
#include "Input.h"
#include <map>
#include <string>
#include <memory>

class MovementRig : public Object3D {
public:
    std::shared_ptr<Object3D> lookAttachment;
    float unitsPerSecond{};
    float degreesPerSecond{};
//    std::map<std::string, int> keyMap;

    MovementRig(float unitsPerSecond_, float degreesPerSecond_) {
        lookAttachment = std::make_shared<Object3D>();
        add(lookAttachment);
        unitsPerSecond = unitsPerSecond_;
        degreesPerSecond = degreesPerSecond_;
    }

    MovementRig() : MovementRig(1.0f, 60.0f) {}

    void attach(const std::shared_ptr<Object3D> &obj) {
//        lookAttachment->add(obj);
        lookAttachment = obj;
    }

    void update(const Mn::Input &input, double delta_time) {
        float moveAmount = unitsPerSecond * (float) delta_time;
        float rotateAmount = degreesPerSecond * (float) M_PI / 180.0f * ((float) delta_time);
        if (input.is_pressed(Mn::key::w)) // move forwards
            lookAttachment->translate(0, 0, -moveAmount, true);
        if (input.is_pressed(Mn::key::s)) // move backwards
            lookAttachment->translate(0, 0, moveAmount, true);
        if (input.is_pressed(Mn::key::d)) // move right
            lookAttachment->translate(moveAmount, 0, 0, true);
        if (input.is_pressed(Mn::key::a)) // move left
            lookAttachment->translate(-moveAmount, 0, 0, true);
        if (input.is_pressed(Mn::key::r)) // move up
            lookAttachment->translate(0, moveAmount, 0, true);
        if (input.is_pressed(Mn::key::f)) // move_down
            lookAttachment->translate(0, -moveAmount, 0, true);
        if (input.is_pressed(Mn::key::e)) // turn_right
            lookAttachment->rotateY(-rotateAmount, true);
        if (input.is_pressed(Mn::key::q)) // turn_left
            lookAttachment->rotateY(rotateAmount, true);
        if (input.is_pressed(Mn::key::t)) // look up
            lookAttachment->rotateX(rotateAmount, true);
        if (input.is_pressed(Mn::key::g)) // look_down
            lookAttachment->rotateX(-rotateAmount, true);
    }
};

#endif //INCLUDED_MN_MOVEMENT_RIG_H
