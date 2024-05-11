#ifndef EXAMPLES_POINTS_SCENE_H
#define EXAMPLES_POINTS_SCENE_H

#include "window/Input.h"
#include "core/Shader.h"
#include "core/Buffer.h"
#include "core/Vao.h"
#include "Point.h"
#include "Camera.h"

#include <vector>


class PointsScene {
public:

    void Initialize(int window_width, int window_height);

    void Release();

    void Draw() const;

    void Update(const Mn::Input &input);

    [[nodiscard]] bool ShouldClose() const;

    void AddPoint(Point point);

private:
    bool should_close_{};
    Mn::ShaderProgram shader_{};
    Mn::Buffer buffer_{};
    Mn::Vao vao_{};

    float window_width_;
    float window_height_;
    Camera camera_{};

    std::vector<float> points_;
};

#endif //EXAMPLES_POINTS_SCENE_H
