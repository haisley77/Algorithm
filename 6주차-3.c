#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


int findk(int a, int b, int n) {
	char ch;

	for (int i = 0; i < n; i++) {
		scanf("%c", &ch);
		// 문자 하나 읽어들이기

		int mid = (a + b) / 2;
		// 중간 인덱스 mid 변수에 저장

		if (ch == 'Y') {
			a = mid + 1;
		}
		if (ch == 'N') {
			b = mid;
		}
	}

	// k를 찾기 위한 정확한 수의 답이 주어진다고 가정했으므로 a != b 가 되는 경우는 고려하지 않아도 됨

	return a;
}

int main() {
	int a, b, n;

	scanf("%d %d %d", &a, &b, &n);
	getchar();

	printf("%d", findk(a, b, n));
	
	return 0;
}