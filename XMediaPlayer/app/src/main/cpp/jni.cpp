
#include <string>
#include "Opengl/EGLContext.h"
#include "demux/FFmpegDemux.h"
#include <jni.h>
#include "log/MLOG.h"
#include "decode/FFmpegdecode.h"
#include "video/OpenGLVideoView.h"
#include "audio/IAudioPlay.h"
#include "audio/IAudioResample.h"
#include "audio/FFmpegAudioResample.h"
#include "audio/OpenSLESAudioPlay.h"
#include "player/MediaPlayer.h"
#include <android/native_window_jni.h>


#ifdef __cplusplus
extern "C" {
#include "libavcodec/jni.h"
};
#endif


ANativeWindow *window = NULL;
MediaPlayer *mediaPlayer = NULL;

std::mutex mut;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_VideoView_release(JNIEnv *env, jobject instance) {


}

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {//system.loadlibrary
    av_jni_set_java_vm(vm, NULL);
    return JNI_VERSION_1_6;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_KSMediaPlayer__1initialize(JNIEnv *env,
                                                                     jobject instance) {
    lock_guard<std::mutex> lk(mut);
    mediaPlayer = new MediaPlayer();
    mediaPlayer->initialize();

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_KSMediaPlayer__1startPlay(JNIEnv *env, jobject instance) {
    lock_guard<std::mutex> lk(mut);
    mediaPlayer->startPlay();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_KSMediaPlayer__1setDataSource(JNIEnv *env,
                                                                        jobject instance,
                                                                        jstring url_) {
    lock_guard<std::mutex> lk(mut);
    const char *url = env->GetStringUTFChars(url_, 0);
    mediaPlayer->setDataSource(url);
    env->ReleaseStringUTFChars(url_, url);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_KSMediaPlayer__1stopPlay(JNIEnv *env, jobject instance) {
    lock_guard<std::mutex> lk(mut);

    // TODO

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_KSMediaPlayer__1release(JNIEnv *env, jobject instance) {
    lock_guard<std::mutex> lk(mut);


}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_KSMediaPlayer__1setWindowSurface(JNIEnv *env,
                                                                           jobject instance,
                                                                           jobject surface) {
    lock_guard<std::mutex> lk(mut);
    window = ANativeWindow_fromSurface(env, surface);
    mediaPlayer->setNativeWindow(window);

}