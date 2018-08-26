//
// Created by developer on 8/26/18.
//

#ifndef XMEDIAPLAYER_MLOG_H
#define XMEDIAPLAYER_MLOG_H


#ifdef ANDROID

#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"XMediaPlayer",__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"XMediaPlayer",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"XMediaPlayer",__VA_ARGS__)
#else

#endif


#endif //XMEDIAPLAYER_MLOG_H
