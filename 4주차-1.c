#include <stdio.h>
#pragma warning (disable:4996)

int H[100] = { 0 };
int n = 0;

void inPlaceHeapSort(void);
void printArray(void);
void downHeap(int i);
void insertItem(int key);
void upHeap(int i);
void rBuildHeap(int i);
void buildHeap(void);



int main() {

	inPlaceHeapSort();
	printArray();

	return 0;
}


void inPlaceHeapSort(void) {

	int key, key_n;

	scanf("%d", &key_n);
	getchar();
	// 키 개수 입력

	for (int i = 1; i <= key_n; i++) {
		scanf("%d", &key);
		insertItem(key);
	}
	// 삽입식 힙 생성 (1기)

	int tmp;

	while (n != 0) {
		tmp = H[1];
		H[1] = H[n];
		H[n] = tmp;
		n--;
		downHeap(1);
	}
	// 힙 오름차순 정렬 (2기)

	return;
}

void printArray(void) {
	int i = 1;
	while (H[i] != 0) {
		printf(" %d", H[i]);
		i++;
	}
}


void downHeap(int i) {
	int tmp;
	int left, right;

	left = 2 * i;
	right = 2 * i + 1;

	if (left > n && right > n) return;

	if (right <= n) {
		if (H[left] < H[right]) {
			if (H[right] > H[i]) {
				tmp = H[i];
				H[i] = H[right];
				H[right] = tmp;
				downHeap(right);
			}
		}
		if (H[left] > H[right]) {
			if (H[left] > H[i]) {
				tmp = H[i];
				H[i] = H[left];
				H[left] = tmp;
				downHeap(left);
			}
		}
	}
	else if (left <= n) {
		if (H[left] > H[i]) {
			tmp = H[i];
			H[i] = H[left];
			H[left] = tmp;
			downHeap(left);
		}
	}
	else return;

}

void insertItem(int key) {
	H[n + 1] = key;
	n++;
	upHeap(n);
	return;
}

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

void rBuildHeap(int i) {
	if (i > n) return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
	return;
}

void buildHeap(void) {

	for (int i = n / 2; i > 0; i--) {
		downHeap(i);
	}
	return;

}