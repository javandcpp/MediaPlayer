//
// Created by developer on 2018/9/16.
//

#include "IPlayer.h"


void IPlayer::main() {
    while (!isExit) {
        mut.lock();
        if (!audioPlay || !videoDecode) {
            mut.unlock();
            xsleep(10);
            continue;
        }

        //获取音频的pts 告诉视频 (视频同步音频)
        int apts = audioPlay->pts;
        videoDecode->syncAudioPts = apts;
        mut.unlock();
    }
}