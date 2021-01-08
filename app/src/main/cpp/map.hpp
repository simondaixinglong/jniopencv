//
// Created by hcDarren on 2018/10/27.
//

#ifndef NDK_DAY47_MAP_H
#define NDK_DAY47_MAP_H

#include <queue>

using namespace std;

// 能用到的语法用一用
typedef bool rb_color;
#define black false // 黑色
#define red true //  红色

template<class K, class V>
class map {
private:
    struct TreeNode;
    int count;
    TreeNode *root;

public:
    map() : root(NULL) {
        count = 0;
    }

public:
    struct iterator;

    TreeNode *parent(TreeNode *pNode) {
        return pNode ? pNode->parent : NULL;
    }

    TreeNode *left(TreeNode *pNode) {
        return pNode ? pNode->left : NULL;
    }

    TreeNode *right(TreeNode *pNode) {
        return pNode ? pNode->right : NULL;
    }

    TreeNode *brother(TreeNode *pNode) {
        return left(parent(pNode)) == pNode ? right(parent(pNode)) : left(parent(pNode));
    }

    rb_color getColor(TreeNode *pNode) {
        return pNode ? pNode->color : black;
    }

    void setColor(TreeNode *pNode, rb_color color) {
        if (pNode) {
            pNode->color = color;
        }
    }

    TreeNode *L_Rotation(TreeNode *pNode) {
        // avl 左旋 , 多了一个父亲节点
        TreeNode *right = pNode->right;
        pNode->right = right->left;
        right->left = pNode;

        // 调整 pNode 父亲的儿子指向
        if (pNode->parent == NULL) {
            root = right;
        } else if (pNode->parent->left == pNode) {
            pNode->parent->left = right;
        } else {
            pNode->parent->right = right;
        }

        // 调整各大节点的父亲
        right->parent = pNode->parent;
        if (pNode->right) {
            pNode->right->parent = pNode;
        }
        pNode->parent = right;

        return right;
    }

    TreeNode *R_Rotation(TreeNode *pNode) {
        TreeNode *left = pNode->left;
        pNode->left = left->right;
        left->right = pNode;

        // 调整 pNode 父亲的儿子指向
        if (pNode->parent == NULL) {
            root = left;
        } else if (pNode->parent->left == pNode) {
            pNode->parent->left = left;
        } else {
            pNode->parent->right = left;
        }

        // 调整各大节点的父亲
        left->parent = pNode->parent;
        if (pNode->left) {
            pNode->left->parent = pNode;
        }
        pNode->parent = left;

        return left;
    }

    void solveDoubleRed(TreeNode *pNode) {
        while (pNode->parent && pNode->parent->color == red) { // 情况1
            if (getColor(brother(parent(pNode))) == red) { // 情况 2
                setColor(parent(pNode), black);
                setColor(brother(parent(pNode)), black);
                setColor(parent(parent(pNode)), red);
                pNode = parent(parent(pNode));
            } else { // 情况 3
                if (left(parent(parent(pNode))) == parent(pNode)) {
                    if (right(parent(pNode)) == pNode) { // 情况 3.1
                        pNode = parent(pNode);
                        L_Rotation(pNode);
                    }
                    // 情况 3.2  把我父亲这棵子树上的红色节点，逻动到我的叔叔的那棵树上
                    setColor(parent(pNode), black);
                    setColor(parent(parent(pNode)), red);
                    R_Rotation(parent(parent(pNode)));
                } else {
                    if (left(parent(pNode)) == pNode) { // 情况 3.1
                        pNode = parent(pNode);
                        R_Rotation(pNode);
                    }
                    // 情况 3.2  把我父亲这棵子树上的红色节点，逻动到我的叔叔的那棵树上
                    setColor(parent(pNode), black);
                    setColor(parent(parent(pNode)), red);
                    L_Rotation(parent(parent(pNode)));
                }
            }
        }

        root->color = black;
    }

    iterator insert(K key, V value) {
        // 插入算法
        if (root == NULL) {
            root = new TreeNode(NULL, NULL, NULL, key, value, black);
            count = 1;
            return iterator(root);
        }

        // 最好我们插入红色节点，它不会违反性质 5 ，但是有可能会违反性质 4
        TreeNode *node = root;
        TreeNode *parent = NULL;

        do {
            parent = node;
            if (key == node->key) {
                node->value = value;
                return iterator(node);
            } else if (key > node->key) {
                node = node->right;
            } else {
                node = node->left;
            }
        } while (node);
        TreeNode *new_node = new TreeNode(NULL, NULL, parent, key, value, red);

        if (key > parent->key) {
            parent->right = new_node;
        } else {
            parent->left = new_node;
        }

        solveDoubleRed(new_node);
        count++;
        return iterator(new_node);
    }

