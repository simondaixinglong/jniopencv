//
// Created by simonday on 2020/12/24.
//

#include "Hello.h"
#include <android/log.h>
#include <string>
#include <queue>
#include "PriortyQueen.hpp"

using namespace std;

template<class T>
class TreeNode {
public:
	TreeNode(T data) {
		this->data = data;
	}

	T data; // 数据
	TreeNode *left = NULL;  // 左孩子
	TreeNode *right = NULL; // 右子树
};

int getDepthTree(TreeNode<char> *pNode) {
	if (pNode == NULL) {
		return 0;
	}
	int leftDepth = getDepthTree(pNode->left);
	int rightDepth = getDepthTree(pNode->right);
	return max(leftDepth, rightDepth) + 1;
}

bool isBalanceTree(TreeNode<char> *pNode) {
	// 可以是一棵空树，左右子树的高度差不会超过 1 ，并且左右两棵子树都是一棵平衡二叉树
	if (pNode == NULL) {
		return true;
	}
	// 左右子树的高度差不会超过 1
	int leftDepth = getDepthTree(pNode->left);
	int rightDepth = getDepthTree(pNode->right);

	// 并且左右两棵子树都是一棵平衡二叉树
	return abs(leftDepth - rightDepth) <= 1 && isBalanceTree(pNode->left) &&
		   isBalanceTree(pNode->right);
}


/**
 * 前序遍历 (必须写成模板才会通用) (方法的回调) 返回值void*visit(T)
 * 思考：CSDN 稳定性
 */
template<class T>
void preOrderTraverse(TreeNode<T> *pNode, void visit(T)) {// 怎么解决这个通用问题
	if (pNode == NULL) {
		return;
	}

	// 首先访问根节点
	visit(pNode->data);

	// 然后访问左节点
	preOrderTraverse(pNode->left, visit);

	// 最后再去访问右子树
	preOrderTraverse(pNode->right, visit);
}

void visitNode(char data) {
	__android_log_print(ANDROID_LOG_ERROR, "TAG", "%c", data);
}

/**
 * 中序遍历
 */
template<class T>
void infixOrderTraverse(TreeNode<T> *pNode, void visit(T)) {// 怎么解决这个通用问题
	if (pNode == NULL) {
		return;
	}

	// 访问左子树
	infixOrderTraverse(pNode->left, visit);

	// 访问根节点
	visit(pNode->data);

	// 访问右子树
	infixOrderTraverse(pNode->right, visit);
}

template<class T>
void epilogueOrderTraverse(TreeNode<T> *pNode, void visit(T)) {// 怎么解决这个通用问题
	if (pNode == NULL) {
		return;
	}

	// 访问左子树
	epilogueOrderTraverse(pNode->left, visit);
	// 访问右子树
	epilogueOrderTraverse(pNode->right, visit);
	// 访问根节点
	visit(pNode->data);
}

template<class T>
void levelOrderTraverse(TreeNode<T> *pNode, void visit(T)) {// 怎么解决这个通用问题
	if (pNode == NULL) {
		return;
	}

	queue<TreeNode<T> *> nodeQ;
	nodeQ.push(pNode);

	while (!nodeQ.empty()) {
		TreeNode<T> *front = nodeQ.front();
		nodeQ.pop();
		visit(front->data);

		if (front->left) {
			nodeQ.push(front->left);
		}
		if (front->right) {
			nodeQ.push(front->right);
		}
	}
}


/**
 * 序列化树
 * @param pNode
 * @param str
 */
void seralizeTree(TreeNode<char> *pNode, string *str) {
	if (pNode == NULL) {
		str->append("#");
		return;
	}

	//先输出根节点
	str->append(string(1, pNode->data));//1表示放一个字符串
	//输出左节点
	seralizeTree(pNode->left, str);
	//输出右节点
	seralizeTree(pNode->right, str);

}

