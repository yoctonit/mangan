#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple> // for std::ignore
#include <vector>

#include "Shader.h"

namespace Mn {

    std::unordered_map<unsigned int, int> Shader::mRefCnt{};

    Shader::Shader() = default;

    Shader::Shader(
            const std::string &vertexShaderFile,
            const std::string &fragmentShaderFile
    ) {
        std::string vertexShaderSource = LoadFile(vertexShaderFile);
        unsigned int vertexShaderId = Compile(vertexShaderSource, GL_VERTEX_SHADER);

        std::string fragmentShaderSource = LoadFile(fragmentShaderFile);
        unsigned int fragmentShaderId = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

        mId = Link(vertexShaderId, fragmentShaderId);
        IncRef();
        std::cout << "Created Shader with id " << mId << "\n";
    }

    Shader::~Shader() {
        int refCnt = DecRef();
        if (refCnt == 0) {
            glDeleteProgram(mId);
            std::cout << "Deleted Shader with id " << mId << "\n";
        }
    }

    // copy constructor
    Shader::Shader(const Shader &other) {
        mId = other.mId;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    Shader &Shader::operator=(const Shader &other) {
        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "Shader self assignment detected.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "Shader assignment with same id detected.\n";
            return *this;
        }
        if (mId != 0) {
            std::ignore = DecRef();
        }
        mId = other.mId;
        IncRef();
        return *this;
    }

    unsigned int Shader::Id() const {
        return mId;
    }

    void Shader::Use() const {
        glUseProgram(mId);
    }

    int Shader::Locate(const std::string &name) const {
        int uniformRef = glGetUniformLocation(mId, name.c_str());
        if (uniformRef != -1) {
            return uniformRef;
        }

        int attributeRef = glGetAttribLocation(mId, name.c_str());
        if (attributeRef != -1) {
            return attributeRef;
        }

        std::cerr << "Uniform/attribute " << name << " not found.\n";
        return -1;
    }

//    [[nodiscard]] int Shader::LocateAttribute(const std::string &attributeName) const {
//        int variableRef = glGetAttribLocation(mId, attributeName.c_str());
//        if (variableRef == -1) {
//            std::cerr << "Attribute " << attributeName << " not found.\n";
//        }
//        return variableRef;
//    }

    void Shader::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << mId << "\n";
    }

//    Shader Shader::FromFiles(const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
//        std::string vertexShaderSource = LoadFile(vertexShaderFile);
//        unsigned int vertexShaderId = Compile(vertexShaderSource, GL_VERTEX_SHADER);
//
//        std::string fragmentShaderSource = LoadFile(fragmentShaderFile);
//        unsigned int fragmentShaderId = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);
//
//        Shader shader;
//        shader.mId = Link(vertexShaderId, fragmentShaderId);
//        std::cout << "Created Shader with id " << shader.mId << "\n";
//        return shader;
//    }

    unsigned int Shader::Compile(const std::string &shaderSource, GLenum shaderType) {
        unsigned int shaderId = glCreateShader(shaderType);

        // Send the shader source code to GL.
        // Note that std::string's .c_str is NULL character terminated.
        auto source = (const GLchar *) shaderSource.c_str();
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shaderId anymore.
            glDeleteShader(shaderId);
            shaderId = 0;

            // Convert the infoLog to string
            std::ostringstream errorMessage;
            for (GLchar c: infoLog) {
                errorMessage << c;
            }

            std::cerr << "Compile shader error: " << errorMessage.str() << "\n";
        }
        return shaderId;
    }

    unsigned int Shader::Link(unsigned int vertexShaderId, unsigned int fragmentShaderId) {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Create empty program object and store reference to it.
        unsigned int programId = glCreateProgram();

        // Attach previously compiled shader programs
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);

        // Link vertex shader to fragment shader
        glLinkProgram(programId);

        // Queries whether program link was successful
        GLint linkSuccess;
        glGetProgramiv(programId, GL_LINK_STATUS, &linkSuccess);

        if (linkSuccess == GL_FALSE) {
            GLint infoLogLength = 0;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

            // The infoLogLength includes the NULL character
            std::vector<GLchar> infoLog(infoLogLength);
            glGetProgramInfoLog(programId, infoLogLength, &infoLogLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(programId);
            programId = 0;
            // Don't leak shaders either.
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);

            // Convert the infoLog to string
            std::ostringstream errorMessage;
            for (GLchar c: infoLog) {
                errorMessage << c;
            }

            std::cerr << "Link shader error: " << errorMessage.str() << "\n";
            return programId;
            // Failed linking, raise exception
            // throw std::runtime_error("Shader link error: " + errorMessage.str());
        }

        // Always detach shaders after a successful link.
        glDetachShader(programId, vertexShaderId);
        glDetachShader(programId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        // linking was successful; return program reference value
        return programId;
    }

    /*
     * Read contents of the file as string
     * @param [in] fileName - Path to the file
     * @param [out] - On successful read file contents, on failed read empty string;
     */
    std::string Shader::LoadFile(const std::string &fileName) {
        std::ifstream fileStream(fileName, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "Could not open " << fileName << "\n";
            return ""; // throw exception?
        }

        std::stringstream str;
        str << fileStream.rdbuf();

        fileStream.close();
        return str.str();
    }

    void Shader::IncRef() const {
        // objects with mId = 0 are 'empty' (non-initialized) objects,
        // so don't note their existence in mRefCnt map
        if (mId == 0) {
            return;
        }
        mRefCnt[mId]++;
    }

    [[nodiscard]] int Shader::DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "Shader: called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }

    void Shader::DebugRefCnt() {
        if (mRefCnt.empty()) {
            std::cout << "RefCnt: <empty>\n";
            return;
        }
        std::cout << "RefCnt:\n";
        for (auto &refCnt: mRefCnt) {
            std::cout << "Id " << refCnt.first << " (cnt=" << refCnt.second << ")\n";
        }
    }

}
