//
// Created by developer on 2018/9/16.
//

#include "OpenGLVideoView.h"
void OpenGLVideoView::SetRender(void *win)
{
    this->window = win;
}
void OpenGLVideoView::Render(AVData data)
{

    if(!window) return;
    if(!texture)
    {
        texture = Texture::Create();

        texture->Init(window, (AVPixelFormat) data.format);
    }
    texture->Draw(data.datas,data.width,data.height);
}