//
// Created by developer on 2018/8/27.
//


#include "FFmpegDemux.h"
#include "MLOG.h"


bool FFmpegDemux::isFirst = false;

FFmpegDemux::FFmpegDemux() {
    if (!isFirst) {
        initAVCodec();

        isFirst = false;
    }
}

FFmpegDemux::~FFmpegDemux() {

}

static int custom_interrupt_callback(void *arg) {
    FFmpegDemux *fFmpegDemux = (FFmpegDemux *) arg;
    return 0;//0继续阻塞
}


bool FFmpegDemux::open(const char *url) {
    int ret = 0;
    avFormatContext = avformat_alloc_context();
    if (!avFormatContext) {
        LOGE("Could not allocate context.\n");
        goto fail;
    }
    avFormatContext->interrupt_callback.callback = custom_interrupt_callback;
    avFormatContext->interrupt_callback.opaque = this;
    if ((ret = avformat_open_input(&avFormatContext, url, 0, 0)) < 0) {
        LOGE("avformat open input failed  :%s!", av_err2str(ret));
        goto fail;
    }
    LOGD("avformat open input successful!");

    if ((ret = avformat_find_stream_info(avFormatContext, 0)) < 0) {
        LOGE("avformat find stream info failed:  %s", av_err2str(ret));
        goto fail;
    }

    setVideoStreamIndex(av_find_best_stream(avFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0));
    setAudioStreamIndex(av_find_best_stream(avFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0));

    LOGD("find stream index  videoStream:%d   audioStream:%d", getVideoStreamIndex(),
         getAudioStreamIndex());

    fail:


    return true;
}

AVParameters *FFmpegDemux::getAudioParameters() {
    if (!avFormatContext || getAudioStreamIndex() < 0) NULL;
    audioAvParameters=new AVParameters();
    audioAvParameters->codecParameters=avcodec_parameters_alloc();
    avcodec_parameters_copy(audioAvParameters->codecParameters,avFormatContext->streams[getAudioStreamIndex()]->codecpar);
    return audioAvParameters;
}

AVParameters *FFmpegDemux::getVideoParamters() {
    if (!avFormatContext || getVideoStreamIndex() < 0)NULL;
    videoAvParameters=new AVParameters();
    videoAvParameters->codecParameters=avcodec_parameters_alloc();
    avcodec_parameters_copy(videoAvParameters->codecParameters,avFormatContext->streams[getVideoStreamIndex()]->codecpar);
    return videoAvParameters;
}

AVData FFmpegDemux::readMediaData() {

    return AVData();
}

void FFmpegDemux::initAVCodec() {
    av_register_all();
    avformat_network_init();
}

int FFmpegDemux::getVideoStreamIndex() const {
    return videoStreamIndex;
}

void FFmpegDemux::setVideoStreamIndex(int videoStreamIndex) {
    FFmpegDemux::videoStreamIndex = videoStreamIndex;
}

int FFmpegDemux::getAudioStreamIndex() const {
    return audioStreamIndex;
}

void FFmpegDemux::setAudioStreamIndex(int audioStreamIndex) {
    FFmpegDemux::audioStreamIndex = audioStreamIndex;
}
