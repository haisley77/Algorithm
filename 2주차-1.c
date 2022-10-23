/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

int main() {

	int n, maxindex;
	int* arr;
	int tmp;
	// swap 변수

	scanf("%d", &n);
	getchar();
	// n 입력
	arr = (int*)malloc(sizeof(int) * n);
	// 크기 n인 배열 동적 할당
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	// 배열 값 입력
	

	for (int pass = n - 1; pass > 0; pass--) {
		maxindex = pass;
		for (int i = pass - 1; i >= 0; i--) {
			if (arr[i] > arr[maxindex]) maxindex = i;
		}
		tmp = arr[pass];
		arr[pass] = arr[maxindex];
		arr[maxindex] = tmp;
	}
	



	for (int i = 0; i < n; i++) printf(" %d", arr[i]);



	free(arr);

	return 0;
}
*/
