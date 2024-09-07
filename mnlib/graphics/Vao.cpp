#include <glad/glad.h>
#include "Vao.h"

namespace Mn {

    std::unordered_map<unsigned int, int> Vao::mRefCnt{};

    Vao::Vao(bool allocate) {
        if (allocate) {
            Create();
        }
    }

    void Vao::Create() {
        glGenVertexArrays(1, &mId);
        glBindVertexArray(mId);
        IncRef();
        std::cout << "Created VAO with id " << mId << "\n";
    }

    Vao::~Vao() {
        int refCnt = DecRef();
        if (refCnt == 0) {
            glDeleteVertexArrays(1, &mId);
            std::cout << "Deleted VAO with id " << mId << "\n";
        }
    }

    // copy constructor
    Vao::Vao(const Vao &other) {
        mId = other.mId;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    Vao &Vao::operator=(const Vao &other) {
        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "Vao self assignment detected.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "Vao assignment with same id detected.\n";
            return *this;
        }
        if (mId != 0) {
            std::ignore = DecRef();
        }
        mId = other.mId;
        IncRef();
        return *this;
    }

    unsigned int Vao::Id() const {
        return mId;
    }

    void Vao::Activate() const {
        glBindVertexArray(mId);
    }

    void Vao::Connect(unsigned int index, int size, int stride, int start) const {
        glVertexAttribPointer(
                index, size, GL_FLOAT, GL_FALSE,
                stride * static_cast<int>(sizeof(float)),
                (void *) (start * sizeof(float)));
        glEnableVertexAttribArray(index);
    }

    void Vao::Draw(GLenum mode, int first, int count) const {
        glBindVertexArray(mId);
        glDrawArrays(mode, first, count);
    }

    void Vao::Draw(GLenum mode, int count, GLenum type, const void *indices) const {
        glBindVertexArray(mId);
        glDrawElements(mode, count, type, indices);
    }

    void Vao::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << mId << "\n";
    }

    void Vao::IncRef() const {
        // objects with mId = 0 are 'empty' (non-initialized) objects,
        // so don't note their existence in mRefCnt map
        if (mId == 0) {
            return;
        }
        mRefCnt[mId]++;
    }

    [[nodiscard]] int Vao::DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "Vao: called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }

    void Vao::DebugRefCnt() {
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
