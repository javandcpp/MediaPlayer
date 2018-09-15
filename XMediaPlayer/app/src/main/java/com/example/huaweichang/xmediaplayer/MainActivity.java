package com.example.huaweichang.xmediaplayer;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }


    public void openVideo(View view){
        openVideo("/sdcard/1080.mp4");
    }

    public native void openVideo(String s);



    @Override
    protected void onResume() {
        super.onResume();

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */



    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("Media");
    }
}
