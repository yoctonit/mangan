//
// Created by ivan on 11.1.2023..
//

#ifndef INCLUDED_MN_SURFACE_H
#define INCLUDED_MN_SURFACE_H

#include <glm/glm.hpp>
#include <cmath>
#include <functional>
#include <utility>
#include <iostream>
#include "Geometry.h"

class ParametricSurface {
public:
    explicit ParametricSurface(std::function<glm::vec3(float, float)> f_) : f{std::move(f_)} {}

    // get a 2D array of points on the surface
    // represented by this function
    std::vector<std::vector<glm::vec2>> getPoints(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution
    ) {
//        std::vector<std::vector<glm::vec2>> points[uResolution + 1][vResolution + 1];
        std::vector<std::vector<glm::vec2>> points(uResolution + 1);

        float deltaU = (uEnd - uStart) / (float) uResolution;
        float deltaV = (vEnd - vStart) / (float) vResolution;

        for (int uIndex = 0; uIndex < uResolution + 1; uIndex++) {
            for (int vIndex = 0; vIndex < vResolution + 1; vIndex++) {
                float u = uStart + (float) uIndex * deltaU;
                float v = vStart + (float) vIndex * deltaV;
//                points[uIndex][vIndex] = this.function.apply(u,v);
                points[uIndex].emplace_back(f(u, v));
            }
        }
//        std::cout << points.size() << "\n";
//        std::cout << points[0].size() << "\n";
//        std::cout << points[0][0].x << "" << points[0][0].x << "\n";
//        std::cout << points[1][0].x << "" << points[1][0].x << "\n";
        return points;
    }

private:
    std::function<glm::vec3(float, float)> f;
};

class SurfaceGeometry : public Geometry {
public:
    SurfaceGeometry(const std::function<glm::vec3(float, float)> &f_,
                    float uStart,
                    float uEnd,
                    int uResolution,
                    float vStart,
                    float vEnd,
                    int vResolution
    ) {
        ParametricSurface surface(f_);
        std::vector<std::vector<glm::vec2>> positions = surface.getPoints(
                uStart, uEnd, uResolution,
                vStart, vEnd, vResolution
        );
        std::vector<glm::vec3> quadColors{
                glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)};

        std::vector<glm::vec3> positionList;
        std::vector<glm::vec3> colorList;

        for (int uIndex = 0; uIndex < uResolution; uIndex++) {
            for (int vIndex = 0; vIndex < vResolution; vIndex++) {
                // position coordinates
                glm::vec3 pA(positions[uIndex + 0][vIndex + 0], 0.0f);
                glm::vec3 pB(positions[uIndex + 1][vIndex + 0], 0.0f);
                glm::vec3 pD(positions[uIndex + 0][vIndex + 1], 0.0f);
                glm::vec3 pC(positions[uIndex + 1][vIndex + 1], 0.0f);
                positionList.push_back(pA);
                positionList.push_back(pB);
                positionList.push_back(pC);
                positionList.push_back(pA);
                positionList.push_back(pC);
                positionList.push_back(pD);
                colorList.push_back(quadColors[0]);
                colorList.push_back(quadColors[1]);
                colorList.push_back(quadColors[2]);
                colorList.push_back(quadColors[3]);
                colorList.push_back(quadColors[4]);
                colorList.push_back(quadColors[5]);
                // positionList.addAll(Arrays.asList(pA, pB, pC, pA, pC, pD));
                // colorList.addAll(quadColors);
            }
        }

        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(toVector(positionList)));
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(toVector(colorList)));
        vertexCount = uResolution * vResolution * 6;
    }
};

class ParametricPlane {
public:
    glm::vec3 operator()(float u, float v) const {
        return {u,v,0.0f};
    }
};

class Plane : public SurfaceGeometry {
public:

