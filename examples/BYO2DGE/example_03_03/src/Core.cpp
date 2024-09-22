#include "Core.h"


void Core::init() {
    mConstColorShader = Mn::ShaderInfo(
            "shader/simple_vs.glsl",
            "shader/simple_fs.glsl"
    );

    mVertexBuffer = Mn::Vbo(
            {
                    0.5f, 0.5f, 0.0f,
                    -0.5f, 0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    -0.5f, -0.5f, 0.0f
            }
    );

    mVao.Create();
    mVao.Connect(mVertexBuffer, mConstColorShader.Location("aPosition"), 3, 3, 0);
}


void Core::clearCanvas(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

//Mn::ShaderInfo &Core::getConstColorShader() {
//    return mConstColorShader;
//}

Renderable Core::createRenderable() {
    return {mVao, mConstColorShader};
}
//void Core::drawSquare(float r, float g, float b, float a) {
//
//    // Step A: Activate the shader
//    mSimpleShader["uPixelColor"] = glm::vec4(r, g, b, a);
//    mSimpleShader.Upload();
//
//    // Step B: Draw with the currently activated geometry and the activated shader
//    mVao.Draw(GL_TRIANGLE_STRIP, 0, 4);
//}
