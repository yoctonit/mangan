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
            glGenBuffers(1, &_id);
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferData(GL_ARRAY_BUFFER, (data.size()) * sizeof(float), data.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            std::cout << "Created buffer with id " << _id << "\n";
        }

//        ~VBO() {
//            std::cout << "Deleted buffer with id " << id << "\n";
//            glDeleteBuffers(1, &_id);
//        }
        void activate() const {
            glBindBuffer(GL_ARRAY_BUFFER, _id);
        }

        [[nodiscard]] unsigned int get() const { return _id; };
        [[nodiscard]] unsigned int id() const { return _id; };

    private:
        unsigned int _id{};
    };

}

#endif //OPENGL_EXAMPLES_VBO_H
