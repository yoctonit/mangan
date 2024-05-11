#include "window/Window.h"
#include "src/Engine.h"
#include "src/Renderable.h"

class MyGame {
public:
    void Initialize() {
        // Step A: Initialize Engine and Camera objects:
        mEngine.Initialize();
        mEngine.BackgroundColor(glm::vec4{0.9f, 0.9f, 0.9f, 1.0f});

        mCamera.Create(
                glm::vec2(20.0f, 60.0f), // center of the WC
                20.0f, // width of WC
                glm::ivec4(20, 40, 600, 300) // viewport:orgX, orgY, W, H
        );
        mCamera.SetViewAndCameraMatrix();

        // Step B: Create the Renderable objects:
        mBlueSq.Create(mEngine.ConstColorSquareVao(), mEngine.ConstColorShader());
        mBlueSq.Color(glm::vec4(0.25f, 0.25f, 0.95f, 1.0f));
        mBlueSq.Xform().Position(20.0f, 60.0f);
        mBlueSq.Xform().RotationInRad(0.2f); // In Radians
        mBlueSq.Xform().Size(5.0f, 5.0f);

        mRedSq.Create(mEngine.ConstColorSquareVao(), mEngine.ConstColorShader());
        mRedSq.Color(glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
        mRedSq.Xform().Position(20.0f, 60.0f);
        mRedSq.Xform().Size(2.0f, 2.0f);

        mTLSq.Create(mEngine.ConstColorSquareVao(), mEngine.ConstColorShader());
        mTLSq.Color(glm::vec4(0.9f, 0.1f, 0.1f, 1.0f));
        mTLSq.Xform().Position(10.0f, 65.0f);

        mTRSq.Create(mEngine.ConstColorSquareVao(), mEngine.ConstColorShader());
        mTRSq.Color(glm::vec4(0.1f, 0.9f, 0.1f, 1.0f));
        mTRSq.Xform().Position(30.0f, 65.0f);

        mBRSq.Create(mEngine.ConstColorSquareVao(), mEngine.ConstColorShader());
        mBRSq.Color(glm::vec4(0.1f, 0.1f, 0.9f, 1.0f));
        mBRSq.Xform().Position(30.0f, 55.0f);

        mBLSq.Create(mEngine.ConstColorSquareVao(), mEngine.ConstColorShader());
        mBLSq.Color(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        mBLSq.Xform().Position(10.0f, 55.0f);
    }

    void Draw() const {
        mEngine.ClearCanvas();
        mCamera.Clear();

        // Center Blue, slightly rotated square
        mBlueSq.Draw(mCamera);

        // Center red square
        mRedSq.Draw(mCamera);

        // Corner squares
        mTLSq.Draw(mCamera);
        mTRSq.Draw(mCamera);
        mBRSq.Draw(mCamera);
        mBLSq.Draw(mCamera);
    }

    void Release() {
        mEngine.Release();
    }

private:
    Engine mEngine;
    Camera mCamera;

    Renderable mBlueSq;
    Renderable mRedSq;
    Renderable mTLSq;
    Renderable mTRSq;
    Renderable mBRSq;
    Renderable mBLSq;
};

int main() {
    Mn::Window window("Example_03_05", 640, 480);

    return window.ShowStaticScene<MyGame>();
}
