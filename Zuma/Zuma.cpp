#include <cstdio>
#include <iostream>
#include <cstring>

#define Max 200
int length;
struct node
{
	char data;
	node *pre;
	node *succ;
	node() {}
	node(char s) :data(s) {}
}*header, *tailer;

void createZuma(char *chars, int length) {
	header = new node();
	tailer = new node();
	header->data = NULL; header->pre = NULL;
	tailer->data = NULL; tailer->succ = NULL;
	node *h = header;
	for (int i = 0; i < length; i++)
	{
		node *rear = new node(chars[i]);
		rear->pre = h;
		h->succ = rear;
		h = rear;
	}
	h->succ = tailer;
	tailer->pre = h;
}

node* insert(int posi, char c) {
	node *h;
	if (posi < length >> 1)
	{
		h = header;
		for (int i = 0; i <= posi; i++)
		{
			h = h->succ;
		}
	}
	else
	{
		int n = length - posi;
		h = tailer;
		for (int i = 0; i < n; i++)
		{
			h = h->pre;
		}
	}
	length++;
	node *p = new node(c);
	p->pre = h->pre; p->succ = h;
	h->pre->succ = p; h->pre = p;
	return p;
}

void remove(node *p, int posi, char c)
{
	while (1)
	{
		node *h = p;
		node *t = p;
		int count = 1;
		//向后查找
		while ((t != tailer) && ((t = t->succ )->data== c))
		{
			count++;
		}
		//向前查找
		while ((h != header) && ((h = h->pre)->data == c))
		{
			count++;
		}
		if (2 < count)
		{
			length -= count;
			node *p1 = h->succ, *p2;
			for (int i = 0; i < count; i++) {
				p2 = p1->succ;
				delete p1;
				p1 = p2;
			}
			h->succ = t;
			t->pre = h;
			p = h;
			c = p->data;
		}
		else
		{
			break;
		}
	}
}

int main() {
	char chars[Max];
	int n;
	gets_s(chars);
	scanf_s("%d", &n);
	length = strlen(chars);
	//创建祖玛
	createZuma(chars, length);
	int posi[Max]; char c[Max];
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d %c", &posi[i], &c[i]);
	}
	for (int i = 0; i < n; i++)
	{
		node *p = insert(posi[i], c[i]);
		remove(p, posi[i], c[i]);
		node *pp = header;
		pp = header;
		printf("%c", '\n');
		if (length == 0) {
			printf("%c", '-');
		}
		for (int i = 0; i < length; i++)
		{
			printf("%c", (pp = pp->succ)->data);
		}
	}
}