#include <jni.h>
#include <string>
#include "cv_helper.h"

using namespace cv;

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day72_MainActivity_mask(JNIEnv *env, jclass type, jobject bitmap) {

    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    // bgr
    Mat bgr;
    cvtColor(src, bgr, COLOR_BGRA2BGR);

    Mat kernel = Mat::zeros(Size(3, 3), CV_32FC1);
    kernel.at<float>(0, 1) = -1;
    kernel.at<float>(1, 0) = -1;
    kernel.at<float>(1, 1) = 5;
    kernel.at<float>(1, 2) = -1;
    kernel.at<float>(2, 1) = -1;

    Mat dst;
    filter2D(bgr, dst, src.depth(), kernel);

    cv_helper::mat2bitmap(env,dst,bitmap);
    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day72_MainActivity_blur(JNIEnv *env, jclass type, jobject bitmap) {

    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    // bgr
    Mat bgr;
    cvtColor(src, bgr, COLOR_BGRA2BGR);

    Mat kernel = Mat::ones(Size(15, 15), CV_32FC1)/(15 * 15);

    Mat dst;
    filter2D(bgr, dst, src.depth(), kernel);

    cv_helper::mat2bitmap(env,dst,bitmap);
    return bitmap;
}