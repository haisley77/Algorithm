// 계속 안 풀린 이유. findPivot 함수 난수 생성 범위 잘못 씀;;; 아 짜증나 ㅠㅠ
// 그래도 inPlacePartition 함수는 완벽하게 이해했다. 다행인건가?

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
// 배열 L의 원소를 출력하는 함수

int findPivot(int* L, int l, int r) {

	srand((unsigned)time(NULL));
	int pivot = rand() % (r - l + 1) + l;
	
	return pivot;
}
// 무작위로 피벗 위치 결정 및 반환하는 함수

Range inPlacePartition(int* L, int l, int r, int k) {
	Range p;
	int i, j, temp, elem;
	i = l;
	j = r - 1;

	elem = L[k];

	temp = L[k];
	L[k] = L[r];
	L[r] = temp;
	// 피벗(k번째 원소)을 마지막 원소와 swap & hide


	while (i <= j) {
		while (i<=j && L[i] < elem) {
			i++;
		}
		// 피벗보다 작은 원소를 피벗 기준 왼쪽으로 모으기

		while (i<=j && L[j] >= elem) {
			j--;
		}
		// 피벗보다 크거나 같은 원소를 피벗 기준 오른쪽으로 모으기

		if (i < j) {
			temp = L[i];
			L[i] = L[j];
			L[j] = temp;
		}
	}
	temp = L[i];
	L[i] = L[r];
	L[r] = temp;
	// i 위치로 숨겨둔 피벗 가져오기 (피벗위치 i)

	p.a = i;
	p.b = i;
	// a,b값을 초기 피벗위치 i로 설정

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
	// 크기가 n인 배열 L 동적 할당

	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}
	// 배열 L 입력

	inPlaceQuickSort(L, 0, n - 1);
	printArray(L, n);

	free(L);

	return 0;
}