//
// Created by ivan on 9.5.2020..
//

#include <iostream>
#include "game_grid.h"

game_grid::game_grid() : _field() {
    for (int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col) {
            if (col == 0 || col == width - 1 || row == 0) {
                _field[row][col] = 'X';
            } else {
                _field[row][col] = ' ';
            }
        }
}

void game_grid::display() const {
    for (int row = height - 1; row >= 0; --row) {
        for (int col = 0; col < width; ++col) {
            std::cout << _field[row][col];
        }
        std::cout << '\n';
    }
}
