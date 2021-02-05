#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct NODE {
    int data, height;
    struct NODE *left, *right;
}NODE;

NODE *search(int key);
NODE *insert(NODE **node, int key);
NODE *leftRotate(NODE **y);
NODE *rightRotate(NODE **y);

int keyequal(int a, int b);
int keylt(int a, int b);
int height(NODE *p);
int getBalance(NODE *p);
int max(int a, int b);

NODE *root = NULL;

int keyequal(int a, int b) {
    if (a==b)
        return 1;
    else
        return 0;
}

int keylt(int a, int b) {
    if (a < b)
        return 1;
    else
        return 0;
}

int getBalance(NODE *p) {
    return (p == NULL) ? 0 : height(p->left) - height(p->right);
}

int height(NODE *p) {
    int left_height, right_height, tree_height;

    if (p == NULL)
        return 0;
    
    left_height = height(p->left);
    right_height = height(p->right);

    if (left_height > right_height)
        tree_height = left_height;
    else
        tree_height = right_height;

    return tree_height;
}

int max(int a, int b){
    return (a > b) ? a:b;
}

NODE *search(int key) {
    NODE *p;
    p = root;
    while (p != NULL) {
        if (keyequal(key, p->data))
            return p;
        else if (keylt(key, p->data))
            p = p->left;
        else
            p = p->right;
    }
    return NULL;
}

NODE *insert(NODE **node, int key) {
    NODE **p, *new;
    int balance;

    p=&(*node);
    if (*p == NULL) {
        if ((new=(NODE*)malloc(sizeof(NODE)))==NULL) {
            printf("Out of memmory\n");
            return NULL;
        }
        new->left = NULL;
        new->right = NULL;
        new->data = key;
        *node = new;
        return new;
    }
    else if (keylt(key, (*p)->data))
        (*p)->left = insert(&(*p)->left, key);
    else if (!keylt(key, (*p)->data))
        (*p)->right = insert(&(*p)->right, key);
    else
        return *node;

    (*node)->height = 1 + max(height((*node)->left), height((*node)->right));
    balance = getBalance(*node);

    if (balance > 1 && key < (*node)->left->data) {
        return rightRotate(&(*node));
    }

    if (balance > 1 && key > (*node)->left->data){
        (*node)->left = leftRotate(&(*node)->left);
        return rightRotate(&(*node));
    }

    return *node;
}

void preorder (NODE *p) {
    if (p==NULL)
        return;
    printf("%d\n", p->data);
    preorder(p->left);
    preorder(p->right);
}

void inorder(NODE *p) {
    if (p == NULL)
        return;
    inorder(p->left);
    printf("%d\n", p->data);
    inorder(p->right);
}

NODE *rightRotate(NODE **y) {
    NODE *x, *t;
    x = (*y) -> right;

    t = x->right;
    x->right = (*y);
    (*y)->left = t;
    (*y)->height=max(height((*y)->left), height((*y)->right)) + 1;
    x -> height = max(height(x->left), height(x->right)) + 1;

    return x;
}

NODE *leftRotate(NODE **y) {
    NODE *x = NULL;
    return x;
}

int main(void) {
    root = insert(&root, 5);
    root = insert(&root, 4);
    root = insert(&root, 3);
    root = insert(&root, 2);
    root = insert(&root, 1);

    inorder(root);
    printf("\n");

    preorder(root);

    return 0;
} 

