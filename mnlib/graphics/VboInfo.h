#ifndef INCLUDED_MN_GRAPHICS_VBO_INFO_H
#define INCLUDED_MN_GRAPHICS_VBO_INFO_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include "Vbo.h"
#include "../geometry/Geometry.h"

namespace Mn {

    class VboInfo {
    public:

        VboInfo();

        explicit VboInfo(const Vbo &vbo, int elementCount);

        explicit VboInfo(const std::vector<float> &data, int elementCount, GLenum type = GL_STATIC_DRAW);

        VboInfo(const Geometry &geom, Geometry::Type type);

        [[nodiscard]] const Vbo &Buffer() const;

        [[nodiscard]] int ElementCount() const;

        void Debug(const std::string &msg) const;

    private:
        Vbo mVbo;
        int mElementCount{};
    };

}

#endif //INCLUDED_MN_GRAPHICS_VBO_INFO_H
