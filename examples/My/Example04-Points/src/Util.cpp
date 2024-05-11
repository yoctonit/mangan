#include "Util.h"
#include <iostream>

glm::vec2 ToWorldCoordinates(Mn::Input::MousePosition mp, const Camera &camera) {
    glm::vec2 result;

    glm::vec4 viewport = camera.Viewport();
    glm::vec2 worldCenter = camera.WCCenter();
    float worldWidth = camera.WCWidth();
    float worldHeight = camera.WCHeight();

    // Coordinates relative to viewport origin
    float xv = mp.x - viewport.x;
    float yv = mp.y - viewport.y;
    std::cout << "(xv, yv) = (" << xv << ", " << yv << ")\n";

    // Coordinates relative to world dimensions if origin of world is lower left corner
    float xw = (worldWidth / viewport[2]) * xv;
    float yw = (worldHeight / viewport[3]) * yv;
    std::cout << "(xw, yw) = (" << xw << ", " << yw << ")\n";

    // Coordinates if world center is (0,0)
    result.x = xw - worldWidth / 2 + worldCenter.x;
    result.y = yw - worldHeight / 2 + + worldCenter.y;
    std::cout << "result = (" << result.x << ", " << result.y << ")\n";

    return result;
}
