#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
/*����������
ʹ�ö��ֲ��ң���һ������Ԫ���в���������(Ҫ�� �β������飬ʵ�ʲ��������� ����
���루input����
�������У���1�������ݼ��ϣ�����֮���ö��ŷָ�����2���Ǵ���������
�����output����
��������Ƿ�ɹ�����ʾ��Ϣ��*/

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
		mid = low + (high - low) / 2;//��ֹ���

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
	printf("���������������','���� �Լ�����Ҫ���ҵ�����: ");
	fgets(input, sizeof(input), stdin);
	char* token = strtok(input, ",");
	while (token != NULL) {
		arr[count++] = atoi(token);
		token = strtok(NULL, ",");
	}

	//��ȡ��������
	scanf("%d", &result);

	//���ֲ���
	result = find_num(arr, n, num);
	if (result = -1)
	{
		printf("%d�������У��±�Ϊ%d\n", num, result);
	}
	else {
		printf("%d����������\n", num);
	}

	return 0;
}