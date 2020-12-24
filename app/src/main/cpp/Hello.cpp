//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {


	return env->NewStringUTF("6888");



}
