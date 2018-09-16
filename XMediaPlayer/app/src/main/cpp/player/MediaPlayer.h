//
// Created by developer on 2018/9/16.
//

#ifndef XMEDIAPLAYER_MEDIAPLAYER_H
#define XMEDIAPLAYER_MEDIAPLAYER_H


#include "IPlayer.h"

class MediaPlayer : public IPlayer {
public:

    MediaPlayer();

    virtual ~MediaPlayer();

    virtual void initialize();

    virtual void setDataSource(const char *url);

    virtual void startPlay();

    virtual void stopPlay();

    virtual void release();

    virtual void setNativeWindow(void *window);


};


#endif //XMEDIAPLAYER_MEDIAPLAYER_H
