#ifndef EXAMPLES_POINT_H
#define EXAMPLES_POINT_H

class Point {
public:
    Point();

    Point(float x_pos, float y_pos, float color_r, float color_g, float color_b);

    float x{}, y{};
    float r{}, g{}, b{};
};

#endif //EXAMPLES_POINT_H
