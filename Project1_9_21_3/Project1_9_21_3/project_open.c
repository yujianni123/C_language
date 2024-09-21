#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	FILE* pf = fopen("test.txt", "w");
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}

	//读文件


	//关闭文件
	fclose(pf);
	pf = NULL;

	return 0;
}