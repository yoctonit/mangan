#include "core/run.h"
#include "core/shader.h"
#include "core/input.h"

class Empty {
public:
    Empty() : red(0.5f), green(0.5f) {}

    ~Empty() = default;

    void initialize(int, int) {}

    void draw() const {
        glClearColor(red, green, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void update(const Mn::Input& input, double ) {
        red = (float(input.get_mouse_x_position()) + 1.0f) / 2.0f;
        green = (float(input.get_mouse_y_position()) + 1.0f) / 2.0f;
//        if (input.is_clicked(Mn::key::a)) {
//            std::cout << input.get_mouse_x_position() << "\n";
//            red += 0.1f;
//            if (red > 1.0f) red = 0.0f;
//        }

        if (input.is_pressed(Mn::key::space ))
            std::cout << "Space\n";
        if (input.is_pressed(Mn::key::right))
            std::cout << "Right Arrow\n";
        if (input.is_pressed(Mn::key::a))
            std::cout << "Letter A\n";
    }

    void cleanup() {}
private:
    float red;
    float green;
};

int main() {
    Mn::Window window(800, 800, "Empty");
    Empty scene;
    Mn::Run<Empty>(scene, window);
    return 0;
}
