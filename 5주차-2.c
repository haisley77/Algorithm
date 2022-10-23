// ��� �� Ǯ�� ����. findPivot �Լ� ���� ���� ���� �߸� ��;;; �� ¥���� �Ф�
// �׷��� inPlacePartition �Լ��� �Ϻ��ϰ� �����ߴ�. �����ΰǰ�?

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable:4996)

typedef struct range {
	int a;
	int b;
} Range;

void printArray(int* L, int n) {
	for (int i = 0; i < n; i++) {
		printf(" %d", L[i]);
	}
	printf("\n");
}
// �迭 L�� ���Ҹ� ����ϴ� �Լ�

int findPivot(int* L, int l, int r) {

	srand((unsigned)time(NULL));
	int pivot = rand() % (r - l + 1) + l;
	
	return pivot;
}
// �������� �ǹ� ��ġ ���� �� ��ȯ�ϴ� �Լ�

Range inPlacePartition(int* L, int l, int r, int k) {
	Range p;
	int i, j, temp, elem;
	i = l;
	j = r - 1;

	elem = L[k];

	temp = L[k];
	L[k] = L[r];
	L[r] = temp;
	// �ǹ�(k��° ����)�� ������ ���ҿ� swap & hide


	while (i <= j) {
		while (i<=j && L[i] < elem) {
			i++;
		}
		// �ǹ����� ���� ���Ҹ� �ǹ� ���� �������� ������

		while (i<=j && L[j] >= elem) {
			j--;
		}
		// �ǹ����� ũ�ų� ���� ���Ҹ� �ǹ� ���� ���������� ������

		if (i < j) {
			temp = L[i];
			L[i] = L[j];
			L[j] = temp;
		}
	}
	temp = L[i];
	L[i] = L[r];
	L[r] = temp;
	// i ��ġ�� ���ܵ� �ǹ� �������� (�ǹ���ġ i)

	p.a = i;
	p.b = i;
	// a,b���� �ʱ� �ǹ���ġ i�� ����

	while (p.b <= r) {
		if (L[p.a] != L[p.b]) {
			p.b--;
			break;
		}
		p.b++;
	}

	return p;
}

void inPlaceQuickSort(int* L, int l, int r) {
	int k;
	if (l >= r) return;

	k = findPivot(L, l, r);

	Range p = inPlacePartition(L, l, r, k);

	inPlaceQuickSort(L, l, p.a - 1);
	inPlaceQuickSort(L, p.b + 1, r);
	
	return;
}


int main() {

	int n;
	scanf("%d", &n);

	int* L = (int*)malloc(sizeof(int) * n);
	// ũ�Ⱑ n�� �迭 L ���� �Ҵ�

	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}
	// �迭 L �Է�

	inPlaceQuickSort(L, 0, n - 1);
	printArray(L, n);

	free(L);

	return 0;
}