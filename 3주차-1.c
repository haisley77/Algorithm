/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int H[100] = {0};
// Èü
int n = 0;
// Èü Å©±â


void upHeap(int i) {
	int tmp;
	if (i == 1) return;

	if (H[i / 2] < H[i]) {
		tmp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = tmp;
		upHeap(i / 2);
	}
	else return;

}

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

void insertItem(int key) {
	H[n + 1] = key;
	upHeap(n + 1);
	n++;
	return;
}



int removeMax(void) {
	int r_key = H[1];
	H[1] = H[n];
	H[n] = 0;
	downHeap(1);
	n--;
	return r_key;
}




void printHeap(void) {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}



void main() {

	char ch;
	int key;


	
	while (1) {
		scanf("%c", &ch);
		getchar();

		if (ch == 'i') {
			scanf("%d", &key);
			getchar();
			insertItem(key);
			printf("0\n");
		}
		else if (ch == 'd') {
			printf("%d\n",removeMax());
		}
		else if (ch == 'p') {
			printHeap();
		}
		else if (ch == 'q') {
			break;
			// ÇÁ·Î±×·¥ Á¾·á
		}
	}

	return;
}
*/