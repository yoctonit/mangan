#ifndef EXAMPLES_UTIL_H
#define EXAMPLES_UTIL_H

#include "window/Input.h"
#include "Camera.h"
#include <glm/glm.hpp>

glm::vec2 ToWorldCoordinates(Mn::Input::MousePosition mp, const Camera& camera);

#endif //EXAMPLES_UTIL_H
