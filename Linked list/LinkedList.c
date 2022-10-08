#include <stdio.h>

/*Item_type held by node is defined by customer for example we use simple int*/
typedef struct Item_type
{
    int data;

} Item_type;

/*Definition of node in linked list */
typedef struct node_tag
{
    Item_type info;
    struct node_tag *next;
} Node_type;

/* MakeNode: make a new node and insert item. */
Node_type *MakeNode(Item_type item)
{
    Node_type *p;

    if ((p = (Node_type *)malloc(sizeof(Node_type))) == NULL)
        Error("Exhausted memory");
    else
    {
        p->info = item;
        p->next = NULL;
    }

    return p;
}

/* Traverse: traverse a list visiting one node at a time. */
void Traverse(Node_type *head, void (*Visit)(Node_type *))
{
    Node_type *p;
    for (p = head; p; p = p->next)
        (*Visit)(p);
}

/* InsertNode: insert node q after node p. */
void InsertNode(Node_type *p, Node_type *q)
{
    if (p == NULL || q == NULL)
        Error("At least one of the nodes p and q is nonexistent");
    else
    {
        q->next = p->next;
        p->next = q;
    }
}

/* InsertBetween: insert q between the nodes r and p. */
void InsertBetween(Node_type *q, Node_type **head, Node_type **r, Node_type *p)
{
    if (p == *head)
    {
        q->next = p;
        *r = *head = q; /* q is at te head of the list */
    }
    else
    {
        q->next = p;
        (*r)->next = q; /* q is after r and before p. */
        *r = q;
    }
}

/* Delete: delete node p from the list; r is in front of p. */
void Delete(Node_type *r, Node_type *p)
{
    if (r == NULL || p == NULL)
        Error("At least one of the nodes p and q is nonexistent");
    else if (r->next != p)
        Error("Nodes r and p not in sequence");
    else
        r->next = p->next;
}
