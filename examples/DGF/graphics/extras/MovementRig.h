#ifndef DGF_GRAPHICS_EXTRAS_MOVEMENT_RIG_H
#define DGF_GRAPHICS_EXTRAS_MOVEMENT_RIG_H

#include <memory>
#include <map>
#include <string>
#include "../core/Object3D.h"
#include "../core/Camera.h"
#include "../core/Input.h"

class MovementRig : public Object3D {
public:
    MovementRig();

    MovementRig(double unitsPerSecond, double degreesPerSecond);

    void attach(const std::shared_ptr<Camera> &camera);

    void update(Input &input, double deltaTime);

private:
    std::shared_ptr<Camera> m_lookAttachment{};
    double m_unitsPerSecond{};
    double m_degreesPerSecond{};
    std::map<std::string, int> m_keyMap;
};

/*
class MovementRig : public Object3D {
public:
    MovementRig();

    MovementRig(double unitsPerSecond, double degreesPerSecond);

    void attach(const std::shared_ptr<Object3D> &obj);

    void update(Input &input, double deltaTime);

private:
    std::shared_ptr<Object3D> m_lookAttachment;
    double m_unitsPerSecond{};
    double m_degreesPerSecond{};
    std::map<std::string, int> m_keyMap;
};
*/
#endif //DGF_GRAPHICS_EXTRAS_MOVEMENT_RIG_H