/**
 * 反序列化 ABD##E##C#F##
 * 需要传二级指针，因为需要递归调用，必须是指向同一值
 * @param str
 * @return
 */
TreeNode<char> *deseralizeTree(char **str) {

	if (**str == '#') {
		*str += 1;
		return NULL;
	}

	TreeNode<char> *pNode = new TreeNode<char>(**str);
	*str += 1;
	pNode->left = deseralizeTree(str);
	pNode->right = deseralizeTree(str);

	return pNode;
}

/**
 * 调整大根堆
 * @param k
 */
void adjustHead(int array[], int size, int k) {
	while (k * 2 + 1 <= size) {//到底的情况
		//最大指向左孩子
		int max = 2 * k + 1;
		//判断是否有右孩子,且右孩子大于左孩子
		if (max + 1 <= size && array[max + 1] > array[max]) {
			max += 1;
		}
		//最大的是自己
		if (array[k] > array[max]) {
			break;
		}
		//交换，最大的网上冒
		swap(array[k], array[max]);
		k = max;
	}
}


void headSort(int arr[], int size) {

	//1.从最后一个不是叶子节点的节点开始调整为最大堆
	for (int i = size / 2 - 1; i >= 0; --i) {
		adjustHead(arr, size, i);
	}

	//2.第一个与最后一个交换，然后再调整为大根堆，不考虑最后一个
	for (int i = size - 1; i >= 0; --i) {
		swap(arr[0], arr[i]);
		//对第0个位置数据进行调整，
		adjustHead(arr, i, 0);
	}

}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_simon_a_jni_JNICard_cardOrc(JNIEnv *env, jclass clazz, jobject bitmap) {

	TreeNode<char> *A = new TreeNode<char>('A');
	TreeNode<char> *B = new TreeNode<char>('B');
	TreeNode<char> *C = new TreeNode<char>('C');
	TreeNode<char> *D = new TreeNode<char>('D');
	TreeNode<char> *E = new TreeNode<char>('E');
	TreeNode<char> *F = new TreeNode<char>('F');
	TreeNode<char> *G = new TreeNode<char>('G');

	A->left = B;
	A->right = C;

	B->left = D;
	B->right = E;

	C->right = F;


	/*__android_log_print(ANDROID_LOG_ERROR,"前序遍历","%c");
// 遍历 （前序，中序，后序，层序）
preOrderTraverse(A,visitNode);
__android_log_print(ANDROID_LOG_ERROR,"中序遍历","%c");
infixOrderTraverse(A,visitNode);
__android_log_print(ANDROID_LOG_ERROR,"后序遍历","%c");
epilogueOrderTraverse(A,visitNode);
// 层序遍历
__android_log_print(ANDROID_LOG_ERROR,"层序遍历","%c");
levelOrderTraverse(A,visitNode);*/

//	int depth = getDepthTree(A);
//	__android_log_print(ANDROID_LOG_ERROR, "TAG", "depth = %d", depth);
//
//	bool isBalance = isBalanceTree(A);
//	__android_log_print(ANDROID_LOG_ERROR, "TAG", "isBalanceTree = %d", isBalance);
//


//	string str;
//	//序列化
//	seralizeTree(A, &str);
//	__android_log_print(ANDROID_LOG_ERROR, "TAG", "%s", str.c_str());

//	//反序列化
//	char *treeStr = "ABD##E##C#F##";
//	TreeNode<char> *node = deseralizeTree(&treeStr);
//
//	string str;
//	//序列化
//	seralizeTree(node, &str);
//	__android_log_print(ANDROID_LOG_ERROR, "TAG", "%s", str.c_str());


	int n = 10;
	PriortyQueen<int> pQueen(n);
	for (int i = 0; i < n; ++i) {
		pQueen.push(rand() % 100);
	}

	while (!pQueen.isEmpty()) {
		__android_log_print(ANDROID_LOG_ERROR, "TAG", "%d", pQueen.pop());
	}

	return env->NewStringUTF("6888");


}


