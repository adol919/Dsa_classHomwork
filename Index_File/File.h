#pragma once
#include<iostream>
#include"AVL.h"
#include"MultList.h"
using namespace std;

struct staff 
{
	char no[8];
	char name[8];
	char zhiwu[8];
	char zhicheng[8];
};

struct idxNode
{
	char no[8];
	int offest;
	idxNode()
	{
		strcpy_s(no, 8, "saf");
		offest = 0;
	}
	idxNode(char _no[], int n)
	{
		strcpy_s(no, 8, _no);
		offest = n;
	}
};

string idxTargetFile = ".\\No_idxFile.dat";//职工号索引文件地址
string zhiwu_idxTargetFile = ".\\zhiwu_idxFile.dat";//职务
string zhicheng_idxTargetFile = ".\\zhicheng_idxFile.dat";//职称
FILE* mfile;

FILE* idxFile;
string targetmfile = ".\\main.dat";//设定目标路径
//备用 文件路径 ".\\main2.dat"



void InputMainFile()//添加一条记录
{

	errno_t err;
	if (err = fopen_s(&mfile, targetmfile.c_str(), "ab+") != 0 || mfile == 0)
	{
		cout << "链接主文件失败" << endl;
		return;
	}

	cout << "请输入信息 职工号 名字  职位  职称" << endl;
	staff sta;
	cin >> sta.no >> sta.name >> sta.zhiwu >> sta.zhicheng;
	if (fwrite(&sta, sizeof(staff), 1, mfile) != 1)
	{
		cout << "写入文件失败" << endl;
		return;
	}

	//添加进入了主文件，当然也要改变索引文件
		//将三个索引表加载到内存中
	AVLTree tree;
	MultList zhiwuList;
	MultList zhichengList;


	idxNode Index;
	//读取二叉平衡树信息

	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "rb+") != 0 || idxFile == 0)
	{
		cout << "索引链接失败" << endl;
		return;
	}
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		if (strcmp(Index.no, "#") != 0)
		{
			tree.insert(Index.no, Index.offest);
		}
	}
	tree.insert(sta.no, tree.getNodeNum() + 1);



	//这之后应该重置指针位置，不然会从尾部写入
	rewind(idxFile);

	//读取完之后要再写入索引表
//只能通过队列层次遍历放入信息了
	Queue<Node*> que;
	Node* firstNode;
	que.push(tree.getRoot());
	int count = tree.getNodeNum();
	int _count = 0;//再加一个条件作为计数
	while (!que.Empty() && _count < count)
	{
		firstNode = que.front();
		strcpy_s(Index.no, 8, firstNode->key);
		Index.offest = firstNode->offest;
		//写入文件信息
		fwrite(&Index, sizeof(idxNode), 1, idxFile);
		if (strcmp(Index.no, "#") != 0)//不是#字符加1
		{
			_count++;
		}

		if (firstNode->leftchild)
		{
			que.push(firstNode->leftchild);
		}
		else
		{
			Node* newNode = new Node("#", 0);
			que.push(newNode);
		}

		if (firstNode->rightchild)
		{
			que.push(firstNode->rightchild);
		}
		else
		{
			Node* newNode = new Node("#", 0);
			que.push(newNode);
		}

		que.pop();
	}


	fclose(idxFile);

	//读取职务多重表信息

	if (err = fopen_s(&idxFile, zhiwu_idxTargetFile.c_str(), "rb+") != 0 || idxFile == 0)
	{
		cout << "索引链接失败" << endl;
		return;
	}
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		zhiwuList.insert(Index.no, Index.offest);
	}

	zhiwuList.insert(sta.zhiwu, zhiwuList.getNodeNum() + 1);
	rewind(idxFile);
	for (int i = 0; i < zhiwuList.getListSize(); i++)
	{
		strcpy_s(Index.no, zhiwuList.getKeyvalue(i));
		LinkList temp = zhiwuList.getLinkList(i);
		ListNode* ptr = temp.getHead();
		while (ptr->next != NULL)
		{
			Index.offest = ptr->next->offest;
			fwrite(&Index, sizeof(idxNode), 1, idxFile);
			ptr = ptr->next;
		}
	}

	fclose(idxFile);

	//读取职称多重表信息

	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "rb+") != 0 || idxFile == 0)
	{
		cout << "索引链接失败" << endl;
		return;
	}
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		zhichengList.insert(Index.no, Index.offest);
	}
	zhichengList.insert(sta.zhicheng, zhichengList.getNodeNum() + 1);
	rewind(idxFile);
	for (int i = 0; i < zhichengList.getListSize(); i++)
	{
		strcpy_s(Index.no, zhichengList.getKeyvalue(i));
		LinkList temp = zhichengList.getLinkList(i);
		ListNode* ptr = temp.getHead();
		while (ptr->next != NULL)
		{
			Index.offest = ptr->next->offest;
			fwrite(&Index, sizeof(idxNode), 1, idxFile);
			ptr = ptr->next;
		}
	}
	fclose(idxFile);


	fclose(mfile);
}

