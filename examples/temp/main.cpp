#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <iostream>

void printMat4(const glm::mat4& m) {
    const float* data = glm::value_ptr(m);
    for (int i = 0; i<16; ++i) {
        std::cout << data[i] << " ";
        if (i%4 == 3) std::cout << "\n";
    }
    std::cout << "\n";
}

void setPosition(glm::mat4& m, glm::vec3 position) {
//    float *p = glm::value_ptr(m);
//    p[12] = position.x;
//    p[13] = position.y;
//    p[14] = position.z;
m = glm::column(m, 3, glm::vec4(position, 1.0f));
//        transform.values[0][3] = position.values[0];
//        transform.values[1][3] = position.values[1];
//        transform.values[2][3] = position.values[2];
}

void printVec3(const glm::vec3& v) {
    std::cout << v.x << " " << v.y << " " << v.z << "\n\n";
}

glm::vec3 getPosition(const glm::mat4& m) {
    const float *p = glm::value_ptr(m);
//    return {p[12], p[13], p[14]};
    return {glm::column(m, 3)};
//        return new glm::vec3(
//                transform.values[0][3],
//                transform.values[1][3],
//                transform.values[2][3]);
}

int main() {
    glm::mat4 m{1.0f};
    printMat4(m);

    m = glm::translate(glm::vec3(1.0f, 2.0f, 3.0f));
    printMat4(m);

    printVec3(getPosition(m));

    setPosition(m, glm::vec3(7.0f, 8.0f, 9.0f));
    printMat4(m);
    printVec3(getPosition(m));
    return 0;
}
//#include "core/run.h"
//#include "core/shader.h"
//#include "core/buffer/gpu_buffer.h"
//#include <iostream>
//
//class Triangle {
//public:
//    Triangle() :
//            shader_program_id(0), /* vertex_pos_location(0), vertex_col_location(0), */ buffer() {
//        std::cout << "Triangle() " << (long long) this << "\n";
//    }
//
//    ~Triangle() { std::cout << "~Triangle() " << (long long) this << "\n"; }
//
//    void initialize(int width, int height) {
//        std::cout << "initialize triangle\n";
//
//        shader_program_id = Mn::Shader::CreateFromFiles("shader/basic.vert", "shader/basic.frag");
//
//        // Vertex array initialization
//        GLuint vertex_array_id;
//        glGenVertexArrays(1, &vertex_array_id);
//        glBindVertexArray(vertex_array_id);
//
//        // first 3 element specify coordinates, and next 3 color of one vertex
//        const std::vector<float> vertices{
//                -0.5f, -0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
//                0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
//                0.0f, 0.57735f, 0.0f, 0.0f, 0.0f, 1.0f
//        };
//        buffer.create(vertices, GL_ARRAY_BUFFER);
//        buffer.activate();
//
//        GLuint vertex_pos_location = Mn::Shader::Location(shader_program_id, "a_position");
//        glEnableVertexAttribArray(vertex_pos_location);
//        glVertexAttribPointer(vertex_pos_location, 3, GL_FLOAT, GL_FALSE,
//                              6 * sizeof(GLfloat), nullptr);
//
//        GLuint vertex_col_location = Mn::Shader::Location(shader_program_id, "a_color");
//        glEnableVertexAttribArray(vertex_col_location);
//        glVertexAttribPointer(vertex_col_location, 3, GL_FLOAT, GL_FALSE,
//                              6 * sizeof(GLfloat), (void *) (sizeof(float) * 3));
//        glViewport(0, 0, width, height);
//    }
//
//    void draw() const {
//        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shader_program_id);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//    }
//
//    void cleanup() {
//        std::cout << "cleanup triangle\n";
//        glUseProgram(0);
//    }
//
//private:
//    GLuint shader_program_id;
////    GLuint vertex_pos_location;
////    GLuint vertex_col_location;
//    mn::gpu_buffer buffer;
//};
//
//int main() {
//    Mn::Window window(800, 800, "Triangle");
//    Triangle scene;
//    Mn::RunStatic<Triangle>(scene, window);
//    return 0;
//}
