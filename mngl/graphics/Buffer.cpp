#include <iostream>
#include "Buffer.h"

namespace Mn {

    Buffer::Buffer() = default;

    Buffer::Buffer(const Vbo &vbo, int elementCount)
            : mVbo(vbo), mElementCount(elementCount) {}

    Buffer::Buffer(const std::vector<float> &data, int elementCount, GLenum type) {
        mVbo = Vbo(data, type);
        mElementCount = elementCount;
        // std::cout << "Buffer: created VBO with id " << mVbo.Id() << "\n";
    }

    Buffer::Buffer(const Geometry &geom, Geometry::Type type) {
        mVbo = Mn::Vbo(geom.Data(type));
        mElementCount = geom.VertexCount();
    }

    const Vbo &Buffer::GetVbo() const {
        return mVbo;
    }

    int Buffer::ElementCount() const {
        return mElementCount;
    }

    void Buffer::Debug(const std::string &msg) const {
        std::cout << msg << " has buffer with id " << mVbo.Id()
                  << " which contains data for " << mElementCount << " elements\n";
    }

}
