#include <iostream>

#pragma once

typedef enum BalanceFactor
{
    LH,
    EH,
    RH
} BalanceFactor;

class AVLtree
{
private:
    int data;
    BalanceFactor bf;
    AVLtree *left;
    AVLtree *right;

    AVLtree* RotateLeft();
    AVLtree* RotateRight();


public:
    AVLtree(const int &data);

    friend void printInOrder(const AVLtree* root) ;
    friend AVLtree *insert(AVLtree *root, const int &newNodeData, bool &taller);
    friend AVLtree *remove(AVLtree *root, const int &NodeDataToRemove, bool &shorter);
    friend AVLtree* LeftBalance(AVLtree* root, bool& taller);
    friend AVLtree* RightBalance(AVLtree* root, bool& taller);
    friend AVLtree* LeftBalanceD(AVLtree* root, bool& shorter);
    friend AVLtree* RightBalanceD(AVLtree* root, bool& shorter);
};

