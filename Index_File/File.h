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

string idxTargetFile = ".\\No_idxFile.dat";//ְ���������ļ���ַ
string zhiwu_idxTargetFile = ".\\zhiwu_idxFile.dat";//ְ��
string zhicheng_idxTargetFile = ".\\zhicheng_idxFile.dat";//ְ��
FILE* mfile;

FILE* idxFile;
string targetmfile = ".\\main.dat";//�趨Ŀ��·��
//���� �ļ�·�� ".\\main2.dat"



void InputMainFile()//���һ����¼
{

	errno_t err;
	if (err = fopen_s(&mfile, targetmfile.c_str(), "ab+") != 0 || mfile == 0)
	{
		cout << "�������ļ�ʧ��" << endl;
		return;
	}

	cout << "��������Ϣ ְ���� ����  ְλ  ְ��" << endl;
	staff sta;
	cin >> sta.no >> sta.name >> sta.zhiwu >> sta.zhicheng;
	if (fwrite(&sta, sizeof(staff), 1, mfile) != 1)
	{
		cout << "д���ļ�ʧ��" << endl;
		return;
	}

	//��ӽ��������ļ�����ȻҲҪ�ı������ļ�
		//��������������ص��ڴ���
	AVLTree tree;
	MultList zhiwuList;
	MultList zhichengList;


	idxNode Index;
	//��ȡ����ƽ������Ϣ

	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "rb+") != 0 || idxFile == 0)
	{
		cout << "��������ʧ��" << endl;
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



	//��֮��Ӧ������ָ��λ�ã���Ȼ���β��д��
	rewind(idxFile);

	//��ȡ��֮��Ҫ��д��������
//ֻ��ͨ�����в�α���������Ϣ��
	Queue<Node*> que;
	Node* firstNode;
	que.push(tree.getRoot());
	int count = tree.getNodeNum();
	int _count = 0;//�ټ�һ��������Ϊ����
	while (!que.Empty() && _count < count)
	{
		firstNode = que.front();
		strcpy_s(Index.no, 8, firstNode->key);
		Index.offest = firstNode->offest;
		//д���ļ���Ϣ
		fwrite(&Index, sizeof(idxNode), 1, idxFile);
		if (strcmp(Index.no, "#") != 0)//����#�ַ���1
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

	//��ȡְ����ر���Ϣ

	if (err = fopen_s(&idxFile, zhiwu_idxTargetFile.c_str(), "rb+") != 0 || idxFile == 0)
	{
		cout << "��������ʧ��" << endl;
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

	//��ȡְ�ƶ��ر���Ϣ

	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "rb+") != 0 || idxFile == 0)
	{
		cout << "��������ʧ��" << endl;
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

//��ӡ���ļ�����
void OutPutMainFile()
{
	errno_t  err;
	
	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "���ļ�����ʧ��" << endl;
		return;
	}

	staff sta;
	while (fread(&sta, sizeof(staff), 1, mfile) != NULL)
	{
		cout << "��� " << sta.no << ' ';
		cout << "���� " << sta.name << ' ';
		cout << "ְ�� " << sta.zhiwu << ' ';
		cout << "ְ�� " << sta.zhicheng << ' ' << endl;
	}

	fclose(mfile);
}





void CreateIdxFile()
{
	
	
	//�������ļ�
	errno_t err;
	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0||mfile==0)
	{
		cout << "���ļ�����ʧ��"<<endl;
		return;
	}

	//��ȡ��Ϣ������ƽ����
	AVLTree tree;

	//��ȡ��Ϣ��ְ����ر�
	MultList zhiwuList;

	//��ȡ��Ϣ��ְ�ƶ��ر�
	MultList zhichengList;

	staff sta;
	int count = 0;//����ж��ٸ���¼
	int n = 0;
	while (fread(&sta, sizeof(staff), 1,mfile ) != NULL)
	{
		tree.insert(sta.no, ++n);
		zhiwuList.insert(sta.zhiwu, n);
		zhichengList.insert(sta.zhicheng, n);
		count++;
	}


	//����������Ϣ���������ļ�
	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "wb") != 0||idxFile==0 )
	{
		cout << "�����ļ�����ʧ��" << endl;
		return;
	}

	//����ְ���������ļ�
	//ֻ��ͨ�����в�α���������Ϣ��
	Queue<Node*> que;
	idxNode Index;
	Node* firstNode;
	que.push(tree.getRoot());
	int _count=0;//�ټ�һ��������Ϊ����
	while (!que.Empty()&&_count<count)
	{
		firstNode = que.front();
		strcpy_s(Index.no,8, firstNode->key);
		Index.offest = firstNode->offest;
		//д���ļ���Ϣ
		fwrite(&Index, sizeof(idxNode), 1, idxFile);
		if (strcmp(Index.no, "#") != 0)//����#�ַ���1
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

	//ְ�������ļ�
	if (err = fopen_s(&idxFile,zhiwu_idxTargetFile.c_str(), "wb") != 0 ||idxFile==0)
	{
		cout << "�����ļ�����ʧ��" << endl;
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

	//ְ�������ļ�
	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "wb") != 0||idxFile==0)
	{
		cout << "�����ļ�����ʧ��" << endl;
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

//��ӡ�����ļ�
void OutPutIdxFile()
{
	

	errno_t err;
	idxNode Index;
	cout << "ְ���������ļ�" << endl;
	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}

	
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		cout << "ְ���� " << Index.no << ' ';
		cout << "���к� " << Index.offest << endl;
	}

	fclose(idxFile);
	//һ���ļ�ָ��ֻ�ܵ��β���һ���ļ�������һ���ļ�֮ǰҪ����ǰ���ļ��رղ��С� 
	//֪���Լ������������ˣ�������һ���ļ�ָ��ͬʱ�򿪶���ļ�������Ҫ�ر�
	cout << "ְ�������ļ�" << endl;
	if (err = fopen_s(&idxFile, zhiwu_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}


	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		cout << "ְ�� " << Index.no << ' ';
		cout << "���к� " << Index.offest << endl;
	}
	fclose(idxFile);

	cout << "ְ�������ļ�" << endl;
	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}

	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		cout << "ְ�� " << Index.no << ' ';
		cout << "���к� " << Index.offest << endl;
	}

	fclose(idxFile);
}

