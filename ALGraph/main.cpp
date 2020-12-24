#include<iostream>
#include<stack>
#include<queue>
using namespace std;

struct Node {
	int Vertex;
	int Arc;
	int** ars;
};

bool* Visited;

void InitGraph(Node* graph)
{

	//输入节点个数
	cout << "请输入节点个数";
	int num;
	cin >> num;
	graph->Vertex = num;

	Visited = new bool[num];
	//建立矩阵 
	graph->ars = new int*[num];
	for (int i = 0; i < num; i++)
	{
		graph->ars[i] = new int[num];
	}
	
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			graph->ars[i][j] = 0;
		}
	}

	cout << "请输入边的个数";

	cin >> graph->Arc;

	for (int i = 0; i < graph->Arc; i++)
	{
		int m, n;
		cout << "输入第一个顶点" << endl;
		cin >> m;
		cout << "输入第二个顶点" << endl;
		cin >> n;
		graph->ars[m][n] = 1;
	}

}

void InitGraph(Node* graph,int num)
{
	graph->Vertex = num;

	graph->ars = new int* [num];
	for (int i = 0; i < num; i++)
	{
		graph->ars[i] = new int[num];
	}
}

int firstAdjVex(Node Graph, int v)
{
	for (int i = 0; i < Graph.Vertex; i++)
	{
		if (Graph.ars[v][i] != 0)
		{
			return i;
		}
	}
	return -1;
}

int nextAdjVex(Node Graph, int v, int w)
{
	for (int i = w+1; i < Graph.Vertex; i++)
	{
		if (Graph.ars[v][i] != 0)
		{
			return i;
		}
	}
	return -1;
}



//函数指针和相关操作

stack<int> sck;
void (*Visit)(int v) = NULL;


//输入栈操作
void _push(int v)
{
	sck.push(v);
}
//打印操作
void _print(int v)
{
	cout << v << ' ';
}


//初始化访问数组和赋值函数指针
void InitVisitedArs(int num,void (*_Visit)(int v))
{
	Visit = _Visit;
	for (int i = 0; i < num; i++)
	{
		Visited[i] = false;
	}

}

//深度优先遍历
void DFS(Node graph, int v)
{
	Visited[v] = true;
	Visit(v);

	int w;
	for (w = firstAdjVex(graph, v); w >= 0; w = nextAdjVex(graph, v, w))
	{
		if (!Visited[w])
		{
			DFS(graph, w);
		}
	}
}

//广度优先遍历
void BFS(Node graph, int v)
{
	queue<int> que;
	que.push(v);
	while (!que.empty())
	{
		v = que.front();
		Visited[v] = true;
		Visit(v);
		que.pop();

		for (int w = firstAdjVex(graph, v); w >= 0; w = nextAdjVex(graph, v, w))
		{
			if (!Visited[w])
			{
				que.push(w);
			}
			
		}
	}

}




//图取反 
void qufan_Graph(Node graph)
{
	int num = graph.Vertex;
	
	Node grc;

	InitGraph(&grc,num);

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			grc.ars[i][j] = graph.ars[j][i];
		}
	}

	//将节点压入栈
	InitVisitedArs(num,_push);
	for (int i = 0; i < num; i++)
	{
		if (!Visited[i])
		{
			DFS(grc, i);
		}
	}

}

//判断访问数组是否全部满了
bool isALLtrue(int num)
{
	for (int i = 0; i < num; i++)
	{
		if (Visited[i] == false)
		{
			return false;
		}
	}
	return true;
}

//输出强连通分量
void outputEnd(Node graph)
{
	
	//取反
	qufan_Graph(graph);
	//初始化
	InitVisitedArs(graph.Vertex, _print);

	int count = 0;
	bool flag = false;
	while (!isALLtrue(graph.Vertex))
	{
		int i = sck.top();
		sck.pop();
		if (!Visited[i])
		{
			flag = true;
			DFS(graph, i);
		}
		if (flag)
		{
			count++;
			cout << endl;
			flag = false;
		}
	}
	if (count == 1)
	{
		cout << "这是强连通分量 " << endl;
	}
	else
	{
		cout << "强连通分量的个数为：　" << count << endl;
	}
}

int main()
{
	Node grap;
	InitGraph(&grap);
	outputEnd(grap);

}

//测试数据 6个顶点 0 1 2 3 4 5 
//7条边 （0，1） （1，2 ） （2，0） （ 2，4） （4，3） （3，5）（ 5，4）

//输出的强连通分量应该为  (0,1,2) (3,4,5)

//测试数据 6个顶点 0 1 2 3 4 5
//8条边 (0,1) (1,0） （1，2）（2,3) (3,2) (2,4) (4,5) (5,4)
//输出强连通分量应该为 (0,1,) (2,3) (4,5)


//测试数据 4个顶点 0，1，2，3

//4条边数 (0,1)(1,2)(2,3)(3,0)

//输出强连通分量 （0,1,2,3）