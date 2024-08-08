#ifndef DGF_GRAPHICS_EXTRAS_POINT_LIGHT_HELPER_H
#define DGF_GRAPHICS_EXTRAS_POINT_LIGHT_HELPER_H

#include <memory>
#include "../core/Mesh.h"
#include "../light/PointLight.h"

class PointLightHelper : public Mesh {
public:
    PointLightHelper(const std::shared_ptr<PointLight>& light, float size, float lineWidth);

    explicit PointLightHelper(const std::shared_ptr<PointLight>& light);
};

#endif //DGF_GRAPHICS_EXTRAS_POINT_LIGHT_HELPER_H
