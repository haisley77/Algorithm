/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

int main() {

	int n, maxindex;
	int* arr;
	int tmp;
	// swap ����

	scanf("%d", &n);
	getchar();
	// n �Է�
	arr = (int*)malloc(sizeof(int) * n);
	// ũ�� n�� �迭 ���� �Ҵ�
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	// �迭 �� �Է�
	

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
