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



	// / 除号的两端都是整数的时候，计算的是整数除法，结果是整除之后的商~
	//%f 是专门用来打印浮点数的 - float,小数点后默认是打印6位
	//%lf 打印double类型的浮点数的

	return 0;
}