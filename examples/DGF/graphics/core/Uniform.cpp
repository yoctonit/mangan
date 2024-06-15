#include <iostream>
#include "Uniform.h"

// get and store reference for program variable with given name
GLint Uniform::locate(GLuint programRef, const std::string &variableName) {
    GLint variableRef = glGetUniformLocation(programRef, variableName.c_str());
    if (variableRef == -1) {
        std::cerr << "Uniform variable " << variableName << " not found.\n";
    }
    return variableRef;
}
