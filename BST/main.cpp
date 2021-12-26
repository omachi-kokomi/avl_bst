#include<iostream>
#include"bst.h"

int main(){
    int a[12] = {25, 20, 36, 10, 22, 30, 40, 5, 12, 28, 38, 48};
    int n = 12;
    NODE* root = createTree(a, 12);
    NODE* value = Search(root, 30);
    NODE* value2 = Search(root, 39);
    if (value2 == NULL) cout << "Not found 39";
    else cout << "Found 39";
    cout << endl;
    if (value == NULL) cout << "Not found 30";
    else cout << "Found 30";
    cout << endl;
    cout << "height Node of 22: " << heightNode(root, 22) << endl;
    cout << "Level of 30: " << Level(root, value)<< endl;
    cout << "countLeaf: " << countLeaf(root)<< endl;
    cout << "countless 30: " << countLess(root, 30) << endl;
    cout <<"countGreater 20: " << countGreater(root, 20) << endl;
    cout << isFullBST(root);
    return 0;
}