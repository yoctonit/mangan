//
// Created by ivan on 9.5.2020..
//

#ifndef INCLUDED_GAME_GRID_H
#define INCLUDED_GAME_GRID_H

#include <array>

class game_grid {

public:
    game_grid();

    void display() const;
private:
    static const int width = 24;
    static const int height = 40;

    std::array<std::array<char, width>, height> _field;
};


#endif //INCLUDED_GAME_GRID_H
