/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

int main() {
	int n, save, j;
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


	for (int pass = 1; pass < n; pass++) {
		save = arr[pass];
		j = pass - 1;
		// save 변수에 pass 인덱스의 arr 배열값 저장
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = save;
		// 정렬된 arr 배열에 save 값 삽입
	}




	for (int i = 0; i < n; i++) printf(" %d", arr[i]);
	// 정렬된 배열값 출력



	free(arr);
	// 메모리 해제

	return 0;
}
*/