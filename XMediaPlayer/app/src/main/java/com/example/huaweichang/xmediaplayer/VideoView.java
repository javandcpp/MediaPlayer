package com.example.huaweichang.xmediaplayer;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;

public class VideoView extends GLSurfaceView implements SurfaceHolder.Callback {
    public VideoView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        initNativeEGL(holder.getSurface());
    }

    public native void initNativeEGL(Surface surface);

    public native void release();
}
