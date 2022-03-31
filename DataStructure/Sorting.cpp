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


//直接插入排序
void InsertSort(SqList& L)
{
	for (int i = 2; i <= L.length; i++)
	{
		if (L.elem[i]<L.elem[i-1])
		{
			L.elem[0] = L.elem[i];//0号元素作为辅助位，和其他元素比较
			L.elem[i] = L.elem[i - 1];//后移一位

			int j = 0;
			for ( j=i-2 ; L.elem[0] < L.elem[j]; j--)
			{
				L.elem[j + 1] = L.elem[j];//后移一位
			}
			L.elem[j + 1] = L.elem[0];
		}		
	}
}


//折半插入排序
void BinaryInsertSort(SqList& L)
{
	for (int i = 2; i <= L.length; i++)
	{
		L.elem[0] = L.elem[i];//保存待插入元素
		int low = 1, high = i - 1;
		while (low<=high)
		{
			int mid = (low + high) / 2;
			if (L.elem[0] < L.elem[mid])
			{
				high = mid - 1;//折半插入在低半区
			}
			else
			{
				low = mid + 1;//折半插入在高半区
			}
		}

		for (int j = i - 1; j>=high+1; j--)//high+1为插入位置
		{
			L.elem[j + 1] = L.elem[j];//后移一位,留出插入空位
		}
		L.elem[high + 1] = L.elem[0]; //插入元素

	}
}


//希尔插入排序
void ShellInsert(SqList& L,int dk)
{
	for (int i = dk+1; i <= L.length; i++)
	{
		if (L.elem[i] < L.elem[i - dk])
		{
			L.elem[0] = L.elem[i];//0号元素作为辅助位，和其他元素比较
			int j = 0;
			for (j = i - dk; j>0 && L.elem[0] < L.elem[j]; j-=dk)
			{
				L.elem[j + dk] = L.elem[j];//后移一位
			}
			L.elem[j + dk] = L.elem[0];
		}
	}
}

//按增量序列dlta[0..t-1]对顺序表做希尔排序
void ShellSort(SqList& L, int dlta[], int t)
{
	for (int i = 0; i < t; i++)
	{
		ShellInsert(L, dlta[i]);
	}
}

//冒泡排序
void BubbleSort(SqList& L)
{
	for (int i = 1 ; i < L.length-1 ; i++)
	{		
		for (int j = 1; j < L.length-i-1; j++)
		{
			if (L.elem[j]>L.elem[j+1])
			{
				L.elem[0] = L.elem[j];
				L.elem[j] = L.elem[j + 1];
				L.elem[j+1] = L.elem[0];
			}
		}
	}
}


//将表分为左右两个子序列，并返回枢轴位置
int Partion(SqList& L, int low, int high)
{
	L.elem[0] = L.elem[low];//第一个元素记录枢轴位置
	int pivotkey = L.elem[low];//第一个元素作为枢轴元素
	while (low < high)
	{
		while (low < high && L.elem[high]>=pivotkey)
		{
			high--;
		}
		L.elem[low] = L.elem[high];//将比枢轴小的元素移动到低端

		while (low < high && L.elem[low] <= pivotkey)
		{
			low--;
		}
		L.elem[high] = L.elem[low];//将比枢轴大的元素移动到高端
	}
	L.elem[low] = L.elem[0];//将枢轴元素记录到位
	return low;//返回枢轴位置
}
//快速排序(递归形式)
void QuickSort(SqList& L, int low, int high)
{
	if (low<high)
	{
		int pivotloc = Partion(L, low, high);//将表一分为二，pivotloc为枢轴位置
		QuickSort(L, low, pivotloc - 1);//对低字表递归排序
		QuickSort(L, pivotloc+1, high);//对高字表递归排序

	}
}

//快排算法拓展（将所有奇数移动到偶数前面）
void Move(int nums[], int length)
{
	int low = 0, high = length - 1;
	while (low<high)
	{
		while (low<high && nums[low]%2!=0)//从前往后找第一个偶数
		{
			low++;
		}
		while (low < high && nums[high] % 2 != 1)//从后往前找第一个奇数
		{
			high--;
		}
		if (low<high)
		{
			int temp = nums[high];
			nums[high] = nums[low];
			nums[low] = temp;
			low++;
			high--;
		}
	}
}


//简单选择排序
void SelectSort(SqList& L)
{
	for (int i = 1; i < L.length; i++)
	{
		int j = 0;
		for (int k = i+1,j=i; k < L.length; k++)//选择最小的元素下标
		{
			if (L.elem[k]<L.elem[j])
			{
				j = k;
			}
		}
		if (j!=i)
		{
			int temp = L.elem[j];
			L.elem[j] = L.elem[i];
			L.elem[i] = temp;
		}
	}
}

typedef SqList HeapType;//堆采用顺序存储表示
//堆排序筛选算法，已知H.elem[s...m]中除H.elem[s]之外均满足堆定义，本函数调整H.elem[s]，使之成为一个小顶堆
void HeapAdjust(HeapType& H, int s, int m)
{
	int rc = H.elem[s];
	for (int j = 2*s; j <= m; j*=2)//沿着值较小的孩子结点向下筛选
	{
		if (j<m && H.elem[j] > H.elem[j+1])
		{
			++j;//j为孩子较小值的下标
		}
		if (rc < H.elem[j])
		{
			break;//满足堆定义，直接返回
		}
		H.elem[s] = H.elem[j];//较小的孩子结点交换到父结点上
		s = j;//s下标为较小孩子结点下标
	}
	H.elem[s] = rc;//rc应插入的位置在s处
}

//对顺序表进行堆排序
void HeapSort(HeapType& H)
{
	for (int i = H.length/2; i > 0; i--)//将表建成小顶堆
	{
		HeapAdjust(H, i, H.length);
	}

	for (int i = H.length ; i > 1; i--)
	{
		//将当前堆顶元素和H.elem[i]（最后一个记录）交换
		int temp = H.elem[1];
		H.elem[1] = H.elem[i];
		H.elem[i] = temp;

		HeapAdjust(H, 1, i-1);//将H.elem[1...i-1]重新调整为小顶堆
	}

	//此时顺序表为逆序
}

//归并算法核心操作
//有序序列为L.elem[i...m]和L.elem[m+1...n]
void Merge(SqList &L,int i,int m,int n)
{//引入辅助表temp
	SqList temp;
	temp.elem = new ElemType;
	int b = i;
	int j = m + 1;
	int k = 1;
	while (i <= m && j <= n)
	{
		if (L.elem[i] < L.elem[j])
		{
			temp.elem[k++] = L.elem[i++];
		}
		else
		{
			temp.elem[k++] = L.elem[j++];
		}
	}
	while (i<=m)
	{
		temp.elem[k++] = L.elem[i++];
	}
	while (j <= n)
	{
		temp.elem[k++] = L.elem[j++];
	}
	k = 1;
	while (b<=n)
	{
		L.elem[b++] = temp.elem[k++];
	}
}

//归并递归算法
//将L.elem[s...t]归并排序
void MSort(SqList &L,int s,int t)
{
	if (s<t)
	{
		int m = (s + t) / 2;
		MSort(L, s, m);//递归的归并左子表
		MSort(L, m+1, t);//递归的归并右子表
		Merge(L, s, m, t);//归并两个子表
	}
}

//对顺序表L做归并排序
void MergeSort(SqList& L)
{
	MSort(L, 1, L.length);
}

























