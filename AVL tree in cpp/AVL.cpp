#include <iostream>
#include "AVL.h"

using namespace std;

AVLtree ::AVLtree(const int &data)
{
    this->data = data;
    bf = EH;
    left = right = nullptr;
}

void printInOrder(const AVLtree *root)
{
    if (root)
    {
        printInOrder(root->left);
        cout << "[" << root->data << "], ";
        printInOrder(root->right);
    }
}

AVLtree *AVLtree::RotateLeft()
{
    AVLtree *temp = this;
    if (!this)
        cout << "ERROR: Can't rotate an empty tree." << endl;
    else if (!this->right)
        cout << "ERROR: Can't rotate left." << endl;
    else
    {
        temp = right;
        right = temp->left;
        temp->left = this;
    }

    return temp;
}

AVLtree *AVLtree::RotateRight()
{
    AVLtree *temp = this;
    if (!this)
        cout << "ERROR: Can't rotate an empty tree." << endl;
    else if (!left)
        cout << "ERROR: Cantt rotate right." << endl;
    else
    {
        temp = left;
        left = temp->right;
        temp->right = this;
    }

    return temp;
}

AVLtree *LeftBalance(AVLtree *root, bool &taller)
{
    AVLtree *ls = root->left, *rs;

    switch (ls->bf)
    {
    case LH:
        root->bf = ls->bf = EH;
        root = root->RotateRight();
        taller = false;
        break;

    case EH:
        cout << "ERROR: Tree is already balance." << endl;
        break;

    case RH:
        rs = ls->right;
        switch (rs->bf)
        {
        case LH:
            root->bf = RH;
            rs->bf = EH;
            break;
        case EH:
            cout << "ERROR: Tree is already balanced." << endl;
            break;
        case RH:
            root->bf = EH;
            ls->bf = LH;
            break;
        }
        rs->bf = EH;
        root->left = ls->RotateLeft();
        root = root->RotateRight();
        taller = false;
        break;
    }

    return root;
}
AVLtree *RightBalance(AVLtree *root, bool &taller)
{
    AVLtree *rs = root->right, *ls;

    switch (rs->bf)
    {
    case RH:
        root->bf = rs->bf = EH;
        root = root->RotateLeft();
        taller = false;
        break;

    case EH:
        cout << "ERROR: Tree is already balanced." << endl;
        break;

    case LH:
        ls = rs->left;
        switch (ls->bf)
        {
        case RH:
            root->bf = LH;
            rs->bf = EH;
            break;
        case EH:
            cout << "ERROR: Tree is already balanced." << endl;
            break;
        case LH:
            root->bf = EH;
            rs->bf = RH;
            break;
        }
        ls->bf = EH;
        root->right = rs->RotateRight();
        root = root->RotateLeft();
        taller = false;
        break;
    }

    return root;
}

AVLtree *LeftBalanceD(AVLtree *root, bool &shorter)
{
    AVLtree *ls = root->left, *rs;

    switch (ls->bf)
    {
    case EH:
        root->bf = LH;
        ls->bf = RH;
        root = root->RotateRight();
        shorter = false;
        break;
    case LH:
        root->bf = ls->bf = EH;
        root = root->RotateRight();
        break;
    case RH:
        rs = ls->right;
        switch (rs->bf)
        {
        case RH:
            root->bf = EH;
            rs->bf = LH;
            break;
        case EH:
            root->bf = ls->bf = EH;
            break;
            case LH:
            root->bf = RH;
            ls->bf = EH;
        }
        rs->bf = EH;
        ls = ls->RotateLeft();
        root = root->RotateRight();
        break;
    }
    return root;
}
AVLtree *RightBalanceD(AVLtree *root, bool &shorter)
{
    AVLtree *rs = root->right, *ls;

    switch (rs->bf)
    {
    case EH:
        root->bf = RH;
        rs->bf = LH;
        root = root->RotateLeft();
        shorter = false;
        break;
    case RH:
        root->bf = rs->bf = EH;
        root = root->RotateLeft();
        break;
    case LH:
        ls = rs->left;
        switch (ls->bf)
        {
        case LH:
            root->bf = EH;
            rs->bf = RH;
            break;
        case EH:
            root->bf = rs->bf = EH;
            break;
            case RH:
            root->bf = LH;
            rs->bf = EH;
        }
        ls->bf = EH;
        rs = rs->RotateRight();
        root = root->RotateLeft();
        break;
    }
    return root;
}



AVLtree *remove(AVLtree *root, const int &NodeDataToRemove, bool &shorter)
{
    if (!root)
    {
        cout << "ERROR: Can't delete empty node." << endl;
        shorter = false;
        return root;
    }
    else if (NodeDataToRemove == root->data)
    {
        AVLtree* temp;
        if (!(root->right))
        {
            temp = root;
            root = root->left;
            shorter = true;
            delete temp;
        }
        else if (!(root->left))
        {
            temp = root;
            root = root->right;
            shorter = true;
            delete temp;
        }
        else
        {
            for (temp = root->right; temp->left; temp = temp->left)
                ;
            AVLtree* newNode = new AVLtree(temp->data);
            newNode->left = root->left;
            newNode->right = root->right;
            newNode->bf = root->bf;
            temp = root;
            root = newNode;
            delete temp;
            root = remove(root->right, root->data, shorter);
        }
    }
    else if (NodeDataToRemove < root->data)
    {
        root->left = remove(root->left, NodeDataToRemove, shorter);
        if (shorter)
        {
            switch (root->bf)
            {
            case EH:
                root->bf = RH;
                shorter = false;
                break;

            case LH:
                root->bf = EH;
                break;

            case RH:
                root = LeftBalanceD(root, shorter);
                break;
            }
        }
    }
    else if (NodeDataToRemove > root->data)
    {
        root->right = remove(root->right, NodeDataToRemove, shorter);
        if (shorter)
        {
            switch (root->bf)
            {
            case EH:
                root->bf = LH;
                shorter = false;
                break;

            case RH:
                root->bf = EH;
                break;

            case LH:
                root = RightBalanceD(root, shorter);
                break;
            }
        }
    }

    return root;
}

AVLtree *insert(AVLtree *root, const int &newNodeData, bool &taller)
{

    if (!root)
    {
        root = new AVLtree(newNodeData);
        taller = true;
    }
    else if (newNodeData == root->data)
    {
        cout << "ERROR: Duplicate Keys." << endl;
        return root;
    }
    else if (newNodeData < root->data)
    {
        root->left = insert(root->left, newNodeData, taller);
        if (taller)
        {
            switch (root->bf)
            {
            case LH:
                root = LeftBalance(root, taller);
                break;

            case EH:
                root->bf = LH;
                break;
            case RH:
                root->bf = EH;
                taller = false;
                break;
            }
        }
    }
    else
    {
        root->right = insert(root->right, newNodeData, taller);
        if (taller)
        {
            switch (root->bf)
            {
            case RH:
                root = RightBalance(root, taller);
                break;
            case EH:
                root->bf = RH;
                break;

            case LH:
                root->bf = EH;
                taller = false;
                break;
            }
        }
    }
    return root;
}
