package com.simon.a.jni;

import android.graphics.Bitmap;
import android.text.TextUtils;

import com.simon.a.jni.listener.MediaErrorListener;

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


    private MediaErrorListener mErrorListener;

    public void setOnErrorListener(MediaErrorListener mErrorListener) {
        this.mErrorListener = mErrorListener;
    }

    // called from jni
    private void onError(int code, String msg) {
        if (mErrorListener != null) {
            mErrorListener.onError(code, msg);
        }
    }

    /**
     * url 可以是本地文件路径，也可以是 http 链接
     */
    private String url;

    public void setDataSource(String url) {
        this.url = url;
    }

    public void play() {
        if (TextUtils.isEmpty(url)) {
            throw new NullPointerException("url is null, please call method setDataSource");
        }

        nPlay(url);
    }

    private native void nPlay(String url);


    private native void nPlay();

    public void prepare() {
        if (TextUtils.isEmpty(url)) {
            throw new NullPointerException("url is null, please call method setDataSource");
        }
        nPrepare(url);
    }

    private native void nPrepare(String url);
}
