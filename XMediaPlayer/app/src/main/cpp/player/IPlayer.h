//
// Created by developer on 2018/9/16.
//

#ifndef XMEDIAPLAYER_IPLAYER_H
#define XMEDIAPLAYER_IPLAYER_H


#include "../NativeThread.h"
#include "../demux/IDemux.h"
#include "../decode/IFFmpegDecode.h"
#include "../audio/IAudioPlay.h"
#include "../video/IVideoView.h"
#include "../audio/IAudioResample.h"

class IPlayer : public NativeThread {
public:

    virtual void main();

    IDemux *mDemux = NULL;
    IFFmpegDecode *videoDecode = NULL;
    IFFmpegDecode *audioDecode = NULL;
    IAudioPlay *audioPlay = NULL;
    IVideoView *videoView = NULL;
    IAudioResample *audioResample = NULL;
    AVParameters *audioParameters=NULL;
    AVParameters *videoParameters=NULL;
    AVParameters audioOutputParameters;

    virtual void initialize()=0;

    virtual void setNativeWindow(void *window)=0;

    virtual void setDataSource(const char *url)=0;

    virtual void startPlay()=0;

    virtual void stopPlay()=0;

    virtual void release()=0;

    std::mutex mut;
};


#endif //XMEDIAPLAYER_IPLAYER_H
