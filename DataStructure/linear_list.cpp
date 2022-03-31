#include<iostream>
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
//定义数据元素类型
typedef int ElemType;



#pragma region 线性表的顺序表示和实现

#define LIST_INIT_SIZE 100 //初始分配量
#define LISTINCREMENT  10  //分配增量

/*用数组来描述（数组下标从'0'开始，线性表下标从'1'开始）*/
//------线性表的动态分配顺序存储结构------
typedef struct 
{
	ElemType* elem;//存储空间基址
	int length;//当前长度
	int listsize;//存储容量
}SqList;


//初始化线性表
Status ListInit_Sq(SqList& L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
	{
		exit(OVERFLOW);//存储分配失败
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

//在线性表中第i个位置前插入新的元素e
Status ListInsert_Sq(SqList& L, int i, ElemType e)
{
	if (i<1 || i>L.length+1)
	{
		return ERROR;//i值不合法
	}
	if (L.length>=L.listsize)//当前存储空间已满，增加分配
	{
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));//重新分配内存空间
		if (!newbase)
		{
			exit(OVERFLOW);//存储分配失败
		}
		L.elem = newbase;//新基址
		L.listsize += LISTINCREMENT;
	}
	ElemType* q = L.elem + (i - 1);//获取第i个元素的地址

	for (ElemType*p=L.elem+(L.length-1); p>=q; --p)
	{
		*(p + 1) =* p;//第i个元素及之后的元素右移
	}
	*q = e;//插入元素
	++L.length;
	return OK;
}

//在线性表中删除第i个元素，并用e返回
Status ListDelete_Sq(SqList& L, int i, ElemType& e)
{
	if (i<1 || i>L.length + 1)
	{
		return ERROR;//i值不合法
	}
	ElemType *p =&( L.elem[i - 1]);//被删除元素的地址
	e = *p;
	ElemType* q = &(L.elem[L.length - 1]);//表尾元素的地址
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;//被删除元素之后的元素左移
	}
	--L.length;
	return OK;
}

//打印线性表
void ListShow_Sq(SqList L)
{
	for (int i = 0; i < L.length; i++)
	{
		cout << L.elem[i] << endl;
	}
}

#pragma endregion

#pragma region 线性表的单链表的表示和实现，此部分算法都为带头结点的链表

//------线性表的单链表存储结构-----用结构指针来表示
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode,*LinkList;

//头插法创建单链表(逆位序)
void LinkList_Create_Head(LinkList& L,int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = 0; i < 10; i++)
	{		
		LinkList p= (LinkList)malloc(sizeof(LNode));
		cout << "请输入数字：";
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}




//尾插法创建单链表
void LinkList_Create_Tail(LinkList& L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LinkList tail = L;//定义一个尾指针，永远指向尾结点
	for (int i = 0; i < 10; i++)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		cout << "请输入数字：";
		cin >> p->data;
		p->next = NULL;
		tail->next = p;
		tail = p;//永远指向尾结点
	}
}



//查找第i个元素，并用e返回
Status LinkList_GetElem(LinkList L, int i, ElemType& e)
{
	LinkList p = L->next;//p指向第一个结点
	int k = 1;
	while (p && k<i)//当k=i时或者p空时退出循环
	{
		p = p->next;
		k++;
	}
	if (!p || k>i)//第i个元素不存在
	{
		return ERROR;
	}
	e = p->data;
	return OK;
}






