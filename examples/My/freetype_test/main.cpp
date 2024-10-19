#include <iostream>
#include <map>
#include <string>

#include "glad/glad.h"
#include "window/Window.h"
#include "core/Shader.h"
#include "core/Vbo.h"
#include "core/Vao.h"
#include "graphics/Uniform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H


void RenderText(const Mn::Vao& vao, const Mn::Vbo& buffer, std::string text, float x, float y, float scale);

// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;     // ID handle of the glyph texture
    glm::ivec2 Size;      // Size of glyph
    glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
    FT_Pos Advance;       // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;


int main() {
    Mn::Window wnd{SCR_WIDTH, SCR_HEIGHT, "FreeType Text"};

    Mn::Shader shader{"shader/vertex.glsl", "shader/fragment.glsl"};
    Mn::Uniform uProjection{shader.Locate("u_projection"), GL_FLOAT_MAT4};
    Mn::Uniform uTextColor{shader.Locate("u_text_color"), GL_FLOAT_VEC3};

    // vertex_pos_location = program.location("vertex");

    uProjection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different from 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, "fonts/LinLibertine_R.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set
    for (unsigned char c = 0; c < 128; ++c) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    std::vector<float> dataSpace;
    dataSpace.resize(6 * 4 * sizeof(GLfloat));
    Mn::Vbo buffer{dataSpace, GL_DYNAMIC_DRAW};
//    buffer.create(6 * 4 * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
//    buffer.activate();

    // Vertex array initialization
    Mn::Vao vao{true};
    vao.Connect(buffer, shader.Locate("vertex"), 4, 4, 0);



//    glEnableVertexAttribArray(vertex_pos_location);
//    glVertexAttribPointer(vertex_pos_location, 4, GL_FLOAT, GL_FALSE,
//                          4 * sizeof(float), nullptr);
//
//    glBindVertexArray(0);

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
            continue;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        uProjection.Upload();
        uTextColor = glm::vec3(0.5, 0.8f, 0.2f);
        uTextColor.Upload();

        vao.Activate();
        RenderText(vao, buffer, "This is sample text, ah yea!", 25.0f, 25.0f, 1.0f);

        uTextColor = glm::vec3(0.3, 0.7f, 0.9f);
        uTextColor.Upload();
        RenderText(vao, buffer, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f);

        wnd.Display();
    }

    return 0;
}


// render line of text
// -------------------
void RenderText(const Mn::Vao& vao, const Mn::Vbo& buffer, std::string text, float x, float y, float scale) {

    glActiveTexture(GL_TEXTURE0);
    vao.Activate();

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); ++c) {
        Character ch = Characters[*c];

        float x_pos = x + ch.Bearing.x * scale;
        auto size_y = static_cast<float>(ch.Size.y);
        auto bearing_y = static_cast<float>(ch.Bearing.y);
        // float y_pos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float y_pos = y - (size_y - bearing_y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        std::vector<float> vertices = {
                x_pos, y_pos + h, 0.0f, 0.0f,
                x_pos, y_pos, 0.0f, 1.0f,
                x_pos + w, y_pos, 1.0f, 1.0f,

                x_pos, y_pos + h, 0.0f, 0.0f,
                x_pos + w, y_pos, 1.0f, 1.0f,
                x_pos + w, y_pos + h, 1.0f, 0.0f
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        buffer.Load(vertices);

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) *
             scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
