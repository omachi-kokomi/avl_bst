#include<iostream>
#include<queue>
using namespace std;

struct AVLNode{
    AVLNode* pLeft;
    AVLNode* pRight;
    int p, q;
};

int Area(int p, int q){
    return p * q;
}

int perimeter(int p, int q){
    return 2 * ( p + q);
}

int max(int a, int b){
    return a > b? a:b;
}

int compare(int p1, int q1, int p2, int q2){
    if (p1* q1 > p2 * q2) return 1;
    if (p1*q1 < p2 * q2) return -1;
    if (p1 + q1 < p2 + q2) return -1;
    if (p1+q1 > p2 + q2) return 1;
    return 0;
}



// Tạo node
AVLNode* createNode(int p, int q) {
	AVLNode* node = new AVLNode;
	node->p = p;
    node->q = q;
	node->pLeft = node->pRight = NULL;
	return node;
}

// Tìm chiều cao của cây
int height(AVLNode* pRoot) {
	if (pRoot == NULL)
		return 0;
	return 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
}

// Xoay phải
AVLNode* rotateRight(AVLNode* pRoot) {
	AVLNode* x = pRoot->pLeft;
	AVLNode* y = x->pRight;
	x->pRight = pRoot;
	pRoot->pLeft = y;
	return x;
}

// Xoay trái
AVLNode* rotateLeft(AVLNode* pRoot) {
	AVLNode* y = pRoot->pRight;
	AVLNode* x = y->pLeft;
	y->pLeft = pRoot;
	pRoot->pRight = x;
	return y;
}

// tìm hệ số cân bằng
int getBalanceFactor(AVLNode* pRoot) {
	if (pRoot == NULL)
		return 0;
	return height(pRoot->pLeft) - height(pRoot->pRight);
}



// Thêm một Node vào cây
void Insert(AVLNode*& pRoot, int p, int q) {
	if (pRoot == NULL) {
		pRoot = createNode(p, q);
		return;
	}
	if (compare(p, q, pRoot->p, pRoot->q)  < 0)
		Insert(pRoot->pLeft, p, q);
	else if (compare(p, q, pRoot->p, pRoot->q)  > 0)
		Insert(pRoot->pRight, p, q);
	else return;

	int balance = getBalanceFactor(pRoot);
	if (balance > 1 && compare(p, q, pRoot->pLeft->p, pRoot->pLeft->q) < 0)
		pRoot = rotateRight(pRoot);
	if (balance <-1 && compare(p, q, pRoot->pRight->p, pRoot->pRight->q) > 0)
		pRoot = rotateLeft(pRoot);
	if (balance > 1 && compare(p, q, pRoot->pLeft->p, pRoot->pLeft->q) > 0) {
		pRoot->pLeft = rotateLeft(pRoot->pLeft);
		pRoot = rotateRight(pRoot);
	}
	if (balance < -1 && compare(p, q, pRoot->pRight->p, pRoot->pRight->q) < 0) {
		pRoot->pRight = rotateRight(pRoot->pRight);
		pRoot = rotateLeft(pRoot);
	}
}

// Tìm kiếm 1 Node
AVLNode* Search(AVLNode* pRoot, int p, int q) {
	if (pRoot == NULL || (p == pRoot->p && q == pRoot->q))
		return pRoot;
	if (compare(p, q, pRoot->p, pRoot->q) < 0)
		return Search(pRoot->pLeft, p, q);
	else
		return Search(pRoot->pRight, p, q);
}

// Tìm phần tử thế mạng
void findMinValue(AVLNode*& X, AVLNode*& Y) {
	if (Y->pLeft != NULL)
		findMinValue(X, Y->pLeft);
	else {
		X->p = Y->p;
		X->q = Y->q;
		X = Y;
		Y = Y->pRight;
	}
}

// Xóa 1 Node ra khỏi cây
void Remove(AVLNode*& pRoot, int p, int q) {
	if (pRoot == NULL)
		return;
	if (compare(p, q, pRoot->p, pRoot->q) < 0)
		Remove(pRoot->pLeft, p, q);
	else if (compare(p, q, pRoot->p, pRoot->q) > 0)
		Remove(pRoot->pRight, p, q);
	else {
		AVLNode* temp = pRoot;
		if (pRoot->pRight == NULL) {
			pRoot = pRoot->pLeft;
		}
		else if (pRoot->pLeft == NULL) {
			pRoot = pRoot->pRight;
		}
		else {
			findMinValue(temp, pRoot->pRight);
		}
		delete temp;
	}
	if (pRoot == NULL)
		return;
	int balance = getBalanceFactor(pRoot);
	if (balance > 1 && getBalanceFactor(pRoot->pLeft) >= 0)
		pRoot = rotateRight(pRoot);
	if (balance > 1 && getBalanceFactor(pRoot->pLeft) < 0) {
		pRoot->pLeft = rotateLeft(pRoot->pLeft);
		pRoot = rotateRight(pRoot);
	}
	if (balance < -1 && getBalanceFactor(pRoot->pRight) <= 0)
		pRoot = rotateLeft(pRoot);
	if (balance < -1 && getBalanceFactor(pRoot->pRight) > 0) {
		pRoot->pRight = rotateRight(pRoot->pRight);
		pRoot = rotateLeft(pRoot);
	}
}

// Duyệt theo mức
void LevelOrder(AVLNode* pRoot) {
	if (pRoot != NULL) {
		queue <AVLNode*> q;
		q.push(pRoot);
		while (!q.empty()) {
			AVLNode* cur = q.front();
			q.pop();
			cout << "Area: " << cur->p << ", " << cur->q << endl;
			if (cur->pLeft != NULL)
				q.push(cur->pLeft);
			if (cur->pRight != NULL)
				q.push(cur->pRight);
		}
	}
}

// Tìm giá trị max
void findMaxValue(AVLNode* pRoot, int& Max) {
	if (pRoot == NULL)
		return;
	if (pRoot->pLeft != NULL)
		Max = (Max > Area(pRoot->pLeft->p, pRoot->pLeft->q)) ? Max : Area(pRoot->pLeft->p, pRoot->pLeft->q);
	if (pRoot->pRight != NULL)
		Max = (Max > Area(pRoot->pRight->p, pRoot->pRight->q)) ? Max : Area(pRoot->pRight->p, pRoot->pRight->q);
	Max = (Max > Area(pRoot->p, pRoot->pLeft->q)) ? Max : Area(pRoot->p, pRoot->pLeft->q);
	findMaxValue(pRoot->pLeft, Max);
	findMaxValue(pRoot->pRight, Max);
}

AVLNode* createTree(vector<int>pList, vector<int>qList){
    AVLNode* root = NULL;
    for (int i = 0; i < pList.size(); i++)
        Insert(root, pList[i], qList[i]);
    return root;
}

int main(){
    vector<int> pList = {3, 2, 6, 4, 10, 4, 2};
    vector<int> qList = {5, 3, 2, 3, 3, 7, 9};
    AVLNode* root = createTree(pList, qList);
    LevelOrder(root);
    Remove(root, 6, 2);
    LevelOrder(root);
    return 0;
}