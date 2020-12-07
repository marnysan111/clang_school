#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 50

typedef struct CELL {
    int key;
    int data;
    struct CELL *next;
} CELL;
CELL *table[BUCKET_SIZE];

int keyequal(int key1,int key2){
    if (key1 == key2){
        return 1;
    } else
    {
        return 0;
    }
    
    //return key1 == key2?1:0;
}

int hash(int key){
    return key % BUCKET_SIZE;
}

// ハッシュ表の初期化
void init() {
    int i;

    for (i = 0; i < BUCKET_SIZE; i++){
        table[i] = NULL;
    }
}

// ハッシュ表を探索する
int *find(int key) {
    CELL *p;

    for (p = table[hash(key)]; p != NULL; p = p -> next) {
        if (keyequal(key, p -> key))
            return &p -> data;
    }
    return NULL;
}


// ハッシュ表にデータを挿入する
int insert (int key, int *data) {
    CELL *p;
    int h;
/*
    if (find(key) != NULL) {
        return 0;
    }
*/
    if ((p = malloc(sizeof(CELL))) == NULL) {
        fprintf(stderr, "put of memory\n");
        exit(2);
    }
    h = hash(key);
    p -> key = key;
    p -> data = *data;
    p -> next = table[h];
    table[h] = p;
    printf("%d,%d,%d,%d\n", p->key, p->data,p->next,table[h]);
    return 1;
}

// ハッシュ表からデータを削除する
int delete(int key){
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
    
    for (q = table[h], p = q -> next; p != NULL; q = p, p = p -> next) {
        if (keyequal(key, p->key)) {
            q -> next = p -> next;
            free(p);
            return 1;
        }
    }
    return 0;
}

int main(){
    init();
    int a = 100;
    int b = 200;
    insert(1,&a);
    insert(1, &b);


    /*
    insert(2,20);
    insert(13,35);
    insert(3,33);
    insert(5,50);

    delete(3);
*/
    printf("%d\n",table[1]->next->data);
    return 0;
}