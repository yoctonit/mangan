#include "window/Window.h"
#include "window/Input.h"

#include "sphere_scene.h"


int main() {
    Mn::Window wnd(800, 600, "Moving on sphere");

    sphere_scene scene(wnd.Width(), wnd.Height());


//    glm::vec3 currPos{1.0f, 0.0f, 0.0f};
    glm::vec3 currPos = glm::normalize(glm::vec3{1.0f, 1.0f, 1.0f});
    glm::vec3 currDir{1.0f, 0.0f, 0.0f};

    glm::vec3 spherical = sphericalCoordinates(currPos);
    std::cout << "Spherical coordinates of currPos: " << currPos;
    std::cout << "distance: " << spherical.x << "\n";
    std::cout << "alpha: " << spherical.y << "\n";
    std::cout << "beta: " << spherical.z << "\n";

    glm::vec3 coord = coordinates(spherical);
    std::cout << "Coordinates from spherical: " << coord;

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();

        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
            continue;
        }

        scene.update(input, 1.0f / 60.0f);

        scene.draw();

        wnd.Display();
    }

    return 0;
}
