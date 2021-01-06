//
// Created by hcDarren on 2018/10/13.
//

#ifndef NDK_DAY44_BST_H
#define NDK_DAY44_BST_H


#include "../../../../../../../../Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64/lib64/clang/9.0.8/include/opencl-c-base.h"

using namespace std;

// c++   Map  MlitiMap  红黑树
// java Map 和 c++ Map 比较
template<class K, class V>
struct TreeNode {
public:
    TreeNode<K, V> *left = NULL;
    TreeNode<K, V> *right = NULL;
    K key;
    V value;
    int height;// 当前树的高度

    TreeNode(K key, V value) : height(1) {// 初始节点的高度为 1
        this->right = NULL;
        this->left = NULL;
        this->key = key;
        this->value = value;
    }

    TreeNode(TreeNode<K, V> *pNode) : height(pNode->height) {
        this->left = pNode->left;
        this->right = pNode->right;
        this->key = pNode->key;
        this->value = pNode->value;
    }
};

template<class K, class V>
class AVL {
    TreeNode<K, V> *root;// 根节点
    int count;// 个数

public:
    AVL() {
        root = NULL;
        count = 0;
    }

    ~AVL() {
        // 大家自己去完成
    }

public:

// 新增 （修改）
    void put(K key, V value) {
        root = addNode(root, key, value);
    }

    // 查找 （自己实现）
    V *get(K key) {

        return NULL;
    }

    int size() {
        return count;
    }

