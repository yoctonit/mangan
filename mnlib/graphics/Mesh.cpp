#include "Mesh.h"

#include <utility>

namespace Mn {

    Mesh::Mesh() = default;

    Mesh::Mesh(const ShaderInfo &shaderInfo) {
        material = shaderInfo;
        mVao.Create();
    }

    Mesh::Mesh(const Geometry &geom, Geometry::Type type, const ShaderInfo &shaderInfo) {
        material = shaderInfo;
        mVao.Create();
        ConnectBuffer(geom, type);
    }

    void Mesh::ConnectBuffer(const Geometry &geom, Geometry::Type type) {
        Vbo buffer;
        buffer = Mn::Vbo(geom.Data(type));
        mBuffers.push_back(buffer);
//        mVertexCount = geom.VertexCount();

        switch (type) {
            case Geometry::Type::Positions:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Position),
                        3, 3, 0);
                mVertexCount = geom.VertexCount();
                break;
            case Geometry::Type::Normals:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Normal),
                        3, 3, 0);
                break;
            case Geometry::Type::TexCoords:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::TexCoord),
                        2, 2, 0);
                break;
            case Geometry::Type::PositionsAndNormals:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Position),
                        3, 6, 0);
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Normal),
                        3, 6, 3);
                mVertexCount = geom.VertexCount();
                break;
            case Geometry::Type::PositionsAndTexCoords:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Position),
                        3, 5, 0);
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::TexCoord),
                        2, 5, 3);
                mVertexCount = geom.VertexCount();
                break;
            case Geometry::Type::NormalsAndTexCoords:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Normal),
                        3, 5, 0);
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::TexCoord),
                        2, 5, 3);
                break;
            case Geometry::Type::PositionsNormalsAndTexCoords:
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Position),
                        3, 8, 0);
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::Normal),
                        3, 8, 3);
                mVao.Connect(
                        material.Location(ShaderInfo::AttributeType::TexCoord),
                        2, 8, 6);
                mVertexCount = geom.VertexCount();
                break;
        }
    }

//    int Mesh::DrawStyle() const {
//        return mDrawStyle;
//    }

    void Mesh::DrawStyle(int drawStyle) {
        mDrawStyle = drawStyle;
    }

    void Mesh::Draw() const {
        renderSettings.Apply();
        material.Upload();
        mVao.Draw(mDrawStyle, 0, mVertexCount);
    }

}
