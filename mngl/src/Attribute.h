//
// Created by ivan on 10.1.2023..
//

#ifndef INCLUDED_MN_UNIFORM_H
#define INCLUDED_MN_UNIFORM_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Mn::Shader
{

    class Attribute
    {
    public:
        Attribute(std::vector<float> data) :  _data{data}
        {
            // reference of available buffer from GPU
            glGenBuffers(1, &_bufferRef);

            // upload data immediately
            // upload();
        };

        void upload(){
                        // select buffer used by the following functions
            glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

            // store data in currently bound buffer
            auto dataSizeInBytes = static_cast<GLsizeiptr>(_data.size() * sizeof(GLfloat));
            glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, _data.data(), GL_STATIC_DRAW);

            // deactivate buffer
            // glBindBuffer(GL_ARRAY_BUFFER, 0);

        };

        virtual void associateVariable(GLuint programRef, const std::string &variableName) = 0;

    protected:
        GLuint _bufferRef{};
        std::vector<float> _data;
    };


    class AttributeVector3 : public Attribute
    {
    public:

        // associate variable in program with this buffer
        void associateVariable(GLuint programRef, const std::string &variableName) override
        {
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
    };

}

#endif // INCLUDED_MN_UNIFORM_H
