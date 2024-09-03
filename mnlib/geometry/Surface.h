#ifndef INCLUDED_MN_GEOMETRY_SURFACE_H
#define INCLUDED_MN_GEOMETRY_SURFACE_H

#include "Geometry.h"

namespace Mn {

    class SurfaceEquation {
    public:
        virtual glm::vec3 operator()(float u, float v) const = 0;
    };

    class Surface : public Geometry {
    public:
        Surface(
                float uStart, float uEnd, int uResolution,
                float vStart, float vEnd, int vResolution
        );

        void CalculateSurface(const SurfaceEquation &surfaceEquation);

    protected:
        float m_uStart;
        float m_uEnd;
        int m_uResolution;

        float m_vStart;
        float m_vEnd;
        int m_vResolution;

        static std::vector<std::vector<glm::vec3>> getPoints(
                float uStart, float uEnd, int uResolution,
                float vStart, float vEnd, int vResolution,
                const SurfaceEquation &surfaceEquation
        );

        static std::vector<std::vector<glm::vec3>> getNormals(
                float uStart, float uEnd, int uResolution,
                float vStart, float vEnd, int vResolution,
                const SurfaceEquation &surfaceEquation
        );

        static std::vector<std::vector<glm::vec2>> getUVs(int uResolution, int vResolution);
    };

}

#endif //INCLUDED_MN_GEOMETRY_SURFACE_H
