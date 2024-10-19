//
// Created by Ivan on 17-Feb-23.
//

#ifndef OPENGL_EXAMPLES_CHARACTER_INFO_H
#define OPENGL_EXAMPLES_CHARACTER_INFO_H

/*
 * File: font.js
 *
 * logics for loading font into the resource_map
 * Note that "font" consists of two files
 *    => the bitmap font image
 *    => the associated xml descriptor file
 */

#include <memory>
#include <map>
#include <string>
#include <json.h>
#include "Texture.h"
#include "SceneFileParser.h"

using json = nlohmann::json;

class CharInfo {
public:
    int mId{};
    float mX{};
    float mY{};
    float mWidth{};
    float mHeight{};
    float mXOffset{};
    float mYOffset{};
    float mXAdvance{};

    void print() const {
        std::cout << "Char: " << mId << "\n";
        std::cout << "("
                  << mX << ", "
                  << mY << ", "
                  << mWidth << ", "
                  << mHeight << ", "
                  << mXOffset << ", "
                  << mYOffset << ", "
                  << mXAdvance << ")\n";
    }
};

// https://www.freeformatter.com/xml-to-json-converter.html#before-output
// for convenient communication of per-character information
// all size returned are in normalize unit (range between 0 and 1)
class CharacterInfo {
public:
    CharacterInfo() {
        // in texture coordinate (0 to 1) maps to the entire image
        mTexCoordLeft = 0.0f;
        mTexCoordRight = 1.0f;
        mTexCoordBottom = 0.0f;
        mTexCoordTop = 0.0f;

        // reference to nominal character size, 1 is "standard width/height" of a char
        mCharWidth = 1.0f;
        mCharHeight = 1.0f;
        mCharWidthOffset = 0.0f;
        mCharHeightOffset = 0.0f;

        // reference of char width/height ratio
        mCharAspectRatio = 1.0f;
    }

    float mTexCoordLeft{};
    float mTexCoordRight{};
    float mTexCoordBottom{};
    float mTexCoordTop{};

    // reference to nominal character size, 1 is "standard width/height" of a char
    float mCharWidth{};
    float mCharHeight{};
    float mCharWidthOffset{};
    float mCharHeightOffset{};

    // reference of char width/height ratio
    float mCharAspectRatio{};
};

class FontInfo {
public:
    float mBase{};
    bool mError{};
    std::map<int, CharInfo> mCharMap;

    void print() const {
        std::cout << "Common->base: " << mBase << "\n";
        for (const auto &it: mCharMap) {
            it.second.print();
        }
    }

    CharInfo get(int charId) {
        return mCharMap[charId];
    }

    CharacterInfo getCharInfo(
            char aChar,
            const std::shared_ptr<Mn::Texture> &tex) {
        CharacterInfo returnInfo;

        // SceneFileParser sfp(descName(fontName));
        // FontInfo fontInfo = sfp.parseFonts();
        if (mError) {
            return returnInfo;
        }

        // let fontInfo = xml.get(descName(fontName));
        // const std::string commonPath = "font/common";
        // let commonInfo = fontInfo.evaluate(commonPath, fontInfo, null, XPathResult.ANY_TYPE, null);
        // commonInfo = commonInfo.iterateNext();
//    if (commonInfo === null) {
//        return returnInfo;
//    }
        // let charHeight = commonInfo.getAttribute("base");
        float charHeight = mBase;

        // std::string charPath = "font/chars/char[@id=" + aChar + "]";
        // let charInfo = fontInfo.evaluate(charPath, fontInfo, null, XPathResult.ANY_TYPE, null);
        // charInfo = charInfo.iterateNext();
//    if (charInfo == nullptr) {
//        return returnInfo;
//    }

        CharInfo charInfo = get(aChar);
        // let texInfo = texture.get(imageName(fontName));
        float leftPixel = charInfo.mX;
        float rightPixel = leftPixel + charInfo.mWidth - 1;
        float topPixel = ((float) tex->height() - 1.0f) - charInfo.mY;
        float bottomPixel = topPixel - charInfo.mHeight + 1;
//    let leftPixel = Number(charInfo.getAttribute("x"));
//    let rightPixel = leftPixel + Number(charInfo.getAttribute("width")) - 1;
//    let topPixel = (tex->height() - 1) - Number(charInfo.getAttribute("y"));
//    let bottomPixel = topPixel - Number(charInfo.getAttribute("height")) + 1;

        // texture coordinate information
        returnInfo.mTexCoordLeft = leftPixel / ((float) tex->width() - 1.0f);
        returnInfo.mTexCoordTop = topPixel / ((float) tex->height() - 1.0f);
        returnInfo.mTexCoordRight = rightPixel / ((float) tex->width() - 1.0f);
        returnInfo.mTexCoordBottom = bottomPixel / ((float) tex->height() - 1.0f);

        // relative character size
        float charWidth = charInfo.mXAdvance;
        returnInfo.mCharWidth = charInfo.mWidth / charWidth;
        returnInfo.mCharHeight = charInfo.mHeight / charHeight;
        returnInfo.mCharWidthOffset = charInfo.mXOffset / charWidth;
        returnInfo.mCharHeightOffset = charInfo.mYOffset / charHeight;
        returnInfo.mCharAspectRatio = charWidth / charHeight;

        return returnInfo;
    }

};

FontInfo parseFonts(const std::string &file_path) {
    std::string sceneDefinition = Mn::Util::Load(file_path);
    json data = json::parse(sceneDefinition);

    FontInfo fontInfo;
    auto common = data["common"];
    if (common == nullptr) {
        std::cout << "No common data for font\n";
        fontInfo.mError = true;
        return fontInfo;
    }
    fontInfo.mBase = common["base"].get<float>();

    auto chars = data["chars"];
    if (chars == nullptr) {
        std::cout << "No characters data for font\n";
        fontInfo.mError = true;
        return fontInfo;
    }
    for (auto c: chars) {
        CharInfo ci;
        ci.mId = c["id"].get<int>();
        ci.mX = (float)c["x"].get<int>();
        ci.mY = (float)c["y"].get<int>();
        ci.mWidth = (float)c["width"].get<int>();
        ci.mHeight = (float)c["height"].get<int>();
        ci.mXOffset = (float)c["xoffset"].get<int>();
        ci.mYOffset = (float)c["yoffset"].get<int>();
        ci.mXAdvance = (float)c["xadvance"].get<int>();
        fontInfo.mCharMap[ci.mId] = ci;
    }
    return fontInfo;
}

//std::string imageName(const std::string& fontName) {
//    const std::string kImageExt = ".png";
//    return fontName + kImageExt;
//}
//std::string descName(const std::string& fontName) {
//    // std::string kDescExt = ".fnt";
//    std::string kDescExt = ".json";
//    return fontName + kDescExt;
//}

//function load(std::string fontName) {
//    texture.load(imageName(fontName));
//    xml.load(descName(fontName));
//}

// Remove the reference to allow associated memory
// be available for subsequent garbage collection
//function unload(fontName) {
//    texture.unload(imageName(fontName));
//    xml.unload(descName(fontName));
//}

//function has(fontName) {
//    return texture.has(imageName(fontName)) && xml.has(descName(fontName));
//}

#endif //OPENGL_EXAMPLES_CHARACTER_INFO_H
