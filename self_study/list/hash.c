#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10

typedef struct cell {
    int key;
    int data;
    struct cell *next;
}CELL;

CELL *table[BUCKET_SIZE];

int keyequal(int key1, int key2){
    return key1 == key2 ? 1:0;
}

int hash(int key) {
    return key % BUCKET_SIZE;
}

// ハッシュ表の初期化
void init(void) {
    int i;
    for (i = 0; i < BUCKET_SIZE; i++){
        table[i] = NULL;
    }
}

// ハッシュ表の探索

int *find(int key) {
    CELL *p;

    for (p = table[hash(key)]; p != NULL; p = p -> next) {
        if (keyequal(key, p->key)){
            return &p->data;
        }
    }
}

// ハッシュ表にデータを挿入
int insert(int key, int data) {
    CELL *p;
    int h;

    if (find(key) != NULL)
    return 0;

    if((p=(CELL*)malloc(sizeof(CELL))) == NULL){
        fprintf(stderr, "*Out of memory\n");
        exit(2);
    }
    h = hash(key);
    p -> key = key;
    p -> data = data;
    p -> next = table[h];
    table[h] = p;
    return 1;
}

// ハッシュ表からデータを削除

int delete(int key) {
    int h;
    CELL *p, *q;

    h = hash(key);
    if (table[h] == NULL)
    return 0;

    if (keyequal(key, table[h] -> key)) {
        p = table[h];
        table[h] = p -> next;
        free(p);
        return 1;
    }

    for (q = table[h], p = q->next; p != NULL; q = p, p = p -> next) {
        if (keyequal(key, p->key)) {
            q -> next = p -> next;
            free(p);
            return 1;
        }
    }
    return 0;
}



int main() {
    init();

    insert(2,20);
    insert(12,22);
    insert(3,30);
    insert(13,33);
    insert(5,50);
    insert(8,80);

    printf("Key:3, Data: %d\n", *find(3));


    return 0;
}



