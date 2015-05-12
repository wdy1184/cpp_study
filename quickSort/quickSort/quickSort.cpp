#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "CreatIntNum.h"
using namespace std;

int randomized_select(int arr[], int p, int r, int i);//��iС��

void quicksort(int arr[], int p,   int r);//��������
int partition(int arr[], int p, int r);//�����黮��

void randomized_quicksort(int arr[], int p, int r);//�������������汾
int randomized_partition(int arr[], int p, int r);//�������������

void exchange(int arr[], int i, int j);//���������е�����Ԫ��
int random(int i, int j);//����i--j�е�һ�������

int main()
{
	long numNum;
	int numTh = -1;//�ڼ�С��
	//�������ֵĸ���
	cout << "������Ҫ�������ֵ�������" << endl;
	cin >> numNum;

	do
	{
		cout << "������Ҫȡ�ڼ�С������" << endl;
		cin >> numTh;
	} while (numTh <= 0 && numTh > numNum);



	//�������鲢���浽�ļ���
	CreatIntNum creatNum(numNum, "num.txt");
	creatNum.genrand(); 

	int *arr = NULL;
	try
	{
		arr = new int[numNum];//ʹ��new��������
	}
	catch (exception e)
	{
		cout << "��������ʧ�ܡ�" << endl;
	}
	

	//��ȡ�ļ��е����ֲ����浽������
	fstream f;
	f.open("num.txt");
	for (long i = 0; i < numNum; i++)
	{
		f >> arr[i];
	}
	f.close();//�ر�f

	//���򲢼�������ʱ��
	clock_t startQuick, endQuick;

	startQuick = clock();
	//��������
	//quicksort(arr, 0, 9);
	//randomized_quicksort(arr, 0, 9);
	int selectNum = randomized_select(arr, 0, numNum-1, numTh);
	endQuick = clock();
	cout << "��" << numTh << "С���ǣ�" << selectNum << endl;

	cout << "The search time is:"<< (double)(endQuick - startQuick)/CLK_TCK << endl;

	
	//ʹ�ÿ���������д�뵽��sortedNum.txt����
	randomized_quicksort(arr, 0, numNum-1);
	creatNum.writeNum(numNum, arr, "sortedNum.txt");

	delete []arr;
	return 0;
}

void quicksort(int arr[], int p,   int r)
{
	int q = 0;
	if (p < r)
	{
		q = partition(arr, p, r);
		quicksort(arr, p, q-1);
		quicksort(arr, q+1, r);
	}
}
int partition(int arr[], int p, int r)
{
	int x = arr[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			exchange(arr, i, j);
		}
	}
	exchange(arr, i+1, r);
	return i+1;
}

void exchange(int arr[], int i, int j)
{
	int temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}


void randomized_quicksort(int arr[], int p, int r)
{
	int q = 0;

	if (p < r)
	{
		q = randomized_partition(arr, p, r);
		randomized_quicksort(arr, p, q-1);
		randomized_quicksort(arr, q+1, r);
	}
}

int randomized_partition(int arr[], int p, int r)
{
	int i = random(p, r);
	exchange(arr, r, i);
	return partition(arr, p, r);
}

int random(int i, int j)
{
	srand( (unsigned int)time(0) );

	int randIntNum = 0;

	randIntNum = rand()%(j-i+1) + i;
	return randIntNum;
}


int randomized_select(int arr[], int p, int r, int i)
{
	int q, k;
	if (p == r)
	{
		return arr[p];
	}
	q = randomized_partition(arr, p, r);
	k = q - p + 1;
	if (i == k)
	{
		return arr[q];
	}
	else if(i < k)
	{
		return randomized_select(arr, p, q-1, i);
	}
	else
	{
		return randomized_select(arr, q+1, r, i-k);
	}
}