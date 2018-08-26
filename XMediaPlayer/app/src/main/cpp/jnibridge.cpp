#include <jni.h>
#include <string>
#include "MyEGL.h"
#include <android/native_window_jni.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_huaweichang_xmediaplayer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {


    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_VideoView_initNativeEGL(JNIEnv *env, jobject instance,
                                                                  jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    MyEGL egl;
    egl.eglInit(surface);



    return;
}