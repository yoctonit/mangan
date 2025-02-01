#include <iostream>
#include <string>
#include <cassert>
#include "math/v2d.h"

using namespace Mn;

std::ostream &operator<<(std::ostream &os, const v2d v) {
    os << "("
       << (epsilon_equal(v.x, 0.0f) ? 0.0f : v.x) << ", "
       << (epsilon_equal(v.y, 0.0f) ? 0.0f : v.y) << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const p2d p) {
    os << "(" << p.x << ", " << p.y << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const v3d v) {
    os << "("
       << (epsilon_equal(v.x, 0.0f) ? 0.0f : v.x) << ", "
       << (epsilon_equal(v.y, 0.0f) ? 0.0f : v.y) << ", "
       << (epsilon_equal(v.z, 0.0f) ? 0.0f : v.z) << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const p3d p) {
    os << "("
       << (epsilon_equal(p.x, 0.0f) ? 0.0f : p.x) << ", "
       << (epsilon_equal(p.y, 0.0f) ? 0.0f : p.y) << ", "
       << (epsilon_equal(p.z, 0.0f) ? 0.0f : p.z) << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const m2d M) {
    os << "|" << M[0] << " " << M[3] << " " << M[6] << "|\n";
    os << "|" << M[1] << " " << M[4] << " " << M[7] << "|\n";
    os << "|" << M[2] << " " << M[5] << " " << M[8] << "|\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const m3d M) {
    os << "|" << M[0] << " " << M[4] << " " << M[8] << " " << M[12] << "|\n";
    os << "|" << M[1] << " " << M[5] << " " << M[9] << " " << M[13] << "|\n";
    os << "|" << M[2] << " " << M[6] << " " << M[10] << " " << M[14] << "|\n";
    os << "|" << M[3] << " " << M[7] << " " << M[11] << " " << M[15] << "|\n";
    return os;
}

const float half_sqrt2 = std::sqrt(2.0f) / 2.0f;

int main() {
    {
        v2d v;
        assert(v.x == 0.0f);
        assert(v.y == 0.0f);
    }

    {
        float a = 0.00010f;
        float b = 0.00009f;
        assert(a != b);
        assert(epsilon_equal(a, b));
    }

    {
        v2d v1{2.0f, 0.0f};
        assert(equal(v2d{1.0f, 0.0f}, normalize(v1)));
//        std::cout << normalize(v1);

        v2d v2{0.0f, 3.5f};
        assert(equal(v2d{0.0f, 1.0f}, normalize(v2)));
//        std::cout << normalize(v2);

        v2d v3{2.0f, 2.0f};
        assert(equal(v2d{half_sqrt2, half_sqrt2}, normalize(v3)));
//        std::cout << normalize(v3);
    }

    {
        m2d M;
        v2d v{1.0f, 2.0f};
//        std::cout << M;
//        std::cout << M * v;
        M = m2d::T(1.5f, 3.0f);
//        std::cout << M;
//        std::cout << M * v;
        p2d p{1.0f, 2.0f};
//        std::cout << M;
//        std::cout << M * p;
    }

    {
        m2d M;
        v2d v{1.0f, 2.0f};
//        std::cout << M;
//        std::cout << M * v;
        M = m2d::S(1.5f, 3.0f);
//        std::cout << M;
//        std::cout << M * v;
        p2d p{1.0f, 2.0f};
//        std::cout << M;
//        std::cout << M * p;
    }

    {
        m2d M;
        v2d v{1.0f, 1.0f};
//        std::cout << M;
//        std::cout << M * v;
        M = m2d::R(deg_to_rad(45.0f));
//        std::cout << M;
//        std::cout << M * v;
        p2d p{1.0f, 1.0f};
//        std::cout << M;
//        std::cout << M * p;
        M = m2d::R(deg_to_rad(90.0f));
//        std::cout << M * v2d{1.0f, 0.0f};
//        std::cout << M * v2d{0.0f, 1.0f};
    }

    {
        m2d M;
        v2d v{1.0f, 0.0f};
//        std::cout << M;
//        std::cout << M * v;
        M = m2d::T(1.0f, 0.0f) * m2d::R(deg_to_rad(45.0f));
//        std::cout << M;
//        std::cout << M * v;
        p2d p{1.0f, 0.0f};
//        std::cout << M;
//        std::cout << M * p;
        M = m2d::R(deg_to_rad(45.0f)) * m2d::T(1.0f, 0.0f);
//        std::cout << M;
//        std::cout << M * v;
//        std::cout << M;
//        std::cout << M * p;
    }

    {
        m3d M;
//        std::cout << M;
    }

    {
        m3d M;
        v3d v{1.0f, 2.0f, 3.0f};
//        std::cout << M;
//        std::cout << M * v;
        M = m3d::T(1.5f, 3.0f, 2.0f);
//        std::cout << M;
//        std::cout << M * v;
        p3d p{1.0f, 2.0f, 3.0f};
//        std::cout << M;
//        std::cout << M * p;
    }

    {
        m3d M;
        v3d v{1.0f, 2.0f, 3.0f};
//        std::cout << M;
//        std::cout << M * v;
        M = m3d::S(1.0f, 3.0f, 2.0f);
//        std::cout << M;
//        std::cout << M * v;
        p3d p{1.0f, 2.0f, 3.0f};
//        std::cout << M;
//        std::cout << M * p;
    }

    {
        m3d M = m3d::Rx(deg_to_rad(45.0f));
        v3d v{0.0f, 1.0f, -1.0f};
//        std::cout << M;
//        std::cout << M * v;

        p3d p{0.0f, 1.0f, 1.0f};
//        std::cout << M;
//        std::cout << M * p;

        M = m3d::Rx(deg_to_rad(90.0f));
//        std::cout << M * v3d{1.0f, 0.0f, 0.0f};
//        std::cout << M * v3d{0.0f, 1.0f, 0.0f};
    }

    {
        m3d M = m3d::Ry(deg_to_rad(45.0f));
        v3d v{1.0f, 0.0f, -1.0f};
//        std::cout << M;
//        std::cout << M * v;

        p3d p{1.0f, 0.0f, 1.0f};
//        std::cout << M;
//        std::cout << M * p;

        M = m3d::Ry(deg_to_rad(90.0f));
//        std::cout << M * v3d{1.0f, 0.0f, 0.0f};
//        std::cout << M * v3d{0.0f, 1.0f, 0.0f};
    }

    {
        m3d M = m3d::Rz(deg_to_rad(45.0f));
        v3d v{1.0f, 1.0f, 0.0f};
//        std::cout << M;
//        std::cout << M * v;

        p3d p{1.0f, 1.0f, 0.0f};
//        std::cout << M;
//        std::cout << M * p;

        M = m3d::Rz(deg_to_rad(90.0f));
//        std::cout << M * v3d{1.0f, 0.0f, 0.0f};
//        std::cout << M * v3d{0.0f, 1.0f, 0.0f};
    }

    {
        m3d M = m3d::R(deg_to_rad(45.0f), {0.0f, 1.0f, 0.0f});
        v3d v{1.0f, 1.0f, 1.0f};
        std::cout << M;
        std::cout << M * v;

        M = m3d::R(deg_to_rad(90.0f), {0.0f, 1.0f, 0.0f});
        p3d p{1.0f, 1.0f, 1.0f};
        std::cout << M;
        std::cout << M * p;
    }

    return 0;
}
