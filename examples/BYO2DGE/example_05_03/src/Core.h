#ifndef BYO2DGE_CORE_H
#define BYO2DGE_CORE_H

#include <chrono>
#include "window/Window.h"
#include "graphics/ShaderInfo.h"
#include "core/Vbo.h"
#include "core/Vao.h"
#include "core/Texture.h"
#include "Renderable.h"
#include "TextureRenderable.h"
#include "SpriteRenderable.h"
#include "SpriteAnimateRenderable.h"
#include "Scene.h"
#include "LevelManager.h"


class Core {
public:
    Core(int width, int height, std::string title);

    static void clearCanvas(float r, float g, float b, float a = 1.0f);

    Renderable createRenderable() const;

    TextureRenderable createTextureRenderable(const Mn::Texture &texture) const;

    SpriteRenderable createSpriteRenderable(const Mn::Texture &texture) const;

    SpriteAnimateRenderable createSpriteAnimateRenderable(const Mn::Texture &texture) const;

    void start(Scene &scene);

    void start(LevelManager &levelManager);

private:
    Mn::Window mWindow;

    // opengl resources
    //-----------------------
    Mn::ShaderInfo mConstColorShader{};
    Mn::ShaderInfo mTextureShader{};
    Mn::ShaderInfo mSpriteShader{};

    Mn::Vbo mVertexBuffer{};
    Mn::Vbo mTextureBuffer{};
    Mn::Vbo mSpriteTextureBuffer{};

    Mn::Vao mPositionsVao{};
    Mn::Vao mTextureVao{};
    Mn::Vao mSpriteVao{};
    //-----------------------


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
