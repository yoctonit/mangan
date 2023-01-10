//
// Created by ivan on 7.5.2020..
//

#include <iostream>
#include <map>
#include <string>

#include "glad/glad.h"
#include "core/window/gl_window.h"
#include "core/shader/program_library.h"
#include "core/buffer/gpu_buffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

mn::gpu_buffer buffer;

GLint shader_program_id;
GLint vertex_pos_location;
GLuint vertex_array_id;
GLint u_projection;
GLint u_text_color;

glm::mat4 projection;

void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    FT_Pos Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;


void setup() {
    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "vertex.glsl", "fragment.glsl");

    shader_program_id = program.handle();
    vertex_pos_location = program.location("vertex");
    u_projection = program.location("u_projection");
    u_text_color = program.location("u_text_color");

    projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
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
    for (unsigned char c = 0; c < 128; ++c)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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

    // Vertex array initialization
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    buffer.create(6 * 4 * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buffer.activate();

    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 4, GL_FLOAT, GL_FALSE,
                          4 * sizeof(float), nullptr);

    glBindVertexArray(0);

//    // configure VAO/VBO for texture quads
//    // -----------------------------------
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_id);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

    RenderText("This is sample text, ah yea!", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
    RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
}

int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(SCR_WIDTH, SCR_HEIGHT, "FreeType Text", 4, 6)) {
        window.clean_up();
        return 1;
    }
    SCR_WIDTH = window.width();
    SCR_HEIGHT = window.height();

    window.set_setup(setup);
    window.set_draw(draw);

    window.action();

    return 0;
}


// render line of text
// -------------------
void RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    glUseProgram(shader_program_id);

    glUniform3f(u_text_color, color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    // glBindVertexArray(VAO);
    glBindVertexArray(vertex_array_id);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); ++c)
    {
        Character ch = Characters[*c];

        float x_pos = x + ch.Bearing.x * scale;
        auto size_y = static_cast<float>(ch.Size.y);
        auto bearing_y = static_cast<float>(ch.Bearing.y);
        // float y_pos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float y_pos = y - (size_y - bearing_y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
//        float vertices[6][4] = {
//                { x_pos,     y_pos + h,   0.0f, 0.0f },
//                { x_pos,     y_pos,       0.0f, 1.0f },
//                { x_pos + w, y_pos,       1.0f, 1.0f },
//
//                { x_pos,     y_pos + h,   0.0f, 0.0f },
//                { x_pos + w, y_pos,       1.0f, 1.0f },
//                { x_pos + w, y_pos + h,   1.0f, 0.0f }
//        };
        float vertices[24] = {
                x_pos,     y_pos + h,   0.0f, 0.0f,
                x_pos,     y_pos,       0.0f, 1.0f,
                x_pos + w, y_pos,       1.0f, 1.0f,

                x_pos,     y_pos + h,   0.0f, 0.0f,
                x_pos + w, y_pos,       1.0f, 1.0f,
                x_pos + w, y_pos + h,   1.0f, 0.0f
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

//        // update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        buffer.load_data_at_offset(0, 6 * 4 * sizeof(GLfloat), vertices);

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
