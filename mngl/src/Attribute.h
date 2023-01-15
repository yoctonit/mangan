//
// Created by ivan on 10.1.2023..
//

#ifndef INCLUDED_MN_ATTRIBUTE_H
#define INCLUDED_MN_ATTRIBUTE_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Mn::Shader {

    class Attribute {
    public:
        explicit Attribute() {
            // reference of available buffer from GPU
            glGenBuffers(1, &_bufferRef);

            // upload data immediately
            // upload();
        };

//        virtual void upload() = 0;

        virtual void associateVariable(GLuint programRef, const std::string &variableName) = 0;


    protected:
        GLuint _bufferRef{};
    };

    class AttributeVector3 : public Attribute {
    public:
        explicit AttributeVector3(const std::vector<float> &data) : Attribute{} {
            // reference of available buffer from GPU
//            glGenBuffers(1, &_bufferRef);

            // upload data immediately
            // upload();
            // select buffer used by the following functions
            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

            // store data in currently bound buffer
            auto dataSizeInBytes = static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat));
            glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, data.data(), GL_STATIC_DRAW);

            // deactivate buffer
            // glBindBuffer(GL_ARRAY_BUFFER, 0);
        };

//        void upload() {
//            // select buffer used by the following functions
//            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);
//
//            // store data in currently bound buffer
//            auto dataSizeInBytes = static_cast<GLsizeiptr>(_data.size() * sizeof(GLfloat));
//            glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, _data.data(), GL_STATIC_DRAW);
//
//            // deactivate buffer
//            // glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        };
        // associate variable in program with this buffer
        void associateVariable(GLuint programRef, const std::string &variableName) override {
            // get reference for program variable with given name
            GLint variableRef = glGetAttribLocation(programRef, variableName.c_str());

            // if the program does not reference the variable, then exit
            if (variableRef == -1)
                return;

            // select buffer used by the following functions
            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

            glVertexAttribPointer(variableRef, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            // indicate that data will be streamed to this variable
            glEnableVertexAttribArray(variableRef);
        }
//    private:
//        std::vector<float> _data;
    };

    class AttributeVector2 : public Attribute {
    public:
        explicit AttributeVector2(const std::vector<float> &data) : Attribute{} {
            // reference of available buffer from GPU
//            glGenBuffers(1, &_bufferRef);

            // upload data immediately
            // upload();
            // select buffer used by the following functions
            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

            // store data in currently bound buffer
            auto dataSizeInBytes = static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat));
            glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, data.data(), GL_STATIC_DRAW);

            // deactivate buffer
            // glBindBuffer(GL_ARRAY_BUFFER, 0);
        };

//        void upload() {
//            // select buffer used by the following functions
//            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);
//
//            // store data in currently bound buffer
//            auto dataSizeInBytes = static_cast<GLsizeiptr>(_data.size() * sizeof(GLfloat));
//            glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, _data.data(), GL_STATIC_DRAW);
//
//            // deactivate buffer
//            // glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        };
        // associate variable in program with this buffer
        void associateVariable(GLuint programRef, const std::string &variableName) override {
            // get reference for program variable with given name
            GLint variableRef = glGetAttribLocation(programRef, variableName.c_str());

            // if the program does not reference the variable, then exit
            if (variableRef == -1)
                return;

            // select buffer used by the following functions
            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

            glVertexAttribPointer(variableRef, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            // indicate that data will be streamed to this variable
            glEnableVertexAttribArray(variableRef);
        }
//    private:
//        std::vector<float> _data;
    };

}

#endif // INCLUDED_MN_ATTRIBUTE_H
