
/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int n;
int maxi = -2;
// �ʱ� maxi

int findkindex(int* A, int k, int l, int r) {
	

	int i = (l + r) / 2;
	// l�� r�� �߰� �� i

	if (l > r) {
		return -1;
	}
	// ��� ���̽� ���̽� ó��
	
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
		// maxi �缳��
		return findkindex(A, k, i + 1, r);
	}

}

int main() {
	int k, i;
	scanf("%d %d", &n, &k);
	int* A = (int*)malloc(sizeof(int) * n);
	// �迭 �����Ҵ�

	for (i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	// �迭 �� �Է�

	int result = findkindex(A, k, 0, n - 1);
	// k�� ��ġ�ϴ� ���� �ε����� result�� ����

	if (result == -1) {
		if (maxi == -2) printf(" %d", result);
		// �Էµ� ���� �ϳ��ε� k ���� ū ���� ���
		else printf(" %d", maxi);
		// �迭 �� �� k �� ��ġ�ϴ� ���� ���� ���
	}
	else printf(" %d", result);
	// �迭 �� �� k�� ��ġ�ϴ� ���� �ִ� ���

	free(A);
	// �޸� ����

	return 0;
}
*/