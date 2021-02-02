//
// Created by hcDarren on 2019/3/2.
//

#ifndef NDK_DAY72_AS_NATIVEMAT_CPP
#define NDK_DAY72_AS_NATIVEMAT_CPP

#include <jni.h>
#include "opencv2/opencv.hpp"

using namespace cv;
extern "C"
JNIEXPORT jlong JNICALL
Java_com_darren_opencv2_Mat_nMat(JNIEnv *env, jobject instance) {
    Mat *mat = new Mat();
    return reinterpret_cast<jlong>(mat);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_darren_opencv2_Mat_nMatIII(JNIEnv *env, jobject instance, jint rows, jint cols, jint type) {
    Mat *mat = new Mat(rows, cols, type);
    return reinterpret_cast<jlong>(mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_opencv2_Mat_nPutF(JNIEnv *env, jobject instance, jlong nativeptr, jint row,
                                  jint cols, jfloat value) {

    Mat *mat = reinterpret_cast<Mat*>(nativeptr);
    mat->at<float>(row,cols) = value;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_opencv2_Mat_nDelete(JNIEnv *env, jobject instance, jlong nativeptr) {
    Mat *mat = reinterpret_cast<Mat*>(nativeptr);
    delete(mat);
}

#endif //NDK_DAY72_AS_NATIVEMAT_CPP
