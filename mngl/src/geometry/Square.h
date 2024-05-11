#ifndef INCLUDED_MN_GEOMETRY_SQUARE_H
#define INCLUDED_MN_GEOMETRY_SQUARE_H

#include <vector>

namespace Mn::geometry {

    std::vector<float> square(float side = 1.0f) {
        float half_side = 0.5f * side;
        return {
                half_side, half_side, 0.0f,
                -half_side, half_side, 0.0f,
                half_side, -half_side, 0.0f,
                -half_side, -half_side, 0.0f
        };
    }

    std::vector<float> textured_square(float side) {
        float half_side = 0.5f * side;
        return {
                half_side, half_side, 0.0f, 1.0f, 1.0f,
                -half_side, half_side, 0.0f, 0.0f, 1.0f,
                half_side, -half_side, 0.0f, 1.0f, 0.0f,
                -half_side, -half_side, 0.0f, 0.0f, 0.0f
        };
    }

    std::vector<float> square_uv() {
        return {
                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
        };
    }

    class square_sprite {
    private:
        float _elm_left;   // bounds of texture coordinate (0 is left, 1 is right)
        float _elm_right;
        float _elm_top;    // 1 is top and 0 is bottom of image
        float _elm_bottom;
        float _texture_width;
        float _texture_height;

    public:
        square_sprite(int texture_width, int texture_height) :
                _elm_left{0.0f},
                _elm_right{1.0f},
                _elm_top{1.0f},
                _elm_bottom{0.0f} {
            _texture_width = float(texture_width);
            _texture_height = float(texture_height);
        }

        // specify element region by texture coordinate (between 0 and 1)
        void element_uv_coordinates(float left, float right, float bottom, float top) {
            _elm_left = left;
            _elm_right = right;
            _elm_bottom = bottom;
            _elm_top = top;
        }

        // specify element region by pixel positions (between 0 to image resolution)
        void element_pixel_positions(float left, float right, float bottom, float top) {
            _elm_left = left / _texture_width;
            _elm_right = right / _texture_width;
            _elm_bottom = bottom / _texture_height;
            _elm_top = top / _texture_height;
        }

        [[nodiscard]] std::vector<float> element_uv_coordinates() const {
            // matches order of square geometry points
            return {
                    _elm_right, _elm_top,
                    _elm_left, _elm_top,
                    _elm_right, _elm_bottom,
                    _elm_left, _elm_bottom
            };
        }
    };

}

#endif //INCLUDED_MN_GEOMETRY_SQUARE_H
