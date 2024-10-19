//
// Created by Ivan on 18-Feb-23.
//

#ifndef OPENGL_EXAMPLES_FONT_RENDERABLE_H
#define OPENGL_EXAMPLES_FONT_RENDERABLE_H

/*
 * Supports the drawing of a string based on a selected Font
 */

#include "../Transform.h"
#include "../Camera.h"
#include "SpriteRenderable.h"
#include "../CharacterInfo.h"

class FontRenderable {
public:
    FontRenderable(const std::string& aString, FontInfo& f, const std::shared_ptr<SpriteRenderable>& sprite) : mFont{f} {
        mFontName = "assets/fonts/system_default_font";
        mOneChar = sprite;
        mXform = std::make_shared<Transform>();
        mText = aString;
        mTexture = sprite->getTexture();
    }

    void draw(const Camera &camera) {
        // we will draw the text string by calling to mOneChar for each of the
        // chars in the mText string.
        float widthOfOneChar = mXform->getWidth() / (float) mText.size();
        float heightOfOneChar = mXform->getHeight();
        // mOneChar.getXform().SetRotationInRad(mXform.getRotationInRad());
        float yPos = mXform->getYPos();

        // center position of the first char
        float xPos = mXform->getXPos() - (widthOfOneChar / 2.0f) + (widthOfOneChar * 0.5f);
        int charIndex;
        char aChar;
        CharacterInfo chInfo;
        float xSize, ySize, xOffset, yOffset;
        for (charIndex = 0; charIndex < mText.size(); charIndex++) {
            // aChar = mText.charCodeAt(charIndex);
            aChar = mText[charIndex];
            // aChar = 'A';
            chInfo = mFont.getCharInfo(aChar, mTexture);

            // set the texture coordinate
            mOneChar->setElementUVCoordinate(
                    chInfo.mTexCoordLeft,
                    chInfo.mTexCoordRight,
                    chInfo.mTexCoordBottom,
                    chInfo.mTexCoordTop);

            // now the size of the char
            xSize = widthOfOneChar * chInfo.mCharWidth;
            ySize = heightOfOneChar * chInfo.mCharHeight;
            mOneChar->getXform()->setSize(xSize, ySize);

            // how much to offset from the center
            xOffset = widthOfOneChar * chInfo.mCharWidthOffset * 0.5f;
            yOffset = heightOfOneChar * chInfo.mCharHeightOffset * 0.5f;

            mOneChar->getXform()->setPosition(xPos - xOffset, yPos - yOffset);

            mOneChar->draw(camera);

            xPos += widthOfOneChar;
        }
    }

    std::shared_ptr<Transform> getXform() { return mXform; }

    std::string getText() { return mText; }
    void setText(const std::string &t) {
            mText = t;
            setTextHeight(getXform()->getHeight());
    }

    void setTextHeight(float h) {
            CharacterInfo chInfo = mFont.getCharInfo('A', mTexture); // this is for "A"
//            CharacterInfo chInfo = mFont.getCharInfo("A".charCodeAt(0)); // this is for "A"
            float w = h * chInfo.mCharAspectRatio;
            getXform()->setSize(w * (float)mText.size(), h);
    }

    std::string getFontName() { return mFontName; }
//    void setFontName(const std::string& f) {
//            mFontName = f;
//            mOneChar->setTexture(mFont.imageName(mFontName));
//    }

    void setColor(glm::vec4 c) { mOneChar->setColor(c); }
    glm::vec4 getColor() { return mOneChar->getColor(); }

    // void update() {}

    /*
     * this can be a potentially useful function. Not included/tested in this version of the engine
    getStringWidth(h) {
        let stringWidth = 0;
        let charSize = h;
        let charIndex, aChar, chInfo;
        for (charIndex = 0; charIndex < mText.length; charIndex++) {
            aChar = mText.charCodeAt(charIndex);
            chInfo = font.getCharInfo(mFont, aChar);
            stringWidth += charSize * chInfo.mCharWidth * chInfo.mXAdvance;
        }
        return stringWidth;
    }
    */
private:
    std::string mFontName;
    std::shared_ptr<SpriteRenderable> mOneChar;
    std::shared_ptr<Transform> mXform; // transform that moves this object around
    std::string mText;
    FontInfo& mFont;
    std::shared_ptr<Mn::Texture> mTexture{};
};

#endif //OPENGL_EXAMPLES_FONT_RENDERABLE_H
