#include <glm/glm.hpp>
#include "MovementRig.h"

MovementRig::MovementRig() :
        MovementRig(1.0, 60.0) {}

MovementRig::MovementRig(double unitsPerSecond, double degreesPerSecond) : Object3D("movementRig") {

    m_unitsPerSecond = unitsPerSecond;
    m_degreesPerSecond = degreesPerSecond;

    // customizable key mappings
    // defaults: W,A,S,D,R,F (move); Q,E (turn); T,G (look)
    m_keyMap["move_forwards"] = MN_KEY_W;
    m_keyMap["move_backwards"] = MN_KEY_S;
    m_keyMap["move_left"] = MN_KEY_A;
    m_keyMap["move_right"] = MN_KEY_D;
    m_keyMap["move_up"] = MN_KEY_R;
    m_keyMap["move_down"] = MN_KEY_F;
    m_keyMap["turn_left"] = MN_KEY_Q;
    m_keyMap["turn_right"] = MN_KEY_E;
    m_keyMap["look_up"] = MN_KEY_T;
    m_keyMap["look_down"] = MN_KEY_G;
}

void MovementRig::attach(const std::shared_ptr<Camera> &camera) {
    m_lookAttachment = camera;
}

void MovementRig::update(Input &input, double deltaTime) {
    auto moveAmount = static_cast<float>(m_unitsPerSecond * deltaTime);
    auto rotateAmount = static_cast<float>(glm::radians(m_degreesPerSecond) * deltaTime);
    auto pos = m_lookAttachment->getPosition();

    if (input.isPressedKey(m_keyMap["move_forwards"])) {
        pos.z -= moveAmount;
        m_lookAttachment->setPosition(pos);
    }
    if (input.isPressedKey(m_keyMap["move_backwards"])) {
        pos.z += moveAmount;
        m_lookAttachment->setPosition(pos);
    }
    if (input.isPressedKey(m_keyMap["move_right"])) {
        pos.x += moveAmount;
        m_lookAttachment->setPosition(pos);
    }
    if (input.isPressedKey(m_keyMap["move_left"])) {
        pos.x -= moveAmount;
        m_lookAttachment->setPosition(pos);
    }
    if (input.isPressedKey(m_keyMap["move_up"])) {
        pos.y += moveAmount;
        m_lookAttachment->setPosition(pos);
    }
    if (input.isPressedKey(m_keyMap["move_down"])) {
        pos.y -= moveAmount;
        m_lookAttachment->setPosition(pos);
    }
//    if (input.isPressedKey(m_keyMap["turn_right"]))
//        rotateY(-rotateAmount, true);
//    if (input.isPressedKey(m_keyMap["turn_left"]))
//        rotateY(rotateAmount, true);
//    if (input.isPressedKey(m_keyMap["look_up"]))
//        m_lookAttachment->rotateX(rotateAmount, true);
//    if (input.isPressedKey(m_keyMap["look_down"]))
//        m_lookAttachment->rotateX(-rotateAmount, true);
}

/*
MovementRig::MovementRig() :
        MovementRig(1.0, 60.0) {}

MovementRig::MovementRig(double unitsPerSecond, double degreesPerSecond)
        : Object3D("movementRig") {
    m_lookAttachment = std::make_shared<Object3D>("lookAtAttachment");
    add(m_lookAttachment);

    m_unitsPerSecond = unitsPerSecond;
    m_degreesPerSecond = degreesPerSecond;

    // customizable key mappings
    // defaults: W,A,S,D,R,F (move); Q,E (turn); T,G (look)
    m_keyMap["move_forwards"] = MN_KEY_W;
    m_keyMap["move_backwards"] = MN_KEY_S;
    m_keyMap["move_left"] = MN_KEY_A;
    m_keyMap["move_right"] = MN_KEY_D;
    m_keyMap["move_up"] = MN_KEY_R;
    m_keyMap["move_down"] = MN_KEY_F;
    m_keyMap["turn_left"] = MN_KEY_Q;
    m_keyMap["turn_right"] = MN_KEY_E;
    m_keyMap["look_up"] = MN_KEY_T;
    m_keyMap["look_down"] = MN_KEY_G;
}

void MovementRig::attach(const std::shared_ptr<Object3D> &object) {
    m_lookAttachment->add(object);
}

void MovementRig::update(Input &input, double deltaTime) {
    auto moveAmount = static_cast<float>(m_unitsPerSecond * deltaTime);
    auto rotateAmount = static_cast<float>(glm::radians(m_degreesPerSecond) * deltaTime);

    if (input.isPressedKey(m_keyMap["move_forwards"]))
        translate(0, 0, -moveAmount, true);
    if (input.isPressedKey(m_keyMap["move_backwards"]))
        translate(0, 0, moveAmount, true);
    if (input.isPressedKey(m_keyMap["move_right"]))
        translate(moveAmount, 0, 0, true);
    if (input.isPressedKey(m_keyMap["move_left"]))
        translate(-moveAmount, 0, 0, true);
    if (input.isPressedKey(m_keyMap["move_up"]))
        translate(0, moveAmount, 0, true);
    if (input.isPressedKey(m_keyMap["move_down"]))
        translate(0, -moveAmount, 0, true);
    if (input.isPressedKey(m_keyMap["turn_right"]))
        rotateY(-rotateAmount, true);
    if (input.isPressedKey(m_keyMap["turn_left"]))
        rotateY(rotateAmount, true);
    if (input.isPressedKey(m_keyMap["look_up"]))
        m_lookAttachment->rotateX(rotateAmount, true);
    if (input.isPressedKey(m_keyMap["look_down"]))
        m_lookAttachment->rotateX(-rotateAmount, true);
}
 */