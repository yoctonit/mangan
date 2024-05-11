#ifndef INCLUDED_MN_CONNECTION_SPRITE_H
#define INCLUDED_MN_CONNECTION_SPRITE_H

#include <memory>
#include "core/Shader.h"
#include "core/VBO.h"
#include "core/VAO.h"
#include "shader/Texture.h"

namespace Mn::connection {

    class Sprite {
    private:
        std::shared_ptr<Mn::Shader::Texture> _shader;
        std::shared_ptr<Mn::VBO> _geometry_buffer;
        std::shared_ptr<Mn::VBO> _texture_coord_buffer;
        std::shared_ptr<Mn::VAO> _vao;

    public:
        Sprite(
                const std::shared_ptr<Mn::Shader::Texture> &shader,
                const std::shared_ptr<Mn::VBO> &geometry_buffer,
                const std::shared_ptr<Mn::VBO> &texture_coord_buffer
        ) : _shader{shader}, _geometry_buffer{geometry_buffer}, _texture_coord_buffer{texture_coord_buffer} {
            _vao = std::make_shared<VAO>();
            _vao->connect(*_geometry_buffer, *_shader->shader(), "a_position", 3, 0, nullptr);
            _vao->connect(*_texture_coord_buffer, *_shader->shader(), "a_texture_coordinate", 2, 0, nullptr);
        }

        [[nodiscard]] std::shared_ptr<Mn::Shader::Texture> shader() const { return _shader; }

        [[nodiscard]] std::shared_ptr<Mn::VBO> texture_coord_buffer() const { return _texture_coord_buffer; }

        [[nodiscard]] std::shared_ptr<Mn::VAO> vao() const { return _vao; }
    };

}

#endif //INCLUDED_MN_CONNECTION_SPRITE_H
