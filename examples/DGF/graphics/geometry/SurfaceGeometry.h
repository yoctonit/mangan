#ifndef DGF_GRAPHICS_GEOMETRY_SURFACE_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_SURFACE_GEOMETRY_H

#include "Geometry.h"


class SurfaceGeometry : public Geometry {
public:
    SurfaceGeometry(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution
    );

    std::vector<std::vector<glm::vec3>> getPoints(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution
    );

    std::vector<std::vector<glm::vec2>> getUVs(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution
    );

    std::vector<std::vector<glm::vec3>> getNormals(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution
    );

    void calculateSurface();

private:
    virtual glm::vec3 surface(float u, float v) = 0;

    float m_uStart;
    float m_uEnd;
    int m_uResolution;

    float m_vStart;
    float m_vEnd;
    int m_vResolution;
};

#endif //DGF_GRAPHICS_GEOMETRY_SURFACE_GEOMETRY_H
