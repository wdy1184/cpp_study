/*
	1.����30000��������
	2.�浽num.txt��
	3.��ȡnum.txt�еĶ�ȡ����
	4.��������
	5.�������(��ʾ����ʱ��)
*/
#include <iostream>
#include <fstream>
#include <time.h>
#include "CreatIntNum.h"
#include "outputArray.h"


using namespace std;
//��������
void InsertSort(int arr[], int numNum);
//�ϲ����� ����Ϊ�����飬��ʼ�㣬������
void MergeSort(int arr[], int startPoint, int endPoint);
//�ϲ� ����Ϊ�� ���飬��ʼ�㣬�м�㣬������
void Merge(int arr[], int startPoint, int middlePoint, int endPoint);

int main()
{
	long numNum;
	//�������ֵĸ���
	cout << "������Ҫ�������ֵ�������" << endl;
	cin >> numNum;

	//�������鲢���浽�ļ���
	CreatIntNum creatNum(numNum, "num.txt");
	creatNum.genrand();

	int *arr;
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

	//outputSortedArray.outArray(arr, numNum);




	/************************************************************************/
	/* ��������                                                                     
	/************************************************************************/
	//���򲢼�������ʱ��
	clock_t startInsert, endInsert;

	startInsert = clock();

	//����
	InsertSort(arr, numNum);

	endInsert = clock();
	creatNum.writeNum(numNum, arr, "insert.txt");
	cout << "The insert sort time is:"<< (double)(endInsert - startInsert)/CLK_TCK << endl;


	/************************************************************************/
	/* �鲢����                                                                     
	/************************************************************************/
	int *arrMerge;
	try
	{
		arrMerge = new int[numNum];//ʹ��new��������
	}
	catch (exception e)
	{
		cout << "��������ʧ�ܡ�" << endl;
	}

	fstream fin;
	fin.open("num.txt");

	//��ȡ�ļ��е����ֲ����浽������
	for (long i = 0; i < numNum; i++)
	{
		fin >> arrMerge[i];
	}
	fin.close();//�ر�fin

	//���򲢼�������ʱ��
	clock_t startMerge, endMerge;

	startMerge = clock();

	//����
	MergeSort(arrMerge, 0, numNum-1);

	endMerge = clock();

	creatNum.writeNum(numNum, arrMerge, "merge.txt");
	cout << "The merge sort time is:"<< (double)(endMerge - startMerge)/CLK_TCK << endl;

	
	//�ͷſռ�
	delete [] arr;
	delete [] arrMerge;
	return 0;
}

void InsertSort(int arr[], int numNum)   
{
	int key, i;
	for (int j = 1; j < numNum; j++)
	{
		key = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i] > key)
		{
			arr[i+1] = arr[i];
			i--;
		}
		arr[i+1] = key;
	}
}

void MergeSort(int arrMerge[], int startPoint, int endPoint)
{
	int middle;//�м��
	if (startPoint < endPoint)
	{
		middle = (startPoint+endPoint) / 2;
		MergeSort(arrMerge, startPoint, middle);
		MergeSort(arrMerge, middle+1, endPoint);
		Merge(arrMerge, startPoint, middle, endPoint);
	}
}

void Merge(int arrMerge[], int startPoint, int middlePoint, int endPoint)
{
	int n1, n2;//Ҫ�ϲ�����������
	int *L, *R;//Ҫ�ϲ�����������

	n1 = middlePoint - startPoint + 1;
	n2 = endPoint - middlePoint;

	try{
		//����������̬����
		L = new int[n1+1];
		R = new int[n2+1];
	}catch(exception e){
		cout << "��������ʧ��" << endl;
	}

	for (int i = 0; i < n1; i++)
	{
		//��startPoint + i��
		L[i] = arrMerge[startPoint + i];
	}

	for (int i = 0; i < n2; i++)
	{
		R[i] = arrMerge[middlePoint + i + 1];
	}

	L[n1] = 2147483647;
	R[n2] = 2147483647;

	int i,j;
	i = j = 0;
	for (int k = startPoint; k <= endPoint; k++)//��startPoint��ʼ��endPoint�������ܹ�������(endPoint-endPoint+1)��ѭ��
	{
		if (L[i] <= R[j])
		{
			arrMerge[k] = L[i];
			i++;
		}
		else
		{
			arrMerge[k] = R[j];
			j++;
		}
	}

	//�ͷſռ�
	delete[] L;
	delete[] R;
}