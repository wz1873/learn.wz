#include<iostream>
using namespace std;

typedef struct Node
{
	int data;
	struct Node* next;
}Node,*LinkList;

int InitList(LinkList& L)
{
	L = (LinkList)malloc(sizeof(Node));
	if (!L)return 0;
	L->data = 0;
	L->next = NULL;
	return 1;
}

void InsertList(LinkList& L,int e)
{
	LinkList p = (LinkList)malloc(sizeof(Node));
	p->data = e;
	p->next = NULL;
	L->next= p;
	L = p;
}

void DeleteList(LinkList& L, int n)
{
	int num = 1;
	LinkList p = L->next,q=L->next;
	while (num < n && p)
	{
		num++;
		q = p;
		p = p->next;
	}
	if (!p)
		cout << "this element isn't found" << endl;
	else
	{
		q->next = p->next;
		free(p);
	}
}

LinkList CombineList1(LinkList& L1, LinkList& L2)//长链表接在短链表后面
{
	LinkList P1 = L1, P2 = L2;
	while (P1->next&& P2->next)//用next是否为空判断是否最后一个结点
	{
		P1 = P1->next;
		P2 = P2->next;
	}
	if (!P1->next)
	{
		P1->next = L2; return L1;
	}
	else
	{
		P2->next = L1; return L2;
	}
}

LinkList CombineList2(LinkList& L1, LinkList& L2)
{
	LinkList p=L1,p1 = L1->next, p2 = L2->next;
	while (p2)
	{
		while (p1!=NULL&&p2!=NULL)//先判断NULL再决定要不要访问data
		{
			if (p1->data < p2->data)
			{
				p = p1;
				p1 = p1->next;
			}
			else break;
		}
		p->next = p2;
		if (!p1)break;
		p = p2;
		p2 = p2->next;
		p->next = p1;
	}
	return L1;
}

void PrintList(LinkList L)
{
	LinkList p = L->next;
	while (p)
	{
		cout << p->data<<" ";
		p = p->next;
	}
	cout << endl;
}

int main()
{
	int a,b;
	LinkList L1=NULL,L2=NULL,head1=NULL,head2=NULL;
	if (InitList(L1) && InitList(L2))
	{
		head1 = L1, head2 = L2;
		cin >> a >> b;
		while (a != 0 && b != 0)
		{
				InsertList(L1, a); InsertList(L2, b);
			    cin >> a >> b;
		}
	}
	PrintList(head1);
	PrintList(head2);
	CombineList2(head1, head2);
	PrintList(head1);
	PrintList(head2);
	DeleteList(head1, 2);
	PrintList(head1);
	return 0;
}

//  1 2 3 4 5 6 7 8 0 0