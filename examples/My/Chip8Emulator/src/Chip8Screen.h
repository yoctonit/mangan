#ifndef EXAMPLES_CHIP8_SCREEN_H
#define EXAMPLES_CHIP8_SCREEN_H

#include <vector>


class Chip8Screen {
public:

    void Init();

    void SetPixel(int x, int y);

    [[nodiscard]] bool IsPixelSet(int x, int y) const;

    bool DrawSprite(int x, int y, const unsigned char *sprite, int num);

    void Clear();

private:
    std::vector<bool> pixels_;

    static void CheckBounds(int x, int y);
};

#endif //EXAMPLES_CHIP8_SCREEN_H