//在第i个元素前插入e
Status LinkList_Insert(LinkList& L, int i, ElemType e)
{
	LinkList p = L;
	int k = 0;

	while (p && k<i-1)//找到第i-1个结点
	{
		p = p->next;
		k++;
	}
	LinkList s = (LinkList)malloc(sizeof(LNode));
	if (!s)
	{
		exit(OVERFLOW);
	}
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
//删除第i个位置的结点
Status LinkList_Delete(LinkList& L, int i, ElemType& e)
{
	LinkList p = L;
	int k = 0;

	while (p && k < i - 1)//找到第i-1个结点
	{
		p = p->next;
		k++;
	}
	LinkList q = p->next;
	p->next = q->next;	
	e=q->data;
	free(q);	
	return OK;
}


//打印单链表
void LinkListShow(LinkList L)
{
	LinkList p = L->next;
	while (p)
	{
		cout << p->data << endl;
		p = p->next;
	}
}
#pragma endregion

#pragma region 循环链表
/*
一般和单链表类似，只是表中最后一个结点的指针域指向头结点。
有时为了操作方便，不设置头指针，设置尾指针。可以简化诸如合并表之类的操作。
*/

//定义尾指针 
typedef LinkList LinkListLast;

//尾插法创建只含尾指针的循环链表
void LinkListLast_Create_Tail(LinkListLast& tail, int n)
{//tail为尾指针
	tail = (LinkListLast)malloc(sizeof(LNode));
	tail->next = tail;
	for (int i = 0; i < 10; i++)
	{
		LinkListLast p = (LinkListLast)malloc(sizeof(LNode));
		cout << "请输入数字：";
		cin >> p->data;
		p->next = tail->next;//p的指针域指向头结点
		tail->next = p;//原先的尾结点指针域指向p
		tail = p;//尾指针指向尾结点
	}
}

#pragma endregion

#pragma region 双向链表

//-----线性表的双向链表存储结构------
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode* prior;
	struct DuLNode* next;
}DuLNode,*DuLinkList;

#pragma endregion

#pragma region 静态单链表
/*
* 用一维数组表示
*/



#pragma endregion

#pragma region 约瑟夫环问题

typedef struct JosephLNode
{
	struct JosephLNode* next;
	int No;//编号
	int Password;//密码

}JosephLNode,*JosephList;

//创建一个约瑟夫环链表（采用只有尾指针的循环单链表，无头结点）
void Create_JosephList(JosephList& jl,int n)
{
	//创建第一个结点
	jl = (JosephList)malloc(sizeof(JosephLNode));
	jl->No = 1;
	cout << "输入密码：";
	cin >> jl->Password;
	jl->next = jl;
	//创建后面的结点
	for (int i = 2; i <= n; i++)
	{
		JosephList p = (JosephList)malloc(sizeof(JosephLNode));
		p->No = i;
		cout << "输入密码：";
		cin>>p->Password;
		p->next = jl->next;//p指向开始结点
		jl->next = p;
		jl = p;//jl始终指向尾结点
	}
}

//约瑟夫环输出
void PlayingJoseph(JosephList jl, int n,int m)
{//m为初始密码,n为约瑟夫结点个数
	JosephList pre=jl;//始终指向当前结点前一个
	JosephList p=jl->next;//始终指向当前结点
	int k = 1;//计数
	while (n>1)
	{
		if (k==m)
		{
			cout << p->No<<endl;//输出编号
			m = p->Password;
			n--;
			pre->next = p->next;
			free(p);
			p = pre->next;
			k = 1;
		}
		else
		{
			k++;
			pre = p;
			p = p->next;
		}
	}
	cout << p->No << endl;
}

#pragma endregion


int main1()
{
	/*SqList q;
	ListInit_Sq(q);
	for (int i = 0; i < 10; i++)
	{
		ListInsert_Sq(q, i + 1, i);
	}
	ListInsert_Sq(q, 3, 100);
	ListShow_Sq(q);
	ElemType e;
	ListDelete_Sq(q, 3, e);
	ListShow_Sq(q);*/

	/*LinkList l;
	LinkList_Create_Tail(l, 10);
	
	ElemType e;
	LinkList_GetElem(l, 4, e);
	LinkList_Insert(l, 5, 100);
	LinkListShow(l);
	LinkList_Delete(l, 6, e);
	LinkListShow(l);*/

	/*LinkListLast l;
	LinkListLast_Create_Tail(l, 10);*/

	JosephList jl;
	Create_JosephList(jl, 5);
	PlayingJoseph(jl, 5, 3);


	system("pause");
	return 0;
}