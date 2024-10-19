#ifndef INCLUDED_MN_GRAPHICS_UNIFORM_H
#define INCLUDED_MN_GRAPHICS_UNIFORM_H

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Mn {

    class Uniform {
    public:
        Uniform();

        Uniform(int location, int type);

        Uniform &operator=(bool data);

        Uniform &operator=(int data);

        Uniform &operator=(float data);

        Uniform &operator=(glm::vec2 data);

        Uniform &operator=(glm::vec3 data);

        Uniform &operator=(glm::vec4 data);

        Uniform &operator=(glm::mat4x4 data);

        void Upload() const;

        void Debug(const std::string &msg) const;

    private:
        int mLocation{-1};
        int mType{-1};

        union Data {
            bool mDataBool;
            int mDataInt;
            float mDataFloat;
            glm::vec2 mDataVec2;
            glm::vec3 mDataVec3;
            glm::vec4 mDataVec4;
            glm::mat4x4 mDataMat4x4;
        } mData{};

        [[nodiscard]] std::string TypeName() const;
    };

}

#endif //INCLUDED_MN_GRAPHICS_UNIFORM_H
