#define _CRT_SECURE_NO_WARNINGS 1
/*
*********************************************************************************************
问题描述
输入n个朋友的信息，包括姓名、生日、电话号码，本题要求编写程序，按照年龄从大到小的顺序依次输出通讯录。
题目保证所有人的生日均不相同。
输入（input）:
输入第一行给出正整数n（<10）。随后n行，每行按照“姓名 生日 电话号码”的格式给出一位朋友的信息，其中“姓名”
是长度不超过10的英文字母组成的字符串，“生日”是yyyymmdd格式的日期，“电话号码”是不超过17位数字及+、-组成的字符串。
输出（output）:
按照年龄从大到小输出朋友的信息，格式同输出。
********************************************************************************/

#include <stdio.h>
#include <string.h>
struct friends {
	char name[11];
	int birthday;
	char number[18];
};

int main() {
	int i, n, j;
	scanf("%d", &n);
	struct friends c[n];

	for (i = 0; i < n; i++) {
		scanf("%s %d %s", c[i].name, &c[i].birthday, c[i].number);
	}

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (c[j].birthday > c[j + 1].birthday) {
				struct friends temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
			}
		}
	}


	for (i = 0; i < n; i++) {
		printf("%s %d %s\n", c[i].name, c[i].birthday, c[i].number);
	}

	return 0;
}