//打印主文件内容
void OutPutMainFile()
{
	errno_t  err;
	
	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "主文件链接失败" << endl;
		return;
	}

	staff sta;
	while (fread(&sta, sizeof(staff), 1, mfile) != NULL)
	{
		cout << "序号 " << sta.no << ' ';
		cout << "姓名 " << sta.name << ' ';
		cout << "职务 " << sta.zhiwu << ' ';
		cout << "职称 " << sta.zhicheng << ' ' << endl;
	}

	fclose(mfile);
}





void CreateIdxFile()
{
	
	
	//链接主文件
	errno_t err;
	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0||mfile==0)
	{
		cout << "主文件链接失败"<<endl;
		return;
	}

	//读取信息到二叉平衡树
	AVLTree tree;

	//读取信息到职务多重表
	MultList zhiwuList;

	//读取信息到职称多重表
	MultList zhichengList;

	staff sta;
	int count = 0;//标记有多少个记录
	int n = 0;
	while (fread(&sta, sizeof(staff), 1,mfile ) != NULL)
	{
		tree.insert(sta.no, ++n);
		zhiwuList.insert(sta.zhiwu, n);
		zhichengList.insert(sta.zhicheng, n);
		count++;
	}


	//将二叉树信息读入索引文件
	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "wb") != 0||idxFile==0 )
	{
		cout << "索引文件链接失败" << endl;
		return;
	}

	//创建职工号索引文件
	//只能通过队列层次遍历放入信息了
	Queue<Node*> que;
	idxNode Index;
	Node* firstNode;
	que.push(tree.getRoot());
	int _count=0;//再加一个条件作为计数
	while (!que.Empty()&&_count<count)
	{
		firstNode = que.front();
		strcpy_s(Index.no,8, firstNode->key);
		Index.offest = firstNode->offest;
		//写入文件信息
		fwrite(&Index, sizeof(idxNode), 1, idxFile);
		if (strcmp(Index.no, "#") != 0)//不是#字符加1
		{
			_count++;
		}

		if (firstNode->leftchild)
		{
			que.push(firstNode->leftchild);
		}
		else
		{
			Node* newNode= new Node("#", 0);
			que.push(newNode);
		}

		if (firstNode->rightchild)
		{
			que.push(firstNode->rightchild);
		}
		else
		{
			Node* newNode = new Node("#", 0);
			que.push(newNode);
		}

		que.pop();
	}

	fclose(idxFile);

	//职务索引文件
	if (err = fopen_s(&idxFile,zhiwu_idxTargetFile.c_str(), "wb") != 0 ||idxFile==0)
	{
		cout << "索引文件链接失败" << endl;
		return;
	}
	for (int i = 0; i < zhiwuList.getListSize(); i++)
	{
		strcpy_s(Index.no, zhiwuList.getKeyvalue(i));
		LinkList temp = zhiwuList.getLinkList(i);
		ListNode* ptr = temp.getHead();
		while (ptr->next != NULL)
		{
			Index.offest = ptr->next->offest;
			fwrite(&Index, sizeof(idxNode), 1, idxFile);
			ptr = ptr->next;
		}
	}

	fclose(idxFile);

	//职称索引文件
	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "wb") != 0||idxFile==0)
	{
		cout << "索引文件链接失败" << endl;
		return;
	}
	for (int i = 0; i < zhichengList.getListSize(); i++)
	{
		strcpy_s(Index.no, zhichengList.getKeyvalue(i));
		LinkList temp = zhichengList.getLinkList(i);
		ListNode* ptr = temp.getHead();
		while (ptr->next != NULL)
		{
			Index.offest = ptr->next->offest;
			fwrite(&Index, sizeof(idxNode), 1, idxFile);
			ptr = ptr->next;
		}
	}
	

	
	fclose(mfile);
	fclose(idxFile);
}

