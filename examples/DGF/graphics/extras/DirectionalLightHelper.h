#ifndef DGF_GRAPHICS_EXTRAS_DIRECTIONAL_LIGHT_HELPER_H
#define DGF_GRAPHICS_EXTRAS_DIRECTIONAL_LIGHT_HELPER_H

#include <memory>
#include "GridHelper.h"
#include "../light/DirectionalLight.h"

class DirectionalLightHelper : public GridHelper {
public:
    DirectionalLightHelper(const std::shared_ptr<DirectionalLight>& light);
};

#endif //DGF_GRAPHICS_EXTRAS_DIRECTIONAL_LIGHT_HELPER_H
