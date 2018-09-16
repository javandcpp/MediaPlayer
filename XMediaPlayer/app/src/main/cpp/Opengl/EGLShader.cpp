//
// Created by developer on 2018/8/29.
//

#include "EGLShader.h"
#include "../log/MLOG.h"
#include <GLES2/gl2.h>

#define GET_STR(x) #x


//片元着色
static const char *fragYUV420P = GET_STR(
        precision
        mediump float;    //精度
        varying
        vec2 vTexCoord;     //顶点着色器传递的坐标
        uniform
        sampler2D yTexture; //输入的材质（不透明灰度，单像素）
        uniform
        sampler2D uTexture;
        uniform
        sampler2D vTexture;
        void main() {
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
        }
);

//片元着色器
static const char *fragNV12 = GET_STR(
        precision
        mediump float;    //精度
        varying
        vec2 vTexCoord;     //顶点着色器传递的坐标
        uniform
        sampler2D yTexture; //输入的材质（不透明灰度，单像素）
        uniform
        sampler2D uvTexture;
        void main() {
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture, vTexCoord).r;
            yuv.g = texture2D(uvTexture, vTexCoord).r - 0.5;
            yuv.b = texture2D(uvTexture, vTexCoord).a - 0.5;
            rgb = mat3(1.0, 1.0, 1.0,
                       0.0, -0.39465, 2.03211,
                       1.13983, -0.58060, 0.0) * yuv;
            //输出像素颜色
            gl_FragColor = vec4(rgb, 1.0);
        }
);

//片元着色器,软解码和部分x86硬解码
static const char *fragNV21 = GET_STR(
        precision
        mediump float;    //精度
        varying
        vec2 vTexCoord;     //顶点着色器传递的坐标
        uniform
        sampler2D yTexture; //输入的材质（不透明灰度，单像素）
        uniform
        sampler2D uvTexture;
        void main() {
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture, vTexCoord).r;
            yuv.g = texture2D(uvTexture, vTexCoord).a - 0.5;
            yuv.b = texture2D(uvTexture, vTexCoord).r - 0.5;
            rgb = mat3(1.0, 1.0, 1.0,
                       0.0, -0.39465, 2.03211,
                       1.13983, -0.58060, 0.0) * yuv;
            //输出像素颜色
            gl_FragColor = vec4(rgb, 1.0);
        }
);

//顶点着色 uniform(const )
// varying变量是vertex和fragment shader之间做数据传递用的 因此varying变量在vertex和fragment shader二者之间的声明必须是一致的
static const char *vertexShader = GET_STR(
        attribute vec4 aPosition; //顶点坐标
        attribute vec2 aTexCoord; //材质顶点坐标
        varying vec2 vTexCoord;   //输出的材质坐标
        void main(){
            vTexCoord = vec2(aTexCoord.x,1.0-aTexCoord.y);
            gl_Position = aPosition;
        }
);

/**
 *
 * 向量

有很多种向量，但是有三种会经常看到

vec2：两个浮点数，适合在Fragment shader中保存X和Y坐标的情况
vec3：三个浮点数
vec4：四个浮点数，在图像处理中持续追踪每个像素的R,G,V,A这四个值。
矩阵

是浮点数组的数组。三个经常处理的矩阵对象

mat2：相当于保存了两个vec2对象的值或四个浮点数。
mat3
mat4




精度控制关键词：lowp highp mediump 指定变量精度（放在数据类型之前）


precision可以用来确定默认精度修饰符。type可以是int或float或采样器类型，
 precision-qualifier可以是lowp, mediump, 或者highp。任何其他类型和修饰符都会引起错误。
 如果type是float类型，那么该精度（precision-qualifier）将适用于所有无精度修饰符的浮点数声明
 （标量，向量，矩阵）。如果type是int类型，那么该精度（precision-qualifier）将适用于所有无精度修饰符的整型数声明（标量，向量）。
 包括全局变量声明，函数返回值声明，函数参数声明，和本地变量声明等。没有声明精度修饰符的变量将使用和它最近的precision语句中的精度。
 */
static GLuint initShader(const char *code, GLint type) {
    //创建shader
    GLuint sh = glCreateShader(type);
    if (sh == 0) {
        LOGE("glCreateShader %d failed!", type);
        return 0;
    }
    //加载shader
    glShaderSource(sh,
                   1,    //shader数量
                   &code, //shader代码
                   0);   //代码长度
    //编译shader
    glCompileShader(sh);

    //获取编译情况
    GLint status;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        LOGE("glCompileShader failed!");
        return 0;
    }
    LOGD("glCompileShader success!");
    return sh;
}

