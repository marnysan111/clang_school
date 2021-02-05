#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define DELETED 1

#define BUCKET_SIZE 10

typedef struct BUCKET{
    int key;
    int data;
}BUCKET;

BUCKET table[BUCKET_SIZE];

int keyequal(int key1,int key2){
    return key1 == key2?1:0;
}

int rehash(int h){
    return (h+1)%BUCKET_SIZE;
}

void init(){
    int i;
    for(i =0;i < BUCKET_SIZE;i++){
        table[i].key = EMPTY;
    }
}

int hash(int key){
    return key % BUCKET_SIZE;
}

int *find(int key){
    int h,count;
    int k;

    count = 0;
    h = rehash(key);
    while((k = table[h].key) != EMPTY){
        if(k != DELETED && keyequal(key,k)){
            return &table[h].data;
        }
        if(++count > BUCKET_SIZE){
            return NULL;
        }
        h = rehash(h);
    }
    return NULL;
}
int insert(int key,int data){
    int h,count;
    int k;

    count = 0;

    h = hash(key);

    while((k = table[h].key) != EMPTY && k != DELETED){
        if(keyequal(key,k)){
            return 0;
        }
        if(++count > BUCKET_SIZE){
            fprintf(stderr,"hash table overflow\n");
            exit(1);
        }
        h = rehash(h);
    }
    table[h].key = key;
    table[h].data = data;
    return 1;
}
int delete(int key){
    int h,count;
    int k;

    count = 0;
    h = hash(key);
    while((k = table[h].key) != EMPTY){
        if(k != DELETED && keyequal(key,k)){
            table[h].key = DELETED;
            return 1;
        }
        if(++count > BUCKET_SIZE){
            return 0;
        }
        h = rehash(h);
    }
    return 0;
}
int main(){
    init();
    insert(12,200);
    insert(2,20);
    insert(13,35);
    insert(3,33);
    insert(5,50);

    delete(3);

    printf("%d\n",table[5].key);
    return 0;
}