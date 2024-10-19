#ifndef INCLUDED_MN_GRAPHICS_EBO_H
#define INCLUDED_MN_GRAPHICS_EBO_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Mn {

    class Ebo {
    public:
        Ebo();

        explicit Ebo(const std::vector<unsigned int> &data, GLenum type = GL_STATIC_DRAW);

        ~Ebo();

        Ebo(const Ebo &other);

        Ebo &operator=(const Ebo &other);

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

#endif //INCLUDED_MN_GRAPHICS_EBO_H
