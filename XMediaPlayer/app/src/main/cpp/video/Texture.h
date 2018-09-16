//
// Created by developer on 2018/9/16.
//

#ifndef XMEDIAPLAYER_TEXTURE_H
#define XMEDIAPLAYER_TEXTURE_H

#include "../Opengl/EGLShader.h"


class Texture {
public:

    EGLShader eglShader;
    AVPixelFormat shaderType;

    static Texture *Create();

    bool Init(void *win, AVPixelFormat type = AV_PIX_FMT_YUV420P);

    void Draw(unsigned char *data[], int width, int height);
};


#endif //XMEDIAPLAYER_TEXTURE_H
