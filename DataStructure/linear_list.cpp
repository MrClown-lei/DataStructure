#include<iostream>
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
//��������Ԫ������
typedef int ElemType;



#pragma region ���Ա��˳���ʾ��ʵ��

#define LIST_INIT_SIZE 100 //��ʼ������
#define LISTINCREMENT  10  //��������

/*�������������������±��'0'��ʼ�����Ա��±��'1'��ʼ��*/
//------���Ա�Ķ�̬����˳��洢�ṹ------
typedef struct 
{
	ElemType* elem;//�洢�ռ��ַ
	int length;//��ǰ����
	int listsize;//�洢����
}SqList;


//��ʼ�����Ա�
Status ListInit_Sq(SqList& L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
	{
		exit(OVERFLOW);//�洢����ʧ��
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

//�����Ա��е�i��λ��ǰ�����µ�Ԫ��e
Status ListInsert_Sq(SqList& L, int i, ElemType e)
{
	if (i<1 || i>L.length+1)
	{
		return ERROR;//iֵ���Ϸ�
	}
	if (L.length>=L.listsize)//��ǰ�洢�ռ����������ӷ���
	{
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));//���·����ڴ�ռ�
		if (!newbase)
		{
			exit(OVERFLOW);//�洢����ʧ��
		}
		L.elem = newbase;//�»�ַ
		L.listsize += LISTINCREMENT;
	}
	ElemType* q = L.elem + (i - 1);//��ȡ��i��Ԫ�صĵ�ַ

	for (ElemType*p=L.elem+(L.length-1); p>=q; --p)
	{
		*(p + 1) =* p;//��i��Ԫ�ؼ�֮���Ԫ������
	}
	*q = e;//����Ԫ��
	++L.length;
	return OK;
}

//�����Ա���ɾ����i��Ԫ�أ�����e����
Status ListDelete_Sq(SqList& L, int i, ElemType& e)
{
	if (i<1 || i>L.length + 1)
	{
		return ERROR;//iֵ���Ϸ�
	}
	ElemType *p =&( L.elem[i - 1]);//��ɾ��Ԫ�صĵ�ַ
	e = *p;
	ElemType* q = &(L.elem[L.length - 1]);//��βԪ�صĵ�ַ
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;//��ɾ��Ԫ��֮���Ԫ������
	}
	--L.length;
	return OK;
}

//��ӡ���Ա�
void ListShow_Sq(SqList L)
{
	for (int i = 0; i < L.length; i++)
	{
		cout << L.elem[i] << endl;
	}
}

#pragma endregion

#pragma region ���Ա�ĵ�����ı�ʾ��ʵ�֣��˲����㷨��Ϊ��ͷ��������

//------���Ա�ĵ�����洢�ṹ-----�ýṹָ������ʾ
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode,*LinkList;

//ͷ�巨����������(��λ��)
void LinkList_Create_Head(LinkList& L,int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = 0; i < 10; i++)
	{		
		LinkList p= (LinkList)malloc(sizeof(LNode));
		cout << "���������֣�";
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}




//β�巨����������
void LinkList_Create_Tail(LinkList& L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LinkList tail = L;//����һ��βָ�룬��Զָ��β���
	for (int i = 0; i < 10; i++)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		cout << "���������֣�";
		cin >> p->data;
		p->next = NULL;
		tail->next = p;
		tail = p;//��Զָ��β���
	}
}



//���ҵ�i��Ԫ�أ�����e����
Status LinkList_GetElem(LinkList L, int i, ElemType& e)
{
	LinkList p = L->next;//pָ���һ�����
	int k = 1;
	while (p && k<i)//��k=iʱ����p��ʱ�˳�ѭ��
	{
		p = p->next;
		k++;
	}
	if (!p || k>i)//��i��Ԫ�ز�����
	{
		return ERROR;
	}
	e = p->data;
	return OK;
}






//�ڵ�i��Ԫ��ǰ����e
Status LinkList_Insert(LinkList& L, int i, ElemType e)
{
	LinkList p = L;
	int k = 0;

	while (p && k<i-1)//�ҵ���i-1�����
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
//ɾ����i��λ�õĽ��
Status LinkList_Delete(LinkList& L, int i, ElemType& e)
{
	LinkList p = L;
	int k = 0;

	while (p && k < i - 1)//�ҵ���i-1�����
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


//��ӡ������
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

#pragma region ѭ������
/*
һ��͵��������ƣ�ֻ�Ǳ������һ������ָ����ָ��ͷ��㡣
��ʱΪ�˲������㣬������ͷָ�룬����βָ�롣���Լ�����ϲ���֮��Ĳ�����
*/

//����βָ�� 
typedef LinkList LinkListLast;

//β�巨����ֻ��βָ���ѭ������
void LinkListLast_Create_Tail(LinkListLast& tail, int n)
{//tailΪβָ��
	tail = (LinkListLast)malloc(sizeof(LNode));
	tail->next = tail;
	for (int i = 0; i < 10; i++)
	{
		LinkListLast p = (LinkListLast)malloc(sizeof(LNode));
		cout << "���������֣�";
		cin >> p->data;
		p->next = tail->next;//p��ָ����ָ��ͷ���
		tail->next = p;//ԭ�ȵ�β���ָ����ָ��p
		tail = p;//βָ��ָ��β���
	}
}

#pragma endregion

#pragma region ˫������

//-----���Ա��˫������洢�ṹ------
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode* prior;
	struct DuLNode* next;
}DuLNode,*DuLinkList;

#pragma endregion

#pragma region ��̬������
/*
* ��һά�����ʾ
*/



#pragma endregion

#pragma region Լɪ������

typedef struct JosephLNode
{
	struct JosephLNode* next;
	int No;//���
	int Password;//����

}JosephLNode,*JosephList;

//����һ��Լɪ����������ֻ��βָ���ѭ����������ͷ��㣩
void Create_JosephList(JosephList& jl,int n)
{
	//������һ�����
	jl = (JosephList)malloc(sizeof(JosephLNode));
	jl->No = 1;
	cout << "�������룺";
	cin >> jl->Password;
	jl->next = jl;
	//��������Ľ��
	for (int i = 2; i <= n; i++)
	{
		JosephList p = (JosephList)malloc(sizeof(JosephLNode));
		p->No = i;
		cout << "�������룺";
		cin>>p->Password;
		p->next = jl->next;//pָ��ʼ���
		jl->next = p;
		jl = p;//jlʼ��ָ��β���
	}
}

//Լɪ�����
void PlayingJoseph(JosephList jl, int n,int m)
{//mΪ��ʼ����,nΪԼɪ�������
	JosephList pre=jl;//ʼ��ָ��ǰ���ǰһ��
	JosephList p=jl->next;//ʼ��ָ��ǰ���
	int k = 1;//����
	while (n>1)
	{
		if (k==m)
		{
			cout << p->No<<endl;//������
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