#ifndef BYO2DGE_CORE_H
#define BYO2DGE_CORE_H

#include <chrono>
#include "window/Window.h"
#include "graphics/ShaderInfo.h"
#include "core/Vbo.h"
#include "core/Vao.h"
#include "Renderable.h"
#include "Scene.h"
#include "LevelManager.h"


class Core {
public:
    Core(int width, int height, std::string title);

    static void clearCanvas(float r, float g, float b, float a = 1.0f);

    Renderable createRenderable() const;

    void start(Scene &scene);

    void start(LevelManager &levelManager);

private:
    Mn::Window mWindow;

    Mn::ShaderInfo mConstColorShader{};
    Mn::Vbo mVertexBuffer{};
    Mn::Vao mVao{};

    // Loop related variables
    //-----------------------
    const float kUPS = 60.0f;                        // Updates per second
    std::chrono::duration<float, std::milli> kMPF{}; // Milliseconds per update

    // Variables for timing game loop.
    std::chrono::time_point<std::chrono::high_resolution_clock> mPrevTime;
    std::chrono::duration<float, std::milli> mLagTime{};

    // The current loop state
    // int mFrameID = -1;
    //-----------------------

    void init();
};

#endif //BYO2DGE_CORE_H
