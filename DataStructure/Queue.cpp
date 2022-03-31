#include<iostream>
#include<string>
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
typedef int QElemType;
#define MAXQSIZE 100//最大队列长度

//----循环队列存储表示----
typedef struct
{
	QElemType* base;
	int front;
	int rear;
}SqQueue;

//初始化
void InitSqQueue(SqQueue& Q)
{
	Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base)
	{
		exit(OVERFLOW);
	}
	Q.front = Q.rear = 0;

}

//队列长度
int QueueLength(SqQueue q)
{
	return (q.rear - q.front + MAXQSIZE) % MAXQSIZE;
}

int EnQueue(SqQueue& q, QElemType e)
{
	if ((q.rear+1)%MAXQSIZE==q.front)
	{
		return ERROR;//队列满
	}
	q.base[q.rear] = e;
	q.rear = (q.rear + 1) % MAXQSIZE;
	return OK;
}

int DeQueue(SqQueue& q, QElemType e)
{
	if (q.rear == q.front)
	{
		return ERROR;//队列空
	}
	e = q.base[q.front];
	q.front = (q.front + 1) % MAXQSIZE;
	return OK;
}

int main5()
{
	return 0;
}