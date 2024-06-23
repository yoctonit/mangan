#ifndef DGF_GRAPHICS_EXTRAS_AXES_GEOMETRY_H
#define DGF_GRAPHICS_EXTRAS_AXES_GEOMETRY_H

#include "../geometry/Geometry.h"

class AxesGeometry : public Geometry {
public:
    AxesGeometry();

    explicit AxesGeometry(float axisLength);
};

#endif //DGF_GRAPHICS_EXTRAS_AXES_GEOMETRY_H
