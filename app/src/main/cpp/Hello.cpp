//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include "huffman.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {



	//We build the tree depending on the string
	// 生成一棵最优的前缀码霍夫曼树
	htTree *codeTree = buildTree("aaaabbcccccccd");
	//We build the table depending on the Huffman tree
	// 根据霍夫曼树生成映射表
	hlTable *codeTable = buildTable(codeTree);

	//We encode using the Huffman table
	encode(codeTable,"aaaabbcccccccd");
	//We decode using the Huffman tree
	//We can decode string that only use symbols from the initial string
	decode(codeTree,"0011111000111");
	//Output : 0011 1110 1011 0001 0010 1010 1100 1111 1000 1001

	return env->NewStringUTF("6888");



}
