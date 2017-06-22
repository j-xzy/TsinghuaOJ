#include <stdio.h>

#define Max 4000005
long result;
long lx[Max];
long ly[Max];

//øÏÀŸ≈≈–Ú
void quickSort(long low, long high)
{
	long i = low;
	long j = high;
	long x = lx[low];
	long y = ly[low];
	do {
		while (lx[i] < x) i++;
		while (lx[j] > x) j--;
		if (i <= j) {
			long tx = lx[i];
			long ty = ly[i];
			lx[i] = lx[j];
			ly[i] = ly[j];
			lx[j] = tx;
			ly[j] = ty;
			i++; j--;
		}
	} while (i <= j);
	if (i < high) quickSort(i, high);
	if (j > low) quickSort(low, j);
}

void merge(long low, long mid, long hi) {
	long *A = ly + low;
	long lb = mid - low;
	long *B = new long[lb];
	for (long i = 0; i < lb; B[i] = A[i++]);
	long lc = hi - mid; long *C = ly + mid;
	for (long i = 0, j = 0, k = 0; j < lb;) {
		if ((k >= lc || B[j] <= C[k])) {
			A[i++] = B[j++];
			result += lc - k;
		}
		if (k < lc && C[k] < B[j]) {
			A[i++] = C[k++];
		}
	}
}

//πÈ≤¢
void mergeSort(long low, long hi) {
	if (hi - low < 2)return;
	long mid = (low + hi) >> 1;
	mergeSort(low, mid);
	mergeSort(mid, hi);
	merge(low, mid, hi);
}

int main() {
	long n;
	scanf("%d", &n);
	for (long i = 0; i < n; i++) {
		scanf("%d%d", &lx[i], &ly[i]);
	}
	quickSort(0, n - 1);
	mergeSort(0, n);//[0,n)
	printf("%d\n", result);
	return 0;
}