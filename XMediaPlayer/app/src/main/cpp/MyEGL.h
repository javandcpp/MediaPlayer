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
    bool eglInit(jobject surface);

    EGLDisplay eglDisplay = EGL_NO_DISPLAY;
    EGLConfig  *eglConfig=NULL;

};


#endif //XMEDIAPLAYER_EGLCONTEXT_H
