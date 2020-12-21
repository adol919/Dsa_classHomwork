#pragma once
#include<iostream>
using namespace std;

//实现队列，为层次遍历做准备
//链队列
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
		Head = new QNode<T>();//为指针分配了一片内存控件作为指向
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
		delete temp;//和new 配合的应该是delete才对
		QueueSize--;
	}
	T front()
	{
		return Head->next->data;
	}
};


//二叉平衡树
struct Node
{
	char key[8];

	int offest;
	
	//平衡因子只需要在插入和删除时，计算使用，平时没必要专门存储

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

	static void print(Node* t)//打印信息,这个是用于在层次遍历中输出信息
	{
		if (t)
		{
			cout << "职工号" << t->key << ' ';
			cout << "序列号" << t->offest << endl;
		}
		
	}

	Node* getRoot()//返回根节点
	{
		return root;
	}

	//插入
	//应该递归插入
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

			//开始计算平衡因子
			int a = height(rts->leftchild) - height(rts->rightchild);
			if (a == 2)
			{
				if (strcmp(t->key, rts->leftchild->key) < 0)
				{
					rts = rightRotation(rts);
					//这里因为& rts也代表着上一个结点的量的值
				}
				else if (strcmp(t->key, rts->leftchild->key) > 0)//大于左子树 lr旋转
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
				else if (strcmp(t->key, rts->rightchild->key) < 0)//小于右子树 rl旋转
				{
					rts = rightLeftRotation(rts);
				}
			}
		}
	}


	//删除

	//r旋转
	Node* rightRotation(Node* t)//通过使用&符号的方式 来旋转返回结点达成目标
	{
		Node* temp = t->leftchild;
		t->leftchild = temp->rightchild;
		temp->rightchild = t;

		return temp;
	}
	//l旋转
	Node* leftRotation(Node* t)
	{

		Node* temp = t->rightchild;
		t->rightchild = temp->leftchild;
		temp->leftchild = t;

		return temp;
	}

	//lr旋转
	Node* leftRightRotation(Node* t)
	{
		
		t->leftchild = leftRotation(t->leftchild);
		return rightRotation(t);
	}

	//rl旋转
	Node* rightLeftRotation(Node* t)
	{
		t->rightchild = rightRotation(t->rightchild);
		return leftRotation(t);
	}


	//得到高度
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



	//层次遍历
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

	//返回结点个数用来确定序列号
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
