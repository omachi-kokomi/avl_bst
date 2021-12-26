#include "bst.h"

int max(int a, int b){
    return a > b? a: b;
}

NODE* createNode(int data){
    NODE* node = new NODE;
    node->key = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void Insert(NODE* &pRoot, int x){
    if (pRoot == NULL){
        pRoot = createNode(x);
        return;
    }
    if (x > pRoot->key)
        Insert(pRoot->right, x);
    else if (x < pRoot->key) Insert(pRoot->left, x);
    else return; 
}

void NLR(NODE* pRoot){
    if(pRoot == NULL) return;
    cout << pRoot->key << " ";
    NLR(pRoot->left);
    NLR(pRoot->right);
}

void LNR(NODE* pRoot){
    if(pRoot == NULL) return;
    LNR(pRoot->left);
    cout << pRoot->key << " ";
    LNR(pRoot->right);
}

void LRN(NODE* pRoot){
    if(pRoot == NULL) return;
    LRN(pRoot->left);
    LRN(pRoot->right);
    cout << pRoot->key << " ";
}

void LevelOrder(NODE* pRoot){
    if (pRoot != NULL) {
		queue <NODE*> q;
		q.push(pRoot);
		while (!q.empty()) {
			NODE* cur = q.front();
			q.pop();
			cout << cur->key << " ";
			if (cur->left != NULL)
				q.push(cur->left);
			if (cur->right != NULL)
				q.push(cur->right);
		}
	}
}

int Height(NODE* pRoot){
    if (pRoot == 0) return 0;
    return max(Height(pRoot->right), Height(pRoot->left)) + 1;
}

int countNode(NODE* pRoot){
    if (pRoot == 0) return 0;
    return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}

int sumNode(NODE* pRoot){
    if (pRoot == 0) return 0;
    return pRoot->key + sumNode(pRoot->left) + sumNode(pRoot->right);
}

NODE* Search(NODE* pRoot, int x){
    if (pRoot == NULL) return NULL;
    if (pRoot->key == x) return pRoot;
    if (pRoot->key > x) return Search(pRoot->left, x);
    else return Search(pRoot->right, x);
}

NODE* minValueNode(NODE* node)
{
    NODE* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* Given a binary search tree and a key, this function
deletes the key and returns the new root */
void Remove(NODE* &pRoot, int key)
{
    // base case
    if (pRoot == NULL)
        return ;
 
    // If the key to be deleted is
    // smaller than the pRoot's
    // key, then it lies in left subtree
    if (key < pRoot->key)
        Remove(pRoot->left, key);
 
    // If the key to be deleted is
    // greater than the pRoot's
    // key, then it lies in right subtree
    else if (key > pRoot->key)
        Remove(pRoot->right, key);
 
    // if key is same as pRoot's key, then This is the NODE
    // to be deleted
    else {
        // NODE has no child
        if (pRoot->left==NULL && pRoot->right==NULL)
        {   
            delete pRoot;
            pRoot = NULL;
            return;
        }
        // NODE with only one child or no child
        else if (pRoot->left == NULL) {
            NODE* temp = pRoot;
            pRoot = pRoot->right;
            delete temp;
            temp = NULL;
        }
        else if (pRoot->right == NULL) {
            NODE* temp = pRoot;
            pRoot = pRoot->left;
            delete temp;
            temp = NULL;
        }
 
        // NODE with two children: Get the inorder successor
        // (smallest in the right subtree)
        NODE* temp = minValueNode(pRoot->right);
 
        // Copy the inorder successor's content to this NODE
        pRoot->key = temp->key;
 
        // Delete the inorder successor
        Remove(pRoot->right, temp->key);
    }

}

NODE* createTree(int a[], int n){
    NODE* root = new NODE;
    root = NULL;
    for (int i = 0; i < n; i++)
        Insert(root, a[i]);
    return root;
}

void removeTree(NODE* &pRoot){
    if (pRoot == NULL) return;
    if (pRoot->right == NULL && pRoot->left == NULL){
        delete pRoot;
        return;
    }
    removeTree(pRoot->right);
    removeTree(pRoot->left);
}

int heightNode(NODE* pRoot, int value){
    if (pRoot == NULL) return -1;
    if (pRoot->key == value) return Height(pRoot);
    else if (pRoot->key > value) return heightNode(pRoot->left, value);
    else return heightNode(pRoot->right, value);
}

// tree level count from 1 2 3 (tree root would be level 1)
int Level(NODE* pRoot, NODE* p){
    if (pRoot == NULL) return -1e9;       // Node p isn't in tree
    if (pRoot == p) return 1;
    else if (pRoot->key < p->key) return 1 + Level(pRoot->right, p);
    else if (pRoot->key > p->key) return 1 + Level(pRoot->left, p);
}

int countLeaf(NODE* pRoot){
    if (pRoot == NULL) return 0;
    if (pRoot->left == NULL && pRoot->right == NULL)
        return 1;
    return countLeaf(pRoot->right) + countLeaf(pRoot->left);
}

int countLess(NODE* pRoot, int x){
    int count = 0;
    if (pRoot == NULL) return 0;
    else if (pRoot->key < x){
        count++;
        count += countLess(pRoot->left, x);
        count += countLess(pRoot->right, x);
    }
    else count += countLess(pRoot->left, x);
    return count;
}

int countGreater(NODE* pRoot, int x){
    int count = 0;
    if (pRoot == NULL) return 0;
    else if (pRoot->key > x){
        count++;
        count += countGreater(pRoot->left, x);
        count += countGreater(pRoot->right, x);
    }
    else count += countGreater(pRoot->right, x);
    return count;
}

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

bool isFullBST(NODE* pRoot){
    if (isBST(pRoot) == true) return false;
    if (pRoot->left == NULL && pRoot->right == NULL)
        return true;
    else if (pRoot->left && pRoot->right){
        return isFullBST(pRoot->left) && isFullBST(pRoot->left);
    }
    else return false;
}