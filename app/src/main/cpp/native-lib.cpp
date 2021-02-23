#include <jni.h>
#include <string>
#include <android/log.h>
#include <queue>
#include <cmath>

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
    return abs(leftDepth - rightDepth) <= 1 && isBalanceTree(pNode->left) && isBalanceTree(pNode->right);
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

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_ndk_day42_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

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
    // F->left = G;

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

    int depth = getDepthTree(A);
    __android_log_print(ANDROID_LOG_ERROR, "TAG", "depth = %d", depth);

    bool isBalance = isBalanceTree(A);
    __android_log_print(ANDROID_LOG_ERROR, "TAG", "isBalanceTree = %d", isBalance);
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}






