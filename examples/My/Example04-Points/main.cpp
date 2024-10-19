#include "window/Window.h"
#include "window/Input.h"
#include "core/Shader.h"
#include "core/Vbo.h"
#include "core/Vao.h"
#include "graphics/Uniform.h"
#include "Camera.h"
#include <iostream>

glm::vec2 ToWorldCoordinates(Mn::MousePosition mp, const Camera &camera);

struct Point {
    float x{}, y{}, r{}, g{}, b{};
};

class Points {
public:
    // 3 floats for position, 3 for color
    Points() : mPoints(MAX * 6) {}

    void AddPoint(Point point) {
        if (mCurrent >= MAX * 6) {
            std::cerr << "No more room for new points\n";
            return;
        }
        mPoints[mCurrent] = point.x;
        mPoints[mCurrent + 1] = point.y;
        mPoints[mCurrent + 2] = 0.0f;

        mPoints[mCurrent + 3] = point.r;
        mPoints[mCurrent + 4] = point.g;
        mPoints[mCurrent + 5] = point.b;

        mCurrent += 6;
    }

    const std::vector<float> &Data() {
        return mPoints;
    }

    [[nodiscard]] int Count() const {
        return mCurrent / 6;
    }

private:
    const int MAX = 1000;
    int mCurrent{};
    std::vector<float> mPoints;
};


int main() {
    Mn::Window wnd(800, 600, "Points");

    Camera camera{};
    camera.Create({400.0f, 300.0f}, 80, {0, 0, wnd.Width(), wnd.Height()});
    camera.BackgroundColor({0.9f, 0.9f, 0.9f, 1.0f});
    camera.SetViewAndCameraMatrix();

    Points points;
    points.AddPoint({361.0f, 271.0f, 1.0f, 0.0f, 0.0f});
    points.AddPoint({439.0f, 271.0f, 0.0f, 1.0f, 0.0f});
    points.AddPoint({361.0f, 329.0f, 0.0f, 0.0f, 1.0f});
    points.AddPoint({439.0f, 329.0f, 1.0f, 1.0f, 0.0f});

    Mn::Shader shader{"shader/basic.vs.glsl", "shader/basic.fs.glsl"};
    Mn::Uniform uModel{shader.Locate("uModel"), GL_FLOAT_MAT4};
    uModel = glm::mat4{1.0f};
    Mn::Uniform uCamera{shader.Locate("uCamera"), GL_FLOAT_MAT4};
    uCamera = camera.CameraMatrix();

    Mn::Vbo buffer{points.Data(), GL_DYNAMIC_DRAW};

    Mn::Vao vao{true};
    vao.Connect(buffer, 0, 3, 6, 0);
    vao.Connect(buffer, 1, 3, 6, 3);

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
            continue;
        }

        if (input.IsClickedButton(MN_MOUSE_BUTTON_LEFT)) {
            auto mp = input.GetMousePosition();
            glm::vec2 p = ToWorldCoordinates(mp, camera);
            points.AddPoint({p.x, p.y, 0.0f, 0.0f, 0.0f});
            buffer.Load(points.Data());
//            std::cout << mp.x << "/" << wnd.Width() << ", "
//                      << mp.y << "/" << wnd.Height() << "\n";
//            std::cout << "size: " << points.Data().size() << "\n";
//            std::cout << "count: " << points.Count() << std::endl;
        }

        camera.Clear();
        shader.Use();
        uModel.Upload();
        uCamera.Upload();

        glEnable(GL_PROGRAM_POINT_SIZE);
        glPointSize(4.0);
        vao.Draw(GL_POINTS, 0, points.Count());

        wnd.Display();
    }

    return 0;
}

glm::vec2 ToWorldCoordinates(Mn::MousePosition mp, const Camera &camera) {
    glm::vec2 result;

    glm::vec4 viewport = camera.Viewport();
    glm::vec2 worldCenter = camera.WCCenter();
    float worldWidth = camera.WCWidth();
    float worldHeight = camera.WCHeight();

    // Coordinates relative to viewport origin
    float xv = mp.x - viewport.x;
    float yv = mp.y - viewport.y;
    std::cout << "(xv, yv) = (" << xv << ", " << yv << ")\n";

    // Coordinates relative to world dimensions if origin of world is lower left corner
    float xw = (worldWidth / viewport[2]) * xv;
    float yw = (worldHeight / viewport[3]) * yv;
    std::cout << "(xw, yw) = (" << xw << ", " << yw << ")\n";

    // Coordinates if world center is (0,0)
    result.x = xw - worldWidth / 2 + worldCenter.x;
    result.y = yw - worldHeight / 2 + +worldCenter.y;
    std::cout << "result = (" << result.x << ", " << result.y << ")\n";

    return result;
}
