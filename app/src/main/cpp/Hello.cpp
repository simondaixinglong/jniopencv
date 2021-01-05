//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include "BST.hpp"
#include <android/log.h>

void visit(int key, int value) {
	__android_log_print(ANDROID_LOG_ERROR, "TAG", "key:%d--value:%d", key, value);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {


	BST<int, int> *bst = new BST<int, int>();

	bst->put(2, 2);
	bst->put(-11, -11);
	bst->put(1, 1);
	bst->put(20, 20);
	bst->put(4, 4);
	bst->put(9, 9);

	bst->inOrderTraverse(visit);

	return env->NewStringUTF("6888");

}
