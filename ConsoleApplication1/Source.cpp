#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define MAX 2000

/*祖玛色块类*/
struct Zuma {
	char date;
	Zuma *up;
	Zuma *down;
	Zuma() {};
	Zuma(char s) :date(s) {};

}*header, *tailer;    //首尾哨兵

char s[MAX];
int length;    //链表长度
int k;    //记录数据长度

		  /*双向链表-尾插法*/
void Creat_zuma(char *s)
{
	header = new Zuma();
	header->up = NULL;

	Zuma *rear = header;    //定义尾部指针-穿针
	for (int i = 0; i < length; i++)
	{
		Zuma *p = new Zuma(s[i]);
		rear->down = p;
		p->up = rear;

		rear = p;    //换针
	}
	tailer = new Zuma();
	rear->down = tailer;
	tailer->up = rear;
	tailer->down = NULL;
}

/*遍历查找pos位置的指针*/
Zuma* Find(int pos)
{
	int counter = 0;
	Zuma *p = header;
	if (length - pos >= pos)    //首部遍历
	{
		while (counter < pos && p->down != tailer)
		{
			p = p->down;
			counter++;
		}
	}
	else {                        //尾部遍历
		p = tailer;
		counter = length;
		while (counter >= pos && p->up != header)
		{
			p = p->up;
			counter--;
		}

	}
	return p;
}

/*消除*/
Zuma* Remove(Zuma *cur, char c)
{
	while (1)
	{
		Zuma *pre = cur->down;
		int counter = 0;
		while (cur != header && cur->date == c)    //向前查重
		{
			cur = cur->up;
			counter++;
		}
		while (pre != tailer && pre->date == c)    //向后查重
		{
			pre = pre->down;
			counter++;
		}
		if (counter >= 3)    //重复元素大于三个
		{
			length -= counter;
			Zuma *p1 = cur->down, *p2;
			while (p1 != pre)    //delete
			{
				p2 = p1->down;
				delete p1;
				p1 = p2;
			}
			cur->down = pre;
			if (pre != NULL)
				pre->up = cur;
			c = cur->date;
		}
		else break;
	}
	return cur;
}

/*插入*/
void Insert(Zuma *p, char c)
{
	Zuma *x = new Zuma(c);
	if (p->down != NULL)
	{
		x->up = p;
		x->down = p->down;
		p->down->up = x;
		p->down = x;
	}
	else {
		x->up = p;
		x->down = NULL;
		p->down = x;

	}
	length++;
}
int main()
{
	int n;
	fgets(s,200,stdin);
	scanf_s("%d", &n);
	length = strlen(s);
	/*搭建*/
	Creat_zuma(s);

	for (int t = 0; t < n; t++)
	{
		char c;
		int pos;
		scanf_s("%d %c", &pos, &c);
		Zuma *p = Find(pos);
		Insert(p, c);
		Zuma *flag = Remove(p, c);
		/*Record*/
		if (flag == header && flag->down == tailer)
		{
			s[k++] = '-';
			s[k++] = '\n';
		}
		else {
			flag = header;
			while (flag->down != tailer)
			{
				s[k++] = flag->down->date;
				flag = flag->down;
			}
			s[k++] = '\n';

		}
		/*Single Input*/
		if (t == n - 1)
		{
			s[k] = '\0';
			printf("%s", s);
			k = 0;
		}
	}
	return 0;
}