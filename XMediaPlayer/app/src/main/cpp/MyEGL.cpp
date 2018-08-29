//
// Created by developer on 8/26/18.
//

#include "MyEGL.h"
#include "MLOG.h"



bool MyEGL::eglInit(jobject surface) {

    if((eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY))==EGL_NO_DISPLAY){
        LOGE("eglDisplay failed!");
        return false;
    }

    LOGD("eglDisplay successful!");
    if(!eglInitialize(eglDisplay,0,0)){
        LOGE("eglInitialize fialed!");
        return false;
    }
    LOGD("eglInitialize successful!");

    const EGLint attribs[]={
            EGL_BUFFER_SIZE, 32,
            EGL_ALPHA_SIZE,8,
            EGL_BLUE_SIZE,8,
            EGL_GREEN_SIZE,8,
            EGL_RED_SIZE,8,
            EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
            EGL_NONE
    };

    EGLint numberConfigs=0;
    if(!eglChooseConfig(eglDisplay,attribs,eglConfig,1,&numberConfigs)){

        LOGE("eglChooseConfig failed!");
        return false;
    }
    LOGD("eglChooseConfig sucessful!");


    return true;
}
