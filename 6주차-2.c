/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


int n;
int mini = -2;
// �ʱ� mini

int findkindex(int* A, int k, int l, int r) {

	while (1) {
		if (l > r) break;
		// Ž�� ���� �ε��� > Ž�� �� �ε��� : �ݺ� Ż��

		int i = (l + r) / 2;
		// l�� r �߰��� i

		if (A[i] == k) {
			return i;
		}
		else if (A[i] < k) {
			l = i + 1;
			// �߰� �ε��� ���Ұ� k ���� ������ Ž�� ���� �ε��� i+1 �� �缳��
		}
		else {
			if (mini == -2 || A[mini] > A[i]) {
				mini = i;
			}
			// mini �� �缳��
			r = i - 1;
			// �߰� �ε��� ���Ұ� k ���� ũ�� Ž�� �� �ε��� i-1 �� �缳��
		}

	}

	return n;
	
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

	if (result == n) {
		if (mini == -2) printf(" %d", result);
		// �Էµ� ���� �ϳ��ε� k ���� ���� ���� ���
		else printf(" %d", mini);
		// �迭 �� �� k �� ��ġ�ϴ� ���� ���� ���
	}
	else printf(" %d", result);
	// �迭 �� �� k�� ��ġ�ϴ� ���� �ִ� ���

	free(A);
	// �޸� ����

	return 0;
}
*/