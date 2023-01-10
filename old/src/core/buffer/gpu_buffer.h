//
// Created by ivan on 26.4.2020..
//

#ifndef INCLUDED_GPU_BUFFER_H
#define INCLUDED_GPU_BUFFER_H

#include <glad/glad.h>
#include <vector>

namespace mn {

    // buffer object (interface to buffer in GPU memory)
    class gpu_buffer {

    public:
        gpu_buffer() = default;

        void create(GLsizeiptr size_, GLenum type_, GLenum usage_ = GL_STATIC_DRAW);
        void create(const std::vector<GLfloat> & data_, GLenum type_, GLenum usage_ = GL_STATIC_DRAW);

        void activate() const { glBindBuffer(_type, _id); }

        int load_data(const std::vector<GLfloat> & data);
        int load_data(GLsizeiptr data_count, const GLfloat *data);
        // void LoadDataAtOffset(unsigned offset, const std::vector<GLfloat> & data);
        void load_data_at_offset(GLintptr offset, GLsizeiptr data_size, const GLfloat * data) const;

        [[nodiscard]] GLuint handle() const { return _id; };

    private:
        GLuint _id;
        GLenum _type;
        GLenum _usage;
        GLsizeiptr _size;

        GLintptr _top; // next free byte position in buffer
    };

}

#endif //INCLUDED_GPU_BUFFER_H
