#ifndef INCLUDED_MN_GRAPHICS_MESH_H
#define INCLUDED_MN_GRAPHICS_MESH_H

#include <vector>
#include "../geometry/Geometry.h"
#include "Material.h"
#include "Vao.h"
#include "Vbo.h"

namespace Mn {

    class Mesh {
    public:
        void Create(Material m);

        void Create(const Geometry &geom, Geometry::Type t, Material m);

        void Release();

        void ConnectBuffer(const Geometry &geom, Geometry::Type type);

        void Draw() const;

        Material material;

    private:
        int mVertexCount{};
        Vao mVao;
        std::vector<Vbo> mBuffers;
    };

}

#endif //INCLUDED_MN_GRAPHICS_MESH_H
