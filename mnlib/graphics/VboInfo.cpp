#include <iostream>
#include "VboInfo.h"

namespace Mn {

    VboInfo::VboInfo() = default;

    VboInfo::VboInfo(const Vbo &vbo, int elementCount)
            : mVbo(vbo), mElementCount(elementCount) {}

    VboInfo::VboInfo(const std::vector<float> &data, int elementCount, GLenum type) {
        mVbo = Vbo(data, type);
        mElementCount = elementCount;
        std::cout << "VboInfo: created VBO with id " << mVbo.Id() << "\n";
    }

    VboInfo::VboInfo(const Geometry &geom, Geometry::Type type) {
        mVbo = Mn::Vbo(geom.Data(type));
        mElementCount = geom.VertexCount();
    }

    const Vbo &VboInfo::Buffer() const {
        return mVbo;
    }

    int VboInfo::ElementCount() const {
        return mElementCount;
    }

    void VboInfo::Debug(const std::string &msg) const {
        std::cout << msg << " has buffer with id " << mVbo.Id()
                  << " which contains data for " << mElementCount << " elements\n";
    }

}
