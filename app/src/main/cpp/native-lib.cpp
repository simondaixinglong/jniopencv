#include <jni.h>
#include <string>
#include "opencv2/opencv.hpp"
#include <android/log.h>

using namespace cv;

#define TAG "FACE_TAG"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// 加载人脸识别的级联分类器
CascadeClassifier cascadeClassifier;

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_ndk_day78_FaceDetection_loadCascade(JNIEnv *env, jobject instance,
                                                    jstring filePath_) {
    const char *filePath = env->GetStringUTFChars(filePath_, 0);

    cascadeClassifier.load(filePath);
    LOGE("人脸识别级联分类器加载成功");
    env->ReleaseStringUTFChars(filePath_, filePath);
}

// 马赛克人脸效果，不让大家看到我
void mosaicFace(Mat mat) {
    // 获取图片宽高
    int src_w = mat.cols;
    int src_h = mat.rows;

    // 省略人脸识别
    int rows_s = src_h / 6;
    int rows_e = src_h * 5 / 6;
    int cols_s = src_w / 6;
    int cols_e = src_w * 5 / 6;
    int size = 15;

    for (int rows = rows_s; rows < rows_e; rows += size) {
        for (int cols = cols_s; cols < cols_e; cols += size) {
            int pixels = mat.at<int>(rows, cols);
            for (int m_rows = 1; m_rows < size; ++m_rows) {
                for (int m_cols = 1; m_cols < size; ++m_cols) {
                    mat.at<int>(rows + m_rows, cols + m_cols) = pixels;
                }
            }
        }
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_ndk_day78_FaceDetection_faceDetection__J(JNIEnv *env, jobject instance,
                                                         jlong nativeObj) {
    Mat *src = reinterpret_cast<Mat *>(nativeObj);

    int width = src->rows;
    int height = src->cols;

    Mat grayMat;
    // 2. 转成灰度图，提升运算速度，灰度图所对应的 CV_8UC1 单颜色通道，信息量少 0-255 1u
    cvtColor(*src, grayMat, COLOR_BGRA2GRAY);

    // 4. 检测人脸，这是个大问题
    // 参数 1.1 会采取上采样和降采样 ，缩放比例
    // 参数 3 检测多少次
    // 参数 Size(width / 2, height / 2) 最小脸的大小
    std::vector<Rect> faces;
    cascadeClassifier.detectMultiScale(grayMat, faces, 1.1, 3, 0, Size(width / 2, height / 2));
    LOGE("人脸size = %d", faces.size());

    if (faces.size() != 1) {
        mosaicFace(*src);
        return;
    }

    // 把脸框出来
    Rect faceRect = faces[0];
    rectangle(*src, faceRect, Scalar(255, 0, 0, 255), 4, LINE_AA);

    // 与服务端进行比对，是不是我
    mosaicFace((*src)(faceRect));
}