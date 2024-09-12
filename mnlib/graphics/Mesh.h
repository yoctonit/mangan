#ifndef INCLUDED_MN_GRAPHICS_MESH_H
#define INCLUDED_MN_GRAPHICS_MESH_H

#include <map>
#include "ShaderInfo.h"
#include "Connection.h"
#include "RenderSettings.h"
#include "Texture.h"

namespace Mn {

    class Mesh {
    public:
        Mesh();

        Mesh(ShaderInfo shaderInfo, Connection connection);

        void AddTexture(const Texture &tex, int unit);

        void DrawStyle(int drawStyle);

        void Draw() const;

        ShaderInfo material;

        RenderSettings renderSettings; // OpenGL render settings

    private:
        int mDrawStyle{GL_TRIANGLES};
        Connection mConnection;
        std::map<int, Texture> mTextures;
    };

}

#endif //INCLUDED_MN_GRAPHICS_MESH_H
