#include "Mesh.h"

#include <utility>

namespace Mn {

    void Mesh::Create(Geometry g, Material m) {
        mGeometry = std::move(g);
        material = std::move(m);
        mVao.Create();
    }

    void Mesh::Create(Geometry g, Geometry::Type t, Material m) {
        mGeometry = std::move(g);
        material = std::move(m);
        mVao.Create();
        ConnectBuffer(t);
    }

    void Mesh::Release() {
        material.Release();
        mVao.Release();
        for (auto &buffer: mBuffers) {
            buffer.Release();
        }
    }

    void Mesh::ConnectBuffer(Geometry::Type type) {
        Vbo buffer;
        buffer = Mn::Vbo::FromData(mGeometry.Data(type));
        mBuffers.push_back(buffer);

        // TODO: Get indexes from material
        switch (type) {
            case Geometry::Type::Positions:
                mVao.Connect(0, 3, 3, 0); // position attribute
                break;
            case Geometry::Type::Normals:
                mVao.Connect(0, 3, 3, 0); // normal attribute
                break;
            case Geometry::Type::TexCoords:
                mVao.Connect(0, 2, 2, 0); // texture coordinates attribute
                break;
            case Geometry::Type::PositionsAndNormals:
                mVao.Connect(0, 3, 6, 0); // position attribute
                mVao.Connect(1, 3, 6, 3); // normal attribute
                break;
            case Geometry::Type::PositionsAndTexCoords:
                mVao.Connect(0, 3, 5, 0); // position attribute
                mVao.Connect(1, 2, 5, 3); // texture coordinates attribute
                break;
            case Geometry::Type::NormalsAndTexCoords:
                mVao.Connect(0, 3, 5, 0); // normal attribute
                mVao.Connect(1, 2, 5, 3); // texture coordinates attribute
                break;
            case Geometry::Type::PositionsNormalsAndTexCoords:
                mVao.Connect(0, 3, 8, 0); // position attribute
                mVao.Connect(1, 3, 8, 3); // normal attribute
                mVao.Connect(2, 2, 8, 6); // texture coordinates attribute
                break;
        }
    }

    // TODO: Get draw type from material
    void Mesh::Draw() const {
        material.Upload();
        mVao.Draw(material.DrawStyle(), 0, mGeometry.VertexCount());
    }

}