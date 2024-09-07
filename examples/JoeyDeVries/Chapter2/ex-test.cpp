#include "engine/Run.h"
#include "graphics/ShaderInfo.h"


class TestExample {
private:
    Mn::Shader shader;
    Mn::ShaderInfo shaderInfo;


public:
    TestExample()
            : shader{
            "shader/lighting_maps_1.vs",
            "shader/multiple_lights.fs"
    }, shaderInfo(shader) {
        shader.Debug("shader");
        Mn::Shader::DebugRefCnt();
        shaderInfo.Debug();
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main() {
    Mn::Window wnd(800, 600, "Test Example");
    Mn::ShowStaticScene<TestExample>(wnd);
    return 0;
}
