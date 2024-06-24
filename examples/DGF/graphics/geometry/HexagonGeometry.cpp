#include "HexagonGeometry.h"

HexagonGeometry::HexagonGeometry()
        : PolygonGeometry(6, 1.0f) {}


HexagonGeometry::HexagonGeometry(float radius)
        : PolygonGeometry(6, radius) {
}
