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

	//����ڵ����
	cout << "������ڵ����";
	int num;
	cin >> num;
	graph->Vertex = num;

	Visited = new bool[num];
	//�������� 
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

	cout << "������ߵĸ���";

	cin >> graph->Arc;

	for (int i = 0; i < graph->Arc; i++)
	{
		int m, n;
		cout << "�����һ������" << endl;
		cin >> m;
		cout << "����ڶ�������" << endl;
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



//����ָ�����ز���

stack<int> sck;
void (*Visit)(int v) = NULL;


//����ջ����
void _push(int v)
{
	sck.push(v);
}
//��ӡ����
void _print(int v)
{
	cout << v << ' ';
}


//��ʼ����������͸�ֵ����ָ��
void InitVisitedArs(int num,void (*_Visit)(int v))
{
	Visit = _Visit;
	for (int i = 0; i < num; i++)
	{
		Visited[i] = false;
	}

}

//������ȱ���
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

//������ȱ���
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




//ͼȡ�� 
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

	//���ڵ�ѹ��ջ
	InitVisitedArs(num,_push);
	for (int i = 0; i < num; i++)
	{
		if (!Visited[i])
		{
			DFS(grc, i);
		}
	}

}

//�жϷ��������Ƿ�ȫ������
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

//���ǿ��ͨ����
void outputEnd(Node graph)
{
	
	//ȡ��
	qufan_Graph(graph);
	//��ʼ��
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
		cout << "����ǿ��ͨ���� " << endl;
	}
	else
	{
		cout << "ǿ��ͨ�����ĸ���Ϊ����" << count << endl;
	}
}

int main()
{
	Node grap;
	InitGraph(&grap);
	outputEnd(grap);

}

//�������� 6������ 0 1 2 3 4 5 
//7���� ��0��1�� ��1��2 �� ��2��0�� �� 2��4�� ��4��3�� ��3��5���� 5��4��

//�����ǿ��ͨ����Ӧ��Ϊ  (0,1,2) (3,4,5)

//�������� 6������ 0 1 2 3 4 5
//8���� (0,1) (1,0�� ��1��2����2,3) (3,2) (2,4) (4,5) (5,4)
//���ǿ��ͨ����Ӧ��Ϊ (0,1,) (2,3) (4,5)


//�������� 4������ 0��1��2��3

//4������ (0,1)(1,2)(2,3)(3,0)

//���ǿ��ͨ���� ��0,1,2,3��