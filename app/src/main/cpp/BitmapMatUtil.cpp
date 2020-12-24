//
// Created by simonday on 2020/12/24.
//

#include "BitmapMatUtil.h"
#include <android/bitmap.h>


/**
 * bitmap转map
 * @param env
 * @param bitmap
 * @param mat
 * @return
 */
int BitmapMatUtil::bitmap2Mat(JNIEnv *env, jobject bitmap, Mat &mat) {

	void *pixes;

	//锁定画布
	AndroidBitmap_lockPixels(env, bitmap, &pixes);

	//构建mat对象，还要判断颜色通道0-255
	//获取bitmap的信息
	AndroidBitmapInfo bitmapInfo;
	AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

	//返回三通道 CV_8UC4->argb CV_8UC2->rgb CV_8UC1->黑白
	Mat createMat(bitmapInfo.height, bitmapInfo.width, CV_8UC2);
	//mat 里面四颜色通道 CV_8UC4
	if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
		Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixes);
		//4颜色通道转换成2颜色通道
		cvtColor(temp, createMat, COLOR_BGRA2BGR565);
		//mat 里面三颜色 CV_8UC2
	} else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
		Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, pixes);
		temp.copyTo(createMat);
	}

	createMat.copyTo(mat);

	//解锁画布
	AndroidBitmap_unlockPixels(env, bitmap);
	return 0;
}


/**
 * mat转bitmap
 * @param env
 * @param bitmap
 * @param mat
 * @return
 */
int BitmapMatUtil::mat2Bitmap(JNIEnv *env, jobject bitmap, Mat &mat) {

}