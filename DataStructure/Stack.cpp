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


#define STACK_INIT_SIZE  100  //存储空间初始分配量
#define STACKINCREMENT   10   //存储空间分配增量
typedef int SElemType;


//-------栈的顺序存储表示------
typedef struct
{
	SElemType* base;//栈底指针，在构造前和销毁后值为NULL
	SElemType* top;//栈顶指针,栈顶元素的下一个位置上
	int stacksize;//当前已分配的存储空间
}SqStack;

//初始化
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

//入栈
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
	*sq.top++ = e;//先赋值再加一
	return OK;
}

//出栈
Status PopStack(SqStack& sq, SElemType& e)
{
	if (sq.base==sq.top)
	{
		return ERROR;
	}
	e = *--sq.top;//先减一再赋值
	return OK;
}


//获取栈顶元素
Status GetTop(SqStack sq, SElemType& e)
{
	if (sq.base == sq.top)
	{
		return ERROR;
	}
	e = *sq.top--;//先减一再赋值
	return OK;
}

//运算符优先级比较
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






