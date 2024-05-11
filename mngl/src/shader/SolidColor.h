#ifndef INCLUDED_MN_SOLID_COLOR_H
#define INCLUDED_MN_SOLID_COLOR_H

#include <memory>
#include "core/Shader.h"

namespace Mn::Shader {

    class SolidColor {
    private:
        std::shared_ptr<Mn::ShaderProgram> _shader;
        GLint _u_model_matrix_ref{};
        GLint _u_camera_matrix_ref{};
        GLint _u_color_ref{};

    public:
        SolidColor() {
            _shader = std::make_shared<Mn::ShaderProgram>("shader/simple.vs", "shader/simple.fs");
            _u_model_matrix_ref = _shader->location("u_model_matrix");
            _u_camera_matrix_ref = _shader->location("u_camera_matrix");
            _u_color_ref = _shader->location("u_color");
        }

        void configure(glm::mat4 model, glm::mat4 view, glm::vec4 color) const {
            _shader->use();
            _shader->uniform(_u_model_matrix_ref, model);
            _shader->uniform(_u_camera_matrix_ref, view);
            _shader->uniform(_u_color_ref, color.r, color.g, color.b, color.a);
        }

        [[nodiscard]] std::shared_ptr<Mn::ShaderProgram> shader() const { return _shader; }

    };

}

#endif //INCLUDED_MN_SOLID_COLOR_H
