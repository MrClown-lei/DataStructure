#include<iostream>
#include<string>
#include<queue>
using namespace std;


//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//定义函数结果类型
typedef int Status;


//-------二叉树的二叉链表存储表示
typedef struct BiTNode
{
	char data;
	struct BiTNode* Lchild, *Rchild;
}BiTNode,*BiTree;



typedef enum PointerTag
{
	Link,//指针
	Thread//线索
};
//二叉树的二叉线索存储表示
typedef struct BiThrNode
{
	char data;
	struct BiThrNode*lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode,*BiThrTree;

//按先序次序输入二叉树结点值，‘#’表示空树
void CreateBiTree(BiTree& T)
{
	char ch;
	cin >> ch;
	if (ch=='#')
	{
		T= NULL;
	}
	else
	{
		if (!(T=(BiTree)malloc(sizeof(BiTNode))))
		{
			exit(OVERFLOW);
		}
		else
		{
			CreateBiTree(T->Lchild);
	        T->data = ch;
			CreateBiTree(T->Rchild);
		}
	}
}

//二叉树先序遍历
void preorder(BiTree T)
{
	if (T!=NULL)
	{
		cout << T->data;
		preorder(T->Lchild);
		preorder(T->Rchild);
	}
}

//二叉树中序遍历
void inorder(BiTree T)
{
	if (T != NULL)
	{
		inorder(T->Lchild);
		cout << T->data;
		inorder(T->Rchild);
	}
}

//二叉树后序遍历
void backorder(BiTree T)
{
	if (T != NULL)
	{
		backorder(T->Lchild);
		backorder(T->Rchild);
		cout << T->data;
	}
}


//二叉树层次遍历
void LevelOrder(BiTree T)
{
	queue<BiTree> qt;
	BiTree q;
	qt.push(T);
	while (!qt.empty())
	{
		q = qt.front();
		qt.pop();
		cout << q->data;
		if (q->Lchild!=NULL)
		{
			qt.push(q->Lchild);
		}
		if (q->Rchild != NULL)
		{
			qt.push(q->Rchild);
		}
	}

}

BiThrTree pre;//始终指向当前结点的前驱
//中序二叉树并线索化
void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild);//线索化左子树
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)//当前结点修改上一个结点的后继
		{
			pre->RTag = Link;
			pre->rchild = p;
		}
		pre = p;//始终指向p前驱
		InThreading(p->rchild);//线索化右子树
	}
}
//中序二叉树并线索化,thrt为建的头结点
void InOrderThreading(BiThrTree& thrt, BiThrTree T)
{
	if (!(thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
	{
		exit(OVERFLOW);
	}
	thrt->LTag = Link;
	thrt->RTag = Thread;
	thrt->rchild = thrt;//初始化头结点
	if (!T)
	{
		thrt->lchild = thrt;//左指针回指
	}
	else
	{
		thrt->lchild = T;//头结点左指针指向根结点
		pre = thrt;
		InThreading(T);
		pre->RTag = Thread;
		pre->rchild = thrt;//最后一个结点右指针线索化
		thrt->rchild = pre;//头结点右指针指向最后一个结点
	}
}

//中序线索化后找某个结点后继
BiThrTree inordernext(BiThrTree p)
{
	if (p->RTag==1)
	{
		return p->rchild;
	}
	else
	{
		BiThrTree q = p->rchild;
		while (q->LTag==0)//当有前驱是跳出循环
		{
			q = q->lchild;
		}
		return q;
	}
}

//中序线索化后找某个结点前驱
BiThrTree inorderlast(BiThrTree p)
{
	if (p->LTag == 1)
	{
		return p->lchild;
	}
	else
	{
		BiThrTree q = p->lchild;
		while (q->RTag == 0)//当有后继时跳出循环
		{
			q = q->rchild;
		}
		return q;
	}
}



//中序遍历输出二叉树叶子结点
void InOrder(BiTree T)
{
	if (T)
	{
		InOrder(T->Lchild);
		if (T->Lchild==NULL && T->Rchild==NULL)
		{
			cout << T->data << endl;
		}
		InOrder(T->Rchild);
	}
}

//求二叉树的高度（后序遍历）
int High(BiTree T)
{
	int hl, hr, h;
	if (!T)return 0;
	else
	{
		hl = High(T->Lchild);
		hr = High(T->Rchild);
		h =( hl > hr ? hl : hr)+1;
		return h;
	}
}

//二叉树相似性判断
int like(BiTree T1, BiTree T2)
{
	int l1, l2;
	if (T1==NULL&&T2==NULL)
	{
		return 1;
	}
	else if (T1 == NULL || T2 == NULL)
	{
		return 0;
	}
	else
	{
		l1 = like(T1->Lchild, T2->Lchild);
		l2 = like(T1->Rchild, T2->Rchild);
		return (l1 && l2);
	}
}

//判断是否是完全二叉树
bool IsComplete(BiTree t)
{
	queue<BiTree> qt;
	if (!t)
	{
		return true;
	}
	qt.push(t);
	while (!qt.empty())
	{
		BiTree q = qt.front();
		qt.pop();
		if (q)
		{
			qt.push(q->Lchild);
			qt.push(q->Rchild);
		}
		else
		{
			while (!qt.empty())
			{
				BiTree q = qt.front();
				qt.pop();
				if (q)//检测到空指针后，若是完全二叉树，则后面的都是空指针，否则不是完全二叉树
				{
					return 0;
				}

			}
		}
	}
	return 1;
}

int main3()
{
	char* ch=new char;
	cin >> ch;

	BiTree t1;
	CreateBiTree(t1);
	/*cout << "-------------" << endl;
	BiTree t2;
	CreateBiTree(t2);
	cout << like(t1, t2);*/
	//InOrder(t);
	bool a = IsComplete(t1);
	cout << a;
	return 0;
}