#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
//算法：
//猴子吃桃问题：猴子第一天摘下若干个桃子，当即吃了一半，还不过瘾，又多吃了一个。
//第二天早上又将第一天剩下的桃子吃掉一半，有多吃了一个。以后每天早上都吃了前一天剩下的一半零一个。
//到第 10 天早上想再吃时，发现只剩下一个桃子了。编写程序求猴子第一天摘了多少个桃子。
int main()
{
	int day, x1, x2;
	day = 9;
	x2 = 1;
	while (day >0)
	{
		x1 = (x2 + 1) * 2;
		x2 = x1;
		day--;
	}
	printf("总的桃子数为：%d", x2);
	return 0;
}