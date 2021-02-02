#include <jni.h>
#include <string>
#include "cv_helper.h"
#include "bitmap_util.h"
#include <android/log.h>
#include <vector>

using namespace cv;
using namespace std;

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day77_MainActivity_hogBitmap(JNIEnv *env, jobject instance, jobject bitmap) {
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);

    // 拿 hog 的特征
    // 1. 分成 8* 8 的网格 ceil 求取直方图
    // 2. 对 ceil 的 4*4 的块去合并直方图，每次必须要有 1/2 的重叠区域
    // 3. 然后获取直方图的数据

    /*
     CV_WRAP HOGDescriptor() : winSize(64,128), blockSize(16,16), blockStride(8,8),
        cellSize(8,8), nbins(9), derivAperture(1), winSigma(-1),
        histogramNormType(HOGDescriptor::L2Hys), L2HysThreshold(0.2), gammaCorrection(true),
        free_coef(-1.f), nlevels(HOGDescriptor::DEFAULT_NLEVELS), signedGradient(false)
    {}


    Mat dst, dst_gary;
    resize(src, dst, Size(64, 128));
    cvtColor(dst, dst_gary, COLOR_BGRA2GRAY);

    HOGDescriptor hogDescriptor;
    vector<float> descriptors;
    vector<Point> locations;

     CV_WRAP virtual void compute(InputArray img,
                 CV_OUT std::vector<float>& descriptors,
                 Size winStride = Size(), Size padding = Size(),
                 const std::vector<Point>& locations = std::vector<Point>()) const;

    hogDescriptor.compute(dst_gary,descriptors,Size(),Size(),locations);

    __android_log_print(ANDROID_LOG_ERROR,"TAG","descriptors size : %d", descriptors.size());
    */

    /*
    CV_WRAP virtual void detectMultiScale(InputArray img, CV_OUT std::vector<Rect>& foundLocations,
                                          CV_OUT std::vector<double>& foundWeights, double hitThreshold = 0,
                                          Size winStride = Size(), Size padding = Size(), double scale = 1.05,
                                          double finalThreshold = 2.0,bool useMeanshiftGrouping = false) const;
                                          */
    // 训练样本，直接拿过来用
    Mat bgr;
    cvtColor(src, bgr, COLOR_BGRA2BGR);
    HOGDescriptor descriptor;
    descriptor.setSVMDetector(descriptor.getDefaultPeopleDetector());
    vector<Rect> foundLocations;
    descriptor.detectMultiScale(bgr, foundLocations, 0, Size(14, 14));
    for (int i = 0; i < foundLocations.size(); ++i) {
        rectangle(src, foundLocations[i], Scalar(255, 0, 0), 2, LINE_AA);
    }
    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day77_MainActivity_lbpBitmap(JNIEnv *env, jobject instance, jobject bitmap) {
    // 自己手写，来看看，两套 ，3*3 ，考虑步长和角度
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    Mat gary;
    cvtColor(src, gary, COLOR_BGRA2GRAY);
    // 3*3 lbp 计算的特征数据
    Mat result = Mat::zeros(Size(src.cols - 2, src.rows - 2), CV_8UC1);

    // 卷积操作
    for (int row = 1; row < gary.rows - 1; ++row) {
        for (int col = 1; col < gary.cols - 1; ++col) {
            uchar pixels = gary.at<uchar>(row, col);
            int rPixels = 0;
            rPixels |= (pixels >= gary.at<uchar>(row - 1, col - 1)) << 0;
            rPixels |= (pixels >= gary.at<uchar>(row - 1, col)) << 1;
            rPixels |= (pixels >= gary.at<uchar>(row - 1, col + 1)) << 2;
            rPixels |= (pixels >= gary.at<uchar>(row, col - 1)) << 7;
            rPixels |= (pixels >= gary.at<uchar>(row, col + 1)) << 3;
            rPixels |= (pixels >= gary.at<uchar>(row + 1, col - 1)) << 6;
            rPixels |= (pixels >= gary.at<uchar>(row + 1, col)) << 5;
            rPixels |= (pixels >= gary.at<uchar>(row + 1, col + 1)) << 4;

            result.at<uchar>(row - 1, col - 1) = rPixels;
        }
    }
    jobject resBitmap = bitmap_util::create_bitmap(env,result.cols,result.rows,src.type());
    cv_helper::mat2bitmap(env,result,resBitmap);
    return resBitmap;
}