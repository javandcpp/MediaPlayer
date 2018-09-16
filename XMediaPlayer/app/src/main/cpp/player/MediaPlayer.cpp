//
// Created by developer on 2018/9/16.
//

#include "MediaPlayer.h"
#include "../demux/FFmpegDemux.h"
#include "../decode/FFmpegdecode.h"
#include "../video/OpenGLVideoView.h"
#include "../audio/FFmpegAudioResample.h"
#include "../audio/OpenSLESAudioPlay.h"
#include "../log/MLOG.h"



MediaPlayer::MediaPlayer() {

}

MediaPlayer::~MediaPlayer() {

}
/**
 * 初始化播放器
 */
void MediaPlayer::initialize() {
    std::lock_guard<std::mutex> lk(mut);
    //解复用
    mDemux = new FFmpegDemux();
    //音视频解码
    audioDecode = new FFmpegdecode();
    videoDecode = new FFmpegdecode();

    mDemux->addObserver(audioDecode);
    mDemux->addObserver(videoDecode);

    //图像渲染
    videoView = new OpenGLVideoView();
    videoDecode->addObserver(videoView);

    //音频重采样
    audioResample = new FFmpegAudioResample();
    audioDecode->addObserver(audioResample);

    //音频播放
    audioPlay = new OpenSLESAudioPlay();
    audioResample->addObserver(audioPlay);


}

/**
 * 设置资源路径
 * @param url
 */
void MediaPlayer::setDataSource(const char *url) {

    std::lock_guard<std::mutex> lk(mut);
    if (mDemux) {
        bool openResult = mDemux->open(url);
        if (!openResult) {
            LOGE("ffmpeg demux failed!");
        }
        LOGD("ffmpeg demux success!");

        audioParameters = mDemux->getAudioParameters();
        videoParameters = mDemux->getVideoParamters();
        LOGD("videoParameters codecID:%d", videoParameters->codecParameters->codec_id);
        LOGD("audioParameters codecID:%d", audioParameters->codecParameters->codec_id);
    }

    if (videoDecode) {
        bool openVideoCodeResult = videoDecode->openCodec(*videoParameters);
        if (!openVideoCodeResult) {
            LOGE("openVideoCodec error!");
            return;
        }
    }
    if (audioDecode) {
        bool openAudioCodec = audioDecode->openCodec(*audioParameters);
        if (!openAudioCodec) {
            LOGE("openAudioCodec error!");
            return;
        }
        //重采样输出
        if (audioResample) {
            audioResample->Init(*audioParameters, audioOutputParameters);
            LOGD("audioResample Init Success");
        }

    }
}

void MediaPlayer::setNativeWindow(void *window) {
    std::lock_guard<std::mutex> lk(mut);
    if (window && videoView) {
        videoView->SetRender(window);
        LOGD("set NativeWindow success");
    } else {
        LOGE("set NativeWindow error");
    }
}

void MediaPlayer::startPlay() {
    std::lock_guard<std::mutex> lk(mut);
    if (audioPlay) {
        audioPlay->StartPlay(audioOutputParameters);
    }
    if (mDemux) {
        mDemux->startThread();
    }
    if (videoDecode) {
        videoDecode->startThread();
    }
    if (audioDecode) {
        audioDecode->startThread();
    }
    this->startThread();
}

void MediaPlayer::stopPlay() {

}

void MediaPlayer::release() {

}