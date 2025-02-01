#ifndef INCLUDED_MN_CORE_VBO_H
#define INCLUDED_MN_CORE_VBO_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Mn {

    class Vbo {
    public:
        Vbo();

        explicit Vbo(const std::vector<float> &data, GLenum type = GL_STATIC_DRAW);

        Vbo(const float* data, int size, GLenum type = GL_STATIC_DRAW);

        ~Vbo();

        Vbo(const Vbo &other);

        Vbo &operator=(const Vbo &other);

        [[nodiscard]] unsigned int Id() const;

        void Activate() const;

        void Load(const std::vector<float> &data) const;

        void Debug(const std::string &msg) const;

        static void DebugRefCnt();

    private:
        unsigned int mId{};

        //////////////////////
        // Reference count map
        //////////////////////
        static std::unordered_map<unsigned int, int> mRefCnt;

        void IncRef() const;

        [[nodiscard]] int DecRef() const;
    };

}

#endif //INCLUDED_MN_CORE_VBO_H
