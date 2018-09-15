//
// Created by developer on 2018/8/27.
//

#include "IFFmpegDecode.h"
#include "MLOG.h"

void IFFmpegDecode::update(AVData pkt) {
    if (pkt.isAudio != isAudio) {
        return;
    }
    while (!isExit) {
        packsMutex.lock();
        if (packs.size() < maxList) {
            //生产者
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        xsleep(1);
    }

}

void IFFmpegDecode::main() {
    while (!isExit) {
        packsMutex.lock();

        //判断音视频同步
//        if(!isAudio && synPts > 0)
//        {
//            if(synPts < pts)
//            {
//                packsMutex.unlock();
//                continue;
//            }
//        }

        if (packs.empty()) {
            packsMutex.unlock();
            xsleep(1);
            continue;
        }
        //取出packet 消费者
        AVData pack = packs.front();
        packs.pop_front();

        //发送数据到解码线程，一个数据包，可能解码多个结果
        if (this->sendPacket(pack)) {
            while (!isExit) {
                //获取解码数据
                AVData frame = this->receiveFrame();
                if (!frame.data) break;
                //XLOGE("RecvFrame %d",frame.size);
                pts = frame.pts;
                //发送数据给观察者
                this->notifyObserver(frame);

            }

        }
        pack.Drop();
        packsMutex.unlock();
    }
}
