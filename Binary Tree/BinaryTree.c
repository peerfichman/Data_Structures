#include <stdio.h>

/*Item_type held by node is defined by customer for example we use simple int*/
typedef struct Item_type
{
    int key;

} Item_type;

/*Compariosn function for int (defined by customer): LT (less then) GT (greater then)*/

int LT(int a, int b) { return a < b; }
int GT(int a, int b) { return a > b; }

/*Definition of tree node*/
typedef struct node_tag
{
    Item_type info;
    struct node_tag *left;
    struct node_tag *right;
} Node_type;

/*Insert: insert newnode in a tree starting at root. */
Node_type *Insert(Node_type *root, Node_type *newnode)
{
    if (root == NULL)
    {
        root = newnode;
        root->left = root->right = NULL;
    }
    else if (LT(newnode->info.key, root->info.key))
        root->left = Insert(root->left, newnode);
    else if (GT(newnode->info.key, root->info.key))
        root->right = Insert(root->right, newnode);
    else
        Error("Duplicate key in a binary tree");
    return root;
}

/*Delete: delete node p, reattach left and right subtrees. */
void Delete(Node_type **p)
{
    Node_type *q;
    if (*p == NULL) /* used to find place for left subtree */
        Error("Cannot delete empty node");
    else if ((*p)->right == NULL)
    {
        q = *p;
        *p = (*p)->left;
        free(q);
    }
    else if ((*p)->left == NULL)
    {
        q = *p;
        *p = (*p)->right;
        free(q);
    }
    else /*neither subtree is empty */
    {
        for (q = (*p)->right; q->left; q = q->left)
            ;
        q->left = (*p)->left;
        q = *p;
        *p = (*p)->right;
        free(q);
    }
}

/*Preorder: visit each node of the tree in preorder. */
void Preorder(Node_type *root)
{
    if (root)
    {
        Visit(root);
        Preorder(root->left);
        Preorder(root->right);
    }
} /*Inorder: visit each node of the tree in inorder. */
void Inorder(Node_type *root)
{
    if (root)
    {
        Inorder(root->left);
        Visit(root);
        Inorder(root->right);
    }
} /*Postorder: visit each node of the tree in postorder. */
void Postorder(Node_type *root)
{
    if (root)
    {
        Postorder(root->left);
        Postorder(root->right);
        Visit(root);
    }
}

/* TreeSearch: search for target starting at node p. */
Node_type *TreeSearch(Node_type *p, int target)
{
    if (p)
        if (LT(target, p->info.key))
            p = TreeSearch(p->left, target);
        else if (GT(target, p->info.key))
            p = TreeSearch(p->right, target);
    return p;
}

/*InorderOutputToList: visit each node of the tree in inorder and output content to list. */
void InorderOutputToList(Node_type *root, Item_type *list, int *i_ptr)
{
    if (root)
    {
        InorderOutputToList(root->left, list, i_ptr);
        list[*i_ptr] = root->info;
        (*i_ptr)++;
        InorderOutputToList(root->right, list, i_ptr);
    }
}

/*TreeSort:  sorting a list using a search tree. */
void TreeSort(Item_type *list, int n)
{
    Node_type *p, *root;
    int i = 0;
    root = NULL;
    while (i < n)
    {
        p = MakeTreeNode(list[i]);
        root = Insert(root, p);
        i++;
    }
    i = 0;
    InorderOutputToList(root, list, &i);
}