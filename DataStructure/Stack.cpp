#include<iostream>
#include<string>
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


#define STACK_INIT_SIZE  100  //�洢�ռ��ʼ������
#define STACKINCREMENT   10   //�洢�ռ��������
typedef int SElemType;


//-------ջ��˳��洢��ʾ------
typedef struct
{
	SElemType* base;//ջ��ָ�룬�ڹ���ǰ�����ٺ�ֵΪNULL
	SElemType* top;//ջ��ָ��,ջ��Ԫ�ص���һ��λ����
	int stacksize;//��ǰ�ѷ���Ĵ洢�ռ�
}SqStack;

//��ʼ��
Status InitStack(SqStack& sq)
{
	sq.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!sq.base)
	{
		exit(OVERFLOW);
	}
	sq.top = sq.base;
	sq.stacksize = STACK_INIT_SIZE;
	return OK;
}

//��ջ
Status PushStack(SqStack& sq, SElemType e)
{
	if (sq.top-sq.base == sq.stacksize)
	{
		sq.base= (SElemType*)realloc(sq.base,(sq.stacksize+STACKINCREMENT) * sizeof(SElemType));
		if (!sq.base)
		{
			exit(OVERFLOW);
		}
		sq.top = sq.base + sq.stacksize;
		sq.stacksize += STACKINCREMENT;
	}
	*sq.top++ = e;//�ȸ�ֵ�ټ�һ
	return OK;
}

//��ջ
Status PopStack(SqStack& sq, SElemType& e)
{
	if (sq.base==sq.top)
	{
		return ERROR;
	}
	e = *--sq.top;//�ȼ�һ�ٸ�ֵ
	return OK;
}


//��ȡջ��Ԫ��
Status GetTop(SqStack sq, SElemType& e)
{
	if (sq.base == sq.top)
	{
		return ERROR;
	}
	e = *sq.top--;//�ȼ�һ�ٸ�ֵ
	return OK;
}

//��������ȼ��Ƚ�
char Precede(char theta1, char theta2)
{
	if ((theta1 == '(' && theta2 == ')') || (theta1 == '#' && theta2 == '#'))
		return '=';
	else if (theta1 == '(' || theta1 == '#' || theta2 == '(' || (theta1 == '+' || theta1 == '-') && (theta2 == '*' || theta2 == '/'))
		return '<';
	else
		return '>';
}







int main2()
{



	return 0;
}






