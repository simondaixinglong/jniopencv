//
// Created by simonday on 2020/12/24.
//

#ifndef MY_APPLICATION_BITMAPMATUTIL_H
#define MY_APPLICATION_BITMAPMATUTIL_H

#include <jni.h>
#include "opencv2/opencv.hpp"

using namespace cv;

class BitmapMatUtil {

public:

	/**
	 * mat转bitmap
	 * @param env
	 * @param bitmap
	 * @param mat
	 * @return
	 */
	static int mat2Bitmap(JNIEnv *env, jobject bitmap, Mat &mat);


	/**
	 * bitmap转mat
	 * @param env
	 * @param bitmap
	 * @param mat
	 * @return
	 */
	static int bitmap2Mat(JNIEnv *env, jobject bitmap, Mat &mat);

};


#endif //MY_APPLICATION_BITMAPMATUTIL_H
