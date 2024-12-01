#define _CRT_SECURE_NO_WARNINGS 1

//问题描述：输入一个中缀算术表达揂, 将其转换为后缀表达式, 然后对后缀表达揂进行求值。运算符包括 + -*/ =, 参与运算的为小于10的自然数。
//输入要求：一组数据，每组数据一行，对应一个算术表达式
//输出要求：对每组数据输出2行, 第1行为中缀表达式对应的后缀式, 第2行为后缀式求值的结果。

//输入、输出样式：
//输入样式：
//9+(3-1)*3+1+2
//输出样式：
//931-3*+1+2+ 
// 18

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define maxsize 50
typedef struct
{
    float data[maxsize];
    int top;
}opstack;

typedef struct
{
    char data[maxsize];
    int top;
}stack;

void InitStack(stack* s);
int GetTop(stack s, char* e);
void Pop(stack* s, char* e);
void Push(stack* s, char e);
void TranslateExpress(char s1[], char s2[]);
int ComputeExpress(char s[]);
int StackEmpty(stack s);

int main()
{
    char a[maxsize], b[maxsize];
    int f;
    gets(a);
    TranslateExpress(a, b);
    printf("%s\n", b);
    f = ComputeExpress(b);
    printf("%d", f);
    return 0;
}

void InitStack(stack* s)
{
    s->top = 0;
}

int GetTop(stack s, char* e)
{
    if (s.top <= 0) return 0;
    else
    {
        *e = s.data[s.top - 1];
        return 1;
    }
}

void Pop(stack* s, char* e)
{
    if (s->top <= 0) printf("栈空!");
    else *e = s->data[--s->top];
}

void Push(stack* s, char e)
{
    if (s->top >= maxsize) printf("栈满!");
    else s->data[s->top++] = e;
}


int StackEmpty(stack s)
{
    if (s.top == 0) return 1;
    else return 0;
}

int ComputeExpress(char a[])
{
    opstack s;
    int i = 0, value;
    float x1, x2, result;
    s.top = -1;
    while (a[i] != '\0')
    {
        if (a[i] != ' ' && a[i] >= '0' && a[i] <= '9')
        {
            value = 0;
            value = a[i] - '0';
            i++;
            s.top++;
            s.data[s.top] = value;
        }
        else
        {
            switch (a[i])
            {
            case '+':
                x1 = s.data[s.top--];
                x2 = s.data[s.top--];
                result = x1 + x2;
                s.data[++s.top] = result;
                break;
            case '-':
                x1 = s.data[s.top--];
                x2 = s.data[s.top--];
                result = x2 - x1;
                s.data[++s.top] = result;
                break;
            case '*':
                x1 = s.data[s.top--];
                x2 = s.data[s.top--];
                result = x1 * x2;
                s.data[++s.top] = result;
                break;
            case '/':
                x1 = s.data[s.top--];
                x2 = s.data[s.top--];
                result = x2 / x1;
                s.data[++s.top] = result;
                break;
            case '^':
                x1 = s.data[s.top--];
                x2 = s.data[s.top--];
                result = pow(x2, x1);
                s.data[++s.top] = result;
                break;
            }
            i++;
        }
    }
    if (!s.top != -1)
    {
        result = s.data[s.top];
        s.top--;
        if (s.top == -1) return result;
        else
        {
            printf("表达式错误!");
            exit(-1);
        }
    }

}

void TranslateExpress(char str[], char exp[])
{
    stack s;
    char ch, e;
    int i = 0, j = 0;
    InitStack(&s);
    ch = str[i++];
    while (ch != '\0')
    {
        switch (ch)
        {
        case '(':
            Push(&s, ch);
            break;
        case ')':
            while (GetTop(s, &e) && e != '(')
            {
                Pop(&s, &e);
                exp[j++] = e;
            }
            Pop(&s, &e);
            break;
        case '+':
        case '-':
            while (!StackEmpty(s) && GetTop(s, &e) && e != '(')
            {
                Pop(&s, &e);
                exp[j++] = e;
            }
            Push(&s, ch);
            break;
        case '*':
        case '/':
            while (!StackEmpty(s) && GetTop(s, &e) && e == '/' || e == '*' || e == '^')
            {
                Pop(&s, &e);
                exp[j++] = e;
            }
            Push(&s, ch);
            break;
        case '^':
            while (!StackEmpty(s) && GetTop(s, &e) && e == '^')
            {
                Pop(&s, &e);
                exp[j++] = e;
            }
            Push(&s, ch);
            break;
        case ' ':
            break;
        default:
            while (ch >= '0' && ch <= '9')
            {
                exp[j++] = ch;
                ch = str[i++];
            }
            i--;
        }
        ch = str[i++];
    }
    while (!StackEmpty(s))
    {
        Pop(&s, &e);
        exp[j++] = e;
    }
    exp[j] = '\0';

}