//��������ļ�
void DeleteAll()
{
	
	errno_t err;

	if (err = fopen_s(&mfile, targetmfile.c_str(), "wb") != 0 || mfile == 0)
	{
		cout << "�������ļ�ʧ��" << endl;
		return;
	}

	fclose(mfile);

	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "wb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}
	fclose(idxFile);

	if (err = fopen_s(&mfile,zhiwu_idxTargetFile.c_str(), "wb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}
	fclose(idxFile);

	if (err = fopen_s(&mfile, zhicheng_idxTargetFile.c_str(), "wb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}
	fclose(idxFile);
	
}

//ͨ��ְ���Ų�����Ϣ
void FindStaff_no()
{
	
	errno_t err;
	if (err = fopen_s(&idxFile, idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}
	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "�������ļ�ʧ��" << endl;
		return;
	}

	//����������
	AVLTree tree;
	idxNode Index;
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		if (strcmp(Index.no, "#") != 0)
		{
			tree.insert(Index.no, Index.offest);
		}
		
	}

	cout << "��ӡ����ƽ����" << endl;
	tree.outPut();

	cout << "������Ҫ��ѯ��ְ����" << endl;
	cin >> Index.no;

	int id = tree.getId(Index.no);
	if (id == -1)
	{
		cout << "û�в��ҵ����ְ����" << endl;
	}
	else
	{
		
		fseek(mfile, sizeof(staff) * (id-1), SEEK_SET);
		staff sta;
		fread(&sta, sizeof(staff), 1, mfile);
		cout << "ְ���� " << sta.no << ' ';
		cout << "���� " << sta.name << ' ';
		cout << "ְ�� " << sta.zhiwu<< ' ';
		cout << "ְ�� " << sta.zhicheng << endl;

	}


	fclose(mfile);
	fclose(idxFile);
}

//ͨ��ְλ�����쵼��ϵ
void FindleadRealtionship()
{
	errno_t err;
	if (err = fopen_s(&idxFile, zhiwu_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}

	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "�������ļ�ʧ��" << endl;
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

	//����쵼��ϵ
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

//���ְ�ƹ�ϵ
void FindZhichengRealtionship()
{
	errno_t err;
	if (err = fopen_s(&idxFile, zhicheng_idxTargetFile.c_str(), "rb") != 0 || idxFile == 0)
	{
		cout << "���������ļ�ʧ��" << endl;
		return;
	}

	if (err = fopen_s(&mfile, targetmfile.c_str(), "rb") != 0 || mfile == 0)
	{
		cout << "�������ļ�ʧ��" << endl;
		return;
	}

	MultList zhichengList;
	idxNode Index;
	while (fread(&Index, sizeof(idxNode), 1, idxFile) != NULL)
	{
		zhichengList.insert(Index.no, Index.offest);
	}

	char _key[8];
	cout << "��������Ҫ���ҵ�ְ��" << endl;
	cin >> _key;

	int id = zhichengList.getKeyId(_key);
	if (id == -1)
	{
		cout << "Ҫ���ҵ�ְ�ƺŲ�����" << endl;
		return;
	}

	//���ְ��
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