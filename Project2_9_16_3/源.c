#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	int m = 3 + 5;
	int n = m - 2;

	printf("%d\n", m);
	printf("%d\n", n);

	int num = 5;
	printf("%d\n", num * num);

	printf("%d\n", 6 / 3);
	printf("%d\n", 6 / 4);//1
	printf("%f\n", 6 / 4.0);//1
	printf("%f\n", 6.0 / 4);//1
	printf("%f\n", 6.0 / 4.0);//1



	// / ���ŵ����˶���������ʱ�򣬼�������������������������֮�����~
	//%f ��ר��������ӡ�������� - float,С�����Ĭ���Ǵ�ӡ6λ
	//%lf ��ӡdouble���͵ĸ�������

	return 0;
}