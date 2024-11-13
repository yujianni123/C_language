#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 200

typedef struct people {
    char name[20];
    char job[20];
    char mobile_phone[20];
    char email[40];
    char addr[100];
} Record;

typedef struct {
    Record* elem;
    int length;
    int listsize;
} SqList;

void PrintList(SqList* L);
int IniList(SqList* t);
int AddRecord(SqList* t, Record rec);
int DeleteRecord(SqList* t, int position);

void PrintList(SqList* L) {
    for (int i = 0; i < L->length; i++) {
        printf("%s %s %s %s %s\n", L->elem[i].name, L->elem[i].job, L->elem[i].mobile_phone, L->elem[i].email, L->elem[i].addr);
    }
}

int IniList(SqList* t) {
    t->elem = (Record*)malloc(MAX * sizeof(Record));
    if (!t->elem) {
        printf("内存分配失败！\n");
        exit(0);
    }
    t->length = 0;
    t->listsize = MAX;
    return 0;
}

int AddRecord(SqList* t, Record rec) {
    if (t->length >= t->listsize) {
        printf("顺序表已满，无法添加新记录！\n");
        return -1;
    }
    t->elem[t->length] = rec;
    t->length++;
    return 0;
}

int DeleteRecord(SqList* t, int position) {
    if (position < 1 || position > t->length) {
       printf("illegal location!\n");
       return -1;
    }
    for (int i = position - 1; i < t->length - 1; i++) {
        t->elem[i] = t->elem[i + 1];
    }
    t->length--;
    return 0;
}

int main() {
    SqList L;
    IniList(&L);
    Record rec;
    while (1) {
        scanf("%19s %19s %19s %39s %99s", rec.name, rec.job, rec.mobile_phone, rec.email, rec.addr);
        if (strcmp(rec.name, "0") == 0 && strcmp(rec.job, "0") == 0 && strcmp(rec.mobile_phone, "0") == 0 && strcmp(rec.email, "0") == 0 && strcmp(rec.addr, "0") == 0) {
            break;
        }
        AddRecord(&L, rec);
    }
    printf("length is %d\n", L.length);
    printf("database is:\n");
    PrintList(&L);
    int position;
    scanf("%d", &position);
    if (DeleteRecord(&L, position) == -1) {
        // 如果位置不合法，不进行删除操作
    }
    else {
       // 如果删除成功，打印更新后的通讯
    }
   printf("after:\n");
    PrintList(&L);
    free(L.elem);
    return 0;
}

