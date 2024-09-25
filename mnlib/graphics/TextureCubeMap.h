#ifndef INCLUDED_MN_GRAPHICS_TEXTURE_CUBE_MAP_H
#define INCLUDED_MN_GRAPHICS_TEXTURE_CUBE_MAP_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <vector>


namespace Mn {

    class TextureCubeMap {
    public:
        TextureCubeMap();

        explicit TextureCubeMap(const std::vector<std::string> &faces);

        ~TextureCubeMap();

        TextureCubeMap(const TextureCubeMap &other);

        TextureCubeMap &operator=(const TextureCubeMap &other);

        [[nodiscard]] unsigned int Id() const;

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        void Activate(int textureUnit = 0) const;

        void SetParameters(int magFilter, int minFilter, int wrap) const;

        void Debug(const std::string &msg) const;

        static void DebugRefCnt();

    private:
        unsigned int mId{};
        int mWidth{};
        int mHeight{};

        //////////////////////
        // Reference count map
        //////////////////////
        static std::unordered_map<unsigned int, int> mRefCnt;

        void IncRef() const;

        [[nodiscard]] int DecRef() const;
    };

}
#endif //INCLUDED_MN_GRAPHICS_TEXTURE_CUBE_MAP_H
