#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 200

typedef struct people { // 联系人信息结构体类型
    char name[20];        // 名字
    char job[20];         // 职业
    char mobile_phone[20]; // 手机
    char email[40];       // Email
    char addr[100];       // 通讯地址
} Record;

typedef struct {  // 顺序表存储结构
    Record* elem;        // 动态分配空间的首地址
    int length;          // 线性表当前长度
    int listsize;        // 线性表最大长度
} SqList;

void PrintList(SqList* L);
int IniList(SqList* t);
int AddRecord(SqList* t, Record rec);
int FindRecord(SqList* L, char* name);

void PrintList(SqList* L) {
    printf("%d\n", L->length); // 输出通讯录中的联系人数量
    for (int i = 0; i < L->length; i++) {
        printf("%s %s %s %s %s\n", L->elem[i].name, L->elem[i].job, L->elem[i].mobile_phone, L->elem[i].email, L->elem[i].addr);
    }
}

int IniList(SqList* t) {
    t->elem = (Record*)malloc(MAX * sizeof(Record)); // 分配内存以存储Record结构体
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

int FindRecord(SqList* L, char* name) {
    for (int i = 0; i < L->length; i++) {
        if (strcmp(L->elem[i].name, name) == 0) {
            printf("%s %s %s %s %s\n", L->elem[i].name, L->elem[i].job, L->elem[i].mobile_phone, L->elem[i].email, L->elem[i].addr);
            return 1;
        }
    }
    return 0;
}

int main() {
    SqList L;
    IniList(&L);

    Record rec;
    // 读取通讯录数据
    while (1) {
        scanf("%19s %19s %19s %39s %99s", rec.name, rec.job, rec.mobile_phone, rec.email, rec.addr);
        if (strcmp(rec.name, "0") == 0 && strcmp(rec.job, "0") == 0 && strcmp(rec.mobile_phone, "0") == 0 && strcmp(rec.email, "0") == 0 && strcmp(rec.addr, "0") == 0) {
            break;
        }
        AddRecord(&L, rec);
    }

    // 输出通讯录
    PrintList(&L);

    // 读取待查找的姓名
    char searchName[20];
    scanf("%19s", searchName);

    // 查询并输出结果
    if (!FindRecord(&L, searchName)) {
        printf("no result!\n");
    }

    // 在程序结束前释放内存
    free(L.elem);
    return 0;
}