#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
int main()
{
	//int* p = (int*)malloc(5 * sizeof(int));
	//if (p == NULL)
	//{
	//	perror("malloc");
	//	return 1;
	//}
	//return 0;


	int* p = (int*)calloc(5 ,sizeof(int));
	if (p == NULL)
	{
		perror("malloc");
		return 1;
	}
	return 0;
}