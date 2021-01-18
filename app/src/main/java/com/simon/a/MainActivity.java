package com.simon.a;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.simon.a.jni.JNICard;

public class MainActivity extends AppCompatActivity {

    private Bitmap cardBitmap;
    private ImageView img2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initParams();
    }

    private void initParams() {
        cardBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.car);

        JNICard.gray(cardBitmap);

//        Bitmap gray = BitmapUtils.gray2(cardBitmap);

        img2 = findViewById(R.id.img_2);
        img2.setImageBitmap(cardBitmap);
    }
}