#include <stdio.h>
#include <stdlib.h>

typedef struct CELL {
    int key;
    int data;
    struct CELL *next;
}CELL;

CELL head;

int insert(int key, int data);
int delete(int key);


int main(void) {
    CELL *p;
    head.next=NULL;

    insert(1,5);
    insert(2,10);
    insert(3,15);
    insert(4,20);

    for (p = head.next; p!=NULL; p = p->next){
        //printf("hello222\n");
        printf("Key: %d, Value: %d\n", p->key, p->data);   
    }

    delete(2);
    delete(4);
    insert(5,25);

    for (p = head.next; p != NULL; p = p->next)
        printf("Key: %d, Value: %d\n", p->key, p->data);

    return 0;
}


int insert(int key, int data) {
    CELL *x,*p;
    //printf("%d,%d\n",key,data);
    
    if ((x=(CELL *)malloc(sizeof(CELL))) == NULL)
        return -1;
    
    
    p = &head;

    while (p -> next != NULL)
        p = p->next;
    //printf("%d,%d\n",key,data);
    x->key = key;
    //printf("%d\n", x->key);
    x->data = data;
    //printf("%d\n", x->data);
    x->next = p->next;

    p->next = x;
    //printf("insert\n");
    //printf("%d,%d\n", x->key , x->data);
    return 0;
}

int delete(int key){
    CELL *p, *q;
    for (p = head.next, q = &head; p != NULL; p = p->next, q = q->next){
        if(p->key == key) {
            q->next=p->next;
            free(p);
        }
    }
    return 0;
}



