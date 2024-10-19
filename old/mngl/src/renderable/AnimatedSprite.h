#ifndef INCLUDED_MN_RENDERABLE_ANIMATED_SPRITE_H
#define INCLUDED_MN_RENDERABLE_ANIMATED_SPRITE_H

#include <memory>
#include "core/Texture.h"
#include "shader/Texture.h"
#include <geometry/Square.h>
#include "connection/Sprite.h"
#include "Transform.h"

namespace Mn::renderable {

    enum class AnimationType {
        right = 0,     // Animate from first (left) towards right, when hit the end, start from the left again
        left = 1,      // Compute find the last element (in the right), start from the right animate left-wards,
        swing = 2      // Animate from first (left) towards the right, when hit the end, animates backwards
    };

    class AnimatedSprite {
    private:
        std::shared_ptr<Mn::connection::Sprite> _connection;
        std::shared_ptr<Mn::Texture> _texture;
        std::shared_ptr<Mn::Transform> _transform;
        glm::vec4 _color;
        int _texture_unit;
        std::shared_ptr<Mn::geometry::square_sprite> _ss;
        GLenum _mode;
        GLint _first;
        GLsizei _count;

        // All coordinates are in texture coordinate (UV between 0 and 1)
        // Information on the sprite element
        float _first_elm_left{}; // 0.0 is left corner of image
        float _elm_top{};        // 1.0 is top corner of image
        float _elm_width{};
        float _elm_height{};
        float _width_padding{};
        int _num_elems{};        // number of elements in an animation

        // per animation settings
        AnimationType _animation_type;
        int _update_interval{};  // how often to advance

        int _current_anim_advance{};
        int _current_elm{};
        int _current_tick{};

    public:

        AnimatedSprite(
                const std::shared_ptr<Mn::connection::Sprite> &connection,
                const std::shared_ptr<Mn::Texture> &texture,
                GLenum mode, GLint first, GLsizei count) :
                _connection{connection},
                _texture{texture},
                _transform{std::make_shared<Mn::Transform>()},
                _color{1.0f, 1.0f, 1.0f, 0.0f},
                _texture_unit{0},
                _mode{mode},
                _first{first},
                _count{count} {

            _ss = std::make_shared<Mn::geometry::square_sprite>(_texture->width(), _texture->height());
            _first_elm_left = 0.0f;
            _elm_top = 1.0f;
            _elm_width = 1.0f;
            _elm_height = 1.0f;
            _width_padding = 0.0f;
            _num_elems = 1;

            _animation_type = AnimationType::right;
            _update_interval = 10;

            _current_anim_advance = -1;
            _current_elm = 0;
            _init_animation();
        }

        void draw(glm::mat4 view) const {
            _connection->texture_coord_buffer()->load(_ss->element_uv_coordinates());
            _texture->activate(_texture_unit);
            _connection->shader()->configure(_transform->matrix(), view, _color, _texture_unit);
            _connection->vao()->draw(_mode, _first, _count);
        }

        std::shared_ptr<Mn::Transform> transform() { return _transform; }

        void color(float r, float g, float b, float a = 1.0f) {
            _color = glm::vec4(r, g, b, a);
        }

        void texture_unit(int tu) { _texture_unit = tu; }

        void mode(GLenum m) { _mode = m; }

        void first(GLint f) { _first = f; }

        void count(GLsizei c) { _count = c; }

        void range(GLint f, GLsizei c) {
            _first = f;
            _count = c;
        }

        // Always set the left-most element to be the first
        void sprite_sequence(
                float top_pixel,   // offset from top-left
                float left_pixel, // offset from top-left
                float elm_width_in_pixel,
                float elm_height_in_pixel,
                float w_padding_in_pixel,  // left/right padding
                int num_elements      // number of elements in sequence
        ) {
            // entire image width, height
            auto imageW = (float) _texture->width();
            auto imageH = (float) _texture->height();

            _num_elems = num_elements;   // number of elements in animation
            _first_elm_left = left_pixel / imageW;
            _elm_top = top_pixel / imageH;
            _elm_width = elm_width_in_pixel / imageW;
            _elm_height = elm_height_in_pixel / imageH;
            _width_padding = w_padding_in_pixel / imageW;
            _init_animation();
        }

        // number of update calls before advancing the animation
        void animation_speed(int tick_interval) {
            _update_interval = tick_interval;
        }

        // number of update calls before advancing the animation
        void inc_animation_speed(int delta_interval) {
            _update_interval += delta_interval;
        }

        [[nodiscard]] AnimationType animation_type() const { return _animation_type; }

        void animation_type(AnimationType type) {
            _animation_type = type;
            _current_anim_advance = -1;
            _current_elm = 0;
            _init_animation();
        }

        void update_animation() {
            _current_tick++;
            if (_current_tick >= _update_interval) {
                _current_tick = 0;
                _current_elm += _current_anim_advance;
                if ((_current_elm >= 0) && (_current_elm < _num_elems)) {
                    _set_sprite_element();
                } else {
                    _init_animation();
                }
            }
        }

    private:
        void _init_animation() {
            _current_tick = 0;
            switch (_animation_type) {
                case AnimationType::swing:
                    _current_anim_advance = -1 * _current_anim_advance; // swings ...
                    _current_elm += 2 * _current_anim_advance;
                    break;
                case AnimationType::right:
                    _current_elm = 0;
                    _current_anim_advance = 1; // either 1 or -1
                    break;
                case AnimationType::left:
                    _current_elm = _num_elems - 1;
                    _current_anim_advance = -1; // either 1 or -1
                    break;
            }
            _set_sprite_element();
        }

        void _set_sprite_element() {
            float left = _first_elm_left + ((float) _current_elm * (_elm_width + _width_padding));
            _ss->element_uv_coordinates(left, left + _elm_width, _elm_top - _elm_height, _elm_top);
        }

    };

}

#endif //INCLUDED_MN_RENDERABLE_ANIMATED_SPRITE_H
