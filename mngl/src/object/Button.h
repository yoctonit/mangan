#ifndef INCLUDED_MN_OBJECT_SQUARE_H
#define INCLUDED_MN_OBJECT_SQUARE_H

#include <vector>
#include <cmath>
#include "renderable/Square.h"
#include "Transform.h"
#include "camera/Camera2D.h"

namespace Mn::object {

    class SolidColorSquare {
    private:
        std::shared_ptr<Mn::renderable::SolidColorSquare> _square;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;
    public:
        explicit SolidColorSquare(const std::shared_ptr<Mn::renderable::SolidColorSquare> &scs)
                : _square{scs},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 1.0f}
                {}

        void draw(const std::shared_ptr<Camera2D>& camera) const {
            _square->draw(_transform->matrix(), camera->camera_matrix(), _color);
        }

        std::shared_ptr<Mn::Transform> transform() { return _transform; }

        void set_color(float r, float g, float b, float a = 1.0f) {
            _color = glm::vec4(r, g, b, a);
        }
    };

}

#endif //INCLUDED_MN_OBJECT_SQUARE_H
