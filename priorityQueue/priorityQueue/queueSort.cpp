#include <iostream>
#include <fstream>
#include <time.h>
#include "MPriorityQueue.h"

using namespace std;


int menu();//ѡ��˵�

bool genrand(int num);//�������

int main()
{
	int num;//���ɵ�Ԫ�ظ���
	cout << "���������ɵ�Ԫ�ظ���(int)��" << endl;
	cin >> num;
	if ( !genrand(++num) )
	{
		exit(1);
	}

	MPNode<int> *arr = NULL;
	try
	{
		arr = new MPNode<int>[num];//ʹ��new��������
	}
	catch (exception e)
	{
		cout << "��������ʧ�ܡ�" << endl;
	}

	int temp;
	//��ȡ�ļ��е����ֲ����浽������
	fstream f;
	f.open("MPNode.txt");
	for (int i = 1; i < num; i++)
	{
		f >> temp;
		arr[i].setKey(temp);
		f >> temp;
		arr[i].setValue(temp);
	}
	f.close();//�ر�




	//����
	MPQueue<int> priorityQueue(num);

	for (int i = 1; i < num; i++)
	{
		priorityQueue.Insert(arr[i]);
	}

	MPNode<int> a;

	bool exit = false;
	for (;;) {
		int choice = menu();
		switch (choice) {
		case (1):
			a = priorityQueue.MaxValue();
			cout << "key:" << a.getKey() << "\tvalue:" << a.getValue() << endl;
			break;
		case (2):
			a = priorityQueue.ExtractMax();
			cout << "key:" << a.getKey() << "\tvalue:" << a.getValue() << endl;
			break;
		case (3):
			int x,key;
			cout << "��Ҫ���ӵڼ�λ��" << endl;
			cout << "���ӵ����٣�" << endl;
			cin >> x >> key;
			priorityQueue.IncreaseKey(x, key);
			break;
		case (4):
			priorityQueue.Output();
			cout << "���¶���MPNode.txt" << endl;
			for (int i = 1; i < num; i++)
			{
				priorityQueue.Insert(arr[i]);
			}
			break;
		case (5):
			continue;
			break;
		case (6):
			exit = true;
			break;
		default:
			cout << "������ѡ�� " << endl;
			break;
		} // end switch

		if (exit == true)
			break;
	} // end forever



	delete [] arr;

	return 0;
}




int menu() {
	int choice;
	cout << "********************" << endl << endl;
	cout << " **** ѡ���б� **** " << endl << endl;
	cout << "(1) ��ʾ������Ԫ�� " << endl;
	cout << "(2) ��ʾ������Ԫ�ز�ȥ�� " << endl;
	cout << "(3) ����keyֵ " << endl;
	cout << "(4) �������ļ� " << endl;
	cout << "(5) ������ʾ�б� " << endl;
	cout << "(6) �˳�: "<< endl << endl;
	cin >> choice;
	return choice;
}


bool genrand(int num)
{
	ofstream output;
	MPNode<int> *dat, *p;


	dat = (MPNode<int> *)malloc(num * sizeof(MPNode<int>));
	p = dat;

	if (dat == NULL)
	{
		cout << "malloc error, memory not enough!\n" << endl;
		exit(1);
	}

	srand( (unsigned int)time(0) );
	for (int i = 1; i < num; i++)
	{
		dat[i].setKey(rand());	// = rand();
	}
	for (int i = 1; i < num; i++)
	{
		dat[i].setValue(rand());	//�˴���֪���᲻���key�ص�
	}

	/* ���浽�ļ��� */
	output.open("MPNode.txt");
	if(!output.is_open())
	{
		std::cout << "can't open file " << "MPNode.txt" << "!\n" << std::endl;
		exit(2);
	}

	for (int j = 1; j < num; j++)
	{
		output << dat[j].getKey() << "\t" << dat[j].getValue() << endl;
	}

	free(dat);
	output.close();

	return true;
}