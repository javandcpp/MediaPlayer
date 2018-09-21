package com.example.huaweichang.xmediaplayer;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.jar.Attributes;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by huaweichang on 2018/9/21.
 */

public class MyGLSurfaceView extends GLSurfaceView implements SurfaceHolder.Callback ,GLSurfaceView.Renderer {

    private Surface mSurface;

    public MyGLSurfaceView(Context context, AttributeSet attributes) {
        super(context,attributes);
    }
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        setRenderer(this);
        mSurface = holder.getSurface();
    }

    public Surface getSurface(){
        return mSurface;
    }

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
