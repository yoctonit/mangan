#include <iostream>
#include <fstream>
#include "../nlohmann/json.h"
#include "Font.h"


Font::Font(const std::string &fontName) {
    std::string fontImageFile = "fonts/" + fontName + ".png";
    mFontTexture = Mn::Texture(fontImageFile);

    std::string fontDescFile = "fonts/" + fontName + ".json";
    std::string fontDescription = LoadFile(fontDescFile);
    nlohmann::json fontInfo = nlohmann::json::parse(fontDescription);

    auto commonInfo = fontInfo["common"];
    if (commonInfo == nullptr) {
        std::cerr << "Font: no common data\n";
        return;
    }
    mCharHeight = commonInfo["base"].get<float>();

    auto chars = fontInfo["chars"];
    if (chars == nullptr) {
        std::cerr << "Font: no chars data\n";
        return;
    }

    for (auto c: chars) {
        int id = c["id"].get<int>();
        float x = c["x"].get<float>();
        float y = c["y"].get<float>();
        float width = c["width"].get<float>();
        float height = c["height"].get<float>();
        float xOffset = c["xoffset"].get<float>();
        float yOffset = c["yoffset"].get<float>();
        float xAdvance = c["xadvance"].get<float>();
        // int page = c["page"].get<int>(); // not used
        // int channel = c["chnl"].get<int>(); // not used

        CharacterInfo characterInfo{};

        auto texWidth = static_cast<float>(mFontTexture.Width());
        auto texHeight = static_cast<float>(mFontTexture.Height());

        float leftPixel = x;
        float rightPixel = leftPixel + width - 1.0f;
        float topPixel = (texHeight - 1.0f) - y;
        float bottomPixel = topPixel - height + 1.0f;

        // texture coordinate information
        characterInfo.TexCoordLeft = leftPixel / (texWidth - 1.0f);
        characterInfo.TexCoordTop = topPixel / (texHeight - 1.0f);
        characterInfo.TexCoordRight = rightPixel / (texWidth - 1.0f);
        characterInfo.TexCoordBottom = bottomPixel / (texHeight - 1.0f);

        // relative character size
        float charWidth = xAdvance;
        characterInfo.CharWidth = width / charWidth;
        characterInfo.CharHeight = height / mCharHeight;
        characterInfo.CharWidthOffset = xOffset / charWidth;
        characterInfo.CharHeightOffset = yOffset / mCharHeight;
        characterInfo.CharAspectRatio = charWidth / mCharHeight;

        mChars[id] = characterInfo;
    }

}

CharacterInfo Font::getCharInfo(int aChar) const {
    auto entry = mChars.find(aChar);
    if (entry == mChars.end()) {
        std::cerr << "No character with code " << aChar << " in font\n";
        return CharacterInfo{};
    }
    return entry->second;
    // return mChars.at(aChar);
}

Mn::Texture Font::getTexture() const {
    return mFontTexture;
}

std::string Font::LoadFile(const std::string &fileName) {
    std::ifstream fileStream(fileName, std::ios::in);
    if (!fileStream.is_open()) {
        std::cerr << "Could not open " << fileName << "\n";
        return ""; // throw exception?
    }

    std::stringstream str;
    str << fileStream.rdbuf();

    fileStream.close();
    return str.str();
}
