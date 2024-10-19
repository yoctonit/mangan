//
// Created by Ivan on 17-Jan-23.
//

#ifndef INCLUDED_MN_SPRITE_MATERIAL_H
#define INCLUDED_MN_SPRITE_MATERIAL_H

#include "../Texture.h"
#include "Material.h"

class SpriteMaterial : public Material {
public:
    explicit SpriteMaterial(const std::string &fileName) :
            Material("shader/SpriteMaterial.vert", "shader/SpriteMaterial.frag"),
            texture(fileName) {

//        addUniform("vec3", "baseColor", new Vector(1, 1, 1));
//        addUniform("sampler2D", "tex", new Vector(texture.textureRef, 1));
//        addUniform("bool", "billboard", 0);
//        addUniform("float", "tileNumber", -1);
//        addUniform("vec2", "tileCount", new Vector(1, 1));
        addUniform("baseColor", Mn::Shader::Uniform());
        addUniform("tex", Mn::Shader::Uniform());
        addUniform("billboard", Mn::Shader::Uniform());
        addUniform("tileNumber", Mn::Shader::Uniform());
        addUniform("tileCount", Mn::Shader::Uniform());
        locateUniforms();

        renderSettings["doubleSide"] = RenderSetting("doubleSide", 1.0f, true);
    }

    void billboard(bool flag) { _billboard = flag; }
    void tileNumber(float tn) { _tileNumber = tn; }
    void tileCount(glm::vec2 tc) { _tileCount = tc; }

    void uploadUniforms() override {
        uniforms["baseColor"].upload(glm::vec3(1.0f, 1.0f, 1.0f));
        uniforms["tex"].upload(texture.textureRef, 1);
        uniforms["billboard"].upload(_billboard);
        uniforms["tileNumber"].upload(_tileNumber);
        uniforms["tileCount"].upload(_tileCount);
    }

private:
    Texture texture;
    bool _billboard{};
    float _tileNumber{};
    glm::vec2 _tileCount{};
};

#endif //INCLUDED_MN_SPRITE_MATERIAL_H
