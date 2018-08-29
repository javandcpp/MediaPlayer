//
// Created by developer on 2018/8/29.
//

#include "EGLShader.h"
#include <EGL/egl.h>

#define GET_STR(x) #x


static const EGLint configAttribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
};

//指定EGLContext属性，这里使用opengles2
static const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,      //指定context为opengles2
        EGL_NONE
};

//fsh
static const char *codeFragShader = GET_STR(
        vec3 yuv;
        vec3 rgb;
        yuv.r = texture2D(yTexture, vTexCoord).r;
        yuv.g = texture2D(uTexture, vTexCoord).r - 0.5;
        yuv.b = texture2D(vTexture, vTexCoord).r - 0.5;
        rgb = mat3(1.0, 1.0, 1.0,
                   0.0, -0.39465, 2.03211,
                   1.13983, -0.58060, 0.0) * yuv;
        //输出像素颜色
        gl_FragColor = vec4(rgb, 1.0);
);

//vsh
static const char *codeVertexShader = GET_STR(
        attribute
        vec4 aPosition; //顶点坐标
        attribute
        vec2 aTexCoord; //材质顶点坐标
        varying
        vec2 vTexCoord;   //输出的材质坐标
        void main() {
            vTexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
            gl_Position = aPosition;
        }
);


