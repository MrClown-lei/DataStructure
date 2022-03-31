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


//ֱ�Ӳ�������
void InsertSort(SqList& L)
{
	for (int i = 2; i <= L.length; i++)
	{
		if (L.elem[i]<L.elem[i-1])
		{
			L.elem[0] = L.elem[i];//0��Ԫ����Ϊ����λ��������Ԫ�رȽ�
			L.elem[i] = L.elem[i - 1];//����һλ

			int j = 0;
			for ( j=i-2 ; L.elem[0] < L.elem[j]; j--)
			{
				L.elem[j + 1] = L.elem[j];//����һλ
			}
			L.elem[j + 1] = L.elem[0];
		}		
	}
}


//�۰��������
void BinaryInsertSort(SqList& L)
{
	for (int i = 2; i <= L.length; i++)
	{
		L.elem[0] = L.elem[i];//���������Ԫ��
		int low = 1, high = i - 1;
		while (low<=high)
		{
			int mid = (low + high) / 2;
			if (L.elem[0] < L.elem[mid])
			{
				high = mid - 1;//�۰�����ڵͰ���
			}
			else
			{
				low = mid + 1;//�۰�����ڸ߰���
			}
		}

		for (int j = i - 1; j>=high+1; j--)//high+1Ϊ����λ��
		{
			L.elem[j + 1] = L.elem[j];//����һλ,���������λ
		}
		L.elem[high + 1] = L.elem[0]; //����Ԫ��

	}
}


//ϣ����������
void ShellInsert(SqList& L,int dk)
{
	for (int i = dk+1; i <= L.length; i++)
	{
		if (L.elem[i] < L.elem[i - dk])
		{
			L.elem[0] = L.elem[i];//0��Ԫ����Ϊ����λ��������Ԫ�رȽ�
			int j = 0;
			for (j = i - dk; j>0 && L.elem[0] < L.elem[j]; j-=dk)
			{
				L.elem[j + dk] = L.elem[j];//����һλ
			}
			L.elem[j + dk] = L.elem[0];
		}
	}
}

//����������dlta[0..t-1]��˳�����ϣ������
void ShellSort(SqList& L, int dlta[], int t)
{
	for (int i = 0; i < t; i++)
	{
		ShellInsert(L, dlta[i]);
	}
}

//ð������
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


//�����Ϊ�������������У�����������λ��
int Partion(SqList& L, int low, int high)
{
	L.elem[0] = L.elem[low];//��һ��Ԫ�ؼ�¼����λ��
	int pivotkey = L.elem[low];//��һ��Ԫ����Ϊ����Ԫ��
	while (low < high)
	{
		while (low < high && L.elem[high]>=pivotkey)
		{
			high--;
		}
		L.elem[low] = L.elem[high];//��������С��Ԫ���ƶ����Ͷ�

		while (low < high && L.elem[low] <= pivotkey)
		{
			low--;
		}
		L.elem[high] = L.elem[low];//����������Ԫ���ƶ����߶�
	}
	L.elem[low] = L.elem[0];//������Ԫ�ؼ�¼��λ
	return low;//��������λ��
}
//��������(�ݹ���ʽ)
void QuickSort(SqList& L, int low, int high)
{
	if (low<high)
	{
		int pivotloc = Partion(L, low, high);//����һ��Ϊ����pivotlocΪ����λ��
		QuickSort(L, low, pivotloc - 1);//�Ե��ֱ�ݹ�����
		QuickSort(L, pivotloc+1, high);//�Ը��ֱ�ݹ�����

	}
}

//�����㷨��չ�������������ƶ���ż��ǰ�棩
void Move(int nums[], int length)
{
	int low = 0, high = length - 1;
	while (low<high)
	{
		while (low<high && nums[low]%2!=0)//��ǰ�����ҵ�һ��ż��
		{
			low++;
		}
		while (low < high && nums[high] % 2 != 1)//�Ӻ���ǰ�ҵ�һ������
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


//��ѡ������
void SelectSort(SqList& L)
{
	for (int i = 1; i < L.length; i++)
	{
		int j = 0;
		for (int k = i+1,j=i; k < L.length; k++)//ѡ����С��Ԫ���±�
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

typedef SqList HeapType;//�Ѳ���˳��洢��ʾ
//������ɸѡ�㷨����֪H.elem[s...m]�г�H.elem[s]֮�������Ѷ��壬����������H.elem[s]��ʹ֮��Ϊһ��С����
void HeapAdjust(HeapType& H, int s, int m)
{
	int rc = H.elem[s];
	for (int j = 2*s; j <= m; j*=2)//����ֵ��С�ĺ��ӽ������ɸѡ
	{
		if (j<m && H.elem[j] > H.elem[j+1])
		{
			++j;//jΪ���ӽ�Сֵ���±�
		}
		if (rc < H.elem[j])
		{
			break;//����Ѷ��壬ֱ�ӷ���
		}
		H.elem[s] = H.elem[j];//��С�ĺ��ӽ�㽻�����������
		s = j;//s�±�Ϊ��С���ӽ���±�
	}
	H.elem[s] = rc;//rcӦ�����λ����s��
}

//��˳�����ж�����
void HeapSort(HeapType& H)
{
	for (int i = H.length/2; i > 0; i--)//������С����
	{
		HeapAdjust(H, i, H.length);
	}

	for (int i = H.length ; i > 1; i--)
	{
		//����ǰ�Ѷ�Ԫ�غ�H.elem[i]�����һ����¼������
		int temp = H.elem[1];
		H.elem[1] = H.elem[i];
		H.elem[i] = temp;

		HeapAdjust(H, 1, i-1);//��H.elem[1...i-1]���µ���ΪС����
	}

	//��ʱ˳���Ϊ����
}

//�鲢�㷨���Ĳ���
//��������ΪL.elem[i...m]��L.elem[m+1...n]
void Merge(SqList &L,int i,int m,int n)
{//���븨����temp
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

//�鲢�ݹ��㷨
//��L.elem[s...t]�鲢����
void MSort(SqList &L,int s,int t)
{
	if (s<t)
	{
		int m = (s + t) / 2;
		MSort(L, s, m);//�ݹ�Ĺ鲢���ӱ�
		MSort(L, m+1, t);//�ݹ�Ĺ鲢���ӱ�
		Merge(L, s, m, t);//�鲢�����ӱ�
	}
}

//��˳���L���鲢����
void MergeSort(SqList& L)
{
	MSort(L, 1, L.length);
}

























