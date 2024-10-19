#ifndef INCLUDED_MN_GRAPHICS_BUFFER_H
#define INCLUDED_MN_GRAPHICS_BUFFER_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include "../core/Vbo.h"
#include "../geometry/Geometry.h"

namespace Mn {

    class Buffer {
    public:

        Buffer();

        explicit Buffer(const Vbo &vbo, int elementCount);

        explicit Buffer(const std::vector<float> &data, int elementCount, GLenum type = GL_STATIC_DRAW);

        Buffer(const Geometry &geom, Geometry::Type type);

        [[nodiscard]] const Vbo &GetVbo() const;

        [[nodiscard]] int ElementCount() const;

        void Debug(const std::string &msg) const;

    private:
        Vbo mVbo;
        int mElementCount{};
    };

}

#endif //INCLUDED_MN_GRAPHICS_BUFFER_H
