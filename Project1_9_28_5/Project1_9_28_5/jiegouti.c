#define _CRT_SECURE_NO_WARNINGS 1
/*
*********************************************************************************************
��������
����n�����ѵ���Ϣ���������������ա��绰���룬����Ҫ���д���򣬰�������Ӵ�С��˳���������ͨѶ¼��
��Ŀ��֤�����˵����վ�����ͬ��
���루input��:
�����һ�и���������n��<10�������n�У�ÿ�а��ա����� ���� �绰���롱�ĸ�ʽ����һλ���ѵ���Ϣ�����С�������
�ǳ��Ȳ�����10��Ӣ����ĸ��ɵ��ַ����������ա���yyyymmdd��ʽ�����ڣ����绰���롱�ǲ�����17λ���ּ�+��-��ɵ��ַ�����
�����output��:
��������Ӵ�С������ѵ���Ϣ����ʽͬ�����
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
