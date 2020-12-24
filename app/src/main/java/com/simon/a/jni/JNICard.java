package com.simon.a.jni;

import android.graphics.Bitmap;

/**
 * Author: simon
 * Description:
 * Date: 2020/12/24 10:30 AM
 * Version:1.0
 */
public class JNICard {

    static {
        System.loadLibrary("Hello");
    }

    public static native String cardOrc(Bitmap bitmap);

}
