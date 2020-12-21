#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<cstdio>

using namespace std;

template<class T>//模板函数
void Swap(T& a, T& b)//仅对接下来声明的第一个函数有用
{
	int temp = a;
	a = b;
	b = a;
}
int main()
{
	int a = 1, b = 2;
	Swap(a, b);//隐式指定类型
	Swap<int>(a, b);//显示指定类型
}

