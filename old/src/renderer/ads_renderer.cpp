//
// Created by ivan on 4.5.2020..
//

#include "ads_renderer.h"
#include "core/shader/program_library.h"
#include "core/buffer/buffer_library.h"
#include "core/buffer/vao_library.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace mn {
    ads_renderer& ads_renderer::instance() {
        static ads_renderer _instance;
        return _instance;
    }

    void ads_renderer::initialize() {
        program_library& program_lib = program_library::instance();
        program = program_lib.get_program_pointer(
                "ads.vert", "ads.frag");
    }

    void ads_renderer::add(model* m) {
        if(program == nullptr) {
            std::cout << "ADS renderer not initialized\n";
            return;
        }

        vao_library& vao_lib = vao_library::instance();

        std::string name = m->name();
        GLuint vertex_array_id;

        if (vao_lib.has_vertex_array_object(name)) {
            std::cout << "Buffer already created for " << name << "\n";
            vertex_array_id = vao_lib.get_vertex_array_object(name);
            _objects.emplace_back(std::make_pair(m, vertex_array_id));
            return;
        }

        std::cout << "Creating buffers first time for " << name << "\n";

        buffer_library& buffer_lib = buffer_library::instance();

        vertex_array_id = vao_lib.create(name);
        std::cout << "ADS Renderer vertex_array_id: " << vertex_array_id << "\n";

//        std::vector<float> vertices;
//        for (auto&& vertex : m->vertices()) {
//            vertices.push_back(vertex.x);
//            vertices.push_back(vertex.y);
//            vertices.push_back(vertex.z);
//        }

        // buffer_lib.create(name + "_vertices", vertices, GL_ARRAY_BUFFER);

        const std::vector<glm::vec3>& vert = m->vertices();
        buffer_lib.create(name + "_vertices", glm::value_ptr(vert[0]), vert.size() * 3, GL_ARRAY_BUFFER);

        gpu_buffer& vertex_buffer = buffer_lib.get_buffer(name + "_vertices");
        vertex_buffer.activate();

        GLuint a_position = program->location("a_position");
        glEnableVertexAttribArray(a_position);
        glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

//        std::vector<float> normals;
//        for (auto&& vertex : m->normals()) {
//            normals.push_back(vertex.x);
//            normals.push_back(vertex.y);
//            normals.push_back(vertex.z);
//        }

        const std::vector<glm::vec3>& norm = m->normals();
        buffer_lib.create(name + "_normals", glm::value_ptr(norm[0]), norm.size() * 3, GL_ARRAY_BUFFER);

        // buffer_lib.create(name + "_normals", normals, GL_ARRAY_BUFFER);
        gpu_buffer& normal_buffer = buffer_lib.get_buffer(name + "_normals");
        normal_buffer.activate();

        GLuint a_normal = program->location("a_normal");
        glEnableVertexAttribArray(a_normal);
        glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindVertexArray(0);

        _objects.emplace_back(std::make_pair(m, vertex_array_id));
    }

    void ads_renderer::render(const mn::perspective_camera& camera, const point_light& light) const {
        glm::mat4 v = camera.view_matrix();
        glm::mat4 p = camera.projection_matrix();

        glUseProgram(program->handle());

        // for (int i = 0; i < _objects.size(); ++i) {
        for (const std::pair<model*, GLuint> &element : _objects ) {
            // model* object = _objects[i].first;
            model* object = element.first;

            glm::mat4 m = object->transform();
            glm::mat4 mv = v * m;
            glm::mat4 mvp = p * mv;
            glm::mat3 n = glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
            n = glm::transpose(glm::inverse(n));

            // material properties
            glm::vec3 Ka(glm::vec3(1.0f, 0.0f, 0.0f)); // Ambient reflectivity
            glm::vec3 Kd(glm::vec3(1.0f, 0.0f, 0.0f)); // Diffuse reflectivity
            glm::vec3 Ks(glm::vec3(0.8f, 0.8f, 0.8f)); // Specular reflectivity
            float shininess = 50.0f;

            glm::vec4 light_position = v * light.position(); // Light position in eye coords.

            glUniform4fv(program->location("u_light.position") , 1, glm::value_ptr(light_position));
            glUniform3fv(program->location("u_light.La"), 1, glm::value_ptr(light.ambient()));
            glUniform3fv(program->location("u_light.Ld"), 1, glm::value_ptr(light.diffuse()));
            glUniform3fv(program->location("u_light.Ls"), 1, glm::value_ptr(light.specular()));

            glUniform3fv(program->location("u_material.Ka"), 1, glm::value_ptr(Ka));
            glUniform3fv(program->location("u_material.Kd"), 1, glm::value_ptr(Kd));
            glUniform3fv(program->location("u_material.Ks"), 1, glm::value_ptr(Ks));
            glUniform1f(program->location("u_material.shininess"), shininess);

            glUniformMatrix4fv(program->location("u_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(mv));
            glUniformMatrix3fv(program->location("u_normal_matrix"), 1, GL_FALSE, glm::value_ptr(n));
            glUniformMatrix4fv(program->location("u_MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

            // glBindVertexArray(_objects[i].second);
            glBindVertexArray(element.second);
            glDrawArrays(GL_TRIANGLES, 0, object->number_of_vertices());
            glBindVertexArray(0);
        }
    }

}

//        std::cout << "========= PLANET ===============\n";
//        std::cout << "a_position: " << program->location("a_position") << "\n";
//        std::cout << "a_normal: " << program->location("a_normal") << "\n";
//
//        std::cout << "u_light_position: " << program->location("u_light.position") << "\n";
//        std::cout << "u_La: " << program->location("u_light.La") << "\n";
//        std::cout << "u_Ld: " << program->location("u_light.Ld") << "\n";
//        std::cout << "u_Ls: " << program->location("u_light.Ls") << "\n";
//
//        std::cout << "u_Ka: " << program->location("u_material.Ka") << "\n";
//        std::cout << "u_Kd: " << program->location("u_material.Kd") << "\n";
//        std::cout << "u_Ks: " << program->location("u_material.Ks") << "\n";
//        std::cout << "u_shininess: " << program->location("u_material.shininess") << "\n";
//
//        std::cout << "u_model_view_matrix: " << program->location("u_model_view_matrix") << "\n";
//        std::cout << "u_normal_matrix: " << program->location("u_normal_matrix") << "\n";
//        std::cout << "u_MVP: " << program->location("u_MVP") << "\n";
//
//        std::cout << "program_id: " << program->handle() << "\n";
