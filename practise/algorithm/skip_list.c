/**
 * 参考自 https://github.com/AndreMouche/algorithms_study/blob/master/data_structure/skiplist.cpp ，https://www.epaperpress.com/sortsearch/txt/skl.txt
 * 踩坑如下：insert方法中 update变量初始化问题，不同于java声明变量后变量初始赋值为NULL，而是随机值，当取址时就会出错。谨记！！！
 *
 * 另外复习下结构体初始化方式：
 *      1.recType value = (recType){key};
 *       or recType value = {key};
 *      2.recType value; value.key = key;
 *      乱序时
 *      3.recType value = {stuff:key}
 */
#include <stdio.h>
#include <stdlib.h>

/* implementation dependent declarations */
typedef enum {
    STATUS_OK,
    STATUS_MEM_EXHAUSTED,
    STATUS_DUPLICATE_KEY,
    STATUS_KEY_NOT_FOUND
} statusEnum;

typedef int keyType;
typedef struct {
    int stuff;
} recType;

#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

#define MAX_LEVEL 15

typedef struct nodeTag{
    keyType key;
    recType rec;
    struct nodeTag *forward[];
} nodeType;

typedef struct {
    nodeType *header;           /* list Header */
    int listLevel;              /* current level of list */
} skipList;

static int randomLevel() {
    int k = 1;
    while(rand()%2) {
        k++;
    }
    k = (k < MAX_LEVEL) ? k : MAX_LEVEL;
    return k;
}

nodeType *creatNode(int level, keyType key, recType value) {
    nodeType *newNode = (nodeType *) malloc(sizeof(nodeType) + level * sizeof(nodeType *));

    newNode->key = key;
    newNode->rec = value;
    for (int i = 0; i < level; i++) {
        newNode->forward[i] = NULL;
    }
    return newNode;
}

statusEnum insert(skipList * list,keyType key,recType value){
    // check exists
    int level = list->listLevel;
    nodeType *x = list->header;
    nodeType *update[MAX_LEVEL];
    for (int i = level; i >= 0; i--) {
        // trick mark by gao
        while (x->forward[i] != NULL && compLT(x->forward[i]->key, key))
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[0];
    if (x != NULL && compEQ(x->key, key))
        return STATUS_DUPLICATE_KEY;
    /* bug,case update[i] has not been inited .will case Segmentation fault
     for(int i = 0 ; i < MAX_LEVEL; i ++ ){
        if (update[i] != NULL && update[i]->forward[i] != NULL && compEQ(update[i]->forward[i]->key, key)) {
            return STATUS_DUPLICATE_KEY;
        }
    }*/
    int newLevel = randomLevel();
    nodeType *newNode = creatNode(newLevel, key, value);
    // bug fix,
    if (newLevel > list->listLevel) {
        for (int i = list->listLevel; i < newLevel; ++i) {
            //bug fix,并不赋值为NULL，方便后面的for循环避免NULL判断
            update[i] = list->header;
//            update[i] = NULL;
        }
        list->listLevel = newLevel;
    }
    for(int i = 0 ; i < newLevel; i ++ ) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    return STATUS_OK;
}

recType * search(skipList * list,keyType key){
    // bad implements
    /*
     // 特殊情况的特殊处理，最好不要上来就处理。应该先记住，尽可能在通用代码中包含特殊情况，如果包含不了再特殊处理。
     if (list->listLevel == 0)
        return NULL;
    int level = list->listLevel;
    nodeType * header= list->header;
    for (int i = level - 1; i >= 0; i--) {
        while (header->forward[i] != NULL && compLT(header->forward[i]->key, key)) {
            header = header->forward[i];
        }

    }
    if (header == NULL || !compEQ(header->forward[0]->key, key)) {
        return NULL;
    }
    return header->forward[0];*/

    //good implements
    nodeType *header, *q = NULL;
    header = list->header;
    int level = list->listLevel;
    for (int i = level; i >= 0; i--) {
        while (header->forward[i] != NULL && compLT(header->forward[i]->key, key)) {
            header = header->forward[i];
        }
        // here!!
        if (header->forward[i]!=NULL && compEQ(header->forward[i]->key, key)) {
            return header->forward[i];
        }
    }
    return NULL;
}


statusEnum delete(skipList * list,keyType key) {
    nodeType *p = list->header,*q = NULL;
    int level = list->listLevel;
    for (int i = level; i >= 0; i--) {
        while (p->forward[i] != NULL && compLT(p->forward[i]->key, key)) {
            p = p->forward[i];
        }
        if (p->forward[i] != NULL && compEQ(p->forward[i]->key, key)) {
            q = p->forward[i];
            p->forward[i] = q->forward[i];
        }
    }
    if (q == NULL) {
        return STATUS_KEY_NOT_FOUND;
    }
    free(q);
/*    while(list->header->forward[level-1]==NULL){
        level--;
        list->listLevel = level;
    }*/
    while (list->listLevel > 0 && list->header->forward[list->listLevel - 1] == NULL) {
        list->listLevel --;
    }
    return STATUS_OK;
}

void printSkipList(skipList *list){
    int level = list->listLevel;
    nodeType *p;
    for (int i = level; i >= 0; i--) {
        p = list->header;
        while(p->forward[i]!=NULL){
            printf("%d\t%d(%d)\t",i, p->forward[i]->key,p->forward[i]->rec.stuff);
            p = p->forward[i];
        }
        printf("\n");
    }
}


skipList * creatSkipList(){
    skipList *sl = (skipList *) malloc(sizeof(skipList));
    if (sl == NULL) {
        printf ("insufficient memory (creatSkipList)\n");
        exit(1);
    }
    // todo check key 0?
    nodeType *node = creatNode(MAX_LEVEL, 0, (recType){0});
    sl->header = node;
    sl->listLevel = 0;
}


void main(int argc, char *argv[]){
    skipList *list = creatSkipList();
    for (int i = 0; i < 1000; i++) {
        keyType key = rand()%10000;
        //recType value = {key};
        recType value = {stuff:key};

        statusEnum  status = insert(list, key, value);
        if (status) {
            printf("statusEnum:%d,key:%d\n", status, key);
        }
    }
    int n;
    scanf("%d", &n);
    recType *value = search(list, n);
    printf("search vlaue:%d\n", value->stuff);
    statusEnum delstatus = delete(list, n);
    printf("del status:%d", delstatus);
    printSkipList(list);
}
