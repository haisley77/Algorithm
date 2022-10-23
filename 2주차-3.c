#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning (disable:4996)


int main() {

	int n, maxindex, minindex, tmp, save;
	int* A, * B;
	int j;

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;


	scanf("%d", &n);
	
	A = (int*)malloc(sizeof(int) * n);
	B = (int*)malloc(sizeof(int) * n);
	// 크기 n 배열 동적 할당

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = B[i] = rand();
	}
	// 배열 A,B 동일한 난수로 초기화

	/*
	for (int pass = n - 1; pass > 0; pass--) {
		maxindex = pass;
		for (int i = pass - 1; i >= 0; i--) {
			if (A[i] > A[maxindex]) maxindex = i;
		}
		tmp = A[pass];
		A[pass] = A[maxindex];
		A[maxindex] = tmp;
	}
	for (int pass = n - 1; pass > 0; pass--) {
		maxindex = pass;
		for (int i = pass - 1; i >= 0; i--) {
			if (B[i] > B[maxindex]) maxindex = i;
		}
		tmp = B[pass];
		B[pass] = B[maxindex];
		B[maxindex] = tmp;
	}
	// 배열 A,B 정렬 (오름차순)
	*/
	
	for (int pass = n - 1; pass > 0; pass--) {
		minindex = pass;
		for (int i = pass - 1; i >= 0; i--) {
			if (A[i] < A[minindex]) minindex = i;
		}
		tmp = A[pass];
		A[pass] = A[minindex];
		A[minindex] = tmp;
	}
	for (int pass = n - 1; pass > 0; pass--) {
		minindex = pass;
		for (int i = pass - 1; i >= 0; i--) {
			if (B[i] < B[minindex]) minindex = i;
		}
		tmp = B[pass];
		B[pass] = B[minindex];
		B[minindex] = tmp;
	}
	// 배열 A,B 정렬 (내림차순)

	



	
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 선택 정렬
	for (int pass = n-1; pass > 0 ; pass--) {
		maxindex = pass;
		for (int i = pass-1; i >= 0; i--) {
			if (A[i] > A[maxindex]) maxindex = i;
		}
		tmp = A[pass];
		A[pass] = A[maxindex];
		A[maxindex] = tmp;
	}
	QueryPerformanceCounter(&end);
	
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.9f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart)*1000);


	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 삽입 정렬
	for (int pass = 1; pass < n; pass++) {
		save = B[pass];
		j = pass - 1;
		while ((j >= 0) && (B[j] > save)) {
			B[j + 1] = B[j];
			j--;
		}
		B[j + 1] = save;
	}
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.9f ms", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


	free(A);
	free(B);
	// 메모리 해제

	return 0;
}
