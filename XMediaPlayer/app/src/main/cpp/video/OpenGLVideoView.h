//
// Created by developer on 2018/9/16.
//

#ifndef XMEDIAPLAYER_OPENGLVIDEOVIEW_H
#define XMEDIAPLAYER_OPENGLVIDEOVIEW_H


#include "IVideoView.h"
#include "Texture.h"
#include <jni.h>

class OpenGLVideoView : public IVideoView {

public:
     virtual void SetRender(void *win);
     virtual void Render(AVData data);

protected:
    void *window = NULL;
    Texture *texture = NULL;
};


#endif //XMEDIAPLAYER_OPENGLVIDEOVIEW_H
