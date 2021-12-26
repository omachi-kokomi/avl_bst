#include<iostream>
#include<queue>
using namespace std;

struct NODE{
    NODE* left;
    NODE* right;
    int key;
    int height;
};

void initTree(NODE*&  pRoot);
NODE* createNode(int data);
int height(NODE* pRoot);
NODE* rotateRight(NODE* pRoot);
NODE* rotateLeft(NODE* pRoot);
int getBalanceFactor(NODE* pRoot);
void Insert(NODE*& pRoot, int x);
NODE* Search(NODE* pRoot, int x);
void findMinValue(NODE*& X, NODE*& Y);
void Remove(NODE*& pRoot, int x);
void NLR(NODE* pRoot);
void LNR(NODE* pRoot);
void LRN(NODE* pRoot);
void LevelOrder(NODE* pRoot);
void findMaxValue(NODE* pRoot, int& Max);
bool isBST(NODE* pRoot);