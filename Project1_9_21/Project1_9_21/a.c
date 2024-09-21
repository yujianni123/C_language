#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

char* GetMemory(void)
{
	char p[] = "Hello World";
	return p;
}

void Test(void)
{
	char* str = NULL;
	str = GetMemory();
	printf(str);
}

int main()
{
	Test();
	return 0;
}