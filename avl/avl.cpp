#include "avl.h"


int max(int a, int b){
    return a > b? a:b;
}

// Khởi tạo rỗng
void initTree(NODE*& pRoot) {
	pRoot->left = NULL;
	pRoot->right = NULL;
	pRoot->key = NULL;
	pRoot->height = 0;
	pRoot = NULL;
}

// Tạo node
NODE* createNode(int data) {
	NODE* node = new NODE;
	node->key = data;
	node->left = node->right = NULL;
	node->height = 1;
	return node;
}

// Tìm chiều cao của cây
int height(NODE* pRoot) {
	if (pRoot == NULL)
		return 0;
	return pRoot->height;
}

// Xoay phải
NODE* rotateRight(NODE* pRoot) {
	NODE* x = pRoot->left;
	NODE* y = x->right;
	x->right = pRoot;
	pRoot->left = y;
	pRoot->height = max(height(pRoot->left), height(pRoot->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

// Xoay trái
NODE* rotateLeft(NODE* pRoot) {
	NODE* y = pRoot->right;
	NODE* x = y->left;
	y->left = pRoot;
	pRoot->right = x;
	pRoot->height = max(height(pRoot->left), height(pRoot->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

// tìm hệ số cân bằng
int getBalanceFactor(NODE* pRoot) {
	if (pRoot == NULL)
		return 0;
	return height(pRoot->left) - height(pRoot->right);
}

// Thêm một Node vào cây
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	if (x < pRoot->key)
		Insert(pRoot->left, x);
	else if (x > pRoot->key)
		Insert(pRoot->right, x);
	else
		return;

	pRoot->height = max(height(pRoot->left), height(pRoot->right)) + 1;
	int balance = getBalanceFactor(pRoot);
	if (balance > 1 && x < pRoot->left->key)
		pRoot = rotateRight(pRoot);
	if (balance <-1 && x > pRoot->right->key)
		pRoot = rotateLeft(pRoot);
	if (balance > 1 && x > pRoot->left->key) {
		pRoot->left = rotateLeft(pRoot->left);
		pRoot = rotateRight(pRoot);
	}
	if (balance < -1 && x < pRoot->right->key) {
		pRoot->right = rotateRight(pRoot->right);
		pRoot = rotateLeft(pRoot);
	}
}

// Tìm kiếm 1 Node
NODE* Search(NODE* pRoot, int x) {
	if (pRoot == NULL || pRoot->key == x)
		return pRoot;
	if (pRoot->key > x)
		return Search(pRoot->left, x);
	else
		return Search(pRoot->right, x);
}

// Tìm phần tử thế mạng
void findMinValue(NODE*& X, NODE*& Y) {
	if (Y->left != NULL)
		findMinValue(X, Y->left);
	else {
		X->key = Y->key;
		X = Y;
		Y = Y->right;
	}
}

// Xóa 1 Node ra khỏi cây
void Remove(NODE*& pRoot, int x) {
	if (pRoot == NULL)
		return;
	if (x < pRoot->key)
		Remove(pRoot->left, x);
	else if (x > pRoot->key)
		Remove(pRoot->right, x);
	else {
		NODE* temp = pRoot;
		if (pRoot->right == NULL) {
			pRoot = pRoot->left;
		}
		else if (pRoot->left == NULL) {
			pRoot = pRoot->right;
		}
		else {
			findMinValue(temp, pRoot->right);
		}
		delete temp;
	}
	if (pRoot == NULL)
		return;
	pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
	int balance = getBalanceFactor(pRoot);
	if (balance > 1 && getBalanceFactor(pRoot->left) >= 0)
		pRoot = rotateRight(pRoot);
	if (balance > 1 && getBalanceFactor(pRoot->left) < 0) {
		pRoot->left = rotateLeft(pRoot->left);
		pRoot = rotateRight(pRoot);
	}
	if (balance < -1 && getBalanceFactor(pRoot->right) <= 0)
		pRoot = rotateLeft(pRoot);
	if (balance < -1 && getBalanceFactor(pRoot->right) > 0) {
		pRoot->right = rotateRight(pRoot->right);
		pRoot = rotateLeft(pRoot);
	}
}

// Duyệt trước
void NLR(NODE* pRoot) {
	if (pRoot != NULL) {
		cout << "Key: " << pRoot->key << " Height: " << pRoot->height << endl;
		NLR(pRoot->left);
		NLR(pRoot->right);
	}
}

// Duyệt giữa
void LNR(NODE* pRoot) {
	if (pRoot != NULL) {
		LNR(pRoot->left);
		cout << "Key: " << pRoot->key << " Height: " << pRoot->height << endl;
		LNR(pRoot->right);
	}
}

// Duyệt sau
void LRN(NODE* pRoot) {
	if (pRoot != NULL) {
		LRN(pRoot->left);
		LRN(pRoot->right);
		cout << "Key: " << pRoot->key << " Height: " << pRoot->height << endl;
	}
}

// Duyệt theo mức
void LevelOrder(NODE* pRoot) {
	if (pRoot != NULL) {
		queue <NODE*> q;
		q.push(pRoot);
		while (!q.empty()) {
			NODE* cur = q.front();
			q.pop();
			cout << "Key: " << cur->key << " Height: " << cur->height << endl;
			if (cur->left != NULL)
				q.push(cur->left);
			if (cur->right != NULL)
				q.push(cur->right);
		}
	}
}

// Tìm giá trị max
void findMaxValue(NODE* pRoot, int& Max) {
	if (pRoot == NULL)
		return;
	if (pRoot->left != NULL)
		Max = (Max > pRoot->left->key) ? Max : pRoot->left->key;
	if (pRoot->right != NULL)
		Max = (Max > pRoot->right->key) ? Max : pRoot->right->key;
	Max = (Max > pRoot->key) ? Max : pRoot->key;
	findMaxValue(pRoot->left, Max);
	findMaxValue(pRoot->right, Max);
}

// Kiểm tra cây nhị phân tìm kiếm, nếu đúng trả về 0, nếu sai trả về 1
bool isBST(NODE* pRoot) {
	if (pRoot == NULL)
		return 0;
	bool left = isBST(pRoot->left);
	int max_Left, max_Right;
	if (pRoot->left != NULL && pRoot->right != NULL) {
		findMaxValue(pRoot->left, max_Left);
		findMaxValue(pRoot->right, max_Right);
		if (!(max_Left <pRoot->key && max_Right>pRoot->key))
			return 1;
	}
	else if (pRoot->left == NULL && pRoot->right != NULL) {
		findMaxValue(pRoot->right, max_Right);
		if (!(pRoot->key < max_Right))
			return 1;
	}
	else if (pRoot->left != NULL && pRoot->right == NULL) {
		findMaxValue(pRoot->left, max_Left);
		if (!(max_Left < pRoot->key))
			return 1;
	}
	bool right = isBST(pRoot->right);
	return left + right;
}

// Kiểm tra cây AVL
bool isAVL(NODE* pRoot) {
	if (!isBST(pRoot)) {
		int banlance = getBalanceFactor(pRoot);
		if (banlance >= -1 && banlance <= 1)
			return 1;
	}
	return 0;
}