//打印索引文件
void OutPutIdxFile()
{
	

	errno_t err;
	idxNode Index;
	cout << "职工号索引文件" << endl;
	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}

	
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		cout << "职工号 " << Index.no << ' ';
		cout << "序列号 " << Index.offest << endl;
	}

	fclose(idxFile);
	//一个文件指针只能单次操作一个文件，打开另一个文件之前要将当前的文件关闭才行。 
	//知道自己的问题所在了，不能用一个文件指针同时打开多个文件，必须要关闭
	cout << "职务索引文件" << endl;
	if (err = fopen_s(&idxFile, zhiwu_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}


	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		cout << "职务 " << Index.no << ' ';
		cout << "序列号 " << Index.offest << endl;
	}
	fclose(idxFile);

	cout << "职称索引文件" << endl;
	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}

	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		cout << "职称 " << Index.no << ' ';
		cout << "序列号 " << Index.offest << endl;
	}

	fclose(idxFile);
}

//清空所有文件
void DeleteAll()
{
	
	errno_t err;

	if (err = fopen_s(&mfile, targetmfile.c_str(), "wb") != 0 || mfile == 0)
	{
		cout << "链接主文件失败" << endl;
		return;
	}

	fclose(mfile);

	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "wb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}
	fclose(idxFile);

	if (err = fopen_s(&mfile,zhiwu_idxTargetFile.c_str(), "wb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}
	fclose(idxFile);

	if (err = fopen_s(&mfile, zhicheng_idxTargetFile.c_str(), "wb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}
	fclose(idxFile);
	
}

//通过职工号查找信息
void FindStaff_no()
{
	
	errno_t err;
	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}
	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "链接主文件失败" << endl;
		return;
	}

	//建立二叉树
	AVLTree tree;
	idxNode Index;
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		if (strcmp(Index.no, "#") != 0)
		{
			tree.insert(Index.no, Index.offest);
		}
		
	}

	cout << "打印二叉平衡树" << endl;
	tree.outPut();

	cout << "请输入要查询的职工号" << endl;
	cin >> Index.no;

	int id = tree.getId(Index.no);
	if (id == -1)
	{
		cout << "没有查找到这个职工号" << endl;
	}
	else
	{
		
		fseek(mfile, sizeof(staff) * (id-1), SEEK_SET);
		staff sta;
		fread(&sta, sizeof(staff), 1, mfile);
		cout << "职工号 " << sta.no << ' ';
		cout << "姓名 " << sta.name << ' ';
		cout << "职务 " << sta.zhiwu<< ' ';
		cout << "职称 " << sta.zhicheng << endl;

	}


	fclose(mfile);
	fclose(idxFile);
}

//通过职位查找领导关系
void FindleadRealtionship()
{
	errno_t err;
	if (err = fopen_s(&idxFile, zhiwu_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}

	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "链接主文件失败" << endl;
		return;
	}

	MultList zhiwuList;
	idxNode Index;
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		zhiwuList.insert(Index.no,Index.offest);
	}

	int len;
	staff sta;

	//输出领导关系
	for (int i = 0; i < zhiwuList.getListSize(); i++)
	{
		cout << zhiwuList.getKeyvalue(i) << ":" << endl;
		ListNode* temp = zhiwuList.getLinkList(i).getHead();

		while (temp->next != NULL)
		{
			len = temp->next->offest;
			temp = temp->next;
			fseek(mfile, (len - 1) * sizeof(staff), 0);
			fread(&sta, sizeof(staff), 1, mfile);
			cout << sta.name << ' ';
		}
		cout << endl;
	}

	fclose(mfile);
	fclose(idxFile);

}

//输出职称关系
void FindZhichengRealtionship()
{
	errno_t err;
	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "链接索引文件失败" << endl;
		return;
	}

	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "链接主文件失败" << endl;
		return;
	}

	MultList zhichengList;
	idxNode Index;
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		zhichengList.insert(Index.no, Index.offest);
	}

	char _key[8];
	cout << "请输入你要查找的职称" << endl;
	cin >> _key;

	int id = zhichengList.getKeyId(_key);
	if (id == -1)
	{
		cout << "要查找的职称号不存在" << endl;
		return;
	}

	//输出职称
	int len;
	staff sta;
	ListNode* temp = zhichengList.getLinkList(id).getHead();
	while (temp->next)
	{
		len = temp->next->offest;
		temp = temp->next;
		fseek(mfile, (len - 1) * sizeof(staff), 0);
		fread(&sta, sizeof(staff), 1, mfile);
		cout << sta.name << ' ';
	}
	cout << endl;
	
	fclose(mfile);
	fclose(idxFile);
}