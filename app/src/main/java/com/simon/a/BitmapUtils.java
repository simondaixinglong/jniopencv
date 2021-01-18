package com.simon.a;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;

/**
 * Author: simon
 * Description:
 * Date: 2021/1/14 1:58 PM
 * Version:1.0
 */
public class BitmapUtils {


    public static Bitmap gray(Bitmap src) {

        Bitmap des = Bitmap.createBitmap(src.getWidth(), src.getHeight(), src.getConfig());
        Canvas canvas = new Canvas(des);

        Paint paint = new Paint();
        paint.setAntiAlias(true);
        paint.setDither(true);

//        ColorMatrix colorMatrix = new ColorMatrix();
//        colorMatrix.setSaturation(0);

//        ColorMatrix colorMatrix = new ColorMatrix(new float[]{
//                1,0,0,0,0,
//                0,1,0,0,0,
//                0,0,1,0,0,
//                0,0,0,1,0,
//        });

        //底片效果
//        ColorMatrix colorMatrix = new ColorMatrix(new float[]{
//                -1,0,0,0,255,
//                0,-1,0,0,255,
//                0,0,-1,0,255,
//                0,0,0,1,0,
//        });

        //亮丽
        ColorMatrix colorMatrix = new ColorMatrix(new float[]{
                1.2f, 0, 0, 0, 0,
                0, 1.2f, 0, 0, 0,
                0, 0, 1.2f, 0, 0,
                0, 0, 0, 1, 0,
        });


        paint.setColorFilter(new ColorMatrixColorFilter(colorMatrix));


        canvas.drawBitmap(src, 0, 0, paint);
        return des;
    }


    public static Bitmap gray2(Bitmap src) {

        Bitmap des = Bitmap.createBitmap(src.getWidth(), src.getHeight(), src.getConfig());

        int[] pixels = new int[src.getWidth() * src.getHeight()];

        src.getPixels(pixels, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());
        for (int i = 0; i < pixels.length; i++) {
            int pixel = pixels[i];

            int a = (pixel >> 24) & 0xff;
            int r = (pixel >> 16) & 0xff;
            int g = (pixel >> 8) & 0xff;
            int b = (pixel) & 0xff;
            int gray = (int) (0.213f * r + 0.715f * g + 0.072f * b);

            pixels[i] = (a << 24) | (gray << 16) | (gray << 8) | gray;

        }

        des.setPixels(pixels, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());

        return des;
    }
}
