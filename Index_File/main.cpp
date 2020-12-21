#include<iostream>

#include"File.h"

using namespace std;

int main()
{
	while (1)
	{
		cout << "-------------------" << endl;
		cout << "选择执行的操作" << endl;
		cout << "1 添加一个文件记录" << endl;
		cout << "2 打印主文件记录" << endl;
		cout << "3 手动创建索引文件" << endl;
		cout << "4 打印索引文件记录" << endl;
		cout << "5 清空文件" << endl;
		cout << "6 查找职工号" << endl;
		cout << "7 通过职位查找领导关系" << endl;
		cout << "8 通过职称分块查找" << endl;
		cout << "其他 退出" << endl;
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