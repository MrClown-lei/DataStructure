#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//��󶥵���
#define MAX_VERTEX_NUM 20
#define INF 99999
//ͼ���ڽӾ���洢�ṹ
typedef struct
{
	string vexs[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;



//ͼ���ڽӱ�洢�ṹ



//����
typedef struct ArcNode
{
	int adjvex;//�û���ָ��Ķ���λ��
	struct ArcNode* nextarc;//ָ����һ������ָ��
	int info;//�û������Ϣ��ָ�루Ȩ�ȣ�
}ArcNode;

//ͷ���
typedef struct VNode
{
	string data;//������Ϣ
	ArcNode* firstarc;//ָ���һ�������ڸö����ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

//ͼ���
typedef struct
{
	AdjList vertices;//�����б�����
	int vexnum;//������
	int arcnum;//����
	int kind;//ͼ������
}AlGraph;

///��ȡ�����
int LocateVex(AlGraph G, string name)
{
	for (int i = 0; i < G.vexnum; i++)
		if (name == G.vertices[i].data)return i;
	return -1;
}
//������Ȩ����ͼ
void CreateDG(AlGraph &G)
{
	cout << "������Ȩ����ͼ��"<<endl;
	cout << "������ͼ�Ķ������ͱ���" << endl;
	cin >> G.vexnum >> G.arcnum;
	cout << "��Ϊ���н��������" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	printf("������%d���ɳ�ʼ��ָ���ն˵�Ļ���\n", G.arcnum);
	string v1, v2;
	for (int i = 0; i < G.arcnum; i++)
	{
		cout << "��" << i + 1 << "��\n";
		cin >> v1 >> v2;
		int m = LocateVex(G, v1);
		int n = LocateVex(G, v2);

		ArcNode* p = new ArcNode;
		p->adjvex = n;
		p->nextarc = NULL;

		if (!G.vertices[m].firstarc)
		{
			G.vertices[m].firstarc = p;
		}
		else
		{
			ArcNode* q = G.vertices[m].firstarc;
			while (q->nextarc)
			{
				q = q->nextarc;
			}
			q->nextarc= p;
		}
	}
}


bool visited[20];
//Ѱ�Ҷ���v�ĵ�һ���ڽӵ�
int FirstAdjVex(AlGraph G, int v)
{
	return G.vertices[v].firstarc->adjvex;
}

//Ѱ�Ҷ���v�������ڽӵ����ڶ���w��ĵ�һ���ڽӵ�
int NextAdjVex(AlGraph G, int v, int w)
{
	ArcNode* p = G.vertices[v].firstarc;
	while (p->adjvex != w)
	{
		p = p->nextarc;
	}

	return p->nextarc ? p->nextarc->adjvex : -1;
}

 #pragma region DFS

void DFS(AlGraph G, int v)
{
	visited[v] = true;
	cout << G.vertices[v].data << endl;
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		if (!visited[w])DFS(G, w);
	}
}
void DFSTraverse(AlGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			DFS(G, i);
		}
	}
}


#pragma endregion

#pragma region BFS

void BFSTraverse(AlGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = false;
	}
	queue<int> qt;
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			cout << G.vertices[i].data << endl;
			qt.push(i);//���ʱ�ͷ��ʣ���ֹ���ʶ��
			while (!qt.empty())
			{
				int v = qt.front();
				qt.pop();
				for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
				{
					if (!visited[w])
					{
						visited[w] = true;
						cout << G.vertices[w].data << endl;
						qt.push(w);//���ʱ�ͷ��ʣ���ֹ���ʶ��
					}
				}
			}
		}
	}
}


#pragma endregion



//���������㷨
void TopoLogicalSort(AlGraph G)
{
    //�����ж������	
	int* Indegree = new int[G.vexnum]{0};
	for (int i = 0; i < G.vexnum; i++)
	{
		for (ArcNode*p=G.vertices[i].firstarc ; p;p=p->nextarc)
		{
			Indegree[p->adjvex]++;
		}
	}
	
	stack<int> S;
	for (int i = 0; i < G.vexnum; i++)//���Ϊ0�Ķ�����ջ
	{
		if (!Indegree[i])
		{
			S.push(i);
		}
	}

	int count = 0;
	cout << "��������";
	while (!S.empty())
	{
		int s_n = S.top();
		S.pop();
		cout << "-->" << G.vertices[s_n].data;
		count++;
		for (ArcNode*p=G.vertices[s_n].firstarc ; p; p=p->nextarc)//ÿ���ڽӵ���ȼ�һ
		{
			if (!(--Indegree[p->adjvex]))//��ȼ�һ����Ϊ0����ջ
			{
				S.push(p->adjvex);
			}
		}
	}
	if (count<G.vexnum)
	{
		cout << "����ͼ���л�·��";
	}
   
}


//��Դ�����·���Ͻ�˹�����㷨
void DIJ(MGraph G,string v_start)
{
	int v0;
	for (int i = 0; i < G.vexnum; i++)
	{
		if (v_start==G.vexs[i])
		{
			v0 = i;
			break;
		}

	}
	bool final[10];//�⼸�����忴����
	bool p[10][10];
	int D[10];
	for (int v = 0; v < G.vexnum; v++)
	{
		final[v] = false;
		D[v] = G.arcs[v0][v];
		for (int w = 0; w < G.vexnum; w++)
		{
			p[v][w] = false;
		}
		if (D[v]<INF)
		{
			p[v][v0] = true;
			p[v][v] = true;
		}
	}
	D[v0] = 0; final[v0] = true;//��ʼ��
	for (int i = 0; i < G.vexnum; i++)
	{
		int min = INF;
		int v = 0;
		for (int w = 0; w < G.vexnum; w++)
		{
			if (!final[w])
			{
				if (D[w]<min)
				{
					v = w;
					min = D[w];
				}
			}
		}
		final[v] = true;
		for (int w = 0; w < G.vexnum; w++)
		{
			if (!final[w]&&(min+G.arcs[v][w]<D[w]))
			{
				D[w]=min + G.arcs[v][w];
				//p[w] = p[v];//�������Ϳ��ܲ��ԣ�Ҳ����forѭ�����θ�ֵ
				p[w][w] = true;
			}
		}
	}
}

int main()
{
	MGraph g;
	string str[] ={ "V0","V1","V2","V3","V4","V5" };
	g.vexs[4]="V5";
	AlGraph G;
	CreateDG(G);
	cout << "----------------------------"<<endl;
	DFSTraverse(G);
	cout << "----------------------------" << endl;
	BFSTraverse(G);
	//TopoLogicalSort(G);

	return 0;
}