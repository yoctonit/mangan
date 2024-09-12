#include "Mesh.h"

#include <utility>

namespace Mn {

    Mesh::Mesh() = default;

    Mesh::Mesh(ShaderInfo shaderInfo, Connection connection)
            : material{std::move(shaderInfo)}, mConnection{std::move(connection)} {
    }

    void Mesh::AddTexture(const Texture &tex, int unit) {
        if (mTextures.find(unit) != mTextures.end()) {
            std::cerr << "Texture unit " << unit << " already occupied\n";
            return;
        }
        mTextures[unit] = tex;
    }

    void Mesh::DrawStyle(int drawStyle) {
        mDrawStyle = drawStyle;
    }

    void Mesh::Draw() const {
        renderSettings.Apply();

        for (auto &texInfo: mTextures) {
            int unit = texInfo.first;
            texInfo.second.Activate(unit);
        }

        material.Upload();
        mConnection.Draw(mDrawStyle);
    }

}
