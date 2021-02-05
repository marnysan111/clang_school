#include <stdio.h>
#include <stdlib.h>

typedef struct CELL {
    int key;
    int data;
    struct CELL *prev, *next;
}CELL;

CELL head, end;

int insert(int key, int data);
int delete(int key);

int main(void){
    CELL *p;

    head.next = &head;
    head.prev = &head;

    insert(1,5);
    insert(2,10);
    insert(3,15);
    insert(4,20);

    for (p=head.next; p!=&head; p=p->next)
        printf("Key:%d, Value:%d\n", p->key, p->data);

    delete(2);
    insert(5,25);

    for (p = head.next; p!=&head; p=p->next)
        printf("Key: %d, Value: %d\n", p->key, p->data);
    
    return 0;
}

/*
    右方向(next)にリストを伸ばす
*/

int insert(int key, int data) {
    CELL *x, *p;

    if ((x = (CELL*)malloc(sizeof(CELL))) == NULL)
        return -1;

    p = &head;
    
    // 終端を探す
    while(p->next != &head)
        p = p->next;
    
    x->key = key;
    x->data = data;

    x->prev = p;
    x->next = p->next;

    p->next->prev = x;
    p->next = x;

    return 0;
}

/*
    リストから該当するキーのCELLを削除する
*/

int delete(int key) {
    CELL *p;
    for(p = head.next; p!=&head; p=p->next) {
        if (p->key == key) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
        }
    }
    return 0;
}





