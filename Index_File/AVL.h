#pragma once
#include<iostream>
using namespace std;

//ʵ�ֶ��У�Ϊ��α�����׼��
//������
template<class T>
struct QNode
{
	T data;
	QNode* next;
	QNode()
	{
		data = NULL;
		next = NULL;
	}
};

template<class T>
class Queue
{
private:
	QNode<T>* Head;
	QNode<T>* rear;
	int QueueSize;
public:
	Queue()
	{
		Head = new QNode<T>();//Ϊָ�������һƬ�ڴ�ؼ���Ϊָ��
		rear = Head;
		QueueSize = 0;
	}

	bool Empty()
	{
		return QueueSize == 0;
	}

	int Size()
	{
		return QueueSize;
	}

	void push(T value)
	{
		QNode<T>* temp = new QNode<T>();
		temp->data = value;
		rear->next = temp;
		rear = rear->next;
		QueueSize++;
	}

	void pop()
	{
		QNode<T>* temp = Head->next;
		Head->next = Head->next->next;
		delete temp;//��new ��ϵ�Ӧ����delete�Ŷ�
		QueueSize--;
	}
	T front()
	{
		return Head->next->data;
	}
};


//����ƽ����
struct Node
{
	char key[8];

	int offest;
	
	//ƽ������ֻ��Ҫ�ڲ����ɾ��ʱ������ʹ�ã�ƽʱû��Ҫר�Ŵ洢

	Node* leftchild;
	Node* rightchild;

	Node(char _key[], int n)
	{
		strcpy_s(key, 8, _key);
		offest = n;

		leftchild = NULL;
		rightchild = NULL;
		
	}

	Node(string s, int n)
	{
		strcpy_s(key, 8,s.c_str());
		offest = n;

		leftchild = NULL;
		rightchild = NULL;
	}

};

class AVLTree
{
private:
	Node* root;
public:
	AVLTree()
	{
		root = NULL;
	}

	static void print(Node* t)//��ӡ��Ϣ,����������ڲ�α����������Ϣ
	{
		if (t)
		{
			cout << "ְ����" << t->key << ' ';
			cout << "���к�" << t->offest << endl;
		}
		
	}

	Node* getRoot()//���ظ��ڵ�
	{
		return root;
	}

	//����
	//Ӧ�õݹ����
	void insert(char _key[], int _offest)
	{
		Node* newNode = new Node(_key, _offest);
	    _Insert(root,newNode);
	}

	void  _Insert(Node* &rts,Node* t)
	{
		if (rts == NULL)
		{
			rts = t;
		}
		else
		{
			if (strcmp(t->key, rts->key) < 0)
			{
				_Insert(rts->leftchild, t);
			}
			else
			{
			    _Insert(rts->rightchild, t);
			}

			//��ʼ����ƽ������
			int a = height(rts->leftchild) - height(rts->rightchild);
			if (a == 2)
			{
				if (strcmp(t->key, rts->leftchild->key) < 0)
				{
					rts = rightRotation(rts);
					//������Ϊ& rtsҲ��������һ����������ֵ
				}
				else if (strcmp(t->key, rts->leftchild->key) > 0)//���������� lr��ת
				{
					rts = leftRightRotation(rts);
				}
			}
			else if (a == -2)
			{
				if (strcmp(t->key,rts->rightchild->key) > 0)
				{
					rts = leftRotation(rts);
				}
				else if (strcmp(t->key, rts->rightchild->key) < 0)//С�������� rl��ת
				{
					rts = rightLeftRotation(rts);
				}
			}
		}
	}


	//ɾ��

	//r��ת
	Node* rightRotation(Node* t)//ͨ��ʹ��&���ŵķ�ʽ ����ת���ؽ����Ŀ��
	{
		Node* temp = t->leftchild;
		t->leftchild = temp->rightchild;
		temp->rightchild = t;

		return temp;
	}
	//l��ת
	Node* leftRotation(Node* t)
	{

		Node* temp = t->rightchild;
		t->rightchild = temp->leftchild;
		temp->leftchild = t;

		return temp;
	}

	//lr��ת
	Node* leftRightRotation(Node* t)
	{
		
		t->leftchild = leftRotation(t->leftchild);
		return rightRotation(t);
	}

	//rl��ת
	Node* rightLeftRotation(Node* t)
	{
		t->rightchild = rightRotation(t->rightchild);
		return leftRotation(t);
	}


	//�õ��߶�
	int height(Node* t)
	{
		if (t == NULL)
		{
			return 0;
		}
		int lLength = height(t->leftchild);
		int rLength = height(t->rightchild);
		return lLength > rLength ? lLength+1 : rLength+1;
	}



	//��α���
	void levelOrderTraverse(Node* t)
	{
		Queue<Node*> que;
		if (t)
			que.push(t);
		Node* temp;
		while (!que.Empty())
		{
			temp = que.front();
			print(temp);
			if (temp->leftchild)
				que.push(temp->leftchild);
			if (temp->rightchild)
				que.push(temp->rightchild);
			que.pop();
		}

	}

	void outPut()
	{
		levelOrderTraverse(root);
	}

	int getId(char _key[])
	{
		Node* ptr = root;
		while (ptr)
		{
			if (strcmp(_key, ptr->key) < 0)
			{
				ptr = ptr->leftchild;
			}
			else if (strcmp(_key, ptr->key) > 0)
			{
				ptr = ptr->rightchild;
			}
			else
			{
				return ptr->offest;
			}
		}
		return - 1;
	}

	//���ؽ���������ȷ�����к�
	int getNodeNum()
	{
		return _getNodeNum(root);
	}

private:
	int _getNodeNum(Node* t)
	{
		if (!t)
		{
			return 0;
		}
		else
		{
			return 1 + _getNodeNum(t->leftchild) + _getNodeNum(t->rightchild);
		}
	}

};
