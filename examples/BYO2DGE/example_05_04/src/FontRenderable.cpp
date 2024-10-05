#include "FontRenderable.h"

FontRenderable::FontRenderable() = default;

FontRenderable::FontRenderable(
        const Font *font,
        SpriteRenderable &spriteRenderable,
        const std::string &text
) : mFont{font} {
    mOneChar = spriteRenderable;
    mText = text;
}

void FontRenderable::draw(const Camera &camera) {
    // we will draw the text string by calling to mOneChar
    // for each of the chars in the mText string.
    float widthOfOneChar = mXform.getWidth() / static_cast<float>(mText.size());
    float heightOfOneChar = mXform.getHeight();
    float yPos = mXform.getYPos();

    // center position of the first char
    // float xPos = mXform.getXPos() - (widthOfOneChar / 2.0f) + (widthOfOneChar * 0.5f); // same as mXform.getXPos()?
    float xPos = mXform.getXPos();
    float xSize, ySize, xOffset, yOffset;

    for (char &c: mText) {
        int aChar = static_cast<int>(static_cast<unsigned char>(c));
        CharacterInfo charInfo = mFont->getCharInfo(aChar);

        // set the texture coordinate
        mOneChar.setElementUVCoordinate(
                charInfo.TexCoordLeft,
                charInfo.TexCoordRight,
                charInfo.TexCoordBottom,
                charInfo.TexCoordTop
        );

        // now the size of the char
        xSize = widthOfOneChar * charInfo.CharWidth;
        ySize = heightOfOneChar * charInfo.CharHeight;
        mOneChar.getXform().setSize(xSize, ySize);

        // how much to offset from the center
        xOffset = widthOfOneChar * charInfo.CharWidthOffset * 0.5f;
        yOffset = heightOfOneChar * charInfo.CharHeightOffset * 0.5f;

        mOneChar.getXform().setPosition(xPos - xOffset, yPos - yOffset);

        mOneChar.draw(camera);

        xPos += widthOfOneChar;
    }
}

void FontRenderable::setColor(glm::vec4 color) {
    mOneChar.setColor(color);
}

glm::vec4 FontRenderable::getColor() const {
    return mOneChar.getColor();
}

Transform &FontRenderable::getXform() {
    return mXform;
}

void FontRenderable::setTextHeight(float h) {
    const CharacterInfo charInfo = mFont->getCharInfo('A');
    float w = h * charInfo.CharAspectRatio;
    mXform.setSize(w * static_cast<float>(mText.size()), h);
}

void FontRenderable::setText(const std::string &text) {
    mText = text;
    setTextHeight(mXform.getHeight());
}

std::string FontRenderable::getText() const {
    return mText;
}
