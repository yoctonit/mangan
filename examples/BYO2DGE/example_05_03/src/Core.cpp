#include "Core.h"

#include <utility>

Core::Core(int width, int height, std::string title)
        : mWindow(width, height, std::move(title)) {
    init();

    kMPF = std::chrono::duration<float, std::milli>(1000.0f / kUPS);
}

void Core::init() {
    mConstColorShader = Mn::ShaderInfo(
            "shader/simple_vs.glsl",
            "shader/simple_fs.glsl"
    );
    mTextureShader = Mn::ShaderInfo(
            "shader/texture_vs.glsl",
            "shader/texture_fs.glsl"
    );
    mSpriteShader = Mn::ShaderInfo(
            "shader/texture_vs.glsl",
            "shader/texture_fs.glsl"
    );

    mVertexBuffer = Mn::Vbo(
            {
                    0.5f, 0.5f, 0.0f,
                    -0.5f, 0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    -0.5f, -0.5f, 0.0f
            }
    );
    mTextureBuffer = Mn::Vbo(
            {
                    1.0f, 1.0f,
                    0.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f
            }
    );
    mSpriteTextureBuffer = Mn::Vbo(
            {
                    1.0f, 1.0f,
                    0.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f
            }, GL_DYNAMIC_DRAW
    );

    mPositionsVao.Create();
    mPositionsVao.Connect(mVertexBuffer, mConstColorShader.Location("aPosition"), 3, 3, 0);

    mTextureVao.Create();
    mTextureVao.Connect(mVertexBuffer, mTextureShader.Location("aPosition"), 3, 3, 0);
    mTextureVao.Connect(mTextureBuffer, mTextureShader.Location("aTexCoord"), 2, 2, 0);

    mSpriteVao.Create();
    mSpriteVao.Connect(mVertexBuffer, mTextureShader.Location("aPosition"), 3, 3, 0);
    mSpriteVao.Connect(mSpriteTextureBuffer, mTextureShader.Location("aTexCoord"), 2, 2, 0);

    // Allows transparency with textures.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void Core::clearCanvas(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderable Core::createRenderable() const {
    return {mPositionsVao, mConstColorShader};
}

TextureRenderable Core::createTextureRenderable(const Mn::Texture &texture) const {
    return {mTextureVao, mTextureShader, texture};
}

SpriteRenderable Core::createSpriteRenderable(const Mn::Texture &texture) const {
    return {mSpriteVao, mSpriteShader, texture, mSpriteTextureBuffer};
}

SpriteAnimateRenderable Core::createSpriteAnimateRenderable(const Mn::Texture &texture) const {
    return {mSpriteVao, mSpriteShader, texture, mSpriteTextureBuffer};
}

void Core::start(Scene &scene) {
    scene.init();

    mPrevTime = std::chrono::high_resolution_clock::now();
    mLagTime = mPrevTime - mPrevTime;

    auto &input = Mn::Window::GetInput();
    while (mWindow.IsOpen() && scene.isRunning()) {
        Mn::Window::PollEvents();

        // Now let's draw
        //     draw() MUST be called before update()
        //     as update() may stop the loop!
        scene.draw();

        // Compute how much time has elapsed since last loop
        const auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = currentTime - mPrevTime;
        mPrevTime = currentTime;
        mLagTime += elapsedTime;

        // Make sure we update the game the appropriate number of times.
        //     Update only every kMPF (1/60 of a second)
        //     If lag larger than update frames, update until caught up.
        while (mLagTime >= kMPF && scene.isRunning()) {
            input.Update();
            scene.update(input);
            mLagTime -= kMPF;
        }

        mWindow.Display();
    }
}

void Core::start(LevelManager &levelManager) {
    mPrevTime = std::chrono::high_resolution_clock::now();
    mLagTime = mPrevTime - mPrevTime;

    auto &input = Mn::Window::GetInput();
    while (mWindow.IsOpen() && levelManager.currentLevel()->isRunning()) {
        Mn::Window::PollEvents();

        // Now let's draw
        //     draw() MUST be called before update()
        //     as update() may stop the loop!
        levelManager.currentLevel()->draw();

        // Compute how much time has elapsed since last loop
        const auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = currentTime - mPrevTime;
        mPrevTime = currentTime;
        mLagTime += elapsedTime;

        // Make sure we update the game the appropriate number of times.
        //     Update only every kMPF (1/60 of a second)
        //     If lag larger than update frames, update until caught up.
        while (mLagTime >= kMPF && levelManager.currentLevel()->isRunning()) {
            input.Update();
            levelManager.currentLevel()->update(input);
            mLagTime -= kMPF;
        }

        mWindow.Display();
    }
}
