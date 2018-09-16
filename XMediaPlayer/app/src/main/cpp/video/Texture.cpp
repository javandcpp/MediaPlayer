//
// Created by developer on 2018/9/16.
//

#include "Texture.h"
#include "../Opengl/EGLContext.h"
#include "../log/MLOG.h"

bool Texture::Init(void *win, AVPixelFormat type) {

    //初始化EGL环境
    if (!MyEGL::Get()->eglInit(win)) {
        LOGD("eglinit failed");
        return false;
    }

    //初始化Shader
    //过程：创建加载编译shader,创建Shader程序，加载顶点片元着色器，传入顶点坐标，材质坐标，设置纹理层次(材质包含贴图，贴图包含纹理)，贴图是建立纹理与物体表面的映射关系.
    if (!eglShader.Init(type)) {
        LOGD("texture eglShader inte failed");
        return false;
    }
    return true;
}

void Texture::Draw(unsigned char **data, int width, int height) {

    eglShader.getTexture(0, width, height, data[0]);  // Y

    if (shaderType == AV_PIX_FMT_YUV420P) {
        eglShader.getTexture(1, width / 2, height / 2, data[1]);  // U
        eglShader.getTexture(2, width / 2, height / 2, data[2]);  // V
    } else {
        eglShader.getTexture(1, width / 2, height / 2, data[1], true);  // UV
    }
    eglShader.draw();
    MyEGL::Get()->drawGraphic();
}

Texture *Texture::Create() {
    return new Texture();
}
