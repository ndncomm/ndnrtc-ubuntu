// 
// renderer.h
//
// Copyright (c) 2015. Peter Gusev. All rights reserved
//

#include <ndnrtc/interfaces.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RendererInternal : public ndnrtc::IExternalRenderer
{
public:
    RendererInternal():renderBuffer_(nullptr), bufferSize_(0) , texture_(0)
    { 
    	// createWindow("NDN-RTC demo consumer v0.0.1");
    }

    ~RendererInternal()
    { 
    	releaseTexture();
    	// closeWindow();
    }
    
    virtual uint8_t* getFrameBuffer(int width, int height);
    virtual void renderBGRAFrame(int64_t timestamp, int width, int height,
                         const uint8_t* buffer);
    
private:
    char *renderBuffer_;
    int bufferSize_;
    GLuint texture_;
    GLFWwindow* window_;
    GLuint framebuffer_;
    GLenum drawBuffers_[1];

    void createWindow(const std::string& windowName);
    void closeWindow();

    void createTexture(int width, int height);
    void releaseTexture();

    void render();
};
