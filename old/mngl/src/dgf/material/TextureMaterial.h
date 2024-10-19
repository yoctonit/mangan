//
// Created by Ivan on 15-Jan-23.
//

#ifndef INCLUDED_MN_TEXTURE_MATERIAL_H
#define INCLUDED_MN_TEXTURE_MATERIAL_H

#include "../Texture.h"
#include "Material.h"

class TextureMaterial : public Material {
public:
    explicit TextureMaterial(const std::string &fileName)
            : Material("shader/TextureMaterial.vert", "shader/TextureMaterial.frag"),
            texture(fileName) {

        //addUniform("vec3", "baseColor", new Vector(1,1,1) );
        //addUniform("sampler2D", "tex", new Vector(texture.textureRef, 1));
        //addUniform("vec2", "repeatUV", new Vector(1,1) );
        //addUniform("vec2", "offsetUV", new Vector(0,0) );
        addUniform("baseColor", Mn::Shader::Uniform());
        addUniform("tex", Mn::Shader::Uniform());
        addUniform("repeatUV", Mn::Shader::Uniform());
        addUniform("offsetUV", Mn::Shader::Uniform());
        locateUniforms();

        renderSettings["doubleSide"] = RenderSetting("doubleSide", 1.0f, true);
        renderSettings["wireframe"] = RenderSetting("wireframe", 1.0f, false);
        renderSettings["lineWidth"] = RenderSetting("lineWidth", 1.0f, true);
    }

    void uploadUniforms() override {
        uniforms["baseColor"].upload(glm::vec3(1.0f, 1.0f, 1.0f));
        uniforms["tex"].upload(texture.textureRef, 1);
        uniforms["repeatUV"].upload(glm::vec2(1.0f, 1.0f));
        uniforms["offsetUV"].upload(glm::vec2(0.0f, 0.0f));
    }
private:
    Texture texture;

};

#endif //INCLUDED_MN_TEXTURE_MATERIAL_H
