#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<cstdio>

using namespace std;

template<class T>//ģ�庯��
void Swap(T& a, T& b)//���Խ����������ĵ�һ����������
{
	int temp = a;
	a = b;
	b = a;
}
int main()
{
	int a = 1, b = 2;
	Swap(a, b);//��ʽָ������
	Swap<int>(a, b);//��ʾָ������
}

