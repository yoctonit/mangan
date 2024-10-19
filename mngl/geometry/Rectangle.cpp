#include "Rectangle.h"

namespace Mn {

    Rectangle::Rectangle(float width, float height) {
        Create(width, height, glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.5f));
    }

    Rectangle::Rectangle(float width, float height, glm::vec2 position, glm::vec2 alignment) {
        Create(width, height, position, alignment);
    }

    void Rectangle::Create(float width, float height, glm::vec2 position, glm::vec2 alignment) {
        float x = position.x;
        float y = position.y;
        float a = alignment.x;
        float b = alignment.y;

        glm::vec3 P0(x + (-a) * width, y + (-b) * height, 0.0f);
        glm::vec3 P1(x + (1.0f - a) * width, y + (-b) * height, 0.0f);
        glm::vec3 P2(x + (-a) * width, y + (1.0f - b) * height, 0.0f);
        glm::vec3 P3(x + (1.0f - a) * width, y + (1.0f - b) * height, 0.0f);

        mVertices = {P0, P1, P3, P0, P3, P2};

        // normal vector
        glm::vec3 N0(0.0f, 0.0f, 1.0f);

        mNormals = {N0, N0, N0, N0, N0, N0};

        // texture coordinates
        glm::vec2 T0(0.0f, 0.0f);
        glm::vec2 T1(1.0f, 0.0f);
        glm::vec2 T2(0.0f, 1.0f);
        glm::vec2 T3(1.0f, 1.0f);

        mTexCoords = {T0, T1, T3, T0, T3, T2};

        mVertexCount = 6;
    }

}