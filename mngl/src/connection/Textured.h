#ifndef INCLUDED_MN_CONNECTION_TEXTURED_H
#define INCLUDED_MN_CONNECTION_TEXTURED_H

#include <memory>
#include "core/Shader.h"
#include "core/VBO.h"
#include "core/VAO.h"
#include "shader/Texture.h"

namespace Mn::connection {

    class Textured {
    private:
        std::shared_ptr<Mn::Shader::Texture> _shader;
        std::shared_ptr<Mn::VBO> _buffer;
        std::shared_ptr<Mn::VAO> _vao;

    public:
        Textured(
                const std::shared_ptr<Mn::Shader::Texture> &shader,
                const std::shared_ptr<Mn::VBO> &buffer
        ) : _shader{shader}, _buffer{buffer} {
            _vao = std::make_shared<VAO>();
            _vao->connect(*_buffer, *_shader->shader(), "a_position", 3, 5, nullptr);
            _vao->connect(*_buffer, *_shader->shader(), "a_texture_coordinate", 2, 5, (void *) (sizeof(float) * 3));
        }

        [[nodiscard]] std::shared_ptr<Mn::Shader::Texture> shader() const { return _shader; }

        [[nodiscard]] std::shared_ptr<Mn::VAO> vao() const { return _vao; }
    };

}

#endif //INCLUDED_MN_CONNECTION_TEXTURED_H
