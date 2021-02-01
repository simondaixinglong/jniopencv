#include <jni.h>
#include <string>
#include "cv_helper.h"
#include "bitmap_util.h"
#include <android/log.h>

using namespace cv;


extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day71_OpenCvUtils_rotation(JNIEnv *env, jclass type, jobject bitmap) {
    // 旋转 90 度
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    // Canvas 90  180 度？
    int res_w = src.rows;
    int res_h = src.cols;

    Mat res(res_h, res_w, src.type());

    for (int rows = 0; rows < res_h; ++rows) {
        for (int cols = 0; cols < res_w; ++cols) {
            // res_w, res_h , 疑问？
            int src_rows = cols;
            int src_cols = res_h - rows;
            res.at<int>(rows, cols) = src.at<int>(src_rows, src_cols);
        }
    }

    // 创建一个新的 bitmap w,h = h,w
    jobject newBitmap = bitmap_util::create_bitmap(env, res_w, res_h, res.type());
    cv_helper::mat2bitmap(env, res, newBitmap);
    return newBitmap;
}
// 调试，非常麻烦，可以网上查一些资料
extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day71_OpenCvUtils_reSize(JNIEnv *env, jclass type, jobject bitmap, jint width,
                                             jint height) {
    // 上采样和降采样
    // 最近领域插值
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    Mat res(height, width, src.type());

    float src_w = src.cols;
    float src_h = src.rows;

    for (int rows = 0; rows < res.rows; ++rows) {
        for (int cols = 0; cols < res.cols; ++cols) {
            //  height 100 src_h 200
            int src_rows = rows * (src_h / height);// src 的 高
            int src_cols = cols * (src_w / width);
            Vec4b pixels = src.at<Vec4b>(src_rows, src_cols);
            res.at<Vec4b>(rows, cols) = pixels;
        }
    }

    jobject newBitmap = bitmap_util::create_bitmap(env, width, height, src.type());
    cv_helper::mat2bitmap(env, res, newBitmap);
    return newBitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day71_OpenCvUtils_warpAffine(JNIEnv *env, jclass type, jobject bitmap) {
    // 旋转 90 度
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);

    Mat res(src.size(), src.type());
    /*Mat M(2,3,CV_32FC1);
    // 这几个值应该怎么确定？
    // [a0,a1,a2]     两个矩阵    [a0,a1]    [a2]       =     [ x ]     *     [a0,a1]    +   [a2]    =   a0*x+b0*x + a2
    // [b0,b1,b2]                 [b0,b1]    [b2]             [ y ]           [b0,b1]        [b2]    =   b0*y+b1*y + b2
    M.at<float>(0,0) = 1;// a0
    M.at<float>(0,1) = 0;// a1
    M.at<float>(0,2) = 0;// a2
    M.at<float>(1,0) = 0;
    M.at<float>(1,1) = 1;
    M.at<float>(1,2) = 0;*/

    Point2f center(src.cols / 2, src.rows / 2);
    double angle = 45;
    double scale = 1;
    Mat M = getRotationMatrix2D(center, angle, scale);

    warpAffine(src, res, M, src.size());
    cv_helper::mat2bitmap(env, res, bitmap);

    return bitmap;
}

void remap(Mat &src, Mat &res, Mat &matX, Mat &matY) {
    res.create(src.size(), src.type());
    int res_w = res.cols;
    int res_h = res.rows;
    for (int rows = 0; rows < res_h; ++rows) {
        for (int cols = 0; cols < res_w; ++cols) {
            int x = matX.at<int>(rows, cols);
            int y = matY.at<int>(rows, cols);
            res.at<Vec4b>(rows, cols) = src.at<Vec4b>(y, x);
        }
    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day71_OpenCvUtils_reMap(JNIEnv *env, jclass type, jobject bitmap) {
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    Mat res;

    Mat matX(src.size(), src.type());
    Mat matY(src.size(), src.type());

    for (int rows = 0; rows < src.rows; ++rows) {
        for (int cols = 0; cols < src.cols; ++cols) {
            matX.at<int>(rows, cols) = src.cols - cols;
            matY.at<int>(rows, cols) = src.rows - rows;
        }
    }

    remap(src, res, matX, matY);
    cv_helper::mat2bitmap(env, res, bitmap);
    return bitmap;
}