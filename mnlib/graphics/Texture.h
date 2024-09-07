#ifndef INCLUDED_MN_GRAPHICS_TEXTURE_H
#define INCLUDED_MN_GRAPHICS_TEXTURE_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>


namespace Mn {

    class Texture {
    public:
//        static Texture FromImage(const std::string &fileName);

        Texture();

        explicit Texture(const std::string &fileName);

        ~Texture();

        Texture(const Texture &other);

        Texture &operator=(const Texture &other);

        // Texture(int width, int height, int magFilter, int minFilter, int wrap);

        // Texture(int width, int height);

        [[nodiscard]] unsigned int Id() const;

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        void Activate(int textureUnit = 0) const;

        // static void Deactivate();

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
#endif //INCLUDED_MN_GRAPHICS_TEXTURE_H
