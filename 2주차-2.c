/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

int main() {
	int n, save, j;
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


	for (int pass = 1; pass < n; pass++) {
		save = arr[pass];
		j = pass - 1;
		// save ������ pass �ε����� arr �迭�� ����
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = save;
		// ���ĵ� arr �迭�� save �� ����
	}




	for (int i = 0; i < n; i++) printf(" %d", arr[i]);
	// ���ĵ� �迭�� ���



	free(arr);
	// �޸� ����

	return 0;
}
*/