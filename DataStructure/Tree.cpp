#include<iostream>
#include<string>
#include<queue>
using namespace std;


//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//���庯���������
typedef int Status;


//-------�������Ķ�������洢��ʾ
typedef struct BiTNode
{
	char data;
	struct BiTNode* Lchild, *Rchild;
}BiTNode,*BiTree;



typedef enum PointerTag
{
	Link,//ָ��
	Thread//����
};
//�������Ķ��������洢��ʾ
typedef struct BiThrNode
{
	char data;
	struct BiThrNode*lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode,*BiThrTree;

//���������������������ֵ����#����ʾ����
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

//�������������
void preorder(BiTree T)
{
	if (T!=NULL)
	{
		cout << T->data;
		preorder(T->Lchild);
		preorder(T->Rchild);
	}
}

//�������������
void inorder(BiTree T)
{
	if (T != NULL)
	{
		inorder(T->Lchild);
		cout << T->data;
		inorder(T->Rchild);
	}
}

//�������������
void backorder(BiTree T)
{
	if (T != NULL)
	{
		backorder(T->Lchild);
		backorder(T->Rchild);
		cout << T->data;
	}
}


//��������α���
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

BiThrTree pre;//ʼ��ָ��ǰ����ǰ��
//�����������������
void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild);//������������
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)//��ǰ����޸���һ�����ĺ��
		{
			pre->RTag = Link;
			pre->rchild = p;
		}
		pre = p;//ʼ��ָ��pǰ��
		InThreading(p->rchild);//������������
	}
}
//�����������������,thrtΪ����ͷ���
void InOrderThreading(BiThrTree& thrt, BiThrTree T)
{
	if (!(thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
	{
		exit(OVERFLOW);
	}
	thrt->LTag = Link;
	thrt->RTag = Thread;
	thrt->rchild = thrt;//��ʼ��ͷ���
	if (!T)
	{
		thrt->lchild = thrt;//��ָ���ָ
	}
	else
	{
		thrt->lchild = T;//ͷ�����ָ��ָ������
		pre = thrt;
		InThreading(T);
		pre->RTag = Thread;
		pre->rchild = thrt;//���һ�������ָ��������
		thrt->rchild = pre;//ͷ�����ָ��ָ�����һ�����
	}
}

//��������������ĳ�������
BiThrTree inordernext(BiThrTree p)
{
	if (p->RTag==1)
	{
		return p->rchild;
	}
	else
	{
		BiThrTree q = p->rchild;
		while (q->LTag==0)//����ǰ��������ѭ��
		{
			q = q->lchild;
		}
		return q;
	}
}

//��������������ĳ�����ǰ��
BiThrTree inorderlast(BiThrTree p)
{
	if (p->LTag == 1)
	{
		return p->lchild;
	}
	else
	{
		BiThrTree q = p->lchild;
		while (q->RTag == 0)//���к��ʱ����ѭ��
		{
			q = q->rchild;
		}
		return q;
	}
}



//����������������Ҷ�ӽ��
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

//��������ĸ߶ȣ����������
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

//�������������ж�
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

//�ж��Ƿ�����ȫ������
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
				if (q)//��⵽��ָ���������ȫ�������������Ķ��ǿ�ָ�룬��������ȫ������
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