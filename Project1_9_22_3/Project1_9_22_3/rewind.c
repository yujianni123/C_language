#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

//rewind ���ļ�ָ���λ�ûص��ļ�����ʼλ��

int main()
{
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL)
	{
		perror(pf);
		return 1;
	}

	//���ļ�
	int ch = fgetc(pf);
	printf("%c\n", ch);
	fseek(pf, -4, SEEK_END);
	printf("%d\n", ftell(pf));



	fclose(pf);
	pf = NULL;
	return 0;
}