
#include <string>
#include "MyEGL.h"
#include "FFmpegDemux.h"
#include <jni.h>
#include "MLOG.h"
#include "FFmpegdecode.h"
#include <android/native_window_jni.h>


FFmpegDemux *fFmpegDemux = NULL;

FFmpegdecode *fFmpegAudioDecode = NULL;
FFmpegdecode *fFmpegVideoDecode = NULL;

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
    fFmpegAudioDecode = new FFmpegdecode();
    fFmpegVideoDecode = new FFmpegdecode();

    fFmpegDemux->addObserver(fFmpegAudioDecode);
    fFmpegDemux->addObserver(fFmpegVideoDecode);

    bool openResult = fFmpegDemux->open(s);
    if (!openResult) {
        LOGE("ffmpeg demux failed!");
    }
    LOGD("ffmpeg demux success!");

    const AVParameters *audioParameters = fFmpegDemux->getAudioParameters();
    const AVParameters *videoParameters = fFmpegDemux->getVideoParamters();

    LOGD("videoParameters codecID:%d", videoParameters->codecParameters->codec_id);
    LOGD("audioParameters codecID:%d", audioParameters->codecParameters->codec_id);

    fFmpegAudioDecode->openCodec(*audioParameters);
    fFmpegVideoDecode->openCodec(*videoParameters);


    fFmpegVideoDecode->startThread();
    fFmpegAudioDecode->startThread();
    fFmpegDemux->startThread();


    env->ReleaseStringUTFChars(s_, s);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_huaweichang_xmediaplayer_VideoView_release(JNIEnv *env, jobject instance) {


    //资源释放
    if (fFmpegDemux) {
        delete fFmpegDemux;
    }
    if (fFmpegVideoDecode) {
        delete fFmpegVideoDecode;
    }
    if (fFmpegAudioDecode) {
        delete fFmpegAudioDecode;
    }


}

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {


    return JNI_VERSION_1_4;
}
