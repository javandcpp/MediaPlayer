package com.example.huaweichang.xmediaplayer;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    private KSMediaPlayer ksMediaPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }




    public void openVideo(View view){
        MyGLSurfaceView glSurfaceView = findViewById(R.id.videoView);
        ksMediaPlayer = new KSMediaPlayer();
        ksMediaPlayer.setSurfaceView(glSurfaceView);

        ksMediaPlayer.setDataSource("/sdcard/test.mp4");
        ksMediaPlayer.startPrepareAsync();
    }

    @Override
    protected void onResume() {
        super.onResume();

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */



    // Used to load the 'native-lib' library on application startup.

}
