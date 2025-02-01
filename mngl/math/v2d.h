#ifndef INCLUDED_MN_MATH_V2D_H
#define INCLUDED_MN_MATH_V2D_H

#include <algorithm>
#include <array>
#include <cmath>

namespace Mn {

    // https://realtimecollisiondetection.net/blog/?p=89
    bool epsilon_equal(float x, float y, float epsilon = 0.0001f) {
        if (std::abs(x - y) <= epsilon * std::max({1.0f, std::abs(x), std::abs(y)})) {
            return true;
        }
        return false;
    }

    float deg_to_rad(float deg) {
        return deg * 3.14159265358979323846f / 180.0f;
    }

    float rad_to_deg(float rad) {
        return rad * 180.0f / 3.14159265358979323846f;
    }

    struct v2d {
        float x{};
        float y{};

        v2d operator*(float val) const;

        v2d operator/(float val) const;

        v2d operator*=(float val);

        v2d operator/=(float val);
    };

    struct p2d {
        float x{};
        float y{};

        p2d operator*(float val) const;

        p2d operator/(float val) const;

        p2d operator*=(float val);

        p2d operator/=(float val);
    };

    struct v3d {
        float x{};
        float y{};
        float z{};

        v3d operator*(float val) const;

        v3d operator/(float val) const;

        v3d operator*=(float val);

        v3d operator/=(float val);
    };

    struct p3d {
        float x{};
        float y{};
        float z{};
    };

    v2d cast_to_v2(p2d p) {
        return {p.x, p.y};
    }

    p2d cast_to_p2(v2d v) {
        return {v.x, v.y};
    }

    v2d operator+(v2d v1, v2d v2) {
        return {v1.x + v2.x, v1.y + v2.y};
    }

    v2d operator-(v2d v1, v2d v2) {
        return {v1.x - v2.x, v1.y - v2.y};
    }

    v2d v2d::operator*(const float val) const {
        return {x * val, y * val};
    }

    v2d operator*(const float val, v2d v) {
        return {v.x * val, v.y * val};
    }

    v2d v2d::operator/(const float val) const {
        return {x / val, y / val};
    }

    v2d v2d::operator*=(const float val) {
        x *= val;
        y *= val;
        return *this;
    }

    v2d v2d::operator/=(const float val) {
        x /= val;
        y /= val;
        return *this;
    }

    bool equal(v2d lhs, v2d rhs) {
        return epsilon_equal(lhs.x, rhs.x) && epsilon_equal(lhs.y, rhs.y);
    }

