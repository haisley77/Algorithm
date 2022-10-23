#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable:4996)


void writeList(int* L, int n) {
	for (int i = 1; i <= n; i++) {
		printf(" %d", L[i]);
	}
	printf("\n");
}

void downheap(int* L, int i, int n) {

	int tmp;
	int left, right;

	left = 2 * i;
	right = 2 * i + 1;
	

	if (left > n && right > n) return;

	if (right <= n) {
		if (L[left] > L[right]) {
			if (L[right] < L[i]) {
				tmp = L[i];
				L[i] = L[right];
				L[right] = tmp;
				downheap(L, right, n);
			}
		}
		else {
			if (L[left] < L[i]) {
				tmp = L[i];
				L[i] = L[left];
				L[left] = tmp;
				downheap(L, left, n);
			}
		}
	}
	else if (left <= n) {
		if (L[left] < L[i]) {
			tmp = L[i];
			L[i] = L[left];
			L[left] = tmp;
			downheap(L, left, n);
		}
	}
	else return;

}

void rBuildHeap(int i, int* L, int n) {

	if (i < n) {
		rBuildHeap(2 * i, L, n);
		rBuildHeap(2 * i + 1, L, n);
		downheap(L, i, n);
	}
	
	return;
}
// ����� �ּ��� ��������� �����ϴ� �Լ�


int findKthSmallest(int* L, int n, int k) {

 	rBuildHeap(1, L, n);

	// ����� �ּ��� ���� O(n) ����ð�

	int tmp;
	for (int i = 0; i < k; i++) {
		tmp = L[n];
		L[n] = L[1];
		L[1] = tmp;
		n--;
		downheap(L, 1, n);
	}
	
	// �� ���� O(klogn) ����ð�


	return L[n + 1];
}
// k��° ���� ���� O(n + klogn) �ð��� ã�� �Լ�


int* buildList(int n, int min, int max) {

	int* L = (int*)malloc(sizeof(int) * (n + 1));

	srand(time(NULL));
	for (int i = 1; i <= n; i++) {
		L[i] = rand() % (max - min + 1) + min;
	}

	L[0] = 0;
	return L;
}

void copy(int* H, int* L, int n) {
	for (int i = 1; i <= n; i++) {
		H[i] = L[i];
	}
	return;
}
// �迭 L�� �迭 H�� �����ϴ� �Լ�


int main() {

	int e;
	double t;
	clock_t start, end;
	int output[4] = { 0 };
	int karray[4] = { 1,100, 99900,99999 };

	int* L = buildList(10, 1, 100);

	writeList(L, 10);

	int* H1 = (int*)malloc(sizeof(int) * 11);
	copy(H1, L, 10);
	// �����Ҵ��� H1 �迭�� ����Ʈ L ����

	for (int k = 1; k <= 3; k++) {
		output[k] = findKthSmallest(L, 10, k);

		copy(L, H1, 10);
		// ���� findKthSmallest �Լ� ȣ�� �� ���� L�� �ʱ� ����Ʈ�� �ǵ��� �ʱ� ����Ʈ�� ������ H1 �迭�� L�� ����
	}
	
	printf("%d %d %d\n", output[1], output[2], output[3]);

	free(L);
	free(H1);
	// �޸� ����


	
	L = buildList(100000, 1, 1000000);


	int* H2 = (int*)malloc(sizeof(int) * 100001);
	copy(H2, L, 100000);
	// �����Ҵ��� H2 �迭�� ����Ʈ L ����

	for (int k = 0; k < 4; k++) {
		start = clock();
		e = findKthSmallest(L, 100000, karray[k]);
		end = clock();

		t = (double)(end - start);
		// CPUtime ����

		copy(L, H2, 100000);
		// ���� findKthSmallest �Լ� ȣ�� �� ���� L�� �ʱ� ����Ʈ�� �ǵ��� �ʱ� ����Ʈ�� ������ H2 �迭�� L�� ����

		printf("%d %lf\n", e, t);

		
	}

	free(L);
	free(H2);
	// �޸� ����



	return 0;
}
