//
// Created by ivan on 10.5.2020..
//

#ifndef INCLUDED_TETRONIMO_H
#define INCLUDED_TETRONIMO_H


class tetronimo {
public:
    tetronimo(int width, int height);
    ~tetronimo();

    void display() const;

protected:
    int _width;
    int _height;
    char * _pattern;
};

class tetronimo_bar_left : public tetronimo {
public:
    tetronimo_bar_left();
};


#endif //INCLUDED_TETRONIMO_H
