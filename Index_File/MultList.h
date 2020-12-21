#pragma once
#include<iostream>
using namespace std;

//�洢���кŵĵ�����
struct ListNode
{
	int offest;
	ListNode* next;
	ListNode()
	{
		offest = -1;
		next = NULL;
	}
};

class LinkList
{
private:
	ListNode* head;
	ListNode* last;
public:
	LinkList()
	{
		head = new ListNode();
		last = head;
	}

	void insert(int offest)
	{
		ListNode* temp = new ListNode();
		temp->offest = offest;
		last->next = temp;
		last = last->next;
	}

	ListNode* getHead()
	{
		return head;
	}

	int getNodeNum()
	{
		ListNode* ptr = head;
		int sum = 0;
		while (ptr->next)
		{
			sum++;
			ptr = ptr->next;
		}
		return sum;
	}

	//��ӡ��Ϣ
	void outPut()
	{
		ListNode* ptr = head->next;
		while (ptr)
		{
			cout << ptr->offest << ' ';
			ptr = ptr->next;
		}
	}
};


//���ر�
struct KeyNode
{
	char key[8];
	LinkList offestList;
	KeyNode()
	{
		*key = 's';
	}
};

class MultList
{
private:
	KeyNode* list;
	int listSize;
	int defaultLength = 10;
public:
	MultList()
	{
		list = new KeyNode[defaultLength];
		listSize = -1;
	}

	//���س���
	int getListSize()
	{
		return listSize + 1;
	}

	//���عؼ���
	char* getKeyvalue(int i)
	{
		return list[i].key;
	}
	//��������
	LinkList getLinkList(int i)
	{
		return list[i].offestList;
	}

	//�õ��ؼ������ڵ�����������
	int getKeyId(char _key[])
	{
		int id = -1;
		for (int i = 0; i <= listSize; i++)
		{
			if (strcmp(list[i].key, _key) == 0)
			{
				id = i;
				return id;
			}
		}
		if (id == -1)
		{
			strcpy_s(list[++listSize].key, 8, _key);
			return listSize;
		}
		else
		{
			return - 1;
		}
	}

	//�������
	void insert(char _key[], int n)
	{
		int id = getKeyId(_key);
		list[id].offestList.insert(n);
	}

	//��ӡ���ر�
	void outPut()
	{
		for (int i = 0; i <= listSize; i++)
		{
			cout << list[i].key << ":   ";
			cout << "���кţ� ";
			list[i].offestList.outPut();
			cout << endl;
		}
	}

	//�����ܵĽ�����
	int getNodeNum()
	{
		int sum = 0;
		for (int i = 0; i <= listSize; i++)
		{
			sum += list[i].offestList.getNodeNum();
		}
		return sum;
	}
};
