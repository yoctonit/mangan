#ifndef INCLUDED_MN_RENDERABLE_BUILDER_H
#define INCLUDED_MN_RENDERABLE_BUILDER_H

#include <unordered_map>
#include "core/Texture.h"
#include <geometry/Square.h>
#include "connection/Sprite.h"
#include "renderable/Sprite.h"
#include "SpriteBuilder.h"

namespace Mn::builder {

    class RenderableBuilder {
    private:
        std::shared_ptr<Mn::Shader::Texture> _texture_shader;

        std::shared_ptr<Mn::connection::Sprite> _sprite_connection;

        std::unordered_map<std::string, std::shared_ptr<Mn::Texture>> _textures;


    public:
        RenderableBuilder() = default;

        SpriteBuilder make_sprite(const std::string &texture_name) {
            if (_sprite_connection == nullptr) {
                _create_sprite_connection();
            }
            auto sprite_texture = texture(texture_name);

            return SpriteBuilder{_sprite_connection, sprite_texture};
        }

    private:
        std::shared_ptr<Mn::Shader::Texture> texture_shader() {
            if (_texture_shader == nullptr) {
                std::cout << "Creating texture shader\n";
                _texture_shader = std::make_shared<Mn::Shader::Texture>();
            } else {
                std::cout << "Texture shader found in builder's cache\n";
            }
            return _texture_shader;
        }

        void _create_sprite_connection() {
            std::cout << "Creating Sprite connection\n";
            auto square_geometry_buffer = std::make_shared<Mn::VBO>(Mn::geometry::square());
            auto square_texture_coord_buffer = std::make_shared<Mn::VBO>(Mn::geometry::square_uv(), GL_DYNAMIC_DRAW);
            _sprite_connection = std::make_shared<Mn::connection::Sprite>(
                    texture_shader(),
                    square_geometry_buffer,
                    square_texture_coord_buffer
            );
        }

        std::shared_ptr<Mn::Texture> texture(const std::string &texture_name) {
            auto got = _textures.find(texture_name);

            std::shared_ptr<Mn::Texture> t;
            if (got == _textures.end()) {
                std::cout << "Creating " << texture_name << "\n";
                t = std::make_shared<Mn::Texture>(texture_name);
                _textures[texture_name] = t;
            } else {
                std::cout << "Found texture " << got->first << " in builder's cache.\n";
                t = got->second;
            }
            return t;
        }

    };

}

#endif //INCLUDED_MN_RENDERABLE_BUILDER_H
