#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	FILE* pf = fopen("test.txt", "wb");
	if (pf == NULL)
	{
		perror(pf);
		return 1;
	}

	int ch = fgetc(pf);
	printf("%c", pf);


	fseek(pf, 4, SEEK_CUR);

	ch = fgetc(pf);
	printf("%c", pf);
	fclose(pf);
	pf =NULL;
	return 0;
}