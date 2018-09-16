//
// Created by developer on 2018/9/16.
//

#ifndef XMEDIAPLAYER_IVIDEOVIEW_H
#define XMEDIAPLAYER_IVIDEOVIEW_H


#include "../AVData.h"
#include "../IObserver.h"


class IVideoView :public IObserver{
public:
    virtual void SetRender(void *win){};
    virtual void Render(AVData data){};
    void update(AVData avData);
};


#endif //XMEDIAPLAYER_IVIDEOVIEW_H
