//
// Created by hcDarren on 2019/3/2.
//

#ifndef NDK_DAY72_AS_NATIVEIMGPROC_CPP
#define NDK_DAY72_AS_NATIVEIMGPROC_CPP

#include <jni.h>
#include "opencv2/opencv.hpp"

using namespace cv;

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_opencv2_Imgproc_nFilter2D(JNIEnv *env, jclass type, jlong srcPtr,
                                          jlong dstPtr, jlong kernelPtr) {

    Mat *src = reinterpret_cast<Mat*>(srcPtr);
    Mat *dst = reinterpret_cast<Mat*>(dstPtr);
    Mat *kernel = reinterpret_cast<Mat*>(kernelPtr);

    Mat bgr;
    cvtColor(*src,bgr,COLOR_BGRA2BGR);

    filter2D(bgr,*dst,src->depth(),*kernel);
}

#endif //NDK_DAY72_AS_NATIVEIMGPROC_CPP
