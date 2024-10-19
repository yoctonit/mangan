#include <iostream>
#include <tuple> // for std::ignore
#include "Ebo.h"

namespace Mn {

    std::unordered_map<unsigned int, int> Ebo::mRefCnt{};

    Ebo::Ebo() = default;

    Ebo::Ebo(const std::vector<unsigned int> &data, GLenum type) {
        glGenBuffers(1, &mId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(data.size() * sizeof(unsigned int)),
                data.data(),
                type
        );
        IncRef();
        std::cout << "Created EBO buffer with id " << mId << "\n";
    }

    Ebo::~Ebo() {
        int refCnt = DecRef();
        if (refCnt == 0) {
            glDeleteBuffers(1, &mId);
            std::cout << "Deleted EBO with id " << mId << "\n";
        }

    }

    // copy constructor
    Ebo::Ebo(const Ebo &other) {
        mId = other.mId;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    Ebo &Ebo::operator=(const Ebo &other) {
        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "Ebo self assignment detected.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "Ebo assignment with same id detected.\n";
            return *this;
        }
        if (mId != 0) {
            std::ignore = DecRef();
        }
        mId = other.mId;
        IncRef();
        return *this;
    }

    unsigned int Ebo::Id() const {
        return mId;
    }

    void Ebo::Activate() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    }

    void Ebo::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << mId << "\n";
    }

    void Ebo::IncRef() const {
        // objects with mId = 0 are 'empty' (non-initialized) objects,
        // so don't note their existence in mRefCnt map
        if (mId == 0) {
            return;
        }
        mRefCnt[mId]++;
    }

    [[nodiscard]] int Ebo::DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "Ebo: called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }

    void Ebo::DebugRefCnt() {
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
