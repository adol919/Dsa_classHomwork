#include<iostream>

#include"File.h"

using namespace std;

int main()
{
	while (1)
	{
		cout << "-------------------" << endl;
		cout << "ѡ��ִ�еĲ���" << endl;
		cout << "1 ���һ���ļ���¼" << endl;
		cout << "2 ��ӡ���ļ���¼" << endl;
		cout << "3 �ֶ����������ļ�" << endl;
		cout << "4 ��ӡ�����ļ���¼" << endl;
		cout << "5 ����ļ�" << endl;
		cout << "6 ����ְ����" << endl;
		cout << "7 ͨ��ְλ�����쵼��ϵ" << endl;
		cout << "8 ͨ��ְ�Ʒֿ����" << endl;
		cout << "���� �˳�" << endl;
		cout << "-------------------" << endl;
		int n;
		cin >> n;

		if (n == 1)
		{
			InputMainFile();
		}
		else if (n==2)
		{
			OutPutMainFile();
		}
		else if (n == 3)
		{
			CreateIdxFile();
		}
		else if (n == 4)
		{
			OutPutIdxFile();
		}
		else if (n == 5)
		{
			DeleteAll();
		}
		else if (n == 6)
		{
			FindStaff_no();
		}
		else if (n == 7)
		{
			FindleadRealtionship();
		}
		else if (n == 8)
		{
			FindZhichengRealtionship();
		}
		else
		{
			break;
		}
	}
}