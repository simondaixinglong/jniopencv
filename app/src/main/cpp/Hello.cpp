//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include "map.hpp"
#include <android/log.h>

void visit(int key, int value, bool isRed) {
    if (isRed) {
        __android_log_print(ANDROID_LOG_ERROR, "TAG", "key = %d , value = %d , color = %s", key, value,"红");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "TAG", "key = %d , value = %d , color = %s", key, value,"黑");
    }
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {


	    map<int, int> *map = new ::map<int, int>();
        map->insert(3, 3);
        map->insert(2, 2);
        map->insert(1, 1);
        map->insert(4, 4);
        map->insert(5, 5);
        map->insert(-5, -5);
        map->insert(-15, -15);
        map->insert(-10, -10);
        map->insert(6, 6);
        map->insert(7, 7);

        map->remove(2);

        map->levelTraverse(visit);


	return env->NewStringUTF("6888");



}
