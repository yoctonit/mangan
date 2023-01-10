//
// Created by ivan on 2.6.2020..
//

#ifndef INCLUDED_MODEL_H
#define INCLUDED_MODEL_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>

namespace mn {

    class model {

    public:
        model() = default;
        virtual ~model() = default;

        [[nodiscard]] virtual const std::vector<glm::vec3>& vertices() const = 0;
        [[nodiscard]] virtual const std::vector<glm::vec3>& normals() const = 0;
        [[nodiscard]] virtual int number_of_vertices() const = 0;
        [[nodiscard]] virtual std::string name() const = 0;
        [[nodiscard]] virtual glm::mat4 transform() const = 0;

    };

}

#endif //INCLUDED_MODEL_H
