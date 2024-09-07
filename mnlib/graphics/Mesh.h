#ifndef INCLUDED_MN_GRAPHICS_MESH_H
#define INCLUDED_MN_GRAPHICS_MESH_H

#include <vector>
#include "../geometry/Geometry.h"
#include "ShaderInfo.h"
#include "RenderSettings.h"
#include "Vao.h"
#include "Vbo.h"

namespace Mn {

    class Mesh {
    public:
        Mesh();

        explicit Mesh(const ShaderInfo &shaderInfo);

        Mesh(const Geometry &geom, Geometry::Type type, const ShaderInfo &shaderInfo);

        void ConnectBuffer(const Geometry &geom, Geometry::Type type);

        // [[nodiscard]] int DrawStyle() const;

        void DrawStyle(int drawStyle);

        void Draw() const;

        ShaderInfo material;

        // Store OpenGL render settings
        RenderSettings renderSettings;

    private:
        int mVertexCount{};
        int mDrawStyle{GL_TRIANGLES};
        Vao mVao;
        std::vector<Vbo> mBuffers;
    };

}

#endif //INCLUDED_MN_GRAPHICS_MESH_H
