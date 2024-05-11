#include "Point.h"

Point::Point() = default;

Point::Point(float x_pos, float y_pos, float color_r, float color_g, float color_b) :
        x{x_pos}, y{y_pos}, r{color_r}, g{color_g}, b{color_b} {}

