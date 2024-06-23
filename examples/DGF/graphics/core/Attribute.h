#ifndef DGF_GRAPHICS_CORE_ATTRIBUTE_H
#define DGF_GRAPHICS_CORE_ATTRIBUTE_H

#include <glad/glad.h>
#include <string>
#include <vector>

class Attribute {
public:
    enum class Type {
        Int, Float, Vec2, Vec3, Vec4
    };

    Attribute();

    Attribute(Type dataType, std::vector<GLfloat> data);

    void uploadData();

    void uploadData(std::vector<GLfloat> data);

    std::vector<GLfloat> &getData();

    void associateVariable(GLuint programRef, const std::string &variableName) const;

private:
    // type of elements in data array
    Type m_dataType{};

    // *flattened* array of data to be stored in buffer
    std::vector<GLfloat> m_data;

    // reference of available buffer from GPU
    GLuint m_bufferRef{};
};

#endif //DGF_GRAPHICS_CORE_ATTRIBUTE_H
