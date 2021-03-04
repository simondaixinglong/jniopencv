package com.simon.a;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.simon.a.jni.JNICard;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private TextView tvNum;
    private Bitmap cardBitmap;
    File mMusicFile;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mMusicFile = new File(Environment.getExternalStorageDirectory(), "input.mp3");
        setContentView(R.layout.activity_main);
        initParams();
    }

    private void initParams() {
        tvNum = findViewById(R.id.tv_num);
        cardBitmap = BitmapFactory.decodeResource(getResources(),R.drawable.card);
    }


    public void getCardNum(View view) {
//        tvNum.setText(JNICard.cardOrc(cardBitmap));

        Log.e("TAG", "file is exist: " + mMusicFile.exists());

        JNICard mPlayer = new JNICard();
        mPlayer.setDataSource(mMusicFile.getAbsolutePath());

//        mPlayer.setOnErrorListener(new MediaErrorListener() {
//            @Override
//            public void onError(int code, String msg) {
//                Log.e("TAG", "error code: " + code);
//                Log.e("TAG", "error msg: " + msg);
//                // Java 的逻辑代码
//            }
//        });

        mPlayer.prepare();
        mPlayer.play();

    }
}