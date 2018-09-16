//
// Created by developer on 8/26/18.
//

#ifndef XMEDIAPLAYER_EGLCONTEXT_H
#define XMEDIAPLAYER_EGLCONTEXT_H

#include <jni.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class MyEGL {
public:
    bool eglInit(void* win);

    EGLDisplay eglDisplay = EGL_NO_DISPLAY;
    EGLSurface  eglSurface=EGL_NO_SURFACE;
    EGLContext eglContext=EGL_NO_CONTEXT;
    void drawGraphic();
    static MyEGL *Get();
    virtual ~MyEGL();

protected:
    MyEGL();


};


#endif //XMEDIAPLAYER_EGLCONTEXT_H
