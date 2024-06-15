#include "engine/Run.h"


class EmptyScene {
public:
    EmptyScene() = default;

    void Render() const {
        glClearColor(0.929f, 0.972f, 0.961, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main() {
    Mn::Window wnd(1024, 1024, "Chapter-02 Example-01 Empty Scene");
    Mn::ShowStaticScene<EmptyScene>(wnd);
    return 0;
}
