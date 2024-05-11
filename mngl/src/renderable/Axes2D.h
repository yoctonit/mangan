#ifndef INCLUDED_MN_RENDERABLE_AXES_2D_H
#define INCLUDED_MN_RENDERABLE_AXES_2D_H

#include <memory>
#include "core/VAO.h"
#include "core/VBO.h"
#include "geometry/Axes2D.h"

namespace Mn::renderable {

    class Axes2D {
    private:
        std::shared_ptr<Mn::ShaderProgram> shader;
        std::shared_ptr<Mn::VAO> vao;
        std::shared_ptr<Mn::VBO> buffer;
        int count{};
    public:
        explicit Axes2D(int x_min, int x_max, int y_min, int y_max, int step) {
            shader = std::make_shared<Mn::ShaderProgram>("shader/axis.vs", "shader/axis.fs");

            Mn::geometry::Axes2D axes2d(x_min, x_max, y_min, y_max, step);
            count = axes2d.count();
            buffer = std::make_shared<Mn::VBO>(axes2d.geometry());

            vao = std::make_shared<Mn::VAO>();
            vao->connect(*buffer, *shader, "a_position", 3, 6, nullptr);
            vao->connect(*buffer, *shader, "a_color", 3, 6, (void *) (sizeof(float) * 3));
        }

        void draw(glm::mat4 model, glm::mat4 view) const {
            shader->use();
            shader->uniform(shader->location("u_model_matrix"), model);
            shader->uniform(shader->location("u_camera_matrix"), view);

            vao->activate();
            glDrawArrays(GL_LINES, 0, count);
        }
    };

}

#endif //INCLUDED_MN_RENDERABLE_AXES_2D_H
