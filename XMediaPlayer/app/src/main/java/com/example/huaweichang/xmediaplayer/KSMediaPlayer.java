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

public class KSMediaPlayer implements SurfaceHolder.Callback, GLSurfaceView.Renderer {


    private GLSurfaceView mSurfaceView;

    public KSMediaPlayer() {
        _initialize();
    }

    public void setDataSource(String url) {
        _setDataSource(url);
    }

    public void setSurfaceView(GLSurfaceView surfaceView) {
        this.mSurfaceView=surfaceView;
        surfaceView.getHolder().addCallback(this);

    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        _setWindowSurface(surfaceHolder.getSurface());
        mSurfaceView.setRenderer(this);
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }

    public native void _initialize();

    public native void _startPlay();

    public native void _setDataSource(String url);

    public native void _stopPlay();

    public native void _release();

    public native void _setWindowSurface(Surface surface);

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {

    }

    @Override
    public void onDrawFrame(GL10 gl10) {

    }
}
