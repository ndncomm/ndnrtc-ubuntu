// 
// renderer.cpp
//
// Copyright (c) 2015. Peter Gusev. All rights reserved
//

#include <stdlib.h>
#include "renderer.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    
    // Open a window and create its OpenGL context
    window_ = glfwCreateWindow(800, 450, windowTitle.c_str(), NULL, NULL);
    
    if( window_ == NULL ){
        LogError("") << "FFailed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials." << std::endl;
        glfwTerminate();
        return;
    }

    glewExperimental=true; // Needed in core profile
    
    if (glewInit() != GLEW_OK) 
    {
        LogError("") << "Failed to initialize GLEW" << std::endl;
        return;
    }
}

void RendererInternal::closeWindow()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void RendererInternal::createTexture(int width, int height)
{
    LogDebug("") << "createing texture..." << std::endl;

    if (glIsTexture(_texture))
    {
        releaseTexture();
        _texture = 0;
    }
    
    glGenTextures(1, (GLuint*) &texture_);
    GetError();
    
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
                 width_,
                 height_,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_INT_8_8_8_8,
                 renderBuffer_);
    GetError();
}

void RendererInternal::releaseTexture()
{
    LogDebug("") << "releasing texture..." << std::endl;
    
    glDeleteTextures(1, (const GLuint*) &_texture);
    GetError();
}

