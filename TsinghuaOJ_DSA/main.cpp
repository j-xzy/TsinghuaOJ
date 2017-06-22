// TsinghuaOJ_DSA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void quicksort(unsigned int *R, int left, int right)
{
	int i = left, j = right; int temp = R[i];
	while (i<j) {
		while ((R[j]>temp) && (j>i)) j = j - 1;
		if (j>i) { R[i] = R[j]; i = i + 1; }
		while ((R[i] <= temp) && (j>i)) i = i + 1;
		if (i<j) { R[j] = R[i]; j = j - 1; }
	}
	R[i] = temp;
	if (left<i - 1) quicksort(R, left, i - 1);
	if (i + 1<right) quicksort(R, i + 1, right);
}

int leftSearch(unsigned int *A, unsigned int const&e, unsigned int lo, unsigned int hi) {
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		if (e < A[mi]) {
			hi = mi;
		}
		else if (e > A[mi])
		{
			lo = mi + 1;
		}
		else
		{
			return mi - 1;
		}
	}
	return --lo;
}

int RightSearch(unsigned int *A, unsigned int const&e, unsigned int lo, unsigned int hi) {
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		if (e < A[mi]) {
			hi = mi;
		}
		else if (e > A[mi])
		{
			lo = mi + 1;
		}
		else
		{
			return mi;
		}
	}
	return --lo;
}



int main()
{
	int n, m;
	//cout << "����n(�������),m(��ѯ����),�ո�ֿ����س�����\n";
	cin >> n >> m;
	unsigned int *left = new unsigned int[m];
	unsigned int *right = new unsigned int[m];
	unsigned int *T = new unsigned int[n];
    //cout << "����X���ϸ�������,�ո�ֿ����س�����\n";
	for (int i = 0; i < n; i++) {
		cin >> T[i];
	};
	//cout << "�������ұ߽�,�ո�ֿ����س�����\n";
	for (int i = 0; i < m; i++) {
		cin >> left[i];
		cin >> right[i];
	}
	quicksort(T, 0, n);
	for (int i = 0; i < m; i++)
	{
		int rankLeft = leftSearch(T, left[i], 0, n);
		int rankRight = RightSearch(T, right[i],0, n);
		int result = rankRight - rankLeft;
		cout << result;
		cout << "\n";
	}
}

