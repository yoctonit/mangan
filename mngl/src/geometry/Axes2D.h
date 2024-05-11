#ifndef INCLUDED_MN_GEOMETRY_AXES_2D_H
#define INCLUDED_MN_GEOMETRY_AXES_2D_H

#include <vector>

namespace Mn::geometry {

    class Axes2D {
    private:
        std::vector<float> _vertices_with_colors;
    public:
        Axes2D(int x_min, int x_max, int y_min, int y_max, int step) {
            // horizontal lines
            for (int y = y_min; y <= y_max; y += step) {
                // left point and color
                add_point(x_min, y, 0);
                if (y == 0) {
                    add_color(1.0f, 0.0f, 0.0f);
                } else {
                    // add_color(0.8f, 0.0f, 0.0f);
                    add_color(0.8f, 0.8f, 0.8f);
                }

                // to zero
                add_point(0, y, 0);
                if (y == 0) {
                    add_color(1.0f, 0.0f, 0.0f);
                } else {
                    float k;
                    if (y < 0) {
                        k = (float) y / (float) y_min;
                    } else {
                        k = (float) y / (float) y_max;
                    }
                    add_color(0.8f * k, 0.8f * k, 0.8f * k);
                    // add_color(0.8f, 0.0f, 0.0f);
                }

                // from zero
                add_point(0, y, 0);
                if (y == 0) {
                    add_color(1.0f, 0.0f, 0.0f);
                } else {
                    float k;
                    if (y < 0) {
                        k = (float) y / (float) y_min;
                    } else {
                        k = (float) y / (float) y_max;
                    }
                    add_color(0.8f * k, 0.8f * k, 0.8f * k);
                    // add_color(0.8f, 0.0f, 0.0f);
                }

                // right point and color
                add_point(x_max, y, 0);
                if (y == 0) {
                    add_color(1.0f, 0.0f, 0.0f);
                } else {
                    // add_color(0.8f, 0.0f, 0.0f);
                    add_color(0.8f, 0.8f, 0.8f);
                }
            }

            // vertical lines
            for (int x = x_min; x <= x_max; x += step) {
                // left point and color
                add_point(x, y_min, 0);
                if (x == 0) {
                    add_color(0.0f, 1.0f, 0.0f);
                } else {
                    // add_color(0.0f, 0.8f, 0.0f);
                    add_color(0.8f, 0.8f, 0.8f);
                }

                // to zero
                add_point(x, 0, 0);
                if (x == 0) {
                    add_color(0.0f, 1.0f, 0.0f);
                } else {
                    float k;
                    if (x < 0) {
                        k = (float) x / (float) x_min;
                    } else {
                        k = (float) x / (float) x_max;
                    }
                    add_color(0.8f * k, 0.8f * k, 0.8f * k);
                    // add_color(0.0f, 0.8f, 0.0f);
                }

                // from zero
                add_point(x, 0, 0);
                if (x == 0) {
                    add_color(0.0f, 1.0f, 0.0f);
                } else {
                    float k;
                    if (x < 0) {
                        k = (float) x / (float) x_min;
                    } else {
                        k = (float) x / (float) x_max;
                    }
                    add_color(0.8f * k, 0.8f * k, 0.8f * k);
                    // add_color(0.0f, 0.8f, 0.0f);
                }

                // right point and color
                add_point(x, y_max, 0);
                // right point color
                if (x == 0) {
                    add_color(0.0f, 1.0f, 0.0f);
                } else {
                    // add_color(0.0f, 0.8f, 0.0f);
                    add_color(0.8f, 0.8f, 0.8f);
                }
            }

        }

        [[nodiscard]] std::vector<float> geometry() const {
            return _vertices_with_colors;
        }

        [[nodiscard]] int count() const {
            return static_cast<int>(_vertices_with_colors.size());
        }

    private:
        void add_point(int x, int y, int z) {
            _vertices_with_colors.push_back((float) x);
            _vertices_with_colors.push_back((float) y);
            _vertices_with_colors.push_back((float) z);
        }

        void add_color(float r, float g, float b) {
            _vertices_with_colors.push_back(r);
            _vertices_with_colors.push_back(g);
            _vertices_with_colors.push_back(b);
        }
    };

}

#endif //INCLUDED_MN_GEOMETRY_AXES_2D_H
