#ifndef INCLUDED_MN_RENDERABLE_TRIANGLE_H
#define INCLUDED_MN_RENDERABLE_TRIANGLE_H

#include <memory>
#include "Transform.h"
#include "SolidColor.h"
#include "Textured.h"

namespace Mn::renderable {

    class SolidColorTriangle {
    private:
        std::shared_ptr<Mn::renderable::SolidColor> _solid_color_renderable;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;

    public:
        explicit SolidColorTriangle(const std::shared_ptr<Mn::renderable::SolidColor> &sc) :
                _solid_color_renderable{sc},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 1.0f} {}

        void draw(glm::mat4 view) const {
            _solid_color_renderable->configure(_transform->matrix(), view, _color);
            _solid_color_renderable->draw(GL_TRIANGLES, 0, 3);
        }

        std::shared_ptr<Mn::Transform> transform() { return _transform; }

        void set_color(float r, float g, float b, float a = 1.0f) {
            _color = glm::vec4(r, g, b, a);
        }
    };

    class TexturedTriangle {
    private:
        std::shared_ptr<Mn::renderable::Textured> _textured_renderable;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;
        int _texture_unit;

    public:
        explicit TexturedTriangle(const std::shared_ptr<Mn::renderable::Textured> &tr) :
                _textured_renderable{tr},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 0.0f},
                _texture_unit{0} {}

        void draw(glm::mat4 view) const {
            _textured_renderable->configure(_transform->matrix(), view, _color, _texture_unit);
            _textured_renderable->draw(GL_TRIANGLES, 0, 3);
        }

        std::shared_ptr<Mn::Transform> transform() { return _transform; }

        void set_color(float r, float g, float b, float a = 1.0f) {
            _color = glm::vec4(r, g, b, a);
        }

        void set_texture_unit(int tu) {
            _texture_unit = tu;
        }
    };

//    class Triangle {
//    private:
//        std::shared_ptr<Mn::ShaderProgram> shader;
//        std::shared_ptr<Mn::VAO> vao;
//        std::shared_ptr<Mn::VBO> buffer;
//        float _r;
//        float _g;
//        float _b;
//        float _a;
//    public:
//        explicit Triangle(float side = 1.0f, float r = 0.0f, float g = 0.0f, float b = 0.0f)
//                : _r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f) {
//            shader = std::make_shared<Mn::ShaderProgram>("shader/simple.vs", "shader/simple.fs");
//
//            buffer = std::make_shared<Mn::VBO>(Mn::geometry::equilateral_triangle(side));
//
//            vao = std::make_shared<Mn::VAO>();
//            vao->connect(*buffer, *shader, "a_position", 3, 0, nullptr);
//        }
//
//        void draw(glm::mat4 model, glm::mat4 view) const {
//            shader->use();
//            shader->uniform(shader->location("u_color"), _r, _g, _b, _a);
//            shader->uniform(shader->location("u_model_matrix"), model);
//            shader->uniform(shader->location("u_camera_matrix"), view);
//
//            vao->activate();
//            glDrawArrays(GL_TRIANGLES, 0, 3);
//        }
//
//        void set_color(float r, float g, float b, float a = 1.0f) {
//            _r = r;
//            _g = g;
//            _b = b;
//            _a = a;
//        }
//    };
//    class SolidColorTriangle {
//    private:
//        std::shared_ptr<Mn::ShaderProgram> shader;
//        std::shared_ptr<Mn::VAO> vao;
//        std::shared_ptr<Mn::VBO> buffer;
//    public:
//        explicit SolidColorTriangle(float side = 1.0f, float r = 0.0f, float g = 0.0f, float b = 0.0f) {
//            shader = std::make_shared<Mn::ShaderProgram>("shader/position.vs", "shader/solid_color.fs");
//            buffer = std::make_shared<Mn::VBO>(Mn::geometry::equilateral_triangle(side));
//
//            vao = std::make_shared<Mn::VAO>();
//            vao->connect(*buffer, *shader, "a_position", 3, 0, nullptr);
//        }
//
//        void draw(float r, float g, float b) const {
//            shader->use();
//            shader->uniform(shader->location("u_color"), r, g, b);
//
//            vao->activate();
//            glDrawArrays(GL_TRIANGLES, 0, 3);
//        }
//    };

}

#endif //INCLUDED_MN_RENDERABLE_TRIANGLE_H
