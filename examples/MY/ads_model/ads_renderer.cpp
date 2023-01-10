//
// Created by ivan on 4.5.2020..
//

#include "ads_renderer.h"
#include "core/shader/program_library.h"
#include "core/buffer/buffer_library.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ads_renderer& ads_renderer::instance() {
    static ads_renderer _instance;
    return _instance;
}

void ads_renderer::initialize() {
    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "ads.vert", "ads.frag");
    shader_program_id = program.handle();
    // program.print();

    a_position = program.location("a_position");
    a_normal = program.location("a_normal");

    u_light_position = program.location("light.u_position");
    u_La = program.location("light.u_La");
    u_Ld = program.location("light.u_Ld");
    u_Ls = program.location("light.u_Ls");

    u_Ka = program.location("material.u_Ka");
    u_Kd = program.location("material.u_Kd");
    u_Ks = program.location("material.u_Ks");
    u_shininess = program.location("material.shininess");

    u_model_view_matrix = program.location("u_model_view_matrix");
    u_normal_matrix = program.location("u_normal_matrix");
    u_MVP = program.location("u_MVP");
}

void ads_renderer::add(mn::icosahedron* object) {
    GLuint vertex_array_id;

    std::string name = object->name();
    auto search = _vao_ids.find(name);
    if (search != _vao_ids.end()) {
        std::cout << "Buffers already created\n";

        vertex_array_id = search->second;
        _objects.emplace_back(std::make_pair(object, vertex_array_id));

        return;
    }

    std::cout << "Creating buffers first time for " << name << "\n";

    mn::buffer_library& lib = mn::buffer_library::instance();

    // Vertex array initialization
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    std::cout << "ADS vertex_array_id: " << vertex_array_id << "\n";

    std::vector<float> vertices;
    for (auto&& vertex : object->vertices()) {
        vertices.push_back(vertex.x);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);
    }

    lib.create(name + "vertices", vertices, GL_ARRAY_BUFFER);

    mn::gpu_buffer& vertex_buffer = lib.get_buffer(name + "vertices");
    vertex_buffer.activate();

    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    std::vector<float> normals;
    for (auto&& vertex : object->normals()) {
        normals.push_back(vertex.x);
        normals.push_back(vertex.y);
        normals.push_back(vertex.z);
    }

    lib.create(name + "normals", normals, GL_ARRAY_BUFFER);

    mn::gpu_buffer& normal_buffer = lib.get_buffer(name + "normals");
    normal_buffer.activate();

    glEnableVertexAttribArray(a_normal);
    glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindVertexArray(0);

    _vao_ids.insert({name, vertex_array_id});
    _objects.emplace_back(std::make_pair(object, vertex_array_id));
}

void ads_renderer::render(const mn::perspective_camera& camera) const {
    glm::mat4 v = camera.view_matrix();
    glm::mat4 p = camera.projection_matrix();

    glUseProgram(shader_program_id);

    for (int i = 0; i < _objects.size(); ++i) {
        mn::icosahedron* object = _objects[i].first;

        float scale = object->scale();
        glm::mat4 m = glm::translate(object->position()) * glm::scale(glm::vec3(scale, scale, scale));
        glm::mat4 mv = v * m;
        glm::mat4 mvp = p * mv;
        glm::mat3 n = glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
        n = glm::transpose(glm::inverse(n));

        glm::vec4 lp_world(0.0f, 0.0f, 0.0f, 1.0f); // Light position in world.
        glm::vec4 light_position = v * lp_world; // Light position in eye coords.
        glm::vec3 La(0.4f, 0.4f, 0.4f); // Diffuse light intensity
        glm::vec3 Ld(1.0f, 1.0f, 1.0f); // Diffuse light intensity
        glm::vec3 Ls(1.0f, 1.0f, 1.0f); // Diffuse light intensity

        glm::vec3 Ka(glm::vec3(object->color())); // Ambient reflectivity
        glm::vec3 Kd(glm::vec3(object->color())); // Diffuse reflectivity
        glm::vec3 Ks(glm::vec3(0.8f, 0.8f, 0.8f)); // Specular reflectivity
        float shininess = 50.0f;

        glUniform4fv(u_light_position, 1, glm::value_ptr(light_position));
        glUniform3fv(u_La, 1, glm::value_ptr(La));
        glUniform3fv(u_Ld, 1, glm::value_ptr(Ld));
        glUniform3fv(u_Ls, 1, glm::value_ptr(Ls));

        glUniform3fv(u_Ka, 1, glm::value_ptr(Ka));
        glUniform3fv(u_Kd, 1, glm::value_ptr(Kd));
        glUniform3fv(u_Ks, 1, glm::value_ptr(Ks));
        glUniform1f(u_shininess, shininess);

        glUniformMatrix4fv(u_model_view_matrix, 1, GL_FALSE, glm::value_ptr(mv));
        glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(n));
        glUniformMatrix4fv(u_MVP, 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(_objects[i].second);
        glDrawArrays(GL_TRIANGLES, 0, object->number_of_vertices());
        glBindVertexArray(0);
    }
}
