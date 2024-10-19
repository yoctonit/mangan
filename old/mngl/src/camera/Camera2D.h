#ifndef INCLUDED_MN_CAMERA_2D_H
#define INCLUDED_MN_CAMERA_2D_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Mn {

    class Camera2D {
    private:
        glm::vec2 _wc_center;
        float _wc_width;
        int _viewport_x;
        int _viewport_y;
        int _viewport_width;
        int _viewport_height;
        glm::vec4 _background_color{};
        glm::mat4 _camera_matrix;

    public:
        // wcCenter: is a vec2
        // wcWidth: is the width of the user defined WC
        //      Height of the user defined WC is implicitly defined by the viewport aspect ratio
        //      Please refer to the following
        // viewportRect: an array of 4 elements
        //      [0] [1]: (x,y) position of lower left corner on the canvas (in pixel)
        //      [2]: width of viewport
        //      [3]: height of viewport
        //
        //  wcHeight = wcWidth * viewport[3]/viewport[2]
        //
        Camera2D(
                glm::vec2 wc_center, float wc_width,
                int viewport_x, int viewport_y,
                int viewport_width, int viewport_height
        ) :
                _wc_center(wc_center),
                _wc_width(wc_width),
                _viewport_x(viewport_x),
                _viewport_y(viewport_y),
                _viewport_width(viewport_width),
                _viewport_height(viewport_height),
                _camera_matrix{1.0f} {
            _background_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
        }

        void wc_center(float x_pos, float y_pos) {
            _wc_center = {x_pos, y_pos};
        }

        [[nodiscard]] glm::vec2 wc_center() const { return _wc_center; }

        void wc_width(float width) { _wc_width = width; }

        [[nodiscard]] float wc_width() const { return _wc_width; }

        [[nodiscard]] float wc_height() const {
            float ratio = (float) _viewport_height / (float) _viewport_width;
            return _wc_width * ratio;
        }

        void background_color(float r, float g, float b, float a = 1.0f) {
            _background_color = glm::vec4(r, g, b, a);
        }

        [[nodiscard]] glm::vec4 background_color() const { return _background_color; }

        void setup_viewport() const {
            glViewport(_viewport_x,       // x position of bottom-left corner of the area to be drawn
                       _viewport_y,       // y position of bottom-left corner of the area to be drawn
                       _viewport_width,   // width of the area to be drawn
                       _viewport_height); // height of the area to be drawn
        }

        void clear_background() const {
            glClearColor(_background_color.r, _background_color.g, _background_color.b, _background_color.a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        // Compute the Camera Matrix; call before you start drawing with this camera
        void set_view_and_camera_matrix() {
            // following the translation, scale to (-1, -1) to (1, 1): a 2x2 square at origin
            _camera_matrix = glm::scale(glm::mat4{1.0f}, glm::vec3(2.0f / _wc_width, 2.0f / wc_height(), 1.0f));

            // first operation to perform is to translate camera center to the origin
            _camera_matrix = glm::translate(_camera_matrix, glm::vec3(-_wc_center.x, -_wc_center.y, 0.0f));
        }

        // Getter for the View-Projection transform operator
        [[nodiscard]] glm::mat4 matrix() const {
            return _camera_matrix;
        }

        glm::vec2 mouse_wc(const Mn::Input &input) {
            glm::vec2 wh{_wc_width, wc_height()};
            glm::vec2 min_wc = _wc_center - wh / 2.0f;

            float x_pos = input.mouse_x_position() - (float) _viewport_x;
            // reverse y position because input measures y from top of the window,
            // and in opengl we need y measured from bottom of the window
            float y_pos = ((float) _viewport_height - input.mouse_y_position()) - (float) _viewport_y;
            glm::vec2 mouse_dc{x_pos, y_pos};

            float aspect = _wc_width / (float) _viewport_width;
            return min_wc + mouse_dc * aspect;
        }

    };

}

#endif //INCLUDED_MN_CAMERA_2D_H
