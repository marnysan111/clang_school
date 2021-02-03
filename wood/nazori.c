#include <stdio.h>

typedef struct Node {
    struct Node *left, *right;
    char label;
} Node;

void preorder(Node *p);
void inorder(Node *p);
void postorder(Node *p);

int main(void) {
    Node n1, n2, n3, n4;

    n1.label = 'a';
    n1.left = &n2;
    n1.right = &n4;

    n2.label = 'b';
    n2.left = &n3;
    n2.right = NULL;

    n3.label = 'c';
    n3.left = NULL;
    n3.right = NULL;

    n4.label = 'd';
    n4.left = NULL;
    n4.right = NULL;

    preorder(&n1);
    inorder(&n1);
    postorder(&n1);
    return 0;
}

void preorder(Node *p) {
    if (p == NULL)
        return;
    printf("preorder: %c\n", p->label);
    preorder(p->left);
    preorder(p->right);
}

void inorder(Node *p) {
    if (p == NULL)
        return;
    inorder(p->left);
    printf("inorder: %c\n", p->label);
    inorder(p->right);
}

void postorder(Node *p) {
    if (p == NULL)
        return;
    postorder(p->left);
    postorder(p->right);
    printf("postorder: %c\n", p->label);
}













