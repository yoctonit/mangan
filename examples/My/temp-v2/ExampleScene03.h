#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_03_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_03_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <core/Shader.h>
#include <core/VAO.h>
#include <core/VBO.h>

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        shader = std::make_shared<Mn::ShaderProgram>("shader/basic.vert", "shader/basic.frag");

        const std::vector<float> vertices{
                -0.5f, -0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.57735f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        buffer = std::make_shared<Mn::VBO>(vertices);

        vao = std::make_shared<Mn::VAO>();
        vao->connect(*buffer, *shader, "a_position", 3, 6, nullptr);
        vao->connect(*buffer, *shader, "a_color", 3, 6, (void *) (sizeof(float) * 3));
    }

    void draw() {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        vao->activate();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void update(const Mn::Input &) {}

    [[nodiscard]] static bool end() {
        return false;
    }

    ~ExampleScene() {
        std::cout << "\nCleanup Scene\n";
        std::cout << "=============\n";
    }

private:
    std::shared_ptr<Mn::ShaderProgram> shader;
    std::shared_ptr<Mn::VAO> vao;
    std::shared_ptr<Mn::VBO> buffer;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_03_H

// Vertex array initialization
//GLuint vertex_array_id;
//glGenVertexArrays(1, &vertex_array_id);
//glBindVertexArray(vertex_array_id);
//
//buffer->activate();
//vertex_pos_location = shader->location("a_position");
//glEnableVertexAttribArray(vertex_pos_location);
//glVertexAttribPointer(vertex_pos_location, 3, GL_FLOAT, GL_FALSE,
//6 * sizeof(GLfloat), nullptr);
//
//vertex_col_location = shader->location("a_color");
//glEnableVertexAttribArray(vertex_col_location);
//glVertexAttribPointer(vertex_col_location, 3, GL_FLOAT, GL_FALSE,
//6 * sizeof(GLfloat), (void *) (sizeof(float) * 3));
