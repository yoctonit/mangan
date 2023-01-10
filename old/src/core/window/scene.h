//
// Created by ivan on 21.4.2020..
//
#ifndef INCLUDED_SCENE_H
#define INCLUDED_SCENE_H

namespace mn {

    class input;

    class scene {
    public:
        scene(int width, int height) : _width(width), _height(height) {}
        virtual void clear() {}
        virtual void initialize() {}
        virtual void update(double seconds, const input& user_input) {}
        virtual void draw() = 0;

        virtual ~scene() = default;

    protected:
        int _width;
        int _height;
    };

}

#endif // INCLUDED_SCENE_H
