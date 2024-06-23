#ifndef DGF_GRAPHICS_EXTRAS_AXES_HELPER_H
#define DGF_GRAPHICS_EXTRAS_AXES_HELPER_H

#include "../core/Mesh.h"

class AxesHelper : public Mesh {
public:
    AxesHelper(float axisLength, float lineWidth);
};

#endif //DGF_GRAPHICS_EXTRAS_AXES_HELPER_H
