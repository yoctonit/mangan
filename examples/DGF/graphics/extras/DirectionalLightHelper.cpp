#include "DirectionalLightHelper.h"

DirectionalLightHelper::DirectionalLightHelper(const std::shared_ptr<DirectionalLight>& light)
        : GridHelper(1.0f, 4, light->color(), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f) {

    auto line = std::make_shared<Geometry>();

    std::vector<float> posData{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f};
    line->addAttribute("vertexPosition", Attribute::Type::Vec3, posData);

    std::vector<float> colData{1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    line->addAttribute("vertexColor", Attribute::Type::Vec3, colData);

    line->vertexCount(2);

    m_geometry->merge(line);
};
