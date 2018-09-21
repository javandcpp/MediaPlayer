package com.example.huaweichang.xmediaplayer;

import android.opengl.GLSurfaceView;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


/**
 * Created by huaweichang on 2018/9/16.
 */

public class KSMediaPlayer{


    private MyGLSurfaceView mSurfaceView;

    private void loadNativelibrary() {
        System.loadLibrary("Media");
    }

    public KSMediaPlayer() {
        loadNativelibrary();
        _initialize();
    }

    public void setDataSource(String url) {
        _setWindowSurface(mSurfaceView.getSurface());
        _setDataSource(url);
    }

    public void setSurfaceView(MyGLSurfaceView surfaceView) {
        this.mSurfaceView = surfaceView;


    }

    public void startPrepareAsync(){
        _startPlay();
    }

    public native void _initialize();

    private native void _startPlay();

    public native void _setDataSource(String url);

    public native void _stopPlay();

    public native void _release();

    public native void _setWindowSurface(Surface surface);

}
