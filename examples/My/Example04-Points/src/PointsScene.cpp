#include "PointsScene.h"
#include "Util.h"
// #include <iostream>

void PointsScene::Initialize(int window_width, int window_height) {
    window_width_ = static_cast<float>(window_width);
    window_height_ = static_cast<float>(window_height);

    shader_ = Mn::ShaderProgram::CreateFromFiles("shader/basic.vs", "shader/basic.fs");

    AddPoint({10.0f, 10.0f, 1.0f, 0.0f, 0.0f});
    AddPoint({-10.0f, 10.0f, 0.0f, 1.0f, 0.0f});
//    buffer_.Create(points_);
    buffer_.Create(1000, GL_DYNAMIC_DRAW);

    vao_.Create();
    vao_.Connect(buffer_, shader_, "a_position", 3, 6, nullptr);
    vao_.Connect(buffer_, shader_, "a_color", 3, 6, (GLvoid *) (3 * sizeof(GLfloat)));

    camera_.Create({-800.0f, -600.0f}, 80, {0, 0, window_width_, window_height_});
    camera_.BackgroundColor({0.9f, 0.9f, 0.9f, 1.0f});
    camera_.SetViewAndCameraMatrix();
}

void PointsScene::Release() {
    shader_.Release();
    buffer_.Release();
    vao_.Release();
}

void PointsScene::Draw() const {
    camera_.Clear();

    shader_.Use();
    glm::mat4 matrix{1.0f};
    Mn::ShaderProgram::Uniform(shader_.UniformLocation("u_model_matrix"), matrix);
    Mn::ShaderProgram::Uniform(shader_.UniformLocation("u_camera_matrix"), camera_.CameraMatrix());

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(4.0);
    int cnt = static_cast<int>(points_.size() / 6);
    vao_.Draw(GL_POINTS, 0, cnt);
}

void PointsScene::Update(const Mn::Input &input) {
    if (input.IsClickedKey(Mn::Input::Key::esc)) {
        should_close_ = true;
    }
    Mn::Input::MousePosition mp = input.Position();
    if (input.IsClickedButton(Mn::Input::Button::left)) {
        // AddPoint({mp.x, mp.y, 0.2f, 0.2f, 0.2f});
        // int cnt = static_cast<int>(points_.size() / 6);
        glm::vec2 p = ToWorldCoordinates(mp, camera_);
        AddPoint({p.x, p.y, 0.2f, 0.2f, 0.2f});
        // std::cout << mp.x << "/" << mp.window_size_x << ", "
        //           << mp.y << "/" << mp.window_size_y << "\n";
        // std::cout << cnt << std::endl;
    }
    buffer_.Load(points_);
}

[[nodiscard]] bool PointsScene::ShouldClose() const {
    return should_close_;
}

void PointsScene::AddPoint(Point point) {
    points_.push_back(point.x);
    points_.push_back(point.y);
    points_.push_back(0.0f);
    points_.push_back(point.r);
    points_.push_back(point.g);
    points_.push_back(point.b);
}
