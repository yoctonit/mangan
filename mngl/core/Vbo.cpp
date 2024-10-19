#include <iostream>
#include <tuple> // for std::ignore
#include "Vbo.h"

namespace Mn {

    std::unordered_map<unsigned int, int> Vbo::mRefCnt{};

    Vbo::Vbo() = default;

    Vbo::Vbo(const std::vector<float> &data, GLenum type) {
        glGenBuffers(1, &mId);
        glBindBuffer(GL_ARRAY_BUFFER, mId);
        glBufferData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(data.size() * sizeof(float)),
                data.data(),
                type
        );
        IncRef();
        std::cout << "Created VBO with id " << mId << "\n";
    }

    Vbo::~Vbo() {
        int refCnt = DecRef();
        if (refCnt == 0) {
            glDeleteBuffers(1, &mId);
            std::cout << "Deleted VBO with id " << mId << "\n";
        }
    }

    // copy constructor
    Vbo::Vbo(const Vbo &other) {
        mId = other.mId;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    Vbo &Vbo::operator=(const Vbo &other) {
        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "Vbo self assignment detected.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "Vbo assignment with same id detected.\n";
            return *this;
        }
        if (mId != 0) {
            std::ignore = DecRef();
        }
        mId = other.mId;
        IncRef();
        return *this;
    }

    unsigned int Vbo::Id() const {
        return mId;
    }

    void Vbo::Activate() const {
        glBindBuffer(GL_ARRAY_BUFFER, mId);
    }

    void Vbo::Load(const std::vector<float> &data) const {
        glBindBuffer(GL_ARRAY_BUFFER, mId);
        glBufferSubData(
                GL_ARRAY_BUFFER,
                0,
                static_cast<GLsizeiptr>(data.size() * sizeof(float)),
                data.data()
        );
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Vbo::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << mId << "\n";
    }

    void Vbo::IncRef() const {
        // objects with mId = 0 are 'empty' (non-initialized) objects,
        // so don't note their existence in mRefCnt map
        if (mId == 0) {
            return;
        }
        mRefCnt[mId]++;
    }

    [[nodiscard]] int Vbo::DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "Vbo: called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }

    void Vbo::DebugRefCnt() {
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
