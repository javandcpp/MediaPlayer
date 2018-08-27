
#include <string>
#include "MyEGL.h"
#include "FFmpegDemux.h"
#include <jni.h>
#include "MLOG.h"
#include <android/native_window_jni.h>

FFmpegDemux *fFmpegDemux = NULL;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_VideoView_initNativeEGL(JNIEnv *env, jobject instance,
                                                                  jobject surface) {


}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_MainActivity_openVideo__Ljava_lang_String_2(JNIEnv *env,
                                                                                      jobject instance,
                                                                                      jstring s_) {
    const char *s = env->GetStringUTFChars(s_, 0);

    fFmpegDemux = new FFmpegDemux();
    fFmpegDemux->open(s);

    const AVParameters *audioParameters = fFmpegDemux->getAudioParameters();
    const AVParameters *videoParameters = fFmpegDemux->getVideoParamters();

    LOGD("videoParameters codecID:%d", videoParameters->codecParameters->codec_id);
    LOGD("audioParameters codecID:%d", audioParameters->codecParameters->codec_id);


    env->ReleaseStringUTFChars(s_, s);
}