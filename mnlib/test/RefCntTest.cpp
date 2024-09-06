#include <iostream>
#include <string>
#include <map>
#include <tuple> // for std::ignore
#include <utility>

int getAvailableId(const std::string &name) {
    static int id = 0;

    std::cout << "Get handle to resource " << name
              << " with id " << (id + 1) << "\n";
    return ++id;
}

class S {
public:
    explicit S(std::string name) : mName{std::move(name)}, mId{0} {
        std::cout << "Creating empty object " << mName << " with id " << mId << "\n";
    };

    explicit S(std::string name, const std::string &resourceName)
            : mName{std::move(name)}, mId{0} {
        mId = getAvailableId(resourceName);
        IncRef();
        std::cout << "Creating object " << mName << " with id " << mId << "\n";
    }

    ~S() {
        std::cout << "Trying to destruct " << mName << " with id " << mId << "...";
        int refCnt = DecRef();
        if (refCnt == 0) {
            std::cout << "Destructing " << mName << " with id " << mId << "\n";
            mId = 0;
        } else {
            std::cout << "skip, there are " << mRefCnt[mId]
                      << " references with id " << mId << " left\n";
        }
    }

    // copy constructor
    S(const S &other) {
//        if (this == &other) {
//            std::cout << "Self assignment detected in copy constructor - aborting assignment.\n";
//            return;
//        }
        std::cout << "Copy constructing object " << mName << " with id " << mId
                  << " from object " << other.mName << " with id " << other.mId << "\n";
        mName = other.mName;
        mId = other.mId;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    S &operator=(const S &other) {
        std::cout << "Copy assigning object " << mName << " with id " << mId
                  << " from object " << other.mName << " with id " << other.mId << "\n";

        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "Self assignment detected - aborting assignment.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "Same id detected - aborting assignment.\n";
            return *this;
        }
        if (mId != 0) {
            std::cout << "Decrementing ref counter for " << mName << " with id " << mId << "\n";
            std::ignore = DecRef();
        }
        mName = other.mName;
        mId = other.mId;
        std::cout << "Incrementing ref counter for " << mName << " with id " << mId << "\n";
        IncRef();
        return *this;
    }

    void Debug(const std::string &msg) const {
        std::cout << "Debug " << msg << ": " << mName << " with id " << mId << "\n";
    }

    static void DebugRefCnt() {
        if (mRefCnt.empty()) {
            std::cout << "RefCnt: <empty>\n";
            return;
        }
        std::cout << "RefCnt:\n";
        for (auto &refCnt: mRefCnt) {
            std::cout << "Id " << refCnt.first << " (cnt=" << refCnt.second << ")\n";
        }
    }

private:
    std::string mName;
    int mId;

    //////////////////////
    // Reference count map
    //////////////////////
    static std::map<int, int> mRefCnt;

    void IncRef() const {
        if (mId == 0) return;
        mRefCnt[mId]++;
    }

    [[nodiscard]] int DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "Called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }
};

std::map<int, int> S::mRefCnt{};


int main() {
    /*
    std::cout << "sizeof(S) " << sizeof(S) << "\n\n";

    S s1("s1");
    {
        S s2{"s2", "shader"};

        s1.Debug("s1");
        s2.Debug("s2");
        S::DebugRefCnt();

        const S &s3{s2};
//        S s3{s2};
        std::cout << "\nAfter copy construction s3{s2}\n";
        s1.Debug("s1");
        s2.Debug("s2");
        s3.Debug("s3");
        S::DebugRefCnt();

        s1 = s2;
        std::cout << "\nAfter assignment s1 = s2\n";
        s1.Debug("s1");
        s2.Debug("s2");
        s3.Debug("s3");
        S::DebugRefCnt();

        std::cout << "\nEntering new scope\n";
        {
            S s4{"s4", "shader"};
            std::cout << "\nAfter creating s4\n";
            s1.Debug("s1");
            s2.Debug("s2");
            s3.Debug("s3");
            s4.Debug("s4");
            S::DebugRefCnt();

            std::cout << "\nAfter s1 = s4\n";
            s1 = s4;
            s1.Debug("s1");
            s2.Debug("s2");
            s3.Debug("s3");
            s4.Debug("s4");
            S::DebugRefCnt();

            std::cout << "\nAdding s5\n";
            S s5 = s1;
            s5.Debug("s5");
            S::DebugRefCnt();
            std::cout << "\nLeaving s4 and s5 scope\n";
        }

        s1.Debug("s1");
        s2.Debug("s2");
        s3.Debug("s3");
        S::DebugRefCnt();
    }

//    S a = a;
//    a.Debug("a");
    S a = s1;
    a.Debug("a");
    S::DebugRefCnt();
*/
    std::cout << "==============================\n";
    S b{"b"};
    S c{"c"};
    b = c;
    b.Debug("b");
    c.Debug("c");

    S::DebugRefCnt();

    return 0;
}
