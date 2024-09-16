#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	int ch = 0;
	while (ch = getchar() != EOF)
	{
		printf("%d\n", ch);
		printf(putchar(ch));
	}
	return 0;
}