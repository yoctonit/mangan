#ifndef INCLUDED_MN_GEOMETRY_RECTANGLE_H
#define INCLUDED_MN_GEOMETRY_RECTANGLE_H

#include "Geometry.h"

namespace Mn {

    class Rectangle : public Geometry {
    public:
        explicit Rectangle(float width = 1.0f, float height = 1.0f);

        Rectangle(float width, float height, glm::vec2 position, glm::vec2 alignment);

    private:
        void Create(
                float width, float height,
                glm::vec2 position = glm::vec2(0.0f, 0.0f),
                glm::vec2 alignment = glm::vec2(0.5f, 0.5f)
        );
    };

}

#endif //INCLUDED_MN_GEOMETRY_RECTANGLE_H
