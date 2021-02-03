#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int data;
    struct NODE *left, *right;
} NODE;

NODE *search (int key);
NODE *insert (int key);
int delete(int key);

NODE *deletemin(NODE **p);

int keyequall(int a, int b);
int leylt (int a, int b);

void preorder(NODE *p);

NODE *root = NULL;

int keyequall(int a, int b) {
    if (a == b)
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

NODE *search(int key) {
    NODE *p;

    p = root;
    while (p != NULL) {
        if (keyequall(key, p->data))
            return p;
        else if (keylt(key, p->data))
            p=p->left;
        else
            p=p->right;
    }
    return NULL;
}

NODE *insert(int key) {
    NODE **p, *new;

    p = &root;
    while (*p != NULL) {
        if (keyequall(key, (*p)->data))
            return NULL;
        else if (keylt(key, (*p)->data))
            p=&(*p)->left;
        else
            p=&(*p)->right;
    }
    if ((new = (NODE*)malloc(sizeof(NODE))) == NULL) {
        printf("Out of memory\n");
        return NULL;
    }
    new -> left = NULL;
    new -> right = NULL;
    new -> data = key;
    *p = new;
    return new;
}

int delete(int key) {
    NODE **p, *x;

    p = &root;
    while (*p != NULL) {
        if (keyequall(key, (*p)->data)) {
        x = *p;
        if (x->left == NULL && x->right == NULL)
            *p = NULL;
        else if (x->left == NULL)
            *p = x->right;
        else {
            *p = deletemin(&x->right);
            (*p) -> right = x->right;
            (*p) -> left = x->left;
        }
        free(x);
        return 1;
    } else if (keylt(key, (*p)->data))
        p=&(*p)->left;
      else
        p=&(*p)->right;
    }
    return 0;
}

NODE *deletemin(NODE **p) {
    NODE *x;

    while ((*p)->left != NULL)
        p=&(*p)->left;
    x = *p;
    *p = (*p)->right;
    return x;
}

void preorder(NODE *p) {
    if (p==NULL)
        return ;
    printf("preorder: %d\n", p->data);
    preorder(p->left);
    preorder(p->right);
}

int main(void) {
    NODE *pt;
    insert(2);
    insert(1);
    insert(4);
    insert(3);
    pt = search(3);
    preorder(root);
    printf("main: %d\n", pt->data);
    delete(2);
    preorder(root);
    return 0;
}

