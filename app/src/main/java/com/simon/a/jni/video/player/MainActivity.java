package com.simon.a.jni.video.player;

import android.os.Bundle;
import android.os.Environment;
import android.view.Surface;
import android.view.View;


import com.simon.a.R;
import com.simon.a.jni.media.DZVideoView;

import java.io.File;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private File mVideoFile = new File(Environment.getExternalStorageDirectory(), "BaiduNetdisk/我的资源/01.mp4");
    private DZVideoView mVideoView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mVideoView = findViewById(R.id.video_view);
    }

    public void play(View view) {
        mVideoView.play(mVideoFile.getAbsolutePath());

        decodeVideo(mVideoFile.getAbsolutePath(),mVideoView.getHolder().getSurface());
    }

    private native void decodeVideo(String absolutePath, Surface surface);
}
