#ifndef INCLUDED_MN_GRAPHICS_CONNECTION_H
#define INCLUDED_MN_GRAPHICS_CONNECTION_H

#include <map>
#include <string>
#include "ShaderInfo.h"
#include "../core/Vao.h"
#include "Buffer.h"
#include "../geometry/Geometry.h"


namespace Mn {

    class Connection {
    public:
        Connection();

        explicit Connection(const Vao &vao);

        Connection(const Geometry &geom, Geometry::Type type, const ShaderInfo &shaderInfo);

        void ConnectBuffer(const Geometry &geom, Geometry::Type type, const ShaderInfo &shaderInfo);

        void ConnectBuffer(const Vbo &vbo, int vertexCount, unsigned int index, int size, int stride, int start);

        void ConnectBuffer(const Buffer &buffer, Geometry::Type type, const ShaderInfo &shaderInfo);

        void ConnectBuffer(const Buffer &buffer, unsigned int index, int size, int stride, int start);

        void SetVertexCount(int vertexCount);

        [[nodiscard]] int VertexCount() const;

        void Activate() const;

        [[nodiscard]] const Vao &GetVao() const;

        void Draw(GLenum mode) const;

        // void Draw(GLenum mode, int count, GLenum type, const void *indices) const;

        void Debug(const std::string &msg) const;

    private:
        Mn::Vao mVao{};
        int mVertexCount{};

        // Buffers connected with Connection, indexed by buffer id
        std::map<unsigned int, Mn::Vbo> mBuffers;

        void AddVbo(const Vbo &vbo);
    };

}

#endif //INCLUDED_MN_GRAPHICS_CONNECTION_H
