#include <iostream>

using namespace std;

#define maxValue 30000

struct activityTime  //�ṹ�����͵�˵���붨��ֿ��� ����
{
int sTime;	
int fTime;   
};

int resultNum = 0;

	/*
		����Ϊ��activityTime times[]�ʱ�� activityTime result[]��� int arrNum�ܻ�� int i��ʼ, int j����
	*/
void recursive_activity_selector(activityTime times[], activityTime result[], int arrNum, int i, int j);//�ݹ�����
int greedy_activity_selector(activityTime times[], activityTime result[], int arrNum);//̰���㷨

int main()
{
	int numNum;
	//�����ĸ���
	cout << "������������(Ϊʵ������)��" << endl;
	cin >> numNum;
	numNum += 2;
	activityTime *arr = NULL;
	try
	{
		arr = new activityTime[numNum];//ʹ��new��������
		for (int i = 0; i < numNum; i++)
		{
			arr[i].sTime = -1;
			arr[i].fTime = -1;
		}
	}
	catch (exception e)
	{
		cout << "��������ʧ�ܡ�" << endl;
	}

	activityTime *result = NULL;
	try
	{
		result = new activityTime[numNum];//ʹ��new��������
		for (int i = 0; i < numNum; i++)
		{
			result[i].sTime = -1;
			result[i].fTime = -1;
		}
	}
	catch (exception e)
	{
		cout << "��������ʧ�ܡ�" << endl;
	}

	//��������
	cout << "������ÿ����Ŀ�ʼ�ͽ���ʱ�䣺" << endl;
	for (int i = 0; i < numNum; i++)
	{
		if (i == 0)
		{
			arr[i].sTime = 0;
			arr[i].fTime = 0;
		}
		else if (i == numNum-1)
		{
			arr[i].sTime = maxValue;
			arr[i].fTime = maxValue;
			cout << "���������" << endl;
		}
		else
		{
			cout << "��ʼ�����ʱ�䣺";
			cin >> arr[i].sTime >> arr[i].fTime;
		}
		
	}

	//̰���㷨���

	/*for (int i = 0; i < greedy_activity_selector(arr, result, numNum); i++)
	{
		cout << "s:" << result[i].sTime << "f:" << result[i].fTime << endl;
	}*/

	//�ݹ����
	recursive_activity_selector(arr, result, numNum, 0, numNum+1);

	for (int i = numNum-1; i >= 0; i--)
	{//&& result[i].sTime != maxValue
		if (result[i].sTime != -1 && result[i].sTime != maxValue)
		{
			cout << "s:" << result[i].sTime << "f:" << result[i].fTime << endl;
		}
	}

	delete []result;
	delete []arr;
}


void recursive_activity_selector(activityTime times[],activityTime result[], int arrNum, int i, int j)
{
	int m = i + 1;
	while (m < j && times[m].sTime < times[i].fTime)
	{
		m = m + 1;
	}
	if (m < j)
	{
		recursive_activity_selector(times, result, arrNum-1, m, j);
		for (int i = 0; i < arrNum; i++)
		{
			if (result[i].sTime == -1)
			{
				result[i].sTime = times[m].sTime;
				result[i].fTime = times[m].fTime;
			}
		}	
	}
}

int greedy_activity_selector(activityTime times[], activityTime result[], int arrNum)
{
	int m, i = 1;
	int resultNum = 0;
	result[resultNum].sTime = times[1].sTime;
	result[resultNum].fTime = times[1].fTime;
	for (m = 2; m < arrNum; m++)
	{
		if (times[m].sTime >= times[i].fTime)
		{
			resultNum++;
			result[resultNum].sTime = times[m].sTime;
			result[resultNum].fTime = times[m].fTime;
			i = m;
		}
	}
	return resultNum;
}
