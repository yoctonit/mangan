#ifndef INCLUDED_MN_CORE_VAO_H
#define INCLUDED_MN_CORE_VAO_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Vbo.h"

namespace Mn {

    struct do_not_allocate {
    };

    class Vao {
    public:
        Vao();

        explicit Vao(do_not_allocate);

        ~Vao();

        Vao(const Vao &other);

        Vao &operator=(const Vao &other);

        [[nodiscard]] unsigned int Id() const;

        void Activate() const;

        void Connect(const Vbo &vbo, unsigned int index, int size, int stride, int start) const;

        void Draw(GLenum mode, int first, int count) const;

        void Draw(GLenum mode, int count, GLenum type, const void *indices) const;

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

#endif //INCLUDED_MN_CORE_VAO_H
