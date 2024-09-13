#ifndef INCLUDED_MN_GRAPHICS_VBO_H
#define INCLUDED_MN_GRAPHICS_VBO_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Mn {

    class Vbo {
    public:
        Vbo();

        explicit Vbo(const std::vector<float> &data, GLenum type = GL_STATIC_DRAW);

        ~Vbo();

        Vbo(const Vbo &other);

        Vbo &operator=(const Vbo &other);

        [[nodiscard]] unsigned int Id() const;

        void Activate() const;

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

#endif //INCLUDED_MN_GRAPHICS_VBO_H

//        void load(const std::vector<float> &data) const {
//            glBindBuffer(GL_ARRAY_BUFFER, m_id);
//            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data());
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//        }