    float dot(v2d v1, v2d v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    float cross(v2d v1, v2d v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    float length(v2d v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    float length_squared(v2d v) {
        return v.x * v.x + v.y * v.y;
    }

    v2d normalize(v2d v) {
        return v / length(v);
    }

    p2d operator+(p2d p, v2d v) {
        return {p.x + v.x, p.y + v.y};
    }

//    p2d operator+(v2d v, p2d p) {
//        return {p.x + v.x, p.y + v.y};
//    }

    v2d operator-(p2d p1, p2d p2) {
        return {p1.x - p2.x, p1.y - p2.y};
    }

    p2d p2d::operator*(const float val) const {
        return {x * val, y * val};
    }

    p2d operator*(const float val, p2d p) {
        return {p.x * val, p.y * val};
    }

    p2d p2d::operator/(const float val) const {
        return {x / val, y / val};
    }

    p2d p2d::operator*=(const float val) {
        x *= val;
        y *= val;
        return *this;
    }

    p2d p2d::operator/=(const float val) {
        x /= val;
        y /= val;
        return *this;
    }

    v3d operator+(v3d v1, v3d v2) {
        return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    }

    v3d operator-(v3d v1, v3d v2) {
        return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    }

    v3d v3d::operator*(const float val) const {
        return {x * val, y * val, z * val};
    }

    v3d v3d::operator/(const float val) const {
        return {x / val, y / val, z / val};
    }

    v3d v3d::operator*=(const float val) {
        x *= val;
        y *= val;
        z *= val;
        return *this;
    }

    v3d v3d::operator/=(const float val) {
        x /= val;
        y /= val;
        z /= val;
        return *this;
    }

    p3d operator+(p3d p, v3d v) {
        return {p.x + v.x, p.y + v.y, p.z + v.z};
    }

    v3d operator-(p3d p1, p3d p2) {
        return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
    }

    v3d operator*(const float val, v3d v) {
        return {v.x * val, v.y * val, v.z * val};
    }

    p3d operator*(const float val, p3d p) {
        return {p.x * val, p.y * val, p.z * val};
    }

    float dot(v3d v1, v3d v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    float length(v3d v) {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    float length_squared(v3d v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    v3d normalize(v3d v) {
        return v / length(v);
    }

    // a11 a12 a13
    // a21 a22 a23
    // a31 a32 a33
    // in array matrix elements are stored in column first order (order that opengl accepts):
    // m{a11, a21, a31, a12, a22, a32, a13, a23, a33}
    //    0    1    2    3    4    5    6    7    8
    class m2d {
        std::array<float, 9> elem{};
    public:
        m2d() : elem{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f} {}

        m2d(
                float a11, float a12, float a13,
                float a21, float a22, float a23,
                float a31, float a32, float a33
        ) : elem{a11, a21, a31, a12, a22, a32, a13, a23, a33} {}

        float operator[](int i) const { return elem[i]; }

        float &operator[](int i) { return elem[i]; }

        static m2d T(float x, float y) {
            m2d M;
            M[6] = x;
            M[7] = y;
            return M;
        }

        // theta is in radians
        static m2d R(float theta) {
            m2d t;
            float cos_theta = std::cos(theta);
            float sin_theta = std::sin(theta);
            t[0] = cos_theta;
            t[1] = sin_theta;
            t[3] = -sin_theta;
            t[4] = cos_theta;
            return t;
        }

        static m2d S(float sx, float sy) {
            m2d M;
            M[0] = sx;
            M[4] = sy;
            return M;
        }
    };

    m2d operator*(m2d A, m2d B) {
//        return {
//            A[0]*B[0]+A[3]*B[1]+A[6]*B[2], A[0]*B[3]+A[3]*B[4]+A[6]*B[5],A[0]*B[6]+A[3]*B[7]+A[6]*B[8],
//            A[1]*B[0]+A[4]*B[1]+A[7]*B[2], A[1]*B[3]+A[4]*B[4]+A[7]*B[5],A[1]*B[6]+A[4]*B[7]+A[7]*B[8],
//            A[2]*B[0]+A[5]*B[1]+A[8]*B[2], A[2]*B[3]+A[5]*B[4]+A[8]*B[5],A[2]*B[6]+A[5]*B[7]+A[8]*B[8]
//        };
        // since a2, a5, a8 and b2, b5, b8 are 0, 0, 1
        return {
                A[0] * B[0] + A[3] * B[1],
                A[0] * B[3] + A[3] * B[4],
                A[0] * B[6] + A[3] * B[7] + A[6],
                A[1] * B[0] + A[4] * B[1],
                A[1] * B[3] + A[4] * B[4],
                A[1] * B[6] + A[4] * B[7] + A[7],
                0.0f, 0.0f, 1.0f
        };
    }

    v2d operator*(m2d M, v2d v) {
        return {M[0] * v.x + M[3] * v.y, M[1] * v.x + M[4] * v.y};
    }

    p2d operator*(m2d M, p2d p) {
        return {M[0] * p.x + M[3] * p.y + M[6], M[1] * p.x + M[4] * p.y + M[7]};
    }

    // a11 a12 a13 a14
    // a21 a22 a23 a24
    // a31 a32 a33 a34
    // a41 a42 a43 a44
    // in array matrix elements are stored in column first order (order that opengl accepts):
    // m{a11, a21, a31, a41, a12, a22, a32, a42, a13, a23, a33, a43, a14, a24, a34, a44}
    //    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    class m3d {
        std::array<float, 16> elem{};
    public:
        m3d() : elem{
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        } {}

        m3d(
                float a11, float a12, float a13, float a14,
                float a21, float a22, float a23, float a24,
                float a31, float a32, float a33, float a34,
                float a41, float a42, float a43, float a44
        ) : elem{
                a11, a21, a31, a41,
                a12, a22, a32, a42,
                a13, a23, a33, a43,
                a14, a24, a34, a44
        } {}

        float operator[](int i) const { return elem[i]; }

        float &operator[](int i) { return elem[i]; }

        static m3d T(float x, float y, float z) {
            m3d M;
            M[12] = x;
            M[13] = y;
            M[14] = z;
            return M;
        }

//        https://pages.cs.wisc.edu/~psilord/docs/local_axis.html
//
//        Rotation about the X axis by an angle a:
//        |1       0        0    0|
//        |0  cos(a)  -sin(a)    0|
//        |0  sin(a)   cos(a)    0|
//        |0       0        0    1|
        // theta is in radians
        static m3d Rx(float theta) {
            m3d M;
            float cos_theta = std::cos(theta);
            float sin_theta = std::sin(theta);
            M[5] = cos_theta;
            M[6] = sin_theta;
            M[9] = -sin_theta;
            M[10] = cos_theta;
            return M;
        }

//
//        Rotation about the Y axis by an angle a:
//        | cos(a)  0  sin(a)    0|
//        |      0  1       0    0|
//        |-sin(a)  0  cos(a)    0|
//        |      0  0       0    1|
        static m3d Ry(float theta) {
            m3d M;
            float cos_theta = std::cos(theta);
            float sin_theta = std::sin(theta);
            M[0] = cos_theta;
            M[2] = -sin_theta;
            M[8] = sin_theta;
            M[10] = cos_theta;
            return M;
        }

//        Rotation about the Z axis by an angle a:
//        |cos(a)  -sin(a)  0   0|
//        |sin(a)   cos(a)  0   0|
//        |     0        0  1   0|
//        |     0        0  0   1|
        static m3d Rz(float theta) {
            m3d M;
            float cos_theta = std::cos(theta);
            float sin_theta = std::sin(theta);
            M[0] = cos_theta;
            M[1] = sin_theta;
            M[4] = -sin_theta;
            M[5] = cos_theta;
            return M;
        }

        // General rotation around axis; axis is unit vector
        static m3d R(float theta, v3d axis) {
            m3d M;
            float cos_theta = std::cos(theta);
            float sin_theta = std::sin(theta);

            M[0] = (1.0f - cos_theta) * axis.x * axis.x + cos_theta;
            M[1] = (1.0f - cos_theta) * axis.x * axis.y + sin_theta * axis.z;
            M[2] = (1.0f - cos_theta) * axis.x * axis.z - sin_theta * axis.y;

            M[4] = (1.0f - cos_theta) * axis.x * axis.y - sin_theta * axis.z;
            M[5] = (1.0f - cos_theta) * axis.y * axis.y + cos_theta;
            M[6] = (1.0f - cos_theta) * axis.y * axis.z + sin_theta * axis.x;

            M[8] = (1.0f - cos_theta) * axis.x * axis.z + sin_theta * axis.y;
            M[9] = (1.0f - cos_theta) * axis.y * axis.z - sin_theta * axis.x;
            M[10] = (1.0f - cos_theta) * axis.z * axis.z + cos_theta;

            return M;
        }

        static m3d S(float sx, float sy, float sz) {
            m3d M;
            M[0] = sx;
            M[5] = sy;
            M[10] = sz;
            return M;
        }

    };

    m3d operator*(m3d A, m3d B) {
//        return {
//            A[0]*B[0]+A[4]*B[1]+A[8]*B[2]+A[12]*B[3],
//            A[0]*B[4]+A[4]*B[5]+A[8]*B[6]+A[12]*B[7],
//            A[0]*B[8]+A[4]*B[9]+A[8]*B[10]+A[12]*B[11],
//            A[0]*B[12]+A[4]*B[13]+A[8]*B[14]+A[12]*B[15],
//
//            A[1]*B[0]+A[5]*B[1]+A[9]*B[2]+A[13]*B[3],
//            A[1]*B[4]+A[5]*B[5]+A[9]*B[6]+A[13]*B[7],
//            A[1]*B[8]+A[5]*B[9]+A[9]*B[10]+A[13]*B[11],
//            A[1]*B[12]+A[5]*B[13]+A[9]*B[14]+A[13]*B[15],
//
//            A[2]*B[0]+A[6]*B[1]+A[10]*B[2]+A[14]*B[3],
//            A[2]*B[4]+A[6]*B[5]+A[10]*B[6]+A[14]*B[7],
//            A[2]*B[8]+A[6]*B[9]+A[10]*B[10]+A[14]*B[11],
//            A[2]*B[12]+A[6]*B[13]+A[10]*B[14]+A[14]*B[15],
//
//            A[3]*B[0]+A[7]*B[1]+A[11]*B[2]+A[15]*B[3],
//            A[3]*B[4]+A[7]*B[5]+A[11]*B[6]+A[15]*B[7],
//            A[3]*B[8]+A[7]*B[9]+A[11]*B[10]+A[15]*B[11],
//            A[3]*B[12]+A[7]*B[13]+A[11]*B[14]+A[15]*B[15],
//        };
        // since a3, a7, a11, a15 and b3, b7, b11, b15 are 0, 0, 0, 1
        return {
                A[0] * B[0] + A[4] * B[1] + A[8] * B[2],
                A[0] * B[4] + A[4] * B[5] + A[8] * B[6],
                A[0] * B[8] + A[4] * B[9] + A[8] * B[10],
                A[0] * B[12] + A[4] * B[13] + A[8] * B[14] + A[12],

                A[1] * B[0] + A[5] * B[1] + A[9] * B[2],
                A[1] * B[4] + A[5] * B[5] + A[9] * B[6],
                A[1] * B[8] + A[5] * B[9] + A[9] * B[10],
                A[1] * B[12] + A[5] * B[13] + A[9] * B[14] + A[13],

                A[2] * B[0] + A[6] * B[1] + A[10] * B[2],
                A[2] * B[4] + A[6] * B[5] + A[10] * B[6],
                A[2] * B[8] + A[6] * B[9] + A[10] * B[10],
                A[2] * B[12] + A[6] * B[13] + A[10] * B[14] + A[14],

                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    v3d operator*(m3d M, v3d v) {
        return {
                M[0] * v.x + M[4] * v.y + M[8] * v.z,
                M[1] * v.x + M[5] * v.y + M[9] * v.z,
                M[2] * v.x + M[6] * v.y + M[10] * v.z
        };
    }

    p3d operator*(m3d M, p3d p) {
        return {
                M[0] * p.x + M[4] * p.y + M[8] * p.z + M[12],
                M[1] * p.x + M[5] * p.y + M[9] * p.z + M[13],
                M[2] * p.x + M[6] * p.y + M[10] * p.z + M[14]
        };
    }

    p2d lerp(p2d x, p2d y, float alpha) {
//        return (1.0f - alpha) * x + alpha * cast_to_v2(y);
        return x + alpha * (x - y);
    }

    float inverse_lerp(p3d x, p3d y, p3d u) {
        v3d t1 = u - x;
        v3d t2 = y - x;
        return dot(t1, t1) / dot(t2, t2);
    }

    /*
     * Returns barycentric coordinates of u in relation to triangle(x, y, z)
     * https://www.youtube.com/watch?v=YwzaFSszSPc&list=PLtuv65ivttlzWM0b2AYzHcbTseqKlrh58
     * Video 49: 08 06 Calculating barycentric coordinates
     vec3 barycentric_coordinates(vec3 x, vec3 y, vec3 z, vec3 u) {
       vec3 f = u - x;
       vec3 e1 = y - x;
       vec3 e2 = z - x;
       float le1 = length(e1);
       float le2 = length(e2);
       float de1e2 = dot(e1, e2);
       float denominator = le1 * le1 * le2 * le2 - de1e2 * de1e2;

       vec3 beta = (le2 * le2 * e1 - de1e2 * e2) / denominator;
       vec3 gamma= (le1 * le1 * e2 - de1e2 * e1) / denominator;

       float u2 = dot(beta, f);
       float u3 = dot(gamma, f);
       float u1 = 1.0f - u2 - u3;
       return {u1, u2, u3};
     }
     */
}

#endif //INCLUDED_MN_MATH_V2D_H
