#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

struct S
{
	char name[20];
	int age;
	int score;
};

int main()
{
	struct S s = { 0 };
	int* pf = ("test.txt", "r");
	if (pf == NULL)
	{
		perror(pf);
		return 1;
	}

	//�����ļ�
	fscanf(pf, "%s %d %f", s.name, &(s.age), &(s.score));

	printf("%s %d %f", s.name, s.age, s.score);

	//�ر��ļ�
	fclose(pf);
	pf = NULL;

	return 0;
}