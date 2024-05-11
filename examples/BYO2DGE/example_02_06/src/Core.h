#ifndef BYO2DGE_EXAMPLES_02_06_H
#define BYO2DGE_EXAMPLES_02_06_H

#include "SimpleShader.h"
#include "Square.h"

class Core {
public:
    void Initialize();

    void Release();

    void Clear() const;

    void Draw();

    void BackgroundColor(glm::vec4 c);

private:
    SimpleShader mSimpleShader{};
    Square mSquare{};
    Mn::Vao vao{};

    glm::vec4 mBackgroundColor{};
};

#endif //BYO2DGE_EXAMPLES_02_06_H
