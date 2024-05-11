#ifndef INCLUDED_MN_RENDERABLE_TEXTURED_H
#define INCLUDED_MN_RENDERABLE_TEXTURED_H

#include <memory>
#include "core/Texture.h"
#include "shader/Texture.h"
#include "connection/Textured.h"
#include "Transform.h"

namespace Mn::renderable {

    class Textured {
    private:
        std::shared_ptr<Mn::connection::Textured> _connection;
        std::shared_ptr<Mn::Texture> _texture;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;
        int _texture_unit;
        GLenum _mode;
        GLint _first;
        GLsizei _count;

    public:
        Textured(
                const std::shared_ptr<Mn::connection::Textured> &connection,
                const std::shared_ptr<Mn::Texture> &texture,
                GLenum mode, GLint first, GLsizei count) :
                _connection{connection},
                _texture{texture},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 0.0f},
                _texture_unit{0},
                _mode{mode},
                _first{first},
                _count{count} {}

        void draw(glm::mat4 view) const {
            _texture->activate(_texture_unit);
            _connection->shader()->configure(_transform->matrix(), view, _color, _texture_unit);
            _connection->vao()->draw(_mode, _first, _count);
        }

        std::shared_ptr<Mn::Transform> transform() { return _transform; }

        void color(float r, float g, float b, float a = 1.0f) {
            _color = glm::vec4(r, g, b, a);
        }

        void texture_unit(int tu) { _texture_unit = tu; }

        void mode(GLenum m) { _mode = m; }

        void first(GLint f) { _first = f; }

        void count(GLsizei c) { _count = c; }

        void range(GLint f, GLsizei c) {
            _first = f;
            _count = c;
        }
    };
//    class Textured {
//    private:
//        std::shared_ptr<Mn::Shader::Texture> _shader;
//        std::shared_ptr<Mn::VBO> _buffer;
//        std::shared_ptr<Mn::VAO> _vao;
//        std::shared_ptr<Mn::Texture> _texture;
//
//    public:
//        Textured(
//                const std::shared_ptr<Mn::Shader::Texture> &shader,
//                const std::shared_ptr<Mn::VBO> &buffer,
//                const std::shared_ptr<Mn::VAO> &vao,
//                const std::shared_ptr<Mn::Texture> &texture) :
//                _shader{shader},
//                _buffer{buffer},
//                _vao{vao},
//                _texture{texture} {
//            vao->connect(*buffer, *shader->shader(), "a_position", 3, 5, nullptr);
//            vao->connect(*buffer, *shader->shader(), "a_texture_coordinate", 2, 5, (void *) (sizeof(float) * 3));
//        }
//
//        void configure(glm::mat4 model, glm::mat4 view, glm::vec4 color, int texture_unit) const {
//            _texture->activate(texture_unit);
//            _shader->configure(model, view, color, texture_unit);
//        }
//
//        void draw(GLenum mode, GLint first, GLsizei count) const {
//            glBindVertexArray(_vao->id());
//            glDrawArrays(mode, first, count);
//        }
//    };

}

#endif //INCLUDED_MN_RENDERABLE_TEXTURED_H
