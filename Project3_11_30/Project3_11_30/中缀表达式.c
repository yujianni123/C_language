#define _CRT_SECURE_NO_WARNINGS 1

//用栈解决表达式求值问题。（提示，请采用链式存储结构）
//
//一、问题描擫
//从键盘输入任意中缀表达式字符串，读字符串，利用栈结构实现表达式求值。
//二、输入与输出
//输入：从键盘中缀表达式擳： 32＋5×（6－4）
//输出：计算结果42 
//问题描述 : 从键盘输入任意中缀表达式字符串，读字符串，利用栈结构实现表达式求值。
//
//输入要求：1行中缀表达式（从键盘输入中缀表达式，如： 32＋5×（6－4）# ），以#作为结束符
//
//输出要求：1行结果（输出计算结果，如：42 ）
//
//示例如下：
//32+5*(6-4)#
//42

#include <stdio.h>
#include <stdlib.h>
#define SUCCESS  10000
#define FAILURE  10001
#define TRUE     10002
#define FALSE    10003

typedef int ElemType;
struct node
{
    ElemType data;
    struct node* next;
};

typedef struct node Node;
struct stack
{
    Node* top;
    int count;
};

typedef struct stack Stack;
int StackInit(Stack** s);
int StackEmpty(Stack* s);
int push(Stack** s, ElemType e);
int GetTop(Stack* s);
int pop(Stack** s);
int StackClear(Stack** s);
int StackDestroy(Stack** s);

int StackInit(Stack** s)
{
    if (s == NULL)
    {
        return FAILURE;
    }
    (*s) = (Stack*)malloc(sizeof(Stack) * 1);
    if ((*s) == NULL)
    {
        return FAILURE;
    }
    (*s)->top = NULL;
    (*s)->count = 0;
    return SUCCESS;
}

int StackEmpty(Stack* s)
{
    if (s == NULL || s->top == NULL)
        return TRUE;
    else
        return FALSE;
}


int push(Stack** s, ElemType e)
{
    if (s == NULL || (*s) == NULL)
    {
        return FAILURE;
    }
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL)
    {
        return FAILURE;
    }

    p->data = e;
    p->next = (*s)->top;
    (*s)->top = p;
    (*s)->count++;
    return SUCCESS;
}


int GetTop(Stack* s)
{
   if (s == NULL || s->top == NULL) {
        return FAILURE;
    }
    return s->top->data;
}

int pop(Stack** s)
{
    if (s == NULL || *s == NULL)
    {
        return FAILURE;
    }
    Node* p = (*s)->top;
    char e = p->data;
    (*s)->top = p->next;
    free(p);
    (*s)->count--;
    return e;
}

int StackClear(Stack** s)
{
    if (s == NULL || *s == NULL)
    {
        return FAILURE;
    }
    Node* p = (*s)->top;

    while (p)
    {
       (*s)->top = p->next;
        free(p);
        p = (*s)->top;
        (*s)->count--;
    }
    return SUCCESS;
}

int StackDestroy(Stack** s)
{
    if (s == NULL || *s == NULL)
    {
        return FAILURE;
    }
    free(*s);
    (*s) = NULL;
   return SUCCESS;
}

int Priority(char ch)
{
    switch (ch)
    {
    case '(':
       return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}



int main()

{
    Stack* s_opt, * s_num=0;
    char opt[1024] = { 0 };
    int i = 0, num1 = 0, num2 = 0, temp = 0;
    if (StackInit(&s_opt) != SUCCESS || StackInit(&s_num) != SUCCESS)
    {
        printf("Init Failure!\n");
    }
    scanf("%s", opt);
    while (opt[i] != '\0' || StackEmpty(s_opt) != TRUE)
    {
        if (opt[i] >= '0' && opt[i] <= '9')
        {
            temp = temp * 10 + opt[i] - '0';
            i++;
            if (opt[i] > '9' || opt[i] < '0')
            {
                push(&s_num, temp);
                temp = 0;
           }
        }
        else
        {
            if (opt[i] == ')' && GetTop(s_opt) == '(')
            {
                pop(&s_opt);
                i++;
                continue;
            }
            if (StackEmpty(s_opt) == TRUE ||
                (Priority(opt[i]) > Priority(GetTop(s_opt)))
                || ((GetTop(s_opt)) == '(' && opt[i] != ')'))
            {
               push(&s_opt, opt[i]);
                i++;
                continue;
            }
            if ((opt[i] == '\0' && StackEmpty(s_opt) != TRUE)
                || (opt[i] == ')' && GetTop(s_opt) != '(') ||
                (Priority(opt[i]) <= Priority(GetTop(s_opt))))
            {
                switch (pop(&s_opt))
                {
                case '+':
                    num1 = pop(&s_num);
                    num2 = pop(&s_num);
                    push(&s_num, (num1 + num2));
                    break;
                case '-':
                    num1 = pop(&s_num);
                    num2 = pop(&s_num);
                    push(&s_num, (num2 - num1));
                    break;
                case '*':
                    num1 = pop(&s_num);
                    num2 = pop(&s_num);
                    push(&s_num, (num1 * num2));
                    break;
                case '/':
                    num1 = pop(&s_num);
                    num2 = pop(&s_num);
                   push(&s_num, (num2 / num1));
                    break;
                }
            }
        }
    }
    printf("%d\n", GetTop(s_num));
    return 0;
}




