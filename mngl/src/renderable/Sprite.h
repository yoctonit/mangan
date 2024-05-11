#ifndef INCLUDED_MN_RENDERABLE_SPRITE_H
#define INCLUDED_MN_RENDERABLE_SPRITE_H

#include <memory>
#include "core/Texture.h"
#include "connection/Sprite.h"
#include "Transform.h"

namespace Mn::renderable {

    class Sprite {
    private:
        std::shared_ptr<Mn::connection::Sprite> _connection;
        std::shared_ptr<Mn::Texture> _texture;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;
        int _texture_unit;
        std::vector<float> _uv_coords;
        GLenum _mode;
        GLint _first;
        GLsizei _count;

    public:
        Sprite(
                const std::shared_ptr<Mn::connection::Sprite> &connection,
                const std::shared_ptr<Mn::Texture> &texture,
                const std::vector<float> &uv_coords,
                GLenum mode, GLint first, GLsizei count) :
                _connection{connection},
                _texture{texture},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 0.0f},
                _texture_unit{0},
                _uv_coords{uv_coords},
                _mode{mode},
                _first{first},
                _count{count} {}

        void draw(glm::mat4 view) const {
            _connection->texture_coord_buffer()->load(_uv_coords);
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

        void uv_coords(const std::vector<float> &uv) { _uv_coords = uv; }
    };

}

#endif //INCLUDED_MN_RENDERABLE_SPRITE_H
