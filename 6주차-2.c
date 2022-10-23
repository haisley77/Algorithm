/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


int n;
int mini = -2;
// 초기 mini

int findkindex(int* A, int k, int l, int r) {

	while (1) {
		if (l > r) break;
		// 탐색 시작 인덱스 > 탐색 끝 인덱스 : 반복 탈출

		int i = (l + r) / 2;
		// l과 r 중간값 i

		if (A[i] == k) {
			return i;
		}
		else if (A[i] < k) {
			l = i + 1;
			// 중간 인덱스 원소가 k 보다 작으면 탐색 시작 인덱스 i+1 로 재설정
		}
		else {
			if (mini == -2 || A[mini] > A[i]) {
				mini = i;
			}
			// mini 값 재설정
			r = i - 1;
			// 중간 인덱스 원소가 k 보다 크면 탐색 끝 인덱스 i-1 로 재설정
		}

	}

	return n;
	
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

	if (result == n) {
		if (mini == -2) printf(" %d", result);
		// 입력된 값이 하나인데 k 보다 작은 수일 경우
		else printf(" %d", mini);
		// 배열 값 중 k 와 일치하는 수가 없는 경우
	}
	else printf(" %d", result);
	// 배열 값 중 k와 일치하는 수가 있는 경우

	free(A);
	// 메모리 해제

	return 0;
}
*/