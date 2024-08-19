#ifndef INCLUDED_MN_GRAPHICS_TEXTURE_H
#define INCLUDED_MN_GRAPHICS_TEXTURE_H

#include <glad/glad.h>
#include <string>


namespace Mn {

    class Texture {
    public:
        static Texture FromImage(const std::string &fileName);

        // Texture(int width, int height, int magFilter, int minFilter, int wrap);

        // Texture(int width, int height);

        [[nodiscard]] unsigned int Id() const;

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        void Activate(int textureUnit = 0) const;

        // static void Deactivate();

        void SetParameters(int magFilter, int minFilter, int wrap) const;

        void Release();

        void Debug(const std::string &msg) const;

    private:
        unsigned int m_id{};
        int m_width{};
        int m_height{};
    };

}
#endif //INCLUDED_MN_GRAPHICS_TEXTURE_H