    // 写完
    bool contains(K key) {
        TreeNode<K, V> *node = root;

        while (node) {
            if (node->key == key) {
                return node->value;
            } else if (node->key > key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        return false;
    }


// 删除 (最主要的内容)
    void remove(K key) {
        // 分情况解决
        root = removeNode(root, key);
    }

    // 中序遍历
    void inOrderTraverse(void (*fun)(K, V)) {
        inOrderTraverse(root, fun);
    }

    // 层序遍历
    void levelTraverse(void (*fun)(K, V)) {
        if (root == NULL) {
            return;
        }
        TreeNode<K, V> *node = root;
        queue<TreeNode<K, V> *> nodes;
        nodes.push(node);
        while (!nodes.empty()) {
            node = nodes.front();
            fun(node->key, node->value);
            nodes.pop();

            if (node->left) {
                nodes.push(node->left);
            }

            if (node->right) {
                nodes.push(node->right);
            }
        }
    }

private:
    int getHeight(TreeNode<K, V> *pNode) {
        return pNode ? pNode->height : 0;
    }

    // 四个旋转操作

    // 右旋
    TreeNode<K, V> *R_Rotation(TreeNode<K, V> *pNode) {
        TreeNode<K, V> *left = pNode->left;
        TreeNode<K, V> *right = left->right;
        left->right = pNode;
        // 按道理如果右边不等于 NULL
        pNode->left = right;

        //  更新高度
        pNode->height = max(getHeight(pNode->left), getHeight(pNode->right)) + 1;
        left->height = max(getHeight(left->left), getHeight(left->right)) + 1;
        return left;
    }

    // 左旋
    TreeNode<K, V> *L_Rotation(TreeNode<K, V> *pNode) {
        TreeNode<K, V> *right = pNode->right;
        pNode->right = right->left;
        right->left = pNode;

        //  更新高度
        pNode->height = max(getHeight(pNode->left), getHeight(pNode->right)) + 1;
        right->height = max(getHeight(right->left), getHeight(right->right)) + 1;
        return right;
    }

    // 先左旋再右旋
    TreeNode<K, V> *L_R_Rotation(TreeNode<K, V> *pNode) {
        pNode->left = L_Rotation(pNode->left);
        return R_Rotation(pNode);
    }

    // 先右旋再左旋
    TreeNode<K, V> *R_L_Rotation(TreeNode<K, V> *pNode) {
        pNode->right = R_Rotation(pNode->right);
        return L_Rotation(pNode);
    }

// 返回一个节点 (逻辑问题？ 1 ，2) ，多去理解
    TreeNode<K, V> *addNode(TreeNode<K, V> *pNode, K key, V value) {
        if (pNode == NULL) {
            count++;
            return new TreeNode<K, V>(key, value);
        }

        if (pNode->key > key) {// 小
            pNode->left = addNode(pNode->left, key, value);
            if (getHeight(pNode->left) - getHeight(pNode->right) == 2) {
                // 调整 , 不能简简单单的就做一次右旋
                if (getHeight(pNode->left->right) > getHeight(pNode->left->left)) {
                    pNode = L_R_Rotation(pNode);
                } else {
                    pNode = R_Rotation(pNode);
                }
            }
        } else if (pNode->key < key) {
            pNode->right = addNode(pNode->right, key, value);
            if (getHeight(pNode->right) - getHeight(pNode->left) == 2) {
                // 调整
                if (getHeight(pNode->right->left) > getHeight(pNode->right->right)) {
                    pNode = R_L_Rotation(pNode);
                } else {
                    pNode = L_Rotation(pNode);
                }
            }
        } else {
            pNode->value = value;
        }

        // 更新二叉树的高度
        pNode->height = max(getHeight(pNode->left), getHeight(pNode->right)) + 1;
        return pNode;
    }

    TreeNode<K, V> *minimum(TreeNode<K, V> *pNode) {
        if (pNode->left == NULL) {
            return pNode;
        }
        return minimum(pNode->left);
    }

    TreeNode<K, V> *removeNode(TreeNode<K, V> *pNode, K key) {
        // 递归没有写到底的情况
        if (pNode == NULL) {
            return NULL;
        }
        if (pNode->key > key) {
            pNode->left = removeNode(pNode->left, key);
            if (getHeight(pNode->right) - getHeight(pNode->left) == 2) {
                // 调整
                if (getHeight(pNode->right->left) > getHeight(pNode->right->right)) {
                    pNode = R_L_Rotation(pNode);
                } else {
                    pNode = L_Rotation(pNode);
                }
            }
        } else if (pNode->key < key) {
            pNode->right = removeNode(pNode->right, key);

            if (getHeight(pNode->left) - getHeight(pNode->right) == 2) {
                // 调整 , 不能简简单单的就做一次右旋
                if (getHeight(pNode->left->right) > getHeight(pNode->left->left)) {
                    pNode = L_R_Rotation(pNode);
                } else {
                    pNode = R_Rotation(pNode);
                }
            }

        } else {// 相等
            count--;
            if (pNode->left == NULL && pNode->right == NULL) {
                delete pNode;
                return NULL;
            } else if (pNode->left == NULL) {
                TreeNode<K, V> *right = pNode->right;
                delete (pNode);
                return right;
            } else if (pNode->right == NULL) {
                TreeNode<K, V> *left = pNode->left;
                delete (pNode);
                return left;
            } else {
                // 左右两子树都不为空
                if (getHeight(pNode->left) > getHeight(pNode->right)) {
                    // 去左边找一个来代替 （最大值）
                    TreeNode<K, V> *max = maximum(pNode->left);
                    TreeNode<K, V> *successor = new TreeNode<K, V>(max);
                    // 保证移除的子节点的高度都有更新
                    successor->left = removeNode(pNode->left, max->key);
                    count++;
                    successor->right = pNode->right;
                    // 更新当前后继的高度
                    delete (pNode);
                    pNode = successor;
                } else {
                    // 去右边找一个来代替 （最小值）
                    TreeNode<K, V> *min = minimum(pNode->right);
                    TreeNode<K, V> *successor = new TreeNode<K, V>(min);
                    // 保证移除的子节点的高度都有更新
                    successor->right = removeNode(pNode->right, min->key);
                    count++;
                    successor->left = pNode->left;
                    // 更新当前后继的高度
                    delete (pNode);
                    pNode = successor;
                }
            }
        }
        pNode->height = max(getHeight(pNode->left), getHeight(pNode->right)) + 1;
        return pNode;
    }

    TreeNode<K, V> *deleteMax(TreeNode<K, V> *pNode) {
        if (pNode->right == NULL) {
            TreeNode<K, V> *left = pNode->left;
            delete (pNode);
            count--;
            return left;
        }
        pNode->right = deleteMax(pNode->right);
        return pNode;
    }

    // 查找当前树的最大值 （最小值怎么找？）
    TreeNode<K, V> *maximum(TreeNode<K, V> *pNode) {
        // 不断的往右边找，直到找到右子树为空节点
        if (pNode->right == NULL) {
            return pNode;
        }
        return maximum(pNode->right);
    }

    void inOrderTraverse(TreeNode<K, V> *pNode, void (*pFunction)(K, V)) {
        if (pNode == NULL) {
            return;
        }
        inOrderTraverse(pNode->left, pFunction);
        pFunction(pNode->key, pNode->value);
        inOrderTraverse(pNode->right, pFunction);
    }
};


#endif //NDK_DAY44_BST_H
