#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

//rewind 让文件指针的位置回到文件的起始位置

int main()
{
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL)
	{
		perror(pf);
		return 1;
	}

	//读文件
	int ch = fgetc(pf);
	printf("%c\n", ch);
	fseek(pf, -4, SEEK_END);
	printf("%d\n", ftell(pf));



	fclose(pf);
	pf = NULL;
	return 0;
}