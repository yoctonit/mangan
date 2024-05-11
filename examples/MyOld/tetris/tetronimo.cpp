//
// Created by ivan on 10.5.2020..
//

#include <iostream>
#include "tetronimo.h"

tetronimo::tetronimo(int width, int height)
: _width(width), _height(height), _pattern(nullptr) {}

tetronimo::~tetronimo() {
    delete [] _pattern;
}

void tetronimo::display() const {
    for (int row = _height - 1; row >= 0; --row) {
        for (int col = 0; col < _width; ++col) {
            std::cout << _pattern[row * _width + col];
        }
        std::cout << '\n';
    }
}

tetronimo_bar_left::tetronimo_bar_left() : tetronimo(6, 6) {
    _pattern = new char[_width * _height]{
            'X', 'X', 'X', 'X', ' ', ' ',
            'X', 'X', 'X', 'X', ' ', ' ',
            ' ', ' ', 'X', 'X', ' ', ' ',
            ' ', ' ', 'X', 'X', ' ', ' ',
            ' ', ' ', 'X', 'X', ' ', ' ',
            ' ', ' ', 'X', 'X', ' ', ' ',
    };
}
