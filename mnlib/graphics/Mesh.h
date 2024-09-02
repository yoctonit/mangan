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
        void Create(Geometry g, Material m);

        void Create(Geometry g, Geometry::Type t, Material m);

        void Release();

        void ConnectBuffer(Geometry::Type type);

        void Draw() const;

        Material material;

    private:
        Geometry mGeometry;
        Vao mVao;
        std::vector<Vbo> mBuffers;
    };

}

#endif //INCLUDED_MN_GRAPHICS_MESH_H
