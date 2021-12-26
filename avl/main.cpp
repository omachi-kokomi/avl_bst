#include <iostream>
#include"avl.h"
using namespace std;

int main(){
    NODE* root;
    initTree(root);
    for (int i = 1; i <= 16; i++){
        if (i == 4 || i == 6 || i == 14) continue;
        Insert(root, i);
    }
    NLR(root);
    // for (int i = 1; i <= 15; i++){
    //     if (i == 4 || i == 6 || i == 14) continue;
    //     Remove(root, i);
    // }
    return 0;
}