#ifndef DGF_GRAPHICS_EXTRAS_GRID_HELPER_H
#define DGF_GRAPHICS_EXTRAS_GRID_HELPER_H

#include "../core/Mesh.h"

class GridHelper : public Mesh {
public:
    GridHelper();

    GridHelper(
            float size, int divisions,
            glm::vec3 gridColor, glm::vec3 centerColor,
            float lineWidth
    );
};

#endif //DGF_GRAPHICS_EXTRAS_GRID_HELPER_H
