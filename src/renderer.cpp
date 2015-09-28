// 
// renderer.cpp
//
// Copyright (c) 2015. Peter Gusev. All rights reserved
//

#include <stdlib.h>
#include <assert.h>
#include "renderer.h"

#define WIN_W 800
#define WIN_H 450

#define GetError( )\
{\
for ( GLenum Error = glGetError( ); ( GL_NO_ERROR != Error ); Error = glGetError( ) )\
{\
switch ( Error )\
{\
case GL_INVALID_ENUM:      LogError("") << "GL_INVALID_ENUM" << std::endl; assert( 1 ); break;\
case GL_INVALID_VALUE:     LogError("") << "GL_INVALID_VALUE" << std::endl; assert( 1 ); break;\
case GL_INVALID_OPERATION: LogError("") << "GL_INVALID_OPERATION" << std::endl; assert( 1 ); break;\
case GL_OUT_OF_MEMORY:     LogError("") << "GL_OUT_OF_MEMORY" << std::endl; assert( 1 ); break;\
default:                                                                              break;\
}\
}\
}

uint8_t* RendererInternal::getFrameBuffer(int width, int height)
{
    if (!renderBuffer_ || width*height*4 > bufferSize_)
    {
        // init ARGB buffer
        bufferSize_ = width*height*4;
        LogInfo("") << "initializing render buffer " << width << "x" << height << "(" << bufferSize_ <<" bytes)..." << std::endl;
        renderBuffer_ = (char*)realloc(renderBuffer_, bufferSize_);
        createTexture(width, height);
    }

    return (uint8_t*)renderBuffer_;
}

void RendererInternal::renderBGRAFrame(int64_t timestamp, int width, int height,
                     const uint8_t* buffer)
{
    // do whatever we need, i.e. drop frame, render it, write to file, etc.
    LogInfo("") << "received frame (" << width << "x" << height << ") at " << timestamp << "ms" << std::endl;
    //render();

    return;
}
    

void RendererInternal::createWindow(const std::string& windowTitle)
{
    if( !glfwInit() )
    {
        LogError("") << "Failed to initialize GLFW\n" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    
    // Open a window and create its OpenGL context
    window_ = glfwCreateWindow(WIN_W, WIN_H, windowTitle.c_str(), NULL, NULL);
    
    if( window_ == NULL ){
        LogError("") << "FFailed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials." << std::endl;
        glfwTerminate();
        return;
    }

    //glewExperimental=true; // Needed in core profile
    
    if (glewInit() != GLEW_OK) 
    {
        LogError("") << "Failed to initialize GLEW" << std::endl;
        return;
    }

    // glfwMakeContextCurrent(window_);
}

void RendererInternal::closeWindow()
{
    //glfwDestroy (window_);
    glfwTerminate();
}

void RendererInternal::createTexture(int width, int height)
{
    int i = 0;

    if (glIsTexture(texture_))
        releaseTexture();
    
    // framebuffer_ = 0;
    // glGenFramebuffers(1, &framebuffer_);
    // GetError();
    // LogDebug("") << i++ << std::endl;

    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    // GetError();
    // LogDebug("") << i++ << std::endl;

    glGenTextures(1, (GLuint*) &texture_);
    GetError();
    LogDebug("") << i++ << std::endl;
    
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_);
    GetError();
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, (GLint)width);
    GetError();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GetError();
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GetError();
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GetError();
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GetError();
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GetError();
    
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB,
                 0,
                 GL_RGBA8,
                 width,
                 height,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_INT_8_8_8_8,
                 renderBuffer_);
    GetError();

    // LogDebug("") << i++ << std::endl;
    // glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_, 0);
    // GetError();
 
    // LogDebug("") << i++ << std::endl;
    // // Set the list of draw buffers.
    // drawBuffers_[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, drawBuffers_); // "1" is the size of DrawBuffers
    // GetError();
    // LogDebug("") << i++ << std::endl;
}

void RendererInternal::releaseTexture()
{
    LogDebug("") << "releasing texture..." << std::endl;

    glDeleteTextures(1, (const GLuint*) &texture_);
    GetError();
    texture_ = 0;
}

void RendererInternal::render()
{
    /*GLfloat _startWidth = 0,
    _startHeight = 0,
    _stopWidth = WIN_W,
    _stopHeight = WIN_H;
    
    GLfloat xStart = (2.0f * _startWidth - 1.0f);
    GLfloat xStop = (2.0f * _stopWidth - 1.0f);
    GLfloat yStart = (1.0f - 2.0f * _stopHeight);
    GLfloat yStop = (1.0f - 2.0f * _startHeight);
    
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_);
    glLoadIdentity();
    
    glBegin(GL_POLYGON);
    {
        glTexCoord2f(0.0, 0.0); glVertex2f(xStart, yStop);
        glTexCoord2f(WIN_W, 0.0); glVertex2f(xStop, yStop);
        glTexCoord2f(WIN_W, WIN_H); glVertex2f(xStop, yStart);
        glTexCoord2f(0.0, WIN_H); glVertex2f(xStart, yStart);
    }
    glEnd();
    glFinish();

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    GetError();

    glViewport(0,0,WIN_W,WIN_H);
    GetError();
    */
}

