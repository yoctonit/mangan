//
// Created by ivan on 26.4.2020..
//

#include "gpu_buffer.h"
#include <stdexcept>

namespace mn {

    /*
     * Create object that contains info about buffer in GPU memory: id, size,...
     * @param {unsigned} size Size of buffer in bytes
     * @param {GLenum} type Type of buffer: GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
     * @param {GLenum} usage Usage hint for buffer: GL_STATIC_DRAW, GL_DYNAMIC_DRAW,...
     */
    void gpu_buffer::create(GLsizeiptr size_, GLenum type_, GLenum usage_) {
        _size = size_;
        _type = type_;
        _usage = usage_;

        _id = 0; // buffer id in the opengl context
        _top = 0; // next free byte position in buffer

        glGenBuffers(1, &_id); // Generate 1 buffer, put the resulting identifier in _id
        glBindBuffer(_type, _id); // Activate buffer
        glBufferData(_type, _size, nullptr, _usage); // Reserve size in bytes
        glBindBuffer(_type, 0); // Deactivate buffer
    }

    void gpu_buffer::create(const std::vector<GLfloat> & data_, GLenum type_, GLenum usage_) {
        _size = data_.size() * sizeof(GLfloat); // size of buffer in bytes
        _type = type_;
        _usage = usage_;

        _id = 0; // buffer id in the opengl context
        _top = 0; // next free byte position in buffer

        glGenBuffers(1, &_id); // Generate 1 buffer, put the resulting identifier in _id
        glBindBuffer(_type, _id); // Activate buffer
        glBufferData(_type, _size, data_.data(), _usage); // Reserve size in bytes and put data
        glBindBuffer(_type, 0); // Deactivate buffer
    }

    /*
     * Load data to OpenGL buffer
     * @returns {int} Offset at which data is loaded
     */
    int gpu_buffer::load_data(const std::vector<GLfloat> & data_) {
        GLintptr offset = _top;
        GLsizeiptr data_size = data_.size() * sizeof(GLfloat); // in bytes

        if ((_top + data_size) > _size) {
            throw std::invalid_argument( "No more space in buffer.");
        }

        glBindBuffer(_type, _id); // Activate vertex buffer
        glBufferSubData(_type, _top, data_size, data_.data()); // Load data into the buffer
        glBindBuffer(_type, 0); // Deactivate buffer

        _top += data_size; // advance position of next free byte
        return offset;
    }

    /*
     * Load data to OpenGL buffer
     * @returns {int} Offset at which data is loaded
     */
    int gpu_buffer::load_data(GLsizeiptr data_count, const GLfloat *data) {
        GLintptr offset = _top;
        GLsizeiptr data_size = data_count * sizeof(GLfloat); // in bytes

        if ((_top + data_size) > _size) {
            throw std::invalid_argument( "No more space in buffer.");
        }

        glBindBuffer(_type, _id); // Activate vertex buffer
        glBufferSubData(_type, _top, data_size, data); // Load data into the buffer
        glBindBuffer(_type, 0); // Deactivate buffer

        _top += data_size; // advance position of next free byte
        return offset;
    }

    void gpu_buffer::load_data_at_offset(GLintptr offset, GLsizeiptr data_size, const GLfloat * data) const {
        if ((offset + data_size) > _size) {
            throw std::invalid_argument( "No more space in buffer.");
        }

        glBindBuffer(_type, _id); // Activate vertex buffer
        glBufferSubData(_type, offset, data_size, data); // Loads data into the buffer
        glBindBuffer(_type, 0); // Deactivate buffer
    }

}