    Plane(float width, float height, int widthSegments, int heightSegments)
            : SurfaceGeometry(ParametricPlane(),
                              -width / 2, width / 2, widthSegments,
                              -height / 2, height / 2, heightSegments) {
    }

//    Plane(float width, float height, int widthSegments, int heightSegments)
//            : SurfaceGeometry([](float u, float v) { return glm::vec3(u, v, 0); },
//                              -width / 2, width / 2, widthSegments,
//                              -height / 2, height / 2, heightSegments) {
//    }

//    PlaneGeometry() {
//        this(1, 1, 8, 8);
//    }
};

class ParametricEllipsoid {
public:
    ParametricEllipsoid(float p1, float p2, float p3)
            : width(p1), height(p2), depth(p3) {}

    glm::vec3 operator()(float u, float v) const {
        return {
                width / 2 * std::sin(u) * std::cos(v),
                height / 2 * std::sin(v),
                depth / 2 * std::cos(u) * std::cos(v)
        };
    }

private:
    float width;
    float height;
    float depth;
};

class Ellipsoid : public SurfaceGeometry {
public:
    Ellipsoid(float width, float height, float depth, int radiusSegments, int heightSegments)
            : SurfaceGeometry(
            ParametricEllipsoid(width, height, depth),
            0.0f, 2 * PI_F, radiusSegments,
            -PI_F / 2, PI_F / 2, heightSegments
    ) {}
//    Ellipsoid(float width, float height, float depth, int radiusSegments, int heightSegments)
//            : SurfaceGeometry(
//            [width, height, depth](float u, float v) {
//                return glm::vec3(
//                        width / 2 * std::sin(u) * std::cos(v),
//                        height / 2 * std::sin(v),
//                        depth / 2 * std::cos(u) * std::cos(v));
//            },
//            0.0f, 2 * PI_F, radiusSegments,
//            -PI_F / 2, PI_F / 2, heightSegments
//    ) {}

//    Ellipsoid() {
//        this(1.0f, 1.0f, 1.0f, 32, 16);
//    }
};

class Sphere : public Ellipsoid {
public:
    Sphere(float radius, int radiusSegments, int heightSegments)
            : Ellipsoid(2 * radius, 2 * radius, 2 * radius, radiusSegments, heightSegments) {
    }

//SphereGeometry(float radius) {
//    this(radius, 32, 16);
//}
//
//SphereGeometry() {
//    this(1, 32, 16);
//}

};

class ParametricCylindrical {
public:
    float radiusTop;
    float radiusBottom;
    float height;

    ParametricCylindrical(float p1, float p2, float p3)
            : radiusTop(p1), radiusBottom(p2), height(p3) {}

    glm::vec3 operator()(float u, float v) const {
        return {
                (v * radiusTop + (1 - v) * radiusBottom) * std::sin(u),
                height * (v - 0.5),
                (v * radiusTop + (1 - v) * radiusBottom) * std::cos(u)};
    }
};

class CylindricalGeometry : public SurfaceGeometry {
public:
    CylindricalGeometry(
            float radiusTop, float radiusBottom, float height,
            int radialSegments, int heightSegments,
            bool closedTop, bool closedBottom) :
            SurfaceGeometry(
                    ParametricCylindrical(radiusTop, radiusBottom, height),
                    0.0f, 2 * PI_F, radialSegments,
                    0.0f, 1.0f, heightSegments
            ) {
    }
//    CylindricalGeometry(
//            float radiusTop, float radiusBottom, float height,
//            int radialSegments, int heightSegments,
//            bool closedTop, bool closedBottom) :
//            SurfaceGeometry(
//                    [radiusTop, radiusBottom, height](float u, float v) {
//                        return glm::vec3(
//                                (v * radiusTop + (1 - v) * radiusBottom) * std::sin(u),
//                                height * (v - 0.5),
//                                (v * radiusTop + (1 - v) * radiusBottom) * std::cos(u));
//                    },
//                    0, 2 * PI_F, radialSegments,
//                    0, 1, heightSegments
//            ) {
//    }

//public CylindricalGeometry()
//{
//    this(1.0f,1.0f,1.0f, 32, 4, true,true);
//}
};

#endif //INCLUDED_MN_SURFACE_H
