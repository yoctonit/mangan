//
// Created by ivan on 21.5.2020..
//

#include "planet_renderer.h"
#include "core/shader/program_library.h"
#include "core/buffer/buffer_library.h"
#include "core/buffer/vao_library.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void planet_renderer::initialize() {
    mn::program_library& program_lib = mn::program_library::instance();
    program = program_lib.get_program_pointer("ads.vert", "ads.frag");

    std::cout << "========= PLANET ===============\n";
    std::cout << "a_position: " << program->location("a_position") << "\n";
    std::cout << "a_normal: " << program->location("a_normal") << "\n";

    std::cout << "u_light_position: " << program->location("light.u_position") << "\n";
    std::cout << "u_La: " << program->location("light.u_La") << "\n";
    std::cout << "u_Ld: " << program->location("light.u_Ld") << "\n";
    std::cout << "u_Ls: " << program->location("light.u_Ls") << "\n";

    std::cout << "u_Ka: " << program->location("material.u_Ka") << "\n";
    std::cout << "u_Kd: " << program->location("material.u_Kd") << "\n";
    std::cout << "u_Ks: " << program->location("material.u_Ks") << "\n";
    std::cout << "u_shininess: " << program->location("material.u_shininess") << "\n";

    std::cout << "u_model_view_matrix: " << program->location("u_model_view_matrix") << "\n";
    std::cout << "u_normal_matrix: " << program->location("u_normal_matrix") << "\n";
    std::cout << "u_MVP: " << program->location("u_MVP") << "\n";

    std::cout << "program_id: " << program->handle() << "\n";

    mn::vao_library& vao_lib = mn::vao_library::instance();

    std::string name = _icosahedron.name();
    if (vao_lib.has_vertex_array_object(name)) {
        vertex_array_id = vao_lib.get_vertex_array_object(name);
        return;
    }

    std::cout << "not found in vao\n";
    mn::buffer_library& buffer_lib = mn::buffer_library::instance();

    vertex_array_id = vao_lib.create(name);
    std::cout << "vertex_array_id: " << vertex_array_id << "\n";

    std::vector<float> vertices;
    for (auto&& vertex : _icosahedron.vertices()) {
        vertices.push_back(vertex.x);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);
    }

    buffer_lib.create(name + "_vertices", vertices, GL_ARRAY_BUFFER);
    mn::gpu_buffer& vertex_buffer = buffer_lib.get_buffer(name + "_vertices");
    vertex_buffer.activate();

    GLuint a_position = program->location("a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    std::vector<float> normals;
    for (auto&& vertex : _icosahedron.normals()) {
        normals.push_back(vertex.x);
        normals.push_back(vertex.y);
        normals.push_back(vertex.z);
    }

    buffer_lib.create(name + "_normals", normals, GL_ARRAY_BUFFER);
    mn::gpu_buffer& normal_buffer = buffer_lib.get_buffer(name + "_normals");
    normal_buffer.activate();

    GLuint a_normal = program->location("a_normal");
    glEnableVertexAttribArray(a_normal);
    glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindVertexArray(0);
}

void planet_renderer::render(const mn::perspective_camera& camera) const {
    glm::mat4 v = camera.view_matrix();
    glm::mat4 p = camera.projection_matrix();

    glUseProgram(program->handle());

    float scale = _icosahedron.scale();
    glm::mat4 m = glm::translate(_icosahedron.position()) * glm::scale(glm::vec3(scale, scale, scale));
    glm::mat4 mv = v * m;
    glm::mat4 mvp = p * mv;
    glm::mat3 n = glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    n = glm::transpose(glm::inverse(n));

    glm::vec4 lp_world(10.0f, 0.0f, 0.0f, 1.0f); // Light position in world.
    glm::vec4 light_position = v * lp_world; // Light position in eye coords.
    glm::vec3 La(0.4f, 0.4f, 0.4f); // Diffuse light intensity
    glm::vec3 Ld(1.0f, 1.0f, 1.0f); // Diffuse light intensity
    glm::vec3 Ls(1.0f, 1.0f, 1.0f); // Diffuse light intensity

    glm::vec3 Ka(glm::vec3(_icosahedron.color())); // Ambient reflectivity
    glm::vec3 Kd(glm::vec3(_icosahedron.color())); // Diffuse reflectivity
    glm::vec3 Ks(glm::vec3(0.8f, 0.8f, 0.8f)); // Specular reflectivity
    float shininess = 50.0f;

    glUniform4fv(program->location("light.u_position") , 1, glm::value_ptr(light_position));
    glUniform3fv(program->location("light.u_La"), 1, glm::value_ptr(La));
    glUniform3fv(program->location("light.u_Ld"), 1, glm::value_ptr(Ld));
    glUniform3fv(program->location("light.u_Ls"), 1, glm::value_ptr(Ls));

    glUniform3fv(program->location("material.u_Ka"), 1, glm::value_ptr(Ka));
    glUniform3fv(program->location("material.u_Kd"), 1, glm::value_ptr(Kd));
    glUniform3fv(program->location("material.u_Ks"), 1, glm::value_ptr(Ks));
    glUniform1f(program->location("material.u_shininess"), shininess);

    glUniformMatrix4fv(program->location("u_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(mv));
    glUniformMatrix3fv(program->location("u_normal_matrix"), 1, GL_FALSE, glm::value_ptr(n));
    glUniformMatrix4fv(program->location("u_MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_TRIANGLES, 0, _icosahedron.number_of_vertices());
    glBindVertexArray(0);
}
