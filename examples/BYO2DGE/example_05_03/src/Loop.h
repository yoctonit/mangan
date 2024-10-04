#ifndef BYO2DGE_LOOP_H
#define BYO2DGE_LOOP_H

#include "engine/Input.h"
#include "engine/Window.h"
#include "Scene.h"
#include <chrono>
#include <memory>
#include <utility>

class Engine;

class Loop {
public:
    explicit Loop(const Mn::Window &window) : mWindow(window) {}

    void start(Scene *scene) {
//        if (mLoopRunning) {
//            throw new Error("loop already running")
//        }

        kMPF = std::chrono::duration<float, std::milli>(1000.0f / kUPS);

        mCurrentScene = scene;
        mCurrentScene->init();

        mPrevTime = std::chrono::high_resolution_clock::now();
        mLagTime = mPrevTime - mPrevTime;
        mLoopRunning = true;
//        mFrameID = requestAnimationFrame(loopOnce);
        auto &input = Mn::Window::GetInput();
        while (mWindow.IsOpen() && mLoopRunning) {
            Mn::Window::PollEvents();

            // input.Update();
            if (input.IsClickedKey(MN_KEY_ESCAPE)) {
                mLoopRunning = false;
            }

            loopOnce(input);

            mWindow.Display();
        }
    }

    void stop() {
        mLoopRunning = false;
        // make sure no more animation frames
        // cancelAnimationFrame(mFrameID);
    }

private:
    const Mn::Window &mWindow;
    const float kUPS = 60.0f;          // Updates per second
    std::chrono::duration<float, std::milli> kMPF{}; // = 1000.0f / kUPS; // Milliseconds per update.

    // Variables for timing game loop.
    std::chrono::time_point<std::chrono::high_resolution_clock> mPrevTime;
    std::chrono::duration<float, std::milli> mLagTime{};

    // The current loop state (running or should stop)
    bool mLoopRunning = false;
    Scene *mCurrentScene{nullptr};
    int mFrameID = -1;

    // This function loops over draw/update once
    void loopOnce(Mn::Input &input) {
        if (!mLoopRunning) {
            return;
        }
        // Step A: set up for next call to loopOnce
        // mFrameID = requestAnimationFrame(loopOnce);

        // Step B: now let's draw
        //         draw() MUST be called before update()
        //         as update() may stop the loop!
        mCurrentScene->draw();

        // Step C: compute how much time has elapsed since  last loopOnce was executed
        // let currentTime = performance.now();
        const auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = currentTime - mPrevTime;
        mPrevTime = currentTime;
        mLagTime += elapsedTime;

        // Step D: Make sure we update the game the appropriate number of times.
        //      Update only every kMPF (1/60 of a second)
        //      If lag larger than update frames, update until caught up.
        while (mLagTime >= kMPF && mLoopRunning) {
            input.Update();
            mCurrentScene->update(input);
            mLagTime -= kMPF;
        }
    }

};

#endif //BYO2DGE_LOOP_H
