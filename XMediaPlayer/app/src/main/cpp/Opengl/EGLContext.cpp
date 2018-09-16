//
// Created by developer on 8/26/18.
//

#include "EGLContext.h"
#include "../log/MLOG.h"

/**
 * EGL是由Khronos Group提供的一组平台无关的API
 *
 *
 *
 * @param win
 * @return
 */

void MyEGL::drawGraphic() {
    if (eglDisplay != EGL_NO_DISPLAY && eglSurface != EGL_NO_SURFACE) {
        eglSwapBuffers(eglDisplay, eglSurface);
    }
}

MyEGL *MyEGL::Get() {
    static MyEGL egl;
    return &egl;
}

bool MyEGL::eglInit(void *win) {
    //获取渲染目标对象(封装物理屏幕的数据类型)
    if ((eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOGE("eglDisplay failed!");
        return false;
    }

    LOGD("eglDisplay successful!");
    //初始化显示设备 ，后面两个参数是 major minor 主次版本 如：1.0(这里可以直接传0)
    if (!eglInitialize(eglDisplay, 0, 0)) {
        LOGE("eglInitialize fialed!");
        return false;
    }
    LOGD("eglInitialize successful!");

    const char *vendor = eglQueryString(eglDisplay, EGL_VENDOR);
    LOGD("egl vendor: %s", vendor); // 打印此版本EGL的实现厂商

    const char *version = eglQueryString(eglDisplay, EGL_VERSION);
    LOGD("egl version:%s", version);// 打印EGL版本号

    const char *
            extension = eglQueryString(eglDisplay, EGL_EXTENSIONS);
    LOGD("egl extension:%s ", extension); //打印支持的EGL扩展


    //FrameBuffer的参数
    const EGLint attribs[] = {
            EGL_BUFFER_SIZE, 32,//color buffer 的颜色深度（bits per pixel）EGL_RED/GREEN/BLUE/ALPHA_SIZE之和
            EGL_ALPHA_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,//Surface类型，可选值为：EGL_WINDOW_BIT, EGL_PIXMAP_BIT ,EGL_PBUFFER_BIT
            EGL_NONE //总是以EGL_NONE结尾
    };

//    EGLint configSpec [] = {
//            EGL_RED_SIZE,8,
//            EGL_GREEN_SIZE,8,
//            EGL_BLUE_SIZE,8,
//            EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
//            EGL_NONE
//    };
    EGLConfig eglConfig = 0;
    EGLint numberConfigs = 0;
    //获取配置信息
    if (!eglChooseConfig(eglDisplay, attribs, &eglConfig, 1, &numberConfigs)) {

        LOGE("eglChooseConfig failed!");
        return false;
    }
    LOGD("eglChooseConfig sucessful!");
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (ANativeWindow *) win, NULL);


    //4 创建并打开EGL上下文
    const EGLint ctxAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, ctxAttr);
    if (eglContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext failed!");
        return false;
    }
    LOGD("eglCreateContext success!");

    //为当前线程绑定surface与Context
    if (EGL_TRUE != eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        LOGE("eglMakeCurrent failed!");
        return false;
    }
    LOGD("eglMakeCurrent success!");
    //注意：Surface其实就是FrameBuffer EGL的工作模式是双缓冲模式，其内部有两个FrameBuffer,一个做为当前显示，另一个在后台等待渲染输出，
    //直到调用eglSwapBuffers  进行前后台FrameBuffer交换.

    //资源销毁  1.销毁显示设备 eglDestroySurface(display,eglsurface);  2.销毁上下文eglDestroyContext(display,context);

    return true;
}

MyEGL::MyEGL() {

}

MyEGL::~MyEGL() {

}
/**
EGLBoolean EGL_TRUE =1, EGL_FALSE=0

EGLint int 数据类型

EGLDisplay 系统显示 ID 或句柄

EGLConfig Surface 的 EGL 配置

EGLSurface 系统窗口或 frame buffer 句柄

EGLContext OpenGL ES 图形上下文

NativeDisplayType Native 系统显示类型

NativeWindowType Native 系统窗口缓存类型

NativePixmapType Native 系统 frame buffer
 */