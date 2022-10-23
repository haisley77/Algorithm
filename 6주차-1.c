
/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int n;
int maxi = -2;
// 초기 maxi

int findkindex(int* A, int k, int l, int r) {
	

	int i = (l + r) / 2;
	// l과 r의 중간 값 i

	if (l > r) {
		return -1;
	}
	// 재귀 베이스 케이스 처리
	
	if (k == A[i]) {
		return i;
	}
	else if (k < A[i]) {
		return findkindex(A, k, l, i - 1);
	}
	else {
		if (maxi == -2 || A[maxi] < A[i]) {
			maxi = i;
		}
		// maxi 재설정
		return findkindex(A, k, i + 1, r);
	}

}

int main() {
	int k, i;
	scanf("%d %d", &n, &k);
	int* A = (int*)malloc(sizeof(int) * n);
	// 배열 동적할당

	for (i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	// 배열 값 입력

	int result = findkindex(A, k, 0, n - 1);
	// k와 일치하는 값의 인덱스를 result에 저장

	if (result == -1) {
		if (maxi == -2) printf(" %d", result);
		// 입력된 값이 하나인데 k 보다 큰 수일 경우
		else printf(" %d", maxi);
		// 배열 값 중 k 와 일치하는 수가 없는 경우
	}
	else printf(" %d", result);
	// 배열 값 중 k와 일치하는 수가 있는 경우

	free(A);
	// 메모리 해제

	return 0;
}
*/