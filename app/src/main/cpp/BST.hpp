//
// Created by simonday on 2021/1/5.
//

#ifndef MY_APPLICATION_BST_HPP
#define MY_APPLICATION_BST_HPP


template<class K, class V>
struct TreeNode {
	TreeNode<K, V> *left = NULL;
	TreeNode<K, V> *right = NULL;
	K key;
	V value;

public:
	TreeNode(TreeNode<K, V> *pNode) {
		this->left = pNode->left;
		this->right = pNode->right;
		this->key = key;
		this->value = value;
	}

	TreeNode(K key, V value) {
		this->right = NULL;
		this->left = NULL;
		this->key = key;
		this->value = value;
	}
};

template<class K, class V>
class BST {
	TreeNode<K, V> *root = NULL;//根节点
	int count = 0;

public:
	BST() {
		root == NULL;
		count = 0;
	}

	~BST() {

	}

	int size() {
		return count;
	}

	//新增（修改）
	void put(K k, V v) {
		root = addNode(root, k, v);
	}

	//查
	V get(K k) {

	}

	//删
	void remove(K k) {
		root = removeNode(root, k);
	}

	bool contains(K k) {
		TreeNode<K, V> *node = root;
		while (node) {
			if (node->key == k) {
				return node->value;
			} else if (node->key > k) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return false;
	}


	/**
	 * 中序遍历
	 * @param fun
	 */
	void inOrderTraverse(void (*fun)(int, int)) {
		inOrderTraverse(root, fun);
	}

private:
	TreeNode<K, V> *addNode(TreeNode<K, V> *pNode, K k, V v) {

		if (pNode == NULL) {
			count++;
			return new TreeNode<K, V>(k, v);
		}

		if (pNode->key > k) {
			pNode->left = addNode(pNode->left, k, v);
		} else if (pNode->key < k) {
			pNode->right = addNode(pNode->right, k, v);
		} else {
			pNode->value = v;
		}

		return pNode;
	}

	TreeNode<K, V> *removeNode(TreeNode<K, V> *pNode, K key) {
		if (pNode->key > key) {
			pNode->left = removeNode(pNode->left, key);
		} else if (pNode->key < key) {
			pNode->right = removeNode(pNode->right, key);
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
				TreeNode<K, V> *successor = new TreeNode<K, V>(maximum(pNode->left));
				successor->left = deleteMax(pNode->left);
				count++;
				successor->right = pNode->right;
				delete (pNode);
				return successor;
			}
		}
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
		return maximum(pNode->left);
	}

	void inOrderTraverse(TreeNode<K, V> *pNode, void (*fun)(int, int)) {
		if (pNode == NULL) {
			return;
		}
		inOrderTraverse(pNode->left, fun);
		fun(pNode->key, pNode->value);
		inOrderTraverse(pNode->right, fun);
	}

};


#endif //MY_APPLICATION_BST_HPP
