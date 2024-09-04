#include "Mesh.h"

#include <utility>

namespace Mn {

    void Mesh::Create(Material m) {
        material = std::move(m);
        mVao.Create();
    }

    void Mesh::Create(const Geometry &geom, Geometry::Type t, Material m) {
        material = std::move(m);
        mVao.Create();
        ConnectBuffer(geom, t);
    }

    void Mesh::Release() {
        material.Release();
        mVao.Release();
        for (auto &buffer: mBuffers) {
            buffer.Release();
        }
    }

    void Mesh::ConnectBuffer(const Geometry &geom, Geometry::Type type) {
        Vbo buffer;
        buffer = Mn::Vbo::FromData(geom.Data(type));
        mBuffers.push_back(buffer);
        mVertexCount = geom.VertexCount();

        switch (type) {
            case Geometry::Type::Positions:
                mVao.Connect(material.Location(Material::AttributeType::Position), 3, 3, 0);
                break;
            case Geometry::Type::Normals:
                mVao.Connect(material.Location(Material::AttributeType::Normal), 3, 3, 0);
                break;
            case Geometry::Type::TexCoords:
                mVao.Connect(material.Location(Material::AttributeType::TexCoord), 2, 2,
                             0);
                break;
            case Geometry::Type::PositionsAndNormals:
                mVao.Connect(material.Location(Material::AttributeType::Position), 3, 6, 0);
                mVao.Connect(material.Location(Material::AttributeType::Normal), 3, 6, 3);
                break;
            case Geometry::Type::PositionsAndTexCoords:
                mVao.Connect(material.Location(Material::AttributeType::Position), 3, 5, 0);
                mVao.Connect(material.Location(Material::AttributeType::TexCoord), 2, 5,
                             3);
                break;
            case Geometry::Type::NormalsAndTexCoords:
                mVao.Connect(material.Location(Material::AttributeType::Normal), 3, 5, 0);
                mVao.Connect(material.Location(Material::AttributeType::TexCoord), 2, 5,
                             3);
                break;
            case Geometry::Type::PositionsNormalsAndTexCoords:
                mVao.Connect(material.Location(Material::AttributeType::Position), 3, 8, 0);
                mVao.Connect(material.Location(Material::AttributeType::Normal), 3, 8, 3);
                mVao.Connect(material.Location(Material::AttributeType::TexCoord), 2, 8,
                             6);
                break;
        }
    }

    void Mesh::Draw() const {
        renderSettings.Apply();
        material.Upload();
        mVao.Draw(material.DrawStyle(), 0, mVertexCount);
    }

}
