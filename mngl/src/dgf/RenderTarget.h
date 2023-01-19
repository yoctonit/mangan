//
// Created by Ivan on 18-Jan-23.
//

#ifndef INCLUDED_MN_RENDER_TARGET_H
#define INCLUDED_MN_RENDER_TARGET_H

#include "glm/glm.hpp"
#include "Texture.h"
#include <memory>
#include <iostream>

class RenderTarget {
// store associated texture dimensions
public:
    int width;
    int height;
    std::shared_ptr<Texture> texture;
    GLuint framebufferRef;

    RenderTarget(glm::vec2 resolution) {
        width = (int) resolution.x;
        height = (int) resolution.y;
// generate an empty texture
        texture = std::make_shared<Texture>(width, height);
// create a framebuffer
        glGenFramebuffers(1, &framebufferRef);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferRef);
// configure color buffer to use this texture
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->textureRef, 0);
// generate a buffer to store depth information
        GLuint depthBufferRef;
        glGenRenderbuffers(1, &depthBufferRef);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBufferRef);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferRef);
// check framebuffer status
        int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer status error: " << status << "\n";
    }
};

#endif //INCLUDED_MN_RENDER_TARGET_H
