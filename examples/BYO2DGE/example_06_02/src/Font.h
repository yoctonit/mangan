#ifndef BYO2DGE_FONT_H
#define BYO2DGE_FONT_H

#include <unordered_map>
#include <string>
#include "core/Texture.h"

struct CharacterInfo {
    // in texture coordinate (0 to 1) maps to the entire image
    float TexCoordLeft{0.0f};
    float TexCoordRight{1.0f};
    float TexCoordBottom{0.0f};
    float TexCoordTop{0.0f};

    // reference to nominal character size, 1 is "standard width/height" of a char
    float CharWidth{1.0f};
    float CharHeight{1.0f};
    float CharWidthOffset{0.0f};
    float CharHeightOffset{0.0f};

    // reference of char width/height ratio
    float CharAspectRatio{1.0f};
};

class Font {
public:
    explicit Font(const std::string &fontName);

    CharacterInfo getCharInfo(int aChar) const;

    Mn::Texture getTexture() const;

private:
    Mn::Texture mFontTexture{};
    float mCharHeight{1.0f};
    std::unordered_map<int, CharacterInfo> mChars;

    /*
     * Read contents of the file as string
     * @param [in] fileName - Path to the file
     * @param [out] - On successful read file contents, on failed read empty string;
     */
    static std::string LoadFile(const std::string &fileName);
};

#endif //BYO2DGE_FONT_H
