#ifndef INCLUDED_MN_TRANSFORM_H
#define INCLUDED_MN_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Mn {

    class Transform {
    private:
        glm::vec2 _position;    // translation
        glm::vec2 _scale;       // width (x), height (y)
        float _rotation_in_rad; // in radians!

    public:
        Transform() : _position{0.0f, 0.0f}, _scale{1.0f, 1.0f}, _rotation_in_rad{} {}

        void position(float x_pos, float y_pos) { _position = glm::vec2(x_pos, y_pos); }

        [[nodiscard]] glm::vec2 position() const { return _position; }

        [[nodiscard]] float x_position() const { return _position.x; }

        void x_position(float x_pos) { _position.x = x_pos; }

        void inc_x_position_by(float delta) { _position.x += delta; }

        [[nodiscard]] float y_position() const { return _position.y; }

        void y_position(float y_pos) { _position.y = y_pos; }

        void inc_y_position_by(float delta) { _position.y += delta; }

        void size(float width, float height) { _scale = glm::vec2(width, height); }

        [[nodiscard]] glm::vec2 size() const { return _scale; }

        void inc_size_by(float delta) {
            inc_width_by(delta);
            inc_height_by(delta);
        }

        [[nodiscard]] float width() const { return _scale.x; }

        void width(float w) { _scale.x = w; }

        void inc_width_by(float delta) { _scale.x += delta; }

        [[nodiscard]] float height() const { return _scale.y; }

        void height(float h) { _scale.y = h; }

        void inc_height_by(float delta) { _scale.y += delta; }

        void rotation_in_rad(float rad) {
            _rotation_in_rad = rad;
            while (_rotation_in_rad > (2.0f * M_PI)) {
                _rotation_in_rad -= (2.0f * M_2_PI);
            }
        }

        void rotation_in_degree(float deg) {
            rotation_in_rad(glm::radians(deg));
        }

        void inc_rotation_by_degree(float delta_deg) {
            inc_rotation_by_rad(glm::radians(delta_deg));
        }

        void inc_rotation_by_rad(float delta_rad) {
            rotation_in_rad(_rotation_in_rad + delta_rad);
        }

        [[nodiscard]] float rotation_in_rad() const { return _rotation_in_rad; }

        [[nodiscard]] float rotation_in_degree() const { return glm::degrees(_rotation_in_rad); }

        // returns the matrix that concatenates the transformations defined
        [[nodiscard]] glm::mat4 matrix() const {
            glm::mat4 matrix{1.0f};

            matrix = glm::translate(matrix, glm::vec3(_position, 0.0f));
            matrix = glm::rotate(matrix, rotation_in_rad(), glm::vec3(0.0f, 0.0f, 1.0f));
            matrix = glm::scale(matrix, glm::vec3(width(), height(), 1.0f));

            return matrix;
        }
    };

}

#endif //INCLUDED_MN_TRANSFORM_H
