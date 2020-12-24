package com.simon.a;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.simon.a.jni.JNICard;

public class MainActivity extends AppCompatActivity {

    private TextView tvNum;
    private Bitmap cardBitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initParams();
    }

    private void initParams() {
        tvNum = findViewById(R.id.tv_num);
        cardBitmap = BitmapFactory.decodeResource(getResources(),R.drawable.card);
    }


    public void getCardNum(View view) {
        tvNum.setText(JNICard.cardOrc(cardBitmap));
    }
}