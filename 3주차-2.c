#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int H[100] = { 0 };
// �� ����
int n;
// ���� ũ��

void downHeap(int i) {
	int tmp;

	if (i == n - 1) return;

	if (H[2 * i] > H[i] || H[2 * i + 1] > H[i]) {
		if (H[2 * i] < H[2 * i + 1]) {
			tmp = H[i];
			H[i] = H[2 * i + 1];
			H[2 * i + 1] = tmp;
			downHeap(2 * i + 1);
		}
		else {
			tmp = H[i];
			H[i] = H[2 * i];
			H[2 * i] = tmp;
			downHeap(2 * i);
		}
	}
	else return;

}

void rBuildHeap(int i) {
	if (i > n) return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
	return;
}

void buildHeap(void) {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
	return;
}




void main() {

	scanf("%d", &n);
	getchar();
	// Ű ����

	for (int i = 1; i <= n; i++) scanf("%d", &H[i]);
	// �ʱ� �迭�� Ű ����

	buildHeap();

	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}



	return;
}