bool EGLShader::Init(AVPixelFormat type) {
    //顶点和片元shader初始化
    //顶点shader初始化
    vsh = initShader(vertexShader, GL_VERTEX_SHADER);
    if (vsh == 0) {
        LOGE("initShader GL_VERTEX_SHADER failed!");
        return false;
    }
    LOGD("initShader GL_VERTEX_SHADER success! %d", type);

    //片元yuv420 shader初始化
    switch (type) {
        case AV_PIX_FMT_YUV420P:
            fsh = initShader(fragYUV420P, GL_FRAGMENT_SHADER);
            break;
        case AV_PIX_FMT_NV12:
            fsh = initShader(fragNV12, GL_FRAGMENT_SHADER);
            break;
        case AV_PIX_FMT_NV21:
            fsh = initShader(fragNV21, GL_FRAGMENT_SHADER);

            break;
        default:
            LOGE("format is error");
            return false;
    }

    if (fsh == 0) {
        LOGE("InitShader GL_FRAGMENT_SHADER failed!");
        return false;
    }
    LOGD("InitShader GL_FRAGMENT_SHADER success!");


    /////////////////////////////////////////////////////////////
    //创建渲染程序
    program = glCreateProgram();
    if (program == 0) {
        LOGE("glCreateProgram failed!");
        return false;
    }
    //渲染程序中加入着色器代码
    glAttachShader(program, vsh);
    glAttachShader(program, fsh);

    //链接程序
    glLinkProgram(program);
    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        LOGE("glLinkProgram failed!");
        return false;
    }
    glUseProgram(program);
    LOGE("glLinkProgram success!");
    /////////////////////////////////////////////////////////////


    //加入三维顶点数据 两个三角形组成正方形
    //opengl 坐标
    static float vers[] = {
            1.0f, -1.0f, 0.0f, //x,y,z
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
    };
    GLuint apos = (GLuint) glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(apos);
    //传递顶点坐标数据
    glVertexAttribPointer(apos, 3, GL_FLOAT, GL_FALSE, 12, vers);

    //加入材质坐标数据
    //纹理坐标
    static float txts[] = {
            1.0f, 0.0f, //右下
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0, 1.0
    };
    //传递材质顶点坐标数据
    GLuint atex = (GLuint) glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(atex);
    glVertexAttribPointer(atex, 2, GL_FLOAT, GL_FALSE, 8, txts);


    //材质纹理初始化
    //设置纹理层
    glUniform1i(glGetUniformLocation(program, "yTexture"), 0); //对于纹理第1层
    switch ((int)type) {
        case AV_PIX_FMT_YUV420P:
            glUniform1i(glGetUniformLocation(program, "uTexture"), 1); //对于纹理第2层
            glUniform1i(glGetUniformLocation(program, "vTexture"), 2); //对于纹理第3层
            break;
        case AV_PIX_FMT_NV21:
        case AV_PIX_FMT_NV12:
            glUniform1i(glGetUniformLocation(program, "uvTexture"), 1); //对于纹理第2层
            break;
    }

    LOGD("初始化Shader成功！");

    return true;

}

void EGLShader::draw() {
    if (!program)
        return;
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void EGLShader::getTexture(unsigned int index, int width, int height, unsigned char *buf,
                           bool isa) {

    unsigned int format = GL_LUMINANCE;
    if (isa)
        format = GL_LUMINANCE_ALPHA;
    if (texts[index] == 0) {
        //材质初始化
        glGenTextures(1, &texts[index]);

        //设置纹理属性
        glBindTexture(GL_TEXTURE_2D, texts[index]);
        //缩小的过滤器
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //设置纹理的格式和大小
        glTexImage2D(GL_TEXTURE_2D,
                     0,           //细节基本 0默认
                     format,//gpu内部格式 亮度，灰度图
                     width, height, //拉升到全屏
                     0,             //边框
                     format,//数据的像素格式 亮度，灰度图 要与上面一致
                     GL_UNSIGNED_BYTE, //像素的数据类型
                     NULL             //纹理的数据
        );
    }


    //激活第1层纹理,绑定到创建的opengl纹理
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texts[index]);
    //替换纹理内容
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, buf);
}