    TreeNode *findTree(K key) {
        TreeNode *node = root;
        while (node) {
            if (key == node->key) {
                return node;
            } else if (key > node->key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return NULL;
    }

    // 关键代码
    void solveLostBlack(TreeNode *pNode) {
        while (pNode != root && pNode->color == black) {
            if (left(parent(pNode)) == pNode) {// 当前节点是父亲节点的左节点
                TreeNode *sib = brother(pNode);
                if (getColor(sib) == red) { // 想办法把兄弟节点变成黑色
                    setColor(sib, black);
                    setColor(parent(pNode), red);
                    L_Rotation(parent(pNode));
                    sib = brother(pNode);
                }
                if (getColor(left(sib)) == black && getColor(right(sib)) == black) {
                    setColor(sib, red);
                    pNode = parent(pNode);
                } else {
                    // 情况 3
                    if (getColor(right(sib)) == black) {
                        setColor(sib,red);
                        setColor(left(sib),black);
                        R_Rotation(sib);
                        sib = brother(pNode);
                    }
                    // 情况 4
                    setColor(sib,getColor(parent(pNode)));
                    setColor(parent(pNode),black);
                    setColor(right(sib),black);
                    L_Rotation(parent(pNode));
                }
            } else {// 当前节点是父亲节点的右节点
                TreeNode *sib = brother(pNode);
                if (getColor(sib) == red) { // 想办法把兄弟节点变成黑色
                    setColor(sib, black);
                    setColor(parent(pNode), red);
                    R_Rotation(parent(pNode));
                    sib = brother(pNode);
                }

                if (getColor(left(sib)) == black && getColor(right(sib)) == black) {
                    setColor(sib, red);
                    pNode = parent(pNode);
                } else {
                    // 情况 3  远侄子是 黑
                    if (getColor(left(sib)) == black) {
                        setColor(sib,red);
                        setColor(right(sib),black);
                        L_Rotation(sib);
                        sib = brother(pNode);
                    }
                    // 情况 4
                    setColor(sib,getColor(parent(pNode)));
                    setColor(parent(pNode),black);
                    setColor(left(sib),black);
                    R_Rotation(parent(pNode));
                }
            }
        }
        // 当遇到一个红色节点，把红色节点染黑即可
        pNode->color = black;
    }

    bool remove(K key) {
        TreeNode *current = findTree(key);

        if (current == NULL) {
            return false;
        }

        if (current->left != NULL && current->right != NULL) {
            TreeNode *successor = current->successor();
            current->key = successor->key;
            current->value = successor->value;
            current = successor;
        }
        TreeNode *replace = current->left ? current->left : current->right;

        if (replace != NULL) {
            // 父亲  , current->parent 会不会有空的情况？
            if (current->parent->left == current) {
                current->parent->left = replace;
            } else {
                current->parent->right = replace;
            }

            replace->parent = current->parent;

            if (current->color == black) {
                solveLostBlack(replace);
            }

            delete (current);
        } else {
            // 为什么不先移除，是因为在修正的时候需要去获取叔叔和侄子节点来分情况判断
            if (current->color == black) {
                solveLostBlack(current);
            }
            // 再来移除
            if (current->parent) {
                if (current->parent->left == current) {
                    current->parent->left = NULL;
                } else {
                    current->parent->right = NULL;
                }
            }
            delete (current);
        }

        count--;
        return true;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    // 层序遍历
    void levelTraverse(void (*fun)(K, V, bool)) {
        if (root == NULL) {
            return;
        }
        TreeNode *node = root;
        queue<TreeNode *> nodes;
        nodes.push(node);
        while (!nodes.empty()) {
            node = nodes.front();
            fun(node->key, node->value, node->color);
            nodes.pop();

            if (node->left) {
                nodes.push(node->left);
            }

            if (node->right) {
                nodes.push(node->right);
            }
        }
    }
};

template<class K, class V>
struct map<K, V>::TreeNode {
public:
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    K key;
    V value;
    // 颜色
    rb_color color;
public:
    TreeNode(TreeNode *left, TreeNode *right, TreeNode *parent, K key, V value, rb_color color)
            :
            left(left), right(right), parent(parent), key(key), value(value), color(color) {}

    // 找到前驱
    TreeNode *precursor() {
        TreeNode *node = right;
        if (node->left) {
            node = node->left;
        }
        return node;
    }

    TreeNode *successor() {
        // 逻辑还是有问题？
        if (right) {
            TreeNode *successor = right;
            while (successor->left) {
                successor = successor->left;
            }
            return successor;
        } else {
            TreeNode *successor = this;
            while (successor->parent && successor->parent->right == successor) {
                successor = successor->parent;
            }
            return successor->parent;
        }
    }
};

template<class K, class V>
struct map<K, V>::iterator {
private:
    TreeNode *node;
public:
    iterator(TreeNode *node) : node(node) {}

    iterator &operator--() {// 找前驱
        node = node->precursor();
        return *this;
    }

    iterator &operator++() {// 找后继
        node = node->successor();
        return *this;
    }

    V operator*() {
        return node->value;
    }
};

#endif //NDK_DAY47_MAP_H
