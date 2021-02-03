package com.darren.ndk.day78;

import org.opencv.core.Mat;

/**
 * Created by hcDarren on 2018/2/3.
 */

public class FaceDetection {
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * 检测人脸并保存人脸信息
     *
     * @param mat 当前帧
     */
    public void faceDetection(Mat mat) {
        faceDetection(mat.nativeObj);
    }

    /**
     * 加载人脸识别的分类器文件
     *
     * @param filePath
     */
    public native void loadCascade(String filePath);

    private native void faceDetection(long nativeObj);

    public native void trainingPattern();

    // 加载样本数据
    public native void loadPattern(String patternPath);
}
