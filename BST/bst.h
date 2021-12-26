#include<iostream>
#include<queue>
using namespace std;

struct NODE{
    int key;
    NODE* left;
    NODE* right;
};

NODE* createNode(int data);
void Insert(NODE* &pRoot, int x);
void NLR(NODE* pRoot);
void LNR(NODE* pRoot);
void LRN(NODE* pRoot);
void LevelOrder(NODE* pRoot);
int Height(NODE* pRoot);
int countNode(NODE* pRoot);
int sumNode(NODE* pRoot);
NODE* Search(NODE* pRoot, int x);
void Remove(NODE* &pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE* &pRoot);
int heightNode(NODE* pRoot, int value);
int Level(NODE* pRoot, NODE* p);
int countLeaf(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);