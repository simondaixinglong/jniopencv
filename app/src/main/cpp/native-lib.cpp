#include <jni.h>
#include <string>
#include <android/log.h>
#include "cv_helper.h"

using namespace std;
using namespace cv;

// 静态注册， 动态注册（6.0 以上 frameworker NDK 源码）  Linux
extern "C"
JNIEXPORT jobject
JNICALL
Java_com_darren_ndk_day70_NDKBitmapUtils_againstWorld(JNIEnv *env, jclass type, jobject bitmap) {
    // bitmap -> mat
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    Mat res(src.size(), src.type());
    // 获取图片宽高
    int src_w = src.cols;
    int src_h = src.rows;
    int mid_h = src_h >> 1;
    int a_h = mid_h >> 1;
    // 处理下半部分
    for (int rows = 0; rows < mid_h; ++rows) {
        for (int cols = 0; cols < src_w; ++cols) {
            // 4 rgba  , 判断 type()
            res.at<Vec4b>(rows + mid_h, cols) = src.at<Vec4b>(rows + a_h, cols);
        }
    }

    // 处理下半部分
    for (int rows = 0; rows < mid_h; ++rows) {
        for (int cols = 0; cols < src_w; ++cols) {
            // 4 rgba  , 判断 type()
            res.at<Vec4b>(rows, cols) = src.at<Vec4b>(src_h - a_h - rows, cols);
        }
    }

    cv_helper::mat2bitmap(env, res, bitmap);

    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day70_NDKBitmapUtils_anaglyph(JNIEnv *env, jclass type, jobject bitmap) {
    // 有立体感，突出了轮廓信息，opencv  卷积
    // [1,0]
    // [0,-1]
    // bitmap -> mat
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    Mat res(src.size(), src.type());
    // 获取图片宽高
    int src_w = src.cols;
    int src_h = src.rows;

    for (int rows = 0; rows < src_h - 1; ++rows) {
        for (int cols = 0; cols < src_w - 1; ++cols) {
            Vec4b pixels_p = src.at<Vec4b>(rows, cols);
            Vec4b pixels_n = src.at<Vec4b>(rows + 1, cols + 1);
            // bgra
            res.at<Vec4b>(rows, cols)[0] = saturate_cast<uchar>(pixels_p[0] - pixels_n[0] + 128);
            res.at<Vec4b>(rows, cols)[1] = saturate_cast<uchar>(pixels_p[1] - pixels_n[1] + 128);
            res.at<Vec4b>(rows, cols)[2] = saturate_cast<uchar>(pixels_p[2] - pixels_n[2] + 128);
        }
    }

    cv_helper::mat2bitmap(env, res, bitmap);

    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day70_NDKBitmapUtils_mosaic(JNIEnv *env, jclass type, jobject bitmap) {
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);

    // 获取图片宽高
    int src_w = src.cols;
    int src_h = src.rows;

    // 省略人脸识别
    int rows_s = src_h >> 2;
    int rows_e = src_h * 3 / 4;
    int cols_s = src_w >> 2;
    int cols_e = src_w * 3 / 4;
    int size = 10;

    for (int rows = rows_s; rows < rows_e; rows += size) {
        for (int cols = cols_s; cols < cols_e; cols += size) {
            int pixels = src.at<int>(rows, cols);
            for (int m_rows = 1; m_rows < size; ++m_rows) {
                for (int m_cols = 1; m_cols < size; ++m_cols) {
                    src.at<int>(rows + m_rows, cols + m_cols) = pixels;
                }
            }
        }
    }

    cv_helper::mat2bitmap(env, src, bitmap);
    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day70_NDKBitmapUtils_groundGlass(JNIEnv *env, jclass type, jobject bitmap) {
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    // 高斯模糊，毛玻璃 （对某个区域取随机像素）
    int src_w = src.cols;
    int src_h = src.rows;
    int size = 8;
    // 知识不是用来背的 20% ，用来唤醒大家的
    RNG rng(time(NULL));
    for (int rows = 0; rows < src_h - size; ++rows) {
        for (int cols = 0; cols < src_w - size; ++cols) {
            int random = rng.uniform(0, 8);
            src.at<int>(rows, cols) = src.at<int>(rows + random, cols + random);
        }
    }
    cv_helper::mat2bitmap(env, src, bitmap);
    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day70_NDKBitmapUtils_oilPainting(JNIEnv *env, jclass type, jobject bitmap) {
    // 油画基于直方统计
    // 1. 每个点需要分成 n*n 小块
    // 2. 统计灰度等级
    // 3. 选择灰度等级中最多的值
    // 4. 找到所有的像素取平均值
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    Mat gary;
    cvtColor(src, gary, COLOR_BGRA2GRAY);
    Mat res(src.size(), src.type());

    int src_w = src.cols;
    int src_h = src.rows;
    int size = 8;
    // 知识不是用来背的 20% ，用来唤醒大家的
    for (int rows = 0; rows < src_h - size; ++rows) {
        for (int cols = 0; cols < src_w - size; ++cols) {
            int g[8] = {0}, b_g[8] = {0}, g_g[8] = {0}, r_g[8] = {0};// 255/8
            // 这个位置  64 循环 -> 1 个像素点 ， 高斯模糊 ，想想怎么优化
            for (int o_rows = 0; o_rows < size; ++o_rows) {
                for (int o_cols = 0; o_cols < size; ++o_cols) {
                    uchar gery = gary.at<uchar>(rows + o_rows, cols + o_cols);
                    uchar index = gery / (254 / 7); // 254*8/254
                    g[index] += 1;
                    // 等级的像素值之和
                    b_g[index] += src.at<Vec4b>(rows + o_rows, cols + o_cols)[0];
                    g_g[index] += src.at<Vec4b>(rows + o_rows, cols + o_cols)[1];
                    r_g[index] += src.at<Vec4b>(rows + o_rows, cols + o_cols)[2];
                }
            }
            // 最大的角标找出来
            int max_index = 0;
            int max = g[0];
            for (int i = 1; i < size; ++i) {
                if (g[max_index] < g[i]) {
                    max_index = i;
                    max = g[i];
                }
            }
            // 会超过 255 ， 会不会超过，超过了会怎样 （头条面试）  截取掉最高位
            res.at<Vec4b>(rows, cols)[0] = b_g[max_index] / max;
            res.at<Vec4b>(rows, cols)[1] = g_g[max_index] / max;
            res.at<Vec4b>(rows, cols)[2] = r_g[max_index] / max;
        }
    }

    cv_helper::mat2bitmap(env, res, bitmap);

    return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_darren_ndk_day70_NDKBitmapUtils_garyOptimize(JNIEnv *env, jclass type, jobject bitmap) {
    Mat src;
    cv_helper::bitmap2mat(env, bitmap, src);
    // 高斯模糊，毛玻璃 （对某个区域取随机像素）
    int src_w = src.cols;
    int src_h = src.rows;
    // 知识不是用来背的 20% ，用来唤醒大家的
    for (int rows = 0; rows < src_h; ++rows) {
        for (int cols = 0; cols < src_w; ++cols) {
            Vec4b pixels = src.at<Vec4b>(rows, cols);
            uchar b = pixels[0];
            uchar g = pixels[1];
            uchar r = pixels[2];
            // 好几种算法求灰度
            // uchar gery = (b + g + r) / 3;
            // 位移 > +- >  */  int > float
            // uchar gery = 0.299 * r + 0.587 * g + 0.1114 * b;
            uchar gery = (r + (g << 1) + b) >> 2; // 0.4  sobel  |x|+|y|
            src.at<Vec4b>(rows, cols)[0] = gery;
            src.at<Vec4b>(rows, cols)[1] = gery;
            src.at<Vec4b>(rows, cols)[2] = gery;
        }
    }
    return bitmap;
}