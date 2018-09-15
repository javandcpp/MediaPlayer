//
// Created by developer on 2018/8/29.
//

#ifndef XMEDIAPLAYER_EGLSHADER_H
#define XMEDIAPLAYER_EGLSHADER_H

enum ShaderType
{
    SHADER_YUV420P = 0,    //软解码和虚拟机
    SHADER_NV12 = 25,      //手机
    SHADER_NV21 = 26
};

class EGLShader {

public:
    virtual bool Init(ShaderType type=SHADER_YUV420P);

    //获取材质并映射到内存
//    virtual void getTexture(unsigned int index,int width,int height, unsigned char *buf,bool isa=false);
//    virtual void draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};

};




#endif //XMEDIAPLAYER_EGLSHADER_H
