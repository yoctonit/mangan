#ifndef INCLUDED_MN_CONNECTION_SOLID_COLOR_H
#define INCLUDED_MN_CONNECTION_SOLID_COLOR_H

#include <memory>
#include "core/Shader.h"
#include "core/VBO.h"
#include "core/VAO.h"
#include "shader/SolidColor.h"

namespace Mn::connection {

    class SolidColor {
    private:
        std::shared_ptr<Mn::Shader::SolidColor> _shader;
        std::shared_ptr<Mn::VBO> _buffer;
        std::shared_ptr<Mn::VAO> _vao;

    public:
        SolidColor(
                const std::shared_ptr<Mn::Shader::SolidColor> &shader,
                const std::shared_ptr<Mn::VBO> &buffer
        ) : _shader{shader}, _buffer{buffer} {
            _vao = std::make_shared<VAO>();
            _vao->connect(*_buffer, *_shader->shader(), "a_position", 3, 0, nullptr);
        }

        [[nodiscard]] std::shared_ptr<Mn::Shader::SolidColor> shader() const { return _shader; }

        [[nodiscard]] std::shared_ptr<Mn::VAO> vao() const { return _vao; }
    };

}

#endif //INCLUDED_MN_CONNECTION_SOLID_COLOR_H
