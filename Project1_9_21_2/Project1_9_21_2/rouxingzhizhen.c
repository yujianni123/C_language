#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

struct S
{
	int n;
	int* arr;
};

int main()
{
	struct S* ps = (struct S*)malloc(sizeof(struct S));
	if (ps == NULL)
		return 1;

	ps->arr = (int*)malloc(5 * sizeof(int));
	if (ps->arr == NULL)
		return 1;
	//ʹ��
	ps->n = 100;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ps->arr[i] = i;
	}

	//���������С
	int*ptr=(int *)realloc(ps->arr,10*sizeof(int));
	if (ptr != NULL)
	{
		ps->arr = ptr;
	}

	//ʹ��
	ps->n = 100;
	//int i = 0;
	for (i = 0; i < 5; i++)
	{
		ps->arr[i] = i;
	}

	//�ͷ�
	free(ps);
	ps = NULL;
	return 0;
}