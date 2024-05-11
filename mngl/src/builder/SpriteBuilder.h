#ifndef INCLUDED_MN_SPRITE_BUILDER_H
#define INCLUDED_MN_SPRITE_BUILDER_H

#include <unordered_map>
#include "core/Texture.h"
#include <geometry/Square.h>
#include "connection/Sprite.h"
#include "renderable/Sprite.h"

namespace Mn::builder {

    class RenderableBuilder;

    class SpriteBuilder {
    private:
        std::shared_ptr<Mn::connection::Sprite> _connection;
        std::shared_ptr<Mn::Texture> _texture;
        std::shared_ptr<Mn::geometry::square_sprite> _ss;
        float _pos_x;
        float _pos_y;
        float _size_x;
        float _size_y;

        SpriteBuilder(const std::shared_ptr<Mn::connection::Sprite> &conn, const std::shared_ptr<Mn::Texture> &tex)
                : _connection{conn}, _texture{tex}, _pos_x{0.0f}, _pos_y{0.0f}, _size_x{1.0f}, _size_y{1.0f} {
            _ss = std::make_shared<Mn::geometry::square_sprite>(_texture->width(), _texture->height());
        }

    public:
        SpriteBuilder &pixel_positions(float left, float right, float bottom, float top) {
            _ss->element_pixel_positions(left, right, bottom, top);
            return *this;
        }

        SpriteBuilder &position(float x, float y) {
            _pos_x = x;
            _pos_y = y;
            return *this;
        }

        SpriteBuilder &size(float w, float h) {
            _size_x = w;
            _size_y = h;
            return *this;
        }

        [[nodiscard]] std::shared_ptr<Mn::renderable::Sprite> create() const {
            std::shared_ptr<Mn::renderable::Sprite> sprite;
            sprite = std::make_shared<Mn::renderable::Sprite>(
                    _connection,
                    _texture,
                    _ss->element_uv_coordinates(),
                    GL_TRIANGLE_STRIP, 0, 4
            );
            sprite->transform()->position(_pos_x, _pos_y);
            sprite->transform()->size(_size_x, _size_y);
            return sprite;
        }

        friend class RenderableBuilder;

    };

}

#endif //INCLUDED_MN_SPRITE_BUILDER_H
