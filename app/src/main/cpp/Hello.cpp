//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include "BitmapMatUtil.h"
#include <android/log.h>
#include "cardorc.h"
#include <vector>

using namespace std;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {


	Mat mat;
	BitmapMatUtil::bitmap2Mat(env, bitmap, mat);


//	Rect cardArea;
//	co1::find_card_area(mat, cardArea);

	//找到了银行卡区域然后进行裁剪
//	Mat card_mat(mat, cardArea);

//	imwrite("/storage/emulated/0/Android/data/com.simon.a/files/card_mat.jpg", card_mat);


	Rect numberArea;
	co1::find_card_number_area(mat, numberArea);

	//找到了银行卡区域然后进行裁剪
	Mat card_number_mat(mat, numberArea);

//	imwrite("/storage/emulated/0/Android/data/com.simon.a/files/number_mat.jpg", card_number_mat);

	vector<Mat> numbers;
	co1::find_card_number(card_number_mat, numbers);

	return env->NewStringUTF("6888");
}
