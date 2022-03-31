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
typedef int QElemType;
#define MAXQSIZE 100//�����г���

//----ѭ�����д洢��ʾ----
typedef struct
{
	QElemType* base;
	int front;
	int rear;
}SqQueue;

//��ʼ��
void InitSqQueue(SqQueue& Q)
{
	Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base)
	{
		exit(OVERFLOW);
	}
	Q.front = Q.rear = 0;

}

//���г���
int QueueLength(SqQueue q)
{
	return (q.rear - q.front + MAXQSIZE) % MAXQSIZE;
}

int EnQueue(SqQueue& q, QElemType e)
{
	if ((q.rear+1)%MAXQSIZE==q.front)
	{
		return ERROR;//������
	}
	q.base[q.rear] = e;
	q.rear = (q.rear + 1) % MAXQSIZE;
	return OK;
}

int DeQueue(SqQueue& q, QElemType e)
{
	if (q.rear == q.front)
	{
		return ERROR;//���п�
	}
	e = q.base[q.front];
	q.front = (q.front + 1) % MAXQSIZE;
	return OK;
}

int main5()
{
	return 0;
}