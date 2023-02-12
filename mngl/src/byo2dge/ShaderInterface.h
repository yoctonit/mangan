#ifndef OPENGL_EXAMPLES_SHADER_INTERFACE_H
#define OPENGL_EXAMPLES_SHADER_INTERFACE_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SquareGeometryBuffer.h"
#include "../Shader.h"

class ShaderInterface {
public:
    virtual void activate(
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            glm::vec4 pixelColor,
            glm::mat4 trsMatrix,
            glm::mat4 cameraMatrix
    ) const = 0;
};

#endif //OPENGL_EXAMPLES_SHADER_INTERFACE_H
