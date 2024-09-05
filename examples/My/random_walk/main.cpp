//
// Created by ivan on 6.5.2020..
//

//#include "glad/glad.h"
//#include "core/window/gl_window.h"
//#include "core/shader/program_library.h"
//#include "core/buffer/gpu_buffer.h"
//#include <random>
//
//const int width = 640;
//const int height = 640;
//
//mn::gpu_buffer buffer;
//
//GLint shader_program_id;
//GLint vertex_pos_location;
//
//std::random_device rd; // obtain a random number from hardware
//std::mt19937 eng(rd()); // seed the generator
//// std::uniform_real_distribution<> distribution(0.0f, 2.0f);
//std::uniform_int_distribution<> distribution(0, 2); // define the range
//
////class Walker {
////public:
////    Walker(int x, int y) : _x(x), _y(y) {}
////    void step();
////
////private:
////    int _x;
////    int _y;
////};
////
////void Walker::step() {
////    _x += 1;
////}
//
//int x = 0;
//int y = 0;
//
//void setup() {
//    mn::program_library& lib = mn::program_library::instance();
//    mn::shader_program& program = lib.get_program(
//            "basic.vert", "basic.frag");
//
//    shader_program_id = program.handle();
//    vertex_pos_location = program.location("a_position");
//
//    // Vertex array initialization
//    GLuint vertex_array_id;
//    glGenVertexArrays(1, &vertex_array_id);
//    glBindVertexArray(vertex_array_id);
//
//    buffer.create(2 * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
//    buffer.activate();
//
//    glEnableVertexAttribArray(vertex_pos_location);
//    glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
//
//    glViewport(0, 0, width, height);
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void update(double, const mn::input&) {
//    float data[2];
//
//    // pick displacement in both direction
//    int dist_x = distribution(eng) - 1.0;
//    int dist_y = distribution(eng) - 1.0;
//    x += dist_x;
//    y += dist_y;
//
//    float half_width = 0.5f * width;
//    float half_height = 0.5f * height;
//    data[0] = float(x) / half_width;
//    data[1] = float(y) / half_height;
//
//    buffer.load_data_at_offset(0, 2 * sizeof(GLfloat), data);
//}
//
//void draw() {
//    glUseProgram(shader_program_id);
//    glDrawArrays(GL_POINTS, 0, 1);
//}
//
//int main()
//{
//    mn::gl_window& window = mn::gl_window::instance();
//
//    if (!window.create(width, height, "Triangle", 4, 6)) {
//        window.clean_up();
//        return 1;
//    }
//
//    window.set_setup(setup);
//    window.set_update(update);
//    window.set_draw(draw);
//
//    window.action();
//
//    return 0;
//}
//
//#include <random>
//
//#include "bitmap_scene.h"
//
//
//const int WIDTH = 640;
//const int HEIGHT = 640;
//
//
//class Walker : public bitmap_scene {
//public:
//    Walker(int width, int height, float x, float y)
//    : bitmap_scene(width, height), _x(x), _y(y), eng((std::random_device())()), distribution(0, 2) {}
//
//    void step();
//    void update(double seconds, const mn::input& user_input) override;
//    void draw() override;
//    void initialize() override;
//
//private:
//    float _x;
//    float _y;
//
//    // std::random_device rd; // obtain a random number from hardware
//    // std::mt19937 eng(rd()); // seed the generator
//    std::mt19937 eng; // seed the generator
//    std::uniform_int_distribution<> distribution; // define the range
//    // std::uniform_real_distribution<> distribution(0.0f, 2.0f);
//};
//
//void Walker::step() {
//    // pick displacement in both direction: -1, 0 or 1
//    float dist_x = distribution(eng) - 1.0f;
//    float dist_y = distribution(eng) - 1.0f;
//
//    _x += dist_x;
//    _y += dist_y;
//}
//
//void Walker::initialize() {
//    glViewport(0, 0, _width, _height);
//    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void Walker::update(double seconds, const mn::input& user_input) {
//    step();
//}
//
//void Walker::draw() {
//    pixel(_x, _y);
//}
//
//
//int main()
//{
//    Walker walker(WIDTH, HEIGHT, 0.5f * WIDTH, 0.5f * HEIGHT);
//
//    walker.run();
//
//    return 0;
//}

#include <random>
#include "core/window/gl_window.h"
#include "util/canvas.h"
#include <iostream>

const int WIDTH = 640;
const int HEIGHT = 640;

class Walker {
public:
    Walker(float x, float y)
    : _x(x), _y(y), eng((std::random_device())()), distribution(0, 2) {}

    void step();
    void draw(mn::canvas& ctx);

private:
    float _x;
    float _y;

    std::mt19937 eng; // seed the generator
    std::uniform_int_distribution<> distribution; // define the range
};

void Walker::step() {
    // pick displacement in both direction: -1, 0 or 1
    float dist_x = distribution(eng) - 1.0f;
    float dist_y = distribution(eng) - 1.0f;

    _x += dist_x;
    _y += dist_y;
}

void Walker::draw(mn::canvas& ctx) {
    step();
    ctx.pixel(_x, _y);
}

int main() {
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(WIDTH, WIDTH, "Random walk",4, 6)) {
        window.clean_up();
        return 1;
    }

    mn::canvas ctx(window.width(), window.height());

    Walker walker(0.5f * WIDTH, 0.5f * HEIGHT);

    window.set_setup([&ctx] () { ctx.clear(glm::vec4(0.1f, 0.1f, 0.8f, 1.0f)); });
    window.set_draw( [&walker, &ctx] () { walker.draw(ctx); } );

    // window.action_test();
    window.action();

    return 0;
}
