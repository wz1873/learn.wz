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
	int blockNumber;//����,����Ϊһ�ٿ�
	
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
		cout << "�������" << i << "������(����-1��������)��" << endl;
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
				cout << "���벻�Ϸ������������һ�鶼�������" << endl;
				cout << "�������" << i << "������(����-1��������)��" << endl;
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
				cout << "��������ڵ� " << block << "�� " << "�� " << number << "��" << endl;
				return;
			}
			else
			{
				cout << "δ�ҵ��������" << endl;
				return;
			}
		}
	}
}

int main()
{
	List L=NULL;
	InitList(L);//һ��ʼ��û�г�ʼ���ģ�������޸���ֵ���Ϸ��������ָ����뾭����ʼ��֮��ſ�������ʹ��
	int num;
	int x;
	int block=-1, number=-1;//Ҳ��Ҫ��ʼ�����򱨴�
	cout << "������ֿ���Ŀ��ע���һ���������ݴ���ǰһ���Ҷ�Ϊ������" << endl;
	    cin >> num;
	    CreatList(L, num);
	    cout << "��������Ҫ���ҵ����֣�" << endl;
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