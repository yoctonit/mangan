#ifndef INCLUDED_MN_GEOMETRY_SURFACE_H
#define INCLUDED_MN_GEOMETRY_SURFACE_H

#include "Geometry.h"

namespace Mn {

    class Surface : public Geometry {
    public:
        Surface(
                float uStart, float uEnd, int uResolution,
                float vStart, float vEnd, int vResolution
        );

        void CalculateSurface();

    protected:
        virtual glm::vec3 SurfaceEquation(float u, float v) = 0;

        float m_uStart;
        float m_uEnd;
        int m_uResolution;

        float m_vStart;
        float m_vEnd;
        int m_vResolution;

        std::vector<std::vector<glm::vec3>> getPoints(
                float uStart, float uEnd, int uResolution,
                float vStart, float vEnd, int vResolution
        );

        std::vector<std::vector<glm::vec3>> getNormals(
                float uStart, float uEnd, int uResolution,
                float vStart, float vEnd, int vResolution
        );

        std::vector<std::vector<glm::vec2>> getUVs(int uResolution, int vResolution);
    };
}

#endif //INCLUDED_MN_GEOMETRY_SURFACE_H
