//
// Created by hcDarren on 2019/3/2.
//

#ifndef NDK_DAY72_AS_NATIVEUTILS_CPP
#define NDK_DAY72_AS_NATIVEUTILS_CPP

#include <jni.h>
#include "cv_helper.h"
#include "opencv2/opencv.hpp"
using namespace cv;

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_opencv2_Utils_nbitmap2mat(JNIEnv *env, jclass type, jobject bitmap, jlong matPtr) {
    Mat *mat = reinterpret_cast<Mat*>(matPtr);
    cv_helper::bitmap2mat(env,bitmap,*mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_opencv2_Utils_nmat2bitmap(JNIEnv *env, jclass type, jlong matPtr, jobject bitmap) {
    Mat *mat = reinterpret_cast<Mat*>(matPtr);
    cv_helper::mat2bitmap(env,*mat,bitmap);
}

#endif //NDK_DAY72_AS_NATIVEUTILS_CPP