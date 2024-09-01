#ifndef INCLUDED_MN_GEOMETRY_ICOSAHEDRON_H
#define INCLUDED_MN_GEOMETRY_ICOSAHEDRON_H

#include <vector>
#include <glm/vec3.hpp>
#include "Geometry.h"

namespace Mn {

    class Icosahedron : public Geometry {
    public:
        void Create(float radius = 1.0f, int levelOfRecursion = 3);

// TexCoords? http://vterrain.org/Textures/spherical.html
// https://stackoverflow.com/questions/5674149/3d-coordinates-on-a-sphere-to-latitude-and-longitude
// http://blog.coredumping.com/subdivision-of-icosahedrons/

    private:
        float mRadius{};

        void Subdivide(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int lor);
    };

}

#endif //INCLUDED_MN_GEOMETRY_ICOSAHEDRON_H
