package com.simon.a;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.storage.StorageManager;
import android.view.View;
import android.widget.TextView;

import com.simon.a.jni.JNICard;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private TextView tvNum;
    private Bitmap cardBitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE}, 0);
        }


        initParams();
    }

    private void initParams() {
        tvNum = findViewById(R.id.tv_num);
        cardBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.card);
    }


    public void getCardNum(View view) {
//        File file = new File(getFileRoot() + "/ocr/a.txt");
//        if (!file.exists()) {
//            file.mkdirs();
//        }


        tvNum.setText(JNICard.cardOrc(cardBitmap));
    }

    private String getFileRoot() {
        if (Environment.getExternalStorageState().equals(
                Environment.MEDIA_MOUNTED)) {
            File external = getExternalFilesDir(null);
            if (external != null) {
                return external.getAbsolutePath();
            }
        }
        return getFilesDir().getAbsolutePath();
    }
}