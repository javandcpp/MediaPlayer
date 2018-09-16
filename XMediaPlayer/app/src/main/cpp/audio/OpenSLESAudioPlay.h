//
// Created by developer on 2018/9/16.
//

#ifndef XMEDIAPLAYER_OPENSLESAUDIOPLAY_H
#define XMEDIAPLAYER_OPENSLESAUDIOPLAY_H


#include "../AVParameters.h"
#include "IAudioPlay.h"

class OpenSLESAudioPlay: public IAudioPlay {
public:
    virtual bool StartPlay(AVParameters out);
    void PlayCall(void *buf);

    OpenSLESAudioPlay();

    virtual ~OpenSLESAudioPlay();
protected:
    unsigned char *buf = 0;
};


#endif //XMEDIAPLAYER_OPENSLESAUDIOPLAY_H
