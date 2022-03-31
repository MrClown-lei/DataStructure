#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//最大顶点数
#define MAX_VERTEX_NUM 20
#define INF 99999
//图的邻接矩阵存储结构
typedef struct
{
	string vexs[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;



//图的邻接表存储结构
//first


//表结点
typedef struct ArcNode
{
	int adjvex;//该弧所指向的顶点位置
	struct ArcNode* nextarc;//指向下一条弧的指针
	int info;//该弧相关信息的指针（权等）
}ArcNode;

//头结点
typedef struct VNode
{
	string data;//顶点信息
	ArcNode* firstarc;//指向第一条依附于该顶点的指针
}VNode,AdjList[MAX_VERTEX_NUM];

//图结点
typedef struct
{
	AdjList vertices;//顶点列表数组
	int vexnum;//顶点数
	int arcnum;//弧数
	int kind;//图的种类
}AlGraph;

///获取结点标号
int LocateVex(AlGraph G, string name)
{
	for (int i = 0; i < G.vexnum; i++)
		if (name == G.vertices[i].data)return i;
	return -1;
}
//建立无权有向图
void CreateDG(AlGraph &G)
{
	cout << "建立无权有向图。"<<endl;
	cout << "请输入图的顶点数和边数" << endl;
	cin >> G.vexnum >> G.arcnum;
	cout << "请为所有结点命名：" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	printf("请输入%d组由初始点指向终端点的弧：\n", G.arcnum);
	string v1, v2;
	for (int i = 0; i < G.arcnum; i++)
	{
		cout << "第" << i + 1 << "组\n";
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
//寻找顶点v的第一个邻接点
int FirstAdjVex(AlGraph G, int v)
{
	return G.vertices[v].firstarc->adjvex;
}

//寻找顶点v的所有邻接点中在顶点w后的第一个邻接点
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
			qt.push(i);//入队时就访问，防止访问多次
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
						qt.push(w);//入队时就访问，防止访问多次
					}
				}
			}
		}
	}
}


#pragma endregion



//拓扑排序算法
void TopoLogicalSort(AlGraph G)
{
    //求所有顶点入度	
	int* Indegree = new int[G.vexnum]{0};
	for (int i = 0; i < G.vexnum; i++)
	{
		for (ArcNode*p=G.vertices[i].firstarc ; p;p=p->nextarc)
		{
			Indegree[p->adjvex]++;
		}
	}
	
	stack<int> S;
	for (int i = 0; i < G.vexnum; i++)//入度为0的顶点入栈
	{
		if (!Indegree[i])
		{
			S.push(i);
		}
	}

	int count = 0;
	cout << "拓扑序列";
	while (!S.empty())
	{
		int s_n = S.top();
		S.pop();
		cout << "-->" << G.vertices[s_n].data;
		count++;
		for (ArcNode*p=G.vertices[s_n].firstarc ; p; p=p->nextarc)//每个邻接点入度减一
		{
			if (!(--Indegree[p->adjvex]))//入度减一后若为0则入栈
			{
				S.push(p->adjvex);
			}
		}
	}
	if (count<G.vexnum)
	{
		cout << "有向图中有回路。";
	}
   
}


//单源点最短路径迪杰斯特拉算法
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
	bool final[10];//这几个定义看书上
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
	D[v0] = 0; final[v0] = true;//初始化
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
				//p[w] = p[v];//数据类型可能不对，也可用for循环依次赋值
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