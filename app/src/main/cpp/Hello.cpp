//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include "AVL.hpp"
#include <android/log.h>

void visit(int key, int value) {
	__android_log_print(ANDROID_LOG_ERROR, "TAG", "key = %d , value = %d", key, value);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {


	AVL<int, int> *avl = new AVL<int, int>();
	avl->put(3, 3);
	avl->put(1, 1);
	avl->put(2, 2);
	avl->put(4, 4);
	avl->put(5, 5);
	avl->put(6, 6);
	avl->put(7, 7);
	avl->put(10, 10);
	avl->put(9, 9);
	avl->put(8, 8);

	avl->remove(6);
	avl->remove(5);

	avl->levelTraverse(visit);



	return env->NewStringUTF("6888");



}
