#ifndef INCLUDED_MN_RENDERABLE_SOLID_COLOR_H
#define INCLUDED_MN_RENDERABLE_SOLID_COLOR_H

#include <memory>
#include "shader/SolidColor.h"
#include "connection/SolidColor.h"
#include "Transform.h"

namespace Mn::renderable {

    class SolidColor {
    private:
        std::shared_ptr<Mn::connection::SolidColor> _connection;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;
        GLenum _mode;
        GLint _first;
        GLsizei _count;

    public:
        SolidColor(
                const std::shared_ptr<Mn::connection::SolidColor> &connection,
                GLenum mode, GLint first, GLsizei count) :
                _connection{connection},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 1.0f},
                _mode{mode},
                _first{first},
                _count{count} {}

        void draw(glm::mat4 view) const {
            _connection->shader()->configure(_transform->matrix(), view, _color);
            _connection->vao()->draw(_mode, _first, _count);
        }

        std::shared_ptr<Mn::Transform> transform() { return _transform; }

        void color(float r, float g, float b, float a = 1.0f) {
            _color = glm::vec4(r, g, b, a);
        }

        void mode(GLenum m) { _mode = m; }

        void first(GLint f) { _first = f; }

        void count(GLsizei c) { _count = c; }

        void range(GLint f, GLsizei c) {
            _first = f;
            _count = c;
        }
    };
//    class SolidColor {
//    private:
//        std::shared_ptr<Mn::connection::SolidColorConnection> _connection;
//
//    public:
//        explicit SolidColor(const std::shared_ptr<Mn::connection::SolidColorConnection> &connection) :
//                _connection{connection} {}
//
//        void configure(glm::mat4 model, glm::mat4 view, glm::vec4 color) const {
//            _connection->shader()->configure(model, view, color);
//        }
//
//        void draw(GLenum mode, GLint first, GLsizei count) const {
//            _connection->vao()->draw(mode, first, count);
//        }
//    };
//    class SolidColor {
//    private:
//        std::shared_ptr<Mn::Shader::SolidColor> _shader;
//        std::shared_ptr<Mn::VBO> _buffer;
//        std::shared_ptr<Mn::VAO> _vao;
//
//    public:
//        SolidColor(
//                const std::shared_ptr<Mn::Shader::SolidColor> &shader,
//                const std::shared_ptr<Mn::VBO> &buffer,
//                const std::shared_ptr<Mn::VAO> &vao) :
//                _shader{shader},
//                _buffer{buffer},
//                _vao{vao} {
//            vao->connect(*buffer, *shader->shader(), "a_position", 3, 0, nullptr);
//        }
//
//        void configure(glm::mat4 model, glm::mat4 view, glm::vec4 color) const {
//            _shader->configure(model, view, color);
//        }
//
//        void draw(GLenum mode, GLint first, GLsizei count) const {
//            glBindVertexArray(_vao->id());
//            glDrawArrays(mode, first, count);
//        }
//    };

}

#endif //INCLUDED_MN_RENDERABLE_SOLID_COLOR_H
