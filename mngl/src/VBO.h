//
// Created by Ivan on 25-Jan-23.
//

#ifndef OPENGL_EXAMPLES_VBO_H
#define OPENGL_EXAMPLES_VBO_H

#include <glad/glad.h>
#include <vector>
#include <iostream>

namespace Mn {

    class VBO {
    public:
        explicit VBO(const std::vector<float> &data) {
            glGenBuffers(1, &id);
            glBindBuffer(GL_ARRAY_BUFFER, id);
            glBufferData(GL_ARRAY_BUFFER, (data.size()) * sizeof(float), data.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            std::cout << "Created buffer with id " << id << "\n";
        }

//        ~VBO() {
//            std::cout << "Deleted buffer with id " << id << "\n";
//            glDeleteBuffers(1, &id);
//        }
        void activate() const {
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }

        [[nodiscard]] unsigned int get() const { return id; };

    private:
        unsigned int id{};
    };

}
#endif //OPENGL_EXAMPLES_VBO_H
