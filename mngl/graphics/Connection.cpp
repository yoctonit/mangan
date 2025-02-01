//#include <glad/glad.h>
#include "Connection.h"

namespace Mn {

    Connection::Connection() = default;
//    Connection::Connection() : mVao(true) {};

    Connection::Connection(const Vao &vao) : mVao(vao) {}

    Connection::Connection(const Geometry &geom, Geometry::Type type, const ShaderInfo &shaderInfo)
            : mVao() {
        ConnectBuffer(geom, type, shaderInfo);
    }

    void Connection::ConnectBuffer(const Geometry &geom, Geometry::Type type, const ShaderInfo &shaderInfo) {
        if (mVao.Id() == 0) {
            mVao = Mn::Vao();
        }
        Vbo vbo;
        vbo = Mn::Vbo(geom.Data(type));
        AddVbo(vbo);
        SetVertexCount(geom.VertexCount());

        switch (type) {
            case Geometry::Type::Positions:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 3, 0);
                break;
            case Geometry::Type::Normals:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 3, 0);
                break;
            case Geometry::Type::TexCoords:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 2, 0);
                break;
            case Geometry::Type::PositionsAndNormals:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 6, 0);
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 6, 3);
                break;
            case Geometry::Type::PositionsAndTexCoords:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 5, 0);
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 5, 3);
                break;
            case Geometry::Type::NormalsAndTexCoords:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 5, 0);
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 5, 3);
                break;
            case Geometry::Type::PositionsNormalsAndTexCoords:
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 8, 0);
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 8, 3);
                mVao.Connect(vbo,
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 8, 6);
                break;
        }

    }

    void
    Connection::ConnectBuffer(const Vbo &vbo, int vertexCount, unsigned int index, int size, int stride, int start) {
        if (mVao.Id() == 0) {
            mVao = Mn::Vao();
        }
        AddVbo(vbo);
        SetVertexCount(vertexCount);
        mVao.Connect(vbo, index, size, stride, start);
    }

    void Connection::ConnectBuffer(const Buffer &buffer, Geometry::Type type, const ShaderInfo &shaderInfo) {
        if (mVao.Id() == 0) {
            mVao = Mn::Vao();
        }

        AddVbo(buffer.GetVbo());
        SetVertexCount(buffer.ElementCount());

        switch (type) {
            case Geometry::Type::Positions:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 3, 0);
                break;
            case Geometry::Type::Normals:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 3, 0);
                break;
            case Geometry::Type::TexCoords:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 2, 0);
                break;
            case Geometry::Type::PositionsAndNormals:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 6, 0);
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 6, 3);
                break;
            case Geometry::Type::PositionsAndTexCoords:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 5, 0);
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 5, 3);
                break;
            case Geometry::Type::NormalsAndTexCoords:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 5, 0);
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 5, 3);
                break;
            case Geometry::Type::PositionsNormalsAndTexCoords:
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Position),
                             3, 8, 0);
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::Normal),
                             3, 8, 3);
                mVao.Connect(buffer.GetVbo(),
                             shaderInfo.Location(ShaderInfo::AttributeType::TexCoord),
                             2, 8, 6);
                break;
        }
    }

    void Connection::ConnectBuffer(const Buffer &buffer, unsigned int index, int size, int stride, int start) {
        if (mVao.Id() == 0) {
            mVao = Mn::Vao();
        }
        AddVbo(buffer.GetVbo());
        SetVertexCount(buffer.ElementCount());
        mVao.Connect(buffer.GetVbo(), index, size, start, start);
    }

    void Connection::Draw(GLenum mode) const {
        mVao.Draw(mode, 0, mVertexCount);
        // glDrawArrays(mode, first, count);
    }

//    void Connection::Draw(GLenum mode, int count, GLenum type, const void *indices) const {
//        glBindVertexArray(mId);
//        glDrawElements(mode, count, type, indices);
//    }

    void Connection::SetVertexCount(int vertexCount) {
        if (mVertexCount == 0) {
            mVertexCount = vertexCount;
            return;
        }
        if (mVertexCount != vertexCount) {
            std::cerr << "Setting different vertexCount (current " << mVertexCount
                      << ", new " << vertexCount << ")\n";
            return;
        }
    }

    int Connection::VertexCount() const {
        return mVertexCount;
    }

    void Connection::Activate() const {
        mVao.Activate();
    }

    const Vao &Connection::GetVao() const {
        return mVao;
    }

    void Connection::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << mVao.Id() << "\n";
    }

    void Connection::AddVbo(const Vbo &vbo) {
        // vbo with that id, already recorded in mBuffers
        if (mBuffers.find(vbo.Id()) != mBuffers.end()) {
            return;
        }
        mBuffers[vbo.Id()] = vbo;
    }

}
