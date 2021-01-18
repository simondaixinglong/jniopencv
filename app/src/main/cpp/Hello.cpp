//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include <android/bitmap.h>


extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {


	return env->NewStringUTF("6888");


}
extern "C"
JNIEXPORT jint JNICALL
Java_com_simon_a_jni_JNICard_gray(JNIEnv *env, jclass clazz, jobject bitmap) {

	AndroidBitmapInfo androidBitmapInfo;
	int info_res = AndroidBitmap_getInfo(env, bitmap, &androidBitmapInfo);
	if (info_res != 0) {
		return -1;
	}

	//void* 指针，因为并不知道图片像素的类型
	void *pixels;

	AndroidBitmap_lockPixels(env, bitmap, &pixels);

	if (androidBitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
		for (int i = 0; i < androidBitmapInfo.width * androidBitmapInfo.height; ++i) {
			uint32_t *pixel_p = reinterpret_cast<uint32_t *>(pixels) + i;
			uint32_t pixel = *pixel_p;

			int a = (pixel >> 24) & 0xff;
			int r = (pixel >> 16) & 0xff;
			int g = (pixel >> 8) & 0xff;
			int b = (pixel) & 0xff;
			int gray = (int) (0.213f * r + 0.715f * g + 0.072f * b);

			*pixel_p = (a << 24) | (gray << 16) | (gray << 8) | gray;

		}
	} else if (androidBitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
		for (int i = 0; i < androidBitmapInfo.width * androidBitmapInfo.height; ++i) {
			uint16_t *pixel_p = reinterpret_cast<uint16_t *>(pixels) + i;
			uint16_t pixel = *pixel_p;

			int r = ((pixel >> 11) & 0x1f) << 3;//5
			int g = ((pixel >> 5) & 0x3f) << 2;//6
			int b = ((pixel) & 0x1f) << 3;//5
			int gray = (int) (0.213f * r + 0.715f * g + 0.072f * b);

			*pixel_p = ((gray >> 3) << 11) | ((gray >> 2) << 5) | (gray >> 3);

		}
	}


	AndroidBitmap_unlockPixels(env, bitmap);
	return 0;
}