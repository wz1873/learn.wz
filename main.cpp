#include<iostream>
using namespace std;
#define MAXNUM 100
typedef struct SListStr
{
	int data;

	struct SListStr* next;

}SList,*PtrSList;

typedef struct ListStr
{
	int blockNumber;//块数,最多分为一百块
	
	SList* arr[MAXNUM];
}*List;

void InitList(List& L)
{
	L = (List)malloc(sizeof(ListStr));
	if (!L)return;
	L->blockNumber = 0;
	return;
}

void InsetSList(PtrSList& SL, int n)
{
	PtrSList p = (PtrSList)malloc(sizeof(SListStr));
	p->data = n;
	p->next = SL->next;
	SL->next = p;
	return;
}

int SearchMax(PtrSList &PS)
{
	int max=-1;
	PtrSList ps=PS;
	while (ps != NULL)
	{
		if (ps->data > max)
			max = ps->data;
		ps = ps->next;
	}
	return max;
}

int SearchMin(PtrSList& PS)
{
	int min = SearchMax(PS);
	PtrSList ps = PS;
	while (ps != NULL)
	{
		if (ps->data < min&&ps->data>=0)
			min = ps->data;
		ps = ps->next;
	}
	return min;
}

List CreatList(List &L,int num)
{
	L->blockNumber = num;
	int i = 1,data,blockInerMax, blockInerMaxLast, blockInerMin, blockInerMinLast;
	for (; i <= num; i++)
	{
		L->arr[i - 1] = (PtrSList)malloc(sizeof(SListStr));
		if (!L->arr[i - 1])return NULL;
		L->arr[i - 1]->data = -1;
		L->arr[i - 1]->next = NULL;
		cout << "请输入第" << i << "块数据(输入-1结束输入)：" << endl;
		while (cin >> data && data != -1)
		{
			InsetSList(L->arr[i - 1], data);
		}
		if (i == 1)
		{
			blockInerMax = SearchMax(L->arr[i - 1]);
			blockInerMin = SearchMin(L->arr[i - 1]);
		}
		else
		{
			blockInerMaxLast = blockInerMax;
			blockInerMinLast = blockInerMin;
			blockInerMax = SearchMax(L->arr[i - 1]);
			blockInerMin = SearchMin(L->arr[i - 1]);
			if (blockInerMaxLast >= blockInerMin)
			{
				cout << "输入不合法，请输入比上一块都大的数字" << endl;
				cout << "请输入第" << i << "块数据(输入-1结束输入)：" << endl;
				while (cin >> data && data != -1)
				{
					InsetSList(L->arr[i - 1], data);
				}
			}
		}
	}

	return L;
}

int SearchNumber(PtrSList& PS, int x)
{
	int i = 1;
	while (PS)
	{
		if (PS->data == x)
		{
			return i+1;
		}
		else
		{
			i++;
			PS = PS->next;
		}
	}
	return -1;
}

void SearchBlock(List& L, int x,int block,int number)
{
	int i = 0;
	PtrSList ps = L->arr[0];
	for (; i < L->blockNumber; i++)
	{
		ps = L->arr[i];
		int max = SearchMax(ps);
		if (max < x)
			ps = ps->next;
		else
		{
			block = i+1;
			PtrSList ptr = ps;
			number=SearchNumber(ptr, x);
			if (number != -1)
			{
				cout << "这个数字在第 " << block << "块 " << "第 " << number << "个" << endl;
				return;
			}
			else
			{
				cout << "未找到这个数字" << endl;
				return;
			}
		}
	}
}

int main()
{
	List L=NULL;
	InitList(L);//一开始是没有初始化的，会出现修改数值不合法的情况，指针必须经过初始化之后才可以正常使用
	int num;
	int x;
	int block=-1, number=-1;//也需要初始化否则报错
	cout << "请输入分块数目：注意后一块所有数据大于前一块且都为正数：" << endl;
	    cin >> num;
	    CreatList(L, num);
	    cout << "请输入需要查找的数字：" << endl;
		    cin >> x;
			SearchBlock(L, x, block, number);
	return 0;
}

/*
3
1 3 2 -1
6 9 8 -1
89 65 43 -1

*/