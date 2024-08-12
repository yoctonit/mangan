#include <glad/glad.h>
#include <iostream>
#include "RenderTarget.h"


RenderTarget::RenderTarget(int w, int h, int magFilter, int minFilter, int wrap)
        : width{w}, height{h} {

    // generate an empty texture
    texture = std::make_shared<Texture>(width, height, magFilter, minFilter, wrap);

    // create a framebuffer
    glGenFramebuffers(1, &framebufferRef);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferRef);

    // configure color buffer to use this texture
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->textureRef(), 0);

    // generate a buffer to store depth information
    GLuint depthBufferRef;
    glGenRenderbuffers(1, &depthBufferRef);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferRef);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferRef);

    // check framebuffer status
    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer status error: " << status << "\n";
    }
}

RenderTarget::RenderTarget(int w, int h)
        : RenderTarget(w, h, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE) {
}