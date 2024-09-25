#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
/*问题描述：
使用二分查找，在一组有序元素中查找数据项(要求： 形参是数组，实际参是数组名 ）。
输入（input）：
输入两行，第1行是数据集合，数据之间用逗号分隔；第2行是待查找数据
输出（output）：
输出查找是否成功的提示信息。*/

//int input(int arr[], int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d", arr[i]);
//	}
//	printf("\n");
//}

int find_num(int arr[],int n,int key)
{
	int low=0,high=n-1,mid=0;
	while (low <= high)
	{
		mid = low + (high - low) / 2;//防止溢出

		if (key == arr[mid])
		{
			return mid;
		}else if (arr[mid] < key){
			low = mid + 1;
		}else {
			high = mid - 1;
		}
	}
	return -1;
}

int main()
{
	int arr[] = {0};
	char input=0;
	int n = sizeof(arr) / sizeof(arr[0]);
	int num=0,result,count=0;
	printf("请输入五个数据用','隔开 以及输入要查找的数字: ");
	fgets(input, sizeof(input), stdin);
	char* token = strtok(input, ",");
	while (token != NULL) {
		arr[count++] = atoi(token);
		token = strtok(NULL, ",");
	}

	//读取查找数据
	scanf("%d", &result);

	//二分查找
	result = find_num(arr, n, num);
	if (result = -1)
	{
		printf("%d在数组中，下标为%d\n", num, result);
	}
	else {
		printf("%d不在数组中\n", num);
	}

	return 0;
}